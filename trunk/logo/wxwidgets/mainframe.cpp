// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/log.h>

    #include <wx/app.h>
    #include <wx/frame.h>

    #include <wx/scrolwin.h>
    #include <wx/menu.h>
    #include <wx/msgdlg.h>

    #include <wx/splitter.h>
    #include <wx/dcmirror.h>
    #include <wx/fontdlg.h>
    #include <wx/printdlg.h>

    #include <wx/dcmemory.h>

    #include <wx/textdlg.h>  // for wxGetTextFromUser
    #include <wx/fontutil.h> // for wxNativeFontInfo
#endif

#include <algorithm>

#include "guiutils.h"
#include "commander.h"
#include "activearea.h"
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
#include "mainwind.h" // for checkwindow()
#include "wrksp.h"
#include "eval.h"
#include "fileswnd.h"
#include "graphwin.h"
#include "mmwind.h" // for uninitialize_timers()
#include "startup.h"
#include "fontutils.h"

// ----------------------------------------------------------------------------
// our classes
// ----------------------------------------------------------------------------

// TODO: move to separate file
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
// CMainFrame::CLogoPicturePrintout
// ----------------------------------------------------------------------------

CMainFrame::CLogoPicturePrintout::CLogoPicturePrintout(
    const wxString        & Title,
    wxWindow              & Screen,
    wxPageSetupDialogData & PageSetup
    ) :
    wxPrintout(Title),
    m_Screen(Screen),
    m_PageSetup(PageSetup)
{
}

bool
CMainFrame::CLogoPicturePrintout::OnPrintPage(
    int Page
    )
{
    // Must of rewrote this at least 26 times and it still does not
    // Work in some situations. This is just the "Paint" of printing.
    // See the print module for all the other stuff.
    wxDC * dc = GetDC();
    if (dc == NULL)
    {
        return false;
    }

    HDC PrintDC = static_cast<HDC>(dc->GetHDC());

    // do we even have a chance?
    if ((GetDeviceCaps(PrintDC, RASTERCAPS) & RC_STRETCHDIB) == 0)
    {
        // notify the user that the printer does not support scaling
        wxMessageBox(
            LOCALIZED_ERROR_PRINTERCANTSCALE, 
            LOCALIZED_ERROR,
            wxICON_ERROR);
        return false;
    }

    int printBitCount = GetDeviceCaps(PrintDC, BITSPIXEL);
    printBitCount *= GetDeviceCaps(PrintDC, PLANES);

    if (printBitCount == 1)
    {
        // This is a monochrome mono printer.
        // Let's let it try to dither a 256 grey scale image
        printBitCount = 8;
    }

    // Get screen bitCount
    wxClientDC * screenDeviceContext = new wxClientDC(&m_Screen);
    HDC screenDc = static_cast<HDC>(screenDeviceContext->GetHDC());

    int screenBitCount = GetDeviceCaps(screenDc, BITSPIXEL);
    screenBitCount *= GetDeviceCaps(screenDc, PLANES);

    // Don't bother creating a DIB with more colors than we have
    if (screenBitCount < printBitCount) 
    {
        printBitCount = screenBitCount;
    }

    // Round to nearest legal bitmap color depth
    if      (                        (printBitCount <  1)) printBitCount =  1;
    else if ((printBitCount >  1) && (printBitCount <  4)) printBitCount =  4;
    else if ((printBitCount >  4) && (printBitCount <  8)) printBitCount =  8;
    else if ((printBitCount >  8) && (printBitCount < 16)) printBitCount = 16;
    else if ((printBitCount > 16) && (printBitCount < 24)) printBitCount = 24;
    else if ((printBitCount > 24)                        ) printBitCount = 32;

    printBitCount = GetConfigurationInt("PrintColorDepth", printBitCount);

    size_t size;
    if (printBitCount <= 8)
    {
        size = sizeof(BITMAPINFOHEADER) + ((1 << printBitCount) * sizeof(RGBQUAD));
    }
    else
    {
        size = sizeof(BITMAPINFOHEADER);
    }

    BITMAPINFO * bitmapInfo = (BITMAPINFO *) new char[size];

    bitmapInfo->bmiHeader.biSize     = sizeof(BITMAPINFOHEADER);
    bitmapInfo->bmiHeader.biWidth    = BitMapWidth;
    bitmapInfo->bmiHeader.biHeight   = BitMapHeight;
    bitmapInfo->bmiHeader.biPlanes   = 1;
    bitmapInfo->bmiHeader.biBitCount = printBitCount;
    bitmapInfo->bmiHeader.biCompression = BI_RGB;
    bitmapInfo->bmiHeader.biSizeImage   = ((((bitmapInfo->bmiHeader.biWidth * bitmapInfo->bmiHeader.biBitCount) + 31) / 32) * 4) * bitmapInfo->bmiHeader.biHeight;
    bitmapInfo->bmiHeader.biXPelsPerMeter = 0;
    bitmapInfo->bmiHeader.biYPelsPerMeter = 0;
    bitmapInfo->bmiHeader.biClrUsed       = 0;
    bitmapInfo->bmiHeader.biClrImportant  = 0;

    // we don't need hour glass here because print module takes care of it 

    // allocate space for the raw DIB data
    unsigned char * bitsPtr = new unsigned char [bitmapInfo->bmiHeader.biSizeImage];
    memset(bitsPtr, 0x00, bitmapInfo->bmiHeader.biSizeImage);

    // get printer size per inch 
    int tempWidth  = GetDeviceCaps(PrintDC, LOGPIXELSX);
    int tempHeight = GetDeviceCaps(PrintDC, LOGPIXELSY);

    // if palette allocate it
    if (EnablePalette)
    {
        OldPalette = SelectPalette(screenDc, ThePalette, FALSE);
        RealizePalette(screenDc);
    }

    // set up an assured contrast ?
    SetTextColor(PrintDC, 0x00000000L);
    SetBkColor(PrintDC, 0x00ffffffL);

    bool isOk = true;

    int scanLines = GetDIBits(
        screenDc,
        MemoryBitMap,
        0,
        BitMapHeight,
        bitsPtr,
        bitmapInfo,
        DIB_RGB_COLORS);
    if (scanLines != 0)
    {
        // there is something to print.

        // print only the active area
        int status = StretchDIBits(
            PrintDC,
            0,
            0,
            (tempWidth  * (g_PrinterAreaXHigh - g_PrinterAreaXLow)) / g_PrinterAreaPixels,
            (tempHeight * (g_PrinterAreaYHigh - g_PrinterAreaYLow)) / g_PrinterAreaPixels,
            +g_PrinterAreaXLow + xoffset,
            BitMapHeight - (-g_PrinterAreaYLow + yoffset),
            g_PrinterAreaXHigh - g_PrinterAreaXLow,
            g_PrinterAreaYHigh - g_PrinterAreaYLow,
            bitsPtr,
            bitmapInfo,
            DIB_RGB_COLORS,
            SRCCOPY);
        if (status <= 0)
        {
            // TODO: message the last error into the current locale
            DWORD lastError = GetLastError();
            const wxString & message = wxString::Format(
                "%s\n%s: %lu",
                LOCALIZED_ERROR_CANTDRAWIMAGE,
                LOCALIZED_ERROR_SUBCODE,
                lastError);

            wxMessageBox(message, LOCALIZED_ERROR, wxICON_ERROR);
            isOk = false;
        }
    }
    else
    {
        // can't do it
        wxMessageBox(
            LOCALIZED_ERROR_CANTEXTRACTIMAGE,
            LOCALIZED_ERROR,
            wxICON_ERROR);
        isOk = false;
    }

    // restore resources 
    if (EnablePalette)
    {
        SelectPalette(screenDc, OldPalette, FALSE);
    }

    delete [] bitsPtr;

    delete bitmapInfo;
    delete screenDeviceContext;

    return isOk;
}

void
CMainFrame::CLogoPicturePrintout::GetPageInfo(
    int *MinPage,
    int *MaxPage,
    int *SelPageFrom,
    int *SelPageTo
    )
{
    *MinPage     = 1;
    *MaxPage     = 1;
    *SelPageFrom = 1;
    *SelPageTo   = 1;
}

bool
CMainFrame::CLogoPicturePrintout::HasPage(int Page)
{
    return Page == 1;
}


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
#if MANUAL_HAS_TRANSLATION_TABLES
    // options for translating to/from English
    ID_HELPLANGTOENGLISH,
    ID_HELPENGLISHTOLANG,
#endif

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
    EVT_MENU(ID_EXIT,               CMainFrame::OnExit)
    EVT_MENU(ID_BITMAPNEW,          CMainFrame::OnBitmapNew)
    EVT_MENU(ID_BITMAPOPEN,         CMainFrame::OnBitmapOpen)
    EVT_MENU(ID_BITMAPSAVE,         CMainFrame::OnBitmapSave)
    EVT_MENU(ID_BITMAPSAVEAS,       CMainFrame::OnBitmapSaveAs)
    EVT_MENU(ID_BITMAPPRINT,        CMainFrame::OnBitmapPrint)
    EVT_MENU(ID_BITMAPPRINTERSETUP, CMainFrame::OnBitmapPrinterSetup)
    EVT_MENU(ID_BITMAPPRINTERAREA,  CMainFrame::OnSetActiveArea)
    EVT_MENU(ID_SETPENSIZE,         CMainFrame::OnSetPenSize)
    EVT_MENU(ID_SETLABELFONT,       CMainFrame::OnSetLabelFont)
    EVT_MENU(ID_SETCOMMANDERFONT,   CMainFrame::OnSetCommanderFont)
    EVT_MENU(ID_SETPENCOLOR,        CMainFrame::OnSetPenColor)
    EVT_MENU(ID_SETSCREENCOLOR,     CMainFrame::OnSetScreenColor)
    EVT_MENU(ID_SETFLOODCOLOR,      CMainFrame::OnSetFloodColor)
    EVT_MENU(ID_HELP,               CMainFrame::OnHelp)
#if MANUAL_HAS_TRANSLATION_TABLES
    // options for translating to/from English
    EVT_MENU(ID_HELPLANGTOENGLISH,  CMainFrame::OnHelpLanguageToEnglish)
    EVT_MENU(ID_HELPENGLISHTOLANG,  CMainFrame::OnHelpEnglishToLanguage)
#endif
    EVT_MENU(ID_HELPTUTORIAL,       CMainFrame::OnHelpTutorial)
    EVT_MENU(ID_HELPDEMO,           CMainFrame::OnHelpDemo)
    EVT_MENU(ID_HELPEXAMPLES,       CMainFrame::OnHelpExamples)
    EVT_MENU(ID_HELPRELEASENOTES,   CMainFrame::OnHelpReleaseNotes)
    EVT_MENU(ID_HELPABOUT,          CMainFrame::OnAboutFmsLogo)
    EVT_MENU(ID_HELPABOUTMS,        CMainFrame::OnAboutMultipleSclerosis)
    EVT_MENU(ID_ZOOMIN,             CMainFrame::OnZoomIn)
    EVT_MENU(ID_ZOOMOUT,            CMainFrame::OnZoomOut)
    EVT_MENU(ID_ZOOMNORMAL,         CMainFrame::OnZoomNormal)
    EVT_CLOSE(CMainFrame::OnClose)
END_EVENT_TABLE()

// My frame constructor
CMainFrame::CMainFrame(
    int             ScreenWidth,
    int             ScreenHeight,
    const wxPoint & Position,
    const wxSize  & Size
    ) : wxFrame(
        NULL, 
        wxID_ANY, 
        LOCALIZED_GENERAL_PRODUCTNAME,
        Position,
        Size,
        wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE),
      m_Screen(NULL),
      m_Commander(NULL),
      m_RealCommander(NULL),
      m_StatusDialog(NULL),
      m_SetPenSizeDialog(NULL),
      m_Splitter(NULL),
      m_CommanderIsDocked(false),
      m_IsNewFile(true),
      m_IsNewBitmap(true),
      m_SetPenColorDialog(NULL),
      m_SetFloodColorDialog(NULL),
      m_SetScreenColorDialog(NULL)
{
    m_FileName[0]   = '\0';
    m_BitmapName[0] = '\0';

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
#if MANUAL_HAS_TRANSLATION_TABLES
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

    SetFmsLogoIcon(*this);

    // Add the splitter to separate the screen from the commander
    m_Splitter = new MainSplitterWindow(this);

    m_Splitter->SetSashGravity(1.0);

    m_Screen = new CScreen(m_Splitter, ScreenWidth, ScreenHeight);

    DockCommanderWindow();

    m_Screen->Show();
    m_Commander->Show();

    // Configure the keyboard shortcuts
    wxAcceleratorEntry acceleratorEntries[1];

    // F1 opens help
    acceleratorEntries[0].Set(wxACCEL_NORMAL, WXK_F1, ID_HELP);

    wxAcceleratorTable acceleratorTable(
        ARRAYSIZE(acceleratorEntries),
        acceleratorEntries);
    SetAcceleratorTable(acceleratorTable);

#if wxUSE_STATUSBAR
    SetStatusText(_T("Min pane size = 0"), 1);
#endif // wxUSE_STATUSBAR

    // Set a flag that the printer data needs to be initialized.
    // We delay the initialization because it can be block
    // if the default printer is an offline network printer.
    m_PageSetupData.SetDefaultInfo(true);

    // init the pens based on the color
    UpdateNormalPen(GetPenStateForSelectedTurtle().Width, pcolor);
    UpdateErasePen(GetPenStateForSelectedTurtle().Width,  scolor);

    // it's show time for our little friend
    draw_turtle(true);
}

CMainFrame::~CMainFrame()
{
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

        m_RealCommander->GiveControlToInputBox();
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

        m_Splitter->SplitHorizontally(m_Screen, newCommander);
        m_Splitter->SetSashPosition(splitterPosition);

#if 0
        // TODO copy the history
        newCommandWindow->Duplicate(*CommandWindow);
#endif


#if 0 // is this necessary with wxWidgets?
        // redraw the entire screen window
        m_Screen->Update();
        newCommander->Update();
#endif

        // commit to the docked commander
        if (m_Commander != NULL)
        {
            // m_Commander is NULL when this is called from the constructor
            m_Commander->Destroy();
        }
        m_Commander     = newCommander;
        m_RealCommander = newCommander->GetCommander();
        m_Commander->Show();

        m_RealCommander->GiveControlToInputBox();

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
    // Construct the default coordinates of the editor's window
    // to be about 1/2 of the working area and placed in the center.
    int maxWidth;
    int maxHeight;
    GetWorkingAreaDimensions(maxWidth, maxHeight);

    int x = (int) (maxWidth * 0.25);
    int y = (int) (maxHeight * 0.25);
    int w = (int) (maxWidth * 0.75);
    int h = (int) (maxHeight * ScreenSz * 0.75);

    // If the user has some coordinates saved, use them, instead.
    GetConfigurationQuadruple("Editor", &x, &y, &w, &h); 
    checkwindow(&x, &y, &w, &h);

    // Determine the title
    const char * editorWindowTitle;
    if (EditArguments != NIL || CheckForErrors)
    {
        editorWindowTitle = LOCALIZED_EDITOR_TITLE;
    }
    else
    {
        editorWindowTitle = FileName.c_str();
    }

    CWorkspaceEditor * editor = new CWorkspaceEditor(
        this,
        editorWindowTitle,
        wxPoint(x, y),
        wxSize(w, h),
        FileName,
        EditArguments,
        CheckForErrors);

    // add this editor the the list of known editors
    m_Editors.insert(std::pair<CWorkspaceEditor*,CWorkspaceEditor*>(editor,editor));

    return editor;
}

bool CMainFrame::PromptUserForInput(char *Output, const char *Prompt)
{
    // get user input
    const wxString userInput = wxGetTextFromUser(
        LOCALIZED_INPUT,
        Prompt,
        wxEmptyString,
        this);
    if (userInput.IsEmpty())
    {
        return false;
    }

    // Copy the user input to the Output string
    strncpy(
        Output,
        userInput.c_str(),
        MAX_BUFFER_SIZE - 1);
    Output[MAX_BUFFER_SIZE - 1] = '\0';
    return true;
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

    GiveFocusToEditbox = false;
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

CStatusDialog *
CMainFrame::GetStatusDialog()
{
    return m_StatusDialog;
}

void
CMainFrame::ClearStatusDialog()
{
    m_StatusDialog = NULL;
}

CScreen * CMainFrame::GetScreen()
{
    return m_Screen;
}

CCommander * CMainFrame::GetCommander()
{
    return m_RealCommander;
}

// Returns the window to which is it appropriate to send state change
// messages, such as minimizing, that are intended for the commander.
//
// If the commander is docked, this is the commander panel.
// If the commander is not docked, this is the top-level window that
// contains the commander panel.
//
wxWindow * CMainFrame::GetTopLevelWindowForCommander()
{
    return m_Commander;
}

void CMainFrame::OnClose(wxCloseEvent& Event)
{
    if (Event.CanVeto())
    {
        // If an editor is running we could lose unsaved changes
        CWorkspaceEditor * editor = GetWorkspaceEditor();
        if (editor != NULL)
        {
            // make sure that the editor is visible
            editor->Iconize(false);
            editor->Show();
            editor->Raise();
            GiveFocusToEditbox = false;

            if (wxMessageBox(
                    LOCALIZED_CHANGESINEDITORMAYBELOST,
                    LOCALIZED_EDITSESSIONISRUNNING,
                    wxOK | wxCANCEL | wxICON_QUESTION) != wxOK)
            {
                // The user doesn't want to shutdown.
                Event.Veto();
                return;
            }
        }


        if (is_executing())
        {
            // The language engine is not halted.
            // Warn user and give chance to abort shutdown.
            if (IsTimeToHalt)
            {
                // we already tried warn user of doom
                if (wxMessageBox(
                        LOCALIZED_NOTHALTEDREALLYEXIT,
                        LOCALIZED_LOGOISNOTHALTED,
                        wxOK | wxCANCEL | wxICON_QUESTION) != wxOK)
                {
                    // The user doesn't want to shutdown.
                    Event.Veto();
                    return;
                }
            }
            else
            {
                // let the user optionally halt first
                if (wxMessageBox(
                        LOCALIZED_NOTHALTEDREALLYHALT,
                        LOCALIZED_LOGOISNOTHALTED,
                        wxOK | wxCANCEL | wxICON_QUESTION) == wxOK)
                {
                    m_RealCommander->Halt();
                }
                Event.Veto();
                return;
            }
        }

        // If the workspace has unsaved changes, then give the
        // user a chance to abort shutdown.
        if (IsDirty)
        {
            CSaveBeforeExitDialog saveChangesDialog(this);

            saveChangesDialog.ShowModal();
            int exitCode = saveChangesDialog.GetReturnCode();
            switch (exitCode)
            {
            case CSaveBeforeExitDialog::SAVEBEFOREEXIT_Cancel:
                // Don't exit FMSLogo
                IsTimeToHalt  = false;
                IsTimeToExit  = false;
                stopping_flag = RUN;
                Event.Veto();
                return;

            case CSaveBeforeExitDialog::SAVEBEFOREEXIT_SaveAndExit:
                // save and then exit

                // HACK: Set TimeToExit and TimeToHalt to false
                // so that writing the file to disk doesn't abort.
                // This is hack because the code should not modify
                // global variables--there should be a way to tell 
                // CMFileSave to ignore errors.
                bool savedIsTimeToExit = IsTimeToExit;
                bool savedIsTimeToHalt = IsTimeToHalt;

                IsTimeToExit = false;
                IsTimeToHalt = false;
                bool isOk = FileSave();
                if (!isOk)
                {
                    // Something went wrong (most likely, the user 
                    // pressed "Cancel" when asked to choose a filename).
                    // Give the user a chance to fix the problem.
                    IsTimeToHalt  = false;
                    IsTimeToExit  = false;
                    stopping_flag = RUN;
                    Event.Veto();
                    return;
                }

                IsTimeToExit = savedIsTimeToExit;
                IsTimeToHalt = savedIsTimeToHalt;
                break;
            }
        }
    }

    // If we made it here we are OK to exit.

    // Don't save the window size if it's minimized, the commander is undocked,
    // or if FMSLogo was started with the -F option.
    if (!IsIconized() && m_CommanderIsDocked && !bFixed)
    {
        // Get location and size of our window on the screen so we can
        // come back up in the same spot next time we are invoked.
        const wxRect mainWindowRect = GetRect();

        // save the current location of the screen
        SetConfigurationQuadruple(
            "Screen",
            mainWindowRect.GetLeft(),
            mainWindowRect.GetTop(),
            mainWindowRect.GetWidth(),
            mainWindowRect.GetHeight());

        // Save the current location of the commander.
        // When the comander is docked, only the height
        // is relevant, but we must save all parts.
        const wxRect commanderRectangle = m_RealCommander->GetScreenRect();

        SetConfigurationQuadruple(
            "Commander",
            commanderRectangle.GetLeft(),
            commanderRectangle.GetTop(),
            commanderRectangle.GetWidth(),
            commanderRectangle.GetHeight());
    }

    // Cleanup the pens
    // REVISIT: This is where the pens were destroyed in the OWL
    // implementation, but it doesn't seem like the right place
    // for it.
    if (g_NormalPen != NULL)
    {
        DeleteObject(g_NormalPen);
        g_NormalPen = NULL;
    }

    if (g_ErasePen != NULL)
    {
        DeleteObject(g_ErasePen);
        g_ErasePen = NULL;
    }

    // Because the timer events are scheduled on
    // the main window's HWND, we must uninitialize them
    // before the main window is destroyed.
    uninitialize_timers();

    // Invoke the default handler, which is to destroy
    // the window and shut down.
    Event.Skip();
}


// menu command handlers
void CMainFrame::OnExit(wxCommandEvent& WXUNUSED(Event))
{
    // Attempt to close the application while
    // giving the user an opportunity to abort
    // the operation.
    Close(false);
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
                GetTopLevelWindowForCommander()) == wxCANCEL)
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
                GetTopLevelWindowForCommander()) == wxCANCEL)
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
                GetTopLevelWindowForCommander()) == wxCANCEL)
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
    dlg.DoDialog();
}

void CMainFrame::OnEraseProcedure(wxCommandEvent& WXUNUSED(Event))
{
    CEraseProcedureDialog dlg(this);
    dlg.DoDialog();
}

void CMainFrame::OnBitmapNew(wxCommandEvent& WXUNUSED(Event))
{
    // Reset the on-screen bitmap.
    HBRUSH brush = ::CreateBrushIndirect(&ScreenBrush);
    if (brush != NULL)
    {
        HDC memoryDC = static_cast<HDC>(m_Screen->GetMemoryDeviceContext().GetHDC());

        ::SelectObject(memoryDC, MemoryBitMap);

        ::FillRect(memoryDC, &FullRect, brush);

        ::SetBkColor(memoryDC, scolor);
        ::SetBkMode(memoryDC, TRANSPARENT);

        ::DeleteObject(brush);
    }

    // Refresh the screen window so that it will repainted
    // to match the memory device context.
    m_Screen->Refresh(true);

    // Mark the bitmap as not ever having been saved.
    m_IsNewBitmap = true;
}

void CMainFrame::OnBitmapOpen(wxCommandEvent& WXUNUSED(Event))
{
    OPENFILENAME openFileName;
    ZeroMemory(&openFileName, sizeof openFileName);
    openFileName.lStructSize       = sizeof openFileName;
    openFileName.hwndOwner         = static_cast<HWND>(GetHandle());
    openFileName.hInstance         = NULL;
    openFileName.lpstrFilter       = LOCALIZED_FILEFILTER_IMAGE;
    openFileName.lpstrCustomFilter = NULL;
    openFileName.nMaxCustFilter    = 0;
    openFileName.nFilterIndex      = 0;
    openFileName.lpstrFile         = m_BitmapName;
    openFileName.nMaxFile          = ARRAYSIZE(m_BitmapName);
    openFileName.lpstrFileTitle    = NULL;
    openFileName.nMaxFileTitle     = 0;
    openFileName.lpstrInitialDir   = NULL;
    openFileName.lpstrTitle        = NULL;
    openFileName.Flags             = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_EXPLORER;
    openFileName.nFileOffset       = 0;
    openFileName.nFileExtension    = 0;
    openFileName.lpstrDefExt       = "bmp";
    openFileName.lCustData         = 0;
    openFileName.lpfnHook          = NULL;
    openFileName.lpTemplateName    = NULL;

    // if user found a file then try to load it
    if (GetOpenFileName(&openFileName))
    {
        DWORD dwPixelWidth  = 1;
        DWORD dwPixelHeight = 1;

        m_IsNewBitmap = false;

        ERR_TYPES status;
        char ext[_MAX_EXT];
        _splitpath(m_BitmapName, NULL, NULL, NULL, ext);
        if (stricmp(ext, ".gif") == 0)
        {
            status = gifload_helper(m_BitmapName, dwPixelWidth, dwPixelHeight);
        }
        else
        {
            status = LoadBitmapFile(m_BitmapName, dwPixelWidth, dwPixelHeight);
        }

        if (status != SUCCESS)
        {
            ShowErrorMessage(status);
        }
    }
}

void CMainFrame::SaveBitmap()
{
    ERR_TYPES status;

    char ext[_MAX_EXT];
    _splitpath(m_BitmapName, NULL, NULL, NULL, ext);
    if (stricmp(ext, ".gif") == 0)
    {
        status = gifsave_helper(m_BitmapName, -1, 0, -1, -1, 8);
    }
    else
    {
        status = DumpBitmapFile(m_BitmapName, 32);
    }

    if (status != SUCCESS)
    {
        ShowErrorMessage(status);
    }
}

void CMainFrame::SaveBitmapAs()
{
    // if new then nulify File name
    if (m_IsNewBitmap)
    {
        m_BitmapName[0] = '\0';
    }

    // Get file name from user
    OPENFILENAME openFileName;
    ZeroMemory(&openFileName, sizeof openFileName);
    openFileName.lStructSize       = sizeof openFileName;
    openFileName.hwndOwner         = static_cast<HWND>(GetHandle());
    openFileName.hInstance         = NULL;
    openFileName.lpstrFilter       = LOCALIZED_FILEFILTER_IMAGE;
    openFileName.lpstrCustomFilter = NULL;
    openFileName.nMaxCustFilter    = 0;
    openFileName.nFilterIndex      = 0;
    openFileName.lpstrFile         = m_BitmapName;
    openFileName.nMaxFile          = ARRAYSIZE(m_BitmapName);
    openFileName.lpstrFileTitle    = NULL;
    openFileName.nMaxFileTitle     = 0;
    openFileName.lpstrInitialDir   = NULL;
    openFileName.lpstrTitle        = NULL;
    openFileName.Flags             = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_EXPLORER;
    openFileName.nFileOffset       = 0;
    openFileName.nFileExtension    = 0;
    openFileName.lpstrDefExt       = "bmp";
    openFileName.lCustData         = 0;
    openFileName.lpfnHook          = NULL;
    openFileName.lpTemplateName    = NULL;

    if (GetSaveFileName(&openFileName))
    {
        // Save the bitmap using the new file name
        m_IsNewBitmap = false;
        SaveBitmap();
    }
}

void CMainFrame::OnBitmapSave(wxCommandEvent& WXUNUSED(Event))
{
    // if new file then switch to save file as, else save
    if (m_IsNewBitmap)
    {
        SaveBitmapAs();
    }
    else
    {
        SaveBitmap();
    }
}

void CMainFrame::OnBitmapSaveAs(wxCommandEvent& WXUNUSED(Event))
{
    SaveBitmapAs();
}

void CMainFrame::InitializePrinter()
{
    // Read the default page settings.
    // On Windows, even though we call ShowModal, no
    // dialog box is displayed because we set the
    // default info to true.
    if (m_PageSetupData.GetDefaultInfo())
    {
#ifdef __WXMSW__
        m_PageSetupData.SetDefaultMinMargins(true);
        wxPageSetupDialog pageSetup(this, &m_PageSetupData);
        if (pageSetup.ShowModal() == wxID_OK)
        {
            // Save the updated preferences.
            m_PageSetupData = pageSetup.GetPageSetupData();
        }
#endif

        // Mark the printer data as having been initialized.
        m_PageSetupData.SetDefaultInfo(false);
    }
}

void CMainFrame::OnBitmapPrint(wxCommandEvent& WXUNUSED(Event))
{
    InitializePrinter();

    wxPrintDialogData printDialogData(m_PageSetupData.GetPrintData());

    // Show the printer selection dialog box.
    wxPrinter printer(&printDialogData);

    // FMSLogo always scales the active area of the screen to fit on a
    // single page, so we disable page number selection to prevent confusion.
    printDialogData.EnablePageNumbers(false);

    CLogoPicturePrintout printout(
        LOCALIZED_GENERAL_PRODUCTNAME,
        *m_Screen,
        m_PageSetupData);

    if (!printer.Print(this, &printout, true))
    {
        // This can happen in two cases:
        // 1) If there was an error while printing, in which
        //    case the operating system will have communicated
        //    the problem to the user, so we don't need to.
        // 2) If the print job was cancelled by the user,
        //    in which case we don't need to tell the user
        //    that they cancelled the job.
        //
        // Therefore, all we need to do is exit.
        return;
    }

    // Preserve the printr settings for the next time.
    m_PageSetupData.SetPrintData(printer.GetPrintDialogData().GetPrintData());
}

void CMainFrame::OnBitmapPrinterSetup(wxCommandEvent& WXUNUSED(Event))
{
    InitializePrinter();

    // Show a dialog box for updating the page setup
    wxPageSetupDialog pageSetup(this, &m_PageSetupData);
    if (pageSetup.ShowModal() == wxID_OK)
    {
        // The user pressed OK on the dialog box.
        // Save the updated preferences.
        m_PageSetupData = pageSetup.GetPageSetupData();
    }
}

void CMainFrame::OnSetPenSize(wxCommandEvent& WXUNUSED(Event))
{
    if (m_SetPenSizeDialog == NULL)
    {
        const int initialSize = get_pen_width();

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
    COLORREF        InitialColor,
    const char  *   LogoCommand
    )
{
    if (SetColorDialog == NULL)
    {
        const wxColor initialColor(
            GetRValue(InitialColor),
            GetGValue(InitialColor),
            GetBValue(InitialColor));

        SetColorDialog = new CSetColor(
            this,
            DialogTitle,
            initialColor,
            LogoCommand,
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
        pcolor,
        LOCALIZED_ALTERNATE_SETPENCOLOR);
}

void CMainFrame::OnSetFloodColor(wxCommandEvent& WXUNUSED(Event))
{
    SetColorHelper(
        m_SetFloodColorDialog,
        LOCALIZED_SETCOLOR_FLOODCOLOR,
        fcolor,
        LOCALIZED_ALTERNATE_SETFLOODCOLOR);
}

void CMainFrame::OnSetScreenColor(wxCommandEvent& WXUNUSED(Event))
{
    SetColorHelper(
        m_SetScreenColorDialog,
        LOCALIZED_SETCOLOR_SCREENCOLOR,
        scolor,
        LOCALIZED_ALTERNATE_SETSCREENCOLOR);
}

void CMainFrame::ShowStatus()
{
    // create a new status dialog, if necessary
    if (!StatusDialogIsShowing())
    {
        m_StatusDialog = new CStatusDialog(this);
        m_StatusDialog->PopulateAllFields();
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
    bool isOk;

    do
    {
        isOk = true;

        CSetActiveArea printerArea(
            this,
            g_PrinterAreaXLow,
            g_PrinterAreaXHigh,
            g_PrinterAreaYLow,
            g_PrinterAreaYHigh,
            g_PrinterAreaPixels);
        if (printerArea.ShowModal() == wxID_OK)
        {
            // the user did not cancel, so commit to the new settings
            int xLow;
            int xHigh;
            int yLow;
            int yHigh;
            printerArea.GetActiveArea(xLow, xHigh, yLow, yHigh);

            // Validate the area
            if (xLow >= xHigh || yLow >= yHigh)
            {
                // The settings are no good.  Notify the user and try again.
                wxMessageBox(LOCALIZED_ERROR_BADINPUT, LOCALIZED_ACTIVEAREA);
                isOk = false;
            }
            else
            {
                // The settings are ok.
                // Use them.
                int pixelsPerInch;
                printerArea.GetPixelsPerInch(pixelsPerInch);

                g_PrinterAreaXLow   = xLow;
                g_PrinterAreaXHigh  = xHigh;
                g_PrinterAreaYLow   = yLow;
                g_PrinterAreaYHigh  = yHigh;
                g_PrinterAreaPixels = pixelsPerInch;
                if (g_PrinterAreaPixels < 1)
                {
                    g_PrinterAreaPixels = 1;
                }

                // Persist the new settings
                SetConfigurationInt("Printer.XLow",   g_PrinterAreaXLow);
                SetConfigurationInt("Printer.XHigh",  g_PrinterAreaXHigh);
                SetConfigurationInt("Printer.YLow",   g_PrinterAreaYLow);
                SetConfigurationInt("Printer.YHigh",  g_PrinterAreaYHigh);
                SetConfigurationInt("Printer.Pixels", g_PrinterAreaPixels);
            }
        }
    } while (!isOk);
}

void CMainFrame::OnSetLabelFont(wxCommandEvent& WXUNUSED(Event))
{
    wxFontDialog fontChooser;

    // Seed the font picker with the current label font
    const wxFont labelFont = GetLabelFont();
    fontChooser.GetFontData().SetInitialFont(labelFont);

    int rval = fontChooser.ShowModal();
    if (rval == wxID_OK)
    {
        // The user selected a new font.

#ifdef __WXMSW__ 

        // Get the LOGFONT struct from the wxFont
        const wxFont newFont = fontChooser.GetFontData().GetChosenFont();
        const struct wxNativeFontInfo * fontInfo = newFont.GetNativeFontInfo();
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

void CMainFrame::OnSetCommanderFont(wxCommandEvent& WXUNUSED(Event))
{
    m_RealCommander->ChooseNewFont();
}

void CMainFrame::OnZoomIn(wxCommandEvent& WXUNUSED(Event))
{
    // TODO
    UndockCommanderWindow();
}

void CMainFrame::OnZoomOut(wxCommandEvent& WXUNUSED(Event))
{
    // TODO
    DockCommanderWindow();
}

void CMainFrame::OnZoomNormal(wxCommandEvent& WXUNUSED(Event))
{
    // TODO
    // For now, show the "To" mini-editor as a test hook
    CMiniEditor dlg(this, "TO SQUARE :length");
    dlg.ShowModal();
}

void CMainFrame::OnHelp(wxCommandEvent& WXUNUSED(Event))
{
    do_help(NULL);
}

#if MANUAL_HAS_TRANSLATION_TABLES

void CMainFrame::OnHelpLanguageToEnglish(wxCommandEvent& WXUNUSED(Event))
{
    do_help("To English");
}

void CMainFrame::OnHelpEnglishToLanguage(wxCommandEvent& WXUNUSED(Event))
{
    do_help("From English");
}

#endif // MANUAL_HAS_TRANSLATION_TABLES

void CMainFrame::OnHelpTutorial(wxCommandEvent& WXUNUSED(Event))
{
    do_help("Where to Start");
}

void CMainFrame::OnHelpDemo(wxCommandEvent& WXUNUSED(Event))
{
    do_execution("demo");
}

void
CMainFrame::OpenFileWithDefaultApplication(
    const char *  FileName
    )
{
    HINSTANCE childApplication = ShellExecute(
        static_cast<HWND>(GetHandle()), // handle to parent window
        "open",                         // operation to perform
        FileName,                       // pointer to filename string
        NULL,                           // pointer to string that specifies executable-file parameters
        NULL,                           // pointer to string that specifies default directory
        SW_SHOWNORMAL);                 // whether file is shown when opened
    if (childApplication != NULL)
    {
        CloseHandle(childApplication);
    }
}

void CMainFrame::OnHelpExamples(wxCommandEvent& WXUNUSED(Event))
{
    char szFileName[MAX_PATH + 1];
    MakeHelpPathName(szFileName, "EXAMPLES\\INDEX.HTML");

    OpenFileWithDefaultApplication(szFileName);
}

void CMainFrame::OnHelpReleaseNotes(wxCommandEvent& WXUNUSED(Event))
{
    char szFileName[MAX_PATH + 1];
    MakeHelpPathName(szFileName, "README.TXT");

    OpenFileWithDefaultApplication(szFileName);
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
