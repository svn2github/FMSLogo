#include "minieditor.h"

#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/settings.h>

#include "minieditortextctrl.h"
#include "logocore.h"  // for ARRAYSIZE
#include "fontutils.h"
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
    wxWindow   * Parent, 
    const char * ToLineString
    )
    : wxDialog(
        Parent,
        wxID_ANY,
        wxString(ToLineString),
        wxDefaultPosition,
        wxSize(240, 212),
        wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER),
      m_TextField(NULL)
{
    wxBoxSizer * topLevelSizer = new wxBoxSizer(wxVERTICAL);

    // add the To Line input
    wxTextCtrl * toLine = new wxTextCtrl(
        this,
        wxID_ANY,
        ToLineString,
        wxDefaultPosition,
        wxDefaultSize,
        wxTE_READONLY);

    // The background color should be light gray to indicate that this
    // is a read-only control.
    toLine->SetBackgroundColour(
        wxSystemSettings::GetColour(wxSYS_COLOUR_3DLIGHT));

    topLevelSizer->Add(
        toLine,
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

    // Set the font to whatever is defined in the configuraton
    wxFont font;
    font.SetFamily(wxFONTFAMILY_TELETYPE); // default to using a fixed-width font
    GetConfigurationFont("CommanderFont", font);
    m_TextField->SetFont(font);

    // Add the "end" button
    wxButton * endButton = new wxButton(
        this,
        wxID_OK,
        LOCALIZED_ALTERNATE_END);
    topLevelSizer->Add(
        endButton,
        0,
        wxALIGN_LEFT | wxBOTTOM | wxLEFT | wxRIGHT,
        10);
    endButton->SetDefault();

    SetSizer(topLevelSizer);
    topLevelSizer->Fit(this);
}

CMiniEditor::~CMiniEditor()
{
}

const wxString
CMiniEditor::GetProcedureBody() const
{
    return m_TextField->GetValue();
}
