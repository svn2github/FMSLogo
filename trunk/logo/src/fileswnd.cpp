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

void filesave(const char *FileName)
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

   PrintWorkspaceToFileStream(fopen(FileName, "w+"));
   }


bool fileload(const char *Filename)
   {
   bool isOk;

   FILE * filestream = fopen(Filename, "r");
   if (filestream != NULL)
      {
      // save all global state that may be modified
      NODE *previous_startup = valnode__caseobj(Startup);

      FIXNUM savedValueStatus = g_ValueStatus;
      bool   savedIsDirty     = IsDirty;
      bool   savedYieldFlag   = yield_flag;
      FILE * savedLoadStream  = loadstream;
      NODE * savedCurrentLine = vref(current_line);

      loadstream = filestream;

      yield_flag = false;
      lsetcursorwait(NIL);

      while (!feof(loadstream) && NOT_THROWING)
         {
         current_line = reref(current_line, reader(loadstream, ""));
         NODE * exec_list = parser(current_line, true);
         g_ValueStatus = VALUE_STATUS_NotOk;
         eval_driver(exec_list);
         }
      fclose(loadstream);

      lsetcursorarrow(NIL);
      yield_flag = savedYieldFlag;

      loadstream = savedLoadStream;

      // run startup after restoring loadstream so
      // that we don't confuse to_helper into reading
      // more data from the current (closed) file stream.
      runstartup(previous_startup);

      // restore the global state
      g_ValueStatus = savedValueStatus;
      IsDirty       = savedIsDirty;
      deref(current_line);
      current_line = savedCurrentLine;

      isOk = true;
      }
   else
      {
      isOk = false;
      }

   return isOk;
   }
