// -*- c++ -*-

#include "selectproceduredialog.h"

class CEraseProcedureDialog : public CSelectProcedureDialog
{
public:
    CEraseProcedureDialog(wxWindow *Parent);

    void OnClose(wxCloseEvent& event);

    virtual void OnChoice(struct NODE * Procedures);
};
