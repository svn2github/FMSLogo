// -*- c++ -*-

#include "aboutmultiplesclerosis.h"

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>

#include "localizedstrings.h"

// ----------------------------------------------------------------------------
// CAboutMultipleSclerosis
// ----------------------------------------------------------------------------

CAboutMultipleSclerosis::CAboutMultipleSclerosis(wxWindow *parent)
    : wxDialog(parent, wxID_ANY, wxString(LOCALIZED_ABOUTMS))
{
    wxStaticText *text1 = new wxStaticText(
        this,
        wxID_ANY,
        "\n  " LOCALIZED_ABOUTMS_FMS "  \n", // add some padding to the sunken border
        wxDefaultPosition,
        wxDefaultSize, 
        wxALIGN_CENTRE | wxSUNKEN_BORDER);

    wxStaticText *text2 = new wxStaticText(
        this,
        wxID_ANY,
        LOCALIZED_ABOUTMS_CONSIDERDONATING, 
        wxDefaultPosition,
        wxDefaultSize, 
        wxALIGN_CENTRE | wxSUNKEN_BORDER);

    wxButton *okButton = new wxButton(this, wxID_CANCEL, LOCALIZED_ABOUTMS_OK);


    wxBoxSizer *sizerTop = new wxBoxSizer(wxVERTICAL);
    sizerTop->Add(text1,    0, wxALIGN_CENTER | wxALL | wxEXPAND, 5);
    sizerTop->Add(text2,    0, wxALIGN_CENTER | wxALL | wxEXPAND, 5);
    sizerTop->Add(okButton, 0, wxALIGN_CENTER | wxALL, 5);

    SetSizer(sizerTop);

    sizerTop->SetSizeHints(this);
    sizerTop->Fit(this);


    // make the "Ok" button the default
    okButton->SetFocus();
    okButton->SetDefault();
}
