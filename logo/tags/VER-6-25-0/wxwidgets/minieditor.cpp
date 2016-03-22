#include "minieditor.h"

#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/settings.h>

#include "minieditortextctrl.h"
#include "logocore.h"  // for ARRAYSIZE
#include "localizedstrings.h"

// Menu IDs
enum
{
   ID_MINIEDITOR_RICHTEXTCONTROL = wxID_HIGHEST,
};

// ----------------------------------------------------------------------------
// CMiniEditor
// ----------------------------------------------------------------------------

CMiniEditor::CMiniEditor(
    wxWindow * Parent, 
    const char * ToLine
    )
    : wxDialog(
        Parent,
        wxID_ANY,
        wxString(ToLine),
        wxDefaultPosition,
        wxDefaultSize,
        wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
    wxBoxSizer *topLevelSizer = new wxBoxSizer(wxVERTICAL);

    // add the To Line input
    m_ToLine = new wxTextCtrl(
        this,
        wxID_ANY,
        ToLine,
        wxDefaultPosition,
        wxDefaultSize,
        wxTE_READONLY);

    // The background color should be light gray to indicate that this
    // is a read-only control.
    m_ToLine->SetBackgroundColour(
        wxSystemSettings::GetColour(wxSYS_COLOUR_3DLIGHT));

    topLevelSizer->Add(
        m_ToLine,
        0,
        wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT | wxEXPAND,
        10);

    // add the procedure body (the editor)
    m_TextField = new CMiniEditorTextCtrl(
        this,
        ID_MINIEDITOR_RICHTEXTCONTROL,
        wxSize(240, 200));
    topLevelSizer->Add(
        m_TextField,
        0,
        wxALIGN_CENTER | wxBOTTOM | wxLEFT | wxRIGHT | wxEXPAND,
        10);


    // add the "end" button
    wxButton * endButton = new wxButton(
        this,
        wxID_OK,
        LOCALIZED_ALTERNATE_END);
    topLevelSizer->Add(
        endButton,
        0,
        wxALIGN_LEFT | wxBOTTOM | wxLEFT | wxRIGHT,
        10);

    SetSizer(topLevelSizer);
    topLevelSizer->Fit(this);
}

CMiniEditor::~CMiniEditor()
{
}
