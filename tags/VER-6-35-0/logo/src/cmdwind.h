// -*- c++ -*-
// Copyright (C) 1995 by the Regents of the University of California
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

#ifndef __CMDWND_H_
#define __CMDWND_H_

#include <owl\dialog.h>
#include <owl\printer.h>
#include <owl\edit.h>

#include "editwnd.h"
#include "commanderbutton.h"
#include "commandercheckbox.h"

class TMyEditboxWindow : public TEdit
{
public:
    TMyEditboxWindow(TWindow *, int, WORD);
    ~TMyEditboxWindow();

protected:
    void EvSetFocus(THandle hWndGetFocus);
    void EvKeyDown(UINT, UINT, UINT);
    void CmSelectAll();

    DECLARE_RESPONSE_TABLE(TMyEditboxWindow);
};

class TMyListboxWindow : public TRichEditWithPopup
{
public:
    TMyListboxWindow(TWindow *, int);
    ~TMyListboxWindow();

    void SetCursorAtBottom();
    bool IsCursorAtBottom() const;

protected:
    void EvChar(uint key, uint repeatCount, uint flags);
    bool CanClose();
    void SetupWindow();
    void CmFileSave();
    void CmFileSaveAs();
    void EvKeyDown(UINT, UINT, UINT);
    void EvKeyUp(UINT, UINT, UINT);
    void EvLButtonDown(UINT modKeys, TPoint & point);
    void EvLButtonDblClk(UINT modKeys, TPoint & point);
    void EvMouseMove(uint modKeys, TPoint& point);

    void CmDisableCommand(TCommandEnabler& commandHandler);
    void CmEnableCommand(TCommandEnabler& commandHandler);

    DECLARE_RESPONSE_TABLE(TMyListboxWindow);

private:
    void CopyCurrentLineToEditBox();

    bool IsControlKeyDown();

    bool m_IsControlKeyDown;
    bool m_IsLeftControlKeyDown;
    bool m_IsRightControlKeyDown;
};

class TMyCommandWindow : public TDialog
{
public:
    TMyCommandWindow(TWindow *, TResId);
    ~TMyCommandWindow();

    bool Duplicate(const TMyCommandWindow & Original);

    void PostKeyDownToEditBox(WPARAM KeyEventWParam, LPARAM KeyEventLParam);
    bool EditBoxWantsKeyEvent(WPARAM KeyEventWParam);
    bool TranslateKeyboardShortcut(TWindow * Window, MSG & Message);

    void ChooseNewFont();

protected:
    void SetupWindow();
    char * GetClassName();
    void RecalculateLayout();
    void UpdateFont(const LOGFONT & NewFont);

    void EvDestroy();
    void CmCancel();
    void CmOk();
    void CmEditAll();
    void EvClose();
public: // HACK: should be protected
    void EvSize(UINT, TSize &);
protected:

public: // HACK: should be protected
    void DoButtonExecute(UINT);
    void DoButtonHalt(UINT);
    void DoButtonYield(UINT);
protected:
    void DoButtonEdall(UINT);
    void DoButtonStatus(UINT);
    void DoButtonPause(UINT);
    void DoButtonTrace(UINT);
    void DoButtonReset(UINT);

public:
    void UpdateYieldButtonState();
    void UpdateTraceButtonState();
    void UpdateStatusButtonState();

protected:
    TCommanderCheckBox TraceButton;
    TCommanderButton   ResetButton;
    TCommanderButton   PauseButton;
    TCommanderButton   HaltButton;
    TCommanderCheckBox StatusButton;
    TCommanderCheckBox YieldButton;
    TCommanderButton   EdallButton;
    TCommanderButton   ExecuteButton;

    HFONT Font;
   
public: // HACK: should be protected
    TMyEditboxWindow Editbox;
    TMyListboxWindow Listbox;

private:

    int m_EditboxHeight;
    int m_ButtonWidth;

    DECLARE_RESPONSE_TABLE(TMyCommandWindow);
};

#endif // __CMDWND_H_
