/*
*  Copyright (C) 2011 by David Costanzo
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*
*/
#include "selectstartupinstruction.h"
#include "localizedstrings.h"
#include "logorc.h"
#include "mainwind.h"

#include "wrksp.h"
#include "argumentutils.h"
#include "debugheap.h"

CSelectStartupInstructionDialog::CSelectStartupInstructionDialog(
    TWindow    * Parent,
    EXPLAINTEXT  ExplainText
    )
    : TDialog(Parent, IDD_SELECTSTARTUPINSTRUCTION)
{
    SetCaption(LOCALIZED_SELECTSTARTUP_CAPTION);

    switch (ExplainText)
    {
    case EXPLAINTEXT_StartupNotDefined:
        m_ExplainText = LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED;
        break;

    case EXPLAINTEXT_StartupEmpty:
        m_ExplainText = LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY;
        break;

    case EXPLAINTEXT_StartupNotList:
        m_ExplainText = LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST;
        break;
    }

    m_SelectedInstruction[0] = '\0';
}

void CSelectStartupInstructionDialog::DoEditControl(UINT message)
{
    switch (message)
    {
    case EN_CHANGE:
        // Something changed.  Read the update into our buffer.
        GetDlgItemText(
            ID_SELECTSTARTUPINSTRUCTION_EDIT,
            m_SelectedInstruction,
            ARRAYSIZE(m_SelectedInstruction));
        break;
    }
}

void CSelectStartupInstructionDialog::DoListBox(UINT message)
{
    switch (message)
    {
    case LBN_DBLCLK:
        CloseWindow(TRUE);
        break;

    case LBN_SELCHANGE:
        // Get the index of the selected item
        int selection = SendDlgItemMsg(
            ID_SELECTSTARTUPINSTRUCTION_LISTBOX,
            LB_GETCURSEL,
            0,
            0);
        if (selection != LB_ERR)
        {
            SendDlgItemMsg(
                ID_SELECTSTARTUPINSTRUCTION_LISTBOX,
                LB_GETTEXT,
                selection,
                (LPARAM) m_SelectedInstruction);

            ::SetWindowText(
                GetDlgItem(ID_SELECTSTARTUPINSTRUCTION_EDIT),
                m_SelectedInstruction);
        }
        break;
    }
}

const char * CSelectStartupInstructionDialog::GetSelectedInstruction() const
{
    return m_SelectedInstruction;
}

bool CSelectStartupInstructionDialog::CanClose()
{
    if (m_SelectedInstruction[0] == '\0')
    {
        // Until something is entered into the list
        // box, we cannot close.
        return false;
    }

    return true;
}

void CSelectStartupInstructionDialog::CmOk(TCommandEnabler& commandHandler)
{
    commandHandler.Enable(m_SelectedInstruction[0] != '\0');
}

void CSelectStartupInstructionDialog::SetupWindow()
{
    TDialog::SetupWindow();

    static const MENUITEM text[] = {
        {LOCALIZED_SELECTPROCEDURE_OK,     IDOK},
        {LOCALIZED_SELECTPROCEDURE_CANCEL, IDCANCEL},
    };

    // fill in the text
    SetTextOnChildWindows(this, text, ARRAYSIZE(text));
    SetDlgItemText(ID_SELECTSTARTUPINSTRUCTION_EXPLAINTEXT, m_ExplainText);

    // get procedures
    NODE * proclist = lprocedures(NIL);
    if (proclist != NIL)
    {
        // put the name of each procedure into the list box
        for (NODE* proclist_node = proclist;
             proclist_node != NIL;
             proclist_node = cdr(proclist_node))
        {
            char tempbuff[MAX_BUFFER_SIZE];
            cnv_strnode_string(tempbuff, proclist_node);
            SendDlgItemMsg(
                ID_SELECTSTARTUPINSTRUCTION_LISTBOX,
                LB_ADDSTRING,
                0,
                (LONG) tempbuff);
        }

        gcref(proclist);
    }
    else
    {
        // There are no procedures
        SendDlgItemMsg(
            ID_SELECTSTARTUPINSTRUCTION_LISTBOX,
            LB_ADDSTRING, 
            0, 
            (LONG) LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED);
        
        ::EnableWindow(
            GetDlgItem(ID_SELECTSTARTUPINSTRUCTION_LISTBOX),
            false);
    }
}

DEFINE_RESPONSE_TABLE1(CSelectStartupInstructionDialog, TDialog)
    EV_CHILD_NOTIFY_ALL_CODES(ID_SELECTSTARTUPINSTRUCTION_EDIT,    DoEditControl),
    EV_CHILD_NOTIFY_ALL_CODES(ID_SELECTSTARTUPINSTRUCTION_LISTBOX, DoListBox),
    EV_COMMAND_ENABLE(IDOK, CmOk),
END_RESPONSE_TABLE;

