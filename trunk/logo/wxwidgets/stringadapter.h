// -*- c++ -*-
#include <wx/setup.h>

// WXSTRING - converts from const char * to wxString
#if wxUSE_UNICODE
#define WXSTRING(STRING) wxString(STRING, wxConvLibc)
#else
#define WXSTRING(STRING) wxString(STRING)
#endif

// WXSTRING_TO_STRING - converts from wxString to const char *.
// Note: because there is data loss in the conversion, every instance
// of this macro should be considered a bug.
#if wxUSE_UNICODE
#define WXSTRING_TO_STRING(STRING) ((STRING).mb_str(wxConvLibc)).data()
#else
#define WXSTRING_TO_STRING(STRING) ((STRING).c_str())
#endif
