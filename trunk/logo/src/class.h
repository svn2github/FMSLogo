/*
*
*       Copyright (C) 1995 by George Mills
*
*      This program is free software; you can redistribute it and/or modify
*      it under the terms of the GNU General Public License as published by
*      the Free Software Foundation; either version 2 of the License, or
*      (at your option) any later version.
*
*      This program is distributed in the hope that it will be useful,
*      but WITHOUT ANY WARRANTY; without even the implied warranty of
*      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*      GNU General Public License for more details.
*
*      You should have received a copy of the GNU General Public License
*      along with this program; if not, write to the Free Software
*      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*
*/

#ifndef __CLASS_H_
#define __CLASS_H_

const int DEFAULT_COMMANDER_HEIGHT = 150;
const int MIN_COMMANDER_HEIGHT     = 100;
const int DEFAULT_SPLITTER_WIDTH   = 5;

typedef struct
   {
   POINT from;
   POINT to;
   BOOL  bValid;
   }
LINEX;

typedef struct
   {
   HBITMAP CutMemoryBitMap;  // Used to store cut and paste
   int CutHeight;            // current cut height
   int CutWidth;             // current cut width
   long CutFlag;             // flag to signal something in cut buffer
   }
CUTMAP;

class TMyFileWindow : public TEditWindow
   {
 public:

   TMyFileWindow(TWindow *, LPCSTR, LPCSTR, NODE *);
   ~TMyFileWindow();

   bool Save();
   bool Read(const char *fileName = NULL);
   bool Write(const char *FileName = NULL);
   void SetFileName(const char *fileName);

   bool CanClose();
   int EndEdit();

   void EvDestroy();

   void CMExit();

   void CMTest();
   void CMSaveAndExit();
   void CMSaveToWorkspace();

   void CMEditSetFont();

   void CMHelp();
   void CMHelpEdit();
   void CMHelpEditTopic();

   virtual void SetupWindow();

   DECLARE_RESPONSE_TABLE(TMyFileWindow);

private:
   char *FileName;
   bool IsNewFile;
   NODE *args_list;
   HFONT hEdtFont;
   }
;

class TMyEditboxWindow : public TEdit
   {
 public:

   TMyEditboxWindow(TWindow *, int, WORD);
   ~TMyEditboxWindow();

 protected:
   void EvKeyDown(UINT, UINT, UINT);
   void EvRButtonUp(UINT, TPoint &);

   DECLARE_RESPONSE_TABLE(TMyEditboxWindow);
   }
;

class TMyListboxWindow : public TEdit
   {
 public:
   TMyListboxWindow(TWindow *, int, WORD);
   ~TMyListboxWindow();

 protected:
   void EvKeyDown(UINT, UINT, UINT);
   void EvLButtonDown(UINT modKeys, TPoint & point);
   void EvLButtonDblClk(UINT modKeys, TPoint & point);
   void EvRButtonUp(UINT, TPoint &);

   DECLARE_RESPONSE_TABLE(TMyListboxWindow);
   }
;

class TMyCommandWindow : public TDialog
   {
 public:

   TMyCommandWindow(TWindow *, LPCSTR);
   ~TMyCommandWindow();

   void PostKeyDownToEditBox(WPARAM KeyEventWParam, LPARAM KeyEventLParam);
   bool EditBoxWantsKeyEvent(WPARAM KeyEventWParam);

   void ChooseNewFont();

 protected:
   void SetupWindow();
   char * GetClassName();
   void RecalculateLayout();

   void EvDestroy();
   void CmCancel();
   void CmOk();
   void EvClose();
 public: // HACK: should be protected
   void EvSize(UINT, TSize &);
 protected:

   void DoListBox(UINT);
   void DoEditBox(UINT);
 public: // HACK: should be protected
   void DoButtonExecute(UINT);
   void DoButtonHalt(UINT);
 protected:
   void DoButtonEdall(UINT);
   void DoButtonStatus(UINT);
   void DoButtonYield(UINT);
   void DoButtonPause(UINT);
   void DoButtonTrace(UINT);
   void DoButtonReset(UINT);

   void EvKeyDown(UINT, UINT, UINT);

protected:
   class TCommanderButton * TraceButton;
   class TCommanderButton * ResetButton;
   class TCommanderButton * PauseButton;
   class TCommanderButton * HaltButton;
   class TCommanderButton * StatusButton;
   class TCommanderButton * YieldButton;
   class TCommanderButton * EdallButton;
   class TCommanderButton * ExecuteButton;

   HFONT Font;
   
public: // HACK: should be protected
   class TMyEditboxWindow * Editbox;
   class TMyListboxWindow * Listbox;


   DECLARE_RESPONSE_TABLE(TMyCommandWindow);
   }
;

class TMyStatusWindow : public TDialog
   {
 public:

   TMyStatusWindow(TWindow *, LPCSTR);
   ~TMyStatusWindow();
   }
;

class TMyPrinterAreaWindow : public TDialog
   {
 public:

   TMyPrinterAreaWindow(TWindow *, LPCSTR);
   ~TMyPrinterAreaWindow();

   void SetupWindow();
   void CloseWindow(int);

   void ResetWindow();

   void DoReset(UINT);

   DECLARE_RESPONSE_TABLE(TMyPrinterAreaWindow);
   }
;

class TMyFileEditWindow : public TDialog
   {
 public:

   int FileEditAll;

   TMyFileEditWindow(TWindow *, LPSTR);
   ~TMyFileEditWindow();

   bool CanClose();
   void SetupWindow();

   void DoAll(UINT);
   void DoCombo(UINT);

   DECLARE_RESPONSE_TABLE(TMyFileEditWindow);
   }
;

class TMyApp : public TApplication
   {
 public:

   TMyApp(LPCSTR AName, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPCSTR lpCmdLine, int nCmdShow)
      : TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow)
      {
      }
   ;
   ~TMyApp();

   void InitMainWindow();
   void InitInstance();
   bool IdleAction(long idleCount);
   bool ProcessAppMsg(MSG & msg);

   void EvSysColorChange();

   DECLARE_RESPONSE_TABLE(TMyApp);
   }
;

class TScreenWindow : public TWindow
   {
 public:
   TScreenWindow(TWindow * AParent, LPCSTR ATitle);
   ~TScreenWindow();

   void Printit(TDC & DC);

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

   DECLARE_RESPONSE_TABLE(TScreenWindow);
   }
;

class TMainFrame : public TDecoratedFrame
   {
 public:

   TMainFrame(TWindow * AParent, LPCSTR ATitle, TPaneSplitter * PaneSplitter);
   ~TMainFrame();

   static int PopupEditorForFile(const char *FileName, NODE *args);
   void MyPopupEdit(const char *FileName, NODE * args);
   void MyPopupStatus();
   void MyPopupStatusKill();
   int MyPopupInput(char *str, char *pmt);

   void CheckForFileError();
   BOOL LoadBitmapFile(LPSTR, DWORD &, DWORD &);
   BOOL OpenDIB(int, DWORD &, DWORD &);
   void GetBitmapData(int TheFile, HANDLE, long);
   BOOL DumpBitmapFile(LPSTR, int);
   BOOL WriteDIB(int TheFile, int MaxBitCount);
   void PutBitmapData(int TheFile, HANDLE, long);
   void SaveFile();
   void SaveFileAs();
   void SaveBitmap();
   void SaveBitmapAs();

   void SetupWindow();
   bool CanClose();
   void GetWindowClass(WNDCLASS & WndClass);
   char * GetClassName();

 protected:
   void EvDestroy();
   void EvTimer(UINT);
   void EvSize(UINT, TSize &);

   void CMFileNew();
   void CMFileOpen();
   void CMFileSave();
   void CMFileSaveAs();
   void CMFileEdit();
   void CMFileErase();
   void CMExit();

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

 public:
   class TPrinter               Printer;
   class TMyFileWindow        * EditWindow;
   class TMyCommandWindow     * CommandWindow;
   class TMyStatusWindow      * StatusWindow;
   class TMyPrinterAreaWindow * PrinterAreaWindow;
   class TMyFileEditWindow    * FileEditWindow;
   class TPaneSplitter        * PaneSplitterWindow;
   class TScreenWindow        * ScreenWindow;

 protected:
   char FileName[MAXPATH];
   char BitmapName[MAXPATH];
   bool IsNewFile;
   bool IsNewBitmap;


   DECLARE_RESPONSE_TABLE(TMainFrame);
   }
;

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
   }
;

typedef void *ent;

class qlink
   {
   friend class qlist;

   qlink *next;
   qlink *prev;
   int type;
   ent e;

   qlink(ent a, qlink * n, qlink * p, int t)
      {
      e = a;
      next = n;
      prev = p;
      type = t;
      }
   }
;

class qlist
   {
   qlink *last;
 public:
   void insert(ent a, int t);
   ent get();
   void zap();
   void clear();

   qlist()
      {
      last = NULL;
      }

   qlist(ent a, int t)
      {
      last = new qlink(a, NULL, NULL, t);
      last->next = last;
      last->prev = last;
      }

   ~qlist()
      {
      clear();
      }
   }
;

typedef struct callthing
   {
   char *func;
   int arg1;
   int arg2;
   int kind;
   }
_callthing
   ;

struct calllist : qlist
   {
   void insert(callthing *a, int t)
      {
      qlist::insert(a, t);
      }
   callthing *get()
      {
      return (callthing *) qlist::get();
      }
   }
;

extern calllist calllists;

extern HBITMAP MemoryBitMap;
extern HBITMAP OldBitmap;

extern HICON hCursor;
extern HICON hCursorWait;
extern HICON hCursorArrow;

extern HPALETTE ThePalette;

extern LPLOGPALETTE MyLogPalette;

extern NUMBER the_zoom;
extern NUMBER ibmoldx;
extern NUMBER ibmoldy;
extern NUMBER ibmoldz;

extern NODE *current_line;

extern char LibPathName[];
extern char TempPathName[];
extern char TempBmpName[];
extern char TempClipName[];
extern char szHelpFileName[];
extern char MCIHelpFileName[];
extern char SelectedText[];

extern HINSTANCE ModulehInstance;

extern HPALETTE OldPalette;
extern HPALETTE OldPalette2;

extern HBRUSH OldBrush;

extern LOGFONT FontRec;

extern LOGPEN NormalPen;
extern LOGPEN ErasePen;

extern LOGBRUSH FloodBrush;
extern LOGBRUSH ScreenBrush;

extern RECT FullRect;

extern TMainFrame *MainWindowx;

extern int PrinterAreaXLow;
extern int PrinterAreaXHigh;
extern int PrinterAreaYLow;
extern int PrinterAreaYHigh;
extern int PrinterAreaPixels;
extern int TPrinterAreaXLow;
extern int TPrinterAreaXHigh;
extern int TPrinterAreaYLow;
extern int TPrinterAreaYHigh;
extern int TPrinterAreaPixels;

extern CUTMAP *CutBmp;
extern int dpenr;
extern int dpeng;
extern int dpenb;
extern int dfldr;
extern int dfldg;
extern int dfldb;
extern int dscnr;
extern int dscng;
extern int dscnb;
extern int IsDirty;
extern int BitMapWidth;
extern int BitMapHeight;
extern int WorldWidth;
extern int WorldHeight;
extern int WorldDepth;
extern int EnablePalette;
extern bool IsPrinterSettingCustom;
extern bool IsTPrinterSettingCustom;
extern int Command_OK;
extern int halt_flag;
extern int traceflag;
extern int stepflag;
extern int pause_flag;
extern int MaxWidth;
extern int MaxHeight;
extern int JustDidEdit;
extern int Time_To_Pause;
extern int Time_To_Halt;
extern int BaseUnitsx;
extern int BaseUnitsy;
extern int current_write_mode;

extern long scolor;
extern long fcolor;
extern long pcolor;
extern long width;
extern long zoom_flag;
extern long MaxColors;
extern long first_init;

extern LINEX TurtlePoints[][4];

extern void MakeHelpPathName(char *szFileName, LPCSTR);
extern void ContextHelp(HWND hWindow, TEdit *Editor);

extern OSVERSIONINFO g_OsVersionInformation;

#endif // __CLASS_H_

