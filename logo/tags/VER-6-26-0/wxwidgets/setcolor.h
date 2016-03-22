// -*- c++ -*-

#include <wx/dialog.h>

class wxButton;
class wxSlider;

class CSetColor : public wxDialog
{
    // private class for the colored rectangles that can set
    // the color when they are clicked.
    class CColorWindow : public wxWindow
    {
    public:
        CColorWindow(
            CSetColor      * Parent,
            wxWindowID       Id,
            const wxPoint  & Pos,
            const wxSize   & Size,
            const wxColour & Color
           );

        void OnClick(wxMouseEvent & Event);

        void SetColor(const wxColour & NewColor);

    private:
        DECLARE_EVENT_TABLE()
    };

public:
    CSetColor(
        wxWindow  *     Parent,
        const char *    WindowTitle,
        const wxColor & InitialColor,
        CSetColor * &   ExternalReference
        );

    void SetColor(const wxColor & NewColor);

    void OnOkButton(wxCommandEvent& Event);
    void OnCancelButton(wxCommandEvent& Event);
    void OnSliderUpdated(wxCommandEvent& Event);
    void OnClose(wxCloseEvent& Event);

private:
    CSetColor    * & m_ExternalReference;

    wxSlider     * m_RedSlider;
    wxSlider     * m_GreenSlider;
    wxSlider     * m_BlueSlider;
    CColorWindow * m_SelectedColor;
    const char   * m_LogoCommand;

    DECLARE_EVENT_TABLE()
};
