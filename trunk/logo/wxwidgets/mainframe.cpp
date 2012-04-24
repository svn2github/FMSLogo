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

class MySplitterWindow : public wxSplitterWindow
{
public:
    MySplitterWindow(wxFrame *parent);

    // event handlers
    void OnPositionChanged(wxSplitterEvent& event);
    void OnPositionChanging(wxSplitterEvent& event);
    void OnDClick(wxSplitterEvent& event);
    void OnUnsplitEvent(wxSplitterEvent& event);

private:
    wxFrame *m_frame;

    DECLARE_EVENT_TABLE()
    DECLARE_NO_COPY_CLASS(MySplitterWindow)
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
    EVT_MENU(ID_FILEEDIT,           CMainFrame::EditProcedure)
    EVT_MENU(ID_FILEERASE,          CMainFrame::EraseProcedure)
    EVT_MENU(ID_SETPENSIZE,         CMainFrame::SetPenSize)
    EVT_MENU(ID_BITMAPPRINTERAREA,  CMainFrame::SetActiveArea)
    EVT_MENU(ID_SETLABELFONT,       CMainFrame::SetLabelFont)
    EVT_MENU(ID_SETPENCOLOR,        CMainFrame::SetPenColor)
    EVT_MENU(ID_SETSCREENCOLOR,     CMainFrame::SetScreenColor)
    EVT_MENU(ID_SETFLOODCOLOR,      CMainFrame::SetFloodColor)
    EVT_MENU(ID_HELP,               CMainFrame::Help)
    EVT_MENU(ID_HELPEXAMPLES,       CMainFrame::Examples)
    EVT_MENU(ID_HELPABOUT,          CMainFrame::AboutFmsLogo)
    EVT_MENU(ID_HELPABOUTMS,        CMainFrame::AboutMultipleSclerosis)
    EVT_MENU(ID_ZOOMIN,             CMainFrame::ZoomIn)
    EVT_MENU(ID_ZOOMOUT,            CMainFrame::ZoomOut)
    EVT_MENU(ID_ZOOMNORMAL,         CMainFrame::ZoomNormal)
    EVT_MENU(ID_EXIT,               CMainFrame::Quit)
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
      m_SetPenColorDialog(NULL),
      m_SetFloodColorDialog(NULL),
      m_SetScreenColorDialog(NULL)
{
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
    m_Splitter = new MySplitterWindow(this);

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


// menu command handlers
void CMainFrame::Quit(wxCommandEvent& WXUNUSED(event) )
{
    CSaveBeforeExitDialog dlg(this);
    dlg.ShowModal();
    CSaveBeforeExitDialog::SAVEBEFOREEXIT code = dlg.GetExitCode();

    if (code != CSaveBeforeExitDialog::SAVEBEFOREEXIT_Cancel)
    {
        Close(true);
    }
}

CScreen * CMainFrame::GetScreen()
{
    return m_Screen;
}

CCommander * CMainFrame::GetCommander()
{
    return m_RealCommander;
}

void CMainFrame::EditProcedure(wxCommandEvent& WXUNUSED(event) )
{
    CEditProcedureDialog dlg(this);
    dlg.ShowModal();
}

void CMainFrame::EraseProcedure(wxCommandEvent& WXUNUSED(event) )
{
    CEraseProcedureDialog dlg(this);
    dlg.ShowModal();
}

void CMainFrame::SetPenSize(wxCommandEvent& WXUNUSED(event) )
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

void CMainFrame::SetPenColor(wxCommandEvent& WXUNUSED(event) )
{
    SetColorHelper(
        m_SetPenColorDialog,
        LOCALIZED_SETCOLOR_PENCOLOR,
        wxColor(0xFF, 0x00, 0x00)); // TODO: read this from the Logo engine
}

void CMainFrame::SetFloodColor(wxCommandEvent& WXUNUSED(event) )
{
    SetColorHelper(
        m_SetFloodColorDialog,
        LOCALIZED_SETCOLOR_FLOODCOLOR,
        wxColor(0x00, 0x00, 0xFF)); // TODO: read this from the Logo engine
}

void CMainFrame::SetScreenColor(wxCommandEvent& WXUNUSED(event) )
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

void CMainFrame::SetActiveArea(wxCommandEvent& WXUNUSED(Event))
{
    CSetActiveArea dlg(this);
    dlg.ShowModal();
}

void CMainFrame::SetLabelFont(wxCommandEvent& WXUNUSED(Event))
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

void CMainFrame::ZoomIn(wxCommandEvent& WXUNUSED(event) )
{
    UndockCommanderWindow();
}

void CMainFrame::ZoomOut(wxCommandEvent& WXUNUSED(event) )
{
    DockCommanderWindow();
}

void CMainFrame::ZoomNormal(wxCommandEvent& WXUNUSED(event) )
{
    // For now, show the "To" mini-editor as a test hook
    CMiniEditor dlg(this, "TO SQUARE :length");
    dlg.ShowModal();
}

void CMainFrame::Help(wxCommandEvent& WXUNUSED(event) )
{
    do_help(NULL);
}

void CMainFrame::Examples(wxCommandEvent& WXUNUSED(Event))
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

void CMainFrame::AboutFmsLogo(wxCommandEvent& WXUNUSED(event) )
{
    // show the "About FMSLogo" dialog box
    CAboutFmsLogo dlg(this);
    dlg.ShowModal();
}

void CMainFrame::AboutMultipleSclerosis(wxCommandEvent& WXUNUSED(event) )
{
    // show the "About FMS" dialog box
    CAboutMultipleSclerosis dlg(this);
    dlg.ShowModal();
}



// ----------------------------------------------------------------------------
// MySplitterWindow
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(MySplitterWindow, wxSplitterWindow)
    EVT_SPLITTER_SASH_POS_CHANGED(wxID_ANY, MySplitterWindow::OnPositionChanged)
    EVT_SPLITTER_SASH_POS_CHANGING(wxID_ANY, MySplitterWindow::OnPositionChanging)

    EVT_SPLITTER_DCLICK(wxID_ANY, MySplitterWindow::OnDClick)

    EVT_SPLITTER_UNSPLIT(wxID_ANY, MySplitterWindow::OnUnsplitEvent)
END_EVENT_TABLE()

MySplitterWindow::MySplitterWindow(wxFrame *parent)
                : wxSplitterWindow(parent, wxID_ANY,
                                   wxDefaultPosition, wxDefaultSize,
                                   wxSP_3D | wxSP_LIVE_UPDATE |
                                   wxCLIP_CHILDREN /* | wxSP_NO_XP_THEME */ )
{
    SetMinimumPaneSize(MIN_COMMANDER_HEIGHT);

    m_frame = parent;
}

void MySplitterWindow::OnPositionChanged(wxSplitterEvent& event)
{
    wxLogStatus(m_frame, _T("Position has changed, now = %d (or %d)"),
                event.GetSashPosition(), GetSashPosition());

    event.Skip();
}

void MySplitterWindow::OnPositionChanging(wxSplitterEvent& event)
{
    wxLogStatus(m_frame, _T("Position is changing, now = %d (or %d)"),
                event.GetSashPosition(), GetSashPosition());

    event.Skip();
}

void MySplitterWindow::OnDClick(wxSplitterEvent& event)
{
#if wxUSE_STATUSBAR
    m_frame->SetStatusText(_T("Splitter double clicked"), 1);
#endif // wxUSE_STATUSBAR

    event.Skip();
}

void MySplitterWindow::OnUnsplitEvent(wxSplitterEvent& event)
{
#if wxUSE_STATUSBAR
    m_frame->SetStatusText(_T("Splitter unsplit"), 1);
#endif // wxUSE_STATUSBAR

    event.Skip();
}

