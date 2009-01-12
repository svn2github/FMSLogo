#ifndef WX_PRECOMP
    #include "wx/scrolwin.h"
#endif

class wxMemoryDC;
class wxBitMap;

class CScreen: public wxScrolledWindow
{
public:
    CScreen(wxWindow* parent);
    virtual ~CScreen();

    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);

    virtual void OnDraw(wxDC& dc);

    wxMemoryDC & GetMemoryDeviceContext();

private:

    wxMemoryDC * m_MemoryDeviceContext;
    wxBitmap   * m_ScreenBitmap;

    DECLARE_NO_COPY_CLASS(CScreen)
    DECLARE_EVENT_TABLE();
};
