// -*- c++ -*-

#include "wx/frame.h"

class wxSplitterWindow;
class wxCommandEvent;
class wxScrolledWindow;
class wxIcon;

class CCommander;

class CMainFrame : public wxFrame
{
public:
    CMainFrame();
    virtual ~CMainFrame();

    // Menu commands
    void SetActiveArea(wxCommandEvent& event);
    void AboutFmsLogo(wxCommandEvent& event);
    void AboutMultipleSclerosis(wxCommandEvent& event);
    void Quit(wxCommandEvent& event);
   
private:

    wxIcon           *m_FmsLogoIcon;
    wxScrolledWindow *m_Screen;
    CCommander       *m_Commander;

    wxSplitterWindow* m_splitter;

    DECLARE_EVENT_TABLE();
    DECLARE_NO_COPY_CLASS(CMainFrame);
};
