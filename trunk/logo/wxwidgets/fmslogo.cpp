#include "fmslogo.h"

#include <algorithm>

#include <wx/msgdlg.h>
#include <wx/filename.h>
#include <wx/string.h>
#include <wx/dcclient.h>
#include <wx/dcmemory.h>

#ifdef __WXMSW__
   #include "wx/msw/private.h"
#endif

#include "init.h"
#include "localizedstrings.h"
#include "logocore.h" // for ARRAYSIZE
#include "mainframe.h"
#include "graphwin.h"
#include "wrksp.h"
#include "help.h"
#include "main.h"
#include "startup.h"
#include "utils.h"
#include "mem.h"
#include "mmwind.h"
#include "files.h"
#include "mainwind.h"
#include "eval.h"
#include "screenwindow.h"

#include "screen.h"
#include "commander.h"

wxFileName * g_LibPathName;     // path to library
wxFileName * g_TempPathName;    // path to temp edit file
wxFileName * g_TempBmpName;     // path to temp bitmap file
wxFileName * g_TempClipName;    // path to temp clipboard file
wxFileName * g_HelpFileName;    // path to help file
wxFileName * g_MciHelpFileName; // path to MCI help file

// global variables declared in main.h
int  GCMAX        = 8192;
int  BitMapWidth  = 1000;
int  BitMapHeight = 1000;
bool bFixed       = false;
int *TopOfStack   = NULL;

static HANDLE g_SingleInstanceMutex = NULL;

static char g_FileToLoad[MAX_PATH] = ""; // routine to exec on start
static bool g_EnterPerspectiveMode = false;
static bool g_CustomWidth          = false;
static bool g_CustomHeight         = false;

#ifdef MEM_DEBUG
typedef DWORD (WINAPI *GETGUIRESOURCES)(HANDLE, DWORD);

static GETGUIRESOURCES g_GetGuiResources     = NULL;
static DWORD           g_OriginalGuiObjects  = 0;
static DWORD           g_OriginalUserObjects = 0;
static HANDLE          g_Fmslogo             = NULL;
static HMODULE         g_User32              = NULL;
#endif // MEM_DEBUG



////////////////////////////////////////////////////////////////////
// Helper Functions

// Creates a unique filename relative to TempPath
static
void ConcatenatePath(char *OutBuffer, const char * BasePath, const char * FileName)
{
    // the first part of the new filename is BasePath
    char * ptr       = OutBuffer;
    const char * src = BasePath;
    while (*src != '\0')
    {
        *ptr++ = *src++;
    }

    // make sure that the path ends in a directory delimiter
    if (*ptr != '\\')
    {
        *ptr++ = '\\';
    }
   
    // append FileName
    strcpy(ptr, FileName);
}


////////////////////////////////////////////////////////////////////
// CFmsLogo
IMPLEMENT_APP(CFmsLogo)

CFmsLogo::CFmsLogo()
{
}

void CFmsLogo::ProcessCommandLine()
{
    // parse the command-line parameters
    g_FileToLoad[0] = '\0';
    bExpert        = false;
    g_CustomWidth  = false;
    g_CustomHeight = false;
    bFixed         = false;

    // For processing the -L parameter
    bool   copyRemaingArgsAsFilename = false;
    size_t fileToLoadIndex           = 0;

    for (wxChar ** nextArgument = argv + 1;
         *nextArgument != NULL; 
         nextArgument++)
    {
        wxChar * argument = *nextArgument;

        if (copyRemaingArgsAsFilename)
        {
            // BUG: this is not backward compatible with MSWLogo.
            // This should tolerate multiple spaces, intead of assuming
            // that there's exactly one space between arguments.
            if (fileToLoadIndex != 0 &&
                fileToLoadIndex < ARRAYSIZE(g_FileToLoad))
            {
                g_FileToLoad[fileToLoadIndex++] = ' ';
            }

            // copy the rest of the line into the g_FileToLoad buffer
            strncpy(
                &g_FileToLoad[fileToLoadIndex],
                argument,
                ARRAYSIZE(g_FileToLoad) - 1 - fileToLoadIndex);

            fileToLoadIndex += strlen(argument);
        }
        else if (*argument == '-')
        {
            argument++; // advance beyond the -

            switch (*argument++)
            {
            case 'p':
            case 'P':
                g_EnterPerspectiveMode = true;
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
                BitMapHeight = strtoul(argument, &argument, 10);
                g_CustomHeight = true;
                break;

            case 'w':
            case 'W':
                BitMapWidth = strtoul(argument, &argument, 10);
                g_CustomWidth = true;
                break;

            case 'l':
            case 'L':
                // the rest of the arguments should be taken as part of a filename
                copyRemaingArgsAsFilename = true;
                break;

            default:
                // invalid command line: unrecognized switch
                wxMessageBox(
                    argument,
                    LOCALIZED_ERROR_BADCOMMANDLINE, 
                    wxOK | wxICON_INFORMATION);
                break;
            }
        }
        else
        {
            // this was not a switch, so treat it as a filename
            if (g_FileToLoad[0] == '\0')
            {
                strncpy(g_FileToLoad, argument, ARRAYSIZE(g_FileToLoad) - 1);
            }
            else
            {
                // we only support loading a single filename.
                wxMessageBox(
                    argument,
                    LOCALIZED_ERROR_BADCOMMANDLINE, 
                    wxOK | wxICON_INFORMATION);
            }
        }
    }

    // if fixed mode then make unspecified dimensions
    // really large (shrink to fit)
    if (bFixed)
    {
        if (!g_CustomWidth)
        {
            BitMapWidth  = 2048;
        }
        if (!g_CustomHeight)
        {
            BitMapHeight = 2048;
        }
    }
}

bool CFmsLogo::OnInit()
{
    bool rval = true;

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
      
    // Get garbage collector stack size from the configuration settings
    GCMAX = GetConfigurationInt("GCStackSize", 8192);

    ProcessCommandLine();

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

    // If -P was specified on the command line, enter perspective mode.
    if (g_EnterPerspectiveMode)
    {
        g_EnterPerspectiveMode = false;
        lperspective(NIL);
    }

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
        if (g_CustomHeight)
        {
            // if height specified santize it against screen height
            h = std::min(h, maxHeight);
        }
        else
        {
            // else choose something reasonable
            h = (int) (maxHeight * ScreenSz);
        }

        if (g_CustomWidth)
        {
            // if width specified santize it against screen width
            w = std::min(w, maxWidth);
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
        w = std::min(w, maxWidth);
        h = std::min(h, (int) (maxHeight * ScreenSz));

        GetConfigurationQuadruple("Screen", &x, &y, &w, &h);

        // the smallest reasonable size is 200 x 200.
        h = std::max(h, 200);
        w = std::max(w, 200);

        // sanatize against screen size
        checkwindow(&x, &y, &w, &h);
    }

    // initialize the values for some of the graphics-related
    // global variables.
    init_graphics();

    // create and show the main frame
    CMainFrame * frame = new CMainFrame(BitMapWidth, BitMapHeight);

    frame->GetScreen()->SetSize(x, y, w, h);
    frame->Show(true);

    // run the startup script that localizes logo
    char startupScript[MAX_PATH + 1];
    MakeHelpPathName(startupScript, "startup.logoscript");
    silent_load(NIL, startupScript);

    //
    // initialize paths to library and help files based on location of executable
    //

    // get the path name of fmslogo.exe
    wxString programFileNamePath;
    wxString programFileNameVolume;

    wxFileName::SplitPath(
#ifdef __WXMSW__
        wxGetFullModuleName(),
#else
        "", // TODO: figure out how to do this on GNU/Linux
#endif
        &programFileNameVolume,
        &programFileNamePath,
        NULL, // don't need the name
        NULL, // don't need the extension
        wxPATH_NATIVE);

    g_LibPathName = new wxFileName(
        programFileNameVolume,
        programFileNamePath + "logolib\\",
        "",
        "");

    g_HelpFileName = new wxFileName(
        programFileNameVolume,
        programFileNamePath,
        "logohelp",
        "chm");

    g_MciHelpFileName = new wxFileName(
        programFileNameVolume,
        programFileNamePath,
        "mcistrwh",
        "hlp");

#if 0
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
    ConcatenatePath(TempPathName, tempPath, "mswlogo.tmp");

    // construct the name of the temporary bitmap file
    ConcatenatePath(TempBmpName, tempPath, "mswlogo.bmp");

    // construct the name of the clipboard file
    ConcatenatePath(TempClipName, tempPath, "mswlogo.clp");
#endif

    return rval;
}

int CFmsLogo::OnExit()
{
    /// --- copied from screensaver WM_DESTROY handler ---
    /// TODO: Is this necessary?
    if (is_executing())
    {
        IsTimeToHalt = true;
    }
    IsTimeToExit = true;
    /// --- end of copied from screensaver WM_DESTROY handler ---

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

    delete g_LibPathName;
    delete g_TempPathName;
    delete g_TempBmpName;
    delete g_TempClipName;
    delete g_HelpFileName;
    delete g_MciHelpFileName;

    HelpUninitialize();

    return wxApp::OnExit();
}

CMainFrame * CFmsLogo::GetMainFrame()
{
    return static_cast<CMainFrame*>(wxTheApp->GetTopWindow());
}


// stubs that abstract the logo engine from the window toolkit
bool CheckOnScreenControls()
{
    return false;
}

void single_step_box(NODE *the_line)
{
}

bool promptuser(char *str, const char *prompt)
{
    return false;
}

void uninitialize_windows()
{
}

HWND GetScreenWindow()
{
    CMainFrame* mainFrame = static_cast<CMainFrame*>(wxTheApp->GetTopWindow());
    return reinterpret_cast<HWND>(mainFrame->GetScreen()->GetHandle());
}

HWND GetMainWindow()
{
    return static_cast<HWND>(wxTheApp->GetTopWindow()->GetHandle());
}

HWND GetCommanderWindow()
{
    CMainFrame* mainFrame = static_cast<CMainFrame*>(wxTheApp->GetTopWindow());
    return reinterpret_cast<HWND>(mainFrame->GetCommander()->GetHandle());
}

HWND GetEditorWindow()
{
    return NULL;
}

UINT GetScreenHorizontalScrollPosition()
{
    CMainFrame* mainFrame = static_cast<CMainFrame*>(wxTheApp->GetTopWindow());
    return mainFrame->GetScreen()->GetScrollPos(wxHORIZONTAL);
}


UINT GetScreenVerticalScrollPosition()
{
    CMainFrame* mainFrame = static_cast<CMainFrame*>(wxTheApp->GetTopWindow());
    return mainFrame->GetScreen()->GetScrollPos(wxVERTICAL);
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
    CMainFrame* mainFrame = static_cast<CMainFrame*>(wxTheApp->GetTopWindow());
    return static_cast<HDC>(mainFrame->GetScreen()->GetScreenDeviceContext().GetHDC());
}

HDC GetMemoryDeviceContext()
{
    CMainFrame* mainFrame = static_cast<CMainFrame*>(wxTheApp->GetTopWindow());
    return static_cast<HDC>(mainFrame->GetScreen()->GetMemoryDeviceContext().GetHDC());
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

void
TraceOutput(
    const char * FormatString,
    ...
    )
{
    va_list args;
    va_start(args, FormatString);
    vfprintf(stderr, FormatString, args);
    va_end(args);
}
