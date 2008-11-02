#include "setactivearea.h"

#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

#include "localizedstrings.h"

// ----------------------------------------------------------------------------
// CSetActiveArea
// ----------------------------------------------------------------------------

static int g_PrinterAreaXLow   = -500;
static int g_PrinterAreaXHigh  =  500;
static int g_PrinterAreaYLow   = -500;
static int g_PrinterAreaYHigh  =  500;
static int g_PrinterAreaPixels =  125;

enum ID_COMMANDER
{
    ID_PIXELSPERINCH = wxID_HIGHEST,
};

CSetActiveArea::CSetActiveArea(wxWindow *parent)
    : wxDialog(parent, wxID_ANY, wxString(LOCALIZED_SELECTACTIVEAREA)),
      m_XLow(g_PrinterAreaXLow),
      m_XHigh(g_PrinterAreaXHigh),
      m_YLow(g_PrinterAreaYLow),
      m_YHigh(g_PrinterAreaYHigh),
      m_PixelsPerInch(g_PrinterAreaPixels)
{

    wxBoxSizer *topLevelSizer = new wxBoxSizer(wxVERTICAL);

    // The "body" of this dialog box: 
    // the group box that holds the dimensions of the active area.
    const wxSize  boxSize(168, 144);
    wxStaticBox *box = new wxStaticBox(
        this,
        wxID_ANY,
        "",
        wxDefaultPosition,
        boxSize);
    topLevelSizer->Add(box, 0, wxALIGN_CENTER | wxEXPAND | wxALL, 5);

    // The contents of the main group box are too complex for any of the
    // sizer classes.  Therefore, we must do the layout the old-fashioned
    // way, by specifying x,y coordinates and size (width, height) of each 
    // widget.
    const wxPoint effectPosition(40, 16);
    new wxStaticText(
        this,
        wxID_ANY,
        LOCALIZED_SELECTACTIVEAREA_EFFECT,
        effectPosition,
        wxDefaultSize,
        wxALIGN_CENTRE);

    // draw the cross-hairs
    const wxPoint verticalLinePosition(effectPosition.x + 105, effectPosition.y + 58);
    const wxSize  verticalLineSize(2, 44);
    new wxStaticLine(
        this,
        wxID_ANY,
        verticalLinePosition,
        verticalLineSize,
        wxLI_VERTICAL);

    const wxPoint horizontalLinePosition(effectPosition.x + 60, effectPosition.y + 78);
    const wxSize  horizontalLineSize(88, 2);
    new wxStaticLine(
        this,
        wxID_ANY,
        horizontalLinePosition,
        horizontalLineSize,
        wxLI_HORIZONTAL);


    const wxPoint yHighTextPosition(effectPosition.x + 32, effectPosition.y + 38);
    new wxStaticText(
        this,
        wxID_ANY,
        LOCALIZED_SELECTACTIVEAREA_YHIGH,
        yHighTextPosition,
        wxDefaultSize,
        wxALIGN_CENTRE);

    const wxPoint xLowTextPosition(effectPosition.x + 8, effectPosition.y + 52);
    new wxStaticText(
        this,
        wxID_ANY,
        LOCALIZED_SELECTACTIVEAREA_XLOW,
        xLowTextPosition,
        wxDefaultSize,
        wxALIGN_CENTRE);

    const wxPoint xHighTextPosition(effectPosition.x + 150, effectPosition.y + 52);
    new wxStaticText(
        this,
        wxID_ANY,
        LOCALIZED_SELECTACTIVEAREA_XHIGH,
        xHighTextPosition,
        wxDefaultSize,
        wxALIGN_CENTRE);

    const wxPoint yLowTextPosition(effectPosition.x + 32, effectPosition.y + 105);
    new wxStaticText(
        this,
        wxID_ANY,
        LOCALIZED_SELECTACTIVEAREA_YLOW,
        yLowTextPosition,
        wxDefaultSize,
        wxALIGN_CENTRE);



    wxString yHighInputValue;
    yHighInputValue.Printf("%d", m_YHigh);

    const wxPoint yHighInputPosition(effectPosition.x + 80, effectPosition.y + 35);
    wxTextCtrl *yHighInput = new wxTextCtrl(
        this,
        wxID_ANY,
        yHighInputValue,
        yHighInputPosition,
        wxDefaultSize);
    // keep this input small--it should only hold 3-4 characters
    yHighInput->SetSize(50, yHighInput->GetSize().GetHeight());


    wxString xLowInputValue;
    xLowInputValue.Printf("%d", m_XLow);

    const wxPoint xLowInputPosition(effectPosition.x + 8, effectPosition.y + 68);
    wxTextCtrl *xLowInput = new wxTextCtrl(
        this,
        wxID_ANY,
        xLowInputValue,
        xLowInputPosition,
        wxDefaultSize);
    // keep this input small--it should only hold 3-4 characters
    xLowInput->SetSize(50, xLowInput->GetSize().GetHeight());


    wxString xHighInputValue;
    xHighInputValue.Printf("%d", m_XHigh);

    const wxPoint xHighInputPosition(effectPosition.x + 150, effectPosition.y + 68);
    wxTextCtrl *xHighInput = new wxTextCtrl(
        this,
        wxID_ANY,
        xHighInputValue,
        xHighInputPosition,
        wxDefaultSize);
    // keep this input small--it should only hold 3-4 characters
    xHighInput->SetSize(50, xHighInput->GetSize().GetHeight());



    wxString yLowInputValue;
    yLowInputValue.Printf("%d", m_YLow);

    const wxPoint yLowInputPosition(effectPosition.x + 80, effectPosition.y + 103);
    wxTextCtrl *yLowInput = new wxTextCtrl(
        this,
        wxID_ANY,
        yLowInputValue,
        yLowInputPosition,
        wxDefaultSize);
    // keep this input small--it should only hold 3-4 characters
    yLowInput->SetSize(50, yLowInput->GetSize().GetHeight());






    //
    // the "pixels per inch" row
    //
    wxBoxSizer *pixelsPerInchRow = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText *pixelsPerInchLabel = new wxStaticText(
        this,
        wxID_ANY,
        LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH);
    pixelsPerInchRow->Add(pixelsPerInchLabel, 0, wxALIGN_RIGHT | wxFIXED_MINSIZE | wxALIGN_CENTER_VERTICAL, 5);

    wxTextCtrl *pixelsPerInchInput = new wxTextCtrl(
        this,
        ID_PIXELSPERINCH,
        "");
    // keep this input small--it should only hold 3-4 characters
    pixelsPerInchInput->SetSize(50, pixelsPerInchInput->GetSize().GetHeight());
    pixelsPerInchRow->Add(pixelsPerInchInput, 0, wxALIGN_RIGHT | wxFIXED_MINSIZE  | wxALIGN_CENTER_VERTICAL | wxALL, 5);

    topLevelSizer->Add(pixelsPerInchRow, 0, wxALIGN_RIGHT);


    //
    // the row of buttons at the bottom: Reset | Cancel | Ok
    //
    wxBoxSizer *buttonRow = new wxBoxSizer(wxHORIZONTAL);

    wxButton *reset = new wxButton(
        this, 
        wxID_ANY, 
        LOCALIZED_SELECTACTIVEAREA_RESET);
    buttonRow->Add(reset, 0, wxALIGN_CENTER | wxALL, 10);

    wxButton *cancel = new wxButton(
        this, 
        wxID_CANCEL, 
        LOCALIZED_SELECTACTIVEAREA_CANCEL);
    buttonRow->Add(cancel, 0, wxALIGN_CENTER | wxALL, 10);

    wxButton *ok = new wxButton(
        this, 
        wxID_ANY,
        LOCALIZED_SELECTACTIVEAREA_OK);
    buttonRow->Add(ok, 0, wxALIGN_CENTER | wxALL, 10);

    topLevelSizer->Add(buttonRow, 0, wxALIGN_CENTER | wxALL);



    // make the "Ok" button the default
    ok->SetFocus();
    ok->SetDefault();

    SetSizer(topLevelSizer);

    topLevelSizer->SetSizeHints(this);
    topLevelSizer->Fit(this);

    Fit();
}
