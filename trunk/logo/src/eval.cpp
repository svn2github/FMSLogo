/*
*      eval.cpp          logo eval/apply module                  dko
*
*       Copyright (C) 1995 by the Regents of the University of California
*       Copyright (C) 1995 by George Mills
*
*      This program is free software; you can redistribute it and/or modify
*      it under the terms of the GNU General Public License as published by
*      the Free Software Foundation; either version 2 of the License, or
*      (at your option) any later version.
*
*      This program is distributed in the hope that it will be useful,
*      but WITHOUT ANY WARRANTY; without even the implied warranty of
*      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*      GNU General Public License for more details.
*
*      You should have received a copy of the GNU General Public License
*      along with this program; if not, write to the Free Software
*      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*
*/
#include <stdio.h>
#include <setjmp.h>

#include "eval.h"
#include "init.h"
#include "files.h"
#include "main.h"
#include "graphwin.h"
#include "mem.h"
#include "error.h"
#include "print.h"
#include "logomath.h"
#include "coms.h"
#include "paren.h"
#include "status.h"
#include "ibmterm.h"
#include "localizedstrings.h"
#include "wrksp.h"
#include "parse.h"
#include "unix.h"
#include "intern.h"
#include "lists.h"
#include "startup.h"
#include "debugheap.h"

#define assign(to, from)    (to = reref(to, from))

// save/restore a NODE
#define save(register)      push(register, stack)
#define restore(register)   (assign(register, car(stack)), pop(stack))

// save/restore two NODEs
#define save2(reg1,reg2)    (push(reg1,stack),setobject(stack,reg2))
#define restore2(reg1,reg2) (assign(reg2,getobject(stack)), \
           assign(reg1,car(stack)), pop(stack))

// save/restore a FIXNUM
#define numsave(register)   numpush(register, &stack)
#define numrestore(register) (register=(FIXNUM)car(stack), numpop(&stack))

// save/restore two FIXNUMs
#define num2save(reg1,reg2) (numpush(reg1,&stack),stack->nunion.ncons.nobj=(NODE *)reg2)
#define num2restore(reg1,reg2) (reg2=(FIXNUM)getobject(stack), \
           reg1=(FIXNUM)car(stack), numpop(&stack))

// save/restore a FIXNUM (reg1) and a NODE (reg2)
#define mixsave(reg1,reg2)  (numpush(reg1,&stack),setobject(stack,reg2))
#define mixrestore(reg1,reg2) deref(reg2); reg2=getobject(stack); \
           reg1=(FIXNUM)car(stack); numpop(&stack)

#define newcont(tag)        (numsave(cont), cont = (FIXNUM)tag)

#define nameis(x,y)         ((object__caseobj(x)) == (object__caseobj(y)))

inline
bool
IsInMacro(
    FIXNUM ValueStatus
    )
{
    return 
        ValueStatus == VALUE_STATUS_NoValueInMacro ||
        ValueStatus == VALUE_STATUS_ValueMaybeOkInMacro;
}

NODE *fun = NIL;                 // current function name
NODE *ufun = NIL;                // current user-defined function name
NODE *last_ufun = NIL;           // the function that called this one
NODE *this_line = NIL;           // the current instruction line
NODE *last_line = NIL;           // the line that called this one
NODE *last_call = NIL;           // the last proc called
NODE *didnt_output_name = NIL;   // the name of the proc that didn't OP
NODE *didnt_get_output = NIL;    // the name of the proc that wanted the OP
NODE *output_node = NIL;         // the output of the current function
FIXNUM repcountup;               // up count for repeat

CTRLTYPE stopping_flag = RUN;
FIXNUM tailcall;    // 0 in sequence, 1 for tail, -1 for arg

FIXNUM g_ValueStatus;

FIXNUM dont_fix_ift = 0;

long eval_count = 0;             // current count of "evaluations" calls

int g_CatchErrorCount = 0;       // the number of nested blocks of CATCH "ERROR
                                 // This is used to disable "ERRACT processing.

bool traceflag = false;          // Flag to signal trace button is active
bool stepflag = false;           // Flag to signal step button is active

static NODE *qm_list = NIL;      // question mark list
static int trace_level = 0;      // indentation level when tracing

static NODE *var       = NIL;    // frame pointer into var_stack
static NODE *var_stack = NIL;    // the stack of variables and their bindings

static int halt_flag = 0;        // Flag to signal it's OK to halt


// Load the definition of ProcNode if the definition of ProcNode
// is currently UNDEFINED.
//
// Return the case object of ProcNode, if successful.
// Return UNDEFINED, otherwise.
NODE *
load_procedure_if_necessary(
    NODE * ProcNode
    )
{
    // try loading from ./<proc>.lgo
    if (procnode__caseobj(ProcNode) == UNDEFINED && 
        NOT_THROWING &&
        ProcNode != Null_Word)
    {
        silent_load(ProcNode, NULL);
    }

    // try loading from <logolib>/<proc>
    if (procnode__caseobj(ProcNode) == UNDEFINED && 
        NOT_THROWING &&
        ProcNode != Null_Word)
    {
        silent_load(ProcNode, LibPathName);
    }

    return procnode__caseobj(ProcNode);
}

void spop(NODE **stack)
{
    assert(stack != NULL && "bad input");
    assert(*stack != NIL && "popping from an empty stack");

    NODE *temp = (*stack)->nunion.ncons.ncdr;

    if (decrefcnt(*stack) == 0)
    {
        (*stack)->nunion.ncons.ncdr = NIL;
        gc(*stack);
    }
    else
    {
        if (temp != NIL) 
        {
            increfcnt(temp);
        }
    }
    *stack = temp;
}

void spush(NODE *obj, NODE **stack)
{
    assert(stack != NULL && "bad input");

    NODE *temp = newnode(CONS);

    setcar(temp, obj);
    temp->nunion.ncons.ncdr = *stack;
    ref(temp);
    *stack = temp;
}

static
void numpop(NODE **stack)
{
    NODE *temp = (*stack)->nunion.ncons.ncdr;

    (*stack)->nunion.ncons.ncar = NIL;
    (*stack)->nunion.ncons.ncdr = NIL;
    (*stack)->nunion.ncons.nobj = NIL;
    deref(*stack);
    *stack = temp;
}

static
void numpush(FIXNUM obj, NODE **stack)
{
    NODE *temp = newnode(CONS);

    temp->nunion.ncons.ncar = (NODE *) obj;
    temp->nunion.ncons.ncdr = *stack;
    ref(temp);
    *stack = temp;
}


// Check if a local variable is already in this frame 
static
bool not_local(NODE *name, NODE *sp)
{
    for (; sp != var; sp = cdr(sp))
    {
        if (compare_node(car(sp), name, TRUE) == 0)
        {
            return false;
        }
    }
    return true;
}

static
void create_local_variable(NODE * caseobject, NODE * var_stack_position)
{
    assert(is_caseobject(caseobject));

    if (not_local(caseobject, var_stack_position))
    {
        // A variable by this name didn't already exist in
        // this scope, so we must create a new scope for it.
        push(caseobject, var_stack);
        setobject(var_stack, valnode__caseobj(caseobject));
    }

    if (flag__caseobj(caseobject, VAL_STEPPED))
    {
        // If the variable is stepped, emit a warning that it is being shadowed
        err_logo(SHADOW_WARN, caseobject);
    }
}

// reverse a list destructively
static
NODE *reverse(NODE *list)
{
    NODE *ret = NIL, *temp;

    ref(list);
    while (list != NIL)
    {
        temp = list;
        list = cdr(list);
        temp->nunion.ncons.ncdr = ret;
        ret = temp;
    }
    return unref(ret);
}

// Returns a new list with the members of "a", followed by the members of "b".
// Neither list is modified, but "b" is referenced by the new list.
static
NODE *append(NODE *a, NODE *b)
{
    NODE * completelist     = NIL;
    NODE * completelist_end = NIL;

    // first, build up a copy of "a"
    while (a != NIL)
    {
        NODE * newnode = cons_list(car(a));

        if (completelist == NIL)
        {
            completelist = newnode;
        }
        else
        {
            setcdr(completelist_end, newnode);
        }
        completelist_end = newnode;

        a = cdr(a);
    }

    // now, append "b"
    if (completelist == NIL)
    {
        completelist = b;
    }
    else
    {
        setcdr(completelist_end, b);
    }

    return completelist;
}

// Reset the var stack to the previous place holder.
static
void reset_args(NODE *old_stack)
{
    for (; var_stack != old_stack; pop(var_stack))
    {
        setvalnode__caseobj(car(var_stack), getobject(var_stack));
    }
}


static
void trace_input(NODE * UnquotedArgument)
{
    // trace a NODE* as if it were an input to a function
    NODE * quoted_arg = vref(maybe_quote(UnquotedArgument));
    print_node(g_Writer.GetStream(), quoted_arg);
    deref(quoted_arg);

    print_space(g_Writer.GetStream());
}

// An explicit control evaluator, taken almost directly from SICP, section
// 5.2.  list is a flat list of expressions to evaluate.  where is a label to
// begin at.  Return value depends on where.
static
NODE *evaluator(NODE *list, enum labels where)
{
    // registers
    NODE *exp = NIL;          // the current expression
    NODE *val = NIL;          // the value of the last expression
    NODE *proc = NIL;         // the procedure definition
    NODE *argl = NIL;         // evaluated argument list
    NODE *unev = NIL;         // list of unevaluated expressions
    NODE *stack = NIL;        // register stack
    NODE *parm = NIL;         // the current formal
    NODE *catch_tag = NIL;
    NODE *arg = NIL;          // the current actual

    // registers that don't get reference counted
    NODE * var_stack_position = NIL;  // temp ptr into var_stack
    FIXNUM cont    = 0;               // where to go next (an enum label)
    NODE * formals = NIL;             // list of formal parameters

    int i;
    bool tracing;                 // are we tracing the current procedure?
    FIXNUM oldtailcall;           // in case of reentrant use of evaluator
    FIXNUM repcount;              // count for repeat
    FIXNUM old_ift_iff;

    oldtailcall = tailcall;
    old_ift_iff = ift_iff_flag;
    save2(var, this_line);
    assign(var, var_stack);
    save2(fun, ufun);
    cont = (FIXNUM) all_done;
    numsave((FIXNUM) cont);
    ref(list);

    newcont(where);
    goto fetch_cont;

 begin_line:
    assign(this_line, list);
    newcont(end_line);
 begin_seq:
    treeify_line(list);
    if (!is_tree(list))
    {
        assign(val, Unbound);
        goto fetch_cont;
    }
    assign(unev, tree__tree(list));
    assign(val, Unbound);
    goto eval_sequence;

 end_line:
    if (val != Unbound)
    {
        if (NOT_THROWING)
        {
            err_logo(DK_WHAT, val);
        }
        deref(val);
    }
    val = NIL;
    goto fetch_cont;


    /* ----------------- EVAL ---------------------------------- */

 tail_eval_dispatch:
    tailcall = 1;
 eval_dispatch:
    switch (nodetype(exp))
    {
    case QUOTE:
        // quoted literal
        assign(val, node__quote(exp));
        goto fetch_cont;

    case COLON:
        // variable
        assign(val, valnode__colon(exp));
        while (val == Unbound && NOT_THROWING)
        {
            assign(val, err_logo(NO_VALUE, node__colon(exp)));
        }
        goto fetch_cont;

    case CONS:
        // procedure application
        if (tailcall == 1 && 
            is_macro(car(exp)) &&
            is_list(procnode__caseobj(car(exp))))
        {
            // tail call to user-defined macro must be treated as non-tail
            // because the expression returned by the macro
            // remains to be evaluated in the caller's context
            assign(unev, NIL);
            goto non_tail_eval;
        }

        // the first element in the list is the function
        assign(fun, car(exp));

        // the rest of the elements are the function's inputs
        if (cdr(exp) != NIL)
        {
            goto ev_application;
        }
        else
        {
            goto ev_no_args;
        }

    case ARRAY:
        // array must be copied
        {
            assign(val, make_array(getarrdim(exp)));
            setarrorg(val, getarrorg(exp));

            NODE ** p = getarrptr(exp);
            NODE ** q = getarrptr(val);
            for (int i = 0; i < getarrdim(exp); i++)
            {
                *q++ = vref(*p);
                p++;
            }
        }
        goto fetch_cont;

    default: 
        // self-evaluating
        assign(val, exp);
        goto fetch_cont;
    }

    assert(0 && !"can't fall through");

 ev_no_args:
    // Evaluate an application of a procedure with no arguments.
    assign(argl, NIL);
    goto apply_dispatch;   // apply the procedure

 ev_application:
    // Evaluate an application of a procedure with arguments.
    assign(unev, cdr(exp));
    assign(argl, NIL);
    mixsave(tailcall, var);
    num2save(g_ValueStatus, ift_iff_flag);
    save2(didnt_get_output, didnt_output_name);
 eval_arg_loop:
    if (unev == NIL) 
    {
        goto eval_args_done;
    }
    assign(exp, car(unev));
    if (exp == Not_Enough_Node)
    {
        if (NOT_THROWING)
        {
            err_logo(NOT_ENOUGH, NIL);
        }
        goto eval_args_done;
    }
    save2(argl, qm_list);
    save2(unev, fun);
    save2(ufun, last_ufun);
    save2(this_line, last_line);
    assign(var, var_stack);
    tailcall = -1;
    g_ValueStatus = VALUE_STATUS_Required;
    assign(didnt_get_output, cons_list(fun, ufun, this_line));
    assign(didnt_output_name, NIL);
    newcont(accumulate_arg);
    goto eval_dispatch;                 // evaluate the current argument

 accumulate_arg:
    /* Put the evaluated argument into the argl list. */
    reset_args(var);
    restore2(this_line, last_line);
    restore2(ufun, last_ufun);
    assign(last_call, fun);
    restore2(unev, fun);
    restore2(argl, qm_list);
    while (NOT_THROWING && val == Unbound)
    {
        assign(val, err_logo(DIDNT_OUTPUT, NIL));
    }
    push(val, argl);
    pop(unev);
    goto eval_arg_loop;

 eval_args_done:
    restore2(didnt_get_output, didnt_output_name);
    num2restore(g_ValueStatus, ift_iff_flag);
    mixrestore(tailcall, var);
    if (stopping_flag == THROWING)
    {
        assign(val, Unbound);
        goto fetch_cont;
    }
    assign(argl, reverse(argl));
    /* --------------------- APPLY ---------------------------- */
 apply_dispatch:
    eval_count++;
    update_status_evals();

    /* Load in the procedure's definition and decide whether it's a compound
     * procedure or a primitive procedure.
     */
    if (fun == NULL)
    { 
        // fun is NULL, so assume proc is undefined (output with no arg)
        assign(proc, UNDEFINED);
    }
    else
    {
        assign(proc, procnode__caseobj(fun));
        if (is_macro(fun))
        {
            num2save(g_ValueStatus, tailcall);
            // BUG: save didnt_get_output, current_unode like UCBLogo?
            g_ValueStatus = VALUE_STATUS_Required;
            newcont(macro_return);
        }
    }

    if (proc == UNDEFINED)
    {
        // proc is still undefined, so we can't apply it.
        // Throw a "don't know how to" error.
        if (NOT_THROWING)
        {
            assign(val, err_logo(DK_HOW, fun));
        }
        else
        {
            assign(val, Unbound);
        }
        goto fetch_cont;
    }

    if (is_list(proc))
    {
        // user-defined procedure (non-primitive)
        goto compound_apply;
    }

    /* primitive_apply */
    if (NOT_THROWING)
    {
        // REVISIT: Trace primitives like UCBLogo does?
        if (!IsTimeToExit)
        {
            assign(val, ((logofunc) * getprimfun(proc)) (argl));
        }
    }
    else
    {
        assign(val, Unbound);
    }

#define do_case(x) case x: goto x;
 fetch_cont:
    {
        enum labels x = (enum labels) cont;
        cont = (FIXNUM) car(stack);
        numpop(&stack);
        switch (x)
        {
            do_list(do_case)
                default : abort();
        }
    }

 compound_apply:
    // call (that is, APPLY) a non-primitive procedure/macro
    check_stop(true);

    if (tracing = flag__caseobj(fun, PROC_TRACED) || traceflag)
    {
        for (i = 0; i < trace_level; i++) 
        {
            print_space(g_Writer.GetStream());
        }
        trace_level++;
        ndprintf(g_Writer.GetStream(), "( %s ", fun);
    }

 lambda_apply:

    // Bind the actual inputs to the formal inputs
    var_stack_position = var_stack; // remember where we came in
    for (formals = formals__procnode(proc);
         formals != NIL;
         formals = cdr(formals))
    {

        parm = car(formals);
        if (nodetype(parm) == INTEGER) 
        {
            // default # args

            // set formals to NIL so that it doesn't get deref'ed in restore
            formals = NIL;
            break;
        }
        if (argl != NIL)
        {
            arg = car(argl);
            if (tracing || traceflag)
            {
                // trace the input
                trace_input(arg);
            }
        }
        else
        {
            arg = Unbound;
        }

        if (nodetype(parm) == CASEOBJ)
        {
            // A named input (the common case) -- treat this a local variable
            create_local_variable(parm, var_stack_position);

            // bind the argument to the formal parameter object
            setvalnode__caseobj(parm, arg);
            if (arg == Unbound)
            {
                // we have more formal inputs than actual inputs
                err_logo(NOT_ENOUGH, fun);
            }
        }
        else if (nodetype(parm) == CONS)
        {
            // parm is optional or rest 
            assert(is_caseobject(car(parm)));

            create_local_variable(car(parm), var_stack_position);

            if (cdr(parm) == NIL)
            {
                // parm is a "rest" input.
                // Bind the rest of the argument list to the formal parameter object
                setvalnode__caseobj(car(parm), argl);

                // trace the "rest" inputs, if necessary
                if (argl != NIL)
                {
                    if (tracing || traceflag)
                    {
                        for (NODE * nextinput = cdr(argl);
                             nextinput != NIL;
                             nextinput = cdr(nextinput))
                        {
                            trace_input(car(nextinput));
                        }
                    }
                } 

                assign(argl, NIL);

                // Set formals to NIL so that it doesn't get deref'ed in restore2()
                // Otherwise this could crash. 
                // See bug #1563318.
                formals = NIL;
                break;
            }
            if (arg == Unbound)
            {
                /* use default */
                save2(fun, var);
                save2(ufun, last_ufun);
                save2(this_line, last_line);
                save2(didnt_output_name, didnt_get_output);
                num2save(ift_iff_flag, g_ValueStatus);
                assign(var, var_stack);
                tailcall = -1;
                g_ValueStatus = VALUE_STATUS_Required;
                save2(formals, argl);
                save(var_stack_position);

                assign(list, cdr(parm));
                if (NOT_THROWING)
                {
                    treeify_line(list);
                }
                else
                {
                    assign(list, NIL);
                }

                assign(val, Unbound);
                if (is_tree(list))
                {
                    // the default value is an expression, which must be run
                    assign(unev, tree__tree(list));
                    newcont(set_args_continue);
                    goto eval_sequence;
                }

            set_args_continue:
                restore(var_stack_position);
                restore2(formals, argl);
                parm = car(formals);
                reset_args(var);
                num2restore(ift_iff_flag, g_ValueStatus);
                restore2(didnt_output_name, didnt_get_output);
                restore2(this_line, last_line);
                restore2(ufun, last_ufun);
                restore2(fun, var);  
                arg = val;
            }

            // bind the given argument to the formal argument
            setvalnode__caseobj(car(parm), arg);
        }

        // advance to the next argument in the list
        if (argl != NIL) 
        {
            pop(argl);
        }
    }

    if (argl != NIL) 
    {
        // APPLY [[A] [IGNORE :A]] [1 2]
        err_logo(TOO_MUCH, fun);
    }
    if (check_throwing)
    {
        assign(val, Unbound);
        goto fetch_cont;
    }

    var_stack_position = NIL;
    if (tracing = (!is_list(fun) && flag__caseobj(fun, PROC_TRACED)) || traceflag)
    {
        if (NOT_THROWING) 
        {
            print_char(g_Writer.GetStream(), ')');
        }
        new_line(g_Writer.GetStream());
        save(fun);
        newcont(compound_apply_continue);
    }
    assign(val, Unbound);
    assign(last_ufun, ufun);
    if (!is_list(fun))
    {
        assign(ufun, fun);
    }
    assign(last_line, this_line);
    assign(this_line, NIL);
    assign(proc, (is_list(fun) ? anonymous_function(fun) : procnode__caseobj(fun)));
    assign(list, bodylist__procnode(proc));// get the body ...
    treeify_body(list);
    if (!is_tree(list))
    {
        // Either there was some error when treeifyng the body
        // or the body consisted of nothing by empty lines.
        // In the first case, we want to jump to the next phase
        // in the evaulator so that we can error-out.
        // In the second case, trying to evaluate this function
        // would crash, but we can instead ignore this function
        // call, since it is a no-op.
        assign(val, Unbound);
        goto fetch_cont;
    }

    assign(unev, tree__tree(list));
    if (NOT_THROWING)
    {
        stopping_flag = RUN;
    }
    assign(output_node, Unbound);

    if (g_ValueStatus == VALUE_STATUS_Required) 
    {
        g_ValueStatus = VALUE_STATUS_OutputOk;
    }
    else if (g_ValueStatus == VALUE_STATUS_ValueMaybeOkInMacro) 
    {
        g_ValueStatus = VALUE_STATUS_MaybeOk;
    }
    else 
    {
        g_ValueStatus = VALUE_STATUS_NotOk;
    }

 eval_sequence:
    // Evaluate each expression in the sequence.  
    // Stop as soon as val != Unbound.
    if (!RUNNING || val != Unbound)
    {
        goto fetch_cont;
    }
    if (nodetype(unev) == LINE)
    {
        // The is_tree() clause prevents a crash when a procedure 
        // is erased while it is being run.
        if (is_tree(unparsed__line(unev)) && 
            the_generation != generation__line(unev))
        {
            // Something got redefined while we're running.
            //
            // We must re-tree-ify the bodylist of the current
            // procedure to ensure that it is tree-ified with the
            // most recent procedure definitions.
            //
            // If we don't do this, the programmer would get the
            // wrong behavior, but we might also AV if the old tree
            // passed the wrong number of inputs to a primitive.

            int linenum = 0;
            assign(this_line, tree__tree(bodylist__procnode(proc)));
            while (this_line != unev) 
            {
                // If redef isn't end of line, don't try to fix,
                // but don't blow up either. (Maybe not called from here.)
                if (this_line == NULL) 
                {
                    goto no_fixup_necessary;
                }
                if (nodetype(this_line) == LINE) 
                {
                    linenum++;
                }
                assign(this_line, cdr(this_line));
	    }

            treeify_body(bodylist__procnode(proc));
            assign(unev, tree__tree(bodylist__procnode(proc)));
            while (--linenum >= 0) 
            {
                do 
                {
                    pop(unev);
                } while (unev != NIL && nodetype(unev) != LINE);
            }
        }

 no_fixup_necessary:
        assign(this_line, unparsed__line(unev));
        if (ufun != NIL && flag__caseobj(ufun, PROC_STEPPED) || stepflag)
        {
            // this is not a lambda function and it is being stepped
            if (tracing || traceflag)
            {
                int i = 1;
                while (i++ < trace_level) 
                {
                    print_space(stdout);
                }
            }
            // print_node(stdout, this_line);
            // ndprintf(stdout, " >>> ");
            input_blocking = true;

            if (!setjmp(iblk_buf))
            {
                single_step_box(this_line);
            }

            input_blocking = false;
            // update_coords('\n');
        }
    }
    assign(exp, car(unev));
    pop(unev);
    if (exp != NIL &&
        is_list(exp) && 
        is_tailform(procnode__caseobj(car(exp))))
    {
        NODE * const caseobj = car(exp);

        // Get the priority of the primitive to get the "true identity".
        // This will compare correctly, even if the procedure is a copydef
        // of another procedure.
        short expression_priority = getprimpri(procnode__caseobj(caseobj));
        if (expression_priority == OUTPUT_PRIORITY)
        {
            // they are calling some form of OUTPUT

            assign(didnt_get_output, cons_list(caseobj, ufun, this_line));
            assign(didnt_output_name, NIL);
            if (g_ValueStatus == VALUE_STATUS_OutputOk || 
                g_ValueStatus == VALUE_STATUS_MaybeOk)
            {
                g_ValueStatus = VALUE_STATUS_Required;
                assign(exp, cadr(exp));
                goto tail_eval_dispatch;
            }
            else if (ufun == NIL)
            {
                // We are not in a user-defined function, so they must 
                // be calling OUTPUT at the top-level, which is an error.
                err_logo(AT_TOPLEVEL, caseobj);
                assign(val, Unbound);
                goto fetch_cont;
            }
            else if (!IsInMacro(g_ValueStatus))
            {
                g_ValueStatus = VALUE_STATUS_Required;
                assign(exp, cadr(exp));
                assign(unev, NIL);

                // compute value then give error
                goto non_tail_eval;
            }
        }
        else if (expression_priority == STOP_PRIORITY)
        {
            // they are calling some form of STOP

            if (ufun == NIL)
            {
                // We are not in a user-defined function, so they must 
                // be calling STOP at the top-level, which is an error.
                err_logo(AT_TOPLEVEL, caseobj);
                assign(val, Unbound);
                goto fetch_cont;
            }
            else if (g_ValueStatus == VALUE_STATUS_NotOk || 
                     g_ValueStatus == VALUE_STATUS_MaybeOk)
            {
                assign(val, Unbound);
                goto fetch_cont;
            }
            else if (!IsInMacro(g_ValueStatus))
            {
                assign(didnt_output_name, fun);
                assign(val, Unbound);
                goto fetch_cont;
            }
            else if (g_ValueStatus == VALUE_STATUS_ValueMaybeOkInMacro)
            {
                // pr apply [output ?] [3]
                assign(didnt_output_name, fun);
                goto tail_eval_dispatch;
            }
        }
        else
        {
            // maybeoutput
            assign(exp, cadr(exp));
            g_ValueStatus = VALUE_STATUS_ValueMaybeOkInMacro;
            goto tail_eval_dispatch;
        }
    }


    if (unev == NIL)
    {
        // falling off tail of sequence
        if (g_ValueStatus == VALUE_STATUS_OutputOk || 
            g_ValueStatus == VALUE_STATUS_NoValueInMacro)
        {
            assign(didnt_output_name, fun);
            assign(unev, Unbound);
            goto non_tail_eval;
        }
        else
        {
            goto tail_eval_dispatch;
        }
    }



    if (car(unev) != NIL &&
        is_list(car(unev)) && 
        is_tailform(procnode__caseobj(car(car(unev)))) &&
        getprimpri(procnode__caseobj(car(car(unev)))) == STOP_PRIORITY)
    {
        // next is STOP
        if ((g_ValueStatus == VALUE_STATUS_NotOk || g_ValueStatus == VALUE_STATUS_MaybeOk) && 
            ufun != NIL)
        {
            goto tail_eval_dispatch;
        }
        else if (!IsInMacro(g_ValueStatus))
        {
            assign(didnt_output_name, fun);
            goto tail_eval_dispatch;
        }
    }
 non_tail_eval:
    // REVISIT: copy after_constant optimization from UCBLogo?
    save2(unev, fun);
    num2save(ift_iff_flag, g_ValueStatus);
    save2(ufun, last_ufun);
    save2(this_line, last_line);
    save2(var, proc);
    save2(qm_list, argl);
    assign(var, var_stack);
    tailcall = 0;
    newcont(eval_sequence_continue);
    goto eval_dispatch;

 eval_sequence_continue:
    reset_args(var);
    restore2(qm_list, argl);
    restore2(var, proc);
    restore2(this_line, last_line);
    restore2(ufun, last_ufun);
    if (dont_fix_ift)
    {
        num2restore(dont_fix_ift, g_ValueStatus);
        dont_fix_ift = 0;
    }
    else
    {
        num2restore(ift_iff_flag, g_ValueStatus);
    }
    restore2(unev, fun);
    if (stopping_flag == MACRO_RETURN)
    {
        if (unev == Unbound) 
        {
            assign(unev, NIL);
        }
        if (val != NIL && is_list(val) && (car(val) == Tag))
        {
            assign(unev, cdr(val)); /* from goto */
        }
        else
        {
            assign(unev, append(val, unev));
        }
        assign(val, Unbound);
        stopping_flag = RUN;
        if (unev == NIL)
        {         
            goto fetch_cont;
        }
    }
    else if (!IsInMacro(g_ValueStatus))
    {
        if (STOPPING || RUNNING)
        {
            assign(output_node, Unbound);
        }

        if (stopping_flag == OUTPUT || STOPPING)
        {
            stopping_flag = RUN;
            assign(val, output_node);

            // set errors, if appropriate
            if (NOT_THROWING)
            {
                if (val != Unbound)
                {
                    // value is bound
                    if (g_ValueStatus == VALUE_STATUS_NotOk || 
                        g_ValueStatus == VALUE_STATUS_Required) // BUG???
                    {
                        // value is bound, but no value was expected
                        assign(didnt_output_name, Output);
                        err_logo(DIDNT_OUTPUT, Output);
                    }
                }
                else 
                {
                    // value is not bound
                    if (g_ValueStatus == VALUE_STATUS_Required)
                    {
                        // a value is required, but was not given
                        assign(didnt_output_name, Stop);
                        err_logo(DIDNT_OUTPUT, Output);
                    }
                }
            }
            goto fetch_cont;
        }
    }

    if (NOT_THROWING && val != Unbound)
    {
        // we have a return value with no function to consume it
        err_logo((unev == NIL ? DK_WHAT_UP : DK_WHAT), val);
        assign(val, Unbound);
    }
    if (NOT_THROWING && (unev == NIL || unev == Unbound))
    {
        if (g_ValueStatus != VALUE_STATUS_NoValueInMacro) 
        {
            err_logo(DIDNT_OUTPUT, NIL);
        }
        goto fetch_cont;
    }
    goto eval_sequence;


 compound_apply_continue:
    /* Only get here if tracing */
    restore(fun);
    --trace_level;
    if (NOT_THROWING)
    {
        for (i = 0; i < trace_level; i++) 
        {
            print_space(g_Writer.GetStream());
        }
        print_node(g_Writer.GetStream(), fun);
        if (val == Unbound)
        {
            // trace that the procedure stopped (without outputting anything)
            ndprintf(g_Writer.GetStream(), LOCALIZED_TRACING_STOPS);
        }
        else
        {
            // trace the output
            NODE * quoted_val = vref(maybe_quote(val));
            ndprintf(g_Writer.GetStream(), LOCALIZED_TRACING_OUTPUTS, quoted_val);
            deref(quoted_val);
        }
    }
    goto fetch_cont;

    assert(0 && !"doesn't fall through");

    /* --------------------- MACROS ---------------------------- */

 macro_return:
    num2restore(g_ValueStatus, tailcall);
    while (!is_list(val) && NOT_THROWING)
    {
        assign(val, err_logo(ERR_MACRO, val));
    }
    if (NOT_THROWING)
    {
        if (is_cont(val))
        {
            // continue to the continuation within val
            newcont(cont__cont(val));
            assign(val, val__cont(val));
            goto fetch_cont;
        }
        else if (tailcall == 0)
        {
            treeify_line(val);
            stopping_flag = MACRO_RETURN;
            if (!is_tree(val)) 
            {
                assign(val, NIL);
            }
            else 
            {
                assign(val, tree__tree(val));
            }
            goto fetch_cont;
        }
        else
        {
            assign(list, val);
            goto begin_seq;
        }
    }
    else
    {
        assign(val, Unbound);
        goto fetch_cont;
    }

    assert(0 && !"doesn't fall through");

    /* --------------------- RUNRESULT ---------------------------- */

 runresult_continuation:
    assign(list, val);
    newcont(runresult_followup);
    g_ValueStatus = VALUE_STATUS_ValueMaybeOkInMacro;
    goto begin_seq;

 runresult_followup:
    if (val == Unbound)
    {
        // If the input to RUNRESULT doesn't output, 
        // then the output is []
        assign(val, NIL);
    }
    else
    {
        // If the input to RUNRESULT outputs something,
        // then the output goes in a list.
        assign(val, cons_list(val));
    }
    goto fetch_cont;


   /* --------------------- REPEAT ---------------------------- */
 repeat_continuation:
    assign(list, cdr(val));
    num2save(repcount,repcountup);
    repcount = getint(car(val));
    repcountup = 0;

 repeat_again:
    assign(val, Unbound);
    if (repcount != 0)
    {
        repcountup++;
        save2(list,var);
        var = reref(var, var_stack);
        num2save(repcount,repcountup);
        num2save(g_ValueStatus,tailcall);
        g_ValueStatus = VALUE_STATUS_NoValueInMacro;
        newcont(repeat_followup);
        goto begin_seq;
    }

 repeat_done:
    num2restore(repcount,repcountup);
    goto fetch_cont;

 repeat_followup:
    if (val != Unbound && NOT_THROWING)
    {
        ref(val);
        err_logo(DK_WHAT, val);
        unref(val);
    }
    num2restore(g_ValueStatus, tailcall);
    num2restore(repcount, repcountup);
    restore2(list,var);
    if (!IsInMacro(g_ValueStatus) && tailcall != 0)
    {
        if (STOPPING || RUNNING) 
        {
            assign(output_node, Unbound);
        }
        if (stopping_flag == OUTPUT || STOPPING)
        {
            stopping_flag = RUN;
            assign(val, output_node);
            goto repeat_done;
        }
    }
    if (repcount > 0) // negative means forever
    {
        --repcount;
    }
    check_stop(true);

    if (RUNNING)
    {
        goto repeat_again;
    }
    else
    {
        assign(val, Unbound);
        goto repeat_done;
    }

    assert(0 && !"can't fall through");


    /* --------------------- CATCH/THROW ---------------------------- */
 catch_continuation:
    assign(list, cdr(val));
    assign(catch_tag, car(val));
    if (Error.Equals(catch_tag))
    {
        // Increment the number of nested CATCH "ERROR blocks.
        // When an error does occur, this value is used to decide
        // between throwing an error or using the value of ERRACT.
        g_CatchErrorCount++;
    }
    save(catch_tag);
    save2(didnt_output_name, didnt_get_output);
    num2save(g_ValueStatus, tailcall);
    newcont(catch_followup);
    g_ValueStatus = VALUE_STATUS_ValueMaybeOkInMacro;
    goto begin_seq;

 catch_followup:
    num2restore(g_ValueStatus, tailcall);
    restore2(didnt_output_name, didnt_get_output);
    restore(catch_tag);
    if (!IsInMacro(g_ValueStatus) && tailcall != 0)
    {
        if (STOPPING || RUNNING) 
        {
            assign(output_node, Unbound);
        }
        if (stopping_flag == OUTPUT || STOPPING)
        {
            stopping_flag = RUN;
            assign(val, output_node);
            if (val != Unbound)
            {
                if (g_ValueStatus == VALUE_STATUS_NotOk ||
                    g_ValueStatus == VALUE_STATUS_Required) // BUG???
                {
                    err_logo(DK_WHAT_UP, val);
                }
            }
        }
    }

    if (Error.Equals(catch_tag))
    {
        // we have reached the end of a CATCH "ERROR [] block
        assert(0 < g_CatchErrorCount);
        g_CatchErrorCount--;
    }

    if (stopping_flag == THROWING)
    {
        // if throw_node=="erreur" and catch_tag=="error", then
        // compare_node() will return false, even in the French 
        // version of FMSLogo.  Therefore, we must treat them as 
        // equal if they both equal Error.
        if (compare_node(throw_node, catch_tag, true) == 0 ||
            Error.Equals(catch_tag) && Error.Equals(throw_node))
            {
                throw_node = reref(throw_node, Unbound);
                stopping_flag = RUN;
                assign(val, output_node);
            }
    }
    goto fetch_cont;

 goto_continuation:
    check_stop(true);

    if (ufun == NIL)
    {
        err_logo(AT_TOPLEVEL, Goto);
        assign(val, Unbound);
        goto fetch_cont;
    }
    assign(proc, procnode__caseobj(ufun));
    assign(list, bodylist__procnode(proc));
    assign(unev, tree__tree(list));
    while (unev != NIL)
    {
        if (nodetype(unev) == LINE)
        {
            assign(this_line, unparsed__line(unev));
        }
        assign(exp, car(unev));
        pop(unev);
        if (is_list(exp) &&
            (object__caseobj(car(exp)) == object__caseobj(Tag)) &&
            (nodetype(cadr(exp)) == QUOTE) &&
            compare_node(val, node__quote(cadr(exp)), TRUE) == 0)
        {
            assign(val, cons(Tag, unev));
            stopping_flag = MACRO_RETURN;
            goto fetch_cont;
        }
    }
    err_logo(BAD_DATA_UNREC, val);
    assign(val, Unbound);
    goto fetch_cont;

    /* --------------------- APPLY ---------------------------- */
 begin_apply:
    /* This is for lapply. */
    assign(fun, car(val));
    while (nodetype(fun) == ARRAY && NOT_THROWING)
    {
        assign(fun, err_logo(APPLY_BAD_DATA, fun));
    }
    assign(argl, cadr(val));
    assign(val, Unbound);
    while (!is_list(argl) && NOT_THROWING)
    {
        assign(argl, err_logo(APPLY_BAD_DATA, argl));
    }
    if (NOT_THROWING && fun != NIL)
    {
        if (is_list(fun))
        {
            // template
            if (is_list(car(fun)) && cdr(fun) != NIL)
            {
                if (is_list(cadr(fun)))
                {
                    // procedure text form [[param ...] [instr ...] ... ] 
                    assign(proc, anonymous_function(fun));
               
                    if (stopping_flag == THROWING)
                    {
                        goto fetch_cont;
                    }

                    // disable tracing for lambda functions
                    tracing = false;
                    goto lambda_apply;
                }
                else
                {
                    // lambda form [[param ...] instr ...]
                    NODE * formal_inputs = car(fun);
                    if (tailcall <= 0) 
                    {
                        // Create a new local variable scope for 
                        // the lambda function call before binding
                        // the formal inputs.
                        save(var);
                        assign(var, var_stack);
                        newcont(after_lambda);
                    }

                    //numsave(tailcall);
                    tailcall = 0;
                    llocal(formal_inputs);  // bind the formals locally
                    //numrestore(tailcall);
                    for (;
                         formal_inputs != NIL && argl && NOT_THROWING;
                         formal_inputs = cdr(formal_inputs), assign(argl, cdr(argl)))
                    {
                        setvalnode__caseobj(car(formal_inputs), car(argl));
                    }

                    if (formal_inputs != NIL) 
                    {
                        // too few inputs
                        err_logo(NOT_ENOUGH, fun);
                        goto fetch_cont;
                    } 
                    else if (argl != NIL) 
                    {
                        // too many inputs.
                        err_logo(TOO_MUCH, car(argl));
                        goto fetch_cont;
                    }
                    else
                    {
                        // correct number of inputs
                        assign(list, cdr(fun));
                        goto lambda_qm;
                    }
                }
            }
            else
            {
                // question-mark form [instr ...]

                // qm_list is restored at accumulate_arg
                assign(qm_list, argl);
                assign(list, fun);
            lambda_qm:
                treeify_line(list);
                if (list == NIL || !is_tree(list))
                {
                    goto fetch_cont;
                }
                assign(unev, tree__tree(list));

                if (tailcall <= 0) 
                {
                    g_ValueStatus = VALUE_STATUS_ValueMaybeOkInMacro;

                    // Create a new local variable scope for 
                    // the lambda function call.
                    save(var);
                    assign(var, var_stack);
                    newcont(after_lambda);
                }
                goto eval_sequence;
            }
        }
        else
        {
            // name of procedure to apply
            assign(fun, intern(fun));

            // load the definition of fun, if necessary
            assign(proc, load_procedure_if_necessary(fun));
            while (proc == UNDEFINED && NOT_THROWING)
            {
                assign(val, err_logo(DK_HOW_UNREC, fun));
            }
            if (NOT_THROWING)
            {
                int min;
                int max;

                if (nodetype(proc) == CONS)
                {
                    // proc is a user-defined or library procedure
                    min = getint(minargs__procnode(proc));
                    max = getint(maxargs__procnode(proc));
                }
                else
                {
                    // proc is a primitive
                    if (getprimdflt(proc) < 0)
                    {
                        // special form (TO or .MACRO)
                        err_logo(DK_HOW_UNREC, fun); // can't apply
                        goto fetch_cont;
                    }
                    else
                    {
                        min = getprimmin(proc);
                        max = getprimmax(proc);
                    }
                }

                int n = list_length(argl);

                if (n < min)
                {
                    err_logo(NOT_ENOUGH, NIL);
                }
                else if (n > max && max >= 0)
                {
                    err_logo(TOO_MUCH, NIL);
                }
                else
                {
                    goto apply_dispatch;
                }
            }
        }
    }
    goto fetch_cont;

 after_lambda:
    reset_args(var);
    restore(var);
    goto fetch_cont;

 all_done:
    deref(list);
    tailcall = oldtailcall;
    ift_iff_flag = old_ift_iff;
    restore2(fun, ufun);
    reset_args(var);
    restore2(var, this_line);
    deref(argl);
    deref(unev);
    deref(stack);
    deref(catch_tag);
    deref(exp);
    deref(proc);
    return val;
}

// Evaluate a line of input.
void eval_driver(NODE *line)
{
    if (line != NIL)
    {
        evaluator(line, begin_line);
    }
}

// Evaluate a sequence of expressions until we get a value to return.
// (Called from erract.)
NODE *err_eval_driver(NODE *seq)
{
    g_ValueStatus = VALUE_STATUS_ValueMaybeOkInMacro;
    return evaluator(seq, begin_seq);
}


/* The logo word APPLY. */
NODE *lapply(NODE *args)
{
    return make_cont(begin_apply, args);
}

// The logo word ? <question-mark>.
// This evalutes some element within qm_list.
//
// ?  evaluates to the first element
// ?1 evaluates to the first element
// ?2 evaluates to the second element
// etc.
//
NODE *lqm(NODE *args)
{
    // Assume ?1 by default
    FIXNUM argnum = 1;
    if (args != NIL) 
    {
        // ?# was given
        argnum = getint(positive_int_arg(args));
    }
    if (stopping_flag == THROWING) 
    {
        return Unbound;
    }

    // get the argnum-th item from qm_list
    NODE *np = qm_list;
    FIXNUM i = argnum;
    while (--i > 0 && np != NIL) 
    {
        np = cdr(np);
    }
    if (np == NIL)
    {
        return err_logo(BAD_DATA_UNREC, make_intnode(argnum));
    }
    return car(np);
}


NODE *llocal(NODE *args)
{
    if (tailcall != 0)
    {
        return Unbound;
    }

    if (args == NIL) 
    {
        return Unbound;
    }

    while (is_list(car(args)) && cdr(args) != NIL && NOT_THROWING)
    {
        setcar(args, err_logo(BAD_DATA, car(args)));
    }

    if (is_list(car(args)))
    {
        args = car(args);
    }

    NODE *var_stack_position = var_stack;

    while (args != NIL && NOT_THROWING)
    {
        NODE * arg = car(args);
        while (!is_word(arg) && NOT_THROWING)
        {
            arg = err_logo(BAD_DATA, arg);
            setcar(args, arg);            // prevent crash in lapply
        }
        if (NOT_THROWING)
        {
            arg = intern(arg);
            setcar(args, arg);            // local [a b] faster next time

            create_local_variable(arg, var_stack_position);

            setvalnode__caseobj(arg, Unbound);
            args = cdr(args);
        }
        if (check_throwing) 
        {
            break;
        }
    }
    assign(var, var_stack);  // so eval won't undo our work
    return Unbound;
}

bool process_special_conditions()
{
    bool error_happened = false;

    if (stopping_flag == THROWING)
    {
        if (Error.Equals(throw_node))
        {
            err_print();
            error_happened = true;
        }
        else if (System.Equals(throw_node))
        {
            PostQuitMessage(1); // set the exit code to 1
            prepare_to_exit(true);
        }
        else if (!Toplevel.Equals(throw_node))
        {
            err_logo(NO_CATCH_TAG, throw_node);
            err_print();
            error_happened = true;
        }

        stopping_flag = RUN;
    }

    if (stopping_flag == STOP || stopping_flag == OUTPUT)
    {
        // This is probably a bug, not a user error.
        // We shouldn't be able to get here without throwing
        // an AT_TOPLEVEL error, which would result in a 
        // stopping_flag of THROWING.
        ndprintf(
            stdout, 
            "%t.\n"
            LOCALIZED_ERROR_ATTOPLEVEL2);
        stopping_flag = RUN;
    }

    return error_happened;
}

void start_execution()
{
    // if executing then it's ok to halt
    assert(0 <= halt_flag);

    halt_flag++;
    if (halt_flag < 1)
    {
        halt_flag = 1;
    }
}

void stop_execution()
{
    // not ok to halt now
    assert(1 <= halt_flag);

    halt_flag--;
    if (halt_flag < 0)
    {
        halt_flag = 0;
    }
}

bool is_executing()
{
    assert(0 <= halt_flag);
    return halt_flag != 0;
}

void do_execution(char * logocommand)
{
    // if something there continue
    if (logocommand[0] != '\0')
    {
        start_execution();

        // this code emulates the TTY model used in UCBLOGO main loop
        NODETYPES this_type = STRING;

        // do control character processing
        for (char * c = logocommand; *c != '\0'; c++)
        {
            if (*c == '\\')
            {
                strcpy(c, c + 1);
                if (*c)
                {
                    if (*c == 'n') 
                    {
                        *c = '\n';
                    }
                    *c = ecma_set(*c);
                }
                this_type = BACKSLASH_STRING;
            }
        }

        check_reserve_tank();

        // Set the stopping_flag to RUN so that we don't print any spurious 
        // warnings about using OUTPUT or STOP while not in a procedure.
        // This is important because do_execution() can be called to process
        // event handlers while evaluator() is running.
        // See bug #1479111 for details.
        FIXNUM   saved_value_status  = g_ValueStatus;
        CTRLTYPE saved_stopping_flag = stopping_flag;
        NODE *   saved_output_node   = vref(output_node);
        NODE *   saved_current_line  = current_line;

        stopping_flag = RUN;

        // turn text into a NODE and parse it
        current_line = vref(make_strnode(
            logocommand, 
            (int) strlen(logocommand), 
            this_type, 
            strnzcpy));

        NODE * exec_list = vref(parser(current_line, true));

        // now process it
        g_ValueStatus = VALUE_STATUS_NotOk;
        eval_driver(exec_list);

        process_special_conditions();

        // restore the stopping flag
        stopping_flag = saved_stopping_flag;
        g_ValueStatus = saved_value_status;

        deref(output_node);
        output_node = saved_output_node;

        // deallocate the line
        deref(current_line);
        current_line = saved_current_line;

        // this is a hack to force garbage collector to properly clean up
        if (exec_list != NIL)
        {
            settype(exec_list, CONS);
            deref(exec_list);
        }

        stop_execution();
    }
}

void uninitialize_eval()
{
    // CONSIDER: should any of these be deref'd in evaluator()?
    deref(qm_list);
    qm_list = NIL;

    deref(last_call);
    last_call = NIL;

    deref(last_line);
    last_line = NIL;

    deref(didnt_output_name);
    didnt_output_name = NIL;

    deref(didnt_get_output);
    didnt_get_output = NIL;

    deref(last_ufun);
    last_ufun = NIL;
}
