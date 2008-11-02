#ifdef __WXMSW__
#  include <windows.h>  // for LOGFONT
#endif

#include <wx/fontutil.h>

#include "utils.h"

void
GetConfigurationFont(
    const char * ConfigName,
    wxFont &     Font
    )
{
#ifdef __WXMSW__
    LOGFONT nativeFont;
    GetConfigurationFont(ConfigName, nativeFont);

    // note: this was copied from wxNativeFontInfo::ToString() in src/msw/font.cpp
    wxString nativeInfo;
    nativeInfo.Printf(
        "%d;%ld;%ld;%ld;%ld;%ld;%d;%d;%d;%d;%d;%d;%d;%d;%s",
        0, // version
        nativeFont.lfHeight,
        nativeFont.lfWidth,
        nativeFont.lfEscapement,
        nativeFont.lfOrientation,
        nativeFont.lfWeight,
        nativeFont.lfItalic,
        nativeFont.lfUnderline,
        nativeFont.lfStrikeOut,
        nativeFont.lfCharSet,
        nativeFont.lfOutPrecision,
        nativeFont.lfClipPrecision,
        nativeFont.lfQuality,
        nativeFont.lfPitchAndFamily,
        nativeFont.lfFaceName);

    Font.SetNativeFontInfo(nativeInfo);
#else
    // TODO: figure out what to do on GNU/Linux
#endif
}


// Set this as the new default font
void
SetConfigurationFont(
    const char *   ConfigName,
    const wxFont & Font
    )
{
#ifdef __WXMSW__

    // Get the LOGFONT struct from the wxFont
    const wxNativeFontInfo * nativeFontInfo = Font.GetNativeFontInfo();
    if (nativeFontInfo != NULL)
    {
        // save the new font preference to persistent storage
        SetConfigurationFont(ConfigName, nativeFontInfo->lf);
    }
#else
    // TODO: figure out what to do on GNU/Linux
#endif
}
