#include "editproceduredialog.h"

#include "localizedstrings.h"
#include "wrksp.h"  // for ledit

// ----------------------------------------------------------------------------
// CEditProcedureDialog
// ----------------------------------------------------------------------------

CEditProcedureDialog::CEditProcedureDialog(
    wxWindow * Parent
    )
    : CSelectProcedureDialog(Parent, LOCALIZED_EDITPROCEDURE)
{
}

void
CEditProcedureDialog::OnChoice(struct NODE * Procedures)
{
    ledit(Procedures);
}

BEGIN_EVENT_TABLE(CEditProcedureDialog, CSelectProcedureDialog)
END_EVENT_TABLE()
