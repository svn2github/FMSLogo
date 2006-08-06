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

#include "allwind.h"

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
char *logolib;
FIXNUM tailcall;    // 0 in sequence, 1 for tail, -1 for arg

FIXNUM val_status;  // 0 means no value allowed (body of cmd),
                    // 1 means value required (arg),
                    // 2 means OUTPUT ok (body of oper),
                    // 3 means val or no val ok (fn inside catch),
                    // 4 means no value in macro (repeat),
                    // 5 means value maybe ok in macro (catch)

FIXNUM dont_fix_ift = 0;

int g_CatchErrorCount = 0;       // the number of nested blocks of CATCH "ERROR
                                 // This is used to disable "ERRACT processing.

static NODE *qm_list = NIL;      // question mark list
static int trace_level = 0;      // indentation level when tracing

static NODE *var       = NIL;    // frame pointer into var_stack
static NODE *var_stack = NIL;    // the stack of variables and their bindings


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
      silent_load(ProcNode, logolib);
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

/* The logo word APPLY. */
NODE *lapply(NODE *args)
   {
   return make_cont(begin_apply, args);
   }

/* The logo word ? <question-mark>. */
NODE *lqm(NODE *args)
   {
   FIXNUM argnum = 1;
   NODE *np = qm_list;

   if (args != NIL) 
      {
      argnum = getint(pos_int_arg(args));
      }
   if (stopping_flag == THROWING) 
      {
      return Unbound;
      }

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
   NODE *var_stack_position = var_stack;

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
         if (not_local(arg, var_stack_position))
            {
            push(arg, var_stack);
            setobject(var_stack, valnode__caseobj(arg));
            }
         setvalnode__caseobj(arg, Unbound);
         tell_shadow(arg);
         args = cdr(args);
         }
      if (check_throwing) 
         {
         break;
         }
      }
   var = reref(var, var_stack);        // so eval won't undo our work
   return Unbound;
   }

// Warn the user if a local variable shadows a global one.
void tell_shadow(NODE *arg)
   {
   if (flag__caseobj(arg, VAL_STEPPED))
      {
      err_logo(SHADOW_WARN, arg);
      }
   }

// Check if a local variable is already in this frame 
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

// nondestructive append
static
NODE *append(NODE *a, NODE *b)
   {
   if (a == NIL) 
      {
      return b;
      }
   return cons(car(a), append(cdr(a), b));
   }

// nondestructive flatten 
static
NODE *flatten(NODE *a)
   {
   if (a == NIL) 
      {
      return NIL;
      }
   return append(car(a), flatten(cdr(a)));
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
   FIXNUM repcountuppoint = 0;   // up count for repeat
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
   make_tree(list);
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
         if (tailcall == 1 && is_macro(car(exp)) &&
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

 ev_no_args:
   // Evaluate an application of a procedure with no arguments.
   assign(argl, NIL);
   goto apply_dispatch;   // apply the procedure

 ev_application:
   // Evaluate an application of a procedure with arguments.
   assign(unev, cdr(exp));
   assign(argl, NIL);
   mixsave(tailcall, var);
   num2save(val_status, ift_iff_flag);
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
   save(argl);
   save2(unev, fun);
   save2(ufun, last_ufun);
   save2(this_line, last_line);
   assign(var, var_stack);
   tailcall = -1;
   val_status = 1;
   assign(didnt_get_output, cons_list(fun, ufun, this_line));
   assign(didnt_output_name, NIL);
   newcont(accumulate_arg);
   goto eval_dispatch;                 /* evaluate the current argument       */

 accumulate_arg:
   /* Put the evaluated argument into the argl list. */
   reset_args(var);
   restore2(this_line, last_line);
   restore2(ufun, last_ufun);
   assign(last_call, fun);
   restore2(unev, fun);
   restore(argl);
   while (NOT_THROWING && val == Unbound)
      {
      assign(val, err_logo(DIDNT_OUTPUT, NIL));
      }
   push(val, argl);
   pop(unev);
   goto eval_arg_loop;

 eval_args_done:
   restore2(didnt_get_output, didnt_output_name);
   num2restore(val_status, ift_iff_flag);
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
   if (fun == NULL) // If fun is NULL then assume proc is undefined (output with no arg)
      {
      assign(proc, UNDEFINED);
      }
   else
      {
      assign(proc, procnode__caseobj(fun));
      if (is_macro(fun))
         {
         num2save(val_status, tailcall);
         val_status = 1;
         newcont(macro_return);
         }
      }

   if (proc == UNDEFINED)
      {
      if (ufun != NIL)
         {
         untreeify_proc(ufun);
         }

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
      goto compound_apply;
      }

   /* primitive_apply */
   if (NOT_THROWING)
      {
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
         print_space(writestream);
         }
      trace_level++;
      ndprintf(writestream, "( %s ", fun);
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
         break; // default # args
         }
      if (argl != NIL)
         {
         arg = car(argl);
         if (tracing || traceflag)
            {
            // trace the input
            NODE * quoted_arg = vref(maybe_quote(arg));
            print_node(writestream, quoted_arg);
            deref(quoted_arg);

            print_space(writestream);
            }
         }
      else
         {
         arg = Unbound;
         }

      if (nodetype(parm) == CASEOBJ)
         {
         // A named input (the common case) -- treat this a local variable
         if (not_local(parm, var_stack_position))
            {
            // A variable by this name didn't already exist in
            // this scope, so we must create a new scope for it.
            push(parm, var_stack);
            setobject(var_stack, valnode__caseobj(parm));
            }
         tell_shadow(parm);
         setvalnode__caseobj(parm, arg);
         if (arg == Unbound)
            {
            // we have more formal inputs than actual inputs
            err_logo(NOT_ENOUGH, fun);
            }
         }
      else if (nodetype(parm) == CONS)
         {
         /* parm is optional or rest */
         if (not_local(car(parm), var_stack_position))
            {
            push(car(parm), var_stack);
            setobject(var_stack, valnode__caseobj(car(parm)));
            }
         tell_shadow(car(parm));
         if (cdr(parm) == NIL)
            {
            /* parm is rest */
            setvalnode__caseobj(car(parm), argl);
            // BUG: should this be traced?
            break;
            }
         if (arg == Unbound)
            {
            /* use default */
            save2(fun, var);
            save2(ufun, last_ufun);
            save2(this_line, last_line);
            save2(didnt_output_name, didnt_get_output);
            num2save(ift_iff_flag, val_status);
            assign(var, var_stack);
            tailcall = -1;
            val_status = 1;
            save2(formals, argl);
            save(var_stack_position);
            assign(list, cdr(parm));
            if (NOT_THROWING)
               {
               make_tree(list);
               }
            else
               {
               assign(list, NIL);
               }
            if (!is_tree(list))
               {
               assign(val, Unbound);
               goto set_args_continue;
               }
            assign(unev, tree__tree(list));
            assign(val, Unbound);
            newcont(set_args_continue);
            goto eval_sequence;


 set_args_continue:
            restore(var_stack_position);
            restore2(formals, argl);
            parm = car(formals);
            reset_args(var);
            num2restore(ift_iff_flag, val_status);
            restore2(didnt_output_name, didnt_get_output);
            restore2(this_line, last_line);
            restore2(ufun, last_ufun);
            restore2(fun, var);
            arg = val;
            }
         setvalnode__caseobj(car(parm), arg);
         }
      if (argl != NIL) 
         {
         pop(argl);
         }
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
         print_char(writestream, ')');
         }
      new_line(writestream);
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
   make_tree_from_body(list);
   if (!is_tree(list))
      {
      assign(val, Unbound);
      goto fetch_cont;
      }

   if (treepair__tree(list) == NIL)
      {
      // The function body consisted of nothing by empty lines.
      // Trying to evaluate this found would crash, but we can
      // safely ignore this function call, since it is a no-op.
      assign(val, Unbound);
      goto fetch_cont;
      }

   assign(unev, tree__tree(list));
   if (NOT_THROWING)
      {
      stopping_flag = RUN;
      }
   assign(output_node, Unbound);

   if (val_status == 1) 
      {
      val_status = 2;
      }
   else if (val_status == 5) 
      {
      val_status = 3;
      }
   else 
      {
      val_status = 0;
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
      // Get the priority of the primitive to get the "true identity".
      // This will compare correctly, even if the procedure is a copydef
      // of another procedure.
      short expression_priority = getprimpri(procnode__caseobj(car(exp)));
      if (expression_priority == OUTPUT_PRIORITY)
         {
         assign(didnt_get_output, cons_list(car(exp), ufun, this_line));
         assign(didnt_output_name, NIL);
         if (val_status == 2 || val_status == 3)
            {
            val_status = 1;
            assign(exp, cadr(exp));
            goto tail_eval_dispatch;
            }
         else if (ufun == NIL)
            {
            err_logo(AT_TOPLEVEL, car(exp));
            assign(val, Unbound);
            goto fetch_cont;
            }
         else if (val_status < 4)
            {
            val_status = 1;
            assign(exp, cadr(exp));
            assign(unev, NIL);
            goto non_tail_eval;        /* compute value then give error       */
            }
         }
      else if (expression_priority == STOP_PRIORITY)
         {
         if (ufun == NIL)
            {
            err_logo(AT_TOPLEVEL, car(exp));
            assign(val, Unbound);
            goto fetch_cont;
            }
         else if (val_status == 0 || val_status == 3)
            {
            assign(val, Unbound);
            goto fetch_cont;
            }
         else if (val_status < 4)
            {
            assign(didnt_output_name, fun);
            assign(val, Unbound);
            goto fetch_cont;
            }
         else if (val_status == 5)
            {
            // pr apply [output ?] [3]
            assign(didnt_output_name, fun);
            goto tail_eval_dispatch;
            }
         }
      else
         {
         /* maybeoutput */
         assign(exp, cadr(exp));
         val_status = 5;
         goto tail_eval_dispatch;
         }
      }
   if (unev == NIL)
      {
      // falling off tail of sequence
      if (val_status == 2 || val_status == 4)
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
      if ((val_status == 0 || val_status == 3) && ufun != NIL)
         {
         goto tail_eval_dispatch;
         }
      else if (val_status < 4)
         {
         assign(didnt_output_name, fun);
         goto tail_eval_dispatch;
         }
      }
 non_tail_eval:
   save2(unev, fun);
   num2save(ift_iff_flag, val_status);
   save2(ufun, last_ufun);
   save2(this_line, last_line);
   save(var);
   assign(var, var_stack);
   tailcall = 0;
   newcont(eval_sequence_continue);
   goto eval_dispatch;

 eval_sequence_continue:
   reset_args(var);
   restore(var);
   restore2(this_line, last_line);
   restore2(ufun, last_ufun);
   if (dont_fix_ift)
      {
      num2restore(dont_fix_ift, val_status);
      dont_fix_ift = 0;
      }
   else
      {
      num2restore(ift_iff_flag, val_status);
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
   else if (val_status < 4)
      {
      if (STOPPING || RUNNING)
         {
         assign(output_node, Unbound);
         }
      if (stopping_flag == OUTPUT || STOPPING)
         {
         stopping_flag = RUN;
         assign(val, output_node);
         if (val != Unbound && val_status < 2 && NOT_THROWING)
            {
            assign(didnt_output_name, Output);
            err_logo(DIDNT_OUTPUT, Output);
            }
         if (val == Unbound && val_status == 1 && NOT_THROWING)
            {
            assign(didnt_output_name, Stop);
            err_logo(DIDNT_OUTPUT, Output);
            }
         goto fetch_cont;
         }
      }
   if (val != Unbound)
      {
      err_logo((unev == NIL ? DK_WHAT_UP : DK_WHAT), val);
      assign(val, Unbound);
      }
   if (NOT_THROWING && (unev == NIL || unev == Unbound))
      {
      if (val_status != 4) 
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
         print_space(writestream);
         }
      print_node(writestream, fun);
      if (val == Unbound)
         {
         // trace that the procedure stopped (without outputting anything)
         ndprintf(writestream, " stops\n");
         }
      else
         {
         // trace the output
         NODE * quoted_val = vref(maybe_quote(val));
         ndprintf(writestream, " outputs %s\n", quoted_val);
         deref(quoted_val);
         }
      }
   goto fetch_cont;

   /* --------------------- MACROS ---------------------------- */

 macro_return:
   num2restore(val_status, tailcall);
   while (!is_list(val) && NOT_THROWING)
      {
      assign(val, err_logo(ERR_MACRO, val));
      }
   if (NOT_THROWING)
      {
      if (is_cont(val))
         {
         newcont(cont__cont(val));
         val->nunion.ncons.ncar = NIL;
         assign(val, val__cont(val));
         goto fetch_cont;
         }
      if (tailcall == 0)
         {
         make_tree(val);
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
      assign(list, val);
      goto begin_seq;
      }
   assign(val, Unbound);
   goto fetch_cont;

   /* --------------------- RUNRESULT ---------------------------- */

 runresult_continuation:
   assign(list, val);
   newcont(runresult_followup);
   val_status = 5;
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
   if (repcount == 0)
      {
 repeat_done:
      num2restore(repcount,repcountup);
      goto fetch_cont;
      }
   repcountup++;
   save2(list,var);
   var = reref(var, var_stack);
   num2save(repcount,repcountup);
   num2save(val_status,tailcall);
   val_status = 4;
   newcont(repeat_followup);
   goto begin_seq;

 repeat_followup:
   if (val != Unbound && NOT_THROWING)
      {
      ref(val);
      err_logo(DK_WHAT, val);
      unref(val);
      }
   num2restore(val_status, tailcall);
   num2restore(repcount, repcountup);
   restore2(list,var);
   if (val_status < 4 && tailcall != 0)
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

   if (RUNNING) goto repeat_again;
   assign(val, Unbound);
   goto repeat_done;

   /* --------------------- CATCH/THROW ---------------------------- */
 catch_continuation:
   assign(list, cdr(val));
   assign(catch_tag, car(val));
   if (compare_node(catch_tag, Error, true) == 0)
      {
      // Increment the number of nested CATCH "ERROR blocks.
      // When an error does occur, this value is used to decide
      // between throwing an error or using the value of ERRACT.
      g_CatchErrorCount++;
      }
   save(catch_tag);
   save2(didnt_output_name, didnt_get_output);
   num2save(val_status, tailcall);
   newcont(catch_followup);
   val_status = 5;
   goto begin_seq;

 catch_followup:
   num2restore(val_status, tailcall);
   restore2(didnt_output_name, didnt_get_output);
   restore(catch_tag);
   if (val_status < 4 && tailcall != 0)
      {
      if (STOPPING || RUNNING) 
         {
         assign(output_node, Unbound);
         }
      if (stopping_flag == OUTPUT || STOPPING)
         {
         stopping_flag = RUN;
         assign(val, output_node);
         if (val != Unbound && val_status < 2)
            {
            err_logo(DK_WHAT_UP, val);
            }
         }
      }

   if (compare_node(catch_tag, Error, true) == 0)
      {
      // we have reached the end of a CATCH "ERROR [] block
      assert(0 < g_CatchErrorCount);
      g_CatchErrorCount--;
      }

   if (stopping_flag == THROWING &&
         compare_node(throw_node, catch_tag, true) == 0)
      {
      throw_node = reref(throw_node, Unbound);
      stopping_flag = RUN;
      assign(val, output_node);
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

               tracing = false;
               goto lambda_apply;
               }
            else
               {
               // lambda form [[param ...] instr ...]
               formals = car(fun);
               if (tailcall <= 0) 
                  {
                  save(var);
                  var = var_stack;
                  newcont(after_lambda);
                  }
               //numsave(tailcall);
               tailcall = 0;
               llocal(formals);  // bind the formals locally
               //numrestore(tailcall);
               for (;
                    formals != NIL && argl && NOT_THROWING;
                    formals = cdr(formals), assign(argl, cdr(argl)))
                  {
                  setvalnode__caseobj(car(formals), car(argl));
                  }

               if (formals != NIL) 
                  {
                  // too few inputs
                  err_logo(NOT_ENOUGH, fun);
                  goto fetch_cont;
                  } 
               else if (argl != NIL) 
                  {
                  // too many inputs
                  err_logo(DK_WHAT, car(argl));
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
            assign(qm_list, argl);
            assign(list, fun);
 lambda_qm:
            make_tree(list);
            if (list == NIL || !is_tree(list))
               {
               goto fetch_cont;
               }
            assign(unev, tree__tree(list));

            if (tailcall <= 0) 
               {
               val_status = 5;
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
   val_status = 5;
   return evaluator(seq, begin_seq);
   }


void uninitialize_eval()
   {
   // CONSIDER: should any of these be deref'd in evaluator()?
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
