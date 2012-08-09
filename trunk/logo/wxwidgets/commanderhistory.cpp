#include "commanderhistory.h"

#include <wx/settings.h>
#include <wx/button.h>

#include "commander.h"
#include "commanderinput.h"
#include "graphwin.h" // for do_help

CCommanderHistory::CCommanderHistory(
    CCommander *    Parent, 
    wxWindowID      Id
    ) : wxRichTextCtrl(
        Parent, 
        Id, 
        wxEmptyString,
        wxDefaultPosition,
        wxDefaultSize,
        wxRE_READONLY | wxWANTS_CHARS)
{
    // The background color should be light gray to indicate that this
    // is a read-only control.
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DLIGHT));

    // Nothing that we write to the control should be undoable by
    // the user.
    BeginSuppressUndo();
}

CCommander * CCommanderHistory::GetCommander() const
{
    return static_cast<CCommander*>(GetParent());
}

bool CCommanderHistory::IsCursorAtBottom() const
{
    long caretPosition = GetCaretPosition();
    long lastPosition  = GetLastPosition();

    return lastPosition <= caretPosition + 1;
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
    wxRichTextLine * line = GetVisibleLineForCaretPosition(GetCaretPosition());
    if (line)
    {
        wxRichTextParagraph* para = GetBuffer().GetParagraphForLine(line);
        if (para)
        {
            wxRichTextRange range(para->GetRange());

            wxString text = GetRange(range.GetStart(), range.GetEnd());

            GetCommander()->GetInput()->SetValue(text);
        }
    }
#endif

}

void CCommanderHistory::OnKeyDown(wxKeyEvent& Event)
{
    int keyCode = Event.GetKeyCode();

    int  flags      = (Event.ShiftDown()) ? wxRICHTEXT_SHIFT_DOWN : 0;
    bool movedCaret = false;

    if (keyCode == WXK_RETURN)
    {
        Event.Skip();
    }
    else if (Event.ControlDown() && keyCode == WXK_HOME)
    {
        // CTRL+HOME scrolls to the top
        MoveHome(flags);
        movedCaret = true;
    }
    else if (Event.ControlDown() && keyCode == WXK_END)
    {
        // CTRL+END scrolls to the bottom
        MoveEnd(flags);
        movedCaret = true;
    }
    else if (Event.GetModifiers() == wxMOD_CONTROL && keyCode == 'C')
    {
        // CTRL+C should copy
        Copy();
    }
    else if (Event.GetModifiers() == wxMOD_NONE && keyCode == WXK_F1)
    {
        // F1 displays the help
        do_help(GetStringSelection().c_str());
    }
    else if (keyCode == WXK_PAGEUP || keyCode == WXK_NUMPAD_PAGEUP)
    {
        // Page Up moves one screen up
        PageUp(1, flags);
        movedCaret = true;
    }
    else if (keyCode == WXK_PAGEDOWN || keyCode == WXK_NUMPAD_PAGEDOWN)
    {
        // Page Down moves one screen down
        PageDown(1, flags);
        movedCaret = true;
    }
    else if (keyCode == WXK_DOWN || keyCode == WXK_NUMPAD_DOWN)
    {
        // If the caret is already at the bottom, then give focus to edit box.
        if (!HasSelection() && IsCursorAtBottom())
        {
            GetCommander()->GetInput()->SetFocus();
        }
        else if (IsCursorAtBottom())
        {
            // The cursor is already at the bottom
            // so we don't have to move it.
            if (!Event.ControlDown())
            {
                // clear the selection to be consistent with MSWLogo
                SelectNone();
            }
        }
        else
        {
            MoveDown(1, flags);
            movedCaret = true;
        }
    }
    else if (keyCode == WXK_UP || keyCode == WXK_NUMPAD_UP)
    {
        MoveUp(1, flags);
        movedCaret = true;
    }
    else if (keyCode == WXK_LEFT || keyCode == WXK_NUMPAD_LEFT)
    {
        if (Event.ControlDown())
        {
            WordLeft(1, flags);
        }
        else
        {
            MoveLeft(1, flags);
        }
        movedCaret = true;
    }
    else if (keyCode == WXK_TAB)
    {
        // TODO: the documentation for wxWANTS_CHARS says that I should
        // create and send a wxNavigationKeyEvent, instead of doing it
        // myself.
        if (Event.ShiftDown())
        {
            // the previous control is the execute button
            GetCommander()->GetEdallButton()->SetFocus();
        }
        else
        {
            // the next control is the commander input
            GetCommander()->GetInput()->SetFocus();
        }
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

    if (movedCaret)
    {
        ScrollIntoView(GetCaretPosition(), keyCode);
        CopyCurrentLineToCommanderInput();
    }
}

void CCommanderHistory::Duplicate(CCommanderHistory & Source)
{
    // Copy the text over
    SetValue(Source.GetValue() + "\n");

    // Put the caret in the same location
    long caretPosition = Source.GetCaretPosition();
    SetInsertionPoint(caretPosition);
    ShowPosition(caretPosition);
}


BEGIN_EVENT_TABLE(CCommanderHistory, wxRichTextCtrl)
    EVT_KEY_DOWN(CCommanderHistory::OnKeyDown)
END_EVENT_TABLE()
