#ifndef WX_PRECOMP
    #include "wx/scrolwin.h"
#endif

class CScreen: public wxScrolledWindow
{
public:
    CScreen(wxWindow* parent);
    virtual ~CScreen(){};

    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);

    virtual void OnDraw(wxDC& dc);

private:
    DECLARE_NO_COPY_CLASS(CScreen)
    DECLARE_EVENT_TABLE();
};
