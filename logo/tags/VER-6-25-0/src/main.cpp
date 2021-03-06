/*
 *  Copyright (C) 1995 by the Regents of the University of California
 *  Copyright (C) 1995 by George Mills
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

#include "Scintilla.h"
#include "allwind.h"
#include "const.h"

bool bExpert;                      // Expert mode
bool bFixed;                       // Fixed mode
static bool bWidth;                // Width mode
static bool bHeight;               // Height mode
static bool bPerspective;          // Perspetive mode start up

HBITMAP MemoryBitMap;              // Backing store bitmap

HCURSOR hCursorWait;               /* handle for hourglass cursor    */
HCURSOR hCursorArrow;              /* handle for normal cursor       */

HPALETTE ThePalette;                   /* Handle for the single color palette */

LPLOGPALETTE MyLogPalette;      /* Handle for the single logical color palette*/

FLONUM the_zoom = 1.0;             // current zoom factor
Point  g_OldPos = {0.0, 0.0, 0.0}; // global store for x,y,z "From" routine

NODE *current_line = NIL;       // current line to be parsed

char LibPathName[MAX_PATH + 1];    // path to library
char TempPathName[MAX_PATH + 1];   // path to temp edit file
char TempBmpName[MAX_PATH + 1];    // path to temp bitmap file
char TempClipName[MAX_PATH + 1];   // path to temp clipboard file
char szHelpFileName[MAX_PATH + 1]; // path to help file

static char g_FileToLoad[MAX_BUFFER_SIZE];  // file to load on start

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

HINSTANCE ModulehInstance;             // FMSLogo instance handle

/* place holders for windows resources */
HPALETTE OldPalette;

LOGFONT FontRec;
LOGFONT EditFontRec;

LOGPEN g_LogicalNormalPen;             // Handle to "Normal" logical Pen
HPEN   g_NormalPen;                    // Handle to "Normal" Pen

LOGPEN g_LogicalErasePen;              // Handle to "Erase" logical Pen
HPEN   g_ErasePen;                     // Handle to "Erase" Pen

LOGBRUSH FloodBrush;                   // Handle to the "floodfill" brush
LOGBRUSH ScreenBrush;                  // Handle to the "screen" background brush

RECT FullRect;                         // Ready rectangle of Full bitmap

TMainFrame *MainWindowx;               // Pointer to the Main window

int GCMAX = 8192;                      // Garbage Collector Stack Size
Color dfld;                            // Current flood color
Color dscn;                            // Current screen color
bool IsDirty = false;                  // Flag to signal to query user ok to quit
int BitMapWidth = 1000;                // Current bitmap size in X
int BitMapHeight = 1000;               // Current bitmap size in Y
int WorldWidth = 1000;                 // Current World size in X
int WorldHeight = 1000;                // Current World size in Y
int WorldDepth = 1000;                 // Current World size in Z
bool EnablePalette;                    // Flag to signal 256 color mode with palette
bool IsOkayToUseCommanderWindow = false; // Flag to signal it's OK to write to recall box
bool traceflag = false;                // Flag to signal trace button is active
bool stepflag = false;                 // Flag to signal step button is active
bool yield_flag = true;                // Flag to signal yield state
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
COLORREF scolor;                       // screen color
COLORREF fcolor;                       // flood color
COLORREF pcolor;                       // pen color
bool zoom_flag = false;                // flag to signal in zoomed state
long MaxColors = 0;                    // The maximum # of colors available

PENSTATE g_PenState;  // The state of the current pen (color, mode, etc.)

TThreeDSolid ThreeD;

OSVERSIONINFO g_OsVersionInformation;

PENSTATE & GetPenStateForSelectedTurtle()
{
    if (g_SelectedTurtle->HasOwnPenState)
    {
        return g_SelectedTurtle->PenState;
    }

    // the current turtle uses the global pen state
    return g_PenState;
}

// returns the dimensions of the working area, that is
// the size of the desktop without the task bar.
void GetWorkingAreaDimensions(int & Width, int & Height)
{
    RECT workingArea;

    SystemParametersInfo(SPI_GETWORKAREA, 0, &workingArea, 0);
    Width  = workingArea.right  - workingArea.left;
    Height = workingArea.bottom - workingArea.top;
}


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

            // kill old palette
            DeleteObject(ThePalette);

            MyLogPalette->palPalEntry[MyLogPalette->palNumEntries].peRed = dpenr;
            MyLogPalette->palPalEntry[MyLogPalette->palNumEntries].peGreen = dpeng;
            MyLogPalette->palPalEntry[MyLogPalette->palNumEntries].peBlue = dpenb;
            MyLogPalette->palPalEntry[MyLogPalette->palNumEntries].peFlags = 0;
            MyLogPalette->palNumEntries++;

            // if status window then update palette usage
            update_status_paletteuse();

            // make new palette with added color
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


// Appends "str" to the end of the what is in the Commander's Recall box.
// If "str" doesn't fit, then some text will be removed from the top to make it fit.
void putcombobox(const char *str)
{
    // only if OK to write to recall box do we do it
    if (IsOkayToUseCommanderWindow)
    {
        TMyListboxWindow & commanderRecallBox = MainWindowx->CommandWindow->Listbox;

        for (int i=0;i<16;i++)
        {
            // remember where we started
            UINT uBefore = commanderRecallBox.GetTextLen();

            // output to list box 
            commanderRecallBox.SetSelection(uBefore, uBefore);
            commanderRecallBox.Insert(str);
            UINT uCheck = commanderRecallBox.GetTextLen();
            commanderRecallBox.Insert("\r\n");
            UINT uAfter = commanderRecallBox.GetTextLen();

            // if last 2 bytes inserted ok get out
            if (uCheck+2 == uAfter) 
            {
                return;
            }

            // strip what we inserted
            commanderRecallBox.SetReadOnly(FALSE);

            commanderRecallBox.SetSelection(uBefore, uAfter);
            commanderRecallBox.DeleteSelection();

            // strip 4k off top
            commanderRecallBox.SetSelection(0, 4096);
            commanderRecallBox.DeleteSelection();

            commanderRecallBox.SetReadOnly(TRUE);
        }

        // if all else fails try this, should never get here
        clearcombobox();
        commanderRecallBox.Insert(str);
        commanderRecallBox.Insert("\r\n");
    }
}


// Process a Logo instruction, as it is processed by the GUI when you click
// on the "Execute" button.  This can be used by other UI elements, such as
// the "Reset" button, to teach the user what a UI element is doing.
void
RunLogoInstructionFromGui(
    char * LogoInstruction
    )
{
    if (LogoInstruction[0] != '\0')
    {
        // The instruction is real.  Do something with it.

        // copy to list box for command recall
        putcombobox(LogoInstruction);

        // if dribble then dribble 
        if (dribblestream != NULL)
        {
            fprintf(dribblestream, "%s\n", LogoInstruction);
        }

        // reset erract loop error history
        clear_is_running_erract_flag();

        // reset evaluation counter (call counter) and execute
        eval_count = 0;
        update_status_evals();

        vector_count = 0;
        update_status_vectors();

        do_execution(LogoInstruction);
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
            LOCALIZED_STEPPING,
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

    // run the script that localizes FMSLogo
    static bool hasRunStartup = false;
    if (!hasRunStartup)
    {
        char startupScript[MAX_PATH + 1];
        MakeHelpPathName(startupScript, "startup.logoscript");
        silent_load(NIL, startupScript);

        hasRunStartup = true;
    }

    // if command arg loaded then execute
    if (g_FileToLoad[0] != '\0')
    {
        silent_load(NIL, g_FileToLoad);
        g_FileToLoad[0] = '\0';
    }

    checkqueue();

    return TApplication::IdleAction(idleCount);
}

// Creates a unique filename relative to TempPath
static
void MakeTempFilename(char *OutBuffer, const char * TempPath, const char * FileName)
{
    // the first part of the temp filename is TempPath
    char * ptr       = OutBuffer;
    const char * src = TempPath;
    while (*src != '\0')
    {
        *ptr++ = *src++;
    }

    // make sure that the path ends in a directory delimiter
    if (*ptr != '\\')
    {
        *ptr++ = '\\';
    }
   
    // append the filename
    strcpy(ptr, FileName);
}


void TMyApp::InitMainWindow()
{
    /* create the window */
    TPaneSplitter * paneSpliter = new TPaneSplitter(NULL);
    MainWindowx = new TMainFrame(NULL, Name, paneSpliter);
    SetMainWindow(MainWindowx);

    // set appropriate default colors
    pcolor = 0x00000000;
    scolor = 0x00FFFFFF;
    fcolor = 0x00000000;


    dfld.red   = 0x00;
    dfld.green = 0x00;
    dfld.blue  = 0x00;

    dscn.red   = 0xFF;
    dscn.green = 0xFF;
    dscn.blue  = 0xFF;

    // initialize the global pen state

    // init the font structure
    FontRec.lfHeight         = 24;
    FontRec.lfWidth          = 0;
    FontRec.lfOrientation    = 0;
    FontRec.lfWeight         = 400;
    FontRec.lfItalic         = 0;
    FontRec.lfUnderline      = 0;
    FontRec.lfStrikeOut      = 0;
    FontRec.lfCharSet        = ANSI_CHARSET;
    FontRec.lfOutPrecision   = OUT_DEFAULT_PRECIS;
    FontRec.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
    FontRec.lfQuality        = DEFAULT_QUALITY;
    FontRec.lfPitchAndFamily = DEFAULT_PITCH;
    strcpy(FontRec.lfFaceName, "Arial");

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

    // The main window should not exceed the size of the working area
    int maxWidth;
    int maxHeight;
    GetWorkingAreaDimensions(maxWidth, maxHeight);
   
    // if fixed mode
    if (bFixed)
    {
        if (bHeight)
        {
            // if height specified santize it against screen height
            h = min(h, maxHeight);
        }
        else
        {
            // else choose something reasonable
            h = (int) (maxHeight * ScreenSz);
        }

        if (bWidth)
        {
            // if width specified santize it against screen width
            w = min(w, maxWidth);
        }
        else
        {
            // else choose something reasonable
            w = maxWidth;
        }

        // fit the bitmap to the size of the window
        BitMapWidth  = w;
        BitMapHeight = h;
    }
    else
    {
        // sanatize window size we would like against screen size
        w = min(w, maxWidth);
        h = min(h, (int) (maxHeight * ScreenSz));

        GetConfigurationQuadruple("Screen", &x, &y, &w, &h);

        // the smallest reasonable size is 200 x 200.
        h = max(h, 200);
        w = max(w, 200);

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
    g_PrinterAreaXLow  = -BitMapWidth  / 2;
    g_PrinterAreaXHigh = +BitMapWidth  / 2;
    g_PrinterAreaYLow  = -BitMapHeight / 2;
    g_PrinterAreaYHigh = +BitMapHeight / 2;

    g_PrinterAreaPixels = max(BitMapWidth, BitMapHeight) / 8;

    ModulehInstance = HInstance;

    // init paths to library and help files based on location of .EXE
    MakeHelpPathName(LibPathName,     "logolib\\");
    MakeHelpPathName(szHelpFileName,  "logohelp.chm");

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
        // warn the user that no TMP variable was defined.
        MessageBox(
            0,
            LOCALIZED_ERROR_TMPNOTDEFINED,
            LOCALIZED_WARNING,
            MB_OK);

        strcpy(tempPath, "C:");
    }

    // construct the name of the temporary editor file
    MakeTempFilename(TempPathName, tempPath, "mswlogo.tmp");

    // construct the name of the temporary bitmap file
    MakeTempFilename(TempBmpName, tempPath, "mswlogo.bmp");

    // construct the name of the clipboard file
    MakeTempFilename(TempClipName, tempPath, "mswlogo.clp");

    g_PrinterAreaXLow   = GetConfigurationInt("Printer.Xlow",  -BitMapWidth  / 2);
    g_PrinterAreaXHigh  = GetConfigurationInt("Printer.XHigh", +BitMapWidth  / 2);
    g_PrinterAreaYLow   = GetConfigurationInt("Printer.Ylow",  -BitMapHeight / 2);
    g_PrinterAreaYHigh  = GetConfigurationInt("Printer.YHigh", +BitMapHeight / 2);
    g_PrinterAreaPixels = GetConfigurationInt("Printer.Pixels", max(BitMapWidth, BitMapHeight) / 8);
}

TMyApp::~TMyApp()
{
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


void 
ShowMessage(
    const char * Title,
    const char * Message
    )
{
    if (MainWindowx->CommandWindow != NULL)
    {
        MainWindowx->CommandWindow->MessageBox(Message, Title);
    }
}

void
ShowErrorMessage(
    const char * Message
    )
{
    ShowMessage(LOCALIZED_ERROR, Message);
}

// Maps ErrorCode to a string and displays it in a message box
void
ShowErrorMessage(
    ERR_TYPES  ErrorCode
    )
{
    const char * errorMessage = NULL;

    switch (ErrorCode)
    {
    case IMAGE_GIF_LOAD_FAILED:
        errorMessage = LOCALIZED_ERROR_GIFREADFAILED;
        break;

    case IMAGE_GIF_SAVE_FAILED:
        errorMessage = LOCALIZED_ERROR_GIFSAVEFAILED;
        break;

    case IMAGE_BMP_OPEN_FAILED:
        errorMessage = LOCALIZED_COULDNOTOPENBMP;
        break;

    case IMAGE_BMP_CREATE_FAILED:
        errorMessage = LOCALIZED_COULDNOTCREATEBMP;
        break;

    case IMAGE_BMP_WRITE_FAILED:
        errorMessage = LOCALIZED_COULDNOTWRITEBMP;
        break;

    case IMAGE_BMP_INVALID:
        errorMessage = LOCALIZED_NOTVALIDBMP;
        break;
    }

    if (errorMessage != NULL)
    {
        ShowErrorMessage(errorMessage);
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
    ShowMessage(Title, Message);
    err_logo(STOP_ERROR, NIL);
}

void
ShowErrorMessageAndStop(
    const char * Message
    )
{
    ShowMessageAndStop(LOCALIZED_ERROR, Message);
}


// Print page (or pages)
void TRulerOut::PrintPage(int /* page */, TRect & /* rect */, UINT /* flags */)
{
    MainWindowx->ScreenWindow->Printit(*DC);
}


const DWORD PROCESS_DEP_DISABLE                     = 0x00000000;
const DWORD PROCESS_DEP_ENABLE                      = 0x00000001;
const DWORD PROCESS_DEP_DISABLE_ATL_THUNK_EMULATION = 0x00000002;

// Best-effort to disable Data Execution Protection.
//
// In general, programs shouldn't disable DEP because that would leave
// their users prone to some buffer-overflow attacks.  However, OWL
// uses some self-modifying code its window message handling.  When
// Windows sees this happening, it assumes the worst--that some buffer
// overrun has been exploited--and terminates the program.
//
// For backward-compatibility reasons, Microsoft published an API that
// allows 32-bit applications to disable DEP on a per-instance basis.
// This is not available in all operating systems, so it is called
// through GetProcAddress() on a best-effort basis.  In the worst case,
// DEP will be enabled on FMSLogo, FMSLogo won't be able to disable
// it, and it will crash (that is, we're no worse off than before).
void DisableDataExecutionProtection()
{
    typedef BOOL (WINAPI *SETPROCESSDEPPOLICY) (DWORD);

    HMODULE kernel32 = GetModuleHandleW(L"kernel32.dll");
    if (kernel32 == NULL)
    {
        // somehow this process didn't link to kernel32.dll
        return;
    }

    SETPROCESSDEPPOLICY setProcessDepPolicy = (SETPROCESSDEPPOLICY)GetProcAddress(
        kernel32,
        "SetProcessDEPPolicy");
    if (setProcessDepPolicy == NULL)
    {
        // SetProcessDEPPolicy was added in XP SP3 and Vista SP1.
        // Any OS before then either doesn't support DEP or doesn't
        // provide an API to disable it.
        return;
    }

    // Disable the DEP policy on a best-effort basis.
    setProcessDepPolicy(PROCESS_DEP_DISABLE);
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

#ifdef MEM_DEBUG
    // define values that didn't exist when Borland C++ was written
    const DWORD GR_GDIOBJECTS  = 0;
    const DWORD GR_USEROBJECTS = 1;
    typedef DWORD WINAPI (*GETGUIRESOURCES)(HANDLE, DWORD);

    GETGUIRESOURCES getGuiResources     = NULL;
    DWORD           originalGuiObjects  = 0;
    DWORD           originalUserObjects = 0;

    HANDLE fmslogo = NULL;

    HMODULE user32 = GetModuleHandle("user32.dll");
    if (user32 != NULL)
    {
        getGuiResources = (GETGUIRESOURCES) GetProcAddress(user32, "GetGuiResources");
        if (getGuiResources != NULL)
        {
            fmslogo = OpenProcess(
                PROCESS_QUERY_INFORMATION, 
                FALSE, 
                GetCurrentProcessId());
            if (fmslogo != NULL)
            {
                originalGuiObjects  = getGuiResources(fmslogo, GR_GDIOBJECTS);
                originalUserObjects = getGuiResources(fmslogo, GR_USEROBJECTS);
            }
        }
    }

#endif // MEM_DEBUG


    memset(&g_OsVersionInformation, 0, sizeof g_OsVersionInformation);
    g_OsVersionInformation.dwOSVersionInfoSize = sizeof g_OsVersionInformation;
    GetVersionEx(&g_OsVersionInformation);

    DisableDataExecutionProtection();

    _control87(EM_OVERFLOW,  EM_OVERFLOW);
    _control87(EM_UNDERFLOW, EM_UNDERFLOW);

    TopOfStack = &i;

    // parse the command-line parameters
    g_FileToLoad[0] = '\0';
    bPerspective = false;
    bExpert      = false;
    bFixed       = false;
    bWidth       = false;
    bHeight      = false;

    for (char * ptr = lpCmdLine; *ptr != '\0'; ptr++)
    {
        if (*ptr == '-')
        {
            ptr++; // advance beyond the -

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
                BitMapHeight = strtoul(ptr, &ptr, 10);
                bHeight = true;
                break;

            case 'w':
            case 'W':
                BitMapWidth = strtoul(ptr, &ptr, 10);
                bWidth = true;
                break;

            case 'l':
            case 'L':
                // advance beyond the whitespace
                while (*ptr == ' ')
                {
                    ptr++;
                }

                // copy the rest of the line into the g_FileToLoad buffer
                strncpy(g_FileToLoad, ptr, ARRAYSIZE(g_FileToLoad) - 1);
                ptr += strlen(ptr) - 1;
                break;

            default:
                // invalid command line: unrecognized switch
                MessageBox(
                    GetFocus(), 
                    lpCmdLine, 
                    LOCALIZED_ERROR_BADCOMMANDLINE, 
                    MB_OK);
                break;
            }
        }
        else if (!IsSpace(*ptr))
        {
            // No switch was used, so this is the name of a file to load.
            // Copy the rest of the command-line into the g_FileToLoad buffer

            // remove the surrounding quotes, if necessary
            bool removeQuotes = false;

            if (*ptr == '"')
            {
                removeQuotes = true;
                ptr++;
            }
            for (size_t i = 0; i < ARRAYSIZE(g_FileToLoad) - 1; i++)
            {
                if (*ptr == '\0')
                {
                    break;
                }

                if (removeQuotes && *ptr == '"')
                {
                    // Determine if this is the end quote.
                    // That is, determine if there's nothing but
                    // whitespace until the end of the command-line.
                    const char * cursor;
                    for (cursor = ptr + 1; *cursor != '\0'; cursor++)
                    {
                        if (!IsSpace(*cursor))
                        {
                            break;
                        }
                    }

                    if (*cursor == '\0')
                    {
                        // ignore the end quote
                        break;
                    }
                }

                g_FileToLoad[i] = *ptr++;
            }

            // g_FileToLoad is already NUL-terminated because it's a
            // static buffer and was initialized to all zeros by the compiler.

            // we've processed the entire command-line
            break;
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
        if (g_FileToLoad[0] == '\0')
        {
            // No logo scripts were specified on the command-line.
            // We should re-use the existing window instead of creating a new 
            // instance of logo, since this was probably just an accident.

            // Find that running copy of Logo and make it visible.
            HWND runningInstance = FindWindow(NULL, LOCALIZED_GENERAL_PRODUCTNAME);
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


    // Get garbage collector stack size from the configuration settings
    GCMAX = GetConfigurationInt("GCStackSize", 8192);

    // Get video mode parameters
    HDC TempDC = GetDC(0);

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
    init_bitmaps();

    // alloc and init the turtles array
    g_TurtlesLimit = 1;
    g_MaxTurtle    = 0;
    g_Turtles      = (Turtle *) calloc(sizeof(*g_Turtles), g_TurtlesLimit);
    g_SelectedTurtle = &g_Turtles[g_MaxTurtle];

    InitializeTurtle(g_SelectedTurtle);

    // init the special turtles
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_LOCATION].IsSpecial   = true;
    g_SpecialTurtles[SPECIAL_TURTLE_LIGHT_LOCATION].IsSpecial = true;
    g_SpecialTurtles[SPECIAL_TURTLE_EYE_FIXATION].IsSpecial   = true;

    // init global pen state
    g_PenState.Color.red   = 0x00;
    g_PenState.Color.green = 0x00;
    g_PenState.Color.blue  = 0x00;
    g_PenState.Width     = 1;
    g_PenState.Mode      = COPY_PUT;
    g_PenState.IsErasing = false;


    // init logo kernel
    init();

    // get an hourglass cursor
    hCursorWait = LoadCursor(NULL, IDC_WAIT);
    hCursorArrow = LoadCursor(NULL, IDC_ARROW);

    if (!Scintilla_RegisterClasses(hInstance))
    {
        return 1;
    }

    int exitCode;
    {
        // go for it
        TMyApp myApp(
            LOCALIZED_GENERAL_PRODUCTNAME,
            hInstance, 
            hPrevInstance, 
            lpCmdLine, 
            nCmdShow);
        myApp.Run();
        exitCode = myApp.Status;
    }

    Scintilla_ReleaseResources();

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

    uninit_bitmaps();

    free(g_Turtles);

    free(gcstack);

    free(hash_table);


    // release the HTML Help subsystem
    HtmlHelpUninitialize();

    CloseHandle(singleInstanceMutex);

#ifdef MEM_DEBUG

    if (fmslogo != NULL)
    {
        // Check if any GUI objects were leaked
        DWORD currentGuiObjects = getGuiResources(fmslogo, GR_GDIOBJECTS);
        if (originalGuiObjects < currentGuiObjects)
        {
            fprintf(
                stderr, 
                "%d GUI objects were leaked.\n",
                currentGuiObjects - originalUserObjects);
        }

        // Check if any USER objects were leaked
        DWORD currentUserObjects = getGuiResources(fmslogo, GR_USEROBJECTS);
        if (originalUserObjects < currentUserObjects)
        {
            fprintf(
                stderr, 
                "%d USER objects were leaked.\n",
                currentUserObjects - originalUserObjects);
        }

        CloseHandle(fmslogo);
    }

#endif // MEM_DEBUG

    return exitCode;
}

static
void
transline_helper(
    const LOGPEN & LogicalPen,
    HPEN           Pen,
    int            LineMode,
    int            FromX,
    int            FromY,
    int            ToX,
    int            ToY
    )
{
    // Convert from Cartesian coordinates to logical window coordinates.
    FromX =  FromX + xoffset;
    FromY = -FromY + yoffset;
    ToX   =  ToX   + xoffset;
    ToY   = -ToY   + yoffset;

    HDC MemDC = MainWindowx->ScreenWindow->GetMemoryDeviceContext();

    if (EnablePalette)
    {
        OldPalette = SelectPalette(MemDC, ThePalette, FALSE);
        RealizePalette(MemDC);
    }

    SetROP2(MemDC, LineMode);

    HPEN oldPen = (HPEN) SelectObject(MemDC, Pen);

    MoveToEx(MemDC, FromX, FromY, 0);
    LineTo(MemDC, ToX, ToY);

    // HACK:
    // LineTo() API does not draw a pixel in the location where it moves to.
    // As a result, moving forward changing colors, then moving backward leaves
    // a dot of the previous color at the location where the direction changed.
    // To address this, we SetPixel to color the end point.
    //
    // This isn't necessary when the pensize != 1.
    // This would be bad to do in penreverse mode.
    //
    PENSTATE & penState = GetPenStateForSelectedTurtle();
    if (penState.Width < 2 && penState.Mode != XOR_PUT)
    {
        SetPixel(MemDC, ToX, ToY, LogicalPen.lopnColor);
    }

    if (EnablePalette)
    {
        SelectPalette(MemDC, OldPalette, FALSE);
    }

    // restore the previous bitmap and pen
    SelectObject(MemDC, oldPen);


    // update the screen
    if (zoom_flag)
    {
        // We are zoomed, so it would be very difficult to just
        // draw the line on the screen.  Instead, invalidate the
        // portion of the screen window that corresponds
        // to the region containing the line which we just drew.
        TRect screenRect;
        if (FromX < ToX)
        {
            screenRect.left   = FromX - penState.Width;
            screenRect.right  = ToX   + penState.Width;
        }
        else
        {
            screenRect.left   = ToX    - penState.Width;
            screenRect.right  = FromX  + penState.Width;
        }

        if (FromY < ToY)
        {
            screenRect.top    = FromY - penState.Width;
            screenRect.bottom = ToY   + penState.Width;
        }
        else
        {
            screenRect.top    = ToY   - penState.Width;
            screenRect.bottom = FromY + penState.Width;
        }

        // remap the screen rectangle based on the zoom factor
        screenRect.left   *= the_zoom;
        screenRect.right  *= the_zoom;
        screenRect.top    *= the_zoom;
        screenRect.bottom *= the_zoom;

        const UINT scrollerX = MainWindowx->ScreenWindow->Scroller->XPos;
        const UINT scrollerY = MainWindowx->ScreenWindow->Scroller->YPos;

        screenRect.left   -= scrollerX;
        screenRect.right  -= scrollerX;
        screenRect.top    -= scrollerY;
        screenRect.bottom -= scrollerY;

        MainWindowx->ScreenWindow->InvalidateRect(screenRect, false);
    }
    else
    {
        // We are not zoomed.
        // Draw the line directly on the screen, rather than invalidating
        // the region containing the line because doing is 400% faster
        // on the squiral benchmark.
        HDC ScreenDC = MainWindowx->ScreenWindow->GetScreenDeviceContext();
        SetROP2(ScreenDC, LineMode);

        if (EnablePalette)
        {
            OldPalette = SelectPalette(ScreenDC, ThePalette, FALSE);
            RealizePalette(ScreenDC);
        }

        oldPen = (HPEN) SelectObject(ScreenDC, Pen);

        TScroller * scroller = MainWindowx->ScreenWindow->Scroller;

        UINT screenFromX = FromX - scroller->XPos;
        UINT screenFromY = FromY - scroller->YPos;

        UINT screenToX   = ToX   - scroller->XPos;
        UINT screenToY   = ToY   - scroller->YPos;

        MoveToEx(ScreenDC, screenFromX, screenFromY, 0);
        LineTo(ScreenDC, screenToX, screenToY);

        PENSTATE & penState = GetPenStateForSelectedTurtle();
        if (penState.Width < 2 && penState.Mode != XOR_PUT)
        {
            SetPixel(ScreenDC, screenFromX, screenFromY, LogicalPen.lopnColor);
        }

        if (EnablePalette)
        {
            SelectPalette(ScreenDC, OldPalette, FALSE);
        }

        // restore the previous pen
        SelectObject(ScreenDC, oldPen);
    }
}


static
void 
transline3d(
    const LOGPEN &logPen, 
    HPEN         &pen, 
    long          modex, 
    const Point & from,
    const Point & to
    )
{
    // First, project the point from world coordinates to
    // window coordinates.
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

    // Now that we have projected this line into the
    // window coordinates, we can call the 2D version to
    // actually draw the line.
    transline_helper(
        logPen,
        pen,
        modex,
        from2d.x,
        from2d.y,
        to2d.x,
        to2d.y);
}

static
void 
transline(
    const LOGPEN &logPen, 
    HPEN         &pen, 
    long          modex, 
    const Point & from,
    const Point & to
    )
{
    transline_helper(
        logPen,
        pen,
        modex,
        g_round(from.x),
        g_round(from.y),
        g_round(to.x),
        g_round(to.y));
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
    if (g_SelectedTurtle->IsSpecial)
    {
        // special turtles don't draw lines when they move
        return;
    }

    if (!g_SelectedTurtle->IsPenUp)
    {
        vector_count++;
        update_status_vectors();

        Point toPoint;
        toPoint.x = x;
        toPoint.y = y;

        HPEN           pen;
        const LOGPEN * logicalPen;
        int            rasterMode;

        if (GetPenStateForSelectedTurtle().IsErasing)
        {
            pen        = g_ErasePen;
            logicalPen = &g_LogicalErasePen;
            rasterMode = R2_COPYPEN;
        }
        else
        {
            pen        = g_NormalPen;
            logicalPen = &g_LogicalNormalPen;

            if (GetPenStateForSelectedTurtle().Mode == XOR_PUT)
            {
                rasterMode = R2_NOT;
            }
            else
            {
                rasterMode = R2_COPYPEN;
            }
        }

        transline(
            *logicalPen,
            pen,
            rasterMode,
            g_OldPos,
            toPoint);
    }
}

void line_to_3d(const Point & ToPoint)
{
    if (g_SelectedTurtle->IsSpecial)
    {
        // special turtles don't draw lines when they move
        return;
    }

    if (!g_SelectedTurtle->IsPenUp)
    {
        vector_count++;
        update_status_vectors();

        HPEN           pen;
        const LOGPEN * logicalPen;
        int            rasterMode;

        if (GetPenStateForSelectedTurtle().IsErasing)
        {
            pen        = g_ErasePen;
            logicalPen = &g_LogicalErasePen;
            rasterMode = R2_COPYPEN;
        }
        else
        {
            pen        = g_NormalPen;
            logicalPen = &g_LogicalNormalPen;

            if (GetPenStateForSelectedTurtle().Mode == XOR_PUT)
            {
                rasterMode = R2_NOT;
            }
            else
            {
                rasterMode = R2_COPYPEN;
            }
        }

        transline3d(
            *logicalPen,
            pen,
            rasterMode,
            g_OldPos,
            ToPoint);
    }
}

// Creates path relative to the directory from to which FMSLogo is installed.
void MakeHelpPathName(char *OutBuffer, const char * TheFileName)
{
    // get the path name of fmslogo.exe
    int nFileNameLen = GetModuleFileName(ModulehInstance, OutBuffer, MAX_PATH);

    // start at the end of the full path to fmslogo.exe and walk
    // backwards in the string until we find the final directory delimiter
    char * pcFileName = OutBuffer + nFileNameLen;
    while (pcFileName > OutBuffer)
    {
        if (*pcFileName == '\\' || *pcFileName == ':')
        {
            pcFileName++;
            break;
        }
        pcFileName--;
    }

    // Append the filename to the relative path
    strcpy(pcFileName, TheFileName);
}


void ContextHelp(TEdit *Editor)
{
    bool didHelp = false;

    // get the keyword selected
    UINT start;
    UINT end;
    Editor->GetSelection(start, end);
    if (start < end && end < start + 80)
    {
        char buffer[100] = {0}; // NUL-terminate

        Editor->GetSubText(buffer, start, end);
      
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

DEFINE_RESPONSE_TABLE1(TMyApp, TApplication)
    EV_WM_SYSCOLORCHANGE,
END_RESPONSE_TABLE;
