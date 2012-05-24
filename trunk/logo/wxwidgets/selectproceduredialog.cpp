#include "selectproceduredialog.h"

#include <wx/listbox.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/button.h>

#include "logocore.h"      // for ARRAYSIZE
#include "wrksp.h"         // for lprocedures
#include "argumentutils.h" // for cnv_strnode_string
#include "logodata.h"      // formake_strnode
#include "screenwindow.h"  // for TraceOutput
#include "guiutils.h"
#include "localizedstrings.h"

// Control IDs
enum
{
   ID_PROCEDURETEXT = wxID_HIGHEST,
   ID_PROCEDURELIST,
   ID_ALL,
};

// ----------------------------------------------------------------------------
// CSelectProcedureDialog
// ----------------------------------------------------------------------------

CSelectProcedureDialog::CSelectProcedureDialog(
    wxWindow   * Parent, 
    const char * Caption
    )
    : wxDialog(
        Parent,
        wxID_ANY,
        wxString(Caption),
        wxDefaultPosition,
        wxDefaultSize, 
        wxCAPTION | wxCLOSE_BOX | wxDEFAULT_DIALOG_STYLE),
      m_SelectedProcedures(NULL),
      m_ProcedureList(NULL)
{
    wxBoxSizer *topLevelSizer = new wxBoxSizer(wxVERTICAL);

    // add the text input
    m_SelectedProcedures = new wxTextCtrl(this, ID_PROCEDURETEXT);
    topLevelSizer->Add(
        m_SelectedProcedures,
        0,
        wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT | wxEXPAND,
        15);

    // add the procedures list
    wxListBox * m_ProcedureList = new wxListBox(this, ID_PROCEDURELIST);

    // get procedures
    NODE * proclist = lprocedures(NIL);

    // put the name of each procedure into the list box
    for (NODE* proclist_node = proclist;
         proclist_node != NIL;
         proclist_node = cdr(proclist_node))
    {
        char tempbuff[MAX_BUFFER_SIZE];
        cnv_strnode_string(tempbuff, proclist_node);

        m_ProcedureList->Append(tempbuff);
    }

    gcref(proclist);

    topLevelSizer->Add(
        m_ProcedureList,
        0,
        wxALIGN_CENTER | wxBOTTOM | wxLEFT | wxRIGHT | wxEXPAND,
        15);

    // add the row of buttons
    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    static const MENUITEM buttonInfo[] = {
        {LOCALIZED_SELECTPROCEDURE_OK,     wxID_OK},
        {LOCALIZED_SELECTPROCEDURE_ALL,    ID_ALL},
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
            wxID_ANY,
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

    // create all of the buttons to be the same size.
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

        // Make the "OK" button the default.
        if (buttonInfo[i].MenuId == wxID_OK)
        {
            button->SetDefault();
        }
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

void CSelectProcedureDialog::DoDialog()
{
    // Show the dialog as a modal box
    int returnCode = ShowModal();
    switch (returnCode)
    {
    case wxID_OK:
    case ID_ALL:

        NODE *arg;
        if (returnCode == ID_ALL)
        {
            // The user clicked ALL get all procedures
            arg = lprocedures(NIL);
        }
        else
        {
            // else find what user selected
            arg = cons_list(make_strnode(m_SelectedProcedures->GetValue().c_str()));
        }

        // if something edit it
        if (arg != NIL) 
        {
            OnChoice(arg);
        }

        gcref(arg);
        break;

    default:
        // The user canceled the dialog
        break;
    }
}

void CSelectProcedureDialog::OnAll(wxCommandEvent& Event)
{
    SetReturnCode(ID_ALL);
    Destroy();
}

void CSelectProcedureDialog::OnProcedureSelect(wxCommandEvent& Event)
{
}

void CSelectProcedureDialog::OnProcedureDoubleClick(wxCommandEvent& Event)
{
}

BEGIN_EVENT_TABLE(CSelectProcedureDialog, wxDialog)
    EVT_BUTTON(ID_ALL,                   CSelectProcedureDialog::OnAll)
    EVT_LISTBOX(ID_PROCEDURELIST,        CSelectProcedureDialog::OnProcedureSelect)
    EVT_LISTBOX_DCLICK(ID_PROCEDURELIST, CSelectProcedureDialog::OnProcedureDoubleClick)
END_EVENT_TABLE()
