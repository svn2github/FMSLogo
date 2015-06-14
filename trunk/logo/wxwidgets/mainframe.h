// -*- c++ -*-
#include <map>

#ifndef WX_PURE
#include <windows.h> // for COLORREF
#endif // WX_PURE

#include <wx/frame.h>
#include <wx/print.h>

#include "localizedstrings.h" // for MANUAL_HAS_TRANSLATION_TABLES


class wxSplitterWindow;
class wxCommandEvent;
class wxScrolledWindow;
class wxIcon;

class CCommander;
class CStatusDialog;
class CWorkspaceEditor;
class CSetPenSize;
class CScreen;
class CSetColor;

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
#ifndef WX_PURE
    bool TranslateKeyboardShortcut(MSG & Message);
#endif

    void ShowStatus();
    void HideStatus();
    bool StatusDialogIsShowing();

    CCommander * GetCommander();
    wxWindow   * GetTopLevelWindowForCommander();
    CScreen    * GetScreen();

    bool IsEditorOpen() const;

    CWorkspaceEditor * GetWorkspaceEditor();

    void
    KeyboardNavigateTopLevelWindow(
        wxWindow * CurrentWindowFocus,
        int        DirectionFlags
        );

    char *
    PromptUserForInput(
        const char * Prompt
        );

    void
    PopupEditor(
        const wxString & FileName,
        NODE           * EditArguments,
        bool             CheckForErrors,
        bool             OpenToError
        );

    void
    PopupEditorToError(
        const char *FileName
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

    // A private helper class for printing
    class CLogoPicturePrintout : public wxPrintout
    {
    public:
        CLogoPicturePrintout(
            const wxString        & Title,
            wxWindow              & Screen,
            wxPageSetupDialogData & PageSetup
            );

        bool OnPrintPage(int Page);
        bool HasPage(int Page);

        void
        GetPageInfo(
            int *MinPage,
            int *MaxPage,
            int *SelPageFrom,
            int *SelPageTo
            );

    private:
        wxWindow              & m_Screen;
        wxPageSetupDialogData & m_PageSetup;
    };

    // Menu commands handlers
    void OnFileNew(wxCommandEvent& Event);
    void OnFileLoad(wxCommandEvent& Event);
    void OnFileOpen(wxCommandEvent& Event);
    void OnFileSave(wxCommandEvent& Event);
    void OnFileSaveAs(wxCommandEvent& Event);
    void OnFileSetAsScreenSaver(wxCommandEvent& Event);
    void OnUpdateFileSetAsScreenSaver(wxUpdateUIEvent& Event);
    void OnEditProcedure(wxCommandEvent& Event);
    void OnEraseProcedure(wxCommandEvent& Event);
    void OnExit(wxCommandEvent& Event);
    void OnBitmapNew(wxCommandEvent& Event);
    void OnBitmapOpen(wxCommandEvent& Event);
    void OnBitmapSave(wxCommandEvent& Event);
    void OnBitmapSaveAs(wxCommandEvent& Event);
    void OnBitmapPrint(wxCommandEvent& Event);
    void OnBitmapPrinterSetup(wxCommandEvent& Event);
    void OnSetLabelFont(wxCommandEvent& Event);
    void OnSetCommanderFont(wxCommandEvent& Event);
    void OnSetActiveArea(wxCommandEvent& Event);
    void OnSetPenSize(wxCommandEvent& Event);
    void OnSetPenColor(wxCommandEvent& Event);
    void OnSetFloodColor(wxCommandEvent& Event);
    void OnSetScreenColor(wxCommandEvent& Event);
    void OnZoomIn(wxCommandEvent& Event);
    void OnZoomOut(wxCommandEvent& Event);
    void OnZoomNormal(wxCommandEvent& Event);
    void OnHelp(wxCommandEvent& Event);
#if MANUAL_HAS_TRANSLATION_TABLES
    void OnHelpLanguageToEnglish(wxCommandEvent& Event);
    void OnHelpEnglishToLanguage(wxCommandEvent& Event);
#endif
    void OnHelpTutorial(wxCommandEvent& Event);
    void OnHelpDemo(wxCommandEvent& Event);
    void OnHelpExamples(wxCommandEvent& Event);
    void OnHelpReleaseNotes(wxCommandEvent& Event);
    void OnAboutFmsLogo(wxCommandEvent& Event);
    void OnAboutMultipleSclerosis(wxCommandEvent& Event);

    void OnClose(wxCloseEvent& Event);

#ifndef WX_PURE
    virtual WXLRESULT MSWWindowProc(
        WXUINT   Message,
        WXWPARAM WParam,
        WXLPARAM LParam
        );
#endif // WX_PURE

    // Private helper functions
    void PostCheckQueueMessage();

    CWorkspaceEditor *
    CreateWorkspaceEditor(
        const wxString & FileName,
        NODE           * EditArguments,
        bool             CheckForErrors,
        bool             OpenToError
        );

#ifndef WX_PURE
    void
    SetColorHelper(
        CSetColor * &   SetColorDialog,
        const char *    DialogTitle,
        COLORREF        InitialColor,
        const char *    LogoCommand
        );

    void
    InitializeOpenFileNameForLogoFiles(
        OPENFILENAME & OpenFileData
        );
#endif // WX_PURE

    bool WarnIfSavingEmptyWorkspace();
    bool FileSave();
    bool SaveFile();
    bool SaveFileAs();
    bool CanClose();

    void SaveBitmap();
    void SaveBitmapAs();

    void
    OpenFileWithDefaultApplication(
        const char * FileName
        );

    void ResizeToFitScreen();
    void InitializePrinter();

    // Member variables
    CScreen          * m_Screen;
    wxWindow         * m_Commander;
    CCommander       * m_RealCommander;
    CStatusDialog    * m_StatusDialog;
    CSetPenSize      * m_SetPenSizeDialog;
    wxSplitterWindow * m_Splitter;

    const int m_OriginalWidth;
    const int m_OriginalHeight;

    bool  m_CommanderIsDocked;
    bool  m_IsNewFile;
    bool  m_IsNewBitmap;

    // m_PageSetupData stores printer preferences across printouts.
    wxPageSetupDialogData m_PageSetupData;

#ifndef WX_PURE
    // TODO: Make these wxString objects
    char m_FileName[MAX_PATH];
    char m_BitmapName[MAX_PATH];
#endif // WX_PURE

    CSetColor * m_SetPenColorDialog;
    CSetColor * m_SetFloodColorDialog;
    CSetColor * m_SetScreenColorDialog;

    // REVISIT: should this be std::set?
    std::map<CWorkspaceEditor*,CWorkspaceEditor*> m_Editors;

    DECLARE_EVENT_TABLE();
    DECLARE_NO_COPY_CLASS(CMainFrame);
};
