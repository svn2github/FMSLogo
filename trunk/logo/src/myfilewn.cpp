/*
 *   Copyright (C) 1995 by the Regents of the University of California
 *   Copyright (C) 1995 by George Mills
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <stdio.h>
#include <dir.h>

#include "myfilewn.h"

#include "Platform.h"
#include "scintilla.h"
#include "SciLexer.h"

#include <owl/richedit.h>

#include "error.h"
#include "main.h"
#include "startup.h"
#include "cursor.h"
#include "eval.h"
#include "logorc.h"
#include "utils.h"
#include "localizedstrings.h"
#include "wrksp.h"

#include "mainframe.h"
#include "cmdwind.h"
#include "graphwin.h" // for do_help()
#include "debugheap.h"


TMyFileWindow::TMyFileWindow(
    TWindow *Parent,
    LPCSTR   Title,
    LPCSTR   TheFilename,
    NODE *   Args,        // consumes a reference
    bool     CheckForErrors
    ) :
    TFrameWindow(Parent, Title, 0, false),
    args_list(Args),
    FileName(NULL),
    check_for_errors(CheckForErrors),
    IsDirty(false),
    SearchDialog(NULL)
{
    Attr.AccelTable = "IDM_FILECOMMANDS";
    Attr.Style = WS_VISIBLE | WS_POPUPWINDOW | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
    FileName = TheFilename ? strnewdup(TheFilename) : NULL;
}

TMyFileWindow::~TMyFileWindow()
{
    if (HWindow)
    {
        HMENU oldMenu = GetMenu();
        if (oldMenu)
        {
            ::DestroyMenu(oldMenu);
        }
    }

    delete FileName;
}

bool TMyFileWindow::TranslateKeyboardShortcut(MSG & Message)
{
    return ::TranslateAccelerator(HWindow, hAccel, &Message) ? true : false;
}

LRESULT TMyFileWindow::SendEditor(UINT Msg, WPARAM wParam, LPARAM lParam)
{
    return ::SendMessage(ScintillaEditor, Msg, wParam, lParam);
}

//
// Saves the contents of the editor to the file currently being edited.
//
// returns true if the file was saved or if the contents were already saved.
//
bool TMyFileWindow::Save()
{
    if (IsDirty)
    {
        if (FileName != NULL)
        {
            return Write();
        }
    }
    else
    {
        // the editor's contents haven't been changed
        return true;
    }

    return false;
}

// Allocates a buffer and returns the selected text.
// The buffer must be deallocated with delete [].
char * TMyFileWindow::GetSelectedText()
{
    const int start = SendEditor(SCI_GETSELECTIONSTART);
    const int end   = SendEditor(SCI_GETSELECTIONEND);

    size_t selectedTextLength = abs(end - start);
    char * selectedText = new char[selectedTextLength + 1];
    if (selectedText != NULL)
    {
        SendEditor(SCI_GETSELTEXT, 0, reinterpret_cast<LPARAM>(selectedText));
        selectedText[selectedTextLength] = '\0';
    }

    return selectedText;
}

//
// Read the contents of a previously-specified file into the editor
//
bool TMyFileWindow::Read(const char *fileName)
{
    if (!fileName)
    {
        if (FileName)
        {
            fileName = FileName;
        }
        else
        {
            return false;
        }
    }

    SendEditor(SCI_CLEARALL);
    SendEditor(SCI_EMPTYUNDOBUFFER);
    SendEditor(SCI_SETSAVEPOINT);
    SendEditor(SCI_CANCEL);
    SendEditor(SCI_SETUNDOCOLLECTION, 0);

    bool success = false;
    FILE * file = fopen(fileName, "rb");
    if (file != NULL)
    {
        // read the entire file in 1 KB blocks
        char data[1024];

        int blockLength = fread(data, 1, sizeof(data), file);
        while (blockLength > 0)
        {
            SendEditor(
                SCI_ADDTEXT,
                blockLength,
                reinterpret_cast<LPARAM>(data));

            blockLength = fread(data, 1, sizeof(data), file);
        }

        if (!ferror(file))
        {
            success = true;
        }

        fclose(file);
    }
    
    SendEditor(SCI_SETUNDOCOLLECTION, 1);
    ::SetFocus(ScintillaEditor);
    SendEditor(SCI_EMPTYUNDOBUFFER);
    SendEditor(SCI_SETSAVEPOINT);
    SendEditor(SCI_GOTOPOS, 0);

    // SCI_GOTOPOS is documented to scroll the position into view, but
    // after reading a large file, the second line is at the top of the
    // editor, not the first one.  To fix this, we make another call to
    // scroll the caret into view.
    SendEditor(SCI_SCROLLCARET);

    if (!success)
    {
        char err[MAXPATH + 33];

        wsprintf(err, LOCALIZED_ERROR_CANTREADFILE, fileName);
        MessageBox(err, GetModule()->GetName(), MB_ICONEXCLAMATION | MB_OK);
    }

    return success;
}

//
// writes the contents of the editor to a previously-specified file
//
bool TMyFileWindow::Write(const char * fileName)
{
    if (!fileName)
    {
        if (FileName)
        {
            fileName = FileName;
        }
        else
        {
            return false;
        }
    }

    FILE* file = fopen(fileName, "wb");
    if (file == NULL) 
    {
        char msg[MAXPATH + 33];

        wsprintf(msg, LOCALIZED_ERROR_CANTWRITEFILE, fileName);
        MessageBox(msg, GetModule()->GetName(), MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    bool success = false;

    char data[1024];
    int lengthDoc = SendEditor(SCI_GETLENGTH);
    for (int i = 0; i < lengthDoc; i += sizeof(data) - 1)
    {
        int grabSize = lengthDoc - i;
        if (sizeof(data) - 1 < grabSize)
        {
            grabSize = sizeof(data) - 1;
        }

        // get this block from the editor
        TEXTRANGE tr;
        tr.chrg.cpMin = i;
        tr.chrg.cpMax = i + grabSize;
        tr.lpstrText  = data;
        SendEditor(SCI_GETTEXTRANGE, 0, reinterpret_cast<LPARAM>(&tr));

        size_t bytesWritten = fwrite(
            data,
            sizeof(char),
            grabSize,
            file);
        if (bytesWritten == grabSize)
        {
            success = true;
        }
    }

    fclose(file);
    SendEditor(SCI_SETSAVEPOINT);

    return success;
}


void TMyFileWindow::CMExit()
{
    // here on FILE-EXIT in editor
    SendMessage(WM_CLOSE);
}

void TMyFileWindow::CMSaveAndExit()
{
    Save();
    CMExit();
}

void TMyFileWindow::CMSaveToWorkspace()
{
    Save();

    if (args_list != NULL)
    {
        EndEdit();

        unlink(TempPathName);

        if (error_happen)
        {
            // notify the user that:
            // 1) The changes in the editor failed to load
            // 2) The cursor is positioned just after the last
            //    successful definition
            MainWindowx->CommandWindow->MessageBox(
                LOCALIZED_CURSORISATLASTGOODDEFINITION,
                LOCALIZED_EDITFAILEDTOLOAD,
                MB_OK | MB_ICONERROR);

            // "force" a change so that we're still in a "dirty" state
            ReopenAfterError();
        }
    }
}

void TMyFileWindow::DoSearch()
{
    // set the search flags (whole word, match case).
    int searchFlags = 0;
    if (SearchData.Flags & FR_MATCHCASE)
    {
        searchFlags |= SCFIND_MATCHCASE;
    }
    if (SearchData.Flags & FR_WHOLEWORD)
    {
        searchFlags |= SCFIND_WHOLEWORD;
    }
    SendEditor(SCI_SETSEARCHFLAGS, searchFlags);

    int searchStringLength = strlen(SearchData.FindWhat);

    if (SearchData.Flags & FR_REPLACEALL)
    {
        // The user selected "Replace All", so the selection
        // goes from the beginning to the end of the document.
        SendEditor(SCI_SETTARGETSTART, 0);
        SendEditor(SCI_SETTARGETEND,   SendEditor(SCI_GETLENGTH));

        int replaceWithLength = strlen(SearchData.ReplaceWith);

        int location = SendEditor(
            SCI_SEARCHINTARGET,
            searchStringLength,
            reinterpret_cast<LPARAM>(SearchData.FindWhat));
        while (location != -1)
        {
            // Found it. Replace the string
            SendEditor(
                SCI_REPLACETARGET,
                replaceWithLength,
                reinterpret_cast<LPARAM>(SearchData.ReplaceWith));

            // Move the selection so that we can repeat the search
            SendEditor(SCI_SETTARGETSTART, location + replaceWithLength);
            SendEditor(SCI_SETTARGETEND,   SendEditor(SCI_GETLENGTH));

            // Repeat the search
            location = SendEditor(
                SCI_SEARCHINTARGET,
                searchStringLength,
                reinterpret_cast<LPARAM>(SearchData.FindWhat));
        }
    }
    else
    {
        if (SearchData.Flags & FR_REPLACE)
        {
            // We are doing a find&replace operation.
            // If the string to be replaced is currently selected, then replace it.
            // After the replacement is performed, search for the next occurence.
            char * selectedText = GetSelectedText();
            if (selectedText != NULL)
            {
                // Found it.  Now figure out what to do with it.
                int cmp;
                if (SearchData.Flags & FR_MATCHCASE)
                {
                    // Do a case-sensitive comparison
                    cmp = strcmp(selectedText, SearchData.FindWhat);
                }
                else
                {
                    // Do a case-insensitive comparison
                    cmp = stricmp(selectedText, SearchData.FindWhat);
                }

                if (cmp == 0)
                {
                    int selectionStart = SendEditor(SCI_GETSELECTIONSTART);
                    int selectionEnd   = SendEditor(SCI_GETSELECTIONEND);

                    // This is a match.  Replace the string.
                    SendEditor(SCI_SETTARGETSTART, selectionStart);
                    SendEditor(SCI_SETTARGETEND,   selectionEnd);

                    int replaceWithLength = strlen(SearchData.ReplaceWith);
                    SendEditor(
                        SCI_REPLACETARGET,
                        replaceWithLength,
                        reinterpret_cast<LPARAM>(SearchData.ReplaceWith));

                    // update the selection to be what we just inserted.
                    SendEditor(SCI_SETSEL, selectionStart, selectionStart + replaceWithLength);
                }

                delete [] selectedText;
            }
        }

        if (SearchData.Flags & FR_DOWN)
        {
            // We're searching down, so the range goes from the
            // current position to the end.
            SendEditor(SCI_SETTARGETSTART, SendEditor(SCI_GETSELECTIONEND));
            SendEditor(SCI_SETTARGETEND,   SendEditor(SCI_GETLENGTH));
        }
        else
        {
            // We're searching up, so the range goes from the
            // current position to the beginning.
            SendEditor(SCI_SETTARGETSTART, SendEditor(SCI_GETSELECTIONSTART));
            SendEditor(SCI_SETTARGETEND,   0);
        }

        // Perform the search.
        int location = SendEditor(
            SCI_SEARCHINTARGET,
            searchStringLength,
            reinterpret_cast<LPARAM>(SearchData.FindWhat));
        if (location != -1)
        {
            // Found it.  Select the string.
            SendEditor(SCI_SETSEL, location, location + searchStringLength);
        }
        else
        {
            // Notify the user that we were unable to find it.
            char err[MAXPATH + 33];
            wsprintf(err, LOCALIZED_STRINGTABLE_CANNOTFINDSTRING, SearchData.FindWhat);

            HWND parent;
            if (SearchDialog)
            {
                parent = SearchDialog->HWindow;
            }
            else
            {
                parent = HWindow;
            }

            ::MessageBox(parent, err, GetModule()->GetName(), MB_ICONWARNING | MB_OK);
        }
    }
}

LRESULT TMyFileWindow::EvFindMsg(WPARAM, LPARAM lParam)
{
    if (SearchDialog != NULL)
    {
        // Update SearchData with the latest FINDREPLACE struct
        SearchDialog->UpdateData(lParam);

        // is the dialog box closing?
        if (SearchData.Flags & FR_DIALOGTERM)
        {
            SearchDialog = NULL;
        }
        else
        {
            DoSearch();
        }
    }

    return 0;
}

void TMyFileWindow::CMEditFind()
{
    // Create and show the search dialog box.
    // Note that this routine should not be callable if the search
    // dialog box is already created.
    if (SearchDialog == NULL)
    {
        SearchData.Flags |= FR_DOWN; // default to searching down
        SearchDialog = new TFindDialog(this, SearchData);
        SearchDialog->Create();
    }
}
void TMyFileWindow::CMEditReplace()
{
  
    // Create and show the search dialog box.
    // Note that this routine should not be callable if the search
    // dialog box is already created.
    if (SearchDialog == NULL)
    {
        SearchData.Flags |= FR_DOWN; // default to searching down
        SearchDialog = new TReplaceDialog(this, SearchData);
        SearchDialog->Create();
    }
}

void TMyFileWindow::CMEditFindNext()
{
    DoSearch();
}

void TMyFileWindow::CMEditFindReplaceEnable(TCommandEnabler& commandHandler)
{
    // once the dialog box is showing, disable selecting it.
    commandHandler.Enable(SearchDialog == NULL);
}

void TMyFileWindow::CMEditFindNextEnable(TCommandEnabler& commandHandler)
{
    // Enable this if there is a search string
    commandHandler.Enable(SearchData.FindWhat[0] != '\0');
}

void TMyFileWindow::CMHelpEditor()
{
    do_help("Editor");
}

void TMyFileWindow::CMHelp()
{
    MainWindowx->CMHelp();
}

void TMyFileWindow::CMHelpSelection()
{
    bool didHelp = false;

    // get the keyword selected
    int start = SendEditor(SCI_GETSELECTIONSTART);
    int end   = SendEditor(SCI_GETSELECTIONEND);
    if (start < end && end < start + 80)
    {
        char buffer[100] = {0}; // NUL-terminate

        SendEditor(SCI_GETSELTEXT, 0, reinterpret_cast<LPARAM>(buffer));

        char * selection = buffer;

        // remove leading whitespace
        while (IsSpace(selection[0]))
        {
            selection++;
        }

        // strip off everything after the first word
        char * ptr = selection;
        while (*ptr != '\0' && !IsSpace(*ptr))
        {
            ptr++;
        }

        // if there was some non-space selected,
        if (ptr != selection)
        {
            // truncate the selection after the first word
            *ptr = '\0';

            // and look it up in the online help
            do_help(selection);
            didHelp = true;
        }
    }

    if (!didHelp)
    {
        do_help(NULL);
    }
}

void TMyFileWindow::CMTest()
{
    char * theText = GetSelectedText();

    char * ptr = theText;

    // strip comments
    bool more = true;
    while (more)
    {
        char * ptr2 = strchr(ptr, ';');

        if (ptr2 != NULL)
        {
            // overwrite the comment character with a space
            *ptr2 = ' ';

            // put whitespace over everything until the end-of-string
            // the end-of-line, or a comment continuer
            while (*ptr2 != '\0' &&
                   *ptr2 != '\n' &&
                   *ptr2 != '\r' &&
                   *ptr2 != '~')
            {
                *ptr2++ = ' ';
            }
        }
        else
        {
            more = false;
        }
    }

    // paste continuation
    more = true;
    while (more)
    {
        char * ptr2 = strchr(ptr, '~');

        if (ptr2 != NULL)
        {
            *ptr2 = ' ';
            char * ptr3 = strchr(ptr2, '\n');
            if (ptr3 != NULL)
            {
                *ptr3 = ' ';
                *(ptr3 - 1) = ' ';
            }
        }
        else
        {
            more = false;
        }
    }

    // for each real line left execute it
    more = true;
    while (more)
    {
        char * ptr2 = strchr(ptr, '\n');

        if (ptr2 != NULL)
        {
            *ptr2 = '\0';
            *(ptr2 - 1) = '\0';
        }

        putcombobox(ptr);
        do_execution(ptr);

        if (ptr2 != NULL)
        {
            ptr = ptr2 + 1;
        }
        else
        {
            more = false;
        }
    }

    delete [] theText;
}

//
// sets the file name of the window and updates the caption
//
void TMyFileWindow::SetFileName(const char *fileName)
{
    // BUG: this should be strcmp while accounting for NULL
    if (FileName != fileName)
    {
        delete FileName;
        FileName = fileName ? strnewdup(fileName) : 0;
    }

    const char *p = FileName ? FileName : "("LOCALIZED_UNTITLED")";

    if (Title == NULL || *Title == '\0')
    {
        SetWindowText(p);
    }
    else
    {
        char newCaption[256];

        newCaption[0] = '\0';
        strncat(newCaption, Title, sizeof(newCaption) - strlen(newCaption));
        strncat(newCaption, " - ", sizeof(newCaption) - strlen(newCaption));
        strncat(newCaption, p,     sizeof(newCaption) - strlen(newCaption));

        SetWindowText(newCaption);
    }
}

void TMyFileWindow::SetEditorFont(const LOGFONT & LogFont)
{
    // set the font face name
    SendEditor(
        SCI_STYLESETFONT,
        STYLE_DEFAULT,
        reinterpret_cast<LPARAM>(LogFont.lfFaceName));

    // set the height in points
    int logPixelsY = GetDeviceCaps(GetDC(ScintillaEditor), LOGPIXELSY);
    int PointSize  = (logPixelsY == 0) ? 10 : -72 * LogFont.lfHeight / logPixelsY;
    SendEditor(SCI_STYLESETSIZE, STYLE_DEFAULT, PointSize);

    // set some of the font's attributes
    SendEditor(SCI_STYLESETBOLD,      STYLE_DEFAULT, FW_BOLD <= LogFont.lfWeight);
    SendEditor(SCI_STYLESETITALIC,    STYLE_DEFAULT, LogFont.lfItalic    ? true : false);
    SendEditor(SCI_STYLESETUNDERLINE, STYLE_DEFAULT, LogFont.lfUnderline ? true : false);

    // apply the font
    SendEditor(SCI_STYLECLEARALL);

    const RGBCOLOR black   = RGB(0,0,0);
    const RGBCOLOR white   = RGB(0xff,0xff,0xff);
    const RGBCOLOR darkgreen = RGB(0,0x80,0);
    const RGBCOLOR darkred   = RGB(0x80, 0, 0);
    const RGBCOLOR red       = RGB(0xFF, 0, 0);
    const RGBCOLOR lightgrey = RGB(0xCC, 0xCC, 0xCC);
    const RGBCOLOR lightblue = RGB(200,  242,  255);
    const RGBCOLOR darkblue  = RGB(  0,  0,   0x80);

    SendEditor(SCI_STYLESETFORE, SCE_FMS_COMMENT,          darkgreen);
    SendEditor(SCI_STYLESETFORE, SCE_FMS_COMMENTBACKSLASH, darkgreen);
    SendEditor(SCI_STYLESETFORE, SCE_FMS_STRING,         darkred);
    SendEditor(SCI_STYLESETFORE, SCE_FMS_STRING_VBAR,    darkred);

    SendEditor(SCI_STYLESETFORE, SCE_FMS_VARIABLE,       darkblue);
    SendEditor(SCI_STYLESETFORE, SCE_FMS_VARIABLE_VBAR,  darkblue);

    SendEditor(SCI_STYLESETFORE, STYLE_BRACELIGHT,    darkgreen);
    SendEditor(SCI_STYLESETBACK, STYLE_BRACELIGHT,    lightblue);

    SendEditor(SCI_STYLESETFORE, STYLE_BRACEBAD,      red);
    SendEditor(SCI_STYLESETBACK, STYLE_BRACEBAD,      lightblue);
}


void TMyFileWindow::SetupWindow()
{
    TFrameWindow::SetupWindow();

    //
    // Construct the main menu
    //
    static const MENUITEM defaultFileMenuItems[] = {
        {LOCALIZED_EDITOR_FILE_SAVEANDEXIT,     CM_FILESAVEANDEXIT},
        {LOCALIZED_EDITOR_FILE_PRINT,           CM_FILEPRINT},
        {0},
        {LOCALIZED_EDITOR_FILE_EXIT,            CM_EDALLEXIT},
    };

    static const MENUITEM expertFileMenuItems[] = {
        {LOCALIZED_EDITOR_FILE_SAVEANDEXIT,     CM_FILESAVEANDEXIT},
        {LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE, CM_FILESAVETOWORKSPACE},
        {LOCALIZED_EDITOR_FILE_PRINT,           CM_FILEPRINT},
        {0},
        {LOCALIZED_EDITOR_FILE_EXIT,            CM_EDALLEXIT},
    };

    static const MENUITEM editMenuItems[] = {
        {LOCALIZED_EDITOR_EDIT_UNDO,      CM_EDITUNDO},
        {LOCALIZED_EDITOR_EDIT_REDO,      CM_EDITREDO},
        {0},
        {LOCALIZED_EDITOR_EDIT_CUT,       CM_EDITCUT},
        {LOCALIZED_EDITOR_EDIT_COPY,      CM_EDITCOPY},
        {LOCALIZED_EDITOR_EDIT_PASTE,     CM_EDITPASTE},
        {LOCALIZED_EDITOR_EDIT_DELETE,    CM_EDITDELETE},
        {0},
        {LOCALIZED_EDITOR_EDIT_CLEARALL,  CM_EDITCLEAR},
        {LOCALIZED_EDITOR_EDIT_SELECTALL, CM_EDITSELECTALL},
    };

    static const MENUITEM searchMenuItems[] = {
        {LOCALIZED_EDITOR_SEARCH_FIND,    CM_EDITFIND},
        {LOCALIZED_EDITOR_SEARCH_REPLACE, CM_EDITREPLACE},
        {LOCALIZED_EDITOR_SEARCH_NEXT,    CM_EDITFINDNEXT},
    };

    static const MENUITEM setMenuItems[] = {
        {LOCALIZED_EDITOR_SET_FONT,       CM_EDITSETFONT}
    };
 
    static const MENUITEM helpMenuItems[] = {
        {LOCALIZED_EDITOR_HELP_INDEX,       CM_HELP},
        {LOCALIZED_EDITOR_HELP_EDITOR,      CM_HELPEDIT},
        {LOCALIZED_EDITOR_HELP_TOPICSEARCH, CM_HELPEDIT_TOPIC},
    };


    TMenu mainMenu(CreateMenu());

    if (bExpert)
    {
        AppendPopupMenu(
            mainMenu, 
            LOCALIZED_EDITOR_FILE,
            expertFileMenuItems,
            ARRAYSIZE(expertFileMenuItems));
    }
    else
    {
        AppendPopupMenu(
            mainMenu, 
            LOCALIZED_EDITOR_FILE,
            defaultFileMenuItems,
            ARRAYSIZE(defaultFileMenuItems));
    }
    AppendPopupMenu(mainMenu, LOCALIZED_EDITOR_EDIT,   editMenuItems,   ARRAYSIZE(editMenuItems));
    AppendPopupMenu(mainMenu, LOCALIZED_EDITOR_SEARCH, searchMenuItems, ARRAYSIZE(searchMenuItems));
    AppendPopupMenu(mainMenu, LOCALIZED_EDITOR_SET,    setMenuItems,    ARRAYSIZE(setMenuItems));
    mainMenu.AppendMenu(MF_STRING, CM_TEST, LOCALIZED_EDITOR_TEST_BUTTON);
    AppendPopupMenu(mainMenu, LOCALIZED_EDITOR_HELP,   helpMenuItems,   ARRAYSIZE(helpMenuItems));
    SetMenu(mainMenu);

    ScintillaEditor = ::CreateWindow(
        "Scintilla",
        LOCALIZED_EDITOR_TITLE,
        WS_CHILD | WS_VSCROLL | WS_HSCROLL | WS_CLIPCHILDREN,
        0,
        0,
        0,
        0,
        HWindow,
        0,
        GetApplication()->GetInstance(),
        0);
    if (ScintillaEditor != NULL)
    {
        ::ShowWindow(ScintillaEditor, SW_SHOW);
        ::SetFocus(ScintillaEditor);

        // set the font
        LOGFONT lf;
        GetConfigurationFont("EditFont", lf);
        SetEditorFont(lf);

        SendEditor(SCI_SETLEXER, SCLEX_FMSLOGO);
        SendEditor(SCI_COLOURISE, 0, -1);

        // override the CTRL+<LETTER> sequences to do nothing so that they
        // don't insert control characters.
        for (int i = 0; i < 26; i++)
        {
            // I'm not sure why, but CTRL+Y for "Redo" is special and if
            // we set the handler to SCI_NULL, it stops working.
            const int key = 'A' + i;
            if (key != 'Y')
            {
                SendEditor(SCI_ASSIGNCMDKEY, key|(SCMOD_CTRL<<16), SCI_NULL);
            }
        }

        // Hide the margin that Scintilla creates by default.
        // We don't use it for anything, so it just looks weird.
        SendEditor(SCI_SETMARGINWIDTHN, 1, 0);

        SetFileName(FileName);

        if (FileName && !Read())
        {
            SetFileName(0);
        }
    }
}

void TMyFileWindow::CMEditSetFont()
{
    // initialize the font chooser to the current font preference
    LOGFONT lf;
    GetConfigurationFont("EditFont", lf);

    // clear the struct
    CHOOSEFONT CF;
    memset(&CF, 0, sizeof(CF));
    CF.lStructSize = sizeof(CF);
    CF.hwndOwner = MainWindowx->HWindow;
    CF.Flags = CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT;
    CF.nFontType = SCREEN_FONTTYPE;
    CF.lpLogFont = &lf;
    CF.hInstance = 0;

    if (::ChooseFont(&CF))
    {
        // save the new font preference to persistent storage
        SetConfigurationFont("EditFont", lf);

        // Start using the new font
        SetEditorFont(lf);
    }
}

// Prints the contents of the editor.
// This was copied from Scite's SciTEWinDlg.cpp.
void TMyFileWindow::CMFilePrint()
{
    //FMS: RemoveFindMarks();
    PRINTDLG pdlg = { sizeof pdlg };

    pdlg.hwndOwner = HWindow;
    pdlg.hInstance = GetApplication()->GetInstance();
    pdlg.Flags = PD_USEDEVMODECOPIES | PD_ALLPAGES | PD_NOPAGENUMS | PD_RETURNDC | PD_NOSELECTION;
    pdlg.nFromPage = 1;
    pdlg.nToPage = 1;
    pdlg.nMinPage = 1;
    pdlg.nMaxPage = 0xffffU; // We do not know how many pages in the
    // document until the printer is selected and the paper size is known.
    pdlg.nCopies = 1;
    //FMS: pdlg.hDC = 0;
    //FMS: pdlg.hDevMode = hDevMode;
    //FMS: pdlg.hDevNames = hDevNames;

    if (!::PrintDlg(&pdlg))
    {
        return;
    }

    //FMS: hDevMode  = pdlg.hDevMode;
    //FMS: hDevNames = pdlg.hDevNames;

    HDC hdc = pdlg.hDC;

    RECT rectMargins;
    RECT rectPhysMargins;
    Point ptPage;
    Point ptDpi;

    // Get printer resolution
    ptDpi.x = GetDeviceCaps(hdc, LOGPIXELSX);    // dpi in X direction
    ptDpi.y = GetDeviceCaps(hdc, LOGPIXELSY);    // dpi in Y direction

    // Start by getting the physical page size (in device units).
    ptPage.x = GetDeviceCaps(hdc, PHYSICALWIDTH);   // device units
    ptPage.y = GetDeviceCaps(hdc, PHYSICALHEIGHT);  // device units

    // Get the dimensions of the unprintable
    // part of the page (in device units).
    rectPhysMargins.left = GetDeviceCaps(hdc, PHYSICALOFFSETX);
    rectPhysMargins.top  = GetDeviceCaps(hdc, PHYSICALOFFSETY);

    // To get the right and lower unprintable area,
    // we take the entire width and height of the paper and
    // subtract everything else.
    rectPhysMargins.right = ptPage.x  // total paper width
        - GetDeviceCaps(hdc, HORZRES) // printable width
        - rectPhysMargins.left;       // left unprintable margin

    rectPhysMargins.bottom = ptPage.y // total paper height
        - GetDeviceCaps(hdc, VERTRES) // printable height
        - rectPhysMargins.top;        // right unprintable margin

    // At this point, rectPhysMargins contains the widths of the
    // unprintable regions on all four sides of the page in device units.

#if 0
    // Take in account the page setup given by the user (if one value is not null)
    if (pagesetupMargin.left   != 0 ||
        pagesetupMargin.right  != 0 ||
        pagesetupMargin.top    != 0 ||
        pagesetupMargin.bottom != 0)
    {
        PRectangle rectSetup;

        // Convert the hundredths of millimeters (HiMetric) or
        // thousandths of inches (HiEnglish) margin values
        // from the Page Setup dialog to device units.
        // (There are 2540 hundredths of a mm in an inch.)

        char localeInfo[3];
        GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_IMEASURE, localeInfo, 3);

        if (localeInfo[0] == '0') {     // Metric system. '1' is US System
            rectSetup.left      = MulDiv(pagesetupMargin.left,   ptDpi.x, 2540);
            rectSetup.top       = MulDiv(pagesetupMargin.top,    ptDpi.y, 2540);
            rectSetup.right     = MulDiv(pagesetupMargin.right,  ptDpi.x, 2540);
            rectSetup.bottom    = MulDiv(pagesetupMargin.bottom, ptDpi.y, 2540);
        }
        else
        {
            rectSetup.left      = MulDiv(pagesetupMargin.left,   ptDpi.x, 1000);
            rectSetup.top       = MulDiv(pagesetupMargin.top,    ptDpi.y, 1000);
            rectSetup.right     = MulDiv(pagesetupMargin.right,  ptDpi.x, 1000);
            rectSetup.bottom    = MulDiv(pagesetupMargin.bottom, ptDpi.y, 1000);
        }

        // Dont reduce margins below the minimum printable area
        rectMargins.left        = Platform::Maximum(rectPhysMargins.left, rectSetup.left);
        rectMargins.top         = Platform::Maximum(rectPhysMargins.top, rectSetup.top);
        rectMargins.right       = Platform::Maximum(rectPhysMargins.right, rectSetup.right);
        rectMargins.bottom      = Platform::Maximum(rectPhysMargins.bottom, rectSetup.bottom);
    }
    else
#endif
    {
        rectMargins.left    = rectPhysMargins.left;
        rectMargins.top     = rectPhysMargins.top;
        rectMargins.right   = rectPhysMargins.right;
        rectMargins.bottom  = rectPhysMargins.bottom;
    }

    // rectMargins now contains the values used to shrink the printable
    // area of the page.

    // Convert device coordinates into logical coordinates
    DPtoLP(hdc, (LPPOINT) &rectMargins,     2);
    DPtoLP(hdc, (LPPOINT) &rectPhysMargins, 2);

    // Convert page size to logical units and we're done!
    DPtoLP(hdc, (LPPOINT) &ptPage, 1);

#if 0
    SString headerFormat = props.Get("print.header.format");
    SString footerFormat = props.Get("print.footer.format");

    TEXTMETRIC tm;
    SString headerOrFooter;     // Usually the path, date and page number

    SString headerStyle = props.Get("print.header.style");
    StyleDefinition sdHeader(headerStyle.c_str());

    int headerLineHeight = ::MulDiv(
        (sdHeader.specified & StyleDefinition::sdSize) ? sdHeader.size : 9,
        ptDpi.y, 72);
    HFONT fontHeader = ::CreateFont(
        headerLineHeight,
        0,
        0,
        0,
        sdHeader.bold ? FW_BOLD : FW_NORMAL,
        sdHeader.italics,
        sdHeader.underlined,
        0,
        0,
        0,
        0,
        0,
        0,
        (sdHeader.specified & StyleDefinition::sdFont) ? sdHeader.font.c_str() : "Arial");
    ::SelectObject(hdc, fontHeader);
    ::GetTextMetrics(hdc, &tm);
    headerLineHeight = tm.tmHeight + tm.tmExternalLeading;

    SString footerStyle = props.Get("print.footer.style");
    StyleDefinition sdFooter(footerStyle.c_str());

    int footerLineHeight = ::MulDiv(
        (sdFooter.specified & StyleDefinition::sdSize) ? sdFooter.size : 9,
        ptDpi.y,
        72);
    HFONT fontFooter = ::CreateFont(
        footerLineHeight,
        0,
        0,
        0,
        sdFooter.bold ? FW_BOLD : FW_NORMAL,
        sdFooter.italics,
        sdFooter.underlined,
        0,
        0,
        0,
        0,
        0,
        0,
        (sdFooter.specified & StyleDefinition::sdFont) ? sdFooter.font.c_str() : "Arial");
    ::SelectObject(hdc, fontFooter);
    ::GetTextMetrics(hdc, &tm);
    footerLineHeight = tm.tmHeight + tm.tmExternalLeading;
#endif

    DOCINFO di = {sizeof(di)};
    di.lpszDocName  = "Logo";
    if (::StartDoc(hdc, &di) < 0)
    {
#if 0
        SString msg = LocaliseMessage("Can not start printer document.");
        WindowMessageBox(wSciTE, msg, MB_OK);
#endif
        return;
    }

    LONG lengthDoc = SendEditor(SCI_GETLENGTH);
    LONG lengthPrinted = 0;

    // We must subtract the physical margins from the printable area
    Scintilla::RangeToFormat frPrint;
    frPrint.hdc = hdc;
    frPrint.hdcTarget = hdc;
    frPrint.rc.left = rectMargins.left - rectPhysMargins.left;
    frPrint.rc.top = rectMargins.top - rectPhysMargins.top;
    frPrint.rc.right = ptPage.x - rectMargins.right - rectPhysMargins.left;
    frPrint.rc.bottom = ptPage.y - rectMargins.bottom - rectPhysMargins.top;
    frPrint.rcPage.left = 0;
    frPrint.rcPage.top = 0;
    frPrint.rcPage.right = ptPage.x - rectPhysMargins.left - rectPhysMargins.right - 1;
    frPrint.rcPage.bottom = ptPage.y - rectPhysMargins.top - rectPhysMargins.bottom - 1;
#if 0
    if (headerFormat.size())
    {
        frPrint.rc.top += headerLineHeight + headerLineHeight / 2;
    }
    if (footerFormat.size())
    {
        frPrint.rc.bottom -= footerLineHeight + footerLineHeight / 2;
    }
#endif

    // Print each page
    int pageNum = 1;
    bool printPage;
#if 0
    PropSetFile propsPrint;
    propsPrint.superPS = &props;
    SetFileProperties(propsPrint);
#endif

    while (lengthPrinted < lengthDoc)
    {
#if 0
        printPage = (!(pdlg.Flags & PD_PAGENUMS) ||
                     (pageNum >= pdlg.nFromPage) && (pageNum <= pdlg.nToPage));
#else
        printPage = 1;
#endif

#if 0
        char pageString[32];
        sprintf(pageString, "%0d", pageNum);
        propsPrint.Set("CurrentPage", pageString);
#endif

        if (printPage)
        {
            ::StartPage(hdc);

#if 0
            if (headerFormat.size())
            {
                SString sHeader = propsPrint.GetExpanded("print.header.format");
                ::SetTextColor(hdc, sdHeader.ForeAsLong());
                ::SetBkColor(hdc, sdHeader.BackAsLong());
                ::SelectObject(hdc, fontHeader);
                UINT ta = ::SetTextAlign(hdc, TA_BOTTOM);
                RECT rcw = {frPrint.rc.left, frPrint.rc.top - headerLineHeight - headerLineHeight / 2,
                            frPrint.rc.right, frPrint.rc.top - headerLineHeight / 2};
                rcw.bottom = rcw.top + headerLineHeight;
                ::ExtTextOut(hdc, frPrint.rc.left + 5, frPrint.rc.top - headerLineHeight / 2,
                             ETO_OPAQUE, &rcw, sHeader.c_str(),
                             static_cast<int>(sHeader.length()), NULL);
                ::SetTextAlign(hdc, ta);
                HPEN pen = ::CreatePen(0, 1, sdHeader.ForeAsLong());
                HPEN penOld = static_cast<HPEN>(::SelectObject(hdc, pen));
                ::MoveToEx(hdc, frPrint.rc.left, frPrint.rc.top - headerLineHeight / 4, NULL);
                ::LineTo(hdc, frPrint.rc.right, frPrint.rc.top - headerLineHeight / 4);
                ::SelectObject(hdc, penOld);
                ::DeleteObject(pen);
            }
#endif
        }

        frPrint.chrg.cpMin = lengthPrinted;
        frPrint.chrg.cpMax = lengthDoc;

        lengthPrinted = SendEditor(
            SCI_FORMATRANGE,
            printPage,
            reinterpret_cast<LPARAM>(&frPrint));

        if (printPage)
        {
#if 0
            if (footerFormat.size())
            {
                SString sFooter = propsPrint.GetExpanded("print.footer.format");
                ::SetTextColor(hdc, sdFooter.ForeAsLong());
                ::SetBkColor(hdc, sdFooter.BackAsLong());
                ::SelectObject(hdc, fontFooter);
                UINT ta = ::SetTextAlign(hdc, TA_TOP);
                RECT rcw = {frPrint.rc.left, frPrint.rc.bottom + footerLineHeight / 2,
                            frPrint.rc.right, frPrint.rc.bottom + footerLineHeight + footerLineHeight / 2};
                ::ExtTextOut(hdc, frPrint.rc.left + 5, frPrint.rc.bottom + footerLineHeight / 2,
                             ETO_OPAQUE, &rcw, sFooter.c_str(),
                             static_cast<int>(sFooter.length()), NULL);
                ::SetTextAlign(hdc, ta);
                HPEN pen = ::CreatePen(0, 1, sdFooter.ForeAsLong());
                HPEN penOld = static_cast<HPEN>(::SelectObject(hdc, pen));
                ::SetBkColor(hdc, sdFooter.ForeAsLong());
                ::MoveToEx(hdc, frPrint.rc.left, frPrint.rc.bottom + footerLineHeight / 4, NULL);
                ::LineTo(hdc, frPrint.rc.right, frPrint.rc.bottom + footerLineHeight / 4);
                ::SelectObject(hdc, penOld);
                ::DeleteObject(pen);
            }
#endif

            ::EndPage(hdc);
        }
        pageNum++;

        if ((pdlg.Flags & PD_PAGENUMS) && (pageNum > pdlg.nToPage))
        {
            break;
        }
    }

    SendEditor(SCI_FORMATRANGE, FALSE, 0);

    ::EndDoc(hdc);
    ::DeleteDC(hdc);
#if 0
    if (fontHeader)
    {
        ::DeleteObject(fontHeader);
    }
    if (fontFooter)
    {
        ::DeleteObject(fontFooter);
    }
#endif
}

void TMyFileWindow::CMEditUndo()
{
    SendEditor(SCI_UNDO);
}

void TMyFileWindow::CMEditUndoEnable(TCommandEnabler& commandHandler)
{
    commandHandler.Enable(SendEditor(SCI_CANUNDO));
}

void TMyFileWindow::CMEditRedo()
{
    SendEditor(SCI_REDO);
}

void TMyFileWindow::CMEditRedoEnable(TCommandEnabler& commandHandler)
{
    commandHandler.Enable(SendEditor(SCI_CANREDO));
}

void TMyFileWindow::CMEditCut()
{
    SendEditor(SCI_CUT);
}

void TMyFileWindow::CMEditCopy()
{
    SendEditor(SCI_COPY);
}


void TMyFileWindow::CMEditPaste()
{
    SendEditor(SCI_PASTE);
}

void TMyFileWindow::CMEditDelete()
{
    SendEditor(SCI_CLEAR);
}

void TMyFileWindow::CMEditSelectAll()
{
    SendEditor(SCI_SELECTALL);
}

void TMyFileWindow::CMEditClearAll()
{
    // deletes everything in the editor
    SendEditor(SCI_SELECTALL);
    SendEditor(SCI_CLEAR);
}

static bool IsParen(int Char)
{
    switch (Char)
    {
    case '(':
    case ')':
    case '[':
    case ']':
    case '{':
    case '}':
        return true;
    }

    return false;
}

void
TMyFileWindow::FindMatchingParen(
    int & CurrentParenPosition,
    int & MatchingParenPosition
    )
{
    CurrentParenPosition  = INVALID_POSITION;
    MatchingParenPosition = INVALID_POSITION;

    int currentPosition = SendEditor(SCI_GETCURRENTPOS);
    int currentChar     = SendEditor(SCI_GETCHARAT, currentPosition);
    if (IsParen(currentChar))
    {
        // we're close enough to a paren to try to match it
        int matchingParenPosition = SendEditor(SCI_BRACEMATCH, currentPosition);
        if (matchingParenPosition != INVALID_POSITION)
        {
            // found a match

            // If the paren after the caret is an open paren, then
            // the matching paren will be after it.  In this case, 
            // we want to jump just after the matching paren's position
            // to remain on the outside of the parens.
            // Likewise, if the paren after the caret is a close paren,
            // then the matching paren will be before it.  In this case,
            // we also want to jump after the matching paren's position
            // so that we can remain on the inside of the parens.
            CurrentParenPosition  = currentPosition;
            MatchingParenPosition = matchingParenPosition + 1;
        }
        else
        {
            // If paren after the caret has no matching paren,
            // then mark it as a bad paren, instead of trying to
            // match the one before the caret.
            CurrentParenPosition  = currentPosition;
            MatchingParenPosition = INVALID_POSITION;
        }
    }
    else
    {
        // we're not over a paren, so try the position just before the caret
        if (currentPosition != 0)
        {
            int previousChar = SendEditor(SCI_GETCHARAT, currentPosition - 1);
            if (IsParen(previousChar))
            {
                // we're close enough to a paren to try to match it
                int matchingParenPosition = SendEditor(SCI_BRACEMATCH, currentPosition - 1);
                if (matchingParenPosition != INVALID_POSITION)
                {
                    // found a match

                    // If the paren before the caret is an open paren, then
                    // the matching paren will be after it.  In this case, 
                    // we want to jump to the matching paren's position to
                    // remain on the inside of the parens.
                    // Likewise, if the paren before the caret is a close paren,
                    // then the matching paren will be before it.  In this case,
                    // we also want to jump after the matching paren's position
                    // so that we can remain on the outside of the parens.
                    CurrentParenPosition  = currentPosition - 1;
                    MatchingParenPosition = matchingParenPosition;
                }
                else
                {
                    CurrentParenPosition  = currentPosition - 1;
                    MatchingParenPosition = INVALID_POSITION;
                }
            }
        }
    }
}

void TMyFileWindow::CMFindMatchingParen()
{
    int currentParenPosition;
    int matchingParenPosition;
    FindMatchingParen(currentParenPosition, matchingParenPosition);
    if (matchingParenPosition != INVALID_POSITION)
    {
        SendEditor(SCI_GOTOPOS, matchingParenPosition);
    }
}

void TMyFileWindow::CMSelectMatchingParen()
{
    int currentParenPosition;
    int matchingParenPosition;
    FindMatchingParen(currentParenPosition, matchingParenPosition);
    if (matchingParenPosition != INVALID_POSITION && currentParenPosition != INVALID_POSITION)
    {
        // found a match
        SendEditor(SCI_SETANCHOR,     SendEditor(SCI_GETCURRENTPOS));
        SendEditor(SCI_SETCURRENTPOS, matchingParenPosition);
        SendEditor(SCI_SCROLLCARET);
    }
}

void TMyFileWindow::CMEnableIfSelectionExists(TCommandEnabler& commandHandler)
{
    int start = SendEditor(SCI_GETSELECTIONSTART);
    int end   = SendEditor(SCI_GETSELECTIONEND);
    commandHandler.Enable(start != end);
}

void TMyFileWindow::CMEnableIfTextExists(TCommandEnabler& commandHandler)
{
    commandHandler.Enable(SendEditor(SCI_GETLENGTH) != 0);
}


void TMyFileWindow::CMEditPasteEnable(TCommandEnabler& commandHandler)
{
    commandHandler.Enable(SendEditor(SCI_CANPASTE));
}


bool TMyFileWindow::EndEdit()
{
    bool realsave = endedit();

    // check for error
    error_happen = process_special_conditions();

    return realsave;
}

void TMyFileWindow::EvDestroy()
{
    // remove this window from the set of windows that the main window is tracking
    MainWindowx->DestroyEditWindow(this);

    if (args_list != NIL || check_for_errors)
    {
        int realsave = EndEdit();

        if (error_happen)
        {
            // Notify the user that:
            // 1) The changes in the editor failed to load
            // 2) The cursor is positioned just after the last 
            //    successful definition
            //
            // Ask if they want to reedit.

            if (MainWindowx->CommandWindow->MessageBox(
                    LOCALIZED_CURSORISATLASTGOODDEFINITION"\n"
                    "\n"
                    LOCALIZED_RETURNTOEDIT,
                    LOCALIZED_EDITFAILEDTOLOAD,
                    MB_YESNO | MB_ICONERROR) == IDYES)
            {
                // open up another editor
                MainWindowx->MyPopupEdit(TempPathName, args_list, check_for_errors);
                unlink(TempPathName);
                IsDirty = true;
            }
            else
            {
                // free up args_list
                assign(args_list, NIL);

                error_happen = false;
                MainWindowx->CommandWindow->Editbox.SetFocus();
            }
        }
        else
        {
            // no errors happened
            if (args_list != NIL)
            {
                // check for quit before erasing
                if (realsave)
                {
                    lerase(args_list);

                    // Since we erased we must load again, but no errors
                    endedit();
                }

                // free up args_list
                assign(args_list, NIL);
            }

            unlink(TempPathName);
            MainWindowx->CommandWindow->Editbox.SetFocus();
        }
    }
    else
    {
        // else execute callback for user callable editor
        callthing *callevent = callthing::CreateFunctionEvent(edit_editexit);
        calllists.insert(callevent);
    }


    // Get location and size of our window on the screen so we can
    // come back up in the same spot next time we are invoked.

    if (!IsIconic())
    {
        TRect wrect;
        GetWindowRect(wrect);

        // Make a string with our window location and size.
        SetConfigurationQuadruple(
            "Editor",
            wrect.Left(),
            wrect.Top(),
            wrect.Width(),
            wrect.Height());
    }

    TFrameWindow::DefaultProcessing();
}

// Forces the child editor into a dirty state,
// and moves the caret to the line that had the error,
// and clears the "error_happen" flag for the next time editor
// is saved.
void TMyFileWindow::ReopenAfterError()
{
    // clear the error flag.
    error_happen = false;

    // Force the child editor into a dirty state.
    IsDirty = true;

    // Move the caret to the character that had the error
    SendEditor(SCI_GOTOPOS, g_CharactersSuccessfullyParsedInEditor);
}

bool TMyFileWindow::CanClose()
{
    // if changed better ask user
    if (IsDirty)
    {
        int result = MessageBox(
            LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE,
            LOCALIZED_CONTENTSCHANGED,
            MB_YESNOCANCEL | MB_ICONQUESTION);
        if (result == IDYES)
        {
            return Save();
        }
        else
        {
            return result != IDCANCEL;
        }
    }

    return true;
}


//
// responds to an incoming WM_SIZE message by resizing the child edit
// control to fill the TMyFileWindow's client area
//
void TMyFileWindow::EvSize(UINT sizeType, TSize &size)
{
    TFrameWindow::EvSize(sizeType, size);
    ::SetWindowPos(ScintillaEditor, 0, 0, 0, size.cx, size.cy, SWP_NOZORDER);
}

//
// responds to an incoming WM_SETFOCUS message by setting the focus to
// the child edit control
//
void TMyFileWindow::EvSetFocus(HWND)
{
    ::SetFocus(ScintillaEditor);
}

TResult TMyFileWindow::EvNotify(uint ctlId, TNotify& notifyInfo)
{
    switch (notifyInfo.code)
    {
    case SCN_SAVEPOINTREACHED:
        IsDirty = false;
        break;

    case SCN_SAVEPOINTLEFT:
        IsDirty = true;
        break;

    case SCN_UPDATEUI:
        {
            int currentParenPosition;
            int matchingParenPosition;
            FindMatchingParen(currentParenPosition, matchingParenPosition);
            if (currentParenPosition != INVALID_POSITION)
            {
                // we're close enough to a paren to try to match it
                if (matchingParenPosition != INVALID_POSITION)
                {
                    // found a match
                    if (currentParenPosition == SendEditor(SCI_GETCURRENTPOS))
                    {
                        SendEditor(
                            SCI_BRACEHIGHLIGHT,
                            currentParenPosition,
                            matchingParenPosition - 1);
                    }
                    else
                    {
                        SendEditor(
                            SCI_BRACEHIGHLIGHT,
                            currentParenPosition,
                            matchingParenPosition);
                    }
                }
                else
                {
                    // didn't find a match
                    SendEditor(SCI_BRACEBADLIGHT, currentParenPosition);
                }
            }
            else
            {
                // we're not adacent to a paren, so remove the paren highlighting.
                SendEditor(SCI_BRACEBADLIGHT,  INVALID_POSITION);
                SendEditor(SCI_BRACEHIGHLIGHT, INVALID_POSITION, INVALID_POSITION);
            }
        }
        break;

    case SCN_HELPTOPIC_SEARCH:
        CMHelpSelection();
        break;
    }

    return TFrameWindow::EvNotify(ctlId, notifyInfo);
}


DEFINE_RESPONSE_TABLE1(TMyFileWindow, TFrameWindow)
    EV_COMMAND(CM_EDALLEXIT,                CMExit),
    EV_COMMAND(CM_FILESAVETOWORKSPACE,      CMSaveToWorkspace),
    EV_COMMAND(CM_FILEPRINT,                CMFilePrint),
    EV_COMMAND(CM_FILESAVEANDEXIT,          CMSaveAndExit),
    EV_COMMAND(CM_EDITFIND,                 CMEditFind),
    EV_COMMAND(CM_EDITREPLACE,              CMEditReplace),
    EV_COMMAND(CM_EDITFINDNEXT,             CMEditFindNext),
    EV_COMMAND_ENABLE(CM_EDITFIND,          CMEditFindReplaceEnable),
    EV_COMMAND_ENABLE(CM_EDITREPLACE,       CMEditFindReplaceEnable),
    EV_COMMAND_ENABLE(CM_EDITFINDNEXT,      CMEditFindNextEnable),
    EV_COMMAND(CM_HELP,                     CMHelp),
    EV_COMMAND(CM_HELPEDIT,                 CMHelpEditor),
    EV_COMMAND(CM_HELPEDIT_TOPIC,           CMHelpSelection),
    EV_COMMAND(CM_EDITSETFONT,              CMEditSetFont),
    EV_COMMAND(CM_TEST,                     CMTest),
    EV_COMMAND(CM_EDITUNDO,                 CMEditUndo),
    EV_COMMAND(CM_EDITREDO,                 CMEditRedo),
    EV_COMMAND(CM_EDITCUT,                  CMEditCut),
    EV_COMMAND(CM_EDITCOPY,                 CMEditCopy),
    EV_COMMAND(CM_EDITPASTE,                CMEditPaste),
    EV_COMMAND(CM_EDITDELETE,               CMEditDelete),
    EV_COMMAND(CM_EDITCLEAR,                CMEditClearAll),
    EV_COMMAND(CM_EDITSELECTALL,            CMEditSelectAll),
    EV_COMMAND_ENABLE(CM_EDITUNDO,          CMEditUndoEnable),
    EV_COMMAND_ENABLE(CM_EDITREDO,          CMEditRedoEnable),
    EV_COMMAND_ENABLE(CM_EDITCUT,           CMEnableIfSelectionExists),
    EV_COMMAND_ENABLE(CM_EDITCOPY,          CMEnableIfSelectionExists),
    EV_COMMAND_ENABLE(CM_EDITPASTE,         CMEditPasteEnable),
    EV_COMMAND_ENABLE(CM_EDITDELETE,        CMEnableIfSelectionExists),
    EV_COMMAND_ENABLE(CM_EDITCLEAR,         CMEnableIfTextExists),
    EV_COMMAND_ENABLE(CM_EDITSELECTALL,     CMEnableIfTextExists),
    EV_COMMAND(CM_FINDMATCHINGPAREN,        CMFindMatchingParen),
    EV_COMMAND(CM_SELECTMATCHINGPAREN,      CMSelectMatchingParen),
    EV_REGISTERED(FINDMSGSTRING,            EvFindMsg),
    EV_WM_SIZE,
    EV_WM_SETFOCUS,
    EV_WM_DESTROY,
END_RESPONSE_TABLE;
