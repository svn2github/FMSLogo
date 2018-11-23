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
// This file contains localized strings for German by Stephan Vogel
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
#define LOCALIZED_ALTERNATE_TRUE     "wahr"
#define LOCALIZED_ALTERNATE_FALSE    "falsch"
#define LOCALIZED_ALTERNATE_END      "ende"
#define LOCALIZED_ALTERNATE_TOPLEVEL "Ausstieg"
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
#define LOCALIZED_ALTERNATE__DEFMACRO              ".defMakro"
#define LOCALIZED_ALTERNATE__EQ                    ".eq"
#define LOCALIZED_ALTERNATE__MACRO                 ".Makro"
#define LOCALIZED_ALTERNATE__MAYBEOUTPUT           ".maybeoutput"
#define LOCALIZED_ALTERNATE__SETBF                 ".setbf"
#define LOCALIZED_ALTERNATE__SETFIRST              ".setfirst"
#define LOCALIZED_ALTERNATE__SETITEM               ".setitem"
#define LOCALIZED_ALTERNATE_ACTIVEAREA             "aktiverBereich"
#define LOCALIZED_ALTERNATE_ALLOPEN                "offenZ"
#define LOCALIZED_ALTERNATE_AND                    "alle?"
#define LOCALIZED_ALTERNATE_APPLY                  "benutze"
#define LOCALIZED_ALTERNATE_ARCCOS                 "arccos"
#define LOCALIZED_ALTERNATE_ARCSIN                 "arcsin"
#define LOCALIZED_ALTERNATE_ARCTAN                 "arctan"
#define LOCALIZED_ALTERNATE_ARITY                  "arity" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARRAY                  "Array"
#define LOCALIZED_ALTERNATE_ARRAYP                 "arrayp"
#define LOCALIZED_ALTERNATE_ARRAY_                 "Array?"
#define LOCALIZED_ALTERNATE_ASCII                  "asc"
#define LOCALIZED_ALTERNATE_ASHIFT                 "ashift"
#define LOCALIZED_ALTERNATE_BACK                   "rückwärts"
#define LOCALIZED_ALTERNATE_BACKSLASHEDP           "backslashedp"
#define LOCALIZED_ALTERNATE_BACKSLASHED_           "backslashed?"
#define LOCALIZED_ALTERNATE_BEFOREP                "beforep"
#define LOCALIZED_ALTERNATE_BEFORE_                "vorher?"
#define LOCALIZED_ALTERNATE_BF                     "oe"
#define LOCALIZED_ALTERNATE_BFS                    "oea"
#define LOCALIZED_ALTERNATE_BITAND                 "bitund"
#define LOCALIZED_ALTERNATE_BITBLOCK               "Bitblock"
#define LOCALIZED_ALTERNATE_BITCOPY                "Bitkopieren"
#define LOCALIZED_ALTERNATE_BITCUT                 "Bitausschneiden"
#define LOCALIZED_ALTERNATE_BITFIT                 "bitfit"
#define LOCALIZED_ALTERNATE_BITINDEX               "Bitindex"
#define LOCALIZED_ALTERNATE_BITLOAD                "Bitladen"
#define LOCALIZED_ALTERNATE_BITLOADSIZE            "bitloadsize"
#define LOCALIZED_ALTERNATE_BITSIZE                "Bitgröße"
#define LOCALIZED_ALTERNATE_BITMAPTURTLE           "bitmapturtle"
#define LOCALIZED_ALTERNATE_BITMODE                "bitmodus"
#define LOCALIZED_ALTERNATE_BITNOT                 "bitnicht"
#define LOCALIZED_ALTERNATE_BITOR                  "bitoder"
#define LOCALIZED_ALTERNATE_BITPASTE               "Biteinfügen"
#define LOCALIZED_ALTERNATE_BITPASTETOINDEX        "Biteinfügeninindex"
#define LOCALIZED_ALTERNATE_BITSAVE                "Bitbewahren"
#define LOCALIZED_ALTERNATE_BITXOR                 "bitxoder"
#define LOCALIZED_ALTERNATE_BK                     "rw"
#define LOCALIZED_ALTERNATE_BL                     "ol"
#define LOCALIZED_ALTERNATE_BURIED                 "versteckt"
#define LOCALIZED_ALTERNATE_BURY                   "verstecke"
#define LOCALIZED_ALTERNATE_BUTFIRST               "ohneerstes"
#define LOCALIZED_ALTERNATE_BUTFIRSTS              "butfirsts"
#define LOCALIZED_ALTERNATE_BUTLAST                "ohneletztes"
#define LOCALIZED_ALTERNATE_BUTTONCREATE           "Knopfschaffen"
#define LOCALIZED_ALTERNATE_BUTTONDELETE           "Knopflöschen"
#define LOCALIZED_ALTERNATE_BUTTONENABLE           "Knopfstatus"
#define LOCALIZED_ALTERNATE_BUTTONUPDATE           "Knopfneu"
#define LOCALIZED_ALTERNATE_BUTTONP                "buttonp"
#define LOCALIZED_ALTERNATE_BUTTON_                "Knopf?"
#define LOCALIZED_ALTERNATE_BYE                    "ade"
#define LOCALIZED_ALTERNATE_CATCH                  "fange"
#define LOCALIZED_ALTERNATE_CHAR                   "Zeichen"
#define LOCALIZED_ALTERNATE_CHDIR                  "chdir"
#define LOCALIZED_ALTERNATE_CHECKBOXCREATE         "Kontrollboxschaffen"
#define LOCALIZED_ALTERNATE_CHECKBOXDELETE         "Kontrollboxlöschen"
#define LOCALIZED_ALTERNATE_CHECKBOXENABLE         "Kontrollboxstatus"
#define LOCALIZED_ALTERNATE_CHECKBOXGET            "Kontrollboxstatus?"
#define LOCALIZED_ALTERNATE_CHECKBOXSET            "Kontrollboxset"
#define LOCALIZED_ALTERNATE_CLEAN                  "lb"
#define LOCALIZED_ALTERNATE_CLEARPALETTE           "LöschePalette"
#define LOCALIZED_ALTERNATE_CLEARSCREEN            "bild"
#define LOCALIZED_ALTERNATE_CLEARTEXT              "LöscheText"
#define LOCALIZED_ALTERNATE_CLEARTIMER             "LöscheZeitnehmer"
#define LOCALIZED_ALTERNATE_CLOSE                  "schließe"
#define LOCALIZED_ALTERNATE_CLOSEALL               "schließealles"
#define LOCALIZED_ALTERNATE_CO                     "wt"
#define LOCALIZED_ALTERNATE_COMBOBOXADDSTRING      "Komtaboxtext"
#define LOCALIZED_ALTERNATE_COMBOBOXCREATE         "Komtaboxschaffen"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETE         "Komtaboxlöschen"
#define LOCALIZED_ALTERNATE_COMBOBOXENABLE         "Komtaboxstatus"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING   "Komtaboxtextlöschen"
#define LOCALIZED_ALTERNATE_COMBOBOXGETTEXT        "Komtaboxtextliste"
#define LOCALIZED_ALTERNATE_COMBOBOXSETTEXT        "Komtaboxsetzetext"
#define LOCALIZED_ALTERNATE_CONTENTS               "Titelliste"
#define LOCALIZED_ALTERNATE_CONTINUE               "weiter"
#define LOCALIZED_ALTERNATE_COPYDEF                "copydef"
#define LOCALIZED_ALTERNATE_COS                    "cos"
#define LOCALIZED_ALTERNATE_COUNT                  "Länge"
#define LOCALIZED_ALTERNATE_CS                     "cs"
#define LOCALIZED_ALTERNATE_CT                     "ls"
#define LOCALIZED_ALTERNATE_CURSOR                 "BO"
#define LOCALIZED_ALTERNATE_DEBUGWINDOWS           "Fensterbaum"
#define LOCALIZED_ALTERNATE_DEFINE                 "def"
#define LOCALIZED_ALTERNATE_DEFINEDP               "def?"
#define LOCALIZED_ALTERNATE_DEFINED_               "definiert?"
#define LOCALIZED_ALTERNATE_DIALOGCREATE           "Dialogschaffen"
#define LOCALIZED_ALTERNATE_DIALOGENABLE           "Dialogstatus"
#define LOCALIZED_ALTERNATE_DIALOGDELETE           "Dialoglöschen"
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         "dialogfileopen"
#define LOCALIZED_ALTERNATE_DIALOGFILESAVE         "dialogfilesave"
#define LOCALIZED_ALTERNATE_DIFFERENCE             "Differenz"
#define LOCALIZED_ALTERNATE_DIRECTORIES            "directories"
#define LOCALIZED_ALTERNATE_DLLCALL                "dllrufen"
#define LOCALIZED_ALTERNATE_DLLFREE                "dllfrei"
#define LOCALIZED_ALTERNATE_DLLLOAD                "dllladen"
#define LOCALIZED_ALTERNATE_DOWN                   "down"
#define LOCALIZED_ALTERNATE_DOWNPITCH              "downpitch"
#define LOCALIZED_ALTERNATE_DRIBBLE                "dribble"
#define LOCALIZED_ALTERNATE_ED                     "ed"
#define LOCALIZED_ALTERNATE_EDIT                   "edit"
#define LOCALIZED_ALTERNATE_ELLIPSEARC             "ellipsearc"
#define LOCALIZED_ALTERNATE_EMPTYP                 "emptyp"
#define LOCALIZED_ALTERNATE_EMPTY_                 "leer?"
#define LOCALIZED_ALTERNATE_EOFP                   "eofp"
#define LOCALIZED_ALTERNATE_EOF_                   "Dateiende?"
#define LOCALIZED_ALTERNATE_EQUALP                 "equalp"
#define LOCALIZED_ALTERNATE_EQUAL_                 "gleich?"
#define LOCALIZED_ALTERNATE_ER                     "erstes"
#define LOCALIZED_ALTERNATE_ERASE                  "vg"
#define LOCALIZED_ALTERNATE_ERASEFILE              "vergissDatei"
#define LOCALIZED_ALTERNATE_ERF                    "vd"
#define LOCALIZED_ALTERNATE_ERROR                  "Fehler"
#define LOCALIZED_ALTERNATE_EVENTCHECK             "EreignisProtokoll"
#define LOCALIZED_ALTERNATE_EXP                    "exp"
#define LOCALIZED_ALTERNATE_FD                     "vw"
#define LOCALIZED_ALTERNATE_FENCE                  "Rand"
#define LOCALIZED_ALTERNATE_FILL                   "fülle"
#define LOCALIZED_ALTERNATE_FILES                  "files"
#define LOCALIZED_ALTERNATE_FIRST                  "er"
#define LOCALIZED_ALTERNATE_FIRSTS                 "aer"
#define LOCALIZED_ALTERNATE_FLOODCOLOR             "Füllfarbez"
#define LOCALIZED_ALTERNATE_FONTFACENAMES          "fontfacenames"
#define LOCALIZED_ALTERNATE_FOREVER                "andauernd"
#define LOCALIZED_ALTERNATE_FORM                   "Zahlformat"
#define LOCALIZED_ALTERNATE_FORWARD                "vorwärts"
#define LOCALIZED_ALTERNATE_FPUT                   "me"
#define LOCALIZED_ALTERNATE_FS                     "vb"
#define LOCALIZED_ALTERNATE_FULLSCREEN             "Vollbild"
#define LOCALIZED_ALTERNATE_FULLTEXT               "Prtext"
#define LOCALIZED_ALTERNATE_GETFOCUS               "getfocus"
#define LOCALIZED_ALTERNATE_GOTO                   "gehe"
#define LOCALIZED_ALTERNATE_GIFLOAD                "gifload"
#define LOCALIZED_ALTERNATE_GIFSIZE                "gifsize"
#define LOCALIZED_ALTERNATE_GIFSAVE                "gifsave"
#define LOCALIZED_ALTERNATE_GPROP                  "gibEg"
#define LOCALIZED_ALTERNATE_GREATEREQUALP          "greaterequalp"
#define LOCALIZED_ALTERNATE_GREATEREQUAL_          "größergleich?"
#define LOCALIZED_ALTERNATE_GREATERP               "greaterp"
#define LOCALIZED_ALTERNATE_GREATER_               "größer?"
#define LOCALIZED_ALTERNATE_GROUPBOXCREATE         "Gruppenboxschaffen"
#define LOCALIZED_ALTERNATE_GROUPBOXDELETE         "Gruppenboxlöschen"
#define LOCALIZED_ALTERNATE_HALT                   "halt"
#define LOCALIZED_ALTERNATE_HASOWNPENP             "hasownpenp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HASOWNPEN_             "hasownpen?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HEADING                "Kurs"
#define LOCALIZED_ALTERNATE_HELP                   "help"
#define LOCALIZED_ALTERNATE_HIDETURTLE             "vergissIgel"
#define LOCALIZED_ALTERNATE_HOME                   "Mitte"
#define LOCALIZED_ALTERNATE_HT                     "vi"
#define LOCALIZED_ALTERNATE_IF                     "wenn"
#define LOCALIZED_ALTERNATE_IFELSE                 "wennsonst"
#define LOCALIZED_ALTERNATE_IFF                    "wf"
#define LOCALIZED_ALTERNATE_IFFALSE                "wennfalsch"
#define LOCALIZED_ALTERNATE_IFT                    "ww"
#define LOCALIZED_ALTERNATE_IFTRUE                 "wennwahr"
#define LOCALIZED_ALTERNATE_INGAMEPORT             "Ingameport"
#define LOCALIZED_ALTERNATE_INPORT                 "inport"
#define LOCALIZED_ALTERNATE_INPORTB                "inportb"
#define LOCALIZED_ALTERNATE_INT                    "ganzzahl"
#define LOCALIZED_ALTERNATE_ITEM                   "Element"
#define LOCALIZED_ALTERNATE_KEYBOARDOFF            "keyboardaus"
#define LOCALIZED_ALTERNATE_KEYBOARDON             "keyboardein"
#define LOCALIZED_ALTERNATE_KEYBOARDVALUE          "TastEG"
#define LOCALIZED_ALTERNATE_KEYP                   "keyp"
#define LOCALIZED_ALTERNATE_KEY_                   "Taste?"
#define LOCALIZED_ALTERNATE_LABEL                  "Igeltext"
#define LOCALIZED_ALTERNATE_LABELFONT              "labelfont"
#define LOCALIZED_ALTERNATE_LABELSIZE              "längeigeltext"
#define LOCALIZED_ALTERNATE_LAST                   "lz"
#define LOCALIZED_ALTERNATE_LEFT                   "links"
#define LOCALIZED_ALTERNATE_LEFTROLL               "leftroll"
#define LOCALIZED_ALTERNATE_LESSEQUALP             "lessequalp"
#define LOCALIZED_ALTERNATE_LESSEQUAL_             "kleinergleich?"
#define LOCALIZED_ALTERNATE_LESSP                  "lessp"
#define LOCALIZED_ALTERNATE_LESS_                  "kleiner?"
#define LOCALIZED_ALTERNATE_LIGHT                  "light"
#define LOCALIZED_ALTERNATE_LIST                   "Liste"
#define LOCALIZED_ALTERNATE_LISTBOXADDSTRING       "Listeboxtext"
#define LOCALIZED_ALTERNATE_LISTBOXCREATE          "Listeboxschaffen"
#define LOCALIZED_ALTERNATE_LISTBOXENABLE          "Listeboxstatus"
#define LOCALIZED_ALTERNATE_LISTBOXDELETE          "Listeboxlöschen"
#define LOCALIZED_ALTERNATE_LISTBOXDELETESTRING    "Listeboxlöschetext"
#define LOCALIZED_ALTERNATE_LISTBOXGETSELECT       "Listeboxwahl"
#define LOCALIZED_ALTERNATE_LISTP                  "listp"
#define LOCALIZED_ALTERNATE_LIST_                  "Liste?"
#define LOCALIZED_ALTERNATE_LN                     "ln"
#define LOCALIZED_ALTERNATE_LOAD                   "lade"
#define LOCALIZED_ALTERNATE_LOCAL                  "lokal"
#define LOCALIZED_ALTERNATE_LOG10                  "log10"
#define LOCALIZED_ALTERNATE_LOGOVERSION            "Logoversion"
#define LOCALIZED_ALTERNATE_LOWERCASE              "klein"
#define LOCALIZED_ALTERNATE_LPUT                   "ml"
#define LOCALIZED_ALTERNATE_LR                     "lr"
#define LOCALIZED_ALTERNATE_LSHIFT                 "lshift"
#define LOCALIZED_ALTERNATE_LT                     "li"
#define LOCALIZED_ALTERNATE_MACHINE                "machine"
#define LOCALIZED_ALTERNATE_MACROP                 "macrop"
#define LOCALIZED_ALTERNATE_MACRO_                 "Makro?"
#define LOCALIZED_ALTERNATE_MAKE                   "setze"
#define LOCALIZED_ALTERNATE_MCI                    "mci"
#define LOCALIZED_ALTERNATE_MEMBER                 "Elementab"
#define LOCALIZED_ALTERNATE_MEMBERP                "Element?"
#define LOCALIZED_ALTERNATE_MEMBER_                "El?"
#define LOCALIZED_ALTERNATE_MESSAGEBOX             "Meldungsbox"
#define LOCALIZED_ALTERNATE_MIDICLOSE              "Midischließen"
#define LOCALIZED_ALTERNATE_MIDIMESSAGE            "Midimeldung"
#define LOCALIZED_ALTERNATE_MIDIOPEN               "Midiöffnen"
#define LOCALIZED_ALTERNATE_MINUS                  "minus"
#define LOCALIZED_ALTERNATE_MKDIR                  "mkdir"
#define LOCALIZED_ALTERNATE_MODULO                 "modulo"
#define LOCALIZED_ALTERNATE_MOUSEOFF               "Mausaus"
#define LOCALIZED_ALTERNATE_MOUSEON                "Mausan"
#define LOCALIZED_ALTERNATE_MOUSEPOS               "MausOrt"
#define LOCALIZED_ALTERNATE_NAMEP                  "namep"
#define LOCALIZED_ALTERNATE_NAME_                  "Name?"
#define LOCALIZED_ALTERNATE_NAMES                  "Namen"
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           "netzannahmeaus"
#define LOCALIZED_ALTERNATE_NETACCEPTON            "netzannahmeein"
#define LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE  "netzannahmewertempfangen"
#define LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE     "netzannahmewertsenden"
#define LOCALIZED_ALTERNATE_NETCONNECTOFF          "netzunterbrechen"
#define LOCALIZED_ALTERNATE_NETCONNECTON           "netzverbinden"
#define LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE "netzverbundwertempfangen"
#define LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE    "netzverbundwertsenden"
#define LOCALIZED_ALTERNATE_NETSHUTDOWN            "netzbeenden"
#define LOCALIZED_ALTERNATE_NETSTARTUP             "netstarten"
#define LOCALIZED_ALTERNATE_NOBITMAPTURTLE         "nobitmapturtle"
#define LOCALIZED_ALTERNATE_NODES                  "Knoten"
#define LOCALIZED_ALTERNATE_NODRIBBLE              "nodribble"
#define LOCALIZED_ALTERNATE_NOSTATUS               "K.Status"
#define LOCALIZED_ALTERNATE_NOT                    "nicht?"
#define LOCALIZED_ALTERNATE_NOTEQUALP              "notequalp"
#define LOCALIZED_ALTERNATE_NOTEQUAL_              "nichtgleich?"
#define LOCALIZED_ALTERNATE_NOYIELD                "noyield"
#define LOCALIZED_ALTERNATE_NUMBERP                "numberp"
#define LOCALIZED_ALTERNATE_NUMBER_                "Zahl?"
#define LOCALIZED_ALTERNATE_OP                     "rg"
#define LOCALIZED_ALTERNATE_OPENAPPEND             "openappend"
#define LOCALIZED_ALTERNATE_OPENREAD               "openread"
#define LOCALIZED_ALTERNATE_OPENUPDATE             "openupdate"
#define LOCALIZED_ALTERNATE_OPENWRITE              "openwrite"
#define LOCALIZED_ALTERNATE_OR                     "eines?"
#define LOCALIZED_ALTERNATE_OUTPORT                "outport"
#define LOCALIZED_ALTERNATE_OUTPORTB               "outportb"
#define LOCALIZED_ALTERNATE_OUTPUT                 "Rückgabe"
#define LOCALIZED_ALTERNATE_PARSE                  "parse"
#define LOCALIZED_ALTERNATE_PAUSE                  "Pause"
#define LOCALIZED_ALTERNATE_PC                     "pc"
#define LOCALIZED_ALTERNATE_PD                     "sa"
#define LOCALIZED_ALTERNATE_PE                     "rd"
#define LOCALIZED_ALTERNATE_PENCOLOR               "FarbeZ"
#define LOCALIZED_ALTERNATE_PENDOWN                "Stiftab"
#define LOCALIZED_ALTERNATE_PENDOWNP               "pendownp"
#define LOCALIZED_ALTERNATE_PENDOWN_               "Stiftab?"
#define LOCALIZED_ALTERNATE_PENERASE               "radiere"
#define LOCALIZED_ALTERNATE_PENMODE                "Stiftmodus"
#define LOCALIZED_ALTERNATE_PENPAINT               "Normalstift"
#define LOCALIZED_ALTERNATE_PENPATTERN             "Stiftform"
#define LOCALIZED_ALTERNATE_PENREVERSE             "Umkehrstift"
#define LOCALIZED_ALTERNATE_PENSIZE                "StiftZ"
#define LOCALIZED_ALTERNATE_PENUP                  "Stifthoch"
#define LOCALIZED_ALTERNATE_PERSPECTIVE            "Perspektive"
#define LOCALIZED_ALTERNATE_PITCH                  "pitch"
#define LOCALIZED_ALTERNATE_PIXEL                  "pixel"
#define LOCALIZED_ALTERNATE_PLAYWAVE               "spielewave"
#define LOCALIZED_ALTERNATE_PLIST                  "Egliste"
#define LOCALIZED_ALTERNATE_PLISTS                 "Eglisten"
#define LOCALIZED_ALTERNATE_PO                     "zg"
#define LOCALIZED_ALTERNATE_POPDIR                 "popdir"
#define LOCALIZED_ALTERNATE_POLYSTART              "Polystart"
#define LOCALIZED_ALTERNATE_POLYEND                "polyende"
#define LOCALIZED_ALTERNATE_POLYVIEW               "Polysehen"
#define LOCALIZED_ALTERNATE_PORTCLOSE              "portschließen"
#define LOCALIZED_ALTERNATE_PORTFLUSH              "portfluten"
#define LOCALIZED_ALTERNATE_PORTMODE               "portmodus"
#define LOCALIZED_ALTERNATE_PORTOPEN               "portöffnen"
#define LOCALIZED_ALTERNATE_PORTREADARRAY          "portliesarray"
#define LOCALIZED_ALTERNATE_PORTREADCHAR           "portlieszeichen"
#define LOCALIZED_ALTERNATE_PORTWRITEARRAY         "portschreibearray"
#define LOCALIZED_ALTERNATE_PORTWRITECHAR          "portschreibezeichen"
#define LOCALIZED_ALTERNATE_POS                    "Ort"
#define LOCALIZED_ALTERNATE_POSXYZ                 "Ortxyz"
#define LOCALIZED_ALTERNATE_POT                    "zt"
#define LOCALIZED_ALTERNATE_POWER                  "Potenz"
#define LOCALIZED_ALTERNATE_PPROP                  "MitEg"
#define LOCALIZED_ALTERNATE_PPT                    "SMale"
#define LOCALIZED_ALTERNATE_PR                     "dz"
#define LOCALIZED_ALTERNATE_PRIMITIVEP             "primitivep"
#define LOCALIZED_ALTERNATE_PRIMITIVE_             "Grundwort?"
#define LOCALIZED_ALTERNATE_PRINT                  "druckezeile"
#define LOCALIZED_ALTERNATE_PROCEDUREP             "procedurep"
#define LOCALIZED_ALTERNATE_PROCEDURE_             "Prozedur?"
#define LOCALIZED_ALTERNATE_PROPLISTP              "proplistp"
#define LOCALIZED_ALTERNATE_PROPLIST_              "proplist?"
#define LOCALIZED_ALTERNATE_PROCEDURES             "Prozedurliste"
#define LOCALIZED_ALTERNATE_PRODUCT                "Produkt"
#define LOCALIZED_ALTERNATE_PU                     "sh"
#define LOCALIZED_ALTERNATE_PX                     "sr"
#define LOCALIZED_ALTERNATE_QUESTIONBOX            "Fragebox"
#define LOCALIZED_ALTERNATE_QUOTIENT               "Quotient"
#define LOCALIZED_ALTERNATE_RADARCCOS              "radarccos"
#define LOCALIZED_ALTERNATE_RADARCSIN              "radarcsin"
#define LOCALIZED_ALTERNATE_RADARCTAN              "radarctan"
#define LOCALIZED_ALTERNATE_RADCOS                 "radcos"
#define LOCALIZED_ALTERNATE_RADIOBUTTONCREATE      "Radioknopfschaffen"
#define LOCALIZED_ALTERNATE_RADIOBUTTONENABLE      "Radioknopfstatus"
#define LOCALIZED_ALTERNATE_RADIOBUTTONDELETE      "Radioknopflöschen"
#define LOCALIZED_ALTERNATE_RADIOBUTTONGET         "Radioknopfstatus?"
#define LOCALIZED_ALTERNATE_RADIOBUTTONSET         "Radioknopfaktiv"
#define LOCALIZED_ALTERNATE_RADSIN                 "radsin"
#define LOCALIZED_ALTERNATE_RADTAN                 "radtan"
#define LOCALIZED_ALTERNATE_RANDOM                 "zz"
#define LOCALIZED_ALTERNATE_RAWASCII               "rawascii"
#define LOCALIZED_ALTERNATE_RC                     "Liestaste"
#define LOCALIZED_ALTERNATE_RCS                    "Liestasten"
#define LOCALIZED_ALTERNATE_READCHAR               "readchar"
#define LOCALIZED_ALTERNATE_READCHARS              "liesZeichen"
#define LOCALIZED_ALTERNATE_READER                 "reader"
#define LOCALIZED_ALTERNATE_READLIST               "liesListe"
#define LOCALIZED_ALTERNATE_READPOS                "Liespos"
#define LOCALIZED_ALTERNATE_READRAWLINE            "readrawline" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READWORD               "liesWort"
#define LOCALIZED_ALTERNATE_REMAINDER              "Rest"
#define LOCALIZED_ALTERNATE_REMPROP                "vgEg"
#define LOCALIZED_ALTERNATE_REPCOUNT               "whZahl"
#define LOCALIZED_ALTERNATE_REPEAT                 "wh"
#define LOCALIZED_ALTERNATE_RERANDOM               "sZ"
#define LOCALIZED_ALTERNATE_RIGHT                  "rechts"
#define LOCALIZED_ALTERNATE_RIGHTROLL              "rightroll"
#define LOCALIZED_ALTERNATE_RL                     "ll"
#define LOCALIZED_ALTERNATE_RMDIR                  "rmdir"
#define LOCALIZED_ALTERNATE_ROLL                   "roll"
#define LOCALIZED_ALTERNATE_ROUND                  "runde"
#define LOCALIZED_ALTERNATE_RR                     "rr"
#define LOCALIZED_ALTERNATE_RT                     "re"
#define LOCALIZED_ALTERNATE_RUN                    "tue"
#define LOCALIZED_ALTERNATE_RUNPARSE               "runparse"
#define LOCALIZED_ALTERNATE_RUNRESULT              "tueWert"
#define LOCALIZED_ALTERNATE_RW                     "rw"
#define LOCALIZED_ALTERNATE_SAVE                   "bw"
#define LOCALIZED_ALTERNATE_SCREENCOLOR            "hgz"
#define LOCALIZED_ALTERNATE_SCROLLBARCREATE        "Rollbalkenschaffen"
#define LOCALIZED_ALTERNATE_SCROLLBARENABLE        "Rollbalkenstatus"
#define LOCALIZED_ALTERNATE_SCROLLBARDELETE        "Rollbalkenlöschen"
#define LOCALIZED_ALTERNATE_SCROLLBARGET           "Rollbalkenwert"
#define LOCALIZED_ALTERNATE_SCROLLBARSET           "Rollbalkendef"
#define LOCALIZED_ALTERNATE_SCROLLX                "scrollx"
#define LOCALIZED_ALTERNATE_SCROLLY                "scrolly"
#define LOCALIZED_ALTERNATE_SCRUNCH                "Skalaz"
#define LOCALIZED_ALTERNATE_SE                     "se"
#define LOCALIZED_ALTERNATE_SELECTBOX              "auswahlbox"
#define LOCALIZED_ALTERNATE_SENTENCE               "satz"
#define LOCALIZED_ALTERNATE_SETACTIVEAREA          "setactivearea"
#define LOCALIZED_ALTERNATE_SETBITINDEX            "setbitindex"
#define LOCALIZED_ALTERNATE_SETBITMODE             "setbitmode"
#define LOCALIZED_ALTERNATE_SETCLIP                "setclip"
#define LOCALIZED_ALTERNATE_SETCURSOR              "setcursor"
#define LOCALIZED_ALTERNATE_SETCURSORNOWAIT        "setcursornowait"
#define LOCALIZED_ALTERNATE_SETCURSORWAIT          "setcursorwait"
#define LOCALIZED_ALTERNATE_SETFC                  "setfc"
#define LOCALIZED_ALTERNATE_SETFLOODCOLOR          "Füllfarbe"
#define LOCALIZED_ALTERNATE_SETFOCUS               "setfocus"
#define LOCALIZED_ALTERNATE_SETH                   "ak"
#define LOCALIZED_ALTERNATE_SETHEADING             "aufkurs"
#define LOCALIZED_ALTERNATE_SETITEM                "setitem"
#define LOCALIZED_ALTERNATE_SETLABELFONT           "setKennungSchrift"
#define LOCALIZED_ALTERNATE_SETLIGHT               "setlight"
#define LOCALIZED_ALTERNATE_SETMARGINS             "setmargins"
#define LOCALIZED_ALTERNATE_SETPC                  "Farbe"
#define LOCALIZED_ALTERNATE_SETPENCOLOR            "Stiftfarbe"
#define LOCALIZED_ALTERNATE_SETPENPATTERN          "StiftFarbMuster"
#define LOCALIZED_ALTERNATE_SETPENSIZE             "Stiftdicke"
#define LOCALIZED_ALTERNATE_SETPITCH               "setpitch"
#define LOCALIZED_ALTERNATE_SETPIXEL               "setpixel"
#define LOCALIZED_ALTERNATE_SETPOS                 "auf"
#define LOCALIZED_ALTERNATE_SETPOSXYZ              "setposxyz" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETREAD                "LiesDatei"
#define LOCALIZED_ALTERNATE_SETREADPOS             "setreadpos"
#define LOCALIZED_ALTERNATE_SETROLL                "setroll"
#define LOCALIZED_ALTERNATE_SETSC                  "hg"
#define LOCALIZED_ALTERNATE_SETSCREENCOLOR         "Hintergrundfarbe"
#define LOCALIZED_ALTERNATE_SETSCRUNCH             "Skala"
#define LOCALIZED_ALTERNATE_SETTIMER               "setzeZeitnehmer"
#define LOCALIZED_ALTERNATE_SETTURTLE              "setzeigel"
#define LOCALIZED_ALTERNATE_SETTURTLEMODE          "setzeigelmodus"
#define LOCALIZED_ALTERNATE_SETWRITE               "Kopieein"
#define LOCALIZED_ALTERNATE_SETWRITEPOS            "setwritepos"
#define LOCALIZED_ALTERNATE_SETX                   "aufx"
#define LOCALIZED_ALTERNATE_SETXY                  "aufxy"
#define LOCALIZED_ALTERNATE_SETXYZ                 "aufxyz"
#define LOCALIZED_ALTERNATE_SETY                   "aufy"
#define LOCALIZED_ALTERNATE_SETZ                   "aufz"
#define LOCALIZED_ALTERNATE_SHELL                  "shell"
#define LOCALIZED_ALTERNATE_SHOW                   "dzl"
#define LOCALIZED_ALTERNATE_SHOWNP                 "shownp"
#define LOCALIZED_ALTERNATE_SHOWN_                 "sichtbar?"
#define LOCALIZED_ALTERNATE_SHOWTURTLE             "zeigIgel"
#define LOCALIZED_ALTERNATE_SIN                    "sin"
#define LOCALIZED_ALTERNATE_SOUND                  "Sound"
#define LOCALIZED_ALTERNATE_SPLITSCREEN            "Teilbild"
#define LOCALIZED_ALTERNATE_SQRT                   "qw"
#define LOCALIZED_ALTERNATE_SS                     "ss"
#define LOCALIZED_ALTERNATE_ST                     "zi"
#define LOCALIZED_ALTERNATE_STANDOUT               "hervorheben"
#define LOCALIZED_ALTERNATE_STATICCREATE           "Statuszeileschaffen"
#define LOCALIZED_ALTERNATE_STATICDELETE           "Statuszeilelöschen"
#define LOCALIZED_ALTERNATE_STATICUPDATE           "Statuszeileneu"
#define LOCALIZED_ALTERNATE_STATUS                 "Status"
#define LOCALIZED_ALTERNATE_STEP                   "PSe"
#define LOCALIZED_ALTERNATE_STEPPED                "stepped"
#define LOCALIZED_ALTERNATE_STOP                   "rk"
#define LOCALIZED_ALTERNATE_SUBSTRINGP             "substringp"
#define LOCALIZED_ALTERNATE_SUBSTRING_             "substring?"
#define LOCALIZED_ALTERNATE_SUM                    "Summe"
#define LOCALIZED_ALTERNATE_TAG                    "tag"
#define LOCALIZED_ALTERNATE_TAN                    "tan"
#define LOCALIZED_ALTERNATE_TEST                   "prüfe"
#define LOCALIZED_ALTERNATE_TEXT                   "PrListe"
#define LOCALIZED_ALTERNATE_TEXTSCREEN             "TextSchirm"
#define LOCALIZED_ALTERNATE_THING                  "Wert"
#define LOCALIZED_ALTERNATE_THROW                  "wirf"
#define LOCALIZED_ALTERNATE_TIME                   "Zeit"
#define LOCALIZED_ALTERNATE_TIMEMILLI              "ZeitMilli"
#define LOCALIZED_ALTERNATE_TO                     "pr"
#define LOCALIZED_ALTERNATE_TONE                   "Ton"
#define LOCALIZED_ALTERNATE_TOWARDS                "ri"
#define LOCALIZED_ALTERNATE_TOWARDSXYZ             "Richtungxyz"
#define LOCALIZED_ALTERNATE_TRACE                  "Pein"
#define LOCALIZED_ALTERNATE_TRACED                 "traced"
#define LOCALIZED_ALTERNATE_TS                     "ts"
#define LOCALIZED_ALTERNATE_TURTLE                 "Igel"
#define LOCALIZED_ALTERNATE_TURTLEMODE             "turtlemode"
#define LOCALIZED_ALTERNATE_TURTLES                "Igelschar"
#define LOCALIZED_ALTERNATE_TYPE                   "drucke"
#define LOCALIZED_ALTERNATE_UNBURY                 "grabeaus"
#define LOCALIZED_ALTERNATE_UNSTEP                 "PSa"
#define LOCALIZED_ALTERNATE_UNTRACE                "Pa"
#define LOCALIZED_ALTERNATE_UP                     "up"
#define LOCALIZED_ALTERNATE_UPPERCASE              "groß"
#define LOCALIZED_ALTERNATE_UPPITCH                "uppitch"
#define LOCALIZED_ALTERNATE_WAIT                   "warte"
#define LOCALIZED_ALTERNATE_WINDOW                 "fenster"
#define LOCALIZED_ALTERNATE_WINDOWCREATE           "Fensterschaffen"
#define LOCALIZED_ALTERNATE_WINDOWENABLE           "Fensterstatus"
#define LOCALIZED_ALTERNATE_WINDOWDELETE           "Fensterlöschen"
#define LOCALIZED_ALTERNATE_WINDOWFILEEDIT         "windowfileedit"
#define LOCALIZED_ALTERNATE_WINDOWSET              "windowset"
#define LOCALIZED_ALTERNATE_WINHELP                "winhelp"
#define LOCALIZED_ALTERNATE_WORD                   "Wort"
#define LOCALIZED_ALTERNATE_WORDP                  "wordp?"
#define LOCALIZED_ALTERNATE_WORD_                  "Wort?"
#define LOCALIZED_ALTERNATE_WRAP                   "Randsprung"
#define LOCALIZED_ALTERNATE_WRITEPOS               "writepos"
#define LOCALIZED_ALTERNATE_WRITER                 "writer"
#define LOCALIZED_ALTERNATE_YESNOBOX               "JaNeinBox"
#define LOCALIZED_ALTERNATE_YIELD                  "yield"
#define LOCALIZED_ALTERNATE_ZOOM                   "Zoom"

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      "OK"
#define LOCALIZED_GENERAL_CANCELBUTTON  "Abbruch"
#define LOCALIZED_GENERAL_APPLYBUTTON   "&Übernahme"

#define LOCALIZED_GENERAL_PRODUCTNAME   "FMSLogo"

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  "Die FMSLogo-Programmierumgebung"

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  "&Datei"
#define LOCALIZED_FILE_NEW              "&Neu\t(löscht Arbeitsspeicher)"
#define LOCALIZED_FILE_LOAD             "&Lade...\t(stellt in den Arbeitsspeicher)"
#define LOCALIZED_FILE_OPEN             "Ö&ffne...\t(ersetzt Arbeitsspeicher)" 
#define LOCALIZED_FILE_SAVE             "&Speichern" 
#define LOCALIZED_FILE_SAVEAS           "Speichern &unter..."
#define LOCALIZED_FILE_SETASSCREENSAVER "Legen Sie als Bildschirmschoner"
#define LOCALIZED_FILE_EDIT             "&Edit..."
#define LOCALIZED_FILE_ERASE            "&Löschen..."
#define LOCALIZED_FILE_EXIT             "&Beenden"

#define LOCALIZED_BITMAP               "&Bild"
#define LOCALIZED_BITMAP_NEW           "&Neu"
#define LOCALIZED_BITMAP_LOAD          "&Lade..."
#define LOCALIZED_BITMAP_SAVE          "&Bewahre..."
#define LOCALIZED_BITMAP_SAVEAS        "Speichern &als..."
#define LOCALIZED_BITMAP_PRINT         "&Drucken..."
#define LOCALIZED_BITMAP_PRINTERSETUP  "Drucker&setup..."
#define LOCALIZED_BITMAP_ACTIVEAREA    "A&ktiver Bereich..."

#define LOCALIZED_SET                  "&Optionen"
#define LOCALIZED_SET_PENSIZE          "Stift&dicke..."
#define LOCALIZED_SET_LABELFONT        "&Grafik-Schrift..."
#define LOCALIZED_SET_COMMANDERFONT    "&Befehle-Schrift..."
#define LOCALIZED_SET_PENCOLOR         "&Stiftfarbe..."
#define LOCALIZED_SET_FLOODCOLOR       "&Füllfarbe..."
#define LOCALIZED_SET_SCREENCOLOR      "&Hintergrundfarbe..."

#define LOCALIZED_ZOOM                 "&Zoom" 
#define LOCALIZED_ZOOM_IN              "&<<"
#define LOCALIZED_ZOOM_OUT             "&>>"
#define LOCALIZED_ZOOM_NORMAL          "&Normal"

#define LOCALIZED_HELP                 "&Hilfen" 
#define LOCALIZED_HELP_INDEX           "&Index"
#define LOCALIZED_HELP_TUTORIAL        "&Tutorial"
#define LOCALIZED_HELP_DEMO            "&Demo" 
#define LOCALIZED_HELP_EXAMPLE         "&Beispiele"
#define LOCALIZED_HELP_RELEASENOTES    "&Anmerkungen"
#define LOCALIZED_HELP_ABOUTFMSLOGO    "&Über " LOCALIZED_GENERAL_PRODUCTNAME "..."
#define LOCALIZED_HELP_MS              "Über &MS..."
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   "Deutsch -> Englisch"
#define LOCALIZED_HELP_ENGLISHTOLANG   "Englisch -> Deutsch"

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              "Aktiver Bereich wählen"
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       "Wirkt auf Drucken und Speichern der Bilder"
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        "Y-Pos"
#define LOCALIZED_SELECTACTIVEAREA_YLOW         "Y-Neg" 
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        "X-Pos"
#define LOCALIZED_SELECTACTIVEAREA_XLOW         "X-Neg"
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH "Igelschritte in Inch gedruckt:"
#define LOCALIZED_SELECTACTIVEAREA_RESET        "&Reset" 
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON

// The screensaver strings
#define LOCALIZED_SCREENSAVER_NAME              LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_SCREENSAVER_DESCRIPTION       "FMSLogo Screensaver"
#define LOCALIZED_SCREENSAVER_SETTINGS_TITLE    "FMSLogo Bildschirmschoner-Einstellungen"
#define LOCALIZED_SCREENSAVER_LOCATE            "&Suchen Sie ..."
#define LOCALIZED_SCREENSAVER_FILE              "Logo &Datei:"
#define LOCALIZED_SCREENSAVER_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SCREENSAVER_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON

// The dialog box for selecting a Startup procedure
#define LOCALIZED_SELECTSTARTUP_CAPTION               "Wählen Sie eine " LOCALIZED_ALTERNATE_STARTUP "-Anweisung"
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED "Der Arbeitsbereich hat keine Anweisungsliste " LOCALIZED_ALTERNATE_STARTUP " definiert, so dass nichts passieren wird,\nwenn der Bildschirmschoner geladen wird. Bitte wählen Sie eine Prozedur aus, wenn das Programm geladen wird."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST   "Die Variable " LOCALIZED_ALTERNATE_STARTUP " ist keine Liste, so dass nichts passieren wird,\nwenn der Bildschirmschoner geladen wird. Bitte wählen Sie eine Prozedur aus, wenn das Programm geladen wird."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY     "Arbeitsbereich hat eine leere " LOCALIZED_ALTERNATE_STARTUP "-Anweisungsliste definiert,\nwenn der Bildschirmschoner geladen wird. Bitte wählen Sie eine Prozedur aus, wenn das Programm geladen wird."
#define LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED   "Keine Prozeduren sind definiert"

// The warning dialog box when the user saves an empty workspace
#define LOCALIZED_EMPTYWORKSPACE_TITLE                LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_EMPTYWORKSPACE_MESSAGE              "Es gibt keine Prozeduren, Variablen oder Eigenschaftslisten definiert,\nso der Arbeitsbereich als eine leere Datei gespeichert werden soll.\n\nMöchten Sie den Arbeitsbereich trotzdem speichern?"

//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     "Kopieren"
#define LOCALIZED_POPUP_CUT                      "Ausschneiden"
#define LOCALIZED_POPUP_PASTE                    "Einfügen"
#define LOCALIZED_POPUP_DELETE                   "Löschen"
#define LOCALIZED_POPUP_UNDO                     "Rückgängig"
#define LOCALIZED_POPUP_REDO                     "Wiederholen"
#define LOCALIZED_POPUP_SELECTALL                "Alles markieren"
#define LOCALIZED_POPUP_HELP                     "Begriffsuche"
#define LOCALIZED_POPUP_REMOVELINES              "Remove Selected Lines" // NOT_YET_LOCALIZED

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   "Editor"

#define LOCALIZED_EDITOR_FILE                    "&Datei"
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        "&Lerne und Ende\tCtrl+D"
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    "Speichern in den &Arbeitsspeicher"
#define LOCALIZED_EDITOR_FILE_PRINT              "&Drucken..." 
#define LOCALIZED_EDITOR_FILE_EXIT               "&Beenden" 

#define LOCALIZED_EDITOR_EDIT                    "&Edit"
#define LOCALIZED_EDITOR_EDIT_UNDO               "&Rückgängig\tCtrl+Z"
#define LOCALIZED_EDITOR_EDIT_REDO               "&Wiederholen\tCtrl+Y"
#define LOCALIZED_EDITOR_EDIT_CUT                "Aus&schneiden\tCtrl+X"
#define LOCALIZED_EDITOR_EDIT_COPY               "&Kopieren\tCtrl+C"
#define LOCALIZED_EDITOR_EDIT_PASTE              "&Einfügen\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_DELETE             "&Löschen\tDel"
#define LOCALIZED_EDITOR_EDIT_CLEARALL           "&Alles löschen\tCtrl+Del"
#define LOCALIZED_EDITOR_EDIT_SELECTALL          "Alles &markieren\tCtrl+A"

#define LOCALIZED_EDITOR_SEARCH                  "&Suchen"
#define LOCALIZED_EDITOR_SEARCH_FIND             "&Finden...\tCtrl+F"
#define LOCALIZED_EDITOR_SEARCH_REPLACE          "&Ersetzen...\tCtrl+H" 
#define LOCALIZED_EDITOR_SEARCH_NEXT             "&Weitersuchen\tF3" 

#define LOCALIZED_EDITOR_SET                     "&Option" 
#define LOCALIZED_EDITOR_SET_FONT                "&Schrift..." 

#define LOCALIZED_EDITOR_TEST                    "Test" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      "&Run Selection\tCtrl+R" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITOR_HELP                    "&Hilfen" 
#define LOCALIZED_EDITOR_HELP_INDEX              "&Index"
#define LOCALIZED_EDITOR_HELP_EDITOR             "&Editor"
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        "&Begriffsuche\tF1"


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    "&Lerne und Ende"
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       "&Nicht speichern"
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       "Es gibt nicht abgespeicherte Änderungen im Arbeitsspeicher. Wenn Sie beenden ohne abzuspeichern, gehen diese Änderungen verloren.  "
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       "Würden Sie gerne Ihre Änderungen speichern bevor Sie beenden?" 


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     "Kommandos"
#define LOCALIZED_COMMANDER_HALT                "Halt"
#define LOCALIZED_COMMANDER_TRACE               "Protokoll"
#define LOCALIZED_COMMANDER_NOTRACE             "K. Prot."
#define LOCALIZED_COMMANDER_PAUSE               "Pause"
#define LOCALIZED_COMMANDER_STATUS              "Status"
#define LOCALIZED_COMMANDER_NOSTATUS            "K. Status"
#define LOCALIZED_COMMANDER_STEP                "Einzelschritt"
#define LOCALIZED_COMMANDER_UNSTEP              "Turbo"
#define LOCALIZED_COMMANDER_RESET               "Reset"
#define LOCALIZED_COMMANDER_EXECUTE             "Ausführen"
#define LOCALIZED_COMMANDER_EDALL               "Editor"

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        "Status"
#define LOCALIZED_STATUS_PEN                    "Stift"
#define LOCALIZED_STATUS_CONTACT                "Zustand:"
#define LOCALIZED_STATUS_WIDTH                  "Dicke:"
#define LOCALIZED_STATUS_STYLE                  "Modus:"
#define LOCALIZED_STATUS_ORIENTATION            "Lagekennung"
#define LOCALIZED_STATUS_PITCH                  "->y,z:"
#define LOCALIZED_STATUS_HEADING                "Kurs:->x,y"
#define LOCALIZED_STATUS_ROLL                   "->x,z:"
#define LOCALIZED_STATUS_TURTLE                 "Igel"
#define LOCALIZED_STATUS_POSITION               "Position(XYZ):"
#define LOCALIZED_STATUS_WHICH                  "Igel-Nr.:"
#define LOCALIZED_STATUS_VISIBILITY             "Sichtbar:"
#define LOCALIZED_STATUS_COLOR                  "Farbe"
#define LOCALIZED_STATUS_PENCOLOR               "Stift(RGB):"
#define LOCALIZED_STATUS_FLOODCOLOR             "Fülle(RGB):"
#define LOCALIZED_STATUS_SCREENCOLOR            "Hinterg(RGB):"
#define LOCALIZED_STATUS_KERNEL                 "L-Kern"
#define LOCALIZED_STATUS_CALLS                  "Aufrufe:"
#define LOCALIZED_STATUS_PEAKMEMORY             "Speicherlast:"

#define LOCALIZED_STATUS_PENREVERSE     "Umkehrstift"
#define LOCALIZED_STATUS_PENNORMAL      "Normalstift"
#define LOCALIZED_STATUS_PENERASE       "löschen"
#define LOCALIZED_STATUS_PENUP          "Hoch"
#define LOCALIZED_STATUS_PENDOWN        "Ab"
#define LOCALIZED_STATUS_PENSHOWN       "Sichtbar"
#define LOCALIZED_STATUS_PENHIDDEN      "Versteckt"
#define LOCALIZED_STATUS_POLYGONS       "Polygone"
#define LOCALIZED_STATUS_VECTORS        "Vektoren"
#define LOCALIZED_STATUS_NODES          "Knoten"
#define LOCALIZED_STATUS_NOT_APPLICABLE "N/A" // NOT_YET_LOCALIZED

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           "&Alle"
#define LOCALIZED_ERASEPROCEDURE                "Lösche Prozedur"
#define LOCALIZED_EDITPROCEDURE                 "Edit Prozedur"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     "Farbe setzen"
#define LOCALIZED_SETCOLOR_PENCOLOR            "Stiftfarbe"
#define LOCALIZED_SETCOLOR_FLOODCOLOR          "Füllfarbe"
#define LOCALIZED_SETCOLOR_SCREENCOLOR         "Hintergrundfarbe"
#define LOCALIZED_SETCOLOR_RED                 "Rot"
#define LOCALIZED_SETCOLOR_GREEN               "Grün"
#define LOCALIZED_SETCOLOR_BLUE                "Blau"
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   "Stiftdicke"
#define LOCALIZED_SETPENSIZE_SIZE              "Dicke"
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     "Über " LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_ABOUTFMS_VERSION             "Version"
#define LOCALIZED_ABOUTFMS_GUI                 "GUI by George Mills\nSoftronics, Inc.\nhttp://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_CORE                "Core by Brian Harvey\nUniversity of California Berkeley"
#define LOCALIZED_ABOUTFMS_INSTALLER           "Installer based on Nullsoft Scriptable Install System\nhttp://nsis.sourceforge.net/"
#define LOCALIZED_ABOUTFMS_ADVENTURE           "The Great Logo Adventure (ISBN 0-9651934-6-2)\nWritten and donated by Jim Muller\nAvailable at http://www.softronix.com/\nPapert, Seymour: Gedankenblitze 8126 rororo"
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       "Special Thanks to Yehuda Katz and Erich Neuwirth"
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME " is free software\nSee GNU Public License"
#define LOCALIZED_ABOUTFMS_NEWSGROUP           "Internet News Group: comp.lang.logo\nVisit the Logo-Forum at\nhttp://groups.yahoo.com/group/LogoForum/"
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     "To learn the internals of computers,\ntry MultiMedia Logic from Softronics, Inc.\nVerändert/übersetzt von Stephan Vogel\nAugust-Ruf-Bildungszentrum Ettenheim/Südbaden\nSeine Logo-Projekte: http://www.lehrer.uni-karlsruhe.de/~za1880/itg/index.htm"
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      "Über FMS"
#define LOCALIZED_ABOUTMS_FMS                  "FMS steht für 'Fight Multiple Sclerosis'." 
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     "Spenden für National Multiple Sclerosis Society\nerbeten, http://www.nmss.org, 1-800-FIGHT-MS\nRechnen und Steuern in M, Inf, Ph und Te.\nFraktale und Rekursionen in Oberstufen"
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

#define LOCALIZED_CHANGESINEDITORMAYBELOST  "Änderungen in dieser Edit-Sitzung können verloren gehen.\n\nWollen Sie wirklich " LOCALIZED_GENERAL_PRODUCTNAME " verlassen?"
#define LOCALIZED_EDITSESSIONISRUNNING      "Eine Edit-Sitzung läuft gerade"

#define LOCALIZED_COULDNOTWRITEBMP            "Konnte nicht .bmp schreiben"
#define LOCALIZED_COULDNOTOPENBMP             "Konnte nicht .bmp öffnen"
#define LOCALIZED_COULDNOTCREATEBMP           "Unfähig Windows 3.0 Bitmap zu erstellen"
#define LOCALIZED_NOTVALIDBMP                 "Kein Windows 3.0 bitmap"

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         "Sie haben nicht auf der Disk abgespeichert"
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     "Ein Neu (New) auszuführen wird alle Definitionen löschen.\n\nFortfahren mit Neu (New)?"
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE "Die zu ladende Datei wird in Ihren Arbeitsspeicher hinein gestellt\nund kann Ihre nicht gespeicherten Änderungen überschreiben.\n\nFortfahren mit Laden (Load)?"
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    "Dies wird alle Ihre nicht gespeicherten Änderungen löschen.\n\nFortfahren mit Öffnen (Open)?"

#define LOCALIZED_EDITORISOPEN                  "Wussten Sie, dass eine Edit-Sitzung gerade läuft?\n\nÄnderungen in dieser Edit-Sitzung sind noch nicht abgespeichert."

#define LOCALIZED_ERROR_CANTREADFILE            "Unfähig Datei \"%s\" von der Disk zu lesen"
#define LOCALIZED_ERROR_CANTWRITEFILE           "Unfähig Datei \"%s\" auf Disk zu schreiben"

#define LOCALIZED_SAVETOWORKSPACE                "Speichern in den Arbeitsspeicher"
#define LOCALIZED_CONTENTSCHANGED                "Inhalte geändert"
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE "Die Inhalte sind geändert.\nWürden Sie gerne die Änderungen im Arbeitsspeicher festhalten?"



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  "Es gab ein Problem, die Inhalte des Editors in den Arbeitsspeicher zu übernehmen.  Der Cursor wird gleich nach der letzten erfolgreichen Definition positioniert.\n\nÜberprüfe den Commander nach möglicher Fehlermeldung."
#define LOCALIZED_RETURNTOEDIT                  "Zurück zum Editor?"

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

#define LOCALIZED_LOGO_FILE_EXTENSION "log"
#define LOCALIZED_FILEFILTER_ALLFILES "Alle Dateien (*.*)|*.*"
#define LOCALIZED_FILEFILTER_LOGO     "Logo Dateien (*.log)|*.log;*.lgo|" LOCALIZED_FILEFILTER_ALLFILES
#define LOCALIZED_FILEFILTER_IMAGE    "Bitmap Dateien (*.bmp)|*.bmp|GIF Dateien (*.gif)|*.gif|" LOCALIZED_FILEFILTER_ALLFILES



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             " stoppt\n"
#define LOCALIZED_TRACING_OUTPUTS           " gibt zurück %s\n"
#define LOCALIZED_TRACING_MAKE              "Setze %s %s"
#define LOCALIZED_TRACING_PPROP             "GibEg %s %s %s"
#define LOCALIZED_TRACING_LOCATION          " in %s\n%s"

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  "Einzelschritt"

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  "%s gelernt\n"


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    "lösche"
#define LOCALIZED_PENMODE_REVERSE  "umgekehrt"
#define LOCALIZED_PENMODE_PAINT    "zeichne"

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          "Logo: Fataler interner Fehler"
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       "Logo: Speicherüberlauf!"
#define LOCALIZED_ERROR_OUTOFMEMORY            "Speicherüberlauf"
#define LOCALIZED_ERROR_STACKOVERFLOW          "Stacküberlauf"
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      "Igel außerhalb der Grenzen"
#define LOCALIZED_ERROR_BADGRAPHINIT           "Konnte Grafiken nicht initialisieren"
#define LOCALIZED_ERROR_BADDATA                "%p mag nicht %s als Eingabe"
#define LOCALIZED_ERROR_DIDNTOUTPUT            "%p gab nicht nach %p aus"
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        "fehlende Eingaben in %p"
#define LOCALIZED_ERROR_TOOMUCH                "zu viel innerhalb der ()'n"
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    "Sie sagen nicht, was mit %s zu machen ist"
#define LOCALIZED_ERROR_PARENMISMATCH          "zu viele ('n"
#define LOCALIZED_ERROR_NOVALUE                "%s hat keinen Wert"
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        "unerwartete ')'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      "unerwartete ']'"
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        "unerwartete '}'"
#define LOCALIZED_ERROR_DONTKNOWHOWTO          "Was soll geschehen mit %p ?"
#define LOCALIZED_ERROR_NOCATCHTAG             "Konnte FANGE-Schild für %p nicht finden"
#define LOCALIZED_ERROR_ALREADYDEFINED         "%p ist schon definiert"
#define LOCALIZED_ERROR_STOPPING               "Gestoppt..."
#define LOCALIZED_ERROR_ALREADYDRIBBLING       "Bereits in Arbeit"
#define LOCALIZED_ERROR_FILESYSTEM                   "File-Systemfehler: %p"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          "Konnte Datei nicht öffnen"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         "Kann nicht Datei: %t öffnen"
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       "Datei ist schon geöffnet"
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           "Datei ist nicht geöffnet"
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  "Konnte Editor-File nicht aufnehmen"
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   "Konnte den Editor nicht starten" 
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    "Konnte Editor-File nicht lesen" 
#define LOCALIZED_ERROR_IFWARNING              "Annahme: Sie meinen wohl WENNSONST (IFELSE), nicht WENN (IF)"
#define LOCALIZED_ERROR_SHADOWWARNING          "%p überwacht von LOKAL (local) im Prozeduraufruf"
#define LOCALIZED_ERROR_USER                   "Wirf \"Fehler"
#define LOCALIZED_ERROR_ISPRIMITIVE            "%p ist ein Grundwort"
#define LOCALIZED_ERROR_TONOTINSIDE            "Kann PR (TO) verwenden innerhalb einer Prozedur"
#define LOCALIZED_ERROR_ATTOPLEVEL             "Kann nur %p  verwenden innerhalb einer Prozedur"
#define LOCALIZED_ERROR_ATTOPLEVEL2            "Nur innerhalb einer Prozedur RÜCKGABE (OUTPUT) oder RK (STOP) verwenden"
#define LOCALIZED_ERROR_NOTEST                 "%p ohne TEST"
#define LOCALIZED_ERROR_BADMACROOUTPUT         "Makro-Rückgabe %s anstatt einer Liste"
#define LOCALIZED_ERROR_DEEPEND                "ENDE(END) innerhalb vielzeiliger Instruktion"
#define LOCALIZED_ERROR_DEEPENDIN              "ENDE (END) innerhalb vielzeiliger Instruktion in %p"
#define LOCALIZED_ERROR_UNKNOWN                "Unbekannte Fehlerbedingung - interner Fehler."
#define LOCALIZED_PAUSING                      "Pausiere..."


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION "Invalid state for instruction: %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MODE_ON_SPRITE             "cannot set the mode of a turtle with a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        "cannot make a special turtle use a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            "cannot use the clipboard as a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_SPECIALFORM                "%p doesn't like %p as input because it has a special form" // NOT_YET_LOCALIZED

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      "Fehler"
#define LOCALIZED_ERROR_BADINPUT             "Falsche Eingabe"
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    "Eingabe wird nicht vermittelt"

#define LOCALIZED_ERROR_CANTOPENPORT         "Konnte Port nicht öffnen"
#define LOCALIZED_ERROR_CANTCLOSEPORT        "Konnte Port nicht schließen"
#define LOCALIZED_ERROR_CANTFLUSHPORT        "Konnte Port nicht durchströmen"
#define LOCALIZED_ERROR_CANTDCBONPORT        "Konnte dcb nicht aufbauen auf Port"
#define LOCALIZED_ERROR_CANTSETPORT          "Konnte Port nicht setzen"
#define LOCALIZED_ERROR_PORTALREADYOPEN      "Port ist schon offen"
#define LOCALIZED_ERROR_PORTNOTOPEN          "Port ist nicht offen"

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   "%s ist bereits vorhanden"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    "%s ist nicht vorhanden"

#define LOCALIZED_ERROR_DLLNOTLOADED          "DLL ist nicht geladen"
#define LOCALIZED_ERROR_DLLLOADFAILED         "DLL-Ladevorgang nicht erfolgreich"
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    "Ungültiger Dateneingangstyp"
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  "Ungültiger Ausgang-Typ"
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   "Funktion nicht gefunden"
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  "Nicht alle Typen/Daten Eingaben werden vermittelt"

#define LOCALIZED_ERROR_NETWORK               "Network Fehler"
#define LOCALIZED_ERROR_NETWORKRECEIVE        "Network Empfangsfehler"
#define LOCALIZED_ERROR_NETWORKSEND           "Network Sendefehler"
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       "Unerwarteter Fehler, Network dürfte heruntergefahren sein"
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     "Nicht gestartet"
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED "Schon gestartet"
#define LOCALIZED_ERROR_NETWORKALREADYON      "Schon an"
#define LOCALIZED_ERROR_NETWORKALREADYOFF     "Schon aus"

// The rest of the network errors shouldn't really be seen -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         "Name zu lang"
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      "Nicht initialisiert"
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      "System nicht bereit"
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED "Version wird nicht unterstützt"
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   "Kann nicht senden, nachdem Socket heruntergefahren ist"
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         "Interrupt-System Ruf"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    "Autorisierte Antwort: Host nicht gefunden"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH "Nicht-autorisiert: Host nicht gefunden. Vgl. NETSTARTUP"
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      "Kein wieder gut zu machender Fehler"
#define LOCALIZED_ERROR_NETWORKNODATA              "Kein Daten-Record verfügbar"
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       "Falsche Datei-Nummer"
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          "Operation würde blockieren"
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       "Operation jetzt im Fortschreiten"
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   "Operation jetzt im Fortschreiten"
#define LOCALIZED_ERROR_NETWORKBADADDRESS          "Falsche Adresse"
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     "Zieladresse gefordert"
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      "Meldung zu lang"
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      "Protokollfamilie wird nicht unterstützt"
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         "Verzeichnis ist nicht leer"
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     "Anwendungsgrenze erreicht"
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           "Diskquote überschritten"
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        "Zu viele offene Dateien"
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        "Zugang verweigert"
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          "Socket-Operation auf fehlendem Socket"
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    "Kann gesuchte Adresse nicht zuteilen"
#define LOCALIZED_ERROR_NETWORKADDRINUSE           "Adresse schon im Gebrauch"
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      "Adressenfamilie wird nicht unterstützt von der Protokollfamilie"
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            "Zeit für Verbindung überschritten"
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    "Socket-Typ wird nicht unterstützt"
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   "Protokoll wird nicht unterstützt"
#define LOCALIZED_ERROR_NETWORKNOBUFFER            "Kein Platz im Puffer"
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    "Socket ist schon verbunden"
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        "Socket wird nicht verbunden"
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         "Falsche Protokolloption"
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     "Verbindungsreset von Peer"
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     "Software verursachte Verbindungsabbruch"
#define LOCALIZED_ERROR_NETWORKISDOWN              "Network ist heruntergefahren"
#define LOCALIZED_ERROR_NETWORKRESET               "Network wurde wieder gestartet"
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   "Verbindung verweigert"
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          "Host ist heruntergefahren"
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   "Host ist nicht erreichbar"
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        "Protokoll ist falsch gesetzt für Socket"
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   "Operation wird nicht unterstützt auf dem Socket"
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         "kein Weg gefunden, um Host zu starten (to remote)"
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         "Zu viele Verweisungen"

#define LOCALIZED_ERROR_POLYSTART               "PolyStart - Fehler"
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED "Sie haben schon ein Polygon gestartet"

#define LOCALIZED_ERROR_POLYEND                 "PolyEnde (PolyEnd) Fehler"
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       "Sie haben kein Polygon gestartet"
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     "Sie müssen mindestens 3 Vektoren haben, um ein Polygon zu definieren"

#define LOCALIZED_ERROR_SOUND                 "Sound - Fehler"

#define LOCALIZED_ERROR_MIDI                  "MIDI Fehler"
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     "Ungültiges MIDI-Interface"
#define LOCALIZED_ERROR_MIDIALREADYOPEN       "Schon offen"
#define LOCALIZED_ERROR_MIDINOTOPEN           "Nicht offen"

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      "Kein Text im Clipboard"

#define LOCALIZED_ERROR_MCI                   "MCI Fehler"

#define LOCALIZED_ERROR_TIMERNOTFOUND         "Zeitnehmer nicht gefunden"

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       "Online-Hilfe ist nicht verfügbar, weil hhctrl.ocx nicht geladen werden konnte." 

#define LOCALIZED_ERROR_BADCOMMANDLINE        "Ungültige Befehlszeile" 

#define LOCALIZED_ERROR_TMPNOTDEFINED         "Die Umgebungsvariable TMP ist nicht definiert oder ungültig.\n" LOCALIZED_GENERAL_PRODUCTNAME " wird versuchen C:\\ zu verwenden, um temporäre Dateien zu speichern"

#define LOCALIZED_ERROR_GIFSAVEFAILED         "Generierungs-Problem GIF, überprüfen Sie Speicher und Diskkapazität"
#define LOCALIZED_ERROR_GIFREADFAILED         "Lese-Problem GIF, überprüfen Sie Speicher und Datenträgerkapazität"

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  "BitMap-Index liegt außerhalb des Bereiches"
#define LOCALIZED_ERROR_BITMAPCUTFAILED        "Ausschneiden ohne Erfolg, möglicherweise nicht genügend Speicher vorhanden"

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    "Nichts einzufügen" 
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  "BitMap im Index muss mit einem Bitmap initialisiert sein" 

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      "Igel %d hat kein Bild, will Halt"

#define LOCALIZED_ERROR_FONTNOTFOUND            "Entschuldigung, es wurde kein Schrifttyp, genannt %s, gefunden.  Wählen Sie einen im folgenden:\n"

#define LOCALIZED_ERROR_PRINTERCANTSCALE        "Druckertreiber unterstützt nicht diese Funktion" 
#define LOCALIZED_ERROR_CANTDRAWIMAGE           "Kann Bild nicht zeichnen"
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        "Kann Bild nicht extrahieren"
#define LOCALIZED_ERROR_SUBCODE                 "Sub Code"

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         "Eingabe:"
#define LOCALIZED_PROMPT_TO     "Pr-Modus (Cancel to End)"
#define LOCALIZED_PROMPT_LIST   "Liste-Modus (Cancel to Halt)"
#define LOCALIZED_PROMPT_PAUSE  "Pause-Modus (Cancel to Continue)"
#define LOCALIZED_PROMPT_INPUT  "Eingabe-Modus (Cancel to Halt)"

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      "Erfolgreich gewechselt nach \"%s\""
#define LOCALIZED_FILE_CHDIRFAILED         "Kein chdir zum Verzeichnis \"%s\""
#define LOCALIZED_FILE_POPPEDTO            "Gewechselt nach \"%s\""
#define LOCALIZED_FILE_MKDIRSUCCEEDED      "Jetzt im neu eingerichteten Verzeichnis \"%s\"" 
#define LOCALIZED_FILE_MKDIRFAILED         "Verzeichnis \"%s\" nicht einrichtbar" 
#define LOCALIZED_FILE_RMDIRSUCCEEDED      "Verzeichnis \"%s\" gelöscht" 
#define LOCALIZED_FILE_RMDIRFAILED         "Löschvorgang des Verzeichnisses \"%s\" nicht erfolgreich" 
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  "Das Verzeichnis existiert nicht."
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY "Das Verzeichnis leeren bevor man es zu löschen versucht."


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       "Logo Bild"

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    "Aktiver Bereich"
#define LOCALIZED_INFORMATION   "Information"
#define LOCALIZED_WARNING       "Achtung"
#define LOCALIZED_UNTITLED      "Unbetitelt"
#define LOCALIZED_UNKNOWN       "Unbekannt"

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       "Ungebunden"

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     "Finden"
#define LOCALIZED_EDITOR_TITLE_REPLACE  "Ersetzen"

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING "%s nicht gefunden"


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
#define LOCALIZED_COLOR_ALICEBLUE             "AliceBlau"
#define LOCALIZED_COLOR_ANTIQUEWHITE          "AntikWeiß"
#define LOCALIZED_COLOR_AQUA                  "WasserBlau"
#define LOCALIZED_COLOR_AQUAMARINE            "Aquamarin"
#define LOCALIZED_COLOR_AZURE                 "Azur"
#define LOCALIZED_COLOR_BEIGE                 "Beige"
#define LOCALIZED_COLOR_BISQUE                "Krebs"
#define LOCALIZED_COLOR_BLACK                 "Schwarz"
#define LOCALIZED_COLOR_BLANCHEDALMOND        "gebleichteMandel"
#define LOCALIZED_COLOR_BLUE                  "Blau"
#define LOCALIZED_COLOR_BLUEVIOLET            "BlauViolett"
#define LOCALIZED_COLOR_BROWN                 "Braun"
#define LOCALIZED_COLOR_BURLYWOOD             "StammHolz"
#define LOCALIZED_COLOR_CADETBLUE             "KadettBlau"
#define LOCALIZED_COLOR_CHARTREUSE            "Chartreuse"
#define LOCALIZED_COLOR_CHOCOLATE             "Schokolade"
#define LOCALIZED_COLOR_CORAL                 "Korallen"
#define LOCALIZED_COLOR_CORNFLOWERBLUE        "KornblumenBlau"
#define LOCALIZED_COLOR_CORNSILK              "KornBraun"
#define LOCALIZED_COLOR_CRIMSON               "Karmesin"
#define LOCALIZED_COLOR_CYAN                  "Zyan"
#define LOCALIZED_COLOR_DARKBLUE              "DunkelBlau"
#define LOCALIZED_COLOR_DARKCYAN              "DunkelZyan"
#define LOCALIZED_COLOR_DARKGOLDENROD         "DarkGoldenRod"
#define LOCALIZED_COLOR_DARKGRAY              "DunkelGrau"
#define LOCALIZED_COLOR_DARKGREEN             "DunkelGrün"
#define LOCALIZED_COLOR_DARKGREY              "DunkelGrau"
#define LOCALIZED_COLOR_DARKKHAKI             "Khakirot"
#define LOCALIZED_COLOR_DARKMAGENTA           "DunkelMagenta"
#define LOCALIZED_COLOR_DARKOLIVEGREEN        "DunkelOlivGrün"
#define LOCALIZED_COLOR_DARKORANGE            "DunkelOrange"
#define LOCALIZED_COLOR_DARKORCHID            "DunkelOrchidee"
#define LOCALIZED_COLOR_DARKRED               "DunkelRot"
#define LOCALIZED_COLOR_DARKSALMON            "DunkelLachs"
#define LOCALIZED_COLOR_DARKSEAGREEN          "DunkelSeeGrün"
#define LOCALIZED_COLOR_DARKSLATEBLUE         "DunkelSchieferBlau"
#define LOCALIZED_COLOR_DARKSLATEGRAY         "DunkelSchieferGrau"
#define LOCALIZED_COLOR_DARKSLATEGREY         "DunkelSchieferGrau"
#define LOCALIZED_COLOR_DARKTURQUOISE         "DunkelTürkis"
#define LOCALIZED_COLOR_DARKVIOLET            "DunkelViolett"
#define LOCALIZED_COLOR_DEEPPINK              "TiefPink"
#define LOCALIZED_COLOR_DEEPSKYBLUE           "TiefHimmelBlau"
#define LOCALIZED_COLOR_DIMGRAY               "MattGrau"
#define LOCALIZED_COLOR_DIMGREY               "MattGrau"
#define LOCALIZED_COLOR_DODGERBLUE            "DodgerBlau"
#define LOCALIZED_COLOR_FIREBRICK             "FeuerZiegel"
#define LOCALIZED_COLOR_FLORALWHITE           "BlütenWeiß"
#define LOCALIZED_COLOR_FORESTGREEN           "WaldGrün"
#define LOCALIZED_COLOR_FUCHSIA               "Helllila"
#define LOCALIZED_COLOR_GAINSBORO             "Gainsboro"
#define LOCALIZED_COLOR_GHOSTWHITE            "GeistWeiß"
#define LOCALIZED_COLOR_GOLD                  "Gold"
#define LOCALIZED_COLOR_GOLDENROD             "Goldrute"
#define LOCALIZED_COLOR_GRAY                  "Grau"
#define LOCALIZED_COLOR_GREEN                 "Grün"
#define LOCALIZED_COLOR_GREENYELLOW           "Grüngelb"
#define LOCALIZED_COLOR_GREY                  "Grau"
#define LOCALIZED_COLOR_HONEYDEW              "Tau"
#define LOCALIZED_COLOR_HOTPINK               "Knallpink"
#define LOCALIZED_COLOR_INDIANRED             "Indischrot"
#define LOCALIZED_COLOR_INDIGO                "Indigo"
#define LOCALIZED_COLOR_IVORY                 "Elfenbein"
#define LOCALIZED_COLOR_KHAKI                 "Khaki"
#define LOCALIZED_COLOR_LAVENDER              "Lavendel"
#define LOCALIZED_COLOR_LAVENDERBLUSH         "LavendelRöte"
#define LOCALIZED_COLOR_LAWNGREEN             "RasenGrün"
#define LOCALIZED_COLOR_LEMONCHIFFON          "Zitronengelb"
#define LOCALIZED_COLOR_LIGHTBLUE             "HellBlau"
#define LOCALIZED_COLOR_LIGHTCORAL            "HellKorallen"
#define LOCALIZED_COLOR_LIGHTCYAN             "HellZyan"
#define LOCALIZED_COLOR_LIGHTGOLDENRODYELLOW  "SchwimmbadBlau"
#define LOCALIZED_COLOR_LIGHTGRAY             "HellGrau"
#define LOCALIZED_COLOR_LIGHTGREEN            "HellGrün"
#define LOCALIZED_COLOR_LIGHTGREY             "HellGrau"
#define LOCALIZED_COLOR_LIGHTPINK             "HellPink"
#define LOCALIZED_COLOR_LIGHTSALMON           "HellLachs"
#define LOCALIZED_COLOR_LIGHTSEAGREEN         "HellSeeGrün"
#define LOCALIZED_COLOR_LIGHTSKYBLUE          "HellHimmelBlau"
#define LOCALIZED_COLOR_LIGHTSLATEGRAY        "HellSchieferGrau"
#define LOCALIZED_COLOR_LIGHTSLATEGREY        "HellSchieferGrau"
#define LOCALIZED_COLOR_LIGHTSTEELBLUE        "HellStahlBlau"
#define LOCALIZED_COLOR_LIGHTYELLOW           "HellGelb"
#define LOCALIZED_COLOR_LIME                  "HellGrün"
#define LOCALIZED_COLOR_LIMEGREEN             "KalkGrün"
#define LOCALIZED_COLOR_LINEN                 "Leinen"
#define LOCALIZED_COLOR_MAGENTA               "Magenta"
#define LOCALIZED_COLOR_MAROON                "Dunkelrot"
#define LOCALIZED_COLOR_MEDIUMAQUAMARINE      "MittelAquaMarin"
#define LOCALIZED_COLOR_MEDIUMBLUE            "MittelBlau"
#define LOCALIZED_COLOR_MEDIUMORCHID          "MittelOrchidee"
#define LOCALIZED_COLOR_MEDIUMPURPLE          "MittelPurpurn"
#define LOCALIZED_COLOR_MEDIUMSEAGREEN        "MittelSeeGrün"
#define LOCALIZED_COLOR_MEDIUMSLATEBLUE       "MittelSchieferBlau"
#define LOCALIZED_COLOR_MEDIUMSPRINGGREEN     "MittelFrühlingGrün"
#define LOCALIZED_COLOR_MEDIUMTURQUOISE       "MittelTürkis"
#define LOCALIZED_COLOR_MEDIUMVIOLETRED       "MittelViolettRot"
#define LOCALIZED_COLOR_MIDNIGHTBLUE          "MitternachtsBlau"
#define LOCALIZED_COLOR_MINTCREAM             "MintCreme"
#define LOCALIZED_COLOR_MISTYROSE             "MistyRose"
#define LOCALIZED_COLOR_MOCCASIN              "Mokassin"
#define LOCALIZED_COLOR_NAVAJOWHITE           "Navajoweiß"
#define LOCALIZED_COLOR_NAVY                  "DunkelBlau"
#define LOCALIZED_COLOR_OLDLACE               "Altespitze"
#define LOCALIZED_COLOR_OLIVE                 "Oliv"
#define LOCALIZED_COLOR_OLIVEDRAB             "OlivDRAB"
#define LOCALIZED_COLOR_ORANGE                "Orange"
#define LOCALIZED_COLOR_ORANGERED             "OrangeRot"
#define LOCALIZED_COLOR_ORCHID                "Orchidee"
#define LOCALIZED_COLOR_PALEGOLDENROD         "PaleGoldenRod"
#define LOCALIZED_COLOR_PALEGREEN             "BlassGrün"
#define LOCALIZED_COLOR_PALETURQUOISE         "BlassTürkis"
#define LOCALIZED_COLOR_PALEVIOLETRED         "BlassViolettRot"
#define LOCALIZED_COLOR_PAPAYAWHIP            "PapayaWhip"
#define LOCALIZED_COLOR_PEACHPUFF             "ApfelGrün"
#define LOCALIZED_COLOR_PERU                  "Peru"
#define LOCALIZED_COLOR_PINK                  "Pink"
#define LOCALIZED_COLOR_PLUM                  "Pflaume"
#define LOCALIZED_COLOR_POWDERBLUE            "PuderBlau"
#define LOCALIZED_COLOR_PURPLE                "Purpurn"
#define LOCALIZED_COLOR_RED                   "Rot"
#define LOCALIZED_COLOR_ROSYBROWN             "PastellBraun"
#define LOCALIZED_COLOR_ROYALBLUE             "KönigsBlau"
#define LOCALIZED_COLOR_SADDLEBROWN           "SattelBraun"
#define LOCALIZED_COLOR_SALMON                "Lachs"
#define LOCALIZED_COLOR_SANDYBROWN            "SandBraun"
#define LOCALIZED_COLOR_SEAGREEN              "SeeGrün"
#define LOCALIZED_COLOR_SEASHELL              "MeerMuschel"
#define LOCALIZED_COLOR_SIENNA                "Siena"
#define LOCALIZED_COLOR_SILVER                "Silber"
#define LOCALIZED_COLOR_SKYBLUE               "HimmelBlau"
#define LOCALIZED_COLOR_SLATEBLUE             "SchieferBlau"
#define LOCALIZED_COLOR_SLATEGRAY             "SchieferGrau"
#define LOCALIZED_COLOR_SLATEGREY             "SchieferGrau"
#define LOCALIZED_COLOR_SNOW                  "Schnee"
#define LOCALIZED_COLOR_SPRINGGREEN           "FrühlingsGrün"
#define LOCALIZED_COLOR_STEELBLUE             "StahlBlau"
#define LOCALIZED_COLOR_TAN                   "Lohe"
#define LOCALIZED_COLOR_TEAL                  "GrünBlau"
#define LOCALIZED_COLOR_THISTLE               "Distel"
#define LOCALIZED_COLOR_TOMATO                "TomatenRot"
#define LOCALIZED_COLOR_TURQUOISE             "Türkis"
#define LOCALIZED_COLOR_VIOLET                "Violett"
#define LOCALIZED_COLOR_WHEAT                 "Weizen"
#define LOCALIZED_COLOR_WHITE                 "Weiß"
#define LOCALIZED_COLOR_WHITESMOKE            "RauchWeiß"
#define LOCALIZED_COLOR_YELLOW                "Gelb"
#define LOCALIZED_COLOR_YELLOWGREEN           "GelbGrün"

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
