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
//   "Impossible d'utiliser POUR (TO) dans une procιdure"
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
#define LOCALIZED_ALTERNATE_TRUE     "true" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FALSE    "false" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_END      "end" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TOPLEVEL "toplevel" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SYSTEM   "system" // NOT_YET_LOCALIZED

//
// Localized "alternate" names of Logo special variables
//
#define LOCALIZED_ALTERNATE_CASEIGNOREDP   "caseignoredp" // NOT_YET_LOCALIZED


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
#define LOCALIZED_ALTERNATE__DEFMACRO              ".defmacro" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE__EQ                    ".eq" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE__MACRO                 ".macro" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE__MAYBEOUTPUT           ".maybeoutput" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE__SETBF                 ".setbf" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE__SETFIRST              ".setfirst" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE__SETITEM               ".setitem" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ACTIVEAREA             "activearea" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ALLOPEN                "allopen" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_AND                    "and" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_APPLY                  "apply" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARCCOS                 "arccos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARCSIN                 "arcsin" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARCTAN                 "arctan" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARRAY                  "array" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARRAYP                 "arrayp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARRAY_                 "array?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ASCII                  "ascii" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ASHIFT                 "ashift" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BACK                   "back" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BACKSLASHEDP           "backslashedp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BACKSLASHED_           "backslashed?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BEFOREP                "beforep" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BEFORE_                "before?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BF                     "bf" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BFS                    "bfs" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITAND                 "bitand" // NOT_YET_LOCALIZED
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
#define LOCALIZED_ALTERNATE_BITNOT                 "bitnot" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITOR                  "bitor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITPASTE               "bitpaste" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITPASTETOINDEX        "bitpastetoindex" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITSAVE                "bitsave" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITXOR                 "bitxor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BK                     "bk" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BL                     "bl" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BURIED                 "buried" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BURY                   "bury" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTFIRST               "butfirst" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTFIRSTS              "butfirsts" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTLAST                "butlast" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTTONCREATE           "buttoncreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTTONDELETE           "buttondelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTTONENABLE           "buttonenable" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTTONUPDATE           "buttonupdate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTTONP                "buttonp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTTON_                "button?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BYE                    "bye" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CATCH                  "catch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CHAR                   "char" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CHDIR                  "chdir" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CHECKBOXCREATE         "checkboxcreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CHECKBOXDELETE         "checkboxdelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CHECKBOXENABLE         "checkboxenable" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CHECKBOXGET            "checkboxget" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CHECKBOXSET            "checkboxset" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CLEAN                  "clean" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CLEARPALETTE           "clearpalette" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CLEARSCREEN            "clearscreen" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CLEARTEXT              "cleartext" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CLEARTIMER             "cleartimer" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CLOSE                  "close" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CLOSEALL               "closeall" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CO                     "co" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COMBOBOXADDSTRING      "comboboxaddstring" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COMBOBOXCREATE         "comboboxcreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COMBOBOXDELETE         "comboboxdelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COMBOBOXENABLE         "comboboxenable" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING   "comboboxdeletestring" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COMBOBOXGETTEXT        "comboboxgettext" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COMBOBOXSETTEXT        "comboboxsettext" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CONTENTS               "contents" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CONTINUE               "continue" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COPYDEF                "copydef" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COS                    "cos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COUNT                  "count" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CS                     "cs" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CT                     "ct" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CURSOR                 "cursor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DEBUGWINDOWS           "debugwindows" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DEFINE                 "define" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DEFINEDP               "definedp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DEFINED_               "defined?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DIALOGCREATE           "dialogcreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DIALOGENABLE           "dialogenable" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DIALOGDELETE           "dialogdelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         "dialogfileopen" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DIALOGFILESAVE         "dialogfilesave" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DIFFERENCE             "difference" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DIRECTORIES            "directories" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DLLCALL                "dllcall" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DLLFREE                "dllfree" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DLLLOAD                "dllload" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DOWN                   "down" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DOWNPITCH              "downpitch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DRIBBLE                "dribble" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ED                     "ed" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EDIT                   "edit" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ELLIPSEARC             "ellipsearc" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EMPTYP                 "emptyp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EMPTY_                 "empty?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EOFP                   "eofp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EOF_                   "eof?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EQUALP                 "equalp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EQUAL_                 "equal?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ER                     "er" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ERASE                  "erase" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ERASEFILE              "erasefile" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ERF                    "erf" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ERROR                  "error" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EVENTCHECK             "eventcheck" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EXP                    "exp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FD                     "fd" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FENCE                  "fence" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FILL                   "fill" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FILES                  "files" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FIRST                  "first" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FIRSTS                 "firsts" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FLOODCOLOR             "floodcolor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FONTFACENAMES          "fontfacenames" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FOREVER                "forever" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FORM                   "form" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FORWARD                "forward" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FPUT                   "fput" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FS                     "fs" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FULLSCREEN             "fullscreen" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FULLTEXT               "fulltext" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GETFOCUS               "getfocus" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GOTO                   "goto" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GIFLOAD                "gifload" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GIFSIZE                "gifsize" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GIFSAVE                "gifsave" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GPROP                  "gprop" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GREATEREQUALP          "greaterequalp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GREATEREQUAL_          "greaterequal?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GREATERP               "greaterp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GREATER_               "greater?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GROUPBOXCREATE         "groupboxcreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GROUPBOXDELETE         "groupboxdelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HALT                   "halt" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HEADING                "heading" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HELP                   "help" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HIDETURTLE             "hideturtle" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HOME                   "home" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HT                     "ht" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_IF                     "if" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_IFELSE                 "ifelse" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_IFF                    "iff" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_IFFALSE                "iffalse" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_IFT                    "ift" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_IFTRUE                 "iftrue" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_INGAMEPORT             "ingameport" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_INPORT                 "inport" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_INPORTB                "inportb" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_INT                    "int" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ITEM                   "item" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_KEYBOARDOFF            "keyboardoff" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_KEYBOARDON             "keyboardon" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_KEYBOARDVALUE          "keyboardvalue" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_KEYP                   "keyp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_KEY_                   "key?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LABEL                  "label" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LABELFONT              "labelfont" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LABELSIZE              "labelsize" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LAST                   "last" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LEFT                   "left" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LEFTROLL               "leftroll" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LESSEQUALP             "lessequalp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LESSEQUAL_             "lessequal?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LESSP                  "lessp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LESS_                  "less?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LIGHT                  "light" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LIST                   "list" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LISTBOXADDSTRING       "listboxaddstring" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LISTBOXCREATE          "listboxcreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LISTBOXENABLE          "listboxenable" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LISTBOXDELETE          "listboxdelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LISTBOXDELETESTRING    "listboxdeletestring" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LISTBOXGETSELECT       "listboxgetselect" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LISTP                  "listp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LIST_                  "list?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LN                     "ln" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LOAD                   "load" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LOCAL                  "local" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LOG10                  "log10" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LOGOVERSION            "logoversion" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LOWERCASE              "lowercase" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LPUT                   "lput" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LR                     "lr" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LSHIFT                 "lshift" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LT                     "lt" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MACHINE                "machine" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MACROP                 "macrop" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MACRO_                 "macro?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MAKE                   "make" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MCI                    "mci" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MEMBER                 "member" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MEMBERP                "memberp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MEMBER_                "member?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MESSAGEBOX             "messagebox" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MIDICLOSE              "midiclose" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MIDIMESSAGE            "midimessage" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MIDIOPEN               "midiopen" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MINUS                  "minus" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MKDIR                  "mkdir" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MODULO                 "modulo" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MOUSEOFF               "mouseoff" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MOUSEON                "mouseon" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MOUSEPOS               "mousepos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NAMEP                  "namep" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NAME_                  "name?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NAMES                  "names" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           "netacceptoff" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NETACCEPTON            "netaccepton" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE  "netacceptreceivevalue" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE     "netacceptsendvalue" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NETCONNECTOFF          "netconnectoff" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NETCONNECTON           "netconnecton" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE "netconnectreceivevalue" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE    "netconnectsendvalue" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NETSHUTDOWN            "netshutdown" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NETSTARTUP             "netstartup" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NOBITMAPTURTLE         "nobitmapturtle" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NODES                  "nodes" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NODRIBBLE              "nodribble" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NOSTATUS               "nostatus" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NOT                    "not" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NOTEQUALP              "notequalp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NOTEQUAL_              "notequal?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NOYIELD                "noyield" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NUMBERP                "numberp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NUMBER_                "number?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OP                     "op" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OPENAPPEND             "openappend" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OPENREAD               "openread" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OPENUPDATE             "openupdate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OPENWRITE              "openwrite" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OR                     "or" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OUTPORT                "outport" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OUTPORTB               "outportb" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OUTPUT                 "output" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PARSE                  "parse" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PAUSE                  "pause" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PC                     "pc" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PD                     "pd" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PE                     "pe" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENCOLOR               "pencolor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENDOWN                "pendown" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENDOWNP               "pendownp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENDOWN_               "pendown?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENERASE               "penerase" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENMODE                "penmode" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENPAINT               "penpaint" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENPATTERN             "penpattern" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENREVERSE             "penreverse" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENSIZE                "pensize" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENUP                  "penup" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PERSPECTIVE            "perspective" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PITCH                  "pitch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PIXEL                  "pixel" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PLAYWAVE               "playwave" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PLIST                  "plist" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PLISTS                 "plists" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PO                     "po" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_POPDIR                 "popdir" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_POLYSTART              "polystart" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_POLYEND                "polyend" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_POLYVIEW               "polyview" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PORTCLOSE              "portclose" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PORTFLUSH              "portflush" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PORTMODE               "portmode" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PORTOPEN               "portopen" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PORTREADARRAY          "portreadarray" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PORTREADCHAR           "portreadchar" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PORTWRITEARRAY         "portwritearray" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PORTWRITECHAR          "portwritechar" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_POS                    "pos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_POSXYZ                 "posxyz" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_POT                    "pot" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_POWER                  "power" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PPROP                  "pprop" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PPT                    "ppt" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PR                     "pr" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PRIMITIVEP             "primitivep" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PRIMITIVE_             "primitive?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PRINT                  "print" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PROCEDUREP             "procedurep" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PROCEDURE_             "procedure?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PROPLISTP              "proplistp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PROPLIST_              "proplist?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PROCEDURES             "procedures" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PRODUCT                "product" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PU                     "pu" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PX                     "px" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_QUESTIONBOX            "questionbox" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_QUOTIENT               "quotient" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADARCCOS              "radarccos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADARCSIN              "radarcsin" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADARCTAN              "radarctan" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADCOS                 "radcos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADIOBUTTONCREATE      "radiobuttoncreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADIOBUTTONENABLE      "radiobuttonenable" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADIOBUTTONDELETE      "radiobuttondelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADIOBUTTONGET         "radiobuttonget" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADIOBUTTONSET         "radiobuttonset" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADSIN                 "radsin" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADTAN                 "radtan" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RANDOM                 "random" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RAWASCII               "rawascii" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RC                     "rc" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RCS                    "rcs" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READCHAR               "readchar" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READCHARS              "readchars" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READER                 "reader" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READLIST               "readlist" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READPOS                "readpos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READWORD               "readword" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_REMAINDER              "remainder" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_REMPROP                "remprop" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_REPCOUNT               "repcount" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_REPEAT                 "repeat" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RERANDOM               "rerandom" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RIGHT                  "right" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RIGHTROLL              "rightroll" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RL                     "rl" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RMDIR                  "rmdir" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ROLL                   "roll" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ROUND                  "round" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RR                     "rr" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RT                     "rt" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RUN                    "run" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RUNPARSE               "runparse" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RUNRESULT              "runresult" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RW                     "rw" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SAVE                   "save" // NOT_YET_LOCALIZED
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
#define LOCALIZED_ALTERNATE_SELECTBOX              "selectbox" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SENTENCE               "sentence" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETACTIVEAREA          "setactivearea" // NOT_YET_LOCALIZED
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
#define LOCALIZED_ALTERNATE_SHOW                   "show" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SHOWNP                 "shownp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SHOWN_                 "shown?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SHOWTURTLE             "showturtle" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SIN                    "sin" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SOUND                  "sound" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SPLITSCREEN            "splitscreen" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SQRT                   "sqrt" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SS                     "ss" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ST                     "st" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STANDOUT               "standout" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STATICCREATE           "staticcreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STATICDELETE           "staticdelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STATICUPDATE           "staticupdate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STATUS                 "status" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STEP                   "step" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STEPPED                "stepped" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STOP                   "stop" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SUBSTRINGP             "substringp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SUBSTRING_             "substring?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SUM                    "sum" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TAG                    "tag" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TAN                    "tan" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TEST                   "test" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TEXT                   "text" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TEXTSCREEN             "textscreen" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_THING                  "thing" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_THROW                  "throw" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TIME                   "time" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TIMEMILLI              "timemilli" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TO                     "to" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TONE                   "tone" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TOWARDS                "towards" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TOWARDSXYZ             "towardsxyz" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TRACE                  "trace" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TRACED                 "traced" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TS                     "ts" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TURTLE                 "turtle" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TURTLEMODE             "turtlemode" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TURTLES                "turtles" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TYPE                   "type" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UNBURY                 "unbury" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UNSTEP                 "unstep" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UNTRACE                "untrace" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UP                     "up" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UPPERCASE              "uppercase" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UPPITCH                "uppitch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WAIT                   "wait" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WINDOW                 "window" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WINDOWCREATE           "windowcreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WINDOWENABLE           "windowenable" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WINDOWDELETE           "windowdelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WINDOWFILEEDIT         "windowfileedit" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WINDOWSET              "windowset" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WINHELP                "winhelp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WORD                   "word" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WORDP                  "wordp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WORD_                  "word?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WRAP                   "wrap" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WRITEPOS               "writepos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WRITER                 "writer" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_YESNOBOX               "yesnobox" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_YIELD                  "yield" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ZOOM                   "zoom" // NOT_YET_LOCALIZED

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      "&OK"
#define LOCALIZED_GENERAL_CANCELBUTTON  "&’κυρο"
#define LOCALIZED_GENERAL_APPLYBUTTON   "&Apply" // NOT_YET_LOCALIZED

#define LOCALIZED_GENERAL_PRODUCTNAME   "FMSLogo"



//
// The menu options on the main window 
//
#define LOCALIZED_FILE        "&Αρχείο" // 
#define LOCALIZED_FILE_NEW    "&Νέο\t(διαγράφει εντολές και μεταβλητές)" // I'm sure "workspace" can have a better translation.
#define LOCALIZED_FILE_LOAD   "&Φόρτωση...\t(προσθέτει εντολές και μεταβλητές από αρχείο)" // 
#define LOCALIZED_FILE_OPEN   "’ν&οιγμα...\t(διαγράφει εντολές και μεταβλητές και ανοίγει ένα νέο αρχείο)" // 
#define LOCALIZED_FILE_SAVE   "&Αποθήκευση"  // 
#define LOCALIZED_FILE_SAVEAS "Αποθήκευση &ως..." // 
#define LOCALIZED_FILE_EDIT   "&Επεξεργασία..." // 
#define LOCALIZED_FILE_ERASE  "&Σβήσιμο..." // 
#define LOCALIZED_FILE_EXIT   "Έ&ξοδος" // 

#define LOCALIZED_BITMAP               "Ει&κόνα" // 
#define LOCALIZED_BITMAP_NEW           "&Νέο" // 
#define LOCALIZED_BITMAP_LOAD          "’ν&οιγμα..." // 
#define LOCALIZED_BITMAP_SAVE          "&Αποθήκευση" // 
#define LOCALIZED_BITMAP_SAVEAS        "Αποθήκευση &ως..." // 
#define LOCALIZED_BITMAP_PRINT         "&Εκτύπωση..." // 
#define LOCALIZED_BITMAP_PRINTERSETUP  "Ε&πιλογές εκτύπωσης..." // 
#define LOCALIZED_BITMAP_ACTIVEAREA    "Ενε&ργή Περιοχή..." // 

#define LOCALIZED_SET                  "&Ρύθμιση" // 
#define LOCALIZED_SET_PENSIZE          "&Μέγεθος πένας..." // 
#define LOCALIZED_SET_LABELFONT        "Γραμματοσειρά &χελωνας..." // 
#define LOCALIZED_SET_COMMANDERFONT    "Γραμματοσειρά παραθύρου &ελέγχου (commander)..." // 
#define LOCALIZED_SET_PENCOLOR         "Χρώμα &πένας..." // 
#define LOCALIZED_SET_FLOODCOLOR       "Χρώμα &γεμίσματος..." // 
#define LOCALIZED_SET_SCREENCOLOR      "Χρώμα &οθόνης..." // 

#define LOCALIZED_ZOOM                 "&Ζουμ"  // 
#define LOCALIZED_ZOOM_IN              "&Μεγέθυνση" // 
#define LOCALIZED_ZOOM_OUT             "&Σμίκρυνση" // 
#define LOCALIZED_ZOOM_NORMAL          "&Κανονικό" // 

#define LOCALIZED_HELP                 "&Βοήθεια"  // 
#define LOCALIZED_HELP_INDEX           "&Θέματα στη βοήθεια" // 
#define LOCALIZED_HELP_MCI             "Βοήθεια για το &MCI" // 
#define LOCALIZED_HELP_HELP            "&Χρήση βοήθειας" // 
#define LOCALIZED_HELP_TUTORIAL        "&Μάθημα" // Perhaps not the best one for "tutorial"
#define LOCALIZED_HELP_DEMO            "&Επίδειξη"  // 
#define LOCALIZED_HELP_EXAMPLE         "&Παραδείγματα" // 
#define LOCALIZED_HELP_RELEASENOTES    "&Σημειώσεις έκδοσης" // 
#define LOCALIZED_HELP_ABOUTFMSLOGO    "&Πληροφορίες για την "LOCALIZED_GENERAL_PRODUCTNAME"..." // I have assumed here that FMSLogo would be female grammatically, as are all the programming languages in Greek
#define LOCALIZED_HELP_MS              "&Πληροφορίες για την MS..." // 
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   "LANGUAGE to English" // NOT_YET_LOCALIZED
#define LOCALIZED_HELP_ENGLISHTOLANG   "English to LANGUAGE" // NOT_YET_LOCALIZED

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              "Επιλογή ενεργής περιοχής" // 
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       "Αυτές οι επιλογές επηρεάζουν την εκτύπωση και αποθήκευση εικόνων" // 
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        "Πάνω όριο" // 
#define LOCALIZED_SELECTACTIVEAREA_YLOW         "Κάτω όριο"  // 
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        "Δεξί όριο" // 
#define LOCALIZED_SELECTACTIVEAREA_XLOW         "Αριστερό όριο" // 
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH "Βήματα χελώνας ανά ίντσα:" // 
#define LOCALIZED_SELECTACTIVEAREA_RESET        "&Επαναφορά"  // 
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON // Localized above
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON // 


//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     "Αντι&γραφή" // 
#define LOCALIZED_POPUP_CUT                      "Απ&οκοπή" // 
#define LOCALIZED_POPUP_PASTE                    "&Επικόλληση" // 
#define LOCALIZED_POPUP_DELETE                   "&Διαγραφή" // 
#define LOCALIZED_POPUP_UNDO                     "Α&ναίρεση" // 
#define LOCALIZED_POPUP_SELECTALL                "Ε&πιλογή όλων" // 
#define LOCALIZED_POPUP_HELP                     "Ανα&ζήτηση στη βοήθεια" // 

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   "Επεξεργαστής" // 

#define LOCALIZED_EDITOR_FILE                    "&Αρχείο" // 
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        "Αποθήκευση και έ&ξοδος\tCtrl+D" // 
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    "Απο&θήκευση" // 
#define LOCALIZED_EDITOR_FILE_PRINT              "&Εκτύπωση..."  // 
#define LOCALIZED_EDITOR_FILE_EXIT               "Έ&ξοδος"  // 

#define LOCALIZED_EDITOR_EDIT                    "&Επεξεργασία" // 
#define LOCALIZED_EDITOR_EDIT_UNDO               "Αναίρεσ&η\tCtrl+Z" // 
#define LOCALIZED_EDITOR_EDIT_CUT                "Απ&οκοπή\tCtrl+X" // 
#define LOCALIZED_EDITOR_EDIT_COPY               "Αντι&γραφή\tCtrl+C" // 
#define LOCALIZED_EDITOR_EDIT_PASTE              "&Επικόλληση\tCtrl+V" // 
#define LOCALIZED_EDITOR_EDIT_DELETE             "&Διαγραφή\tDel" // 
#define LOCALIZED_EDITOR_EDIT_CLEARALL           "Κα&θαρισμός όλων\tCtrl+Del" // 
#define LOCALIZED_EDITOR_EDIT_SELECTALL          "Ε&πιλογή όλων\tCtrl+A" // 

#define LOCALIZED_EDITOR_SEARCH                  "Ανα&ζήτηση" // 
#define LOCALIZED_EDITOR_SEARCH_FIND             "Εύ&ρεση...\tCtrl+F" // 
#define LOCALIZED_EDITOR_SEARCH_REPLACE          "Αντι&κατάσταση...\tCtrl+H"  // 
#define LOCALIZED_EDITOR_SEARCH_NEXT             "Ε&πόμενο\tF3"  // 

#define LOCALIZED_EDITOR_SET                     "&Ρυθμίση"  // 
#define LOCALIZED_EDITOR_SET_FONT                "&Γραμματοσειρά..."  // 

#define LOCALIZED_EDITOR_TEST                    "Δοκιμή!" // 

#define LOCALIZED_EDITOR_HELP                    "&Βοήθεια"  // 
#define LOCALIZED_EDITOR_HELP_INDEX              "&Θέματα στη βοήθεια" // 
#define LOCALIZED_EDITOR_HELP_EDITOR             "Επε&ξεργαστής" // 
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        "Ανα&ζήτηση θέματος\tF1" // 


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES //
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    "Απο&θήκευση και έξοδος" // 
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       "Χωρίς αποθήκευση" // 
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON // 
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       "Υπάρχουν αλλαγές που δεν έχουν αποθηκευθεί.  Αν δεν τις αποθηκεύσετε, αυτές οι αλλαγές θα χαθούν.  " // 
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       "Θέλετε να αποθηκεύσετε τις αλλαγές σας πριν την έξοδο;"  // 


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     "Παράθυρο ελέγχου" // 
#define LOCALIZED_COMMANDER_HALT                "Σταμάτημα" // 
#define LOCALIZED_COMMANDER_TRACE               "Ανίχνευση" // 
#define LOCALIZED_COMMANDER_NOTRACE             "Χωρίς" // 
#define LOCALIZED_COMMANDER_PAUSE               "Παύση" // 
#define LOCALIZED_COMMANDER_STATUS              "Κατάσταση" // 
#define LOCALIZED_COMMANDER_NOSTATUS            "Χωρίς" // 
#define LOCALIZED_COMMANDER_STEP                "Βήμα" // 
#define LOCALIZED_COMMANDER_UNSTEP              "Χωρίς" // 
#define LOCALIZED_COMMANDER_RESET               "Επαναφορά" // 
#define LOCALIZED_COMMANDER_EXECUTE             "Εκτέλεση" // 
#define LOCALIZED_COMMANDER_EDALL               "Επεξεργασία" // If that's too long, please replace it again with EDALL

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        "Κατάσταση" // 
#define LOCALIZED_STATUS_PEN                    "Πένα" // 
#define LOCALIZED_STATUS_CONTACT                "Επαφή:" // 
#define LOCALIZED_STATUS_WIDTH                  "Πλάτος:" // 
#define LOCALIZED_STATUS_STYLE                  "Στυλ:" // 
#define LOCALIZED_STATUS_ORIENTATION            "Προσανατολισμός" // 
#define LOCALIZED_STATUS_PITCH                  "Κλίση:" // 
#define LOCALIZED_STATUS_HEADING                "Κατεύθυνση:" // 
#define LOCALIZED_STATUS_ROLL                   "Στροφή:" // 
#define LOCALIZED_STATUS_TURTLE                 "Χελώνα" // 
#define LOCALIZED_STATUS_POSITION               "Θέση (XYZ):" // XYZ is fine :P
#define LOCALIZED_STATUS_WHICH                  "Χελώνα:" // 
#define LOCALIZED_STATUS_VISIBILITY             "Ορατότητα:" // 
#define LOCALIZED_STATUS_COLOR                  "Χρώμα" // 
#define LOCALIZED_STATUS_PENCOLOR               "Πένα (ΚΠΓ):" // Maybe a teacher would recognize RGB more easily than the Greek equivalent, but I've translated it anyway.
#define LOCALIZED_STATUS_FLOODCOLOR             "Γέμισμα (ΚΠΓ):" // 
#define LOCALIZED_STATUS_SCREENCOLOR            "Οθόνη (ΚΠΓ):" // 
#define LOCALIZED_STATUS_PALETTE                "Παλέτα:" // 
#define LOCALIZED_STATUS_KERNEL                 "Πυρήνας" // 
#define LOCALIZED_STATUS_CALLS                  "Κλήσεις:" // 
#define LOCALIZED_STATUS_PEAKMEMORY             "Μνήμη:" // 

#define LOCALIZED_STATUS_PENREVERSE  "Αντίστροφο" // 
#define LOCALIZED_STATUS_PENNORMAL   "Κανονικό" // 
#define LOCALIZED_STATUS_PENERASE    "Σβήσιμο" // 
#define LOCALIZED_STATUS_PENUP       "Πάνω" // 
#define LOCALIZED_STATUS_PENDOWN     "Κάτω" // 
#define LOCALIZED_STATUS_PENSHOWN    "Ορατή" //  
#define LOCALIZED_STATUS_PENHIDDEN   "Αόρατη" // 
#define LOCALIZED_STATUS_POLYGONS    "Πολύγωνα" // 
#define LOCALIZED_STATUS_VECTORS     "Διανύσματα" // 
#define LOCALIZED_STATUS_NODES       "Κόμβοι" // 

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           "&Όλες"
#define LOCALIZED_ERASEPROCEDURE                "Σβήσιμο εντολής"
#define LOCALIZED_EDITPROCEDURE                 "Επεξεργασία εντολής"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     "Ρύθμιση χρώματος" // 
#define LOCALIZED_SETCOLOR_PENCOLOR            "Pen Color" // NOT_YET_LOCALIZED
#define LOCALIZED_SETCOLOR_FLOODCOLOR          "Flood Color" // NOT_YET_LOCALIZED
#define LOCALIZED_SETCOLOR_SCREENCOLOR         "Screen Color" // NOT_YET_LOCALIZED
#define LOCALIZED_SETCOLOR_RED                 "Κόκκινο" // 
#define LOCALIZED_SETCOLOR_GREEN               "Πράσινο" // 
#define LOCALIZED_SETCOLOR_BLUE                "Γαλάζιο" // 
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON // 
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON // 
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON // NOT_YET_LOCALIZED

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   "Μέγεθος πένας" // 
#define LOCALIZED_SETPENSIZE_SIZE              "Μέγεθος" // 
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON // NOT_YET_LOCALIZED


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     "Πληροφορίες για την "LOCALIZED_GENERAL_PRODUCTNAME // 
#define LOCALIZED_ABOUTFMS_VERSION             LOCALIZED_GENERAL_PRODUCTNAME", έκδοση "FMSLOGO_VERSION // 
#define LOCALIZED_ABOUTFMS_GUI                 "GUI από τον George Mills (mills@softronix.com)\nSoftronics, Inc.\nhttp:\x2F/www.softronix.com/" // 
#define LOCALIZED_ABOUTFMS_CORE                "Πυρήνας από τον Brian Harvey (bh@cs.berkeley.edu)\nUniversity of California Berkeley" // 
#define LOCALIZED_ABOUTFMS_INSTALLER           "Εγκαταστάτης βασισμένος στο Nullsoft Scriptable Install System\nhttp:\x2F/nsis.sourceforge.net" // 
#define LOCALIZED_ABOUTFMS_ADVENTURE           "The Great Logo Adventure (ISBN 0-9651934-6-2)\nΓράφτηκε και δωρίστηκε από τον Jim Muller\nΔιαθέσιμο στο http:\x2F/www.softronix.com/" // 
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       "Ευχαριστούμε τους Yehuda Katz (yehuka@softhome.net)\nκαι Erich Neuwirth (erich.neuwirth@univie.ac.at)" // 
#define LOCALIZED_ABOUTFMS_GPL                 "Η "LOCALIZED_GENERAL_PRODUCTNAME" είναι ελεύθερο λογισμικό\nΔείτε τη GNU Public License" // I dared to add a string ("H ") before the PRODUCTNAME constant :P
#define LOCALIZED_ABOUTFMS_NEWSGROUP           "News Group στο Διαδίκτυο: comp.lang.logo\nΕπισκεφθείτε το Logo-Forum στο\nhttp:\x2F/groups.yahoo.com/group/LogoForum/" // 
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     "Μετάφραση στα Ελληνικά:\nΘοδωρής Χατζηγιαννάκης (teo64x@yahoo.gr)" // 
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON // 


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      "Πληροφορίες για το FMS" // 
#define LOCALIZED_ABOUTMS_FMS                  "FMS σημαίνει Fight Multiple Sclerosis." // Maybe someone should give an accurate translation of Multiple Sclerosis
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     "Please consider donating to the\nNational Multiple Sclerosis Society.\nhttp:\x2F/www.nmss.org\n1-800-FIGHT-MS" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTMS_OK                   LOCALIZED_GENERAL_OKBUTTON // 


//
// Strings on the SELECTBOX Dialog box
//
#define LOCALIZED_SELECTBOX_OK                 LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTBOX_CANCEL             LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED


// 
// Strings in various other dialog boxes
// 

#define LOCALIZED_CHANGESINEDITORMAYBELOST  "Αλλαγές σε αυτή την περίοδο λειτουργίας ίσως χαθούν.\n\nΘέλετε πραγματικά να κλείσετε την "LOCALIZED_GENERAL_PRODUCTNAME";" // 
#define LOCALIZED_EDITSESSIONISRUNNING      "Ο επεξεργαστής κώδικα είναι ήδη ανοιχτός" // 

#define LOCALIZED_NOTHALTEDREALLYEXIT        "Στην "LOCALIZED_GENERAL_PRODUCTNAME" δεν αρέσει να κλείνει πριν σταματήσει.\n\nΘέλετε πραγματικά να κλείσει η "LOCALIZED_GENERAL_PRODUCTNAME"?" // 
#define LOCALIZED_NOTHALTEDREALLYHALT        "Στην "LOCALIZED_GENERAL_PRODUCTNAME" δεν αρέσει να κλέινει πριν σταματήσει.\n\nΘέλετε πραγματικά να σταματήσει η "LOCALIZED_GENERAL_PRODUCTNAME"?" // 
#define LOCALIZED_LOGOISNOTHALTED            "Η "LOCALIZED_GENERAL_PRODUCTNAME" δε σταματάει" // 

#define LOCALIZED_WRITEFAILEDNOMEMORY         "Η εγγραφή απέτυχε. Ίσως δεν υπάρχει αρκετή ελεύθερη μνήμη." // 
#define LOCALIZED_COULDNOTWRITEBMP            "Αδύνατη η εγγραφή στο .bmp" // 
#define LOCALIZED_COULDNOTOPENBMP             "Αδύνατη η ανάγνωση από το .bmp" // 
#define LOCALIZED_COULDNOTCREATEBMP           "Αδύνατο να δημιουργηθεί η εικόνα Windows 3.0 bitmap" // 
#define LOCALIZED_NOTVALIDBMP                 "Η εικόν δεν είναι Windows 3.0 bitmap" // 

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         "Δεν αποθηκεύσατε στο δίσκο" // 
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     "Η εκτέλεση ενός νέου αρχείου θα σβήσει τις υπάρχουσες εντολές και μεταβλητές.\n\nΣυνέχεια;" // 
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE "Το αρχείο που φορτώνεται θα προστεθεί στις υπάρχουσες εντολές και μεταβλητές\nκαι ίσως σβήσει όποιες αλλαγές δεν έχετε αποθηκεύσει.\n\nΣυνέχεια;" // 
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    "Αυτό θα σβήσει όλες τις αλλαγές που δεν έχετε αποθηκεύσει.\n\nΣυνέχεια;" // 

#define LOCALIZED_EDITORISOPEN                  "Ξέρετε ότι ήδη έχετε μια περίοδο επεξεργασίας ανοιχτή;\n\nΟποιαδήποτε αλλαγή σε αυτή την περίοδο δε θα αποθηκευθεί." // 

#define LOCALIZED_ERROR_CANTREADFILE            "Αδυναμία ανάγνωσης του αρχείου \"%s\" από το δίσκο" // 
#define LOCALIZED_ERROR_CANTWRITEFILE           "Αδυναμία εγγραφής του αρχείου \"%s\" στο δίσκο" // 

#define LOCALIZED_SAVETOWORKSPACE                "Αποθήκευση" // 
#define LOCALIZED_CONTENTSCHANGED                "Τα περιεχόμενα άλλαξαν" // 
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE "Τα περιεχόμενα έχουν αλλάξει.\nΘέλετε να τα αποθηκεύσετε;" // 



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  "Ο δείκτης θα τοποθετηθεί μετά τον τελευταίο επιτυχημένο ορισμό.\nΕλέγξτε το παράθυρο ελέγχου για πιθανό μήνυμα λάθους." // 
#define LOCALIZED_RETURNTOEDIT                  "Επιστροφή στην επεξεργασία;" // 

#define LOCALIZED_EDITFAILEDTOLOAD              "Η επεξεργασία σας ΑΠΕΤΥΧΕ να φορτωθεί" // Isn't the use of capitals like shouting to the programmer for making a mistake? ;P



// 
//  Strings used in the File-Open filters
//
#define LOCALIZED_FILEFILTER_ALLFILES "Όλα τα αρχεία (*.*)|*.*|" // 
#define LOCALIZED_FILEFILTER_LOGO     "Αρχεία Logo (*.lgo)|*.lgo|"LOCALIZED_FILEFILTER_ALLFILES // 
#define LOCALIZED_FILEFILTER_IMAGE    "Αρχεία εικόνας Bitmap (*.bmp)|*.bmp|Αρχεία εικόνας GIF (*.gif)|*.gif|"LOCALIZED_FILEFILTER_ALLFILES // 



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             " σταματάει\n" // 
#define LOCALIZED_TRACING_OUTPUTS           " επιστρέφει %s\n" // 
#define LOCALIZED_TRACING_MAKE              "Μεταβλητή %s %s"  // 
#define LOCALIZED_TRACING_PPROP             "Ιδιότητα %s %s %s" // 
#define LOCALIZED_TRACING_LOCATION          " στο %s\n%s" // 

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  "Βήμα-βήμα" // NOT_YET_LOCALIZED

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  "%s ορίστηκε\n" // 


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    "σβήσιμο" // 
#define LOCALIZED_PENMODE_REVERSE  "αντίστροφο" // 
#define LOCALIZED_PENMODE_PAINT    "σχεδιασμός" // 

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          "Logo: Εσωτερικό σφάλμα" // 
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       "Logo: Ανεπάρκεια μνήμης" // 
#define LOCALIZED_ERROR_OUTOFMEMORY            "Ανεπάρκεια μνήμης" // 
#define LOCALIZED_ERROR_STACKOVERFLOW          "υπερχείλιση στοίβας" // 
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      "χελώνα εκτός ορίων" // 
#define LOCALIZED_ERROR_BADGRAPHINIT           "αδυναμία εκκίνησης γραφικών" // 
#define LOCALIZED_ERROR_BADDATA                "Στο %p δεν αρέσει το %s ως παράμετρος" // 
#define LOCALIZED_ERROR_DIDNTOUTPUT            "Το %p επέστρεψε τιμή για το %p" // 
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        "ανεπάρκεια παραμέτρων για το %p" // 
#define LOCALIZED_ERROR_TOOMUCH                "υπερβολικά μεγάλη παράσταση ανάμεσα στα ()" // 
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    "Δεν είπες τί να κάνω με το %s" // 
#define LOCALIZED_ERROR_PARENMISMATCH          "Υπερβολικά πολλά ('s" // 
#define LOCALIZED_ERROR_NOVALUE                "Το %s δεν έχει τιμή" // 
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        "μη προβλεπόμενο ')'" // 
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      "μη προβλεπόμενο ']'" // 
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        "μη προβλεπόμενο '}'" // 
#define LOCALIZED_ERROR_DONTKNOWHOWTO          "Δεν ξέρω το %p" // 
#define LOCALIZED_ERROR_NOCATCHTAG             "Δε μπορώ να βρω ετικέτα συνέχειας για το %p" // 
#define LOCALIZED_ERROR_ALREADYDEFINED         "Το %p έχει ήδη οριστεί" // 
#define LOCALIZED_ERROR_STOPPING               "Σταμάτημα..." // 
#define LOCALIZED_ERROR_ALREADYDRIBBLING       "Γίνεται ήδη καταγραφή" // 
#define LOCALIZED_ERROR_FILESYSTEM                   "Σφάλμα συστήματος αρχείων: %p" // 
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          "Αδυναμία ανοίγματος" // 
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         "Αδυναμία ανοίγματος του %t" // 
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       "Το αρχείο είναι ήδη ανοιχτό" // 
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           "Το αρχείο δεν είναι ανοιχτό" // 
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  "Αδυναμία δημιουργία του αρχείου επεξεργαστή κώδικα"// 
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   "Αδυναμία ανοίγματος του επεξεργαστή κώδικα"  // 
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    "Αδυναμία ανάγνωσης του αρχείου επεξεργαστή κώδικα"  // 
#define LOCALIZED_ERROR_IFWARNING              "Θεωρώ ότι εννοούσες IFELSE, όχι IF" // This should change a little when primitives are localized
#define LOCALIZED_ERROR_SHADOWWARNING          "Το %p υποσκιάζεται από τοπικό στην κλήση της εντολής" // I could make it a little more accurate if I knew whether it refers to a variable or something else
#define LOCALIZED_ERROR_USER                   "Throw \"Error" // 
#define LOCALIZED_ERROR_ISPRIMITIVE            "Το %p είναι στοιχειώδης εντολή" // 
#define LOCALIZED_ERROR_TONOTINSIDE            "Αδύνατη η χρήση του TO μέσα σε εντολή" // But why? :D
#define LOCALIZED_ERROR_ATTOPLEVEL             "Το %p χρησιμοποιείται μόνο μέσα σε εντολές" // 
#define LOCALIZED_ERROR_ATTOPLEVEL2            "Μπορείτε να χρησιμοποιήσετε OUTPUT ή STOP μόνο μέσα σε εντολή" // 
#define LOCALIZED_ERROR_NOTEST                 "%p χωρίς TEST" // 
#define LOCALIZED_ERROR_BADMACROOUTPUT         "Η μακροεντολή επέστρεψε %s αντί για λίστα" // 
#define LOCALIZED_ERROR_DEEPEND                "Το END βρίσκεται μέσα σε οδηγία πολλαπλών γραμμών" // 
#define LOCALIZED_ERROR_DEEPENDIN              "Το END βρίσκεται μέσα σε οδηγία πολλαπλών γραμμών στο %p" // 
#define LOCALIZED_ERROR_UNKNOWN                "’γνωστη κατάσταση σφάλματος - εσωτερικό σφάλμα." // 

#define LOCALIZED_PAUSING                      "Παύση..." // 


//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      "Σφάλμα" // 
#define LOCALIZED_ERROR_BADINPUT             "Κακή παράμετρος" // 
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    "Η παράμετρος δεν ταιριάζει" // 

#define LOCALIZED_ERROR_CANTOPENPORT         "Αδύνατο το άνοιγμα της θύρας" // 
#define LOCALIZED_ERROR_CANTCLOSEPORT        "Αδύνατο το κλείσιμο της θύρας" // 
#define LOCALIZED_ERROR_CANTFLUSHPORT        "Αδύνατο το άδειασμα της θύρας" // 
#define LOCALIZED_ERROR_CANTDCBONPORT        "Αδύνατη η δημιουργία dcb στη θύρα" // 
#define LOCALIZED_ERROR_CANTSETPORT          "Αδύνατη η ρύθμιση της θύρας" // 
#define LOCALIZED_ERROR_PORTALREADYOPEN      "Η θύρα είναι ήδη ανοιχτή" // 
#define LOCALIZED_ERROR_PORTNOTOPEN          "Η θύρα δεν είναι ανοιχτή" // 
#define LOCALIZED_ERROR_FIRSTINPUTNOTANARRY  "Η πρώτη παράγραφος πρέπει να είναι πίνακας (array)" // 

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   "Υπάρχει ήδη" // 
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    "Δεν υπάρχει" // 

#define LOCALIZED_ERROR_DLL                   "Σφάλμα DLL" // 
#define LOCALIZED_ERROR_DLLNOTLOADED          "Το DLL δεν έχει φορτωθεί" // 
#define LOCALIZED_ERROR_DLLALREADYLOADED      "Το DLL έχει ήδη φορτωθεί" // 
#define LOCALIZED_ERROR_DLLLOADFAILED         "Η φόρτωση του DLL απέτυχε" // 
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    "’κυρος τύπος δεδομένων" // 
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  "’κυρος τύπος επιστροφής" // 
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   "Η συνάρτηση δε βρέθηκε" // 
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  "Δεν ταιριάζουιν όλες οι παράμετροι Τύπου/Δεδομένων" // 

#define LOCALIZED_ERROR_NETWORK                    "Σφάλμα δικτύου" // 
#define LOCALIZED_ERROR_NETWORKRECEIVE             "Σφάλμα αποδοχής από το δίκτυο" // 
#define LOCALIZED_ERROR_NETWORKSEND                "Σφάλμα αποστολής στο δίκτυο" // 
#define LOCALIZED_ERROR_NETWORKSHUTDOWN            "Μη προβλεπόμενο σφάλμα, ίσως το δίκτυο να έκλεισε" // 
#define LOCALIZED_ERROR_NETWORKNOTSTARTED          "Δεν άρχισε" // 
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED      "Έχει ήδη αρχίσει" // 
#define LOCALIZED_ERROR_NETWORKALREADYON           "Ήδη ανοιχτό" // 
#define LOCALIZED_ERROR_NETWORKALREADYOFF          "Ήδη κλειστό" // 

// The rest of the network errors shouldn't really see -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         "Πολύ μεγάλο όνομα" // 
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      "Δεν άρχισε" // 
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      "Το σύστημα δεν είναι έτοιμο" // 
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED "Η έκδοση δεν υποστηρίζεται" // 
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   "Αδύνατη η αποστολή μετά το κλείσιμο της υποδοχής" // 
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         "Η κλήση συστήματος διακόπηκε" // 
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    "Επίσημη απάντηση: δε βρέθηκε ο κεντρικός υπολογιστής" // 
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH "Ανεπίσημη: δε βρέθηκε ο κεντρικός υπολογιστής. Δείτε το NETSTARTUP" // 
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      "Μη ανανήψιμο σφάλμα" // 
#define LOCALIZED_ERROR_NETWORKNODATA              "Δεν υπάρχει εγγραφή δεδομένων" // 
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       "Λάθος αριθμός αρχείου" // 
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          "Η διαδικασία θα εμπόδιζε" // 
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       "Η διαδικασία εκτελείται τώρα" // 
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   "Η διαδικασία εκτελείται ήδη" // 
#define LOCALIZED_ERROR_NETWORKBADADDRESS          "Κακή διεύθυνση" // 
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     "Χρειάζεται διεύθυνση προορισμού" // 
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      "Το μήνυμα είναι πολύ μεγάλο" // 
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      "Η οικογένεια πρωτοκόλλου δεν υποστηρίζεται" // 
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         "Ο κατάλογος δεν είναι άδειος" // 
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     "Όριο εφαρμογών" // 
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           "Η αναλογία δίσκου ξεπεράστηκε" // 
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT // 
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        "Πολλά ανοιχτά αρχεία" // 
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        "Η πρόσβαση απαγορεύτηκε" // 
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          "Διαδικασία υποδοχής σε μη υποδοχή" // 
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    "Αδύνατη η εκχώρηση των ζητούμενων διευθύνσεων" // 
#define LOCALIZED_ERROR_NETWORKADDRINUSE           "Η διεύθυνση χρησιμοποιείται ήδη" // 
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      "Η οικογένεια διευθύνσεων δεν υποστηρίζεται από την οικογένεια πρωτοκόλλου" // 
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            "Ο χρόνος σύνδεσης έληξε" // 
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    "Ο τύπος υποδοχής δεν υποστηρίζεται" // 
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   "Ο τύπος πρωτοκόλλου δεν υποστηρίζεται" // 
#define LOCALIZED_ERROR_NETWORKNOBUFFER            "Δεν υπάρχει χώρος στην προσωρινή μνήμη (buffer)" // 
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    "Η υποδοχή είναι ήδη συνδεδεμένη" // 
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        "Η υποδοχή δεν είναι συνδεδεμένη" // 
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         "Κακή επιλογή στο πρωτόκολλο" // 
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     "Η σύνδεση επανήλθε" // 
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     "Το λογισμικό προκάλεσε κλείσιμο της σύνδεσης" // 
#define LOCALIZED_ERROR_NETWORKISDOWN              "Το δίκτυο δε λειτουργεί" // 
#define LOCALIZED_ERROR_NETWORKRESET               "Το δίκτυο επανήλθε" // 
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   "Η σύνδεση δεν έγινε δεκτή" // 
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          "Ο κεντρικός υπολογιστής δε λειτουργεί" // 
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   "Αδύνατη η επαφή με τον κεντρικό υπολογιστή" // 
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        "Το πρωτόκολλο είναι λάθος τύπου για την υποδοχή" // 
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   "Η διαδικασία δεν υποστηρίζεται στην υποδοχή" // 
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         "Δε βρέθηκε διαδρομή στον απομακρυσμένο κεντρικό υπολογιστή" // 
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         "Υπερβολικά πολλές αναφορές" // 

#define LOCALIZED_ERROR_POLYSTART               "Σφάλμα PolyStart" // 
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED "Έχετε ήδη ξεκινήσει ένα πολύγωνο" // 

#define LOCALIZED_ERROR_POLYEND                 "Σφάλμα PolyEnd" // 
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       "Δεν έχετε ξεκινήσει πολύγωνο" // 
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     "Χρειάζεστε τουλάχιστον 3 διανύσματα για να ορίσετε ένα πολύγωνο" // 

#define LOCALIZED_ERROR_SOUND                 "Σφάλμα ήχου" // 

#define LOCALIZED_ERROR_MIDI                  "Σφάλμα MIDI" // 
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     "’κυρη συσκευή MIDI" // 
#define LOCALIZED_ERROR_MIDIALREADYOPEN       "Είναι ήδη ανοιχτή" // 
#define LOCALIZED_ERROR_MIDINOTOPEN           "Δεν είναι ανοιχτή" // 

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      "Δεν υπάρχει κείμενο στο πρόχειρο" // 

#define LOCALIZED_ERROR_MCI                   "Σφάλμα MCI" // 

#define LOCALIZED_ERROR_TIMERTOOMANY          "Υπερβολικά πολλοί χρονοδιακόπτες" // 
#define LOCALIZED_ERROR_TIMERBADID            "Λάθος αριθμός χρονοδιακόπτη" // 
#define LOCALIZED_ERROR_TIMERNOTFOUND         "Ο χρονοδιακόπτης δε βρέθηκε" // 

#define LOCALIZED_ERROR_BITMODEBADBITMODE     "’κυρο BitMode" // 

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       "Η online βοήθεια δεν είναι διαθέσιμη γιατί το hhctrl.ocx δε φορτώθηκε."  // 
#define LOCALIZED_ERROR_HHCTRLATOMNOTFOUND    "Η online βοήθεια δεν είναι διαθέσιμη γιατί το hhctrl.ocx δεν περιέχει ATOM_HTMLHELP_API_ANSI."  // 

#define LOCALIZED_ERROR_BADCOMMANDLINE        "Λάθος εντολή γραμμής εντολών"  // 

#define LOCALIZED_ERROR_TMPNOTDEFINED         "Η μεταβλητή περιβάλλοντος TMP δεν έχει οριστεί ή είναι άκυρη.\nΗ "LOCALIZED_GENERAL_PRODUCTNAME" θα προσπαθήσει να χρησιμοποιήσει το C:\\ για την αποθήκευση προσωρινών αρχείων" // 

#define LOCALIZED_ERROR_GIFSAVEFAILED         "Αδύνατη η δημιουργία του GIF, ελέγξτε τη μνήμη και το χώρο στο δίσκο" // 
#define LOCALIZED_ERROR_GIFREADFAILED         "Αδύνατη η ανάγνωση του GIF, ελέγξτε τη μνήμη και το χώρο στο δίσκο" // 

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  "Ο δείκτης BitMap είναι εκτός ορίου" // 
#define LOCALIZED_ERROR_BITMAPCUTFAILED        "Η αποκοπή (cut) απέτυχε, ίσως δεν υπάρχει αρκετή μνήμη" // 
#define LOCALIZED_ERROR_BITMAPFITFAILED        "Η προσαρμογή (fit) απέτυχε, ίσως δεν υπάρχει αρκετή μνήμη" // 

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    "Δεν υπάρχει τίποτα για επικόλληση"  // 
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  "Το BitMap στον κατάλογο πρέπει να έχει εκκινηθεί με μια εικόνα"  // 

#define LOCALIZED_ERROR_BADTURTLEID             "Λάθος αριθμός χελώνας" // 
#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      "Η χελώνα %d δεν έχει εικόνα, θα σταματήσει" // 

#define LOCALIZED_ERROR_FONTNOTFOUND            "Η γραμματοσειρά %s δε βρέθηκε.  Επιλέξτε μία από τις παρακάτω:\n" // 

#define LOCALIZED_ERROR_PRINTERCANTSCALE        "Ο οδηγός του εκτυπωτή δεν υποστηρίζει αυτή τη δυνατότητα."  // 
#define LOCALIZED_ERROR_CANTDRAWIMAGE           "Η εικόνα δε μπορεί να σχεδιαστεί" // 
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        "Η εικόνα δε μπορεί να εξαχθεί" // 
#define LOCALIZED_ERROR_SUBCODE                 "Υποκώδικας" // 

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         "Παράμετρος:" // 
#define LOCALIZED_PROMPT_TO     "Σύστημα To (Ακύρωση για End)" // 
#define LOCALIZED_PROMPT_LIST   "Σύστημα List (Ακύρωση για Σταμάτημα)" // 
#define LOCALIZED_PROMPT_PAUSE  "Σύστημα Pause (Ακύρωση για Συνέχεια)" // 
#define LOCALIZED_PROMPT_INPUT  "Σύστημα Input (Ακύρωση για Σταμάτημα)" // 

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      "Είσοδος στον κατάλογο \"%s\"" // 
#define LOCALIZED_FILE_CHDIRFAILED         "Αδύνατη η είσοδος τον κατάλογο \"%s\"" // 
#define LOCALIZED_FILE_POPPEDTO            "Έξοδος στον κατάλογο \"%s\"" // 
#define LOCALIZED_FILE_MKDIRSUCCEEDED      "Είσοδος στο νέο κατάλογο \"%s\""  // 
#define LOCALIZED_FILE_MKDIRFAILED         "Αδυναμία δημιουργίας του καταλόγου \"%s\""  // 
#define LOCALIZED_FILE_RMDIRSUCCEEDED      "Αφαιρέθηκε κατάλογος \"%s\""  // 
#define LOCALIZED_FILE_RMDIRFAILED         "Αδυναμία αφαίρεσης του καταλόγου \"%s\""  // 
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  "Ο κατάλογος δεν υπάρχει" // 
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY "Σιγουρευτείτε ότι ο κατάλογος είναι άδειος πριν προσπαθήσετε να τον αφαιρέσετε." // 


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       "Logo Picture" // NOT_YET_LOCALIZED

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    "Ενεργή περιοχή" // 
#define LOCALIZED_INFORMATION   "Πληροφορίες" // 
#define LOCALIZED_WARNING       "Προσοχή" // 
#define LOCALIZED_UNTITLED      "Χωρίς τίτλο" // 
#define LOCALIZED_UNKNOWN       "’γνωστο" // 

#define LOCALIZED_UNBOUND       "(Εκτός ορίου)" // 

//
// Strings that explain the purpose of each menu option.
// I don't think that any of these strings can be seen by the user, 
// so you probably don't have to translate these.
//
#define LOCALIZED_STRINGTABLE_FILESAVEAS "Αποθηκεύει τον κώδικα και τις μεταβλητές σε ένα αρχείο" // 
#define LOCALIZED_STRINGTABLE_FILEOPEN "Σβήνει τον τρέχοντα κώδικα και φορτώνει ένα νέο αρχείο" // 
#define LOCALIZED_STRINGTABLE_FILELOAD "Εντοπίζει και φορτώνει ένα πρόγραμμα Logo, προσθέτοντάς το στον υπάρχοντα κώδικα" // 
#define LOCALIZED_STRINGTABLE_FILENEW "Σβήνει όλο τον κώδικα" // 
#define LOCALIZED_STRINGTABLE_FILESAVE "Αποθηκεύει όλο τον κώδικα" // 
#define LOCALIZED_STRINGTABLE_FILEEDIT "Επιλογή μιας εντολής προς επεξεργασία" // 
#define LOCALIZED_STRINGTABLE_FILEERASE "Επιλογή μιας εντολής προς διαγραφή" // 
#define LOCALIZED_STRINGTABLE_EXIT "Κλείνει τη Logo" // 
#define LOCALIZED_STRINGTABLE_BITMAPNEW "Καθαρίζει τη οθόνη" // 
#define LOCALIZED_STRINGTABLE_BITMAPOPEN "Φορτώνει μια εικόνα Windows bitmap" // 
#define LOCALIZED_STRINGTABLE_BITMAPSAVE "Αποθηκεύει τα περιεχόμενα της οθόνης σε μια εικόνα bitmap" // 
#define LOCALIZED_STRINGTABLE_BITMAPSAVEAS "Αποθηκεύει τα περιεχόμενα της οθόνης σε άλλο αρχείο" // 
#define LOCALIZED_STRINGTABLE_BITMAPPRINT "Εκτυπώνει τα περιεχόμενα της οθόνης" // 
#define LOCALIZED_STRINGTABLE_BITMAPPRINTERSETUP "Ρυθμίζει τον εκτυπωτή σας" // 
#define LOCALIZED_STRINGTABLE_BITMAPPRINTERAREA "Ρυθμίζει την περιοχή της οθόνης που θα εκτυπωθεί ή θα αποθηκευθεί" // 
#define LOCALIZED_STRINGTABLE_SETPENSIZE "Ρυθμίζει το πάχος της πένας της χελώνας" // 
#define LOCALIZED_STRINGTABLE_SETFONT "Ρυθμίζει τη γραμματοσειρά που χρησιμοποιείται από την εντολή LABEL" // 
#define LOCALIZED_STRINGTABLE_SETCOMMANDERFONT "Ρυθμίζει τη γραμματοσειρά που χρησιμοποιείται στο παράθυρο ελέγχου" // 
#define LOCALIZED_STRINGTABLE_SETPENCOLOR "Ρυθμίζει το χρώμα της πένας της χελώνας" // 
#define LOCALIZED_STRINGTABLE_SETFLOODCOLOR "Ρυθμίζει το χρώμα που χρησιμοποιείται από την εντολή FILL" // 
#define LOCALIZED_STRINGTABLE_SETSCREENCOLOR "Καθαρίζει την οθόνη και τις δίνει ένα διαφορετικό χρώμα" // 
#define LOCALIZED_STRINGTABLE_ZOOMIN "Μεγεθύνει την οθόνη" // 
#define LOCALIZED_STRINGTABLE_ZOOMOUT "Σμικρύνει την οθόνη" // 
#define LOCALIZED_STRINGTABLE_ZOOMNORMAL "Επαναφέρει την οθόνη στο κανονικό της μέγεθος" // 
#define LOCALIZED_STRINGTABLE_HELP "Ανοίγει έναν κατάλογο με θέματα στη βοήθεια" // 
#define LOCALIZED_STRINGTABLE_HELPMCI "Ανοίγει έναν κατάλογο με θέματα στη βοήθεια για το Media Control Interface" // 
#define LOCALIZED_STRINGTABLE_HELPHELP "Ανοίγει βοήθεια σχετική με τη χρήση της βοήθειας" // 
#define LOCALIZED_STRINGTABLE_HELPTUTORIAL "Ανοίγει ένα μικρό μάθημα σχετικό με τη χρήση της "LOCALIZED_GENERAL_PRODUCTNAME // 
#define LOCALIZED_STRINGTABLE_HELPDEMO "Κάνει μια επίδειξη του τί μπορείτε να κάνετε στην "LOCALIZED_GENERAL_PRODUCTNAME // 
#define LOCALIZED_STRINGTABLE_HELPEXAMPLES "Εμφανίζει έναν κατάλογο με προγράμματα-δείγματα" // 
#define LOCALIZED_STRINGTABLE_HELPRELEASENOTES "Εμφανίζει τις σημειώσεις αυτής της έκδοσης της "LOCALIZED_GENERAL_PRODUCTNAME // 
#define LOCALIZED_STRINGTABLE_HELPABOUT "Εμφανίζει την έκδοση και πληροφορίες copyright" // 
#define LOCALIZED_STRINGTABLE_HELPABOUTMS "Εμφανίζει ένα μήνυμα σχετικά με τη Multiple Sclerosis" // 
#define LOCALIZED_STRINGTABLE_EDITDELETE "Διαγράφει την τρέχουσα επιλογή (και δεν αντιγράφει στο πρόχειρο)" // 
#define LOCALIZED_STRINGTABLE_EDITCLEAR "Διαγράφει όλο το κείμενο" // 
#define LOCALIZED_STRINGTABLE_EDITUNDO "Αναιρεί την προηγούμενη ενέργεια" // 
#define LOCALIZED_STRINGTABLE_EDITCUT "Αφαιρεί το επιλεγμένο κείμενο και το μεταφέρει στο πρόχειρο" // 
#define LOCALIZED_STRINGTABLE_EDITCOPY "Αντιγράφει το επιλεγμένο κείμενο στο πρόχειρο" // 
#define LOCALIZED_STRINGTABLE_EDITPASTE "Εισάγει το κείμενο από το πρόχειρο στην τρέχουσα θέση" // 
#define LOCALIZED_STRINGTABLE_EDITSELECTALL "Επιλέγει όλο το κείμενο" // 
#define LOCALIZED_STRINGTABLE_EDITFIND "Ψάχνει για κείμενο" // 
#define LOCALIZED_STRINGTABLE_EDITREPLACE "Ψάχνει για κείμενο και το αντικαθιστά με άλλο κείμενο" // 
#define LOCALIZED_STRINGTABLE_EDITFINDNEXT "Επαναλαμβάνει την τελευταία εντολή Εύρεσης ή Αντικατάστασης" // 
#define LOCALIZED_STRINGTABLE_EDITSETFONT "Ρυθμίζει τη γραμματοσειρά για τον επεξεργαστή κώδικα" // 
#define LOCALIZED_STRINGTABLE_TEST "Εκτελεί τις επιλεγμένες εντολές Logo " // 
#define LOCALIZED_STRINGTABLE_HELPEDIT "Εμφανίζει βοήθεια για τη χρήση του επεξεργαστή κώδικα" // 
#define LOCALIZED_STRINGTABLE_HELPEDIT_TOPIC "Εμφανίζει βοήθεια για τη Logo" // 
#define LOCALIZED_STRINGTABLE_FILESAVEANDEXIT "Αποθηκεύει τον κώδικα και κλείνει τον επεξεργαστή κώδικα" // 
#define LOCALIZED_STRINGTABLE_FILESAVETOWORKSPACE "Αποθηκεύει τον κώδικα" // 
#define LOCALIZED_STRINGTABLE_FILEPRINT "Εκτυπώνει τον κώδικα" // 
#define LOCALIZED_STRINGTABLE_EDALLEXIT "Κλείνει τον επεξεργαστή κώδικα" // 

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING "{ Δε βρέθηκε το %s }" // 


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
#define LOCALIZED_COLOR_DARKORANGE            "Darkorange" // NOT_YET_LOCALIZED
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
