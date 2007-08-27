
// ============================================================================
// declarations
// ============================================================================

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

    #include "wx/textdlg.h"       // for wxGetTextFromUser
#endif

#include "wx/splitter.h"
#include "wx/dcmirror.h"

#include "commander.h"
#include "logocore.h"
#include "localizedstrings.h"
#include "fmslogo.h"

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
// our classes
// ----------------------------------------------------------------------------

class MyApp: public wxApp
{
public:
    MyApp() { }

    virtual bool OnInit();

    DECLARE_NO_COPY_CLASS(MyApp)
};

class CMainFrame: public wxFrame
{
public:
   CMainFrame();
   virtual ~CMainFrame();

   // Menu commands
   void Unsplit(wxCommandEvent& event);
   void ToggleLive(wxCommandEvent& event);
   void SetPosition(wxCommandEvent& event);
   void SetMinSize(wxCommandEvent& event);
   void SetGravity(wxCommandEvent& event);
   void Replace(wxCommandEvent &event);

   void Quit(wxCommandEvent& event);

   // Menu command update functions
   void UpdateUIHorizontal(wxUpdateUIEvent& event);
   void UpdateUIVertical(wxUpdateUIEvent& event);
   void UpdateUIUnsplit(wxUpdateUIEvent& event);
   
private:
   wxScrolledWindow *m_Screen;
   CCommander       *m_Commander;

   wxSplitterWindow* m_splitter;
   wxWindow *m_replacewindow;

   DECLARE_EVENT_TABLE();
   DECLARE_NO_COPY_CLASS(CMainFrame);
};

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

class MyCanvas: public wxScrolledWindow
{
public:
    MyCanvas(wxWindow* parent, bool mirror);
    virtual ~MyCanvas(){};

    virtual void OnDraw(wxDC& dc);

private:
    bool m_mirror;

    DECLARE_NO_COPY_CLASS(MyCanvas)
};

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// MyApp
// ----------------------------------------------------------------------------

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    // create and show the main frame
    CMainFrame* frame = new CMainFrame;

    frame->Show(true);

    return true;
}

// ----------------------------------------------------------------------------
// CMainFrame
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
    EVT_MENU(SPLIT_UNSPLIT, CMainFrame::Unsplit)
    EVT_MENU(SPLIT_LIVE, CMainFrame::ToggleLive)
    EVT_MENU(SPLIT_SETPOSITION, CMainFrame::SetPosition)
    EVT_MENU(SPLIT_SETMINSIZE, CMainFrame::SetMinSize)
    EVT_MENU(SPLIT_SETGRAVITY, CMainFrame::SetGravity)
    EVT_MENU(SPLIT_REPLACE, CMainFrame::Replace)

    EVT_MENU(SPLIT_QUIT, CMainFrame::Quit)

    EVT_UPDATE_UI(SPLIT_VERTICAL, CMainFrame::UpdateUIVertical)
    EVT_UPDATE_UI(SPLIT_HORIZONTAL, CMainFrame::UpdateUIHorizontal)
    EVT_UPDATE_UI(SPLIT_UNSPLIT, CMainFrame::UpdateUIUnsplit)
END_EVENT_TABLE()

struct MENUITEM 
{
    const char *  MenuText;
    int           MenuId;
};

static
void
FillMenu(
    wxMenu *          Menu,
    const MENUITEM *  MenuItems,
    size_t            MenuItemsLength
    )
{
    for (size_t i = 0; i < MenuItemsLength; i++)
    {
        if (MenuItems[i].MenuText != NULL)
        {
            Menu->Append(
                MenuItems[i].MenuId,
                MenuItems[i].MenuText);
        }
        else
        {
            Menu->AppendSeparator();
        }
    }
}

static
void
AppendChildMenu(
    wxMenuBar *       MainMenu,
    const char *      ChildMenuText,
    const MENUITEM *  ChildMenuItems,
    size_t            ChildMenuItemsLength
    )
{
    // create the popup menu
    wxMenu * childMenu = new wxMenu;

    // fill the child menu with its items
    FillMenu(childMenu, ChildMenuItems, ChildMenuItemsLength);

    // append the child menu to the main menu
    MainMenu->Append(childMenu, ChildMenuText);
}

enum MenuIds
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

    ID_SETFONT,
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


// My frame constructor
CMainFrame::CMainFrame()
       : wxFrame(NULL, wxID_ANY, _T("wxSplitterWindow sample"),
                 wxDefaultPosition, wxSize(420, 300),
                 wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE)
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
        {LOCALIZED_SET_LABELFONT,     ID_SETFONT},
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
        {LOCALIZED_HELP_MCI,           ID_HELPMCI},
        {LOCALIZED_HELP_HELP,          ID_HELPHELP},
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


    m_splitter = new MySplitterWindow(this);
    
    m_splitter->SetSashGravity(1.0);

    m_Screen = new MyCanvas(m_splitter, true);
    m_Screen->SetBackgroundColour(*wxWHITE);
    m_Screen->SetScrollbars(20, 20, 5, 5);

    //m_Commander = new MyCanvas(m_splitter, false);
    m_Commander = new CCommander(m_splitter);

    m_Screen->Show(true);
    m_Commander->Show(true);
    m_splitter->SplitHorizontally(m_Screen, m_Commander);

#if wxUSE_STATUSBAR
    SetStatusText(_T("Min pane size = 0"), 1);
#endif // wxUSE_STATUSBAR

    m_replacewindow = (wxWindow *)0;
}

CMainFrame::~CMainFrame()
{
    if (m_replacewindow) {
        m_replacewindow->Destroy();
        m_replacewindow = (wxWindow *)0;
    }
}

// menu command handlers

void CMainFrame::Quit(wxCommandEvent& WXUNUSED(event) )
{
    Close(true);
}

void CMainFrame::Unsplit(wxCommandEvent& WXUNUSED(event) )
{
    if ( m_splitter->IsSplit() )
        m_splitter->Unsplit();
#if wxUSE_STATUSBAR
    SetStatusText(_T("No splitter"));
#endif // wxUSE_STATUSBAR
}

void CMainFrame::ToggleLive(wxCommandEvent& event )
{
    long style = m_splitter->GetWindowStyleFlag();
    if ( event.IsChecked() )
        style |= wxSP_LIVE_UPDATE;
    else
        style &= ~wxSP_LIVE_UPDATE;

    m_splitter->SetWindowStyleFlag(style);
}

void CMainFrame::SetPosition(wxCommandEvent& WXUNUSED(event) )
{
    wxString str;
    str.Printf( wxT("%d"), m_splitter->GetSashPosition());
    str = wxGetTextFromUser(_T("Enter splitter position:"), _T(""), str, this);
    if ( str.empty() )
        return;

    long pos;
    if ( !str.ToLong(&pos) )
    {
        wxLogError(_T("The splitter position should be an integer."));
        return;
    }

    m_splitter->SetSashPosition(pos);

    wxLogStatus(this, _T("Splitter position set to %ld"), pos);
}

void CMainFrame::SetMinSize(wxCommandEvent& WXUNUSED(event) )
{
    wxString str;
    str.Printf( wxT("%d"), m_splitter->GetMinimumPaneSize());
    str = wxGetTextFromUser(_T("Enter minimal size for panes:"), _T(""), str, this);
    if ( str.empty() )
        return;

    int minsize = wxStrtol( str, (wxChar**)NULL, 10 );
    m_splitter->SetMinimumPaneSize(minsize);
#if wxUSE_STATUSBAR
    str.Printf( wxT("Min pane size = %d"), minsize);
    SetStatusText(str, 1);
#endif // wxUSE_STATUSBAR
}
void CMainFrame::SetGravity(wxCommandEvent& WXUNUSED(event) )
{
    wxString str;
    str.Printf( wxT("%g"), m_splitter->GetSashGravity());
    str = wxGetTextFromUser(_T("Enter sash gravity (0,1):"), _T(""), str, this);
    if ( str.empty() )
        return;

    double gravity = wxStrtod( str, (wxChar**)NULL);
    m_splitter->SetSashGravity(gravity);
#if wxUSE_STATUSBAR
    str.Printf( wxT("Gravity = %g"), gravity);
    SetStatusText(str, 1);
#endif // wxUSE_STATUSBAR
}

void CMainFrame::Replace(wxCommandEvent& WXUNUSED(event) )
{
    if (m_replacewindow == 0) {
        m_replacewindow = m_splitter->GetWindow2();
        m_splitter->ReplaceWindow(m_replacewindow, new wxPanel(m_splitter, wxID_ANY));
        m_replacewindow->Hide();
    } else {
        wxWindow *empty = m_splitter->GetWindow2();
        m_splitter->ReplaceWindow(empty, m_replacewindow);
        m_replacewindow->Show();
        m_replacewindow = 0;
        empty->Destroy();
    }
}

// Update UI handlers

void CMainFrame::UpdateUIHorizontal(wxUpdateUIEvent& event)
{
    event.Enable( (!m_splitter->IsSplit()) || (m_splitter->GetSplitMode() != wxSPLIT_HORIZONTAL) );
}

void CMainFrame::UpdateUIVertical(wxUpdateUIEvent& event)
{
    event.Enable( ( (!m_splitter->IsSplit()) || (m_splitter->GetSplitMode() != wxSPLIT_VERTICAL) ) );
}

void CMainFrame::UpdateUIUnsplit(wxUpdateUIEvent& event)
{
    event.Enable( m_splitter->IsSplit() );
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

// ----------------------------------------------------------------------------
// MyCanvas
// ----------------------------------------------------------------------------

MyCanvas::MyCanvas(wxWindow* parent, bool mirror)
        : wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                           wxHSCROLL | wxVSCROLL | wxNO_FULL_REPAINT_ON_RESIZE)
{
    m_mirror = mirror;
}

void MyCanvas::OnDraw(wxDC& dcOrig)
{
}

