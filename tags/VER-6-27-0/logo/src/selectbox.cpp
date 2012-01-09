/*
 *  Copyright (C) 2007 by David Costanzo
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

#include "selectbox.h"
#include "mainwind.h"
#include "logorc.h"
#include "argumentutils.h"
#include "debugheap.h"

#include "localizedstrings.h"

const int DOUBLECLICK = 2;

CSelectBox::CSelectBox(
    TWindow     * Parent,
    const char  * Title,
    struct NODE * Choices
    ) : TDialog(Parent, IDD_SELECTBOX),
        m_ListBox(this, ID_CHOICES),
        m_Choices(Choices),
        m_Selection(-1)
{
    SetCaption(Title);
}


void CSelectBox::SetupWindow()
{
    TDialog::SetupWindow();

    // set the text in all of the controls
    static const MENUITEM text[] = {
        {LOCALIZED_SELECTBOX_OK,     IDOK},
        {LOCALIZED_SELECTBOX_CANCEL, IDCANCEL},
    };
    SetTextOnChildWindows(this, text, ARRAYSIZE(text));

    // add a string to the pick-list for each choice
    for (NODE * choices = m_Choices;
         choices != NIL;
         choices = cdr(choices))
    {
        char choice[MAX_BUFFER_SIZE];
        cnv_strnode_string(choice, choices);

        m_ListBox.AddString(choice);
    }

    // select the first item
    if (m_ListBox.GetCount() != 0) 
    {
        m_ListBox.SetSelIndex(0);
        m_ListBox.SetCaretIndex(0, false);
    }
}


// User pressed OK
void
CSelectBox::CmOk()
{
    // Get selection from the listbox
    m_Selection = m_ListBox.GetSelIndex();
    if (m_Selection < 0)
    {
        m_Selection = 0;
    }

    TDialog::CmOk();
}


// User double-clicked on a choice.
void
CSelectBox::OnDoubleClick()
{
    // Get selection from the listbox
    m_Selection = m_ListBox.GetSelIndex();
    if (m_Selection < 0)
    {
        m_Selection = 0;
    }

    CloseWindow();
}

//
// Return the result of the selection.
//
int
CSelectBox::GetSelection() const
{
    return m_Selection;
}

DEFINE_RESPONSE_TABLE1(CSelectBox, TDialog)
    EV_CHILD_NOTIFY(ID_CHOICES, DOUBLECLICK, OnDoubleClick),
    EV_COMMAND(IDOK, CmOk),
END_RESPONSE_TABLE;
