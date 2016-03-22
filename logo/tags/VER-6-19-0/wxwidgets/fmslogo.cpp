
#include "fmslogo.h"

#include <windows.h>

#include <wx/filename.h>
#include <wx/string.h>

#ifdef __WXMSW__
   #include "wx/msw/private.h"
#endif

#include "logocore.h" // for ARRAYSIZE
#include "mainframe.h"
#include "help.h"

wxFileName * g_LibPathName;     // path to library
wxFileName * g_TempPathName;    // path to temp edit file
wxFileName * g_TempBmpName;     // path to temp bitmap file
wxFileName * g_TempClipName;    // path to temp clipboard file
wxFileName * g_HelpFileName;    // path to help file
wxFileName * g_MciHelpFileName; // path to MCI help file

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

bool CFmsLogo::OnInit()
{
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
        wxGetFullModuleName(),
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
