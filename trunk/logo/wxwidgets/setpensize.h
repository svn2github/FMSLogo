// -*- c++ -*-

#include <wx/dialog.h>

class wxButton;

class CSetPenSize : public wxDialog
{
    // private class for the window that set the pen size
    class CPenSizeWindow : public wxWindow
    {
    public:
        CPenSizeWindow(
            CSetPenSize   * Parent,
            wxWindowID      Id,
            const wxPoint & Pos,
            const wxSize  & Size,
            int             PenSize
           );

        void OnPaint(wxPaintEvent & event);
        void OnClick(wxMouseEvent & event);

        void SetPenSize(int PenSize);

    private:
        int m_PenWidth;

        DECLARE_EVENT_TABLE()
    };

public:
    CSetPenSize(
        wxWindow    *   Parent,
        int             InitialPenSize,
        CSetPenSize * & ExternalReference
        );

    void SetPenSize(int PenSize);

    void OnOkButton(wxCommandEvent& event);
    void OnCancelButton(wxCommandEvent& event);
    void OnSliderUpdated(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);

private:
    int m_PenWidth;

    CSetPenSize    * & m_ExternalReference;
    CPenSizeWindow *   m_ThicknessDisplay;
    wxSlider       *   m_ThicknessSlider;

    DECLARE_EVENT_TABLE()
};
