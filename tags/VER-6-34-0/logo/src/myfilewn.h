// -*- c++ -*-
// Copyright (C) 1995 by George Mills
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifndef __MYFILEWN_H_
#define __MYFILEWN_H_

#include <windows.h>
#include <owl/framewin.h>
#include <owl/findrepl.h>

struct NODE;

class TMyFileWindow : public TFrameWindow
{
public:

    TMyFileWindow(TWindow *, LPCSTR, LPCSTR, NODE *, bool);
    ~TMyFileWindow();

    bool Save();
    bool Read(const char *fileName = NULL);
    bool Write(const char *FileName = NULL);
    void SetFileName(const char *fileName);
    bool TranslateKeyboardShortcut(MSG & Message);

    bool CanClose();
    bool EndEdit();
    void ReopenAfterError();

    //
    // message response functions
    //
    void EvSize(UINT sizeType, TSize &);
    void EvSetFocus(HWND lostFocus);
    void EvDestroy();
    LRESULT EvFindMsg(WPARAM, LPARAM lParam);

    //
    // menu command handlers
    //
    void CMFilePrint();     // CM_FILEPRINT
    void CMExit();

    void CMTest();
    void CMSaveAndExit();
    void CMSaveToWorkspace();

    void CMEditSetFont();

    void CMHelp();
    void CMHelpEditor();
    void CMHelpSelection();

    void CMEditFind();
    void CMEditReplace();
    void CMEditFindNext();

    void CMEditCut();
    void CMEditCopy();
    void CMEditPaste();
    void CMEditDelete();
    void CMEditClearAll();
    void CMEditSelectAll();
    void CMEditUndo();
    void CMEditRedo();
    void CMEditPasteEnable(TCommandEnabler& commandHandler);
    void CMEnableIfSelectionExists(TCommandEnabler& commandHandler);
    void CMEnableIfTextExists(TCommandEnabler& commandHandler);
    void CMEditUndoEnable(TCommandEnabler& commandHandler);
    void CMEditRedoEnable(TCommandEnabler& commandHandler);
    void CMEditFindReplaceEnable(TCommandEnabler& commandHandler);
    void CMEditFindNextEnable(TCommandEnabler& commandHandler);

    void CMFindMatchingParen();
    void CMSelectMatchingParen();

protected:
    void SetupWindow();

    DECLARE_RESPONSE_TABLE(TMyFileWindow);

private:
    TFindReplaceDialog::TData SearchData;
    TFindReplaceDialog*       SearchDialog;

    char *  GetSelectedText();
    void    DoSearch();
    LRESULT SendEditor(UINT Msg, WPARAM wParam=0, LPARAM lParam=0);
    void    SetEditorFont(const LOGFONT & LogFont);
    TResult EvNotify(uint ctlId, TNotify& notifyInfo);
    void    FindMatchingParen(int & CurrentParenPosition, int & MatchingParenPosition);

private:
    HWND           ScintillaEditor;
    char         * FileName;
    struct NODE  * args_list;
    bool           check_for_errors;
    bool           IsDirty;
};

#endif // __MYFILEWN_H_
