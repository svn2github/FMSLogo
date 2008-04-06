#ifdef __WXMSW__
#  include <windows.h>  // for LOGFONT
#endif

#include <wx/menu.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/fontdlg.h>
#include <wx/fontutil.h>

#include "workspaceeditor.h"
#include "localizedstrings.h"
#include "guiutils.h"
#include "logocore.h" // for ARRAYSIZE
#include "utils.h"

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
    EVT_MENU(ID_EDALLEXIT,    CWorkspaceEditor::Quit)
    EVT_MENU(ID_EDITSETFONT,  CWorkspaceEditor::SetFont)
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

#ifdef __WXMSW__

    LOGFONT nativeFont;
    GetConfigurationFont("EditFont", nativeFont);

    // note: this was copied from wxNativeFontInfo::ToString() in src/msw/font.cpp
    wxString nativeInfo;
    nativeInfo.Printf(
        "%d;%ld;%ld;%ld;%ld;%ld;%d;%d;%d;%d;%d;%d;%d;%d;%s",
        0, // version
        nativeFont.lfHeight,
        nativeFont.lfWidth,
        nativeFont.lfEscapement,
        nativeFont.lfOrientation,
        nativeFont.lfWeight,
        nativeFont.lfItalic,
        nativeFont.lfUnderline,
        nativeFont.lfStrikeOut,
        nativeFont.lfCharSet,
        nativeFont.lfOutPrecision,
        nativeFont.lfClipPrecision,
        nativeFont.lfQuality,
        nativeFont.lfPitchAndFamily,
        nativeFont.lfFaceName);

    wxFont font;
    font.SetNativeFontInfo(nativeInfo);

#else

    wxFont font;
    font.SetFamily(wxFONTFAMILY_TELETYPE);

#endif

    m_RichTextControl->SetFont(font);
}

void CWorkspaceEditor::SetFont(wxCommandEvent& WXUNUSED(event) )
{
    wxFont font;

#ifdef __WXMSW__

    LOGFONT nativeFont;
    GetConfigurationFont("EditFont", nativeFont);

    // note: this was copied from wxNativeFontInfo::ToString() in src/msw/font.cpp
    wxString nativeInfo;
    nativeInfo.Printf(
        "%d;%ld;%ld;%ld;%ld;%ld;%d;%d;%d;%d;%d;%d;%d;%d;%s",
        0, // version
        nativeFont.lfHeight,
        nativeFont.lfWidth,
        nativeFont.lfEscapement,
        nativeFont.lfOrientation,
        nativeFont.lfWeight,
        nativeFont.lfItalic,
        nativeFont.lfUnderline,
        nativeFont.lfStrikeOut,
        nativeFont.lfCharSet,
        nativeFont.lfOutPrecision,
        nativeFont.lfClipPrecision,
        nativeFont.lfQuality,
        nativeFont.lfPitchAndFamily,
        nativeFont.lfFaceName);

    font.SetNativeFontInfo(nativeInfo);
#endif

    wxFontDialog  fontChooser;

    fontChooser.GetFontData().SetInitialFont(font);

    int rval = fontChooser.ShowModal();
    if (rval == wxID_OK)
    {
        // the user selected a new font
        font = fontChooser.GetFontData().GetChosenFont();

        // use this font
        m_RichTextControl->SetFont(font);

        // Set this as the new default font
#ifdef __WXMSW__

        // Get the LOGFONT struct from the wxFont
        const wxNativeFontInfo * nativeFontInfo = font.GetNativeFontInfo();
        if (nativeFontInfo != NULL)
        {
            // save the new font preference to persistent storage
            SetConfigurationFont("EditFont", nativeFontInfo->lf);
        }
#endif

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
void CWorkspaceEditor::Quit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}
