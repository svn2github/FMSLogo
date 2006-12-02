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

CSelectProcedureWindow::CSelectProcedureWindow(
   TWindow    * Parent, 
   const char * Caption
   )
   : TDialog(Parent, "IDD_SELECTPROCEDURE"),
     m_FileEditAll(false)
   {
   m_SelectedProcedures[0] = '\0';

   SetCaption(Caption);
   }

void CSelectProcedureWindow::DoAll(UINT)
   {
   m_FileEditAll = true;
   CloseWindow(TRUE);
   }

void CSelectProcedureWindow::DoCombo(UINT)
   {
   TMessage Msg = __GetTMessage();

   if (Msg.LP.Hi == CBN_DBLCLK)
      {
      CloseWindow(TRUE);
      }
   }

bool CSelectProcedureWindow::CanClose()
   {
   GetDlgItemText(ID_SELECTPROCEDURE_COMBO, m_SelectedProcedures, MAX_BUFFER_SIZE);

   return true;
   }

void CSelectProcedureWindow::SetupWindow()
   {
   TDialog::SetupWindow();

   // fill in the text
   SetDlgItemText(IDOK,                   LOCALIZED_SELECTPROCEDURE_OK);
   SetDlgItemText(IDCANCEL,               LOCALIZED_SELECTPROCEDURE_CANCEL);
   SetDlgItemText(ID_SELECTPROCEDURE_ALL, LOCALIZED_SELECTPROCEDURE_ALL);

   // get procedures
   NODE * proclist = lprocedures(NIL);

   // put the name of each procedure into the list box
   for (NODE* proclist_node = proclist;
        proclist_node != NIL;
        proclist_node = cdr(proclist_node))
      {
      char tempbuff[MAX_BUFFER_SIZE];
      cnv_strnode_string(tempbuff, proclist_node);
      SendDlgItemMsg(ID_SELECTPROCEDURE_COMBO, CB_ADDSTRING, 0, (LONG) tempbuff);
      }

   gcref(proclist);
   }


void CSelectProcedureWindow::ShowDialog()
   {
   // Show the dialog as a modal box
   if (Execute() == IDOK)
      {
      NODE *arg;
      if (m_FileEditAll)
         {
         // the user clicked ALL get all procedures
         arg = lprocedures(NIL);
         }
      else
         {
         // else find what user selected
         arg = cons_list(make_strnode(m_SelectedProcedures));
         }

      // if something edit it
      if (arg != NIL) 
         {
         OnChoice(arg);
         }

      gcref(arg);
      }
   }

DEFINE_RESPONSE_TABLE1(CSelectProcedureWindow, TDialog)
  EV_CHILD_NOTIFY_ALL_CODES(ID_SELECTPROCEDURE_ALL,   DoAll),
  EV_CHILD_NOTIFY_ALL_CODES(ID_SELECTPROCEDURE_COMBO, DoCombo),
END_RESPONSE_TABLE;


// shows a "Select Procedures to Edit" dialog
CEditProcedureWindow::CEditProcedureWindow(TWindow * Parent) 
   : CSelectProcedureWindow(Parent, LOCALIZED_EDITPROCEDURE)
   {
   }

void
CEditProcedureWindow::OnChoice(NODE * Procedures)
   {
   ledit(Procedures);
   }


// shows a "Select Procedures to Erase" dialog
CEraseProcedureWindow::CEraseProcedureWindow(TWindow * Parent) 
   : CSelectProcedureWindow(Parent, LOCALIZED_ERASEPROCEDURE)
   {
   }

void
CEraseProcedureWindow::OnChoice(NODE * Procedures)
   {
   lerase(Procedures);
   }

