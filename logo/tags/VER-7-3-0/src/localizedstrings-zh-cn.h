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
// This file contains localized strings for Chinese by Pachleng
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
#define LOCALIZED_ALTERNATE_TRUE     "true" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FALSE    "false" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_END      "end" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TOPLEVEL "toplevel" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SYSTEM   "system" // NOT_YET_LOCALIZED

//
// Localized "alternate" names of Logo special variables
//
#define LOCALIZED_ALTERNATE_CASEIGNOREDP    "caseignoredp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ERRACT          "erract" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STARTUP         "startup" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_REDEFP          "redefp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PRINTWIDTHLIMIT "printwidthlimit" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PRINTDEPTHLIMIT "printdepthlimit" // NOT_YET_LOCALIZED


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
#define LOCALIZED_ALTERNATE_ARITY                  "arity" // NOT_YET_LOCALIZED
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
#define LOCALIZED_ALTERNATE_HASOWNPENP             "hasownpenp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HASOWNPEN_             "hasownpen?" // NOT_YET_LOCALIZED
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
#define LOCALIZED_ALTERNATE_MAKE                   "Make" // NOT_YET_LOCALIZED
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
#define LOCALIZED_ALTERNATE_PLIST                  "Plist" // NOT_YET_LOCALIZED
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
#define LOCALIZED_ALTERNATE_PPROP                  "Pprop" // NOT_YET_LOCALIZED
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
#define LOCALIZED_ALTERNATE_READRAWLINE            "readrawline" // NOT_YET_LOCALIZED
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
#define LOCALIZED_GENERAL_OKBUTTON      "ȷ��"
#define LOCALIZED_GENERAL_CANCELBUTTON  "ȡ��"
#define LOCALIZED_GENERAL_APPLYBUTTON   "Ӧ��(&A)"

#define LOCALIZED_GENERAL_PRODUCTNAME   "FMSLogo"

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  "FMSLogo��������"

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  "�ļ�(&F)"
#define LOCALIZED_FILE_NEW              "�½�(&N)\t(���������)"
#define LOCALIZED_FILE_LOAD             "����(&L)...\t(�ϲ�����ǰ������)"
#define LOCALIZED_FILE_OPEN             "��(&O)...\t(�滻��ǰ������)" 
#define LOCALIZED_FILE_SAVE             "����(&S)" 
#define LOCALIZED_FILE_SAVEAS           "���Ϊ(&A)..."
#define LOCALIZED_FILE_SETASSCREENSAVER "��Ϊ����(&T)"
#define LOCALIZED_FILE_EDIT             "�༭(&E)..."
#define LOCALIZED_FILE_ERASE            "���(&R)..."
#define LOCALIZED_FILE_EXIT             "�˳�(&X)"

#define LOCALIZED_BITMAP               "ͼƬ(&B)"
#define LOCALIZED_BITMAP_NEW           "�½�(&N)"
#define LOCALIZED_BITMAP_LOAD          "����(&L)..."
#define LOCALIZED_BITMAP_SAVE          "����(&S)"
#define LOCALIZED_BITMAP_SAVEAS        "���Ϊ(&A)..."
#define LOCALIZED_BITMAP_PRINT         "��ӡ(&P)..."
#define LOCALIZED_BITMAP_PRINTERSETUP  "��ӡ������(&R)..."
#define LOCALIZED_BITMAP_ACTIVEAREA    "�����(&C)..."

#define LOCALIZED_SET                  "����(&S)"
#define LOCALIZED_SET_PENSIZE          "���ʴ�С(&Z)..."
#define LOCALIZED_SET_LABELFONT        "��ע����(&L)..."
#define LOCALIZED_SET_COMMANDERFONT    "���������(&C)..."
#define LOCALIZED_SET_PENCOLOR         "������ɫ(&P)..."
#define LOCALIZED_SET_FLOODCOLOR       "�����ɫ(&L)..."
#define LOCALIZED_SET_SCREENCOLOR      "������ɫ(&S)..."

#define LOCALIZED_ZOOM                 "����(&Z)" 
#define LOCALIZED_ZOOM_IN              "�Ŵ�(&I)"
#define LOCALIZED_ZOOM_OUT             "��С(&O)"
#define LOCALIZED_ZOOM_NORMAL          "��ԭ(&N)"

#define LOCALIZED_HELP                 "����(&H)" 
#define LOCALIZED_HELP_INDEX           "����(&I)"
#define LOCALIZED_HELP_TUTORIAL        "�̳�(&T)"
#define LOCALIZED_HELP_DEMO            "��ʾ(&D)" 
#define LOCALIZED_HELP_EXAMPLE         "ʾ��(&E)"
#define LOCALIZED_HELP_RELEASENOTES    "����˵��(&R)"
#define LOCALIZED_HELP_ABOUTFMSLOGO    "����" LOCALIZED_GENERAL_PRODUCTNAME "(&A)..."
#define LOCALIZED_HELP_MS              "����FMS(&B)..."
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   "����תӢ��"
#define LOCALIZED_HELP_ENGLISHTOLANG   "Ӣ��ת����"

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              "ѡ������"
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       "��Щ����Ӱ��ͼƬ�Ĵ�ӡ�ͱ���"
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        "Y-��"
#define LOCALIZED_SELECTACTIVEAREA_YLOW         "Y-��"
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        "X-��"
#define LOCALIZED_SELECTACTIVEAREA_XLOW         "X-��"
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH "��ӡ�ĺ�������/Ӣ��:"
#define LOCALIZED_SELECTACTIVEAREA_RESET        "����(&R)"
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON

// The screensaver strings
#define LOCALIZED_SCREENSAVER_NAME              LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_SCREENSAVER_DESCRIPTION       "FMSLogo����"
#define LOCALIZED_SCREENSAVER_SETTINGS_TITLE    "FMSLogo��������"
#define LOCALIZED_SCREENSAVER_LOCATE            "��λ(&L)..." 
#define LOCALIZED_SCREENSAVER_FILE              "Logo�ļ�(&F):" 
#define LOCALIZED_SCREENSAVER_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SCREENSAVER_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON

// The dialog box for selecting a Startup procedure
#define LOCALIZED_SELECTSTARTUP_CAPTION               "ѡ��һ��" LOCALIZED_ALTERNATE_STARTUP "ָ��"
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED "���Ĺ�����û�ж���" LOCALIZED_ALTERNATE_STARTUP "ָ���б�, �����������ʱ\nʲôҲ���ᷢ��.\n���ڳ�������ʱѡ��һ������."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST   LOCALIZED_ALTERNATE_STARTUP "���������б�, �����������ʱ\nʲôҲ���ᷢ��.\n���ڳ�������ʱѡ��һ������."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY     "���Ĺ�����������һ����" LOCALIZED_ALTERNATE_STARTUP "ָ���б�, �����������ʱ\nʲôҲ���ᷢ��.\n���ڳ�������ʱѡ��һ������."
#define LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED   "����δ����"

// The warning dialog box when the user saves an empty workspace
#define LOCALIZED_EMPTYWORKSPACE_TITLE                LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_EMPTYWORKSPACE_MESSAGE              "���̡������������б�û�ж���,\n���ع�����������Ϊ���ļ�.\n\n��ȷ��������?"

//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     "����(&C)"
#define LOCALIZED_POPUP_CUT                      "����(&X)"
#define LOCALIZED_POPUP_PASTE                    "ճ��(&P)"
#define LOCALIZED_POPUP_DELETE                   "ɾ��(&D)"
#define LOCALIZED_POPUP_UNDO                     "����(&U)"
#define LOCALIZED_POPUP_REDO                     "�ָ�(&R)"
#define LOCALIZED_POPUP_SELECTALL                "ȫѡ(&A)"
#define LOCALIZED_POPUP_HELP                     "��������(&T)"
#define LOCALIZED_POPUP_REMOVELINES              "�����ѡ����(&L)"

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   "����༭��"

#define LOCALIZED_EDITOR_FILE                    "�ļ�(&F)"
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        "������˳�(&S)\tCtrl+D"
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    "���浽������(&W)"
#define LOCALIZED_EDITOR_FILE_PRINT              "��ӡ(&P)..." 
#define LOCALIZED_EDITOR_FILE_EXIT               "�˳�(&X)" 

#define LOCALIZED_EDITOR_EDIT                    "�༭(&E)"
#define LOCALIZED_EDITOR_EDIT_UNDO               "����(&U)\tCtrl+Z"
#define LOCALIZED_EDITOR_EDIT_REDO               "�ָ�(&R)\tCtrl+Y"
#define LOCALIZED_EDITOR_EDIT_CUT                "����(&X)\tCtrl+X"
#define LOCALIZED_EDITOR_EDIT_COPY               "����(&C)\tCtrl+C"
#define LOCALIZED_EDITOR_EDIT_PASTE              "ճ��(&P)\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_DELETE             "ɾ��(&D)\tDel"
#define LOCALIZED_EDITOR_EDIT_CLEARALL           "ȫ�����(&L)\tCtrl+Del"
#define LOCALIZED_EDITOR_EDIT_SELECTALL          "ȫѡ(&A)\tCtrl+A"

#define LOCALIZED_EDITOR_SEARCH                  "����(&S)"
#define LOCALIZED_EDITOR_SEARCH_FIND             "����(&F)...\tCtrl+F"
#define LOCALIZED_EDITOR_SEARCH_REPLACE          "�滻(&R)...\tCtrl+H" 
#define LOCALIZED_EDITOR_SEARCH_NEXT             "��һ��(&N)\tF3"

#define LOCALIZED_EDITOR_SET                     "����(&T)"
#define LOCALIZED_EDITOR_SET_FONT                "����(&F)..." 

#define LOCALIZED_EDITOR_TEST                    "����"
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      "����(&R)\tCtrl+R"

#define LOCALIZED_EDITOR_HELP                    "����(&H)"
#define LOCALIZED_EDITOR_HELP_INDEX              "����(&I)"
#define LOCALIZED_EDITOR_HELP_EDITOR             "����༭��(&E)"
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        "��������(&T)\tF1"


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    "������˳�(&S)"
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       "������(&D)"
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       "�������Ѹı�.  ��������˳�, ������������ʧ."
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       "�˳�ǰ�������Ĳ�����"


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     "�����"
#define LOCALIZED_COMMANDER_HALT                "��ֹ"
#define LOCALIZED_COMMANDER_TRACE               "����"
#define LOCALIZED_COMMANDER_NOTRACE             "������"
#define LOCALIZED_COMMANDER_PAUSE               "��ͣ"
#define LOCALIZED_COMMANDER_STATUS              "��ʾ״̬"
#define LOCALIZED_COMMANDER_NOSTATUS            "����״̬"
#define LOCALIZED_COMMANDER_STEP                "����"
#define LOCALIZED_COMMANDER_UNSTEP              "ֹͣ����"
#define LOCALIZED_COMMANDER_RESET               "����"
#define LOCALIZED_COMMANDER_EXECUTE             "ִ��"
#define LOCALIZED_COMMANDER_EDALL               "����༭��"

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        "״̬����"
#define LOCALIZED_STATUS_PEN                    "����"
#define LOCALIZED_STATUS_CONTACT                "����:"
#define LOCALIZED_STATUS_WIDTH                  "���:"
#define LOCALIZED_STATUS_STYLE                  "���:"
#define LOCALIZED_STATUS_ORIENTATION            "����"
#define LOCALIZED_STATUS_PITCH                  "��ߵ�:"
#define LOCALIZED_STATUS_HEADING                "�Ƕ�:"
#define LOCALIZED_STATUS_ROLL                   "����:"
#define LOCALIZED_STATUS_TURTLE                 "����"
#define LOCALIZED_STATUS_POSITION               "λ��(XYZ):"
#define LOCALIZED_STATUS_WHICH                  "λ��:"
#define LOCALIZED_STATUS_VISIBILITY             "�ɼ���:"
#define LOCALIZED_STATUS_COLOR                  "��ɫ"
#define LOCALIZED_STATUS_PENCOLOR               "����(RGB):"
#define LOCALIZED_STATUS_FLOODCOLOR             "���(RGB):"
#define LOCALIZED_STATUS_SCREENCOLOR            "����(RGB):"
#define LOCALIZED_STATUS_KERNEL                 "�ں�"
#define LOCALIZED_STATUS_CALLS                  "���ô���:"
#define LOCALIZED_STATUS_PEAKMEMORY             "�ڴ��ֵ:"

#define LOCALIZED_STATUS_PENREVERSE     "����"
#define LOCALIZED_STATUS_PENNORMAL      "����"
#define LOCALIZED_STATUS_PENERASE       "����"
#define LOCALIZED_STATUS_PENUP          "����"
#define LOCALIZED_STATUS_PENDOWN        "����"
#define LOCALIZED_STATUS_PENSHOWN       "��ʾ"
#define LOCALIZED_STATUS_PENHIDDEN      "����"
#define LOCALIZED_STATUS_POLYGONS       "�����"
#define LOCALIZED_STATUS_VECTORS        "����"
#define LOCALIZED_STATUS_NODES          "�ڵ�"
#define LOCALIZED_STATUS_NOT_APPLICABLE "������/����"

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           "����(&A)"
#define LOCALIZED_ERASEPROCEDURE                "�������"
#define LOCALIZED_EDITPROCEDURE                 "�༭����"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     "��ɫ����"
#define LOCALIZED_SETCOLOR_PENCOLOR            "������ɫ"
#define LOCALIZED_SETCOLOR_FLOODCOLOR          "�����ɫ"
#define LOCALIZED_SETCOLOR_SCREENCOLOR         "������ɫ"
#define LOCALIZED_SETCOLOR_RED                 "��ɫ"
#define LOCALIZED_SETCOLOR_GREEN               "��ɫ"
#define LOCALIZED_SETCOLOR_BLUE                "��ɫ"
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   "���ʴ�С"
#define LOCALIZED_SETPENSIZE_SIZE              "��С"
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     "����" LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_ABOUTFMS_VERSION             "�汾"
#define LOCALIZED_ABOUTFMS_GUI                 "�����д:  George Mills\nSoftronics, Inc.\nhttp://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_CORE                "�ں˱�д: Brian Harvey\n���������Ǵ�ѧ����������У"
#define LOCALIZED_ABOUTFMS_INSTALLER           "��װ������Nullsoft Scriptable Install System����\nhttp://nsis.sourceforge.net/"
#define LOCALIZED_ABOUTFMS_ADVENTURE           "��The Great Logo Adventure��(ISBN 0-9651934-6-2)\n����: Jim Muller\n�����http://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       "�ر���лYehuda Katz��Neuwirth"
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME "���������\n�μ�GNU Public License"
#define LOCALIZED_ABOUTFMS_NEWSGROUP           "����������: comp.lang.logo\nLogo��̳\nhttp://groups.yahoo.com/group/LogoForum/"
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     "����ѧϰ�����ԭ��,\n����Softronics, Inc.��ϵ��ȡMultiMedia Logic"
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      "����FMS"
#define LOCALIZED_ABOUTMS_FMS                  "FMS��Fight Multiple Sclerosis����д"
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     "�����\nNational Multiple Sclerosis Society.\nhttp://www.nmss.org\n1-800-FIGHT-MS"
#define LOCALIZED_ABOUTMS_OK                   LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the SELECTBOX Dialog box
//
#define LOCALIZED_SELECTBOX_OK                 LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTBOX_CANCEL             LOCALIZED_GENERAL_CANCELBUTTON

//
// Strings on the QUESTIONBOX dialog box
//
#define LOCALIZED_QUESTIONBOX_OK               LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_QUESTIONBOX_CANCEL           LOCALIZED_GENERAL_CANCELBUTTON


// 
// Strings in various other dialog boxes
// 

#define LOCALIZED_CHANGESINEDITORMAYBELOST  "���в�������ʧ��\n\n��ȷ���˳��� " LOCALIZED_GENERAL_PRODUCTNAME "?"
#define LOCALIZED_EDITSESSIONISRUNNING      "�༭�Ի���������"

#define LOCALIZED_COULDNOTWRITEBMP            "ͼƬ����ʧ��"
#define LOCALIZED_COULDNOTOPENBMP             "ͼƬ��ʧ��"
#define LOCALIZED_COULDNOTCREATEBMP           "���ܴ���Windows 3.0λͼ"
#define LOCALIZED_NOTVALIDBMP                 "����Windows 3.0λͼ"

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         "��δ����"
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     "����½���������ж���.\n\nȷ���½���?"
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE "������ļ����ϲ���ǰ������\n�����������޸�.\n\n����������?"
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    "δ����Ĳ�������ʧ.\n\nȷ������?"

#define LOCALIZED_EDITORISOPEN                  "������ִ��һ���༭.\n\n����������δ����."

#define LOCALIZED_ERROR_CANTREADFILE            "���ܶ�ȡ�ļ�\"%s\""
#define LOCALIZED_ERROR_CANTWRITEFILE           "����д�ļ�\"%s\""

#define LOCALIZED_SAVETOWORKSPACE                "���浽������"
#define LOCALIZED_CONTENTSCHANGED                "�����Ѹ���"
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE "�����Ѹ���, \n��Ҫ���������?"



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  "�������, \n\n��鿴����ڵĴ�����ʾ��"
#define LOCALIZED_RETURNTOEDIT                  "���ر༭��?"

#define LOCALIZED_EDITFAILEDTOLOAD              LOCALIZED_SAVETOWORKSPACE

#define LOCALIZED_ERRORINFILETITLE              "�ļ��д���"
#define LOCALIZED_ERRORINFILEMESSAGE            "�����ļ�ʱ���� \"%s\".\n\n��鿴����ڵĴ�����ʾ.\n\n��Ҫ�ڱ༭�����ļ��鿴������"

#define LOCALIZED_CANNOTALLOCATESCREEN          "���仭�������ڴ�ʧ��.  ����������ĳߴ糬���˿����ڴ�.\n\n" LOCALIZED_GENERAL_PRODUCTNAME


// 
//  Strings used in the File-Open filters
//
#define LOCALIZED_FILE_LOAD_DIALOG_TITLE    "����Logo����(�ϲ�����ǰ������)"
#define LOCALIZED_FILE_OPEN_DIALOG_TITLE    "��Logo����(�滻��ǰ������)"
#define LOCALIZED_FILE_SAVE_DIALOG_TITLE    "ѡ�������ļ�"
#define LOCALIZED_BITMAP_OPEN_DIALOG_TITLE  "����ͼƬ"
#define LOCALIZED_BITMAP_SAVE_DIALOG_TITLE  "ѡ��ǰ���򱣴��ļ�"

#define LOCALIZED_LOGO_FILE_EXTENSION "lgo"
#define LOCALIZED_FILEFILTER_ALLFILES "�����ļ�(*.*)|*.*"
#define LOCALIZED_FILEFILTER_LOGO     "Logo�ļ�(*.lgo)|*.lgo|" LOCALIZED_FILEFILTER_ALLFILES
#define LOCALIZED_FILEFILTER_IMAGE    "ͼƬ�ļ�(*.bmp)|*.bmp|GIF�ļ�(*.gif)|*.gif|" LOCALIZED_FILEFILTER_ALLFILES



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
#define LOCALIZED_STEPPING                  "����"

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  "%s�Ѷ���\n"


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    "����"
#define LOCALIZED_PENMODE_REVERSE  "����"
#define LOCALIZED_PENMODE_PAINT    "��ͼ"

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          "Logo: �����ڲ�����"
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       "Logo: �ڴ治��"
#define LOCALIZED_ERROR_OUTOFMEMORY            "�ڴ治��"
#define LOCALIZED_ERROR_STACKOVERFLOW          "��ջ���"
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      "���곬����Χ"
#define LOCALIZED_ERROR_BADGRAPHINIT           "ͼ�γ�ʼ��ʧ��"
#define LOCALIZED_ERROR_BADDATA                "%p ��ϲ�� %s ��Ϊ����"
#define LOCALIZED_ERROR_DIDNTOUTPUT            "%p δ�����%p"
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        "���벻��: %p"
#define LOCALIZED_ERROR_TOOMUCH                "̫���ڲ�()'s"
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    "��û��ָ����δ���%s"
#define LOCALIZED_ERROR_PARENMISMATCH          "̫��('s"
#define LOCALIZED_ERROR_NOVALUE                "%sδ��ֵ"
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        "�����')'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      "�����']'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        "�����'}'"
#define LOCALIZED_ERROR_DONTKNOWHOWTO          "�Ҳ�֪�����%p"
#define LOCALIZED_ERROR_NOCATCHTAG             "���ܷ���%p�Ĳ�����"
#define LOCALIZED_ERROR_ALREADYDEFINED         "%p�Ѷ���"
#define LOCALIZED_ERROR_STOPPING               "����ֹͣ..."
#define LOCALIZED_ERROR_ALREADYDRIBBLING       "��й©"
#define LOCALIZED_ERROR_FILESYSTEM                   "�ļ�ϵͳ����: %p"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          "���ļ�ʧ��"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         "���ܴ��ļ�: %t"
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       "�ļ��Ѵ�"
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           "�ļ�δ��"
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  "�����༭���ļ�ʧ��"
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   "���ر༭��ʧ��" 
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    "��ȡ�༭���ļ�ʧ��" 
#define LOCALIZED_ERROR_IFWARNING              "�ٶ���ʹ�õ���IFELSE, ����IF"
#define LOCALIZED_ERROR_SHADOWWARNING          "%p�������ڲ���������"
#define LOCALIZED_ERROR_USER                   "�׳� \"����"
#define LOCALIZED_ERROR_ISPRIMITIVE            "%p��ԭ��"
#define LOCALIZED_ERROR_TONOTINSIDE            "�����ڲ�����ʹ��TO"
#define LOCALIZED_ERROR_ATTOPLEVEL             "%pֻ���ڹ����ڲ�ʹ��"
#define LOCALIZED_ERROR_ATTOPLEVEL2            "OUTPUT��STOPֻ���ڹ�����ʹ��"
#define LOCALIZED_ERROR_NOTEST                 "%pδ����"
#define LOCALIZED_ERROR_BADMACROOUTPUT         "�����%s�����б�"
#define LOCALIZED_ERROR_DEEPEND                "����ָ���к���END"
#define LOCALIZED_ERROR_DEEPENDIN              "����ָ��%p�к���END"
#define LOCALIZED_ERROR_UNKNOWN                "δ֪��������-�ڲ�����."
#define LOCALIZED_PAUSING                      "��ͣ..."


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION "%pָ���״̬��Ч"
#define LOCALIZED_ERROR_MODE_ON_SPRITE             "���ڹ������ת��ͼƬʱ������������ģʽ"
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        "��������תͼƬ�����ڹ�ͼƬ"
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            "�����ü�������Ϊ��תͼƬ"
#define LOCALIZED_ERROR_SPECIALFORM                "%p������%p��Ϊ����, �����������ʽ"

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      "����"
#define LOCALIZED_ERROR_BADINPUT             "��Ч����"
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    "���벻���"

#define LOCALIZED_ERROR_CANTOPENPORT         "�򿪶˿�ʧ��"
#define LOCALIZED_ERROR_CANTCLOSEPORT        "�رն˿�ʧ��"
#define LOCALIZED_ERROR_CANTFLUSHPORT        "ˢ�¶˿�ʧ��"
#define LOCALIZED_ERROR_CANTDCBONPORT        "�ڶ˿ڽ���dcbʧ��"
#define LOCALIZED_ERROR_CANTSETPORT          "���ö˿�ʧ��"
#define LOCALIZED_ERROR_PORTALREADYOPEN      "�˿��Ѵ�"
#define LOCALIZED_ERROR_PORTNOTOPEN          "�˿�δ��"

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   "%s�Ѵ���"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    "%s������"

#define LOCALIZED_ERROR_DLLNOTLOADED          "DLL��δװ��"
#define LOCALIZED_ERROR_DLLLOADFAILED         "DLLװ��ʧ��"
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    "���������������Ч"
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  "�����������Ч"
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   "����δ����"
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  "�е�����/����δ���"

#define LOCALIZED_ERROR_NETWORK               "�������"
#define LOCALIZED_ERROR_NETWORKRECEIVE        "������մ���"
#define LOCALIZED_ERROR_NETWORKSEND           "���緢������"
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       "δ֪����, ��������ѹر�"
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     "��δ��ʼ"
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED "�ѿ�ʼ"
#define LOCALIZED_ERROR_NETWORKALREADYON      "�Ѵ�"
#define LOCALIZED_ERROR_NETWORKALREADYOFF     "�ѹر�"

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

#define LOCALIZED_ERROR_POLYSTART               "�������ʼ����"
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED "�ѿ�ʼ����λ���"

#define LOCALIZED_ERROR_POLYEND                 "����ν�������"
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       "��û�п�ʼ���ƶ����"
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     "����һ�����������Ҫ�����߶�"

#define LOCALIZED_ERROR_SOUND                 "��������"

#define LOCALIZED_ERROR_MIDI                  "MIDI����"
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     "��Ч��MIDI�豸"
#define LOCALIZED_ERROR_MIDIALREADYOPEN       "�Ѵ�"
#define LOCALIZED_ERROR_MIDINOTOPEN           "δ��"

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      "������û���ı�"

#define LOCALIZED_ERROR_MCI                   "MCI����"

#define LOCALIZED_ERROR_TIMERNOTFOUND         "δ���ֶ�ʱ��"

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       "���߰�����Ч, hhctrl.ocx����ʧ��"

#define LOCALIZED_ERROR_BADCOMMANDLINE        "��������Ч" 

#define LOCALIZED_ERROR_TMPNOTDEFINED         "��������TMPδ�������Ч.\n" LOCALIZED_GENERAL_PRODUCTNAME " ���Ա�����ʱ�ļ���C:\\"

#define LOCALIZED_ERROR_GIFSAVEFAILED         "����GIFʧ��, �����ڴ��Ӳ��"
#define LOCALIZED_ERROR_GIFREADFAILED         "��ȡGIFʧ��, �����ڴ��Ӳ��"

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  "ͼƬ����������Χ"
#define LOCALIZED_ERROR_BITMAPCUTFAILED        "����ʧ��, �����ڴ治��"

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    "�������" 
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  "�����е�ͼƬ������λͼ��ʼ��" 

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      "����%dû��ͼƬ, ����ֹ"

#define LOCALIZED_ERROR_FONTNOTFOUND            "������%sδ����.  ��ѡ��:\n"

#define LOCALIZED_ERROR_PRINTERCANTSCALE        "��ӡ��������֧�ָù���" 
#define LOCALIZED_ERROR_CANTDRAWIMAGE           "��ͼʧ��"
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        "��ȡͼ��ʧ��"
#define LOCALIZED_ERROR_SUBCODE                 "�ӹ���"

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         "����:"
#define LOCALIZED_PROMPT_TO     "Toģʽ(Cancel to End)"
#define LOCALIZED_PROMPT_LIST   "�б�ģʽ(Cancel to Halt)"
#define LOCALIZED_PROMPT_PAUSE  "��ͣģʽ(Cancel to Continue)"
#define LOCALIZED_PROMPT_INPUT  "����ģʽ(Cancel to Halt)"

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      "�л���\"%s\""
#define LOCALIZED_FILE_CHDIRFAILED         "chdir\"%s\"ʧ��"
#define LOCALIZED_FILE_POPPEDTO            "����\"%s\""
#define LOCALIZED_FILE_MKDIRSUCCEEDED      "λ���½��ļ���\"%s\"" 
#define LOCALIZED_FILE_MKDIRFAILED         "�����ļ���ʧ��\"%s\"" 
#define LOCALIZED_FILE_RMDIRSUCCEEDED      "�ļ�����ɾ��\"%s\"" 
#define LOCALIZED_FILE_RMDIRFAILED         "ɾ���ļ���ʧ��\"%s\"" 
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  "�ļ��в�����."
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY "���ļ���Ϊ��"


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       "Logo Picture" // NOT_YET_LOCALIZED

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    "�����"
#define LOCALIZED_INFORMATION   "��ʾ"
#define LOCALIZED_WARNING       "����"
#define LOCALIZED_UNTITLED      "�ޱ���"
#define LOCALIZED_UNKNOWN       "δ֪"

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       "��"

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     "����"
#define LOCALIZED_EDITOR_TITLE_REPLACE  "�滻" 

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING "%sδ�ҵ�"


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
#define LOCALIZED_WINDOWCLASSNAME_WINDOW       "����"
#define LOCALIZED_WINDOWCLASSNAME_STATIC       "�ı���"
#define LOCALIZED_WINDOWCLASSNAME_LISTBOX      "�б��"
#define LOCALIZED_WINDOWCLASSNAME_COMBOBOX     "��Ͽ�"
#define LOCALIZED_WINDOWCLASSNAME_BUTTON       "��ť"
#define LOCALIZED_WINDOWCLASSNAME_SCROLLBAR    "������"
#define LOCALIZED_WINDOWCLASSNAME_GROUPBOX     "�����"
#define LOCALIZED_WINDOWCLASSNAME_RADIOBUTTON  "��ѡ��ť"
#define LOCALIZED_WINDOWCLASSNAME_CHECKBOX     "��ѡ��"
#define LOCALIZED_WINDOWCLASSNAME_DIALOG       "�Ի���"


//
// The name of the default font face name.
// This should only be translated if the given font face doesn't include glyphs
// for characters in your language.  The specified font face name must be part
// of all Windows versions from Windows XP onward that would support your
// language.
//
#define LOCALIZED_DEFAULT_FONT_FACE "����"
