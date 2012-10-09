#include "commanderbutton.h"
#include "commander.h"
#include "commanderinput.h"

CCommanderButton::CCommanderButton(
    CCommander *    Parent, 
    wxWindowID      Id, 
    const wxString& Label
    ) : wxButton(Parent, Id, Label)
{
}

void CCommanderButton::OnKeyDown(wxKeyEvent& Event)
{
    const int keyCode = Event.GetKeyCode();

    if (keyCode == WXK_SPACE)
    {
        // Spaces are transformed into button presses,
        // so we want to handle this event.
        Event.Skip();
    }
    else if (CCommanderInput::WantsKeyEvent(keyCode))
    {
        // We don't handle this key stroke.
        // Give focus to the edit box and send the press to it.
        CCommander * commander = static_cast<CCommander*>(GetParent());
        commander->ProcessKeyDownEventAtInputControl(Event);
    }
    else
    {
        // Continue with default event processing.
        Event.Skip();
    }
}


BEGIN_EVENT_TABLE(CCommanderButton, wxButton)
    EVT_KEY_DOWN(CCommanderButton::OnKeyDown)
END_EVENT_TABLE()
