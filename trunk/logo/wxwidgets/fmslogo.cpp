#include "fmslogo.h"

#include <wx/msgdlg.h>
#include <wx/filename.h>
#include <wx/string.h>

#ifdef __WXMSW__
   #include "wx/msw/private.h"
#endif

#include "localizedstrings.h"
#include "logocore.h" // for ARRAYSIZE
#include "mainframe.h"
#include "help.h"

wxFileName * g_LibPathName;     // path to library
wxFileName * g_TempPathName;    // path to temp edit file
wxFileName * g_TempBmpName;     // path to temp bitmap file
wxFileName * g_TempClipName;    // path to temp clipboard file
wxFileName * g_HelpFileName;    // path to help file
wxFileName * g_MciHelpFileName; // path to MCI help file

static char g_FileToLoad[MAX_BUFFER_SIZE];  // routine to exec on start

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

static bool g_PerspectiveMode = false;
static bool g_ExpertMode      = false;
static bool g_FixedMode       = false;
static bool g_CustomWidth     = false;
static bool g_CustomHeight    = false;

static int g_BitMapWidth;
static int g_BitMapHeight;

void CFmsLogo::ProcessCommandLine()
{
    // process the command-line parameters
    // parse the command-line parameters
    g_PerspectiveMode = false;
    g_ExpertMode      = false;
    g_FixedMode       = false;

    // for processing the -L parameter
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
                g_PerspectiveMode = true;
                break;

            case 'e':
            case 'E':
                g_ExpertMode = true;
                break;

            case 'f':
            case 'F':
                g_FixedMode = true;
                break;

            case 'h':
            case 'H':
                g_BitMapHeight = strtoul(argument, &argument, 10);
                g_CustomHeight = true;
                break;

            case 'w':
            case 'W':
                g_BitMapWidth = strtoul(argument, &argument, 10);
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

    if (g_FileToLoad[0] != '\0')
    {
        fprintf(stderr, "Loading file `%s'\n", g_FileToLoad);
    }
}

bool CFmsLogo::OnInit()
{

    ProcessCommandLine();

    // create and show the main frame
    CMainFrame* frame = new CMainFrame;

    frame->Show(true);

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

    return true;
}

int CFmsLogo::OnExit()
{
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
