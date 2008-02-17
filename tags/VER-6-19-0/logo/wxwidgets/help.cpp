#include "help.h"

#include <wx/filename.h>
#include <wx/msgdlg.h>
#include <wx/textctrl.h>

#include "localizedstrings.h"
#include "fmslogo.h"

#ifdef __WXMSW__ // the .chm only builds on Windows
#include <windows.h>

////////////////////////////////////////////////////////////////////
// copied from HTML Help Workshop/include/htmlhelp.h
//
#define ATOM_HTMLHELP_API_ANSI (LPTSTR)((DWORD)((WORD)(14)))
#define HH_DISPLAY_TOPIC        0x0000
#define HH_KEYWORD_LOOKUP       0x000D
#define HH_CLOSE_ALL            0x0012  // close all windows opened directly or indirectly by the caller

struct HH_AKLINK
{
    int       cbStruct;     // sizeof this structure
    BOOL      fReserved;    // must be FALSE (really!)
    LPCTSTR   pszKeywords;  // semi-colon separated keywords
    LPCTSTR   pszUrl;       // URL to jump to if no keywords found (may be NULL)
    LPCTSTR   pszMsgText;   // Message text to display in MessageBox if pszUrl is NULL and no keyword match
    LPCTSTR   pszMsgTitle;  // Message text to display in MessageBox if pszUrl is NULL and no keyword match
    LPCTSTR   pszWindow;    // Window to display URL in
    BOOL      fIndexOnFail; // Displays index if keyword lookup fails.
};
//
////////////////////////////////////////////////////////////////////

typedef HWND WINAPI (*HTMLHELPFUNC)(HWND, LPCSTR, UINT, DWORD);
static HTMLHELPFUNC g_HtmlHelpFunc;
static HMODULE      g_HtmlHelpLib;
#endif // __WXMSW__

bool
HelpInitialize(
    void
    )
{
#ifdef __WXMSW__ // the .chm only builds on Windows
    if (g_HtmlHelpFunc != NULL)
    {
        // The HTML Help subsystem has already been initialized
        return true;
    }

    // Load the ActiveX control
    g_HtmlHelpLib = ::LoadLibrary("hhctrl.ocx");
    if (g_HtmlHelpLib == NULL) 
    {
        ::wxMessageBox(
            LOCALIZED_ERROR_HHCTRLNOTLOADED, 
            LOCALIZED_ERROR,
            wxOK);
        return false;
    }

    // Get the HtmlHelpA() function pointer
    g_HtmlHelpFunc = (HTMLHELPFUNC) ::GetProcAddress(
        g_HtmlHelpLib, 
        ATOM_HTMLHELP_API_ANSI);
    if (g_HtmlHelpFunc == NULL)
    {
        ::wxMessageBox(
            LOCALIZED_ERROR_HHCTRLATOMNOTFOUND,
            LOCALIZED_ERROR,
            wxOK);

        HelpUninitialize();
        return false;
    }
#endif // __WXMSW__ 

    // success
    return true;
}

void
HelpUninitialize(
    void
    )
{
#ifdef __WXMSW__ // the .chm only builds on Windows
    if (g_HtmlHelpFunc != NULL)
    {
        g_HtmlHelpFunc(NULL, NULL, HH_CLOSE_ALL, 0);
        g_HtmlHelpFunc = NULL;
    }

    if (g_HtmlHelpLib != NULL)
    {
        ::FreeLibrary(g_HtmlHelpLib);
        g_HtmlHelpLib = NULL;
    }
#endif
}

// Opens the manual to whatever is selected in Input
// If ManualEntry is the empty string, then the index is opened.
void OpenHelp(const wxString & ManualEntry)
{
    if (!HelpInitialize())
    {
        return;
    }

    // get the keyword selected
    wxString selection(ManualEntry);

    // remove leading whitespace
    selection = selection.Trim(true);

    // remove trailing whitespace
    selection = selection.Trim(false);

    // if there was some non-space selected,
    const char * keywords;
    if (selection.Len() != 0)
    {
        // look it up in the online help
        keywords = selection.c_str();
    }
    else
    {
        // otherwise, just open the manual to the table of contents
        keywords = NULL;
    }

#ifdef __WXMSW__ // the .chm only builds on Windows
    g_HtmlHelpFunc(
        GetDesktopWindow(),
        g_HelpFileName->GetFullPath(),
        HH_DISPLAY_TOPIC,
        0);

    HH_AKLINK aklink = {0};
    aklink.cbStruct     = sizeof aklink;
    aklink.fReserved    = FALSE;
    aklink.pszKeywords  = keywords;
    aklink.pszUrl       = NULL;
    aklink.pszMsgText   = NULL;
    aklink.pszMsgTitle  = NULL;
    aklink.pszWindow    = "Main";
    aklink.fIndexOnFail = TRUE;

    g_HtmlHelpFunc(
        GetDesktopWindow(), 
        g_HelpFileName->GetFullPath(),
        HH_KEYWORD_LOOKUP, 
        (DWORD) &aklink);

#endif // __WXMSW__
}
