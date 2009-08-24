#include <screen.h>

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include <wx/event.h>
    #include <wx/dc.h>
    #include <wx/dcmemory.h>
#endif

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
    // TODO: 1000x1000 should be passed in
    m_ScreenBitmap        = new wxBitmap(1000, 1000);
    m_MemoryDeviceContext = new wxMemoryDC(*m_ScreenBitmap);

    if (!m_MemoryDeviceContext->IsOk())
    {
        // TODO: report an error
    }

    // clear the bitmap to all white
    m_MemoryDeviceContext->SetBrush(*wxWHITE_BRUSH);
    m_MemoryDeviceContext->Clear();
}

CScreen::~CScreen()
{
    delete m_ScreenBitmap;
    delete m_MemoryDeviceContext;
}

void CScreen::OnDraw(wxDC& DeviceContext)
{
    // This is a compromise between speed and memory (as is most code).
    // All drawing is written to the backing store 1 to 1 even when zoomed.
    // When zoomed all drawing and painting is scaled to the display on the fly.
    // Painting can be a bit slow while zoomed. It also can be inaccurate when
    // mixing scaled painting and scaled drawing. Printing is never zoomed.
    // User can use Bitfit if he/she wants data scaled.

    bool isOk = DeviceContext.Blit(
        0,                           // destination X
        0,                           // destination Y
        m_ScreenBitmap->GetWidth(),  // width
        m_ScreenBitmap->GetHeight(), // height
        m_MemoryDeviceContext,       // source DC
        0,                           // source X
        0);                          // source Y

#if 0
    // grab the client area's backing store (a bitmap)
    HDC memoryDC = m_MemoryDeviceContext;

    HBITMAP oldBitmap = (HBITMAP) SelectObject(memoryDC, MemoryBitMap);

    HPALETTE oldPalette  = NULL;
    HPALETTE oldPalette2 = NULL;

    /* if palette allocate it */

    if (EnablePalette)
    {
        oldPalette = SelectPalette(PaintDC, ThePalette, FALSE);
        RealizePalette(PaintDC);

        oldPalette2 = SelectPalette(memoryDC, ThePalette, FALSE);
        RealizePalette(memoryDC);
    }

    /* if 1 to 1 the just do normal paint */

    if (the_zoom == 1.0)
    {
        BitBlt(
            PaintDC,
            PaintRect.Left(),
            PaintRect.Top(),
            PaintRect.Width(),
            PaintRect.Height(),
            memoryDC,
            PaintRect.Left(),
            PaintRect.Top(),
            SRCCOPY);
    }

    /* else compute scaling and then display */

    else if (the_zoom > 1.0)
    {
        TRect TempRect;

        TempRect = PaintRect;

        TempRect.Inflate(((int) (the_zoom+0.5))*2, ((int) (the_zoom+0.5))*2);

        TempRect.left   /= the_zoom;
        TempRect.top    /= the_zoom;
        TempRect.right  /= the_zoom;
        TempRect.bottom /= the_zoom;

        if (TempRect.left < 0)
        {
            TempRect.left = 0;
        }
        if (TempRect.top < 0)
        {
            TempRect.top = 0;
        }
        if (TempRect.right > BitMapWidth)
        {
            TempRect.right = BitMapWidth;
        }
        if (TempRect.bottom > BitMapHeight)
        {
            TempRect.bottom = BitMapHeight;
        }

        SetStretchBltMode(PaintDC, COLORONCOLOR);

        StretchBlt(
            PaintDC,
            TempRect.Left()   * the_zoom,
            TempRect.Top()    * the_zoom,
            TempRect.Width()  * the_zoom,
            TempRect.Height() * the_zoom,
            memoryDC,
            TempRect.Left()  ,
            TempRect.Top()   ,
            TempRect.Width() ,
            TempRect.Height(),
            SRCCOPY);
    }
    else
    {
        /* else compute scaling and then display */
        SetStretchBltMode(PaintDC, COLORONCOLOR);

        StretchBlt(
            PaintDC,
            0,
            0,
            BitMapWidth * the_zoom,
            BitMapHeight * the_zoom,
            memoryDC,
            0,
            0,
            BitMapWidth,
            BitMapHeight,
            SRCCOPY);
    }

    /* restore resources */

    if (EnablePalette)
    {
        SelectPalette(memoryDC, oldPalette2, FALSE);
        SelectPalette(PaintDC, oldPalette, FALSE);
    }

    SelectObject(memoryDC, oldBitmap);

    /* if turtle do it */

    SetROP2(PaintDC, R2_NOT);

    for (int j = 0; j <= g_MaxTurtle; j++)
    {
        if (g_Turtles[j].IsShown)
        {
            if (g_Turtles[j].Bitmap)
            {
                turtlepaste(j);
            }
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    if (g_Turtles[j].Points[i].bValid)
                    {
                        MoveToEx(
                            PaintDC,
                            g_Turtles[j].Points[i].from.x * the_zoom,
                            g_Turtles[j].Points[i].from.y * the_zoom,
                            0);

                        LineTo(
                            PaintDC,
                            g_Turtles[j].Points[i].to.x * the_zoom,
                            g_Turtles[j].Points[i].to.y * the_zoom);
                    }
                }
            }
        }
    }
#endif
}

wxMemoryDC & CScreen::GetMemoryDeviceContext()
{
    return *m_MemoryDeviceContext;
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

    fprintf(stderr, "CScreen::OnKeyDown()\n");

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
