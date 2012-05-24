// -*- c++ -*-

#ifndef _SELECTPROCEDUREDIALOG_H_
#define _SELECTPROCEDUREDIALOG_H_

#include <wx/dialog.h>

class CSelectProcedureDialog : public wxDialog
{
public:
    CSelectProcedureDialog(wxWindow *Parent, const char * Caption);
    ~CSelectProcedureDialog();

    void DoDialog();

protected:
    virtual void OnChoice(struct NODE * Procedures) = 0;

private:
    // event handlers
    void OnAll(wxCommandEvent& Event);
    void OnProcedureSelect(wxCommandEvent& Event);
    void OnProcedureDoubleClick(wxCommandEvent& Event);

    // member variables
    class wxTextCtrl * m_SelectedProcedures;
    class wxListBox  * m_ProcedureList;

    DECLARE_NO_COPY_CLASS(CSelectProcedureDialog);
    DECLARE_EVENT_TABLE();
};

#endif // _SELECTPROCEDUREDIALOG_H_
