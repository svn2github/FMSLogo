#include "minieditortextctrl.h"

#include <wx/event.h>

// ----------------------------------------------------------------------------
// CMiniEditorTextCtrl
// ----------------------------------------------------------------------------

CMiniEditorTextCtrl::CMiniEditorTextCtrl(
    wxWindow*      Parent,
    wxWindowID     Id,
    const wxSize & Size
    ) : wxRichTextCtrl(
        Parent,
        Id,
        wxEmptyString,
        wxDefaultPosition,
        Size,
        wxRE_MULTILINE | wxWANTS_CHARS)
{
}

CMiniEditorTextCtrl::~CMiniEditorTextCtrl()
{
}

void CMiniEditorTextCtrl::OnKeyDown(wxKeyEvent& Event)
{
    int keyCode = Event.GetKeyCode();

    switch (keyCode)
    {
    case WXK_RETURN:
        WriteText("\n");
        break;

    case WXK_TAB:
        // Use TAB and SHIFT+TAB as a navigational key event
        {
            wxNavigationKeyEvent eventNav;
            eventNav.SetDirection(!Event.ShiftDown());
            eventNav.SetWindowChange(Event.ControlDown());
            eventNav.SetEventObject(this);

            GetParent()->GetEventHandler()->ProcessEvent(eventNav);
        }
        break;

    default:
        Event.Skip();
    }
}


BEGIN_EVENT_TABLE(CMiniEditorTextCtrl, wxRichTextCtrl)
    EVT_KEY_DOWN(CMiniEditorTextCtrl::OnKeyDown)
END_EVENT_TABLE()
