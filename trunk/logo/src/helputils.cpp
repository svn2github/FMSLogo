#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include "helputils.h"

   #include <wx/string.h>

   #include "logocore.h" // for IsSpace
   #include "graphwin.h" // for do_help
   #include "stringadapter.h"
#endif


// Open the help to the topic specified in the first word of SelectedText.
void ContextHelp(const wxString & SelectedText)
{
    const char * src = WXSTRING_TO_STRING(SelectedText);

    // remove leading whitespace
    while (IsSpace(*src))
    {
        src++;
    }

    // Copy the first word (up until the first whitespace character)
    // to a separate buffer that can be NULL-terminated.
    char buffer[100];
    char * dest      = buffer;
    char * destLimit = buffer + sizeof(buffer) - 1;
    while (*src != '\0' && !IsSpace(*src) && dest < destLimit)
    {
        *dest++ = *src++;
    }

    // Truncate the selection after the first word.
    *dest = '\0';

    // Look it up in the online help.
    do_help(buffer);
}

