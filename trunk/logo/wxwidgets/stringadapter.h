// -*- c++ -*-
#include <wx/setup.h>

// WXSTRING - converts from const char * to wxString
#if wxUSE_UNICODE
#define WXSTRING(STRING) wxString(STRING, wxConvLibc)
#else
#define WXSTRING(STRING) wxString(STRING)
#endif

// WXSTRING_TO_STRING - converts from wxString to const char *.
#if wxUSE_UNICODE
#define WXSTRING_TO_STRING(STRING) ((STRING).mb_str(wxConvLibc)).data()
#else
#define WXSTRING_TO_STIRNG(STRING) ((STRING).c_str())
#endif
