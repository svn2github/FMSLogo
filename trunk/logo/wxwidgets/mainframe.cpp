// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/log.h"

    #include "wx/app.h"
    #include "wx/frame.h"

    #include "wx/scrolwin.h"
    #include "wx/menu.h"
    #include "wx/msgdlg.h"

    #include "wx/splitter.h"
    #include "wx/dcmirror.h"
    #include "wx/icon.h"
    #include "wx/fontdlg.h"

    #include "wx/dcmemory.h"

    #include <wx/fontutil.h> // for wxNativeFontInfo
#endif

#include <algorithm>

#include "guiutils.h"
#include "commander.h"
#include "setactivearea.h"
#include "aboutfmslogo.h"
#include "aboutmultiplesclerosis.h"
#include "savebeforeexitdialog.h"
#include "logocore.h"
#include "localizedstrings.h"
#include "fmslogo.h"
#include "mainframe.h"
#include "setpensize.h"
#include "utils.h"
#include "statusdialog.h"
#include "screen.h"
#include "editproceduredialog.h"
#include "eraseproceduredialog.h"
#include "minieditor.h"
#include "workspaceeditor.h"
#include "logodata.h"
#include "setcolor.h"
#include "graphwin.h"
#include "init.h"
#include "main.h"
#include "screenwindow.h" // for TraceOutput
#include "wrksp.h"
#include "eval.h"
#include "fileswnd.h"

#include "fmslogo-16x16.xpm"

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// ID for the menu commands
enum
{
    SPLIT_QUIT = 1,
    SPLIT_HORIZONTAL,
    SPLIT_VERTICAL,
    SPLIT_UNSPLIT,
    SPLIT_LIVE,
    SPLIT_SETPOSITION,
    SPLIT_SETMINSIZE,
    SPLIT_SETGRAVITY,
    SPLIT_REPLACE
};

// ----------------------------------------------------------------------------
// Global Variables
// ----------------------------------------------------------------------------

// TODO: move this someplace sensible
static wxFont g_LabelFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

// ----------------------------------------------------------------------------
// our classes
// ----------------------------------------------------------------------------

class MainSplitterWindow : public wxSplitterWindow
{
public:
    MainSplitterWindow(wxFrame *Parent);

private:
    // event handlers
    void OnPositionChanged(wxSplitterEvent& Event);
    void OnPositionChanging(wxSplitterEvent& Event);
    void OnDClick(wxSplitterEvent& Event);
    void OnUnsplitEvent(wxSplitterEvent& Event);

    wxFrame *m_frame;

    DECLARE_EVENT_TABLE()
    DECLARE_NO_COPY_CLASS(MainSplitterWindow)
};

// ----------------------------------------------------------------------------
// CMainFrame
// ----------------------------------------------------------------------------

enum MainFrameMenuIds
{
    ID_FILENEW,
    ID_FILELOAD,
    ID_FILEOPEN,
    ID_FILESAVE,
    ID_FILESAVEAS,
    ID_FILEEDIT,
    ID_FILEERASE,
    ID_EXIT,

    ID_BITMAPNEW,
    ID_BITMAPOPEN,
    ID_BITMAPSAVE,
    ID_BITMAPSAVEAS,

    ID_BITMAPPRINT,
    ID_BITMAPPRINTERSETUP,

    ID_BITMAPPRINTERAREA,

    ID_SETPENSIZE,

    ID_SETLABELFONT,
    ID_SETCOMMANDERFONT,

    ID_SETPENCOLOR,
    ID_SETFLOODCOLOR,
    ID_SETSCREENCOLOR,

    ID_ZOOMIN,
    ID_ZOOMOUT,
    ID_ZOOMNORMAL,

    ID_HELP,
#if LOCALE!=1033
    // options for translating to/from English
    ID_HELPLANGTOENGLISH,
    ID_HELPENGLISHTOLANG,
#endif
    ID_HELPMCI,
    ID_HELPHELP,

    ID_HELPTUTORIAL,
    ID_HELPDEMO,
    ID_HELPEXAMPLES,
    ID_HELPRELEASENOTES,

    ID_HELPABOUT,
    ID_HELPABOUTMS,
};

BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
    EVT_MENU(ID_FILENEW,            CMainFrame::OnFileNew)
    EVT_MENU(ID_FILELOAD,           CMainFrame::OnFileLoad)
    EVT_MENU(ID_FILEOPEN,           CMainFrame::OnFileOpen)
    EVT_MENU(ID_FILESAVE,           CMainFrame::OnFileSave)
    EVT_MENU(ID_FILESAVEAS,         CMainFrame::OnFileSaveAs)
    EVT_MENU(ID_FILEEDIT,           CMainFrame::OnEditProcedure)
    EVT_MENU(ID_FILEERASE,          CMainFrame::OnEraseProcedure)
    EVT_MENU(ID_EXIT,               CMainFrame::OnQuit)
    EVT_MENU(ID_SETPENSIZE,         CMainFrame::OnSetPenSize)
    EVT_MENU(ID_BITMAPPRINTERAREA,  CMainFrame::OnSetActiveArea)
    EVT_MENU(ID_SETLABELFONT,       CMainFrame::OnSetLabelFont)
    EVT_MENU(ID_SETPENCOLOR,        CMainFrame::OnSetPenColor)
    EVT_MENU(ID_SETSCREENCOLOR,     CMainFrame::OnSetScreenColor)
    EVT_MENU(ID_SETFLOODCOLOR,      CMainFrame::OnSetFloodColor)
    EVT_MENU(ID_HELP,               CMainFrame::OnHelp)
    EVT_MENU(ID_HELPEXAMPLES,       CMainFrame::OnExamples)
    EVT_MENU(ID_HELPABOUT,          CMainFrame::OnAboutFmsLogo)
    EVT_MENU(ID_HELPABOUTMS,        CMainFrame::OnAboutMultipleSclerosis)
    EVT_MENU(ID_ZOOMIN,             CMainFrame::OnZoomIn)
    EVT_MENU(ID_ZOOMOUT,            CMainFrame::OnZoomOut)
    EVT_MENU(ID_ZOOMNORMAL,         CMainFrame::OnZoomNormal)
END_EVENT_TABLE()

// My frame constructor
CMainFrame::CMainFrame(
    int screenWidth,
    int screenHeight
    ) : wxFrame(
        NULL, 
        wxID_ANY, 
        LOCALIZED_GENERAL_PRODUCTNAME,
        wxDefaultPosition,
        wxSize(420, 300),
        wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE),
      m_FmsLogoIcon(NULL),
      m_Screen(NULL),
      m_Commander(NULL),
      m_RealCommander(NULL),
      m_StatusDialog(NULL),
      m_SetPenSizeDialog(NULL),
      m_Splitter(NULL),
      m_CommanderIsDocked(false),
      m_IsNewFile(true),
      m_SetPenColorDialog(NULL),
      m_SetFloodColorDialog(NULL),
      m_SetScreenColorDialog(NULL)
{
    m_FileName[0] = '\0';

#if wxUSE_STATUSBAR
    CreateStatusBar(2);
#endif // wxUSE_STATUSBAR

    //
    // Construct the main menu
    //
    static const MENUITEM fileMenuItems[] = {
        {LOCALIZED_FILE_NEW,    ID_FILENEW},
        {LOCALIZED_FILE_LOAD,   ID_FILELOAD},
        {LOCALIZED_FILE_OPEN,   ID_FILEOPEN},
        {LOCALIZED_FILE_SAVE,   ID_FILESAVE},
        {LOCALIZED_FILE_SAVEAS, ID_FILESAVEAS},
        {0},
        {LOCALIZED_FILE_EDIT,   ID_FILEEDIT},
        {LOCALIZED_FILE_ERASE,  ID_FILEERASE},
        {0},
        {LOCALIZED_FILE_EXIT,   ID_EXIT},
    };

    static const MENUITEM bitmapMenuItems[] = {
        {LOCALIZED_BITMAP_NEW,           ID_BITMAPNEW},
        {LOCALIZED_BITMAP_LOAD,          ID_BITMAPOPEN},
        {LOCALIZED_BITMAP_SAVE,          ID_BITMAPSAVE},
        {LOCALIZED_BITMAP_SAVEAS,        ID_BITMAPSAVEAS},
        {0},
        {LOCALIZED_BITMAP_PRINT,         ID_BITMAPPRINT},
        {LOCALIZED_BITMAP_PRINTERSETUP,  ID_BITMAPPRINTERSETUP},
        {0},
        {LOCALIZED_BITMAP_ACTIVEAREA,    ID_BITMAPPRINTERAREA},
    };

    static const MENUITEM setMenuItems[] = {
        {LOCALIZED_SET_PENSIZE,       ID_SETPENSIZE},
        {0},
        {LOCALIZED_SET_LABELFONT,     ID_SETLABELFONT},
        {LOCALIZED_SET_COMMANDERFONT, ID_SETCOMMANDERFONT},
        {0},
        {LOCALIZED_SET_PENCOLOR,      ID_SETPENCOLOR},
        {LOCALIZED_SET_FLOODCOLOR,    ID_SETFLOODCOLOR},
        {LOCALIZED_SET_SCREENCOLOR,   ID_SETSCREENCOLOR},
    };

    static const MENUITEM zoomMenuItems[] = {
        {LOCALIZED_ZOOM_IN,     ID_ZOOMIN},
        {LOCALIZED_ZOOM_OUT,    ID_ZOOMOUT},
        {LOCALIZED_ZOOM_NORMAL, ID_ZOOMNORMAL},
    };
 
    static const MENUITEM helpMenuItems[] = {
        {LOCALIZED_HELP_INDEX,         ID_HELP},
#if LOCALE!=1033
        // options for translating to/from English
        {LOCALIZED_HELP_LANGTOENGLISH, ID_HELPLANGTOENGLISH},
        {LOCALIZED_HELP_ENGLISHTOLANG, ID_HELPENGLISHTOLANG},
#endif
        {0},
        {LOCALIZED_HELP_TUTORIAL,      ID_HELPTUTORIAL},
        {LOCALIZED_HELP_DEMO,          ID_HELPDEMO},
        {LOCALIZED_HELP_EXAMPLE,       ID_HELPEXAMPLES},
        {LOCALIZED_HELP_RELEASENOTES,  ID_HELPRELEASENOTES},
        {0},
        {LOCALIZED_HELP_ABOUTFMSLOGO,  ID_HELPABOUT},
        {LOCALIZED_HELP_MS,            ID_HELPABOUTMS},
    };

    // Make a menubar
    wxMenuBar * mainMenu = new wxMenuBar;

    AppendChildMenu(mainMenu, LOCALIZED_FILE,   fileMenuItems,   ARRAYSIZE(fileMenuItems));
    AppendChildMenu(mainMenu, LOCALIZED_BITMAP, bitmapMenuItems, ARRAYSIZE(bitmapMenuItems));
    AppendChildMenu(mainMenu, LOCALIZED_SET,    setMenuItems,    ARRAYSIZE(setMenuItems));
    AppendChildMenu(mainMenu, LOCALIZED_ZOOM,   zoomMenuItems,   ARRAYSIZE(zoomMenuItems));
    AppendChildMenu(mainMenu, LOCALIZED_HELP,   helpMenuItems,   ARRAYSIZE(helpMenuItems));

    SetMenuBar(mainMenu);

    // Add the splitter to separate the screen from the commander
    m_Splitter = new MainSplitterWindow(this);

    m_Splitter->SetSashGravity(1.0);

    m_Screen = new CScreen(m_Splitter, screenWidth, screenHeight);

    m_RealCommander = new CCommander(m_Splitter);
    m_Commander = m_RealCommander;

    m_Screen->Show(true);
    m_Commander->Show(true);
    m_Splitter->SplitHorizontally(m_Screen, m_Commander);
    m_CommanderIsDocked = true;

#if 0
    wxAcceleratorEntry entries[1];
    entries[0].Set(0,  WXK_F1, ID_HELP);
    wxAcceleratorTable accel(ARRAYSIZE(entries), entries);
    SetAcceleratorTable(accel);
#endif

#if wxUSE_STATUSBAR
    SetStatusText(_T("Min pane size = 0"), 1);
#endif // wxUSE_STATUSBAR

    m_FmsLogoIcon = new wxIcon(fmslogo_16x16_xpm);
    SetIcon(*m_FmsLogoIcon);

    // init the pens based on the color
    UpdateNormalPen(GetPenStateForSelectedTurtle().Width, pcolor);
    UpdateErasePen(GetPenStateForSelectedTurtle().Width,  scolor);

    // it's show time for our little friend
    draw_turtle(true);
}

CMainFrame::~CMainFrame()
{
    delete m_FmsLogoIcon;
}


void CMainFrame::UndockCommanderWindow()
{
    if (m_CommanderIsDocked)
    {
        CCommanderDialog * newCommander = new CCommanderDialog(this);
#if 0
        // TODO: copy over the content/state of the dialog
        newCommandWindow->Duplicate(m_CommandWindow);
#endif

#if 0
        if (bFixed)
        {
            // The user requested that we never change the size of the drawing surface,
            // so we must shrink the main window to hold just the screen.
            TRect screenWindowRect;
            screenWindowRect.SetWH(
                0,
                0,
                Attr.W,
                Attr.H - CommandWindow->GetWindowRect().Height() - PaneSplitterWindow->GetSplitterWidth());

            SetWindowPos(
                NULL,
                screenWindowRect,
                SWP_NOZORDER | SWP_NOMOVE | SWP_NOCOPYBITS);
        }

#endif 
        m_Splitter->Unsplit(m_Commander);


        // commit to the new commander
        m_Commander->Destroy();
        m_Commander     = newCommander;
        m_RealCommander = newCommander->GetCommander();
        m_Commander->Show();

#if 0
        CommandWindow->Editbox.SetFocus();
#endif
        m_CommanderIsDocked = false;
    }
}

void CMainFrame::DockCommanderWindow()
{
    if (!m_CommanderIsDocked) 
    {
        CCommander * newCommander = new CCommander(m_Splitter);

#ifdef __WXMSW__ // utils.cpp only builds on Windows

        // restore the commander window's height
        int commanderWindowX      = 0;
        int commanderWindowY      = 0;
        int commanderWindowWidth  = 0;
        int commanderWindowHeight = DEFAULT_COMMANDER_HEIGHT;
        GetConfigurationQuadruple(
            "Commander",
            &commanderWindowX,
            &commanderWindowY,
            &commanderWindowWidth,
            &commanderWindowHeight);

        // sanity-check the input
        commanderWindowHeight = std::max(commanderWindowHeight, MIN_COMMANDER_HEIGHT);
#else
        int commanderWindowHeight = MIN_COMMANDER_HEIGHT;
#endif

#if 0
        if (bFixed)
        {
            // The user requested that we never change the size of the drawing surface,
            // so we must grow the main window to hold the commander window.

            TRect originalWindowRect;
            originalWindowRect.SetWH(
                Attr.X,
                Attr.Y,
                Attr.W,
                Attr.H);

            // grow the main window to hold the splitter and the commander
            const int totalHeight =
                originalWindowRect.Height() +
                PaneSplitterWindow->GetSplitterWidth() +
                commanderWindowHeight;
         
            const TRect newWindowRect(
                originalWindowRect.Left(),
                originalWindowRect.Top(),
                originalWindowRect.Right(),
                originalWindowRect.Top() + totalHeight);

            SetWindowPos(
                NULL,
                newWindowRect,
                SWP_NOZORDER | SWP_NOMOVE | SWP_NOCOPYBITS);
        }
#endif

#if 0  // is this necessary with wxWindows?

        // HACK: Hide the current commander window before adding
        // the new one to the splitter.  This somehow forces a 
        // refresh of the entire screen window.  Without it, the
        // scrollbars sometimes don't show up (I don't know why).
        // This is a hack because I'm sure there's a more direct
        // way to force the scrollbars to show up.
        //
        // See bug #1372200 for details.
        CommandWindow->Show(SW_HIDE);
#endif


        int clientWidth;
        int clientHeight;
        GetClientSize(&clientWidth, &clientHeight);

        int splitterWidth = m_Splitter->GetSashSize();

        int splitterPosition = clientHeight - commanderWindowHeight - splitterWidth;

        // the splitter can't get too small
        if (splitterPosition < 20)
        {
            splitterPosition = 20;
        }

        m_Splitter->SetSashPosition(splitterPosition);

        m_Splitter->SplitHorizontally(m_Screen, newCommander);

#if 0
        // TODO copy the history
        newCommandWindow->Duplicate(*CommandWindow);
#endif

#if 0
        // redraw the entire screen window
        ScreenWindow->Invalidate(true);
        newCommandWindow->Invalidate(true);
#endif

        // commit to the docked commander
        m_Commander->Close(true);
        m_Commander     = newCommander;
        m_RealCommander = newCommander->GetCommander();
        m_Commander->Show();

#if 0
        CommandWindow->Editbox.SetFocus();
#endif

        m_CommanderIsDocked = true;
    }
}

CWorkspaceEditor * CMainFrame::GetWorkspaceEditor()
{
    if (m_Editors.empty())
    {
        return NULL;
    }

    // return any of the editors (doesn't matter which one)
    return (*m_Editors.begin()).first;
}

CWorkspaceEditor *
CMainFrame::CreateWorkspaceEditor(
    const wxString & FileName,
    NODE           * EditArguments,
    bool             CheckForErrors
    )
{
    CWorkspaceEditor * editor = new CWorkspaceEditor(
        this,
        LOCALIZED_EDITOR_TITLE,
        FileName,
        EditArguments,
        CheckForErrors);

#if 0
    // Construct the default coordinates of the editor's window
    // to be about 1/2 of the working area and placed in the center.
    int maxWidth;
    int maxHeight;
    GetWorkingAreaDimensions(maxWidth, maxHeight);

    int x = (int) (maxWidth * 0.25);
    int y = (int) (maxHeight * 0.25);
    int w = (int) (maxWidth * 0.75);
    int h = (int) (maxHeight * ScreenSz * 0.75);

    GetConfigurationQuadruple("Editor", &x, &y, &w, &h); 
    checkwindow(&x, &y, &w, &h);

    // now set them 
    editor->Attr.Style = WS_VISIBLE | WS_POPUPWINDOW | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
    editor->Editor->Attr.Style |= ES_NOHIDESEL;

    // let user edit
    editor->Create();

    // force a resize to fix RichEdit ScrollBar not appearing automatically
    editor->SetWindowPos(0, x, y, w + 1, h, SWP_NOZORDER);
    editor->SetWindowPos(0, x, y, w, h, SWP_NOZORDER);

    if (args != NULL || check_for_errors)
    {
        // retitle without filename
        editor->SetWindowText(LOCALIZED_EDITOR_TITLE);
    }
#endif

    // add this editor the the list of known editors
    m_Editors.insert(std::pair<CWorkspaceEditor*,CWorkspaceEditor*>(editor,editor));

    return editor;
}

void
CMainFrame::PopupEditor(
    const wxString & FileName,
    NODE           * EditArguments,
    bool             CheckForErrors
    )
{
    CWorkspaceEditor * editor = CreateWorkspaceEditor(
        FileName,
        EditArguments,
        CheckForErrors);

    if (EditArguments != NIL || CheckForErrors)
    {
        // If an error occured "force" a change so that we're
        // still in "dirty" state.
        if (editor->IsErrorDetected())
        {
            //TODO: Implement this
            //editor->ReopenAfterError();
        }
    }

    // TODO: m_GiveFocusToEditbox = false;
}

static
void
CreateTemplateLogoFileForEditor(
    const wxString & FileName,
    NODE           * EditArguments
    )
{
    // TODO: Use wxWidgets class for File I/O
    FILE* logoFile = fopen(FileName.c_str(), "w");
    if (logoFile != NULL)
    {
        if (EditArguments != NIL)
        {
            // Arguments were given to EDIT and the workspace was empty.
            // So show a "TO" and "END" to help guide the user to their
            // next action.
            fprintf(logoFile, "%s\n", To.GetName());
            fprintf(logoFile, "%s\n", End.GetName());
        }
        else
        {
            // No arguments were passed to EDIT, so we opened
            // an empty workspace.
            fprintf(logoFile, "\n");
        }
    }

    fclose(logoFile);
}


int
CMainFrame::PopupEditorForFile(
    const wxString & FileName,
    NODE           * EditArguments
    )
{
    // If no file (or empty) create template
    // TODO: Use a wxWidgets class for the file I/O.
    FILE * logoFile = fopen(FileName, "r");
    if (logoFile != NULL)
    {
        // file exists.  check if it's empty.
        bool fileIsEmpty = getc(logoFile) == EOF;
        fclose(logoFile);

        if (fileIsEmpty)
        {
            CreateTemplateLogoFileForEditor(FileName, EditArguments);
        }
    }
    else
    {
        // file doesn't exist.  Create it.
        CreateTemplateLogoFileForEditor(FileName, EditArguments);
    }

    CFmsLogo::GetMainFrame()->PopupEditor(
        FileName,
        EditArguments,
        false);
    return 0;
}


void CMainFrame::CloseWorkspaceEditor(CWorkspaceEditor * Editor)
{
    m_Editors.erase(Editor);
}

CScreen * CMainFrame::GetScreen()
{
    return m_Screen;
}

CCommander * CMainFrame::GetCommander()
{
    return m_RealCommander;
}

// menu command handlers
void CMainFrame::OnQuit(wxCommandEvent& WXUNUSED(Event))
{
    CSaveBeforeExitDialog dlg(this);
    dlg.ShowModal();
    CSaveBeforeExitDialog::SAVEBEFOREEXIT code = dlg.GetExitCode();

    if (code != CSaveBeforeExitDialog::SAVEBEFOREEXIT_Cancel)
    {
        Close(true);
    }
}

// CONSIDER: move this to wrksp.c, since it has no coheasion
// with the UI.
static void EraseContentsOfWorkspace()
{
    NODE * workspace_contents;

    // erase the unburied contents of the workspace
    workspace_contents = cons_list(lcontents(NIL));
    lerase(workspace_contents);
    gcref(workspace_contents);

    // erase the buried contents of the workspace
    workspace_contents = cons_list(lburied(NIL));
    lerase(workspace_contents);
    gcref(workspace_contents);

    IsDirty = false;
}

void CMainFrame::OnFileNew(wxCommandEvent& WXUNUSED(Event))
{
    if (IsDirty)
    {
        // Warn the user that File-New will erase the contents 
        // of the workspace and give them a chance to cancel the
        // operation.
        if (wxMessageBox(
                LOCALIZED_FILENEWWILLERASEWORKSPACE,
                LOCALIZED_YOUHAVEUNSAVEDCHANGES,
                wxOK | wxCANCEL | wxICON_QUESTION,
                GetCommander()) == wxCANCEL)
        {
            return;
        }
    }

    // else start with a clean plate
    m_IsNewFile = true;
    EraseContentsOfWorkspace();
}

void
CMainFrame::InitializeOpenFileNameForLogoFiles(
    OPENFILENAME & OpenFileData
    )
{
    ZeroMemory(&OpenFileData, sizeof OpenFileData);
    OpenFileData.lStructSize       = sizeof OpenFileData;
    OpenFileData.hwndOwner         = static_cast<HWND>(GetHandle());
    OpenFileData.hInstance         = NULL;
    OpenFileData.lpstrFilter       = LOCALIZED_FILEFILTER_LOGO;
    OpenFileData.lpstrCustomFilter = NULL;
    OpenFileData.nMaxCustFilter    = 0;
    OpenFileData.nFilterIndex      = 0;
    OpenFileData.lpstrFile         = m_FileName;
    OpenFileData.nMaxFile          = ARRAYSIZE(m_FileName);
    OpenFileData.lpstrFileTitle    = NULL;
    OpenFileData.nMaxFileTitle     = 0;
    OpenFileData.lpstrInitialDir   = NULL;
    OpenFileData.lpstrTitle        = NULL;
    OpenFileData.Flags             = OFN_HIDEREADONLY | OFN_EXPLORER;
    OpenFileData.nFileOffset       = 0;
    OpenFileData.nFileExtension    = 0;
    OpenFileData.lpstrDefExt       = LOCALIZED_LOGO_FILE_EXTENSION;
    OpenFileData.lCustData         = 0;
    OpenFileData.lpfnHook          = NULL;
    OpenFileData.lpTemplateName    = NULL;
}

void CMainFrame::OnFileLoad(wxCommandEvent& WXUNUSED(Event))
{
    if (IsDirty)
    {
        // Warn the user that File-Load may erase the contents 
        // of the workspace and give them a chance to cancel the
        // operation.
        if (wxMessageBox(
                LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE,
                LOCALIZED_YOUHAVEUNSAVEDCHANGES,
                wxOK | wxCANCEL | wxICON_QUESTION,
                GetCommander()) == wxCANCEL)
        {
            return;
        }
    }

    // show the user a file-picker dialog
    // TODO: switch to use wxFileSelector
    OPENFILENAME openFileName;
    InitializeOpenFileNameForLogoFiles(openFileName);
    openFileName.Flags |= OFN_FILEMUSTEXIST;

    // if user found a file then try to load it
    if (GetOpenFileName(&openFileName))
    {
        m_IsNewFile = false;

        start_execution();

        bool isOk = fileload(m_FileName);
        if (!isOk) 
        {
            err_logo(
                FILE_ERROR, 
                make_static_strnode(LOCALIZED_ERROR_FILESYSTEM_CANTOPEN));
        }

        // handle any error that may have occured
        process_special_conditions();

        stop_execution();
    }
}

void CMainFrame::OnFileOpen(wxCommandEvent& WXUNUSED(Event))
{
    if (IsDirty)
    {
        // Warn the user that File-Open will erase the contents 
        // of the workspace and give them a chance to cancel the
        // operation.
        if (wxMessageBox(
                LOCALIZED_FILEOPENWILLERASEWORKSPACE,
                LOCALIZED_YOUHAVEUNSAVEDCHANGES,
                wxOK | wxCANCEL | wxICON_QUESTION,
                GetCommander()) == wxCANCEL)
        {
            return;
        }
    }

    // show the user a file-picker dialog
    OPENFILENAME openFileName;
    InitializeOpenFileNameForLogoFiles(openFileName);
    openFileName.Flags |= OFN_FILEMUSTEXIST;

    // if user found a file then try to open it
    if (GetOpenFileName(&openFileName))
    {
        // start with a clean plate
        m_IsNewFile = false;

        // erase the contents of the workspace
        EraseContentsOfWorkspace();

        start_execution();

        bool isOk = fileload(m_FileName);
        if (!isOk) 
        {
            err_logo(
                FILE_ERROR, 
                make_static_strnode(LOCALIZED_ERROR_FILESYSTEM_CANTOPEN));
        }

        // handle any error that may have occured
        process_special_conditions();

        stop_execution();
    }
}

// Displays a warning if the workspace is empty
// and therefore if saving it would save an empty
// file, which is probably not what the user expects.
//
// returns true, if we should continue to save the workspace.
// returns false, if we should not save the workspace.
bool CMainFrame::WarnIfSavingEmptyWorkspace()
{
    // Check if there's something in the workspace that
    // isn't buried (which would be saved).
    if (!something_is_unburied())
    {
        // TODO: use wxMessageBox if it supports default buttons
        if (MessageBox(
                static_cast<HWND>(GetHandle()),
                LOCALIZED_EMPTYWORKSPACE_MESSAGE,
                LOCALIZED_EMPTYWORKSPACE_TITLE,
                MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
        {
            return false;
        }
    }

    return true;
}

// Prompts the user for the name of the file to save
// the contents as, then saves the file.
//
// Returns "true" if the user saves the file.
// Returns "false" if the user cancels the save or if the 
// file couldn't be saved for other reasons.
bool CMainFrame::SaveFileAs()
{
    // if new the nulify File name
    if (m_IsNewFile)
    {
        m_FileName[0] = '\0';
    }

    // Get file name from user and then save the file
    OPENFILENAME openFileName;
    InitializeOpenFileNameForLogoFiles(openFileName);
    openFileName.Flags |= OFN_OVERWRITEPROMPT;

    bool isOk;
    if (GetSaveFileName(&openFileName))
    {
        m_IsNewFile = false;
        isOk = SaveFile();
    }
    else
    {
        isOk = false;
    }

    return isOk;
}

bool CMainFrame::SaveFile()
{
    filesave(m_FileName);

    // handle any error that may have occured
    process_special_conditions();

    // BUG: don't assume the file was saved
    return true;
}


bool CMainFrame::FileSave()
{
    bool isOk;

    if (m_IsNewFile)
    {
        // The file has never been saved, so we don't know
        // what file we should save it to.
        // Ask the user with a "Save As" dialog.
        isOk = SaveFileAs();
    }
    else
    {
        // Save the file
        isOk = SaveFile();
    }

    return isOk;
}

void CMainFrame::OnFileSave(wxCommandEvent& WXUNUSED(Event))
{
    if (!WarnIfSavingEmptyWorkspace())
    {
        return;
    }

    FileSave();
}

void CMainFrame::OnFileSaveAs(wxCommandEvent& WXUNUSED(Event))
{
    if (!WarnIfSavingEmptyWorkspace())
    {
        return;
    }

    SaveFileAs();
}

void CMainFrame::OnEditProcedure(wxCommandEvent& WXUNUSED(Event))
{
    CEditProcedureDialog dlg(this);
    dlg.ShowModal();
}

void CMainFrame::OnEraseProcedure(wxCommandEvent& WXUNUSED(Event))
{
    CEraseProcedureDialog dlg(this);
    dlg.ShowModal();
}

void CMainFrame::OnSetPenSize(wxCommandEvent& WXUNUSED(Event))
{
    if (m_SetPenSizeDialog == NULL)
    {
        // TODO: read this from the Logo engine
        const int initialSize = 2;

        m_SetPenSizeDialog = new CSetPenSize(
            this,
            initialSize,
            m_SetPenSizeDialog);

        m_SetPenSizeDialog->Show();
    }
    else
    {
        m_SetPenSizeDialog->SetFocus();
    }
}

void
CMainFrame::SetColorHelper(
    CSetColor * &   SetColorDialog,
    const char  *   DialogTitle,
    const wxColor & InitialColor
    )
{
    if (SetColorDialog == NULL)
    {
        SetColorDialog = new CSetColor(
            this,
            DialogTitle,
            InitialColor,
            SetColorDialog);

        SetColorDialog->Show();
    }
    else
    {
        SetColorDialog->SetFocus();
    }
}

void CMainFrame::OnSetPenColor(wxCommandEvent& WXUNUSED(Event))
{
    SetColorHelper(
        m_SetPenColorDialog,
        LOCALIZED_SETCOLOR_PENCOLOR,
        wxColor(0xFF, 0x00, 0x00)); // TODO: read this from the Logo engine
}

void CMainFrame::OnSetFloodColor(wxCommandEvent& WXUNUSED(Event))
{
    SetColorHelper(
        m_SetFloodColorDialog,
        LOCALIZED_SETCOLOR_FLOODCOLOR,
        wxColor(0x00, 0x00, 0xFF)); // TODO: read this from the Logo engine
}

void CMainFrame::OnSetScreenColor(wxCommandEvent& WXUNUSED(Event))
{
    SetColorHelper(
        m_SetScreenColorDialog,
        LOCALIZED_SETCOLOR_SCREENCOLOR,
        wxColor(0x00, 0xFF, 0x00)); // TODO: read this from the Logo engine
}

void CMainFrame::ShowStatus()
{
    // create a new status dialog, if necessary
    if (!StatusDialogIsShowing())
    {
        m_StatusDialog = new CStatusDialog(this);
        m_StatusDialog->Show();
    }
}

void CMainFrame::HideStatus()
{
    // destroy the status dialog
    if (StatusDialogIsShowing())
    {
        m_StatusDialog->Close();
        m_StatusDialog = NULL;
    }
}

bool CMainFrame::StatusDialogIsShowing()
{
    return m_StatusDialog != NULL;
}

void CMainFrame::OnSetActiveArea(wxCommandEvent& WXUNUSED(Event))
{
    CSetActiveArea dlg(this);
    dlg.ShowModal();
}

void CMainFrame::OnSetLabelFont(wxCommandEvent& WXUNUSED(Event))
{
    wxFontDialog fontChooser;
    fontChooser.GetFontData().SetInitialFont(g_LabelFont);

    int rval = fontChooser.ShowModal();
    if (rval == wxID_OK)
    {
        // the user selected a new font

        // set the new label font now, just in case running
        // the instruction doesn't wor for some reason.
        g_LabelFont = fontChooser.GetFontData().GetChosenFont();

#ifdef __WXMSW__ 

        // Get the LOGFONT struct from the wxFont
        const struct wxNativeFontInfo * fontInfo = g_LabelFont.GetNativeFontInfo();
        if (fontInfo != NULL)
        {
            const class wxNativeFontInfo * nativeFontInfo = (class wxNativeFontInfo*)fontInfo;

            // commit to the new font
            char setlabelfont[MAX_BUFFER_SIZE];

            NormalizeCaseForDisplay(
                setlabelfont,
                LOCALIZED_ALTERNATE_SETLABELFONT,
                STRINGLENGTH(LOCALIZED_ALTERNATE_SETLABELFONT));

            char logoInstruction[512];
            sprintf(
                logoInstruction,
                "%s [[%s] %ld %ld %ld %ld %d %d %d %d %d %d %d %d]",
                setlabelfont,
                nativeFontInfo->lf.lfFaceName,
                nativeFontInfo->lf.lfHeight,
                nativeFontInfo->lf.lfWidth,
                nativeFontInfo->lf.lfOrientation,
                nativeFontInfo->lf.lfWeight,
                nativeFontInfo->lf.lfItalic,
                nativeFontInfo->lf.lfUnderline,
                nativeFontInfo->lf.lfStrikeOut,
                nativeFontInfo->lf.lfCharSet,
                nativeFontInfo->lf.lfOutPrecision,
                nativeFontInfo->lf.lfClipPrecision,
                nativeFontInfo->lf.lfQuality,
                nativeFontInfo->lf.lfPitchAndFamily);

            RunLogoInstructionFromGui(logoInstruction);
        }
#endif
    }
}

void CMainFrame::OnZoomIn(wxCommandEvent& WXUNUSED(Event))
{
    UndockCommanderWindow();
}

void CMainFrame::OnZoomOut(wxCommandEvent& WXUNUSED(Event))
{
    DockCommanderWindow();
}

void CMainFrame::OnZoomNormal(wxCommandEvent& WXUNUSED(Event))
{
    // For now, show the "To" mini-editor as a test hook
    CMiniEditor dlg(this, "TO SQUARE :length");
    dlg.ShowModal();
}

void CMainFrame::OnHelp(wxCommandEvent& WXUNUSED(Event))
{
    do_help(NULL);
}

void CMainFrame::OnExamples(wxCommandEvent& WXUNUSED(Event))
{
    // For now, doodle something on the screen so that we can test
    // saving the screen as a bitmap.
    wxMemoryDC & memoryDeviceContext = m_Screen->GetMemoryDeviceContext();

    memoryDeviceContext.SetPen(*wxBLACK_PEN);
    memoryDeviceContext.DrawLine(0, 0, 100, 200);

    memoryDeviceContext.SetBackgroundMode(wxTRANSPARENT);
    memoryDeviceContext.DrawText(_T("Testing"), 50, 50);

    memoryDeviceContext.SetPen(*wxRED_PEN);
    memoryDeviceContext.SetBrush(*wxGREEN_BRUSH);
    memoryDeviceContext.DrawRectangle(120, 120, 100, 80);
    
    // Tell wxWidgets to call CScreen::OnDraw at the next opportunity.
    m_Screen->Refresh(false);
}

void CMainFrame::OnAboutFmsLogo(wxCommandEvent& WXUNUSED(Event))
{
    // show the "About FMSLogo" dialog box
    CAboutFmsLogo dlg(this);
    dlg.ShowModal();
}

void CMainFrame::OnAboutMultipleSclerosis(wxCommandEvent& WXUNUSED(Event))
{
    // show the "About FMS" dialog box
    CAboutMultipleSclerosis dlg(this);
    dlg.ShowModal();
}



// ----------------------------------------------------------------------------
// MainSplitterWindow
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(MainSplitterWindow, wxSplitterWindow)
    EVT_SPLITTER_SASH_POS_CHANGED(wxID_ANY, MainSplitterWindow::OnPositionChanged)
    EVT_SPLITTER_SASH_POS_CHANGING(wxID_ANY, MainSplitterWindow::OnPositionChanging)

    EVT_SPLITTER_DCLICK(wxID_ANY, MainSplitterWindow::OnDClick)

    EVT_SPLITTER_UNSPLIT(wxID_ANY, MainSplitterWindow::OnUnsplitEvent)
END_EVENT_TABLE()

MainSplitterWindow::MainSplitterWindow(
    wxFrame *Parent
    ) : wxSplitterWindow(
        Parent,
        wxID_ANY,
        wxDefaultPosition,
        wxDefaultSize,
        wxSP_3D | wxSP_LIVE_UPDATE | wxCLIP_CHILDREN /* | wxSP_NO_XP_THEME */)
{
    SetMinimumPaneSize(MIN_COMMANDER_HEIGHT);

    m_frame = Parent;
}

void MainSplitterWindow::OnPositionChanged(wxSplitterEvent& event)
{
    wxLogStatus(
        m_frame,
        "Position has changed, now = %d (or %d)",
        event.GetSashPosition(),
        GetSashPosition());

    event.Skip();
}

void MainSplitterWindow::OnPositionChanging(wxSplitterEvent& event)
{
    wxLogStatus(
        m_frame,
        "Position is changing, now = %d (or %d)",
        event.GetSashPosition(),
        GetSashPosition());

    event.Skip();
}

void MainSplitterWindow::OnDClick(wxSplitterEvent& Event)
{
#if wxUSE_STATUSBAR
    m_frame->SetStatusText("Splitter double clicked", 1);
#endif // wxUSE_STATUSBAR

    Event.Skip();
}

void MainSplitterWindow::OnUnsplitEvent(wxSplitterEvent& Event)
{
#if wxUSE_STATUSBAR
    m_frame->SetStatusText("Splitter unsplit", 1);
#endif // wxUSE_STATUSBAR

    Event.Skip();
}
