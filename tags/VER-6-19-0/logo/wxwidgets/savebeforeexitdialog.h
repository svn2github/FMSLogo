// -*- c++ -*-

#include <wx/dialog.h>

class wxButton;

class CSaveBeforeExitDialog : public wxDialog
{
public:
    CSaveBeforeExitDialog(wxWindow *Parent);

    enum SAVEBEFOREEXIT
    {
        SAVEBEFOREEXIT_Cancel,
        SAVEBEFOREEXIT_ExitWithoutSaving,
        SAVEBEFOREEXIT_SaveAndExit,
    };

    void OnExitWithoutSaving(wxCommandEvent& event);
    void OnSaveBeforeExit(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);
    SAVEBEFOREEXIT GetExitCode();

private:
    SAVEBEFOREEXIT m_ExitStatus;

    DECLARE_EVENT_TABLE();
};
