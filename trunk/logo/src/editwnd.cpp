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

TRichEditWithPopup::TRichEditWithPopup(
    TWindow* parent,
    int id,
    const char * text,
    int x,
    int y,
    int w,
    int h,
    const char * fileName
    ) : 
    TRichEdit(parent, id, text, x, y, w, h, fileName)
{
    PopupMenu.AppendMenu(MF_STRING, CM_EDITUNDO,       LOCALIZED_POPUP_UNDO);
    PopupMenu.AppendMenu(MF_SEPARATOR, 0, NULL);
    PopupMenu.AppendMenu(MF_STRING, CM_EDITCUT,        LOCALIZED_POPUP_CUT);
    PopupMenu.AppendMenu(MF_STRING, CM_EDITCOPY,       LOCALIZED_POPUP_COPY);
    PopupMenu.AppendMenu(MF_STRING, CM_EDITPASTE,      LOCALIZED_POPUP_PASTE);
    PopupMenu.AppendMenu(MF_STRING, CM_EDITDELETE,     LOCALIZED_POPUP_DELETE);
    PopupMenu.AppendMenu(MF_STRING, CM_EDITSELECTALL,  LOCALIZED_POPUP_SELECTALL);
    PopupMenu.AppendMenu(MF_SEPARATOR, 0, NULL);
    PopupMenu.AppendMenu(MF_STRING, CM_HELPEDIT_TOPIC, LOCALIZED_POPUP_HELP);
}

// protected constructor does not supply a menu
TRichEditWithPopup::TRichEditWithPopup(
    TWindow* parent,
    int      id
    ) : 
    TRichEdit(parent, id, NULL, 0, 0, 0, 0)
{
}

TRichEditWithPopup::~TRichEditWithPopup()
{
}

void TRichEditWithPopup::CmSelectAll()
{
    int endOfText = GetTextLen();
    SetSelection(0, endOfText);
}

void TRichEditWithPopup::CmSelectAllEnable(TCommandEnabler& commandHandler)
{
    UINT textLength = GetTextLen();
    bool isNotEmpty = textLength != 0;
    commandHandler.Enable(isNotEmpty);
}

void TRichEditWithPopup::EvRButtonUp(UINT, TPoint & point)
{
    ClientToScreen(point);
    PopupMenu.TrackPopupMenu(TPM_LEFTBUTTON, point, 0, HWindow);
}

// paste as raw text so that we don't preserve any
// formatting of rich text.
void TRichEditWithPopup::CmPasteAsText()
{
    OpenClipboard();

    HGLOBAL hText = GetClipboardData(CF_TEXT);
    if (hText)
    {
        LPCSTR lpText = (LPCSTR) GlobalLock(hText);
        Insert(lpText);
        GlobalUnlock(hText);
    }

    CloseClipboard();
}


// paste as raw text so that we don't preserve any
// formatting of rich text.
void TRichEditWithPopup::CmHelpEditTopic()
{
    ContextHelp(this);
}

int TRichEditWithPopup::GetCaretPosition()
{
    // Get the caret's position as a POINT
    POINT caretPosition;
    BOOL isOk = ::GetCaretPos(&caretPosition);
    if (!isOk)
    {
        return -1;
    }

    // Convert the POINT to a logical position within the text
    LRESULT caretChar = SendMessage(EM_CHARFROMPOS, 0, (LPARAM) &caretPosition);

    return caretChar;
}

void TRichEditWithPopup::SetCaretPosition(uint32 CaretCharIndex)
{
    // Convert the character index into a client rectangle POINT
    POINT caretPosition;
    SendMessage(EM_POSFROMCHAR, (WPARAM)&caretPosition, CaretCharIndex);

    // Set the caret's position
    ::SetCaretPos(caretPosition.x, caretPosition.y);
}

void TRichEditWithPopup::UpdateCaretPosition(uint32 NewCaretIndex)
{
    int previousCaretIndex = GetCaretPosition();

    // The TRichEdit class doesn't like it when the caret
    // and the selection are updated independently.
    // If there is a selection, then one of the endpoints
    // must be the current caret.  We need to update that
    // endpoint to use the new caret location.
    UINT start;
    UINT end;
    GetSelection(start, end);

    // If start != end, then it means that the user has 
    if (start != end)
    {
        if (start == previousCaretIndex)
        {
            SetSelection(NewCaretIndex, end);
        }
        else
        {
            SetSelection(start, NewCaretIndex);
        }
    }
    else 
    {
        SetSelection(NewCaretIndex, NewCaretIndex);
    }

    SetCaretPosition(NewCaretIndex);
}

int
TRichEditWithPopup::SearchForwardForMatchingParen(
    int  CaretPosition,
    char ParenToMatch
    )
{
    int bracketCount = 0;
    int parenCount   = 0;
    int braceCount   = 0;
    char searchChar[2];

    // search forward for the matching close bracket/paren
    int endOfText = GetTextLen();
    for (int searchCharIndex = CaretPosition; searchCharIndex < endOfText; searchCharIndex++)
    {
        GetSubText(searchChar, searchCharIndex, searchCharIndex + 1);
        switch (searchChar[0])
        {
        case ']':
            bracketCount--;
            break;

        case '[':
            bracketCount++;
            break;

        case ')':
            parenCount--;
            break;

        case '(':
            parenCount++;
            break;

        case '{':
            braceCount--;
            break;

        case '}':
            braceCount++;
            break;
        }

        if (ParenToMatch == '[' && bracketCount == 0 ||
            ParenToMatch == '(' && parenCount   == 0 ||
            ParenToMatch == '{' && braceCount   == 0)
        {
            return searchCharIndex;
        }
    }

    return -1;
}

int
TRichEditWithPopup::SearchBackwardForMatchingParen(
    int  CaretPosition,
    char ParenToMatch
    )
{
    int bracketCount = 0;
    int parenCount   = 0;
    int braceCount   = 0;
    char searchChar[2];

    // search backward for the matching bracket/paren
    for (int searchCharIndex = CaretPosition; 0 <= searchCharIndex; searchCharIndex--)
    {
        GetSubText(searchChar, searchCharIndex, searchCharIndex + 1);
        switch (searchChar[0])
        {
        case ']':
            bracketCount--;
            break;

        case '[':
            bracketCount++;
            break;

        case ')':
            parenCount--;
            break;

        case '(':
            parenCount++;
            break;

        case '{':
            braceCount--;
            break;

        case '}':
            braceCount++;
            break;
        }

        if (ParenToMatch == ']' && bracketCount == 0 ||
            ParenToMatch == ')' && parenCount   == 0 ||
            ParenToMatch == '}' && braceCount   == 0)
        {
            return searchCharIndex;
        }
    }

    return -1;
}

// If the cursor is over a paren, bracket, or brace,
// this will make the cursor jump to the matching paren,
// bracket, or brace.
void TRichEditWithPopup::CmFindMatchingParen()
{
    int caretPosition = GetCaretPosition();
    if (caretPosition == -1)
    {
        // We cannot determine where the caret it,
        // so it's impossible to determine the paren that
        // matches the character at the caret.
        return;
    }

    int matchingParenIndex = -1;

    char charUnderCursor[2];
    GetSubText(charUnderCursor, caretPosition, caretPosition + 1);
    switch (charUnderCursor[0])
    {
    case ']':
    case ')':
    case '}':
        matchingParenIndex = SearchBackwardForMatchingParen(
            caretPosition,
            charUnderCursor[0]);
        break;

    case '[':
    case '(':
    case '{':
        matchingParenIndex = SearchForwardForMatchingParen(
            caretPosition,
            charUnderCursor[0]);
        break;
    }

    if (matchingParenIndex != -1)
    {
        UpdateCaretPosition(matchingParenIndex);
    }
}

// If the cursor is over a paren, bracket, or brace,
// this will set the selection to the include everything
// between the two parens.
void TRichEditWithPopup::CmSelectMatchingParen()
{
    int caretPosition = GetCaretPosition();
    if (caretPosition == -1)
    {
        // We cannot determine where the caret it,
        // so it's impossible to determine the paren that
        // matches the character at the caret.
        return;
    }

    int matchingParenIndex = -1;

    char charUnderCursor[2];
    GetSubText(charUnderCursor, caretPosition, caretPosition + 1);
    switch (charUnderCursor[0])
    {
    case ']':
    case ')':
    case '}':
        matchingParenIndex = SearchBackwardForMatchingParen(
            caretPosition,
            charUnderCursor[0]);
        if (matchingParenIndex != -1)
        {
            SetSelection(caretPosition + 1, matchingParenIndex);
        }
        break;

    case '[':
    case '(':
    case '{':
        matchingParenIndex = SearchForwardForMatchingParen(
            caretPosition,
            charUnderCursor[0]);
        if (matchingParenIndex != -1)
        {
            SetSelection(caretPosition, matchingParenIndex + 1);
        }
        break;
    }
}

DEFINE_RESPONSE_TABLE1(TRichEditWithPopup, TRichEdit)
    EV_WM_RBUTTONUP,
    EV_COMMAND(CM_EDITPASTE,            CmPasteAsText),
    EV_COMMAND(CM_EDITSELECTALL,        CmSelectAll),
    EV_COMMAND(CM_HELPEDIT_TOPIC,       CmHelpEditTopic),
    EV_COMMAND(CM_FINDMATCHINGPAREN,    CmFindMatchingParen),
    EV_COMMAND(CM_SELECTMATCHINGPAREN,  CmSelectMatchingParen),
    EV_COMMAND_ENABLE(CM_EDITSELECTALL, CmSelectAllEnable),
END_RESPONSE_TABLE;

