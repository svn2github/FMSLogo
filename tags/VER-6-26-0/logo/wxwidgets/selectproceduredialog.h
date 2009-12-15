// -*- c++ -*-

#ifndef _SELECTPROCEDUREDIALOG_H_
#define _SELECTPROCEDUREDIALOG_H_

#include <wx/dialog.h>

class CSelectProcedureDialog : public wxDialog
{
public:
    CSelectProcedureDialog(wxWindow *Parent, const char * Caption);
    ~CSelectProcedureDialog();

    void OnClose(wxCloseEvent& event);

protected:
    virtual void OnChoice(struct NODE * Procedures) = 0;

private:
    bool m_FileEditAll;              // true if all procedures were selected
    char m_SelectedProcedures[256];  // buffer to hold selected procedure names
};

#endif // _SELECTPROCEDUREDIALOG_H_
