#include "commanderhistory.h"

#include "help.h"
#include "commander.h"
#include "commanderinput.h"

CCommanderHistory::CCommanderHistory(
    CCommander *    Parent, 
    wxWindowID      Id
    ) : wxRichTextCtrl(
        Parent, 
        Id, 
        wxEmptyString,
        wxDefaultPosition,
        wxDefaultSize,
        wxRE_READONLY | wxRE_READONLY)
{
}

CCommander * CCommanderHistory::GetCommander() const
{
    return static_cast<CCommander*>(GetParent());
}

bool CCommanderHistory::IsCursorAtBottom() const
{
    long caretPosition = GetCaretPosition();
    long lastPosition  = GetLastPosition();
    return lastPosition == caretPosition;
}

void CCommanderHistory::CopyCurrentLineToCommanderInput() const
{
#if 0
    char buf[1024] = {0};

    int currentline = GetLineFromPos(-1);

    // Look for the first line backwards from the current line
    // that doesn't ends in an EOL sequence.
    // This tells us where this line really begins (ignoring word-wrapping)
    for (long prevline = currentline - 1;
         0 <= prevline;
         prevline--)
    {
        wxString line = GetLineText();

        // advance to the last char in buf
        char * ptr = line + strlen(buf) - 1;
        if (*ptr == '\n' || *ptr == '\r')
        {
            // we reached a line that ends in an EOL
            break;
        }

        // This line does not end in an EOL sequence.
        // Therefore, it is part of the current line.
        currentline = prevline;
    }
   
    // read as many word-wrapped lines as it takes to get to the end of a real line
    char * ptr = buf;
    char * end = buf + sizeof(buf) - 1;
    while (ptr < end)
    {
        bool isok = GetLine(ptr, end - ptr, currentline);
        if (!isok)
        {
            break;
        }

        if (*ptr == '\0')
        {
            // The line was blank.  
            // This happens when the commander is squished such that
            // it can't hold a single character.
            // We must detect this condition and break out to avoid an inifnite loop.
            // See bug #1652924 for details.
            break;
        }

        // advance to the last char in buf
        ptr = ptr + strlen(ptr) - 1;

        if (*ptr == '\n' || *ptr == '\r')
        {
            // we reached the end of the line
            break;
        }

        // This line doesn't end in an EOL sequence.
        // This must be a word-wrapped line.

        if (end <= ptr + 2)
        {
            // buf can't hold any more characters
            break;
        }

        if (*ptr != ' ')
        {
            // append a space to the end of buf
            ptr++;
            ptr[0] = ' ';
            ptr[1] = '\0';
        }

        // advance to the NUL
        ptr++;
        currentline++;
    }

    // remove trailing whitespace
    for (char * stringend = buf + strlen(buf) - 1;
         buf <= stringend && isspace(*stringend);
         stringend--)
    {
        *stringend = '\0';
    }
#else
    wxString text = "fake text from history";
#endif

    GetCommander()->GetInput()->SetValue(text);
}

// KeyboardNavigate() is a virtual function that is called from the
// wxEVT_CHAR event handler of wxRichTextCtrl.  Because the navigation 
// controls are not sent to wxEVT_KEY_DOWN, we must intercept them here.
bool CCommanderHistory::KeyboardNavigate(int keyCode, int flags)
{
    fprintf(stderr, "CCommanderHistory::KeyboardNavigate()\n");

    bool rval = wxRichTextCtrl::KeyboardNavigate(keyCode, flags);

    if (keyCode == WXK_UP   ||
        keyCode == WXK_DOWN ||
        keyCode == WXK_LEFT)
    {
        // If the caret moves down off bottom, then give focus to edit box.
        // NOTE: This logic must come before DefaultProcessing() when the cursor 
        // is already at the bottom in order to prevent an extra beep.
        if (keyCode == WXK_DOWN && !HasSelection())
        {
            if (IsCursorAtBottom())
            {
                GetCommander()->GetInput()->SetFocus();
                return rval;
            }
        }

        // up&down keys move up and down
        if (keyCode == WXK_DOWN)
        {
            MoveDown(1);
        }
        else if (keyCode == WXK_UP)
        {
            MoveUp(1);
        }

        CopyCurrentLineToCommanderInput();

#ifndef SELECTBOTTOMLINE
        // If the caret moves down off bottom, then give focus to edit box.
        if (keyCode == WXK_DOWN && !HasSelection())
        {
            if (IsCursorAtBottom())
            {
                GetCommander()->GetInput()->SetFocus();
            }
        }
#endif

    }

    return rval;
}

void CCommanderHistory::OnKeyDown(wxKeyEvent& Event)
{
    int keyCode = Event.GetKeyCode();
    fprintf(stderr, "CCommanderHistory::OnKeyDown()\n");

    if (keyCode == WXK_F1)
    {
        OpenHelp(GetStringSelection());
    }
    else if (CCommanderInput::WantsKeyEvent(keyCode))
    {
        GetCommander()->PostKeyDownToInputControl(Event);
    }
    else
    {
        // default processing
        Event.Skip();
    }
}

void CCommanderHistory::OnChar(wxKeyEvent& Event)
{
    fprintf(stderr, "CCommanderHistory::OnChar()\n");
    Event.Skip();
}


BEGIN_EVENT_TABLE(CCommanderHistory, wxRichTextCtrl)
    EVT_KEY_DOWN(CCommanderHistory::OnKeyDown)
    EVT_CHAR(CCommanderHistory::OnChar)
END_EVENT_TABLE()
