// -*- c++ -*-

#include "wx/frame.h"

class wxSplitterWindow;
class wxCommandEvent;
class wxScrolledWindow;
class wxIcon;
class CCommander;
class CStatusDialog;

class CSetPenSize;

class CMainFrame : public wxFrame
{
public:
    CMainFrame();
    virtual ~CMainFrame();

    // Menu commands
    void SetActiveArea(wxCommandEvent& event);
    void SetPenSize(wxCommandEvent& event);
    void ZoomIn(wxCommandEvent& event);
    void ZoomOut(wxCommandEvent& event);
    void AboutFmsLogo(wxCommandEvent& event);
    void AboutMultipleSclerosis(wxCommandEvent& event);
    void Quit(wxCommandEvent& event);

    void UndockCommanderWindow();
    void DockCommanderWindow();

    void ShowStatus();
    void HideStatus();
    bool StatusDialogIsShowing();

    CCommander * GetCommander();


private:
    wxIcon           * m_FmsLogoIcon;
    wxScrolledWindow * m_Screen;
    wxWindow         * m_Commander;
    CCommander       * m_RealCommander;
public:  // HACK: make this private
    CStatusDialog    * m_StatusDialog;
private:
    CSetPenSize      * m_SetPenSizeDialog;
    wxSplitterWindow * m_Splitter;

    bool  m_CommanderIsDocked;

    DECLARE_EVENT_TABLE();
    DECLARE_NO_COPY_CLASS(CMainFrame);
};
