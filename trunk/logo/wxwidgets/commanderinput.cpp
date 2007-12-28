#include "commanderinput.h"


#include "commander.h"
#include "help.h"

CCommanderInput::CCommanderInput(
    CCommander *    Parent, 
    wxWindowID      Id
    ) : wxTextCtrl(Parent, Id)
{
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

    // we want alphanumeric keys
    if ('0' <= KeyCode && KeyCode <= 'Z')
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

#if 0
    // we want the "OEM" keys, which are usually punctiation and international characters
    // OEM keys are not defined in Borland 5.0.2's header files
    const WPARAM VK_OEM_1   = 186;
    const WPARAM VK_OEM_102 = 226;
    if (VK_OEM_1 <= KeyEventWParam && KeyEventWParam <= VK_OEM_102)
    {
        return true;
    }
#endif
    // we want the "hardware-specific keys".
    // I hope these coorepond to the windows OEM keys which are usually
    // punctiation and international characters.
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

void CCommanderInput::OnKeyDown(wxKeyEvent& Event)
{
    int keyCode = Event.GetKeyCode();

    switch (keyCode)
    {
    case WXK_F1:
        OpenHelp(GetStringSelection());
        break;

    case WXK_UP:
        static_cast<CCommander*>(GetParent())->GiveControlToHistoryBox();
        break;

    default:
        // default processing
        Event.Skip();
        break;
    }
}

BEGIN_EVENT_TABLE(CCommanderInput, wxTextCtrl)
    EVT_KEY_DOWN(CCommanderInput::OnKeyDown)
END_EVENT_TABLE()
