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
/////////////////////////////////////////////////////////////////////////////

//
// Localized "alternate" spellings of Logo reserved words
//
#define LOCALIZED_ALTERNATE_TRUE     "������" 
#define LOCALIZED_ALTERNATE_FALSE    "����" 
#define LOCALIZED_ALTERNATE_END      "�����"
#define LOCALIZED_ALTERNATE_TOPLEVEL "��������������" 
#define LOCALIZED_ALTERNATE_SYSTEM   "�������" 

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
#define LOCALIZED_ALTERNATE_ARITY                  "arity" // NOT_YET_LOCALIZED
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
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         "������������������"
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
#define LOCALIZED_ALTERNATE_HASOWNPENP             "hasownpenp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HASOWNPEN_             "hasownpen?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HEADING                "�����������" 
#define LOCALIZED_ALTERNATE_HELP                   "������" 
#define LOCALIZED_ALTERNATE_HIDETURTLE             "������������"
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
#define LOCALIZED_ALTERNATE_INT                    "����������"
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
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           "��������������������"
#define LOCALIZED_ALTERNATE_NETACCEPTON            "���������������������"
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
#define LOCALIZED_ALTERNATE_RC                     "����"
#define LOCALIZED_ALTERNATE_RCS                    "���" 
#define LOCALIZED_ALTERNATE_READCHAR               "���������" 
#define LOCALIZED_ALTERNATE_READCHARS              "����������" 
#define LOCALIZED_ALTERNATE_READER                 "�����������" 
#define LOCALIZED_ALTERNATE_READLIST               "���������" 
#define LOCALIZED_ALTERNATE_READPOS                "��������" 
#define LOCALIZED_ALTERNATE_READRAWLINE            "readrawline" // NOT_YET_LOCALIZED
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
#define LOCALIZED_GENERAL_OKBUTTON      "��" 
#define LOCALIZED_GENERAL_CANCELBUTTON  "������" 
#define LOCALIZED_GENERAL_APPLYBUTTON   "&���������" 

#define LOCALIZED_GENERAL_PRODUCTNAME   "FMSLogo" 

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  "����� ���������������� FMSLogo" 

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  "&����" 
#define LOCALIZED_FILE_NEW              "&�����" 
#define LOCALIZED_FILE_LOAD             "&���������..." 
#define LOCALIZED_FILE_OPEN             "&�������..."  
#define LOCALIZED_FILE_SAVE             "&���������"  
#define LOCALIZED_FILE_SAVEAS           "��������� &���..." 
#define LOCALIZED_FILE_SETASSCREENSAVER "Se&t As Screen Saver" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_EDIT             "&�������������..." 
#define LOCALIZED_FILE_ERASE            "�&������..." 
#define LOCALIZED_FILE_EXIT             "&�����" 

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
#define LOCALIZED_HELP_ABOUTFMSLOGO    "&� " LOCALIZED_GENERAL_PRODUCTNAME "..."
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
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        "X-������" 
#define LOCALIZED_SELECTACTIVEAREA_XLOW         "X-�����" 
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH "���������� ����� �� ����:" 
#define LOCALIZED_SELECTACTIVEAREA_RESET        "&�����"  
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON 
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON 

// The screensaver strings
#define LOCALIZED_SCREENSAVER_NAME              LOCALIZED_GENERAL_PRODUCTNAME // NOT_YET_LOCALIZED
#define LOCALIZED_SCREENSAVER_DESCRIPTION       "FMSLogo Screensaver" // NOT_YET_LOCALIZED
#define LOCALIZED_SCREENSAVER_SETTINGS_TITLE    "FMSLogo Screensaver Settings" // NOT_YET_LOCALIZED
#define LOCALIZED_SCREENSAVER_LOCATE            "&Locate ..."  // NOT_YET_LOCALIZED
#define LOCALIZED_SCREENSAVER_FILE              "Logo &File:"  // NOT_YET_LOCALIZED
#define LOCALIZED_SCREENSAVER_OK                LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SCREENSAVER_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED

// The dialog box for selecting a Startup procedure
#define LOCALIZED_SELECTSTARTUP_CAPTION               "Select a " LOCALIZED_ALTERNATE_STARTUP " instruction" // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED "Your workspace does not have a " LOCALIZED_ALTERNATE_STARTUP " instruction list defined, so nothing\nwill happen when the screensaver is loaded.\nPlease select a procedure to run when the program is loaded." // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST   "The " LOCALIZED_ALTERNATE_STARTUP " variable is not a list, so nothing will happen when the screensaver\nis loaded.\nPlease select a procedure to run when the program is loaded." // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY     "Your workspace has an empty " LOCALIZED_ALTERNATE_STARTUP " instruction list defined, so nothing will\nhappen when the screensaver is loaded.\nPlease select a procedure to run when the program is loaded." // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED   "No procedures are defined" // NOT_YET_LOCALIZED

// The warning dialog box when the user saves an empty workspace
#define LOCALIZED_EMPTYWORKSPACE_TITLE                LOCALIZED_GENERAL_PRODUCTNAME // NOT_YET_LOCALIZED
#define LOCALIZED_EMPTYWORKSPACE_MESSAGE              "There are no procedures, variables, or property lists defined,\nso the workspace will be saved as an empty file.\n\nDo you want to save the workspace anyway?" // NOT_YET_LOCALIZED

//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     "����������" 
#define LOCALIZED_POPUP_CUT                      "��������" 
#define LOCALIZED_POPUP_PASTE                    "��������" 
#define LOCALIZED_POPUP_DELETE                   "�������" 
#define LOCALIZED_POPUP_UNDO                     "��������" 
#define LOCALIZED_POPUP_REDO                     "�������" 
#define LOCALIZED_POPUP_SELECTALL                "�������� ��" 
#define LOCALIZED_POPUP_HELP                     "����� �� �������" 
#define LOCALIZED_POPUP_REMOVELINES              "Remove Selected Lines" // NOT_YET_LOCALIZED

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
#define LOCALIZED_EDITOR_EDIT_UNDO               "&��������\tCtrl+Z" 
#define LOCALIZED_EDITOR_EDIT_REDO               "&�������\tCtrl+Y" 
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

#define LOCALIZED_EDITOR_TEST                    "����"
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      "&Run Selection\tCtrl+R" // NOT_YET_LOCALIZED

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
#define LOCALIZED_ABOUTFMS                     "� " LOCALIZED_GENERAL_PRODUCTNAME 
#define LOCALIZED_ABOUTFMS_VERSION             "������"
#define LOCALIZED_ABOUTFMS_GUI                 "��� ������� ������\nSoftronics, Inc.\nhttp://www.softronix.com/" 
#define LOCALIZED_ABOUTFMS_CORE                "���� ������� �����\n�������������� ����������� ������" 
#define LOCALIZED_ABOUTFMS_INSTALLER           "����������� ���������� �� Nullsoft Scriptable Install \nhttp://nsis.sourceforge.net/" 
#define LOCALIZED_ABOUTFMS_ADVENTURE           "The Great Logo Adventure (ISBN 0-9651934-6-2)\n���������� � ���������� ������ ��������\n�������� �� http://www.softronix.com/" 
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       "���������� ������ ����� � ����� ���������" 
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME " ���������������� ��������\n��. �������� ���"
#define LOCALIZED_ABOUTFMS_NEWSGROUP           "������ �������� � ���������: comp.lang.logo\n�������� ����� ��\nhttp://groups.yahoo.com/group/LogoForum/" 
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     "��� �������� ���������� ������� ����������,\n�����������  MultiMedia Logic �� Softronics, Inc.\n��������� � ����������� �� ������� ���� �������� �����\n��������� ��������������� �����������, ����-���, bii@bsu.ru"
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON 


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      "� FMS" 
#define LOCALIZED_ABOUTMS_FMS                  "FMS �������� 'Fight Multiple Sclerosis'." 
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     "����������, ����������� ����������� ������\nNational Multiple Sclerosis Society.\nhttp://www.nmss.org\n1-800-FIGHT-MS" 
#define LOCALIZED_ABOUTMS_OK                   LOCALIZED_GENERAL_OKBUTTON 


//
// Strings on the SELECTBOX Dialog box
//
#define LOCALIZED_SELECTBOX_OK                 LOCALIZED_GENERAL_OKBUTTON 
#define LOCALIZED_SELECTBOX_CANCEL             LOCALIZED_GENERAL_CANCELBUTTON

//
// Strings on the QUESTIONBOX dialog box
//
#define LOCALIZED_QUESTIONBOX_OK               LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_QUESTIONBOX_CANCEL           LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED


// 
// Strings in various other dialog boxes
// 

#define LOCALIZED_CHANGESINEDITORMAYBELOST  "��������� � ���� ������ �������������� ����� ���� �������.\n\n�� ������������� ������ ����� �� " LOCALIZED_GENERAL_PRODUCTNAME "?"
#define LOCALIZED_EDITSESSIONISRUNNING      "����� �������������� �������" 

#define LOCALIZED_COULDNOTWRITEBMP            "�� ���� �������� .bmp" 
#define LOCALIZED_COULDNOTOPENBMP             "�� ���� ������� .bmp" 
#define LOCALIZED_COULDNOTCREATEBMP           "���������� ������� Windows 3.0 �������" 
#define LOCALIZED_NOTVALIDBMP                 "�� ��������� ������� Windows 3.0" 

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         "�� �� ��������� �� ����" 
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     "�������� ������ ������ ��� ������ �� ������� �������.\n\n���������� �����?" 
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE "����������� ���� ����� ��������� � ������� ����� ������� �������\n�, ����� �������� ���� ������������� ������.\n\n���������� ���������?" 
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    "��� �������� ������ ��� ���� ������������� ������.\n\n���������� �������?" 

#define LOCALIZED_EDITORISOPEN                  "�� ������, ��� ������� ����� ��������������?\n\n��� ��������� � ���� ������ �������������� �� ���� ���������"

#define LOCALIZED_ERROR_CANTREADFILE            "���������� ��������� ���� \"%s\" � �����" 
#define LOCALIZED_ERROR_CANTWRITEFILE           "���������� �������� ���� \"%s\" �� ����" 

#define LOCALIZED_SAVETOWORKSPACE                "��������� � ������� �������" 
#define LOCALIZED_CONTENTSCHANGED                "Contents Changed" // NOT_YET_LOCALIZED
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE "���������� ��������.\n ������ �� ��������� ��������� � ������� �������?" 



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  "���������� �������� ����������  ���������� ���������  � ������� �������. ������ ����� ������� �� ��������� �������� ������������. \n\n ��� ������������ ��������� ������ ������������� ��������� ����." 
#define LOCALIZED_RETURNTOEDIT                  "��������� � ��������?" 

#define LOCALIZED_EDITFAILEDTOLOAD              LOCALIZED_SAVETOWORKSPACE 

#define LOCALIZED_ERRORINFILETITLE              "Error in File" // NOT_YET_LOCALIZED
#define LOCALIZED_ERRORINFILEMESSAGE            "There was a problem loading the contents of the file \"%s\".\n\nCheck the Commander for possible error message.\n\nDo you want to open the file in the editor to see the error?" // NOT_YET_LOCALIZED

#define LOCALIZED_CANNOTALLOCATESCREEN          "Unable to allocate memory for the screen window.  You may have requested a width and height that exceeds the amount of available video RAM.\n\n" LOCALIZED_GENERAL_PRODUCTNAME " can't continue." // NOT_YET_LOCALIZED


// 
//  Strings used in the File-Open filters
//
#define LOCALIZED_FILE_LOAD_DIALOG_TITLE    "Select the Logo program to load (merge into workspace)" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_OPEN_DIALOG_TITLE    "Select the Logo program to open (replace the workspace with)" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_SAVE_DIALOG_TITLE    "Select the file to which the workspace will be saved" // NOT_YET_LOCALIZED
#define LOCALIZED_BITMAP_OPEN_DIALOG_TITLE  "Select the image to load" // NOT_YET_LOCALIZED
#define LOCALIZED_BITMAP_SAVE_DIALOG_TITLE  "Select the file to which the active area will be saved" // NOT_YET_LOCALIZED

#define LOCALIZED_LOGO_FILE_EXTENSION "lgo"
#define LOCALIZED_FILEFILTER_ALLFILES "��� ����� (*.*)|*.*" 
#define LOCALIZED_FILEFILTER_LOGO     "����-����� (*.lgo)|*.lgo|" LOCALIZED_FILEFILTER_ALLFILES 
#define LOCALIZED_FILEFILTER_IMAGE    "��������� ����� (*.bmp)|*.bmp|GIF-����� (*.gif)|*.gif|" LOCALIZED_FILEFILTER_ALLFILES



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             " �������\n" 
#define LOCALIZED_TRACING_OUTPUTS           " ���������� %s\n" 
#define LOCALIZED_TRACING_MAKE              "����� %s %s" 
#define LOCALIZED_TRACING_PPROP             "��������� %s %s %s" 
#define LOCALIZED_TRACING_LOCATION          " � %s\n%s" 

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  "��������� ���" 

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  "%s ����������\n" 


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    "������" 
#define LOCALIZED_PENMODE_REVERSE  "��������" 
#define LOCALIZED_PENMODE_PAINT    "�����" 

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          "����: ��������� ���������� ������" 
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       "����: ������������ ������" 
#define LOCALIZED_ERROR_OUTOFMEMORY            "������������ ������" 
#define LOCALIZED_ERROR_STACKOVERFLOW          "������������ �����" 
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      "������� ����� �� �������" 
#define LOCALIZED_ERROR_BADGRAPHINIT           "�� ���� ���������������� �������" 
#define LOCALIZED_ERROR_BADDATA                "%p �� �������� %s ��� ��������" 
#define LOCALIZED_ERROR_DIDNTOUTPUT            "%p �� ���������� %p" 
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        "�� ������� ���������� � %p" 
#define LOCALIZED_ERROR_TOOMUCH                "������� ����� ���������� ()" 
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    "�� �� ������� ��� ������ � %s" 
#define LOCALIZED_ERROR_PARENMISMATCH          "������� ����� (" 
#define LOCALIZED_ERROR_NOVALUE                "%s �� ����� ��������" 
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        "�������������� ')'" 
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      "�������������� ']'" 
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        "�������������� '}'" 
#define LOCALIZED_ERROR_DONTKNOWHOWTO          "� �� ���� ��� ������ �  %p" 
#define LOCALIZED_ERROR_NOCATCHTAG             "�� ������� ����� ��� %p" 
#define LOCALIZED_ERROR_ALREADYDEFINED         "%p ��� ����������" 
#define LOCALIZED_ERROR_STOPPING               "���������..." 
#define LOCALIZED_ERROR_ALREADYDRIBBLING       "��� ����������������" 
#define LOCALIZED_ERROR_FILESYSTEM                   "������ �������� �������: %p" 
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          "�� ���� ������� ����" 
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         "���������� ������� ����: %t" 
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       "���� ��� ������" 
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           "���� �� ������" 
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  "�� ���� ������� ������������� ����"
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   "�� ���� ��������� ��������"  
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    "�� ���� ��������� ������������� ����" 
#define LOCALIZED_ERROR_IFWARNING              "�������� �� ����� ����� ���������, � �� ����" 
#define LOCALIZED_ERROR_SHADOWWARNING          "%p �������� �������� � ������ ���������" 
#define LOCALIZED_ERROR_USER                   "��������� \"������" 
#define LOCALIZED_ERROR_ISPRIMITIVE            "%p ��������" 
#define LOCALIZED_ERROR_TONOTINSIDE            "�� ���� ������������ ��� ������ ���������" 
#define LOCALIZED_ERROR_ATTOPLEVEL             "����� ������������ %p ������ ������ ���������" 
#define LOCALIZED_ERROR_ATTOPLEVEL2            "�� ������ ���������� ������ ���������, ����� ������������ ����� ��� ����" 
#define LOCALIZED_ERROR_NOTEST                 "%p ��� ����" 
#define LOCALIZED_ERROR_BADMACROOUTPUT         "��������� ������� %s ������ ������" 
#define LOCALIZED_ERROR_DEEPEND                "����� ������ ������-��������� ����������" 
#define LOCALIZED_ERROR_DEEPENDIN              "����� ������ ������-��������� ���������� � %p" 
#define LOCALIZED_ERROR_UNKNOWN                "����������� ��������� ������� - ���������� ������." 
#define LOCALIZED_PAUSING                      "�����..." 


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION "Invalid state for instruction: %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MODE_ON_SPRITE             "cannot set the mode of a turtle with a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        "cannot make a special turtle use a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            "cannot use the clipboard as a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_SPECIALFORM                "%p doesn't like %p as input because it has a special form" // NOT_YET_LOCALIZED

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      "������" 
#define LOCALIZED_ERROR_BADINPUT             "�������� ��������" 
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    "��������� �� ����������" 

#define LOCALIZED_ERROR_CANTOPENPORT         "���������� ������� ����" 
#define LOCALIZED_ERROR_CANTCLOSEPORT        "���������� ������� ����" 
#define LOCALIZED_ERROR_CANTFLUSHPORT        "���������� �������� ����"                                                                                                                           
#define LOCALIZED_ERROR_CANTDCBONPORT        "���������� ��������� ��������� dcb �� �����" 
#define LOCALIZED_ERROR_CANTSETPORT          "���������� ���������� ����" 
#define LOCALIZED_ERROR_PORTALREADYOPEN      "���� ��� ������" 
#define LOCALIZED_ERROR_PORTNOTOPEN          "���� �� ������" 

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   "%s ��� ����������" 
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    "%s �� ����������" 

#define LOCALIZED_ERROR_DLLNOTLOADED          "DLL �� ���������" 
#define LOCALIZED_ERROR_DLLLOADFAILED         "DLL �������� ��������" 
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    "������������ ��� ������ ���������" 
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  "������������ ��� ������ ����������" 
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   "������� �� �������" 
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  "�� ��� ����/������ ���������� ���������" 

#define LOCALIZED_ERROR_NETWORK               "������ ����" 
#define LOCALIZED_ERROR_NETWORKRECEIVE        "������ �������� ������" 
#define LOCALIZED_ERROR_NETWORKSEND           "������ �������� ������" 
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       "����������� ������, ���� ����� ���� ����������" 
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     "�� ��������" 
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED "��� ��������" 
#define LOCALIZED_ERROR_NETWORKALREADYON      "��� ��������" 
#define LOCALIZED_ERROR_NETWORKALREADYOFF     "��� ���������" 

// The rest of the network errors shouldn't really be seen -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         "������� ������� ���" 
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

#define LOCALIZED_ERROR_POLYSTART               "������ ����������" 
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED "������������� ��� �����" 

#define LOCALIZED_ERROR_POLYEND                 "������ ����������" 
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       "������������� �� �����" 
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     "������ ���� �� ������� ���� 3 �������, ����� ���������� �������������" 

#define LOCALIZED_ERROR_SOUND                 "������ �����" 

#define LOCALIZED_ERROR_MIDI                  "������ MIDI" 
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     "������������ MIDI ����������" 
#define LOCALIZED_ERROR_MIDIALREADYOPEN       "��� �������" 
#define LOCALIZED_ERROR_MIDINOTOPEN           "�� �������" 

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      "� ������ ��� ������" 

#define LOCALIZED_ERROR_MCI                   "������ ���" 

#define LOCALIZED_ERROR_TIMERNOTFOUND         "������ �� ������" 

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       "������-������ ����������, �.�. hhctrl.ocx �� ����� ���� ���������." 

#define LOCALIZED_ERROR_BADCOMMANDLINE        "������ ��������� ������"  

#define LOCALIZED_ERROR_TMPNOTDEFINED         "���������� ����� TMP �� ���������� ��� �� ���������.\n" LOCALIZED_GENERAL_PRODUCTNAME " ����� ������������ C: \\��� �������� ��������� ������"

#define LOCALIZED_ERROR_GIFSAVEFAILED         "�������� �������� GIF, ��������� ������ � �������� ������������" 
#define LOCALIZED_ERROR_GIFREADFAILED         "�������� ������ GIF, ��������� ������ � �������� ������������" 

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  "��������� ������ ��� ���������" 
#define LOCALIZED_ERROR_BITMAPCUTFAILED        "�������� �������� �� �������, �������� ��������� ������" 

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    "������ ��������" 
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  "��������� ������ ������ ������������� � ������� ��������" 

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      "��� ������� %d ��� �������, ������������" 

#define LOCALIZED_ERROR_FONTNOTFOUND            "\n� ���������, ����� �� ����� %s, �� ������. �������� ���� �� ���������:\n" 

#define LOCALIZED_ERROR_PRINTERCANTSCALE        "������� ������ �� ������������ ��� �������"  
#define LOCALIZED_ERROR_CANTDRAWIMAGE           "���������� ����������� �����������" 
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        "���������� �������� �����������" 
#define LOCALIZED_ERROR_SUBCODE                 "�������������� ���" 

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         "����:" 
#define LOCALIZED_PROMPT_TO     "��� (������ ��� ���������)" 
#define LOCALIZED_PROMPT_LIST   "������ (������ ��� ��������)" 
#define LOCALIZED_PROMPT_PAUSE  "Pause Mode (Cancel to Continue)" // NOT_YET_LOCALIZED
#define LOCALIZED_PROMPT_INPUT  "���� (������ ��� ��������)" 

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      "���������� �� \"%s\"" 
#define LOCALIZED_FILE_CHDIRFAILED         "���������� ������ �� ����� \"%s\"" 
#define LOCALIZED_FILE_POPPEDTO            "���� � \"%s\"" 
#define LOCALIZED_FILE_MKDIRSUCCEEDED      "������ �� ����� ��������� ����� \"%s\""  
#define LOCALIZED_FILE_MKDIRFAILED         "���������� ������� ����� \"%s\""  
#define LOCALIZED_FILE_RMDIRSUCCEEDED      "���������� ����� \"%s\""  
#define LOCALIZED_FILE_RMDIRFAILED         "�� ������� �������� ����������� ����� \"%s\""  
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  "����� ����� �� ����������." 
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY "��������� � ���, ��� ���������� ����� ����� � ������������." 


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       "����-�������" 

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    "�������� �������" 
#define LOCALIZED_INFORMATION   "����������" 
#define LOCALIZED_WARNING       "��������������" 
#define LOCALIZED_UNTITLED      "��� ���������" 
#define LOCALIZED_UNKNOWN       "����������" 

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       "�������������" 

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     "�����"
#define LOCALIZED_EDITOR_TITLE_REPLACE  "������"

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING "%s �� ������" 


//
// The words that describe color vectors.
// These words were selected from a de facto HTML standard, so you may
// be able to find translations for the entire set on the Web.
//
// As with the procedure names, these are part of the programming language,
// so once they are translated, they cannot be changed without breaking
// compatibility with older programs that may use the old name.
//
// Note that the colors have no spaces in their names.  This makes them
// easier to use, as the programmer doesn't have to escape the space
// when providing them as a literal word, as in:
//
//  SETPENCOLOR "AliceBlue
//
// In absense of the space, The PascalCase makes it easier to see the word
// separation in the documentation.
//
#define LOCALIZED_COLOR_ALICEBLUE             "����������-�������" 
#define LOCALIZED_COLOR_ANTIQUEWHITE          "�����_�����" 
#define LOCALIZED_COLOR_AQUA                  "����" 
#define LOCALIZED_COLOR_AQUAMARINE            "���������" 
#define LOCALIZED_COLOR_AZURE                 "��������" 
#define LOCALIZED_COLOR_BEIGE                 "�������" 
#define LOCALIZED_COLOR_BISQUE                "��������" 
#define LOCALIZED_COLOR_BLACK                 "������" 
#define LOCALIZED_COLOR_BLANCHEDALMOND        "���������������" 
#define LOCALIZED_COLOR_BLUE                  "�����" 
#define LOCALIZED_COLOR_BLUEVIOLET            "���������-�������" 
#define LOCALIZED_COLOR_BROWN                 "����������" 
#define LOCALIZED_COLOR_BURLYWOOD             "������_������" 
#define LOCALIZED_COLOR_CADETBLUE             "�������_�����" 
#define LOCALIZED_COLOR_CHARTREUSE            "�������" 
#define LOCALIZED_COLOR_CHOCOLATE             "����������" 
#define LOCALIZED_COLOR_CORAL                 "������" 
#define LOCALIZED_COLOR_CORNFLOWERBLUE        "�������" 
#define LOCALIZED_COLOR_CORNSILK              "�����������" 
#define LOCALIZED_COLOR_CRIMSON               "���������" 
#define LOCALIZED_COLOR_CYAN                  "�������" 
#define LOCALIZED_COLOR_DARKBLUE              "�����-�����" 
#define LOCALIZED_COLOR_DARKCYAN              "�����-�������" 
#define LOCALIZED_COLOR_DARKGOLDENROD         "�����-����������������" 
#define LOCALIZED_COLOR_DARKGRAY              "�����-�����" 
#define LOCALIZED_COLOR_DARKGREEN             "�����-�������" 
#define LOCALIZED_COLOR_DARKGREY              "�����-�����" 
#define LOCALIZED_COLOR_DARKKHAKI             "����_������" 
#define LOCALIZED_COLOR_DARKMAGENTA           "�����-���������" 
#define LOCALIZED_COLOR_DARKOLIVEGREEN        "�����-���������������" 
#define LOCALIZED_COLOR_DARKORANGE            "�����-���������" 
#define LOCALIZED_COLOR_DARKORCHID            "�����-�������" 
#define LOCALIZED_COLOR_DARKRED               "�����-�������" 
#define LOCALIZED_COLOR_DARKSALMON            "�����-���������������" 
#define LOCALIZED_COLOR_DARKSEAGREEN          "�������_�����_������" 
#define LOCALIZED_COLOR_DARKSLATEBLUE         "�����-���������������" 
#define LOCALIZED_COLOR_DARKSLATEGRAY         "�����-�����������������" 
#define LOCALIZED_COLOR_DARKSLATEGREY         "�����-�����������������" 
#define LOCALIZED_COLOR_DARKTURQUOISE         "�����-���������" 
#define LOCALIZED_COLOR_DARKVIOLET            "�����-����������" 
#define LOCALIZED_COLOR_DEEPPINK              "�����-�������" 
#define LOCALIZED_COLOR_DEEPSKYBLUE           "�����-������������" 
#define LOCALIZED_COLOR_DIMGRAY               "������-�����" 
#define LOCALIZED_COLOR_DIMGREY               "������-�����" 
#define LOCALIZED_COLOR_DODGERBLUE            "������-�����������" 
#define LOCALIZED_COLOR_FIREBRICK             "���������" 
#define LOCALIZED_COLOR_FLORALWHITE           "��������-�����" 
#define LOCALIZED_COLOR_FORESTGREEN           "������_������" 
#define LOCALIZED_COLOR_FUCHSIA               "������"
#define LOCALIZED_COLOR_GAINSBORO             "���������" 
#define LOCALIZED_COLOR_GHOSTWHITE            "�������-�����" 
#define LOCALIZED_COLOR_GOLD                  "�������" 
#define LOCALIZED_COLOR_GOLDENROD             "������-�������" 
#define LOCALIZED_COLOR_GRAY                  "�����" 
#define LOCALIZED_COLOR_GREEN                 "������" 
#define LOCALIZED_COLOR_GREENYELLOW           "�����-�������" 
#define LOCALIZED_COLOR_GREY                  "�����" 
#define LOCALIZED_COLOR_HONEYDEW              "�����-���������" 
#define LOCALIZED_COLOR_HOTPINK               "����-�������"
#define LOCALIZED_COLOR_INDIANRED             "����-�������" 
#define LOCALIZED_COLOR_INDIGO                "������" 
#define LOCALIZED_COLOR_IVORY                 "��������_�����" 
#define LOCALIZED_COLOR_KHAKI                 "����" 
#define LOCALIZED_COLOR_LAVENDER              "����������" 
#define LOCALIZED_COLOR_LAVENDERBLUSH         "����������-����������" 
#define LOCALIZED_COLOR_LAWNGREEN             "�������_�������" 
#define LOCALIZED_COLOR_LEMONCHIFFON          "��������" 
#define LOCALIZED_COLOR_LIGHTBLUE             "������-�����" 
#define LOCALIZED_COLOR_LIGHTCORAL            "������-����������" 
#define LOCALIZED_COLOR_LIGHTCYAN             "������-�������" 
#define LOCALIZED_COLOR_LIGHTGOLDENRODYELLOW  "������-�������������������" 
#define LOCALIZED_COLOR_LIGHTGRAY             "������-�����" 
#define LOCALIZED_COLOR_LIGHTGREEN            "������-�������" 
#define LOCALIZED_COLOR_LIGHTGREY             "������-�����" 
#define LOCALIZED_COLOR_LIGHTPINK             "������-�������" 
#define LOCALIZED_COLOR_LIGHTSALMON           "������-���������������" 
#define LOCALIZED_COLOR_LIGHTSEAGREEN         "�������_�����_�������" 
#define LOCALIZED_COLOR_LIGHTSKYBLUE          "������-������������" 
#define LOCALIZED_COLOR_LIGHTSLATEGRAY        "������-�����������������" 
#define LOCALIZED_COLOR_LIGHTSLATEGREY        "������-�����������������" 
#define LOCALIZED_COLOR_LIGHTSTEELBLUE        "������-��������" 
#define LOCALIZED_COLOR_LIGHTYELLOW           "������-������" 
#define LOCALIZED_COLOR_LIME                  "�������" 
#define LOCALIZED_COLOR_LIMEGREEN             "�������_����" 
#define LOCALIZED_COLOR_LINEN                 "�������" 
#define LOCALIZED_COLOR_MAGENTA               "���������" 
#define LOCALIZED_COLOR_MAROON                "����������" 
#define LOCALIZED_COLOR_MEDIUMAQUAMARINE      "��������-�������������" 
#define LOCALIZED_COLOR_MEDIUMBLUE            "��������-�����" 
#define LOCALIZED_COLOR_MEDIUMORCHID          "��������-������������" 
#define LOCALIZED_COLOR_MEDIUMPURPLE          "��������-���������" 
#define LOCALIZED_COLOR_MEDIUMSEAGREEN        "�������_�����_���������" 
#define LOCALIZED_COLOR_MEDIUMSLATEBLUE       "��������-���������������" 
#define LOCALIZED_COLOR_MEDIUMSPRINGGREEN     "��������_������_��������� " 
#define LOCALIZED_COLOR_MEDIUMTURQUOISE       "��������-���������" 
#define LOCALIZED_COLOR_MEDIUMVIOLETRED       "��������-����������������" 
#define LOCALIZED_COLOR_MIDNIGHTBLUE          "�����-�����" 
#define LOCALIZED_COLOR_MINTCREAM             "�����-��������" 
#define LOCALIZED_COLOR_MISTYROSE             "�������-�������" 
#define LOCALIZED_COLOR_MOCCASIN              "��������" 
#define LOCALIZED_COLOR_NAVAJOWHITE           "������-�����" 
#define LOCALIZED_COLOR_NAVY                  "�������" 
#define LOCALIZED_COLOR_OLDLACE               "������_�������" 
#define LOCALIZED_COLOR_OLIVE                 "���������" 
#define LOCALIZED_COLOR_OLIVEDRAB             "������-���������" 
#define LOCALIZED_COLOR_ORANGE                "���������" 
#define LOCALIZED_COLOR_ORANGERED             "������-���������" 
#define LOCALIZED_COLOR_ORCHID                "�������" 
#define LOCALIZED_COLOR_PALEGOLDENROD         "������-�������" 
#define LOCALIZED_COLOR_PALEGREEN             "������-�������" 
#define LOCALIZED_COLOR_PALETURQUOISE         "������-���������" 
#define LOCALIZED_COLOR_PALEVIOLETRED         "������-����������������" 
#define LOCALIZED_COLOR_PAPAYAWHIP            "�����_������" 
#define LOCALIZED_COLOR_PEACHPUFF             "����������" 
#define LOCALIZED_COLOR_PERU                  "������-����������" 
#define LOCALIZED_COLOR_PINK                  "�������" 
#define LOCALIZED_COLOR_PLUM                  "��������" 
#define LOCALIZED_COLOR_POWDERBLUE            "�������-�����" 
#define LOCALIZED_COLOR_PURPLE                "���������" 
#define LOCALIZED_COLOR_RED                   "�������" 
#define LOCALIZED_COLOR_ROSYBROWN             "������-����������" 
#define LOCALIZED_COLOR_ROYALBLUE             "�����������_�����" 
#define LOCALIZED_COLOR_SADDLEBROWN           "��������_�����" 
#define LOCALIZED_COLOR_SALMON                "��������-�������" 
#define LOCALIZED_COLOR_SANDYBROWN            "���������" 
#define LOCALIZED_COLOR_SEAGREEN              "�������_�����" 
#define LOCALIZED_COLOR_SEASHELL              "�������_��������" 
#define LOCALIZED_COLOR_SIENNA                "����" 
#define LOCALIZED_COLOR_SILVER                "�����������" 
#define LOCALIZED_COLOR_SKYBLUE               "�������-�����" 
#define LOCALIZED_COLOR_SLATEBLUE             "����������-�����" 
#define LOCALIZED_COLOR_SLATEGRAY             "��������-�����" 
#define LOCALIZED_COLOR_SLATEGREY             "��������-�����" 
#define LOCALIZED_COLOR_SNOW                  "�������" 
#define LOCALIZED_COLOR_SPRINGGREEN           "��������_������ " 
#define LOCALIZED_COLOR_STEELBLUE             "��������-��������" 
#define LOCALIZED_COLOR_TAN                   "�����" 
#define LOCALIZED_COLOR_TEAL                  "����������-�������" 
#define LOCALIZED_COLOR_THISTLE               "�����������" 
#define LOCALIZED_COLOR_TOMATO                "��������" 
#define LOCALIZED_COLOR_TURQUOISE             "���������" 
#define LOCALIZED_COLOR_VIOLET                "����������" 
#define LOCALIZED_COLOR_WHEAT                 "���������" 
#define LOCALIZED_COLOR_WHITE                 "�����" 
#define LOCALIZED_COLOR_WHITESMOKE            "�������-�����" 
#define LOCALIZED_COLOR_YELLOW                "������" 
#define LOCALIZED_COLOR_YELLOWGREEN           "�����-�������" 

//
// The name of each "window class" that DEBUGWINDOWS prints.
// These should match the corresponding terms that is used
// in the  LOCALIZED_ALTERNATE_*CREATE procedures.
//
#define LOCALIZED_WINDOWCLASSNAME_WINDOW       "����" 
#define LOCALIZED_WINDOWCLASSNAME_STATIC       "���������" 
#define LOCALIZED_WINDOWCLASSNAME_LISTBOX      "������_�������" 
#define LOCALIZED_WINDOWCLASSNAME_COMBOBOX     "����" 
#define LOCALIZED_WINDOWCLASSNAME_BUTTON       "������" 
#define LOCALIZED_WINDOWCLASSNAME_SCROLLBAR    "������_��������" 
#define LOCALIZED_WINDOWCLASSNAME_GROUPBOX     "������" 
#define LOCALIZED_WINDOWCLASSNAME_RADIOBUTTON  "�����_������" 
#define LOCALIZED_WINDOWCLASSNAME_CHECKBOX     "�������������" 
#define LOCALIZED_WINDOWCLASSNAME_DIALOG       "������" 


//
// The name of the default font face name.
// This should only be translated if the given font face doesn't include glyphs
// for characters in your language.  The specified font face name must be part
// of all Windows versions from Windows XP onward that would support your
// language.
//
#define LOCALIZED_DEFAULT_FONT_FACE "Courier New" // NOT_YET_LOCALIZED
