/*
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

void filesave(char *temp)
   {
   FILE *tmp;
   NODE *arg;
   int save_yield_flag;

   if (::FindWindow(NULL, "Editor"))
      {
      MainWindowx->CommandWindow->MessageBox(
         "Did you know you have an edit session running?\n"
            "\n"
            "Any changes in this edit session are not being saved.",
         "Information",
         MB_OK | MB_ICONQUESTION);
      }

   arg = cons(make_strnode(temp, NULL, strlen(temp), STRING, strnzcpy), NIL);

   tmp = writestream;
   writestream = open_file(car(arg), "w+");
   if (writestream != NULL)
      {

      save_yield_flag = yield_flag;
      yield_flag = 0;
      lsetcursorwait();

      setcar(arg, cons(lcontents(), NIL));
      lpo(car(arg));
      fclose(writestream);
      IsDirty = 0;

      lsetcursorarrow();
      yield_flag = save_yield_flag;

      }
   else
      {
      err_logo(FILE_ERROR, make_static_strnode("Could not open file"));
      }
   writestream = tmp;
   }

void fileload(char *temp)
   {
   FILE *tmp;
   NODE *tmp_line, *exec_list, *arg;
   NODE *st = valnode__caseobj(Startup);
   int sv_val_status = val_status;
   int IsDirtySave;
   int save_yield_flag;

   arg = make_strnode(temp, NULL, strlen(temp), STRING, strnzcpy);

   IsDirtySave = IsDirty;
   tmp = loadstream;
   tmp_line = vref(current_line);
   loadstream = open_file(arg, "r");
   if (loadstream != NULL)
      {

      save_yield_flag = yield_flag;
      yield_flag = 0;
      lsetcursorwait();

      while (!feof(loadstream) && NOT_THROWING)
         {
         current_line = reref(current_line, reader(loadstream, ""));
         exec_list = parser(current_line, TRUE);
         val_status = 0;
         if (exec_list != NIL) eval_driver(exec_list);
         }
      fclose(loadstream);

      lsetcursorarrow();
      yield_flag = save_yield_flag;

      runstartup(st);
      val_status = sv_val_status;
      }
   else
      {
      err_logo(FILE_ERROR, make_static_strnode("Could not open file"));
      }
   loadstream = tmp;
   deref(current_line);
   current_line = tmp_line;
   IsDirty = IsDirtySave;
   }

NODE *cons_list3(NODE *node1, NODE *node2, NODE *node3)
   {
   NODE *nptr, *outline = NIL, *lastnode, *val;

   nptr = node1;
   val = cons(nptr, NIL);
   outline = val;
   lastnode = outline;

   nptr = node2;
   val = cons(nptr, NIL);
   setcdr(lastnode, val);
   lastnode = val;

   nptr = node3;
   val = cons(nptr, NIL);
   setcdr(lastnode, val);
   lastnode = val;

   return outline;
   }

