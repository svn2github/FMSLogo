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
#include <graphwin.h>
#include <screenwindow.h>

// ----------------------------------------------------------------------------
// CScreen
// ----------------------------------------------------------------------------

CScreen::CScreen(
    wxWindow* parent,
    int       logicalScreenWidth,
    int       logicalScreenHeight
    ) : 
    wxScrolledWindow(
        parent, 
        wxID_ANY, 
        wxDefaultPosition, 
        wxDefaultSize,
        wxHSCROLL | wxVSCROLL | wxNO_FULL_REPAINT_ON_RESIZE),
    m_ScreenDeviceContext(0),
    m_MemoryDeviceContext(0),
    m_ScreenBitmap(0)
{
    SetVirtualSize(logicalScreenWidth, logicalScreenHeight);

    m_ScreenDeviceContext = new wxClientDC(this);
    m_ScreenBitmap        = new wxBitmap(logicalScreenWidth, logicalScreenHeight);
    m_MemoryDeviceContext = new wxMemoryDC(*m_ScreenBitmap);

    if (!m_MemoryDeviceContext->IsOk())
    {
        // TODO: report an error
    }

    // Get a pointer to the native in-memory image of the screen
    MemoryBitMap = static_cast<HBITMAP>(m_ScreenBitmap->GetHBITMAP());

    // clear the bitmap to all white
    m_MemoryDeviceContext->SetBrush(*wxWHITE_BRUSH);
    m_MemoryDeviceContext->Clear();
}

CScreen::~CScreen()
{
    if (m_MemoryDeviceContext)
    {
        m_MemoryDeviceContext->SelectObject(wxNullBitmap);
        MemoryBitMap = NULL;
    }

    delete m_ScreenDeviceContext;
    delete m_ScreenBitmap;
    delete m_MemoryDeviceContext;
}

void CScreen::OnPaint(wxPaintEvent& PaintEvent)
{
    wxPaintDC DeviceContext(this);
    PrepareDC(DeviceContext);

    // This is a compromise between speed and memory (as is most code).
    // All drawing is written to the backing store 1 to 1 even when zoomed.
    // When zoomed all drawing and painting is scaled to the display on the fly.
    // Painting can be a bit slow while zoomed. It also can be inaccurate when
    // mixing scaled painting and scaled drawing. Printing is never zoomed.
    // User can use Bitfit if he/she wants data scaled.
    HDC PaintDC = static_cast<HDC>(DeviceContext.GetHDC());

    // grab the client area's backing store (a bitmap)
    HDC memoryDC = static_cast<HDC>(m_MemoryDeviceContext->GetHDC());

    //HBITMAP oldBitmap = (HBITMAP) SelectObject(memoryDC, MemoryBitMap);
    m_MemoryDeviceContext->SelectObject(*m_ScreenBitmap);

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
        // Determine the top left corner of where the window is scrolled
        int vbX;
        int vbY; 
        GetViewStart(&vbX, &vbY);

        for (wxRegionIterator regionIterator(GetUpdateRegion());
             regionIterator;
             regionIterator++)
        {
            wxCoord x      = regionIterator.GetX();
            wxCoord y      = regionIterator.GetY();
            wxCoord width  = regionIterator.GetW();
            wxCoord height = regionIterator.GetH();

            DeviceContext.Blit(
                x,
                y,
                width,
                height,
                m_MemoryDeviceContext,
                x,
                y,
                wxCOPY);
        }
    }
#if 1
    else
    {
        TraceOutput("fixme: Painting with zoom not implemented.\n");
    }
#else

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
#endif

    /* restore resources */

    if (EnablePalette)
    {
        SelectPalette(memoryDC, oldPalette2, FALSE);
        SelectPalette(PaintDC, oldPalette, FALSE);
    }

    //SelectObject(memoryDC, oldBitmap);

    /* if turtle do it */

    SetROP2(PaintDC, R2_NOT);

    for (int j = 0; j <= g_MaxTurtle; j++)
    {
        if (g_Turtles[j].IsShown)
        {
            if (g_Turtles[j].BitmapRasterMode)
            {
                turtlepaste(j);
            }
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    if (g_Turtles[j].Points[i].bValid)
                    {
                        DeviceContext.DrawLine(
                            g_Turtles[j].Points[i].from.x * the_zoom,
                            g_Turtles[j].Points[i].from.y * the_zoom,
                            g_Turtles[j].Points[i].to.x * the_zoom,
                            g_Turtles[j].Points[i].to.y * the_zoom);
                    }
                }
            }
        }
    }
}

wxClientDC & CScreen::GetScreenDeviceContext()
{
    return *m_ScreenDeviceContext;
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

    TraceOutput("CScreen::OnKeyDown()\n");

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
    EVT_PAINT(CScreen::OnPaint)
END_EVENT_TABLE()
