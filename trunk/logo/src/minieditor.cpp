#include "minieditor.h"

#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/settings.h>

#include "minieditortextctrl.h"
#include "fontutils.h"
#include "stringadapter.h"
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
        WXSTRING(ToLineString),
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
        WXSTRING(ToLineString),
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
        1, // expand this control with the size of the dialog box
        wxALIGN_CENTER | wxBOTTOM | wxLEFT | wxRIGHT | wxEXPAND,
        10);

    // Set the font to whatever is defined in the configuraton
    wxFont font;
    font.SetFamily(wxFONTFAMILY_TELETYPE); // default to using a fixed-width font
    GetConfigurationFont("CommanderFont", font);
    m_TextField->SetFont(font);

    // Add a row for the two buttons (End and Cancel)
    wxBoxSizer *buttonRow = new wxBoxSizer(wxHORIZONTAL);
    topLevelSizer->Add(
        buttonRow,
        0,
        wxALIGN_CENTER | wxBOTTOM | wxLEFT | wxRIGHT | wxEXPAND,
        10);

    // Add the "end" button
    wxButton * endButton = new wxButton(
        this,
        wxID_OK,
        WXSTRING(LOCALIZED_ALTERNATE_END));
    buttonRow->Add(
        endButton,
        0,
        wxALIGN_LEFT);
    endButton->SetDefault();

    // Add a stretch spacer between End and Cancel so
    // that they can be on the left and right of the
    // dialog box, instead of next to each other.
    buttonRow->AddStretchSpacer();

    // Add the "Cancel" button.
    // While a Cancel button was not in the original design, wxWidgets
    // requires that it exist in order for the ESC key to act like a cancel.
    // Without it, ESC would simulate a keypress on the End button,
    // causing the definition to be accepted, instead of abandoned.
    wxButton * cancelButton = new wxButton(
        this,
        wxID_CANCEL,
        WXSTRING(LOCALIZED_GENERAL_CANCELBUTTON));
    buttonRow->Add(
        cancelButton,
        0,
        wxALIGN_RIGHT);

    SetSizer(topLevelSizer);

    // Ensure that the user doesn't resize the window so small
    // that the buttons overlap or are off-screen.
    topLevelSizer->SetSizeHints(this);
}

CMiniEditor::~CMiniEditor()
{
}

const wxString
CMiniEditor::GetProcedureBody() const
{
    return m_TextField->GetValue();
}
