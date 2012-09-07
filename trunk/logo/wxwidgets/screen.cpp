#include "screen.h"

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#include <algorithm>

#ifndef WX_PRECOMP
    #include <wx/event.h>
    #include <wx/dc.h>
    #include <wx/dcmemory.h>
#endif

#include "devwind.h"
#include "logoeventqueue.h"
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

// This function converts wxWidgets virtual key codes to Windows Virtual
// Key Code, which is what FMSLogo programs expect to be given.
// The code is based on wxCharCodeWXToMSW in wxMSW-2.8.12/src/msw/window.cpp,
// but unlike wxKeyEvent.GetRawKeyCode(), it returns the windows key code on
// non-Windows platforms.
static
int
WxKeyCodeToVirtualKeyCode(
    int WxKeyCode
    )
{
    static const struct wxKeyMapping
    {
        int       WindowVirtualKeyCode;
        wxKeyCode WxKeyCode;
    } specialKeys[] =
    {
        {VK_CANCEL,        WXK_CANCEL},
        {VK_BACK,          WXK_BACK},
        {VK_TAB,           WXK_TAB},
        {VK_CLEAR,         WXK_CLEAR},
        {VK_SHIFT,         WXK_SHIFT},
        {VK_CONTROL,       WXK_CONTROL},
        {VK_MENU ,         WXK_ALT},
        {VK_PAUSE,         WXK_PAUSE},
        {VK_CAPITAL,       WXK_CAPITAL},
        {VK_SPACE,         WXK_SPACE},
        {VK_ESCAPE,        WXK_ESCAPE},
        {VK_SELECT,        WXK_SELECT},
        {VK_PRINT,         WXK_PRINT},
        {VK_EXECUTE,       WXK_EXECUTE},
        {VK_SNAPSHOT,      WXK_SNAPSHOT},
        {VK_HELP,          WXK_HELP},

        {VK_NUMPAD0,       WXK_NUMPAD0},
        {VK_NUMPAD1,       WXK_NUMPAD1},
        {VK_NUMPAD2,       WXK_NUMPAD2},
        {VK_NUMPAD3,       WXK_NUMPAD3},
        {VK_NUMPAD4,       WXK_NUMPAD4},
        {VK_NUMPAD5,       WXK_NUMPAD5},
        {VK_NUMPAD6,       WXK_NUMPAD6},
        {VK_NUMPAD7,       WXK_NUMPAD7},
        {VK_NUMPAD8,       WXK_NUMPAD8},
        {VK_NUMPAD9,       WXK_NUMPAD9},
        {VK_MULTIPLY,      WXK_NUMPAD_MULTIPLY},
        {VK_ADD,           WXK_NUMPAD_ADD},
        {VK_SUBTRACT,      WXK_NUMPAD_SUBTRACT},
        {VK_DECIMAL,       WXK_NUMPAD_DECIMAL},
        {VK_DIVIDE,        WXK_NUMPAD_DIVIDE},

        {VK_F1,            WXK_F1},
        {VK_F2,            WXK_F2},
        {VK_F3,            WXK_F3},
        {VK_F4,            WXK_F4},
        {VK_F5,            WXK_F5},
        {VK_F6,            WXK_F6},
        {VK_F7,            WXK_F7},
        {VK_F8,            WXK_F8},
        {VK_F9,            WXK_F9},
        {VK_F10,           WXK_F10},
        {VK_F11,           WXK_F11},
        {VK_F12,           WXK_F12},
        {VK_F13,           WXK_F13},
        {VK_F14,           WXK_F14},
        {VK_F15,           WXK_F15},
        {VK_F16,           WXK_F16},
        {VK_F17,           WXK_F17},
        {VK_F18,           WXK_F18},
        {VK_F19,           WXK_F19},
        {VK_F20,           WXK_F20},
        {VK_F21,           WXK_F21},
        {VK_F22,           WXK_F22},
        {VK_F23,           WXK_F23},
        {VK_F24,           WXK_F24},

        {VK_NUMLOCK,       WXK_NUMLOCK},
        {VK_SCROLL,        WXK_SCROLL},

        {VK_LWIN,          WXK_WINDOWS_LEFT},
        {VK_RWIN,          WXK_WINDOWS_RIGHT},
        {VK_APPS,          WXK_WINDOWS_MENU},

        // Add some keys codes that are not 1:1
        {VK_PRIOR,         WXK_PAGEUP},
        {VK_PRIOR,         WXK_NUMPAD_PAGEUP},

        {VK_NEXT,          WXK_PAGEDOWN},
        {VK_NEXT,          WXK_NUMPAD_PAGEDOWN},

        {VK_END,           WXK_END},
        {VK_END,           WXK_NUMPAD_END},

        {VK_HOME,          WXK_HOME},
        {VK_HOME,          WXK_NUMPAD_HOME},

        {VK_LEFT,          WXK_LEFT},
        {VK_LEFT,          WXK_NUMPAD_LEFT},

        {VK_UP,            WXK_UP},
        {VK_UP,            WXK_NUMPAD_UP},

        {VK_RIGHT,         WXK_RIGHT},
        {VK_RIGHT,         WXK_NUMPAD_RIGHT},

        {VK_DOWN,          WXK_DOWN},
        {VK_DOWN,          WXK_NUMPAD_DOWN},

        {VK_INSERT,        WXK_INSERT},
        {VK_INSERT,        WXK_NUMPAD_INSERT},

        {VK_DELETE,        WXK_DELETE},
        {VK_DELETE,        WXK_NUMPAD_DELETE},
    };

    // check the table first
    for (size_t i = 0; i < ARRAYSIZE(specialKeys); i++)
    {
        if (specialKeys[i].WxKeyCode == WxKeyCode)
        {
            return specialKeys[i].WindowVirtualKeyCode;
        }
    }

    // This key code has no special mapping, so it's likely to be
    // an ASCII code.
    return WxKeyCode;
}

void CScreen::OnKeyDown(wxKeyEvent& Event)
{
    int keyCode = Event.GetKeyCode();

    // if keyboard was on and up and down is enabled then continue
    if (KeyboardCapture == KEYBOARDCAPTURE_KeyDownKeyUp)
    {
        // Map WX keycodes to Windows key codes
        int windowsKeyCode = WxKeyCodeToVirtualKeyCode(keyCode);

        // Post the event to the logo event queue
        callthing *callevent = callthing::CreateKeyboardEvent(
            keyboard_keydown,
            windowsKeyCode);

        calllists.insert(callevent);
        checkqueue();
    }
    else if (keyCode == WXK_PRIOR ||
             keyCode == WXK_UP    ||
             keyCode == WXK_NEXT  ||
             keyCode == WXK_DOWN  ||
             keyCode == WXK_LEFT  ||
             keyCode == WXK_RIGHT)
    {
        // scroll main window with arrow keys
        Event.Skip();
    }
    else if (KeyboardCapture == KEYBOARDCAPTURE_Off &&
             CCommanderInput::WantsKeyEvent(keyCode))
    {
        CCommander * commander = CFmsLogo::GetMainFrame()->GetCommander();

        // We don't handle this key.
        // Give focus to the edit box and send the press to it.
        commander->PostKeyDownToInputControl(Event);
    }
    else
    {
        // default processing
        Event.Skip();
    }
}

void CScreen::OnKeyUp(wxKeyEvent& Event)
{
    if (KeyboardCapture == KEYBOARDCAPTURE_KeyDownKeyUp)
    {
        // Map WX keycodes to Windows key codes
        int wxKeyCode      = Event.GetKeyCode();
        int windowsKeyCode = WxKeyCodeToVirtualKeyCode(wxKeyCode);

        // Post the event to the logo event queue
        callthing *callevent = callthing::CreateKeyboardEvent(
            keyboard_keyup,
            windowsKeyCode);

        calllists.insert(callevent);
        checkqueue();
    }
    else
    {
        // else do your normal stuff
        Event.Skip();
    }
}

static
bool
IsLogoCharCode(
    int WxKeyCode
    )
{
    // MSWLogo did not consider all keys to be "KeyDown" keycodes.
    // For example, the function keys and the shift key did not
    // generate a KeyDown event.  For compatibility, only want to
    // forward a keyboard event when MSWLogo would have.

    // Look for "bad" codes, rather than the "good" key codes 
    // because it's better to err on the side of generating too many
    // events (which will likely be ignored by the Logo program)
    // than generating too few, which could cause some Logo programs
    // to misbehave.
    switch (WxKeyCode)
    {
    case WXK_CANCEL:
    case WXK_CLEAR:
    case WXK_SHIFT:
    case WXK_CONTROL:
    case WXK_ALT:
    case WXK_PAUSE:
    case WXK_SELECT:
    case WXK_PRINT:
    case WXK_SNAPSHOT:
    case WXK_HELP:

    case WXK_F1:
    case WXK_F2:
    case WXK_F3:
    case WXK_F4:
    case WXK_F5:
    case WXK_F6:
    case WXK_F7:
    case WXK_F8:
    case WXK_F9:
    case WXK_F10:
    case WXK_F11:
    case WXK_F12:
    case WXK_F13:
    case WXK_F14:
    case WXK_F15:
    case WXK_F16:
    case WXK_F17:
    case WXK_F18:
    case WXK_F19:
    case WXK_F20:
    case WXK_F21:
    case WXK_F22:
    case WXK_F23:
    case WXK_F24:

    case WXK_NUMLOCK:
    case WXK_SCROLL:

    case WXK_WINDOWS_LEFT:
    case WXK_WINDOWS_RIGHT:
    case WXK_WINDOWS_MENU:

    case WXK_END:
    case WXK_NUMPAD_END:
    case WXK_HOME:
    case WXK_NUMPAD_HOME:
    case WXK_LEFT:
    case WXK_NUMPAD_LEFT:
    case WXK_UP:
    case WXK_NUMPAD_UP:
    case WXK_RIGHT:
    case WXK_NUMPAD_RIGHT:
    case WXK_DOWN:
    case WXK_NUMPAD_DOWN:
    case WXK_INSERT:
    case WXK_NUMPAD_INSERT:
    case WXK_DELETE:
    case WXK_NUMPAD_DELETE:
        return false;
    }

    return true;
}

void CScreen::OnChar(wxKeyEvent& Event)
{
    int wxKeyCode = Event.GetKeyCode();

    // If KEYBOARDON was run with a single parameter, then MSWLogo converts
    // WM_CHAR messages, instead of WM_KEY_DOWN messages.
    // WM_CHAR is similar to EVT_CHAR events in wxWidgets, except that EVT_CHAR
    // over-generates, so we filter out the extras using IsLogoCharCode().
    if (KeyboardCapture == KEYBOARDCAPTURE_KeyDown &&
        IsLogoCharCode(wxKeyCode))
    {

        // Map WX keycodes to Windows key codes
        int windowsKeyCode = WxKeyCodeToVirtualKeyCode(wxKeyCode);

        // Forward the event to Logo
        callthing * callevent = callthing::CreateKeyboardEvent(
            keyboard_keyup,
            windowsKeyCode);

        calllists.insert(callevent);
        checkqueue();
    }
    else
    {
        // else do your normal stuff
        Event.Skip();
    }
}

static void ProcessMouseEvent(wxMouseEvent & Event, char * Callback)
{
    if (MouseCaptureIsEnabled)
    {
        // if user turned on mouse the queue up event
        callthing * callevent = callthing::CreateMouseEvent(
            Callback,
            Event.GetX(),
            Event.GetY());

        calllists.insert(callevent);
        checkqueue();
    }

    // Always do default processing
    Event.Skip();
}

void CScreen::OnRightMouseButtonDown(wxMouseEvent& Event)
{
    ProcessMouseEvent(Event, mouse_rbuttondown);
}

void CScreen::OnRightMouseButtonUp(wxMouseEvent& Event)
{
    ProcessMouseEvent(Event, mouse_rbuttonup);
}

void CScreen::OnLeftMouseButtonDown(wxMouseEvent& Event)
{
    ProcessMouseEvent(Event, mouse_lbuttondown);
}

void CScreen::OnLeftMouseButtonUp(wxMouseEvent& Event)
{
    ProcessMouseEvent(Event, mouse_lbuttonup);
}

void CScreen::OnMouseMove(wxMouseEvent& Event)
{
    ProcessMouseEvent(Event, mouse_mousemove);
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
    EVT_CHAR(CScreen::OnChar)
    EVT_LEFT_DOWN(CScreen::OnLeftMouseButtonDown)
    EVT_LEFT_UP(CScreen::OnLeftMouseButtonUp)
    EVT_RIGHT_DOWN(CScreen::OnRightMouseButtonDown)
    EVT_RIGHT_UP(CScreen::OnRightMouseButtonUp)
    EVT_MOTION(CScreen::OnMouseMove)
    EVT_PAINT(CScreen::OnPaint)
    EVT_SIZE(CScreen::OnSize)
    EVT_SCROLLWIN(CScreen::OnScroll)
END_EVENT_TABLE()
