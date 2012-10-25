/*
 *  Copyright (C) 1995 by the Regents of the University of California
 *  Copyright (C) 1995 by George Mills
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifndef WX_PURE
#include <windows.h>

#ifdef max // MS compilers #define max in windows.h
#undef max
#endif
#endif

#include <algorithm>
#include <string.h>

#include "startup.h"
#include "activearea.h"
#include "graphwin.h"
#include "utils.h"
#include "main.h"
#include "debugheap.h"

#include "localizedstrings.h"

#ifdef WX_PURE
#define MAX_PATH 260
#endif

Color dfld;                        // Current flood color
Color dscn;                        // Current screen color

char LibPathName[MAX_PATH + 1];    // path to library
char TempPathName[MAX_PATH + 1];   // path to temp edit file
char TempBmpName[MAX_PATH + 1];    // path to temp bitmap file
char TempClipName[MAX_PATH + 1];   // path to temp clipboard file
char szHelpFileName[MAX_PATH + 1]; // path to help file

#ifndef WX_PURE
COLORREF scolor;                   // screen color
COLORREF fcolor;                   // flood color
COLORREF pcolor;                   // pen color

OSVERSIONINFO g_OsVersionInformation;
#endif

char g_FmslogoBaseDirectory[MAX_PATH+1]; // The directory that contains FMSLogo.exe

// Creates path relative to the directory from to which FMSLogo is installed.
void MakeHelpPathName(char *OutBuffer, const char * TheFileName)
{
    strncpy(OutBuffer, g_FmslogoBaseDirectory, MAX_PATH);
    strncat(OutBuffer, TheFileName,            MAX_PATH - strlen(OutBuffer));
}

// Creates a unique filename relative to TempPath
static
void MakeTempFilename(char *OutBuffer, const char * TempPath, const char * FileName)
{
    // the first part of the temp filename is TempPath
    char * ptr       = OutBuffer;
    const char * src = TempPath;
    while (*src != '\0')
    {
        *ptr++ = *src++;
    }

    // make sure that the path ends in a directory delimiter
    if (*ptr != '\\')
    {
        *ptr++ = '\\';
    }
   
    // append the filename
    strcpy(ptr, FileName);
}


void init_osversion()
{
#ifndef WX_PURE
    memset(&g_OsVersionInformation, 0, sizeof g_OsVersionInformation);
    g_OsVersionInformation.dwOSVersionInfoSize = sizeof g_OsVersionInformation;
    GetVersionEx(&g_OsVersionInformation);
#endif
}


void init_graphics()
{
#ifndef WX_PURE
    // set appropriate default colors
    pcolor = 0x00000000;
    scolor = 0x00FFFFFF;
    fcolor = 0x00000000;
#endif

    dfld.red   = 0x00;
    dfld.green = 0x00;
    dfld.blue  = 0x00;

    dscn.red   = 0xFF;
    dscn.green = 0xFF;
    dscn.blue  = 0xFF;

    // initialize the global pen state
#ifndef WX_PURE
    // init the font structure
    FontRec.lfHeight         = 24;
    FontRec.lfWidth          = 0;
    FontRec.lfOrientation    = 0;
    FontRec.lfWeight         = 400;
    FontRec.lfItalic         = 0;
    FontRec.lfUnderline      = 0;
    FontRec.lfStrikeOut      = 0;
    FontRec.lfCharSet        = ANSI_CHARSET;
    FontRec.lfOutPrecision   = OUT_DEFAULT_PRECIS;
    FontRec.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
    FontRec.lfQuality        = DEFAULT_QUALITY;
    FontRec.lfPitchAndFamily = DEFAULT_PITCH;
    strcpy(FontRec.lfFaceName, "Arial");

    FloodBrush.lbStyle = BS_SOLID;
    FloodBrush.lbColor = fcolor;
    FloodBrush.lbHatch = HS_VERTICAL;

    ScreenBrush.lbStyle = BS_SOLID;
    ScreenBrush.lbColor = scolor;
    ScreenBrush.lbHatch = HS_VERTICAL;

    // Set handy rectangle of full bitmap
    SetRect(&FullRect, 0, 0, BitMapWidth, BitMapHeight);
#endif

    // turtle coords are in center
    xoffset = BitMapWidth  / 2;
    yoffset = BitMapHeight / 2;

    // Init active area even if off
    g_PrinterAreaXLow  = -BitMapWidth  / 2;
    g_PrinterAreaXHigh = +BitMapWidth  / 2;
    g_PrinterAreaYLow  = -BitMapHeight / 2;
    g_PrinterAreaYHigh = +BitMapHeight / 2;

    g_PrinterAreaPixels = std::max(BitMapWidth, BitMapHeight) / 8;

    // init paths to library and help files based on location of .EXE
    MakeHelpPathName(LibPathName,     "logolib\\");
    MakeHelpPathName(szHelpFileName,  "logohelp.chm");

#ifdef WX_PURE
    const char * tempPath = getenv("TMP");
    if (tempPath == NULL)
    {
        tempPath = "~";
    }
#else
    DWORD tempPathLength;
    char  tempPath[MAX_PATH];
    bool  tempPathIsValid = false;

    tempPathLength = GetTempPath(
        sizeof tempPath,
        tempPath);
    if (tempPathLength != 0)
    {
        DWORD tempPathAttributes = GetFileAttributes(tempPath);
        if (tempPathAttributes != 0xFFFFFFFF)
        {
            // tempPath must be a directory that we can write to
            if ( (tempPathAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
                 !(tempPathAttributes & FILE_ATTRIBUTE_READONLY))
            {
                tempPathIsValid = true;
            }
        }
    }

    if (!tempPathIsValid)
    {
        // warn the user that no TMP variable was defined.
        MessageBox(
            0,
            LOCALIZED_ERROR_TMPNOTDEFINED,
            LOCALIZED_WARNING,
            MB_OK);

        strcpy(tempPath, "C:");
    }
#endif

    // construct the name of the temporary editor file
    MakeTempFilename(TempPathName, tempPath, "mswlogo.tmp");

    // construct the name of the temporary bitmap file
    MakeTempFilename(TempBmpName, tempPath, "mswlogo.bmp");

    // construct the name of the clipboard file
    MakeTempFilename(TempClipName, tempPath, "mswlogo.clp");

    g_PrinterAreaXLow   = GetConfigurationInt("Printer.Xlow",  -BitMapWidth  / 2);
    g_PrinterAreaXHigh  = GetConfigurationInt("Printer.XHigh", +BitMapWidth  / 2);
    g_PrinterAreaYLow   = GetConfigurationInt("Printer.Ylow",  -BitMapHeight / 2);
    g_PrinterAreaYHigh  = GetConfigurationInt("Printer.YHigh", +BitMapHeight / 2);
    g_PrinterAreaPixels = GetConfigurationInt("Printer.Pixels", std::max(BitMapWidth, BitMapHeight) / 8);
}

#ifndef WX_PURE
// Best-effort to disable Data Execution Protection.
//
// In general, programs shouldn't disable DEP because that would leave
// their users prone to some buffer-overflow attacks.  However, OWL
// uses some self-modifying code its window message handling.  When
// Windows sees this happening, it assumes the worst--that some buffer
// overrun has been exploited--and terminates the program.
//
// For backward-compatibility reasons, Microsoft published an API that
// allows 32-bit applications to disable DEP on a per-instance basis.
// This is not available in all operating systems, so it is called
// through GetProcAddress() on a best-effort basis.  In the worst case,
// DEP will be enabled on FMSLogo, FMSLogo won't be able to disable
// it, and it will crash (that is, we're no worse off than before).
const DWORD PROCESS_DEP_DISABLE                     = 0x00000000;

#if !defined PROCESS_DEP_ENABLE
  const DWORD PROCESS_DEP_ENABLE                      = 0x00000001;
#endif

#if !defined PROCESS_DEP_DISABLE_ATL_THUNK_EMULATION
  const DWORD PROCESS_DEP_DISABLE_ATL_THUNK_EMULATION = 0x00000002;
#endif

void DisableDataExecutionProtection()
{

    typedef BOOL (WINAPI *SETPROCESSDEPPOLICY) (DWORD);

    HMODULE kernel32 = GetModuleHandleW(L"kernel32.dll");
    if (kernel32 == NULL)
    {
        // somehow this process didn't link to kernel32.dll
        return;
    }

    SETPROCESSDEPPOLICY setProcessDepPolicy = (SETPROCESSDEPPOLICY)GetProcAddress(
        kernel32,
        "SetProcessDEPPolicy");
    if (setProcessDepPolicy == NULL)
    {
        // SetProcessDEPPolicy was added in XP SP3 and Vista SP1.
        // Any OS before then either doesn't support DEP or doesn't
        // provide an API to disable it.
        return;
    }

    // Disable the DEP policy on a best-effort basis.
    setProcessDepPolicy(PROCESS_DEP_DISABLE);
}

#endif
