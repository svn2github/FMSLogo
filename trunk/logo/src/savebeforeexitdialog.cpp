/*
*  Copyright (C) 2006 by David Costanzo
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*
*/

#include "allwind.h"

CSaveBeforeExitDialog::CSaveBeforeExitDialog(
   TWindow *Parent
   ) : TDialog(Parent, IDD_SAVEBEFOREEXIT),
       m_ExitStatus(IDCANCEL)
   {
   SetCaption(LOCALIZED_UNSAVEDCHANGES);
   }

void CSaveBeforeExitDialog::SetupWindow()
   {
   TDialog::SetupWindow();

   SetDlgItemText(IDYES,                      LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT);
   SetDlgItemText(IDNO,                       LOCALIZED_UNSAVEDCHANGES_DONTSAVE);
   SetDlgItemText(IDCANCEL,                   LOCALIZED_UNSAVEDCHANGES_CANCEL);
   SetDlgItemText(ID_UNSAVEDCHANGES_MESSAGE1, LOCALIZED_UNSAVEDCHANGES_MESSAGE1);
   SetDlgItemText(ID_UNSAVEDCHANGES_MESSAGE2, LOCALIZED_UNSAVEDCHANGES_MESSAGE2);
   }

void CSaveBeforeExitDialog::EvSaveBeforeExit()
   {
   m_ExitStatus = IDYES;
   CloseWindow();
   }

void CSaveBeforeExitDialog::EvExitWithoutSaving()
   {
   m_ExitStatus = IDNO;
   CloseWindow();
   }

int CSaveBeforeExitDialog::GetExitCode()
   {
   return m_ExitStatus;
   }

DEFINE_RESPONSE_TABLE1(CSaveBeforeExitDialog, TDialog)
   EV_BN_CLICKED(IDYES, EvSaveBeforeExit),
   EV_BN_CLICKED(IDNO,  EvExitWithoutSaving),
END_RESPONSE_TABLE;

