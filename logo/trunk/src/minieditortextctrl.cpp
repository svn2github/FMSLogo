#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include "minieditortextctrl.h"

   #include <wx/event.h>

   #include "stringadapter.h"
   #include "helputils.h" // for ContextHelp()
#endif

// ----------------------------------------------------------------------------
// CMiniEditorTextCtrl
// ----------------------------------------------------------------------------

CMiniEditorTextCtrl::CMiniEditorTextCtrl(
    wxWindow*      Parent,
    wxWindowID     Id
    ) : CLogoCodeCtrl(Parent, Id)
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
    case WXK_F1:
        // F1 displays the help
        ContextHelp(GetStringSelection());
        break;

    case WXK_RETURN:
        // Enter writes a newline, instead of pressing the default button,
        // which would close the mini-editor.
        WriteText(WXSTRING("\n"));
        break;

    case WXK_TAB:
        // Use TAB and SHIFT+TAB as a navigational key events
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

    default:
        Event.Skip();
        break;
    }
}


BEGIN_EVENT_TABLE(CMiniEditorTextCtrl, CLogoCodeCtrl)
    EVT_KEY_DOWN(CMiniEditorTextCtrl::OnKeyDown)
END_EVENT_TABLE()
