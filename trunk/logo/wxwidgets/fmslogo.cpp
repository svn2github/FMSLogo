
#include "fmslogo.h"
#include "mainframe.h"

IMPLEMENT_APP(CFmsLogo)

CFmsLogo::CFmsLogo()
{
}

bool CFmsLogo::OnInit()
{
    // create and show the main frame
    CMainFrame* frame = new CMainFrame;

    frame->Show(true);

    return true;
}

CMainFrame * CFmsLogo::GetMainFrame()
{
    return static_cast<CMainFrame*>(wxTheApp->GetTopWindow());
}
