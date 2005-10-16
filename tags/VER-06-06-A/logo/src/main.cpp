/*
*
*       Copyright (C) 1995 by the Regents of the University of California
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

#include "allwind.h"

CUTMAP *CutBmp;              /* Pointer to Bit Cut memory array malloc on init*/

//HANDLE HashHandle = 0;           /* Handle to Hashtable                 */
//HANDLE StackHandle = 0;          /* Handle to Gargebage Collector Stack */
BOOL bPerspective;                 /* Perspetive mode startt up           */
BOOL bExpert;                      /* Expert mode                         */
BOOL bFixed;                       /* Fixed mode                          */
BOOL bWidth;                       /* Width mode                          */
BOOL bHeight;                      /* Height mode                         */
//BOOL bSilent;                    /* Silent mode                         */

HBITMAP MemoryBitMap;              /* Backing store bitmap                */

HICON hCursor;                         /* handle for saved cursor             */
HICON hCursorWait;                     /* handle for hour glass cursor        */
HICON hCursorArrow;                    /* handle for hour glass cursor        */

HPALETTE ThePalette;                   /* Handle for the single color palette */

LPLOGPALETTE MyLogPalette;      /* Handle for the single logical color palette*/

NUMBER the_zoom = 1.0;                 /* current zoom factor                 */
NUMBER ibmoldx;                        /* global store for x "From" routine   */
NUMBER ibmoldy;                        /* global store for y "From" routine   */
NUMBER ibmoldz;                        /* global store for z "From" routine   */

NODE *current_line = NIL;              /* current line to be parsed           */

char LibPathName[EXE_NAME_MAX_SIZE + 1];    /* path to library                */
char TempPathName[EXE_NAME_MAX_SIZE + 1];   /* path to temp edit file         */
char TempBmpName[EXE_NAME_MAX_SIZE + 1];    /* path to temp bitmap file       */
char TempClipName[EXE_NAME_MAX_SIZE + 1];   /* path to temp clipboard file    */
char szHelpFileName[EXE_NAME_MAX_SIZE + 1]; /* path to help file              */
char MCIHelpFileName[EXE_NAME_MAX_SIZE + 1];/* path to MCI help file          */
char SelectedText[MAX_BUFFER_SIZE];    /* buffer for selected text            */
char commandarg[MAX_BUFFER_SIZE];      /* Routine to exec on start            */

// holds callback code

char edit_editexit[MAX_BUFFER_SIZE];   /* callable editor cb                  */
char mci_callback[MAX_BUFFER_SIZE];    /* MCI callback code                   */
char *timer_callback[MAX_TIMERS];      /* timer cb malloc'd as needed         */
char *mouse_lbuttondown = NULL;        /* Mouse Left button down cb           */
char *mouse_lbuttonup = NULL;          /* Mouse Right button up cb            */
char *mouse_rbuttondown = NULL;        /* Mouse Left button down cb           */
char *mouse_rbuttonup = NULL;          /* Mouse Right button up cb            */
char *mouse_mousemove = NULL;          /* Mouse Move cb                       */
char *keyboard_keydown = NULL;         /* KeyBoard key down                   */
char *keyboard_keyup = NULL;           /* KeyBoard key up                     */

HINSTANCE ModulehInstance;             /* About box instance handle           */

/* place holders for windows resources */

HBITMAP OldBitmap;
HBITMAP OldBitmap2;

HPALETTE OldPalette;
HPALETTE OldPalette2;

HBRUSH OldBrush;

HFONT OldFont;

LOGFONT FontRec;
LOGFONT EditFontRec;

LOGPEN NormalPen;                      /* Handle to "Normal" logical Pen      */
LOGPEN ErasePen;                       /* Handle to "Erase" logical Pen       */

LOGBRUSH FloodBrush;                   /* Handle to the "floodfill" brush     */
LOGBRUSH ScreenBrush;               /* Handle to the "screen" background brush*/

RECT FullRect;                         /* Ready rectangle of Full bitmap      */

TMainFrame *MainWindowx;               /* Pointer to the Main window          */

/* Active area dimensions (real and temp) */

int PrinterAreaXLow;
int PrinterAreaXHigh;
int PrinterAreaYLow;
int PrinterAreaYHigh;
int PrinterAreaPixels;
int TPrinterAreaXLow;
int TPrinterAreaXHigh;
int TPrinterAreaYLow;
int TPrinterAreaYHigh;
int TPrinterAreaPixels;

int GCMAX = 8192;                      /* Garbage Collector STack Size (Logo.ini)       */
int MAX_PHYS_LINE = 8192;              /* Maximum Physical Line Size (Logo.ini)         */
//int ROUNDPOS;                        /* Round returned POS                            */
//int BUFFERTYPE;                      /* Buffered TYPE command                         */
int dpenr;                             /* Current draw pen color red                    */
int dpeng;                             /* Current draw pen color green                  */
int dpenb;                             /* Current draw pen color blue                   */
int dfldr;                             /* Current flood pen color red                   */
int dfldg;                             /* Current flood pen color green                 */
int dfldb;                             /* Current flood pen color blue                  */
int dscnr;                             /* Current screen pen color red                  */
int dscng;                             /* Current screen pen color green                */
int dscnb;                             /* Current screen pen color blue                 */
int IsDirty = 0;                       /* Flag to signal to query user ok to quit       */
int BitMapWidth = 1000;                /* Current bitmap size in X                      */
int BitMapHeight = 1000;               /* Current bitmap size in Y                      */
int WorldWidth = 1000;                 /* Current World size in X                       */
int WorldHeight = 1000;                /* Current World size in Y                       */
int WorldDepth = 1000;                 /* Current World size in Z                       */
int EnablePalette;                     /* Flag to signal 256 color mode with palette    */
bool IsPrinterSettingCustom = false;   /* Flag to signal Active area is active          */
bool IsTPrinterSettingCustom = false;  /* Dynamic copy of CustomFlag                    */
int Command_OK = 0;                    /* Flag to signal it's OK to write to recall box */
int halt_flag = 0;                     /* Flag to signal it's OK to halt                */
int traceflag = 0;                     /* Flag to signal trace button is active         */
int stepflag = 0;                      /* Flag to signal trace button is active         */
int pause_flag = 0;                    /* Flag to signal pause button is pushed         */
int yield_flag = 1;                    /* Flag to signal yield state                    */
int status_flag = 0;                   /* Flag to signal status box is poped up         */
unsigned int uCurrentTime = 0;         /* Flag to signal status box is poped up         */
int MaxWidth = 0;                      /* Actual Main window size x                     */
int MaxHeight = 0;                     /* Actual Main window size y                     */
int xoffset = 0;                       /* Used to go from logo to windows coords x      */
int yoffset = 0;                       /* Used to go from logo to windows coords y      */
int JustDidEdit = 0;                   /* Flag to signal last command was edit (like)   */
int Time_To_Exit = 0;                  /* Flag to signal it's time to exit              */
int Time_To_Pause = 0;                 /* UCBLOGO? pause flag                           */
int Time_To_Halt = 0;                  /* UCBLOGO? halt flag                            */
int error_happen;                      /* FLag to signal Error happened on edit reload  */
int keyboard_on = 0;                   /* Flag to signal Keyboard is enabled            */
int keyboard_value = 0;                /* Value of Keyboard key                         */
int mouse_on = 0;                      /* Flag to signal Mouse is enabled               */
int mouse_posx = 0;                    /* Value of Mouse position x                     */
int mouse_posy = 0;                    /* Value of Mouse position y                     */
int memory_count = 0;                  /* Current amount of logo segments malloc'd      */
int BaseUnitsx = 0;                    /* X Units Windows uses to for units in dialog   */
int BaseUnitsy = 0;                    /* Y Units Windows uses to for units in dialog   */

long eval_count = 0;                   /* current count of "evaluations" calls          */
long vector_count = 0;                 /* current count of vectors drawn                */
long scolor = 1;                       /* screen color                                  */
long fcolor = 1;                       /* flood color                                   */
long pcolor = 1;                       /* pen color                                     */
long width = 1;                        /* pen width                                     */
long zoom_flag = 0;                    /* flag to signal in zoomed state                */
long MaxColors = 0;                    /* The maximum # of colors available             */
long first_init = 0;                   /* hack flag to signal one time initialization   */

LINEX TurtlePoints[TURTLES][4];        /* used to store 3 vertices of turtle            */

TThreeDSolid ThreeD;

void putfileeditcombo(char *str)
   {
   MainWindowx->FileEditWindow->SendDlgItemMsg(
      ID_FILEEDITCOMBO,
      CB_ADDSTRING,
      0, (LONG) str);
   }

void cnv_strnode_string(char *textbuf, NODE *arg)
   {
   print_stringptr = textbuf;
   print_stringlen = MAX_BUFFER_SIZE;
   ndprintf((FILE *) NULL, "%p", car(arg));
   *print_stringptr = '\0';
   }

long LoadColor(int dpenr, int dpeng, int dpenb)
   {

   /* adds color to palette */

   int Index;
   long color;

   /* convert to color and find nearest match */

   color = PALETTERGB(dpenr, dpeng, dpenb);

   Index = GetNearestPaletteIndex(ThePalette, color);

   /* if not exact and room for more then allocate it */

   if ((PALETTERGB(
               MyLogPalette->palPalEntry[Index].peRed,
               MyLogPalette->palPalEntry[Index].peGreen,
               MyLogPalette->palPalEntry[Index].peBlue) != color) && (MyLogPalette->palNumEntries < (MaxColors - 1)))
      {

      /* Why do check again? */

      if (MyLogPalette->palNumEntries < 255)
         {

         /* kill old palette */

         DeleteObject(ThePalette);

         MyLogPalette->palPalEntry[MyLogPalette->palNumEntries].peRed = dpenr;
         MyLogPalette->palPalEntry[MyLogPalette->palNumEntries].peGreen = dpeng;
         MyLogPalette->palPalEntry[MyLogPalette->palNumEntries].peBlue = dpenb;
         MyLogPalette->palPalEntry[MyLogPalette->palNumEntries].peFlags = 0;
         MyLogPalette->palNumEntries++;

         /* if status window then update palette usage */

         if (status_flag)
            {
            update_status_paletteuse();
            }

         /* make new palette with added color */

         ThePalette = CreatePalette(MyLogPalette);
         }
      }

   /* return color new, matched or close */

   return (color);
   }


/* this routine is here to allow a non object call */

int TMyWindow_MyPopupEdit(char *FileName, NODE *args)
   {
   FILE *edfd;

   /* If no file (or empty) create template */

   if ((edfd = fopen(FileName, "r")) == NULL)
      {
      if ((edfd = fopen(FileName, "w")) != NULL)
         {
         if (args != NULL)
            {
            fwrite("to\n", 1, 3, edfd);
            fwrite("end\n", 1, 4, edfd);
            }
         else
            {
            fwrite("\n", 1, 1, edfd);
            }
         fclose(edfd);
         }
      }
   else
      {
      if (getc(edfd) == EOF)
         {
         fclose(edfd);
         edfd = fopen(FileName, "w");
         if (args != NULL)
            {
            fwrite("to\n", 1, 3, edfd);
            fwrite("end\n", 1, 4, edfd);
            }
         else
            {
            fwrite("\n", 1, 1, edfd);
            }
         }
      fclose(edfd);
      }

   MainWindowx->MyPopupEdit(FileName, args);
   return (0);
   }

void clearcombobox()
   {

   /* clear the recall box */

   MainWindowx->CommandWindow->Listbox->SetReadOnly(FALSE);
   MainWindowx->CommandWindow->Listbox->Clear();
   MainWindowx->CommandWindow->Listbox->SetReadOnly(TRUE);
   }

void putcombobox(char *str)
   {

   /* only if OK to write to recall box do we do it */

   if (Command_OK)
      {
      UINT uBefore;
      UINT uAfter;
      UINT uCheck;

      for (int i=0;i<16;i++)
         {
         /* remember where we started */

         uBefore = MainWindowx->CommandWindow->Listbox->GetTextLen();

         /* output to list box */

         MainWindowx->CommandWindow->Listbox->SetSelection(uBefore, uBefore);
         MainWindowx->CommandWindow->Listbox->Insert(str);
         uCheck = MainWindowx->CommandWindow->Listbox->GetTextLen();
         MainWindowx->CommandWindow->Listbox->Insert("\r\n");
         uAfter = MainWindowx->CommandWindow->Listbox->GetTextLen();

         /* if last 2 bytes inserted ok get out */

         if (uCheck+2 == uAfter) return;

         /* strip what we inserted */

         MainWindowx->CommandWindow->Listbox->SetReadOnly(FALSE);

         MainWindowx->CommandWindow->Listbox->SetSelection(uBefore, uAfter);
         MainWindowx->CommandWindow->Listbox->DeleteSelection();

         /* strip 4k off top */

         MainWindowx->CommandWindow->Listbox->SetSelection(0, 4096);
         MainWindowx->CommandWindow->Listbox->DeleteSelection();

         MainWindowx->CommandWindow->Listbox->SetReadOnly(TRUE);
         }

      // if all else fails try this, should never get here
      clearcombobox();
      MainWindowx->CommandWindow->Listbox->Insert(str);
      MainWindowx->CommandWindow->Listbox->Insert("\r\n");

      }
   }

int promptuser(char *str, char *pmt)
   {
   *str = '\0';
   if (MainWindowx->MyPopupInput(str, pmt) == 0)
      {
      return 0;
      //    if (halt_flag) Time_To_Halt = 1;
      //      MainWindowx->CommandWindow->PostMessage(WM_COMMAND, ID_HALT, ID_HALT);
      }
   else
      {
      return 1;
      }
   }

void single_step_box(NODE *the_line)
   {
   char textbuf[MAX_BUFFER_SIZE];

   // pop up single step box showing line of code

   print_stringptr = textbuf;
   print_stringlen = MAX_BUFFER_SIZE;
   ndprintf((FILE *) NULL, "%p", the_line);
   *print_stringptr = '\0';

   if (MainWindowx->CommandWindow->MessageBox(
           textbuf,
           "Single Step",
           MB_OKCANCEL) == IDCANCEL)
      {
      if (stepflag)
         {
         stepflag = 0;
         MainWindowx->CommandWindow->SendDlgItemMsg(ID_YIELD, WM_SETTEXT, 0, (DWORD) "Step");
         }
      else
         {
         err_logo(STOP_ERROR, NIL);
         }
      }
   }

void getcombobox(char *str)
   {
   // get it and clear it

   SelectedText[0] = '\0';

   MainWindowx->CommandWindow->Editbox->GetText(str, MAX_BUFFER_SIZE);
   MainWindowx->CommandWindow->Editbox->Clear();
   }


bool TMyApp::ProcessAppMsg(MSG &msg)
   {
   if (MainWindow && TranslateAccelerator(MainWindow->HWindow, HAccTable, &msg))
      {
      return true;
      }

   return TApplication::ProcessAppMsg(msg);
   }

void TMyApp::InitInstance()
   {
   TApplication::InitInstance();
   HAccTable = LoadAccelerators("LOGOACC");
   }

bool TMyApp::IdleAction(long idleCount)
   {
   // this is the time to exit, when things are settled down

   if (Time_To_Exit)
      {
      Time_To_Exit = 0;
      MainWindow->PostMessage(WM_CLOSE);
      }

   if (bPerspective)
      {
      bPerspective = FALSE;
      lperspective();
      }

   // if command arg loaded then execute

   if (commandarg[0] != '\0')
      {
      silent_load(NIL, commandarg);
      commandarg[0] = '\0';
      }

   checkqueue();

   return TApplication::IdleAction(idleCount);
   }

void TMyApp::InitMainWindow()
   {
   /* create the window */
   TPaneSplitter * paneSpliter = new TPaneSplitter(NULL);
   MainWindowx = new TMainFrame(NULL, Name, paneSpliter);
   SetMainWindow(MainWindowx);

   /* set appropriate default colors */

   pcolor = 0x00000000;
   scolor = 0x00ffffffL;
   fcolor = 0x00000000L;

   dpenr = 0x00;
   dpeng = 0x00;
   dpenb = 0x00;

   dfldr = 0x00;
   dfldg = 0x00;
   dfldb = 0x00;

   dscnr = 0xff;
   dscng = 0xff;
   dscnb = 0xff;

   // init the font structure

   FontRec.lfHeight = 24;
   FontRec.lfWidth = 0;
   FontRec.lfOrientation = 0;
   FontRec.lfWeight = 400;
   FontRec.lfItalic = 0;
   FontRec.lfUnderline = 0;
   FontRec.lfStrikeOut = 0;
   FontRec.lfCharSet = ANSI_CHARSET;
   FontRec.lfOutPrecision = OUT_DEFAULT_PRECIS;
   FontRec.lfClipPrecision = CLIP_DEFAULT_PRECIS;
   FontRec.lfQuality = DEFAULT_QUALITY;
   FontRec.lfPitchAndFamily = DEFAULT_PITCH;
   strcpy(FontRec.lfFaceName, "Arial");

   /* init all the pens based on the color */

   NormalPen.lopnStyle = PS_INSIDEFRAME;
   NormalPen.lopnWidth.x = width;
   NormalPen.lopnColor = pcolor;

   ErasePen.lopnStyle = PS_INSIDEFRAME;
   ErasePen.lopnWidth.x = width;
   ErasePen.lopnColor = scolor;

   FloodBrush.lbStyle = BS_SOLID;
   FloodBrush.lbColor = fcolor;
   FloodBrush.lbHatch = HS_VERTICAL;

   ScreenBrush.lbStyle = BS_SOLID;
   ScreenBrush.lbColor = scolor;
   ScreenBrush.lbHatch = HS_VERTICAL;

   // determine how big a window we would like
   int x = 0;
   int y = 0;
   int w = BitMapWidth;
   int h = BitMapHeight;
   
   // if fixed mode
   if (bFixed)
      {
      if (bHeight)
         {
         // if height specified santize it against screen height
         h = min(h, MaxHeight);
         }
      else
         {
         // else choose something reasonable
         h = (int) (MaxHeight * ScreenSz);
         }

      if (bWidth)
         {
         // if width specified santize it against screen width
         w = min(w, MaxWidth);
         }
      else
         {
         // else choose something reasonable
         w = MaxWidth;
         }

      // fit the bitmap to the size of the window
      BitMapWidth  = w;
      BitMapHeight = h;
      }
   else
      {
      // sanatize window size we would like against screen screen size
      w = min(w, MaxWidth);
      h = min(h, (int) (MaxHeight * ScreenSz));

      GetPrivateProfileQuadruple(
         "LOGO",
         "Screen",
         &x,
         &y,
         &w,
         &h);

      // The "Screen" also has the height of the commander
      // window and the splitter that goes between the
      // screen and the commander window.
      // We must subtract these out to get the real height.
      int commander_x      = 0;
      int commander_y      = 0;
      int commander_width  = 0;
      int commander_height = DEFAULT_COMMANDER_HEIGHT;
      GetPrivateProfileQuadruple(
         "LOGO",
         "Commander",
         &commander_x,
         &commander_y,
         &commander_width,
         &commander_height);

      // sanity-check the input
      if (0 < commander_height && commander_height < h)
        {
        h -= commander_height;
        }

      h -= DEFAULT_SPLITTER_WIDTH;

      // sanatize against screen size
      checkwindow(&x, &y, &w, &h);
      }

   MainWindowx->SetWindowPos(
      NULL,
      x,
      y,
      w,
      h,
      SWP_NOZORDER);

   // Set handy rectangle of full bitmap
   SetRect(&FullRect, 0, 0, BitMapWidth, BitMapHeight);

   // turtle coords are in center
   xoffset = BitMapWidth  / 2;
   yoffset = BitMapHeight / 2;

   // Init active area even if off
   PrinterAreaXLow  = -BitMapWidth  / 2;
   PrinterAreaXHigh = +BitMapWidth  / 2;
   PrinterAreaYLow  = -BitMapHeight / 2;
   PrinterAreaYHigh = +BitMapHeight / 2;

   PrinterAreaPixels = max(BitMapWidth, BitMapHeight) / 8;

   // clear bitmap to white
   HDC screenDC = CreateDC("DISPLAY", NULL, NULL, NULL);
   if (screenDC != NULL)
      {
      MemoryBitMap = CreateCompatibleBitmap(screenDC, BitMapWidth, BitMapHeight);

      HDC memoryDC = CreateCompatibleDC(screenDC);
      if (memoryDC != NULL)
         {
         OldBitmap = (HBITMAP) SelectObject(memoryDC, MemoryBitMap);

         PatBlt(memoryDC, 0, 0, BitMapWidth, BitMapHeight, WHITENESS);

         SelectObject(memoryDC, OldBitmap);

         DeleteDC(memoryDC);
         }

      DeleteDC(screenDC);
      }

   ModulehInstance = HInstance;

   /* init paths to library and help files based on locaation of .EXE */

   MakeHelpPathName(LibPathName, "logolib\\");
   logolib = LibPathName;
   MakeHelpPathName(szHelpFileName, "logo.hlp");

   DWORD tempPathLength;
   char  tempPath[MAX_PATH];
   bool  tempPathIsValid = false;

   tempPathLength = GetTempPath(
      sizeof tempPath,
      tempPath);
   if (tempPathLength != 0)
      {
      DWORD tempPathAttributes = GetFileAttributes(tempPath);
      if (tempPathAttributes != 0xFFFFFFFF)
         {
         // tempPath must be a directory that we can write to
         if ( (tempPathAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
             !(tempPathAttributes & FILE_ATTRIBUTE_READONLY))
            {
            tempPathIsValid = true;
            }
         }
      }

   if (!tempPathIsValid)
      {
      MessageBox(
         0,
         "The environment variable TMP is not defined or invalid.\n"
            "FMSLogo will attempt to use C:\\ for storing temporary files",
         "Warning",
         MB_OK);

      strcpy(tempPath, "C:");
      tempPathLength = strlen("C:");
      }

   // construct the name of the temporary editor file
   strcpy(TempPathName, tempPath);
   if (TempPathName[tempPathLength - 1] == '\\')
      {
      TempPathName[tempPathLength - 1] = '\0';
      }
   strcat(TempPathName, "\\mswlogo.tmp");

   // construct the name of the temporary bitmap file
   strcpy(TempBmpName, tempPath);
   if (TempBmpName[tempPathLength - 1] == '\\')
      {
      TempBmpName[tempPathLength - 1] = '\0';
      }
   strcat(TempBmpName, "\\mswlogo.bmp");

   // construct the name of the clipboard file
   strcpy(TempClipName, tempPath);
   if (TempClipName[tempPathLength - 1] == '\\')
      {
      TempClipName[tempPathLength - 1] = '\0';
      }
   strcat(TempClipName, "\\mswlogo.clp");


   MakeHelpPathName(MCIHelpFileName, "mcistrwh.hlp");

   PrinterAreaXLow  = GetPrivateProfileInt("Printer", "Xlow",  -BitMapWidth  / 2, "LOGO.INI");
   PrinterAreaXHigh = GetPrivateProfileInt("Printer", "XHigh", +BitMapWidth  / 2, "LOGO.INI");
   PrinterAreaYLow  = GetPrivateProfileInt("Printer", "Ylow",  -BitMapHeight / 2, "LOGO.INI");
   PrinterAreaYHigh = GetPrivateProfileInt("Printer", "YHigh", +BitMapHeight / 2, "LOGO.INI");

   PrinterAreaPixels = GetPrivateProfileInt("Printer", "Pixels", max(BitMapWidth, BitMapHeight) / 8, "LOGO.INI");

   if ((PrinterAreaXLow  == -BitMapWidth  / 2) &&
       (PrinterAreaXHigh == +BitMapWidth  / 2) &&
       (PrinterAreaYLow  == -BitMapHeight / 2) &&
       (PrinterAreaYHigh == +BitMapHeight / 2))
      {
      IsPrinterSettingCustom = false;
      }
   else
      {
      IsPrinterSettingCustom = true;
      }
   }

TMyApp::~TMyApp()
   {
   //   delete MainWindowx;
   }

void TMyApp::EvSysColorChange()
   {
   }

void MyMessageScan()
   {
   MSG msg;

   /* depending on yield flag check for messages */

   if (yield_flag)
      {
      while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
         {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
         }
      }
   }

// Print page (or pages)

void TRulerOut::PrintPage(int /* page */, TRect & /* rect */, UINT /* flags */)
   {
   MainWindowx->ScreenWindow->Printit(*DC);
   }


int *TopOfStack;

int WINAPI
WinMain(
   HINSTANCE hInstance,
   HINSTANCE hPrevInstance,
   LPSTR     lpCmdLine,
   int       nCmdShow
)
   {
   int i;
   char *ptr;
   HDC TempDC;

   // Check to see if another instance of Logo is currently running:
   HANDLE singleInstanceMutex = CreateMutex(
      NULL,  // default security attributes
      FALSE, // no initial owner
      "LogoForWindowsMutex");

   if (GetLastError() == ERROR_ALREADY_EXISTS)
      {
      // A copy of Logo is already running.
      // Find that window and make it visible.
      HWND runningInstance = FindWindow(NULL, "FMSLogo");
      if (runningInstance != NULL)
         {
         // bring running instance to the the foreground
         ::SetForegroundWindow(runningInstance);
         if (::IsIconic(runningInstance))
            {
            // the running instance is minimized, so restore it
            ::ShowWindow(runningInstance, SW_RESTORE);
            }

         CloseHandle(singleInstanceMutex);
         return 1;
         }

      // We can't find the window, so we'll start up another instance.
      // The feature of not running two instances is supposed to make
      // things simpler.  If the other copy of Logo failed to exit
      // cleanly, or if some other application created the mutex,
      // it would more confusing if this Logo didn't start up.
      }

   _control87( EM_OVERFLOW, EM_OVERFLOW );
   _control87( EM_UNDERFLOW, EM_UNDERFLOW );

   TopOfStack = &i;

   // parse -h height -w width as being the bitmap size

   commandarg[0] = '\0';
   bPerspective = FALSE;
   bExpert      = FALSE;
   bFixed       = FALSE;
   bWidth       = FALSE;
   bHeight      = FALSE;

   for (ptr = lpCmdLine; *ptr != '\0'; ptr++)
      {
      if (*ptr == '-')
         {
         if (*++ptr == '\0')
            {
            MessageBox(GetFocus(), lpCmdLine, "Invalid Command Line", MB_OK);
            break;
            }
         switch (*ptr++)
            {
             case 'p':
             case 'P':
                bPerspective = TRUE;
                break;

             case 'e':
             case 'E':
                bExpert = TRUE;
                break;

             case 'f':
             case 'F':
                bFixed = TRUE;
                break;

             case 'h':
             case 'H':
                i = 0;
                for (; ((*ptr == ' ') || ((*ptr >= '0') && (*ptr <= '9'))); ptr++)
                   {
                   commandarg[i++] = *ptr;
                   }
                ptr--;
                commandarg[i] = '\0';
                sscanf(commandarg, "%d", &BitMapHeight);
                commandarg[0] = '\0';
                bHeight = TRUE;
                break;

             case 'w':
             case 'W':
                i = 0;
                for (; ((*ptr == ' ') || ((*ptr >= '0') && (*ptr <= '9'))); ptr++)
                   {
                   commandarg[i++] = *ptr;
                   }
                ptr--;
                commandarg[i] = '\0';
                sscanf(commandarg, "%d", &BitMapWidth);
                commandarg[0] = '\0';
                bWidth = TRUE;
                break;

             case 'l':
             case 'L':
                i = 0;
                for (; (*ptr == ' '); ptr++)
                   {
                   }
                for (; (*ptr != '\0'); ptr++)
                   {
                   commandarg[i++] = *ptr;
                   }
                break;

             default:
                MessageBox(GetFocus(), lpCmdLine, "Invalid Command Line", MB_OK);
                break;
            }
         }
      }

      
   // if fixed mode then make unspecified dimensions
   // really large (shrink to fit)
   if (bFixed)
      {
      if (!bWidth)
         {
         BitMapWidth  = 2048;
         }
      if (!bHeight)
         {
         BitMapHeight = 2048;
         }
      }


   // Get garbage collector stack size from logo.ini
   GCMAX = GetPrivateProfileInt("LOGO", "GCStackSize", 8192, "LOGO.INI");

   // Get Max Physical line from logo.ini
   MAX_PHYS_LINE = GetPrivateProfileInt("LOGO", "MaxPhysLine", 8192, "LOGO.INI");

   /* Get video mode parameters */
   TempDC = GetDC(0);

   RECT MaxRect;
   SystemParametersInfo(SPI_GETWORKAREA, 0, &MaxRect, 0);
   MaxWidth  = MaxRect.right  - MaxRect.left;
   MaxHeight = MaxRect.bottom - MaxRect.top;

   MaxColors = pow(
      2,
      GetDeviceCaps(TempDC, BITSPIXEL) + GetDeviceCaps(TempDC, PLANES));

   ReleaseDC(0, TempDC);

   // Get Dialog Units for Controls

   BaseUnitsx = LOWORD(GetDialogBaseUnits());
   BaseUnitsy = HIWORD(GetDialogBaseUnits());

   TMyApp MyApp("FMSLogo", hInstance, hPrevInstance, lpCmdLine, nCmdShow);

   srand(time(NULL));

   // alloc and init hash table
   hash_table = (NODE **) calloc(sizeof(NODE *), HASH_LEN);

   // alloc garbage collector stack
   gcstack = (NODE **) malloc(sizeof(NODE *) *GCMAX);

   gctop = gcstack;

   // init the timer callback array

   for (i = 0; i < MAX_TIMERS; i++)
      {
      timer_callback[i] = NULL;
      }

   // alloc and init the bitmap cut array
   CutBmp = (CUTMAP *) malloc(sizeof(CUTMAP) * MaxBitCuts);

   memset(CutBmp, 0, sizeof(CUTMAP) * MaxBitCuts);

   // init logo kernel

   init();

   /* get an hourglass cursor */

   hCursorWait = LoadCursor(NULL, IDC_WAIT);
   hCursorArrow = LoadCursor(NULL, IDC_ARROW);

   // go for it

   MyApp.Run();

   lnetshutdown();

   CloseHandle(singleInstanceMutex);
   return MyApp.Status;
   }

void transline3d(LOGPEN &logPen, long modex, FLONUM fromx, FLONUM fromy, FLONUM fromz, FLONUM tox, FLONUM toy, FLONUM toz)
   {
   VECTOR from3d;
   from3d.x = fromx / WorldWidth;
   from3d.y = fromy / WorldHeight;
   from3d.z = fromz / WorldDepth;

   VECTOR to3d;
   to3d.x = tox / WorldWidth;
   to3d.y = toy / WorldHeight;
   to3d.z = toz / WorldDepth;

   if (bPolyFlag)
      {
      if (!ThePolygon ||
          (fabs(ThePolygon->Vertex.x - to3d.x) > epsilon) ||
          (fabs(ThePolygon->Vertex.y - to3d.y) > epsilon) ||
          (fabs(ThePolygon->Vertex.z - to3d.z) > epsilon))
         {
         ThreeD.AddPoint(&ThePolygon, to3d);
         }
      }

   POINT from2d;
   POINT to2d;
   if (!ThreeD.TransformSegment(from3d, to3d, from2d, to2d))
      {
      return;
      }

   long iFromx =  from2d.x + xoffset;
   long iFromy = -from2d.y + yoffset;
   long iTox   =  to2d.x   + xoffset;
   long iToy   = -to2d.y   + yoffset;

   HPEN hPen = CreatePenIndirect(&logPen);

   HDC ScreenDC = GetDC(MainWindowx->ScreenWindow->HWindow);
   HDC MemDC = CreateCompatibleDC(ScreenDC);
   OldBitmap = (HBITMAP) SelectObject(MemDC, MemoryBitMap);

   if (EnablePalette)
      {
      OldPalette = SelectPalette(MemDC, ThePalette, FALSE);
      RealizePalette(MemDC);
      }

   SetROP2(MemDC, modex);

   HPEN oldPen = (HPEN) SelectObject(MemDC, hPen);

   MoveToEx(MemDC, iFromx, iFromy, 0);
   LineTo(MemDC, iTox, iToy);

   if (EnablePalette)
      {
      SelectPalette(MemDC, OldPalette, FALSE);
      }

   // restore the pen and bitmap
   SelectObject(MemDC, oldPen);
   SelectObject(MemDC, OldBitmap);
   DeleteDC(MemDC);

   // screen

   //   ::SetCapture(MainHWindow);
   SetROP2(ScreenDC, modex);

   if (EnablePalette)
      {
      OldPalette = SelectPalette(ScreenDC, ThePalette, FALSE);
      RealizePalette(ScreenDC);
      }

   oldPen = (HPEN) SelectObject(ScreenDC, hPen);

   if (zoom_flag)
      {
      MainWindowx->ScreenWindow->Invalidate(false);
      }
   else
      {
      MoveToEx(
         ScreenDC,
         iFromx - MainWindowx->ScreenWindow->Scroller->XPos,
         iFromy - MainWindowx->ScreenWindow->Scroller->YPos,
         0);

      LineTo(
         ScreenDC,
         iTox - MainWindowx->ScreenWindow->Scroller->XPos,
         iToy - MainWindowx->ScreenWindow->Scroller->YPos);
      }

   if (EnablePalette)
      {
      SelectPalette(ScreenDC, OldPalette, FALSE);
      }

   SelectObject(ScreenDC, oldPen);

   DeleteObject(hPen);
   ReleaseDC(MainWindowx->ScreenWindow->HWindow, ScreenDC);
   }

void transline(LOGPEN &logPen, long modex, FLONUM fromx, FLONUM fromy, FLONUM tox, FLONUM toy)
   {
   long iFromx =  g_round(fromx) + xoffset;
   long iFromy = -g_round(fromy) + yoffset;
   long iTox   =  g_round(tox)   + xoffset;
   long iToy   = -g_round(toy)   + yoffset;

   HPEN hPen = CreatePenIndirect(&logPen);

   HDC ScreenDC = GetDC(MainWindowx->ScreenWindow->HWindow);
   HDC MemDC = CreateCompatibleDC(ScreenDC);

   HBITMAP oldBitmap = (HBITMAP) SelectObject(MemDC, MemoryBitMap);
   if (EnablePalette)
      {
      OldPalette = SelectPalette(MemDC, ThePalette, FALSE);
      RealizePalette(MemDC);
      }

   SetROP2(MemDC, modex);

   HPEN oldPen = (HPEN) SelectObject(MemDC, hPen);

   MoveToEx(MemDC, iFromx, iFromy, 0);

   LineTo(MemDC, iTox, iToy);

   if (EnablePalette)
      {
      SelectPalette(MemDC, OldPalette, FALSE);
      }

   // restore the previous bitmap and pen
   SelectObject(MemDC, oldPen);
   SelectObject(MemDC, oldBitmap);
   DeleteDC(MemDC);

   // screen

   //   ::SetCapture(MainHWindow);
   SetROP2(ScreenDC, modex);

   if (EnablePalette)
      {
      OldPalette = SelectPalette(ScreenDC, ThePalette, FALSE);
      RealizePalette(ScreenDC);
      }

   oldPen = (HPEN) SelectObject(ScreenDC, hPen);

   if (zoom_flag)
      {
      MainWindowx->ScreenWindow->Invalidate(false);
      }
   else
      {
      MoveToEx(
         ScreenDC,
         iFromx - MainWindowx->ScreenWindow->Scroller->XPos,
         iFromy - MainWindowx->ScreenWindow->Scroller->YPos,
         0);
      
      LineTo(
         ScreenDC,
         iTox   - MainWindowx->ScreenWindow->Scroller->XPos,
         iToy   - MainWindowx->ScreenWindow->Scroller->YPos);
      }

   if (EnablePalette)
      {
      SelectPalette(ScreenDC, OldPalette, FALSE);
      }

   // restore the previous pen
   SelectObject(ScreenDC, oldPen);

   DeleteObject(hPen);
   //   ReleaseCapture();
   ReleaseDC(MainWindowx->ScreenWindow->HWindow, ScreenDC);
   }

typedef struct line_segent
   {
   VECTOR from;
   VECTOR to;
   } LINE3D;

LINE3D turtle_vertices[4] =
   {
      {{-16.0, 0.0, 0.0},{ 16.0,  0.0, 0.0}},
      {{ 16.0, 0.0, 0.0},{  0.0, 16.0, 0.0}},
      {{  0.0,16.0, 0.0},{-16.0,  0.0, 0.0}},
      {{  8.0, 0.0, 0.0},{  8.0,  8.0, 0.0}}
   }
;

void ibmturt(int hide)
   {
   FLONUM rx;
   FLONUM ry;

   FLONUM oldx;
   FLONUM oldy;
   FLONUM Cz;
   FLONUM Sz;

   long iOldx;
   long iOldy;
   long iNewx;
   long iNewy;
   long j;
   long iFromx;
   long iFromy;
   long iTox;
   long iToy;

   TRect temp;

   VECTOR rp;

   VECTOR from3d;
   VECTOR to3d;

   POINT from2d;
   POINT to2d;

   BOOL bMinMax = FALSE;

   FLONUM newx = 0.0;
   FLONUM newy = 0.0;

   long minx = 100000;
   long miny = 100000;
   long maxx = -100000;
   long maxy = -100000;

   if (hide == 1)
      {

      for (j = 0; j < 4; j++)
         {

         if (current_mode == perspectivemode)
            {
            rp = MVxyMultiply(turtle_matrix[turtle_which], turtle_vertices[j].from);

            from3d.x = (turtle_p[turtle_which].x + rp.x) / BitMapWidth;
            from3d.y = (turtle_p[turtle_which].y + rp.y) / BitMapWidth;
            from3d.z = (turtle_p[turtle_which].z + rp.z) / BitMapWidth;

            rp = MVxyMultiply(turtle_matrix[turtle_which], turtle_vertices[j].to);

            to3d.x = (turtle_p[turtle_which].x + rp.x) / BitMapWidth;
            to3d.y = (turtle_p[turtle_which].y + rp.y) / BitMapWidth;
            to3d.z = (turtle_p[turtle_which].z + rp.z) / BitMapWidth;

            if (ThreeD.TransformSegment(from3d, to3d, from2d, to2d))
               {
               iFromx =  from2d.x + xoffset;
               iFromy = -from2d.y + yoffset;
               iTox   =  to2d.x   + xoffset;
               iToy   = -to2d.y   + yoffset;
               
               minx = min(minx, (long) from2d.x);
               miny = min(miny, (long) from2d.y);
               maxx = max(maxx, (long) from2d.x);
               maxy = max(maxy, (long) from2d.y);

               bMinMax = TRUE;
               
               TurtlePoints[turtle_which][j].from.x = iFromx;
               TurtlePoints[turtle_which][j].from.y = iFromy;
               TurtlePoints[turtle_which][j].to.x   = iTox;
               TurtlePoints[turtle_which][j].to.y   = iToy;
               TurtlePoints[turtle_which][j].bValid = TRUE;
               }
            else
               {
               TurtlePoints[turtle_which][j].bValid = FALSE;
               }
            }
         else
            {
            Cz = cos(-turtle_heading[turtle_which] * RADCVT);
            Sz = sin(-turtle_heading[turtle_which] * RADCVT);

            rx = Cz * turtle_vertices[j].from.x - Sz * turtle_vertices[j].from.y;
            ry = Sz * turtle_vertices[j].from.x + Cz * turtle_vertices[j].from.y;

            oldx = turtle_p[turtle_which].x + rx;
            oldy = turtle_p[turtle_which].y + ry;
            
            rx = Cz * turtle_vertices[j].to.x - Sz * turtle_vertices[j].to.y;
            ry = Sz * turtle_vertices[j].to.x + Cz * turtle_vertices[j].to.y;
            
            newx = turtle_p[turtle_which].x + rx;
            newy = turtle_p[turtle_which].y + ry;
            
            iOldx = g_round(oldx);
            iOldy = g_round(oldy);
            iNewx = g_round(newx);
            iNewy = g_round(newy);
            
            iFromx =  iOldx + xoffset;
            iFromy = -iOldy + yoffset;
            iTox   =  iNewx + xoffset;
            iToy   = -iNewy + yoffset;
                        
            minx = min(minx, iOldx);
            miny = min(miny, iOldy);
            maxx = max(maxx, iOldx);
            maxy = max(maxy, iOldy);

            bMinMax = TRUE;
            
            TurtlePoints[turtle_which][j].from.x = iFromx;
            TurtlePoints[turtle_which][j].from.y = iFromy;
            TurtlePoints[turtle_which][j].to.x   = iTox;
            TurtlePoints[turtle_which][j].to.y   = iToy;

            TurtlePoints[turtle_which][j].bValid = TRUE;
            TurtlePoints[turtle_which][3].bValid = FALSE;
            }
         }
      }
   else
      {
      // consider adding these to turtle points for efficiency
      for (j = 0; j < 4; j++)
         {
         if (TurtlePoints[turtle_which][j].bValid)
            {
            minx = min(minx, (long) (+(TurtlePoints[turtle_which][j].from.x - xoffset)));
            miny = min(miny, (long) (-(TurtlePoints[turtle_which][j].from.y - yoffset)));
            maxx = max(maxx, (long) (+(TurtlePoints[turtle_which][j].from.x - xoffset)));
            maxy = max(maxy, (long) (-(TurtlePoints[turtle_which][j].from.y - yoffset)));
            bMinMax = TRUE;
            }
         }
      }
   
   if (turtle_bitmap[turtle_which])
      {
      POINT dest;

      if (current_mode == perspectivemode)
         {
         VECTOR from3d;

         from3d.x = turtle_p[turtle_which].x / WorldWidth;
         from3d.y = turtle_p[turtle_which].y / WorldHeight;
         from3d.z = turtle_p[turtle_which].z / WorldDepth;

         if (ThreeD.TransformPoint(from3d, dest))
            {
            bMinMax = TRUE;
            }
         else
            {
            bMinMax = FALSE;
            }
         }
      else
         {
         dest.x = g_round(turtle_p[turtle_which].x);
         dest.y = g_round(turtle_p[turtle_which].y);
         }

      temp.Set(
         (+dest.x - MainWindowx->ScreenWindow->Scroller->XPos / the_zoom + xoffset                                      ) * the_zoom,
         (-dest.y - MainWindowx->ScreenWindow->Scroller->YPos / the_zoom + yoffset + LL - CutBmp[turtle_which].CutHeight) * the_zoom,
         (+dest.x - MainWindowx->ScreenWindow->Scroller->XPos / the_zoom + xoffset + CutBmp[turtle_which].CutWidth      ) * the_zoom,
         (-dest.y - MainWindowx->ScreenWindow->Scroller->YPos / the_zoom + yoffset + LL                                 ) * the_zoom);

      temp.Normalize();
      }
   else
      {
      temp.left   = (+minx - MainWindowx->ScreenWindow->Scroller->XPos / the_zoom + xoffset) * the_zoom;
      temp.top    = (-maxy - MainWindowx->ScreenWindow->Scroller->YPos / the_zoom + yoffset) * the_zoom;
      temp.right  = (+maxx - MainWindowx->ScreenWindow->Scroller->XPos / the_zoom + xoffset) * the_zoom;
      temp.bottom = (-miny - MainWindowx->ScreenWindow->Scroller->YPos / the_zoom + yoffset) * the_zoom;
      }


   temp.Inflate(1+the_zoom,1+the_zoom);
   
   if (bMinMax)
      {
      MainWindowx->ScreenWindow->InvalidateRect(temp, false);
      }
   }

void ibmfrom(NUMBER x, NUMBER y)
   {
   ibmoldx = x;
   ibmoldy = y;
   }

void ibmfrom3d(NUMBER x, NUMBER y, NUMBER z)
   {
   ibmoldx = x;
   ibmoldy = y;
   ibmoldz = z;
   }

void ibmto(NUMBER x, NUMBER y)
   {
   if (pen_vis == 0)
      {
      if (turtle_which >= (TURTLES - TURTLEN)) return;

      vector_count++;
      if (status_flag) update_status_vectors();

      if (in_erase_mode)
         {
         transline(ErasePen, R2_COPYPEN, ibmoldx, ibmoldy, x, y);
         }
      else if (current_write_mode == XOR_PUT)
         {
         transline(NormalPen, R2_NOT, ibmoldx, ibmoldy, x, y);
         }
      else
         {
         transline(NormalPen, R2_COPYPEN, ibmoldx, ibmoldy, x, y);
         }
      }
   }

void ibmto3d(NUMBER x, NUMBER y, NUMBER z)
   {
   if (pen_vis == 0)
      {
      if (turtle_which >= (TURTLES - TURTLEN)) return;

      vector_count++;
      if (status_flag) update_status_vectors();

      if (in_erase_mode)
         {
         transline3d(ErasePen, R2_COPYPEN, ibmoldx, ibmoldy, ibmoldz, x, y, z);
         }
      else if (current_write_mode == XOR_PUT)
         {
         transline3d(NormalPen, R2_NOT, ibmoldx, ibmoldy, ibmoldz, x, y, z);
         }
      else
         {
         transline3d(NormalPen, R2_COPYPEN, ibmoldx, ibmoldy, ibmoldz, x, y, z);
         }
      }
   }

void MakeHelpPathName(char *OutBuffer, const char * TheFileName)
   {
   char *pcFileName;
   int nFileNameLen;

   nFileNameLen = GetModuleFileName(ModulehInstance, OutBuffer, EXE_NAME_MAX_SIZE);
   pcFileName = OutBuffer + nFileNameLen;

   while (pcFileName > OutBuffer)
      {
      if (*pcFileName == '\\' || *pcFileName == ':')
         {
         * (++pcFileName) = '\0';
         break;
         }
      nFileNameLen--;
      pcFileName--;
      }

   // BUG: Why 13?
   if ((nFileNameLen + 13) < EXE_NAME_MAX_SIZE)
      {
      lstrcat(OutBuffer, TheFileName);
      }
   else
      {
      lstrcat(OutBuffer, "?");
      }
   }


void ContextHelp(HWND /* hWindow */, TEdit *Editor)
   {
   UINT start;
   UINT end;

   // get the keyword selected

   Editor->GetSelection(start, end);
   if (start != end)
      {
      char theText[80];
      Editor->GetSubText(theText, start, end);

      // clean up line before passing to help

      int i = strlen(theText) - 1;
      while ((theText[i] == ' ') && (i > 0))
         {
         theText[i--] = '\0';
         }

      i = 0;
      while ((theText[i] == ' ') && (i < 80))
         {
         i++;
         }

      char *ptr = theText + i;

      do_help(ptr);
      }
   else
      {
      do_help(NULL);
      }
   }

DEFINE_RESPONSE_TABLE1(TMyApp, TApplication)
  EV_WM_SYSCOLORCHANGE,
END_RESPONSE_TABLE;

