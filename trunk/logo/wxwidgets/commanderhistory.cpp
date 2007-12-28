#include "commanderhistory.h"

#include "help.h"
#include "commander.h"
#include "commanderinput.h"

CCommanderHistory::CCommanderHistory(
    CCommander *    Parent, 
    wxWindowID      Id
    ) : wxRichTextCtrl(Parent, Id)
{
}

void CCommanderHistory::OnKeyDown(wxKeyEvent& Event)
{
    int keyCode = Event.GetKeyCode();

    if (keyCode == WXK_F1)
    {
        OpenHelp(GetStringSelection());
    }
    else if (CCommanderInput::WantsKeyEvent(keyCode))
    {
        CCommander * commander = static_cast<CCommander*>(GetParent());
        commander->PostKeyDownToInputControl(Event);
    }
    else
    {
        // default processing
        Event.Skip();
    }
}

BEGIN_EVENT_TABLE(CCommanderHistory, wxRichTextCtrl)
    EVT_KEY_DOWN(CCommanderHistory::OnKeyDown)
END_EVENT_TABLE()
