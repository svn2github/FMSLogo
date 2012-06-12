#ifdef __WXMSW__
#  include <windows.h>  // for LOGFONT
#endif

#include <wx/fontutil.h>

#include "utils.h"
#include "graphwin.h"

static
const wxFont
LogFontToWxFont(
    const LOGFONT & NativeLogicalFont
    )
{
    // note: this was copied from wxNativeFontInfo::ToString() in src/msw/font.cpp
    wxString nativeInfo;
    nativeInfo.Printf(
        "%d;%ld;%ld;%ld;%ld;%ld;%d;%d;%d;%d;%d;%d;%d;%d;%s",
        0, // version
        NativeLogicalFont.lfHeight,
        NativeLogicalFont.lfWidth,
        NativeLogicalFont.lfEscapement,
        NativeLogicalFont.lfOrientation,
        NativeLogicalFont.lfWeight,
        NativeLogicalFont.lfItalic,
        NativeLogicalFont.lfUnderline,
        NativeLogicalFont.lfStrikeOut,
        NativeLogicalFont.lfCharSet,
        NativeLogicalFont.lfOutPrecision,
        NativeLogicalFont.lfClipPrecision,
        NativeLogicalFont.lfQuality,
        NativeLogicalFont.lfPitchAndFamily,
        NativeLogicalFont.lfFaceName);

    wxFont font;
    font.SetNativeFontInfo(nativeInfo);

    return font;
}

void
GetConfigurationFont(
    const char * ConfigName,
    wxFont &     Font
    )
{
#ifdef __WXMSW__
    // Get the font
    LOGFONT nativeFont;
    GetConfigurationFont(ConfigName, nativeFont);

    // Convert it to a wxFont
    Font = LogFontToWxFont(nativeFont);
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

const wxFont
GetLabelFont()
{
    return LogFontToWxFont(FontRec);
}
