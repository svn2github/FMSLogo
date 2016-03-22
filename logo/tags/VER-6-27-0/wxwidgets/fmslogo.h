// -*- c++ -*-

#include "wx/app.h"

class CMainFrame;
class wxFileName;

///////////////////////////////////////////////////////////////
// Constants
const int DEFAULT_COMMANDER_HEIGHT = 150;
const int MIN_COMMANDER_HEIGHT     = 110;
const int DEFAULT_SPLITTER_WIDTH   = 5;

///////////////////////////////////////////////////////////////
// Global Variables
extern wxFileName * g_LibPathName;     // path to library
extern wxFileName * g_TempPathName;    // path to temp edit file
extern wxFileName * g_TempBmpName;     // path to temp bitmap file
extern wxFileName * g_TempClipName;    // path to temp clipboard file
extern wxFileName * g_HelpFileName;    // path to help file
extern wxFileName * g_MciHelpFileName; // path to MCI help file


///////////////////////////////////////////////////////////////
// Classes
class CFmsLogo : public wxApp
{
public:
    CFmsLogo();

    static CMainFrame * GetMainFrame();

    virtual bool OnInit();
    virtual int  OnExit();

private:
    void ProcessCommandLine();

    DECLARE_NO_COPY_CLASS(CFmsLogo)
};

