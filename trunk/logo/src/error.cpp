/*
*      error.c         logo error module                       dvb
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

NODE *    throw_node = NIL;
ERR_TYPES erract_errtype;

static NODE * err_mesg = NIL;

void err_print()
   {
   if (err_mesg == NIL) 
      {
      return;
      }

   CTRLTYPE save_flag = stopping_flag;

   stopping_flag = RUN;
   print_backslashes = true;

   print_helper(stdout, cadr(err_mesg));

   if (err_mesg == NIL)
      {
      MainWindowx->CommandWindow->MessageBox(
         "I Lost an Error Message",
         "Double Error");
      return;
      }

   if (car(cddr(err_mesg)) != NIL)
      {
      ndprintf(stdout, "  in %s\n%s", car(cddr(err_mesg)), cadr(cddr(err_mesg)));
      }

   deref(err_mesg);
   err_mesg = NIL;
   new_line(stdout);

   print_backslashes = false;
   stopping_flag = save_flag;
   }

NODE *err_logo(ERR_TYPES error_type, NODE *error_desc)
   {
   bool recoverable = false;
   bool warning = false;
   bool uplevel = false;

   NODE * error_message = NIL;

   ref(error_desc);
   switch (error_type)
      {
      case FATAL:
         prepare_to_exit(FALSE);
         printfx("Logo: Fatal Internal Error.\n");
         exit(1);

      case OUT_OF_MEM_UNREC:
         prepare_to_exit(FALSE);
         printfx("Logo: Out of Memory.\n");
         exit(1);

      case OUT_OF_MEM:
         use_reserve_tank();
         error_message = cons_list(make_static_strnode("out of space"));
         break;

      case STACK_OVERFLOW:
         error_message = cons_list(make_static_strnode("stack overflow"));
         break;

      case TURTLE_OUT_OF_BOUNDS:
         error_message = cons_list(make_static_strnode("turtle out of bounds"));
         break;

      case BAD_GRAPH_INIT:
         error_message = cons_list(make_static_strnode("couldn't initialize graphics"));
         break;

      case BAD_DATA_UNREC:
         error_message = cons_list(
            fun,
            make_static_strnode("doesn\'t like"),
            error_desc, 
            make_static_strnode("as input"));
         break;
         
      case DIDNT_OUTPUT:
          if (didnt_output_name != NIL)
             {
             last_call = reref(last_call, didnt_output_name);
             }
          if (error_desc == NIL)
             {
             error_desc = vref(car(didnt_get_output));
             ufun = reref(ufun, cadr(didnt_get_output));
             this_line = reref(this_line, cadr(cdr(didnt_get_output)));
             }
          error_message = cons_list(
             last_call,
             make_static_strnode("didn\'t output to"),
             error_desc);
          recoverable = true;
          break;

      case NOT_ENOUGH:
         error_message = cons_list(
            make_static_strnode("not enough inputs to"), 
            error_desc == NIL ? fun : error_desc);
           break;

      case BAD_DATA:
         error_message = cons_list(
            fun,
            make_static_strnode("doesn\'t like"), 
            error_desc,
            make_static_strnode("as input"));
         recoverable = true;
         break;

      case APPLY_BAD_DATA:
         error_message = cons_list(
            make_static_strnode("APPLY doesn\'t like"),
            error_desc,
            make_static_strnode("as input"));
         recoverable = true;
         break;

      case TOO_MUCH:
         error_message = cons_list(make_static_strnode("too much inside ()\'s"));
         break;

      case DK_WHAT_UP:
         uplevel = true;
         // FALLTHROUGH
      case DK_WHAT:
         error_message = cons_list(
            make_static_strnode("You don\'t say what to do with"), 
            error_desc);
         break;

      case PAREN_MISMATCH:
         error_message = cons_list(make_static_strnode("too many (\'s"));
         break;

      case NO_VALUE:
         error_message = cons_list(
            error_desc,
            make_static_strnode("has no value"));
         recoverable = true;
         break;

      case UNEXPECTED_PAREN:
         error_message = cons_list(make_static_strnode("unexpected \')\'"));
         break;

      case UNEXPECTED_BRACKET:
         error_message = cons_list(make_static_strnode("unexpected \']\'"));
         break;

      case UNEXPECTED_BRACE:
         error_message = cons_list(make_static_strnode("unexpected \'}\'"));
         break;

      case DK_HOW:
         recoverable = true;
         /* FALLTHROUGH */

      case DK_HOW_UNREC:
         error_message = cons_list(
            make_static_strnode("I don\'t know how to"), 
            error_desc);
         break;

      case NO_CATCH_TAG:
         error_message = cons_list(
            make_static_strnode("Can't find catch tag for"), 
            error_desc);
         break;

      case ALREADY_DEFINED:
         error_message = cons_list(
            error_desc,
            make_static_strnode("is already defined"));
         break;

      case STOP_ERROR:
         yield_flag = 1;
         error_message = cons_list(make_static_strnode("Stopping..."));
         break;

      case ALREADY_DRIBBLING:
         error_message = cons_list(make_static_strnode("Already dribbling"));
         break;

      case FILE_ERROR:
         error_message = cons_list(
            make_static_strnode("File system error:"),
            error_desc);
         break;

      case IF_WARNING:
         error_message = cons_list(make_static_strnode("Assuming you mean IFELSE, not IF"));
         warning = true;
         break;

      case SHADOW_WARN:
         error_message = cons_list(
            error_desc,
            make_static_strnode("shadowed by local in procedure call"));
         warning = true;
         break;

      case USER_ERR:
         if (error_desc == Unbound)
            {
            error_message = cons_list(make_static_strnode("Throw \"Error"));
            }
         else
            {
            uplevel = true;
            if (is_list(error_desc))
               {
               error_message = error_desc;
               }
            else
               {
               error_message = cons_list(error_desc);
               }
            }
         break;
         
      case IS_PRIM:
         error_message = cons_list(
            error_desc,
            make_static_strnode("is a primitive"));
         break;

      case NOT_INSIDE:
         error_message = cons_list(make_static_strnode("Can't use TO inside a procedure"));
         break;
         
      case AT_TOPLEVEL:
         error_message = cons_list(
            make_static_strnode("Can only use"),
            error_desc,
            make_static_strnode("inside a procedure"));
         break;

      case NO_TEST:
         error_message = cons_list(
            fun,
            make_static_strnode("without TEST"));
         break;

      case ERR_MACRO:
         error_message = cons_list(
            make_static_strnode("Macro returned"), 
            error_desc,
            make_static_strnode("instead of a list"));
         break;

      case DEEPEND:
         if (error_desc == NIL)
            {
            error_message = cons_list(make_static_strnode("END inside multi-line instruction."));
            }
         else
            {
            error_message = cons_list(
               make_static_strnode("END inside multi-line instruction in"),
               error_desc);
            }
         break;
             
      default:
         prepare_to_exit(FALSE);
         printfx("Unknown error condition - internal error.\n");
         exit(1);
      }

   deref(didnt_output_name);
   didnt_output_name = NIL;
   if (uplevel && ufun != NIL)
      {
      ufun = reref(ufun, last_ufun);
      this_line = reref(this_line, last_line);
      }

   NODE * error_code = make_intnode((FIXNUM) error_type);

   // replace the old error 4-tuple withthe new one
   deref(err_mesg);
   if (ufun != NIL)
      {
      err_mesg = cons_list(error_code, error_message, ufun, this_line);
      }
   else
      {
      err_mesg = cons_list(error_code, error_message, NIL, NIL);
      }
   vref(err_mesg);

   deref(error_desc);

   if (warning)
      {
      err_print();
      return Unbound;
      }

   NODE * err_act = vref(valnode__caseobj(Erract));
   NODE * val     = Unbound;

   if (err_act != NIL && err_act != UNDEFINED)
      {
      if (error_type != erract_errtype)
         {
         int sv_val_status = val_status;

         erract_errtype = error_type;
         setvalnode__caseobj(Erract, NIL);
         val_status = 5;
         val = err_eval_driver(err_act);
         ref(val);
         val_status = sv_val_status;
         setvalnode__caseobj(Erract, err_act);
         deref(err_act);
         if (recoverable && val != Unbound)
            {
            return unref(val);
            }
         else if (!recoverable && val != Unbound)
            {
            ndprintf(stdout, "You don't say what to do with %s\n", val);
            val = reref(val, Unbound);
            throw_node = reref(throw_node, Toplevel);
            }
         else
            {
            return Unbound;
            }
         }
      else
         {
         ndprintf(stdout, "Erract loop\n");
         throw_node = reref(throw_node, Toplevel);
         }
      }
   else
      {
      /* no erract */
      throw_node = reref(throw_node, Error);
      }
   stopping_flag = THROWING;
   output_node = Unbound;
   return unref(val);
   }

NODE *lerror(NODE *)
   {
   NODE *val;

   val = err_mesg;
   err_mesg = NIL;
   return (unref(val));
   }

NODE *lpause(NODE*)
   {
   NODE *elist = NIL, *val = Unbound, *uname = NIL;
   int sav_input_blocking;
   int sv_val_status;

   jmp_buf sav_iblk;


   if (err_mesg != NIL) err_print();
   /* if (ufun != NIL) */
   {
      uname = reref(uname, ufun);
      ufun = NIL;
   }

   ndprintf(stdout, "Pausing...");

   memcpy(sav_iblk, iblk_buf, sizeof(sav_iblk));

   sav_input_blocking = input_blocking;
   input_blocking = 0;
   sv_val_status = val_status;
   while (RUNNING)
      {
      if (uname != NIL) print_node(stdout, uname);
      new_line(stdout);
      input_mode = INPUTMODE_Pause;
      elist = reref(elist, reader(stdin, "? "));
      if (NOT_THROWING) 
         {
         elist = reref(elist, parser(elist, TRUE));
         }
      else 
         {
         elist = reref(elist, NIL);
         }
      input_mode = INPUTMODE_None;
      MyMessageScan();
      if (feof(stdin) /*ggm && !isatty(0)*/) lbye(NIL);
#ifdef __ZTC__
      if (feof(stdin)) rewind(stdin);
#endif
      val_status = 5;
      if (elist != NIL) eval_driver(elist);
      if (stopping_flag == THROWING)
         {
         if (compare_node(throw_node, Pause, TRUE) == 0)
            {
            val = vref(output_node);
            output_node = reref(output_node, Unbound);
            stopping_flag = RUN;
            deref(elist);

            memcpy(iblk_buf, sav_iblk, sizeof(sav_iblk));

            input_blocking = sav_input_blocking;
            val_status = sv_val_status;
            if (uname != NIL)
               {
               ufun = reref(ufun, uname);
               deref(uname);
               }
            return unref(val);
            }
         else if (compare_node(throw_node, Error, TRUE) == 0)
            {
            err_print();
            stopping_flag = RUN;
            }
         }
      }
   deref(elist);

   memcpy(iblk_buf, sav_iblk, sizeof(sav_iblk));

   input_blocking = sav_input_blocking;
   unblock_input();
   val_status = sv_val_status;
   if (uname != NIL)
      {
      ufun = reref(ufun, uname);
      deref(uname);
      }
   
   return unref(val);
   }

NODE *lcontinue(NODE *args)
   {
   stopping_flag = THROWING;
   throw_node = reref(throw_node, Pause);
   if (args != NIL)
      {
      output_node = reref(output_node, car(args));
      }
   else
      {
      output_node = reref(output_node, Unbound);
      }

   return Unbound;
   }


void uninitialize_error()
   {
   deref(throw_node);
   throw_node = NIL;

   deref(err_mesg);
   err_mesg = NIL;
   }
