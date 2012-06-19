#include "editproceduredialog.h"

#include "localizedstrings.h"
#include "wrksp.h"  // for ledit
#include "eval.h"   // for process_special_conditions

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
    // Open the procedure(s) in the editor.
    ledit(Procedures);

    // Handle any errors that may have occured.
    process_special_conditions();
}

BEGIN_EVENT_TABLE(CEditProcedureDialog, CSelectProcedureDialog)
END_EVENT_TABLE()
