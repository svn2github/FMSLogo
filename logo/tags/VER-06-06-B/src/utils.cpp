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
*
*/

#include "allwind.h"

const char LOGOINIFILENAME[] = "Logo.ini";

void
SetPrivateProfileInt(
    const char *        Section,
    const char *        Key,
    int                 Value
)
   {
   char buffer[64];

   wsprintf(buffer, "%d", Value);

   WritePrivateProfileString(
      Section,
      Key,
      buffer,
      LOGOINIFILENAME);
   }


void
GetPrivateProfileQuadruple(
   const char *        Section,
   const char *        Key,
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
   outputString[0] = '\0';

   // Get the quadruple from the WIN.INI file.
   GetPrivateProfileString(
      Section,
      Key,
      defaultString,
      outputString,
      sizeof(outputString),
      LOGOINIFILENAME);

   // Decode location and size of window from profile string.
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
SetPrivateProfileQuadruple(
    const char *        Section,
    const char *        Key,
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

   // Set the quadruple in the INI file.
   WritePrivateProfileString(
      Section,
      Key,
      quadruple,
      LOGOINIFILENAME);
   }

bool
GetPrivateProfileFont(
   LPCSTR     ApplicationName,
   LOGFONT  & LogFont
)
{
   memset(&LogFont, 0, sizeof(LogFont));

   GetPrivateProfileString(
      ApplicationName,
      "FaceName",
      "Courier",
      LogFont.lfFaceName,
      LF_FACESIZE,
      LOGOINIFILENAME);

   LogFont.lfHeight = GetPrivateProfileInt(
      ApplicationName,
      "Height",
      -13,
      LOGOINIFILENAME);

   LogFont.lfWeight = GetPrivateProfileInt(
      ApplicationName,
      "Weight",
      400,
      LOGOINIFILENAME);

   LogFont.lfItalic = GetPrivateProfileInt(
      ApplicationName,
      "Italic",
      0,
      LOGOINIFILENAME);

   LogFont.lfCharSet = GetPrivateProfileInt(
      ApplicationName,
      "CharSet",
      0,
      LOGOINIFILENAME);

   LogFont.lfOutPrecision = GetPrivateProfileInt(
      ApplicationName,
      "OutPrecision",
      1,
      LOGOINIFILENAME);

   LogFont.lfClipPrecision = GetPrivateProfileInt(
      ApplicationName,
      "ClipPrecision",
      2,
      LOGOINIFILENAME);

   LogFont.lfQuality = GetPrivateProfileInt(
      ApplicationName,
      "Quality",
      1,
      LOGOINIFILENAME);

   LogFont.lfPitchAndFamily = GetPrivateProfileInt(
      ApplicationName,
      "PitchAndFamily",
      49,
      LOGOINIFILENAME);

   return true;
}

bool
SetPrivateProfileFont(
   LPCSTR     ApplicationName,
   LOGFONT  & LogFont
)
   {
   WritePrivateProfileString(
      ApplicationName,
      "FaceName",
      LogFont.lfFaceName,
      LOGOINIFILENAME);

   SetPrivateProfileInt(ApplicationName, "Height",         LogFont.lfHeight);
   SetPrivateProfileInt(ApplicationName, "Weight",         LogFont.lfWeight);
   SetPrivateProfileInt(ApplicationName, "Italic",         LogFont.lfItalic);
   SetPrivateProfileInt(ApplicationName, "CharSet",        LogFont.lfCharSet);
   SetPrivateProfileInt(ApplicationName, "OutPrecision",   LogFont.lfOutPrecision);
   SetPrivateProfileInt(ApplicationName, "ClipPrecision",  LogFont.lfClipPrecision);
   SetPrivateProfileInt(ApplicationName, "Quality",        LogFont.lfQuality);
   SetPrivateProfileInt(ApplicationName, "PitchAndFamily", LogFont.lfPitchAndFamily);
   return true;
   }

