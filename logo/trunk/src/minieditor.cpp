#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include "minieditor.h"

   #include <wx/button.h>
   #include <wx/textctrl.h>
   #include <wx/sizer.h>
   #include <wx/settings.h>

   #include "minieditortextctrl.h"
   #include "fontutils.h"
   #include "stringadapter.h"
   #include "localizedstrings.h"
#endif

// Menu IDs
enum
{
    ID_MINIEDITOR_BODYTEXT = wxID_HIGHEST,

    ID_FINDMATCHINGPAREN,
    ID_SELECTMATCHINGPAREN,
    ID_AUTOCOMPLETE,
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
        wxSize(300, 400),
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
        wxTOP | wxLEFT | wxRIGHT | wxEXPAND,
        10);

    // add the procedure body (the editor)
    m_TextField = new CMiniEditorTextCtrl(this, ID_MINIEDITOR_BODYTEXT);
    topLevelSizer->Add(
        m_TextField,
        1, // expand this control with the size of the dialog box
        wxBOTTOM | wxLEFT | wxRIGHT | wxEXPAND,
        10);

    // Set the font to whatever is defined in the configuraton
    wxFont font;
    font.SetFamily(wxFONTFAMILY_TELETYPE); // default to using a fixed-width font
    GetConfigurationFont("EditFont", font);
    m_TextField->SetFont(font);

    // Add a row for the two buttons (End and Cancel)
    wxBoxSizer *buttonRow = new wxBoxSizer(wxHORIZONTAL);
    topLevelSizer->Add(
        buttonRow,
        0,
        wxBOTTOM | wxLEFT | wxRIGHT | wxEXPAND,
        10);

    // Add the "end" button
    wxButton * endButton = new wxButton(
        this,
        wxID_OK,
        WXSTRING(LOCALIZED_ALTERNATE_END));
    buttonRow->Add(endButton);
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
    buttonRow->Add(cancelButton);

    SetSizer(topLevelSizer);

    // Ensure that the user doesn't resize the window so small
    // that the buttons overlap or are off-screen.
    SetMinSize(GetSize());

    // Configure the keyboard shortcuts
    wxAcceleratorEntry acceleratorEntries[3];

    // Ctrl+] moves to matching paren
    acceleratorEntries[0].Set(
        wxACCEL_CTRL,
        ']',
        ID_FINDMATCHINGPAREN);

    // Ctrl+Shift+] selects to matching paren
    acceleratorEntries[1].Set(
        wxACCEL_CTRL | wxACCEL_SHIFT,
        ']',
        ID_SELECTMATCHINGPAREN);

    // Ctrl+Enter starts auto-complete
    acceleratorEntries[2].Set(
        wxACCEL_CTRL,
        WXK_SPACE,
        ID_AUTOCOMPLETE);

    wxAcceleratorTable acceleratorTable(
        ARRAYSIZE(acceleratorEntries),
        acceleratorEntries);
    SetAcceleratorTable(acceleratorTable);
}

CMiniEditor::~CMiniEditor()
{
}

const wxString
CMiniEditor::GetProcedureBody() const
{
    return m_TextField->GetText();
}

void CMiniEditor::OnFindMatchingParen(wxCommandEvent& WXUNUSED(Event))
{
    m_TextField->FindMatchingParen();
}

void CMiniEditor::OnSelectMatchingParen(wxCommandEvent& WXUNUSED(Event))
{
    m_TextField->SelectMatchingParen();
}

void CMiniEditor::OnAutoComplete(wxCommandEvent& WXUNUSED(Event))
{
    m_TextField->AutoComplete();
}

BEGIN_EVENT_TABLE(CMiniEditor, wxDialog)
    EVT_MENU(ID_FINDMATCHINGPAREN,   CMiniEditor::OnFindMatchingParen)
    EVT_MENU(ID_SELECTMATCHINGPAREN, CMiniEditor::OnSelectMatchingParen)
    EVT_MENU(ID_AUTOCOMPLETE,        CMiniEditor::OnAutoComplete)
END_EVENT_TABLE()
