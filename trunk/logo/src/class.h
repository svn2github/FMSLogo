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

#ifndef __CLASS_H_
#define __CLASS_H_

const int DEFAULT_COMMANDER_HEIGHT = 150;
const int MIN_COMMANDER_HEIGHT     = 100;
const int DEFAULT_SPLITTER_WIDTH   = 5;

// what is this?  Some kind of border?
const int LL = 1;

struct MENUITEM 
{
    const char *  MenuText;
    UINT          MenuId;
};

struct Color
{
    int   red;
    int   green;
    int   blue;
};

enum KEYBOARDCAPTURE
{
    KEYBOARDCAPTURE_Off,
    KEYBOARDCAPTURE_KeyDown,
    KEYBOARDCAPTURE_KeyDownKeyUp,
};

enum INPUTMODE
{
    INPUTMODE_None,
    INPUTMODE_To,
    INPUTMODE_List,
    INPUTMODE_Pause,
};


struct LINEX
{
    POINT from;
    POINT to;
    bool  bValid;
};

struct CUTMAP
{
    HBITMAP CutMemoryBitMap;  // Used to store cut and paste
    int     CutHeight;        // current cut height
    int     CutWidth;         // current cut width
    bool    CutFlag;          // flag to signal something in cut buffer
};

class qlink
{
    friend class qlist;

    qlink *next;
    qlink *prev;
    void * e;

    qlink(void * a, qlink * n, qlink * p)
    {
        e = a;
        next = n;
        prev = p;
    }
};

class qlist
{
    qlink *last;
public:
    void insert(void * a);
    void * get();
    void zap();
    void clear();
    void remove(void * a);
    qlink * find(void * a);

    qlist()
    {
        last = NULL;
    }

    qlist(void * a)
    {
        last = new qlink(a, NULL, NULL);
        last->next = last;
        last->prev = last;
    }

    ~qlist()
    {
        clear();
    }
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

class CLocalizedNode
{
public:
    CLocalizedNode();

    void Initialize(
        const char    * PrimaryName,
        const char    * AlternateName
        );

    NODE *       GetNode() const;
    const char * GetName() const;
    bool         Equals(NODE * Node) const;

private:
    NODE * m_Primary;
    NODE * m_Alternate;
};

class CFileStream
{
public:
    CFileStream(FILE * DefaultStream);

    void   SetStreamToOpenFile(NODE * FileName);
    void   ResetToDefaultStream();
    bool   IsNamed(NODE * FileName) const;
    NODE * GetName() const;
    NODE * GetPosition() const;
    void   SetPosition(NODE * Arguments);

    FILE * GetStream() const
    {
        assert(m_Stream != NULL);
        return m_Stream;
    }

    void SetStream(FILE * Stream)
    {
        assert(m_Stream != NULL);
        m_Stream = Stream;
        assert(m_Stream != NULL);
    }

private:
    FILE *  m_Stream;
    NODE *  m_Name;
    FILE *  m_DefaultStream;
};


// Class for buffering (carrying over) network data from 
// one "receive" call to another when 
class CCarryOverBuffer 
{
public:
    CCarryOverBuffer();

    void ReleaseBuffer();

    void Append(const char * AppendBuffer, int AppendBufferLength);
    void ShiftLeft(int ShiftAmount);

    char * m_Buffer;
    int    m_BufferSize;
    int    m_BytesOfData;
};

class CNetworkConnection 
{
public:
    CNetworkConnection();

    void 
    Enable(
        const char *    OnSendReady,
        const char *    OnReceiveReady,
        unsigned int    ServerPort,
        const char *    HostName,
        DWORD           ResolvedHostNameMessage
        );

    bool IsEnabled() const;
    void Disable();

    void SetLastPacketReceived(char * LastPacket);
    NODE * GetLastPacketReceived() const;

    void
    AsyncReceive(
        TWindow    *     Window,
        const char *     ErrorMessage
        );

    void
    AsyncClose(
        TWindow    *      Window
        );

    void Shutdown();

    void
    PostOnSendReadyEvent(
        TWindow  *  Window
        );

    bool
    SendValue(
        const char * Data
        );

    SOCKET       m_Socket;     // socket for the connection
    unsigned int m_Port;       // server's listen port

    bool         m_IsConnected;  // socket is connected
    bool         m_IsBusy;       // socket is too busy to send
private:
    bool         m_IsEnabled;    // if message processing is enabled for this socket

public:
    PHOSTENT     m_HostEntry;    // Pointer to Host Entry

    char * m_OnReceiveReady;  // Buffer for receive callback
private:
    char * m_OnSendReady;     // Buffer for send    callback

    char * m_ReceiveValue;    // pointer to the last packet received

    CCarryOverBuffer m_CarryOverData;  // a buffer for carrying over partial packets 
                                       // from one recv() call to the next.
};


class TMyFileWindow : public TEditWindow
{
public:

    TMyFileWindow(TWindow *, LPCSTR, LPCSTR, NODE *, bool);
    ~TMyFileWindow();

    bool Save();
    bool Read(const char *fileName = NULL);
    bool Write(const char *FileName = NULL);
    void SetFileName(const char *fileName);

    bool CanClose();
    bool EndEdit();

    void EvDestroy();

    void CMExit();

    void CMTest();
    void CMSaveAndExit();
    void CMSaveToWorkspace();

    void CMEditSetFont();

    void CMHelp();
    void CMHelpEdit();
    void CMHelpEditTopic();

protected:
    void SetupWindow();

    DECLARE_RESPONSE_TABLE(TMyFileWindow);

private:
    char *FileName;
    NODE *args_list;
    HFONT hEdtFont;
    bool  check_for_errors;
};

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

#include "commanderbutton.h"
#include "commandercheckbox.h"

class TMyCommandWindow : public TDialog
{
public:
    TMyCommandWindow(TWindow *, TResId);
    ~TMyCommandWindow();

    bool Duplicate(const TMyCommandWindow & Original);

    void PostKeyDownToEditBox(WPARAM KeyEventWParam, LPARAM KeyEventLParam);
    bool EditBoxWantsKeyEvent(WPARAM KeyEventWParam);

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

class CStatusWindow : public TDialog
{
public:
    CStatusWindow(TWindow * Parent);

protected:
    void EvDestroy();
    void SetupWindow();

    DECLARE_RESPONSE_TABLE(CStatusWindow);
};

class CPrinterAreaWindow : public TDialog
{
public:

    CPrinterAreaWindow(TWindow * Parent);

    int m_XLow;
    int m_XHigh;
    int m_YLow;
    int m_YHigh;
    int m_PixelsPerInch;

protected:
    void SetupWindow();
    void CloseWindow(int);
    void DoReset(UINT);

private:
    void ResetWindow();

    DECLARE_RESPONSE_TABLE(CPrinterAreaWindow);
};

class CSelectProcedureWindow : public TDialog
{
public:

    CSelectProcedureWindow(
        TWindow *    Parent,
        const char * Caption
        );

    void ShowDialog();

protected:
    bool CanClose();
    void SetupWindow();

    virtual void OnChoice(NODE * Procedures) = 0;

    void DoAll(UINT);
    void DoCombo(UINT);

    bool m_FileEditAll;              // true if all procedures were selected
    char m_SelectedProcedures[256];  // buffer to hold selected functions

private:
    DECLARE_RESPONSE_TABLE(CSelectProcedureWindow);
};

// shows a "Select Procedures to Edit" dialog
class CEditProcedureWindow : public CSelectProcedureWindow
{
public:
    CEditProcedureWindow(TWindow * Parent);

protected:
    void OnChoice(NODE * Procedures);
};

// shows a "Select Procedures to Erase" dialog
class CEraseProcedureWindow : public CSelectProcedureWindow
{
public:
    CEraseProcedureWindow(TWindow * Parent);

protected:
    void OnChoice(NODE * Procedures);
};

class TMyApp : public TApplication
{
public:

    TMyApp(LPCSTR AName, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPCSTR lpCmdLine, int nCmdShow)
        : TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow)
    {
    }
        
    ~TMyApp();

    void InitMainWindow();
    void InitInstance();
    bool IdleAction(long idleCount);
    bool ProcessAppMsg(MSG & msg);

    void EvSysColorChange();

    DECLARE_RESPONSE_TABLE(TMyApp);
};

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

    HDC   m_ScreenDeviceContext;
    HDC   m_MemoryDeviceContext;
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

    bool LoadBitmapFile(LPCSTR, DWORD &, DWORD &);
    bool OpenDIB(FILE* File, DWORD &, DWORD &);
    bool DumpBitmapFile(LPCSTR Filename, int MaxBitCount);
    bool WriteDIB(FILE* File, int MaxBitCount);

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
    void CMHelpMCI();
    void CMHelpHelp();
    void CMHelpDemo();
    void CMHelpExamples();
    void CMHelpReleaseNotes();
    void CMHelpTutorial();
    void CMHelpAbout();
    void CMHelpAboutMS();

#if LOCALE!=1033
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

    void EraseContentsOfWorkspace();

    void
    ShowColorPicker(
        class TColorDialog * & ColorPickerDialog,
        COLORREF               InitialColor,
        const char *           EnglishDescription,
        const char *           LogoCommand
        );

public:
    class TPrinter               Printer;
    class TMyCommandWindow     * CommandWindow;
    class CStatusWindow        * StatusWindow;
    class TPaneSplitter        * PaneSplitterWindow;
    class TScreenWindow        * ScreenWindow;

private:

    class TColorDialog  * m_ScreenColorPicker;
    class TColorDialog  * m_PenColorPicker;
    class TColorDialog  * m_FloodColorPicker;

    class TSizeDialog   * m_PenSizePicker;

    CEditors              m_Editors;

    char FileName[MAXPATH];
    char BitmapName[MAXPATH];
    bool IsNewFile;
    bool IsNewBitmap;
    bool IsCommanderDocked;


    DECLARE_RESPONSE_TABLE(TMainFrame);
};

class TRulerOut : public TPrintout
{
public:

    TRulerOut(Pchar ATitle) : TPrintout(ATitle)
    {
    }

    void PrintPage(int Page, TRect & Rect, UINT Flags);

    void GetDialogInfo(int &minPage, int &maxPage, int &selFromPage, int &selToPage)
    {
        minPage = 1;
        maxPage = 1;
        selFromPage = 1;
        selToPage = 1;
    }

    void SetBanding(BOOL b)
    {
        Banding = b;
    }

    bool HasPage(int pageNumber)
    {
        return pageNumber == 1;
    }
};


enum EVENTTYPE
{
    EVENTTYPE_Unknown,
    EVENTTYPE_Mouse,
    EVENTTYPE_Keyboard,
    EVENTTYPE_YieldFunction,
    EVENTTYPE_NoYieldFunction,
    EVENTTYPE_NetworkReceiveReady,
};

class callthing
{
private:
    // Hide the ctor. 
    // All events should be created with CreateEvent*().
    callthing() {};

public:
    // structured ways to create events
    static callthing * CreateKeyboardEvent(char * function, int key);
    static callthing * CreateMouseEvent(char * function, int x, int y);
    static callthing * CreateFunctionEvent(char * function);
    static callthing * CreateNoYieldFunctionEvent(char * function);
    static callthing * CreateNetworkReceiveReadyEvent(CNetworkConnection * NetworkConnection, const char * packet);

    ~callthing();

    // CONSIDER: a union would make this struct smaller
    EVENTTYPE            kind;
    CNetworkConnection * networkconnection;
    char *               func;
    char *               networkpacket;
    int                  arg1;
    int                  arg2;
};

struct calllist : public qlist
{
    void insert(callthing *a)
    {
        qlist::insert(a);
    }
    callthing *get()
    {
        return (callthing *) qlist::get();
    }
};

extern calllist calllists;

extern HBITMAP MemoryBitMap;

extern HCURSOR hCursorWait;
extern HCURSOR hCursorArrow;

extern HPALETTE ThePalette;

extern LPLOGPALETTE MyLogPalette;

extern FLONUM the_zoom;
extern Point  g_OldPos;

extern char LibPathName[];
extern char TempPathName[];
extern char TempBmpName[];
extern char TempClipName[];
extern char szHelpFileName[];
extern char MCIHelpFileName[];

extern HINSTANCE ModulehInstance;

extern HPALETTE OldPalette;

extern LOGFONT FontRec;

extern LOGPEN g_LogicalNormalPen;
extern HPEN   g_NormalPen;

extern LOGPEN g_LogicalErasePen;
extern HPEN   g_ErasePen;

extern LOGBRUSH FloodBrush;
extern LOGBRUSH ScreenBrush;

extern RECT FullRect;

extern TMainFrame *MainWindowx;

extern int g_PrinterAreaXLow;
extern int g_PrinterAreaXHigh;
extern int g_PrinterAreaYLow;
extern int g_PrinterAreaYHigh;
extern int g_PrinterAreaPixels;

extern CUTMAP *CutBmp;
extern Color dpen;
extern Color dfld;
extern Color dscn;
extern int BitMapWidth;
extern int BitMapHeight;
extern int WorldWidth;
extern int WorldHeight;
extern int WorldDepth;
extern bool EnablePalette;
extern bool IsOkayToUseCommanderWindow;
extern bool stepflag;
extern bool GiveFocusToEditbox;
extern int BaseUnitsx;
extern int BaseUnitsy;
extern int current_write_mode;

extern COLORREF scolor;
extern COLORREF fcolor;
extern COLORREF pcolor;
extern long g_PenWidth;
extern bool zoom_flag;
extern long MaxColors;

extern LINEX TurtlePoints[][4];

extern void MakeHelpPathName(char *szFileName, LPCSTR);
extern void ContextHelp(TEdit *Editor);

extern OSVERSIONINFO g_OsVersionInformation;

#endif // __CLASS_H_
