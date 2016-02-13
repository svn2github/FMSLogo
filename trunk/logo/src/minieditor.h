// -*- c++ -*-

#ifndef _MINIEDITOR_H_
#define _MINIEDITOR_H_

#include <wx/dialog.h>

class wxRichTextCtrl;

class CMiniEditor : public wxDialog
{
public:
    CMiniEditor(wxWindow *Parent, const char * ToLine);
    ~CMiniEditor();

    const wxString GetProcedureBody() const;

private:

    wxRichTextCtrl * m_TextField;

    DECLARE_NO_COPY_CLASS(CMiniEditor);
};

#endif // _MINIEDITOR_H_
