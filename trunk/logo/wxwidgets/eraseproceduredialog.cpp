#include "eraseproceduredialog.h"

#include "localizedstrings.h"
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
    // TODO: lerase(Procedures);
}

