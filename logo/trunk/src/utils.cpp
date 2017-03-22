/*
 *
 *       Copyright (C) 1995 by the Regents of the University of California
 *       Copyright (C) 1995 by George Mills
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
    #include <windows.h>
    #include <stdio.h>
    #include "localizedstrings.h"
    #include "debugheap.h"
#endif

// the name of the FMSLogo registry key under HKCU
const char FMSLOGO_REGISTRY_KEY_NAME[] = "Software\\FMSLogo";

// manifest constants to help protect against typos
const char FONTPROPERTY_FaceName[]       = "FaceName";
const char FONTPROPERTY_Height[]         = "Height";
const char FONTPROPERTY_Weight[]         = "Weight";
const char FONTPROPERTY_Italic[]         = "Italic";
const char FONTPROPERTY_CharSet[]        = "CharSet";
const char FONTPROPERTY_OutPrecision[]   = "OutPrecision";
const char FONTPROPERTY_ClipPrecision[]  = "ClipPrecision";
const char FONTPROPERTY_Quality[]        = "Quality";
const char FONTPROPERTY_PitchAndFamily[] = "PitchAndFamily";

static
HKEY
OpenFmsLogoKeyForSettingValue()
{
    HKEY fmslogoKey;

    // Use RegCreateKeyEx() instead of RegOpenKeyEx() because
    // the key may not already exist.  For example, if FMSlogo 
    // were "installed" with XCOPY or by uncompressing a ZIP file.

    LONG result = RegCreateKeyEx(
        HKEY_CURRENT_USER,
        FMSLOGO_REGISTRY_KEY_NAME,
        0,      // reserved
        NULL,   // ignored
        REG_OPTION_NON_VOLATILE,
        KEY_SET_VALUE,
        NULL,   // default security attributes
        &fmslogoKey,
        NULL);  // don't care if the key already existed
    if (result != ERROR_SUCCESS)
    {
        // failed!
        fmslogoKey = NULL;
    }

    return fmslogoKey;
}

static
HKEY
OpenFmsLogoKeyForGettingValue()
{
    HKEY fmslogoKey;

    LONG result = RegOpenKeyEx(
        HKEY_CURRENT_USER,
        FMSLOGO_REGISTRY_KEY_NAME,
        0, // reserved
        KEY_QUERY_VALUE,
        &fmslogoKey);
    if (result != ERROR_SUCCESS)
    {
        // failed!
        fmslogoKey = NULL;
    }

    return fmslogoKey;
}

void
SetConfigurationInt(
    const char *        Name,
    int                 Value
    )
{
    HKEY fmslogoKey = OpenFmsLogoKeyForSettingValue();
    if (fmslogoKey != NULL)
    {
        DWORD value          = static_cast<DWORD>(Value);
        const BYTE *valuePtr = reinterpret_cast<BYTE*>(&value);

        RegSetValueEx(
            fmslogoKey,
            Name,
            0,   // reserved
            REG_DWORD,
            valuePtr,
            sizeof value);

        RegCloseKey(fmslogoKey);
    }
}

int
GetConfigurationInt(
    const char *        Name,
    int                 DefaultValue
    )
{
    int returnValue = DefaultValue;

    HKEY fmslogoKey = OpenFmsLogoKeyForGettingValue();
    if (fmslogoKey != NULL)
    {
        DWORD value;
        DWORD valueSize = sizeof value;
        BYTE *valuePtr  = reinterpret_cast<BYTE*>(&value);
        DWORD type      = REG_DWORD;

        LONG result = RegQueryValueEx(
            fmslogoKey,
            Name,
            0,   // reserved
            &type,
            valuePtr,
            &valueSize);
        if (result    == ERROR_SUCCESS && 
            type      == REG_DWORD     &&
            valueSize == sizeof(value))
        {
            // we successfully read the value as a DWORD
            returnValue = value;
        }

        RegCloseKey(fmslogoKey);
    }

    return returnValue;
}

void
SetConfigurationString(
    const char *        Name,
    const char *        Value
    )
{
    HKEY fmslogoKey = OpenFmsLogoKeyForSettingValue();
    if (fmslogoKey != NULL)
    {
        DWORD valueLength    = strlen(Value) + sizeof(char);   // include NUL
        const BYTE *valuePtr = reinterpret_cast<const BYTE*>(Value);

        RegSetValueEx(
            fmslogoKey,
            Name,
            0,   // reserved
            REG_SZ,
            valuePtr,
            valueLength);

        RegCloseKey(fmslogoKey);
    }
}

void
GetConfigurationString(
    const char *        Name,
    char *              Value,
    size_t              ValueLength,
    const char *        DefaultValue
    )
{
#ifdef DEBUG
    memset(Value, 0xDD, ValueLength);
#endif

    bool useDefaultValue = true;

    HKEY fmslogoKey = OpenFmsLogoKeyForGettingValue();
    if (fmslogoKey != NULL)
    {
        DWORD valueSize = ValueLength - 1;  // leave room for NUL
        BYTE *valuePtr  = reinterpret_cast<BYTE*>(Value);
        DWORD valueType;

        LONG result = RegQueryValueEx(
            fmslogoKey,
            Name,
            0,   // reserved
            &valueType,
            valuePtr,
            &valueSize);
        if (result == ERROR_SUCCESS && 
            valueType == REG_SZ     &&
            valueSize < ValueLength - 1)
        {
            // we successfully read the value as a string
            Value[valueSize] = '\0';
            useDefaultValue  = false;
        }

        RegCloseKey(fmslogoKey);
    }

    if (useDefaultValue)
    {
        strcpy(Value, DefaultValue);
    }
}

void
GetConfigurationQuadruple(
    const char *        Name,
    int *               Value1,
    int *               Value2,
    int *               Value3,
    int *               Value4
    )
{
    char defaultString[256];
    sprintf(
        defaultString,
        "%d,%d,%d,%d",
        *Value1,
        *Value2,
        *Value3,
        *Value4);

    char outputString[256];

    // Get the quadruple from the configuration settings
    GetConfigurationString(
        Name,
        outputString,
        sizeof(outputString),
        defaultString);

    // Decode the quadruple string into numbers
    char * cp = outputString;

    *Value1 = (int) strtol(cp, &cp, 10);
    cp++;

    *Value2 = (int) strtol(cp, &cp, 10);
    cp++;

    *Value3 = (int) strtol(cp, &cp, 10);
    cp++;

    *Value4 = (int) strtol(cp, &cp, 10);
}


void
SetConfigurationQuadruple(
    const char *        Name,
    int                 Value1,
    int                 Value2,
    int                 Value3,
    int                 Value4
    )
{
    char quadruple[256];

    sprintf(
        quadruple,
        "%d,%d,%d,%d",
        Value1,
        Value2,
        Value3,
        Value4);

    // Set the quadruple in the configuration.
    SetConfigurationString(
        Name,
        quadruple);
}

static
char *
GetRelativeFontPropertyPointer(
    char *  FullyQualifiedName
    )
{
    // find where the relative property name should start
    char * relativeName = strchr(FullyQualifiedName, '\0');

    // add a '.' to distigush the relative part from the absolute part.
    *relativeName++ = '.';

    return relativeName;
}



void
GetConfigurationFont(
    const char * Name,
    LOGFONT  &   LogFont
    )
{
    memset(&LogFont, 0, sizeof(LogFont));

    char fullyQualifiedName[256];

    strcpy(fullyQualifiedName, Name);

    // find the end of the fullyQualifiedName
    char * relativeName = GetRelativeFontPropertyPointer(fullyQualifiedName);
   
    strcpy(relativeName, FONTPROPERTY_FaceName);
    GetConfigurationString(
        fullyQualifiedName, 
        LogFont.lfFaceName,
        LF_FACESIZE,
        LOCALIZED_DEFAULT_FONT_FACE);

    strcpy(relativeName, FONTPROPERTY_Height);
    LogFont.lfHeight = GetConfigurationInt(fullyQualifiedName, -13);

    strcpy(relativeName, FONTPROPERTY_Weight);
    LogFont.lfWeight = GetConfigurationInt(fullyQualifiedName, 400);

    strcpy(relativeName, FONTPROPERTY_Italic);
    LogFont.lfItalic = GetConfigurationInt(fullyQualifiedName, 0);

    strcpy(relativeName, FONTPROPERTY_CharSet);
    LogFont.lfCharSet = GetConfigurationInt(fullyQualifiedName, 0);

    strcpy(relativeName, FONTPROPERTY_OutPrecision);
    LogFont.lfOutPrecision = GetConfigurationInt(fullyQualifiedName, 1);

    strcpy(relativeName, FONTPROPERTY_ClipPrecision);
    LogFont.lfClipPrecision = GetConfigurationInt(fullyQualifiedName, 2);

    strcpy(relativeName, FONTPROPERTY_Quality);
    LogFont.lfQuality = GetConfigurationInt(fullyQualifiedName, 1);

    strcpy(relativeName, FONTPROPERTY_PitchAndFamily);
    LogFont.lfPitchAndFamily = GetConfigurationInt(fullyQualifiedName, 49);
}

void
SetConfigurationFont(
    const char *       Name,
    const LOGFONT  &   LogFont
    )
{
    char fullyQualifiedName[256];

    strcpy(fullyQualifiedName, Name);

    // find where the relative property name should start
    char * relativeName = GetRelativeFontPropertyPointer(fullyQualifiedName);

    strcpy(relativeName, FONTPROPERTY_FaceName);
    SetConfigurationString(fullyQualifiedName, LogFont.lfFaceName);

    const struct PROPERTY {
        const char * Name;
        int          Value;
    } properties[] = {
        {FONTPROPERTY_Height,          LogFont.lfHeight},
        {FONTPROPERTY_Weight,          LogFont.lfWeight},
        {FONTPROPERTY_Italic,          LogFont.lfItalic},
        {FONTPROPERTY_CharSet,         LogFont.lfCharSet},
        {FONTPROPERTY_OutPrecision,    LogFont.lfOutPrecision},
        {FONTPROPERTY_ClipPrecision,   LogFont.lfClipPrecision},
        {FONTPROPERTY_Quality,         LogFont.lfQuality},
        {FONTPROPERTY_PitchAndFamily,  LogFont.lfPitchAndFamily},
    };

    for (size_t i = 0; i < sizeof(properties) / sizeof(*properties); i++)
    {
        strcpy(relativeName, properties[i].Name);
        SetConfigurationInt(fullyQualifiedName, properties[i].Value);
    }
}
