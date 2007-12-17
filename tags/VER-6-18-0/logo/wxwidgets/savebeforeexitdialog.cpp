#include "savebeforeexitdialog.h"

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>

#include "localizedstrings.h"

// ----------------------------------------------------------------------------
// CSaveBeforeExitDialog
// ----------------------------------------------------------------------------

// Menu IDs
enum
{
   ID_EXITWITHOUTSAVING = wxID_HIGHEST,
};

CSaveBeforeExitDialog::CSaveBeforeExitDialog(wxWindow *Parent)
    : wxDialog(Parent, wxID_ANY, wxString(LOCALIZED_UNSAVEDCHANGES)),
      m_ExitStatus(SAVEBEFOREEXIT_Cancel)
{
    wxBoxSizer *topLevelSizer = new wxBoxSizer(wxVERTICAL);

    // add the text that explains the button choices
    wxStaticText *message1 = new wxStaticText(
        this,
        wxID_ANY,
        LOCALIZED_UNSAVEDCHANGES_MESSAGE1);
    message1->Wrap(400);
    topLevelSizer->Add(message1, 0, wxALIGN_LEFT | wxALL, 10);

    wxStaticText *message2 = new wxStaticText(
        this,
        wxID_ANY,
        LOCALIZED_UNSAVEDCHANGES_MESSAGE2);
    message1->Wrap(400);
    topLevelSizer->Add(message2, 0, wxALIGN_LEFT | wxALL, 10);


    // add the buttons
    wxBoxSizer * buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton *saveAndExitButton = new wxButton(
        this, 
        wxID_OK,
        LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT);
    buttonSizer->Add(saveAndExitButton, 0, wxALIGN_CENTER | wxALL, 5);

    wxButton *exitWithoutSavingButton = new wxButton(
        this, 
        ID_EXITWITHOUTSAVING,
        LOCALIZED_UNSAVEDCHANGES_DONTSAVE);
    buttonSizer->Add(exitWithoutSavingButton, 0, wxALIGN_CENTER | wxALL, 5);

    wxButton *cancelButton = new wxButton(
        this, 
        wxID_CANCEL,
        LOCALIZED_UNSAVEDCHANGES_CANCEL);
    buttonSizer->Add(cancelButton, 0, wxALIGN_CENTER | wxALL, 5);

    topLevelSizer->Add(buttonSizer, 0, wxALIGN_RIGHT | wxALL, 5);


    SetSizer(topLevelSizer);

    topLevelSizer->SetSizeHints(this);
    topLevelSizer->Fit(this);

    // make the "Save and Exit" button the default
    saveAndExitButton->SetDefault();
    saveAndExitButton->SetFocus();
}


void CSaveBeforeExitDialog::OnExitWithoutSaving(wxCommandEvent& WXUNUSED(event))
{
    m_ExitStatus = SAVEBEFOREEXIT_ExitWithoutSaving;
    Destroy();
}

void CSaveBeforeExitDialog::OnSaveBeforeExit(wxCommandEvent& WXUNUSED(event))
{
    m_ExitStatus = SAVEBEFOREEXIT_SaveAndExit;
    Destroy();
}

void CSaveBeforeExitDialog::OnCancel(wxCommandEvent& WXUNUSED(event))
{
    m_ExitStatus = SAVEBEFOREEXIT_Cancel;
    Destroy();
}

CSaveBeforeExitDialog::SAVEBEFOREEXIT CSaveBeforeExitDialog::GetExitCode()
{
    return m_ExitStatus;
}

BEGIN_EVENT_TABLE(CSaveBeforeExitDialog, wxDialog)
    EVT_BUTTON(wxID_CANCEL,           CSaveBeforeExitDialog::OnCancel)
    EVT_BUTTON(wxID_OK,               CSaveBeforeExitDialog::OnSaveBeforeExit)
    EVT_BUTTON(ID_EXITWITHOUTSAVING,  CSaveBeforeExitDialog::OnExitWithoutSaving)
END_EVENT_TABLE()

