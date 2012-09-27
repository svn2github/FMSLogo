#include <windows.h>
#include <time.h>
#include <string>
#include <scrnsave.h>
#include <stdlib.h>

#include "init.h"
#include "graphwin.h"
#include "startup.h"
#include "main.h"
#include "mem.h"
#include "mmwind.h"
#include "wrksp.h"
#include "utils.h"
#include "files.h"
#include "localizedstrings.h"
#include "logoeventqueue.h"
#include "mainwind.h"
#include "devwind.h"
#include "eval.h"
#include "logorc.h"
#include "netwind.h"
#include "screenwindow.h"

#include "resource.h"

#ifdef __GNUC__
#define USER_TIMER_MINIMUM (0x0000000A)
#define GR_GDIOBJECTS      0
#define GR_USEROBJECTS     1
#endif

int *TopOfStack  = NULL;
int BitMapWidth  = 0;
int BitMapHeight = 0;

static UINT   g_Timer;
static CHAR   g_FileToLoad[MAX_PATH] = "";
static HANDLE g_SingleInstanceMutex  = NULL;

static bool g_IsLoadingFile          = false;

#ifdef MEM_DEBUG
typedef DWORD (WINAPI *GETGUIRESOURCES)(HANDLE, DWORD);

static GETGUIRESOURCES g_GetGuiResources     = NULL;
static DWORD           g_OriginalGuiObjects  = 0;
static DWORD           g_OriginalUserObjects = 0;
static HANDLE          g_Fmslogo             = NULL;
static HMODULE         g_User32              = NULL;
#endif

static HWND g_ScreenWindow = NULL;
static HDC  g_ScreenDeviceContext = NULL;
static HDC  g_MemoryDeviceContext = NULL;

static DWORD g_TickCountOfMostRecentLoad = 0;

static int   g_NextTextLine = 0;


const DWORD DELAYTIME_MILLISECONDS = 10000;


static
void
UninitializeLogoEngine()
{
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

    uninit_turtles();

    // release the HTML Help subsystem
    HtmlHelpUninitialize();

    CloseHandle(g_SingleInstanceMutex);
    g_SingleInstanceMutex = NULL;

#ifdef MEM_DEBUG
    if (g_Fmslogo != NULL)
    {
        // Check if any GUI objects were leaked
        DWORD currentGuiObjects = g_GetGuiResources(g_Fmslogo, GR_GDIOBJECTS);
        if (g_OriginalGuiObjects < currentGuiObjects)
        {
            TraceOutput(
                "%d GUI objects were leaked.\n",
                currentGuiObjects - g_OriginalUserObjects);
        }

        // Check if any USER objects were leaked
        DWORD currentUserObjects = g_GetGuiResources(g_Fmslogo, GR_USEROBJECTS);
        if (g_OriginalUserObjects < currentUserObjects)
        {
            TraceOutput(
                "%d USER objects were leaked.\n",
                currentUserObjects - g_OriginalUserObjects);
        }

        CloseHandle(g_Fmslogo);
    }
#endif // MEM_DEBUG
}

LRESULT WINAPI ScreenSaverProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT     rval = 0;
    callthing * callevent;

    // used for WM_PAINT
    BOOL updateRectangleExists;
    RECT updateRectangle;

    switch(message)
    {
    case WM_CREATE:

        g_ScreenWindow = hwnd;
        GetClientRect(g_ScreenWindow, &FullRect);

        // Size-to-fit
        BitMapHeight = FullRect.bottom;
        BitMapWidth  = FullRect.right;

        // Fill the screen with blackness.
        g_ScreenDeviceContext = GetDC(g_ScreenWindow);
        g_MemoryDeviceContext = CreateCompatibleDC(g_ScreenDeviceContext);

        // create the in-memory image of the bitmap
        MemoryBitMap = CreateCompatibleBitmap(
            g_ScreenDeviceContext,
            BitMapWidth,
            BitMapHeight);

        // set the bitmap object of the screen
        SelectObject(g_MemoryDeviceContext, MemoryBitMap);

#ifdef MEM_DEBUG
        g_Fmslogo = NULL;
        g_User32  = GetModuleHandle("user32.dll");
        if (g_User32 != NULL)
        {
            g_GetGuiResources = (GETGUIRESOURCES) GetProcAddress(g_User32, "GetGuiResources");
            if (g_GetGuiResources != NULL)
            {
                g_Fmslogo = OpenProcess(
                    PROCESS_QUERY_INFORMATION, 
                    FALSE, 
                    GetCurrentProcessId());
                if (g_Fmslogo != NULL)
                {
                    g_OriginalGuiObjects  = g_GetGuiResources(g_Fmslogo, GR_GDIOBJECTS);
                    g_OriginalUserObjects = g_GetGuiResources(g_Fmslogo, GR_USEROBJECTS);
                }
            }
        }
#endif // MEM_DEBUG

        init_osversion();

        DisableDataExecutionProtection();

        // Figure out the path that contains fmslogo.exe
        HKEY fmslogoKey;
        LONG result;
        result = RegOpenKeyEx(
            HKEY_LOCAL_MACHINE,
            "Software\\FMSLogo",
            0, // reserved
            KEY_QUERY_VALUE,
            &fmslogoKey);
        if (result == ERROR_SUCCESS)
        {
            DWORD valueSize = ARRAYSIZE(g_FmslogoBaseDirectory) - 2;  // leave room for the backslash and NUL
            BYTE *valuePtr  = reinterpret_cast<BYTE*>(g_FmslogoBaseDirectory);
            DWORD valueType;

            LONG result = RegQueryValueEx(
                fmslogoKey,
                "Install_Dir",
                0,   // reserved
                &valueType,
                valuePtr,
                &valueSize);
            if (result == ERROR_SUCCESS && 
                valueType == REG_SZ     &&
                valueSize < ARRAYSIZE(g_FmslogoBaseDirectory) - 2)
            {
                // we successfully read the value as a string.
                // Append the missing backslash
                if (valueSize != 0 && g_FmslogoBaseDirectory[valueSize] == '\0')
                {
                    valueSize--;
                }
                g_FmslogoBaseDirectory[valueSize + 0] = '\\';
                g_FmslogoBaseDirectory[valueSize + 1] = '\0';
            }

            RegCloseKey(fmslogoKey);
        }

        //_control87(EM_OVERFLOW,  EM_OVERFLOW);
        //_control87(EM_UNDERFLOW, EM_UNDERFLOW);
        TopOfStack = (int*) &rval;

        // Grab the single instance lock.
        // We don't want to fail if Logo is running, since we are a screen saver.
        // But we do want to prevent Logo from being uninstalled.
        g_SingleInstanceMutex = CreateMutex(
            NULL,  // default security attributes
            FALSE, // no initial owner
            "LogoForWindowsMutex");

        // Get video mode parameters
        init_videomode();

        srand(time(NULL));

        // init the timer callback array
        init_timers();

        // alloc and init the bitmap cut array
        init_bitmaps();

        // alloc and init the turtles array
        init_turtles();

        // init global pen state
        init_penstate();

        // init logo kernel
        init();

        // initialize the hourglass and arrow cursors
        init_cursors();

        // initialize the values for some of the graphics-related
        // global variables.
        init_graphics();

        // run the startup script that localizes logo
        char startupScript[MAX_PATH + 1];
        MakeHelpPathName(startupScript, "startup.logoscript");
        silent_load(NIL, startupScript);

        // force the next WM_TIMER update to run the program
        g_TickCountOfMostRecentLoad = 0;

        // Start the timer.
        // Use the minimum timer tick time so that we can run
        // the next instruction as soon as the previous one completes.
        g_Timer = SetTimer(hwnd, 33, USER_TIMER_MINIMUM, NULL);
        break;

    case WM_PAINT:

        updateRectangleExists = GetUpdateRect(hwnd, &updateRectangle, FALSE);
        if (updateRectangleExists)
        {
            // There is a dirty rectangle that needs to be redrawn.
            PAINTSTRUCT repaintInfo = {0};
            HDC         deviceContext;

            repaintInfo.rcPaint = updateRectangle;

            deviceContext = BeginPaint(hwnd, &repaintInfo);
            if (deviceContext)
            {
                PaintToScreenWindow(
                    deviceContext,
                    FullRect);

                EndPaint(hwnd, &repaintInfo);
            }
        }

        break;

    case WM_ERASEBKGND:
        // Fill the screen with whiteness.
        FillRect(
            g_ScreenDeviceContext,
            &FullRect,
            (HBRUSH) GetStockObject(WHITE_BRUSH));

        // mark the background as being erased
        rval = 1;
        break;

    case WM_KEYUP:
        if (keyboard_keyup != NULL)
        {
            callevent = callthing::CreateKeyboardEvent(keyboard_keyup, wParam);

            calllists.insert(callevent);
            checkqueue();
        }
        else
        {
            rval = DefScreenSaverProc(hwnd, message, wParam, lParam);
        }
        break;

    case WM_KEYDOWN:
        if (keyboard_keydown != NULL)
        {
            callevent = callthing::CreateKeyboardEvent(keyboard_keydown, wParam);

            calllists.insert(callevent);
            checkqueue();
        }
        else
        {
            rval = DefScreenSaverProc(hwnd, message, wParam, lParam);
        }
        break;

    case WM_TIMER:

        if (wParam < 16)
        {
            // not safe to yield
            callthing * callevent = callthing::CreateNoYieldFunctionEvent(timer_callback[wParam]);
            calllists.insert(callevent);
            PostMessage(hwnd, WM_CHECKQUEUE, 0, 0);
        }
        else if (wParam < 32)
        {
            // yieldable
            callevent = callthing::CreateFunctionEvent(timer_callback[wParam]);
            calllists.insert(callevent);
            PostMessage(hwnd, WM_CHECKQUEUE, 0, 0);
        }
        else if (wParam == 33)
        {
            // This is the screen saver's event
            if (!g_IsLoadingFile)
            {
                // Run the file to load it it's been more than DELAYTIME
                // milliseconds since the last time we ran it.
                if (g_TickCountOfMostRecentLoad + DELAYTIME_MILLISECONDS <= GetTickCount())
                {
                    // reset the screen and text area
                    lclearscreen(NULL);
                    g_NextTextLine = 0;

                    // Always re-read the file to load from the registry, in case it changed.
                    GetConfigurationString(
                        "ScreenSaverFile",
                        g_FileToLoad,
                        ARRAYSIZE(g_FileToLoad),
                        "");
                    if (g_FileToLoad[0] != '\0')
                    {
                        g_IsLoadingFile = true;
                        silent_load(NIL, g_FileToLoad);
                        g_TickCountOfMostRecentLoad = GetTickCount();
                        g_IsLoadingFile = false;
                        if (IsTimeToExit)
                        {
                            // The window has already been destroyed,
                            // so we should quit Logo.
                            UninitializeLogoEngine();
                        }
                    }
                }
            }
        }
        else
        {
            // this is an unknown event
        }
        break;

    case WM_CHECKQUEUE:
        checkqueue();
        break;

    case MM_MCINOTIFY:
        // if user fired up a callback mci event then queue it up here
        callevent = callthing::CreateNoYieldFunctionEvent(mci_callback);
        calllists.insert(callevent);
        PostMessage(hwnd, WM_CHECKQUEUE, 0, 0);
        break;

    case WM_NETWORK_CONNECTSENDACK:
        g_ClientConnection.OnConnectSendAck(hwnd, lParam);
        break;

    case WM_NETWORK_CONNECTSENDFINISH:
        g_ClientConnection.OnConnectSendFinish(hwnd, lParam);
        break;

    case WM_NETWORK_LISTENRECEIVEACK:
        g_ServerConnection.OnListenReceiveAck(hwnd, lParam);
        break;

    case WM_NETWORK_LISTENRECEIVEFINISH:
        g_ServerConnection.OnListenReceiveFinish(hwnd, lParam);
        break;

    case WM_DESTROY:

        if (is_executing())
        {
            IsTimeToHalt = true;
        }
        IsTimeToExit = true;

        if (g_Timer != 0)
        {
            KillTimer(g_ScreenWindow, g_Timer);
            g_Timer = 0;
        }

        if (MemoryBitMap != NULL)
        {
            DeleteObject(MemoryBitMap);
            MemoryBitMap = NULL;
        }

        if (g_MemoryDeviceContext != NULL)
        {
            DeleteDC(g_MemoryDeviceContext);
            g_MemoryDeviceContext = NULL;
        }
   
        if (g_ScreenDeviceContext != NULL)
        {
            ReleaseDC(g_ScreenWindow, g_ScreenDeviceContext);
            g_ScreenDeviceContext = NULL;
        }

        g_ScreenWindow = NULL;
 
        if (g_IsLoadingFile)
        {
            // Something prevents the screensaver process
            // from terminating if WM_DESTROY is sent while 
            // the logo engine is running from a WM_TIMER.
            exit(EXIT_SUCCESS);
        }
        else
        {
            // We are not in the Logo evaluator, so we can cleanup here.
            UninitializeLogoEngine();
        }
        break;

    default: 
        rval = DefScreenSaverProc(hwnd, message, wParam, lParam);
    }

    return rval;
}

// This is the function Windows calls to launch our dialog box.
BOOL WINAPI ScreenSaverConfigureDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    DWORD        bytesWritten;
    OPENFILENAME openFileName;
    char         logoFileFilter[256];

    switch (message)
    {
    case WM_INITDIALOG:
        // WM_INITDIALOG - initialize the dialog box with values.

        // Read which file to use from the registry.
        GetConfigurationString(
            "ScreenSaverFile",
            g_FileToLoad,
            ARRAYSIZE(g_FileToLoad),
            "");

        // Update the field in the dialog box to reflect this
        return ::SetDlgItemText(hDlg, IDC_LOGOFILEEDIT, g_FileToLoad);

    case WM_COMMAND:
        // WM_COMMAND will be given to us as the message for the main execution of the
        // dialog box.  This happens when the user hits a button, like OK, Cancel, Reset, etc.

        switch LOWORD(wParam)
        {
        case IDOK:
            // The use pressed the OK button.
            // Copy all of the values which the user entered into the dialog box
            // and transfer it to the all the values from each control and store them in global variables
            // so that we can later persist them to the registry.
            bytesWritten = GetDlgItemText(
                hDlg,
                IDC_LOGOFILEEDIT,
                g_FileToLoad,
                ARRAYSIZE(g_FileToLoad));
            if (bytesWritten != 0)
            {
                // Persist the values
                SetConfigurationString(
                    "ScreenSaverFile",
                    g_FileToLoad);
            }

            EndDialog(hDlg, TRUE);
            return TRUE;

        case IDCANCEL:
            // They hit the Cancel button, so ignore what they put into the
            // dialog box and just exit.
            EndDialog(hDlg, FALSE);
            return TRUE;
   
            // They hit the Reset to Defaults button, so set all the edit boxes to good defaults.
        case IDC_LOCATE:

            // translate from the file filter format which
            // Borland uses to the one which the screensaver uses.
            // This saves the translators time in that they don't have
            // to localize two strings.
            size_t i = 0;
            while (i < ARRAYSIZE(logoFileFilter) &&
                   LOCALIZED_FILEFILTER_LOGO[i] != '\0')
            {
                logoFileFilter[i] = LOCALIZED_FILEFILTER_LOGO[i];
                if (logoFileFilter[i] == '|')
                {
                    // map all | characters to \0
                    logoFileFilter[i] = '\0';
                }

                i++;
            }
            // Add another NULL terminator
            logoFileFilter[i] = '\0';

            ZeroMemory(&openFileName, sizeof openFileName);
            openFileName.lStructSize       = sizeof openFileName;
            openFileName.hwndOwner         = hDlg;
            openFileName.hInstance         = NULL;
            openFileName.lpstrFilter       = logoFileFilter;
            openFileName.lpstrCustomFilter = NULL;
            openFileName.nMaxCustFilter    = 0;
            openFileName.nFilterIndex      = 0;
            openFileName.lpstrFile         = g_FileToLoad;
            openFileName.nMaxFile          = ARRAYSIZE(g_FileToLoad);
            openFileName.lpstrFileTitle    = NULL;
            openFileName.nMaxFileTitle     = 0;
            openFileName.lpstrInitialDir   = NULL;
            openFileName.lpstrTitle        = NULL;
            openFileName.Flags             = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
            openFileName.nFileOffset       = 0;
            openFileName.nFileExtension    = 0;
            openFileName.lpstrDefExt       = NULL;
            openFileName.lCustData         = 0;
            openFileName.lpfnHook          = NULL;
            openFileName.lpTemplateName    = NULL;

            if (GetOpenFileName(&openFileName))
            {
                // update the dialog box item
                ::SetDlgItemText(hDlg, IDC_LOGOFILEEDIT, openFileName.lpstrFile);
            }
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

BOOL WINAPI RegisterDialogClasses(HANDLE hInst)
{
    return TRUE;
}

// stubs that abstract the logo engine from the window toolkit
bool CheckOnScreenControls()
{
    return false;
}

void single_step_box(NODE *the_line)
{
}

// This function is called when Logo wants to write a line of text to the commander's
// recall box.  Since we don't have a recall box, we instead write directly to the
// screen.
void putcombobox(const char *str)
{
    HDC     memoryDeviceContext = GetMemoryDeviceContext();
    HBITMAP oldBitmap           = (HBITMAP) SelectObject(memoryDeviceContext, MemoryBitMap);

    if (EnablePalette)
    {
        OldPalette = SelectPalette(memoryDeviceContext, ThePalette, FALSE);
        RealizePalette(memoryDeviceContext);
    }

    SetBkColor(memoryDeviceContext, scolor);
    SetBkMode(memoryDeviceContext, TRANSPARENT);
    SetTextColor(memoryDeviceContext, pcolor);

    FontRec.lfEscapement = 0;
    HFONT tempFont = CreateFontIndirect(&FontRec);
    HFONT oldFont = (HFONT) SelectObject(memoryDeviceContext, tempFont);

    // figure out how much space this text will take up
    SIZE size;
    GetTextExtentPoint(memoryDeviceContext, str, strlen(str), &size);

    if (BitMapHeight < g_NextTextLine + size.cy)
    {
        // The text won't fit on the screen,
        // so wrap it back to the beginning.
        g_NextTextLine = 0;
    }

    TextOut(
        memoryDeviceContext,
        0,
        g_NextTextLine,
        str,
        strlen(str));

    if (EnablePalette)
    {
        SelectPalette(memoryDeviceContext, OldPalette, FALSE);
    }

    SelectObject(memoryDeviceContext, oldFont);
    SelectObject(memoryDeviceContext, oldBitmap);

    DeleteObject(tempFont);

    // Update the screen to show the text.
    RECT textRect;
    textRect.left   = 0;
    textRect.top    = g_NextTextLine;
    textRect.right  = size.cx;
    textRect.bottom = g_NextTextLine + size.cy;

    InvalidateRect(GetScreenWindow(), &textRect, TRUE);

    // Move to the next line
    g_NextTextLine += size.cy + 10;
}

bool promptuser(char *str, const char *prompt)
{
    return false;
}

HWND GetScreenWindow()
{
    return g_ScreenWindow;
}

HWND GetMainWindow()
{
    // Return the screen so that WM_TIMER events that are
    // created by SetTimer() get posted to the ScreenSaverProc.
    return g_ScreenWindow;
}

HWND GetCommanderWindow()
{
    return NULL;
}

HWND GetParentWindowForDialog()
{
    // Because the screen window is full screen and always on top,
    // it must be the parent of any dialog box that we want to
    // show, or else that dialog wouldn't be visible.
    return GetScreenWindow();
}

HWND GetEditorWindow()
{
    return NULL;
}

UINT GetScreenHorizontalScrollPosition()
{
    return 0;
}

UINT GetScreenVerticalScrollPosition()
{
    return 0;
}

void SetScreenScrollPosition(UINT x, UINT y)
{
}

bool IsEditorOpen()
{
    return false;
}

void OpenEditorToLocationOfFirstError(const char *FileName)
{
}


HDC GetScreenDeviceContext()
{
    return g_ScreenDeviceContext;
}

HDC GetMemoryDeviceContext()
{
    return g_MemoryDeviceContext;
}

void OpenStatusWindow()
{
}

void CloseStatusWindow()
{
}

void AdjustScrollPositionToZoomFactor(FLONUM NewZoomFactor)
{
}

void UndockCommanderWindow()
{
    // The screen saver doesn't have a commander window,
    // so there is nothing to undock.
}

void DockCommanderWindow()
{
    // The screen saver doesn't have a commander window,
    // so there is nothing to dock.
}

int ShowEditorForFile(const char *FileName, NODE *args)
{
    return 0;
}

void
ShowProcedureMiniEditor(
    const char           * ToLine,
    class CDynamicBuffer & ReadBuffer
    )
{
    // Reading from stdin is not supported in the screensaver
    err_logo(STOP_ERROR, NIL);
}

void
TraceOutput(
    const char * FormatString,
    ...
    )
{
    char formattedString[256] = {0};

    va_list args;

    va_start(args, FormatString);

    int bytesNeeded = vsnprintf(
        formattedString,
        ARRAYSIZE(formattedString) - 1,
        FormatString,
        args);
    if (0 <= bytesNeeded)
    {
        OutputDebugString(formattedString);
    }

    va_end(args);
}
