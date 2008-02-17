#include "wx/menu.h"
#include "wx/richtext/richtextctrl.h"

#include "workspaceeditor.h"
#include "localizedstrings.h"
#include "guiutils.h"
#include "logocore.h" // for ARRAYSIZE

static bool bExpert = false;


enum
{
    ID_FILESAVEANDEXIT = wxID_HIGHEST,
    ID_FILEPRINT,
    ID_EDALLEXIT,
    ID_FILESAVETOWORKSPACE,
    ID_EDITUNDO,
    ID_EDITCUT,
    ID_EDITCOPY,
    ID_EDITPASTE,
    ID_EDITDELETE,
    ID_EDITCLEAR,
    ID_EDITSELECTALL,
    ID_EDITFIND,
    ID_EDITREPLACE,
    ID_EDITFINDNEXT,
    ID_EDITSETFONT,
    ID_HELP,
    ID_TEST,
    ID_HELPEDIT,
    ID_HELPEDIT_TOPIC,

    ID_RICHTEXTCONTROL,
};

BEGIN_EVENT_TABLE(CWorkspaceEditor, wxFrame)
    EVT_MENU(ID_EDALLEXIT,  CWorkspaceEditor::Quit)
END_EVENT_TABLE()


// My frame constructor
CWorkspaceEditor::CWorkspaceEditor(wxWindow * Parent)
    : wxFrame(
        Parent,
        wxID_ANY, 
        LOCALIZED_EDITOR_TITLE,
        wxDefaultPosition, 
        wxSize(420, 300),
        wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE)
{
    CreateStatusBar(1);

    m_RichTextControl = new wxRichTextCtrl(this, ID_RICHTEXTCONTROL);

    //
    // Construct the main menu
    //
    static const MENUITEM defaultFileMenuItems[] = {
        {LOCALIZED_EDITOR_FILE_SAVEANDEXIT,     ID_FILESAVEANDEXIT},
        {LOCALIZED_EDITOR_FILE_PRINT,           ID_FILEPRINT},
        {0},
        {LOCALIZED_EDITOR_FILE_EXIT,            ID_EDALLEXIT},
    };

    static const MENUITEM expertFileMenuItems[] = {
        {LOCALIZED_EDITOR_FILE_SAVEANDEXIT,     ID_FILESAVEANDEXIT},
        {LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE, ID_FILESAVETOWORKSPACE},
        {LOCALIZED_EDITOR_FILE_PRINT,           ID_FILEPRINT},
        {0},
        {LOCALIZED_EDITOR_FILE_EXIT,            ID_EDALLEXIT},
    };

    static const MENUITEM editMenuItems[] = {
        {LOCALIZED_EDITOR_EDIT_UNDO,      ID_EDITUNDO},
        {0},
        {LOCALIZED_EDITOR_EDIT_CUT,       ID_EDITCUT},
        {LOCALIZED_EDITOR_EDIT_COPY,      ID_EDITCOPY},
        {LOCALIZED_EDITOR_EDIT_PASTE,     ID_EDITPASTE},
        {LOCALIZED_EDITOR_EDIT_DELETE,    ID_EDITDELETE},
        {0},
        {LOCALIZED_EDITOR_EDIT_CLEARALL,  ID_EDITCLEAR},
        {LOCALIZED_EDITOR_EDIT_SELECTALL, ID_EDITSELECTALL},
    };

    static const MENUITEM searchMenuItems[] = {
        {LOCALIZED_EDITOR_SEARCH_FIND,    ID_EDITFIND},
        {LOCALIZED_EDITOR_SEARCH_REPLACE, ID_EDITREPLACE},
        {LOCALIZED_EDITOR_SEARCH_NEXT,    ID_EDITFINDNEXT},
    };

    static const MENUITEM setMenuItems[] = {
        {LOCALIZED_EDITOR_SET_FONT,       ID_EDITSETFONT}
    };
 
    static const MENUITEM helpMenuItems[] = {
        {LOCALIZED_EDITOR_HELP_INDEX,       ID_HELP},
        {LOCALIZED_EDITOR_HELP_EDITOR,      ID_HELPEDIT},
        {LOCALIZED_EDITOR_HELP_TOPICSEARCH, ID_HELPEDIT_TOPIC},
    };


    wxMenuBar * mainMenu = new wxMenuBar;

    if (bExpert)
    {
        AppendChildMenu(
            mainMenu, 
            LOCALIZED_EDITOR_FILE,
            expertFileMenuItems,
            ARRAYSIZE(expertFileMenuItems));
    }
    else
    {
        AppendChildMenu(
            mainMenu, 
            LOCALIZED_EDITOR_FILE,
            defaultFileMenuItems,
            ARRAYSIZE(defaultFileMenuItems));
    }
    AppendChildMenu(mainMenu, LOCALIZED_EDITOR_EDIT,   editMenuItems,   ARRAYSIZE(editMenuItems));
    AppendChildMenu(mainMenu, LOCALIZED_EDITOR_SEARCH, searchMenuItems, ARRAYSIZE(searchMenuItems));
    AppendChildMenu(mainMenu, LOCALIZED_EDITOR_SET,    setMenuItems,    ARRAYSIZE(setMenuItems));
    mainMenu->Append(new wxMenu, LOCALIZED_EDITOR_TEST);
    AppendChildMenu(mainMenu, LOCALIZED_EDITOR_HELP,   helpMenuItems,   ARRAYSIZE(helpMenuItems));


    SetMenuBar(mainMenu);
}

// menu command handlers
void CWorkspaceEditor::Quit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}
