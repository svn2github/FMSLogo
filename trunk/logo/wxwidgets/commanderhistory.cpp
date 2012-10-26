#include "commanderhistory.h"

#include <wx/settings.h>
#include <wx/button.h>
#include <wx/menu.h>

#include "commander.h"
#include "commanderinput.h"
#include "helputils.h" // for ContextHelp()
#include "guiutils.h"  // for FillMenu()
#include "logocore.h"  // for ARRAYSIZE

#include "localizedstrings.h"

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
    wxRichTextLine * line = GetVisibleLineForCaretPosition(GetCaretPosition());
    if (line != NULL)
    {
        wxRichTextParagraph* paragraph = GetBuffer().GetParagraphForLine(line);
        if (paragraph != NULL)
        {
            wxRichTextRange range(paragraph->GetRange());

            const wxString & text = GetRange(range.GetStart(), range.GetEnd());

            GetCommander()->GetInput()->SetValue(text);
        }
    }
}

void CCommanderHistory::OnContextHelp(wxCommandEvent& Event)
{
    ContextHelp(GetStringSelection());
}

void CCommanderHistory::OnKeyDown(wxKeyEvent& Event)
{
    int keyCode = Event.GetKeyCode();

    int  flags      = (Event.ShiftDown()) ? wxRICHTEXT_SHIFT_DOWN : 0;
    bool movedCaret = false;

    if (keyCode == WXK_RETURN)
    {
        // Enter does the same as pressing the Execute button.
        GetCommander()->GiveControlToInputBox();
        GetCommander()->Execute();
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
        ContextHelp(GetStringSelection());
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
        if (Event.ShiftDown())
        {
            // Shift+Tab means navigate backward.
            Navigate(wxNavigationKeyEvent::IsBackward);
        }
        else
        {
            // Tab means navigate forward.
            Navigate(wxNavigationKeyEvent::IsForward);
        }
    }
    else if (CCommanderInput::WantsKeyEvent(keyCode))
    {
        GetCommander()->ProcessKeyDownEventAtInputControl(Event);
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

void CCommanderHistory::ScrollToBottom()
{
    long lastPosition = GetLastPosition();
    ShowPosition(lastPosition);
}

void CCommanderHistory::OnLeftMouseButtonDown(wxMouseEvent& Event)
{
    // Have the base class process the mouse click so that
    // the cursor will be moved to the location of the click.
    OnLeftClick(Event);
    OnLeftUp(Event);

    // On a single click, the contents of the current line
    // gets copied to the commander's input box.
    CopyCurrentLineToCommanderInput();

    // Continue with the default processing for the event.
    Event.Skip();
}

void CCommanderHistory::OnLeftMouseButtonDoubleClick(wxMouseEvent& Event)
{
    // On a double-click, the contents of the current line are executed.
    CopyCurrentLineToCommanderInput();
    GetCommander()->GiveControlToInputBox();
    GetCommander()->Execute();

    // Don't call Event.Skip() because GetCommander()->Execute can run
    // TEXTSCREEN, which would delete this control.  Therefore we cannot
    // safely do any further processing on this control.
}

void CCommanderHistory::OnContextMenu(wxContextMenuEvent& Event)
{
    // Show a popup menu that is appropriate for a read-only test control.
    static const MENUITEM contextMenuItems[] = {
        {LOCALIZED_POPUP_COPY,      wxID_COPY},
        {LOCALIZED_POPUP_SELECTALL, wxID_SELECTALL},
        {0},
        {LOCALIZED_POPUP_HELP,      wxID_HELP_INDEX},
    };

    wxMenu menu;
    FillMenu(&menu, contextMenuItems, ARRAYSIZE(contextMenuItems));

    PopupMenu(&menu);
}

BEGIN_EVENT_TABLE(CCommanderHistory, wxRichTextCtrl)
    EVT_MENU(wxID_HELP_INDEX, CCommanderHistory::OnContextHelp)
    EVT_KEY_DOWN(CCommanderHistory::OnKeyDown)
    EVT_LEFT_DOWN(CCommanderHistory::OnLeftMouseButtonDown)
    EVT_LEFT_DCLICK(CCommanderHistory::OnLeftMouseButtonDoubleClick)
    EVT_CONTEXT_MENU(CCommanderHistory::OnContextMenu)
END_EVENT_TABLE()
