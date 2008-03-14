#include "editproceduredialog.h"

#include "localizedstrings.h"
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
    // TODO: ledit(Procedures);
}

