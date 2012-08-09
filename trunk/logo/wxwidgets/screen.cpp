#include "screen.h"

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#include <algorithm>

#ifndef WX_PRECOMP
    #include <wx/event.h>
    #include <wx/dc.h>
    #include <wx/dcmemory.h>
#endif

#include "fmslogo.h"
#include "commander.h"
#include "commanderinput.h"
#include "mainframe.h"
#include "graphwin.h"
#include "screenwindow.h"
#include "main.h"
#include "startup.h"
#include "logocore.h"

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
    m_MemoryBitmap(0),
    m_XScrollRatio(0.5),
    m_YScrollRatio(0.5)
{
    if (!bFixed)
    {
        // Prepare the scrollbars
        SetVirtualSize(logicalScreenWidth, logicalScreenHeight);
        SetScrollRate(1, 1);

        // Scroll to the center
        ScrollToRatio();
    }

    m_ScreenDeviceContext = new wxClientDC(this);
    m_MemoryBitmap        = new wxBitmap(logicalScreenWidth, logicalScreenHeight);
    m_MemoryDeviceContext = new wxMemoryDC(*m_MemoryBitmap);

    if (!m_MemoryDeviceContext->IsOk())
    {
        // TODO: report an error
    }

    // Get a pointer to the native in-memory image of the screen
    MemoryBitMap = static_cast<HBITMAP>(m_MemoryBitmap->GetHBITMAP());

    // clear the bitmap to all white
    SetBackgroundColour(*wxWHITE);
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
    delete m_MemoryBitmap;
    delete m_MemoryDeviceContext;
}

static
FLONUM
GetScrollRatio(int CurrentPosition, int TotalLength)
{
    FLONUM ratio;

    if (TotalLength <= 1)
    {
        ratio = 0;
    }
    else
    {
        ratio = (FLONUM) CurrentPosition / (FLONUM) (TotalLength);
    }

    return ratio;
}

void CScreen::ScrollToRatio()
{
    // Get the virtual size.
    // This is the size of the drawable areas scaled to the
    // current zoom factor.
    int virtualWidth;
    int virtualHeight;
    GetVirtualSize(&virtualWidth, &virtualHeight);

    // Get the size of the viewable area.
    const wxRect & screenRect = GetClientSize();

    // Calculate the scroll positions that correspond to
    // the scroll ratios.
    int newXScrollPosition = -1;
    if (screenRect.GetWidth() <= virtualWidth)
    {
        int totalRange = virtualWidth - screenRect.GetWidth();
        newXScrollPosition = static_cast<int>(totalRange * m_XScrollRatio);
    }

    int newYScrollPosition = -1;
    if (screenRect.GetHeight() <= virtualHeight)
    {
        int totalRange = virtualHeight - screenRect.GetHeight();
        newYScrollPosition = static_cast<int>(totalRange * m_YScrollRatio);
    }

    // Scroll to the new location
    Scroll(newXScrollPosition, newYScrollPosition);
}

void CScreen::AdjustScrollPositionToZoomFactor(FLONUM NewZoomFactor)
{
    SetVirtualSize(
        BitMapWidth  * NewZoomFactor,
        BitMapHeight * NewZoomFactor);

    ScrollToRatio();
}

void CScreen::OnPaint(wxPaintEvent& PaintEvent)
{
    wxPaintDC paintContext(this);
    PrepareDC(paintContext);

    // This is a compromise between speed and memory (as is most code).
    // All drawing is written to the backing store 1 to 1 even when zoomed.
    // When zoomed all drawing and painting is scaled to the display on the fly.
    // Painting can be a bit slow while zoomed. It also can be inaccurate when
    // mixing scaled painting and scaled drawing. Printing is never zoomed.
    // User can use Bitfit if he/she wants data scaled.
    HDC PaintDC = static_cast<HDC>(paintContext.GetHDC());

    // grab the client area's backing store (a bitmap)
    HDC memoryDC = static_cast<HDC>(m_MemoryDeviceContext->GetHDC());

    //HBITMAP oldBitmap = (HBITMAP) SelectObject(memoryDC, MemoryBitMap);
    //m_MemoryDeviceContext->SelectObject(*m_MemoryBitmap);

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

    // Determine the top left corner of where the window is scrolled
    int vbX;
    int vbY; 
    GetViewStart(&vbX, &vbY);

    if (!zoom_flag)
    {
        // The image is not zoomed.  Do a normal BLIT

        // Determine the size of the viewable area
        int clientWidth;
        int clientHeight;
        GetClientSize(&clientWidth, &clientHeight);

        for (wxRegionIterator regionIterator(GetUpdateRegion());
             regionIterator;
             regionIterator++)
        {
            // The x,y coordinates are on the client area
            wxCoord x      = regionIterator.GetX();
            wxCoord y      = regionIterator.GetY();
            wxCoord width  = regionIterator.GetWidth();
            wxCoord height = regionIterator.GetHeight();

            // Fill the part to the right of the screen.
            if (BitMapWidth <= x + width)
            {
                paintContext.SetBrush(*wxWHITE_BRUSH);
                paintContext.SetPen(*wxWHITE_PEN);

                paintContext.DrawRectangle(
                    BitMapWidth,               // x
                    0,                         // y
                    clientWidth - BitMapWidth, // width
                    BitMapHeight);             // height
            }

            // Fill the part below the screen.
            if (BitMapHeight <= y + height)
            {
                paintContext.SetBrush(*wxWHITE_BRUSH);
                paintContext.SetPen(*wxWHITE_PEN);

                paintContext.DrawRectangle(
                    x,                             // x
                    BitMapHeight,                  // y
                    BitMapWidth,                   // width
                    clientHeight - BitMapHeight);  // height
            }

            paintContext.Blit(
                x + vbX,
                y + vbY,
                width,
                height,
                m_MemoryDeviceContext,
                x + vbX,
                y + vbY);
        }
    }
    else
    {
        // We are zoomed.  Compute scaling and then display
        if (g_OsVersionInformation.dwPlatformId == VER_PLATFORM_WIN32_NT)
        {
            SetStretchBltMode(PaintDC, HALFTONE);
        }
        else
        {
            // HALFTONE is not supported on Win 95/98/ME
            SetStretchBltMode(PaintDC, COLORONCOLOR);
        }

        for (wxRegionIterator regionIterator(GetUpdateRegion());
             regionIterator;
             regionIterator++)
        {
            // regionIterator gives coordinates in terms of the
            // client area.
            // We need to determine what rectangle in memoryBitmap corresponds
            // to this rectangle.
            FLONUM sourceRectLeft   = regionIterator.GetX();
            FLONUM sourceRectTop    = regionIterator.GetY();
            FLONUM sourceRectRight  = sourceRectLeft + regionIterator.GetWidth();
            FLONUM sourceRectBottom = sourceRectTop  + regionIterator.GetHeight();

            // Shift the rectangle based on the scroll position.
            sourceRectLeft   += vbX;
            sourceRectRight  += vbX;
            sourceRectTop    += vbY;
            sourceRectBottom += vbY;

            // First, expand the source rectangle a little bit based zoom factor,
            // It doesn't hurt to copy a little more than necessary, but copying
            // less can result in jaggies.
            const FLONUM inflateIncrement = (the_zoom+0.5)*2.0;
            sourceRectLeft   -= inflateIncrement;
            sourceRectTop    -= inflateIncrement;
            sourceRectRight  += inflateIncrement;
            sourceRectBottom += inflateIncrement;

            // Second, scale based on the zoom factor.
            // We divide by the zoom factor to convert from screen coordinates
            // to turtle coordinates.  If we're zoomed in, the_zoom greater
            // than 1, so dividing by it will shrink the rectangle that
            // we're going to copy from.
            FLONUM scaledSourceRectLeft   = sourceRectLeft   / the_zoom;
            FLONUM scaledSourceRectTop    = sourceRectTop    / the_zoom;
            FLONUM scaledSourceRectRight  = sourceRectRight  / the_zoom;
            FLONUM scaledSourceRectBottom = sourceRectBottom / the_zoom;

            // fill the part to the right of the screen.
            if (BitMapWidth < scaledSourceRectRight)
            {
                paintContext.SetBrush(*wxWHITE_BRUSH);
                paintContext.SetPen(*wxWHITE_PEN);

                paintContext.DrawRectangle(
                    BitMapWidth * the_zoom,
                    0,
                    sourceRectRight,
                    BitMapHeight * the_zoom);
            }

            // fill the part below the screen.
            if (BitMapHeight < scaledSourceRectBottom)
            {
                paintContext.SetBrush(*wxWHITE_BRUSH);
                paintContext.SetPen(*wxWHITE_PEN);

                paintContext.DrawRectangle(
                    sourceRectLeft,                              // x
                    BitMapHeight * the_zoom,                     // y
                    sourceRectRight - sourceRectLeft,            // width
                    sourceRectBottom - BitMapHeight * the_zoom); // height
            }

            // Make sure that none of rectangle's borders are off-screen
            // after we inflated it.
            RECT sourceRect;
            sourceRect.left   = (int) (std::min(std::max(0.0, scaledSourceRectLeft),   (double)BitMapWidth));
            sourceRect.top    = (int) (std::min(std::max(0.0, scaledSourceRectTop),    (double)BitMapHeight));
            sourceRect.right  = (int) (std::min(std::max(0.0, scaledSourceRectRight),  (double)BitMapWidth));
            sourceRect.bottom = (int) (std::min(std::max(0.0, scaledSourceRectBottom), (double)BitMapHeight));

            // Now project the source rectangle back onto the screen.
            // This should be roughtly the same as the original regionIterator,
            // but may be larger due to rounding and may be smaller due to 
            // trucation of the off-world areas that still fit on the screen.
            RECT destRect;
            destRect.left   = sourceRect.left   * the_zoom;
            destRect.top    = sourceRect.top    * the_zoom;
            destRect.right  = sourceRect.right  * the_zoom;
            destRect.bottom = sourceRect.bottom * the_zoom;

            // Copy the corresponding part of the image to the screen
            StretchBlt(
                PaintDC,
                destRect.left,
                destRect.top,
                destRect.right  - destRect.left,
                destRect.bottom - destRect.top,
                memoryDC,
                sourceRect.left,
                sourceRect.top,
                sourceRect.right  - sourceRect.left,
                sourceRect.bottom - sourceRect.top,
                SRCCOPY);
        }
    }

    /* restore resources */
    if (EnablePalette)
    {
        SelectPalette(memoryDC, oldPalette2, FALSE);
        SelectPalette(PaintDC, oldPalette, FALSE);
    }

    //SelectObject(memoryDC, oldBitmap);

    // draw the turtles on top of the image
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
                        paintContext.DrawLine(
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

void CScreen::OnScroll(wxScrollWinEvent& Event)
{
    if (Event.GetEventType() == wxEVT_SCROLLWIN_THUMBRELEASE)
    {
        // The user has just let go of the mouse after scrolling.

        // Get the virtual size.
        // This is the size of the drawable areas scaled to the
        // current zoom factor.
        int virtualWidth;
        int virtualHeight;
        GetVirtualSize(&virtualWidth, &virtualHeight);

        // Get the size of the viewable area, which is also
        // the scroll range, since we scroll 1:1 with pixels.
        int viewWidth;
        int viewHeight;
        GetClientSize(&viewWidth, &viewHeight);

        // Update the scroll ratio that corresponds to this event.
        switch (Event.GetOrientation())
        {
        case wxHORIZONTAL:
            m_XScrollRatio = GetScrollRatio(Event.GetPosition(), virtualWidth - viewWidth);
            break;

        case wxVERTICAL:
            m_YScrollRatio = GetScrollRatio(Event.GetPosition(), virtualHeight - viewHeight);
            break;
        }
    }

    // Force a screen repaint
    Update();

    // continue with the default processing
    Event.Skip();
}

void CScreen::OnKeyDown(wxKeyEvent& Event)
{
    int keyCode = Event.GetKeyCode();

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
        commander->PostKeyDownToInputControl(Event);
    }
    else
    {
        Event.Skip();
    }
    

    // default processing?
}

void CScreen::OnKeyUp(wxKeyEvent& Event)
{
    Event.Skip();
}

void CScreen::OnSize(wxSizeEvent& Event)
{
    ScrollToRatio();
    Event.Skip();
    Refresh();
}

BEGIN_EVENT_TABLE(CScreen, wxScrolledWindow)
    EVT_KEY_DOWN(CScreen::OnKeyDown)
    EVT_KEY_UP(CScreen::OnKeyUp)
    EVT_PAINT(CScreen::OnPaint)
    EVT_SIZE(CScreen::OnSize)
    EVT_SCROLLWIN(CScreen::OnScroll)
END_EVENT_TABLE()
