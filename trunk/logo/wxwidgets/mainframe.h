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
    CMainFrame(
        int             ScreenWidth,
        int             ScreenHeight,
        const wxPoint & Position = wxDefaultPosition,
        const wxSize  & Size     = wxDefaultSize
        );

    virtual ~CMainFrame();

    void UndockCommanderWindow();
    void DockCommanderWindow();

    void ShowStatus();
    void HideStatus();
    bool StatusDialogIsShowing();

    CCommander * GetCommander();
    CScreen    * GetScreen();

    CWorkspaceEditor * GetWorkspaceEditor();

    bool
    PromptUserForInput(
        char       * Output,
        const char * Prompt
        );

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

    CStatusDialog * GetStatusDialog();
    void            ClearStatusDialog();

private:

    // Menu commands handlers
    void OnFileNew(wxCommandEvent& Event);
    void OnFileLoad(wxCommandEvent& Event);
    void OnFileOpen(wxCommandEvent& Event);
    void OnFileSave(wxCommandEvent& Event);
    void OnFileSaveAs(wxCommandEvent& Event);
    void OnEditProcedure(wxCommandEvent& Event);
    void OnEraseProcedure(wxCommandEvent& Event);
    void OnExit(wxCommandEvent& Event);
    void OnBitmapNew(wxCommandEvent& Event);
    void OnBitmapOpen(wxCommandEvent& Event);
    void OnBitmapSave(wxCommandEvent& Event);
    void OnBitmapSaveAs(wxCommandEvent& Event);
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

    void OnClose(wxCloseEvent& Event);

    // Private helper functions
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

    void
    InitializeOpenFileNameForLogoFiles(
        OPENFILENAME & OpenFileData
        );

    bool WarnIfSavingEmptyWorkspace();
    bool FileSave();
    bool SaveFile();
    bool SaveFileAs();
    bool CanClose();

    void SaveBitmap();
    void SaveBitmapAs();

    // Member variables
    CScreen          * m_Screen;
    wxWindow         * m_Commander;
    CCommander       * m_RealCommander;
    CStatusDialog    * m_StatusDialog;
    CSetPenSize      * m_SetPenSizeDialog;
    wxSplitterWindow * m_Splitter;

    bool  m_CommanderIsDocked;
    bool  m_IsNewFile;
    bool  m_IsNewBitmap;

    // TODO: Make these wxString objects
    char m_FileName[MAX_PATH];
    char m_BitmapName[MAX_PATH];

    class CSetColor * m_SetPenColorDialog;
    class CSetColor * m_SetFloodColorDialog;
    class CSetColor * m_SetScreenColorDialog;

    std::map<CWorkspaceEditor*,CWorkspaceEditor*>  m_Editors;

    DECLARE_EVENT_TABLE();
    DECLARE_NO_COPY_CLASS(CMainFrame);
};
