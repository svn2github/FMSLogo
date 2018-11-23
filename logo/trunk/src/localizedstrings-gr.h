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
// This file contains localized strings for Greek by Theodoros Chatzigiannakis
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
#define LOCALIZED_ALTERNATE_TRUE     "������" // 
#define LOCALIZED_ALTERNATE_FALSE    "������" // 
#define LOCALIZED_ALTERNATE_END      "�����" // 
#define LOCALIZED_ALTERNATE_TOPLEVEL "����" // 
#define LOCALIZED_ALTERNATE_SYSTEM   "�������" // 

//
// Localized "alternate" names of Logo special variables
//
#define LOCALIZED_ALTERNATE_CASEIGNOREDP    "caseignoredp"
#define LOCALIZED_ALTERNATE_ERRACT          "�������_���������"
#define LOCALIZED_ALTERNATE_STARTUP         "��������"
#define LOCALIZED_ALTERNATE_REDEFP          "������������������" 
#define LOCALIZED_ALTERNATE_PRINTWIDTHLIMIT "������_���������"
#define LOCALIZED_ALTERNATE_PRINTDEPTHLIMIT "�����_���������"


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
#define LOCALIZED_ALTERNATE__DEFMACRO              ".�������_����������" // 
#define LOCALIZED_ALTERNATE__EQ                    ".���" // 
#define LOCALIZED_ALTERNATE__MACRO                 ".�����������" // 
#define LOCALIZED_ALTERNATE__MAYBEOUTPUT           ".������_������" // 
#define LOCALIZED_ALTERNATE__SETBF                 ".setbf" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE__SETFIRST              ".setfirst" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE__SETITEM               ".setitem" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ACTIVEAREA             "������_�������" // 
#define LOCALIZED_ALTERNATE_ALLOPEN                "�������" // 
#define LOCALIZED_ALTERNATE_AND                    "���" // 
#define LOCALIZED_ALTERNATE_APPLY                  "��������" // 
#define LOCALIZED_ALTERNATE_ARCCOS                 "arccos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARCSIN                 "arcsin" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARCTAN                 "arctan" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARITY                  "arity" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARRAY                  "�������" // 
#define LOCALIZED_ALTERNATE_ARRAYP                 "arrayp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARRAY_                 "�������?" // 
#define LOCALIZED_ALTERNATE_ASCII                  "ascii" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ASHIFT                 "������������_��������" // 
#define LOCALIZED_ALTERNATE_BACK                   "����" // 
#define LOCALIZED_ALTERNATE_BACKSLASHEDP           "backslashedp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BACKSLASHED_           "backslashed?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BEFOREP                "beforep" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BEFORE_                "����?" // 
#define LOCALIZED_ALTERNATE_BF                     "bf" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BFS                    "bfs" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITAND                 "�������_���" // 
#define LOCALIZED_ALTERNATE_BITBLOCK               "bitblock" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITCOPY                "bitcopy" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITCUT                 "bitcut" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITFIT                 "bitfit" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITINDEX               "bitindex" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITLOAD                "bitload" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITLOADSIZE            "bitloadsize" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITSIZE                "bitsize" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITMAPTURTLE           "bitmapturtle" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITMODE                "bitmode" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITNOT                 "�������_���" // 
#define LOCALIZED_ALTERNATE_BITOR                  "�������_�" // 
#define LOCALIZED_ALTERNATE_BITPASTE               "bitpaste" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITPASTETOINDEX        "bitpastetoindex" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITSAVE                "bitsave" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITXOR                 "�������_��0����������_�" // 
#define LOCALIZED_ALTERNATE_BK                     "bk" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BL                     "bl" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BURIED                 "buried" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BURY                   "bury" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTFIRST               "�����_�����" // 
#define LOCALIZED_ALTERNATE_BUTFIRSTS              "�����_�����" // 
#define LOCALIZED_ALTERNATE_BUTLAST                "�����_���������" // 
#define LOCALIZED_ALTERNATE_BUTTONCREATE           "������_����������" // 
#define LOCALIZED_ALTERNATE_BUTTONDELETE           "������_��������" // 
#define LOCALIZED_ALTERNATE_BUTTONENABLE           "������_������������" // 
#define LOCALIZED_ALTERNATE_BUTTONUPDATE           "������_���������" // 
#define LOCALIZED_ALTERNATE_BUTTONP                "buttonp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTTON_                "������?" // 
#define LOCALIZED_ALTERNATE_BYE                    "�����" // 
#define LOCALIZED_ALTERNATE_CATCH                  "catch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CHAR                   "����������" // 
#define LOCALIZED_ALTERNATE_CHDIR                  "���������_������" // 
#define LOCALIZED_ALTERNATE_CHECKBOXCREATE         "�������_�������_����������" // 
#define LOCALIZED_ALTERNATE_CHECKBOXDELETE         "�������_�������_��������" // 
#define LOCALIZED_ALTERNATE_CHECKBOXENABLE         "�������_�������_������������" // 
#define LOCALIZED_ALTERNATE_CHECKBOXGET            "�������_�������_����" // 
#define LOCALIZED_ALTERNATE_CHECKBOXSET            "�������_�������_�������" // 
#define LOCALIZED_ALTERNATE_CLEAN                  "����������" // 
#define LOCALIZED_ALTERNATE_CLEARPALETTE           "clearpalette" //
#define LOCALIZED_ALTERNATE_CLEARSCREEN            "����������_������" // 
#define LOCALIZED_ALTERNATE_CLEARTEXT              "����������_��������" // 
#define LOCALIZED_ALTERNATE_CLEARTIMER             "����������_�����������" // 
#define LOCALIZED_ALTERNATE_CLOSE                  "��������" // 
#define LOCALIZED_ALTERNATE_CLOSEALL               "��������_����" // 
#define LOCALIZED_ALTERNATE_CO                     "co" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COMBOBOXADDSTRING      "�������_��������_��������" // 
#define LOCALIZED_ALTERNATE_COMBOBOXCREATE         "�������_��������_����������" // 
#define LOCALIZED_ALTERNATE_COMBOBOXDELETE         "�������_��������_��������" // 
#define LOCALIZED_ALTERNATE_COMBOBOXENABLE         "�������_��������_������������" // 
#define LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING   "�������_��������_��������" // 
#define LOCALIZED_ALTERNATE_COMBOBOXGETTEXT        "�������_��������_����" // 
#define LOCALIZED_ALTERNATE_COMBOBOXSETTEXT        "�������_��������_�������" // 
#define LOCALIZED_ALTERNATE_CONTENTS               "�����������" // 
#define LOCALIZED_ALTERNATE_CONTINUE               "��������" // 
#define LOCALIZED_ALTERNATE_COPYDEF                "���������_�������" // 
#define LOCALIZED_ALTERNATE_COS                    "����������" // 
#define LOCALIZED_ALTERNATE_COUNT                  "�������" // 
#define LOCALIZED_ALTERNATE_CS                     "cs" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CT                     "ct" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CURSOR                 "cursor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DEBUGWINDOWS           "debugwindows" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DEFINE                 "�������" // 
#define LOCALIZED_ALTERNATE_DEFINEDP               "definedp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DEFINED_               "��������?" // 
#define LOCALIZED_ALTERNATE_DIALOGCREATE           "��������_��������_����������" // 
#define LOCALIZED_ALTERNATE_DIALOGENABLE           "��������_��������_������������" // 
#define LOCALIZED_ALTERNATE_DIALOGDELETE           "��������_��������_��������" // 
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         "��������_������_�������" // 
#define LOCALIZED_ALTERNATE_DIALOGFILESAVE         "��������_������_����������" // 
#define LOCALIZED_ALTERNATE_DIFFERENCE             "�������" // 
#define LOCALIZED_ALTERNATE_DIRECTORIES            "���������" // 
#define LOCALIZED_ALTERNATE_DLLCALL                "DLL_�����" // 
#define LOCALIZED_ALTERNATE_DLLFREE                "DLL_��������" // 
#define LOCALIZED_ALTERNATE_DLLLOAD                "DLL_�������" // 
#define LOCALIZED_ALTERNATE_DOWN                   "����" // 
#define LOCALIZED_ALTERNATE_DOWNPITCH              "downpitch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DRIBBLE                "���������" // 
#define LOCALIZED_ALTERNATE_ED                     "ed" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EDIT                   "edit" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ELLIPSEARC             "ellipsearc" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EMPTYP                 "emptyp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EMPTY_                 "�����?" // 
#define LOCALIZED_ALTERNATE_EOFP                   "eofp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EOF_                   "�����_�������?" // 
#define LOCALIZED_ALTERNATE_EQUALP                 "equalp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EQUAL_                 "���?" // 
#define LOCALIZED_ALTERNATE_ER                     "er" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ERASE                  "�������" // 
#define LOCALIZED_ALTERNATE_ERASEFILE              "�������_�������" // 
#define LOCALIZED_ALTERNATE_ERF                    "erf" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ERROR                  "������" // 
#define LOCALIZED_ALTERNATE_EVENTCHECK             "�������_���������" // 
#define LOCALIZED_ALTERNATE_EXP                    "exp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FD                     "fd" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FENCE                  "fence" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FILL                   "�������" // 
#define LOCALIZED_ALTERNATE_FILES                  "������" // 
#define LOCALIZED_ALTERNATE_FIRST                  "�����" // 
#define LOCALIZED_ALTERNATE_FIRSTS                 "�����" // 
#define LOCALIZED_ALTERNATE_FLOODCOLOR             "�����_����������" // 
#define LOCALIZED_ALTERNATE_FONTFACENAMES          "��������������" // 
#define LOCALIZED_ALTERNATE_FOREVER                "forever" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FORM                   "form" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FORWARD                "������" // 
#define LOCALIZED_ALTERNATE_FPUT                   "fput" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FS                     "fs" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FULLSCREEN             "������_�����" // 
#define LOCALIZED_ALTERNATE_FULLTEXT               "������_�������" // 
#define LOCALIZED_ALTERNATE_GETFOCUS               "�����" // 
#define LOCALIZED_ALTERNATE_GOTO                   "�������" // 
#define LOCALIZED_ALTERNATE_GIFLOAD                "GIF_�������" // 
#define LOCALIZED_ALTERNATE_GIFSIZE                "GIF_�������" // 
#define LOCALIZED_ALTERNATE_GIFSAVE                "GIF_����������" // 
#define LOCALIZED_ALTERNATE_GPROP                  "��������_����" // 
#define LOCALIZED_ALTERNATE_GREATEREQUALP          "greaterequalp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GREATEREQUAL_          "����������_���?" // 
#define LOCALIZED_ALTERNATE_GREATERP               "greaterp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GREATER_               "����������?" // 
#define LOCALIZED_ALTERNATE_GROUPBOXCREATE         "�������_������_����������" // 
#define LOCALIZED_ALTERNATE_GROUPBOXDELETE         "�������_������_��������" // 
#define LOCALIZED_ALTERNATE_HALT                   "halt" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HASOWNPENP             "hasownpenp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HASOWNPEN_             "hasownpen?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HEADING                "����������" // 
#define LOCALIZED_ALTERNATE_HELP                   "�������" // 
#define LOCALIZED_ALTERNATE_HIDETURTLE             "hideturtle" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HOME                   "�����" // 
#define LOCALIZED_ALTERNATE_HT                     "ht" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_IF                     "��" // 
#define LOCALIZED_ALTERNATE_IFELSE                 "��_������" // 
#define LOCALIZED_ALTERNATE_IFF                    "iff" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_IFFALSE                "��_������" // 
#define LOCALIZED_ALTERNATE_IFT                    "ift" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_IFTRUE                 "��_������" // 
#define LOCALIZED_ALTERNATE_INGAMEPORT             "ingameport" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_INPORT                 "inport" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_INPORTB                "inportb" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_INT                    "��������" // 
#define LOCALIZED_ALTERNATE_ITEM                   "��������" // 
#define LOCALIZED_ALTERNATE_KEYBOARDOFF            "������������_��������������" // 
#define LOCALIZED_ALTERNATE_KEYBOARDON             "������������_������������" // 
#define LOCALIZED_ALTERNATE_KEYBOARDVALUE          "������������_����" // 
#define LOCALIZED_ALTERNATE_KEYP                   "keyp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_KEY_                   "�������?" // 
#define LOCALIZED_ALTERNATE_LABEL                  "�������" // 
#define LOCALIZED_ALTERNATE_LABELFONT              "�������_�������������" // 
#define LOCALIZED_ALTERNATE_LABELSIZE              "�������_�������" // 
#define LOCALIZED_ALTERNATE_LAST                   "���������" // 
#define LOCALIZED_ALTERNATE_LEFT                   "��������" // 
#define LOCALIZED_ALTERNATE_LEFTROLL               "leftroll" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LESSEQUALP             "lessequalp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LESSEQUAL_             "���������_���?" // 
#define LOCALIZED_ALTERNATE_LESSP                  "lessp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LESS_                  "���������?" // 
#define LOCALIZED_ALTERNATE_LIGHT                  "���" // 
#define LOCALIZED_ALTERNATE_LIST                   "�����" // 
#define LOCALIZED_ALTERNATE_LISTBOXADDSTRING       "�������_������_��������" // 
#define LOCALIZED_ALTERNATE_LISTBOXCREATE          "�������_������_����������" // 
#define LOCALIZED_ALTERNATE_LISTBOXENABLE          "�������_������_������������" // 
#define LOCALIZED_ALTERNATE_LISTBOXDELETE          "�������_������_��������" // 
#define LOCALIZED_ALTERNATE_LISTBOXDELETESTRING    "�������_������_��������" // 
#define LOCALIZED_ALTERNATE_LISTBOXGETSELECT       "�������_������_�������" // 
#define LOCALIZED_ALTERNATE_LISTP                  "listp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LIST_                  "�����?" // 
#define LOCALIZED_ALTERNATE_LN                     "ln" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LOAD                   "�������" // 
#define LOCALIZED_ALTERNATE_LOCAL                  "������" // 
#define LOCALIZED_ALTERNATE_LOG10                  "log10" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LOGOVERSION            "������" // 
#define LOCALIZED_ALTERNATE_LOWERCASE              "����" // 
#define LOCALIZED_ALTERNATE_LPUT                   "��������_�����" // 
#define LOCALIZED_ALTERNATE_LR                     "lr" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LSHIFT                 "��������" // 
#define LOCALIZED_ALTERNATE_LT                     "lt" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MACHINE                "������" // 
#define LOCALIZED_ALTERNATE_MACROP                 "macrop" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MACRO_                 "�����������?" // 
#define LOCALIZED_ALTERNATE_MAKE                   "���������" // 
#define LOCALIZED_ALTERNATE_MCI                    "mci" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MEMBER                 "�����" // 
#define LOCALIZED_ALTERNATE_MEMBERP                "memberp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MEMBER_                "�����?" // 
#define LOCALIZED_ALTERNATE_MESSAGEBOX             "������" // 
#define LOCALIZED_ALTERNATE_MIDICLOSE              "MIDI_��������" // 
#define LOCALIZED_ALTERNATE_MIDIMESSAGE            "MIDI_������" // 
#define LOCALIZED_ALTERNATE_MIDIOPEN               "MIDI_�������" // 
#define LOCALIZED_ALTERNATE_MINUS                  "�����" // 
#define LOCALIZED_ALTERNATE_MKDIR                  "���������_����������" // 
#define LOCALIZED_ALTERNATE_MODULO                 "modulo" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MOUSEOFF               "�������_��������������" // 
#define LOCALIZED_ALTERNATE_MOUSEON                "�������_������������" // 
#define LOCALIZED_ALTERNATE_MOUSEPOS               "�������_����" // 
#define LOCALIZED_ALTERNATE_NAMEP                  "namep" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NAME_                  "�����?" // 
#define LOCALIZED_ALTERNATE_NAMES                  "�������" // 
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           "������_�������_��������������" // 
#define LOCALIZED_ALTERNATE_NETACCEPTON            "������_�������_������������" // 
#define LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE  "������_�������_����_�����" // 
#define LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE     "������_�������_����_���������" // 
#define LOCALIZED_ALTERNATE_NETCONNECTOFF          "������_�������_��������������" // 
#define LOCALIZED_ALTERNATE_NETCONNECTON           "������_�������_������������" // 
#define LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE "������_�������_����_�����" // 
#define LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE    "������_�������_����_���������" // 
#define LOCALIZED_ALTERNATE_NETSHUTDOWN            "������_��������������" // 
#define LOCALIZED_ALTERNATE_NETSTARTUP             "������_������������" // 
#define LOCALIZED_ALTERNATE_NOBITMAPTURTLE         "nobitmapturtle" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NODES                  "������" // 
#define LOCALIZED_ALTERNATE_NODRIBBLE              "nodribble" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NOSTATUS               "nostatus" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NOT                    "���" // 
#define LOCALIZED_ALTERNATE_NOTEQUALP              "notequalp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NOTEQUAL_              "���_���?" // 
#define LOCALIZED_ALTERNATE_NOYIELD                "noyield" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NUMBERP                "numberp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NUMBER_                "�������?" // 
#define LOCALIZED_ALTERNATE_OP                     "op" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OPENAPPEND             "�������_����������" // 
#define LOCALIZED_ALTERNATE_OPENREAD               "�������_��������" // 
#define LOCALIZED_ALTERNATE_OPENUPDATE             "�������_���������" // 
#define LOCALIZED_ALTERNATE_OPENWRITE              "�������_�������" // 
#define LOCALIZED_ALTERNATE_OR                     "�" // 
#define LOCALIZED_ALTERNATE_OUTPORT                "outport" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OUTPORTB               "outportb" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OUTPUT                 "������" // 
#define LOCALIZED_ALTERNATE_PARSE                  "�����������" // 
#define LOCALIZED_ALTERNATE_PAUSE                  "�����" // 
#define LOCALIZED_ALTERNATE_PC                     "pc" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PD                     "pd" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PE                     "pe" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENCOLOR               "����_�����" // 
#define LOCALIZED_ALTERNATE_PENDOWN                "����_����" // 
#define LOCALIZED_ALTERNATE_PENDOWNP               "pendownp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENDOWN_               "����_����?" // 
#define LOCALIZED_ALTERNATE_PENERASE               "����_�������" // 
#define LOCALIZED_ALTERNATE_PENMODE                "����_�������" // 
#define LOCALIZED_ALTERNATE_PENPAINT               "����_��������" // 
#define LOCALIZED_ALTERNATE_PENPATTERN             "����_������" // 
#define LOCALIZED_ALTERNATE_PENREVERSE             "����_����������" // 
#define LOCALIZED_ALTERNATE_PENSIZE                "����_�������" // 
#define LOCALIZED_ALTERNATE_PENUP                  "����_����" // 
#define LOCALIZED_ALTERNATE_PERSPECTIVE            "���������" // 
#define LOCALIZED_ALTERNATE_PITCH                  "pitch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PIXEL                  "pixel" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PLAYWAVE               "�����������" // 
#define LOCALIZED_ALTERNATE_PLIST                  "��������_�����" // 
#define LOCALIZED_ALTERNATE_PLISTS                 "��������_������" // 
#define LOCALIZED_ALTERNATE_PO                     "po" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_POPDIR                 "���������_����" // 
#define LOCALIZED_ALTERNATE_POLYSTART              "��������_����" // 
#define LOCALIZED_ALTERNATE_POLYEND                "��������_�����" // 
#define LOCALIZED_ALTERNATE_POLYVIEW               "��������_�������" // 
#define LOCALIZED_ALTERNATE_PORTCLOSE              "����_��������" // 
#define LOCALIZED_ALTERNATE_PORTFLUSH              "����_����������" // 
#define LOCALIZED_ALTERNATE_PORTMODE               "����_�������" // 
#define LOCALIZED_ALTERNATE_PORTOPEN               "����_�������" // 
#define LOCALIZED_ALTERNATE_PORTREADARRAY          "����_��������_������" // 
#define LOCALIZED_ALTERNATE_PORTREADCHAR           "����_��������_���������" // 
#define LOCALIZED_ALTERNATE_PORTWRITEARRAY         "����_�������_������" // 
#define LOCALIZED_ALTERNATE_PORTWRITECHAR          "����_�������_���������" // 
#define LOCALIZED_ALTERNATE_POS                    "����" // 
#define LOCALIZED_ALTERNATE_POSXYZ                 "����_XYZ" // XYZ is Engilsh, copy XYZ in Greek
#define LOCALIZED_ALTERNATE_POT                    "pot" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_POWER                  "������" // 
#define LOCALIZED_ALTERNATE_PPROP                  "��������_�������" // 
#define LOCALIZED_ALTERNATE_PPT                    "ppt" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PR                     "pr" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PRIMITIVEP             "primitivep" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PRIMITIVE_             "primitive?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PRINT                  "��������" // 
#define LOCALIZED_ALTERNATE_PROCEDUREP             "procedurep" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PROCEDURE_             "procedure?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PROPLISTP              "proplistp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PROPLIST_              "proplist?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PROCEDURES             "procedures" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PRODUCT                "��������" // 
#define LOCALIZED_ALTERNATE_PU                     "pu" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PX                     "px" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_QUESTIONBOX            "������_�������" // 
#define LOCALIZED_ALTERNATE_QUOTIENT               "��������" // 
#define LOCALIZED_ALTERNATE_RADARCCOS              "radarccos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADARCSIN              "radarcsin" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADARCTAN              "radarctan" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADCOS                 "radcos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADIOBUTTONCREATE      "�������_��������_����������" // 
#define LOCALIZED_ALTERNATE_RADIOBUTTONENABLE      "�������_��������_������������" // 
#define LOCALIZED_ALTERNATE_RADIOBUTTONDELETE      "�������_��������_��������" // 
#define LOCALIZED_ALTERNATE_RADIOBUTTONGET         "�������_��������_����" // 
#define LOCALIZED_ALTERNATE_RADIOBUTTONSET         "�������_��������_�������" // 
#define LOCALIZED_ALTERNATE_RADSIN                 "radsin" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADTAN                 "radtan" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RANDOM                 "random" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RAWASCII               "rawascii" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RC                     "rc" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RCS                    "rcs" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READCHAR               "��������_���������" // 
#define LOCALIZED_ALTERNATE_READCHARS              "��������_����������" // 
#define LOCALIZED_ALTERNATE_READER                 "��������_����" // 
#define LOCALIZED_ALTERNATE_READLIST               "��������_������" // 
#define LOCALIZED_ALTERNATE_READPOS                "��������_����" // 
#define LOCALIZED_ALTERNATE_READRAWLINE            "readrawline" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READWORD               "��������_�����" // 
#define LOCALIZED_ALTERNATE_REMAINDER              "��������" // 
#define LOCALIZED_ALTERNATE_REMPROP                "��������_��������" // 
#define LOCALIZED_ALTERNATE_REPCOUNT               "���������_�������" // 
#define LOCALIZED_ALTERNATE_REPEAT                 "���������" // 
#define LOCALIZED_ALTERNATE_RERANDOM               "rerandom" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RIGHT                  "right" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RIGHTROLL              "rightroll" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RL                     "rl" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RMDIR                  "���������_��������" // 
#define LOCALIZED_ALTERNATE_ROLL                   "roll" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ROUND                  "���������������" // 
#define LOCALIZED_ALTERNATE_RR                     "rr" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RT                     "rt" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RUN                    "��������" // 
#define LOCALIZED_ALTERNATE_RUNPARSE               "��������_�����������" // 
#define LOCALIZED_ALTERNATE_RUNRESULT              "��������_����������" // 
#define LOCALIZED_ALTERNATE_RW                     "rw" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SAVE                   "����������" // 
#define LOCALIZED_ALTERNATE_SCREENCOLOR            "screencolor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCROLLBARCREATE        "scrollbarcreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCROLLBARENABLE        "scrollbarenable" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCROLLBARDELETE        "scrollbardelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCROLLBARGET           "scrollbarget" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCROLLBARSET           "scrollbarset" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCROLLX                "scrollx" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCROLLY                "scrolly" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCRUNCH                "scrunch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SE                     "se" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SELECTBOX              "������_�������" // 
#define LOCALIZED_ALTERNATE_SENTENCE               "�������" // 
#define LOCALIZED_ALTERNATE_SETACTIVEAREA          "������_�������_�������" // 
#define LOCALIZED_ALTERNATE_SETBITINDEX            "setbitindex" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETBITMODE             "setbitmode" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETCLIP                "setclip" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETCURSOR              "setcursor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETCURSORNOWAIT        "setcursornowait" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETCURSORWAIT          "setcursorwait" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETFC                  "setfc" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETFLOODCOLOR          "setfloodcolor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETFOCUS               "setfocus" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETH                   "seth" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETHEADING             "setheading" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETITEM                "setitem" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETLABELFONT           "setlabelfont" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETLIGHT               "setlight" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETMARGINS             "setmargins" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPC                  "setpc" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPENCOLOR            "setpencolor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPENPATTERN          "setpenpattern" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPENSIZE             "setpensize" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPITCH               "setpitch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPIXEL               "setpixel" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPOS                 "setpos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPOSXYZ              "setposxyz" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETREAD                "setread" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETREADPOS             "setreadpos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETROLL                "setroll" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETSC                  "setsc" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETSCREENCOLOR         "setscreencolor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETSCRUNCH             "setscrunch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETTIMER               "settimer" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETTURTLE              "setturtle" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETTURTLEMODE          "setturtlemode" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETWRITE               "setwrite" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETWRITEPOS            "setwritepos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETX                   "setx" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETXY                  "setxy" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETXYZ                 "setxyz" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETY                   "sety" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETZ                   "setz" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SHELL                  "shell" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SHOW                   "��������" // 
#define LOCALIZED_ALTERNATE_SHOWNP                 "shownp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SHOWN_                 "shown?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SHOWTURTLE             "showturtle" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SIN                    "�������" // 
#define LOCALIZED_ALTERNATE_SOUND                  "����" // 
#define LOCALIZED_ALTERNATE_SPLITSCREEN            "splitscreen" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SQRT                   "����" // 
#define LOCALIZED_ALTERNATE_SS                     "ss" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ST                     "st" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STANDOUT               "standout" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STATICCREATE           "staticcreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STATICDELETE           "staticdelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STATICUPDATE           "staticupdate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STATUS                 "status" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STEP                   "����" // 
#define LOCALIZED_ALTERNATE_STEPPED                "stepped" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STOP                   "���������" // 
#define LOCALIZED_ALTERNATE_SUBSTRINGP             "substringp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SUBSTRING_             "substring?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SUM                    "��������" // 
#define LOCALIZED_ALTERNATE_TAG                    "tag" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TAN                    "tan" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TEST                   "������" // 
#define LOCALIZED_ALTERNATE_TEXT                   "text" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TEXTSCREEN             "textscreen" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_THING                  "����" // 
#define LOCALIZED_ALTERNATE_THROW                  "throw" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TIME                   "���"
#define LOCALIZED_ALTERNATE_TIMEMILLI              "������" // 
#define LOCALIZED_ALTERNATE_TO                     "to" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TONE                   "tone" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TOWARDS                "����" // 
#define LOCALIZED_ALTERNATE_TOWARDSXYZ             "����_XYZ" // 
#define LOCALIZED_ALTERNATE_TRACE                  "trace" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TRACED                 "traced" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TS                     "ts" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TURTLE                 "������" //
#define LOCALIZED_ALTERNATE_TURTLEMODE             "������_�������" // 
#define LOCALIZED_ALTERNATE_TURTLES                "�������" // 
#define LOCALIZED_ALTERNATE_TYPE                   "type" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UNBURY                 "unbury" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UNSTEP                 "unstep" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UNTRACE                "untrace" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UP                     "up" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UPPERCASE              "��������" // 
#define LOCALIZED_ALTERNATE_UPPITCH                "uppitch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WAIT                   "�������" // 
#define LOCALIZED_ALTERNATE_WINDOW                 "��������" // 
#define LOCALIZED_ALTERNATE_WINDOWCREATE           "��������_����������" // 
#define LOCALIZED_ALTERNATE_WINDOWENABLE           "��������_������������" // 
#define LOCALIZED_ALTERNATE_WINDOWDELETE           "��������_��������" // 
#define LOCALIZED_ALTERNATE_WINDOWFILEEDIT         "windowfileedit" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WINDOWSET              "windowset" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WINHELP                "BOHUEIA" // 
#define LOCALIZED_ALTERNATE_WORD                   "����" // 
#define LOCALIZED_ALTERNATE_WORDP                  "wordp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WORD_                  "����?" // 
#define LOCALIZED_ALTERNATE_WRAP                   "wrap" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WRITEPOS               "�������_����" // 
#define LOCALIZED_ALTERNATE_WRITER                 "�������_����������" // 
#define LOCALIZED_ALTERNATE_YESNOBOX               "������_���_���" // 
#define LOCALIZED_ALTERNATE_YIELD                  "yield" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ZOOM                   "���������" // 

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      "OK"
#define LOCALIZED_GENERAL_CANCELBUTTON  "�����"
#define LOCALIZED_GENERAL_APPLYBUTTON   "&Apply" // NOT_YET_LOCALIZED

#define LOCALIZED_GENERAL_PRODUCTNAME   "FMSLogo"

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  "The FMSLogo programming environment" // NOT_YET_LOCALIZED

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  "&������" // 
#define LOCALIZED_FILE_NEW              "&���\t(��������� ������� ��� ����������)" // I'm sure "workspace" can have a better translation.
#define LOCALIZED_FILE_LOAD             "&�������...\t(��������� ������� ��� ���������� ��� ������)" // 
#define LOCALIZED_FILE_OPEN             "��&�����...\t(��������� ������� ��� ���������� ��� ������� ��� ��� ������)" // 
#define LOCALIZED_FILE_SAVE             "&����������"  // 
#define LOCALIZED_FILE_SAVEAS           "���������� &��..." // 
#define LOCALIZED_FILE_SETASSCREENSAVER "Se&t As Screen Saver" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_EDIT             "&�����������..." // 
#define LOCALIZED_FILE_ERASE            "&�������..." // 
#define LOCALIZED_FILE_EXIT             "�&�����" // 

#define LOCALIZED_BITMAP               "��&����" // 
#define LOCALIZED_BITMAP_NEW           "&���" // 
#define LOCALIZED_BITMAP_LOAD          "��&�����..." // 
#define LOCALIZED_BITMAP_SAVE          "&����������" // 
#define LOCALIZED_BITMAP_SAVEAS        "���������� &��..." // 
#define LOCALIZED_BITMAP_PRINT         "&��������..." // 
#define LOCALIZED_BITMAP_PRINTERSETUP  "�&������� ���������..." // 
#define LOCALIZED_BITMAP_ACTIVEAREA    "���&��� �������..." // 

#define LOCALIZED_SET                  "&�������" // 
#define LOCALIZED_SET_PENSIZE          "&������� �����..." // 
#define LOCALIZED_SET_LABELFONT        "������������� &�������..." // 
#define LOCALIZED_SET_COMMANDERFONT    "������������� ��������� &������� (commander)..." // 
#define LOCALIZED_SET_PENCOLOR         "����� &�����..." // 
#define LOCALIZED_SET_FLOODCOLOR       "����� &����������..." // 
#define LOCALIZED_SET_SCREENCOLOR      "����� &������..." // 

#define LOCALIZED_ZOOM                 "&����"  // 
#define LOCALIZED_ZOOM_IN              "&���������" // 
#define LOCALIZED_ZOOM_OUT             "&���������" // 
#define LOCALIZED_ZOOM_NORMAL          "&��������" // 

#define LOCALIZED_HELP                 "&�������"  // 
#define LOCALIZED_HELP_INDEX           "&������ ��� �������" // 
#define LOCALIZED_HELP_TUTORIAL        "&������" // 
#define LOCALIZED_HELP_DEMO            "&��������"  // 
#define LOCALIZED_HELP_EXAMPLE         "&������������" // 
#define LOCALIZED_HELP_RELEASENOTES    "&���������� �������" // 
#define LOCALIZED_HELP_ABOUTFMSLOGO    "&����������� ��� ��� " LOCALIZED_GENERAL_PRODUCTNAME "..." 
#define LOCALIZED_HELP_MS              "&����������� ��� ��� MS..." // 
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   "LANGUAGE to English" // NOT_YET_LOCALIZED
#define LOCALIZED_HELP_ENGLISHTOLANG   "English to LANGUAGE" // NOT_YET_LOCALIZED

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              "������� ������� ��������" // 
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       "����� �� �������� ���������� ��� �������� ��� ���������� �������" // 
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        "���� ����" // 
#define LOCALIZED_SELECTACTIVEAREA_YLOW         "���� ����"  // 
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        "���� ����" // 
#define LOCALIZED_SELECTACTIVEAREA_XLOW         "�������� ����" // 
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH "������ ������� ��� �����:" // 
#define LOCALIZED_SELECTACTIVEAREA_RESET        "&���������"  // 
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON // Localized above
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON // 

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
#define LOCALIZED_POPUP_COPY                     "����&�����" // 
#define LOCALIZED_POPUP_CUT                      "��&�����" // 
#define LOCALIZED_POPUP_PASTE                    "&����������" // 
#define LOCALIZED_POPUP_DELETE                   "&��������" // 
#define LOCALIZED_POPUP_UNDO                     "�&�������" // 
#define LOCALIZED_POPUP_REDO                     "������� ���������" // 
#define LOCALIZED_POPUP_SELECTALL                "�&������ ����" // 
#define LOCALIZED_POPUP_HELP                     "���&������ ��� �������" // 
#define LOCALIZED_POPUP_REMOVELINES              "Remove Selected Lines" // NOT_YET_LOCALIZED

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   "������������" // 

#define LOCALIZED_EDITOR_FILE                    "&������" // 
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        "���������� ��� �&�����\tCtrl+D" // 
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    "���&�������" // 
#define LOCALIZED_EDITOR_FILE_PRINT              "&��������..."  // 
#define LOCALIZED_EDITOR_FILE_EXIT               "�&�����"  // 

#define LOCALIZED_EDITOR_EDIT                    "&�����������" // 
#define LOCALIZED_EDITOR_EDIT_UNDO               "�������&�\tCtrl+Z" // 
#define LOCALIZED_EDITOR_EDIT_REDO               "������� ���������\tCtrl+Y" // 
#define LOCALIZED_EDITOR_EDIT_CUT                "��&�����\tCtrl+X" // 
#define LOCALIZED_EDITOR_EDIT_COPY               "����&�����\tCtrl+C" // 
#define LOCALIZED_EDITOR_EDIT_PASTE              "&����������\tCtrl+V" // 
#define LOCALIZED_EDITOR_EDIT_DELETE             "&��������\tDel" // 
#define LOCALIZED_EDITOR_EDIT_CLEARALL           "��&�������� ����\tCtrl+Del" // 
#define LOCALIZED_EDITOR_EDIT_SELECTALL          "�&������ ����\tCtrl+A" // 

#define LOCALIZED_EDITOR_SEARCH                  "���&������" // 
#define LOCALIZED_EDITOR_SEARCH_FIND             "��&����...\tCtrl+F" // 
#define LOCALIZED_EDITOR_SEARCH_REPLACE          "����&���������...\tCtrl+H"  // 
#define LOCALIZED_EDITOR_SEARCH_NEXT             "�&������\tF3"  // 

#define LOCALIZED_EDITOR_SET                     "&�������"  // 
#define LOCALIZED_EDITOR_SET_FONT                "&�������������..."  // 

#define LOCALIZED_EDITOR_TEST                    "������"
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      "&Run Selection\tCtrl+R" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITOR_HELP                    "&�������"  // 
#define LOCALIZED_EDITOR_HELP_INDEX              "&������ ��� �������" // 
#define LOCALIZED_EDITOR_HELP_EDITOR             "���&���������" // 
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        "���&������ �������\tF1" // 


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES //
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    "���&������� ��� ������" // 
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       "����� ����������" // 
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON // 
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       "�������� ������� ��� ��� ����� �����������.  �� ��� ��� ������������, ����� �� ������� �� ������.  " // 
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       "������ �� ������������ ��� ������� ��� ���� ��� �����;"  // 


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     "�������� �������" // 
#define LOCALIZED_COMMANDER_HALT                "���������" // 
#define LOCALIZED_COMMANDER_TRACE               "���������" // 
#define LOCALIZED_COMMANDER_NOTRACE             "�����" // 
#define LOCALIZED_COMMANDER_PAUSE               "�����" // 
#define LOCALIZED_COMMANDER_STATUS              "���������" // 
#define LOCALIZED_COMMANDER_NOSTATUS            "�����" // 
#define LOCALIZED_COMMANDER_STEP                "����" // 
#define LOCALIZED_COMMANDER_UNSTEP              "�����" // 
#define LOCALIZED_COMMANDER_RESET               "���������" // 
#define LOCALIZED_COMMANDER_EXECUTE             "��������" // 
#define LOCALIZED_COMMANDER_EDALL               "�����������" // If that's too long, please replace it again with EDALL

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        "���������" // 
#define LOCALIZED_STATUS_PEN                    "����" // 
#define LOCALIZED_STATUS_CONTACT                "�����:" // 
#define LOCALIZED_STATUS_WIDTH                  "������:" // 
#define LOCALIZED_STATUS_STYLE                  "����:" // 
#define LOCALIZED_STATUS_ORIENTATION            "���������������" // 
#define LOCALIZED_STATUS_PITCH                  "�����:" // 
#define LOCALIZED_STATUS_HEADING                "����������:" // 
#define LOCALIZED_STATUS_ROLL                   "������:" // 
#define LOCALIZED_STATUS_TURTLE                 "������" // 
#define LOCALIZED_STATUS_POSITION               "���� (XYZ):" //
#define LOCALIZED_STATUS_WHICH                  "������:" // 
#define LOCALIZED_STATUS_VISIBILITY             "���������:" // 
#define LOCALIZED_STATUS_COLOR                  "�����" // 
#define LOCALIZED_STATUS_PENCOLOR               "���� (���/RGB):" //
#define LOCALIZED_STATUS_FLOODCOLOR             "������� (���/RGB):" // 
#define LOCALIZED_STATUS_SCREENCOLOR            "����� (���/RGB):" // 
#define LOCALIZED_STATUS_KERNEL                 "�������" // 
#define LOCALIZED_STATUS_CALLS                  "�������:" // 
#define LOCALIZED_STATUS_PEAKMEMORY             "�����:" // 

#define LOCALIZED_STATUS_PENREVERSE     "����������" // 
#define LOCALIZED_STATUS_PENNORMAL      "��������" // 
#define LOCALIZED_STATUS_PENERASE       "�������" // 
#define LOCALIZED_STATUS_PENUP          "����" // 
#define LOCALIZED_STATUS_PENDOWN        "����" // 
#define LOCALIZED_STATUS_PENSHOWN       "�����" //  
#define LOCALIZED_STATUS_PENHIDDEN      "������" // 
#define LOCALIZED_STATUS_POLYGONS       "��������" // 
#define LOCALIZED_STATUS_VECTORS        "����������" // 
#define LOCALIZED_STATUS_NODES          "������" // 
#define LOCALIZED_STATUS_NOT_APPLICABLE "N/A" // NOT_YET_LOCALIZED

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           "&����"
#define LOCALIZED_ERASEPROCEDURE                "������� �������"
#define LOCALIZED_EDITPROCEDURE                 "����������� �������"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     "������� ��������" // 
#define LOCALIZED_SETCOLOR_PENCOLOR            "����� �����" // 
#define LOCALIZED_SETCOLOR_FLOODCOLOR          "����� ����������" // 
#define LOCALIZED_SETCOLOR_SCREENCOLOR         "����� ������" // 
#define LOCALIZED_SETCOLOR_RED                 "�������" // 
#define LOCALIZED_SETCOLOR_GREEN               "�������" // 
#define LOCALIZED_SETCOLOR_BLUE                "�������" // 
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON // 
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON // 
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON // NOT_YET_LOCALIZED

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   "������� �����" // 
#define LOCALIZED_SETPENSIZE_SIZE              "�������" // 
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON // NOT_YET_LOCALIZED


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     "����������� ��� ��� " LOCALIZED_GENERAL_PRODUCTNAME 
#define LOCALIZED_ABOUTFMS_VERSION             "������"
#define LOCALIZED_ABOUTFMS_GUI                 "GUI ��� ��� George Mills\nSoftronics, Inc.\nhttp://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_CORE                "������� ��� ��� Brian Harvey\nUniversity of California Berkeley"
#define LOCALIZED_ABOUTFMS_INSTALLER           "������������ ���������� ��� Nullsoft Scriptable Install System\nhttp://nsis.sourceforge.net"
#define LOCALIZED_ABOUTFMS_ADVENTURE           "The Great Logo Adventure (ISBN 0-9651934-6-2)\n�������� ��� ��������� ��� ��� Jim Muller\n��������� ��� http://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       "������������ ���� Yehuda Katz ��� Erich Neuwirth"
#define LOCALIZED_ABOUTFMS_GPL                 "� " LOCALIZED_GENERAL_PRODUCTNAME " ����� �������� ���������\n����� �� GNU Public License"
#define LOCALIZED_ABOUTFMS_NEWSGROUP           "News Group ��� ���������: comp.lang.logo\n������������ �� Logo-Forum ���\nhttp://groups.yahoo.com/group/LogoForum/"
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     "��������� ��� ��������:\n������� �������������� (teo64x@yahoo.gr)"
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      "����������� ��� �� FMS" // 
#define LOCALIZED_ABOUTMS_FMS                  "FMS �������� Fight Multiple Sclerosis." //
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     "Please consider donating to the\nNational Multiple Sclerosis Society.\nhttp://www.nmss.org\n1-800-FIGHT-MS" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTMS_OK                   LOCALIZED_GENERAL_OKBUTTON // 


//
// Strings on the SELECTBOX Dialog box
//
#define LOCALIZED_SELECTBOX_OK                 LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTBOX_CANCEL             LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED

//
// Strings on the QUESTIONBOX dialog box
//
#define LOCALIZED_QUESTIONBOX_OK               LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_QUESTIONBOX_CANCEL           LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED


// 
// Strings in various other dialog boxes
// 

#define LOCALIZED_CHANGESINEDITORMAYBELOST  "������� �� ���� ��� ������� ����������� ���� ������.\n\n������ ���������� �� �������� ��� " LOCALIZED_GENERAL_PRODUCTNAME ";" //
#define LOCALIZED_EDITSESSIONISRUNNING      "� ������������ ������ ����� ��� ��������" // 

#define LOCALIZED_COULDNOTWRITEBMP            "������� � ������� ��� .bmp" // 
#define LOCALIZED_COULDNOTOPENBMP             "������� � �������� ��� �� .bmp" // 
#define LOCALIZED_COULDNOTCREATEBMP           "������� �� ������������ � ������ Windows 3.0 bitmap" // 
#define LOCALIZED_NOTVALIDBMP                 "� ����� ��� ����� Windows 3.0 bitmap" // 

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         "��� ������������ ��� �����" // 
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     "� �������� ���� ���� ������� �� ������ ��� ���������� ������� ��� ����������.\n\n��������;" // 
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE "�� ������ ��� ���������� �� ��������� ���� ���������� ������� ��� ����������\n��� ���� ������ ������ ������� ��� ����� �����������.\n\n��������;" // 
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    "���� �� ������ ���� ��� ������� ��� ��� ����� �����������.\n\n��������;" // 

#define LOCALIZED_EDITORISOPEN                  "������ ��� ��� ����� ��� ������� ������������ �������;\n\n����������� ������ �� ���� ��� ������� �� �� �����������." // 

#define LOCALIZED_ERROR_CANTREADFILE            "�������� ��������� ��� ������� \"%s\" ��� �� �����" // 
#define LOCALIZED_ERROR_CANTWRITEFILE           "�������� �������� ��� ������� \"%s\" ��� �����" // 

#define LOCALIZED_SAVETOWORKSPACE                "����������" // 
#define LOCALIZED_CONTENTSCHANGED                "�� ����������� �������" // 
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE "�� ����������� ����� �������.\n������ �� �� ������������;" // 



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  "� ������� �� ����������� ���� ��� ��������� ����������� ������.\n������� �� �������� ������� ��� ������ ������ ������." // 
#define LOCALIZED_RETURNTOEDIT                  "��������� ���� �����������;" // 

#define LOCALIZED_EDITFAILEDTOLOAD              "� ����������� ��� ������� �� ��������" // Isn't the use of capitals like shouting to the programmer for making a mistake? ;P

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
#define LOCALIZED_FILEFILTER_ALLFILES "��� �� ������ (*.*)|*.*"
#define LOCALIZED_FILEFILTER_LOGO     "������ Logo (*.lgo)|*.lgo|" LOCALIZED_FILEFILTER_ALLFILES
#define LOCALIZED_FILEFILTER_IMAGE    "������ ������� Bitmap (*.bmp)|*.bmp|������ ������� GIF (*.gif)|*.gif|" LOCALIZED_FILEFILTER_ALLFILES



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             " ���������\n"
#define LOCALIZED_TRACING_OUTPUTS           " ���������� %s\n"
#define LOCALIZED_TRACING_MAKE              "��������� %s %s"
#define LOCALIZED_TRACING_PPROP             "�������� %s %s %s"
#define LOCALIZED_TRACING_LOCATION          " ��� %s\n%s"

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  "����-����"

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  "%s ��������\n" // 


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    "�������" // 
#define LOCALIZED_PENMODE_REVERSE  "����������" // 
#define LOCALIZED_PENMODE_PAINT    "����������" // 

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          "Logo: ��������� ������" // 
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       "Logo: ���������� ������" // 
#define LOCALIZED_ERROR_OUTOFMEMORY            "���������� ������" // 
#define LOCALIZED_ERROR_STACKOVERFLOW          "����������� �������" // 
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      "������ ����� �����" // 
#define LOCALIZED_ERROR_BADGRAPHINIT           "�������� ��������� ��������" // 
#define LOCALIZED_ERROR_BADDATA                "��� %p ��� ������ �� %s �� ����������" // 
#define LOCALIZED_ERROR_DIDNTOUTPUT            "�� %p ��� ��������� ���� ��� �� %p" // 
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        "���������� ���������� ��� �� %p" // 
#define LOCALIZED_ERROR_TOOMUCH                "���������� ������ ��������� ������� ��� ()" // 
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    "��� ����� �� �� ���� �� �� %s" // 
#define LOCALIZED_ERROR_PARENMISMATCH          "���������� ����� ('s" // 
#define LOCALIZED_ERROR_NOVALUE                "�� %s ��� ���� ����" // 
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        "�� ������������ ')'" // 
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      "�� ������������ ']'" // 
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        "�� ������������ '}'" // 
#define LOCALIZED_ERROR_DONTKNOWHOWTO          "��� ���� �� %p" // 
#define LOCALIZED_ERROR_NOCATCHTAG             "�� ����� �� ��� ������� ��������� ��� �� %p" // 
#define LOCALIZED_ERROR_ALREADYDEFINED         "�� %p ���� ��� �������" // 
#define LOCALIZED_ERROR_STOPPING               "���������..." // 
#define LOCALIZED_ERROR_ALREADYDRIBBLING       "������� ��� ���������" // 
#define LOCALIZED_ERROR_FILESYSTEM                   "������ ���������� �������: %p" // 
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          "�������� ����������" // 
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         "�������� ���������� ��� %t" // 
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       "�� ������ ����� ��� �������" // 
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           "�� ������ ��� ����� �������" // 
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  "�������� ���������� ��� ������� ����������� ������"// 
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   "�������� ���������� ��� ����������� ������"  // 
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    "�������� ��������� ��� ������� ����������� ������"  // 
#define LOCALIZED_ERROR_IFWARNING              "����� ��� ��������� IFELSE, ��� IF" // This should change a little when primitives are localized
#define LOCALIZED_ERROR_SHADOWWARNING          "�� %p ������������ ��� ������ ���� ����� ��� �������" // I could make it a little more accurate if I knew whether it refers to a variable or something else
#define LOCALIZED_ERROR_USER                   "Throw \"Error" // 
#define LOCALIZED_ERROR_ISPRIMITIVE            "�� %p ����� ����������� ������" // 
#define LOCALIZED_ERROR_TONOTINSIDE            "������� � ����� ��� TO ���� �� ������" // But why? :D
#define LOCALIZED_ERROR_ATTOPLEVEL             "�� %p ��������������� ���� ���� �� �������" // 
#define LOCALIZED_ERROR_ATTOPLEVEL2            "�������� �� ��������������� OUTPUT � STOP ���� ���� �� ������" // 
#define LOCALIZED_ERROR_NOTEST                 "%p ����� TEST" // 
#define LOCALIZED_ERROR_BADMACROOUTPUT         "� ����������� ��������� %s ���� ��� �����" // 
#define LOCALIZED_ERROR_DEEPEND                "�� END ��������� ���� �� ������ ��������� �������" // 
#define LOCALIZED_ERROR_DEEPENDIN              "�� END ��������� ���� �� ������ ��������� ������� ��� %p" // 
#define LOCALIZED_ERROR_UNKNOWN                "������� ��������� ��������� - ��������� ������." // 
#define LOCALIZED_PAUSING                      "�����..." // 


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION "Invalid state for instruction: %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MODE_ON_SPRITE             "cannot set the mode of a turtle with a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        "cannot make a special turtle use a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            "cannot use the clipboard as a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_SPECIALFORM                "%p doesn't like %p as input because it has a special form" // NOT_YET_LOCALIZED

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      "������" // 
#define LOCALIZED_ERROR_BADINPUT             "���� ����������" // 
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    "� ���������� ��� ���������" // 

#define LOCALIZED_ERROR_CANTOPENPORT         "������� �� ������� ��� �����" // 
#define LOCALIZED_ERROR_CANTCLOSEPORT        "������� �� �������� ��� �����" // 
#define LOCALIZED_ERROR_CANTFLUSHPORT        "������� �� �������� ��� �����" // 
#define LOCALIZED_ERROR_CANTDCBONPORT        "������� � ���������� dcb ��� ����" // 
#define LOCALIZED_ERROR_CANTSETPORT          "������� � ������� ��� �����" // 
#define LOCALIZED_ERROR_PORTALREADYOPEN      "� ���� ����� ��� �������" // 
#define LOCALIZED_ERROR_PORTNOTOPEN          "� ���� ��� ����� �������" // 

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   "������� ���: %s"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    "��� �������: %s"

#define LOCALIZED_ERROR_DLLNOTLOADED          "�� DLL ��� ���� ��������" // 
#define LOCALIZED_ERROR_DLLLOADFAILED         "� ������� ��� DLL �������" // 
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    "������ ����� ���������" // 
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  "������ ����� ����������" // 
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   "� ��������� �� �������" // 
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  "��� ����������� ���� �� ���������� �����/���������" // 

#define LOCALIZED_ERROR_NETWORK               "������ �������" // 
#define LOCALIZED_ERROR_NETWORKRECEIVE        "������ �������� ��� �� ������" // 
#define LOCALIZED_ERROR_NETWORKSEND           "������ ��������� ��� ������" // 
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       "�� ������������ ������, ���� �� ������ �� �������" // 
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     "��� ������" // 
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED "���� ��� �������" // 
#define LOCALIZED_ERROR_NETWORKALREADYON      "��� �������" // 
#define LOCALIZED_ERROR_NETWORKALREADYOFF     "��� �������" // 

// The rest of the network errors shouldn't really be seen -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         "���� ������ �����" // 
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      "��� ������" // 
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      "�� ������� ��� ����� ������" // 
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED "� ������ ��� �������������" // 
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   "������� � �������� ���� �� �������� ��� ��������" // 
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         "� ����� ���������� ���������" // 
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    "������� ��������: �� ������� � ��������� �����������" // 
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH "���������: �� ������� � ��������� �����������. ����� �� NETSTARTUP" // 
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      "�� ��������� ������" // 
#define LOCALIZED_ERROR_NETWORKNODATA              "��� ������� ������� ���������" // 
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       "����� ������� �������" // 
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          "� ���������� �� ��������" // 
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       "� ���������� ���������� ����" // 
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   "� ���������� ���������� ���" // 
#define LOCALIZED_ERROR_NETWORKBADADDRESS          "���� ���������" // 
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     "���������� ��������� ����������" // 
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      "�� ������ ����� ���� ������" // 
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      "� ���������� ����������� ��� �������������" // 
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         "� ��������� ��� ����� ������" // 
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     "���� ���������" // 
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           "� �������� ������ �����������" // 
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT // 
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        "����� ������� ������" // 
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        "� �������� ������������" // 
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          "���������� �������� �� �� �������" // 
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    "������� � �������� ��� ���������� �����������" // 
#define LOCALIZED_ERROR_NETWORKADDRINUSE           "� ��������� ��������������� ���" // 
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      "� ���������� ����������� ��� ������������� ��� ��� ���������� �����������" // 
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            "� ������ �������� �����" // 
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    "� ����� �������� ��� �������������" // 
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   "� ����� ����������� ��� �������������" // 
#define LOCALIZED_ERROR_NETWORKNOBUFFER            "��� ������� ����� ���� ��������� ����� (buffer)" // 
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    "� ������� ����� ��� �����������" // 
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        "� ������� ��� ����� �����������" // 
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         "���� ������� ��� ����������" // 
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     "� ������� ��������" // 
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     "�� ��������� ��������� �������� ��� ��������" // 
#define LOCALIZED_ERROR_NETWORKISDOWN              "�� ������ �� ����������" // 
#define LOCALIZED_ERROR_NETWORKRESET               "�� ������ ��������" // 
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   "� ������� ��� ����� �����" // 
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          "� ��������� ����������� �� ����������" // 
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   "������� � ����� �� ��� �������� ����������" // 
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        "�� ���������� ����� ����� ����� ��� ��� �������" // 
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   "� ���������� ��� ������������� ���� �������" // 
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         "�� ������� �������� ���� ������������� �������� ����������" // 
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         "���������� ������ ��������" // 

#define LOCALIZED_ERROR_POLYSTART               "������ PolyStart" // 
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED "����� ��� ��������� ��� ��������" // 

#define LOCALIZED_ERROR_POLYEND                 "������ PolyEnd" // 
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       "��� ����� ��������� ��������" // 
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     "���������� ����������� 3 ���������� ��� �� ������� ��� ��������" // 

#define LOCALIZED_ERROR_SOUND                 "������ ����" // 

#define LOCALIZED_ERROR_MIDI                  "������ MIDI" // 
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     "����� ������� MIDI" // 
#define LOCALIZED_ERROR_MIDIALREADYOPEN       "����� ��� �������" // 
#define LOCALIZED_ERROR_MIDINOTOPEN           "��� ����� �������" // 

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      "��� ������� ������� ��� ��������" // 

#define LOCALIZED_ERROR_MCI                   "������ MCI" // 

#define LOCALIZED_ERROR_TIMERNOTFOUND         "� �������������� �� �������" // 

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       "� online ������� ��� ����� ��������� ����� �� hhctrl.ocx �� ���������."  // 

#define LOCALIZED_ERROR_BADCOMMANDLINE        "����� ������ ������� �������"  // 

#define LOCALIZED_ERROR_TMPNOTDEFINED         "� ��������� ������������� TMP ��� ���� ������� � ����� �����.\n� " LOCALIZED_GENERAL_PRODUCTNAME " �� ����������� �� �������������� �� C:\\ ��� ��� ���������� ���������� �������" //

#define LOCALIZED_ERROR_GIFSAVEFAILED         "������� � ���������� ��� GIF, ������� �� ����� ��� �� ���� ��� �����" // 
#define LOCALIZED_ERROR_GIFREADFAILED         "������� � �������� ��� GIF, ������� �� ����� ��� �� ���� ��� �����" // 

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  "� ������� BitMap ����� ����� �����" // 
#define LOCALIZED_ERROR_BITMAPCUTFAILED        "� ������� (cut) �������, ���� ��� ������� ������ �����" // 

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    "��� ������� ������ ��� ����������"  // 
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  "�� BitMap ���� �������� ������ �� ���� ��������� �� ��� ������"  // 

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      "� ������ %d ��� ���� ������, �� ����������" // 

#define LOCALIZED_ERROR_FONTNOTFOUND            "� ������������� %s �� �������.  �������� ��� ��� ��� ��������:\n" // 

#define LOCALIZED_ERROR_PRINTERCANTSCALE        "� ������ ��� �������� ��� ����������� ���� �� ����������."  // 
#define LOCALIZED_ERROR_CANTDRAWIMAGE           "� ������ �� ������ �� ����������" // 
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        "� ������ �� ������ �� �������" // 
#define LOCALIZED_ERROR_SUBCODE                 "����������" // 

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         "����������:" // 
#define LOCALIZED_PROMPT_TO     "������� To (������� ��� End)" // 
#define LOCALIZED_PROMPT_LIST   "������� List (������� ��� ���������)" // 
#define LOCALIZED_PROMPT_PAUSE  "������� Pause (������� ��� ��������)" // 
#define LOCALIZED_PROMPT_INPUT  "������� Input (������� ��� ���������)" // 

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      "������� ���� �������� \"%s\"" // 
#define LOCALIZED_FILE_CHDIRFAILED         "������� � ������� ��� �������� \"%s\"" // 
#define LOCALIZED_FILE_POPPEDTO            "������ ���� �������� \"%s\"" // 
#define LOCALIZED_FILE_MKDIRSUCCEEDED      "������� ��� ��� �������� \"%s\""  // 
#define LOCALIZED_FILE_MKDIRFAILED         "�������� ����������� ��� ��������� \"%s\""  // 
#define LOCALIZED_FILE_RMDIRSUCCEEDED      "���������� ��������� \"%s\""  // 
#define LOCALIZED_FILE_RMDIRFAILED         "�������� ��������� ��� ��������� \"%s\""  // 
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  "� ��������� ��� �������" // 
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY "������������� ��� � ��������� ����� ������ ���� ������������ �� ��� ����������." // 


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       "Logo Picture" // NOT_YET_LOCALIZED

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    "������ �������" // 
#define LOCALIZED_INFORMATION   "�����������" // 
#define LOCALIZED_WARNING       "�������" // 
#define LOCALIZED_UNTITLED      "����� �����" // 
#define LOCALIZED_UNKNOWN       "�������" // 

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       "(����� �����)" // 

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     "������"
#define LOCALIZED_EDITOR_TITLE_REPLACE  "�������������"

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING "{ �� ������� �� %s }" // 


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
// These should match the corresponding terms that is used
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


//
// The name of the default font face name.
// This should only be translated if the given font face doesn't include glyphs
// for characters in your language.  The specified font face name must be part
// of all Windows versions from Windows XP onward that would support your
// language.
//
#define LOCALIZED_DEFAULT_FONT_FACE "Courier New" // NOT_YET_LOCALIZED
