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

/* File editor members */

TMyFileEditWindow::TMyFileEditWindow(TWindow *AParent, LPSTR ATitle)
: TDialog(AParent, ATitle)
   {
   }

TMyFileEditWindow::~TMyFileEditWindow()
   {
   }

void TMyFileEditWindow::DoAll(UINT)
   {
   FileEditAll = 1;
   CloseWindow(TRUE);
   }

void TMyFileEditWindow::DoCombo(UINT)
   {
   TMessage Msg = __GetTMessage();

   if (Msg.LP.Hi == CBN_DBLCLK)
      {
      CloseWindow(TRUE);
      }
   }

bool TMyFileEditWindow::CanClose()
   {
   SendDlgItemMsg(
      ID_FILEEDITCOMBO,
      WM_GETTEXT,
      MAX_BUFFER_SIZE,
      (LONG) SelectedText);

   return TRUE;
   }

void TMyFileEditWindow::SetupWindow()
   {
   // get procedures
   NODE * proclst = lprocedures(NIL);

   // pop them into the list box
   while (proclst != NIL)
      {
      char tempbuff[MAX_BUFFER_SIZE];
      cnv_strnode_string(tempbuff, proclst);
      SendDlgItemMsg(ID_FILEEDITCOMBO, CB_ADDSTRING, 0, (LONG) tempbuff);
      proclst = cdr(proclst);
      }

   // REVISIT: does this leak proclst?
   }

DEFINE_RESPONSE_TABLE1(TMyFileEditWindow, TDialog)
  EV_CHILD_NOTIFY_ALL_CODES(ID_FILEEDITALL, DoAll),
  EV_CHILD_NOTIFY_ALL_CODES(ID_FILEEDITCOMBO, DoCombo),
END_RESPONSE_TABLE;

