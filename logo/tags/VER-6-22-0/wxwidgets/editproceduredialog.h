// -*- c++ -*-

#include "selectproceduredialog.h"

class CEditProcedureDialog : public CSelectProcedureDialog
{
public:
    CEditProcedureDialog(wxWindow *Parent);

    void OnClose(wxCloseEvent& event);

    virtual void OnChoice(struct NODE * Procedures);
};
