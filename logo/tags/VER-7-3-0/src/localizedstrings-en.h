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
// This file contains localized strings for English
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
//   "Impossible d'utiliser POUR (TO) dans une procédure"
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
#define LOCALIZED_ALTERNATE_TRUE     "true"
#define LOCALIZED_ALTERNATE_FALSE    "false"
#define LOCALIZED_ALTERNATE_END      "end"
#define LOCALIZED_ALTERNATE_TOPLEVEL "toplevel"
#define LOCALIZED_ALTERNATE_SYSTEM   "system"

//
// Localized "alternate" names of Logo special variables
//
#define LOCALIZED_ALTERNATE_CASEIGNOREDP    "caseignoredp"
#define LOCALIZED_ALTERNATE_ERRACT          "erract"
#define LOCALIZED_ALTERNATE_STARTUP         "startup"
#define LOCALIZED_ALTERNATE_REDEFP          "redefp"
#define LOCALIZED_ALTERNATE_PRINTWIDTHLIMIT "printwidthlimit"
#define LOCALIZED_ALTERNATE_PRINTDEPTHLIMIT "printdepthlimit"


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
#define LOCALIZED_ALTERNATE__DEFMACRO              ".defmacro"
#define LOCALIZED_ALTERNATE__EQ                    ".eq"
#define LOCALIZED_ALTERNATE__MACRO                 ".macro"
#define LOCALIZED_ALTERNATE__MAYBEOUTPUT           ".maybeoutput"
#define LOCALIZED_ALTERNATE__SETBF                 ".setbf"
#define LOCALIZED_ALTERNATE__SETFIRST              ".setfirst"
#define LOCALIZED_ALTERNATE__SETITEM               ".setitem"
#define LOCALIZED_ALTERNATE_ACTIVEAREA             "activearea"
#define LOCALIZED_ALTERNATE_ALLOPEN                "allopen"
#define LOCALIZED_ALTERNATE_AND                    "and"
#define LOCALIZED_ALTERNATE_APPLY                  "apply"
#define LOCALIZED_ALTERNATE_ARCCOS                 "arccos"
#define LOCALIZED_ALTERNATE_ARCSIN                 "arcsin"
#define LOCALIZED_ALTERNATE_ARCTAN                 "arctan"
#define LOCALIZED_ALTERNATE_ARITY                  "arity"
#define LOCALIZED_ALTERNATE_ARRAY                  "array"
#define LOCALIZED_ALTERNATE_ARRAYP                 "arrayp"
#define LOCALIZED_ALTERNATE_ARRAY_                 "array?"
#define LOCALIZED_ALTERNATE_ASCII                  "ascii"
#define LOCALIZED_ALTERNATE_ASHIFT                 "ashift"
#define LOCALIZED_ALTERNATE_BACK                   "back"
#define LOCALIZED_ALTERNATE_BACKSLASHEDP           "backslashedp"
#define LOCALIZED_ALTERNATE_BACKSLASHED_           "backslashed?"
#define LOCALIZED_ALTERNATE_BEFOREP                "beforep"
#define LOCALIZED_ALTERNATE_BEFORE_                "before?"
#define LOCALIZED_ALTERNATE_BF                     "bf"
#define LOCALIZED_ALTERNATE_BFS                    "bfs"
#define LOCALIZED_ALTERNATE_BITAND                 "bitand"
#define LOCALIZED_ALTERNATE_BITBLOCK               "bitblock"
#define LOCALIZED_ALTERNATE_BITCOPY                "bitcopy"
#define LOCALIZED_ALTERNATE_BITCUT                 "bitcut"
#define LOCALIZED_ALTERNATE_BITFIT                 "bitfit"
#define LOCALIZED_ALTERNATE_BITINDEX               "bitindex"
#define LOCALIZED_ALTERNATE_BITLOAD                "bitload"
#define LOCALIZED_ALTERNATE_BITLOADSIZE            "bitloadsize"
#define LOCALIZED_ALTERNATE_BITSIZE                "bitsize"
#define LOCALIZED_ALTERNATE_BITMAPTURTLE           "bitmapturtle"
#define LOCALIZED_ALTERNATE_BITMODE                "bitmode"
#define LOCALIZED_ALTERNATE_BITNOT                 "bitnot"
#define LOCALIZED_ALTERNATE_BITOR                  "bitor"
#define LOCALIZED_ALTERNATE_BITPASTE               "bitpaste"
#define LOCALIZED_ALTERNATE_BITPASTETOINDEX        "bitpastetoindex"
#define LOCALIZED_ALTERNATE_BITSAVE                "bitsave"
#define LOCALIZED_ALTERNATE_BITXOR                 "bitxor"
#define LOCALIZED_ALTERNATE_BK                     "bk"
#define LOCALIZED_ALTERNATE_BL                     "bl"
#define LOCALIZED_ALTERNATE_BURIED                 "buried"
#define LOCALIZED_ALTERNATE_BURY                   "bury"
#define LOCALIZED_ALTERNATE_BUTFIRST               "butfirst"
#define LOCALIZED_ALTERNATE_BUTFIRSTS              "butfirsts"
#define LOCALIZED_ALTERNATE_BUTLAST                "butlast"
#define LOCALIZED_ALTERNATE_BUTTONCREATE           "buttoncreate"
#define LOCALIZED_ALTERNATE_BUTTONDELETE           "buttondelete"
#define LOCALIZED_ALTERNATE_BUTTONENABLE           "buttonenable"
#define LOCALIZED_ALTERNATE_BUTTONUPDATE           "buttonupdate"
#define LOCALIZED_ALTERNATE_BUTTONP                "buttonp"
#define LOCALIZED_ALTERNATE_BUTTON_                "button?"
#define LOCALIZED_ALTERNATE_BYE                    "bye"
#define LOCALIZED_ALTERNATE_CATCH                  "catch"
#define LOCALIZED_ALTERNATE_CHAR                   "char"
#define LOCALIZED_ALTERNATE_CHDIR                  "chdir"
#define LOCALIZED_ALTERNATE_CHECKBOXCREATE         "checkboxcreate"
#define LOCALIZED_ALTERNATE_CHECKBOXDELETE         "checkboxdelete"
#define LOCALIZED_ALTERNATE_CHECKBOXENABLE         "checkboxenable"
#define LOCALIZED_ALTERNATE_CHECKBOXGET            "checkboxget"
#define LOCALIZED_ALTERNATE_CHECKBOXSET            "checkboxset"
#define LOCALIZED_ALTERNATE_CLEAN                  "clean"
#define LOCALIZED_ALTERNATE_CLEARPALETTE           "clearpalette"
#define LOCALIZED_ALTERNATE_CLEARSCREEN            "clearscreen"
#define LOCALIZED_ALTERNATE_CLEARTEXT              "cleartext"
#define LOCALIZED_ALTERNATE_CLEARTIMER             "cleartimer"
#define LOCALIZED_ALTERNATE_CLOSE                  "close"
#define LOCALIZED_ALTERNATE_CLOSEALL               "closeall"
#define LOCALIZED_ALTERNATE_CO                     "co"
#define LOCALIZED_ALTERNATE_COMBOBOXADDSTRING      "comboboxaddstring"
#define LOCALIZED_ALTERNATE_COMBOBOXCREATE         "comboboxcreate"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETE         "comboboxdelete"
#define LOCALIZED_ALTERNATE_COMBOBOXENABLE         "comboboxenable"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING   "comboboxdeletestring"
#define LOCALIZED_ALTERNATE_COMBOBOXGETTEXT        "comboboxgettext"
#define LOCALIZED_ALTERNATE_COMBOBOXSETTEXT        "comboboxsettext"
#define LOCALIZED_ALTERNATE_CONTENTS               "contents"
#define LOCALIZED_ALTERNATE_CONTINUE               "continue"
#define LOCALIZED_ALTERNATE_COPYDEF                "copydef"
#define LOCALIZED_ALTERNATE_COS                    "cos"
#define LOCALIZED_ALTERNATE_COUNT                  "count"
#define LOCALIZED_ALTERNATE_CS                     "cs"
#define LOCALIZED_ALTERNATE_CT                     "ct"
#define LOCALIZED_ALTERNATE_CURSOR                 "cursor"
#define LOCALIZED_ALTERNATE_DEBUGWINDOWS           "debugwindows"
#define LOCALIZED_ALTERNATE_DEFINE                 "define"
#define LOCALIZED_ALTERNATE_DEFINEDP               "definedp"
#define LOCALIZED_ALTERNATE_DEFINED_               "defined?"
#define LOCALIZED_ALTERNATE_DIALOGCREATE           "dialogcreate"
#define LOCALIZED_ALTERNATE_DIALOGENABLE           "dialogenable"
#define LOCALIZED_ALTERNATE_DIALOGDELETE           "dialogdelete"
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         "dialogfileopen"
#define LOCALIZED_ALTERNATE_DIALOGFILESAVE         "dialogfilesave"
#define LOCALIZED_ALTERNATE_DIFFERENCE             "difference"
#define LOCALIZED_ALTERNATE_DIRECTORIES            "directories"
#define LOCALIZED_ALTERNATE_DLLCALL                "dllcall"
#define LOCALIZED_ALTERNATE_DLLFREE                "dllfree"
#define LOCALIZED_ALTERNATE_DLLLOAD                "dllload"
#define LOCALIZED_ALTERNATE_DOWN                   "down"
#define LOCALIZED_ALTERNATE_DOWNPITCH              "downpitch"
#define LOCALIZED_ALTERNATE_DRIBBLE                "dribble"
#define LOCALIZED_ALTERNATE_ED                     "ed"
#define LOCALIZED_ALTERNATE_EDIT                   "edit"
#define LOCALIZED_ALTERNATE_ELLIPSEARC             "ellipsearc"
#define LOCALIZED_ALTERNATE_EMPTYP                 "emptyp"
#define LOCALIZED_ALTERNATE_EMPTY_                 "empty?"
#define LOCALIZED_ALTERNATE_EOFP                   "eofp"
#define LOCALIZED_ALTERNATE_EOF_                   "eof?"
#define LOCALIZED_ALTERNATE_EQUALP                 "equalp"
#define LOCALIZED_ALTERNATE_EQUAL_                 "equal?"
#define LOCALIZED_ALTERNATE_ER                     "er"
#define LOCALIZED_ALTERNATE_ERASE                  "erase"
#define LOCALIZED_ALTERNATE_ERASEFILE              "erasefile"
#define LOCALIZED_ALTERNATE_ERF                    "erf"
#define LOCALIZED_ALTERNATE_ERROR                  "error"
#define LOCALIZED_ALTERNATE_EVENTCHECK             "eventcheck"
#define LOCALIZED_ALTERNATE_EXP                    "exp"
#define LOCALIZED_ALTERNATE_FD                     "fd"
#define LOCALIZED_ALTERNATE_FENCE                  "fence"
#define LOCALIZED_ALTERNATE_FILL                   "fill"
#define LOCALIZED_ALTERNATE_FILES                  "files"
#define LOCALIZED_ALTERNATE_FIRST                  "first"
#define LOCALIZED_ALTERNATE_FIRSTS                 "firsts"
#define LOCALIZED_ALTERNATE_FLOODCOLOR             "floodcolor"
#define LOCALIZED_ALTERNATE_FONTFACENAMES          "fontfacenames"
#define LOCALIZED_ALTERNATE_FOREVER                "forever"
#define LOCALIZED_ALTERNATE_FORM                   "form"
#define LOCALIZED_ALTERNATE_FORWARD                "forward"
#define LOCALIZED_ALTERNATE_FPUT                   "fput"
#define LOCALIZED_ALTERNATE_FS                     "fs"
#define LOCALIZED_ALTERNATE_FULLSCREEN             "fullscreen"
#define LOCALIZED_ALTERNATE_FULLTEXT               "fulltext"
#define LOCALIZED_ALTERNATE_GETFOCUS               "getfocus"
#define LOCALIZED_ALTERNATE_GOTO                   "goto"
#define LOCALIZED_ALTERNATE_GIFLOAD                "gifload"
#define LOCALIZED_ALTERNATE_GIFSIZE                "gifsize"
#define LOCALIZED_ALTERNATE_GIFSAVE                "gifsave"
#define LOCALIZED_ALTERNATE_GPROP                  "gprop"
#define LOCALIZED_ALTERNATE_GREATEREQUALP          "greaterequalp"
#define LOCALIZED_ALTERNATE_GREATEREQUAL_          "greaterequal?"
#define LOCALIZED_ALTERNATE_GREATERP               "greaterp"
#define LOCALIZED_ALTERNATE_GREATER_               "greater?"
#define LOCALIZED_ALTERNATE_GROUPBOXCREATE         "groupboxcreate"
#define LOCALIZED_ALTERNATE_GROUPBOXDELETE         "groupboxdelete"
#define LOCALIZED_ALTERNATE_HALT                   "halt"
#define LOCALIZED_ALTERNATE_HASOWNPENP             "hasownpenp"
#define LOCALIZED_ALTERNATE_HASOWNPEN_             "hasownpen?"
#define LOCALIZED_ALTERNATE_HEADING                "heading"
#define LOCALIZED_ALTERNATE_HELP                   "help"
#define LOCALIZED_ALTERNATE_HIDETURTLE             "hideturtle"
#define LOCALIZED_ALTERNATE_HOME                   "home"
#define LOCALIZED_ALTERNATE_HT                     "ht"
#define LOCALIZED_ALTERNATE_IF                     "if"
#define LOCALIZED_ALTERNATE_IFELSE                 "ifelse"
#define LOCALIZED_ALTERNATE_IFF                    "iff"
#define LOCALIZED_ALTERNATE_IFFALSE                "iffalse"
#define LOCALIZED_ALTERNATE_IFT                    "ift"
#define LOCALIZED_ALTERNATE_IFTRUE                 "iftrue"
#define LOCALIZED_ALTERNATE_INGAMEPORT             "ingameport"
#define LOCALIZED_ALTERNATE_INPORT                 "inport"
#define LOCALIZED_ALTERNATE_INPORTB                "inportb"
#define LOCALIZED_ALTERNATE_INT                    "int"
#define LOCALIZED_ALTERNATE_ITEM                   "item"
#define LOCALIZED_ALTERNATE_KEYBOARDOFF            "keyboardoff"
#define LOCALIZED_ALTERNATE_KEYBOARDON             "keyboardon"
#define LOCALIZED_ALTERNATE_KEYBOARDVALUE          "keyboardvalue"
#define LOCALIZED_ALTERNATE_KEYP                   "keyp"
#define LOCALIZED_ALTERNATE_KEY_                   "key?"
#define LOCALIZED_ALTERNATE_LABEL                  "label"
#define LOCALIZED_ALTERNATE_LABELFONT              "labelfont"
#define LOCALIZED_ALTERNATE_LABELSIZE              "labelsize"
#define LOCALIZED_ALTERNATE_LAST                   "last"
#define LOCALIZED_ALTERNATE_LEFT                   "left"
#define LOCALIZED_ALTERNATE_LEFTROLL               "leftroll"
#define LOCALIZED_ALTERNATE_LESSEQUALP             "lessequalp"
#define LOCALIZED_ALTERNATE_LESSEQUAL_             "lessequal?"
#define LOCALIZED_ALTERNATE_LESSP                  "lessp"
#define LOCALIZED_ALTERNATE_LESS_                  "less?"
#define LOCALIZED_ALTERNATE_LIGHT                  "light"
#define LOCALIZED_ALTERNATE_LIST                   "list"
#define LOCALIZED_ALTERNATE_LISTBOXADDSTRING       "listboxaddstring"
#define LOCALIZED_ALTERNATE_LISTBOXCREATE          "listboxcreate"
#define LOCALIZED_ALTERNATE_LISTBOXENABLE          "listboxenable"
#define LOCALIZED_ALTERNATE_LISTBOXDELETE          "listboxdelete"
#define LOCALIZED_ALTERNATE_LISTBOXDELETESTRING    "listboxdeletestring"
#define LOCALIZED_ALTERNATE_LISTBOXGETSELECT       "listboxgetselect"
#define LOCALIZED_ALTERNATE_LISTP                  "listp"
#define LOCALIZED_ALTERNATE_LIST_                  "list?"
#define LOCALIZED_ALTERNATE_LN                     "ln"
#define LOCALIZED_ALTERNATE_LOAD                   "load"
#define LOCALIZED_ALTERNATE_LOCAL                  "local"
#define LOCALIZED_ALTERNATE_LOG10                  "log10"
#define LOCALIZED_ALTERNATE_LOGOVERSION            "logoversion"
#define LOCALIZED_ALTERNATE_LOWERCASE              "lowercase"
#define LOCALIZED_ALTERNATE_LPUT                   "lput"
#define LOCALIZED_ALTERNATE_LR                     "lr"
#define LOCALIZED_ALTERNATE_LSHIFT                 "lshift"
#define LOCALIZED_ALTERNATE_LT                     "lt"
#define LOCALIZED_ALTERNATE_MACHINE                "machine"
#define LOCALIZED_ALTERNATE_MACROP                 "macrop"
#define LOCALIZED_ALTERNATE_MACRO_                 "macro?"
#define LOCALIZED_ALTERNATE_MAKE                   "Make"
#define LOCALIZED_ALTERNATE_MCI                    "mci"
#define LOCALIZED_ALTERNATE_MEMBER                 "member"
#define LOCALIZED_ALTERNATE_MEMBERP                "memberp"
#define LOCALIZED_ALTERNATE_MEMBER_                "member?"
#define LOCALIZED_ALTERNATE_MESSAGEBOX             "messagebox"
#define LOCALIZED_ALTERNATE_MIDICLOSE              "midiclose"
#define LOCALIZED_ALTERNATE_MIDIMESSAGE            "midimessage"
#define LOCALIZED_ALTERNATE_MIDIOPEN               "midiopen"
#define LOCALIZED_ALTERNATE_MINUS                  "minus"
#define LOCALIZED_ALTERNATE_MKDIR                  "mkdir"
#define LOCALIZED_ALTERNATE_MODULO                 "modulo"
#define LOCALIZED_ALTERNATE_MOUSEOFF               "mouseoff"
#define LOCALIZED_ALTERNATE_MOUSEON                "mouseon"
#define LOCALIZED_ALTERNATE_MOUSEPOS               "mousepos"
#define LOCALIZED_ALTERNATE_NAMEP                  "namep"
#define LOCALIZED_ALTERNATE_NAME_                  "name?"
#define LOCALIZED_ALTERNATE_NAMES                  "names"
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           "netacceptoff"
#define LOCALIZED_ALTERNATE_NETACCEPTON            "netaccepton"
#define LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE  "netacceptreceivevalue"
#define LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE     "netacceptsendvalue"
#define LOCALIZED_ALTERNATE_NETCONNECTOFF          "netconnectoff"
#define LOCALIZED_ALTERNATE_NETCONNECTON           "netconnecton"
#define LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE "netconnectreceivevalue"
#define LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE    "netconnectsendvalue"
#define LOCALIZED_ALTERNATE_NETSHUTDOWN            "netshutdown"
#define LOCALIZED_ALTERNATE_NETSTARTUP             "netstartup"
#define LOCALIZED_ALTERNATE_NOBITMAPTURTLE         "nobitmapturtle"
#define LOCALIZED_ALTERNATE_NODES                  "nodes"
#define LOCALIZED_ALTERNATE_NODRIBBLE              "nodribble"
#define LOCALIZED_ALTERNATE_NOSTATUS               "nostatus"
#define LOCALIZED_ALTERNATE_NOT                    "not"
#define LOCALIZED_ALTERNATE_NOTEQUALP              "notequalp"
#define LOCALIZED_ALTERNATE_NOTEQUAL_              "notequal?"
#define LOCALIZED_ALTERNATE_NOYIELD                "noyield"
#define LOCALIZED_ALTERNATE_NUMBERP                "numberp"
#define LOCALIZED_ALTERNATE_NUMBER_                "number?"
#define LOCALIZED_ALTERNATE_OP                     "op"
#define LOCALIZED_ALTERNATE_OPENAPPEND             "openappend"
#define LOCALIZED_ALTERNATE_OPENREAD               "openread"
#define LOCALIZED_ALTERNATE_OPENUPDATE             "openupdate"
#define LOCALIZED_ALTERNATE_OPENWRITE              "openwrite"
#define LOCALIZED_ALTERNATE_OR                     "or"
#define LOCALIZED_ALTERNATE_OUTPORT                "outport"
#define LOCALIZED_ALTERNATE_OUTPORTB               "outportb"
#define LOCALIZED_ALTERNATE_OUTPUT                 "output"
#define LOCALIZED_ALTERNATE_PARSE                  "parse"
#define LOCALIZED_ALTERNATE_PAUSE                  "pause"
#define LOCALIZED_ALTERNATE_PC                     "pc"
#define LOCALIZED_ALTERNATE_PD                     "pd"
#define LOCALIZED_ALTERNATE_PE                     "pe"
#define LOCALIZED_ALTERNATE_PENCOLOR               "pencolor"
#define LOCALIZED_ALTERNATE_PENDOWN                "pendown"
#define LOCALIZED_ALTERNATE_PENDOWNP               "pendownp"
#define LOCALIZED_ALTERNATE_PENDOWN_               "pendown?"
#define LOCALIZED_ALTERNATE_PENERASE               "penerase"
#define LOCALIZED_ALTERNATE_PENMODE                "penmode"
#define LOCALIZED_ALTERNATE_PENPAINT               "penpaint"
#define LOCALIZED_ALTERNATE_PENPATTERN             "penpattern"
#define LOCALIZED_ALTERNATE_PENREVERSE             "penreverse"
#define LOCALIZED_ALTERNATE_PENSIZE                "pensize"
#define LOCALIZED_ALTERNATE_PENUP                  "penup"
#define LOCALIZED_ALTERNATE_PERSPECTIVE            "perspective"
#define LOCALIZED_ALTERNATE_PITCH                  "pitch"
#define LOCALIZED_ALTERNATE_PIXEL                  "pixel"
#define LOCALIZED_ALTERNATE_PLAYWAVE               "playwave"
#define LOCALIZED_ALTERNATE_PLIST                  "Plist"
#define LOCALIZED_ALTERNATE_PLISTS                 "plists"
#define LOCALIZED_ALTERNATE_PO                     "po"
#define LOCALIZED_ALTERNATE_POPDIR                 "popdir"
#define LOCALIZED_ALTERNATE_POLYSTART              "polystart"
#define LOCALIZED_ALTERNATE_POLYEND                "polyend"
#define LOCALIZED_ALTERNATE_POLYVIEW               "polyview"
#define LOCALIZED_ALTERNATE_PORTCLOSE              "portclose"
#define LOCALIZED_ALTERNATE_PORTFLUSH              "portflush"
#define LOCALIZED_ALTERNATE_PORTMODE               "portmode"
#define LOCALIZED_ALTERNATE_PORTOPEN               "portopen"
#define LOCALIZED_ALTERNATE_PORTREADARRAY          "portreadarray"
#define LOCALIZED_ALTERNATE_PORTREADCHAR           "portreadchar"
#define LOCALIZED_ALTERNATE_PORTWRITEARRAY         "portwritearray"
#define LOCALIZED_ALTERNATE_PORTWRITECHAR          "portwritechar"
#define LOCALIZED_ALTERNATE_POS                    "pos"
#define LOCALIZED_ALTERNATE_POSXYZ                 "posxyz"
#define LOCALIZED_ALTERNATE_POT                    "pot"
#define LOCALIZED_ALTERNATE_POWER                  "power"
#define LOCALIZED_ALTERNATE_PPROP                  "Pprop"
#define LOCALIZED_ALTERNATE_PPT                    "ppt"
#define LOCALIZED_ALTERNATE_PR                     "pr"
#define LOCALIZED_ALTERNATE_PRIMITIVEP             "primitivep"
#define LOCALIZED_ALTERNATE_PRIMITIVE_             "primitive?"
#define LOCALIZED_ALTERNATE_PRINT                  "print"
#define LOCALIZED_ALTERNATE_PROCEDUREP             "procedurep"
#define LOCALIZED_ALTERNATE_PROCEDURE_             "procedure?"
#define LOCALIZED_ALTERNATE_PROPLISTP              "proplistp"
#define LOCALIZED_ALTERNATE_PROPLIST_              "proplist?"
#define LOCALIZED_ALTERNATE_PROCEDURES             "procedures"
#define LOCALIZED_ALTERNATE_PRODUCT                "product"
#define LOCALIZED_ALTERNATE_PU                     "pu"
#define LOCALIZED_ALTERNATE_PX                     "px"
#define LOCALIZED_ALTERNATE_QUESTIONBOX            "questionbox"
#define LOCALIZED_ALTERNATE_QUOTIENT               "quotient"
#define LOCALIZED_ALTERNATE_RADARCCOS              "radarccos"
#define LOCALIZED_ALTERNATE_RADARCSIN              "radarcsin"
#define LOCALIZED_ALTERNATE_RADARCTAN              "radarctan"
#define LOCALIZED_ALTERNATE_RADCOS                 "radcos"
#define LOCALIZED_ALTERNATE_RADIOBUTTONCREATE      "radiobuttoncreate"
#define LOCALIZED_ALTERNATE_RADIOBUTTONENABLE      "radiobuttonenable"
#define LOCALIZED_ALTERNATE_RADIOBUTTONDELETE      "radiobuttondelete"
#define LOCALIZED_ALTERNATE_RADIOBUTTONGET         "radiobuttonget"
#define LOCALIZED_ALTERNATE_RADIOBUTTONSET         "radiobuttonset"
#define LOCALIZED_ALTERNATE_RADSIN                 "radsin"
#define LOCALIZED_ALTERNATE_RADTAN                 "radtan"
#define LOCALIZED_ALTERNATE_RANDOM                 "random"
#define LOCALIZED_ALTERNATE_RAWASCII               "rawascii"
#define LOCALIZED_ALTERNATE_RC                     "rc"
#define LOCALIZED_ALTERNATE_RCS                    "rcs"
#define LOCALIZED_ALTERNATE_READCHAR               "readchar"
#define LOCALIZED_ALTERNATE_READCHARS              "readchars"
#define LOCALIZED_ALTERNATE_READER                 "reader"
#define LOCALIZED_ALTERNATE_READLIST               "readlist"
#define LOCALIZED_ALTERNATE_READPOS                "readpos"
#define LOCALIZED_ALTERNATE_READRAWLINE            "readrawline"
#define LOCALIZED_ALTERNATE_READWORD               "readword"
#define LOCALIZED_ALTERNATE_REMAINDER              "remainder"
#define LOCALIZED_ALTERNATE_REMPROP                "remprop"
#define LOCALIZED_ALTERNATE_REPCOUNT               "repcount"
#define LOCALIZED_ALTERNATE_REPEAT                 "repeat"
#define LOCALIZED_ALTERNATE_RERANDOM               "rerandom"
#define LOCALIZED_ALTERNATE_RIGHT                  "right"
#define LOCALIZED_ALTERNATE_RIGHTROLL              "rightroll"
#define LOCALIZED_ALTERNATE_RL                     "rl"
#define LOCALIZED_ALTERNATE_RMDIR                  "rmdir"
#define LOCALIZED_ALTERNATE_ROLL                   "roll"
#define LOCALIZED_ALTERNATE_ROUND                  "round"
#define LOCALIZED_ALTERNATE_RR                     "rr"
#define LOCALIZED_ALTERNATE_RT                     "rt"
#define LOCALIZED_ALTERNATE_RUN                    "run"
#define LOCALIZED_ALTERNATE_RUNPARSE               "runparse"
#define LOCALIZED_ALTERNATE_RUNRESULT              "runresult"
#define LOCALIZED_ALTERNATE_RW                     "rw"
#define LOCALIZED_ALTERNATE_SAVE                   "save"
#define LOCALIZED_ALTERNATE_SCREENCOLOR            "screencolor"
#define LOCALIZED_ALTERNATE_SCROLLBARCREATE        "scrollbarcreate"
#define LOCALIZED_ALTERNATE_SCROLLBARENABLE        "scrollbarenable"
#define LOCALIZED_ALTERNATE_SCROLLBARDELETE        "scrollbardelete"
#define LOCALIZED_ALTERNATE_SCROLLBARGET           "scrollbarget"
#define LOCALIZED_ALTERNATE_SCROLLBARSET           "scrollbarset"
#define LOCALIZED_ALTERNATE_SCROLLX                "scrollx"
#define LOCALIZED_ALTERNATE_SCROLLY                "scrolly"
#define LOCALIZED_ALTERNATE_SCRUNCH                "scrunch"
#define LOCALIZED_ALTERNATE_SE                     "se"
#define LOCALIZED_ALTERNATE_SELECTBOX              "selectbox"
#define LOCALIZED_ALTERNATE_SENTENCE               "sentence"
#define LOCALIZED_ALTERNATE_SETACTIVEAREA          "setactivearea"
#define LOCALIZED_ALTERNATE_SETBITINDEX            "setbitindex"
#define LOCALIZED_ALTERNATE_SETBITMODE             "setbitmode"
#define LOCALIZED_ALTERNATE_SETCLIP                "setclip"
#define LOCALIZED_ALTERNATE_SETCURSOR              "setcursor"
#define LOCALIZED_ALTERNATE_SETCURSORNOWAIT        "setcursornowait"
#define LOCALIZED_ALTERNATE_SETCURSORWAIT          "setcursorwait"
#define LOCALIZED_ALTERNATE_SETFC                  "setfc"
#define LOCALIZED_ALTERNATE_SETFLOODCOLOR          "setfloodcolor"
#define LOCALIZED_ALTERNATE_SETFOCUS               "setfocus"
#define LOCALIZED_ALTERNATE_SETH                   "seth"
#define LOCALIZED_ALTERNATE_SETHEADING             "setheading"
#define LOCALIZED_ALTERNATE_SETITEM                "setitem"
#define LOCALIZED_ALTERNATE_SETLABELFONT           "setlabelfont"
#define LOCALIZED_ALTERNATE_SETLIGHT               "setlight"
#define LOCALIZED_ALTERNATE_SETMARGINS             "setmargins"
#define LOCALIZED_ALTERNATE_SETPC                  "setpc"
#define LOCALIZED_ALTERNATE_SETPENCOLOR            "setpencolor"
#define LOCALIZED_ALTERNATE_SETPENPATTERN          "setpenpattern"
#define LOCALIZED_ALTERNATE_SETPENSIZE             "setpensize"
#define LOCALIZED_ALTERNATE_SETPITCH               "setpitch"
#define LOCALIZED_ALTERNATE_SETPIXEL               "setpixel"
#define LOCALIZED_ALTERNATE_SETPOS                 "setpos"
#define LOCALIZED_ALTERNATE_SETPOSXYZ              "setposxyz"
#define LOCALIZED_ALTERNATE_SETREAD                "setread"
#define LOCALIZED_ALTERNATE_SETREADPOS             "setreadpos"
#define LOCALIZED_ALTERNATE_SETROLL                "setroll"
#define LOCALIZED_ALTERNATE_SETSC                  "setsc"
#define LOCALIZED_ALTERNATE_SETSCREENCOLOR         "setscreencolor"
#define LOCALIZED_ALTERNATE_SETSCRUNCH             "setscrunch"
#define LOCALIZED_ALTERNATE_SETTIMER               "settimer"
#define LOCALIZED_ALTERNATE_SETTURTLE              "setturtle"
#define LOCALIZED_ALTERNATE_SETTURTLEMODE          "setturtlemode"
#define LOCALIZED_ALTERNATE_SETWRITE               "setwrite"
#define LOCALIZED_ALTERNATE_SETWRITEPOS            "setwritepos"
#define LOCALIZED_ALTERNATE_SETX                   "setx"
#define LOCALIZED_ALTERNATE_SETXY                  "setxy"
#define LOCALIZED_ALTERNATE_SETXYZ                 "setxyz"
#define LOCALIZED_ALTERNATE_SETY                   "sety"
#define LOCALIZED_ALTERNATE_SETZ                   "setz"
#define LOCALIZED_ALTERNATE_SHELL                  "shell"
#define LOCALIZED_ALTERNATE_SHOW                   "show"
#define LOCALIZED_ALTERNATE_SHOWNP                 "shownp"
#define LOCALIZED_ALTERNATE_SHOWN_                 "shown?"
#define LOCALIZED_ALTERNATE_SHOWTURTLE             "showturtle"
#define LOCALIZED_ALTERNATE_SIN                    "sin"
#define LOCALIZED_ALTERNATE_SOUND                  "sound"
#define LOCALIZED_ALTERNATE_SPLITSCREEN            "splitscreen"
#define LOCALIZED_ALTERNATE_SQRT                   "sqrt"
#define LOCALIZED_ALTERNATE_SS                     "ss"
#define LOCALIZED_ALTERNATE_ST                     "st"
#define LOCALIZED_ALTERNATE_STANDOUT               "standout"
#define LOCALIZED_ALTERNATE_STATICCREATE           "staticcreate"
#define LOCALIZED_ALTERNATE_STATICDELETE           "staticdelete"
#define LOCALIZED_ALTERNATE_STATICUPDATE           "staticupdate"
#define LOCALIZED_ALTERNATE_STATUS                 "status"
#define LOCALIZED_ALTERNATE_STEP                   "step"
#define LOCALIZED_ALTERNATE_STEPPED                "stepped"
#define LOCALIZED_ALTERNATE_STOP                   "stop"
#define LOCALIZED_ALTERNATE_SUBSTRINGP             "substringp"
#define LOCALIZED_ALTERNATE_SUBSTRING_             "substring?"
#define LOCALIZED_ALTERNATE_SUM                    "sum"
#define LOCALIZED_ALTERNATE_TAG                    "tag"
#define LOCALIZED_ALTERNATE_TAN                    "tan"
#define LOCALIZED_ALTERNATE_TEST                   "test"
#define LOCALIZED_ALTERNATE_TEXT                   "text"
#define LOCALIZED_ALTERNATE_TEXTSCREEN             "textscreen"
#define LOCALIZED_ALTERNATE_THING                  "thing"
#define LOCALIZED_ALTERNATE_THROW                  "throw"
#define LOCALIZED_ALTERNATE_TIME                   "time"
#define LOCALIZED_ALTERNATE_TIMEMILLI              "timemilli"
#define LOCALIZED_ALTERNATE_TO                     "to"
#define LOCALIZED_ALTERNATE_TONE                   "tone"
#define LOCALIZED_ALTERNATE_TOWARDS                "towards"
#define LOCALIZED_ALTERNATE_TOWARDSXYZ             "towardsxyz"
#define LOCALIZED_ALTERNATE_TRACE                  "trace"
#define LOCALIZED_ALTERNATE_TRACED                 "traced"
#define LOCALIZED_ALTERNATE_TS                     "ts"
#define LOCALIZED_ALTERNATE_TURTLE                 "turtle"
#define LOCALIZED_ALTERNATE_TURTLEMODE             "turtlemode"
#define LOCALIZED_ALTERNATE_TURTLES                "turtles"
#define LOCALIZED_ALTERNATE_TYPE                   "type"
#define LOCALIZED_ALTERNATE_UNBURY                 "unbury"
#define LOCALIZED_ALTERNATE_UNSTEP                 "unstep"
#define LOCALIZED_ALTERNATE_UNTRACE                "untrace"
#define LOCALIZED_ALTERNATE_UP                     "up"
#define LOCALIZED_ALTERNATE_UPPERCASE              "uppercase"
#define LOCALIZED_ALTERNATE_UPPITCH                "uppitch"
#define LOCALIZED_ALTERNATE_WAIT                   "wait"
#define LOCALIZED_ALTERNATE_WINDOW                 "window"
#define LOCALIZED_ALTERNATE_WINDOWCREATE           "windowcreate"
#define LOCALIZED_ALTERNATE_WINDOWENABLE           "windowenable"
#define LOCALIZED_ALTERNATE_WINDOWDELETE           "windowdelete"
#define LOCALIZED_ALTERNATE_WINDOWFILEEDIT         "windowfileedit"
#define LOCALIZED_ALTERNATE_WINDOWSET              "windowset"
#define LOCALIZED_ALTERNATE_WINHELP                "winhelp"
#define LOCALIZED_ALTERNATE_WORD                   "word"
#define LOCALIZED_ALTERNATE_WORDP                  "wordp"
#define LOCALIZED_ALTERNATE_WORD_                  "word?"
#define LOCALIZED_ALTERNATE_WRAP                   "wrap"
#define LOCALIZED_ALTERNATE_WRITEPOS               "writepos"
#define LOCALIZED_ALTERNATE_WRITER                 "writer"
#define LOCALIZED_ALTERNATE_YESNOBOX               "yesnobox"
#define LOCALIZED_ALTERNATE_YIELD                  "yield"
#define LOCALIZED_ALTERNATE_ZOOM                   "zoom"

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      "OK"
#define LOCALIZED_GENERAL_CANCELBUTTON  "Cancel"
#define LOCALIZED_GENERAL_APPLYBUTTON   "&Apply"

#define LOCALIZED_GENERAL_PRODUCTNAME   "FMSLogo"

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  "The FMSLogo programming environment"

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  "&File"
#define LOCALIZED_FILE_NEW              "&New\t(erase workspace)"
#define LOCALIZED_FILE_LOAD             "&Load...\t(merge into workspace)"
#define LOCALIZED_FILE_OPEN             "&Open...\t(replace workspace)" 
#define LOCALIZED_FILE_SAVE             "&Save" 
#define LOCALIZED_FILE_SAVEAS           "Save &As..."
#define LOCALIZED_FILE_SETASSCREENSAVER "Se&t As Screen Saver"
#define LOCALIZED_FILE_EDIT             "&Edit..."
#define LOCALIZED_FILE_ERASE            "E&rase..."
#define LOCALIZED_FILE_EXIT             "E&xit"

#define LOCALIZED_BITMAP               "&Bitmap"
#define LOCALIZED_BITMAP_NEW           "&New"
#define LOCALIZED_BITMAP_LOAD          "&Load..."
#define LOCALIZED_BITMAP_SAVE          "&Save"
#define LOCALIZED_BITMAP_SAVEAS        "Save &As..."
#define LOCALIZED_BITMAP_PRINT         "&Print..."
#define LOCALIZED_BITMAP_PRINTERSETUP  "P&rinter Setup..."
#define LOCALIZED_BITMAP_ACTIVEAREA    "A&ctive Area..."

#define LOCALIZED_SET                  "&Set"
#define LOCALIZED_SET_PENSIZE          "Pen Si&ze..."
#define LOCALIZED_SET_LABELFONT        "&Label Font..."
#define LOCALIZED_SET_COMMANDERFONT    "&Commander Font..."
#define LOCALIZED_SET_PENCOLOR         "&Pen Color..."
#define LOCALIZED_SET_FLOODCOLOR       "F&lood Color..."
#define LOCALIZED_SET_SCREENCOLOR      "&Screen Color..."

#define LOCALIZED_ZOOM                 "&Zoom" 
#define LOCALIZED_ZOOM_IN              "&In"
#define LOCALIZED_ZOOM_OUT             "&Out"
#define LOCALIZED_ZOOM_NORMAL          "&Normal"

#define LOCALIZED_HELP                 "&Help" 
#define LOCALIZED_HELP_INDEX           "&Index"
#define LOCALIZED_HELP_TUTORIAL        "&Tutorial"
#define LOCALIZED_HELP_DEMO            "&Demo" 
#define LOCALIZED_HELP_EXAMPLE         "&Examples"
#define LOCALIZED_HELP_RELEASENOTES    "&Release Notes"
#define LOCALIZED_HELP_ABOUTFMSLOGO    "&About " LOCALIZED_GENERAL_PRODUCTNAME "..."
#define LOCALIZED_HELP_MS              "&About MS..."
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   "LANGUAGE to English"
#define LOCALIZED_HELP_ENGLISHTOLANG   "English to LANGUAGE"

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              "Select Active Area"
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       "These affect Printing and Saving Bitmaps"
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        "Y-High"
#define LOCALIZED_SELECTACTIVEAREA_YLOW         "Y-Low" 
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        "X-High"
#define LOCALIZED_SELECTACTIVEAREA_XLOW         "X-Low"
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH "Turtle steps per inch printed:"
#define LOCALIZED_SELECTACTIVEAREA_RESET        "&Reset" 
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON

// The screensaver strings
#define LOCALIZED_SCREENSAVER_NAME              LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_SCREENSAVER_DESCRIPTION       "FMSLogo Screensaver"
#define LOCALIZED_SCREENSAVER_SETTINGS_TITLE    "FMSLogo Screensaver Settings"
#define LOCALIZED_SCREENSAVER_LOCATE            "&Locate ..." 
#define LOCALIZED_SCREENSAVER_FILE              "Logo &File:" 
#define LOCALIZED_SCREENSAVER_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SCREENSAVER_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON

// The dialog box for selecting a Startup procedure
#define LOCALIZED_SELECTSTARTUP_CAPTION               "Select a " LOCALIZED_ALTERNATE_STARTUP " instruction"
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED "Your workspace does not have a " LOCALIZED_ALTERNATE_STARTUP " instruction list defined, so nothing\nwill happen when the screensaver is loaded.\nPlease select a procedure to run when the program is loaded."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST   "The " LOCALIZED_ALTERNATE_STARTUP " variable is not a list, so nothing will happen when the screensaver\nis loaded.\nPlease select a procedure to run when the program is loaded."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY     "Your workspace has an empty " LOCALIZED_ALTERNATE_STARTUP " instruction list defined, so nothing will\nhappen when the screensaver is loaded.\nPlease select a procedure to run when the program is loaded."
#define LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED   "No procedures are defined"

// The warning dialog box when the user saves an empty workspace
#define LOCALIZED_EMPTYWORKSPACE_TITLE                LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_EMPTYWORKSPACE_MESSAGE              "There are no procedures, variables, or property lists defined,\nso the workspace will be saved as an empty file.\n\nDo you want to save the workspace anyway?"

//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     "Copy"
#define LOCALIZED_POPUP_CUT                      "Cut"
#define LOCALIZED_POPUP_PASTE                    "Paste"
#define LOCALIZED_POPUP_DELETE                   "Delete"
#define LOCALIZED_POPUP_UNDO                     "Undo"
#define LOCALIZED_POPUP_REDO                     "Redo"
#define LOCALIZED_POPUP_SELECTALL                "Select All"
#define LOCALIZED_POPUP_HELP                     "Topic Search"
#define LOCALIZED_POPUP_REMOVELINES              "Remove Selected Lines"

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   "Editor"

#define LOCALIZED_EDITOR_FILE                    "&File"
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        "&Save and Exit\tCtrl+D"
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    "Save to &Workspace"
#define LOCALIZED_EDITOR_FILE_PRINT              "&Print..." 
#define LOCALIZED_EDITOR_FILE_EXIT               "E&xit" 

#define LOCALIZED_EDITOR_EDIT                    "&Edit"
#define LOCALIZED_EDITOR_EDIT_UNDO               "&Undo\tCtrl+Z"
#define LOCALIZED_EDITOR_EDIT_REDO               "&Redo\tCtrl+Y"
#define LOCALIZED_EDITOR_EDIT_CUT                "&Cut\tCtrl+X"
#define LOCALIZED_EDITOR_EDIT_COPY               "C&opy\tCtrl+C"
#define LOCALIZED_EDITOR_EDIT_PASTE              "&Paste\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_DELETE             "&Delete\tDel"
#define LOCALIZED_EDITOR_EDIT_CLEARALL           "C&lear All\tCtrl+Del"
#define LOCALIZED_EDITOR_EDIT_SELECTALL          "S&elect All\tCtrl+A"

#define LOCALIZED_EDITOR_SEARCH                  "&Search"
#define LOCALIZED_EDITOR_SEARCH_FIND             "&Find...\tCtrl+F"
#define LOCALIZED_EDITOR_SEARCH_REPLACE          "&Replace...\tCtrl+H" 
#define LOCALIZED_EDITOR_SEARCH_NEXT             "&Next\tF3" 

#define LOCALIZED_EDITOR_SET                     "Se&t" 
#define LOCALIZED_EDITOR_SET_FONT                "&Font..." 

#define LOCALIZED_EDITOR_TEST                    "Test"
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      "&Run Selection\tCtrl+R"

#define LOCALIZED_EDITOR_HELP                    "&Help" 
#define LOCALIZED_EDITOR_HELP_INDEX              "&Index"
#define LOCALIZED_EDITOR_HELP_EDITOR             "&Editor"
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        "&Topic Search\tF1"


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    "&Save and Exit"
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       "&Don't Save"
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       "There are unsaved changes in the workspace.  If you exit without saving, these changes will be lost.  "
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       "Would you like to save your changes before exiting?" 


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     "Commander"
#define LOCALIZED_COMMANDER_HALT                "Halt"
#define LOCALIZED_COMMANDER_TRACE               "Trace"
#define LOCALIZED_COMMANDER_NOTRACE             "NoTrace"
#define LOCALIZED_COMMANDER_PAUSE               "Pause"
#define LOCALIZED_COMMANDER_STATUS              "Status"
#define LOCALIZED_COMMANDER_NOSTATUS            "NoStatus"
#define LOCALIZED_COMMANDER_STEP                "Step"
#define LOCALIZED_COMMANDER_UNSTEP              "UnStep"
#define LOCALIZED_COMMANDER_RESET               "Reset"
#define LOCALIZED_COMMANDER_EXECUTE             "Execute"
#define LOCALIZED_COMMANDER_EDALL               "Edall"

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        "Status"
#define LOCALIZED_STATUS_PEN                    "Pen"
#define LOCALIZED_STATUS_CONTACT                "Contact:"
#define LOCALIZED_STATUS_WIDTH                  "Width:"
#define LOCALIZED_STATUS_STYLE                  "Style:"
#define LOCALIZED_STATUS_ORIENTATION            "Orientation"
#define LOCALIZED_STATUS_PITCH                  "Pitch:"
#define LOCALIZED_STATUS_HEADING                "Heading:"
#define LOCALIZED_STATUS_ROLL                   "Roll:"
#define LOCALIZED_STATUS_TURTLE                 "Turtle"
#define LOCALIZED_STATUS_POSITION               "Position(XYZ):"
#define LOCALIZED_STATUS_WHICH                  "Which:"
#define LOCALIZED_STATUS_VISIBILITY             "Visibility:"
#define LOCALIZED_STATUS_COLOR                  "Color"
#define LOCALIZED_STATUS_PENCOLOR               "Pen(RGB):"
#define LOCALIZED_STATUS_FLOODCOLOR             "Flood(RGB):"
#define LOCALIZED_STATUS_SCREENCOLOR            "Screen(RGB):"
#define LOCALIZED_STATUS_KERNEL                 "Kernel"
#define LOCALIZED_STATUS_CALLS                  "Calls:"
#define LOCALIZED_STATUS_PEAKMEMORY             "Peak Memory:"

#define LOCALIZED_STATUS_PENREVERSE     "Reverse"
#define LOCALIZED_STATUS_PENNORMAL      "Normal"
#define LOCALIZED_STATUS_PENERASE       "Erase"
#define LOCALIZED_STATUS_PENUP          "Up"
#define LOCALIZED_STATUS_PENDOWN        "Down"
#define LOCALIZED_STATUS_PENSHOWN       "Shown"
#define LOCALIZED_STATUS_PENHIDDEN      "Hidden"
#define LOCALIZED_STATUS_POLYGONS       "Polygons"
#define LOCALIZED_STATUS_VECTORS        "Vectors"
#define LOCALIZED_STATUS_NODES          "Nodes"
#define LOCALIZED_STATUS_NOT_APPLICABLE "N/A"

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           "&All"
#define LOCALIZED_ERASEPROCEDURE                "Erase Procedure"
#define LOCALIZED_EDITPROCEDURE                 "Edit Procedure"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     "Set Color"
#define LOCALIZED_SETCOLOR_PENCOLOR            "Pen Color"
#define LOCALIZED_SETCOLOR_FLOODCOLOR          "Flood Color"
#define LOCALIZED_SETCOLOR_SCREENCOLOR         "Screen Color"
#define LOCALIZED_SETCOLOR_RED                 "Red"
#define LOCALIZED_SETCOLOR_GREEN               "Green"
#define LOCALIZED_SETCOLOR_BLUE                "Blue"
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   "Pen Size"
#define LOCALIZED_SETPENSIZE_SIZE              "Thickness"
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     "About " LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_ABOUTFMS_VERSION             "Version"
#define LOCALIZED_ABOUTFMS_GUI                 "GUI by George Mills\nSoftronics, Inc.\nhttp://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_CORE                "Core by Brian Harvey\nUniversity of California Berkeley"
#define LOCALIZED_ABOUTFMS_INSTALLER           "Installer based on Nullsoft Scriptable Install System\nhttp://nsis.sourceforge.net/"
#define LOCALIZED_ABOUTFMS_ADVENTURE           "The Great Logo Adventure (ISBN 0-9651934-6-2)\nWritten and donated by Jim Muller\nAvailable at http://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       "Special thanks to Yehuda Katz and Erich Neuwirth"
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME " is free software\nSee GNU Public License"
#define LOCALIZED_ABOUTFMS_NEWSGROUP           "Internet News Group: comp.lang.logo\nVisit the Logo-Forum at\nhttp://groups.yahoo.com/group/LogoForum/"
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     "To learn the internals of computers,\ntry MultiMedia Logic from Softronics, Inc."
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      "About FMS"
#define LOCALIZED_ABOUTMS_FMS                  "FMS stands for Fight Multiple Sclerosis."
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     "Please consider donating to the\nNational Multiple Sclerosis Society.\nhttp://www.nmss.org\n1-800-FIGHT-MS"
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

#define LOCALIZED_CHANGESINEDITORMAYBELOST  "Changes in this edit session may be lost.\n\nDo you really want to exit " LOCALIZED_GENERAL_PRODUCTNAME "?"
#define LOCALIZED_EDITSESSIONISRUNNING      "An Edit session is running"

#define LOCALIZED_COULDNOTWRITEBMP            "Could not write .bmp"
#define LOCALIZED_COULDNOTOPENBMP             "Could not open .bmp"
#define LOCALIZED_COULDNOTCREATEBMP           "Unable to create Windows 3.0 bitmap"
#define LOCALIZED_NOTVALIDBMP                 "Not a Windows 3.0 bitmap"

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         "You have not saved to disk"
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     "Executing a new will erase all definitions.\n\nContinue with New?"
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE "The file being loaded will be merged into your workspace\nand may overwrite your unsaved changes.\n\nContinue with Load?"
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    "This will erase all of your unsaved changes.\n\nContinue with Open?"

#define LOCALIZED_EDITORISOPEN                  "Did you know you have an edit session running?\n\nAny changes in this edit session are not being saved."

#define LOCALIZED_ERROR_CANTREADFILE            "Unable to read file \"%s\" from disk"
#define LOCALIZED_ERROR_CANTWRITEFILE           "Unable to write file \"%s\" to disk"

#define LOCALIZED_SAVETOWORKSPACE                "Save to Workspace"
#define LOCALIZED_CONTENTSCHANGED                "Contents Changed"
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE "The contents have changed.\nWould you like to save the changes to the workspace?"



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  "There was a problem saving the contents of the editor to the workspace.  The cursor will be positioned just after last successful definition.\n\nCheck the Commander for possible error message."
#define LOCALIZED_RETURNTOEDIT                  "Return to the editor?"

#define LOCALIZED_EDITFAILEDTOLOAD              LOCALIZED_SAVETOWORKSPACE

#define LOCALIZED_ERRORINFILETITLE              "Error in File"
#define LOCALIZED_ERRORINFILEMESSAGE            "There was a problem loading the contents of the file \"%s\".\n\nCheck the Commander for possible error message.\n\nDo you want to open the file in the editor to see the error?"

#define LOCALIZED_CANNOTALLOCATESCREEN          "Unable to allocate memory for the screen window.  You may have requested a width and height that exceeds the amount of available video RAM.\n\n" LOCALIZED_GENERAL_PRODUCTNAME " can't continue."


// 
//  Strings used in the File-Open filters
//
#define LOCALIZED_FILE_LOAD_DIALOG_TITLE    "Select the Logo program to load (merge into workspace)"
#define LOCALIZED_FILE_OPEN_DIALOG_TITLE    "Select the Logo program to open (replace the workspace with)"
#define LOCALIZED_FILE_SAVE_DIALOG_TITLE    "Select the file to which the workspace will be saved"
#define LOCALIZED_BITMAP_OPEN_DIALOG_TITLE  "Select the image to load"
#define LOCALIZED_BITMAP_SAVE_DIALOG_TITLE  "Select the file to which the active area will be saved"

#define LOCALIZED_LOGO_FILE_EXTENSION "lgo"
#define LOCALIZED_FILEFILTER_ALLFILES "All Files (*.*)|*.*"
#define LOCALIZED_FILEFILTER_LOGO     "Logo Files (*.lgo)|*.lgo|" LOCALIZED_FILEFILTER_ALLFILES
#define LOCALIZED_FILEFILTER_IMAGE    "Bitmap Files (*.bmp)|*.bmp|GIF Files (*.gif)|*.gif|" LOCALIZED_FILEFILTER_ALLFILES



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             " stops\n"
#define LOCALIZED_TRACING_OUTPUTS           " outputs %s\n"
#define LOCALIZED_TRACING_MAKE              "Make %s %s"
#define LOCALIZED_TRACING_PPROP             "Pprop %s %s %s"
#define LOCALIZED_TRACING_LOCATION          " in %s\n%s"

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  "Single Step"

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  "%s defined\n"


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    "erase"
#define LOCALIZED_PENMODE_REVERSE  "reverse"
#define LOCALIZED_PENMODE_PAINT    "paint"

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          "Logo: Fatal Internal Error"
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       "Logo: Out of memory"
#define LOCALIZED_ERROR_OUTOFMEMORY            "Out of memory"
#define LOCALIZED_ERROR_STACKOVERFLOW          "stack overflow"
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      "turtle out of bounds"
#define LOCALIZED_ERROR_BADGRAPHINIT           "couldn't initialize graphics"
#define LOCALIZED_ERROR_BADDATA                "%p doesn't like %s as input"
#define LOCALIZED_ERROR_DIDNTOUTPUT            "%p didn't output to %p"
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        "not enough inputs to %p"
#define LOCALIZED_ERROR_TOOMUCH                "too much inside ()'s"
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    "You don't say what to do with %s"
#define LOCALIZED_ERROR_PARENMISMATCH          "too many ('s"
#define LOCALIZED_ERROR_NOVALUE                "%s has no value"
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        "unexpected ')'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      "unexpected ']'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        "unexpected '}'"
#define LOCALIZED_ERROR_DONTKNOWHOWTO          "I don't know how to %p"
#define LOCALIZED_ERROR_NOCATCHTAG             "Can't find catch tag for %p"
#define LOCALIZED_ERROR_ALREADYDEFINED         "%p is already defined"
#define LOCALIZED_ERROR_STOPPING               "Stopping..."
#define LOCALIZED_ERROR_ALREADYDRIBBLING       "Already dribbling"
#define LOCALIZED_ERROR_FILESYSTEM                   "File system error: %p"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          "Could not open file"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         "Unable to open file: %t"
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       "File already open"
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           "File not open"
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  "Could not create editor file"
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   "Could not launch the editor" 
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    "Could not read editor file" 
#define LOCALIZED_ERROR_IFWARNING              "Assuming you mean IFELSE, not IF"
#define LOCALIZED_ERROR_SHADOWWARNING          "%p shadowed by local in procedure call"
#define LOCALIZED_ERROR_USER                   "Throw \"Error"
#define LOCALIZED_ERROR_ISPRIMITIVE            "%p is a primitive"
#define LOCALIZED_ERROR_TONOTINSIDE            "Can't use TO inside a procedure"
#define LOCALIZED_ERROR_ATTOPLEVEL             "Can only use %p inside a procedure"
#define LOCALIZED_ERROR_ATTOPLEVEL2            "You must be in a procedure to use OUTPUT or STOP"
#define LOCALIZED_ERROR_NOTEST                 "%p without TEST"
#define LOCALIZED_ERROR_BADMACROOUTPUT         "Macro output %s instead of a list"
#define LOCALIZED_ERROR_DEEPEND                "END inside multi-line instruction"
#define LOCALIZED_ERROR_DEEPENDIN              "END inside multi-line instruction in %p"
#define LOCALIZED_ERROR_UNKNOWN                "Unknown error condition - internal error."
#define LOCALIZED_PAUSING                      "Pausing..."


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION "Invalid state for instruction: %p"
#define LOCALIZED_ERROR_MODE_ON_SPRITE             "cannot set the mode of a turtle with a rotating bitmap"
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        "cannot make a special turtle use a rotating bitmap"
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            "cannot use the clipboard as a rotating bitmap"
#define LOCALIZED_ERROR_SPECIALFORM                "%p doesn't like %p as input because it has a special form"

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      "Error"
#define LOCALIZED_ERROR_BADINPUT             "Bad input"
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    "Input is not paired"

#define LOCALIZED_ERROR_CANTOPENPORT         "Could not open port"
#define LOCALIZED_ERROR_CANTCLOSEPORT        "Could not close port"
#define LOCALIZED_ERROR_CANTFLUSHPORT        "Could not flush port"
#define LOCALIZED_ERROR_CANTDCBONPORT        "Could not build dcb on port"
#define LOCALIZED_ERROR_CANTSETPORT          "Could not set port"
#define LOCALIZED_ERROR_PORTALREADYOPEN      "Port is already open"
#define LOCALIZED_ERROR_PORTNOTOPEN          "Port is not open"

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   "%s already exists"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    "%s does not exist"

#define LOCALIZED_ERROR_DLLNOTLOADED          "DLL is not loaded"
#define LOCALIZED_ERROR_DLLLOADFAILED         "DLL load failed"
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    "Invalid data type input"
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  "Invalid output type"
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   "Function not found"
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  "Not all Type/Data inputs are paired"

#define LOCALIZED_ERROR_NETWORK               "Network Error"
#define LOCALIZED_ERROR_NETWORKRECEIVE        "Network Receive Error"
#define LOCALIZED_ERROR_NETWORKSEND           "Network Send Error"
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       "Unexpected Error, Network may be shutdown"
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     "Not started"
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED "Already started"
#define LOCALIZED_ERROR_NETWORKALREADYON      "Already on"
#define LOCALIZED_ERROR_NETWORKALREADYOFF     "Already off"

// The rest of the network errors shouldn't really be seen -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         "Name too long"
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      "Not initialized"
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      "System not ready"
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED "Version is not supported"
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   "Can't send after socket shutdown"
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         "Interrupted system call"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    "Authoritative Answer: Host not found"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH "Non-Authoritative: Host not found. See NETSTARTUP"
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      "Non-recoverable error"
#define LOCALIZED_ERROR_NETWORKNODATA              "No data record available"
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       "Bad file number"
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          "Operation would block"
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       "Operation now in progress"
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   "Operation already in progress"
#define LOCALIZED_ERROR_NETWORKBADADDRESS          "Bad address"
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     "Destination address required"
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      "Message too long"
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      "Protocol family not supported"
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         "Directory not empty"
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     "Application limit has been reached"
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           "Disk quota exceeded"
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        "Too many open files"
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        "Access denied"
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          "Socket operation on non-socket"
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    "Can't assign requested address"
#define LOCALIZED_ERROR_NETWORKADDRINUSE           "Address already in use"
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      "Address family not supported by protocol family"
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            "Connection timed out"
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    "Socket type not supported"
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   "Protocol not supported"
#define LOCALIZED_ERROR_NETWORKNOBUFFER            "No space in buffer"
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    "Socket is already connected"
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        "Socket is not connected"
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         "Bad protocol option"
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     "Connection reset by peer"
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     "Software caused connection abort"
#define LOCALIZED_ERROR_NETWORKISDOWN              "Network is down"
#define LOCALIZED_ERROR_NETWORKRESET               "Network was reset"
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   "Connection refused"
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          "Host is down"
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   "Host is unreachable"
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        "Protocol is wrong type for socket"
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   "Operation not supported on socket"
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         "No path to remote host was found"
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         "Too many references"

#define LOCALIZED_ERROR_POLYSTART               "PolyStart Error"
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED "You already have a Polygon started"

#define LOCALIZED_ERROR_POLYEND                 "PolyEnd Error"
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       "You have not started a Polygon"
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     "You must have at least 3 vectors to define a polygon"

#define LOCALIZED_ERROR_SOUND                 "Sound Error"

#define LOCALIZED_ERROR_MIDI                  "MIDI Error"
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     "Invalid MIDI device"
#define LOCALIZED_ERROR_MIDIALREADYOPEN       "Already open"
#define LOCALIZED_ERROR_MIDINOTOPEN           "Not open"

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      "No Text in Clipboard"

#define LOCALIZED_ERROR_MCI                   "MCI Error"

#define LOCALIZED_ERROR_TIMERNOTFOUND         "Timer not found"

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       "Online help is unavailable because hhctrl.ocx could not be loaded." 

#define LOCALIZED_ERROR_BADCOMMANDLINE        "Invalid Command Line" 

#define LOCALIZED_ERROR_TMPNOTDEFINED         "The environment variable TMP is not defined or invalid.\n" LOCALIZED_GENERAL_PRODUCTNAME " will attempt to use C:\\ for storing temporary files"

#define LOCALIZED_ERROR_GIFSAVEFAILED         "Problem Generating GIF, check memory and diskspace"
#define LOCALIZED_ERROR_GIFREADFAILED         "Problem Reading GIF, check memory and diskspace"

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  "BitMap Index out of range"
#define LOCALIZED_ERROR_BITMAPCUTFAILED        "Cut failed, Possibly not enough Memory"

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    "Nothing to Paste" 
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  "BitMap at Index must be initialized with a bitmap" 

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      "Turtle %d has no picture, will Halt"

#define LOCALIZED_ERROR_FONTNOTFOUND            "Sorry, no font named %s was found.  Choose one of the following:\n"

#define LOCALIZED_ERROR_PRINTERCANTSCALE        "Print driver does not support this function" 
#define LOCALIZED_ERROR_CANTDRAWIMAGE           "Cannot draw image"
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        "Cannot extract image"
#define LOCALIZED_ERROR_SUBCODE                 "Sub Code"

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         "Input:"
#define LOCALIZED_PROMPT_TO     "To Mode (Cancel to End)"
#define LOCALIZED_PROMPT_LIST   "List Mode (Cancel to Halt)"
#define LOCALIZED_PROMPT_PAUSE  "Pause Mode (Cancel to Continue)"
#define LOCALIZED_PROMPT_INPUT  "Input Mode (Cancel to Halt)"

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      "Changed to \"%s\""
#define LOCALIZED_FILE_CHDIRFAILED         "Could not chdir to directory \"%s\""
#define LOCALIZED_FILE_POPPEDTO            "Popped to \"%s\""
#define LOCALIZED_FILE_MKDIRSUCCEEDED      "Now in newly created directory \"%s\"" 
#define LOCALIZED_FILE_MKDIRFAILED         "Failed to create directory \"%s\"" 
#define LOCALIZED_FILE_RMDIRSUCCEEDED      "Removed directory \"%s\"" 
#define LOCALIZED_FILE_RMDIRFAILED         "Failed to remove directory \"%s\"" 
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  "The directory does not exist."
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY "Make sure the directory is empty before trying to remove it."


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       "Logo Picture"

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    "Active Area"
#define LOCALIZED_INFORMATION   "Information"
#define LOCALIZED_WARNING       "Warning"
#define LOCALIZED_UNTITLED      "Untitled"
#define LOCALIZED_UNKNOWN       "Unknown"

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       "nothing"

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     "Find"
#define LOCALIZED_EDITOR_TITLE_REPLACE  "Replace" 

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING "Cannot find %s"


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
#define LOCALIZED_COLOR_ALICEBLUE             "AliceBlue"
#define LOCALIZED_COLOR_ANTIQUEWHITE          "AntiqueWhite"
#define LOCALIZED_COLOR_AQUA                  "Aqua"
#define LOCALIZED_COLOR_AQUAMARINE            "Aquamarine"
#define LOCALIZED_COLOR_AZURE                 "Azure"
#define LOCALIZED_COLOR_BEIGE                 "Beige"
#define LOCALIZED_COLOR_BISQUE                "Bisque"
#define LOCALIZED_COLOR_BLACK                 "Black"
#define LOCALIZED_COLOR_BLANCHEDALMOND        "BlanchedAlmond"
#define LOCALIZED_COLOR_BLUE                  "Blue"
#define LOCALIZED_COLOR_BLUEVIOLET            "BlueViolet"
#define LOCALIZED_COLOR_BROWN                 "Brown"
#define LOCALIZED_COLOR_BURLYWOOD             "BurlyWood"
#define LOCALIZED_COLOR_CADETBLUE             "CadetBlue"
#define LOCALIZED_COLOR_CHARTREUSE            "Chartreuse"
#define LOCALIZED_COLOR_CHOCOLATE             "Chocolate"
#define LOCALIZED_COLOR_CORAL                 "Coral"
#define LOCALIZED_COLOR_CORNFLOWERBLUE        "CornflowerBlue"
#define LOCALIZED_COLOR_CORNSILK              "Cornsilk"
#define LOCALIZED_COLOR_CRIMSON               "Crimson"
#define LOCALIZED_COLOR_CYAN                  "Cyan"
#define LOCALIZED_COLOR_DARKBLUE              "DarkBlue"
#define LOCALIZED_COLOR_DARKCYAN              "DarkCyan"
#define LOCALIZED_COLOR_DARKGOLDENROD         "DarkGoldenRod"
#define LOCALIZED_COLOR_DARKGRAY              "DarkGray"
#define LOCALIZED_COLOR_DARKGREEN             "DarkGreen"
#define LOCALIZED_COLOR_DARKGREY              "DarkGrey"
#define LOCALIZED_COLOR_DARKKHAKI             "DarkKhaki"
#define LOCALIZED_COLOR_DARKMAGENTA           "DarkMagenta"
#define LOCALIZED_COLOR_DARKOLIVEGREEN        "DarkOliveGreen"
#define LOCALIZED_COLOR_DARKORANGE            "DarkOrange"
#define LOCALIZED_COLOR_DARKORCHID            "DarkOrchid"
#define LOCALIZED_COLOR_DARKRED               "DarkRed"
#define LOCALIZED_COLOR_DARKSALMON            "DarkSalmon"
#define LOCALIZED_COLOR_DARKSEAGREEN          "DarkSeaGreen"
#define LOCALIZED_COLOR_DARKSLATEBLUE         "DarkSlateBlue"
#define LOCALIZED_COLOR_DARKSLATEGRAY         "DarkSlateGray"
#define LOCALIZED_COLOR_DARKSLATEGREY         "DarkSlateGrey"
#define LOCALIZED_COLOR_DARKTURQUOISE         "DarkTurquoise"
#define LOCALIZED_COLOR_DARKVIOLET            "DarkViolet"
#define LOCALIZED_COLOR_DEEPPINK              "DeepPink"
#define LOCALIZED_COLOR_DEEPSKYBLUE           "DeepSkyBlue"
#define LOCALIZED_COLOR_DIMGRAY               "DimGray"
#define LOCALIZED_COLOR_DIMGREY               "DimGrey"
#define LOCALIZED_COLOR_DODGERBLUE            "DodgerBlue"
#define LOCALIZED_COLOR_FIREBRICK             "FireBrick"
#define LOCALIZED_COLOR_FLORALWHITE           "FloralWhite"
#define LOCALIZED_COLOR_FORESTGREEN           "ForestGreen"
#define LOCALIZED_COLOR_FUCHSIA               "Fuchsia"
#define LOCALIZED_COLOR_GAINSBORO             "Gainsboro"
#define LOCALIZED_COLOR_GHOSTWHITE            "GhostWhite"
#define LOCALIZED_COLOR_GOLD                  "Gold"
#define LOCALIZED_COLOR_GOLDENROD             "GoldenRod"
#define LOCALIZED_COLOR_GRAY                  "Gray"
#define LOCALIZED_COLOR_GREEN                 "Green"
#define LOCALIZED_COLOR_GREENYELLOW           "GreenYellow"
#define LOCALIZED_COLOR_GREY                  "Grey"
#define LOCALIZED_COLOR_HONEYDEW              "HoneyDew"
#define LOCALIZED_COLOR_HOTPINK               "HotPink"
#define LOCALIZED_COLOR_INDIANRED             "IndianRed"
#define LOCALIZED_COLOR_INDIGO                "Indigo"
#define LOCALIZED_COLOR_IVORY                 "Ivory"
#define LOCALIZED_COLOR_KHAKI                 "Khaki"
#define LOCALIZED_COLOR_LAVENDER              "Lavender"
#define LOCALIZED_COLOR_LAVENDERBLUSH         "LavenderBlush"
#define LOCALIZED_COLOR_LAWNGREEN             "LawnGreen"
#define LOCALIZED_COLOR_LEMONCHIFFON          "LemonChiffon"
#define LOCALIZED_COLOR_LIGHTBLUE             "LightBlue"
#define LOCALIZED_COLOR_LIGHTCORAL            "LightCoral"
#define LOCALIZED_COLOR_LIGHTCYAN             "LightCyan"
#define LOCALIZED_COLOR_LIGHTGOLDENRODYELLOW  "LightGoldenRodYellow"
#define LOCALIZED_COLOR_LIGHTGRAY             "LightGray"
#define LOCALIZED_COLOR_LIGHTGREEN            "LightGreen"
#define LOCALIZED_COLOR_LIGHTGREY             "LightGrey"
#define LOCALIZED_COLOR_LIGHTPINK             "LightPink"
#define LOCALIZED_COLOR_LIGHTSALMON           "LightSalmon"
#define LOCALIZED_COLOR_LIGHTSEAGREEN         "LightSeaGreen"
#define LOCALIZED_COLOR_LIGHTSKYBLUE          "LightSkyBlue"
#define LOCALIZED_COLOR_LIGHTSLATEGRAY        "LightSlateGray"
#define LOCALIZED_COLOR_LIGHTSLATEGREY        "LightSlateGrey"
#define LOCALIZED_COLOR_LIGHTSTEELBLUE        "LightSteelBlue"
#define LOCALIZED_COLOR_LIGHTYELLOW           "LightYellow"
#define LOCALIZED_COLOR_LIME                  "Lime"
#define LOCALIZED_COLOR_LIMEGREEN             "LimeGreen"
#define LOCALIZED_COLOR_LINEN                 "Linen"
#define LOCALIZED_COLOR_MAGENTA               "Magenta"
#define LOCALIZED_COLOR_MAROON                "Maroon"
#define LOCALIZED_COLOR_MEDIUMAQUAMARINE      "MediumAquaMarine"
#define LOCALIZED_COLOR_MEDIUMBLUE            "MediumBlue"
#define LOCALIZED_COLOR_MEDIUMORCHID          "MediumOrchid"
#define LOCALIZED_COLOR_MEDIUMPURPLE          "MediumPurple"
#define LOCALIZED_COLOR_MEDIUMSEAGREEN        "MediumSeaGreen"
#define LOCALIZED_COLOR_MEDIUMSLATEBLUE       "MediumSlateBlue"
#define LOCALIZED_COLOR_MEDIUMSPRINGGREEN     "MediumSpringGreen"
#define LOCALIZED_COLOR_MEDIUMTURQUOISE       "MediumTurquoise"
#define LOCALIZED_COLOR_MEDIUMVIOLETRED       "MediumVioletRed"
#define LOCALIZED_COLOR_MIDNIGHTBLUE          "MidnightBlue"
#define LOCALIZED_COLOR_MINTCREAM             "MintCream"
#define LOCALIZED_COLOR_MISTYROSE             "MistyRose"
#define LOCALIZED_COLOR_MOCCASIN              "Moccasin"
#define LOCALIZED_COLOR_NAVAJOWHITE           "NavajoWhite"
#define LOCALIZED_COLOR_NAVY                  "Navy"
#define LOCALIZED_COLOR_OLDLACE               "OldLace"
#define LOCALIZED_COLOR_OLIVE                 "Olive"
#define LOCALIZED_COLOR_OLIVEDRAB             "OliveDrab"
#define LOCALIZED_COLOR_ORANGE                "Orange"
#define LOCALIZED_COLOR_ORANGERED             "OrangeRed"
#define LOCALIZED_COLOR_ORCHID                "Orchid"
#define LOCALIZED_COLOR_PALEGOLDENROD         "PaleGoldenRod"
#define LOCALIZED_COLOR_PALEGREEN             "PaleGreen"
#define LOCALIZED_COLOR_PALETURQUOISE         "PaleTurquoise"
#define LOCALIZED_COLOR_PALEVIOLETRED         "PaleVioletRed"
#define LOCALIZED_COLOR_PAPAYAWHIP            "PapayaWhip"
#define LOCALIZED_COLOR_PEACHPUFF             "PeachPuff"
#define LOCALIZED_COLOR_PERU                  "Peru"
#define LOCALIZED_COLOR_PINK                  "Pink"
#define LOCALIZED_COLOR_PLUM                  "Plum"
#define LOCALIZED_COLOR_POWDERBLUE            "PowderBlue"
#define LOCALIZED_COLOR_PURPLE                "Purple"
#define LOCALIZED_COLOR_RED                   "Red"
#define LOCALIZED_COLOR_ROSYBROWN             "RosyBrown"
#define LOCALIZED_COLOR_ROYALBLUE             "RoyalBlue"
#define LOCALIZED_COLOR_SADDLEBROWN           "SaddleBrown"
#define LOCALIZED_COLOR_SALMON                "Salmon"
#define LOCALIZED_COLOR_SANDYBROWN            "SandyBrown"
#define LOCALIZED_COLOR_SEAGREEN              "SeaGreen"
#define LOCALIZED_COLOR_SEASHELL              "SeaShell"
#define LOCALIZED_COLOR_SIENNA                "Sienna"
#define LOCALIZED_COLOR_SILVER                "Silver"
#define LOCALIZED_COLOR_SKYBLUE               "SkyBlue"
#define LOCALIZED_COLOR_SLATEBLUE             "SlateBlue"
#define LOCALIZED_COLOR_SLATEGRAY             "SlateGray"
#define LOCALIZED_COLOR_SLATEGREY             "SlateGrey"
#define LOCALIZED_COLOR_SNOW                  "Snow"
#define LOCALIZED_COLOR_SPRINGGREEN           "SpringGreen"
#define LOCALIZED_COLOR_STEELBLUE             "SteelBlue"
#define LOCALIZED_COLOR_TAN                   "Tan"
#define LOCALIZED_COLOR_TEAL                  "Teal"
#define LOCALIZED_COLOR_THISTLE               "Thistle"
#define LOCALIZED_COLOR_TOMATO                "Tomato"
#define LOCALIZED_COLOR_TURQUOISE             "Turquoise"
#define LOCALIZED_COLOR_VIOLET                "Violet"
#define LOCALIZED_COLOR_WHEAT                 "Wheat"
#define LOCALIZED_COLOR_WHITE                 "White"
#define LOCALIZED_COLOR_WHITESMOKE            "WhiteSmoke"
#define LOCALIZED_COLOR_YELLOW                "Yellow"
#define LOCALIZED_COLOR_YELLOWGREEN           "YellowGreen"

//
// The name of each "window class" that DEBUGWINDOWS prints.
// These should match the corresponding terms that is used
// in the  LOCALIZED_ALTERNATE_*CREATE procedures.
//
#define LOCALIZED_WINDOWCLASSNAME_WINDOW       "Window"
#define LOCALIZED_WINDOWCLASSNAME_STATIC       "Static"
#define LOCALIZED_WINDOWCLASSNAME_LISTBOX      "ListBox"
#define LOCALIZED_WINDOWCLASSNAME_COMBOBOX     "ComboBox"
#define LOCALIZED_WINDOWCLASSNAME_BUTTON       "Button"
#define LOCALIZED_WINDOWCLASSNAME_SCROLLBAR    "ScrollBar"
#define LOCALIZED_WINDOWCLASSNAME_GROUPBOX     "GroupBox"
#define LOCALIZED_WINDOWCLASSNAME_RADIOBUTTON  "RadioButton"
#define LOCALIZED_WINDOWCLASSNAME_CHECKBOX     "CheckBox"
#define LOCALIZED_WINDOWCLASSNAME_DIALOG       "Dialog"


//
// The name of the default font face name.
// This should only be translated if the given font face doesn't include glyphs
// for characters in your language.  The specified font face name must be part
// of all Windows versions from Windows XP onward that would support your
// language.
//
#define LOCALIZED_DEFAULT_FONT_FACE "Courier New"
