#ifdef __WXMSW__
#  include <windows.h>  // for keybd_event
#endif

#include <wx/clipbrd.h>

#include "commanderinput.h"

#include "commander.h"
#include "logocore.h"  // for ARRAYSIZE
#include "helputils.h" // for ContextHelp

enum
{
    KEY_CODE_CLOSE_BRACKET = 0xDD,
};

enum 
{
    ID_FINDMATCHINGPAREN = wxID_HIGHEST,
    ID_SELECTMATCHINGPAREN,
};

CCommanderInput::CCommanderInput(
    CCommander *    Parent, 
    wxWindowID      Id
    ) :
    CLogoCodeCtrl(Parent, Id)
{
    // Configure the keyboard shortcuts
    wxAcceleratorEntry acceleratorEntries[8];

    acceleratorEntries[0].Set(wxACCEL_CTRL, 'A', wxID_SELECTALL);
    acceleratorEntries[1].Set(wxACCEL_CTRL, 'Z', wxID_UNDO);
    acceleratorEntries[2].Set(wxACCEL_CTRL, 'Y', wxID_REDO);
    acceleratorEntries[3].Set(wxACCEL_CTRL, 'X', wxID_CUT);
    acceleratorEntries[4].Set(wxACCEL_CTRL, 'C', wxID_COPY);
    acceleratorEntries[5].Set(wxACCEL_CTRL, 'V', wxID_PASTE);

    // Ctrl+] moves to matching paren
    acceleratorEntries[6].Set(
        wxACCEL_CTRL,
        KEY_CODE_CLOSE_BRACKET,
        ID_FINDMATCHINGPAREN);

    // Ctrl+Shift+] selects to matching paren
    acceleratorEntries[7].Set(
        wxACCEL_CTRL | wxACCEL_SHIFT,
        KEY_CODE_CLOSE_BRACKET,
        ID_SELECTMATCHINGPAREN);


    wxAcceleratorTable acceleratorTable(
        ARRAYSIZE(acceleratorEntries),
        acceleratorEntries);
    SetAcceleratorTable(acceleratorTable);

    SetUseHorizontalScrollBar(false);

    // For compatibility with the OWL version of FMSLogo, the selection
    // should be shown as white on dark blue.
    const wxColor white(0xFF, 0xFF, 0xFF);
    const wxColor darkblue(0, 0, 0x80);
    SetSelForeground(true, white);
    SetSelBackground(true, darkblue);
}

bool
CCommanderInput::WantsKeyEvent(
    int KeyCode
    )
{
    // we want the space bar
    if (KeyCode == WXK_SPACE)
    {
        return true;
    }

    // we want the backspace and delete keys
    if (KeyCode == WXK_BACK || KeyCode == WXK_DELETE)
    {
        return true;
    }

    // we want all printing characters
    if (WXK_SPACE <= KeyCode && KeyCode < WXK_START)
    {
        return true;
    }

    // we want the printing characters from the numpad
    if ((WXK_NUMPAD0 <= KeyCode && KeyCode <= WXK_NUMPAD9) ||
        (WXK_NUMPAD_SPACE <= KeyCode && KeyCode <= WXK_NUMPAD_ENTER) ||
        (WXK_NUMPAD_EQUAL <= KeyCode && KeyCode <= WXK_NUMPAD_DIVIDE))
    {
        return true;
    }

    // we want the "hardware-specific keys".
    // I hope these correpond to the windows OEM keys which are usually
    // punctuation and international characters.
    if (WXK_SPECIAL1 <= KeyCode && KeyCode <= WXK_SPECIAL20)
    {
        return true;
    }

    // there are a few navigational keys that we also want.
    if (KeyCode == WXK_NUMPAD_HOME  || 
        KeyCode == WXK_NUMPAD_END   || 
        KeyCode == WXK_NUMPAD_RIGHT || 
        KeyCode == WXK_HOME         || 
        KeyCode == WXK_END          || 
        KeyCode == WXK_RIGHT)
    {
        return true;
    }

    // reject everything else
    return false;
}

void CCommanderInput::SimulateKeyPress(wxKeyEvent & KeyEvent)
{
    if (KeyEvent.ShiftDown())
    {
        // An early adopter of the wxWidgets FMSLogo reported that
        // the key events with Shift are not emulated properly by
        // EmulateKeyEvent() on his Vista Business machine.
        // 
        // To account for this, we must explicitly handle all such
        // key events.
        int keyCode = KeyEvent.GetKeyCode();
        switch (keyCode)
        {
        case WXK_HOME:
        case WXK_NUMPAD_HOME:
            if (KeyEvent.ControlDown())
            {
                // Ctrl+Shift+Home selects to the top of the input.
                DocumentStartExtend();
            }
            else
            {
                // Shift+Home selects to the beginning of the input.
                HomeExtend();
            }
            break;

        case WXK_END:
        case WXK_NUMPAD_END:
            if (KeyEvent.ControlDown())
            {
                // Ctrl+Shift+End selects to the bottom of the input.
                DocumentEndExtend();
            }
            else
            {
                // Shift+End selects to the end of the line.
                LineEndExtend();
            }
            break;

        case WXK_LEFT:
        case WXK_NUMPAD_LEFT:
            if (KeyEvent.ControlDown())
            {
                // Ctrl+Shift+Left extends the selection a word to the left.
                WordLeftExtend();
            }
            else
            {
                // Shift+Left extends the selection a character to the left.
                CharLeftExtend();
            }
            break;

        case WXK_RIGHT:
        case WXK_NUMPAD_RIGHT:
            if (KeyEvent.ControlDown())
            {
                // Ctrl+Shift+Right extends the selection a word to the right.
                WordRightExtend();
            }
            else
            {
                // Shift+Right extends the selection a character to the right.
                CharRightExtend();
            }
            break;
        }
    }
    else
    {
#ifdef __WXMSW__
        // Copied from wxTextCtrl::EmulateKeyEvent(KeyEvent)
        BYTE code = static_cast<BYTE>(KeyEvent.GetRawKeyCode());
        ::keybd_event(code, 0, 0 /* key press */, 0);
        ::keybd_event(code, 0, KEYEVENTF_KEYUP, 0);
#endif
    }
}

void CCommanderInput::SetText(const wxString & NewText)
{
    CLogoCodeCtrl::SetText(NewText);
    SetSelection(0, 0);
    EmptyUndoBuffer();
}

void CCommanderInput::OnKeyDown(wxKeyEvent& Event)
{
    int keyCode = Event.GetKeyCode();

    switch (keyCode)
    {
    case WXK_F1:
        ContextHelp(GetSelectedText());
        break;

    case WXK_UP:
    case WXK_NUMPAD_UP:
        if (GetCurrentLine() == 0)
        {
            static_cast<CCommander*>(GetParent())->GiveControlToHistoryBox();
        }
        else
        {
            LineUp();
        }
        break;

    case WXK_TAB:
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
        break;

    case WXK_RETURN:
    case WXK_NUMPAD_ENTER:
        static_cast<CCommander*>(GetParent())->Execute();
        break;

    default:
        // default processing
        Event.Skip();
        break;
    }
}

void CCommanderInput::OnChar(wxKeyEvent& Event)
{
    int keyCode = Event.GetKeyCode();
    switch (keyCode)
    {
    case WXK_RETURN:
    case WXK_NUMPAD_ENTER:
        // Do nothing -- we already handled this on OnKeyDown().
        // According to the wxWidgets documentation, this isn't supposed to
        // generate a call to OnChar() because we didn't call Event.Skip(),
        // but it does.  To prevent a carriage return from being written to
        // the input field, we need to ignore this event.
        break;

    default:
        // default processing
        Event.Skip();
        break;
    }
}

void CCommanderInput::OnFindMatchingParen(wxCommandEvent& WXUNUSED(Event))
{
    FindMatchingParen();
}

void CCommanderInput::OnSelectMatchingParen(wxCommandEvent& WXUNUSED(Event))
{
    SelectMatchingParen();
}

void CCommanderInput::OnKillFocus(wxFocusEvent & Event)
{
    // For compatibility with the OWL versin of FMSLogo, when
    // the control loses focus, the selection should become invisible.
    HideSelection(true);
    Event.Skip();
}

void CCommanderInput::OnSetFocus(wxFocusEvent & Event)
{
    // When the control gets focus, the selection should become visible.
    HideSelection(false);
    Event.Skip();
}

void CCommanderInput::OnPaste(wxCommandEvent& Event)
{
    // This overrides the default paste handler to strip out
    // and trailing newlines, which are present when copying
    // and pasting code snippets from the manual or the Web.
    // Because the commander input is only one line tall, if we
    // included the trailing newline, then the user would see a
    // blank line after the pasting and it wouldn't be clear that
    // the contents of the clipboard was pasted.

    // A more comprehensive solution would be to increase the size
    // of the commander input to show everything that was pasted,
    // or at least up to four lines.
    
    // In wxWidgets 3.1.0, this can use EVT_STC_CLIPBOARD_PASTE

    bool handledEvent = false;
    if (wxTheClipboard->Open())
    {
        // Only special processing for text.
        if (wxTheClipboard->IsSupported(wxDF_TEXT))
        {
            // Get the text that is being pasted.
            wxTextDataObject data;
            wxTheClipboard->GetData(data);
            wxString pastedText = data.GetText();

            // Determine where trailing newlines (if any) start.
            size_t pastedTextLength = pastedText.length();
            int lastIndex;
            for (lastIndex = pastedTextLength - 1;
                 0 <= lastIndex;
                 lastIndex--)
            {
                if (pastedText[lastIndex] == '\\')
                {
                    // We shouldn't remove a quoted newline,
                    // so put it back.
                    lastIndex++;
                    break;
                }
                else if (pastedText[lastIndex] != '\n' &&
                         pastedText[lastIndex] != '\r')
                {
                    // We have found a trailing character
                    // that isn't a newline, so we're done.
                    break;
                }
            }

            // Strip the trailing newlines
            pastedText = pastedText.Truncate(lastIndex + 1);

            // Perform the paste.
            ReplaceSelection(pastedText);
            handledEvent = true;
        }

        wxTheClipboard->Close();
    }
   
    if (!handledEvent)
    {
        // Standard processing.
        Event.Skip();
    }
}

BEGIN_EVENT_TABLE(CCommanderInput, CLogoCodeCtrl)
    EVT_KEY_DOWN(CCommanderInput::OnKeyDown)
    EVT_CHAR(CCommanderInput::OnChar)
    EVT_SET_FOCUS(CCommanderInput::OnSetFocus)
    EVT_KILL_FOCUS(CCommanderInput::OnKillFocus)
    EVT_MENU(ID_FINDMATCHINGPAREN,   CCommanderInput::OnFindMatchingParen)
    EVT_MENU(ID_SELECTMATCHINGPAREN, CCommanderInput::OnSelectMatchingParen)
    EVT_MENU(wxID_PASTE,             CCommanderInput::OnPaste)
END_EVENT_TABLE()
