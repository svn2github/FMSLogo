// -*- c++ -*-

#include <wx/dialog.h>

class wxButton;

class CSetActiveArea : public wxDialog
{
public:
    CSetActiveArea(wxWindow *parent);

private:
    int m_XLow;
    int m_XHigh;
    int m_YLow;
    int m_YHigh;

    int m_PixelsPerInch;
};
