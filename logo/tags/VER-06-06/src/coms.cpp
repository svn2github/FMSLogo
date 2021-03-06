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
   return (UNBOUND);
   }

NODE *lstop()
   {
   if (NOT_THROWING)
      stopping_flag = STOP;
   return (UNBOUND);
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
            err_logo(USER_ERR, UNBOUND);
         }
      else
         {
         stopping_flag = THROWING;
         throw_node = reref(throw_node, car(arg));
         if (cdr(arg) != NIL)
            output_node = reref(output_node, cadr(arg));
         else
            output_node = reref(output_node, UNBOUND);
         }
      }
   return (UNBOUND);
   }

NODE *lcatch(NODE *args)
   {
   return make_cont(catch_continuation, cons(car(args), lrun(cdr(args))));
   }

int torf_arg(NODE *args)
   {
   NODE *arg = car(args);

   while (NOT_THROWING)
      {
      if (compare_node(arg, Truex, TRUE) == 0) return TRUE;
      if (compare_node(arg, Falsex, TRUE) == 0) return FALSE;
      setcar(args, err_logo(BAD_DATA, arg));
      arg = car(args);
      }
   return -1;
   }

NODE *lgoto(NODE *args)
   {
   return make_cont(goto_continuation, car(args));
   }

NODE *ltag(NODE */* args */)
   {
   return UNBOUND;
   }

NODE *lnot(NODE *args)
   {
   int arg = torf_arg(args);

   if (NOT_THROWING)
      {
      if (arg) return (Falsex);
      else return (Truex);
      }
   return (UNBOUND);
   }

NODE *land(NODE *args)
   {
   int arg;

   if (args == NIL) return (Truex);
   while (NOT_THROWING)
      {
      arg = torf_arg(args);
      if (arg == FALSE)
         return (Falsex);
      args = cdr(args);
      if (args == NIL) break;
      }
   if (NOT_THROWING) return (Truex);
   else return (UNBOUND);
   }

NODE *lor(NODE *args)
   {
   int arg;

   if (args == NIL) return (Falsex);
   while (NOT_THROWING)
      {
      arg = torf_arg(args);
      if (arg == TRUE)
         return (Truex);
      args = cdr(args);
      if (args == NIL) break;
      }
   if (NOT_THROWING) return (Falsex);
   else return (UNBOUND);
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

NODE *lif(NODE *args)                  /* macroized                           */
   {
   NODE *yes;
   int pred;

   if (cddr(args) != NIL) return (lifelse(args));

   pred = torf_arg(args);
   yes = runnable_arg(cdr(args));
   if (NOT_THROWING)
      {
      if (pred) return (yes);
      return (NIL);
      }
   return (UNBOUND);
   }

NODE *lifelse(NODE *args)              /* macroized                           */
   {
   NODE *yes, *no;
   int pred;

   pred = torf_arg(args);
   yes = runnable_arg(cdr(args));
   no = runnable_arg(cddr(args));
   if (NOT_THROWING)
      {
      if (pred) return (yes);
      return (no);
      }
   return (UNBOUND);
   }

NODE *lrun(NODE *args)                 /* macroized                           */
   {
   NODE *arg = runnable_arg(args);

   if (NOT_THROWING) return (arg);
   return (UNBOUND);
   }

NODE *lrunresult(NODE *args)
   {
   return make_cont(runresult_continuation, lrun(args));
   }

NODE *pos_int_arg(NODE *args)
   {
   NODE *arg = car(args), *val;
   FIXNUM i;
   FLONUM f;

   val = cnv_node_to_numnode(arg);
   while ((nodetype(val) != INT || getint(val) < 0) && NOT_THROWING)
      {
      if (nodetype(val) == FLOAT &&
            fmod((f = getfloat(val)), 1.0) == 0.0 &&
            f >= 0.0 && f < (FLONUM) MAXINT)
         {
#ifdef mac
         i = f;
#else
         i = f;
#endif
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
   return UNBOUND;
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

NODE *lrepcount()
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
   int arg = torf_arg(args);

   if (tailcall != 0) return UNBOUND;
   if (NOT_THROWING)
      {
      ift_iff_flag = arg;
      dont_fix_ift = 1;
      }
   return (UNBOUND);
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
void prepare_to_exit(BOOLEANx okay)
#else
void prepare_to_exit(BOOLEANx /* okay */)
#endif
   {
#ifdef mac
   void prepare_to_exit(BOOLEANx okay)
   if (okay)
         {
         console_options.pause_atexit = 0;
         exit(0);
         }
#endif
#ifdef ibm
   exit_program();
   ltextscreen();
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

NODE *lbye()
   {
   prepare_to_exit(TRUE);
   //    if (ufun != NIL || loadstream != stdin) exit(0);
   //    if (isatty(0) && isatty(1)) lcleartext();
   //    printf("Thank you for using Logo.\n");
   //    printf("Have a nice day.\n");
   return (UNBOUND);
   }

NODE *ltime(void)
/* LOGO time */
   {
   NODE *arg, *val = UNBOUND;
   char *Xtim;
   time_t tvec;

   time(&tvec);
   Xtim = ctime(&tvec);

   arg = make_strnode(Xtim, NULL, strlen(Xtim) - 1, STRING, strnzcpy);
   val = parser(arg, FALSE);
   return (val);

   //   return(make_strnode(Xtim, NULL, strlen(Xtim), STRING, strnzcpy));
   //   return(make_static_strnode(Xtim));
   }

NODE *ltimemilli(void)
/* LOGO time */
   {
   return (make_intnode((FIXNUM) GetCurrentTime()));
   }

NODE *lwait(NODE *args)
   {
   NODE *num;
   //    long itim;
   clock_t NumTicksToWait;

   num = pos_int_arg(args);
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
         NumTicksToWait = (((unsigned int) getint(num) * CLK_TCK) / 60) + clock();
         while (NumTicksToWait > clock() && !Time_To_Halt) MyMessageScan();
#endif
         }
      }
   return (UNBOUND);
   }

NODE *lshell(NODE *args)
   {
   char textbuf[MAX_BUFFER_SIZE];

   cnv_strnode_string(textbuf, args);

   if (WinExec(textbuf, SW_SHOW) > 31)
      return (Truex);
   else
      return (Falsex);
   }


