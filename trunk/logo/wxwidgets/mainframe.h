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

struct NODE;

class CMainFrame : public wxFrame
{
public:
    CMainFrame(int ScreenWidth, int ScreenHeight);
    virtual ~CMainFrame();

    void UndockCommanderWindow();
    void DockCommanderWindow();

    void ShowStatus();
    void HideStatus();
    bool StatusDialogIsShowing();

    CCommander * GetCommander();
    CScreen    * GetScreen();

    CWorkspaceEditor * GetWorkspaceEditor();

    void
    PopupEditor(
        const wxString & FileName,
        NODE           * EditArguments,
        bool             CheckForErrors
        );

    static
    int
    PopupEditorForFile(
        const wxString & FileName,
        NODE           * EditArguments
        );

    void CloseWorkspaceEditor(CWorkspaceEditor * Editor);

private:

    // Menu commands handlers
    void OnEditProcedure(wxCommandEvent& Event);
    void OnEraseProcedure(wxCommandEvent& Event);
    void OnSetLabelFont(wxCommandEvent& Event);
    void OnSetActiveArea(wxCommandEvent& Event);
    void OnSetPenSize(wxCommandEvent& Event);
    void OnSetPenColor(wxCommandEvent& Event);
    void OnSetFloodColor(wxCommandEvent& Event);
    void OnSetScreenColor(wxCommandEvent& Event);
    void OnZoomIn(wxCommandEvent& Event);
    void OnZoomOut(wxCommandEvent& Event);
    void OnZoomNormal(wxCommandEvent& Event);
    void OnHelp(wxCommandEvent& Event);
    void OnExamples(wxCommandEvent& Event);
    void OnAboutFmsLogo(wxCommandEvent& Event);
    void OnAboutMultipleSclerosis(wxCommandEvent& Event);
    void OnQuit(wxCommandEvent& Event);

    CWorkspaceEditor *
    CreateWorkspaceEditor(
        const wxString & FileName,
        NODE           * EditArguments,
        bool             CheckForErrors
        );

    void
    SetColorHelper(
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
