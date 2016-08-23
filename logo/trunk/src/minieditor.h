// -*- c++ -*-

#ifndef _MINIEDITOR_H_
#define _MINIEDITOR_H_

#include <wx/dialog.h>

class CMiniEditorTextCtrl;

class CMiniEditor : public wxDialog
{
public:
    CMiniEditor(wxWindow *Parent, const char * ToLine);
    ~CMiniEditor();

    const wxString GetProcedureBody() const;

private:
    void OnFindMatchingParen(wxCommandEvent& Event);
    void OnSelectMatchingParen(wxCommandEvent& Event);
    void OnAutoComplete(wxCommandEvent& Event);

    CMiniEditorTextCtrl * m_TextField;

    DECLARE_EVENT_TABLE();
    DECLARE_NO_COPY_CLASS(CMiniEditor);
};

#endif // _MINIEDITOR_H_
