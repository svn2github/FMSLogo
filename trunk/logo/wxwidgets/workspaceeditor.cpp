#ifdef __WXMSW__
#  include <windows.h>  // for LOGFONT
#endif

#include <wx/menu.h>
#include <wx/fontdlg.h>

#include "workspaceeditor.h"
#include "logocodectrl.h"
#include "localizedstrings.h"
#include "guiutils.h"
#include "logocore.h" // for ARRAYSIZE
#include "fontutils.h"
#include "fmslogo.h"
#include "mainframe.h"
#include "utils.h"
#include "wrksp.h" // for bExpert
#include "screenwindow.h" // for TraceOutput

enum
{
    KEY_CODE_CLOSE_BRACKET = 0xDD,
};

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

    ID_LOGOCODECONTROL,

    ID_FINDMATCHINGPAREN,
    ID_SELECTMATCHINGPAREN,
};

BEGIN_EVENT_TABLE(CWorkspaceEditor, wxFrame)
    EVT_MENU(ID_EDALLEXIT,           CWorkspaceEditor::OnQuit)
    EVT_MENU(ID_EDITSETFONT,         CWorkspaceEditor::OnSetFont)
    EVT_MENU(ID_EDITUNDO,            CWorkspaceEditor::OnUndo)
    EVT_MENU(ID_EDITCUT,             CWorkspaceEditor::OnCut)
    EVT_MENU(ID_EDITCOPY,            CWorkspaceEditor::OnCopy)
    EVT_MENU(ID_EDITPASTE,           CWorkspaceEditor::OnPaste)
    EVT_MENU(ID_EDITDELETE,          CWorkspaceEditor::OnDelete)
    EVT_MENU(ID_EDITCLEAR,           CWorkspaceEditor::OnClear)
    EVT_MENU(ID_EDITSELECTALL,       CWorkspaceEditor::OnSelectAll)
    EVT_MENU(ID_FINDMATCHINGPAREN,   CWorkspaceEditor::OnFindMatchingParen)
    EVT_MENU(ID_SELECTMATCHINGPAREN, CWorkspaceEditor::OnSelectMatchingParen)
    EVT_CLOSE(CWorkspaceEditor::OnClose)
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

    m_LogoCodeControl = new CLogoCodeCtrl(this, ID_LOGOCODECONTROL);
 
    // Make sure that the Logo code edit control expands
    // to fill all available space
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_LogoCodeControl, 1, wxEXPAND);
    SetSizer(sizer);

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

    // set the font
    wxFont font;
    font.SetFamily(wxFONTFAMILY_TELETYPE);
    GetConfigurationFont("EditFont", font);
    m_LogoCodeControl->SetFont(font);

    // HACK: fill with some sample text until we can read
    // the text from the workspace.
    m_LogoCodeControl->SetText(
        "to square\n"
        "  ;; makes a square\n"
        "  repeat 4 [ fd 100 rt 90 ]\n"
        "end\n");

    wxAcceleratorEntry accelleratorEntries[2];

    // Ctrl+] moves to matching paren
    accelleratorEntries[0].Set(wxACCEL_CTRL, KEY_CODE_CLOSE_BRACKET, ID_FINDMATCHINGPAREN);

    // Ctrl+Shift+] selects to matching paren
    accelleratorEntries[1].Set(wxACCEL_CTRL | wxACCEL_SHIFT, KEY_CODE_CLOSE_BRACKET, ID_SELECTMATCHINGPAREN);

    wxAcceleratorTable acceleratorTable(ARRAYSIZE(accelleratorEntries), accelleratorEntries);
    SetAcceleratorTable(acceleratorTable);
}

void CWorkspaceEditor::OnSetFont(wxCommandEvent& WXUNUSED(event) )
{
    wxFont font;

    font.SetFamily(wxFONTFAMILY_TELETYPE);
    GetConfigurationFont("EditFont", font);

    wxFontDialog fontChooser;
    fontChooser.GetFontData().SetInitialFont(font);

    int rval = fontChooser.ShowModal();
    if (rval == wxID_OK)
    {
        // the user selected a new font
        font = fontChooser.GetFontData().GetChosenFont();

        // use this font in the Rich Edit
        m_LogoCodeControl->SetFont(font);

        // Set this as the new default font
        SetConfigurationFont("EditFont", font);

#if 0
        // Changing the font counts a modification as far as
        // the edit control is concerned, but not as far as
        // Logo is concerned.
        // Therefore, we must preserve the IsModified() state
        // ourselves to prevent spurious warnings when closing
        // an unedited document.
        bool editorIsModified = Editor->IsModified();

        Editor->SetWindowFont(hFont, true);

        if (!editorIsModified)
        {
            Editor->ClearModify();
        }
#endif
    }
}

// menu command handlers
void CWorkspaceEditor::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // let the window be destroyed
    Close(true);
}

void CWorkspaceEditor::OnUndo(wxCommandEvent& WXUNUSED(event))
{
    m_LogoCodeControl->Undo();
}

void CWorkspaceEditor::OnCut(wxCommandEvent& WXUNUSED(event))
{
    m_LogoCodeControl->Cut();
}

void CWorkspaceEditor::OnCopy(wxCommandEvent& WXUNUSED(event))
{
    m_LogoCodeControl->Copy();
}

void CWorkspaceEditor::OnPaste(wxCommandEvent& WXUNUSED(event))
{
    m_LogoCodeControl->Paste();
}

void CWorkspaceEditor::OnDelete(wxCommandEvent& WXUNUSED(event))
{
    m_LogoCodeControl->Clear();
}

void CWorkspaceEditor::OnClear(wxCommandEvent& WXUNUSED(event))
{
    // Delete everything in the editor
    m_LogoCodeControl->SelectAll();
    m_LogoCodeControl->Clear();
}

void CWorkspaceEditor::OnSelectAll(wxCommandEvent& WXUNUSED(event))
{
    m_LogoCodeControl->SelectAll();
}

void CWorkspaceEditor::OnFindMatchingParen(wxCommandEvent& WXUNUSED(event))
{
    m_LogoCodeControl->FindMatchingParen();
}

void CWorkspaceEditor::OnSelectMatchingParen(wxCommandEvent& WXUNUSED(event))
{
    m_LogoCodeControl->SelectMatchingParen();
}

void CWorkspaceEditor::OnClose(wxCloseEvent& event)
{
    // remove this window from the set of windows that the main window is tracking
    CFmsLogo::GetMainFrame()->CloseWorkspaceEditor(this);

    // Save the location and size of our window so we can
    // come back up in the same spot next time we are invoked.
    if (!IsIconized())
    {
        const wxRect windowRectangle = GetRect();

        SetConfigurationQuadruple(
            "Editor",
            windowRectangle.GetLeft(),
            windowRectangle.GetTop(),
            windowRectangle.GetWidth(),
            windowRectangle.GetHeight());
    }

    Destroy();
}
