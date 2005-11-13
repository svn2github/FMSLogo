/*
*      coms.c     program execution control module      dvb
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

FIXNUM ift_iff_flag = -1;

NODE *make_cont(enum labels cont, NODE *val)
   {
#ifdef __ZTC__
   union
      {
      enum labels lll;
      NODE *ppp;
      }
   cast;
#endif
   NODE *retval = cons(NIL, val);
#ifdef __ZTC__
   cast.lll = cont;
   retval->n_car = cast.ppp;
#else
   retval->n_car = (NODE *) cont;
#endif
   settype(retval, CONT);
   return retval;
   }

NODE *loutput(NODE *arg)
   {
   if (NOT_THROWING)
      {
      stopping_flag = OUTPUT;
      output_node = reref(output_node, car(arg));
      }
   return Unbound;
   }

NODE *lstop(NODE *arg)
   {
   if (NOT_THROWING)
      stopping_flag = STOP;
   return Unbound;
   }

NODE *lthrow(NODE *arg)
   {
   if (NOT_THROWING)
      {
      if (compare_node(car(arg), Error, TRUE) == 0)
         {
         if (cdr(arg) != NIL)
            err_logo(USER_ERR, cadr(arg));
         else
            err_logo(USER_ERR, Unbound);
         }
      else
         {
         stopping_flag = THROWING;
         throw_node = reref(throw_node, car(arg));
         if (cdr(arg) != NIL)
            output_node = reref(output_node, cadr(arg));
         else
            output_node = reref(output_node, Unbound);
         }
      }
   return Unbound;
   }

NODE *lcatch(NODE *args)
   {
   return make_cont(catch_continuation, cons(car(args), lrun(cdr(args))));
   }

bool boolean_arg(NODE *args)
   {
   NODE *arg = car(args);

   while (NOT_THROWING)
      {
      if (compare_node(arg, Truex, TRUE) == 0) 
         {
         return true;
         }
      if (compare_node(arg, Falsex, TRUE) == 0) 
         {
         return false;
         }
      setcar(args, err_logo(BAD_DATA, arg));
      arg = car(args);
      }

   // default to "true" for backward compatability.
   // (This used to return to -1, which is more likely to behave like "true" than "false").
   return true;
   }

NODE *lgoto(NODE *args)
   {
   return make_cont(goto_continuation, car(args));
   }

NODE *ltag(NODE */* args */)
   {
   return Unbound;
   }

NODE *lnot(NODE *args)
   {
   bool arg = boolean_arg(args);

   if (NOT_THROWING)
      {
      if (arg) 
         {
         return Falsex;
         }
      else 
         {
         return Truex;
         }
      }

   return Unbound;
   }

NODE *land(NODE *args)
   {
   if (args == NIL) 
      {
      return Truex;
      }

   while (NOT_THROWING)
      {
      bool arg = boolean_arg(args);
      if (!arg)
         {
         // found a false argument, so entire expression is false
         return Falsex;
         }

      args = cdr(args);
      if (args == NIL) 
         {
         break;
         }
      }

   if (NOT_THROWING) 
      {
      // there were no false arguments, so entire expression is true
      return Truex;
      }

   return Unbound;
   }

NODE *lor(NODE *args)
   {
   if (args == NIL)
      {
      return Falsex;
      }

   while (NOT_THROWING)
      {
      bool arg = boolean_arg(args);
      if (arg)
         {
         // found a true argument, so entire expression is true
         return Truex;
         }

      args = cdr(args);
      if (args == NIL) 
         {
         break;
         }
      }

   if (NOT_THROWING) 
      {
      // there were no true arguments, so entire expression is false
      return Falsex;
      }

   return Unbound;
   }

NODE *runnable_arg(NODE *args)
   {
   NODE *arg = car(args);

   if (!aggregate(arg))
      {
      setcar(args, parser(arg, TRUE));
      arg = car(args);
      }
   while (!is_list(arg) && NOT_THROWING)
      {
      setcar(args, err_logo(BAD_DATA, arg));
      arg = car(args);
      }
   return (arg);
   }

NODE *lif(NODE *args)  // macroized
   {
   if (cddr(args) != NIL)
      {
      return lifelse(args);
      }

   bool pred = boolean_arg(args);
   NODE * yes = runnable_arg(cdr(args));
   if (NOT_THROWING)
      {
      if (pred) 
         {
         return yes;
         }
      return NIL;
      }

   return Unbound;
   }

NODE *lifelse(NODE *args)              /* macroized                           */
   {
   bool pred = boolean_arg(args);
   NODE* yes = runnable_arg(cdr(args));
   NODE* no = runnable_arg(cddr(args));
   if (NOT_THROWING)
      {
      if (pred) 
         {
         return yes;
         }
      return no;
      }
   return Unbound;
   }

NODE *lrun(NODE *args)                 /* macroized                           */
   {
   NODE *arg = runnable_arg(args);

   if (NOT_THROWING)
      {
      return arg;
      }
   return Unbound;
   }

NODE *lrunresult(NODE *args)
   {
   return make_cont(runresult_continuation, lrun(args));
   }

NODE *pos_int_arg(NODE *args)
   {
   NODE *arg = car(args);
   FIXNUM i;
   FLONUM f;

   NODE * val = cnv_node_to_numnode(arg);
   while ((nodetype(val) != INT || getint(val) < 0) && NOT_THROWING)
      {
      if (nodetype(val) == FLOAT &&
            fmod((f = getfloat(val)), 1.0) == 0.0 &&
            f >= 0.0 && f < (FLONUM) MAXINT)
         {
         i = f;

         gcref(val);
         val = make_intnode(i);
         break;
         }
      gcref(val);
      setcar(args, err_logo(BAD_DATA, arg));
      arg = car(args);
      val = cnv_node_to_numnode(arg);
      }
   setcar(args, val);
   if (nodetype(val) == INT) return (val);
   return Unbound;
   }

NODE *lrepeat(NODE *args)
   {
   NODE *cnt, *torpt, *retval = NIL;

   cnt = pos_int_arg(args);
   torpt = lrun(cdr(args));
   if (NOT_THROWING)
      {
      retval = make_cont(repeat_continuation, cons(cnt, torpt));
      }
   return (retval);
   }

NODE *lrepcount(NODE *args)
   {
   return (make_intnode((FIXNUM) repcountup));
   }

NODE *lforever(NODE *args)
   {
   NODE *torpt = lrun(args);

   if (NOT_THROWING)
      return make_cont(repeat_continuation, cons(make_intnode(-1), torpt));
   return NIL;
   }

NODE *ltest(NODE *args)
   {
   bool arg = boolean_arg(args);

   if (tailcall != 0) return Unbound;
   if (NOT_THROWING)
      {
      ift_iff_flag = arg ? 1 : 0;
      dont_fix_ift = 1;
      }
   return Unbound;
   }

NODE *liftrue(NODE *args)
   {
   if (ift_iff_flag < 0)
      return (err_logo(NO_TEST, NIL));
   else if (ift_iff_flag > 0)
      return (lrun(args));
   else
      return (NIL);
   }

NODE *liffalse(NODE *args)
   {
   if (ift_iff_flag < 0)
      return (err_logo(NO_TEST, NIL));
   else if (ift_iff_flag == 0)
      return (lrun(args));
   else
      return (NIL);
   }

#ifdef mac
void prepare_to_exit(bool okay)
#else
void prepare_to_exit(bool /* okay */)
#endif
   {
#ifdef mac
   void prepare_to_exit(bool okay)
   if (okay)
         {
         console_options.pause_atexit = 0;
         exit(0);
         }
#endif
#ifdef ibm
   exit_program();
   ltextscreen(NIL);
   ibm_plain_mode();
#endif
#ifdef unix
   extern int getpid();
   char ef[30];

   charmode_off();
   sprintf(ef, "/tmp/logo%d", getpid());
   unlink(ef);
#endif
   }

NODE *lbye(NODE *args)
   {
   prepare_to_exit(TRUE);
   //    if (ufun != NIL || loadstream != stdin) exit(0);
   //    if (isatty(0) && isatty(1)) lcleartext();
   //    printf("Thank you for using Logo.\n");
   //    printf("Have a nice day.\n");
   return Unbound;
   }

/* LOGO time */
NODE *ltime(NODE *)
   {
   time_t tvec;
   time(&tvec);
   const char * Xtim = ctime(&tvec);

   NODE * arg = make_strnode(Xtim, strlen(Xtim) - 1, STRING, strnzcpy);
   NODE * val = parser(arg, FALSE);
   return (val);

   //   return(make_strnode(Xtim, NULL, strlen(Xtim), STRING, strnzcpy));
   //   return(make_static_strnode(Xtim));
   }

NODE *ltimemilli(NODE *)
/* LOGO time */
   {
   return (make_intnode((FIXNUM) GetCurrentTime()));
   }

NODE *lwait(NODE *args)
   {
   NODE * num = pos_int_arg(args);
   if (NOT_THROWING)
      {
      //        fflush(stdout); /* csls v. 1 p. 7 */
#ifdef __ZTC__
      zflush();
#endif
      if (getint(num) > 0)
         {
#ifdef bsd
         unsigned int n;
#ifdef ultrix
         n = (unsigned int) getint(num) / 60;
         sleep(n);
#else
         n = (unsigned int) getint(num) * 16667;
         usleep(n);
#endif
#else
         clock_t NumTicksToWait = (((unsigned int) getint(num) * CLK_TCK) / 60) + clock();
         while (NumTicksToWait > clock() && !IsTimeToHalt) 
           {
           MyMessageScan();
           }
#endif
         }
      }
   return Unbound;
   }

NODE *lshell(NODE *args)
   {
   char textbuf[MAX_BUFFER_SIZE];
   cnv_strnode_string(textbuf, args);

   if (WinExec(textbuf, SW_SHOW) > 31)
      return Truex;
   else
      return Falsex;
   }
