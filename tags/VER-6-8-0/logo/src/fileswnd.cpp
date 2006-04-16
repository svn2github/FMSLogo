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

void filesave(const char *Filename)
   {
   if (::FindWindow(NULL, "Editor"))
      {
      MainWindowx->CommandWindow->MessageBox(
         "Did you know you have an edit session running?\n"
            "\n"
            "Any changes in this edit session are not being saved.",
         "Information",
         MB_OK | MB_ICONQUESTION);
      }

   NODE* filename_node = vref(make_strnode(Filename));

   FILE * tmp = writestream;
   writestream = open_file(filename_node, "w+");
   if (writestream != NULL)
      {
      int save_yield_flag = yield_flag;
      yield_flag = 0;
      lsetcursorwait(NIL);

      NODE * entire_workspace = vref(cons_list(lcontents(NIL)));
      lpo(entire_workspace);
      deref(entire_workspace);

      fclose(writestream);
      IsDirty = false;

      lsetcursorarrow(NIL);
      yield_flag = save_yield_flag;
      }
   else
      {
      err_logo(FILE_ERROR, make_static_strnode("Could not open file"));
      }
   writestream = tmp;

   deref(filename_node);
   }

void fileload(const char *Filename)
   {
   NODE *st = valnode__caseobj(Startup);
   int sv_val_status = val_status;

   NODE * arg = make_strnode(Filename);

   bool   IsDirtySave = IsDirty;
   FILE * tmp         = loadstream;
   NODE * tmp_line    = vref(current_line);
   loadstream = open_file(arg, "r");
   if (loadstream != NULL)
      {
      int save_yield_flag = yield_flag;
      yield_flag = 0;
      lsetcursorwait(NIL);

      while (!feof(loadstream) && NOT_THROWING)
         {
         current_line = reref(current_line, reader(loadstream, ""));
         NODE * exec_list = parser(current_line, true);
         val_status = 0;
         if (exec_list != NIL) 
            {
            eval_driver(exec_list);
            }
         }
      fclose(loadstream);

      lsetcursorarrow(NIL);
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
