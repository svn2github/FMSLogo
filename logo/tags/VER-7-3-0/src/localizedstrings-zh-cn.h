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
//   "Impossible d'utiliser POUR (TO) dans une proc閐ure"
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
#define LOCALIZED_GENERAL_OKBUTTON      "确定"
#define LOCALIZED_GENERAL_CANCELBUTTON  "取消"
#define LOCALIZED_GENERAL_APPLYBUTTON   "应用(&A)"

#define LOCALIZED_GENERAL_PRODUCTNAME   "FMSLogo"

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  "FMSLogo开发环境"

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  "文件(&F)"
#define LOCALIZED_FILE_NEW              "新建(&N)\t(清除工作区)"
#define LOCALIZED_FILE_LOAD             "载入(&L)...\t(合并至当前工作区)"
#define LOCALIZED_FILE_OPEN             "打开(&O)...\t(替换当前工作区)" 
#define LOCALIZED_FILE_SAVE             "保存(&S)" 
#define LOCALIZED_FILE_SAVEAS           "另存为(&A)..."
#define LOCALIZED_FILE_SETASSCREENSAVER "设为屏保(&T)"
#define LOCALIZED_FILE_EDIT             "编辑(&E)..."
#define LOCALIZED_FILE_ERASE            "清除(&R)..."
#define LOCALIZED_FILE_EXIT             "退出(&X)"

#define LOCALIZED_BITMAP               "图片(&B)"
#define LOCALIZED_BITMAP_NEW           "新建(&N)"
#define LOCALIZED_BITMAP_LOAD          "载入(&L)..."
#define LOCALIZED_BITMAP_SAVE          "保存(&S)"
#define LOCALIZED_BITMAP_SAVEAS        "另存为(&A)..."
#define LOCALIZED_BITMAP_PRINT         "打印(&P)..."
#define LOCALIZED_BITMAP_PRINTERSETUP  "打印机设置(&R)..."
#define LOCALIZED_BITMAP_ACTIVEAREA    "活动区域(&C)..."

#define LOCALIZED_SET                  "设置(&S)"
#define LOCALIZED_SET_PENSIZE          "画笔大小(&Z)..."
#define LOCALIZED_SET_LABELFONT        "标注字体(&L)..."
#define LOCALIZED_SET_COMMANDERFONT    "命令窗口字体(&C)..."
#define LOCALIZED_SET_PENCOLOR         "画笔颜色(&P)..."
#define LOCALIZED_SET_FLOODCOLOR       "填充颜色(&L)..."
#define LOCALIZED_SET_SCREENCOLOR      "画布颜色(&S)..."

#define LOCALIZED_ZOOM                 "缩放(&Z)" 
#define LOCALIZED_ZOOM_IN              "放大(&I)"
#define LOCALIZED_ZOOM_OUT             "缩小(&O)"
#define LOCALIZED_ZOOM_NORMAL          "还原(&N)"

#define LOCALIZED_HELP                 "帮助(&H)" 
#define LOCALIZED_HELP_INDEX           "索引(&I)"
#define LOCALIZED_HELP_TUTORIAL        "教程(&T)"
#define LOCALIZED_HELP_DEMO            "演示(&D)" 
#define LOCALIZED_HELP_EXAMPLE         "示例(&E)"
#define LOCALIZED_HELP_RELEASENOTES    "发布说明(&R)"
#define LOCALIZED_HELP_ABOUTFMSLOGO    "关于" LOCALIZED_GENERAL_PRODUCTNAME "(&A)..."
#define LOCALIZED_HELP_MS              "关于FMS(&B)..."
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   "中文转英文"
#define LOCALIZED_HELP_ENGLISHTOLANG   "英文转中文"

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              "选择活动区域"
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       "这些设置影响图片的打印和保存"
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        "Y-高"
#define LOCALIZED_SELECTACTIVEAREA_YLOW         "Y-低"
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        "X-高"
#define LOCALIZED_SELECTACTIVEAREA_XLOW         "X-低"
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH "打印的海龟像素/英寸:"
#define LOCALIZED_SELECTACTIVEAREA_RESET        "重置(&R)"
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON

// The screensaver strings
#define LOCALIZED_SCREENSAVER_NAME              LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_SCREENSAVER_DESCRIPTION       "FMSLogo屏保"
#define LOCALIZED_SCREENSAVER_SETTINGS_TITLE    "FMSLogo屏保设置"
#define LOCALIZED_SCREENSAVER_LOCATE            "定位(&L)..." 
#define LOCALIZED_SCREENSAVER_FILE              "Logo文件(&F):" 
#define LOCALIZED_SCREENSAVER_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SCREENSAVER_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON

// The dialog box for selecting a Startup procedure
#define LOCALIZED_SELECTSTARTUP_CAPTION               "选择一个" LOCALIZED_ALTERNATE_STARTUP "指令"
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED "您的工作区没有定义" LOCALIZED_ALTERNATE_STARTUP "指令列表, 因此载入屏保时\n什么也不会发生.\n请在程序载入时选择一个过程."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST   LOCALIZED_ALTERNATE_STARTUP "变量不是列表, 因此载入屏保时\n什么也不会发生.\n请在程序载入时选择一个过程."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY     "您的工作区定义了一个空" LOCALIZED_ALTERNATE_STARTUP "指令列表, 因此载入屏保时\n什么也不会发生.\n请在程序载入时选择一个过程."
#define LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED   "过程未定义"

// The warning dialog box when the user saves an empty workspace
#define LOCALIZED_EMPTYWORKSPACE_TITLE                LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_EMPTYWORKSPACE_MESSAGE              "过程、变量、属性列表还没有定义,\n隐藏工作区将保存为空文件.\n\n您确定保存吗?"

//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     "复制(&C)"
#define LOCALIZED_POPUP_CUT                      "剪切(&X)"
#define LOCALIZED_POPUP_PASTE                    "粘贴(&P)"
#define LOCALIZED_POPUP_DELETE                   "删除(&D)"
#define LOCALIZED_POPUP_UNDO                     "撤销(&U)"
#define LOCALIZED_POPUP_REDO                     "恢复(&R)"
#define LOCALIZED_POPUP_SELECTALL                "全选(&A)"
#define LOCALIZED_POPUP_HELP                     "搜索主题(&T)"
#define LOCALIZED_POPUP_REMOVELINES              "清除已选线条(&L)"

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   "代码编辑器"

#define LOCALIZED_EDITOR_FILE                    "文件(&F)"
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        "保存后退出(&S)\tCtrl+D"
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    "保存到工作区(&W)"
#define LOCALIZED_EDITOR_FILE_PRINT              "打印(&P)..." 
#define LOCALIZED_EDITOR_FILE_EXIT               "退出(&X)" 

#define LOCALIZED_EDITOR_EDIT                    "编辑(&E)"
#define LOCALIZED_EDITOR_EDIT_UNDO               "撤销(&U)\tCtrl+Z"
#define LOCALIZED_EDITOR_EDIT_REDO               "恢复(&R)\tCtrl+Y"
#define LOCALIZED_EDITOR_EDIT_CUT                "剪切(&X)\tCtrl+X"
#define LOCALIZED_EDITOR_EDIT_COPY               "复制(&C)\tCtrl+C"
#define LOCALIZED_EDITOR_EDIT_PASTE              "粘贴(&P)\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_DELETE             "删除(&D)\tDel"
#define LOCALIZED_EDITOR_EDIT_CLEARALL           "全部清除(&L)\tCtrl+Del"
#define LOCALIZED_EDITOR_EDIT_SELECTALL          "全选(&A)\tCtrl+A"

#define LOCALIZED_EDITOR_SEARCH                  "搜索(&S)"
#define LOCALIZED_EDITOR_SEARCH_FIND             "查找(&F)...\tCtrl+F"
#define LOCALIZED_EDITOR_SEARCH_REPLACE          "替换(&R)...\tCtrl+H" 
#define LOCALIZED_EDITOR_SEARCH_NEXT             "下一个(&N)\tF3"

#define LOCALIZED_EDITOR_SET                     "设置(&T)"
#define LOCALIZED_EDITOR_SET_FONT                "字体(&F)..." 

#define LOCALIZED_EDITOR_TEST                    "测试"
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      "运行(&R)\tCtrl+R"

#define LOCALIZED_EDITOR_HELP                    "帮助(&H)"
#define LOCALIZED_EDITOR_HELP_INDEX              "索引(&I)"
#define LOCALIZED_EDITOR_HELP_EDITOR             "代码编辑器(&E)"
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        "主题搜索(&T)\tF1"


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    "保存后退出(&S)"
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       "不保存(&D)"
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       "工作区已改变.  如果现在退出, 所做操作将丢失."
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       "退出前保存您的操作吗？"


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     "命令窗口"
#define LOCALIZED_COMMANDER_HALT                "终止"
#define LOCALIZED_COMMANDER_TRACE               "跟踪"
#define LOCALIZED_COMMANDER_NOTRACE             "不跟踪"
#define LOCALIZED_COMMANDER_PAUSE               "暂停"
#define LOCALIZED_COMMANDER_STATUS              "显示状态"
#define LOCALIZED_COMMANDER_NOSTATUS            "隐藏状态"
#define LOCALIZED_COMMANDER_STEP                "单步"
#define LOCALIZED_COMMANDER_UNSTEP              "停止单步"
#define LOCALIZED_COMMANDER_RESET               "重置"
#define LOCALIZED_COMMANDER_EXECUTE             "执行"
#define LOCALIZED_COMMANDER_EDALL               "代码编辑器"

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        "状态窗口"
#define LOCALIZED_STATUS_PEN                    "画笔"
#define LOCALIZED_STATUS_CONTACT                "触点:"
#define LOCALIZED_STATUS_WIDTH                  "宽度:"
#define LOCALIZED_STATUS_STYLE                  "风格:"
#define LOCALIZED_STATUS_ORIENTATION            "方向"
#define LOCALIZED_STATUS_PITCH                  "最高点:"
#define LOCALIZED_STATUS_HEADING                "角度:"
#define LOCALIZED_STATUS_ROLL                   "滚动:"
#define LOCALIZED_STATUS_TURTLE                 "海龟"
#define LOCALIZED_STATUS_POSITION               "位置(XYZ):"
#define LOCALIZED_STATUS_WHICH                  "位置:"
#define LOCALIZED_STATUS_VISIBILITY             "可见性:"
#define LOCALIZED_STATUS_COLOR                  "颜色"
#define LOCALIZED_STATUS_PENCOLOR               "画笔(RGB):"
#define LOCALIZED_STATUS_FLOODCOLOR             "填充(RGB):"
#define LOCALIZED_STATUS_SCREENCOLOR            "画布(RGB):"
#define LOCALIZED_STATUS_KERNEL                 "内核"
#define LOCALIZED_STATUS_CALLS                  "调用次数:"
#define LOCALIZED_STATUS_PEAKMEMORY             "内存峰值:"

#define LOCALIZED_STATUS_PENREVERSE     "反向"
#define LOCALIZED_STATUS_PENNORMAL      "正常"
#define LOCALIZED_STATUS_PENERASE       "擦除"
#define LOCALIZED_STATUS_PENUP          "向上"
#define LOCALIZED_STATUS_PENDOWN        "向下"
#define LOCALIZED_STATUS_PENSHOWN       "显示"
#define LOCALIZED_STATUS_PENHIDDEN      "隐藏"
#define LOCALIZED_STATUS_POLYGONS       "多边形"
#define LOCALIZED_STATUS_VECTORS        "立体"
#define LOCALIZED_STATUS_NODES          "节点"
#define LOCALIZED_STATUS_NOT_APPLICABLE "不适用/适用"

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           "所有(&A)"
#define LOCALIZED_ERASEPROCEDURE                "清除过程"
#define LOCALIZED_EDITPROCEDURE                 "编辑过程"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     "颜色设置"
#define LOCALIZED_SETCOLOR_PENCOLOR            "画笔颜色"
#define LOCALIZED_SETCOLOR_FLOODCOLOR          "填充颜色"
#define LOCALIZED_SETCOLOR_SCREENCOLOR         "画布颜色"
#define LOCALIZED_SETCOLOR_RED                 "红色"
#define LOCALIZED_SETCOLOR_GREEN               "绿色"
#define LOCALIZED_SETCOLOR_BLUE                "蓝色"
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   "画笔大小"
#define LOCALIZED_SETPENSIZE_SIZE              "大小"
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     "关于" LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_ABOUTFMS_VERSION             "版本"
#define LOCALIZED_ABOUTFMS_GUI                 "界面编写:  George Mills\nSoftronics, Inc.\nhttp://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_CORE                "内核编写: Brian Harvey\n加利福利亚大学，伯克利分校"
#define LOCALIZED_ABOUTFMS_INSTALLER           "安装包采用Nullsoft Scriptable Install System制作\nhttp://nsis.sourceforge.net/"
#define LOCALIZED_ABOUTFMS_ADVENTURE           "《The Great Logo Adventure》(ISBN 0-9651934-6-2)\n作者: Jim Muller\n请访问http://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       "特别鸣谢Yehuda Katz和Neuwirth"
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME "是自由软件\n参见GNU Public License"
#define LOCALIZED_ABOUTFMS_NEWSGROUP           "网络新闻组: comp.lang.logo\nLogo论坛\nhttp://groups.yahoo.com/group/LogoForum/"
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     "如需学习计算机原理,\n请与Softronics, Inc.联系索取MultiMedia Logic"
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      "关于FMS"
#define LOCALIZED_ABOUTMS_FMS                  "FMS是Fight Multiple Sclerosis的缩写"
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     "请捐助\nNational Multiple Sclerosis Society.\nhttp://www.nmss.org\n1-800-FIGHT-MS"
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

#define LOCALIZED_CHANGESINEDITORMAYBELOST  "所有操作将丢失，\n\n您确定退出吗？ " LOCALIZED_GENERAL_PRODUCTNAME "?"
#define LOCALIZED_EDITSESSIONISRUNNING      "编辑对话正在运行"

#define LOCALIZED_COULDNOTWRITEBMP            "图片保存失败"
#define LOCALIZED_COULDNOTOPENBMP             "图片打开失败"
#define LOCALIZED_COULDNOTCREATEBMP           "不能创建Windows 3.0位图"
#define LOCALIZED_NOTVALIDBMP                 "不是Windows 3.0位图"

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         "还未保存"
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     "如果新建将清空所有定义.\n\n确定新建吗?"
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE "载入的文件将合并当前工作区\n并覆盖您的修改.\n\n继续载入吗?"
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    "未保存的操作将丢失.\n\n确定打开吗?"

#define LOCALIZED_EDITORISOPEN                  "您正在执行一个编辑.\n\n所做操作还未保存."

#define LOCALIZED_ERROR_CANTREADFILE            "不能读取文件\"%s\""
#define LOCALIZED_ERROR_CANTWRITEFILE           "不能写文件\"%s\""

#define LOCALIZED_SAVETOWORKSPACE                "保存到工作区"
#define LOCALIZED_CONTENTSCHANGED                "内容已更改"
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE "内容已更改, \n您要保存更改吗?"



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  "保存出错, \n\n请查看命令窗口的错误提示。"
#define LOCALIZED_RETURNTOEDIT                  "返回编辑器?"

#define LOCALIZED_EDITFAILEDTOLOAD              LOCALIZED_SAVETOWORKSPACE

#define LOCALIZED_ERRORINFILETITLE              "文件有错误"
#define LOCALIZED_ERRORINFILEMESSAGE            "载入文件时出错 \"%s\".\n\n请查看命令窗口的错误提示.\n\n您要在编辑器打开文件查看错误吗？"

#define LOCALIZED_CANNOTALLOCATESCREEN          "分配画布窗口内存失败.  可能您申请的尺寸超过了可用内存.\n\n" LOCALIZED_GENERAL_PRODUCTNAME


// 
//  Strings used in the File-Open filters
//
#define LOCALIZED_FILE_LOAD_DIALOG_TITLE    "载入Logo程序(合并至当前工作区)"
#define LOCALIZED_FILE_OPEN_DIALOG_TITLE    "打开Logo程序(替换当前工作区)"
#define LOCALIZED_FILE_SAVE_DIALOG_TITLE    "选择工作区文件"
#define LOCALIZED_BITMAP_OPEN_DIALOG_TITLE  "载入图片"
#define LOCALIZED_BITMAP_SAVE_DIALOG_TITLE  "选择当前区域保存文件"

#define LOCALIZED_LOGO_FILE_EXTENSION "lgo"
#define LOCALIZED_FILEFILTER_ALLFILES "所有文件(*.*)|*.*"
#define LOCALIZED_FILEFILTER_LOGO     "Logo文件(*.lgo)|*.lgo|" LOCALIZED_FILEFILTER_ALLFILES
#define LOCALIZED_FILEFILTER_IMAGE    "图片文件(*.bmp)|*.bmp|GIF文件(*.gif)|*.gif|" LOCALIZED_FILEFILTER_ALLFILES



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
#define LOCALIZED_STEPPING                  "单步"

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  "%s已定义\n"


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    "擦除"
#define LOCALIZED_PENMODE_REVERSE  "反向"
#define LOCALIZED_PENMODE_PAINT    "画图"

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          "Logo: 致命内部错误"
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       "Logo: 内存不足"
#define LOCALIZED_ERROR_OUTOFMEMORY            "内存不足"
#define LOCALIZED_ERROR_STACKOVERFLOW          "堆栈溢出"
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      "海龟超出范围"
#define LOCALIZED_ERROR_BADGRAPHINIT           "图形初始化失败"
#define LOCALIZED_ERROR_BADDATA                "%p 不喜欢 %s 作为输入"
#define LOCALIZED_ERROR_DIDNTOUTPUT            "%p 未输出至%p"
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        "输入不足: %p"
#define LOCALIZED_ERROR_TOOMUCH                "太多内部()'s"
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    "您没有指定如何处理%s"
#define LOCALIZED_ERROR_PARENMISMATCH          "太多('s"
#define LOCALIZED_ERROR_NOVALUE                "%s未赋值"
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        "意外的')'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      "意外的']'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        "意外的'}'"
#define LOCALIZED_ERROR_DONTKNOWHOWTO          "我不知道如何%p"
#define LOCALIZED_ERROR_NOCATCHTAG             "不能发现%p的捕获标记"
#define LOCALIZED_ERROR_ALREADYDEFINED         "%p已定义"
#define LOCALIZED_ERROR_STOPPING               "正在停止..."
#define LOCALIZED_ERROR_ALREADYDRIBBLING       "已泄漏"
#define LOCALIZED_ERROR_FILESYSTEM                   "文件系统错误: %p"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          "打开文件失败"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         "不能打开文件: %t"
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       "文件已打开"
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           "文件未打开"
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  "创建编辑器文件失败"
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   "加载编辑器失败" 
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    "读取编辑器文件失败" 
#define LOCALIZED_ERROR_IFWARNING              "假定你使用的是IFELSE, 不是IF"
#define LOCALIZED_ERROR_SHADOWWARNING          "%p过程中内部变量屏蔽"
#define LOCALIZED_ERROR_USER                   "抛出 \"错误"
#define LOCALIZED_ERROR_ISPRIMITIVE            "%p是原语"
#define LOCALIZED_ERROR_TONOTINSIDE            "过程内部不能使用TO"
#define LOCALIZED_ERROR_ATTOPLEVEL             "%p只能在过程内部使用"
#define LOCALIZED_ERROR_ATTOPLEVEL2            "OUTPUT和STOP只能在过程内使用"
#define LOCALIZED_ERROR_NOTEST                 "%p未测试"
#define LOCALIZED_ERROR_BADMACROOUTPUT         "宏输出%s代替列表"
#define LOCALIZED_ERROR_DEEPEND                "多行指令中含有END"
#define LOCALIZED_ERROR_DEEPENDIN              "多行指令%p中含有END"
#define LOCALIZED_ERROR_UNKNOWN                "未知错误条件-内部错误."
#define LOCALIZED_PAUSING                      "暂停..."


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION "%p指令的状态无效"
#define LOCALIZED_ERROR_MODE_ON_SPRITE             "当乌龟带有旋转的图片时，不能设置其模式"
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        "不能用旋转图片制作乌龟图片"
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            "不能用剪贴板作为旋转图片"
#define LOCALIZED_ERROR_SPECIALFORM                "%p不能用%p作为输入, 因其有特殊格式"

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      "错误"
#define LOCALIZED_ERROR_BADINPUT             "无效输入"
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    "输入不配对"

#define LOCALIZED_ERROR_CANTOPENPORT         "打开端口失败"
#define LOCALIZED_ERROR_CANTCLOSEPORT        "关闭端口失败"
#define LOCALIZED_ERROR_CANTFLUSHPORT        "刷新端口失败"
#define LOCALIZED_ERROR_CANTDCBONPORT        "在端口建立dcb失败"
#define LOCALIZED_ERROR_CANTSETPORT          "设置端口失败"
#define LOCALIZED_ERROR_PORTALREADYOPEN      "端口已打开"
#define LOCALIZED_ERROR_PORTNOTOPEN          "端口未打开"

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   "%s已存在"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    "%s不存在"

#define LOCALIZED_ERROR_DLLNOTLOADED          "DLL还未装入"
#define LOCALIZED_ERROR_DLLLOADFAILED         "DLL装入失败"
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    "输入的数据类型无效"
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  "输出的类型无效"
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   "函数未发现"
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  "有的类型/数据未配对"

#define LOCALIZED_ERROR_NETWORK               "网络错误"
#define LOCALIZED_ERROR_NETWORKRECEIVE        "网络接收错误"
#define LOCALIZED_ERROR_NETWORKSEND           "网络发生错误"
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       "未知错误, 网络可能已关闭"
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     "还未开始"
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED "已开始"
#define LOCALIZED_ERROR_NETWORKALREADYON      "已打开"
#define LOCALIZED_ERROR_NETWORKALREADYOFF     "已关闭"

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

#define LOCALIZED_ERROR_POLYSTART               "多边形起始错误"
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED "已开始多边形绘制"

#define LOCALIZED_ERROR_POLYEND                 "多边形结束错误"
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       "还没有开始绘制多边形"
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     "定义一个多边形至少要三条线段"

#define LOCALIZED_ERROR_SOUND                 "声音错误"

#define LOCALIZED_ERROR_MIDI                  "MIDI错误"
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     "无效的MIDI设备"
#define LOCALIZED_ERROR_MIDIALREADYOPEN       "已打开"
#define LOCALIZED_ERROR_MIDINOTOPEN           "未打开"

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      "剪贴板没有文本"

#define LOCALIZED_ERROR_MCI                   "MCI错误"

#define LOCALIZED_ERROR_TIMERNOTFOUND         "未发现定时器"

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       "在线帮助无效, hhctrl.ocx加载失败"

#define LOCALIZED_ERROR_BADCOMMANDLINE        "命令行无效" 

#define LOCALIZED_ERROR_TMPNOTDEFINED         "环境变量TMP未定义或无效.\n" LOCALIZED_GENERAL_PRODUCTNAME " 尝试保存临时文件到C:\\"

#define LOCALIZED_ERROR_GIFSAVEFAILED         "生成GIF失败, 请检查内存和硬盘"
#define LOCALIZED_ERROR_GIFREADFAILED         "读取GIF失败, 请检查内存和硬盘"

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  "图片索引超出范围"
#define LOCALIZED_ERROR_BITMAPCUTFAILED        "剪切失败, 可能内存不足"

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    "剪贴板空" 
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  "索引中的图片必须用位图初始化" 

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      "海龟%d没有图片, 将终止"

#define LOCALIZED_ERROR_FONTNOTFOUND            "字体名%s未发现.  请选择:\n"

#define LOCALIZED_ERROR_PRINTERCANTSCALE        "打印机驱动不支持该功能" 
#define LOCALIZED_ERROR_CANTDRAWIMAGE           "画图失败"
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        "抽取图像失败"
#define LOCALIZED_ERROR_SUBCODE                 "子过程"

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         "输入:"
#define LOCALIZED_PROMPT_TO     "To模式(Cancel to End)"
#define LOCALIZED_PROMPT_LIST   "列表模式(Cancel to Halt)"
#define LOCALIZED_PROMPT_PAUSE  "暂停模式(Cancel to Continue)"
#define LOCALIZED_PROMPT_INPUT  "输入模式(Cancel to Halt)"

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      "切换至\"%s\""
#define LOCALIZED_FILE_CHDIRFAILED         "chdir\"%s\"失败"
#define LOCALIZED_FILE_POPPEDTO            "弹出\"%s\""
#define LOCALIZED_FILE_MKDIRSUCCEEDED      "位于新建文件夹\"%s\"" 
#define LOCALIZED_FILE_MKDIRFAILED         "创建文件夹失败\"%s\"" 
#define LOCALIZED_FILE_RMDIRSUCCEEDED      "文件夹已删除\"%s\"" 
#define LOCALIZED_FILE_RMDIRFAILED         "删除文件夹失败\"%s\"" 
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  "文件夹不存在."
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY "请文件夹为空"


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       "Logo Picture" // NOT_YET_LOCALIZED

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    "活动区域"
#define LOCALIZED_INFORMATION   "提示"
#define LOCALIZED_WARNING       "警告"
#define LOCALIZED_UNTITLED      "无标题"
#define LOCALIZED_UNKNOWN       "未知"

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       "空"

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     "查找"
#define LOCALIZED_EDITOR_TITLE_REPLACE  "替换" 

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING "%s未找到"


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
#define LOCALIZED_WINDOWCLASSNAME_WINDOW       "窗体"
#define LOCALIZED_WINDOWCLASSNAME_STATIC       "文本框"
#define LOCALIZED_WINDOWCLASSNAME_LISTBOX      "列表框"
#define LOCALIZED_WINDOWCLASSNAME_COMBOBOX     "组合框"
#define LOCALIZED_WINDOWCLASSNAME_BUTTON       "按钮"
#define LOCALIZED_WINDOWCLASSNAME_SCROLLBAR    "滚动条"
#define LOCALIZED_WINDOWCLASSNAME_GROUPBOX     "分组框"
#define LOCALIZED_WINDOWCLASSNAME_RADIOBUTTON  "单选按钮"
#define LOCALIZED_WINDOWCLASSNAME_CHECKBOX     "复选框"
#define LOCALIZED_WINDOWCLASSNAME_DIALOG       "对话框"


//
// The name of the default font face name.
// This should only be translated if the given font face doesn't include glyphs
// for characters in your language.  The specified font face name must be part
// of all Windows versions from Windows XP onward that would support your
// language.
//
#define LOCALIZED_DEFAULT_FONT_FACE "宋体"
