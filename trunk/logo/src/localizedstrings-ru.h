//
// Copyright (C) 2006 by David Costanzo
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

/////////////////////////////////////////////////////////////////////////////
// This file contains localized strings for Russian by Igor Baglaev
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Localization Instructions:
//
// This file a C++ header file, so if you are familiar with how C++ works, it
// will help.
//
// Each localized string is a line that takes the following form:
//
//      #define <TOKEN> "<quoted-string>" //<status>
//
//   #define         - is part of C++.  Do not change this.
//   <TOKEN>         - is how the FMSLogo source code refers to the string.
//                     This must not change, regardless of the locale.
//   <quoted-string> - is what fmslogo.exe will use whenever it refers 
//                     to <TOKEN>.  This is bit that must be translated.
//   <status>        - This is some information on whether or not the
//                     string has been localized yet.  For example, is 
//                     someone has localized FMSLogo into French, then I add
//                     a new string, I will append //NOT_YET_LOCALIZED as a
//                     reminder that we need to localized just this one string.
//
// To localize FMSLogo, you must to translate the phrases in <quoted-string>
// from English to your language.  Once you have localized a string, please
// remove the //<status> comment at the end of the line.
//
// If you think that a string should *NOT* be translated (for example "FMSLogo"),
// then just delete the //<status> comment to indicate that you have decided
// not to translate the string.  If you are not sure how to translate a string
// please leave the //<status> comment so that that someone else may investigate
// it.
//
//
// For quoted strings that refer to commands, please refer to the command
// in your language, then put the English form in parentheses.  For example:
//
//   "Can't use TO inside a procedure"
//
// is translated into French as:
//
//   "Impossible d'utiliser POUR (TO) dans une proc�dure"
//
//
// Please note that some of the quoted strings embed a <TOKEN> within them.
// For example, the phrase:
//
//   "I like FMSLogo, do you?"
//
// Might appear as:
//
//   "I like "LOCALIZED_GENERAL_PRODUCTNAME", do you?"
//
// When fmslogo.exe is built, the LOCALIZED_GENERAL_PRODUCTNAME will be 
// replaced with the localized form of FMSLogo and will look like the
// original phrase.  Please only translate the "I like " and ", do you?".
//
// Some of the quoted strings (the ones that appear in menus and buttons)
// have ampersands "&" characters in them.  For example the word "File" 
// may appear as "&File".  This tells Windows that ALT+F should take the
// user straight to this option.
// 
// Some of the quoted strings have a "%p" or a "%s" in them.  For example,
// the error message for when you give bad input looks like this:
//
//    "%p doesn't like %s as input"
//
// The "%p" and "%s" are replaced with the procedure name and the input
// that it doesn't like.  You must NOT add any "%" characters to any string, 
// nor can you change the order in which the %p and %s occur.
//
// There are some special characters that you can add to a string with a 
// special "escape sequence", which begins with a backslash "\".
//
//             +--------------------------------------+
//             | Special Character | Escape Sequence  |
//             +--------------------------------------+
//             |  Tab              |        \t        |
//             |  Newline          |        \n        |
//             |  Backslash        |        \\        |
//             |  DoubleQuote      |        \"        |
//             +--------------------------------------+
//
// Due to a bug in Borland's resource compiler, two forward slashes cannot
// appear in a quoted string.  To work around this problem, I "escape" the
// first slash, as in:
// 
//    "http://fmslogo.org/" -> "http:\x2F/fmslogo.org/
//
/////////////////////////////////////////////////////////////////////////////

//
// Localized "alternate" spellings of Logo reserved words
//
#define LOCALIZED_ALTERNATE_TRUE     "������" 
#define LOCALIZED_ALTERNATE_FALSE    "����" 
#define LOCALIZED_ALTERNATE_END      "�����"
#define LOCALIZED_ALTERNATE_TOPLEVEL "��������������" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SYSTEM   "�������" // NOT_YET_LOCALIZED

//
// Localized "alternate" names of Logo special variables
//
#define LOCALIZED_ALTERNATE_CASEIGNOREDP    "�����������������������" 
#define LOCALIZED_ALTERNATE_ERRACT          "������" 
#define LOCALIZED_ALTERNATE_STARTUP         "������" 
#define LOCALIZED_ALTERNATE_REDEFP          "���������" 
#define LOCALIZED_ALTERNATE_PRINTWIDTHLIMIT "����������" 
#define LOCALIZED_ALTERNATE_PRINTDEPTHLIMIT "�����������"


//
// Localized "alternate" spellings of Logo primitives.
// These become the perferred name of the primitives.  For example,
// when you press the "reset" button, FMSLogo will write the value of
// LOCALIZED_ALTERNATE_CLEARSCREEN to the commander.
// 
// Furthermore, if one of the LOCALIZED_ALTERNATE names uses the same text 
// as the English counterpart, then the localized name will be used. 
// For example, in the English version, "ct" is short for "CLEARTEXT".
// In the French version, "ct" is short for "CACHETORTUE" (HIDETURTLE).
// So in the French FMSLogo, running "ct" will hide the turtle.
//
// That said, it is strongly recommended that you do not choose names
// that match the long English name of any command.  If you do, you may
// find that some programs won't run on the localized version of FMSLogo.
// 
// If you don't know how to translate a particular command, leave it
// as the English name and it will be ignored.
//
#define LOCALIZED_ALTERNATE__DEFMACRO              ".���������"
#define LOCALIZED_ALTERNATE__EQ                    ".����" 
#define LOCALIZED_ALTERNATE__MACRO                 ".������"
#define LOCALIZED_ALTERNATE__MAYBEOUTPUT           ".���������"
#define LOCALIZED_ALTERNATE__SETBF                 ".���������" 
#define LOCALIZED_ALTERNATE__SETFIRST              ".������������" 
#define LOCALIZED_ALTERNATE__SETITEM               ".����������" 
#define LOCALIZED_ALTERNATE_ACTIVEAREA             "������������" 
#define LOCALIZED_ALTERNATE_ALLOPEN                "���������" 
#define LOCALIZED_ALTERNATE_AND                    "���"
#define LOCALIZED_ALTERNATE_APPLY                  "���������" 
#define LOCALIZED_ALTERNATE_ARCCOS                 "arccos" 
#define LOCALIZED_ALTERNATE_ARCSIN                 "arcsin" 
#define LOCALIZED_ALTERNATE_ARCTAN                 "arctg" 
#define LOCALIZED_ALTERNATE_ARRAY                  "������"
#define LOCALIZED_ALTERNATE_ARRAYP                 "��������" 
#define LOCALIZED_ALTERNATE_ARRAY_                 "������?" 
#define LOCALIZED_ALTERNATE_ASCII                  "���" 
#define LOCALIZED_ALTERNATE_ASHIFT                 "������" 
#define LOCALIZED_ALTERNATE_BACK                   "�����"
#define LOCALIZED_ALTERNATE_BACKSLASHEDP           "������������" 
#define LOCALIZED_ALTERNATE_BACKSLASHED_           "����������?" 
#define LOCALIZED_ALTERNATE_BEFOREP                "�������" 
#define LOCALIZED_ALTERNATE_BEFORE_                "�������?" 
#define LOCALIZED_ALTERNATE_BF                     "���"
#define LOCALIZED_ALTERNATE_BFS                    "����" 
#define LOCALIZED_ALTERNATE_BITAND                 "���������" 
#define LOCALIZED_ALTERNATE_BITBLOCK               "���������" 
#define LOCALIZED_ALTERNATE_BITCOPY                "������������" 
#define LOCALIZED_ALTERNATE_BITCUT                 "�����������" 
#define LOCALIZED_ALTERNATE_BITFIT                 "������������" 
#define LOCALIZED_ALTERNATE_BITINDEX               "�����������" 
#define LOCALIZED_ALTERNATE_BITLOAD                "������������" 
#define LOCALIZED_ALTERNATE_BITLOADSIZE            "�������������������" 
#define LOCALIZED_ALTERNATE_BITSIZE                "������������" 
#define LOCALIZED_ALTERNATE_BITMAPTURTLE           "������������" 
#define LOCALIZED_ALTERNATE_BITMODE                "�����������" 
#define LOCALIZED_ALTERNATE_BITNOT                 "���������" 
#define LOCALIZED_ALTERNATE_BITOR                  "���������" 
#define LOCALIZED_ALTERNATE_BITPASTE               "�����������" 
#define LOCALIZED_ALTERNATE_BITPASTETOINDEX        "����������������" 
#define LOCALIZED_ALTERNATE_BITSAVE                "������������" 
#define LOCALIZED_ALTERNATE_BITXOR                 "�������������" 
#define LOCALIZED_ALTERNATE_BK                     "��"
#define LOCALIZED_ALTERNATE_BL                     "���"
#define LOCALIZED_ALTERNATE_BURIED                 "�������" 
#define LOCALIZED_ALTERNATE_BURY                   "�����" 
#define LOCALIZED_ALTERNATE_BUTFIRST               "������������"
#define LOCALIZED_ALTERNATE_BUTFIRSTS              "�����������" 
#define LOCALIZED_ALTERNATE_BUTLAST                "���������������"
#define LOCALIZED_ALTERNATE_BUTTONCREATE           "������������"
#define LOCALIZED_ALTERNATE_BUTTONDELETE           "�����������" 
#define LOCALIZED_ALTERNATE_BUTTONENABLE           "�������������" 
#define LOCALIZED_ALTERNATE_BUTTONUPDATE           "������������" 
#define LOCALIZED_ALTERNATE_BUTTONP                "��������" 
#define LOCALIZED_ALTERNATE_BUTTON_                "������?" 
#define LOCALIZED_ALTERNATE_BYE                    "����" 
#define LOCALIZED_ALTERNATE_CATCH                  "������" 
#define LOCALIZED_ALTERNATE_CHAR                   "������"
#define LOCALIZED_ALTERNATE_CHDIR                  "������" 
#define LOCALIZED_ALTERNATE_CHECKBOXCREATE         "��������������" 
#define LOCALIZED_ALTERNATE_CHECKBOXDELETE         "�������������"
#define LOCALIZED_ALTERNATE_CHECKBOXENABLE         "���������������" 
#define LOCALIZED_ALTERNATE_CHECKBOXGET            "������������" 
#define LOCALIZED_ALTERNATE_CHECKBOXSET            "�������������" 
#define LOCALIZED_ALTERNATE_CLEAN                  "������" 
#define LOCALIZED_ALTERNATE_CLEARPALETTE           "������������" 
#define LOCALIZED_ALTERNATE_CLEARSCREEN            "�����������"
#define LOCALIZED_ALTERNATE_CLEARTEXT              "�����������" 
#define LOCALIZED_ALTERNATE_CLEARTIMER             "������������" 
#define LOCALIZED_ALTERNATE_CLOSE                  "������" 
#define LOCALIZED_ALTERNATE_CLOSEALL               "���������" 
#define LOCALIZED_ALTERNATE_CO                     "����" 
#define LOCALIZED_ALTERNATE_COMBOBOXADDSTRING      "�����������" 
#define LOCALIZED_ALTERNATE_COMBOBOXCREATE         "����������" 
#define LOCALIZED_ALTERNATE_COMBOBOXDELETE         "���������" 
#define LOCALIZED_ALTERNATE_COMBOBOXENABLE         "�����������" 
#define LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING   "���������������" 
#define LOCALIZED_ALTERNATE_COMBOBOXGETTEXT        "���������" 
#define LOCALIZED_ALTERNATE_COMBOBOXSETTEXT        "���������������" 
#define LOCALIZED_ALTERNATE_CONTENTS               "����������" 
#define LOCALIZED_ALTERNATE_CONTINUE               "��������" 
#define LOCALIZED_ALTERNATE_COPYDEF                "��������" 
#define LOCALIZED_ALTERNATE_COS                    "cos" 
#define LOCALIZED_ALTERNATE_COUNT                  "�������"
#define LOCALIZED_ALTERNATE_CS                     "��"
#define LOCALIZED_ALTERNATE_CT                     "��" 
#define LOCALIZED_ALTERNATE_CURSOR                 "������" 
#define LOCALIZED_ALTERNATE_DEBUGWINDOWS           "�����������" 
#define LOCALIZED_ALTERNATE_DEFINE                 "��������" 
#define LOCALIZED_ALTERNATE_DEFINEDP               "�����������" 
#define LOCALIZED_ALTERNATE_DEFINED_               "���������?" 
#define LOCALIZED_ALTERNATE_DIALOGCREATE           "������������" 
#define LOCALIZED_ALTERNATE_DIALOGENABLE           "�������������" 
#define LOCALIZED_ALTERNATE_DIALOGDELETE           "�����������" 
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         "���������������" 
#define LOCALIZED_ALTERNATE_DIALOGFILESAVE         "�����������������" 
#define LOCALIZED_ALTERNATE_DIFFERENCE             "��������"
#define LOCALIZED_ALTERNATE_DIRECTORIES            "�����" 
#define LOCALIZED_ALTERNATE_DLLCALL                "��������" 
#define LOCALIZED_ALTERNATE_DLLFREE                "��������" 
#define LOCALIZED_ALTERNATE_DLLLOAD                "�����������" 
#define LOCALIZED_ALTERNATE_DOWN                   "����" 
#define LOCALIZED_ALTERNATE_DOWNPITCH              "���������" 
#define LOCALIZED_ALTERNATE_DRIBBLE                "��������" 
#define LOCALIZED_ALTERNATE_ED                     "���" 
#define LOCALIZED_ALTERNATE_EDIT                   "�������������" 
#define LOCALIZED_ALTERNATE_ELLIPSEARC             "�����������" 
#define LOCALIZED_ALTERNATE_EMPTYP                 "��������" 
#define LOCALIZED_ALTERNATE_EMPTY_                 "������?" 
#define LOCALIZED_ALTERNATE_EOFP                   "�����" 
#define LOCALIZED_ALTERNATE_EOF_                   "���?" 
#define LOCALIZED_ALTERNATE_EQUALP                 "��������"
#define LOCALIZED_ALTERNATE_EQUAL_                 "equal?" 
#define LOCALIZED_ALTERNATE_ER                     "��" 
#define LOCALIZED_ALTERNATE_ERASE                  "�����" 
#define LOCALIZED_ALTERNATE_ERASEFILE              "���������" 
#define LOCALIZED_ALTERNATE_ERF                    "���" 
#define LOCALIZED_ALTERNATE_ERROR                  "������" 
#define LOCALIZED_ALTERNATE_EVENTCHECK             "������������" 
#define LOCALIZED_ALTERNATE_EXP                    "exp" 
#define LOCALIZED_ALTERNATE_FD                     "��"
#define LOCALIZED_ALTERNATE_FENCE                  "����������" 
#define LOCALIZED_ALTERNATE_FILL                   "�����"
#define LOCALIZED_ALTERNATE_FILES                  "�����" 
#define LOCALIZED_ALTERNATE_FIRST                  "������"
#define LOCALIZED_ALTERNATE_FIRSTS                 "������" 
#define LOCALIZED_ALTERNATE_FLOODCOLOR             "�����������" 
#define LOCALIZED_ALTERNATE_FONTFACENAMES          "��������������" 
#define LOCALIZED_ALTERNATE_FOREVER                "�����������" 
#define LOCALIZED_ALTERNATE_FORM                   "������" 
#define LOCALIZED_ALTERNATE_FORWARD                "������"
#define LOCALIZED_ALTERNATE_FPUT                   "�����" 
#define LOCALIZED_ALTERNATE_FS                     "��" 
#define LOCALIZED_ALTERNATE_FULLSCREEN             "�����������" 
#define LOCALIZED_ALTERNATE_FULLTEXT               "���������" 
#define LOCALIZED_ALTERNATE_GETFOCUS               "������������" 
#define LOCALIZED_ALTERNATE_GOTO                   "�������" 
#define LOCALIZED_ALTERNATE_GIFLOAD                "����������" 
#define LOCALIZED_ALTERNATE_GIFSIZE                "���������" 
#define LOCALIZED_ALTERNATE_GIFSAVE                "����������" 
#define LOCALIZED_ALTERNATE_GPROP                  "�����" 
#define LOCALIZED_ALTERNATE_GREATEREQUALP          "�������������" 
#define LOCALIZED_ALTERNATE_GREATEREQUAL_          "�����������?" 
#define LOCALIZED_ALTERNATE_GREATERP               "��������"
#define LOCALIZED_ALTERNATE_GREATER_               "������?" 
#define LOCALIZED_ALTERNATE_GROUPBOXCREATE         "������������" 
#define LOCALIZED_ALTERNATE_GROUPBOXDELETE         "�����������" 
#define LOCALIZED_ALTERNATE_HALT                   "�������" 
#define LOCALIZED_ALTERNATE_HEADING                "�����������" 
#define LOCALIZED_ALTERNATE_HELP                   "������" 
#define LOCALIZED_ALTERNATE_HIDETURTLE             "�������������"
#define LOCALIZED_ALTERNATE_HOME                   "�����"
#define LOCALIZED_ALTERNATE_HT                     "��"
#define LOCALIZED_ALTERNATE_IF                     "����"
#define LOCALIZED_ALTERNATE_IFELSE                 "���������"
#define LOCALIZED_ALTERNATE_IFF                    "�����" 
#define LOCALIZED_ALTERNATE_IFFALSE                "��������" 
#define LOCALIZED_ALTERNATE_IFT                    "�����" 
#define LOCALIZED_ALTERNATE_IFTRUE                 "����������" 
#define LOCALIZED_ALTERNATE_INGAMEPORT             "��������" 
#define LOCALIZED_ALTERNATE_INPORT                 "�����" 
#define LOCALIZED_ALTERNATE_INPORTB                "������" 
#define LOCALIZED_ALTERNATE_INT                    "�����" 
#define LOCALIZED_ALTERNATE_ITEM                   "�������"
#define LOCALIZED_ALTERNATE_KEYBOARDOFF            "�����������������" 
#define LOCALIZED_ALTERNATE_KEYBOARDON             "����������������" 
#define LOCALIZED_ALTERNATE_KEYBOARDVALUE          "���������������" 
#define LOCALIZED_ALTERNATE_KEYP                   "���������" 
#define LOCALIZED_ALTERNATE_KEY_                   "�������?" 
#define LOCALIZED_ALTERNATE_LABEL                  "�������"
#define LOCALIZED_ALTERNATE_LABELFONT              "������������"
#define LOCALIZED_ALTERNATE_LABELSIZE              "�������������" 
#define LOCALIZED_ALTERNATE_LAST                   "���������"
#define LOCALIZED_ALTERNATE_LEFT                   "������"
#define LOCALIZED_ALTERNATE_LEFTROLL               "���������" 
#define LOCALIZED_ALTERNATE_LESSEQUALP             "�������������" 
#define LOCALIZED_ALTERNATE_LESSEQUAL_             "�����������?" 
#define LOCALIZED_ALTERNATE_LESSP                  "��������"
#define LOCALIZED_ALTERNATE_LESS_                  "������?" 
#define LOCALIZED_ALTERNATE_LIGHT                  "�������" 
#define LOCALIZED_ALTERNATE_LIST                   "������"
#define LOCALIZED_ALTERNATE_LISTBOXADDSTRING       "�����������������" 
#define LOCALIZED_ALTERNATE_LISTBOXCREATE          "�����������" 
#define LOCALIZED_ALTERNATE_LISTBOXENABLE          "������������" 
#define LOCALIZED_ALTERNATE_LISTBOXDELETE          "����������" 
#define LOCALIZED_ALTERNATE_LISTBOXDELETESTRING    "����������������" 
#define LOCALIZED_ALTERNATE_LISTBOXGETSELECT       "����������" 
#define LOCALIZED_ALTERNATE_LISTP                  "��������" 
#define LOCALIZED_ALTERNATE_LIST_                  "��������?" 
#define LOCALIZED_ALTERNATE_LN                     "ln" 
#define LOCALIZED_ALTERNATE_LOAD                   "�������" 
#define LOCALIZED_ALTERNATE_LOCAL                  "���������" 
#define LOCALIZED_ALTERNATE_LOG10                  "lg" 
#define LOCALIZED_ALTERNATE_LOGOVERSION            "����������" 
#define LOCALIZED_ALTERNATE_LOWERCASE              "��������" 
#define LOCALIZED_ALTERNATE_LPUT                   "�������"
#define LOCALIZED_ALTERNATE_LR                     "���" 
#define LOCALIZED_ALTERNATE_LSHIFT                 "������" 
#define LOCALIZED_ALTERNATE_LT                     "��"
#define LOCALIZED_ALTERNATE_MACHINE                "������" 
#define LOCALIZED_ALTERNATE_MACROP                 "��������" 
#define LOCALIZED_ALTERNATE_MACRO_                 "������?" 
#define LOCALIZED_ALTERNATE_MAKE                   "�����"
#define LOCALIZED_ALTERNATE_MCI                    "���" 
#define LOCALIZED_ALTERNATE_MEMBER                 "���������"
#define LOCALIZED_ALTERNATE_MEMBERP                "���������"
#define LOCALIZED_ALTERNATE_MEMBER_                "�������?" 
#define LOCALIZED_ALTERNATE_MESSAGEBOX             "�������������" 
#define LOCALIZED_ALTERNATE_MIDICLOSE              "����������" 
#define LOCALIZED_ALTERNATE_MIDIMESSAGE            "�������������" 
#define LOCALIZED_ALTERNATE_MIDIOPEN               "����������" 
#define LOCALIZED_ALTERNATE_MINUS                  "�����" 
#define LOCALIZED_ALTERNATE_MKDIR                  "�������" 
#define LOCALIZED_ALTERNATE_MODULO                 "��������"
#define LOCALIZED_ALTERNATE_MOUSEOFF               "��������"
#define LOCALIZED_ALTERNATE_MOUSEON                "�������"
#define LOCALIZED_ALTERNATE_MOUSEPOS               "���������"
#define LOCALIZED_ALTERNATE_NAMEP                  "�����" 
#define LOCALIZED_ALTERNATE_NAME_                  "���?" 
#define LOCALIZED_ALTERNATE_NAMES                  "�����" 
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           "���������������" 
#define LOCALIZED_ALTERNATE_NETACCEPTON            "��������������" 
#define LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE  "���������������" 
#define LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE     "�����������������" 
#define LOCALIZED_ALTERNATE_NETCONNECTOFF          "���������������" 
#define LOCALIZED_ALTERNATE_NETCONNECTON           "��������������" 
#define LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE "��������������" 
#define LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE    "����������������" 
#define LOCALIZED_ALTERNATE_NETSHUTDOWN            "��������" 
#define LOCALIZED_ALTERNATE_NETSTARTUP             "�����������" 
#define LOCALIZED_ALTERNATE_NOBITMAPTURTLE         "��������������" 
#define LOCALIZED_ALTERNATE_NODES                  "����" 
#define LOCALIZED_ALTERNATE_NODRIBBLE              "������������" 
#define LOCALIZED_ALTERNATE_NOSTATUS               "����������" 
#define LOCALIZED_ALTERNATE_NOT                    "��" 
#define LOCALIZED_ALTERNATE_NOTEQUALP              "���������" 
#define LOCALIZED_ALTERNATE_NOTEQUAL_              "�������?" 
#define LOCALIZED_ALTERNATE_NOYIELD                "����������" 
#define LOCALIZED_ALTERNATE_NUMBERP                "�������" 
#define LOCALIZED_ALTERNATE_NUMBER_                "�����?" 
#define LOCALIZED_ALTERNATE_OP                     "��"
#define LOCALIZED_ALTERNATE_OPENAPPEND             "������������" 
#define LOCALIZED_ALTERNATE_OPENREAD               "�����������" 
#define LOCALIZED_ALTERNATE_OPENUPDATE             "������������" 
#define LOCALIZED_ALTERNATE_OPENWRITE              "������������" 
#define LOCALIZED_ALTERNATE_OR                     "���" 
#define LOCALIZED_ALTERNATE_OUTPORT                "�������" 
#define LOCALIZED_ALTERNATE_OUTPORTB               "��������" 
#define LOCALIZED_ALTERNATE_OUTPUT                 "�����"
#define LOCALIZED_ALTERNATE_PARSE                  "������" 
#define LOCALIZED_ALTERNATE_PAUSE                  "�����" 
#define LOCALIZED_ALTERNATE_PC                     "��" 
#define LOCALIZED_ALTERNATE_PD                     "��" 
#define LOCALIZED_ALTERNATE_PE                     "��"
#define LOCALIZED_ALTERNATE_PENCOLOR               "��������"  
#define LOCALIZED_ALTERNATE_PENDOWN                "����������"
#define LOCALIZED_ALTERNATE_PENDOWNP               "����������" 
#define LOCALIZED_ALTERNATE_PENDOWN_               "��������?" 
#define LOCALIZED_ALTERNATE_PENERASE               "������"
#define LOCALIZED_ALTERNATE_PENMODE                "���������" 
#define LOCALIZED_ALTERNATE_PENPAINT               "���������"
#define LOCALIZED_ALTERNATE_PENPATTERN             "����������" 
#define LOCALIZED_ALTERNATE_PENREVERSE             "������������"
#define LOCALIZED_ALTERNATE_PENSIZE                "����������" 
#define LOCALIZED_ALTERNATE_PENUP                  "�����������"
#define LOCALIZED_ALTERNATE_PERSPECTIVE            "����������������" 
#define LOCALIZED_ALTERNATE_PITCH                  "�����" 
#define LOCALIZED_ALTERNATE_PIXEL                  "�������" 
#define LOCALIZED_ALTERNATE_PLAYWAVE               "�������������" 
#define LOCALIZED_ALTERNATE_PLIST                  "��������" 
#define LOCALIZED_ALTERNATE_PLISTS                 "��������" 
#define LOCALIZED_ALTERNATE_PO                     "�����" 
#define LOCALIZED_ALTERNATE_POPDIR                 "��������" 
#define LOCALIZED_ALTERNATE_POLYSTART              "����������" 
#define LOCALIZED_ALTERNATE_POLYEND                "����������" 
#define LOCALIZED_ALTERNATE_POLYVIEW               "������������" 
#define LOCALIZED_ALTERNATE_PORTCLOSE              "����������" 
#define LOCALIZED_ALTERNATE_PORTFLUSH              "�������" 
#define LOCALIZED_ALTERNATE_PORTMODE               "����������" 
#define LOCALIZED_ALTERNATE_PORTOPEN               "����������" 
#define LOCALIZED_ALTERNATE_PORTREADARRAY          "��������������" 
#define LOCALIZED_ALTERNATE_PORTREADCHAR           "�������������" 
#define LOCALIZED_ALTERNATE_PORTWRITEARRAY         "������������" 
#define LOCALIZED_ALTERNATE_PORTWRITECHAR          "�����������" 
#define LOCALIZED_ALTERNATE_POS                    "�����" 
#define LOCALIZED_ALTERNATE_POSXYZ                 "�����_xyz" 
#define LOCALIZED_ALTERNATE_POT                    "�������" 
#define LOCALIZED_ALTERNATE_POWER                  "�������"
#define LOCALIZED_ALTERNATE_PPROP                  "���������" 
#define LOCALIZED_ALTERNATE_PPT                    "���"
#define LOCALIZED_ALTERNATE_PR                     "��"
#define LOCALIZED_ALTERNATE_PRIMITIVEP             "����������" 
#define LOCALIZED_ALTERNATE_PRIMITIVE_             "��������?" 
#define LOCALIZED_ALTERNATE_PRINT                  "����"
#define LOCALIZED_ALTERNATE_PROCEDUREP             "�����������" 
#define LOCALIZED_ALTERNATE_PROCEDURE_             "���������?" 
#define LOCALIZED_ALTERNATE_PROPLISTP              "�����������" 
#define LOCALIZED_ALTERNATE_PROPLIST_              "���������?" 
#define LOCALIZED_ALTERNATE_PROCEDURES             "���������"
#define LOCALIZED_ALTERNATE_PRODUCT                "������������"
#define LOCALIZED_ALTERNATE_PU                     "��"
#define LOCALIZED_ALTERNATE_PX                     "���"
#define LOCALIZED_ALTERNATE_QUESTIONBOX            "�����������" 
#define LOCALIZED_ALTERNATE_QUOTIENT               "�������"
#define LOCALIZED_ALTERNATE_RADARCCOS              "radarccos" 
#define LOCALIZED_ALTERNATE_RADARCSIN              "radarcsin" 
#define LOCALIZED_ALTERNATE_RADARCTAN              "radarctg" 
#define LOCALIZED_ALTERNATE_RADCOS                 "radcos" 
#define LOCALIZED_ALTERNATE_RADIOBUTTONCREATE      "�����������������" 
#define LOCALIZED_ALTERNATE_RADIOBUTTONENABLE      "������������������" 
#define LOCALIZED_ALTERNATE_RADIOBUTTONDELETE      "����������������" 
#define LOCALIZED_ALTERNATE_RADIOBUTTONGET         "������������������" 
#define LOCALIZED_ALTERNATE_RADIOBUTTONSET         "�������������������" 
#define LOCALIZED_ALTERNATE_RADSIN                 "radsin" 
#define LOCALIZED_ALTERNATE_RADTAN                 "radtg" 
#define LOCALIZED_ALTERNATE_RANDOM                 "���������"
#define LOCALIZED_ALTERNATE_RAWASCII               "�������" 
#define LOCALIZED_ALTERNATE_RC                     "��" 
#define LOCALIZED_ALTERNATE_RCS                    "���" 
#define LOCALIZED_ALTERNATE_READCHAR               "���������" 
#define LOCALIZED_ALTERNATE_READCHARS              "����������" 
#define LOCALIZED_ALTERNATE_READER                 "�����������" 
#define LOCALIZED_ALTERNATE_READLIST               "���������" 
#define LOCALIZED_ALTERNATE_READPOS                "��������" 
#define LOCALIZED_ALTERNATE_READWORD               "��������"
#define LOCALIZED_ALTERNATE_REMAINDER              "�������"
#define LOCALIZED_ALTERNATE_REMPROP                "�������" 
#define LOCALIZED_ALTERNATE_REPCOUNT               "�������"
#define LOCALIZED_ALTERNATE_REPEAT                 "�������"
#define LOCALIZED_ALTERNATE_RERANDOM               "���������" 
#define LOCALIZED_ALTERNATE_RIGHT                  "�������"
#define LOCALIZED_ALTERNATE_RIGHTROLL              "����������" 
#define LOCALIZED_ALTERNATE_RL                     "��" 
#define LOCALIZED_ALTERNATE_RMDIR                  "�����" 
#define LOCALIZED_ALTERNATE_ROLL                   "����" 
#define LOCALIZED_ALTERNATE_ROUND                  "�����"
#define LOCALIZED_ALTERNATE_RR                     "���" 
#define LOCALIZED_ALTERNATE_RT                     "��"
#define LOCALIZED_ALTERNATE_RUN                    "���������" 
#define LOCALIZED_ALTERNATE_RUNPARSE               "���������" 
#define LOCALIZED_ALTERNATE_RUNRESULT              "������" 
#define LOCALIZED_ALTERNATE_RW                     "��"
#define LOCALIZED_ALTERNATE_SAVE                   "�������" 
#define LOCALIZED_ALTERNATE_SCREENCOLOR            "����������" 
#define LOCALIZED_ALTERNATE_SCROLLBARCREATE        "��������������" 
#define LOCALIZED_ALTERNATE_SCROLLBARENABLE        "��������������" 
#define LOCALIZED_ALTERNATE_SCROLLBARDELETE        "������������" 
#define LOCALIZED_ALTERNATE_SCROLLBARGET           "���������������" 
#define LOCALIZED_ALTERNATE_SCROLLBARSET           "������������" 
#define LOCALIZED_ALTERNATE_SCROLLX                "���������_x" 
#define LOCALIZED_ALTERNATE_SCROLLY                "���������_y" 
#define LOCALIZED_ALTERNATE_SCRUNCH                "���������" 
#define LOCALIZED_ALTERNATE_SE                     "��"
#define LOCALIZED_ALTERNATE_SELECTBOX              "����������" 
#define LOCALIZED_ALTERNATE_SENTENCE               "�����������"
#define LOCALIZED_ALTERNATE_SETACTIVEAREA          "���������������" 
#define LOCALIZED_ALTERNATE_SETBITINDEX            "�����������������" 
#define LOCALIZED_ALTERNATE_SETBITMODE             "�����������������" 
#define LOCALIZED_ALTERNATE_SETCLIP                "�������" 
#define LOCALIZED_ALTERNATE_SETCURSOR              "���������" 
#define LOCALIZED_ALTERNATE_SETCURSORNOWAIT        "������������" 
#define LOCALIZED_ALTERNATE_SETCURSORWAIT          "����������" 
#define LOCALIZED_ALTERNATE_SETFC                  "�����"
#define LOCALIZED_ALTERNATE_SETFLOODCOLOR          "����������������" 
#define LOCALIZED_ALTERNATE_SETFOCUS               "����������" 
#define LOCALIZED_ALTERNATE_SETH                   "����"
#define LOCALIZED_ALTERNATE_SETHEADING             "���������"
#define LOCALIZED_ALTERNATE_SETITEM                "������������"
#define LOCALIZED_ALTERNATE_SETLABELFONT           "���������������"
#define LOCALIZED_ALTERNATE_SETLIGHT               "���������������" 
#define LOCALIZED_ALTERNATE_SETMARGINS             "�������" 
#define LOCALIZED_ALTERNATE_SETPC                  "��"
#define LOCALIZED_ALTERNATE_SETPENCOLOR            "�������������"
#define LOCALIZED_ALTERNATE_SETPENPATTERN          "�������������" 
#define LOCALIZED_ALTERNATE_SETPENSIZE             "���������������"
#define LOCALIZED_ALTERNATE_SETPITCH               "��������" 
#define LOCALIZED_ALTERNATE_SETPIXEL               "����������" 
#define LOCALIZED_ALTERNATE_SETPOS                 "����������"
#define LOCALIZED_ALTERNATE_SETPOSXYZ              "��������_xyz" 
#define LOCALIZED_ALTERNATE_SETREAD                "���������" 
#define LOCALIZED_ALTERNATE_SETREADPOS             "������������" 
#define LOCALIZED_ALTERNATE_SETROLL                "�������" 
#define LOCALIZED_ALTERNATE_SETSC                  "���" 
#define LOCALIZED_ALTERNATE_SETSCREENCOLOR         "�������������" 
#define LOCALIZED_ALTERNATE_SETSCRUNCH             "�����������������" 
#define LOCALIZED_ALTERNATE_SETTIMER               "���������" 
#define LOCALIZED_ALTERNATE_SETTURTLE              "����������" 
#define LOCALIZED_ALTERNATE_SETTURTLEMODE          "���������������" 
#define LOCALIZED_ALTERNATE_SETWRITE               "���������" 
#define LOCALIZED_ALTERNATE_SETWRITEPOS            "������������" 
#define LOCALIZED_ALTERNATE_SETX                   "���_x" 
#define LOCALIZED_ALTERNATE_SETXY                  "���_xy"
#define LOCALIZED_ALTERNATE_SETXYZ                 "���_xyz" 
#define LOCALIZED_ALTERNATE_SETY                   "���_y" 
#define LOCALIZED_ALTERNATE_SETZ                   "���_z" 
#define LOCALIZED_ALTERNATE_SHELL                  "��������" 
#define LOCALIZED_ALTERNATE_SHOW                   "������"
#define LOCALIZED_ALTERNATE_SHOWNP                 "���������" 
#define LOCALIZED_ALTERNATE_SHOWN_                 "�������?" 
#define LOCALIZED_ALTERNATE_SHOWTURTLE             "�������������"
#define LOCALIZED_ALTERNATE_SIN                    "sin" 
#define LOCALIZED_ALTERNATE_SOUND                  "����" 
#define LOCALIZED_ALTERNATE_SPLITSCREEN            "���������" 
#define LOCALIZED_ALTERNATE_SQRT                   "������"
#define LOCALIZED_ALTERNATE_SS                     "��" 
#define LOCALIZED_ALTERNATE_ST                     "��"
#define LOCALIZED_ALTERNATE_STANDOUT               "�����" 
#define LOCALIZED_ALTERNATE_STATICCREATE           "���������������" 
#define LOCALIZED_ALTERNATE_STATICDELETE           "��������������" 
#define LOCALIZED_ALTERNATE_STATICUPDATE           "���������������" 
#define LOCALIZED_ALTERNATE_STATUS                 "������" 
#define LOCALIZED_ALTERNATE_STEP                   "���" 
#define LOCALIZED_ALTERNATE_STEPPED                "����������" 
#define LOCALIZED_ALTERNATE_STOP                   "����" 
#define LOCALIZED_ALTERNATE_SUBSTRINGP             "�����������" 
#define LOCALIZED_ALTERNATE_SUBSTRING_             "���������?" 
#define LOCALIZED_ALTERNATE_SUM                    "�����"
#define LOCALIZED_ALTERNATE_TAG                    "�����" 
#define LOCALIZED_ALTERNATE_TAN                    "tg" 
#define LOCALIZED_ALTERNATE_TEST                   "����" 
#define LOCALIZED_ALTERNATE_TEXT                   "�����" 
#define LOCALIZED_ALTERNATE_TEXTSCREEN             "��������������" 
#define LOCALIZED_ALTERNATE_THING                  "������" 
#define LOCALIZED_ALTERNATE_THROW                  "���������" 
#define LOCALIZED_ALTERNATE_TIME                   "�����" 
#define LOCALIZED_ALTERNATE_TIMEMILLI              "���������" 
#define LOCALIZED_ALTERNATE_TO                     "���"
#define LOCALIZED_ALTERNATE_TONE                   "���" 
#define LOCALIZED_ALTERNATE_TOWARDS                "�������" 
#define LOCALIZED_ALTERNATE_TOWARDSXYZ             "�������_xyz" 
#define LOCALIZED_ALTERNATE_TRACE                  "�����" 
#define LOCALIZED_ALTERNATE_TRACED                 "��������������" 
#define LOCALIZED_ALTERNATE_TS                     "��" 
#define LOCALIZED_ALTERNATE_TURTLE                 "�������" 
#define LOCALIZED_ALTERNATE_TURTLEMODE             "������������" 
#define LOCALIZED_ALTERNATE_TURTLES                "�������" 
#define LOCALIZED_ALTERNATE_TYPE                   "������" 
#define LOCALIZED_ALTERNATE_UNBURY                 "����������" 
#define LOCALIZED_ALTERNATE_UNSTEP                 "�������" 
#define LOCALIZED_ALTERNATE_UNTRACE                "��������" 
#define LOCALIZED_ALTERNATE_UP                     "�����" 
#define LOCALIZED_ALTERNATE_UPPERCASE              "���������" 
#define LOCALIZED_ALTERNATE_UPPITCH                "����������" 
#define LOCALIZED_ALTERNATE_WAIT                   "���"
#define LOCALIZED_ALTERNATE_WINDOW                 "����" 
#define LOCALIZED_ALTERNATE_WINDOWCREATE           "����������"
#define LOCALIZED_ALTERNATE_WINDOWENABLE           "�����������" 
#define LOCALIZED_ALTERNATE_WINDOWDELETE           "���������"
#define LOCALIZED_ALTERNATE_WINDOWFILEEDIT         "���������������" 
#define LOCALIZED_ALTERNATE_WINDOWSET              "����������" 
#define LOCALIZED_ALTERNATE_WINHELP                "����������" 
#define LOCALIZED_ALTERNATE_WORD                   "�����"
#define LOCALIZED_ALTERNATE_WORDP                  "�������" 
#define LOCALIZED_ALTERNATE_WORD_                  "�����?" 
#define LOCALIZED_ALTERNATE_WRAP                   "�������" 
#define LOCALIZED_ALTERNATE_WRITEPOS               "�������" 
#define LOCALIZED_ALTERNATE_WRITER                 "��������" 
#define LOCALIZED_ALTERNATE_YESNOBOX               "���������" 
#define LOCALIZED_ALTERNATE_YIELD                  "��������" 
#define LOCALIZED_ALTERNATE_ZOOM                   "�������" 

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      "&OK" // NOT_YET_LOCALIZED
#define LOCALIZED_GENERAL_CANCELBUTTON  "&������" 
#define LOCALIZED_GENERAL_APPLYBUTTON   "&���������" 

#define LOCALIZED_GENERAL_PRODUCTNAME   "FMSLogo" 



//
// The menu options on the main window 
//
#define LOCALIZED_FILE        "&����" 
#define LOCALIZED_FILE_NEW    "&�����" 
#define LOCALIZED_FILE_LOAD   "&���������..." 
#define LOCALIZED_FILE_OPEN   "&�������..."  
#define LOCALIZED_FILE_SAVE   "&���������"  
#define LOCALIZED_FILE_SAVEAS "��������� &���..." 
#define LOCALIZED_FILE_EDIT   "&�������������..." 
#define LOCALIZED_FILE_ERASE  "�&������..." 
#define LOCALIZED_FILE_EXIT   "&�����" 

#define LOCALIZED_BITMAP               "&�������" 
#define LOCALIZED_BITMAP_NEW           "&�����" 
#define LOCALIZED_BITMAP_LOAD          "&���������..." 
#define LOCALIZED_BITMAP_SAVE          "&���������" 
#define LOCALIZED_BITMAP_SAVEAS        "��������� &���..." 
#define LOCALIZED_BITMAP_PRINT         "&������..." 
#define LOCALIZED_BITMAP_PRINTERSETUP  "�&������� ��������..." 
#define LOCALIZED_BITMAP_ACTIVEAREA    "&�������� ����..." 

#define LOCALIZED_SET                  "&����������" 
#define LOCALIZED_SET_PENSIZE          "&������ ����..." 
#define LOCALIZED_SET_LABELFONT        "&����� ��������..." 
#define LOCALIZED_SET_COMMANDERFONT    "��&��� ���������� ����..." 
#define LOCALIZED_SET_PENCOLOR         "��&�� ����..." 
#define LOCALIZED_SET_FLOODCOLOR       "�&��� �������..." 
#define LOCALIZED_SET_SCREENCOLOR      "&���� ������..." 

#define LOCALIZED_ZOOM                 "&����"  
#define LOCALIZED_ZOOM_IN              "&���������" 
#define LOCALIZED_ZOOM_OUT             "�&��������" 
#define LOCALIZED_ZOOM_NORMAL          "&�����" 

#define LOCALIZED_HELP                 "&������"  
#define LOCALIZED_HELP_INDEX           "&������" 
#define LOCALIZED_HELP_TUTORIAL        "�&�������� ���������" 
#define LOCALIZED_HELP_DEMO            "&����"  
#define LOCALIZED_HELP_EXAMPLE         "&�������" 
#define LOCALIZED_HELP_RELEASENOTES    "�&��������� � �������" 
#define LOCALIZED_HELP_ABOUTFMSLOGO    "&� "LOCALIZED_GENERAL_PRODUCTNAME"..."
#define LOCALIZED_HELP_MS              "&� MS..." 
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   "������-����������" 
#define LOCALIZED_HELP_ENGLISHTOLANG   "�����-�������" 

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              "������� �������� ����" 
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       "��������� ������� ������ � ���������� ��������� �����������" 
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        "Y-��������" 
#define LOCALIZED_SELECTACTIVEAREA_YLOW         "Y-������"  
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        "X-�����" 
#define LOCALIZED_SELECTACTIVEAREA_XLOW         "X-������" 
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH "���������� ����� �� ����:" 
#define LOCALIZED_SELECTACTIVEAREA_RESET        "&�����"  
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON 
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON 


//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     "����������" 
#define LOCALIZED_POPUP_CUT                      "��������" 
#define LOCALIZED_POPUP_PASTE                    "��������" 
#define LOCALIZED_POPUP_DELETE                   "�������" 
#define LOCALIZED_POPUP_UNDO                     "��������" 
#define LOCALIZED_POPUP_SELECTALL                "�������� ��" 
#define LOCALIZED_POPUP_HELP                     "����� �� �������" 

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   "��������" 

#define LOCALIZED_EDITOR_FILE                    "&����" 
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        "&��������� � �����\tCtrl+D" 
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    "�&��������" 
#define LOCALIZED_EDITOR_FILE_PRINT              "&������..."  
#define LOCALIZED_EDITOR_FILE_EXIT               "&�����"  

#define LOCALIZED_EDITOR_EDIT                    "&�������������" 
#define LOCALIZED_EDITOR_EDIT_UNDO               "&������\tCtrl+Z" 
#define LOCALIZED_EDITOR_EDIT_CUT                "&��������\tCtrl+X" 
#define LOCALIZED_EDITOR_EDIT_COPY               "&����������\tCtrl+C" 
#define LOCALIZED_EDITOR_EDIT_PASTE              "�&�������\tCtrl+V" 
#define LOCALIZED_EDITOR_EDIT_DELETE             "&�������\tDel" 
#define LOCALIZED_EDITOR_EDIT_CLEARALL           "�&������� ��\tCtrl+Del" 
#define LOCALIZED_EDITOR_EDIT_SELECTALL          "�&������� ��\tCtrl+A" 

#define LOCALIZED_EDITOR_SEARCH                  "&�����" 
#define LOCALIZED_EDITOR_SEARCH_FIND             "&�����...\tCtrl+F" 
#define LOCALIZED_EDITOR_SEARCH_REPLACE          "&������...\tCtrl+H"  
#define LOCALIZED_EDITOR_SEARCH_NEXT             "&���������\tF3"  

#define LOCALIZED_EDITOR_SET                     "&����������"  
#define LOCALIZED_EDITOR_SET_FONT                "&�����..."  

#define LOCALIZED_EDITOR_TEST                    "����!" 

#define LOCALIZED_EDITOR_HELP                    "&������"  
#define LOCALIZED_EDITOR_HELP_INDEX              "&������" 
#define LOCALIZED_EDITOR_HELP_EDITOR             "&��������" 
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        "�&���� �� �������\tF1"


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES // NOT_YET_LOCALIZED
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    "&��������� � �����" 
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       "&�� ���������" 
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON 
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       "� ������� ������������ ���� �� ���������� ������. ���� �� �������, ��� ������ ����� ��������.  " 
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       "��������� ������ ����� �������?"  


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     "��������" 
#define LOCALIZED_COMMANDER_HALT                "�������" 
#define LOCALIZED_COMMANDER_TRACE               "�����" 
#define LOCALIZED_COMMANDER_NOTRACE             "��������" 
#define LOCALIZED_COMMANDER_PAUSE               "�����" 
#define LOCALIZED_COMMANDER_STATUS              "������" 
#define LOCALIZED_COMMANDER_NOSTATUS            "����������" 
#define LOCALIZED_COMMANDER_STEP                "���" 
#define LOCALIZED_COMMANDER_UNSTEP              "�������" 
#define LOCALIZED_COMMANDER_RESET               "�����" 
#define LOCALIZED_COMMANDER_EXECUTE             "���������" 
#define LOCALIZED_COMMANDER_EDALL               "��������" 

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        "������" 
#define LOCALIZED_STATUS_PEN                    "����" 
#define LOCALIZED_STATUS_CONTACT                "����:" 
#define LOCALIZED_STATUS_WIDTH                  "������:" 
#define LOCALIZED_STATUS_STYLE                  "�����:" 
#define LOCALIZED_STATUS_ORIENTATION            "����������" 
#define LOCALIZED_STATUS_PITCH                  "�����:" 
#define LOCALIZED_STATUS_HEADING                "�����������:" 
#define LOCALIZED_STATUS_ROLL                   "����:" 
#define LOCALIZED_STATUS_TURTLE                 "�������" 
#define LOCALIZED_STATUS_POSITION               "�������(XYZ):" 
#define LOCALIZED_STATUS_WHICH                  "�����:" 
#define LOCALIZED_STATUS_VISIBILITY             "���������:" 
#define LOCALIZED_STATUS_COLOR                  "����" 
#define LOCALIZED_STATUS_PENCOLOR               "����(RGB):" 
#define LOCALIZED_STATUS_FLOODCOLOR             "�������(RGB):" 
#define LOCALIZED_STATUS_SCREENCOLOR            "�����(RGB):" 
#define LOCALIZED_STATUS_PALETTE                "������������ �������:" 
#define LOCALIZED_STATUS_KERNEL                 "����" 
#define LOCALIZED_STATUS_CALLS                  "������:" 
#define LOCALIZED_STATUS_PEAKMEMORY             "������� ������:" 

#define LOCALIZED_STATUS_PENREVERSE     "������" 
#define LOCALIZED_STATUS_PENNORMAL      "�����" 
#define LOCALIZED_STATUS_PENERASE       "������" 
#define LOCALIZED_STATUS_PENUP          "�������" 
#define LOCALIZED_STATUS_PENDOWN        "�������" 
#define LOCALIZED_STATUS_PENSHOWN       "������" 
#define LOCALIZED_STATUS_PENHIDDEN      "�� ������" 
#define LOCALIZED_STATUS_POLYGONS       "�������" 
#define LOCALIZED_STATUS_VECTORS        "�������" 
#define LOCALIZED_STATUS_NODES          "������" 
#define LOCALIZED_STATUS_NOT_APPLICABLE "N/A" 

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON 
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON 
#define LOCALIZED_SELECTPROCEDURE_ALL           "&���" 
#define LOCALIZED_ERASEPROCEDURE                "������� ���������" 
#define LOCALIZED_EDITPROCEDURE                 "������������� ���������" 


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     "���������� ����" 
#define LOCALIZED_SETCOLOR_PENCOLOR            "���� ����" 
#define LOCALIZED_SETCOLOR_FLOODCOLOR          "���� �������" 
#define LOCALIZED_SETCOLOR_SCREENCOLOR         "���� ������" 
#define LOCALIZED_SETCOLOR_RED                 "�������" 
#define LOCALIZED_SETCOLOR_GREEN               "������" 
#define LOCALIZED_SETCOLOR_BLUE                "�����" 
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON 
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON 
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON 

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   "������ ����" 
#define LOCALIZED_SETPENSIZE_SIZE              "�������" 
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON 
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON 
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON 


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     "� "LOCALIZED_GENERAL_PRODUCTNAME 
#define LOCALIZED_ABOUTFMS_VERSION             LOCALIZED_GENERAL_PRODUCTNAME" ������ "FMSLOGO_VERSION 
#define LOCALIZED_ABOUTFMS_GUI                 "��� ������� ������ by George Mills (mills@softronix.com)\nSoftronics, Inc.\nhttp:\x2F/www.softronix.com/" 
#define LOCALIZED_ABOUTFMS_CORE                "���� ������� ����� (bh@cs.berkeley.edu)\n�������������� ����������� ������" 
#define LOCALIZED_ABOUTFMS_INSTALLER           "����������� ���������� �� Nullsoft Scriptable Install \nhttp:\x2F/nsis.sourceforge.net/" 
#define LOCALIZED_ABOUTFMS_ADVENTURE           "The Great Logo Adventure (ISBN 0-9651934-6-2)\n���������� � ���������� ������ ��������\n�������� �� http:\x2F/www.softronix.com/" 
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       "���������� ������ ����� (yehuka@softhome.net)\n� ����� ���������� (erich.neuwirth@univie.ac.at)" 
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME" ���������������� ��������\n��. �������� ���" 
#define LOCALIZED_ABOUTFMS_NEWSGROUP           "������ �������� � ���������: comp.lang.logo\n�������� ����� ��\nhttp:\x2F/groups.yahoo.com/group/LogoForum/" 
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     "�������� ���������� ������� ����������,\n�� MultiMedia Logic �� Softronics, Inc." 
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON 


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      "� FMS" 
#define LOCALIZED_ABOUTMS_FMS                  "FMS �������� 'Fight Multiple Sclerosis'." 
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     "����������, ����������� ����������� ������\nNational Multiple Sclerosis Society.\nhttp:\x2F/www.nmss.org\n1-800-FIGHT-MS" 
#define LOCALIZED_ABOUTMS_OK                   LOCALIZED_GENERAL_OKBUTTON 


//
// Strings on the SELECTBOX Dialog box
//
#define LOCALIZED_SELECTBOX_OK                 LOCALIZED_GENERAL_OKBUTTON 
#define LOCALIZED_SELECTBOX_CANCEL             LOCALIZED_GENERAL_CANCELBUTTON


// 
// Strings in various other dialog boxes
// 

#define LOCALIZED_CHANGESINEDITORMAYBELOST  "Changes in this edit session may be lost.\n\nDo you really want to exit "LOCALIZED_GENERAL_PRODUCTNAME"?" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITSESSIONISRUNNING      "An Edit session is running" // NOT_YET_LOCALIZED

#define LOCALIZED_NOTHALTEDREALLYEXIT        LOCALIZED_GENERAL_PRODUCTNAME" does not like exiting while not halted.\n\nDo you really want to exit "LOCALIZED_GENERAL_PRODUCTNAME"?" // NOT_YET_LOCALIZED
#define LOCALIZED_NOTHALTEDREALLYHALT        LOCALIZED_GENERAL_PRODUCTNAME" does not like exiting while not halted.\n\nDo you really want to Halt "LOCALIZED_GENERAL_PRODUCTNAME"?" // NOT_YET_LOCALIZED
#define LOCALIZED_LOGOISNOTHALTED            LOCALIZED_GENERAL_PRODUCTNAME" is not Halted" // NOT_YET_LOCALIZED

#define LOCALIZED_COULDNOTWRITEBMP            "Could not write .bmp" // NOT_YET_LOCALIZED
#define LOCALIZED_COULDNOTOPENBMP             "Could not open .bmp" // NOT_YET_LOCALIZED
#define LOCALIZED_COULDNOTCREATEBMP           "Unable to create Windows 3.0 bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_NOTVALIDBMP                 "Not a Windows 3.0 bitmap" // NOT_YET_LOCALIZED

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         "You have not saved to disk" // NOT_YET_LOCALIZED
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     "Executing a new will erase all definitions.\n\nContinue with New?" // NOT_YET_LOCALIZED
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE "The file being loaded will be merged into your workspace\nand may overwrite your unsaved changes.\n\nContinue with Load?" // NOT_YET_LOCALIZED
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    "This will erase all of your unsaved changes.\n\nContinue with Open?" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITORISOPEN                  "Did you know you have an edit session running?\n\nAny changes in this edit session are not being saved." // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_CANTREADFILE            "Unable to read file \"%s\" from disk" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTWRITEFILE           "Unable to write file \"%s\" to disk" // NOT_YET_LOCALIZED

#define LOCALIZED_SAVETOWORKSPACE                "Save to Workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_CONTENTSCHANGED                "Contents Changed" // NOT_YET_LOCALIZED
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE "The contents have changed.\nWould you like to save the changes to the workspace?" // NOT_YET_LOCALIZED



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  "There was a problem saving the contents of the editor to the workspace.  The cursor will be positioned just after last successful definition.\n\nCheck the Commander for possible error message." // NOT_YET_LOCALIZED
#define LOCALIZED_RETURNTOEDIT                  "Return to the editor?" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITFAILEDTOLOAD              LOCALIZED_SAVETOWORKSPACE // NOT_YET_LOCALIZED



// 
//  Strings used in the File-Open filters
//
#define LOCALIZED_FILEFILTER_ALLFILES "All Files (*.*)|*.*|" // NOT_YET_LOCALIZED
#define LOCALIZED_FILEFILTER_LOGO     "Logo Files (*.lgo)|*.lgo|"LOCALIZED_FILEFILTER_ALLFILES // NOT_YET_LOCALIZED
#define LOCALIZED_FILEFILTER_IMAGE    "Bitmap Files (*.bmp)|*.bmp|GIF Files (*.gif)|*.gif|"LOCALIZED_FILEFILTER_ALLFILES // NOT_YET_LOCALIZED



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             " stops\n" // NOT_YET_LOCALIZED
#define LOCALIZED_TRACING_OUTPUTS           " outputs %s\n" // NOT_YET_LOCALIZED
#define LOCALIZED_TRACING_MAKE              "Make %s %s" // NOT_YET_LOCALIZED
#define LOCALIZED_TRACING_PPROP             "Pprop %s %s %s" // NOT_YET_LOCALIZED
#define LOCALIZED_TRACING_LOCATION          " in %s\n%s" // NOT_YET_LOCALIZED

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  "Single Step" // NOT_YET_LOCALIZED

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  "%s defined\n" // NOT_YET_LOCALIZED


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    "erase" // NOT_YET_LOCALIZED
#define LOCALIZED_PENMODE_REVERSE  "reverse" // NOT_YET_LOCALIZED
#define LOCALIZED_PENMODE_PAINT    "paint" // NOT_YET_LOCALIZED

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          "Logo: Fatal Internal Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       "Logo: Out of memory" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_OUTOFMEMORY            "Out of memory" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_STACKOVERFLOW          "stack overflow" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      "turtle out of bounds" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BADGRAPHINIT           "couldn't initialize graphics" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BADDATA                "%p doesn't like %s as input" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DIDNTOUTPUT            "%p didn't output to %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        "not enough inputs to %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_TOOMUCH                "too much inside ()'s" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    "You don't say what to do with %s" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_PARENMISMATCH          "too many ('s" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NOVALUE                "%s has no value" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        "unexpected ')'" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      "unexpected ']'" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        "unexpected '}'" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DONTKNOWHOWTO          "I don't know how to %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NOCATCHTAG             "Can't find catch tag for %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_ALREADYDEFINED         "%p is already defined" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_STOPPING               "Stopping..." // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_ALREADYDRIBBLING       "Already dribbling" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM                   "File system error: %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          "Could not open file" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         "Unable to open file: %t" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       "File already open" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           "File not open" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  "Could not create editor file" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   "Could not launch the editor"  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    "Could not read editor file"  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_IFWARNING              "Assuming you mean IFELSE, not IF" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_SHADOWWARNING          "%p shadowed by local in procedure call" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_USER                   "Throw \"Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_ISPRIMITIVE            "%p is a primitive" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_TONOTINSIDE            "Can't use TO inside a procedure" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_ATTOPLEVEL             "Can only use %p inside a procedure" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_ATTOPLEVEL2            "You must be in a procedure to use OUTPUT or STOP" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NOTEST                 "%p without TEST" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BADMACROOUTPUT         "Macro output %s instead of a list" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DEEPEND                "END inside multi-line instruction" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DEEPENDIN              "END inside multi-line instruction in %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_UNKNOWN                "Unknown error condition - internal error." // NOT_YET_LOCALIZED

#define LOCALIZED_PAUSING                      "Pausing..." // NOT_YET_LOCALIZED


//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      "Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BADINPUT             "Bad input" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    "Input is not paired" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_CANTOPENPORT         "Could not open port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTCLOSEPORT        "Could not close port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTFLUSHPORT        "Could not flush port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTDCBONPORT        "Could not build dcb on port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTSETPORT          "Could not set port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_PORTALREADYOPEN      "Port is already open" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_PORTNOTOPEN          "Port is not open" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FIRSTINPUTNOTANARRY  "First input must be an array" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   "%s already exists" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    "%s does not exist" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_DLLNOTLOADED          "DLL is not loaded" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLLOADFAILED         "DLL load failed" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    "Invalid data type input" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  "Invalid output type" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   "Function not found" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  "Not all Type/Data inputs are paired" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_NETWORK               "Network Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKRECEIVE        "Network Receive Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKSEND           "Network Send Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       "Unexpected Error, Network may be shutdown" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     "Not started" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED "Already started" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKALREADYON      "Already on" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKALREADYOFF     "Already off" // NOT_YET_LOCALIZED

// The rest of the network errors shouldn't really be seen -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         "Name too long" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      "Not initialized" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      "System not ready" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED "Version is not supported" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   "Can't send after socket shutdown" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         "Interrupted system call" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    "Authoritative Answer: Host not found" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH "Non-Authoritative: Host not found. See NETSTARTUP" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      "Non-recoverable error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNODATA              "No data record available" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       "Bad file number" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          "Operation would block" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       "Operation now in progress" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   "Operation already in progress" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKBADADDRESS          "Bad address" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     "Destination address required" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      "Message too long" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      "Protocol family not supported" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         "Directory not empty" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     "Application limit has been reached" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           "Disk quota exceeded" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        "Too many open files" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        "Access denied" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          "Socket operation on non-socket" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    "Can't assign requested address" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKADDRINUSE           "Address already in use" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      "Address family not supported by protocol family" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            "Connection timed out" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    "Socket type not supported" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   "Protocol not supported" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOBUFFER            "No space in buffer" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    "Socket is already connected" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        "Socket is not connected" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         "Bad protocol option" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     "Connection reset by peer" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     "Software caused connection abort" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKISDOWN              "Network is down" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKRESET               "Network was reset" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   "Connection refused" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          "Host is down" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   "Host is unreachable" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        "Protocol is wrong type for socket" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   "Operation not supported on socket" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         "No path to remote host was found" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         "Too many references" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_POLYSTART               "PolyStart Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED "You already have a Polygon started" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_POLYEND                 "PolyEnd Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       "You have not started a Polygon" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     "You must have at least 3 vectors to define a polygon" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_SOUND                 "Sound Error" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_MIDI                  "MIDI Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     "Invalid MIDI device" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MIDIALREADYOPEN       "Already open" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MIDINOTOPEN           "Not open" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      "No Text in Clipboard" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_MCI                   "MCI Error" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_TIMERNOTFOUND         "Timer not found" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       "Online help is unavailable because hhctrl.ocx could not be loaded."  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_HHCTRLATOMNOTFOUND    "Online help is unavailable because hhctrl.ocx does not contain ATOM_HTMLHELP_API_ANSI."  // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_BADCOMMANDLINE        "Invalid Command Line"  // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_TMPNOTDEFINED         "The environment variable TMP is not defined or invalid.\n"LOCALIZED_GENERAL_PRODUCTNAME" will attempt to use C:\\ for storing temporary files" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_GIFSAVEFAILED         "Problem Generating GIF, check memory and diskspace" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_GIFREADFAILED         "Problem Reading GIF, check memory and diskspace" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  "BitMap Index out of range" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPCUTFAILED        "Cut failed, Possibly not enough Memory" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPFITFAILED        "Fit failed, Possibly not enough Memory" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    "Nothing to Paste"  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  "BitMap at Index must be initialized with a bitmap"  // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_BADTURTLEID             "Bad Turtle Id" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      "Turtle %d has no picture, will Halt" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_FONTNOTFOUND            "Sorry, no font named %s was found.  Choose one of the following:\n" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_PRINTERCANTSCALE        "Print driver does not support this function"  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTDRAWIMAGE           "Cannot draw image" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        "Cannot extract image" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_SUBCODE                 "Sub Code" // NOT_YET_LOCALIZED

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         "Input:" // NOT_YET_LOCALIZED
#define LOCALIZED_PROMPT_TO     "To Mode (Cancel to End)" // NOT_YET_LOCALIZED
#define LOCALIZED_PROMPT_LIST   "List Mode (Cancel to Halt)" // NOT_YET_LOCALIZED
#define LOCALIZED_PROMPT_PAUSE  "Pause Mode (Cancel to Continue)" // NOT_YET_LOCALIZED
#define LOCALIZED_PROMPT_INPUT  "Input Mode (Cancel to Halt)" // NOT_YET_LOCALIZED

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      "Changed to \"%s\"" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_CHDIRFAILED         "Could not chdir to directory \"%s\"" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_POPPEDTO            "Popped to \"%s\"" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_MKDIRSUCCEEDED      "Now in newly created directory \"%s\""  // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_MKDIRFAILED         "Failed to create directory \"%s\""  // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_RMDIRSUCCEEDED      "Removed directory \"%s\""  // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_RMDIRFAILED         "Failed to remove directory \"%s\""  // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  "The directory does not exist." // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY "Make sure the directory is empty before trying to remove it." // NOT_YET_LOCALIZED


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       "Logo Picture" // NOT_YET_LOCALIZED

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    "Active Area" // NOT_YET_LOCALIZED
#define LOCALIZED_INFORMATION   "Information" // NOT_YET_LOCALIZED
#define LOCALIZED_WARNING       "Warning" // NOT_YET_LOCALIZED
#define LOCALIZED_UNTITLED      "Untitled" // NOT_YET_LOCALIZED
#define LOCALIZED_UNKNOWN       "Unknown" // NOT_YET_LOCALIZED

#define LOCALIZED_UNBOUND       "Unbound" // NOT_YET_LOCALIZED

//
// Strings that explain the purpose of each menu option.
// I don't think that any of these strings can be seen by the user, 
// so you probably don't have to translate these.
//
#define LOCALIZED_STRINGTABLE_FILESAVEAS "Saves the contents of the workspace to a new file" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILEOPEN "Erases the current workspace and loads a Logo program as the new workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILELOAD "Locates and loads a Logo program into the current workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILENEW "Erases the contents of the workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILESAVE "Saves the contents of the workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILEEDIT "Selects a procedure to edit" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILEERASE "Selects a procedure to erase" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EXIT "Exits Logo" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_BITMAPNEW "Clears the screen" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_BITMAPOPEN "Loads a new screen from a Windows bitmap file" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_BITMAPSAVE "Saves the contents of the screen to a bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_BITMAPSAVEAS "Saves the contents of the screen to a different file" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_BITMAPPRINT "Prints the contents of the screen" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_BITMAPPRINTERSETUP "Configures your printer" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_BITMAPPRINTERAREA "Sets the area of the screen that will be printed or saved to a bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_SETPENSIZE "Sets the thickness of the turtle's pen" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_SETFONT "Sets the font that is used by the LABEL command" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_SETCOMMANDERFONT "Sets the font used in the commander window" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_SETPENCOLOR "Sets the color of the turtle's pen" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_SETFLOODCOLOR "Sets the color used by the FILL command" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_SETSCREENCOLOR "Clears the screen and sets it to a new color" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_ZOOMIN "Zooms in on the screen" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_ZOOMOUT "Zooms out on the screen" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_ZOOMNORMAL "Restores the screen to its original size" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELP "Opens an index of help topics" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPMCI "Opens an index of help topics for the Media Control Interface" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPHELP "Opens help on using help" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPTUTORIAL "Opens a short tutorial on using "LOCALIZED_GENERAL_PRODUCTNAME // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPDEMO "Shows a demonstration of some things you can do in "LOCALIZED_GENERAL_PRODUCTNAME // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPEXAMPLES "Displays an index of the sample programs" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPRELEASENOTES "Displays the release notes for this version of "LOCALIZED_GENERAL_PRODUCTNAME // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPABOUT "Displays version and copyright information" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPABOUTMS "Displays a message about Multiple Sclerosis" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITDELETE "Deletes the current selection (and does not copy to the clipboard)" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITCLEAR "Deletes all text" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITUNDO "Undoes the previous action" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITCUT "Removes the selected text and puts it on the clipboard" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITCOPY "Copies the selected text to the clipboard" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITPASTE "Inserts the text from the clipboard at the current position" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITSELECTALL "Selects all text" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITFIND "Searches for text" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITREPLACE "Searches for text and replaces it with other text" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITFINDNEXT "Repeats the previous Find or Replace command" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITSETFONT "Sets the font for the editor window" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_TEST "Runs the selected Logo instructions" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPEDIT "Displays help on using the editor" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPEDIT_TOPIC "Displays help for Logo" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILESAVEANDEXIT "Saves and exits the current workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILESAVETOWORKSPACE "Saves the current workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILEPRINT "Prints the current workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDALLEXIT "Closes the workspace" // NOT_YET_LOCALIZED

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING "Cannot find %s" // NOT_YET_LOCALIZED


//
// The words that describe color vectors.
// These words were selected from a de facto HTML standard, so you may
// be able to find translations for the entire set on the Web.
//
#define LOCALIZED_COLOR_ALICEBLUE             "AliceBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_ANTIQUEWHITE          "AntiqueWhite" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_AQUA                  "Aqua" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_AQUAMARINE            "Aquamarine" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_AZURE                 "Azure" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_BEIGE                 "Beige" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_BISQUE                "Bisque" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_BLACK                 "Black" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_BLANCHEDALMOND        "BlanchedAlmond" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_BLUE                  "Blue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_BLUEVIOLET            "BlueViolet" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_BROWN                 "Brown" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_BURLYWOOD             "BurlyWood" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_CADETBLUE             "CadetBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_CHARTREUSE            "Chartreuse" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_CHOCOLATE             "Chocolate" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_CORAL                 "Coral" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_CORNFLOWERBLUE        "CornflowerBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_CORNSILK              "Cornsilk" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_CRIMSON               "Crimson" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_CYAN                  "Cyan" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKBLUE              "DarkBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKCYAN              "DarkCyan" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKGOLDENROD         "DarkGoldenRod" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKGRAY              "DarkGray" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKGREEN             "DarkGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKGREY              "DarkGrey" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKKHAKI             "DarkKhaki" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKMAGENTA           "DarkMagenta" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKOLIVEGREEN        "DarkOliveGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKORANGE            "DarkOrange" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKORCHID            "DarkOrchid" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKRED               "DarkRed" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKSALMON            "DarkSalmon" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKSEAGREEN          "DarkSeaGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKSLATEBLUE         "DarkSlateBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKSLATEGRAY         "DarkSlateGray" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKSLATEGREY         "DarkSlateGrey" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKTURQUOISE         "DarkTurquoise" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DARKVIOLET            "DarkViolet" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DEEPPINK              "DeepPink" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DEEPSKYBLUE           "DeepSkyBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DIMGRAY               "DimGray" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DIMGREY               "DimGrey" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_DODGERBLUE            "DodgerBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_FIREBRICK             "FireBrick" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_FLORALWHITE           "FloralWhite" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_FORESTGREEN           "ForestGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_FUCHSIA               "Fuchsia" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_GAINSBORO             "Gainsboro" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_GHOSTWHITE            "GhostWhite" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_GOLD                  "Gold" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_GOLDENROD             "GoldenRod" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_GRAY                  "Gray" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_GREEN                 "Green" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_GREENYELLOW           "GreenYellow" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_GREY                  "Grey" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_HONEYDEW              "HoneyDew" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_HOTPINK               "HotPink" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_INDIANRED             "IndianRed" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_INDIGO                "Indigo" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_IVORY                 "Ivory" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_KHAKI                 "Khaki" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LAVENDER              "Lavender" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LAVENDERBLUSH         "LavenderBlush" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LAWNGREEN             "LawnGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LEMONCHIFFON          "LemonChiffon" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTBLUE             "LightBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTCORAL            "LightCoral" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTCYAN             "LightCyan" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTGOLDENRODYELLOW  "LightGoldenRodYellow" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTGRAY             "LightGray" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTGREEN            "LightGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTGREY             "LightGrey" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTPINK             "LightPink" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTSALMON           "LightSalmon" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTSEAGREEN         "LightSeaGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTSKYBLUE          "LightSkyBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTSLATEGRAY        "LightSlateGray" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTSLATEGREY        "LightSlateGrey" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTSTEELBLUE        "LightSteelBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIGHTYELLOW           "LightYellow" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIME                  "Lime" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LIMEGREEN             "LimeGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_LINEN                 "Linen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MAGENTA               "Magenta" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MAROON                "Maroon" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MEDIUMAQUAMARINE      "MediumAquaMarine" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MEDIUMBLUE            "MediumBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MEDIUMORCHID          "MediumOrchid" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MEDIUMPURPLE          "MediumPurple" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MEDIUMSEAGREEN        "MediumSeaGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MEDIUMSLATEBLUE       "MediumSlateBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MEDIUMSPRINGGREEN     "MediumSpringGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MEDIUMTURQUOISE       "MediumTurquoise" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MEDIUMVIOLETRED       "MediumVioletRed" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MIDNIGHTBLUE          "MidnightBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MINTCREAM             "MintCream" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MISTYROSE             "MistyRose" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_MOCCASIN              "Moccasin" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_NAVAJOWHITE           "NavajoWhite" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_NAVY                  "Navy" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_OLDLACE               "OldLace" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_OLIVE                 "Olive" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_OLIVEDRAB             "OliveDrab" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_ORANGE                "Orange" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_ORANGERED             "OrangeRed" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_ORCHID                "Orchid" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_PALEGOLDENROD         "PaleGoldenRod" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_PALEGREEN             "PaleGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_PALETURQUOISE         "PaleTurquoise" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_PALEVIOLETRED         "PaleVioletRed" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_PAPAYAWHIP            "PapayaWhip" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_PEACHPUFF             "PeachPuff" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_PERU                  "Peru" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_PINK                  "Pink" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_PLUM                  "Plum" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_POWDERBLUE            "PowderBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_PURPLE                "Purple" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_RED                   "Red" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_ROSYBROWN             "RosyBrown" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_ROYALBLUE             "RoyalBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SADDLEBROWN           "SaddleBrown" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SALMON                "Salmon" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SANDYBROWN            "SandyBrown" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SEAGREEN              "SeaGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SEASHELL              "SeaShell" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SIENNA                "Sienna" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SILVER                "Silver" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SKYBLUE               "SkyBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SLATEBLUE             "SlateBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SLATEGRAY             "SlateGray" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SLATEGREY             "SlateGrey" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SNOW                  "Snow" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_SPRINGGREEN           "SpringGreen" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_STEELBLUE             "SteelBlue" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_TAN                   "Tan" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_TEAL                  "Teal" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_THISTLE               "Thistle" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_TOMATO                "Tomato" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_TURQUOISE             "Turquoise" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_VIOLET                "Violet" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_WHEAT                 "Wheat" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_WHITE                 "White" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_WHITESMOKE            "WhiteSmoke" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_YELLOW                "Yellow" // NOT_YET_LOCALIZED
#define LOCALIZED_COLOR_YELLOWGREEN           "YellowGreen" // NOT_YET_LOCALIZED

//
// The name of each "window class" that DEBUGWINDOWS prints.
// These should match the cooresponding terms that is used
// in the  LOCALIZED_ALTERNATE_*CREATE procedures.
//
#define LOCALIZED_WINDOWCLASSNAME_WINDOW       "Window" // NOT_YET_LOCALIZED
#define LOCALIZED_WINDOWCLASSNAME_STATIC       "Static" // NOT_YET_LOCALIZED
#define LOCALIZED_WINDOWCLASSNAME_LISTBOX      "ListBox" // NOT_YET_LOCALIZED
#define LOCALIZED_WINDOWCLASSNAME_COMBOBOX     "ComboBox" // NOT_YET_LOCALIZED
#define LOCALIZED_WINDOWCLASSNAME_BUTTON       "Button" // NOT_YET_LOCALIZED
#define LOCALIZED_WINDOWCLASSNAME_SCROLLBAR    "ScrollBar" // NOT_YET_LOCALIZED
#define LOCALIZED_WINDOWCLASSNAME_GROUPBOX     "GroupBox" // NOT_YET_LOCALIZED
#define LOCALIZED_WINDOWCLASSNAME_RADIOBUTTON  "RadioButton" // NOT_YET_LOCALIZED
#define LOCALIZED_WINDOWCLASSNAME_CHECKBOX     "CheckBox" // NOT_YET_LOCALIZED
#define LOCALIZED_WINDOWCLASSNAME_DIALOG       "Dialog" // NOT_YET_LOCALIZED
