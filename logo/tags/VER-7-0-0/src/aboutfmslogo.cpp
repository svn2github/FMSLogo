#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include "aboutfmslogo.h"

   #include <wx/sizer.h>
   #include <wx/stattext.h>
   #include <wx/button.h>

   #include "localizedstrings.h"
   #include "logocore.h" // for ARRAYSIZE
   #include "stringadapter.h"
#endif

// ----------------------------------------------------------------------------
// CAboutFmsLogo
// ----------------------------------------------------------------------------

#define LOCALIZED_ABOUTFMS_WXWIDGETS_VERSION                \
    LOCALIZED_GENERAL_PRODUCTNAME                           \
    " " LOCALIZED_ABOUTFMS_VERSION " " FMSLOGO_VERSION "\n" \
    "http://sourceforge.net/projects/fmslogo"               \

CAboutFmsLogo::CAboutFmsLogo(wxWindow * Parent)
    : wxDialog(Parent, wxID_ANY, WXSTRING(LOCALIZED_ABOUTFMS))
{
    wxBoxSizer *sizerTop = new wxBoxSizer(wxVERTICAL);

    
    // The text in all of the static controls
    static const char * staticText[] = {
        "  " LOCALIZED_ABOUTFMS_WXWIDGETS_VERSION  "  ",
        "  " LOCALIZED_ABOUTFMS_GUI                "  ",
        "  " LOCALIZED_ABOUTFMS_CORE               "  ",
        "  " LOCALIZED_ABOUTFMS_INSTALLER          "  ",
        "  " LOCALIZED_ABOUTFMS_ADVENTURE          "  ",
        "  " LOCALIZED_ABOUTFMS_SPECIALTHANKS      "  ",
        "  " LOCALIZED_ABOUTFMS_GPL                "  ",
        "  " LOCALIZED_ABOUTFMS_NEWSGROUP          "  ",
        "  " LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC    "  ",
    };

    for (size_t i = 0; i < ARRAYSIZE(staticText); i++)
    {
        wxStaticText *info = new wxStaticText(
            this,
            wxID_ANY,
            WXSTRING(staticText[i]),
            wxDefaultPosition,
            wxDefaultSize, 
            wxALIGN_CENTRE | wxSUNKEN_BORDER);

        sizerTop->Add(info, 0, wxALL | wxEXPAND, 5);
    }

    wxButton *okButton = new wxButton(
        this,
        wxID_CANCEL,
        WXSTRING(LOCALIZED_ABOUTFMS_OK));
    sizerTop->Add(okButton, 0, wxALIGN_CENTER | wxALL, 5);

    SetSizer(sizerTop);

    sizerTop->SetSizeHints(this);
    sizerTop->Fit(this);

    // make the "Ok" button the default
    okButton->SetFocus();
    okButton->SetDefault();
}
