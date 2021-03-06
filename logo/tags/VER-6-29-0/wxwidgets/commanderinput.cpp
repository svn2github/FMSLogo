#include "commanderinput.h"

#include "commander.h"
#include "logocore.h"  // for ARRAYSIZE
#include "helputils.h" // for ContextHelp

CCommanderInput::CCommanderInput(
    CCommander *    Parent, 
    wxWindowID      Id
    ) : wxTextCtrl(Parent, Id)
{
    // Configure the keyboard shortcuts
    wxAcceleratorEntry acceleratorEntries[1];

    // Ctrl+A is Select All
    acceleratorEntries[0].Set(wxACCEL_CTRL, 'A', wxID_SELECTALL);

    wxAcceleratorTable acceleratorTable(
        ARRAYSIZE(acceleratorEntries),
        acceleratorEntries);
    SetAcceleratorTable(acceleratorTable);
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

void CCommanderInput::Duplicate(CCommanderInput & Source)
{
    SetValue(Source.GetValue());
}

void CCommanderInput::OnKeyDown(wxKeyEvent& Event)
{
    int keyCode = Event.GetKeyCode();

    switch (keyCode)
    {
    case WXK_F1:
        ContextHelp(GetStringSelection());
        break;

    case WXK_UP:
    case WXK_NUMPAD_UP:
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
