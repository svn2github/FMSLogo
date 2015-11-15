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
#include "main.h"

#include <windows.h>
#include <float.h>
#include <math.h>

#include "Scintilla.h"
#include "debugheap.h"
#include "3dsolid.h"
#include "const.h"
#include "eval.h"
#include "print.h"
#include "parse.h"
#include "error.h"
#include "files.h"
#include "ibmterm.h"
#include "utils.h"
#include "init.h"
#include "graphwin.h"
#include "wrksp.h"

#include "mmwind.h"
#include "mainwind.h"
#include "cursor.h"
#include "mainframe.h"
#include "cmdwind.h"
#include "status.h"
#include "graphwin.h"
#include "dlgwind.h"
#include "startup.h"
#include "stringprintednode.h"
#include "screenwindow.h"

#include "localizedstrings.h"

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

bool bFixed;                       // Fixed mode
static bool bWidth;                // Width mode
static bool bHeight;               // Height mode
static bool bPerspective;          // Perspetive mode start up

static char g_FileToLoad[MAX_BUFFER_SIZE];  // file to load on start

// holds callback code

char edit_editexit[MAX_BUFFER_SIZE];   /* callable editor cb                  */

TMainFrame *MainWindowx;               // Pointer to the Main window

int BitMapWidth = 1000;                // Current bitmap size in X
int BitMapHeight = 1000;               // Current bitmap size in Y
bool IsOkayToUseCommanderWindow = false; // Flag to signal it's OK to write to recall box
bool error_happen;                       // Flag to signal Error happened on edit reload


void clearcombobox()
{
    // clear the recall box
    MainWindowx->CommandWindow->Listbox.Clear();

    // scroll it to the top
    MainWindowx->CommandWindow->Listbox.SetCursorAtBottom();
}

// Appends "str" to the end of the what is in the Commander's Recall box.
// If "Text" doesn't fit, then some text will be removed from the top to make it fit.
void putcombobox(const char * Text, MESSAGETYPE MessageType)
{
    // only if OK to write to recall box do we do it
    if (IsOkayToUseCommanderWindow)
    {
        TMyListboxWindow & commanderRecallBox = MainWindowx->CommandWindow->Listbox;

        for (int i=0;i<16;i++)
        {
            // Remember where we started.
            UINT uBefore = commanderRecallBox.GetTextLen();

            // Output to the end of the recall box.
            commanderRecallBox.SetSelection(uBefore, uBefore);
            commanderRecallBox.Insert(Text);
            UINT uAfterText = commanderRecallBox.GetTextLen();

            if (MessageType == MESSAGETYPE_Error)
            {
                // We are writing an error message, so make
                // whatever text we just wrote red.

                // First, select the text we wrote.
                // We hide the selection indicator as we do this
                // so that the error text doesn't appear to flash.
                UINT uAfter = commanderRecallBox.GetTextLen();
                commanderRecallBox.HideSelection(true, false);
                commanderRecallBox.SetSelection(uBefore, uAfterText);

                // Set the selected text to bold red.
                TCharFormat currentFormat;
                commanderRecallBox.GetCharFormat(currentFormat);
                TCharFormat errorFormat(currentFormat);
                errorFormat.SetTextColor(TColor(255, 0, 0)); // red
                errorFormat.EnableBold(); // bold
                commanderRecallBox.SetCharFormat(errorFormat);

                // Reset the character format that's just after
                // what we wrote to be the normal format
                // so that subsequent text is written as normal.
                commanderRecallBox.SetSelection(uAfterText, uAfterText);
                commanderRecallBox.HideSelection(false, false);
                commanderRecallBox.SetCharFormat(currentFormat);
            }

            commanderRecallBox.Insert("\r\n");
            UINT uAfter = commanderRecallBox.GetTextLen();

            // if last 2 bytes inserted ok get out
            if (uAfterText+2 == uAfter) 
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
        commanderRecallBox.Insert(Text);
        commanderRecallBox.Insert("\r\n");
    }
}

void putcombobox(const char * Text)
{
    putcombobox(Text, MESSAGETYPE_Normal);
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

char * promptuser(const char *prompt)
{
    return MainWindowx->MyPopupInput(prompt);
}

void single_step_box(NODE *the_line)
{
    // Print the line into a buffer, honoring the current printing limits
    CStringPrintedNode printedLine(the_line, CStringPrintedNode::WithPrintLimits);

    // pop up single step box showing line of code
    if (MainWindowx->CommandWindow->MessageBox(
            printedLine.GetString(),
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


void TMyApp::InitMainWindow()
{
    /* create the window */
    TPaneSplitter * paneSpliter = new TPaneSplitter(NULL);
    MainWindowx = new TMainFrame(NULL, Name, paneSpliter);
    SetMainWindow(MainWindowx);


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

    init_graphics();
}

TMyApp::~TMyApp()
{
}

void TMyApp::EvSysColorChange()
{
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

    init_osversion();

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

            if (*ptr == '\0')
            {
                // We processed the entire command line.
                // If we continued the loop, we would increment beyond the
                // command line string and into unallocated memory.
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

    // Figure out the path that contains fmslogo.exe
    DWORD nFileNameLength = ::GetModuleFileName(
        GetModuleHandle(NULL),
        g_FmslogoBaseDirectory,
        ARRAYSIZE(g_FmslogoBaseDirectory));

    // start at the end of the full path of fmslogo.exe and walk
    // backwards in the string until we find the final directory delimiter
    for (char * charPtr = g_FmslogoBaseDirectory + nFileNameLength;
         charPtr > g_FmslogoBaseDirectory;
         charPtr--)
    {
        if (*charPtr == '\\')
        {
            // found the last backslash
            break;
        }
        *charPtr = '\0';
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

    init_cursors();

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

    uninit_turtles();

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
            TraceOutput(
                "%d GUI objects were leaked.\n",
                currentGuiObjects - originalUserObjects);
        }

        // Check if any USER objects were leaked
        DWORD currentUserObjects = getGuiResources(fmslogo, GR_USEROBJECTS);
        if (originalUserObjects < currentUserObjects)
        {
            TraceOutput(
                "%d USER objects were leaked.\n",
                currentUserObjects - originalUserObjects);
        }

        CloseHandle(fmslogo);
    }

#endif // MEM_DEBUG

    return exitCode;
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
