#ifndef _FONTUTILS_H_
#define _FONTUTILS_H_

#include <wx/font.h>

void
GetConfigurationFont(
    const char * ConfigName,
    wxFont &     Font
    );

void
SetConfigurationFont(
    const char *   ConfigName,
    const wxFont & Font
    );

const wxFont
GetLabelFont();

#endif // _FONTUTILS_H_
