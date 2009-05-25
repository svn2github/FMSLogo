// -*- c++ -*-

#ifndef _MINIEDITOR_H_
#define _MINIEDITOR_H_

#include <wx/dialog.h>

class wxButton;
class wxTextCtrl;
class wxRichTextCtrl;

class CMiniEditor : public wxDialog
{
public:
    CMiniEditor(wxWindow *Parent, const char * ToLine);
    ~CMiniEditor();

private:
    wxRichTextCtrl * m_TextField;
    wxTextCtrl     * m_ToLine;
    wxButton       * m_EndButton;

    wxString m_ToLineString;
    wxString m_EditorContents;
};

#endif // _MINIEDITOR_H_
