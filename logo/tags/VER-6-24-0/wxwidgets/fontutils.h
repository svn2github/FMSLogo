#ifndef _FONTUTILS_H_
#define _FONTUTILS_H_

class wxFont;

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

#endif // _FONTUTILS_H_

