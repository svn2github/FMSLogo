// Copyright (C) 2006 by the David Costanzo
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#include "minieditor.h"

#include "utils.h"
#include "logorc.h"
#include "localizedstrings.h"
#include "debugheap.h"

TMiniEditorRichEdit::TMiniEditorRichEdit(TWindow * Parent)
    : TRichEditWithPopup(Parent, ID_MINIEDITCTRL)
{
    Attr.Style |= ES_WANTRETURN | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_SUNKEN;
}


//
// constructor for a TMiniEditor
//
// initializes its data fields using passed parameters and default values
// constructs its child edit control
//
TMiniEditor::TMiniEditor(
    TWindow *    Parent,
    const char * ToLine
    ) : TDialog(Parent, IDD_MINIEDITOR),
        m_TextField(this),
        m_ToLine(this, ID_TOLINE, 0),
        m_EndButton(this, IDOK),
        m_EditorContents(NULL),
        m_EditorContentsLength(0)
{
    m_ToLineString = strnewdup(ToLine);

    SetCaption(ToLine);
}

TMiniEditor::~TMiniEditor()
{
    delete [] m_EditorContents;
    delete [] m_ToLineString;
}

// responds to an incoming WM_SETFOCUS message by setting the focus to
// the child edit control
//
void TMiniEditor::EvSetFocus(HWND)
{
    m_TextField.SetFocus();
}

void TMiniEditor::SetupWindow()
{
    TDialog::SetupWindow();

    m_ToLine.Create();
    m_ToLine.SetCaption(m_ToLineString);

    SetDlgItemText(IDOK, LOCALIZED_ALTERNATE_END);

    m_EndButton.Create();

    m_TextField.Create();

    LOGFONT lf;
    GetConfigurationFont("CommanderFont", lf);
    HFONT font = CreateFontIndirect(&lf);
    if (font != NULL)
    {
        m_TextField.SetWindowFont(font, TRUE);
        DeleteObject(font);
    }

    RecalculateLayout();

    m_TextField.SetFocus();
}


void TMiniEditor::CmOk()
{
    // Copy from the editor into a buffer

    // reset any value that may be in the editor
    delete [] m_EditorContents;
    m_EditorContentsLength = 0;

    // copy the data from the rich edit into a flat buffer
    m_EditorContentsLength = m_TextField.GetWindowTextLength();

    m_EditorContents = new char [m_EditorContentsLength + 1];
    if (m_EditorContents != NULL)
    {
        memset(m_EditorContents, 0, m_EditorContentsLength + 1);

        m_TextField.GetSubText(m_EditorContents, 0, m_EditorContentsLength);
    }

    TDialog::CmOk();
}


const char * TMiniEditor::GetText()
{
    return m_EditorContents;
}

void TMiniEditor::RecalculateLayout()
{
    TRect windowRect;
    GetWindowRect(windowRect);


    const int minHeight = 200;
    const int minWidth  = 100;
    if (windowRect.Width() < minWidth || windowRect.Height() < minHeight)
    {
        // don't let the size go below 100x100
        const int width  = windowRect.Width()  < minWidth  ? minWidth : windowRect.Width();
        const int height = windowRect.Height() < minHeight ? minHeight : windowRect.Height();

        SetWindowPos(NULL, 0, 0, width, height, SWP_NOMOVE);
    }

    TRect clientRect;
    GetClientRect(clientRect);

    TRect toLineRect;
    m_ToLine.GetWindowRect(toLineRect);

    TRect endButtonRect;
    m_EndButton.GetWindowRect(endButtonRect);

    const int totalWidth    = clientRect.Width();
    const int totalHeight   = clientRect.Height();

    const int toLineHeight    = toLineRect.Height();
    const int endButtonHeight = endButtonRect.Height();
    const int endButtonWidth  = endButtonRect.Width();

    const int xBorder = 4;
    const int yBorder = 4;
   

    // position the "END" button
    m_EndButton.SetWindowPos(
        NULL, 
        xBorder,
        totalHeight - yBorder - endButtonHeight,
        endButtonWidth,
        endButtonHeight,
        0);

    // position the procedure body
    m_TextField.SetWindowPos(
        NULL,
        xBorder,
        toLineHeight + 2 * yBorder,
        totalWidth - xBorder * 2,
        totalHeight - (4 * yBorder + toLineHeight + endButtonHeight),
        0);

    // position the "TO" line
    m_ToLine.SetWindowPos(
        NULL,
        xBorder,
        yBorder,
        totalWidth - xBorder * 2,
        toLineHeight,
        0);
}

void TMiniEditor::EvSize(UINT Arg1, TSize & NewSize)
{
    TDialog::EvSize(Arg1, NewSize);

    RecalculateLayout();

    Invalidate(true);
}

DEFINE_RESPONSE_TABLE1(TMiniEditor, TDialog)
    EV_WM_SETFOCUS,
    EV_WM_SIZE,
    EV_COMMAND(IDOK, CmOk),
END_RESPONSE_TABLE;
