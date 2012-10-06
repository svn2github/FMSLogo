#include "commandertogglebutton.h"
#include "commander.h"
#include "commanderinput.h"

CCommanderToggleButton::CCommanderToggleButton(
    CCommander *    Parent, 
    wxWindowID      Id,
    const char *    DownLabel,
    const char *    UpLabel
    ) : wxToggleButton(Parent, Id, ""),
        m_DownLabel(DownLabel),
        m_UpLabel(UpLabel)
{
}

void CCommanderToggleButton::OnKeyDown(wxKeyEvent& Event)
{
    if (CCommanderInput::WantsKeyEvent(Event.GetKeyCode()))
    {
        CCommander * commander = static_cast<CCommander*>(GetParent());

        // We don't handle this key.
        // Give focus to the edit box and send the press to it.
        commander->ProcessKeyDownEventAtInputControl(Event);
    }

    Event.Skip();
}

void CCommanderToggleButton::SetPressedState(bool IsPressed)
{
    SetLabel(IsPressed ? m_DownLabel : m_UpLabel);
    SetValue(IsPressed);
}

BEGIN_EVENT_TABLE(CCommanderToggleButton, wxToggleButton)
    EVT_KEY_DOWN(CCommanderToggleButton::OnKeyDown)
END_EVENT_TABLE()
