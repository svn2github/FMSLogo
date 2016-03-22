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
    if (CCommanderInput::WantsKeyEvent(Event.GetKeyCode()))
    {
        CCommander * commander = static_cast<CCommander*>(GetParent());

        // We don't handle this key.
        // Give focus to the edit box and send the press to it.
        commander->ProcessKeyDownEventAtInputControl(Event);
    }

    // don't process the event (wxButtons don't usually get them)
    Event.Skip();
}

BEGIN_EVENT_TABLE(CCommanderButton, wxButton)
    EVT_KEY_DOWN(CCommanderButton::OnKeyDown)
END_EVENT_TABLE()
