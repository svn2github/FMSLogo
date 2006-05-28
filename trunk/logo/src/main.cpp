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
#include "const.h"

CUTMAP *CutBmp;              // Pointer to Bit Cut memory array malloc on init

//HANDLE HashHandle = 0;           // Handle to Hashtable
//HANDLE StackHandle = 0;          // Handle to Garbage Collector Stack
bool bExpert;                      // Expert mode
bool bFixed;                       // Fixed mode
bool bWidth;                       // Width mode
bool bHeight;                      // Height mode
static bool bPerspective;          // Perspetive mode start up

HBITMAP MemoryBitMap;              /* Backing store bitmap                */

HCURSOR hCursorWait;               /* handle for hour glass cursor    */
HCURSOR hCursorArrow;              /* handle for normal cursor        */

HPALETTE ThePalette;                   /* Handle for the single color palette */

LPLOGPALETTE MyLogPalette;      /* Handle for the single logical color palette*/

FLONUM the_zoom = 1.0;             // current zoom factor
Point  g_OldPos = {0.0, 0.0, 0.0}; // global store for x,y,z "From" routine

NODE *current_line = NIL;       // current line to be parsed

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
HPALETTE OldPalette;

LOGFONT FontRec;
LOGFONT EditFontRec;

LOGPEN NormalPen;                      // Handle to "Normal" logical Pen
LOGPEN ErasePen;                       // Handle to "Erase" logical Pen

LOGBRUSH FloodBrush;                   // Handle to the "floodfill" brush
LOGBRUSH ScreenBrush;                  // Handle to the "screen" background brush

RECT FullRect;                         // Ready rectangle of Full bitmap

TMainFrame *MainWindowx;               // Pointer to the Main window

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

int GCMAX = 8192;                      // Garbage Collector Stack Size (Logo.ini)
int MAX_PHYS_LINE = 8192;              // Maximum Physical Line Size (Logo.ini)
Color dpen;                            // Current pen color
Color dfld;                            // Current flood color
Color dscn;                            // Current screen color
bool IsDirty = false;                  // Flag to signal to query user ok to quit
int BitMapWidth = 1000;                // Current bitmap size in X
int BitMapHeight = 1000;               // Current bitmap size in Y
int WorldWidth = 1000;                 // Current World size in X
int WorldHeight = 1000;                // Current World size in Y
int WorldDepth = 1000;                 // Current World size in Z
bool EnablePalette;                    // Flag to signal 256 color mode with palette
bool IsPrinterSettingCustom = false;   // Flag to signal Active area is active
bool IsTPrinterSettingCustom = false;  // Dynamic copy of CustomFlag
bool IsOkayToUseCommanderWindow = false; // Flag to signal it's OK to write to recall box
bool traceflag = false;                // Flag to signal trace button is active
bool stepflag = false;                 // Flag to signal step button is active
int pause_flag = 0;                    // Flag to signal pause button is pushed
int yield_flag = 1;                    // Flag to signal yield state
bool status_flag = false;              // Flag to signal status box is popped up
int MaxWidth = 0;                      // Actual Main window size x
int MaxHeight = 0;                     // Actual Main window size y
int xoffset = 0;                       // Used to go from logo to windows coords x
int yoffset = 0;                       // Used to go from logo to windows coords y
bool GiveFocusToEditbox = false;       // Flag to signal that focus should go to the editbox
bool IsTimeToExit = false;             // Flag to signal it's time to exit
bool IsTimeToPause = false;            // UCBLOGO? pause flag
bool IsTimeToHalt = false;             // UCBLOGO? halt flag
bool error_happen;                     // Flag to signal Error happened on edit reload
KEYBOARDCAPTURE KeyboardCapture = KEYBOARDCAPTURE_Off; // Flag to signal Keyboard is enabled
int keyboard_value = 0;                // Value of Keyboard key
bool MouseCaptureIsEnabled = false;    // Flag to signal Mouse is enabled
int mouse_posx = 0;                    // Value of Mouse position x
int mouse_posy = 0;                    // Value of Mouse position y
int memory_count = 0;                  // Current amount of logo segments malloc'd
int BaseUnitsx = 0;                    // X Units Windows uses to for units in dialog
int BaseUnitsy = 0;                    // Y Units Windows uses to for units in dialog

long eval_count = 0;                   // current count of "evaluations" calls
long vector_count = 0;                 // current count of vectors drawn
COLORREF scolor = 1;                   // screen color
COLORREF fcolor = 1;                   // flood color
COLORREF pcolor = 1;                   // pen color
long width = 1;                        // pen width
long zoom_flag = 0;                    // flag to signal in zoomed state
long MaxColors = 0;                    // The maximum # of colors available

LINEX TurtlePoints[TURTLES][4];        // used to store 3 vertices of turtle

TThreeDSolid ThreeD;

OSVERSIONINFO g_OsVersionInformation;


typedef struct line_segent
   {
   VECTOR from;
   VECTOR to;
   } LINE3D;

static const LINE3D turtle_vertices[4] =
   {
      {{-16.0, 0.0, 0.0},{ 16.0,  0.0, 0.0}},
      {{ 16.0, 0.0, 0.0},{  0.0, 16.0, 0.0}},
      {{  0.0,16.0, 0.0},{-16.0,  0.0, 0.0}},
      {{  8.0, 0.0, 0.0},{  8.0,  8.0, 0.0}},
   }
;

void cnv_strnode_string(char *textbuf, NODE *arg)
   {
   print_stringptr = textbuf;
   print_stringlen = MAX_BUFFER_SIZE;
   ndprintf((FILE *) NULL, "%p", car(arg));
   assert(print_stringptr - textbuf < MAX_BUFFER_SIZE); // buffer overrun
   *print_stringptr = '\0';
   }

/* adds color to palette */
COLORREF LoadColor(int dpenr, int dpeng, int dpenb)
   {

   /* convert to color and find nearest match */
   COLORREF color = PALETTERGB(dpenr, dpeng, dpenb);
   int Index = GetNearestPaletteIndex(ThePalette, color);

   /* if not exact and room for more then allocate it */
   if ((PALETTERGB(
               MyLogPalette->palPalEntry[Index].peRed,
               MyLogPalette->palPalEntry[Index].peGreen,
               MyLogPalette->palPalEntry[Index].peBlue) != color) && 
       (MyLogPalette->palNumEntries < (MaxColors - 1)))
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
   return color;
   }


void clearcombobox()
   {
   // clear the recall box
   MainWindowx->CommandWindow->Listbox.Clear();

   // scroll it to the top
   MainWindowx->CommandWindow->Listbox.SetCursorAtBottom();
   }

   
void putcombobox(const char *str)
   {
   /* only if OK to write to recall box do we do it */
   if (IsOkayToUseCommanderWindow)
      {
      for (int i=0;i<16;i++)
         {
         /* remember where we started */
         UINT uBefore = MainWindowx->CommandWindow->Listbox.GetTextLen();

         /* output to list box */
         MainWindowx->CommandWindow->Listbox.SetSelection(uBefore, uBefore);
         MainWindowx->CommandWindow->Listbox.Insert(str);
         UINT uCheck = MainWindowx->CommandWindow->Listbox.GetTextLen();
         MainWindowx->CommandWindow->Listbox.Insert("\r\n");
         UINT uAfter = MainWindowx->CommandWindow->Listbox.GetTextLen();

         /* if last 2 bytes inserted ok get out */
         if (uCheck+2 == uAfter) 
            {
            return;
            }

         /* strip what we inserted */
         MainWindowx->CommandWindow->Listbox.SetReadOnly(FALSE);

         MainWindowx->CommandWindow->Listbox.SetSelection(uBefore, uAfter);
         MainWindowx->CommandWindow->Listbox.DeleteSelection();

         /* strip 4k off top */
         MainWindowx->CommandWindow->Listbox.SetSelection(0, 4096);
         MainWindowx->CommandWindow->Listbox.DeleteSelection();

         MainWindowx->CommandWindow->Listbox.SetReadOnly(TRUE);
         }

      // if all else fails try this, should never get here
      clearcombobox();
      MainWindowx->CommandWindow->Listbox.Insert(str);
      MainWindowx->CommandWindow->Listbox.Insert("\r\n");
      }
   }

bool promptuser(char *str, const char *prompt)
   {
   *str = '\0';
   if (MainWindowx->MyPopupInput(str, prompt))
      {
      return true;
      }
   else
      {
      return false;
      // if (!is_executing()) IsTimeToHalt = true;
      // MainWindowx->CommandWindow->PostMessage(WM_COMMAND, ID_HALT, ID_HALT);
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
         // act like someone pressed the "UnStep" button
         MainWindowx->CommandWindow->DoButtonYield(0);
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

   MainWindowx->CommandWindow->Editbox.GetText(str, MAX_BUFFER_SIZE);
   MainWindowx->CommandWindow->Editbox.Clear();
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
   if (IsTimeToExit)
      {
      IsTimeToExit = false;
      MainWindow->PostMessage(WM_CLOSE);
      }

   if (bPerspective)
      {
      bPerspective = false;
      lperspective(NIL);
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

   dpen.red   = 0x00;
   dpen.green = 0x00;
   dpen.blue  = 0x00;

   dfld.red   = 0x00;
   dfld.green = 0x00;
   dfld.blue  = 0x00;

   dscn.red   = 0xff;
   dscn.green = 0xff;
   dscn.blue  = 0xff;

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
         HBITMAP oldBitmap = (HBITMAP) SelectObject(memoryDC, MemoryBitMap);

         PatBlt(memoryDC, 0, 0, BitMapWidth, BitMapHeight, WHITENESS);

         SelectObject(memoryDC, oldBitmap);

         DeleteDC(memoryDC);
         }

      DeleteDC(screenDC);
      }

   ModulehInstance = HInstance;

   // init paths to library and help files based on location of .EXE
   MakeHelpPathName(LibPathName, "logolib\\");
   logolib = LibPathName;
   MakeHelpPathName(szHelpFileName, "logohelp.chm");

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
   /* depending on yield flag check for messages */

   if (yield_flag)
      {
      MSG msg;
      while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
         {     
         TranslateMessage(&msg);
         DispatchMessage(&msg);
         }
      }
   }

// Shows a message box and sets the logo error.
// This helper was created because these two operations appear next
// to each other very often, not because coupling the operations is 
// good design.
void 
ShowMessageAndStop(
   const char * Title,
   const char * Message
   )
   {
   if (MainWindowx->CommandWindow != NULL)
      {
      MainWindowx->CommandWindow->MessageBox(Message, Title);
      }
   err_logo(STOP_ERROR, NIL);
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

   memset(&g_OsVersionInformation, 0, sizeof g_OsVersionInformation);
   g_OsVersionInformation.dwOSVersionInfoSize = sizeof g_OsVersionInformation;
   GetVersionEx(&g_OsVersionInformation);

   _control87( EM_OVERFLOW, EM_OVERFLOW );
   _control87( EM_UNDERFLOW, EM_UNDERFLOW );

   TopOfStack = &i;

   // parse the command-line parameters
   commandarg[0] = '\0';
   bPerspective = false;
   bExpert      = false;
   bFixed       = false;
   bWidth       = false;
   bHeight      = false;

   for (const char * ptr = lpCmdLine; *ptr != '\0'; ptr++)
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
                bPerspective = true;
                break;

             case 'e':
             case 'E':
                bExpert = true;
                break;

             case 'f':
             case 'F':
                bFixed = true;
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
                bHeight = true;
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
                bWidth = true;
                break;

             case 'l':
             case 'L':
                i = 0;

                // advance beyond the whitespace
                for (; (*ptr == ' '); ptr++)
                   {
                   }

                // copy the rest of the line into the commandarg buffer.
                for (; (*ptr != '\0'); ptr++)
                   {
                   // BUG: possible buffer overflow
                   commandarg[i++] = *ptr;
                   }
                break;

             default:
                MessageBox(GetFocus(), lpCmdLine, "Invalid Command Line", MB_OK);
                break;
            }
         }
      }

   // Check to see if another instance of Logo is currently running
   HANDLE singleInstanceMutex = CreateMutex(
      NULL,  // default security attributes
      FALSE, // no initial owner
      "LogoForWindowsMutex");
   if (GetLastError() == ERROR_ALREADY_EXISTS)
      {
      // A copy of Logo is already running.
      if (commandarg[0] == '\0')
         {
         // No logo scripts were specified on the command-line.
         // We should re-use the exiting window, since this was probably
         // just an accidently not create a new instance of logo.
         // Find that running copy of Logo and make it visible.
         HWND runningInstance = FindWindow(NULL, "FMSLogo");
         if (runningInstance != NULL)
            {
            // bring running instance to the the foreground
            ::SetForegroundWindow(runningInstance);
            if ( ::IsIconic(runningInstance) ||
                !::IsWindowVisible(runningInstance))
               {
               // the running instance is not visible, so restore it
               ::ShowWindow(runningInstance, SW_SHOWDEFAULT);
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
      else
         {
         // a Logo script was specified on the command-line.
         // This means that we should open up a new instance
         // of Logo, even if one is already running.
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
   HDC TempDC = GetDC(0);

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
   CutBmp = (CUTMAP *) calloc(sizeof(CUTMAP), MaxBitCuts);

   // init logo kernel
   init();

   // get an hourglass cursor
   hCursorWait = LoadCursor(NULL, IDC_WAIT);
   hCursorArrow = LoadCursor(NULL, IDC_ARROW);

   int exitCode;
      {
      // go for it
      TMyApp myApp("FMSLogo", hInstance, hPrevInstance, lpCmdLine, nCmdShow);
      myApp.Run();
      exitCode = myApp.Status;
      }

   if (hCursorWait)
      {
      DestroyCursor(hCursorWait);
      }

   if (hCursorArrow)
      {
      DestroyCursor(hCursorArrow);
      }

   // cleanup all subsystems
   uninit();

   /* Note Bitmap index 0 belongs to Clipboard */
   for (int i = 1; i < MaxBitCuts; i++)
      {
      if (CutBmp[i].CutFlag)
         {
         DeleteObject(CutBmp[i].CutMemoryBitMap);
         }
      }
   free(CutBmp);

   free(gcstack);

   free(hash_table);


   // release the HTML Help subsystem
   HtmlHelpUninitialize();

   CloseHandle(singleInstanceMutex);

   return exitCode;
   }

static
void 
transline3d(
   const LOGPEN &logPen, 
   long          modex, 
   const Point & from,
   const Point & to
)
   {
   VECTOR from3d;
   from3d.x = from.x / WorldWidth;
   from3d.y = from.y / WorldHeight;
   from3d.z = from.z / WorldDepth;

   VECTOR to3d;
   to3d.x = to.x / WorldWidth;
   to3d.y = to.y / WorldHeight;
   to3d.z = to.z / WorldDepth;

   if (bPolyFlag)
      {
      if (!ThePolygon ||
          (fabs(ThePolygon->Vertex.x - to3d.x) > FLONUM_EPSILON) ||
          (fabs(ThePolygon->Vertex.y - to3d.y) > FLONUM_EPSILON) ||
          (fabs(ThePolygon->Vertex.z - to3d.z) > FLONUM_EPSILON))
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

   // restore the pen and bitmap
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

static
void 
transline(
   const LOGPEN &logPen, 
   long          modex, 
   const Point & from,
   const Point & to
)
   {
   long iFromx =  g_round(from.x) + xoffset;
   long iFromy = -g_round(from.y) + yoffset;
   long iTox   =  g_round(to.x)   + xoffset;
   long iToy   = -g_round(to.y)   + yoffset;

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

void ibmturt(bool erase)
   {
   TRect screenBoundingBox;

   bool bMinMax = false;

   long minx = 100000;
   long miny = 100000;
   long maxx = -100000;
   long maxy = -100000;

   if (erase)
      {

      if (current_mode == perspectivemode)
         {
         // in 3D mode
         for (int j = 0; j < 4; j++)
            {
            VECTOR rp = MVxyMultiply(g_Turtles[turtle_which].Matrix, turtle_vertices[j].from);

            VECTOR from3d;
            from3d.x = (g_Turtles[turtle_which].Position.x + rp.x) / BitMapWidth;
            from3d.y = (g_Turtles[turtle_which].Position.y + rp.y) / BitMapWidth;
            from3d.z = (g_Turtles[turtle_which].Position.z + rp.z) / BitMapWidth;

            rp = MVxyMultiply(g_Turtles[turtle_which].Matrix, turtle_vertices[j].to);

            VECTOR to3d;
            to3d.x = (g_Turtles[turtle_which].Position.x + rp.x) / BitMapWidth;
            to3d.y = (g_Turtles[turtle_which].Position.y + rp.y) / BitMapWidth;
            to3d.z = (g_Turtles[turtle_which].Position.z + rp.z) / BitMapWidth;

            POINT from2d;
            POINT to2d;
            if (ThreeD.TransformSegment(from3d, to3d, from2d, to2d))
               {
               long iFromx =  from2d.x + xoffset;
               long iFromy = -from2d.y + yoffset;
               long iTox   =  to2d.x   + xoffset;
               long iToy   = -to2d.y   + yoffset;
               
               minx = min(minx, (long) from2d.x);
               miny = min(miny, (long) from2d.y);
               maxx = max(maxx, (long) from2d.x);
               maxy = max(maxy, (long) from2d.y);

               bMinMax = true;
               
               TurtlePoints[turtle_which][j].from.x = iFromx;
               TurtlePoints[turtle_which][j].from.y = iFromy;
               TurtlePoints[turtle_which][j].to.x   = iTox;
               TurtlePoints[turtle_which][j].to.y   = iToy;
               TurtlePoints[turtle_which][j].bValid = true;
               }
            else
               {
               TurtlePoints[turtle_which][j].bValid = false;
               }
            }
         }
      else
         {
         // 2D mode
         for (int j = 0; j < 3; j++)
            {
            FLONUM Cz = cos(-g_Turtles[turtle_which].Heading * rads_per_degree);
            FLONUM Sz = sin(-g_Turtles[turtle_which].Heading * rads_per_degree);

            FLONUM rx = Cz * turtle_vertices[j].from.x - Sz * turtle_vertices[j].from.y;
            FLONUM ry = Sz * turtle_vertices[j].from.x + Cz * turtle_vertices[j].from.y;

            FLONUM oldx = g_Turtles[turtle_which].Position.x + rx;
            FLONUM oldy = g_Turtles[turtle_which].Position.y + ry;
            
            rx = Cz * turtle_vertices[j].to.x - Sz * turtle_vertices[j].to.y;
            ry = Sz * turtle_vertices[j].to.x + Cz * turtle_vertices[j].to.y;
            
            FLONUM newx = g_Turtles[turtle_which].Position.x + rx;
            FLONUM newy = g_Turtles[turtle_which].Position.y + ry;
            
            long iOldx = g_round(oldx);
            long iOldy = g_round(oldy);
            long iNewx = g_round(newx);
            long iNewy = g_round(newy);
            
            long iFromx =  iOldx + xoffset;
            long iFromy = -iOldy + yoffset;
            long iTox   =  iNewx + xoffset;
            long iToy   = -iNewy + yoffset;
                        
            minx = min(minx, iOldx);
            miny = min(miny, iOldy);
            maxx = max(maxx, iOldx);
            maxy = max(maxy, iOldy);

            bMinMax = true;
            
            TurtlePoints[turtle_which][j].from.x = iFromx;
            TurtlePoints[turtle_which][j].from.y = iFromy;
            TurtlePoints[turtle_which][j].to.x   = iTox;
            TurtlePoints[turtle_which][j].to.y   = iToy;

            TurtlePoints[turtle_which][j].bValid = true;
            }

         // The line that distingiushes left from right is not needed
         // in 2D modes.
         TurtlePoints[turtle_which][3].bValid = false;
         }
      }
   else
      {
      // consider adding these to turtle points for efficiency
      for (int j = 0; j < 4; j++)
         {
         if (TurtlePoints[turtle_which][j].bValid)
            {
            minx = min(minx, (long) (+(TurtlePoints[turtle_which][j].from.x - xoffset)));
            miny = min(miny, (long) (-(TurtlePoints[turtle_which][j].from.y - yoffset)));
            maxx = max(maxx, (long) (+(TurtlePoints[turtle_which][j].from.x - xoffset)));
            maxy = max(maxy, (long) (-(TurtlePoints[turtle_which][j].from.y - yoffset)));
            bMinMax = true;
            }
         }
      }
   
   if (g_Turtles[turtle_which].Bitmap)
      {
      POINT dest;

      if (current_mode == perspectivemode)
         {
         VECTOR from3d;

         from3d.x = g_Turtles[turtle_which].Position.x / WorldWidth;
         from3d.y = g_Turtles[turtle_which].Position.y / WorldHeight;
         from3d.z = g_Turtles[turtle_which].Position.z / WorldDepth;

         if (ThreeD.TransformPoint(from3d, dest))
            {
            bMinMax = true;
            }
         else
            {
            bMinMax = false;
            }
         }
      else
         {
         dest.x = g_round(g_Turtles[turtle_which].Position.x);
         dest.y = g_round(g_Turtles[turtle_which].Position.y);
         }

      screenBoundingBox.Set(
         (+dest.x - MainWindowx->ScreenWindow->Scroller->XPos / the_zoom + xoffset                                      ) * the_zoom,
         (-dest.y - MainWindowx->ScreenWindow->Scroller->YPos / the_zoom + yoffset + LL - CutBmp[turtle_which].CutHeight) * the_zoom,
         (+dest.x - MainWindowx->ScreenWindow->Scroller->XPos / the_zoom + xoffset + CutBmp[turtle_which].CutWidth      ) * the_zoom,
         (-dest.y - MainWindowx->ScreenWindow->Scroller->YPos / the_zoom + yoffset + LL                                 ) * the_zoom);

      screenBoundingBox.Normalize();
      }
   else
      {
      screenBoundingBox.left   = (+minx - MainWindowx->ScreenWindow->Scroller->XPos / the_zoom + xoffset) * the_zoom;
      screenBoundingBox.top    = (-maxy - MainWindowx->ScreenWindow->Scroller->YPos / the_zoom + yoffset) * the_zoom;
      screenBoundingBox.right  = (+maxx - MainWindowx->ScreenWindow->Scroller->XPos / the_zoom + xoffset) * the_zoom;
      screenBoundingBox.bottom = (-miny - MainWindowx->ScreenWindow->Scroller->YPos / the_zoom + yoffset) * the_zoom;
      }


   screenBoundingBox.Inflate(1+the_zoom,1+the_zoom);
   
   if (bMinMax)
      {
      MainWindowx->ScreenWindow->InvalidateRect(screenBoundingBox, false);
      }
   }

void move_to(FLONUM x, FLONUM y)
   {
   g_OldPos.x = x;
   g_OldPos.y = y;
   }

void move_to_3d(FLONUM x, FLONUM y, FLONUM z)
   {
   g_OldPos.x = x;
   g_OldPos.y = y;
   g_OldPos.z = z;
   }

void line_to(FLONUM x, FLONUM y)
   {
   if (turtle_which >= (TURTLES - TURTLEN)) 
      {
      return;
      }

   if (!g_Turtles[turtle_which].IsPenUp)
      {
      vector_count++;
      if (status_flag) 
         {
         update_status_vectors();
         }

      Point toPoint;
      toPoint.x = x;
      toPoint.y = y;

      if (in_erase_mode)
         {
         transline(ErasePen, R2_COPYPEN, g_OldPos, toPoint);
         }
      else if (current_write_mode == XOR_PUT)
         {
         transline(NormalPen, R2_NOT, g_OldPos, toPoint);
         }
      else
         {
         transline(NormalPen, R2_COPYPEN, g_OldPos, toPoint);
         }
      }
   }

void line_to_3d(const Point & ToPoint)
   {
   if (turtle_which >= (TURTLES - TURTLEN)) 
      {
      return;
      }

   if (!g_Turtles[turtle_which].IsPenUp)
      {
      vector_count++;
      if (status_flag) 
         {
         update_status_vectors();
         }

      if (in_erase_mode)
         {
         transline3d(ErasePen, R2_COPYPEN, g_OldPos, ToPoint);
         }
      else if (current_write_mode == XOR_PUT)
         {
         transline3d(NormalPen, R2_NOT, g_OldPos, ToPoint);
         }
      else
         {
         transline3d(NormalPen, R2_COPYPEN, g_OldPos, ToPoint);
         }
      }
   }

void MakeHelpPathName(char *OutBuffer, const char * TheFileName)
   {
   int nFileNameLen = GetModuleFileName(ModulehInstance, OutBuffer, EXE_NAME_MAX_SIZE);
   char * pcFileName = OutBuffer + nFileNameLen;

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

