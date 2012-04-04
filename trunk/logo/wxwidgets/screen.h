#ifndef WX_PRECOMP
    #include "wx/scrolwin.h"
#endif

class wxClientDC;
class wxMemoryDC;
class wxBitMap;

class CScreen: public wxScrolledWindow
{
public:
    CScreen(wxWindow* parent, int width, int height);
    virtual ~CScreen();

    void OnKeyDown(wxKeyEvent& Event);
    void OnKeyUp(wxKeyEvent& Event);
    void OnScroll(wxScrollWinEvent & Event);
    void OnPaint(wxPaintEvent& PaintEvent);

    wxClientDC & GetScreenDeviceContext();
    wxMemoryDC & GetMemoryDeviceContext();

private:

    wxClientDC * m_ScreenDeviceContext;
    wxMemoryDC * m_MemoryDeviceContext;
    wxBitmap   * m_MemoryBitmap;

    DECLARE_NO_COPY_CLASS(CScreen)
    DECLARE_EVENT_TABLE();
};
