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
class CScreen;

class CMainFrame : public wxFrame
{
public:
    CMainFrame();
    virtual ~CMainFrame();

    // Menu commands
    void EditProcedure(wxCommandEvent& event);
    void EraseProcedure(wxCommandEvent& event);
    void SetLabelFont(wxCommandEvent& event);
    void SetActiveArea(wxCommandEvent& event);
    void SetPenSize(wxCommandEvent& event);
    void SetPenColor(wxCommandEvent& event);
    void SetFloodColor(wxCommandEvent& event);
    void SetScreenColor(wxCommandEvent& event);
    void ZoomIn(wxCommandEvent& event);
    void ZoomOut(wxCommandEvent& event);
    void ZoomNormal(wxCommandEvent& event);
    void Help(wxCommandEvent& event);
    void Examples(wxCommandEvent& event);
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
    void
    CMainFrame::SetColorHelper(
        class CSetColor * &   SetColorDialog,
        const char *          DialogTitle,
        const class wxColor & InitialColor
        );

    wxIcon           * m_FmsLogoIcon;
    CScreen          * m_Screen;
    wxWindow         * m_Commander;
    CCommander       * m_RealCommander;
public:  // HACK: make this private
    CStatusDialog    * m_StatusDialog;
private:
    CSetPenSize      * m_SetPenSizeDialog;
    wxSplitterWindow * m_Splitter;

    bool  m_CommanderIsDocked;

    class CSetColor * m_SetPenColorDialog;
    class CSetColor * m_SetFloodColorDialog;
    class CSetColor * m_SetScreenColorDialog;

    std::map<CWorkspaceEditor*,CWorkspaceEditor*>  m_Editors;

    DECLARE_EVENT_TABLE();
    DECLARE_NO_COPY_CLASS(CMainFrame);
};
