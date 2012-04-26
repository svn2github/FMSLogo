#ifdef __WXMSW__
#  include <windows.h>  // for LOGFONT
#endif

#include <wx/menu.h>
#include <wx/fontdlg.h>
#include <wx/msgdlg.h>

#include "workspaceeditor.h"
#include "commander.h"
#include "logocodectrl.h"
#include "localizedstrings.h"
#include "guiutils.h"
#include "fontutils.h"
#include "fmslogo.h"
#include "mainframe.h"
#include "utils.h"
#include "logocore.h"     // for ARRAYSIZE
#include "wrksp.h"        // for bExpert
#include "screenwindow.h" // for TraceOutput
#include "eval.h"         // for process_special_conditions
#include "startup.h"      // for TempPathName
#include "mem.h"          // for reref

enum
{
    KEY_CODE_CLOSE_BRACKET = 0xDD,
};

enum
{
    ID_FILESAVEANDEXIT = wxID_HIGHEST,
    ID_FILEPRINT,
    ID_FILEEXIT,
    ID_FILESAVETOWORKSPACE,
    ID_EDITUNDO,
    ID_EDITREDO,
    ID_EDITCUT,
    ID_EDITCOPY,
    ID_EDITPASTE,
    ID_EDITDELETE,
    ID_EDITCLEAR,
    ID_EDITSELECTALL,
    ID_SEARCHFIND,
    ID_SEARCHREPLACE,
    ID_SEARCHFINDNEXT,
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

    EVT_MENU(ID_FILEEXIT,            CWorkspaceEditor::OnExit)
    EVT_MENU(ID_FILESAVEANDEXIT,     CWorkspaceEditor::OnSaveAndExit)
    EVT_MENU(ID_FILEPRINT,           CWorkspaceEditor::OnPrint)


    EVT_MENU(ID_EDITUNDO,            CWorkspaceEditor::OnUndo)
    EVT_UPDATE_UI(ID_EDITUNDO,       CWorkspaceEditor::OnUpdateUndo)

    EVT_MENU(ID_EDITUNDO,            CWorkspaceEditor::OnUndo)
    EVT_UPDATE_UI(ID_EDITUNDO,       CWorkspaceEditor::OnUpdateUndo)
    EVT_MENU(ID_EDITREDO,            CWorkspaceEditor::OnRedo)
    EVT_UPDATE_UI(ID_EDITREDO,       CWorkspaceEditor::OnUpdateRedo)
    EVT_MENU(ID_EDITCUT,             CWorkspaceEditor::OnCut)
    EVT_UPDATE_UI(ID_EDITCUT,        CWorkspaceEditor::OnUpdateCut)
    EVT_MENU(ID_EDITCOPY,            CWorkspaceEditor::OnCopy)
    EVT_UPDATE_UI(ID_EDITCOPY,       CWorkspaceEditor::OnUpdateCopy)
    EVT_MENU(ID_EDITPASTE,           CWorkspaceEditor::OnPaste)
    EVT_UPDATE_UI(ID_EDITPASTE,      CWorkspaceEditor::OnUpdatePaste)
    EVT_MENU(ID_EDITDELETE,          CWorkspaceEditor::OnDelete)
    EVT_UPDATE_UI(ID_EDITDELETE,     CWorkspaceEditor::OnUpdateDelete)
    EVT_MENU(ID_EDITCLEAR,           CWorkspaceEditor::OnClear)
    EVT_UPDATE_UI(ID_EDITCLEAR,      CWorkspaceEditor::OnUpdateClear)
    EVT_MENU(ID_EDITSELECTALL,       CWorkspaceEditor::OnSelectAll)
    EVT_UPDATE_UI(ID_EDITSELECTALL,  CWorkspaceEditor::OnUpdateSelectAll)
    EVT_MENU(ID_EDITSELECTALL,       CWorkspaceEditor::OnSelectAll)
    EVT_UPDATE_UI(ID_EDITSELECTALL,  CWorkspaceEditor::OnUpdateSelectAll)

    EVT_MENU(ID_SEARCHFIND,          CWorkspaceEditor::OnFind)
    EVT_UPDATE_UI(ID_SEARCHFIND,     CWorkspaceEditor::OnUpdateFind)
    EVT_MENU(ID_SEARCHREPLACE,       CWorkspaceEditor::OnReplace)
    EVT_UPDATE_UI(ID_SEARCHREPLACE,  CWorkspaceEditor::OnUpdateReplace)
    EVT_MENU(ID_SEARCHFINDNEXT,      CWorkspaceEditor::OnFindNext)
    EVT_UPDATE_UI(ID_SEARCHFINDNEXT, CWorkspaceEditor::OnUpdateFindNext)

    EVT_MENU(ID_EDITSETFONT,         CWorkspaceEditor::OnSetFont)

    EVT_MENU(ID_FINDMATCHINGPAREN,   CWorkspaceEditor::OnFindMatchingParen)
    EVT_MENU(ID_SELECTMATCHINGPAREN, CWorkspaceEditor::OnSelectMatchingParen)
    EVT_CLOSE(CWorkspaceEditor::OnClose)

    EVT_FIND(wxID_ANY,             CWorkspaceEditor::OnFindDialog)
    EVT_FIND_NEXT(wxID_ANY,        CWorkspaceEditor::OnFindDialog)
    EVT_FIND_REPLACE(wxID_ANY,     CWorkspaceEditor::OnFindDialogReplace)
    EVT_FIND_REPLACE_ALL(wxID_ANY, CWorkspaceEditor::OnFindDialogReplaceAll)
    EVT_FIND_CLOSE(wxID_ANY,       CWorkspaceEditor::OnFindDialogClose)
END_EVENT_TABLE()


// The workspace frame's constructor
CWorkspaceEditor::CWorkspaceEditor(
    wxWindow       * Parent,
    const wxString & Title,
    const wxString & FileName,
    NODE           * EditArguments,
    bool             CheckForErrors
    )
    : wxFrame(
        Parent,
        wxID_ANY, 
        Title,
        wxDefaultPosition, 
        wxSize(420, 300),
        wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE),
    m_LogoCodeControl(NULL),
    m_FindReplaceDialog(NULL),
    m_FileName(FileName),
    m_EditArguments(EditArguments),
    m_CheckForErrors(CheckForErrors),
    m_ErrorDetected(false)
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
        {LOCALIZED_EDITOR_FILE_EXIT,            ID_FILEEXIT},
    };

    static const MENUITEM expertFileMenuItems[] = {
        {LOCALIZED_EDITOR_FILE_SAVEANDEXIT,     ID_FILESAVEANDEXIT},
        {LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE, ID_FILESAVETOWORKSPACE},
        {LOCALIZED_EDITOR_FILE_PRINT,           ID_FILEPRINT},
        {0},
        {LOCALIZED_EDITOR_FILE_EXIT,            ID_FILEEXIT},
    };

    static const MENUITEM editMenuItems[] = {
        {LOCALIZED_EDITOR_EDIT_UNDO,      ID_EDITUNDO},
        {LOCALIZED_EDITOR_EDIT_REDO,      ID_EDITREDO},
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
        {LOCALIZED_EDITOR_SEARCH_FIND,    ID_SEARCHFIND},
        {LOCALIZED_EDITOR_SEARCH_REPLACE, ID_SEARCHREPLACE},
        {LOCALIZED_EDITOR_SEARCH_NEXT,    ID_SEARCHFINDNEXT},
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

    // Configure the keyboard shortcuts
    wxAcceleratorEntry acceleratorEntries[3];

    // Ctrl+] moves to matching paren
    acceleratorEntries[0].Set(
        wxACCEL_CTRL,
        KEY_CODE_CLOSE_BRACKET,
        ID_FINDMATCHINGPAREN);

    // Ctrl+Shift+] selects to matching paren
    acceleratorEntries[1].Set(
        wxACCEL_CTRL | wxACCEL_SHIFT,
        KEY_CODE_CLOSE_BRACKET,
        ID_SELECTMATCHINGPAREN);

    // Ctrl+D saves and closes the editor
    acceleratorEntries[2].Set(
        wxACCEL_CTRL,
        'D',
        ID_FILESAVEANDEXIT);

    wxAcceleratorTable acceleratorTable(
        ARRAYSIZE(acceleratorEntries),
        acceleratorEntries);
    SetAcceleratorTable(acceleratorTable);

    SetFileName(FileName);
    if (!FileName.IsEmpty())
    {
        if (!Read())
        {
            // We couldn't read the file into the editor,
            // so unset the filename.
            SetFileName(wxEmptyString);
        }
    }

    // make sure that the editor is visible
    Iconize(false);
    Show();
    Raise();
}

bool CWorkspaceEditor::IsErrorDetected() const
{
    return m_ErrorDetected;
}


void CWorkspaceEditor::OnSetFont(wxCommandEvent& WXUNUSED(Event))
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

// Evaluates the contents of the editor as Logo code and sets the
// ErrorDetected flag if something went wrong.
bool CWorkspaceEditor::EndEdit()
{
    bool realsave = endedit();

    // check for errors
    m_ErrorDetected = process_special_conditions();

    return realsave;
}

//
// Saves the contents of the editor to the file currently being edited.
//
// returns true if the file was saved or if the contents were already saved.
//
bool CWorkspaceEditor::Save()
{
    if (!m_LogoCodeControl->IsDirty())
    {
        // The editor's contents are already in sync with
        // the workspace, so nothing needs to be done.
        return true;
    }

    // Save the contents.
    return Write();
}

// A helper routine for selecting a file to read from or
// write to.
const wxChar *
CWorkspaceEditor::SelectFile(
    const wxString & GivenFileName
    ) const
{
    if (!GivenFileName.IsEmpty())
    {
        // We were given a file name, so use it.
        return GivenFileName.c_str();
    }

    // The caller didn't supply a file name, so use the
    // file name that was supplied in the constructor.
    if (m_FileName.IsEmpty())
    {
        // No file name was ever given.
        return NULL;
    }

    return m_FileName.c_str();
}

//
// sets the file name of the window and updates the caption
//
void CWorkspaceEditor::SetFileName(const wxString & NewFileName)
{
    m_FileName = NewFileName;

    const wxChar * newTitle = m_FileName.IsEmpty() ?
        "("LOCALIZED_UNTITLED")" :
        m_FileName.c_str();

    const wxString & currentTitle = GetName();
    if (currentTitle.IsEmpty())
    {
        // The editor has no caption
        SetName(newTitle);
    }
    else
    {
        SetName(currentTitle + " - " + newTitle);
    }
}


//
// Read the contents of a previously-specified file into the editor
//
bool CWorkspaceEditor::Read(const wxString & FileName)
{
    const wxChar * fileName = SelectFile(FileName);
    if (fileName == NULL)
    {
        // No file name was given.
        return false;
    }

    m_LogoCodeControl->ClearAll();
    m_LogoCodeControl->EmptyUndoBuffer();
    m_LogoCodeControl->SetSavePoint();
    m_LogoCodeControl->Cancel();
    m_LogoCodeControl->SetUndoCollection(0);

    // TODO: use a wxWidgets class for I/O instead of the C runtime
    bool success = false;
    FILE * file = fopen(fileName, "rb");
    if (file != NULL)
    {
        // read the entire file in 1 KB blocks
        char data[1025];

        int blockLength = fread(data, 1, sizeof(data) - 1, file);
        while (blockLength > 0)
        {
            data[blockLength] = '\0';
            m_LogoCodeControl->AddTextRaw(data);

            blockLength = fread(data, 1, sizeof(data) - 1, file);
        }

        if (!ferror(file))
        {
            success = true;
        }

        fclose(file);
    }

    m_LogoCodeControl->SetUndoCollection(true);
    m_LogoCodeControl->SetFocus();
    m_LogoCodeControl->EmptyUndoBuffer();
    m_LogoCodeControl->SetSavePoint();
    m_LogoCodeControl->GotoPos(0);

    if (!success)
    {
        // Something when wrong when trying to open the file.
        // Report the error to the user.
        const wxString & errorMessage = wxString::Format(
            LOCALIZED_ERROR_CANTREADFILE,
            fileName);

        wxMessageBox(
            errorMessage,
            LOCALIZED_GENERAL_PRODUCTNAME,
            wxICON_EXCLAMATION | wxOK);
    }

    return success;
}

//
// Writes the contents of the editor to a previously-specified file.
//
bool
CWorkspaceEditor::Write(
    const wxString & FileName
    )
{
    const wxChar * fileName = SelectFile(FileName);
    if (fileName == NULL)
    {
        // No file name was given.
        return false;
    }

    // TODO: Use wxWidgets file I/O instead of the C runtime.
    FILE* file = fopen(fileName, "wb");
    if (file == NULL) 
    {
        // Something when wrong when trying to open the file.
        // Report the error to the user.
        const wxString & errorMessage = wxString::Format(
            LOCALIZED_ERROR_CANTWRITEFILE,
            fileName);

        wxMessageBox(
            errorMessage,
            LOCALIZED_GENERAL_PRODUCTNAME,
            wxICON_EXCLAMATION | wxOK);

        return false;
    }

    bool success = true;

    const size_t WRITE_BLOCK_SIZE = 1024;
    int lengthDoc = m_LogoCodeControl->GetTextLength();
    for (int i = 0;
         i < lengthDoc;
         i += WRITE_BLOCK_SIZE)
    {
        size_t grabSize = lengthDoc - i;
        if (WRITE_BLOCK_SIZE < grabSize)
        {
            grabSize = WRITE_BLOCK_SIZE;
        }

        // Get this block from the editor
        const wxString & textBlock = m_LogoCodeControl->GetTextRange(
            i,
            i + grabSize);

        size_t bytesWritten = fwrite(
            textBlock.GetData(),
            sizeof(wxChar),
            grabSize,
            file);
        if (bytesWritten != grabSize)
        {
            // Not all of the data was written.
            success = false;
            break;
        }
    }

    fclose(file);

    if (success)
    {
        m_LogoCodeControl->SetSavePoint();
    }

    return success;
}

// menu command handlers
void CWorkspaceEditor::OnExit(wxCommandEvent& WXUNUSED(Event))
{
    // let the window be destroyed
    Close(true);
}

void CWorkspaceEditor::OnSaveAndExit(wxCommandEvent& Event)
{
    Save();
    OnExit(Event);
}

// Prints the contents of the editor
void CWorkspaceEditor::OnPrint(wxCommandEvent& WXUNUSED(Event))
{
    m_LogoCodeControl->Print();
}

void CWorkspaceEditor::OnUndo(wxCommandEvent& WXUNUSED(Event))
{
    m_LogoCodeControl->Undo();
}

void CWorkspaceEditor::OnUpdateUndo(wxUpdateUIEvent& Event)
{
    Event.Enable(m_LogoCodeControl->CanUndo());
}

void CWorkspaceEditor::OnRedo(wxCommandEvent& WXUNUSED(Event))
{
    m_LogoCodeControl->Redo();
}

void CWorkspaceEditor::OnUpdateRedo(wxUpdateUIEvent& Event)
{
    Event.Enable(m_LogoCodeControl->CanRedo());
}

void CWorkspaceEditor::OnCut(wxCommandEvent& WXUNUSED(Event))
{
    m_LogoCodeControl->Cut();
}

void CWorkspaceEditor::OnUpdateCut(wxUpdateUIEvent& Event)
{
    Event.Enable(m_LogoCodeControl->IsTextSelected());
}

void CWorkspaceEditor::OnCopy(wxCommandEvent& WXUNUSED(Event))
{
    m_LogoCodeControl->Copy();
}

void CWorkspaceEditor::OnUpdateCopy(wxUpdateUIEvent& Event)
{
    Event.Enable(m_LogoCodeControl->IsTextSelected());
}

void CWorkspaceEditor::OnPaste(wxCommandEvent& WXUNUSED(Event))
{
    m_LogoCodeControl->Paste();
}

void CWorkspaceEditor::OnUpdatePaste(wxUpdateUIEvent& Event)
{
    Event.Enable(m_LogoCodeControl->CanPaste());
}

void CWorkspaceEditor::OnDelete(wxCommandEvent& WXUNUSED(Event))
{
    m_LogoCodeControl->Clear();
}

void CWorkspaceEditor::OnUpdateDelete(wxUpdateUIEvent& Event)
{
    Event.Enable(m_LogoCodeControl->IsTextSelected());
}

void CWorkspaceEditor::OnClear(wxCommandEvent& WXUNUSED(Event))
{
    // Delete everything in the editor
    m_LogoCodeControl->SelectAll();
    m_LogoCodeControl->Clear();
}

void CWorkspaceEditor::OnUpdateClear(wxUpdateUIEvent& Event)
{
    // Enable if text exists
    Event.Enable(m_LogoCodeControl->GetLength() != 0);
}

void CWorkspaceEditor::OnSelectAll(wxCommandEvent& WXUNUSED(Event))
{
    m_LogoCodeControl->SelectAll();
}

void CWorkspaceEditor::OnUpdateSelectAll(wxUpdateUIEvent& Event)
{
    // Enable if text exists
    Event.Enable(m_LogoCodeControl->GetLength() != 0);
}

void CWorkspaceEditor::OnFind(wxCommandEvent& WXUNUSED(Event))
{
    // Create and show the search dialog box.
    // Note that this routine should not be callable if the search
    // dialog box is already created.
    if (m_FindReplaceDialog == NULL)
    {
        m_FindReplaceData.SetFlags(wxFR_DOWN); // default to searching down
        m_FindReplaceDialog = new wxFindReplaceDialog(
            this,
            &m_FindReplaceData,
            LOCALIZED_EDITOR_TITLE_FIND);

        m_FindReplaceDialog->Show();
    }
}

void CWorkspaceEditor::OnUpdateFind(wxUpdateUIEvent& Event)
{
    // Once the dialog box is showing, disable selecting it.
    Event.Enable(m_FindReplaceDialog == NULL);
}

void CWorkspaceEditor::OnReplace(wxCommandEvent& WXUNUSED(Event))
{
    // Create and show the search dialog box.
    // Note that this routine should not be callable if the search
    // dialog box is already created.
    if (m_FindReplaceDialog == NULL)
    {
        m_FindReplaceData.SetFlags(wxFR_DOWN); // default to searching down
        m_FindReplaceDialog = new wxFindReplaceDialog(
            this,
            &m_FindReplaceData,
            LOCALIZED_EDITOR_TITLE_REPLACE,
            wxFR_REPLACEDIALOG);

        m_FindReplaceDialog->Show();
    }
}

void CWorkspaceEditor::OnUpdateReplace(wxUpdateUIEvent& Event)
{
    // Once the dialog box is showing, disable selecting it.
    Event.Enable(m_FindReplaceDialog == NULL);
}

void CWorkspaceEditor::OnFindNext(wxCommandEvent& WXUNUSED(Event))
{
    m_LogoCodeControl->Find(
        static_cast<wxFindReplaceFlags>(m_FindReplaceData.GetFlags()),
        m_FindReplaceData.GetFindString());
}

void CWorkspaceEditor::OnUpdateFindNext(wxUpdateUIEvent& Event)
{
    // Enable the option if we have a string to look for.
    Event.Enable(!m_FindReplaceData.GetFindString().IsEmpty());
}

void CWorkspaceEditor::OnFindDialog(wxFindDialogEvent & WXUNUSED(Event))
{
    m_LogoCodeControl->Find(
        static_cast<wxFindReplaceFlags>(m_FindReplaceData.GetFlags()),
        m_FindReplaceData.GetFindString());
}

void CWorkspaceEditor::OnFindDialogReplace(wxFindDialogEvent& WXUNUSED(Event))
{
    m_LogoCodeControl->Replace(
        static_cast<wxFindReplaceFlags>(m_FindReplaceData.GetFlags()),
        m_FindReplaceData.GetFindString(),
        m_FindReplaceData.GetReplaceString());
}

void CWorkspaceEditor::OnFindDialogReplaceAll(wxFindDialogEvent& WXUNUSED(Event))
{
    m_LogoCodeControl->ReplaceAll(
        static_cast<wxFindReplaceFlags>(m_FindReplaceData.GetFlags()),
        m_FindReplaceData.GetFindString(),
        m_FindReplaceData.GetReplaceString());
}

void CWorkspaceEditor::OnFindDialogClose(wxFindDialogEvent& WXUNUSED(Event))
{
    m_FindReplaceDialog->Destroy();
    m_FindReplaceDialog = NULL;
}

void CWorkspaceEditor::OnFindMatchingParen(wxCommandEvent& WXUNUSED(Event))
{
    m_LogoCodeControl->FindMatchingParen();
}

void CWorkspaceEditor::OnSelectMatchingParen(wxCommandEvent& WXUNUSED(Event))
{
    m_LogoCodeControl->SelectMatchingParen();
}

void CWorkspaceEditor::OnClose(wxCloseEvent& Event)
{
    // remove this window from the set of windows that the main window is tracking
    CFmsLogo::GetMainFrame()->CloseWorkspaceEditor(this);

    if (m_EditArguments != NIL || m_CheckForErrors)
    {
        CCommander * commander = CFmsLogo::GetMainFrame()->GetCommander();

        int realsave = EndEdit();
        if (m_ErrorDetected)
        {
            // Notify the user that:
            // 1) The changes in the editor failed to load
            // 2) The cursor is positioned just after the last 
            //    successful definition
            //
            // Ask if they want to reedit.
            if (::wxMessageBox(
                    LOCALIZED_CURSORISATLASTGOODDEFINITION"\n"
                        "\n"
                        LOCALIZED_RETURNTOEDIT,
                    LOCALIZED_EDITFAILEDTOLOAD,
                    wxYES_NO | wxICON_ERROR,
                    commander) == wxYES)
            {
                // Open up another editor
                CFmsLogo::GetMainFrame()->PopupEditor(
                    TempPathName,
                    m_EditArguments,
                    m_CheckForErrors);
                unlink(TempPathName);
                //TODO: IsDirty = true;
            }
            else
            {
                // The user doesn't care about the error.
                m_ErrorDetected = false;
                commander->GiveControlToInputBox();
            }
        }
        else
        {
            // no errors happened
            if (m_EditArguments != NIL)
            {
                // check for quit before erasing
                if (realsave)
                {
                    lerase(m_EditArguments);

                    // Since we erased part of the workspace,
                    // we must load again, but no errors
                    endedit();
                }

                // free up m_EditArguments
                m_EditArguments = reref(m_EditArguments, NIL);
            }

            // Delete the temporary file which held the workspace
            // while we were re-reading it.
            unlink(TempPathName);

            // Give focus back to the commander so that the user
            // can give Logo more commands.
            commander->GiveControlToInputBox();
        }
    }
    else
    {
#if 0 // TODO
        // else execute callback for user callable editor
        callthing *callevent = callthing::CreateFunctionEvent(edit_editexit);
        calllists.insert(callevent);
#endif
    }

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
