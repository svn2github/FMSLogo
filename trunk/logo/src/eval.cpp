/*
*      eval.c          logo eval/apply module                  dko
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

#ifndef TIOCSTI
extern jmp_buf iblk_buf;
#endif

#define assign(to, from)    (to = reref(to, from))
#define init(to, from)      (to = valref(from))

#define save(register)      push(register, stack)
#define restore(register)   (assign(register, car(stack)), pop(stack))

#define save2(reg1,reg2)    (push(reg1,stack),setobject(stack,reg2))
#define restore2(reg1,reg2) (assign(reg2,getobject(stack)), \
           assign(reg1,car(stack)), pop(stack))

/* saving and restoring FIXNUMs rather than NODEs */

#define numsave(register)   numpush(register, &stack)
#define numrestore(register) (register=(FIXNUM)car(stack), numpop(&stack))

#define num2save(reg1,reg2) (numpush(reg1,&stack),stack->n_obj=(NODE *)reg2)
#define num2restore(reg1,reg2) (reg2=(FIXNUM)getobject(stack), \
           reg1=(FIXNUM)car(stack), numpop(&stack))

/* save and restore a FIXNUM (reg1) and a NODE (reg2) */

#define mixsave(reg1,reg2)  (numpush(reg1,&stack),setobject(stack,reg2))
#define mixrestore(reg1,reg2) deref(reg2); reg2=getobject(stack); \
           reg1=(FIXNUM)car(stack); numpop(&stack)

#define newcont(tag)        (numsave(cont), cont = (FIXNUM)tag)

#define nameis(x,y)         ((object__caseobj(x)) == (object__caseobj(y)))

typedef NODE * (*nodeinout) (NODE *arg);

/* These variables are all externed in globals.h */

NODE
*fun = NIL,                            /* current function name               */
*ufun = NIL,                           /* current user-defined function name  */
*last_ufun = NIL,                      /* the function that called this one   */
*this_line = NIL,                      /* the current instruction line        */
*last_line = NIL,                      /* the line that called this one       */
*var_stack = NIL,                 /* the stack of variables and their bindings*/
*var = NIL,                            /* frame pointer into var_stack        */
*last_call = NIL,                      /* the last proc called                */
*didnt_output_name = NIL,              /* the name of the proc that didn't OP */
*didnt_get_output = NIL,            /* the name of the proc that wanted the OP*/
*output_node = NIL;                    /* the output of the current function  */
FIXNUM repcountup;                     /* up count for repeat                 */


CTRLTYPE stopping_flag = RUN;
char *logolib;
FIXNUM tailcall;                      /* 0 in sequence, 1 for tail, -1 for arg*/
FIXNUM val_status;                    /* 0 means no value allowed (body of cmd),
1 means value required (arg),
2 means OUTPUT ok (body of oper),
3 means val or no val ok (fn inside catch),
4 means no value in macro (repeat),
5 means value maybe ok in macro (catch)
*/
FIXNUM dont_fix_ift = 0;

/* These variables are local to this file. */
static NODE *qm_list = NIL;            /* question mark list                  */
static int trace_level = 0;            /* indentation level when tracing      */

/* These first few functions are externed in globals.h */

void spop(NODE **stack)
   {
   NODE *temp = (*stack)->n_cdr;

   if (decrefcnt(*stack) == 0)
      {
      (*stack)->n_cdr = NIL;
      gc(*stack);
      }
   else
      {
      if (temp != NIL) increfcnt(temp);
      }
   *stack = temp;
   }

void spush(NODE *obj, NODE **stack)
   {
   NODE *temp = newnode(CONS);

   setcar(temp, obj);
   temp->n_cdr = *stack;
   ref(temp);
   *stack = temp;
   }

void numpop(NODE **stack)
   {
   NODE *temp = (*stack)->n_cdr;

   (*stack)->n_car = NIL;
   (*stack)->n_cdr = NIL;
   (*stack)->n_obj = NIL;
   deref(*stack);
   *stack = temp;
   }

void numpush(FIXNUM obj, NODE **stack)
   {
   NODE *temp = newnode(CONS);

   temp->n_car = (NODE *) obj;
   temp->n_cdr = *stack;
   ref(temp);
   *stack = temp;
   }

/* forward declaration */
NODE *evaluator(NODE *list, enum labels where);

/* Evaluate a line of input. */
void eval_driver(NODE *line)
   {
   evaluator(line, begin_line);
   }

/* Evaluate a sequence of expressions until we get a value to return.
* (Called from erract.)
*/
NODE *err_eval_driver(NODE *seq)
   {
   val_status = 5;
   return evaluator(seq, begin_seq);
   }

/* The logo word APPLY. */
NODE *lapply(NODE *args)
   {
   return make_cont(begin_apply, args);
   }

/* The logo word ? <question-mark>. */
NODE *lqm(NODE *args)
   {
   FIXNUM argnum = 1, i;
   NODE *np = qm_list;

   if (args != NIL) argnum = getint(pos_int_arg(args));
   if (stopping_flag == THROWING) return Unbound;
   i = argnum;
   while (--i > 0 && np != NIL) np = cdr(np);
   if (np == NIL)
      return (err_logo(BAD_DATA_UNREC, make_intnode(argnum)));
   return (car(np));
   }

/* The rest of the functions are local to this file. */

/* Warn the user if a local variable shadows a global one. */
void tell_shadow(NODE *arg)
   {
   if (flag__caseobj(arg, VAL_STEPPED))
      err_logo(SHADOW_WARN, arg);
   }

/* Check if a local variable is already in this frame */
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

/* reverse a list destructively */
NODE *reverse(NODE *list)
   {
   NODE *ret = NIL, *temp;

   ref(list);
   while (list != NIL)
      {
      temp = list;
      list = cdr(list);
      temp->n_cdr = ret;
      ret = temp;
      }
   return unref(ret);
   }

/* nondestructive append */
NODE *append(NODE *a, NODE *b)
   {
   //    NODE *result;

   if (a == NIL) return b;
   return cons(car(a), append(cdr(a), b));
   }

/* nondestructive flatten */
NODE *flatten(NODE *a)
   {
   if (a == NIL) return NIL;
   return append(car(a), flatten(cdr(a)));
   }

/* Reset the var stack to the previous place holder.
*/
void reset_args(NODE *old_stack)
   {
   for (; var_stack != old_stack; pop(var_stack))
      setvalnode__caseobj(car(var_stack), getobject(var_stack));
   }

/* An explicit control evaluator, taken almost directly from SICP, section
* 5.2.  list is a flat list of expressions to evaluate.  where is a label to
* begin at.  Return value depends on where.
*/
NODE *evaluator(NODE *list, enum labels where)
   {

   /* registers */
   NODE *exp = NIL,                    /* the current expression              */
   *val = NIL,                         /* the value of the last expression    */
   *proc = NIL,                        /* the procedure definition            */
   *argl = NIL,                        /* evaluated argument list             */
   *unev = NIL,                        /* list of unevaluated expressions     */
   *stack = NIL,                       /* register stack                      */
   *parm = NIL,                        /* the current formal                  */
   *catch_tag = NIL,
   *arg = NIL;                         /* the current actual                  */

   /* registers that don't get reference counted, so we pretend they're ints */
   FIXNUM vsp = 0,                     /* temp ptr into var_stack             */
      cont = 0,                           /* where to go next                    */
      formals = (FIXNUM) NIL;             /* list of formal parameters           */

   int i;
   //    int nargs;
   bool tracing;                  /* are we tracing the current procedure?*/
   FIXNUM oldtailcall;                /* in case of reentrant use of evaluator*/
   FIXNUM repcount;                    /* count for repeat                    */
   FIXNUM repcountuppoint = 0;         /* up count for repeat                 */
   FIXNUM old_ift_iff;

   oldtailcall = tailcall;
   old_ift_iff = ift_iff_flag;
   save2(var, this_line);
   assign(var, var_stack);
   save2(fun, ufun);
   cont = (FIXNUM) all_done;
   numsave((FIXNUM) cont);
   newcont(where);
   goto fetch_cont;

 begin_line:
   ref(list);
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
      if (NOT_THROWING) err_logo(DK_WHAT, val);
      deref(val);
      }
   val = NIL;
   deref(list);
   goto fetch_cont;


   /* ----------------- EVAL ---------------------------------- */

 tail_eval_dispatch:
   tailcall = 1;
 eval_dispatch:
   switch (nodetype(exp))
      {
       case QUOTE:                      /* quoted literal                      */
           assign(val, node__quote(exp));
           goto fetch_cont;
       case COLON:                      /* variable                            */
           assign(val, valnode__colon(exp));
           while (val == Unbound && NOT_THROWING)
              assign(val, err_logo(NO_VALUE, node__colon(exp)));
           goto fetch_cont;
       case CONS:                       /* procedure application               */
           if (tailcall == 1 && is_macro(car(exp)) &&
                 is_list(procnode__caseobj(car(exp))))
              {
              /* tail call to user-defined macro must be treated as non-tail
               * because the expression returned by the macro
               * remains to be evaluated in the caller's context */
              assign(unev, NIL);
              goto non_tail_eval;
              }
           assign(fun, car(exp));
           if (cdr(exp) != NIL)
              goto ev_application;
           else
              goto ev_no_args;
       case ARRAY:                      /* array must be copied                */
           {
              NODE **p, **q;
              assign(val, make_array(getarrdim(exp)));
              setarrorg(val, getarrorg(exp));
              for (p = getarrptr(exp), q = getarrptr(val), i = 0;
                    i < getarrdim(exp); i++, p++)
                 *q++ = vref(*p);
           }
           goto fetch_cont;
       default:
           assign(val, exp);             /* self-evaluating                     */
           goto fetch_cont;
      }

 ev_no_args:
   /* Evaluate an application of a procedure with no arguments. */
   assign(argl, NIL);
   goto apply_dispatch;                /* apply the procedure                 */

 ev_application:
   /* Evaluate an application of a procedure with arguments. */
   assign(unev, cdr(exp));
   assign(argl, NIL);
   mixsave(tailcall, var);
   num2save(val_status, ift_iff_flag);
   save2(didnt_get_output, didnt_output_name);
 eval_arg_loop:
   if (unev == NIL) goto eval_args_done;
   assign(exp, car(unev));
   if (exp == Not_Enough_Node)
      {
      if (NOT_THROWING)
         err_logo(NOT_ENOUGH, NIL);
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
   if (status_flag) update_status_evals();

   /* Load in the procedure's definition and decide whether it's a compound
    * procedure or a primitive procedure.
    */
   if (fun == NULL) // If fun is NULL then assume proc is undefined (output with no arg)
      {
      proc = UNDEFINED;
      }
   else
	   {
   	proc = procnode__caseobj(fun);
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
         assign(val, err_logo(DK_HOW, fun));
      else
         assign(val, Unbound);
      goto fetch_cont;
      }
   if (is_list(proc)) goto compound_apply;
   /* primitive_apply */
   if (NOT_THROWING)
      assign(val, ((nodeinout) * getprimfun(proc)) (argl));
   else
      assign(val, Unbound);
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
#ifdef mac
   check_mac_stop();
#endif
#ifdef ibm
   check_ibm_stop(1);
#endif
   if (tracing = flag__caseobj(fun, PROC_TRACED) || traceflag)
      {
      for (i = 0; i < trace_level; i++) print_space(writestream);
      trace_level++;
      ndprintf(writestream, "( %s ", fun);
      }
   /* Bind the actuals to the formals */
 lambda_apply:
   vsp = (FIXNUM) var_stack;           /* remember where we came in           */
   for (formals = (FIXNUM) formals__procnode(proc);
         formals != (FIXNUM) NIL;
         formals = (FIXNUM) cdr((NODE *) formals))
      {
      parm = car((NODE *) formals);
      if (nodetype(parm) == INT) break;/* default # args                      */
      if (argl != NIL)
         {
         arg = car(argl);
         if (tracing || traceflag)
            {
            print_node(writestream, maybe_quote(arg));
            print_space(writestream);
            }
         }
      else
         arg = Unbound;
      if (nodetype(parm) == CASEOBJ)
         {
         if (not_local(parm, (NODE *) vsp))
            {
            push(parm, var_stack);
            setobject(var_stack, valnode__caseobj(parm));
            }
         tell_shadow(parm);
         setvalnode__caseobj(parm, arg);
         }
      else if (nodetype(parm) == CONS)
         {
         /* parm is optional or rest */
         if (not_local(car(parm), (NODE *) vsp))
            {
            push(car(parm), var_stack);
            setobject(var_stack, valnode__caseobj(car(parm)));
            }
         tell_shadow(car(parm));
         if (cdr(parm) == NIL)
            {
            /* parm is rest */
            setvalnode__caseobj(car(parm), argl);
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
            mixsave(formals, argl);
            numsave(vsp);
            assign(list, cdr(parm));
            if (NOT_THROWING)
               make_tree(list);
            else
               assign(list, NIL);
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
            numrestore(vsp);
            mixrestore(formals, argl);
            parm = car((NODE *) formals);
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
      if (argl != NIL) pop(argl);
      }
   if (check_throwing)
      {
      assign(val, Unbound);
      goto fetch_cont;
      }
   vsp = 0;
   if (tracing = (!is_list(fun) && flag__caseobj(fun, PROC_TRACED)) || traceflag)
      {
      if (NOT_THROWING) print_char(writestream, ')');
      new_line(writestream);
      save(fun);
      newcont(compound_apply_continue);
      }
   assign(val, Unbound);
   assign(last_ufun, ufun);
   if (!is_list(fun)) assign(ufun, fun);
   assign(last_line, this_line);
   assign(this_line, NIL);
   proc = (is_list(fun) ? anonymous_function(fun) : procnode__caseobj(fun));
   assign(list, bodylist__procnode(proc));/* get the body ...                 */
   make_tree_from_body(list);
   if (!is_tree(list))
      {
      goto fetch_cont;
      }
   assign(unev, tree__tree(list));
   if (NOT_THROWING) stopping_flag = RUN;
   assign(output_node, Unbound);
   if (val_status == 1) val_status = 2;
   else if (val_status == 5) val_status = 3;
   else val_status = 0;
 eval_sequence:
   /* Evaluate each expression in the sequence.  Stop as soon as
    * val != Unbound.
    */
   if (!RUNNING || val != Unbound)
      {
      goto fetch_cont;
      }
   if (nodetype(unev) == LINE)
      {
      assign(this_line, unparsed__line(unev));
      if (flag__caseobj(ufun, PROC_STEPPED) || stepflag)
         {
         //         char junk[20];

         if (tracing || traceflag)
            {
            int i = 1;
            while (i++ < trace_level) print_space(stdout);
            }
         //         print_node(stdout, this_line);
         //         ndprintf(stdout, " >>> ");
         input_blocking++;
#ifndef TIOCSTI
         if (!setjmp(iblk_buf))
#endif
#ifdef __ZTC__
            ztc_getcr();
#else
            //             fgets(junk, 19, stdin);
            single_step_box(this_line);
#endif
         input_blocking = 0;
         //         update_coords('\n');
         }
      }
   assign(exp, car(unev));
   pop(unev);
   if (exp != NIL &&
         is_list(exp) && (is_tailform(procnode__caseobj(car(exp)))))
      {
      if (nameis(car(exp), Output) || nameis(car(exp), Op))
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
      else if (nameis(car(exp), Stop))
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
         is_list(car(unev)) && nameis(car(car(unev)), Stop))
      {
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
      num2restore(ift_iff_flag, val_status);
   restore2(unev, fun);
   if (stopping_flag == MACRO_RETURN)
      {
      if (unev == Unbound) assign(unev, NIL);
      if (val != NIL && is_list(val) && (car(val) == Tag))
         assign(unev, cdr(val)); /* from goto */
      else
         assign(unev, append(val, unev));
      assign(val, Unbound);
      stopping_flag = RUN;
      if (unev == NIL) goto fetch_cont;
      }
   else if (val_status < 4)
      {
      if (STOPPING || RUNNING) assign(output_node, Unbound);
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
      if (val_status != 4) err_logo(DIDNT_OUTPUT, NIL);
      goto fetch_cont;
      }
   goto eval_sequence;

 compound_apply_continue:
   /* Only get here if tracing */
   restore(fun);
   --trace_level;
   if (NOT_THROWING)
      {
      for (i = 0; i < trace_level; i++) print_space(writestream);
      print_node(writestream, fun);
      if (val == Unbound)
         ndprintf(writestream, " stops\n");
      else
         {
         ref(val);
         ndprintf(writestream, " outputs %s\n", maybe_quote(val));
         deref(val);
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
         val->n_car = NIL;
         assign(val, val__cont(val));
         goto fetch_cont;
         }
 macro_reval:
      if (tailcall == 0)
         {
         make_tree(val);
         stopping_flag = MACRO_RETURN;
         if (!is_tree(val)) assign(val, NIL);
         else assign(val, tree__tree(val));
         goto fetch_cont;
         }
      assign(list, val);
      goto begin_seq;
      }
   assign(val, Unbound);
   goto fetch_cont;

 runresult_continuation:
   assign(list, val);
   newcont(runresult_followup);
   val_status = 5;
   goto begin_seq;

 runresult_followup:
   if (val == Unbound)
      {
      assign(val, NIL);
      }
   else
      {
      assign(val, cons(val, NIL));
      }
   goto fetch_cont;

 repeat_continuation:
   assign(list, cdr(val));
   repcount = getint(car(val));
   repcountup = 1;
 repeat_again:
   assign(val, Unbound);
   if (repcount == 0)
      {
      if (repcountuppoint) repcountup = (FIXNUM) car((NODE *) repcountuppoint);
      goto fetch_cont;
      }
   mixsave(repcount, list);
   numsave(repcountuppoint);
   numsave(repcountup);
   repcountuppoint = (FIXNUM) stack;
   num2save(val_status, tailcall);
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
   numrestore(repcountup);
   numrestore(repcountuppoint);
   mixrestore(repcount, list);
   if (val_status < 4 && tailcall != 0)
      {
      if (STOPPING || RUNNING) assign(output_node, Unbound);
      if (stopping_flag == OUTPUT || STOPPING)
         {
         stopping_flag = RUN;
         assign(val, output_node);
         if (val != Unbound && val_status < 2)
            {
            err_logo(DK_WHAT_UP, val);
            }
         goto fetch_cont;
         }
      }
   if (repcount > 0)                   /* negative means forever              */
      {
      --repcount;
      ++repcountup;
      }
#ifdef mac
   check_mac_stop();
#endif
#ifdef ibm
   check_ibm_stop(1);
#endif
   if (RUNNING) goto repeat_again;
   assign(val, Unbound);
   goto fetch_cont;

 catch_continuation:
   assign(list, cdr(val));
   assign(catch_tag, car(val));
   if (compare_node(catch_tag, Error, TRUE) == 0)
      {
      push(Erract, var_stack);
      setobject(var_stack, valnode__caseobj(Erract));
      setvalnode__caseobj(Erract, Unbound);
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
      if (STOPPING || RUNNING) assign(output_node, Unbound);
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
   if (stopping_flag == THROWING &&
         compare_node(throw_node, catch_tag, TRUE) == 0)
      {
      throw_node = reref(throw_node, Unbound);
      stopping_flag = RUN;
      assign(val, output_node);
      }
   goto fetch_cont;

 goto_continuation:
#ifdef mac
   check_mac_stop();
#endif
#ifdef ibm
   check_ibm_stop(1);
#endif
   if (ufun == NIL)
      {
      err_logo(AT_TOPLEVEL, Goto);
      assign(val, Unbound);
      goto fetch_cont;
      }
   proc = procnode__caseobj(ufun);
   assign(list, bodylist__procnode(proc));
   assign(unev, tree__tree(list));
   while (unev != NIL)
      {
      if (nodetype(unev) == LINE)
         assign(this_line, unparsed__line(unev));
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

 begin_apply:
   /* This is for lapply. */
   assign(fun, car(val));
   while (nodetype(fun) == ARRAY && NOT_THROWING)
      assign(fun, err_logo(APPLY_BAD_DATA, fun));
   assign(argl, cadr(val));
   assign(val, Unbound);
   while (!is_list(argl) && NOT_THROWING)
      assign(argl, err_logo(APPLY_BAD_DATA, argl));
   if (NOT_THROWING && fun != NIL)
      {
      if (is_list(fun))
         {
         /* template */
         if (is_list(car(fun)) && cdr(fun) != NIL)
            {
            if (is_list(cadr(fun)))
               {
               /* procedure text form */
               proc = anonymous_function(fun);
               tracing = 0;
               goto lambda_apply;
               }
            /* lambda form */
            formals = (FIXNUM) car(fun);
            numsave(tailcall);
            tailcall = 0;
            llocal((NODE *) formals);  /* bind the formals locally            */
            numrestore(tailcall);
            for (;
                  formals && argl && NOT_THROWING;
                  formals = (FIXNUM) cdr((NODE *) formals),
                  assign(argl, cdr(argl)))
               setvalnode__caseobj(car((NODE *) formals), car(argl));
            assign(val, cdr(fun));
            goto macro_reval;
            }
         else
            {
            /* question-mark form */
            save(qm_list);
            assign(qm_list, argl);
            assign(list, fun);
            make_tree(list);
            if (list == NIL || !is_tree(list))
               {
               goto qm_failed;
               }
            assign(unev, tree__tree(list));
            save2(didnt_output_name, didnt_get_output);
            num2save(val_status, tailcall);
            newcont(qm_continue);
            val_status = 5;
            goto eval_sequence;

 qm_continue:
            num2restore(val_status, tailcall);
            restore2(didnt_output_name, didnt_get_output);
            if (val_status < 4 && tailcall != 0)
               {
               if (STOPPING || RUNNING) assign(output_node, Unbound);
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
 qm_failed:
            restore(qm_list);
            goto fetch_cont;
            }
         }
      else
         {
         /* name of procedure to apply */
         int min, max, n;
         NODE *arg;
         assign(fun, intern(fun));
         if (procnode__caseobj(fun) == UNDEFINED && NOT_THROWING &&
               fun != Null_Word)
            silent_load(fun, NULL);    /* try ./<fun>.lg                      */
         if (procnode__caseobj(fun) == UNDEFINED && NOT_THROWING &&
               fun != Null_Word)
            silent_load(fun, logolib); /* try <logolib>/<fun>                 */
         proc = procnode__caseobj(fun);
         while (proc == UNDEFINED && NOT_THROWING)
            {
            assign(val, err_logo(DK_HOW_UNREC, fun));
            }
         if (NOT_THROWING)
            {
            if (nodetype(proc) == CONS)
               {
               min = getint(minargs__procnode(proc));
               max = getint(maxargs__procnode(proc));
               }
            else
               {
               if (getprimdflt(proc) < 0)
                  {
                  /* special form */
                  err_logo(DK_HOW_UNREC, fun);/* can't apply                  */
                  goto fetch_cont;
                  }
               else
                  {
                  min = getprimmin(proc);
                  max = getprimmax(proc);
                  }
               }
            for (n = 0, arg = argl; arg != NIL; n++, arg = cdr(arg));
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

 all_done:
   tailcall = oldtailcall;
   ift_iff_flag = old_ift_iff;
   restore2(fun, ufun);
   reset_args(var);
   restore2(var, this_line);
   deref(argl); deref(unev); deref(stack); deref(catch_tag); deref(exp);
   return (val);
   }
