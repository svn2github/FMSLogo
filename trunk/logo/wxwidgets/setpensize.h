// -*- c++ -*-

#include <wx/dialog.h>

class wxButton;

class CSetPenSize : public wxDialog
{
public:
    CSetPenSize(wxWindow *parent);

private:
    int m_PenWidth;

    wxWindow * m_ThicknessDisplay;

    DECLARE_EVENT_TABLE()
};
