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
// This file contains localized strings for Pseudoloc by David Costanzo
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
#define LOCALIZED_ALTERNATE_TRUE     "pseudo.true"
#define LOCALIZED_ALTERNATE_FALSE    "pseudo.false"
#define LOCALIZED_ALTERNATE_END      "pseudo.end"
#define LOCALIZED_ALTERNATE_TOPLEVEL "pseudo.toplevel"
#define LOCALIZED_ALTERNATE_SYSTEM   "pseudo.system"

//
// Localized "alternate" names of Logo special variables
//
#define LOCALIZED_ALTERNATE_CASEIGNOREDP    "pseudo.caseignoredp"
#define LOCALIZED_ALTERNATE_ERRACT          "pseudo.erract"
#define LOCALIZED_ALTERNATE_STARTUP         "pseudo.startup"
#define LOCALIZED_ALTERNATE_REDEFP          "pseudo.redefp"
#define LOCALIZED_ALTERNATE_PRINTWIDTHLIMIT "pseudo.printwidthlimit"
#define LOCALIZED_ALTERNATE_PRINTDEPTHLIMIT "pseudo.printdepthlimit"


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
#define LOCALIZED_ALTERNATE__DEFMACRO              "pseudo..defmacro"
#define LOCALIZED_ALTERNATE__EQ                    "pseudo..eq"
#define LOCALIZED_ALTERNATE__MACRO                 "pseudo..macro"
#define LOCALIZED_ALTERNATE__MAYBEOUTPUT           "pseudo..maybeoutput"
#define LOCALIZED_ALTERNATE__SETBF                 "pseudo..setbf"
#define LOCALIZED_ALTERNATE__SETFIRST              "pseudo..setfirst"
#define LOCALIZED_ALTERNATE__SETITEM               "pseudo..setitem"
#define LOCALIZED_ALTERNATE_ACTIVEAREA             "pseudo.activearea"
#define LOCALIZED_ALTERNATE_ALLOPEN                "pseudo.allopen"
#define LOCALIZED_ALTERNATE_AND                    "pseudo.and"
#define LOCALIZED_ALTERNATE_APPLY                  "pseudo.apply"
#define LOCALIZED_ALTERNATE_ARCCOS                 "pseudo.arccos"
#define LOCALIZED_ALTERNATE_ARCSIN                 "pseudo.arcsin"
#define LOCALIZED_ALTERNATE_ARCTAN                 "pseudo.arctan"
#define LOCALIZED_ALTERNATE_ARITY                  "pseudo.arity"
#define LOCALIZED_ALTERNATE_ARRAY                  "pseudo.array"
#define LOCALIZED_ALTERNATE_ARRAYP                 "pseudo.arrayp"
#define LOCALIZED_ALTERNATE_ARRAY_                 "pseudo.array?"
#define LOCALIZED_ALTERNATE_ASCII                  "pseudo.ascii"
#define LOCALIZED_ALTERNATE_ASHIFT                 "pseudo.ashift"
#define LOCALIZED_ALTERNATE_BACK                   "pseudo.back"
#define LOCALIZED_ALTERNATE_BACKSLASHEDP           "pseudo.backslashedp"
#define LOCALIZED_ALTERNATE_BACKSLASHED_           "pseudo.backslashed?"
#define LOCALIZED_ALTERNATE_BEFOREP                "pseudo.beforep"
#define LOCALIZED_ALTERNATE_BEFORE_                "pseudo.before?"
#define LOCALIZED_ALTERNATE_BF                     "pseudo.bf"
#define LOCALIZED_ALTERNATE_BFS                    "pseudo.bfs"
#define LOCALIZED_ALTERNATE_BITAND                 "pseudo.bitand"
#define LOCALIZED_ALTERNATE_BITBLOCK               "pseudo.bitblock"
#define LOCALIZED_ALTERNATE_BITCOPY                "pseudo.bitcopy"
#define LOCALIZED_ALTERNATE_BITCUT                 "pseudo.bitcut"
#define LOCALIZED_ALTERNATE_BITFIT                 "pseudo.bitfit"
#define LOCALIZED_ALTERNATE_BITINDEX               "pseudo.bitindex"
#define LOCALIZED_ALTERNATE_BITLOAD                "pseudo.bitload"
#define LOCALIZED_ALTERNATE_BITLOADSIZE            "pseudo.bitloadsize"
#define LOCALIZED_ALTERNATE_BITSIZE                "pseudo.bitsize"
#define LOCALIZED_ALTERNATE_BITMAPTURTLE           "pseudo.bitmapturtle"
#define LOCALIZED_ALTERNATE_BITMODE                "pseudo.bitmode"
#define LOCALIZED_ALTERNATE_BITNOT                 "pseudo.bitnot"
#define LOCALIZED_ALTERNATE_BITOR                  "pseudo.bitor"
#define LOCALIZED_ALTERNATE_BITPASTE               "pseudo.bitpaste"
#define LOCALIZED_ALTERNATE_BITPASTETOINDEX        "pseudo.bitpastetoindex"
#define LOCALIZED_ALTERNATE_BITSAVE                "pseudo.bitsave"
#define LOCALIZED_ALTERNATE_BITXOR                 "pseudo.bitxor"
#define LOCALIZED_ALTERNATE_BK                     "pseudo.bk"
#define LOCALIZED_ALTERNATE_BL                     "pseudo.bl"
#define LOCALIZED_ALTERNATE_BURIED                 "pseudo.buried"
#define LOCALIZED_ALTERNATE_BURY                   "pseudo.bury"
#define LOCALIZED_ALTERNATE_BUTFIRST               "pseudo.butfirst"
#define LOCALIZED_ALTERNATE_BUTFIRSTS              "pseudo.butfirsts"
#define LOCALIZED_ALTERNATE_BUTLAST                "pseudo.butlast"
#define LOCALIZED_ALTERNATE_BUTTONCREATE           "pseudo.buttoncreate"
#define LOCALIZED_ALTERNATE_BUTTONDELETE           "pseudo.buttondelete"
#define LOCALIZED_ALTERNATE_BUTTONENABLE           "pseudo.buttonenable"
#define LOCALIZED_ALTERNATE_BUTTONUPDATE           "pseudo.buttonupdate"
#define LOCALIZED_ALTERNATE_BUTTONP                "pseudo.buttonp"
#define LOCALIZED_ALTERNATE_BUTTON_                "pseudo.button?"
#define LOCALIZED_ALTERNATE_BYE                    "pseudo.bye"
#define LOCALIZED_ALTERNATE_CATCH                  "pseudo.catch"
#define LOCALIZED_ALTERNATE_CHAR                   "pseudo.char"
#define LOCALIZED_ALTERNATE_CHDIR                  "pseudo.chdir"
#define LOCALIZED_ALTERNATE_CHECKBOXCREATE         "pseudo.checkboxcreate"
#define LOCALIZED_ALTERNATE_CHECKBOXDELETE         "pseudo.checkboxdelete"
#define LOCALIZED_ALTERNATE_CHECKBOXENABLE         "pseudo.checkboxenable"
#define LOCALIZED_ALTERNATE_CHECKBOXGET            "pseudo.checkboxget"
#define LOCALIZED_ALTERNATE_CHECKBOXSET            "pseudo.checkboxset"
#define LOCALIZED_ALTERNATE_CLEAN                  "pseudo.clean"
#define LOCALIZED_ALTERNATE_CLEARPALETTE           "pseudo.clearpalette"
#define LOCALIZED_ALTERNATE_CLEARSCREEN            "pseudo.clearscreen"
#define LOCALIZED_ALTERNATE_CLEARTEXT              "pseudo.cleartext"
#define LOCALIZED_ALTERNATE_CLEARTIMER             "pseudo.cleartimer"
#define LOCALIZED_ALTERNATE_CLOSE                  "pseudo.close"
#define LOCALIZED_ALTERNATE_CLOSEALL               "pseudo.closeall"
#define LOCALIZED_ALTERNATE_CO                     "pseudo.co"
#define LOCALIZED_ALTERNATE_COMBOBOXADDSTRING      "pseudo.comboboxaddstring"
#define LOCALIZED_ALTERNATE_COMBOBOXCREATE         "pseudo.comboboxcreate"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETE         "pseudo.comboboxdelete"
#define LOCALIZED_ALTERNATE_COMBOBOXENABLE         "pseudo.comboboxenable"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING   "pseudo.comboboxdeletestring"
#define LOCALIZED_ALTERNATE_COMBOBOXGETTEXT        "pseudo.comboboxgettext"
#define LOCALIZED_ALTERNATE_COMBOBOXSETTEXT        "pseudo.comboboxsettext"
#define LOCALIZED_ALTERNATE_CONTENTS               "pseudo.contents"
#define LOCALIZED_ALTERNATE_CONTINUE               "pseudo.continue"
#define LOCALIZED_ALTERNATE_COPYDEF                "pseudo.copydef"
#define LOCALIZED_ALTERNATE_COS                    "pseudo.cos"
#define LOCALIZED_ALTERNATE_COUNT                  "pseudo.count"
#define LOCALIZED_ALTERNATE_CS                     "pseudo.cs"
#define LOCALIZED_ALTERNATE_CT                     "pseudo.ct"
#define LOCALIZED_ALTERNATE_CURSOR                 "pseudo.cursor"
#define LOCALIZED_ALTERNATE_DEBUGWINDOWS           "pseudo.debugwindows"
#define LOCALIZED_ALTERNATE_DEFINE                 "pseudo.define"
#define LOCALIZED_ALTERNATE_DEFINEDP               "pseudo.definedp"
#define LOCALIZED_ALTERNATE_DEFINED_               "pseudo.defined?"
#define LOCALIZED_ALTERNATE_DIALOGCREATE           "pseudo.dialogcreate"
#define LOCALIZED_ALTERNATE_DIALOGENABLE           "pseudo.dialogenable"
#define LOCALIZED_ALTERNATE_DIALOGDELETE           "pseudo.dialogdelete"
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         "pseudo.dialogfileopen"
#define LOCALIZED_ALTERNATE_DIALOGFILESAVE         "pseudo.dialogfilesave"
#define LOCALIZED_ALTERNATE_DIFFERENCE             "pseudo.difference"
#define LOCALIZED_ALTERNATE_DIRECTORIES            "pseudo.directories"
#define LOCALIZED_ALTERNATE_DLLCALL                "pseudo.dllcall"
#define LOCALIZED_ALTERNATE_DLLFREE                "pseudo.dllfree"
#define LOCALIZED_ALTERNATE_DLLLOAD                "pseudo.dllload"
#define LOCALIZED_ALTERNATE_DOWN                   "pseudo.down"
#define LOCALIZED_ALTERNATE_DOWNPITCH              "pseudo.downpitch"
#define LOCALIZED_ALTERNATE_DRIBBLE                "pseudo.dribble"
#define LOCALIZED_ALTERNATE_ED                     "pseudo.ed"
#define LOCALIZED_ALTERNATE_EDIT                   "pseudo.edit"
#define LOCALIZED_ALTERNATE_ELLIPSEARC             "pseudo.ellipsearc"
#define LOCALIZED_ALTERNATE_EMPTYP                 "pseudo.emptyp"
#define LOCALIZED_ALTERNATE_EMPTY_                 "pseudo.empty?"
#define LOCALIZED_ALTERNATE_EOFP                   "pseudo.eofp"
#define LOCALIZED_ALTERNATE_EOF_                   "pseudo.eof?"
#define LOCALIZED_ALTERNATE_EQUALP                 "pseudo.equalp"
#define LOCALIZED_ALTERNATE_EQUAL_                 "pseudo.equal?"
#define LOCALIZED_ALTERNATE_ER                     "pseudo.er"
#define LOCALIZED_ALTERNATE_ERASE                  "pseudo.erase"
#define LOCALIZED_ALTERNATE_ERASEFILE              "pseudo.erasefile"
#define LOCALIZED_ALTERNATE_ERF                    "pseudo.erf"
#define LOCALIZED_ALTERNATE_ERROR                  "pseudo.error"
#define LOCALIZED_ALTERNATE_EVENTCHECK             "pseudo.eventcheck"
#define LOCALIZED_ALTERNATE_EXP                    "pseudo.exp"
#define LOCALIZED_ALTERNATE_FD                     "pseudo.fd"
#define LOCALIZED_ALTERNATE_FENCE                  "pseudo.fence"
#define LOCALIZED_ALTERNATE_FILL                   "pseudo.fill"
#define LOCALIZED_ALTERNATE_FILES                  "pseudo.files"
#define LOCALIZED_ALTERNATE_FIRST                  "pseudo.first"
#define LOCALIZED_ALTERNATE_FIRSTS                 "pseudo.firsts"
#define LOCALIZED_ALTERNATE_FLOODCOLOR             "pseudo.floodcolor"
#define LOCALIZED_ALTERNATE_FONTFACENAMES          "pseudo.fontfacenames"
#define LOCALIZED_ALTERNATE_FOREVER                "pseudo.forever"
#define LOCALIZED_ALTERNATE_FORM                   "pseudo.form"
#define LOCALIZED_ALTERNATE_FORWARD                "pseudo.forward"
#define LOCALIZED_ALTERNATE_FPUT                   "pseudo.fput"
#define LOCALIZED_ALTERNATE_FS                     "pseudo.fs"
#define LOCALIZED_ALTERNATE_FULLSCREEN             "pseudo.fullscreen"
#define LOCALIZED_ALTERNATE_FULLTEXT               "pseudo.fulltext"
#define LOCALIZED_ALTERNATE_GETFOCUS               "pseudo.getfocus"
#define LOCALIZED_ALTERNATE_GOTO                   "pseudo.goto"
#define LOCALIZED_ALTERNATE_GIFLOAD                "pseudo.gifload"
#define LOCALIZED_ALTERNATE_GIFSIZE                "pseudo.gifsize"
#define LOCALIZED_ALTERNATE_GIFSAVE                "pseudo.gifsave"
#define LOCALIZED_ALTERNATE_GPROP                  "pseudo.gprop"
#define LOCALIZED_ALTERNATE_GREATEREQUALP          "pseudo.greaterequalp"
#define LOCALIZED_ALTERNATE_GREATEREQUAL_          "pseudo.greaterequal?"
#define LOCALIZED_ALTERNATE_GREATERP               "pseudo.greaterp"
#define LOCALIZED_ALTERNATE_GREATER_               "pseudo.greater?"
#define LOCALIZED_ALTERNATE_GROUPBOXCREATE         "pseudo.groupboxcreate"
#define LOCALIZED_ALTERNATE_GROUPBOXDELETE         "pseudo.groupboxdelete"
#define LOCALIZED_ALTERNATE_HALT                   "pseudo.halt"
#define LOCALIZED_ALTERNATE_HASOWNPENP             "pseudo.hasownpenp"
#define LOCALIZED_ALTERNATE_HASOWNPEN_             "pseudo.hasownpen?"
#define LOCALIZED_ALTERNATE_HEADING                "pseudo.heading"
#define LOCALIZED_ALTERNATE_HELP                   "pseudo.help"
#define LOCALIZED_ALTERNATE_HIDETURTLE             "pseudo.hideturtle"
#define LOCALIZED_ALTERNATE_HOME                   "pseudo.home"
#define LOCALIZED_ALTERNATE_HT                     "pseudo.ht"
#define LOCALIZED_ALTERNATE_IF                     "pseudo.if"
#define LOCALIZED_ALTERNATE_IFELSE                 "pseudo.ifelse"
#define LOCALIZED_ALTERNATE_IFF                    "pseudo.iff"
#define LOCALIZED_ALTERNATE_IFFALSE                "pseudo.iffalse"
#define LOCALIZED_ALTERNATE_IFT                    "pseudo.ift"
#define LOCALIZED_ALTERNATE_IFTRUE                 "pseudo.iftrue"
#define LOCALIZED_ALTERNATE_INGAMEPORT             "pseudo.ingameport"
#define LOCALIZED_ALTERNATE_INPORT                 "pseudo.inport"
#define LOCALIZED_ALTERNATE_INPORTB                "pseudo.inportb"
#define LOCALIZED_ALTERNATE_INT                    "pseudo.int"
#define LOCALIZED_ALTERNATE_ITEM                   "pseudo.item"
#define LOCALIZED_ALTERNATE_KEYBOARDOFF            "pseudo.keyboardoff"
#define LOCALIZED_ALTERNATE_KEYBOARDON             "pseudo.keyboardon"
#define LOCALIZED_ALTERNATE_KEYBOARDVALUE          "pseudo.keyboardvalue"
#define LOCALIZED_ALTERNATE_KEYP                   "pseudo.keyp"
#define LOCALIZED_ALTERNATE_KEY_                   "pseudo.key?"
#define LOCALIZED_ALTERNATE_LABEL                  "pseudo.label"
#define LOCALIZED_ALTERNATE_LABELFONT              "pseudo.labelfont"
#define LOCALIZED_ALTERNATE_LABELSIZE              "pseudo.labelsize"
#define LOCALIZED_ALTERNATE_LAST                   "pseudo.last"
#define LOCALIZED_ALTERNATE_LEFT                   "pseudo.left"
#define LOCALIZED_ALTERNATE_LEFTROLL               "pseudo.leftroll"
#define LOCALIZED_ALTERNATE_LESSEQUALP             "pseudo.lessequalp"
#define LOCALIZED_ALTERNATE_LESSEQUAL_             "pseudo.lessequal?"
#define LOCALIZED_ALTERNATE_LESSP                  "pseudo.lessp"
#define LOCALIZED_ALTERNATE_LESS_                  "pseudo.less?"
#define LOCALIZED_ALTERNATE_LIGHT                  "pseudo.light"
#define LOCALIZED_ALTERNATE_LIST                   "pseudo.list"
#define LOCALIZED_ALTERNATE_LISTBOXADDSTRING       "pseudo.listboxaddstring"
#define LOCALIZED_ALTERNATE_LISTBOXCREATE          "pseudo.listboxcreate"
#define LOCALIZED_ALTERNATE_LISTBOXENABLE          "pseudo.listboxenable"
#define LOCALIZED_ALTERNATE_LISTBOXDELETE          "pseudo.listboxdelete"
#define LOCALIZED_ALTERNATE_LISTBOXDELETESTRING    "pseudo.listboxdeletestring"
#define LOCALIZED_ALTERNATE_LISTBOXGETSELECT       "pseudo.listboxgetselect"
#define LOCALIZED_ALTERNATE_LISTP                  "pseudo.listp"
#define LOCALIZED_ALTERNATE_LIST_                  "pseudo.list?"
#define LOCALIZED_ALTERNATE_LN                     "pseudo.ln"
#define LOCALIZED_ALTERNATE_LOAD                   "pseudo.load"
#define LOCALIZED_ALTERNATE_LOCAL                  "pseudo.local"
#define LOCALIZED_ALTERNATE_LOG10                  "pseudo.log10"
#define LOCALIZED_ALTERNATE_LOGOVERSION            "pseudo.logoversion"
#define LOCALIZED_ALTERNATE_LOWERCASE              "pseudo.lowercase"
#define LOCALIZED_ALTERNATE_LPUT                   "pseudo.lput"
#define LOCALIZED_ALTERNATE_LR                     "pseudo.lr"
#define LOCALIZED_ALTERNATE_LSHIFT                 "pseudo.lshift"
#define LOCALIZED_ALTERNATE_LT                     "pseudo.lt"
#define LOCALIZED_ALTERNATE_MACHINE                "pseudo.machine"
#define LOCALIZED_ALTERNATE_MACROP                 "pseudo.macrop"
#define LOCALIZED_ALTERNATE_MACRO_                 "pseudo.macro?"
#define LOCALIZED_ALTERNATE_MAKE                   "pseudo.Make"
#define LOCALIZED_ALTERNATE_MCI                    "pseudo.mci"
#define LOCALIZED_ALTERNATE_MEMBER                 "pseudo.member"
#define LOCALIZED_ALTERNATE_MEMBERP                "pseudo.memberp"
#define LOCALIZED_ALTERNATE_MEMBER_                "pseudo.member?"
#define LOCALIZED_ALTERNATE_MESSAGEBOX             "pseudo.messagebox"
#define LOCALIZED_ALTERNATE_MIDICLOSE              "pseudo.midiclose"
#define LOCALIZED_ALTERNATE_MIDIMESSAGE            "pseudo.midimessage"
#define LOCALIZED_ALTERNATE_MIDIOPEN               "pseudo.midiopen"
#define LOCALIZED_ALTERNATE_MINUS                  "pseudo.minus"
#define LOCALIZED_ALTERNATE_MKDIR                  "pseudo.mkdir"
#define LOCALIZED_ALTERNATE_MODULO                 "pseudo.modulo"
#define LOCALIZED_ALTERNATE_MOUSEOFF               "pseudo.mouseoff"
#define LOCALIZED_ALTERNATE_MOUSEON                "pseudo.mouseon"
#define LOCALIZED_ALTERNATE_MOUSEPOS               "pseudo.mousepos"
#define LOCALIZED_ALTERNATE_NAMEP                  "pseudo.namep"
#define LOCALIZED_ALTERNATE_NAME_                  "pseudo.name?"
#define LOCALIZED_ALTERNATE_NAMES                  "pseudo.names"
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           "pseudo.netacceptoff"
#define LOCALIZED_ALTERNATE_NETACCEPTON            "pseudo.netaccepton"
#define LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE  "pseudo.netacceptreceivevalue"
#define LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE     "pseudo.netacceptsendvalue"
#define LOCALIZED_ALTERNATE_NETCONNECTOFF          "pseudo.netconnectoff"
#define LOCALIZED_ALTERNATE_NETCONNECTON           "pseudo.netconnecton"
#define LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE "pseudo.netconnectreceivevalue"
#define LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE    "pseudo.netconnectsendvalue"
#define LOCALIZED_ALTERNATE_NETSHUTDOWN            "pseudo.netshutdown"
#define LOCALIZED_ALTERNATE_NETSTARTUP             "pseudo.netstartup"
#define LOCALIZED_ALTERNATE_NOBITMAPTURTLE         "pseudo.nobitmapturtle"
#define LOCALIZED_ALTERNATE_NODES                  "pseudo.nodes"
#define LOCALIZED_ALTERNATE_NODRIBBLE              "pseudo.nodribble"
#define LOCALIZED_ALTERNATE_NOSTATUS               "pseudo.nostatus"
#define LOCALIZED_ALTERNATE_NOT                    "pseudo.not"
#define LOCALIZED_ALTERNATE_NOTEQUALP              "pseudo.notequalp"
#define LOCALIZED_ALTERNATE_NOTEQUAL_              "pseudo.notequal?"
#define LOCALIZED_ALTERNATE_NOYIELD                "pseudo.noyield"
#define LOCALIZED_ALTERNATE_NUMBERP                "pseudo.numberp"
#define LOCALIZED_ALTERNATE_NUMBER_                "pseudo.number?"
#define LOCALIZED_ALTERNATE_OP                     "pseudo.op"
#define LOCALIZED_ALTERNATE_OPENAPPEND             "pseudo.openappend"
#define LOCALIZED_ALTERNATE_OPENREAD               "pseudo.openread"
#define LOCALIZED_ALTERNATE_OPENUPDATE             "pseudo.openupdate"
#define LOCALIZED_ALTERNATE_OPENWRITE              "pseudo.openwrite"
#define LOCALIZED_ALTERNATE_OR                     "pseudo.or"
#define LOCALIZED_ALTERNATE_OUTPORT                "pseudo.outport"
#define LOCALIZED_ALTERNATE_OUTPORTB               "pseudo.outportb"
#define LOCALIZED_ALTERNATE_OUTPUT                 "pseudo.output"
#define LOCALIZED_ALTERNATE_PARSE                  "pseudo.parse"
#define LOCALIZED_ALTERNATE_PAUSE                  "pseudo.pause"
#define LOCALIZED_ALTERNATE_PC                     "pseudo.pc"
#define LOCALIZED_ALTERNATE_PD                     "pseudo.pd"
#define LOCALIZED_ALTERNATE_PE                     "pseudo.pe"
#define LOCALIZED_ALTERNATE_PENCOLOR               "pseudo.pencolor"
#define LOCALIZED_ALTERNATE_PENDOWN                "pseudo.pendown"
#define LOCALIZED_ALTERNATE_PENDOWNP               "pseudo.pendownp"
#define LOCALIZED_ALTERNATE_PENDOWN_               "pseudo.pendown?"
#define LOCALIZED_ALTERNATE_PENERASE               "pseudo.penerase"
#define LOCALIZED_ALTERNATE_PENMODE                "pseudo.penmode"
#define LOCALIZED_ALTERNATE_PENPAINT               "pseudo.penpaint"
#define LOCALIZED_ALTERNATE_PENPATTERN             "pseudo.penpattern"
#define LOCALIZED_ALTERNATE_PENREVERSE             "pseudo.penreverse"
#define LOCALIZED_ALTERNATE_PENSIZE                "pseudo.pensize"
#define LOCALIZED_ALTERNATE_PENUP                  "pseudo.penup"
#define LOCALIZED_ALTERNATE_PERSPECTIVE            "pseudo.perspective"
#define LOCALIZED_ALTERNATE_PITCH                  "pseudo.pitch"
#define LOCALIZED_ALTERNATE_PIXEL                  "pseudo.pixel"
#define LOCALIZED_ALTERNATE_PLAYWAVE               "pseudo.playwave"
#define LOCALIZED_ALTERNATE_PLIST                  "pseudo.Plist"
#define LOCALIZED_ALTERNATE_PLISTS                 "pseudo.plists"
#define LOCALIZED_ALTERNATE_PO                     "pseudo.po"
#define LOCALIZED_ALTERNATE_POPDIR                 "pseudo.popdir"
#define LOCALIZED_ALTERNATE_POLYSTART              "pseudo.polystart"
#define LOCALIZED_ALTERNATE_POLYEND                "pseudo.polyend"
#define LOCALIZED_ALTERNATE_POLYVIEW               "pseudo.polyview"
#define LOCALIZED_ALTERNATE_PORTCLOSE              "pseudo.portclose"
#define LOCALIZED_ALTERNATE_PORTFLUSH              "pseudo.portflush"
#define LOCALIZED_ALTERNATE_PORTMODE               "pseudo.portmode"
#define LOCALIZED_ALTERNATE_PORTOPEN               "pseudo.portopen"
#define LOCALIZED_ALTERNATE_PORTREADARRAY          "pseudo.portreadarray"
#define LOCALIZED_ALTERNATE_PORTREADCHAR           "pseudo.portreadchar"
#define LOCALIZED_ALTERNATE_PORTWRITEARRAY         "pseudo.portwritearray"
#define LOCALIZED_ALTERNATE_PORTWRITECHAR          "pseudo.portwritechar"
#define LOCALIZED_ALTERNATE_POS                    "pseudo.pos"
#define LOCALIZED_ALTERNATE_POSXYZ                 "pseudo.posxyz"
#define LOCALIZED_ALTERNATE_POT                    "pseudo.pot"
#define LOCALIZED_ALTERNATE_POWER                  "pseudo.power"
#define LOCALIZED_ALTERNATE_PPROP                  "pseudo.Pprop"
#define LOCALIZED_ALTERNATE_PPT                    "pseudo.ppt"
#define LOCALIZED_ALTERNATE_PR                     "pseudo.pr"
#define LOCALIZED_ALTERNATE_PRIMITIVEP             "pseudo.primitivep"
#define LOCALIZED_ALTERNATE_PRIMITIVE_             "pseudo.primitive?"
#define LOCALIZED_ALTERNATE_PRINT                  "pseudo.print"
#define LOCALIZED_ALTERNATE_PROCEDUREP             "pseudo.procedurep"
#define LOCALIZED_ALTERNATE_PROCEDURE_             "pseudo.procedure?"
#define LOCALIZED_ALTERNATE_PROPLISTP              "pseudo.proplistp"
#define LOCALIZED_ALTERNATE_PROPLIST_              "pseudo.proplist?"
#define LOCALIZED_ALTERNATE_PROCEDURES             "pseudo.procedures"
#define LOCALIZED_ALTERNATE_PRODUCT                "pseudo.product"
#define LOCALIZED_ALTERNATE_PU                     "pseudo.pu"
#define LOCALIZED_ALTERNATE_PX                     "pseudo.px"
#define LOCALIZED_ALTERNATE_QUESTIONBOX            "pseudo.questionbox"
#define LOCALIZED_ALTERNATE_QUOTIENT               "pseudo.quotient"
#define LOCALIZED_ALTERNATE_RADARCCOS              "pseudo.radarccos"
#define LOCALIZED_ALTERNATE_RADARCSIN              "pseudo.radarcsin"
#define LOCALIZED_ALTERNATE_RADARCTAN              "pseudo.radarctan"
#define LOCALIZED_ALTERNATE_RADCOS                 "pseudo.radcos"
#define LOCALIZED_ALTERNATE_RADIOBUTTONCREATE      "pseudo.radiobuttoncreate"
#define LOCALIZED_ALTERNATE_RADIOBUTTONENABLE      "pseudo.radiobuttonenable"
#define LOCALIZED_ALTERNATE_RADIOBUTTONDELETE      "pseudo.radiobuttondelete"
#define LOCALIZED_ALTERNATE_RADIOBUTTONGET         "pseudo.radiobuttonget"
#define LOCALIZED_ALTERNATE_RADIOBUTTONSET         "pseudo.radiobuttonset"
#define LOCALIZED_ALTERNATE_RADSIN                 "pseudo.radsin"
#define LOCALIZED_ALTERNATE_RADTAN                 "pseudo.radtan"
#define LOCALIZED_ALTERNATE_RANDOM                 "pseudo.random"
#define LOCALIZED_ALTERNATE_RAWASCII               "pseudo.rawascii"
#define LOCALIZED_ALTERNATE_RC                     "pseudo.rc"
#define LOCALIZED_ALTERNATE_RCS                    "pseudo.rcs"
#define LOCALIZED_ALTERNATE_READCHAR               "pseudo.readchar"
#define LOCALIZED_ALTERNATE_READCHARS              "pseudo.readchars"
#define LOCALIZED_ALTERNATE_READER                 "pseudo.reader"
#define LOCALIZED_ALTERNATE_READLIST               "pseudo.readlist"
#define LOCALIZED_ALTERNATE_READPOS                "pseudo.readpos"
#define LOCALIZED_ALTERNATE_READRAWLINE            "pseudo.readrawline"
#define LOCALIZED_ALTERNATE_READWORD               "pseudo.readword"
#define LOCALIZED_ALTERNATE_REMAINDER              "pseudo.remainder"
#define LOCALIZED_ALTERNATE_REMPROP                "pseudo.remprop"
#define LOCALIZED_ALTERNATE_REPCOUNT               "pseudo.repcount"
#define LOCALIZED_ALTERNATE_REPEAT                 "pseudo.repeat"
#define LOCALIZED_ALTERNATE_RERANDOM               "pseudo.rerandom"
#define LOCALIZED_ALTERNATE_RIGHT                  "pseudo.right"
#define LOCALIZED_ALTERNATE_RIGHTROLL              "pseudo.rightroll"
#define LOCALIZED_ALTERNATE_RL                     "pseudo.rl"
#define LOCALIZED_ALTERNATE_RMDIR                  "pseudo.rmdir"
#define LOCALIZED_ALTERNATE_ROLL                   "pseudo.roll"
#define LOCALIZED_ALTERNATE_ROUND                  "pseudo.round"
#define LOCALIZED_ALTERNATE_RR                     "pseudo.rr"
#define LOCALIZED_ALTERNATE_RT                     "pseudo.rt"
#define LOCALIZED_ALTERNATE_RUN                    "pseudo.run"
#define LOCALIZED_ALTERNATE_RUNPARSE               "pseudo.runparse"
#define LOCALIZED_ALTERNATE_RUNRESULT              "pseudo.runresult"
#define LOCALIZED_ALTERNATE_RW                     "pseudo.rw"
#define LOCALIZED_ALTERNATE_SAVE                   "pseudo.save"
#define LOCALIZED_ALTERNATE_SCREENCOLOR            "pseudo.screencolor"
#define LOCALIZED_ALTERNATE_SCROLLBARCREATE        "pseudo.scrollbarcreate"
#define LOCALIZED_ALTERNATE_SCROLLBARENABLE        "pseudo.scrollbarenable"
#define LOCALIZED_ALTERNATE_SCROLLBARDELETE        "pseudo.scrollbardelete"
#define LOCALIZED_ALTERNATE_SCROLLBARGET           "pseudo.scrollbarget"
#define LOCALIZED_ALTERNATE_SCROLLBARSET           "pseudo.scrollbarset"
#define LOCALIZED_ALTERNATE_SCROLLX                "pseudo.scrollx"
#define LOCALIZED_ALTERNATE_SCROLLY                "pseudo.scrolly"
#define LOCALIZED_ALTERNATE_SCRUNCH                "pseudo.scrunch"
#define LOCALIZED_ALTERNATE_SE                     "pseudo.se"
#define LOCALIZED_ALTERNATE_SELECTBOX              "pseudo.selectbox"
#define LOCALIZED_ALTERNATE_SENTENCE               "pseudo.sentence"
#define LOCALIZED_ALTERNATE_SETACTIVEAREA          "pseudo.setactivearea"
#define LOCALIZED_ALTERNATE_SETBITINDEX            "pseudo.setbitindex"
#define LOCALIZED_ALTERNATE_SETBITMODE             "pseudo.setbitmode"
#define LOCALIZED_ALTERNATE_SETCLIP                "pseudo.setclip"
#define LOCALIZED_ALTERNATE_SETCURSOR              "pseudo.setcursor"
#define LOCALIZED_ALTERNATE_SETCURSORNOWAIT        "pseudo.setcursornowait"
#define LOCALIZED_ALTERNATE_SETCURSORWAIT          "pseudo.setcursorwait"
#define LOCALIZED_ALTERNATE_SETFC                  "pseudo.setfc"
#define LOCALIZED_ALTERNATE_SETFLOODCOLOR          "pseudo.setfloodcolor"
#define LOCALIZED_ALTERNATE_SETFOCUS               "pseudo.setfocus"
#define LOCALIZED_ALTERNATE_SETH                   "pseudo.seth"
#define LOCALIZED_ALTERNATE_SETHEADING             "pseudo.setheading"
#define LOCALIZED_ALTERNATE_SETITEM                "pseudo.setitem"
#define LOCALIZED_ALTERNATE_SETLABELFONT           "pseudo.setlabelfont"
#define LOCALIZED_ALTERNATE_SETLIGHT               "pseudo.setlight"
#define LOCALIZED_ALTERNATE_SETMARGINS             "pseudo.setmargins"
#define LOCALIZED_ALTERNATE_SETPC                  "pseudo.setpc"
#define LOCALIZED_ALTERNATE_SETPENCOLOR            "pseudo.setpencolor"
#define LOCALIZED_ALTERNATE_SETPENPATTERN          "pseudo.setpenpattern"
#define LOCALIZED_ALTERNATE_SETPENSIZE             "pseudo.setpensize"
#define LOCALIZED_ALTERNATE_SETPITCH               "pseudo.setpitch"
#define LOCALIZED_ALTERNATE_SETPIXEL               "pseudo.setpixel"
#define LOCALIZED_ALTERNATE_SETPOS                 "pseudo.setpos"
#define LOCALIZED_ALTERNATE_SETPOSXYZ              "pseudo.setposxyz"
#define LOCALIZED_ALTERNATE_SETREAD                "pseudo.setread"
#define LOCALIZED_ALTERNATE_SETREADPOS             "pseudo.setreadpos"
#define LOCALIZED_ALTERNATE_SETROLL                "pseudo.setroll"
#define LOCALIZED_ALTERNATE_SETSC                  "pseudo.setsc"
#define LOCALIZED_ALTERNATE_SETSCREENCOLOR         "pseudo.setscreencolor"
#define LOCALIZED_ALTERNATE_SETSCRUNCH             "pseudo.setscrunch"
#define LOCALIZED_ALTERNATE_SETTIMER               "pseudo.settimer"
#define LOCALIZED_ALTERNATE_SETTURTLE              "pseudo.setturtle"
#define LOCALIZED_ALTERNATE_SETTURTLEMODE          "pseudo.setturtlemode"
#define LOCALIZED_ALTERNATE_SETWRITE               "pseudo.setwrite"
#define LOCALIZED_ALTERNATE_SETWRITEPOS            "pseudo.setwritepos"
#define LOCALIZED_ALTERNATE_SETX                   "pseudo.setx"
#define LOCALIZED_ALTERNATE_SETXY                  "pseudo.setxy"
#define LOCALIZED_ALTERNATE_SETXYZ                 "pseudo.setxyz"
#define LOCALIZED_ALTERNATE_SETY                   "pseudo.sety"
#define LOCALIZED_ALTERNATE_SETZ                   "pseudo.setz"
#define LOCALIZED_ALTERNATE_SHELL                  "pseudo.shell"
#define LOCALIZED_ALTERNATE_SHOW                   "pseudo.show"
#define LOCALIZED_ALTERNATE_SHOWNP                 "pseudo.shownp"
#define LOCALIZED_ALTERNATE_SHOWN_                 "pseudo.shown?"
#define LOCALIZED_ALTERNATE_SHOWTURTLE             "pseudo.showturtle"
#define LOCALIZED_ALTERNATE_SIN                    "pseudo.sin"
#define LOCALIZED_ALTERNATE_SOUND                  "pseudo.sound"
#define LOCALIZED_ALTERNATE_SPLITSCREEN            "pseudo.splitscreen"
#define LOCALIZED_ALTERNATE_SQRT                   "pseudo.sqrt"
#define LOCALIZED_ALTERNATE_SS                     "pseudo.ss"
#define LOCALIZED_ALTERNATE_ST                     "pseudo.st"
#define LOCALIZED_ALTERNATE_STANDOUT               "pseudo.standout"
#define LOCALIZED_ALTERNATE_STATICCREATE           "pseudo.staticcreate"
#define LOCALIZED_ALTERNATE_STATICDELETE           "pseudo.staticdelete"
#define LOCALIZED_ALTERNATE_STATICUPDATE           "pseudo.staticupdate"
#define LOCALIZED_ALTERNATE_STATUS                 "pseudo.status"
#define LOCALIZED_ALTERNATE_STEP                   "pseudo.step"
#define LOCALIZED_ALTERNATE_STEPPED                "pseudo.stepped"
#define LOCALIZED_ALTERNATE_STOP                   "pseudo.stop"
#define LOCALIZED_ALTERNATE_SUBSTRINGP             "pseudo.substringp"
#define LOCALIZED_ALTERNATE_SUBSTRING_             "pseudo.substring?"
#define LOCALIZED_ALTERNATE_SUM                    "pseudo.sum"
#define LOCALIZED_ALTERNATE_TAG                    "pseudo.tag"
#define LOCALIZED_ALTERNATE_TAN                    "pseudo.tan"
#define LOCALIZED_ALTERNATE_TEST                   "pseudo.test"
#define LOCALIZED_ALTERNATE_TEXT                   "pseudo.text"
#define LOCALIZED_ALTERNATE_TEXTSCREEN             "pseudo.textscreen"
#define LOCALIZED_ALTERNATE_THING                  "pseudo.thing"
#define LOCALIZED_ALTERNATE_THROW                  "pseudo.throw"
#define LOCALIZED_ALTERNATE_TIME                   "pseudo.time"
#define LOCALIZED_ALTERNATE_TIMEMILLI              "pseudo.timemilli"
#define LOCALIZED_ALTERNATE_TO                     "pseudo.to"
#define LOCALIZED_ALTERNATE_TONE                   "pseudo.tone"
#define LOCALIZED_ALTERNATE_TOWARDS                "pseudo.towards"
#define LOCALIZED_ALTERNATE_TOWARDSXYZ             "pseudo.towardsxyz"
#define LOCALIZED_ALTERNATE_TRACE                  "pseudo.trace"
#define LOCALIZED_ALTERNATE_TRACED                 "pseudo.traced"
#define LOCALIZED_ALTERNATE_TS                     "pseudo.ts"
#define LOCALIZED_ALTERNATE_TURTLE                 "pseudo.turtle"
#define LOCALIZED_ALTERNATE_TURTLEMODE             "pseudo.turtlemode"
#define LOCALIZED_ALTERNATE_TURTLES                "pseudo.turtles"
#define LOCALIZED_ALTERNATE_TYPE                   "pseudo.type"
#define LOCALIZED_ALTERNATE_UNBURY                 "pseudo.unbury"
#define LOCALIZED_ALTERNATE_UNSTEP                 "pseudo.unstep"
#define LOCALIZED_ALTERNATE_UNTRACE                "pseudo.untrace"
#define LOCALIZED_ALTERNATE_UP                     "pseudo.up"
#define LOCALIZED_ALTERNATE_UPPERCASE              "pseudo.uppercase"
#define LOCALIZED_ALTERNATE_UPPITCH                "pseudo.uppitch"
#define LOCALIZED_ALTERNATE_WAIT                   "pseudo.wait"
#define LOCALIZED_ALTERNATE_WINDOW                 "pseudo.window"
#define LOCALIZED_ALTERNATE_WINDOWCREATE           "pseudo.windowcreate"
#define LOCALIZED_ALTERNATE_WINDOWENABLE           "pseudo.windowenable"
#define LOCALIZED_ALTERNATE_WINDOWDELETE           "pseudo.windowdelete"
#define LOCALIZED_ALTERNATE_WINDOWFILEEDIT         "pseudo.windowfileedit"
#define LOCALIZED_ALTERNATE_WINDOWSET              "pseudo.windowset"
#define LOCALIZED_ALTERNATE_WINHELP                "pseudo.winhelp"
#define LOCALIZED_ALTERNATE_WORD                   "pseudo.word"
#define LOCALIZED_ALTERNATE_WORDP                  "pseudo.wordp"
#define LOCALIZED_ALTERNATE_WORD_                  "pseudo.word?"
#define LOCALIZED_ALTERNATE_WRAP                   "pseudo.wrap"
#define LOCALIZED_ALTERNATE_WRITEPOS               "pseudo.writepos"
#define LOCALIZED_ALTERNATE_WRITER                 "pseudo.writer"
#define LOCALIZED_ALTERNATE_YESNOBOX               "pseudo.yesnobox"
#define LOCALIZED_ALTERNATE_YIELD                  "pseudo.yield"
#define LOCALIZED_ALTERNATE_ZOOM                   "pseudo.zoom"

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      "pseudo.OK"
#define LOCALIZED_GENERAL_CANCELBUTTON  "pseudo.Cancel"
#define LOCALIZED_GENERAL_APPLYBUTTON   "pseudo.&Apply"

#define LOCALIZED_GENERAL_PRODUCTNAME   "pseudo.FMSLogo"

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  "pseudo.The FMSLogo programming environment"

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  "pseudo.&File"
#define LOCALIZED_FILE_NEW              "pseudo.&New\t(erase workspace)"
#define LOCALIZED_FILE_LOAD             "pseudo.&Load...\t(merge into workspace)"
#define LOCALIZED_FILE_OPEN             "pseudo.&Open...\t(replace workspace)" 
#define LOCALIZED_FILE_SAVE             "pseudo.&Save" 
#define LOCALIZED_FILE_SAVEAS           "pseudo.Save &As..."
#define LOCALIZED_FILE_SETASSCREENSAVER "pseudo.Se&t As Screen Saver"
#define LOCALIZED_FILE_EDIT             "pseudo.&Edit..."
#define LOCALIZED_FILE_ERASE            "pseudo.E&rase..."
#define LOCALIZED_FILE_EXIT             "pseudo.E&xit"

#define LOCALIZED_BITMAP               "pseudo.&Bitmap"
#define LOCALIZED_BITMAP_NEW           "pseudo.&New"
#define LOCALIZED_BITMAP_LOAD          "pseudo.&Load..."
#define LOCALIZED_BITMAP_SAVE          "pseudo.&Save"
#define LOCALIZED_BITMAP_SAVEAS        "pseudo.Save &As..."
#define LOCALIZED_BITMAP_PRINT         "pseudo.&Print..."
#define LOCALIZED_BITMAP_PRINTERSETUP  "pseudo.P&rinter Setup..."
#define LOCALIZED_BITMAP_ACTIVEAREA    "pseudo.A&ctive Area..."

#define LOCALIZED_SET                  "pseudo.&Set"
#define LOCALIZED_SET_PENSIZE          "pseudo.Pen Si&ze..."
#define LOCALIZED_SET_LABELFONT        "pseudo.&Label Font..."
#define LOCALIZED_SET_COMMANDERFONT    "pseudo.&Commander Font..."
#define LOCALIZED_SET_PENCOLOR         "pseudo.&Pen Color..."
#define LOCALIZED_SET_FLOODCOLOR       "pseudo.F&lood Color..."
#define LOCALIZED_SET_SCREENCOLOR      "pseudo.&Screen Color..."

#define LOCALIZED_ZOOM                 "pseudo.&Zoom" 
#define LOCALIZED_ZOOM_IN              "pseudo.&In"
#define LOCALIZED_ZOOM_OUT             "pseudo.&Out"
#define LOCALIZED_ZOOM_NORMAL          "pseudo.&Normal"

#define LOCALIZED_HELP                 "pseudo.&Help" 
#define LOCALIZED_HELP_INDEX           "pseudo.&Index"
#define LOCALIZED_HELP_TUTORIAL        "pseudo.&Tutorial"
#define LOCALIZED_HELP_DEMO            "pseudo.&Demo" 
#define LOCALIZED_HELP_EXAMPLE         "pseudo.&Examples"
#define LOCALIZED_HELP_RELEASENOTES    "pseudo.&Release Notes"
#define LOCALIZED_HELP_ABOUTFMSLOGO    "pseudo.&About "LOCALIZED_GENERAL_PRODUCTNAME"..."
#define LOCALIZED_HELP_MS              "pseudo.&About MS..."
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   "pseudo.LANGUAGE to English"
#define LOCALIZED_HELP_ENGLISHTOLANG   "pseudo.English to LANGUAGE"

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              "pseudo.Select Active Area"
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       "pseudo.These affect Printing and Saving Bitmaps"
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        "pseudo.Y-High"
#define LOCALIZED_SELECTACTIVEAREA_YLOW         "pseudo.Y-Low" 
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        "pseudo.X-High"
#define LOCALIZED_SELECTACTIVEAREA_XLOW         "pseudo.X-Low"
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH "pseudo.Turtle steps per inch printed:"
#define LOCALIZED_SELECTACTIVEAREA_RESET        "pseudo.&Reset" 
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON

// The screensaver strings
#define LOCALIZED_SCREENSAVER_NAME              LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_SCREENSAVER_DESCRIPTION       "pseudo.FMSLogo Screensaver"
#define LOCALIZED_SCREENSAVER_SETTINGS_TITLE    "pseudo.FMSLogo Screensaver Settings"
#define LOCALIZED_SCREENSAVER_LOCATE            "pseudo.&Locate ..." 
#define LOCALIZED_SCREENSAVER_FILE              "pseudo.Logo &File:" 
#define LOCALIZED_SCREENSAVER_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SCREENSAVER_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON

// The dialog box for selecting a Startup procedure
#define LOCALIZED_SELECTSTARTUP_CAPTION               "pseudo.Select a " LOCALIZED_ALTERNATE_STARTUP " instruction"
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED "pseudo.Your workspace does not have a " LOCALIZED_ALTERNATE_STARTUP " instruction list defined, so nothing\nwill happen when the screensaver is loaded.\nPlease select a procedure to run when the program is loaded."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST   "pseudo.The " LOCALIZED_ALTERNATE_STARTUP " variable is not a list, so nothing will happen when the screensaver\nis loaded.\nPlease select a procedure to run when the program is loaded."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY     "pseudo.Your workspace has an empty " LOCALIZED_ALTERNATE_STARTUP " instruction list defined, so nothing will\nhappen when the screensaver is loaded.\nPlease select a procedure to run when the program is loaded."
#define LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED   "pseudo.No procedures are defined"

// The warning dialog box when the user saves an empty workspace
#define LOCALIZED_EMPTYWORKSPACE_TITLE                LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_EMPTYWORKSPACE_MESSAGE              "pseudo.There are no procedures, variables, or property lists defined,\nso the workspace will be saved as an empty file.\n\nDo you want to save the workspace anyway?"

//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     "pseudo.Copy"
#define LOCALIZED_POPUP_CUT                      "pseudo.Cut"
#define LOCALIZED_POPUP_PASTE                    "pseudo.Paste"
#define LOCALIZED_POPUP_DELETE                   "pseudo.Delete"
#define LOCALIZED_POPUP_UNDO                     "pseudo.Undo"
#define LOCALIZED_POPUP_REDO                     "pseudo.Redo"
#define LOCALIZED_POPUP_SELECTALL                "pseudo.Select All"
#define LOCALIZED_POPUP_HELP                     "pseudo.Topic Search"
#define LOCALIZED_POPUP_REMOVELINES              "pseudo.Remove Selected Lines"

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   "pseudo.Editor"

#define LOCALIZED_EDITOR_FILE                    "pseudo.&File"
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        "pseudo.&Save and Exit\tCtrl+D"
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    "pseudo.Save to &Workspace"
#define LOCALIZED_EDITOR_FILE_PRINT              "pseudo.&Print..." 
#define LOCALIZED_EDITOR_FILE_EXIT               "pseudo.E&xit" 

#define LOCALIZED_EDITOR_EDIT                    "pseudo.&Edit"
#define LOCALIZED_EDITOR_EDIT_UNDO               "pseudo.&Undo\tCtrl+Z"
#define LOCALIZED_EDITOR_EDIT_REDO               "pseudo.&Redo\tCtrl+Y"
#define LOCALIZED_EDITOR_EDIT_CUT                "pseudo.&Cut\tCtrl+X"
#define LOCALIZED_EDITOR_EDIT_COPY               "pseudo.C&opy\tCtrl+C"
#define LOCALIZED_EDITOR_EDIT_PASTE              "pseudo.&Paste\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_DELETE             "pseudo.&Delete\tDel"
#define LOCALIZED_EDITOR_EDIT_CLEARALL           "pseudo.C&lear All\tCtrl+Del"
#define LOCALIZED_EDITOR_EDIT_SELECTALL          "pseudo.S&elect All\tCtrl+A"

#define LOCALIZED_EDITOR_SEARCH                  "pseudo.&Search"
#define LOCALIZED_EDITOR_SEARCH_FIND             "pseudo.&Find...\tCtrl+F"
#define LOCALIZED_EDITOR_SEARCH_REPLACE          "pseudo.&Replace...\tCtrl+H" 
#define LOCALIZED_EDITOR_SEARCH_NEXT             "pseudo.&Next\tF3" 

#define LOCALIZED_EDITOR_SET                     "pseudo.Se&t" 
#define LOCALIZED_EDITOR_SET_FONT                "pseudo.&Font..." 

#define LOCALIZED_EDITOR_TEST                    "pseudo.Test"
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      "pseudo.&Run Selection\tCtrl+R"

#define LOCALIZED_EDITOR_HELP                    "pseudo.&Help" 
#define LOCALIZED_EDITOR_HELP_INDEX              "pseudo.&Index"
#define LOCALIZED_EDITOR_HELP_EDITOR             "pseudo.&Editor"
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        "pseudo.&Topic Search\tF1"


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    "pseudo.&Save and Exit"
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       "pseudo.&Don't Save"
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       "pseudo.There are unsaved changes in the workspace.  If you exit without saving, these changes will be lost.  "
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       "pseudo.Would you like to save your changes before exiting?" 


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     "pseudo.Commander"
#define LOCALIZED_COMMANDER_HALT                "pseudo.Halt"
#define LOCALIZED_COMMANDER_TRACE               "pseudo.Trace"
#define LOCALIZED_COMMANDER_NOTRACE             "pseudo.NoTrace"
#define LOCALIZED_COMMANDER_PAUSE               "pseudo.Pause"
#define LOCALIZED_COMMANDER_STATUS              "pseudo.Status"
#define LOCALIZED_COMMANDER_NOSTATUS            "pseudo.NoStatus"
#define LOCALIZED_COMMANDER_STEP                "pseudo.Step"
#define LOCALIZED_COMMANDER_UNSTEP              "pseudo.UnStep"
#define LOCALIZED_COMMANDER_RESET               "pseudo.Reset"
#define LOCALIZED_COMMANDER_EXECUTE             "pseudo.Execute"
#define LOCALIZED_COMMANDER_EDALL               "pseudo.Edall"

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        "pseudo.Status"
#define LOCALIZED_STATUS_PEN                    "pseudo.Pen"
#define LOCALIZED_STATUS_CONTACT                "pseudo.Contact:"
#define LOCALIZED_STATUS_WIDTH                  "pseudo.Width:"
#define LOCALIZED_STATUS_STYLE                  "pseudo.Style:"
#define LOCALIZED_STATUS_ORIENTATION            "pseudo.Orientation"
#define LOCALIZED_STATUS_PITCH                  "pseudo.Pitch:"
#define LOCALIZED_STATUS_HEADING                "pseudo.Heading:"
#define LOCALIZED_STATUS_ROLL                   "pseudo.Roll:"
#define LOCALIZED_STATUS_TURTLE                 "pseudo.Turtle"
#define LOCALIZED_STATUS_POSITION               "pseudo.Position(XYZ):"
#define LOCALIZED_STATUS_WHICH                  "pseudo.Which:"
#define LOCALIZED_STATUS_VISIBILITY             "pseudo.Visibility:"
#define LOCALIZED_STATUS_COLOR                  "pseudo.Color"
#define LOCALIZED_STATUS_PENCOLOR               "pseudo.Pen(RGB):"
#define LOCALIZED_STATUS_FLOODCOLOR             "pseudo.Flood(RGB):"
#define LOCALIZED_STATUS_SCREENCOLOR            "pseudo.Screen(RGB):"
#define LOCALIZED_STATUS_KERNEL                 "pseudo.Kernel"
#define LOCALIZED_STATUS_CALLS                  "pseudo.Calls:"
#define LOCALIZED_STATUS_PEAKMEMORY             "pseudo.Peak Memory:"

#define LOCALIZED_STATUS_PENREVERSE     "pseudo.Reverse"
#define LOCALIZED_STATUS_PENNORMAL      "pseudo.Normal"
#define LOCALIZED_STATUS_PENERASE       "pseudo.Erase"
#define LOCALIZED_STATUS_PENUP          "pseudo.Up"
#define LOCALIZED_STATUS_PENDOWN        "pseudo.Down"
#define LOCALIZED_STATUS_PENSHOWN       "pseudo.Shown"
#define LOCALIZED_STATUS_PENHIDDEN      "pseudo.Hidden"
#define LOCALIZED_STATUS_POLYGONS       "pseudo.Polygons"
#define LOCALIZED_STATUS_VECTORS        "pseudo.Vectors"
#define LOCALIZED_STATUS_NODES          "pseudo.Nodes"
#define LOCALIZED_STATUS_NOT_APPLICABLE "pseudo.N/A"

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           "pseudo.&All"
#define LOCALIZED_ERASEPROCEDURE                "pseudo.Erase Procedure"
#define LOCALIZED_EDITPROCEDURE                 "pseudo.Edit Procedure"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     "pseudo.Set Color"
#define LOCALIZED_SETCOLOR_PENCOLOR            "pseudo.Pen Color"
#define LOCALIZED_SETCOLOR_FLOODCOLOR          "pseudo.Flood Color"
#define LOCALIZED_SETCOLOR_SCREENCOLOR         "pseudo.Screen Color"
#define LOCALIZED_SETCOLOR_RED                 "pseudo.Red"
#define LOCALIZED_SETCOLOR_GREEN               "pseudo.Green"
#define LOCALIZED_SETCOLOR_BLUE                "pseudo.Blue"
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   "pseudo.Pen Size"
#define LOCALIZED_SETPENSIZE_SIZE              "pseudo.Thickness"
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     "pseudo.About "LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_ABOUTFMS_VERSION             "pseudo.Version"
#define LOCALIZED_ABOUTFMS_GUI                 "pseudo.GUI by George Mills\nSoftronics, Inc.\nhttp://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_CORE                "pseudo.Core by Brian Harvey\nUniversity of California Berkeley"
#define LOCALIZED_ABOUTFMS_INSTALLER           "pseudo.Installer based on Nullsoft Scriptable Install System\nhttp://nsis.sourceforge.net/"
#define LOCALIZED_ABOUTFMS_ADVENTURE           "pseudo.The Great Logo Adventure (ISBN 0-9651934-6-2)\nWritten and donated by Jim Muller\nAvailable at http://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       "pseudo.Special thanks to Yehuda Katz and Erich Neuwirth"
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME" is free software\nSee GNU Public License"
#define LOCALIZED_ABOUTFMS_NEWSGROUP           "pseudo.Internet News Group: comp.lang.logo\nVisit the Logo-Forum at\nhttp://groups.yahoo.com/group/LogoForum/"
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     "pseudo.To learn the internals of computers,\ntry MultiMedia Logic from Softronics, Inc."
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      "pseudo.About FMS"
#define LOCALIZED_ABOUTMS_FMS                  "pseudo.FMS stands for Fight Multiple Sclerosis."
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     "pseudo.Please consider donating to the\nNational Multiple Sclerosis Society.\nhttp://www.nmss.org\n1-800-FIGHT-MS"
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

#define LOCALIZED_CHANGESINEDITORMAYBELOST  "pseudo.Changes in this edit session may be lost.\n\nDo you really want to exit "LOCALIZED_GENERAL_PRODUCTNAME"?"
#define LOCALIZED_EDITSESSIONISRUNNING      "pseudo.An Edit session is running"

#define LOCALIZED_COULDNOTWRITEBMP            "pseudo.Could not write .bmp"
#define LOCALIZED_COULDNOTOPENBMP             "pseudo.Could not open .bmp"
#define LOCALIZED_COULDNOTCREATEBMP           "pseudo.Unable to create Windows 3.0 bitmap"
#define LOCALIZED_NOTVALIDBMP                 "pseudo.Not a Windows 3.0 bitmap"

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         "pseudo.You have not saved to disk"
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     "pseudo.Executing a new will erase all definitions.\n\nContinue with New?"
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE "pseudo.The file being loaded will be merged into your workspace\nand may overwrite your unsaved changes.\n\nContinue with Load?"
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    "pseudo.This will erase all of your unsaved changes.\n\nContinue with Open?"

#define LOCALIZED_EDITORISOPEN                  "pseudo.Did you know you have an edit session running?\n\nAny changes in this edit session are not being saved."

#define LOCALIZED_ERROR_CANTREADFILE            "pseudo.Unable to read file \"%s\" from disk"
#define LOCALIZED_ERROR_CANTWRITEFILE           "pseudo.Unable to write file \"%s\" to disk"

#define LOCALIZED_SAVETOWORKSPACE                "pseudo.Save to Workspace"
#define LOCALIZED_CONTENTSCHANGED                "pseudo.Contents Changed"
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE "pseudo.The contents have changed.\nWould you like to save the changes to the workspace?"



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  "pseudo.There was a problem saving the contents of the editor to the workspace.  The cursor will be positioned just after last successful definition.\n\nCheck the Commander for possible error message."
#define LOCALIZED_RETURNTOEDIT                  "pseudo.Return to the editor?"

#define LOCALIZED_EDITFAILEDTOLOAD              LOCALIZED_SAVETOWORKSPACE

#define LOCALIZED_ERRORINFILETITLE              "pseudo.Error in File"
#define LOCALIZED_ERRORINFILEMESSAGE            "pseudo.There was a problem loading the contents of the file \"%s\".\n\nCheck the Commander for possible error message.\n\nDo you want to open the file in the editor to see the error?"

#define LOCALIZED_CANNOTALLOCATESCREEN          "pseudo.Unable to allocate memory for the screen window.  You may have requested a width and height that exceeds the amount of available video RAM.\n\n" LOCALIZED_GENERAL_PRODUCTNAME " can't continue."


// 
//  Strings used in the File-Open filters
//
#define LOCALIZED_FILE_LOAD_DIALOG_TITLE    "pseudo.Select the Logo program to load (merge into workspace)"
#define LOCALIZED_FILE_OPEN_DIALOG_TITLE    "pseudo.Select the Logo program to open (replace the workspace with)"
#define LOCALIZED_FILE_SAVE_DIALOG_TITLE    "pseudo.Select the file to which the workspace will be saved"
#define LOCALIZED_BITMAP_OPEN_DIALOG_TITLE  "pseudo.Select the image to load"
#define LOCALIZED_BITMAP_SAVE_DIALOG_TITLE  "pseudo.Select the file to which the active area will be saved"

#define LOCALIZED_LOGO_FILE_EXTENSION "pseudo.lgo"
#define LOCALIZED_FILEFILTER_ALLFILES "pseudo.All Files (*.*)|*.*"
#define LOCALIZED_FILEFILTER_LOGO     "pseudo.Logo Files (*.lgo)|*.lgo|"LOCALIZED_FILEFILTER_ALLFILES
#define LOCALIZED_FILEFILTER_IMAGE    "pseudo.Bitmap Files (*.bmp)|*.bmp|GIF Files (*.gif)|*.gif|"LOCALIZED_FILEFILTER_ALLFILES



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             " pseudo.stops\n"
#define LOCALIZED_TRACING_OUTPUTS           " pseudo.outputs %s\n"
#define LOCALIZED_TRACING_MAKE              "pseudo.Make %s %s"
#define LOCALIZED_TRACING_PPROP             "pseudo.Pprop %s %s %s"
#define LOCALIZED_TRACING_LOCATION          " pseudo.in %s\n%s"

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  "pseudo.Single Step"

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  "pseudo.%s defined\n"


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    "pseudo.erase"
#define LOCALIZED_PENMODE_REVERSE  "pseudo.reverse"
#define LOCALIZED_PENMODE_PAINT    "pseudo.paint"

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          "pseudo.Logo: Fatal Internal Error"
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       "pseudo.Logo: Out of memory"
#define LOCALIZED_ERROR_OUTOFMEMORY            "pseudo.Out of memory"
#define LOCALIZED_ERROR_STACKOVERFLOW          "pseudo.stack overflow"
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      "pseudo.turtle out of bounds"
#define LOCALIZED_ERROR_BADGRAPHINIT           "pseudo.couldn't initialize graphics"
#define LOCALIZED_ERROR_BADDATA                "pseudo.%p doesn't like %s as input"
#define LOCALIZED_ERROR_DIDNTOUTPUT            "pseudo.%p didn't output to %p"
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        "pseudo.not enough inputs to %p"
#define LOCALIZED_ERROR_TOOMUCH                "pseudo.too much inside ()'s"
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    "pseudo.You don't say what to do with %s"
#define LOCALIZED_ERROR_PARENMISMATCH          "pseudo.too many ('s"
#define LOCALIZED_ERROR_NOVALUE                "pseudo.%s has no value"
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        "pseudo.unexpected ')'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      "pseudo.unexpected ']'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        "pseudo.unexpected '}'"
#define LOCALIZED_ERROR_DONTKNOWHOWTO          "pseudo.I don't know how to %p"
#define LOCALIZED_ERROR_NOCATCHTAG             "pseudo.Can't find catch tag for %p"
#define LOCALIZED_ERROR_ALREADYDEFINED         "pseudo.%p is already defined"
#define LOCALIZED_ERROR_STOPPING               "pseudo.Stopping..."
#define LOCALIZED_ERROR_ALREADYDRIBBLING       "pseudo.Already dribbling"
#define LOCALIZED_ERROR_FILESYSTEM                   "pseudo.File system error: %p"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          "pseudo.Could not open file"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         "pseudo.Unable to open file: %t"
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       "pseudo.File already open"
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           "pseudo.File not open"
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  "pseudo.Could not create editor file"
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   "pseudo.Could not launch the editor" 
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    "pseudo.Could not read editor file" 
#define LOCALIZED_ERROR_IFWARNING              "pseudo.Assuming you mean IFELSE, not IF"
#define LOCALIZED_ERROR_SHADOWWARNING          "pseudo.%p shadowed by local in procedure call"
#define LOCALIZED_ERROR_USER                   "pseudo.Throw \"Error"
#define LOCALIZED_ERROR_ISPRIMITIVE            "pseudo.%p is a primitive"
#define LOCALIZED_ERROR_TONOTINSIDE            "pseudo.Can't use TO inside a procedure"
#define LOCALIZED_ERROR_ATTOPLEVEL             "pseudo.Can only use %p inside a procedure"
#define LOCALIZED_ERROR_ATTOPLEVEL2            "pseudo.You must be in a procedure to use OUTPUT or STOP"
#define LOCALIZED_ERROR_NOTEST                 "pseudo.%p without TEST"
#define LOCALIZED_ERROR_BADMACROOUTPUT         "pseudo.Macro output %s instead of a list"
#define LOCALIZED_ERROR_DEEPEND                "pseudo.END inside multi-line instruction"
#define LOCALIZED_ERROR_DEEPENDIN              "pseudo.END inside multi-line instruction in %p"
#define LOCALIZED_ERROR_UNKNOWN                "pseudo.Unknown error condition - internal error."
#define LOCALIZED_PAUSING                      "pseudo.Pausing..."


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION "pseudo.Invalid state for instruction: %p"
#define LOCALIZED_ERROR_MODE_ON_SPRITE             "pseudo.cannot set the mode of a turtle with a rotating bitmap"
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        "pseudo.cannot make a special turtle use a rotating bitmap"
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            "pseudo.cannot use the clipboard as a rotating bitmap"
#define LOCALIZED_ERROR_SPECIALFORM                "pseudo.%p doesn't like %p as input because it has a special form"

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      "pseudo.Error"
#define LOCALIZED_ERROR_BADINPUT             "pseudo.Bad input"
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    "pseudo.Input is not paired"

#define LOCALIZED_ERROR_CANTOPENPORT         "pseudo.Could not open port"
#define LOCALIZED_ERROR_CANTCLOSEPORT        "pseudo.Could not close port"
#define LOCALIZED_ERROR_CANTFLUSHPORT        "pseudo.Could not flush port"
#define LOCALIZED_ERROR_CANTDCBONPORT        "pseudo.Could not build dcb on port"
#define LOCALIZED_ERROR_CANTSETPORT          "pseudo.Could not set port"
#define LOCALIZED_ERROR_PORTALREADYOPEN      "pseudo.Port is already open"
#define LOCALIZED_ERROR_PORTNOTOPEN          "pseudo.Port is not open"

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   "pseudo.%s already exists"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    "pseudo.%s does not exist"

#define LOCALIZED_ERROR_DLLNOTLOADED          "pseudo.DLL is not loaded"
#define LOCALIZED_ERROR_DLLLOADFAILED         "pseudo.DLL load failed"
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    "pseudo.Invalid data type input"
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  "pseudo.Invalid output type"
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   "pseudo.Function not found"
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  "pseudo.Not all Type/Data inputs are paired"

#define LOCALIZED_ERROR_NETWORK               "pseudo.Network Error"
#define LOCALIZED_ERROR_NETWORKRECEIVE        "pseudo.Network Receive Error"
#define LOCALIZED_ERROR_NETWORKSEND           "pseudo.Network Send Error"
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       "pseudo.Unexpected Error, Network may be shutdown"
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     "pseudo.Not started"
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED "pseudo.Already started"
#define LOCALIZED_ERROR_NETWORKALREADYON      "pseudo.Already on"
#define LOCALIZED_ERROR_NETWORKALREADYOFF     "pseudo.Already off"

// The rest of the network errors shouldn't really be seen -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         "pseudo.Name too long"
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      "pseudo.Not initialized"
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      "pseudo.System not ready"
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED "pseudo.Version is not supported"
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   "pseudo.Can't send after socket shutdown"
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         "pseudo.Interrupted system call"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    "pseudo.Authoritative Answer: Host not found"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH "pseudo.Non-Authoritative: Host not found. See NETSTARTUP"
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      "pseudo.Non-recoverable error"
#define LOCALIZED_ERROR_NETWORKNODATA              "pseudo.No data record available"
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       "pseudo.Bad file number"
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          "pseudo.Operation would block"
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       "pseudo.Operation now in progress"
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   "pseudo.Operation already in progress"
#define LOCALIZED_ERROR_NETWORKBADADDRESS          "pseudo.Bad address"
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     "pseudo.Destination address required"
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      "pseudo.Message too long"
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      "pseudo.Protocol family not supported"
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         "pseudo.Directory not empty"
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     "pseudo.Application limit has been reached"
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           "pseudo.Disk quota exceeded"
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        "pseudo.Too many open files"
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        "pseudo.Access denied"
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          "pseudo.Socket operation on non-socket"
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    "pseudo.Can't assign requested address"
#define LOCALIZED_ERROR_NETWORKADDRINUSE           "pseudo.Address already in use"
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      "pseudo.Address family not supported by protocol family"
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            "pseudo.Connection timed out"
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    "pseudo.Socket type not supported"
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   "pseudo.Protocol not supported"
#define LOCALIZED_ERROR_NETWORKNOBUFFER            "pseudo.No space in buffer"
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    "pseudo.Socket is already connected"
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        "pseudo.Socket is not connected"
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         "pseudo.Bad protocol option"
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     "pseudo.Connection reset by peer"
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     "pseudo.Software caused connection abort"
#define LOCALIZED_ERROR_NETWORKISDOWN              "pseudo.Network is down"
#define LOCALIZED_ERROR_NETWORKRESET               "pseudo.Network was reset"
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   "pseudo.Connection refused"
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          "pseudo.Host is down"
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   "pseudo.Host is unreachable"
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        "pseudo.Protocol is wrong type for socket"
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   "pseudo.Operation not supported on socket"
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         "pseudo.No path to remote host was found"
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         "pseudo.Too many references"

#define LOCALIZED_ERROR_POLYSTART               "pseudo.PolyStart Error"
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED "pseudo.You already have a Polygon started"

#define LOCALIZED_ERROR_POLYEND                 "pseudo.PolyEnd Error"
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       "pseudo.You have not started a Polygon"
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     "pseudo.You must have at least 3 vectors to define a polygon"

#define LOCALIZED_ERROR_SOUND                 "pseudo.Sound Error"

#define LOCALIZED_ERROR_MIDI                  "pseudo.MIDI Error"
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     "pseudo.Invalid MIDI device"
#define LOCALIZED_ERROR_MIDIALREADYOPEN       "pseudo.Already open"
#define LOCALIZED_ERROR_MIDINOTOPEN           "pseudo.Not open"

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      "pseudo.No Text in Clipboard"

#define LOCALIZED_ERROR_MCI                   "pseudo.MCI Error"

#define LOCALIZED_ERROR_TIMERNOTFOUND         "pseudo.Timer not found"

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       "pseudo.Online help is unavailable because hhctrl.ocx could not be loaded." 

#define LOCALIZED_ERROR_BADCOMMANDLINE        "pseudo.Invalid Command Line" 

#define LOCALIZED_ERROR_TMPNOTDEFINED         "pseudo.The environment variable TMP is not defined or invalid.\n"LOCALIZED_GENERAL_PRODUCTNAME" will attempt to use C:\\ for storing temporary files"

#define LOCALIZED_ERROR_GIFSAVEFAILED         "pseudo.Problem Generating GIF, check memory and diskspace"
#define LOCALIZED_ERROR_GIFREADFAILED         "pseudo.Problem Reading GIF, check memory and diskspace"

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  "pseudo.BitMap Index out of range"
#define LOCALIZED_ERROR_BITMAPCUTFAILED        "pseudo.Cut failed, Possibly not enough Memory"

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    "pseudo.Nothing to Paste" 
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  "pseudo.BitMap at Index must be initialized with a bitmap" 

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      "pseudo.Turtle %d has no picture, will Halt"

#define LOCALIZED_ERROR_FONTNOTFOUND            "pseudo.Sorry, no font named %s was found.  Choose one of the following:\n"

#define LOCALIZED_ERROR_PRINTERCANTSCALE        "pseudo.Print driver does not support this function" 
#define LOCALIZED_ERROR_CANTDRAWIMAGE           "pseudo.Cannot draw image"
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        "pseudo.Cannot extract image"
#define LOCALIZED_ERROR_SUBCODE                 "pseudo.Sub Code"

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         "pseudo.Input:"
#define LOCALIZED_PROMPT_TO     "pseudo.To Mode (Cancel to End)"
#define LOCALIZED_PROMPT_LIST   "pseudo.List Mode (Cancel to Halt)"
#define LOCALIZED_PROMPT_PAUSE  "pseudo.Pause Mode (Cancel to Continue)"
#define LOCALIZED_PROMPT_INPUT  "pseudo.Input Mode (Cancel to Halt)"

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      "pseudo.Changed to \"%s\""
#define LOCALIZED_FILE_CHDIRFAILED         "pseudo.Could not chdir to directory \"%s\""
#define LOCALIZED_FILE_POPPEDTO            "pseudo.Popped to \"%s\""
#define LOCALIZED_FILE_MKDIRSUCCEEDED      "pseudo.Now in newly created directory \"%s\"" 
#define LOCALIZED_FILE_MKDIRFAILED         "pseudo.Failed to create directory \"%s\"" 
#define LOCALIZED_FILE_RMDIRSUCCEEDED      "pseudo.Removed directory \"%s\"" 
#define LOCALIZED_FILE_RMDIRFAILED         "pseudo.Failed to remove directory \"%s\"" 
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  "pseudo.The directory does not exist."
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY "pseudo.Make sure the directory is empty before trying to remove it."


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       "pseudo.Logo Picture"

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    "pseudo.Active Area"
#define LOCALIZED_INFORMATION   "pseudo.Information"
#define LOCALIZED_WARNING       "pseudo.Warning"
#define LOCALIZED_UNTITLED      "pseudo.Untitled"
#define LOCALIZED_UNKNOWN       "pseudo.Unknown"

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       "pseudo.nothing"

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     "pseudo.Find"
#define LOCALIZED_EDITOR_TITLE_REPLACE  "pseudo.Replace" 

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING "pseudo.Cannot find %s"


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
#define LOCALIZED_COLOR_ALICEBLUE             "pseudo.AliceBlue"
#define LOCALIZED_COLOR_ANTIQUEWHITE          "pseudo.AntiqueWhite"
#define LOCALIZED_COLOR_AQUA                  "pseudo.Aqua"
#define LOCALIZED_COLOR_AQUAMARINE            "pseudo.Aquamarine"
#define LOCALIZED_COLOR_AZURE                 "pseudo.Azure"
#define LOCALIZED_COLOR_BEIGE                 "pseudo.Beige"
#define LOCALIZED_COLOR_BISQUE                "pseudo.Bisque"
#define LOCALIZED_COLOR_BLACK                 "pseudo.Black"
#define LOCALIZED_COLOR_BLANCHEDALMOND        "pseudo.BlanchedAlmond"
#define LOCALIZED_COLOR_BLUE                  "pseudo.Blue"
#define LOCALIZED_COLOR_BLUEVIOLET            "pseudo.BlueViolet"
#define LOCALIZED_COLOR_BROWN                 "pseudo.Brown"
#define LOCALIZED_COLOR_BURLYWOOD             "pseudo.BurlyWood"
#define LOCALIZED_COLOR_CADETBLUE             "pseudo.CadetBlue"
#define LOCALIZED_COLOR_CHARTREUSE            "pseudo.Chartreuse"
#define LOCALIZED_COLOR_CHOCOLATE             "pseudo.Chocolate"
#define LOCALIZED_COLOR_CORAL                 "pseudo.Coral"
#define LOCALIZED_COLOR_CORNFLOWERBLUE        "pseudo.CornflowerBlue"
#define LOCALIZED_COLOR_CORNSILK              "pseudo.Cornsilk"
#define LOCALIZED_COLOR_CRIMSON               "pseudo.Crimson"
#define LOCALIZED_COLOR_CYAN                  "pseudo.Cyan"
#define LOCALIZED_COLOR_DARKBLUE              "pseudo.DarkBlue"
#define LOCALIZED_COLOR_DARKCYAN              "pseudo.DarkCyan"
#define LOCALIZED_COLOR_DARKGOLDENROD         "pseudo.DarkGoldenRod"
#define LOCALIZED_COLOR_DARKGRAY              "pseudo.DarkGray"
#define LOCALIZED_COLOR_DARKGREEN             "pseudo.DarkGreen"
#define LOCALIZED_COLOR_DARKGREY              "pseudo.DarkGrey"
#define LOCALIZED_COLOR_DARKKHAKI             "pseudo.DarkKhaki"
#define LOCALIZED_COLOR_DARKMAGENTA           "pseudo.DarkMagenta"
#define LOCALIZED_COLOR_DARKOLIVEGREEN        "pseudo.DarkOliveGreen"
#define LOCALIZED_COLOR_DARKORANGE            "pseudo.DarkOrange"
#define LOCALIZED_COLOR_DARKORCHID            "pseudo.DarkOrchid"
#define LOCALIZED_COLOR_DARKRED               "pseudo.DarkRed"
#define LOCALIZED_COLOR_DARKSALMON            "pseudo.DarkSalmon"
#define LOCALIZED_COLOR_DARKSEAGREEN          "pseudo.DarkSeaGreen"
#define LOCALIZED_COLOR_DARKSLATEBLUE         "pseudo.DarkSlateBlue"
#define LOCALIZED_COLOR_DARKSLATEGRAY         "pseudo.DarkSlateGray"
#define LOCALIZED_COLOR_DARKSLATEGREY         "pseudo.DarkSlateGrey"
#define LOCALIZED_COLOR_DARKTURQUOISE         "pseudo.DarkTurquoise"
#define LOCALIZED_COLOR_DARKVIOLET            "pseudo.DarkViolet"
#define LOCALIZED_COLOR_DEEPPINK              "pseudo.DeepPink"
#define LOCALIZED_COLOR_DEEPSKYBLUE           "pseudo.DeepSkyBlue"
#define LOCALIZED_COLOR_DIMGRAY               "pseudo.DimGray"
#define LOCALIZED_COLOR_DIMGREY               "pseudo.DimGrey"
#define LOCALIZED_COLOR_DODGERBLUE            "pseudo.DodgerBlue"
#define LOCALIZED_COLOR_FIREBRICK             "pseudo.FireBrick"
#define LOCALIZED_COLOR_FLORALWHITE           "pseudo.FloralWhite"
#define LOCALIZED_COLOR_FORESTGREEN           "pseudo.ForestGreen"
#define LOCALIZED_COLOR_FUCHSIA               "pseudo.Fuchsia"
#define LOCALIZED_COLOR_GAINSBORO             "pseudo.Gainsboro"
#define LOCALIZED_COLOR_GHOSTWHITE            "pseudo.GhostWhite"
#define LOCALIZED_COLOR_GOLD                  "pseudo.Gold"
#define LOCALIZED_COLOR_GOLDENROD             "pseudo.GoldenRod"
#define LOCALIZED_COLOR_GRAY                  "pseudo.Gray"
#define LOCALIZED_COLOR_GREEN                 "pseudo.Green"
#define LOCALIZED_COLOR_GREENYELLOW           "pseudo.GreenYellow"
#define LOCALIZED_COLOR_GREY                  "pseudo.Grey"
#define LOCALIZED_COLOR_HONEYDEW              "pseudo.HoneyDew"
#define LOCALIZED_COLOR_HOTPINK               "pseudo.HotPink"
#define LOCALIZED_COLOR_INDIANRED             "pseudo.IndianRed"
#define LOCALIZED_COLOR_INDIGO                "pseudo.Indigo"
#define LOCALIZED_COLOR_IVORY                 "pseudo.Ivory"
#define LOCALIZED_COLOR_KHAKI                 "pseudo.Khaki"
#define LOCALIZED_COLOR_LAVENDER              "pseudo.Lavender"
#define LOCALIZED_COLOR_LAVENDERBLUSH         "pseudo.LavenderBlush"
#define LOCALIZED_COLOR_LAWNGREEN             "pseudo.LawnGreen"
#define LOCALIZED_COLOR_LEMONCHIFFON          "pseudo.LemonChiffon"
#define LOCALIZED_COLOR_LIGHTBLUE             "pseudo.LightBlue"
#define LOCALIZED_COLOR_LIGHTCORAL            "pseudo.LightCoral"
#define LOCALIZED_COLOR_LIGHTCYAN             "pseudo.LightCyan"
#define LOCALIZED_COLOR_LIGHTGOLDENRODYELLOW  "pseudo.LightGoldenRodYellow"
#define LOCALIZED_COLOR_LIGHTGRAY             "pseudo.LightGray"
#define LOCALIZED_COLOR_LIGHTGREEN            "pseudo.LightGreen"
#define LOCALIZED_COLOR_LIGHTGREY             "pseudo.LightGrey"
#define LOCALIZED_COLOR_LIGHTPINK             "pseudo.LightPink"
#define LOCALIZED_COLOR_LIGHTSALMON           "pseudo.LightSalmon"
#define LOCALIZED_COLOR_LIGHTSEAGREEN         "pseudo.LightSeaGreen"
#define LOCALIZED_COLOR_LIGHTSKYBLUE          "pseudo.LightSkyBlue"
#define LOCALIZED_COLOR_LIGHTSLATEGRAY        "pseudo.LightSlateGray"
#define LOCALIZED_COLOR_LIGHTSLATEGREY        "pseudo.LightSlateGrey"
#define LOCALIZED_COLOR_LIGHTSTEELBLUE        "pseudo.LightSteelBlue"
#define LOCALIZED_COLOR_LIGHTYELLOW           "pseudo.LightYellow"
#define LOCALIZED_COLOR_LIME                  "pseudo.Lime"
#define LOCALIZED_COLOR_LIMEGREEN             "pseudo.LimeGreen"
#define LOCALIZED_COLOR_LINEN                 "pseudo.Linen"
#define LOCALIZED_COLOR_MAGENTA               "pseudo.Magenta"
#define LOCALIZED_COLOR_MAROON                "pseudo.Maroon"
#define LOCALIZED_COLOR_MEDIUMAQUAMARINE      "pseudo.MediumAquaMarine"
#define LOCALIZED_COLOR_MEDIUMBLUE            "pseudo.MediumBlue"
#define LOCALIZED_COLOR_MEDIUMORCHID          "pseudo.MediumOrchid"
#define LOCALIZED_COLOR_MEDIUMPURPLE          "pseudo.MediumPurple"
#define LOCALIZED_COLOR_MEDIUMSEAGREEN        "pseudo.MediumSeaGreen"
#define LOCALIZED_COLOR_MEDIUMSLATEBLUE       "pseudo.MediumSlateBlue"
#define LOCALIZED_COLOR_MEDIUMSPRINGGREEN     "pseudo.MediumSpringGreen"
#define LOCALIZED_COLOR_MEDIUMTURQUOISE       "pseudo.MediumTurquoise"
#define LOCALIZED_COLOR_MEDIUMVIOLETRED       "pseudo.MediumVioletRed"
#define LOCALIZED_COLOR_MIDNIGHTBLUE          "pseudo.MidnightBlue"
#define LOCALIZED_COLOR_MINTCREAM             "pseudo.MintCream"
#define LOCALIZED_COLOR_MISTYROSE             "pseudo.MistyRose"
#define LOCALIZED_COLOR_MOCCASIN              "pseudo.Moccasin"
#define LOCALIZED_COLOR_NAVAJOWHITE           "pseudo.NavajoWhite"
#define LOCALIZED_COLOR_NAVY                  "pseudo.Navy"
#define LOCALIZED_COLOR_OLDLACE               "pseudo.OldLace"
#define LOCALIZED_COLOR_OLIVE                 "pseudo.Olive"
#define LOCALIZED_COLOR_OLIVEDRAB             "pseudo.OliveDrab"
#define LOCALIZED_COLOR_ORANGE                "pseudo.Orange"
#define LOCALIZED_COLOR_ORANGERED             "pseudo.OrangeRed"
#define LOCALIZED_COLOR_ORCHID                "pseudo.Orchid"
#define LOCALIZED_COLOR_PALEGOLDENROD         "pseudo.PaleGoldenRod"
#define LOCALIZED_COLOR_PALEGREEN             "pseudo.PaleGreen"
#define LOCALIZED_COLOR_PALETURQUOISE         "pseudo.PaleTurquoise"
#define LOCALIZED_COLOR_PALEVIOLETRED         "pseudo.PaleVioletRed"
#define LOCALIZED_COLOR_PAPAYAWHIP            "pseudo.PapayaWhip"
#define LOCALIZED_COLOR_PEACHPUFF             "pseudo.PeachPuff"
#define LOCALIZED_COLOR_PERU                  "pseudo.Peru"
#define LOCALIZED_COLOR_PINK                  "pseudo.Pink"
#define LOCALIZED_COLOR_PLUM                  "pseudo.Plum"
#define LOCALIZED_COLOR_POWDERBLUE            "pseudo.PowderBlue"
#define LOCALIZED_COLOR_PURPLE                "pseudo.Purple"
#define LOCALIZED_COLOR_RED                   "pseudo.Red"
#define LOCALIZED_COLOR_ROSYBROWN             "pseudo.RosyBrown"
#define LOCALIZED_COLOR_ROYALBLUE             "pseudo.RoyalBlue"
#define LOCALIZED_COLOR_SADDLEBROWN           "pseudo.SaddleBrown"
#define LOCALIZED_COLOR_SALMON                "pseudo.Salmon"
#define LOCALIZED_COLOR_SANDYBROWN            "pseudo.SandyBrown"
#define LOCALIZED_COLOR_SEAGREEN              "pseudo.SeaGreen"
#define LOCALIZED_COLOR_SEASHELL              "pseudo.SeaShell"
#define LOCALIZED_COLOR_SIENNA                "pseudo.Sienna"
#define LOCALIZED_COLOR_SILVER                "pseudo.Silver"
#define LOCALIZED_COLOR_SKYBLUE               "pseudo.SkyBlue"
#define LOCALIZED_COLOR_SLATEBLUE             "pseudo.SlateBlue"
#define LOCALIZED_COLOR_SLATEGRAY             "pseudo.SlateGray"
#define LOCALIZED_COLOR_SLATEGREY             "pseudo.SlateGrey"
#define LOCALIZED_COLOR_SNOW                  "pseudo.Snow"
#define LOCALIZED_COLOR_SPRINGGREEN           "pseudo.SpringGreen"
#define LOCALIZED_COLOR_STEELBLUE             "pseudo.SteelBlue"
#define LOCALIZED_COLOR_TAN                   "pseudo.Tan"
#define LOCALIZED_COLOR_TEAL                  "pseudo.Teal"
#define LOCALIZED_COLOR_THISTLE               "pseudo.Thistle"
#define LOCALIZED_COLOR_TOMATO                "pseudo.Tomato"
#define LOCALIZED_COLOR_TURQUOISE             "pseudo.Turquoise"
#define LOCALIZED_COLOR_VIOLET                "pseudo.Violet"
#define LOCALIZED_COLOR_WHEAT                 "pseudo.Wheat"
#define LOCALIZED_COLOR_WHITE                 "pseudo.White"
#define LOCALIZED_COLOR_WHITESMOKE            "pseudo.WhiteSmoke"
#define LOCALIZED_COLOR_YELLOW                "pseudo.Yellow"
#define LOCALIZED_COLOR_YELLOWGREEN           "pseudo.YellowGreen"

//
// The name of each "window class" that DEBUGWINDOWS prints.
// These should match the corresponding terms that is used
// in the  LOCALIZED_ALTERNATE_*CREATE procedures.
//
#define LOCALIZED_WINDOWCLASSNAME_WINDOW       "pseudo.Window"
#define LOCALIZED_WINDOWCLASSNAME_STATIC       "pseudo.Static"
#define LOCALIZED_WINDOWCLASSNAME_LISTBOX      "pseudo.ListBox"
#define LOCALIZED_WINDOWCLASSNAME_COMBOBOX     "pseudo.ComboBox"
#define LOCALIZED_WINDOWCLASSNAME_BUTTON       "pseudo.Button"
#define LOCALIZED_WINDOWCLASSNAME_SCROLLBAR    "pseudo.ScrollBar"
#define LOCALIZED_WINDOWCLASSNAME_GROUPBOX     "pseudo.GroupBox"
#define LOCALIZED_WINDOWCLASSNAME_RADIOBUTTON  "pseudo.RadioButton"
#define LOCALIZED_WINDOWCLASSNAME_CHECKBOX     "pseudo.CheckBox"
#define LOCALIZED_WINDOWCLASSNAME_DIALOG       "pseudo.Dialog"


//
// The name of the default font face name.
// This should only be translated if the given font face doesn't include glyphs
// for characters in your language.  The specified font face name must be part
// of all Windows versions from Windows XP onward that would support your
// language.
//
#define LOCALIZED_DEFAULT_FONT_FACE "pseudo.Courier"
