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

#ifndef __MAINFRAME_H_
#define __MAINFRAME_H_

#include <owl\decframe.h>
#include <owl\panespli.h>

#include "logocore.h"         // for FLONUM
#include "logoeventqueue.h"   // for qlist
#include "localizedstrings.h" // for MANUAL_HAS_TRANSLATION_TABLES

class TScreenWindow : public TWindow
{
public:
    TScreenWindow(TWindow * AParent, LPCSTR ATitle);
    ~TScreenWindow();

    void AdjustScrollPositionToZoomFactor(FLONUM ZoomFactor);
    void Printit(TDC & DC);

    HDC GetScreenDeviceContext() const
    {
        return m_ScreenDeviceContext;
    }

    HDC GetMemoryDeviceContext() const
    {
        return m_MemoryDeviceContext;
    }

protected:
    void SetupWindow();

    void Paint(TDC &, bool, TRect &);

    void EvKeyDown(UINT, UINT, UINT);
    void EvKeyUp(UINT, UINT, UINT);
    void EvChar(UINT, UINT, UINT);
    void EvLButtonDown(UINT, TPoint &);
    void EvLButtonUp(UINT, TPoint &);
    void EvRButtonDown(UINT, TPoint &);
    void EvRButtonUp(UINT, TPoint &); 
    void EvMouseMove(UINT, TPoint &);
    void EvSize(UINT, TSize &);
    void EvDestroy();

    DECLARE_RESPONSE_TABLE(TScreenWindow);

private:
    void GetScrollRatios(FLONUM & XRatio, FLONUM & YRatio);

    HDC    m_ScreenDeviceContext;
    HDC    m_MemoryDeviceContext;
};

class CEditors : public qlist
{
public:
    void insert(class TMyFileWindow * Editor)
    {
        qlist::insert(Editor);
    }

    qlink * find(class TMyFileWindow * Editor)
    {
        return qlist::find(Editor);
    }

    void remove(class TMyFileWindow * Editor)
    {
        qlist::remove(Editor);
    }

    class TMyFileWindow * get()
    {
        return (class TMyFileWindow *) qlist::get();
    }
};

class TMainFrame : public TDecoratedFrame
{
public:

    TMainFrame(TWindow * AParent, LPCSTR ATitle, TPaneSplitter * PaneSplitter);
    ~TMainFrame();

    static int PopupEditorForFile(const char *FileName, NODE *args);
    class TMyFileWindow * CreateEditWindow(const char *FileName, NODE *args, bool check_for_errors);
    void DestroyEditWindow(class TMyFileWindow * EditWindow);
    void MyPopupEdit(const char *FileName, NODE * args, bool check_for_errors);
    void MyPopupEditToError(const char *FileName);
    bool IsEditorOpen();
    TMyFileWindow * GetEditor();

    void MyPopupStatus();
    void MyPopupStatusKill();
    bool MyPopupInput(char *str, const char *prompt);

    void FixWindowTitle();
    void UndockCommanderWindow();
    void DockCommanderWindow();

protected:
    void SetupWindow();
    bool CanClose();
    void GetWindowClass(WNDCLASS & WndClass);
    char * GetClassName();

    bool FileSave();
    bool SaveFile();
    bool SaveFileAs();
    void SaveBitmap();
    void SaveBitmapAs();

    void EvDestroy();
    void EvTimer(UINT);
    void EvSize(UINT, TSize &);

    void CMFileNew();
    void CMFileLoad();
    void CMFileOpen();

public:
    // The File-Save options are public so that the
    // commander's list box can delegate the message.
    void CMFileSave();
    void CMFileSaveAs();

protected:
    void CMFileEdit();
    void CMFileErase();
    void CMFileSetAsScreenSaverEnable(TCommandEnabler& commandHandler);
    void CMFileSetAsScreenSaver();
    void CMExit();
    void CmSelectAll();

    void CMBitmapNew();
    void CMBitmapOpen();
    void CMBitmapSave();
    void CMBitmapSaveAs();
    void CMBitmapPrint();
    void CMBitmapPrinterSetup();
    void CMBitmapPrinterArea();

public:  //HACK
    void CMHelp();
protected:
    void CMHelpDemo();
    void CMHelpExamples();
    void CMHelpReleaseNotes();
    void CMHelpTutorial();
    void CMHelpAbout();
    void CMHelpAboutMS();

#if MANUAL_HAS_TRANSLATION_TABLES
    void CMHelpLangToEnglish();
    void CMHelpEnglishToLang();
#endif

    void CMControlExecute();

    void CMSetFont();
    void CMSetCommanderFont();
    void CMSetPenSize();
    void CMSetPenColor();
    void CMSetFloodColor();
    void CMSetScreenColor();

    void CMZoomIn();
    void CMZoomOut();
    void CMZoomNormal();

    LRESULT MMMCINotify(WPARAM, LPARAM);
    LRESULT WMCheckQueue(WPARAM, LPARAM);
    LRESULT OnNetworkConnectSendAck(WPARAM, LPARAM);
    LRESULT OnNetworkConnectSendFinish(WPARAM, LPARAM);
    LRESULT OnNetworkListenReceiveAck(WPARAM, LPARAM);
    LRESULT OnNetworkListenReceiveFinish(WPARAM, LPARAM);

private:

    bool WarnIfSavingEmptyWorkspace();
    void EraseContentsOfWorkspace();

    void
    InitializeOpenFileNameForLogoFiles(
        OPENFILENAME & OpenFileData
        );

    void
    ShowColorPicker(
        class TColorDialog * & ColorPickerDialog,
        COLORREF               InitialColor,
        const char *           EnglishDescription,
        const char *           LogoCommand
        );

public:
    class TMyCommandWindow     * CommandWindow;
    class CStatusWindow        * StatusWindow;
    class TPaneSplitter        * PaneSplitterWindow;
    class TScreenWindow        * ScreenWindow;

private:

    class TPrinter      * m_Printer;
    class TColorDialog  * m_ScreenColorPicker;
    class TColorDialog  * m_PenColorPicker;
    class TColorDialog  * m_FloodColorPicker;

    class TSizeDialog   * m_PenSizePicker;

    CEditors              m_Editors;

    char FileName[MAX_PATH];
    char BitmapName[MAX_PATH];
    bool IsNewFile;
    bool IsNewBitmap;
    bool IsCommanderDocked;


    DECLARE_RESPONSE_TABLE(TMainFrame);
};

struct MENUITEM 
{
    const char *  MenuText;
    UINT          MenuId;
};

extern void FillMenu(
    class TMenu           & Menu, 
    const struct MENUITEM * MenuItems,
    size_t                  MenuItemsLength
    );

extern void AppendPopupMenu(
    class TMenu           & Menu,
    const char            * PopupMenuText,
    const struct MENUITEM * PopupMenuItems,
    size_t                  PopupMenuItemsLength
    );

extern void SetTextOnChildWindows(
    class TWindow *  Parent,
    const MENUITEM * ChildText,
    size_t           ChildTextLength
    );

#endif // __MAINFRAME_H_
