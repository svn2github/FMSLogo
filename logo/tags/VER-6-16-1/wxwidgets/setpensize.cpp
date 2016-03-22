#include "setpensize.h"

#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/stattext.h>

#include "logocore.h"
#include "localizedstrings.h"

// ----------------------------------------------------------------------------
// CSetPenSize
// ----------------------------------------------------------------------------

enum ID_SETPENSIZE
{
    ID_SETPENSIZE_PIXELSPERINCH = wxID_HIGHEST,
    ID_SETPENSIZE_SLIDER,
    ID_SETPENSIZE_OK,
    ID_SETPENSIZE_APPLY,
    ID_SETPENSIZE_SIZE1,
    ID_SETPENSIZE_SIZE2,
    ID_SETPENSIZE_SIZE3,
    ID_SETPENSIZE_SIZE4,
    ID_SETPENSIZE_SIZE5,
    ID_SETPENSIZE_SIZE6,
    ID_SETPENSIZE_SIZE7,
    ID_SETPENSIZE_SIZE8,
};

CSetPenSize::CSetPenSize(wxWindow *Parent)
    : wxDialog(Parent, wxID_ANY, wxString(LOCALIZED_SETPENSIZE)),
      m_PenWidth(1)
{
    wxBoxSizer *topLevelSizer = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer *thicknessSettingSizer = new wxStaticBoxSizer(wxVERTICAL, this);


    //
    // Add the left-hand pane, which has thickness setting by picture on
    // the top and thickness setting by slider on the bottom.
    //
    topLevelSizer->Add(
        thicknessSettingSizer,
        0,
        wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALL,
        5);


    //
    // Add the row of computed size selector pictures
    //
    wxBoxSizer *thicknessByPictures = new wxBoxSizer(wxHORIZONTAL);

    static const struct {
        int  ChildId;
        int  PenWidth;
    } data[] = {
        {ID_SETPENSIZE_SIZE1, 1},
        {ID_SETPENSIZE_SIZE2, 2},
        {ID_SETPENSIZE_SIZE3, 3},
        {ID_SETPENSIZE_SIZE4, 4},
        {ID_SETPENSIZE_SIZE5, 6},
        {ID_SETPENSIZE_SIZE6, 8},
        {ID_SETPENSIZE_SIZE7, 16},
        {ID_SETPENSIZE_SIZE8, 32},
    };

    for (size_t i = 0; i < ARRAYSIZE(data); i++)
    {
        wxWindow * picture = new wxWindow(
            this,
            data[i].ChildId, 
            wxDefaultPosition,
            wxSize(30, 30));

        picture->SetBackgroundColour(*wxWHITE);

        wxWindowDC dc(picture);
        dc.SetPen(*wxBLACK_PEN);
        dc.SetBrush(*wxGREEN_BRUSH);
        dc.DrawRectangle(120, 120, 100, 80);

        thicknessByPictures->Add(picture, 0, wxALIGN_CENTER | wxALL, 5);
    }
    thicknessSettingSizer->Add(
        thicknessByPictures,
        0,
        wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALL,
        5);


    thicknessSettingSizer->AddSpacer(10);

    //
    // Add the row of computed size selector pictures
    //
    wxBoxSizer *thicknessBySlider = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *thicknessText = new wxStaticText(
        this,
        wxID_ANY,
        LOCALIZED_SETPENSIZE_SIZE,
        wxDefaultPosition,
        wxDefaultSize,
        wxALIGN_CENTRE);
    thicknessBySlider->Add(
        thicknessText,
        0,
        wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALL,
        5);

    wxSlider * slider = new wxSlider(
        this,
        ID_SETPENSIZE_SLIDER,
        m_PenWidth, 
        1,
        32,
        wxDefaultPosition,
        wxSize(250, 24),
        wxSL_HORIZONTAL);
    thicknessBySlider->Add(
        slider,
        0,
        wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALL,
        5);

    thicknessSettingSizer->Add(
        thicknessBySlider, 
        0, 
        wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxEXPAND | wxALL,
        5);



    //
    // the column with the thickness display, the OK, Cancel, and Apply buttons
    //
    wxBoxSizer *buttonColumn = new wxBoxSizer(wxVERTICAL);

    m_ThicknessDisplay = new wxWindow(
        this,
        wxID_ANY,
        wxDefaultPosition,
        wxSize(40, 40));
    m_ThicknessDisplay->SetBackgroundColour(*wxWHITE);
    buttonColumn->Add(m_ThicknessDisplay, 0, wxALIGN_CENTER | wxALL, 10);

    wxButton *ok = new wxButton(
        this, 
        wxID_ANY, 
        LOCALIZED_SETPENSIZE_OK);
    buttonColumn->Add(ok, 0, wxALIGN_CENTER | wxALL, 5);

    wxButton *cancel = new wxButton(
        this, 
        wxID_CANCEL, 
        LOCALIZED_SETPENSIZE_CANCEL);
    buttonColumn->Add(cancel, 0, wxALIGN_CENTER | wxALL, 5);

    wxButton *apply = new wxButton(
        this, 
        wxID_ANY,
        LOCALIZED_SETPENSIZE_APPLY);
    buttonColumn->Add(apply, 0, wxALIGN_CENTER | wxALL, 5);

    topLevelSizer->Add(buttonColumn, 0, wxALIGN_CENTER | wxALL, 5);


    // make the "Ok" button the default
    ok->SetFocus();
    ok->SetDefault();

    SetSizer(topLevelSizer);

    topLevelSizer->SetSizeHints(this);
    topLevelSizer->Fit(this);

    Fit();
}

BEGIN_EVENT_TABLE(CSetPenSize, wxDialog)
END_EVENT_TABLE()
