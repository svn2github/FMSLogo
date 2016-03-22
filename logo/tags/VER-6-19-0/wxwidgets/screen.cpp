#include <screen.h>

#include <wx/event.h>

#include <fmslogo.h>
#include <commander.h>
#include <commanderinput.h>
#include <mainframe.h>

// ----------------------------------------------------------------------------
// CScreen
// ----------------------------------------------------------------------------

CScreen::CScreen(
    wxWindow* parent
    ) : 
    wxScrolledWindow(
        parent, 
        wxID_ANY, 
        wxDefaultPosition, 
        wxDefaultSize,
        wxHSCROLL | wxVSCROLL | wxNO_FULL_REPAINT_ON_RESIZE)
{
}

void CScreen::OnDraw(wxDC& dcOrig)
{
}

void CScreen::OnKeyDown(wxKeyEvent& event)
{
    int keyCode = event.GetKeyCode();

#if 0
    // if keyboard was on and up and down is enabled then continue
    if (KeyboardCapture == KEYBOARDCAPTURE_KeyDownKeyUp)
    {
        callthing *callevent = callthing::CreateKeyboardEvent(keyboard_keydown, Msg.WParam);

        calllists.insert(callevent);
        checkqueue();

        // Don't do scrolling
        return;
    }

    // scroll main window with arrow keys
    if (Msg.WParam == VK_PRIOR ||
        Msg.WParam == VK_UP)
    {
        Scroller->ScrollBy(0, -Scroller->YLine);
    }
    else if (Msg.WParam == VK_NEXT ||
             Msg.WParam == VK_DOWN)
    {
        Scroller->ScrollBy(0, Scroller->YLine);
    }
    else if (Msg.WParam == VK_LEFT)
    {
        Scroller->ScrollBy(-Scroller->XLine, 0);
    }
    else if (Msg.WParam == VK_RIGHT)
    {
        Scroller->ScrollBy(Scroller->XLine, 0);
    }
    else if (KeyboardCapture == KEYBOARDCAPTURE_Off &&
        );
#endif

    fprintf(stderr, "CScreen::OnKeyDown()");

    if (CCommanderInput::WantsKeyEvent(keyCode))
    {
        CCommander * commander = CFmsLogo::GetMainFrame()->GetCommander();

        // we don't handle this key.
        // give focus to the edit box and send the press to it.
        commander->PostKeyDownToInputControl(event);
    }
    else
    {
        event.Skip();
    }
    

    // default processing?
}

void CScreen::OnKeyUp(wxKeyEvent& Event)
{
    Event.Skip();
}

BEGIN_EVENT_TABLE(CScreen, wxScrolledWindow)
    EVT_KEY_DOWN(CScreen::OnKeyDown)
    EVT_KEY_UP(CScreen::OnKeyUp)
END_EVENT_TABLE()
