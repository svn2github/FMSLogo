// -*- c++ -*-
#include <map>

#include "wx/frame.h"

class wxSplitterWindow;
class wxCommandEvent;
class wxScrolledWindow;
class wxIcon;

class CCommander;
class CStatusDialog;
class CWorkspaceEditor;
class CSetPenSize;

class CMainFrame : public wxFrame
{
public:
    CMainFrame();
    virtual ~CMainFrame();

    // Menu commands
    void EditProcedure(wxCommandEvent& event);
    void EraseProcedure(wxCommandEvent& event);
    void SetActiveArea(wxCommandEvent& event);
    void SetPenSize(wxCommandEvent& event);
    void ZoomIn(wxCommandEvent& event);
    void ZoomOut(wxCommandEvent& event);
    void ZoomNormal(wxCommandEvent& event);
    void Help(wxCommandEvent& event);
    void AboutFmsLogo(wxCommandEvent& event);
    void AboutMultipleSclerosis(wxCommandEvent& event);
    void Quit(wxCommandEvent& event);

    void UndockCommanderWindow();
    void DockCommanderWindow();

    void ShowStatus();
    void HideStatus();
    bool StatusDialogIsShowing();

    CCommander * GetCommander();

    CWorkspaceEditor * GetWorkspaceEditor();
    CWorkspaceEditor * CreateWorskpaceEditor();
    void CloseWorkspaceEditor(CWorkspaceEditor * Editor);


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

    std::map<CWorkspaceEditor*,CWorkspaceEditor*>  m_Editors;

    DECLARE_EVENT_TABLE();
    DECLARE_NO_COPY_CLASS(CMainFrame);
};
