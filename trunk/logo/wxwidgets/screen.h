#ifndef WX_PRECOMP
    #include "wx/scrolwin.h"
#endif

#include <logocore.h> // for FLONUM

class wxClientDC;
class wxMemoryDC;
class wxBitMap;

class CScreen: public wxScrolledWindow
{
public:
    CScreen(wxWindow* parent, int width, int height);
    virtual ~CScreen();

    wxClientDC & GetScreenDeviceContext();
    wxMemoryDC & GetMemoryDeviceContext();

    void AdjustScrollPositionToZoomFactor(FLONUM NewZoomFactor);

private:
    // event handlers
    void OnKeyDown(wxKeyEvent& Event);
    void OnKeyUp(wxKeyEvent& Event);
    void OnChar(wxKeyEvent& Event);
    void OnScroll(wxScrollWinEvent & Event);
    void OnPaint(wxPaintEvent& PaintEvent);
    void OnSize(wxSizeEvent& Event);

    // helper functions
    void ScrollToRatio();

    // member variables
    wxClientDC * m_ScreenDeviceContext;
    wxMemoryDC * m_MemoryDeviceContext;
    wxBitmap   * m_MemoryBitmap;

    double       m_XScrollRatio;
    double       m_YScrollRatio;

    DECLARE_NO_COPY_CLASS(CScreen)
    DECLARE_EVENT_TABLE();
};
