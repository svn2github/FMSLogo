#include "eraseproceduredialog.h"

#include "localizedstrings.h"
#include "wrksp.h"  // for lerase

// ----------------------------------------------------------------------------
// CEraseProcedureDialog
// ----------------------------------------------------------------------------

CEraseProcedureDialog::CEraseProcedureDialog(
    wxWindow * Parent
    )
    : CSelectProcedureDialog(Parent, LOCALIZED_ERASEPROCEDURE)
{
}

void
CEraseProcedureDialog::OnChoice(struct NODE * Procedures)
{
    lerase(Procedures);
}

BEGIN_EVENT_TABLE(CEraseProcedureDialog, CSelectProcedureDialog)
END_EVENT_TABLE()
