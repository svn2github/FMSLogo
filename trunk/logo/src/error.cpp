/*
*      error.cpp         logo error module                       dvb
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

// Holds the values for ERROR
static const char * g_ErrorFormatString = NULL;
static NODE *       g_ErrorArguments    = NIL;
static NODE *       g_ErrorCode         = NIL;
static NODE *       g_ErrorFunction     = NIL;
static NODE *       g_ErrorLine         = NIL;

static bool g_IsRunningErractInstructionList = false;

static
void set_is_running_erract_flag()
   {
   g_IsRunningErractInstructionList = true;
   }

// REVISIT: does this really need to be callable from other files?
void clear_is_running_erract_flag()
   {
   g_IsRunningErractInstructionList = false;
   }

static
bool last_error_exists()
   {
   return g_ErrorFormatString != NULL;
   }

static
void clear_last_error()
   {
   g_ErrorFormatString = NULL;

   deref(g_ErrorArguments);
   g_ErrorArguments = NIL;

   deref(g_ErrorCode);
   g_ErrorCode = NIL;

   deref(g_ErrorFunction);
   g_ErrorFunction = NIL;

   deref(g_ErrorLine);
   g_ErrorLine = NIL;
   }

static
void 
err_print_helper(
   char * Buffer,
   size_t BufferLength
   )
   {
   if (!last_error_exists())
      {
      // there is no error to print
      return;
      }

   FILE * fp;
   if (Buffer == NULL)
      {
      fp = stdout;
      }
   else
      {
      print_stringptr = Buffer;
      print_stringlen = BufferLength;
      fp = NULL;
      }

   CTRLTYPE save_flag = stopping_flag;
   stopping_flag = RUN;
   print_backslashes = true;

   if (g_ErrorArguments == NIL)
      {
      // this is a zero-argument error message
      ndprintf(fp, g_ErrorFormatString);
      }
   else if (cdr(g_ErrorArguments) == NIL)
      {
      // this is a one-argument error message
      ndprintf(fp, g_ErrorFormatString, car(g_ErrorArguments));
      }
   else
      {
      // this is a two-argument error message
      ndprintf(fp, g_ErrorFormatString, car(g_ErrorArguments), cadr(g_ErrorArguments));
      }

   // Print the location where the error happened, if applicable.
   if (g_ErrorFunction != NIL && Buffer == NULL)
      {
      ndprintf(fp, LOCALIZED_TRACING_LOCATION, g_ErrorFunction, g_ErrorLine);
      }

   // flush the file stream
   if (Buffer == NULL)
      {
      new_line(stdout);
      }
   else
      {
      *print_stringptr = '\0';
      }

   print_backslashes = false;
   stopping_flag = save_flag;
   }

void err_print()
   {
   // print the error
   err_print_helper(NULL, 0);

   // clear the error now that it has been consumed
   clear_last_error();
   }

NODE *err_logo(ERR_TYPES error_type, NODE *error_desc)
   {
   clear_last_error();

   bool recoverable = false;
   bool warning = false;
   bool uplevel = false;

   NODE * error_message = NIL;

   ref(error_desc);
   switch (error_type)
      {
      case FATAL:
         prepare_to_exit(FALSE);
         printfx("%s", LOCALIZED_ERROR_FATALINTERNAL);
         exit(1);

      case OUT_OF_MEM_UNREC:
         prepare_to_exit(FALSE);
         printfx("%s", LOCALIZED_ERROR_OUTOFMEMORY);
         exit(1);

      case OUT_OF_MEM:
         use_reserve_tank();
         g_ErrorFormatString = LOCALIZED_ERROR_OUTOFMEMORY;
         break;

      case STACK_OVERFLOW:
         g_ErrorFormatString = LOCALIZED_ERROR_STACKOVERFLOW;
         break;

      case TURTLE_OUT_OF_BOUNDS:
         g_ErrorFormatString = LOCALIZED_ERROR_TURTLEOUTOFBOUNDS;
         break;

      case BAD_GRAPH_INIT:
         g_ErrorFormatString = LOCALIZED_ERROR_BADGRAPHINIT;
         break;

      case BAD_DATA_UNREC:
         g_ErrorFormatString = LOCALIZED_ERROR_BADDATA;
         error_message = cons_list(fun, error_desc);
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

          g_ErrorFormatString = LOCALIZED_ERROR_DIDNTOUTPUT;
          error_message = cons_list(last_call, error_desc);
          recoverable = true;
          break;

      case NOT_ENOUGH:
         g_ErrorFormatString = LOCALIZED_ERROR_NOTENOUGHINPUTS;
         error_message = cons_list(error_desc == NIL ? fun : error_desc);
         break;

      case BAD_DATA:
         g_ErrorFormatString = LOCALIZED_ERROR_BADDATA;
         error_message = cons_list(fun, error_desc);
         recoverable = true;
         break;

      case APPLY_BAD_DATA:
         g_ErrorFormatString = LOCALIZED_ERROR_BADDATA;
         error_message = cons_list(make_static_strnode("APPLY"), error_desc);
         recoverable = true;
         break;

      case TOO_MUCH:
         g_ErrorFormatString = LOCALIZED_ERROR_TOOMUCH;
         break;

      case DK_WHAT_UP:
         uplevel = true;
         // FALLTHROUGH
      case DK_WHAT:
         g_ErrorFormatString = LOCALIZED_ERROR_DONTSAYWHATTODOWITH;
         error_message = cons_list(error_desc);
         break;

      case PAREN_MISMATCH:
         g_ErrorFormatString = LOCALIZED_ERROR_PARENMISMATCH;
         break;

      case NO_VALUE:
         g_ErrorFormatString = LOCALIZED_ERROR_NOVALUE;
         error_message = cons_list(error_desc);
         recoverable = true;
         break;

      case UNEXPECTED_PAREN:
         g_ErrorFormatString = LOCALIZED_ERROR_UNEXPECTEDPAREN;
         break;

      case UNEXPECTED_BRACKET:
         g_ErrorFormatString = LOCALIZED_ERROR_UNEXPECTEDBRACKET;
         break;

      case UNEXPECTED_BRACE:
         g_ErrorFormatString = LOCALIZED_ERROR_UNEXPECTEDBRACE;
         break;

      case DK_HOW:
         recoverable = true;
         /* FALLTHROUGH */

      case DK_HOW_UNREC:
         g_ErrorFormatString = LOCALIZED_ERROR_DONTKNOWHOWTO;
         error_message = cons_list(error_desc);
         break;

      case NO_CATCH_TAG:
         g_ErrorFormatString = LOCALIZED_ERROR_NOCATCHTAG;
         error_message = cons_list(error_desc);
         break;

      case ALREADY_DEFINED:
         g_ErrorFormatString = LOCALIZED_ERROR_ALREADYDEFINED;
         error_message = cons_list(error_desc);
         break;

      case STOP_ERROR:
         g_ErrorFormatString = LOCALIZED_ERROR_STOPPING;
         yield_flag = true;
         break;

      case ALREADY_DRIBBLING:
         g_ErrorFormatString = LOCALIZED_ERROR_ALREADYDRIBBLING;
         break;

      case FILE_ERROR:
         g_ErrorFormatString = LOCALIZED_ERROR_FILESYSTEM;
         error_message = cons_list(error_desc);
         break;

      case IF_WARNING:
         g_ErrorFormatString = LOCALIZED_ERROR_IFWARNING;
         warning = true;
         break;

      case SHADOW_WARN:
         g_ErrorFormatString = LOCALIZED_ERROR_SHADOWWARNING;
         error_message = cons_list(error_desc);
         warning = true;
         break;

      case USER_ERR:
         if (error_desc == Unbound)
            {
            g_ErrorFormatString = LOCALIZED_ERROR_USER;
            }
         else
            {
            uplevel = true;

            g_ErrorFormatString = "%p";
            error_message = cons_list(error_desc);
            }
         break;
         
      case IS_PRIM:
         g_ErrorFormatString = LOCALIZED_ERROR_ISPRIMITIVE;
         error_message = cons_list(error_desc);
         break;

      case NOT_INSIDE:
         g_ErrorFormatString = LOCALIZED_ERROR_TONOTINSIDE;
         break;
         
      case AT_TOPLEVEL:
         g_ErrorFormatString = LOCALIZED_ERROR_ATTOPLEVEL;
         error_message = cons_list(error_desc);
         break;

      case NO_TEST:
         g_ErrorFormatString = LOCALIZED_ERROR_NOTEST;
         error_message = cons_list(fun);
         break;

      case ERR_MACRO:
         g_ErrorFormatString = LOCALIZED_ERROR_BADMACROOUTPUT;
         error_message = cons_list(error_desc);
         break;

      case DEEPEND:
         if (error_desc == NIL)
            {
            g_ErrorFormatString = LOCALIZED_ERROR_DEEPEND;
            }
         else
            {
            g_ErrorFormatString = LOCALIZED_ERROR_DEEPENDIN;
            error_message = cons_list(error_desc);
            }
         break;
             
      default:
         prepare_to_exit(FALSE);
         printfx("%s", LOCALIZED_ERROR_UNKNOWN);
         exit(1);
      }

   deref(didnt_output_name);
   didnt_output_name = NIL;
   if (uplevel && ufun != NIL)
      {
      ufun = reref(ufun, last_ufun);
      this_line = reref(this_line, last_line);
      }

   g_ErrorCode = vref(make_intnode((FIXNUM) error_type));

   // replace the old error parameters with the new ones
   g_ErrorArguments = vref(error_message);

   if (ufun != NIL)
      {
      g_ErrorFunction = vref(ufun);
      g_ErrorLine     = vref(this_line);
      }

   deref(error_desc);

   if (warning)
      {
      err_print();
      return Unbound;
      }

   // If this error is recoverable and ERRACT is defined,
   // then we should run :ERRACT to get a new value.
   NODE * err_act_value = valnode__caseobj(Erract);
   NODE * new_throw_node;

   if (g_CatchErrorCount == 0 && 
       !g_IsRunningErractInstructionList && 
       err_act_value != NIL && 
       err_act_value != UNDEFINED)
      {
      // don't let one erract interrupt another
      set_is_running_erract_flag();

      // run the erract instruction list
      FIXNUM saved_value_status = g_ValueStatus;

      NODE * val = err_eval_driver(err_act_value);

      g_ValueStatus = saved_value_status;

      // reset the erract-is-running flag so that it can be called again
      clear_is_running_erract_flag();

      if (val != Unbound)
         {
         if (recoverable)
            {
            // Return the value returned from :ERRACT so that the
            // caller can replace the bad value with this one.
            return unref(val);
            }
         else
            {
            // This error wasn't recoverable, so ERRACT shouldn't
            // have output a new value to use.
            ndprintf(stdout, LOCALIZED_ERROR_DONTSAYWHATTODOWITH"\n", val);
            deref(val);
            new_throw_node = Toplevel;
            }
         }
      else
         {
         // val is Unbound
         //
         // If the error is recoverable, this is a problem because
         // Erract didn't output a replacement value.
         //
         // If the error is not recoverable, then the Error was not handled.
         //
         // Either way, we throw Error
         new_throw_node = Error;
         }
      }
   else
      {
      // We're in a catch block, or no erract is defined, or the erract 
      // instruction list that we are currently processing threw an error.
      // Either way, we should throw the error.
      new_throw_node = Error;
      }

   stopping_flag = THROWING;
   throw_node  = reref(throw_node, new_throw_node);
   output_node = reref(output_node, Unbound);
   return Unbound;
   }

NODE *lerror(NODE *)
   {
   if (!last_error_exists())
      {
      return NIL;
      }

   // format the error message into a buffer
   char error_message[200];
   err_print_helper(error_message, sizeof(error_message));

   // return the ERROR 4-tuple [code message function line]
   NODE * val = cons_list(
      g_ErrorCode,
      make_strnode(error_message),
      g_ErrorFunction,
      g_ErrorLine);

   clear_last_error();

   return val;
   }

NODE *lpause(NODE*)
   {
   if (last_error_exists())
      {
      err_print();
      }

   NODE * uname = vref(ufun);
   ufun = NIL;

   ndprintf(stdout, LOCALIZED_PAUSING);

   jmp_buf sav_iblk;
   memcpy(sav_iblk, iblk_buf, sizeof(sav_iblk));

   bool saved_input_blocking = input_blocking;
   input_blocking = false;
   FIXNUM saved_value_status = g_ValueStatus;
   while (RUNNING)
      {
      if (uname != NIL) 
         {
         print_node(stdout, uname);
         }

      new_line(stdout);

      // get the interactive input for the "pause"
      input_mode = INPUTMODE_Pause;
      NODE * elist = vref(reader(stdin, "? "));
      if (NOT_THROWING) 
         {
         elist = reref(elist, parser(elist, true));
         }
      else 
         {
         elist = reref(elist, NIL);
         }

      // check if there are other things to do
      input_mode = INPUTMODE_None;
      MyMessageScan();

      if (feof(stdin)) 
         {
         lbye(NIL);
         }

      g_ValueStatus = VALUE_STATUS_ValueMaybeOkInMacro;
      eval_driver(elist);

      if (stopping_flag == THROWING)
         {
         if (compare_node(throw_node, Pause, true) == 0)
            {
            NODE * val = vref(output_node);
            output_node = reref(output_node, Unbound);
            stopping_flag = RUN;

            memcpy(iblk_buf, sav_iblk, sizeof(sav_iblk));

            input_blocking = saved_input_blocking;
            g_ValueStatus  = saved_value_status;
            if (uname != NIL)
               {
               ufun = reref(ufun, uname);
               deref(uname);
               }

            deref(elist);
            return unref(val);
            }
         else if (compare_node(throw_node, Error, true) == 0)
            {
            err_print();
            stopping_flag = RUN;
            }
         }

      check_stop(false);

      deref(elist);
      }

   memcpy(iblk_buf, sav_iblk, sizeof(sav_iblk));

   input_blocking = saved_input_blocking;
   unblock_input();
   g_ValueStatus = saved_value_status;
   if (uname != NIL)
      {
      ufun = reref(ufun, uname);
      deref(uname);
      }
   
   return Unbound;
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

   clear_last_error();
   }
