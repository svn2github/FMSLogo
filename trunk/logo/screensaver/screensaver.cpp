#include <windows.h>
#include <time.h>
#include <scrnsave.h>

#include "init.h"
#include "graphwin.h"
#include "startup.h"
#include "main.h"
#include "mem.h"
#include "mmwind.h"
#include "wrksp.h"
#include "utils.h"
#include "files.h"
#include "screenwindow.h"

int *TopOfStack  = NULL;
int BitMapWidth  = 0;
int BitMapHeight = 0;

int GCMAX = 1024*8;

static UINT   g_Timer;
static CHAR   g_FileToLoad[MAX_PATH] = "C:\\Documents and Settings\\Dave\\My Documents\\saver.lgo";
static HANDLE g_SingleInstanceMutex = NULL;

#ifdef MEM_DEBUG
// define values that didn't exist when Borland C++ was written
const DWORD GR_GDIOBJECTS  = 0;
const DWORD GR_USEROBJECTS = 1;
typedef DWORD WINAPI (*GETGUIRESOURCES)(HANDLE, DWORD);

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

const DWORD DELAYTIME_MILLISECONDS = 10000;

LRESULT WINAPI ScreenSaverProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int i;

    switch(message)
    {
    case WM_CREATE:

        // Start the timer.
        // Use the minimum timer tick time so that we can run
        // the next instruction as soon as the previous one completes.
        g_Timer = SetTimer(
            hwnd,
            33,
            USER_TIMER_MINIMUM,
            NULL);

        g_ScreenWindow = hwnd;
        GetClientRect(g_ScreenWindow, &FullRect);

        // Fill the screen with blackness.
        g_ScreenDeviceContext = GetDC(g_ScreenWindow);
        g_MemoryDeviceContext = CreateCompatibleDC(g_ScreenDeviceContext);
        
        // Size-to-fit
        BitMapHeight = FullRect.bottom;
        BitMapWidth  = FullRect.right;

#ifdef MEM_DEBUG
        g_Fmslogo = NULL;
        g_User32  = GetModuleHandle("user32.dll");
        if (user32 != NULL)
        {
            g_GetGuiResources = (GETGUIRESOURCES) GetProcAddress(user32, "GetGuiResources");
            if (g_etGuiResources != NULL)
            {
                g_Fmslogo = OpenProcess(
                    PROCESS_QUERY_INFORMATION, 
                    FALSE, 
                    GetCurrentProcessId());
                if (g_Fmslogo != NULL)
                {
                    g_OriginalGuiObjects  = getGuiResources(fmslogo, GR_GDIOBJECTS);
                    g_OriginalUserObjects = getGuiResources(fmslogo, GR_USEROBJECTS);
                }
            }
        }
#endif // MEM_DEBUG

        init_osversion();

        DisableDataExecutionProtection();

        //_control87(EM_OVERFLOW,  EM_OVERFLOW);
        //_control87(EM_UNDERFLOW, EM_UNDERFLOW);

        TopOfStack = &i;

        // Grab the single instance lock.
        // We don't want to fail if Logo is running, since we are a screen saver.
        // But we do want to prevent Logo from being uninstalled.
        g_SingleInstanceMutex = CreateMutex(
            NULL,  // default security attributes
            FALSE, // no initial owner
            "LogoForWindowsMutex");
      
        // Get garbage collector stack size from the configuration settings
        GCMAX = GetConfigurationInt("GCStackSize", 8192);

        // Get video mode parameters
        init_videomode();

        srand(time(NULL));

        // alloc garbage collector stack
        gcstack = (NODE **) malloc(sizeof(NODE *) *GCMAX);

        gctop = gcstack;

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
        break;

    case WM_ERASEBKGND:
        // Fill the screen with whiteness.
        FillRect(
            g_ScreenDeviceContext,
            &FullRect,
            (HBRUSH) GetStockObject(WHITE_BRUSH));
        break;

    case WM_TIMER:

        // Run the file to load it it's been more than DELAYTIME
        // milliseconds since the last time we ran it.
        if (g_TickCountOfMostRecentLoad + DELAYTIME_MILLISECONDS <= GetTickCount())
        {
            lclearscreen(NULL);
            silent_load(NIL, g_FileToLoad);
            g_TickCountOfMostRecentLoad = GetTickCount();
        }
        break;

    case WM_DESTROY:

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

        free(gcstack);

        // release the HTML Help subsystem
        HtmlHelpUninitialize();

        CloseHandle(g_SingleInstanceMutex);
        g_SingleInstanceMutex = NULL;

#ifdef MEM_DEBUG
        if (g_Fmslogo != NULL)
        {
            // Check if any GUI objects were leaked
            DWORD currentGuiObjects = getGuiResources(fmslogo, GR_GDIOBJECTS);
            if (g_OriginalGuiObjects < currentGuiObjects)
            {
                fprintf(
                    stderr, 
                    "%d GUI objects were leaked.\n",
                    currentGuiObjects - originalUserObjects);
            }

            // Check if any USER objects were leaked
            DWORD currentUserObjects = getGuiResources(fmslogo, GR_USEROBJECTS);
            if (g_OriginalUserObjects < currentUserObjects)
            {
                fprintf(
                    stderr, 
                    "%d USER objects were leaked.\n",
                    currentUserObjects - originalUserObjects);
            }

            CloseHandle(g_Fmslogo);
        }
#endif // MEM_DEBUG

        if (g_Timer == 0)
        {
            KillTimer(hwnd, g_Timer);
            g_Timer = 0;
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
        break;

    default: 
        return DefScreenSaverProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

BOOL WINAPI ScreenSaverConfigureDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    return TRUE;
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

void putcombobox(const char *str)
{
}

bool promptuser(char *str, const char *prompt)
{
    return false;
}

void emptyqueue()
{
}

void uninitialize_windows()
{
}

HWND GetScreenWindow()
{
    return g_ScreenWindow;
}

HWND GetMainWindow()
{
    return NULL;
}

HWND GetCommanderWindow()
{
    return NULL;
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
}

int ShowEditorForFile(const char *FileName, NODE *args)
{
    return 0;
}
