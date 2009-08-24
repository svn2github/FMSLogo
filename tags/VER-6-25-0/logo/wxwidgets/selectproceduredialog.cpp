#include "selectproceduredialog.h"

#include <wx/listbox.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/button.h>

#include "logocore.h"  // for ARRAYSIZE
#include "guiutils.h"
#include "localizedstrings.h"

// Menu IDs
enum
{
   ID_SELECTPROCEDUREDIALOG_ALL = wxID_HIGHEST,
   ID_SELECTPROCEDUREDIALOG_OK,
};

// ----------------------------------------------------------------------------
// CSelectProcedureDialog
// ----------------------------------------------------------------------------

CSelectProcedureDialog::CSelectProcedureDialog(
    wxWindow * Parent, 
    const char * Caption
    )
    : wxDialog(
        Parent,
        wxID_ANY,
        wxString(Caption),
        wxDefaultPosition,
        wxDefaultSize, 
        wxCAPTION | wxCLOSE_BOX |wxDEFAULT_DIALOG_STYLE)
{
    wxBoxSizer *topLevelSizer = new wxBoxSizer(wxVERTICAL);

    // add the text input
    wxTextCtrl *procedureName = new wxTextCtrl(
        this,
        wxID_ANY);
    topLevelSizer->Add(
        procedureName,
        0,
        wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT | wxEXPAND,
        15);

    // add the procedures list
    wxListBox * allProcedures = new wxListBox(
        this,
        wxID_ANY);
    topLevelSizer->Add(
        allProcedures,
        0,
        wxALIGN_CENTER | wxBOTTOM | wxLEFT | wxRIGHT | wxEXPAND,
        15);


    // add the row of buttons
    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    static const MENUITEM buttonInfo[] = {
        {LOCALIZED_SELECTPROCEDURE_OK,     ID_SELECTPROCEDUREDIALOG_OK},
        {LOCALIZED_SELECTPROCEDURE_ALL,    ID_SELECTPROCEDUREDIALOG_ALL},
        {LOCALIZED_SELECTPROCEDURE_CANCEL, wxID_CANCEL},
    };


    // HACK: 
    // Create and destroy each button to get the width and height
    // of the "exact fit" size of the largest button.  We will
    // use this size when we recreate the buttons later.
    // Ideally, we'd just be able to resize the buttons, but I haven't
    // figured out how to do that.
    int maxHeight = 0;
    int maxWidth  = 0;
    for (size_t i = 0; i < ARRAYSIZE(buttonInfo); i++)
    {
        wxButton * button = new wxButton(
            this,
            buttonInfo[i].MenuId,
            buttonInfo[i].MenuText,
            wxDefaultPosition,
            wxDefaultSize,
            wxBU_EXACTFIT);

        if (maxWidth < button->GetBestSize().GetWidth())
        {
            maxWidth = button->GetBestSize().GetWidth();
        }

        if (maxHeight < button->GetBestSize().GetHeight())
        {
            maxHeight = button->GetBestSize().GetHeight();
        }

        delete button;
    }

    // create of the buttons to be the same size.
    const wxSize buttonSize(maxWidth, maxHeight);
    for (size_t i = 0; i < ARRAYSIZE(buttonInfo); i++)
    {
        wxButton * button = new wxButton(
            this,
            buttonInfo[i].MenuId,
            buttonInfo[i].MenuText,
            wxDefaultPosition,
            buttonSize);

        buttonSizer->Add(
            button,
            0,
            wxALIGN_CENTER | wxLEFT | wxRIGHT,
            5);
    }


    topLevelSizer->Add(
        buttonSizer,
        0,
        wxALIGN_CENTER | wxBOTTOM | wxLEFT | wxRIGHT,
        15);

    SetSizer(topLevelSizer);
    topLevelSizer->Fit(this);
}

CSelectProcedureDialog::~CSelectProcedureDialog()
{
}
