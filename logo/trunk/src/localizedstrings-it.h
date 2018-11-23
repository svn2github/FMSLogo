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
// This file contains localized strings for Italian by Stefano Federici and Francesco Simone Carta
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
#define LOCALIZED_ALTERNATE_TRUE     "vero"
#define LOCALIZED_ALTERNATE_FALSE    "falso"
#define LOCALIZED_ALTERNATE_END      "fine"
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
#define LOCALIZED_ALTERNATE__DEFMACRO              ".defmacro"
#define LOCALIZED_ALTERNATE__EQ                    ".uguale"
#define LOCALIZED_ALTERNATE__MACRO                 ".macro"
#define LOCALIZED_ALTERNATE__MAYBEOUTPUT           ".forseriporta"
#define LOCALIZED_ALTERNATE__SETBF                 ".asmenpri"
#define LOCALIZED_ALTERNATE__SETFIRST              ".asprimo"
#define LOCALIZED_ALTERNATE__SETITEM               ".aselemento"
#define LOCALIZED_ALTERNATE_ACTIVEAREA             "areaattiva"
#define LOCALIZED_ALTERNATE_ALLOPEN                "arcaperti"
#define LOCALIZED_ALTERNATE_AND                    "e"
#define LOCALIZED_ALTERNATE_APPLY                  "applica"
#define LOCALIZED_ALTERNATE_ARCCOS                 "arccos"
#define LOCALIZED_ALTERNATE_ARCSIN                 "arcsen"
#define LOCALIZED_ALTERNATE_ARCTAN                 "arctan"
#define LOCALIZED_ALTERNATE_ARITY                  "rango"
#define LOCALIZED_ALTERNATE_ARRAY                  "vettore"
#define LOCALIZED_ALTERNATE_ARRAYP                 "vettorep"
#define LOCALIZED_ALTERNATE_ARRAY_                 "vettore?"
#define LOCALIZED_ALTERNATE_ASCII                  "ascii"
#define LOCALIZED_ALTERNATE_ASHIFT                 "scorriaritmetico"
#define LOCALIZED_ALTERNATE_BACK                   "indietro"
#define LOCALIZED_ALTERNATE_BACKSLASHEDP           "barrarovesciatap"
#define LOCALIZED_ALTERNATE_BACKSLASHED_           "barrarovesciata?"
#define LOCALIZED_ALTERNATE_BEFOREP                "primap"
#define LOCALIZED_ALTERNATE_BEFORE_                "prima?"
#define LOCALIZED_ALTERNATE_BF                     "mp"
#define LOCALIZED_ALTERNATE_BFS                    "mpi"
#define LOCALIZED_ALTERNATE_BITAND                 "bitand"
#define LOCALIZED_ALTERNATE_BITBLOCK               "bloccodis"
#define LOCALIZED_ALTERNATE_BITCOPY                "copiadis"
#define LOCALIZED_ALTERNATE_BITCUT                 "tagliadis"
#define LOCALIZED_ALTERNATE_BITFIT                 "adattadis"
#define LOCALIZED_ALTERNATE_BITINDEX               "indicedis"
#define LOCALIZED_ALTERNATE_BITLOAD                "caricadis"
#define LOCALIZED_ALTERNATE_BITLOADSIZE            "caricadisdim"
#define LOCALIZED_ALTERNATE_BITSIZE                "dimdis"
#define LOCALIZED_ALTERNATE_BITMAPTURTLE           "tartadis"
#define LOCALIZED_ALTERNATE_BITMODE                "mododis"
#define LOCALIZED_ALTERNATE_BITNOT                 "bitnot"
#define LOCALIZED_ALTERNATE_BITOR                  "bitor"
#define LOCALIZED_ALTERNATE_BITPASTE               "incolladis"
#define LOCALIZED_ALTERNATE_BITPASTETOINDEX        "incollaindicedis"
#define LOCALIZED_ALTERNATE_BITSAVE                "salvadis"
#define LOCALIZED_ALTERNATE_BITXOR                 "bitxor"
#define LOCALIZED_ALTERNATE_BK                     "i"
#define LOCALIZED_ALTERNATE_BL                     "mu"
#define LOCALIZED_ALTERNATE_BURIED                 "nascosto"
#define LOCALIZED_ALTERNATE_BURY                   "nascondi"
#define LOCALIZED_ALTERNATE_BUTFIRST               "menpri"
#define LOCALIZED_ALTERNATE_BUTFIRSTS              "menprimi"
#define LOCALIZED_ALTERNATE_BUTLAST                "menult"
#define LOCALIZED_ALTERNATE_BUTTONCREATE           "pulsantecrea"
#define LOCALIZED_ALTERNATE_BUTTONDELETE           "pulsantecancella"
#define LOCALIZED_ALTERNATE_BUTTONENABLE           "pulsanteattiva"
#define LOCALIZED_ALTERNATE_BUTTONUPDATE           "pulsanteaggiorna"
#define LOCALIZED_ALTERNATE_BUTTONP                "pulsantep"
#define LOCALIZED_ALTERNATE_BUTTON_                "pulsante?"
#define LOCALIZED_ALTERNATE_BYE                    "ciao"
#define LOCALIZED_ALTERNATE_CATCH                  "acchiappa"
#define LOCALIZED_ALTERNATE_CHAR                   "car"
#define LOCALIZED_ALTERNATE_CHDIR                  "chdir"
#define LOCALIZED_ALTERNATE_CHECKBOXCREATE         "casellacrea"
#define LOCALIZED_ALTERNATE_CHECKBOXDELETE         "casellacancella"
#define LOCALIZED_ALTERNATE_CHECKBOXENABLE         "casellaattiva"
#define LOCALIZED_ALTERNATE_CHECKBOXGET            "casellavalore"
#define LOCALIZED_ALTERNATE_CHECKBOXSET            "casellaassegna"
#define LOCALIZED_ALTERNATE_CLEAN                  "pulisci"
#define LOCALIZED_ALTERNATE_CLEARPALETTE           "puliscipaletta"
#define LOCALIZED_ALTERNATE_CLEARSCREEN            "puliscischermo"
#define LOCALIZED_ALTERNATE_CLEARTEXT              "puliscitesto"
#define LOCALIZED_ALTERNATE_CLEARTIMER             "cancetempo"
#define LOCALIZED_ALTERNATE_CLOSE                  "chiudi"
#define LOCALIZED_ALTERNATE_CLOSEALL               "chiuditutti"
#define LOCALIZED_ALTERNATE_CO                     "co"
#define LOCALIZED_ALTERNATE_COMBOBOXADDSTRING      "comboaggiungi"
#define LOCALIZED_ALTERNATE_COMBOBOXCREATE         "combocrea"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETE         "combocancella"
#define LOCALIZED_ALTERNATE_COMBOBOXENABLE         "comboattiva"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING   "combotogli"
#define LOCALIZED_ALTERNATE_COMBOBOXGETTEXT        "combotesto"
#define LOCALIZED_ALTERNATE_COMBOBOXSETTEXT        "comboassegnatesto"
#define LOCALIZED_ALTERNATE_CONTENTS               "contenuti"
#define LOCALIZED_ALTERNATE_CONTINUE               "continua"
#define LOCALIZED_ALTERNATE_COPYDEF                "copiadef"
#define LOCALIZED_ALTERNATE_COS                    "cos"
#define LOCALIZED_ALTERNATE_COUNT                  "conta"
#define LOCALIZED_ALTERNATE_CS                     "ps"
#define LOCALIZED_ALTERNATE_CT                     "pt"
#define LOCALIZED_ALTERNATE_CURSOR                 "cursore"
#define LOCALIZED_ALTERNATE_DEBUGWINDOWS           "finestradebug"
#define LOCALIZED_ALTERNATE_DEFINE                 "definisci"
#define LOCALIZED_ALTERNATE_DEFINEDP               "definitap"
#define LOCALIZED_ALTERNATE_DEFINED_               "definita?"
#define LOCALIZED_ALTERNATE_DIALOGCREATE           "dialogocrea"
#define LOCALIZED_ALTERNATE_DIALOGENABLE           "dialogoattiva"
#define LOCALIZED_ALTERNATE_DIALOGDELETE           "dialogocancella"
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         "dialogoaprifile"
#define LOCALIZED_ALTERNATE_DIALOGFILESAVE         "dialogosalvafile"
#define LOCALIZED_ALTERNATE_DIFFERENCE             "differenza"
#define LOCALIZED_ALTERNATE_DIRECTORIES            "cartelle"
#define LOCALIZED_ALTERNATE_DLLCALL                "chiamadll"
#define LOCALIZED_ALTERNATE_DLLFREE                "liberadll"
#define LOCALIZED_ALTERNATE_DLLLOAD                "caricadll"
#define LOCALIZED_ALTERNATE_DOWN                   "eg"
#define LOCALIZED_ALTERNATE_DOWNPITCH              "elevagiu"
#define LOCALIZED_ALTERNATE_DRIBBLE                "registra"
#define LOCALIZED_ALTERNATE_ED                     "ed"
#define LOCALIZED_ALTERNATE_EDIT                   "edita"
#define LOCALIZED_ALTERNATE_ELLIPSEARC             "arcoellisse"
#define LOCALIZED_ALTERNATE_EMPTYP                 "vuotop"
#define LOCALIZED_ALTERNATE_EMPTY_                 "vuoto?"
#define LOCALIZED_ALTERNATE_EOFP                   "finefilep"
#define LOCALIZED_ALTERNATE_EOF_                   "finefile?"
#define LOCALIZED_ALTERNATE_EQUALP                 "ugualep"
#define LOCALIZED_ALTERNATE_EQUAL_                 "uguale?"
#define LOCALIZED_ALTERNATE_ER                     "ca"
#define LOCALIZED_ALTERNATE_ERASE                  "erase" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ERASEFILE              "cancellafile"
#define LOCALIZED_ALTERNATE_ERF                    "caf"
#define LOCALIZED_ALTERNATE_ERROR                  "errore"
#define LOCALIZED_ALTERNATE_EVENTCHECK             "controllaevento"
#define LOCALIZED_ALTERNATE_EXP                    "esp"
#define LOCALIZED_ALTERNATE_FD                     "a"
#define LOCALIZED_ALTERNATE_FENCE                  "muro"
#define LOCALIZED_ALTERNATE_FILL                   "riempi"
#define LOCALIZED_ALTERNATE_FILES                  "catalogo"
#define LOCALIZED_ALTERNATE_FIRST                  "pri"
#define LOCALIZED_ALTERNATE_FIRSTS                 "primi"
#define LOCALIZED_ALTERNATE_FLOODCOLOR             "coloreriempi"
#define LOCALIZED_ALTERNATE_FONTFACENAMES          "nomicaratteri"
#define LOCALIZED_ALTERNATE_FOREVER                "persempre"
#define LOCALIZED_ALTERNATE_FORM                   "formato"
#define LOCALIZED_ALTERNATE_FORWARD                "avanti"
#define LOCALIZED_ALTERNATE_FPUT                   "inpri"
#define LOCALIZED_ALTERNATE_FS                     "sp"
#define LOCALIZED_ALTERNATE_FULLSCREEN             "schermopieno"
#define LOCALIZED_ALTERNATE_FULLTEXT               "fulltext"
#define LOCALIZED_ALTERNATE_GETFOCUS               "getfocus"
#define LOCALIZED_ALTERNATE_GOTO                   "goto"
#define LOCALIZED_ALTERNATE_GIFLOAD                "caricagif"
#define LOCALIZED_ALTERNATE_GIFSIZE                "grandezzagif"
#define LOCALIZED_ALTERNATE_GIFSAVE                "salvagif"
#define LOCALIZED_ALTERNATE_GPROP                  "prop"
#define LOCALIZED_ALTERNATE_GREATEREQUALP          "maggioreougualep"
#define LOCALIZED_ALTERNATE_GREATEREQUAL_          "maggioreouguale?"
#define LOCALIZED_ALTERNATE_GREATERP               "maggiorep"
#define LOCALIZED_ALTERNATE_GREATER_               "maggiore?"
#define LOCALIZED_ALTERNATE_GROUPBOXCREATE         "gruppocrea"
#define LOCALIZED_ALTERNATE_GROUPBOXDELETE         "gruppocancella"
#define LOCALIZED_ALTERNATE_HALT                   "alt"
#define LOCALIZED_ALTERNATE_HASOWNPENP             "possiedepennap"
#define LOCALIZED_ALTERNATE_HASOWNPEN_             "possiedepenna?"
#define LOCALIZED_ALTERNATE_HEADING                "direzione"
#define LOCALIZED_ALTERNATE_HELP                   "aiuto"
#define LOCALIZED_ALTERNATE_HIDETURTLE             "nastarta"
#define LOCALIZED_ALTERNATE_HOME                   "tana"
#define LOCALIZED_ALTERNATE_HT                     "nt"
#define LOCALIZED_ALTERNATE_IF                     "se"
#define LOCALIZED_ALTERNATE_IFELSE                 "seallora"
#define LOCALIZED_ALTERNATE_IFF                    "sef"
#define LOCALIZED_ALTERNATE_IFFALSE                "sefalso"
#define LOCALIZED_ALTERNATE_IFT                    "sev"
#define LOCALIZED_ALTERNATE_IFTRUE                 "severo"
#define LOCALIZED_ALTERNATE_INGAMEPORT             "inportagiochi"
#define LOCALIZED_ALTERNATE_INPORT                 "inporta"
#define LOCALIZED_ALTERNATE_INPORTB                "inportabyte"
#define LOCALIZED_ALTERNATE_INT                    "intero"
#define LOCALIZED_ALTERNATE_ITEM                   "elemento"
#define LOCALIZED_ALTERNATE_KEYBOARDOFF            "tastierano"
#define LOCALIZED_ALTERNATE_KEYBOARDON             "tastierasi"
#define LOCALIZED_ALTERNATE_KEYBOARDVALUE          "tasto"
#define LOCALIZED_ALTERNATE_KEYP                   "tastop"
#define LOCALIZED_ALTERNATE_KEY_                   "tasto?"
#define LOCALIZED_ALTERNATE_LABEL                  "etichetta"
#define LOCALIZED_ALTERNATE_LABELFONT              "fontetichetta"
#define LOCALIZED_ALTERNATE_LABELSIZE              "grandezzaetichetta"
#define LOCALIZED_ALTERNATE_LAST                   "ultimo"
#define LOCALIZED_ALTERNATE_LEFT                   "sinistra"
#define LOCALIZED_ALTERNATE_LEFTROLL               "rolliosinistra"
#define LOCALIZED_ALTERNATE_LESSEQUALP             "minoreougualep"
#define LOCALIZED_ALTERNATE_LESSEQUAL_             "minoreouguale?"
#define LOCALIZED_ALTERNATE_LESSP                  "minorep"
#define LOCALIZED_ALTERNATE_LESS_                  "minore?"
#define LOCALIZED_ALTERNATE_LIGHT                  "luce"
#define LOCALIZED_ALTERNATE_LIST                   "lista"
#define LOCALIZED_ALTERNATE_LISTBOXADDSTRING       "listasceltaaggiungi"
#define LOCALIZED_ALTERNATE_LISTBOXCREATE          "listasceltacrea"
#define LOCALIZED_ALTERNATE_LISTBOXENABLE          "listasceltaattiva"
#define LOCALIZED_ALTERNATE_LISTBOXDELETE          "listasceltacancella"
#define LOCALIZED_ALTERNATE_LISTBOXDELETESTRING    "listasceltatogli"
#define LOCALIZED_ALTERNATE_LISTBOXGETSELECT       "listasceltascegli"
#define LOCALIZED_ALTERNATE_LISTP                  "listap"
#define LOCALIZED_ALTERNATE_LIST_                  "lista?"
#define LOCALIZED_ALTERNATE_LN                     "ln"
#define LOCALIZED_ALTERNATE_LOAD                   "apri"
#define LOCALIZED_ALTERNATE_LOCAL                  "locale"
#define LOCALIZED_ALTERNATE_LOG10                  "log10"
#define LOCALIZED_ALTERNATE_LOGOVERSION            "versionelogo"
#define LOCALIZED_ALTERNATE_LOWERCASE              "minuscolo"
#define LOCALIZED_ALTERNATE_LPUT                   "inult"
#define LOCALIZED_ALTERNATE_LR                     "rs"
#define LOCALIZED_ALTERNATE_LSHIFT                 "scorrisin"
#define LOCALIZED_ALTERNATE_LT                     "s"
#define LOCALIZED_ALTERNATE_MACHINE                "macchina"
#define LOCALIZED_ALTERNATE_MACROP                 "macrop"
#define LOCALIZED_ALTERNATE_MACRO_                 "macro?"
#define LOCALIZED_ALTERNATE_MAKE                   "assegna"
#define LOCALIZED_ALTERNATE_MCI                    "mci"
#define LOCALIZED_ALTERNATE_MEMBER                 "membro"
#define LOCALIZED_ALTERNATE_MEMBERP                "elementop"
#define LOCALIZED_ALTERNATE_MEMBER_                "elemento?"
#define LOCALIZED_ALTERNATE_MESSAGEBOX             "messaggio"
#define LOCALIZED_ALTERNATE_MIDICLOSE              "chiudimidi"
#define LOCALIZED_ALTERNATE_MIDIMESSAGE            "messaggiomidi"
#define LOCALIZED_ALTERNATE_MIDIOPEN               "aprimidi"
#define LOCALIZED_ALTERNATE_MINUS                  "minus"
#define LOCALIZED_ALTERNATE_MKDIR                  "mkdir"
#define LOCALIZED_ALTERNATE_MODULO                 "modulo"
#define LOCALIZED_ALTERNATE_MOUSEOFF               "disattivamouse"
#define LOCALIZED_ALTERNATE_MOUSEON                "attivamouse"
#define LOCALIZED_ALTERNATE_MOUSEPOS               "posizionemouse"
#define LOCALIZED_ALTERNATE_NAMEP                  "nomep"
#define LOCALIZED_ALTERNATE_NAME_                  "nome?"
#define LOCALIZED_ALTERNATE_NAMES                  "nomi"
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           "reteaccettano"
#define LOCALIZED_ALTERNATE_NETACCEPTON            "reteaccettasi"
#define LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE  "reteaccettaricevivalore"
#define LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE     "reteaccettainviavalore"
#define LOCALIZED_ALTERNATE_NETCONNECTOFF          "reteconnettino"
#define LOCALIZED_ALTERNATE_NETCONNECTON           "reteconnettisi"
#define LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE "reteconnettiricevivalore"
#define LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE    "reteconnettiinviavalore"
#define LOCALIZED_ALTERNATE_NETSHUTDOWN            "retechiudi"
#define LOCALIZED_ALTERNATE_NETSTARTUP             "reteavvia"
#define LOCALIZED_ALTERNATE_NOBITMAPTURTLE         "nodisegnotarta"
#define LOCALIZED_ALTERNATE_NODES                  "nodi"
#define LOCALIZED_ALTERNATE_NODRIBBLE              "nodirigi"
#define LOCALIZED_ALTERNATE_NOSTATUS               "nostato"
#define LOCALIZED_ALTERNATE_NOT                    "non"
#define LOCALIZED_ALTERNATE_NOTEQUALP              "nonugualep"
#define LOCALIZED_ALTERNATE_NOTEQUAL_              "nonuguale?"
#define LOCALIZED_ALTERNATE_NOYIELD                "eventino"
#define LOCALIZED_ALTERNATE_NUMBERP                "numerop"
#define LOCALIZED_ALTERNATE_NUMBER_                "numero?"
#define LOCALIZED_ALTERNATE_OP                     "ri"
#define LOCALIZED_ALTERNATE_OPENAPPEND             "apriaccoda"
#define LOCALIZED_ALTERNATE_OPENREAD               "aprilettura"
#define LOCALIZED_ALTERNATE_OPENUPDATE             "apriaggiorna"
#define LOCALIZED_ALTERNATE_OPENWRITE              "apriscrittura"
#define LOCALIZED_ALTERNATE_OR                     "unovero?"
#define LOCALIZED_ALTERNATE_OUTPORT                "scrivisuporta"
#define LOCALIZED_ALTERNATE_OUTPORTB               "scrivisuportab"
#define LOCALIZED_ALTERNATE_OUTPUT                 "riporta"
#define LOCALIZED_ALTERNATE_PARSE                  "analizza"
#define LOCALIZED_ALTERNATE_PAUSE                  "pausa"
#define LOCALIZED_ALTERNATE_PC                     "cp"
#define LOCALIZED_ALTERNATE_PD                     "giu"
#define LOCALIZED_ALTERNATE_PE                     "pe" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENCOLOR               "colpenna"
#define LOCALIZED_ALTERNATE_PENDOWN                "pennagiu"
#define LOCALIZED_ALTERNATE_PENDOWNP               "pennagiup"
#define LOCALIZED_ALTERNATE_PENDOWN_               "pennagiu?"
#define LOCALIZED_ALTERNATE_PENERASE               "cancella"
#define LOCALIZED_ALTERNATE_PENMODE                "cancepenna"
#define LOCALIZED_ALTERNATE_PENPAINT               "pennadisegna"
#define LOCALIZED_ALTERNATE_PENPATTERN             "motivopenna"
#define LOCALIZED_ALTERNATE_PENREVERSE             "pennainversa"
#define LOCALIZED_ALTERNATE_PENSIZE                "trattopenna"
#define LOCALIZED_ALTERNATE_PENUP                  "sulapenna"
#define LOCALIZED_ALTERNATE_PERSPECTIVE            "prospettiva"
#define LOCALIZED_ALTERNATE_PITCH                  "elevazione"
#define LOCALIZED_ALTERNATE_PIXEL                  "pixel"
#define LOCALIZED_ALTERNATE_PLAYWAVE               "suovawave"
#define LOCALIZED_ALTERNATE_PLIST                  "listaprop"
#define LOCALIZED_ALTERNATE_PLISTS                 "pliste"
#define LOCALIZED_ALTERNATE_PO                     "sc"
#define LOCALIZED_ALTERNATE_POPDIR                 "dirsu"
#define LOCALIZED_ALTERNATE_POLYSTART              "iniziopoli"
#define LOCALIZED_ALTERNATE_POLYEND                "finepoli"
#define LOCALIZED_ALTERNATE_POLYVIEW               "vedipoli"
#define LOCALIZED_ALTERNATE_PORTCLOSE              "chiudiporta"
#define LOCALIZED_ALTERNATE_PORTFLUSH              "svuotaporta"
#define LOCALIZED_ALTERNATE_PORTMODE               "modoporta"
#define LOCALIZED_ALTERNATE_PORTOPEN               "apriporta"
#define LOCALIZED_ALTERNATE_PORTREADARRAY          "leggivettoredaporta"
#define LOCALIZED_ALTERNATE_PORTREADCHAR           "leggicardaporta"
#define LOCALIZED_ALTERNATE_PORTWRITEARRAY         "scrivivettoresuporta"
#define LOCALIZED_ALTERNATE_PORTWRITECHAR          "scrivicarsuporta"
#define LOCALIZED_ALTERNATE_POS                    "pos"
#define LOCALIZED_ALTERNATE_POSXYZ                 "posxyz"
#define LOCALIZED_ALTERNATE_POT                    "scp"
#define LOCALIZED_ALTERNATE_POWER                  "potenza"
#define LOCALIZED_ALTERNATE_PPROP                  "asprop"
#define LOCALIZED_ALTERNATE_PPT                    "ped"
#define LOCALIZED_ALTERNATE_PR                     "st"
#define LOCALIZED_ALTERNATE_PRIMITIVEP             "primitivap"
#define LOCALIZED_ALTERNATE_PRIMITIVE_             "primitiva?"
#define LOCALIZED_ALTERNATE_PRINT                  "stampa"
#define LOCALIZED_ALTERNATE_PROCEDUREP             "procedurap"
#define LOCALIZED_ALTERNATE_PROCEDURE_             "procedura?"
#define LOCALIZED_ALTERNATE_PROPLISTP              "listapropp"
#define LOCALIZED_ALTERNATE_PROPLIST_              "listaprop?"
#define LOCALIZED_ALTERNATE_PROCEDURES             "procedure"
#define LOCALIZED_ALTERNATE_PRODUCT                "prodotto"
#define LOCALIZED_ALTERNATE_PU                     "su"
#define LOCALIZED_ALTERNATE_PX                     "pi"
#define LOCALIZED_ALTERNATE_QUESTIONBOX            "finestradomanda"
#define LOCALIZED_ALTERNATE_QUOTIENT               "quoziente"
#define LOCALIZED_ALTERNATE_RADARCCOS              "radarccos"
#define LOCALIZED_ALTERNATE_RADARCSIN              "radarcsen"
#define LOCALIZED_ALTERNATE_RADARCTAN              "radarctan"
#define LOCALIZED_ALTERNATE_RADCOS                 "radcos"
#define LOCALIZED_ALTERNATE_RADIOBUTTONCREATE      "pulsanteradiocrea"
#define LOCALIZED_ALTERNATE_RADIOBUTTONENABLE      "pulsanteradioattiva"
#define LOCALIZED_ALTERNATE_RADIOBUTTONDELETE      "pulsanteradiocancella"
#define LOCALIZED_ALTERNATE_RADIOBUTTONGET         "pulsanteradiovalore"
#define LOCALIZED_ALTERNATE_RADIOBUTTONSET         "pulsanteradioassegna"
#define LOCALIZED_ALTERNATE_RADSIN                 "radsen"
#define LOCALIZED_ALTERNATE_RADTAN                 "radtan"
#define LOCALIZED_ALTERNATE_RANDOM                 "acaso"
#define LOCALIZED_ALTERNATE_RAWASCII               "rawascii"
#define LOCALIZED_ALTERNATE_RC                     "lc"
#define LOCALIZED_ALTERNATE_RCS                    "lcs"
#define LOCALIZED_ALTERNATE_READCHAR               "leggicar"
#define LOCALIZED_ALTERNATE_READCHARS              "leggicaratteri"
#define LOCALIZED_ALTERNATE_READER                 "dacheleggi"
#define LOCALIZED_ALTERNATE_READLIST               "leggilista"
#define LOCALIZED_ALTERNATE_READPOS                "poslettura"
#define LOCALIZED_ALTERNATE_READRAWLINE            "leggirigagrezza"
#define LOCALIZED_ALTERNATE_READWORD               "leggiparola"
#define LOCALIZED_ALTERNATE_REMAINDER              "resto"
#define LOCALIZED_ALTERNATE_REMPROP                "togliprop"
#define LOCALIZED_ALTERNATE_REPCOUNT               "iterazioni"
#define LOCALIZED_ALTERNATE_REPEAT                 "ripeti"
#define LOCALIZED_ALTERNATE_RERANDOM               "riacaso"
#define LOCALIZED_ALTERNATE_RIGHT                  "destra"
#define LOCALIZED_ALTERNATE_RIGHTROLL              "rolliodestro"
#define LOCALIZED_ALTERNATE_RL                     "rl" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RMDIR                  "eliminadir"
#define LOCALIZED_ALTERNATE_ROLL                   "rollio"
#define LOCALIZED_ALTERNATE_ROUND                  "arrotonda"
#define LOCALIZED_ALTERNATE_RR                     "rd"
#define LOCALIZED_ALTERNATE_RT                     "d"
#define LOCALIZED_ALTERNATE_RUN                    "esegui"
#define LOCALIZED_ALTERNATE_RUNPARSE               "analizzaesegui"
#define LOCALIZED_ALTERNATE_RUNRESULT              "risultatoesegui"
#define LOCALIZED_ALTERNATE_RW                     "lp"
#define LOCALIZED_ALTERNATE_SAVE                   "salva"
#define LOCALIZED_ALTERNATE_SCREENCOLOR            "colsfondo"
#define LOCALIZED_ALTERNATE_SCROLLBARCREATE        "barrascorrimentocrea"
#define LOCALIZED_ALTERNATE_SCROLLBARENABLE        "barrascorrimentoattiva"
#define LOCALIZED_ALTERNATE_SCROLLBARDELETE        "barrascorrimentocancella"
#define LOCALIZED_ALTERNATE_SCROLLBARGET           "barrascorrimentovalore"
#define LOCALIZED_ALTERNATE_SCROLLBARSET           "barrascorrimentoassegna"
#define LOCALIZED_ALTERNATE_SCROLLX                "scorrix"
#define LOCALIZED_ALTERNATE_SCROLLY                "scorriy"
#define LOCALIZED_ALTERNATE_SCRUNCH                "schia"
#define LOCALIZED_ALTERNATE_SE                     "fr"
#define LOCALIZED_ALTERNATE_SELECTBOX              "selezione"
#define LOCALIZED_ALTERNATE_SENTENCE               "frase"
#define LOCALIZED_ALTERNATE_SETACTIVEAREA          "asareaattiva"
#define LOCALIZED_ALTERNATE_SETBITINDEX            "asindicedis"
#define LOCALIZED_ALTERNATE_SETBITMODE             "asmododis"
#define LOCALIZED_ALTERNATE_SETCLIP                "assegnaclip"
#define LOCALIZED_ALTERNATE_SETCURSOR              "setcursor"
#define LOCALIZED_ALTERNATE_SETCURSORNOWAIT        "ascursorenoattesa"
#define LOCALIZED_ALTERNATE_SETCURSORWAIT          "ascursoreattesa"
#define LOCALIZED_ALTERNATE_SETFC                  "ascr"
#define LOCALIZED_ALTERNATE_SETFLOODCOLOR          "ascolriempi"
#define LOCALIZED_ALTERNATE_SETFOCUS               "asfuoco"
#define LOCALIZED_ALTERNATE_SETH                   "asdir"
#define LOCALIZED_ALTERNATE_SETHEADING             "asdir"
#define LOCALIZED_ALTERNATE_SETITEM                "aselem"
#define LOCALIZED_ALTERNATE_SETLABELFONT           "asfontetichetta"
#define LOCALIZED_ALTERNATE_SETLIGHT               "asluce"
#define LOCALIZED_ALTERNATE_SETMARGINS             "asmargini"
#define LOCALIZED_ALTERNATE_SETPC                  "ascp"
#define LOCALIZED_ALTERNATE_SETPENCOLOR            "ascolpenna"
#define LOCALIZED_ALTERNATE_SETPENPATTERN          "asmotivopenna"
#define LOCALIZED_ALTERNATE_SETPENSIZE             "astrattopenna"
#define LOCALIZED_ALTERNATE_SETPITCH               "aselevazione"
#define LOCALIZED_ALTERNATE_SETPIXEL               "aspixel"
#define LOCALIZED_ALTERNATE_SETPOS                 "aspos"
#define LOCALIZED_ALTERNATE_SETPOSXYZ              "asposxyz"
#define LOCALIZED_ALTERNATE_SETREAD                "leggida"
#define LOCALIZED_ALTERNATE_SETREADPOS             "leggipos"
#define LOCALIZED_ALTERNATE_SETROLL                "asrollio"
#define LOCALIZED_ALTERNATE_SETSC                  "ascs"
#define LOCALIZED_ALTERNATE_SETSCREENCOLOR         "ascoloreschermo"
#define LOCALIZED_ALTERNATE_SETSCRUNCH             "asschia"
#define LOCALIZED_ALTERNATE_SETTIMER               "astempo"
#define LOCALIZED_ALTERNATE_SETTURTLE              "astarta"
#define LOCALIZED_ALTERNATE_SETTURTLEMODE          "asmodotarta"
#define LOCALIZED_ALTERNATE_SETWRITE               "scrivisu"
#define LOCALIZED_ALTERNATE_SETWRITEPOS            "scrivipos"
#define LOCALIZED_ALTERNATE_SETX                   "vax"
#define LOCALIZED_ALTERNATE_SETXY                  "vaxy"
#define LOCALIZED_ALTERNATE_SETXYZ                 "vaxyz"
#define LOCALIZED_ALTERNATE_SETY                   "vay"
#define LOCALIZED_ALTERNATE_SETZ                   "vaz"
#define LOCALIZED_ALTERNATE_SHELL                  "shell"
#define LOCALIZED_ALTERNATE_SHOW                   "mostra"
#define LOCALIZED_ALTERNATE_SHOWNP                 "inmostra?"
#define LOCALIZED_ALTERNATE_SHOWN_                 "invista?"
#define LOCALIZED_ALTERNATE_SHOWTURTLE             "mostarta"
#define LOCALIZED_ALTERNATE_SIN                    "sen"
#define LOCALIZED_ALTERNATE_SOUND                  "suona"
#define LOCALIZED_ALTERNATE_SPLITSCREEN            "splitscreen"
#define LOCALIZED_ALTERNATE_SQRT                   "radq"
#define LOCALIZED_ALTERNATE_SS                     "ss"
#define LOCALIZED_ALTERNATE_ST                     "mt"
#define LOCALIZED_ALTERNATE_STANDOUT               "standout"
#define LOCALIZED_ALTERNATE_STATICCREATE           "etichettacrea"
#define LOCALIZED_ALTERNATE_STATICDELETE           "etichettacancella"
#define LOCALIZED_ALTERNATE_STATICUPDATE           "etichettaaggiorna"
#define LOCALIZED_ALTERNATE_STATUS                 "stato"
#define LOCALIZED_ALTERNATE_STEP                   "passo"
#define LOCALIZED_ALTERNATE_STEPPED                "listapassi"
#define LOCALIZED_ALTERNATE_STOP                   "stop"
#define LOCALIZED_ALTERNATE_SUBSTRINGP             "sottostringap"
#define LOCALIZED_ALTERNATE_SUBSTRING_             "sottostringa?"
#define LOCALIZED_ALTERNATE_SUM                    "somma"
#define LOCALIZED_ALTERNATE_TAG                    "tag"
#define LOCALIZED_ALTERNATE_TAN                    "tan"
#define LOCALIZED_ALTERNATE_TEST                   "verifica"
#define LOCALIZED_ALTERNATE_TEXT                   "testo"
#define LOCALIZED_ALTERNATE_TEXTSCREEN             "textscreen"
#define LOCALIZED_ALTERNATE_THING                  "cosa"
#define LOCALIZED_ALTERNATE_THROW                  "lancia"
#define LOCALIZED_ALTERNATE_TIME                   "tempo"
#define LOCALIZED_ALTERNATE_TIMEMILLI              "millisec"
#define LOCALIZED_ALTERNATE_TO                     "per"
#define LOCALIZED_ALTERNATE_TONE                   "nota"
#define LOCALIZED_ALTERNATE_TOWARDS                "verso"
#define LOCALIZED_ALTERNATE_TOWARDSXYZ             "versoxyz"
#define LOCALIZED_ALTERNATE_TRACE                  "traccia"
#define LOCALIZED_ALTERNATE_TRACED                 "listatraccia"
#define LOCALIZED_ALTERNATE_TS                     "ts"
#define LOCALIZED_ALTERNATE_TURTLE                 "tarta"
#define LOCALIZED_ALTERNATE_TURTLEMODE             "modotarta"
#define LOCALIZED_ALTERNATE_TURTLES                "maxturta"
#define LOCALIZED_ALTERNATE_TYPE                   "scrivi"
#define LOCALIZED_ALTERNATE_UNBURY                 "scopri"
#define LOCALIZED_ALTERNATE_UNSTEP                 "nopasso"
#define LOCALIZED_ALTERNATE_UNTRACE                "notraccia"
#define LOCALIZED_ALTERNATE_UP                     "es"
#define LOCALIZED_ALTERNATE_UPPERCASE              "maiuscolo"
#define LOCALIZED_ALTERNATE_UPPITCH                "elevasu"
#define LOCALIZED_ALTERNATE_WAIT                   "aspetta"
#define LOCALIZED_ALTERNATE_WINDOW                 "finestra"
#define LOCALIZED_ALTERNATE_WINDOWCREATE           "finestracrea"
#define LOCALIZED_ALTERNATE_WINDOWENABLE           "finestraattiva"
#define LOCALIZED_ALTERNATE_WINDOWDELETE           "finestracancella"
#define LOCALIZED_ALTERNATE_WINDOWFILEEDIT         "finestraedita"
#define LOCALIZED_ALTERNATE_WINDOWSET              "finestraimposta"
#define LOCALIZED_ALTERNATE_WINHELP                "finestraaiuto"
#define LOCALIZED_ALTERNATE_WORD                   "parola"
#define LOCALIZED_ALTERNATE_WORDP                  "parolap"
#define LOCALIZED_ALTERNATE_WORD_                  "parola?"
#define LOCALIZED_ALTERNATE_WRAP                   "circolare"
#define LOCALIZED_ALTERNATE_WRITEPOS               "posscrittura"
#define LOCALIZED_ALTERNATE_WRITER                 "scritturasu"
#define LOCALIZED_ALTERNATE_YESNOBOX               "finestrasino"
#define LOCALIZED_ALTERNATE_YIELD                  "eventisi"
#define LOCALIZED_ALTERNATE_ZOOM                   "zoom"

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      "OK"
#define LOCALIZED_GENERAL_CANCELBUTTON  "Annulla"
#define LOCALIZED_GENERAL_APPLYBUTTON   "&Applica"

#define LOCALIZED_GENERAL_PRODUCTNAME   "FMSLogo"

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  "L'ambiente di programmazione FMSLogo"

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  "&File"
#define LOCALIZED_FILE_NEW              "&Nuovo\t(cancella Spazio di Lavoro)"
#define LOCALIZED_FILE_LOAD             "&Carica...\t(aggiunge allo Spazio di Lavoro)"
#define LOCALIZED_FILE_OPEN             "&Apri...\t(sostituisce Spazio di Lavoro)"
#define LOCALIZED_FILE_SAVE             "&Salva"
#define LOCALIZED_FILE_SAVEAS           "Salva con &nome..."
#define LOCALIZED_FILE_SETASSCREENSAVER "Impostare come Salvaschermo"
#define LOCALIZED_FILE_EDIT             "&Modifica..."
#define LOCALIZED_FILE_ERASE            "&Cancella..."
#define LOCALIZED_FILE_EXIT             "&Esci"

#define LOCALIZED_BITMAP               "&Disegno"
#define LOCALIZED_BITMAP_NEW           "&Nuovo"
#define LOCALIZED_BITMAP_LOAD          "&Carica..."
#define LOCALIZED_BITMAP_SAVE          "&Salva"
#define LOCALIZED_BITMAP_SAVEAS        "Salva con &nome..."
#define LOCALIZED_BITMAP_PRINT         "Stam&pa..."
#define LOCALIZED_BITMAP_PRINTERSETUP  "&Imposta stampante..."
#define LOCALIZED_BITMAP_ACTIVEAREA    "&Area attiva..."

#define LOCALIZED_SET                  "&Opzioni"
#define LOCALIZED_SET_PENSIZE          "Dimensione &Penna..."
#define LOCALIZED_SET_LABELFONT        "Carattere &etichette..."
#define LOCALIZED_SET_COMMANDERFONT    "Carattere finestra &Comandi..."
#define LOCALIZED_SET_PENCOLOR         "Co&lore Penna..."
#define LOCALIZED_SET_FLOODCOLOR       "Colore &Riempimento..."
#define LOCALIZED_SET_SCREENCOLOR      "Colore &Schermo..."

#define LOCALIZED_ZOOM                 "&Zoom"
#define LOCALIZED_ZOOM_IN              "&Ingrandisci"
#define LOCALIZED_ZOOM_OUT             "&Rimpicciolisci"
#define LOCALIZED_ZOOM_NORMAL          "&Normale"

#define LOCALIZED_HELP                 "&Aiuto"
#define LOCALIZED_HELP_INDEX           "&Indice"
#define LOCALIZED_HELP_TUTORIAL        "&Tutorial"
#define LOCALIZED_HELP_DEMO            "&Dimostrazione"
#define LOCALIZED_HELP_EXAMPLE         "&Esempi"
#define LOCALIZED_HELP_RELEASENOTES    "Note di &rilascio"
#define LOCALIZED_HELP_ABOUTFMSLOGO    "Informazioni su &" LOCALIZED_GENERAL_PRODUCTNAME "..."
#define LOCALIZED_HELP_MS              "Informazioni su &MS..."
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   "da Italiano a Inglese"
#define LOCALIZED_HELP_ENGLISHTOLANG   "English to Italian"

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              "Selezione area di stampa attiva"
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       "Queste impostazioni agiscono su Salva e Stampa"
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        "Y-Alto"
#define LOCALIZED_SELECTACTIVEAREA_YLOW         "Y-Basso"
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        "X-Sinistra"
#define LOCALIZED_SELECTACTIVEAREA_XLOW         "X-Destra"
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH "Passi di Tartaruga stampati per pollice:"
#define LOCALIZED_SELECTACTIVEAREA_RESET        "&Reimposta"
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON

// The screensaver strings
#define LOCALIZED_SCREENSAVER_NAME              LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_SCREENSAVER_DESCRIPTION       "FMSLogo Screensaver"
#define LOCALIZED_SCREENSAVER_SETTINGS_TITLE    "FMSLogo Screensaver Impostazioni"
#define LOCALIZED_SCREENSAVER_LOCATE            "&Individuare ..."
#define LOCALIZED_SCREENSAVER_FILE              "Logo &File:"
#define LOCALIZED_SCREENSAVER_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SCREENSAVER_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON

// The dialog box for selecting a Startup procedure
#define LOCALIZED_SELECTSTARTUP_CAPTION               "Selezionare un'istruzione " LOCALIZED_ALTERNATE_STARTUP
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED "L'area di lavoro non ha una lista di istruzioni " LOCALIZED_ALTERNATE_STARTUP " definita,\nquindi non succederà nulla quando viene caricato il salvaschermo.\nSi prega di selezionare una procedura da eseguire quando viene caricato il programma."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST   "La variabile " LOCALIZED_ALTERNATE_STARTUP " non è un elenco,\nquindi non succederà nulla quando viene caricato il salvaschermo.\nSi prega di selezionare una procedura da eseguire quando viene caricato il programma."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY     "Area di lavoro ha definita in lista istruzioni una vuoto " LOCALIZED_ALTERNATE_STARTUP ", quindi non succederà nulla quando viene caricato il salvaschermo.\nSi prega di selezionare una procedura da eseguire quando viene caricato il programma."
#define LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED   "Nessuna procedura è definita"

// The warning dialog box when the user saves an empty workspace
#define LOCALIZED_EMPTYWORKSPACE_TITLE                LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_EMPTYWORKSPACE_MESSAGE              "Non esistono procedure, variabili o elenchi di proprietà definiti,\nquindi l'area di lavoro verrà salvato come un file vuoto.\n\nVuoi salvare l'area di lavoro comunque?"

//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     "Copia"
#define LOCALIZED_POPUP_CUT                      "Taglia"
#define LOCALIZED_POPUP_PASTE                    "Incolla"
#define LOCALIZED_POPUP_DELETE                   "Cancella"
#define LOCALIZED_POPUP_UNDO                     "Annulla"
#define LOCALIZED_POPUP_REDO                     "Ripristina"
#define LOCALIZED_POPUP_SELECTALL                "Seleziona Tutto"
#define LOCALIZED_POPUP_HELP                     "Cerca Argomento"
#define LOCALIZED_POPUP_REMOVELINES              "Rimuovi Righe Selezionate"

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   "Editor"

#define LOCALIZED_EDITOR_FILE                    "&File"
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        "&Salva ed esci\tCtrl+D"
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    "Salva su &Cartella"
#define LOCALIZED_EDITOR_FILE_PRINT              "Stam&pa..."
#define LOCALIZED_EDITOR_FILE_EXIT               "Esci"

#define LOCALIZED_EDITOR_EDIT                    "&Modifica"
#define LOCALIZED_EDITOR_EDIT_UNDO               "&Annulla\tCtrl+Z"
#define LOCALIZED_EDITOR_EDIT_REDO               "&Ripristina\tCtrl+Y"
#define LOCALIZED_EDITOR_EDIT_CUT                "&Taglia\tCtrl+X"
#define LOCALIZED_EDITOR_EDIT_COPY               "&Copia\tCtrl+C"
#define LOCALIZED_EDITOR_EDIT_PASTE              "&Incolla\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_DELETE             "&Elimina\tDel"
#define LOCALIZED_EDITOR_EDIT_CLEARALL           "Ca&ncella Tutto\tCtrl+Del"
#define LOCALIZED_EDITOR_EDIT_SELECTALL          "&Seleziona Tutto\tCtrl+A"

#define LOCALIZED_EDITOR_SEARCH                  "&Cerca"
#define LOCALIZED_EDITOR_SEARCH_FIND             "&Trova...\tCtrl+F"
#define LOCALIZED_EDITOR_SEARCH_REPLACE          "&Sostituisci...\tCtrl+H"
#define LOCALIZED_EDITOR_SEARCH_NEXT             "&Successivo\tF3"

#define LOCALIZED_EDITOR_SET                     "&Opzioni"
#define LOCALIZED_EDITOR_SET_FONT                "&Carattere..."

#define LOCALIZED_EDITOR_TEST                    "Prova"
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      "P&rova Selezione\tCtrl+R"

#define LOCALIZED_EDITOR_HELP                    "&Aiuto"
#define LOCALIZED_EDITOR_HELP_INDEX              "&Indice"
#define LOCALIZED_EDITOR_HELP_EDITOR             "&Editor"
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        "&Cerca Argomento\tF1"


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    "&Salva e Esci"
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       "&Non Salvare"
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       "Il contenuto è stato modificato.  Se esci senza salvare, queste modifiche andranno perse.  "
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       "Vorresti salvare le modifiche prima di uscire?"


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     "Comandi"
#define LOCALIZED_COMMANDER_HALT                "Alt"
#define LOCALIZED_COMMANDER_TRACE               "Traccia"
#define LOCALIZED_COMMANDER_NOTRACE             "NoTraccia"
#define LOCALIZED_COMMANDER_PAUSE               "Pausa"
#define LOCALIZED_COMMANDER_STATUS              "Stato"
#define LOCALIZED_COMMANDER_NOSTATUS            "NoStato"
#define LOCALIZED_COMMANDER_STEP                "Passo"
#define LOCALIZED_COMMANDER_UNSTEP              "NoPasso"
#define LOCALIZED_COMMANDER_RESET               "Reimposta"
#define LOCALIZED_COMMANDER_EXECUTE             "Esegui"
#define LOCALIZED_COMMANDER_EDALL               "EdTutto"

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        "Stato"
#define LOCALIZED_STATUS_PEN                    "Penna"
#define LOCALIZED_STATUS_CONTACT                "Contatto:"
#define LOCALIZED_STATUS_WIDTH                  "Ampiezza:"
#define LOCALIZED_STATUS_STYLE                  "Stile:"
#define LOCALIZED_STATUS_ORIENTATION            "Orientamento"
#define LOCALIZED_STATUS_PITCH                  "Inclinazione:"
#define LOCALIZED_STATUS_HEADING                "Direzione:"
#define LOCALIZED_STATUS_ROLL                   "Rotazione:"
#define LOCALIZED_STATUS_TURTLE                 "Tartaruga"
#define LOCALIZED_STATUS_POSITION               "Posizione(XYZ):"
#define LOCALIZED_STATUS_WHICH                  "Numero:"
#define LOCALIZED_STATUS_VISIBILITY             "Visibilità:"
#define LOCALIZED_STATUS_COLOR                  "Colore"
#define LOCALIZED_STATUS_PENCOLOR               "Penna(RGB):"
#define LOCALIZED_STATUS_FLOODCOLOR             "Riempimento(RGB):"
#define LOCALIZED_STATUS_SCREENCOLOR            "Schermo(RGB):"
#define LOCALIZED_STATUS_KERNEL                 "Kernel"
#define LOCALIZED_STATUS_CALLS                  "Chiamate:"
#define LOCALIZED_STATUS_PEAKMEMORY             "Picco Memoria Allocata:"

#define LOCALIZED_STATUS_PENREVERSE     "Inverso"
#define LOCALIZED_STATUS_PENNORMAL      "Normale"
#define LOCALIZED_STATUS_PENERASE       "Cancella"
#define LOCALIZED_STATUS_PENUP          "Su"
#define LOCALIZED_STATUS_PENDOWN        "Giù"
#define LOCALIZED_STATUS_PENSHOWN       "Visibile"
#define LOCALIZED_STATUS_PENHIDDEN      "Nascosta"
#define LOCALIZED_STATUS_POLYGONS       "Poligoni"
#define LOCALIZED_STATUS_VECTORS        "Vettori"
#define LOCALIZED_STATUS_NODES          "Nodi"
#define LOCALIZED_STATUS_NOT_APPLICABLE "N/D"

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           "&Tutte"
#define LOCALIZED_ERASEPROCEDURE                "Elimina Procedura"
#define LOCALIZED_EDITPROCEDURE                 "Modifica Procedura"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     "Colore"
#define LOCALIZED_SETCOLOR_PENCOLOR            "Colore Penna"
#define LOCALIZED_SETCOLOR_FLOODCOLOR          "Colore Riempimento"
#define LOCALIZED_SETCOLOR_SCREENCOLOR         "Colore Schermo"
#define LOCALIZED_SETCOLOR_RED                 "Rosso"
#define LOCALIZED_SETCOLOR_GREEN               "Verde"
#define LOCALIZED_SETCOLOR_BLUE                "Blu"
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   "Dimensione Penna"
#define LOCALIZED_SETPENSIZE_SIZE              "Spessore"
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     "Informazioni su " LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_ABOUTFMS_VERSION             "Versione"
#define LOCALIZED_ABOUTFMS_GUI                 "GUI di George Mills\nSoftronics, Inc.\nhttp://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_CORE                "Core di Brian Harvey\nUniversity of California Berkeley"
#define LOCALIZED_ABOUTFMS_INSTALLER           "Installatore basato su Nullsoft Scriptable Install System\nhttp://nsis.sourceforge.net/"
#define LOCALIZED_ABOUTFMS_ADVENTURE           "The Great Logo Adventure (ISBN 0-9651934-6-2)\nScritto e donato da Jim Muller\nDisponibile a http://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       "Ringrazimenti a Yehuda Katz e Erich Neuwirth"
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME " è free software\nVedere la Licenza Pubblica GNU"
#define LOCALIZED_ABOUTFMS_NEWSGROUP           "Internet News Group: comp.lang.logo\nVisita il Forum Logo a\nhttp://groups.yahoo.com/group/LogoForum/"
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     "Traduzione italiana di Stefano Federici, aggiunte e correzioni di Francesco Simone Carta"
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      "Informazioni su FMS"
#define LOCALIZED_ABOUTMS_FMS                  "FMS sta per Fight Multiple Sclerosis (Combatti la Sclerosi Multipla)"
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     "Ti preghiamo di considerare una donazione a\nNational Multiple Sclerosis Society.\nhttp://www.nmss.org\n1-800-FIGHT-MS"
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

#define LOCALIZED_CHANGESINEDITORMAYBELOST  "Le modifiche effettuate in questa sessione possono essere perse.\n\nSei sicuro di voler uscire da " LOCALIZED_GENERAL_PRODUCTNAME "?"
#define LOCALIZED_EDITSESSIONISRUNNING      "L'Editor è giù in esecuzione"

#define LOCALIZED_COULDNOTWRITEBMP            "Impossibile scrivere il file .bmp"
#define LOCALIZED_COULDNOTOPENBMP             "Impossibile aprire il file .bmp"
#define LOCALIZED_COULDNOTCREATEBMP           "Impossibile creare una bitmap Windows 3.0"
#define LOCALIZED_NOTVALIDBMP                 "Il file non è una bitmap Windows 3.0"

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         "Le modifiche non sono state salvate sul disco"
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     "L'esecuzione di questo comando cancellerà tutte le procedure definite.\n\nConfermi l'esecuzione del comando Nuovo?"
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE "Le definizioni delle procedure definire nel file di cui si è richiesto il caricamento verranno mescolate alle definizioni già presenti nello Spazio di Lavoro\ne potrebbero sovrascrivere eventuali modifiche non ancora salvate.\n\nConfermi l'esecuzione del comando Carica?"
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    "Questa operazioni causerà la perdita di tutte le modifiche non salvate.\n\nConfermi l'esecuzione del comando Apri?"

#define LOCALIZED_EDITORISOPEN                  "Sapevi di avere un'altra sessione di Editor già in esecuzione?\n\nQualunque modifica in questa sessione di Editor non verrà salvata."

#define LOCALIZED_ERROR_CANTREADFILE            "Impossibile leggere il file \"%s\" dal disco"
#define LOCALIZED_ERROR_CANTWRITEFILE           "Impossibile scrivere il file \"%s\" sul disco"

#define LOCALIZED_SAVETOWORKSPACE                "Salva nello Spazio di Lavoro"
#define LOCALIZED_CONTENTSCHANGED                "Il contenuto è stato modificato"
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE "Il contenuto è stato modificato.\nVuoi salvare le modifiche nello Spazio di Lavoro?"



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  "Il salvataggio del contenuto dell'Editor nello Spazio di Lavoro non è riuscito.  Il cursose verrà posto subito dopo l'ultima definizione salvata con successo.\n\nControlla l'area Comandi per eventuali messaggi d'errore."
#define LOCALIZED_RETURNTOEDIT                  "Vuoi tornare all'Editor?"

#define LOCALIZED_EDITFAILEDTOLOAD              LOCALIZED_SAVETOWORKSPACE

#define LOCALIZED_ERRORINFILETITLE              "Errore nel file"
#define LOCALIZED_ERRORINFILEMESSAGE            "C'è stato un problema durante il caricamento del file \"%s\".\n\nControlla l'elenco Comandi per possibili messaggi di errore.\n\nVuoi aprire l'Editor e vedere l'errore?"

#define LOCALIZED_CANNOTALLOCATESCREEN          "Impossibile allocare la memoria per la finestra. Potresti avere richiesto altezza e larghezza che eccedono la quantità di memoria video disponibile.\n\n" LOCALIZED_GENERAL_PRODUCTNAME " impossibile continuare."


// 
//  Strings used in the File-Open filters
//
#define LOCALIZED_FILE_LOAD_DIALOG_TITLE    "Scegli il programma Logo da caricare (aggiunge allo Spazio di Lavoro)"
#define LOCALIZED_FILE_OPEN_DIALOG_TITLE    "Scegli il programma Logo da aprire (sostituisce lo Spazio di Lavoro)"
#define LOCALIZED_FILE_SAVE_DIALOG_TITLE    "Scegli il file in cui salvare lo Spazio di Lavoro"
#define LOCALIZED_BITMAP_OPEN_DIALOG_TITLE  "Scegli l'immagine da caricare"
#define LOCALIZED_BITMAP_SAVE_DIALOG_TITLE  "Scegli il file in cui salvare l'area attiva"

#define LOCALIZED_LOGO_FILE_EXTENSION "lgo"
#define LOCALIZED_FILEFILTER_ALLFILES "Tutti i File (*.*)|*.*"
#define LOCALIZED_FILEFILTER_LOGO     "File Logo (*.lgo)|*.lgo|" LOCALIZED_FILEFILTER_ALLFILES
#define LOCALIZED_FILEFILTER_IMAGE    "File Bitmap (*.bmp)|*.bmp|File GIF (*.gif)|*.gif|" LOCALIZED_FILEFILTER_ALLFILES



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             " ferma\n"
#define LOCALIZED_TRACING_OUTPUTS           " scrive %s\n"
#define LOCALIZED_TRACING_MAKE              "Assegna %s %s"
#define LOCALIZED_TRACING_PPROP             "AsProp %s %s %s"
#define LOCALIZED_TRACING_LOCATION          " in %s\n%s"

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  "Passo Singolo"

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  "%s è stata definita\n"


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    "cancella"
#define LOCALIZED_PENMODE_REVERSE  "inversa"
#define LOCALIZED_PENMODE_PAINT    "disegna"

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          "Logo: Errore Interno Irreversibile"
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       "Logo: Memoria esaurita"
#define LOCALIZED_ERROR_OUTOFMEMORY            "Memoria esaurita"
#define LOCALIZED_ERROR_STACKOVERFLOW          "stack overflow"
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      "la tartaruga ha superato i confini"
#define LOCALIZED_ERROR_BADGRAPHINIT           "impossibile inizializzare il modulo grafico"
#define LOCALIZED_ERROR_BADDATA                "%p non può avere %s come argomento"
#define LOCALIZED_ERROR_DIDNTOUTPUT            "%p non ha prodotto un risultato che invece occorre a %p"
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        "argomenti insufficienti per %p"
#define LOCALIZED_ERROR_TOOMUCH                "superato il numero massimo di oggetti permessi all'interno di ()"
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    "Non so cosa fare con %s"
#define LOCALIZED_ERROR_PARENMISMATCH          "Troppe (" //
#define LOCALIZED_ERROR_NOVALUE                "%s non ha valore"
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        "')' inattesa"
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      "']' inattesa"
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        "'}' inattesa"
#define LOCALIZED_ERROR_DONTKNOWHOWTO          "Non so come fare %p"
#define LOCALIZED_ERROR_NOCATCHTAG             "Impossibile trovare il tag %p"
#define LOCALIZED_ERROR_ALREADYDEFINED         "%p è già definita"
#define LOCALIZED_ERROR_STOPPING               "Sto fermando..."
#define LOCALIZED_ERROR_ALREADYDRIBBLING       "Sto già registrando"
#define LOCALIZED_ERROR_FILESYSTEM                   "Errore del File System: %p"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          "Impossibile aprire il file"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         "Impossibile aprire il file: %t"
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       "File già aperto"
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           "File non aperto"
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  "Impossibile creare il file dell'Editor"
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   "Impossibile eseguire l'Editor"
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    "Impossibile leggere il file dell'Editor"
#define LOCALIZED_ERROR_IFWARNING              "Penso sia SEALTRIMENTI, non SE"
#define LOCALIZED_ERROR_SHADOWWARNING          "La variabile globale %p è nascosta da una variabile locale nella procedura chiamata"
#define LOCALIZED_ERROR_USER                   "Lancia \"Errore"
#define LOCALIZED_ERROR_ISPRIMITIVE            "%p è una primitiva"
#define LOCALIZED_ERROR_TONOTINSIDE            "Non è possibile usare PER all'interno di una procedura"
#define LOCALIZED_ERROR_ATTOPLEVEL             "%p può essere usato solo all'interno di una procedura"
#define LOCALIZED_ERROR_ATTOPLEVEL2            "E' necessario trovarsi all'interno di una procedura per usare RIPORTA o STOP"
#define LOCALIZED_ERROR_NOTEST                 "%p senza VERIFICA"
#define LOCALIZED_ERROR_BADMACROOUTPUT         "La Macro ha restituito %s invece di una lista"
#define LOCALIZED_ERROR_DEEPEND                "FINE all'interno di un'istruzione multi-riga"
#define LOCALIZED_ERROR_DEEPENDIN              "FINE FINE all'interno di un'istruzione multi-riga in %p"
#define LOCALIZED_ERROR_UNKNOWN                "Errore sconosciuto - errore interno."
#define LOCALIZED_PAUSING                      "In pausa..."


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION "Stato non valido per l'istruzione: %p"
#define LOCALIZED_ERROR_MODE_ON_SPRITE             "impossibile impostare il modo per una tartaruga con bitmap rotante"
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        "impossibile creare una tartaruga speciale con una bitmap rotante"
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            "non posso usare gli appunti come bitmap rotante"
#define LOCALIZED_ERROR_SPECIALFORM                "a %p non piace %p come argomento perché ha una forma speciale"

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      "Errore"
#define LOCALIZED_ERROR_BADINPUT             "Argomento errato"
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    "I dati inseriti non sono accoppiati correttamente"

#define LOCALIZED_ERROR_CANTOPENPORT         "Impossibile aprire la porta"
#define LOCALIZED_ERROR_CANTCLOSEPORT        "Impossibile chiudere la porta"
#define LOCALIZED_ERROR_CANTFLUSHPORT        "Impossibile inviare i dati alla porta"
#define LOCALIZED_ERROR_CANTDCBONPORT        "Impossibile costruire il blocco DCB sulla porta"
#define LOCALIZED_ERROR_CANTSETPORT          "Impossibile configurare la porta"
#define LOCALIZED_ERROR_PORTALREADYOPEN      "La porta è già aperta"
#define LOCALIZED_ERROR_PORTNOTOPEN          "La porta non è aperta"

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   "%s esiste già"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    "%s non esiste"

#define LOCALIZED_ERROR_DLLNOTLOADED          "La DLL non è stata caricata"
#define LOCALIZED_ERROR_DLLLOADFAILED         "Il caricamento della DLL è fallito"
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    "Il tipo dell'argomento non è valido"
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  "Il tipo del risultato non è valido"
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   "Funzione non trovata"
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  "Non tutte le coppie Tipo/Dato sono correttamente accoppiate"

#define LOCALIZED_ERROR_NETWORK               "Errore di rete"
#define LOCALIZED_ERROR_NETWORKRECEIVE        "Errore di ricezione dalla rete"
#define LOCALIZED_ERROR_NETWORKSEND           "Errore di invio alla rete"
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       "Errore inatteso, E' possibile che la connessione di rete sia caduta"
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     "Non avviata"
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED "Già avviata"
#define LOCALIZED_ERROR_NETWORKALREADYON      "Già attiva"
#define LOCALIZED_ERROR_NETWORKALREADYOFF     "Già disattivata"

// The rest of the network errors shouldn't really be seen -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         "Nome troppo lungo"
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      "Non inzializzata"
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      "Il sistema non è pronto"
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED "La versione non è supportata"
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   "Impossibile inviare i dati dopo la disconnessione"
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         "Chiamata di sistema interrotta"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    "Risposta Authoritative: Host non trovato"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH "Non-Authoritative: Host non trovato. Vedi RETEAVVIA"
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      "Errore irreversibile"
#define LOCALIZED_ERROR_NETWORKNODATA              "Data Record non disponibile"
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       "File Number errato"
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          "Questa operazione causerebbe un blocco"
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       "L'Operazione è ora in corso"
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   "L'Operazione è già in corso"
#define LOCALIZED_ERROR_NETWORKBADADDRESS          "Indirizzo errato"
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     "Indirizzo di destinazione obbligatorio"
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      "Messaggio troppo lungo"
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      "Famiglia di protocolli non supportata"
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         "La cartella non è vuota"
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     "Il limite dell'applicazione è stato raggiunto"
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           "La quota di disco è stata superata"
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        "Troppi file aperti"
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        "Accesso negato"
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          "Richiesta un'operazione di socket su qualcosa che non è un socket"
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    "Impossibile assegnare l'indirizzo richiesto"
#define LOCALIZED_ERROR_NETWORKADDRINUSE           "Indirizzo già in uso"
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      "Famiglia di indirizzi non supportata dalla famiglia di protocolli"
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            "Connessione scaduta"
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    "Tipo di socket non supportato"
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   "Protocollo non supportato"
#define LOCALIZED_ERROR_NETWORKNOBUFFER            "Spazio insufficiente nel buffer"
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    "Il socket è già connesso"
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        "Il socket non è connesso"
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         "Opzioni errata per questo protocollo"
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     "La connessione è stata resettata dall'altro computer"
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     "Il programma ha causato la perdita della connessione"
#define LOCALIZED_ERROR_NETWORKISDOWN              "La connessione di rete non è attiva"
#define LOCALIZED_ERROR_NETWORKRESET               "La connessione di rete è stata resettata"
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   "La richiesta di connessione è stat rifiutata"
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          "L'host non è attivo"
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   "L'host non è raggiungibile"
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        "Il tipo di protocollo non è corretto per questo socket"
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   "Questa operazione non è supportata da questo socket"
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         "L'host remoto non è raggiungibile"
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         "Troppi riferimenti"

#define LOCALIZED_ERROR_POLYSTART               "Errore INIZIOPOLI"
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED "Hai già un poligono avviato"

#define LOCALIZED_ERROR_POLYEND                 "Errore FINEPOLI"
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       "Non hai iniziato un poligono"
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     "Devi avere almeno 3 segmenti per definire un poligono"

#define LOCALIZED_ERROR_SOUND                 "Errore Suono"

#define LOCALIZED_ERROR_MIDI                  "Errore MIDI"
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     "Dispositivo MIDI non valido"
#define LOCALIZED_ERROR_MIDIALREADYOPEN       "Già aperto"
#define LOCALIZED_ERROR_MIDINOTOPEN           "Già chiuso"

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      "La Clipboard è vuota"

#define LOCALIZED_ERROR_MCI                   "Errore MCI"

#define LOCALIZED_ERROR_TIMERNOTFOUND         "Timer non trovato"

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       "Help online non disponibile in quanto non è stato possibile caricare il file hhctrl.ocx"

#define LOCALIZED_ERROR_BADCOMMANDLINE        "Linea di comando non valida"

#define LOCALIZED_ERROR_TMPNOTDEFINED         "La variabile di ambiente TMP non è definita oppure è non valida.\n" LOCALIZED_GENERAL_PRODUCTNAME " tenterà di usare C:\\ per memorizzare i file temporanei"

#define LOCALIZED_ERROR_GIFSAVEFAILED         "Si è verificato un problema nella generazione del file GIF, controlla la memoria e lo spazio disponibile sul disco"
#define LOCALIZED_ERROR_GIFREADFAILED         "Si è verificato un problema nella lettura del file GIF, controlla la memoria e lo spazio disponibile sul disco"

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  "Indice BitMap fuori dall'intervallo"
#define LOCALIZED_ERROR_BITMAPCUTFAILED        "Taglia fallito, E' possibile che non ci sia abbastanza memoria disponibile"

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    "Non c'è niente da incollare"
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  "L'indice fornito non è un indice di BitMap valido"

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      "La tartaruga %d non ha una immagine associate e verrà quindi fermata"

#define LOCALIZED_ERROR_FONTNOTFOUND            "Spiacente ma non è stato trovato alcun carattere il cui nome sia %s.  Scegli uno dei seguenti caratteri:\n"

#define LOCALIZED_ERROR_PRINTERCANTSCALE        "Il driver della stampante non supporta questa funzionalità"
#define LOCALIZED_ERROR_CANTDRAWIMAGE           "Impossibile disegnare l'immagine"
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        "Impossibile estrarre l'immagine"
#define LOCALIZED_ERROR_SUBCODE                 "Codice di errore di Windows"

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         "Immissione:"
#define LOCALIZED_PROMPT_TO     "Modo PER (Annulla per terminare)"
#define LOCALIZED_PROMPT_LIST   "Modo Lista (Annulla per terminare)"
#define LOCALIZED_PROMPT_PAUSE  "Modo Pausa (Annulla per continuare)"
#define LOCALIZED_PROMPT_INPUT  "Modo Immissione (Annulla per terminare)"

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      "La nuova cartella è \"%s\""
#define LOCALIZED_FILE_CHDIRFAILED         "Impossibile chdir nella cartella \"%s\""
#define LOCALIZED_FILE_POPPEDTO            "Salito alla cartella \"%s\""
#define LOCALIZED_FILE_MKDIRSUCCEEDED      "Spostato nella nuova cartella \"%s\""
#define LOCALIZED_FILE_MKDIRFAILED         "Impossibile create la cartella \"%s\""
#define LOCALIZED_FILE_RMDIRSUCCEEDED      "Eliminata la cartella \"%s\""
#define LOCALIZED_FILE_RMDIRFAILED         "Impossibile eliminare la cartella \"%s\""
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  "La cartella non eiste."
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY "Assicurarsi che la cartella sia vuota prima di provare ad eliminarla."


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       "Immagine Logo"

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    "Area Attiva"
#define LOCALIZED_INFORMATION   "Informazioni"
#define LOCALIZED_WARNING       "Avviso"
#define LOCALIZED_UNTITLED      "Senzatitolo"
#define LOCALIZED_UNKNOWN       "Sconosciuto"

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       "Non inzializzato"

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     "Trova"
#define LOCALIZED_EDITOR_TITLE_REPLACE  "Sostituisci"

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING "%s non trovato"


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
#define LOCALIZED_COLOR_ALICEBLUE             "BluAlice"
#define LOCALIZED_COLOR_ANTIQUEWHITE          "BiancoDiTitanio"
#define LOCALIZED_COLOR_AQUA                  "Acqua"
#define LOCALIZED_COLOR_AQUAMARINE            "Acquamarina"
#define LOCALIZED_COLOR_AZURE                 "Azzurro"
#define LOCALIZED_COLOR_BEIGE                 "Beige"
#define LOCALIZED_COLOR_BISQUE                "Biscotto"
#define LOCALIZED_COLOR_BLACK                 "Nero"
#define LOCALIZED_COLOR_BLANCHEDALMOND        "MandorlaBollita"
#define LOCALIZED_COLOR_BLUE                  "Blu"
#define LOCALIZED_COLOR_BLUEVIOLET            "IndacoScuro"
#define LOCALIZED_COLOR_BROWN                 "Marrone"
#define LOCALIZED_COLOR_BURLYWOOD             "Radica"
#define LOCALIZED_COLOR_CADETBLUE             "BluCadetto"
#define LOCALIZED_COLOR_CHARTREUSE            "Chartreuse"
#define LOCALIZED_COLOR_CHOCOLATE             "Cioccolato"
#define LOCALIZED_COLOR_CORAL                 "Corallo"
#define LOCALIZED_COLOR_CORNFLOWERBLUE        "BluFiordaliso"
#define LOCALIZED_COLOR_CORNSILK              "SetaMais"
#define LOCALIZED_COLOR_CRIMSON               "Cremisi"
#define LOCALIZED_COLOR_CYAN                  "Ciano"
#define LOCALIZED_COLOR_DARKBLUE              "BluScuro"
#define LOCALIZED_COLOR_DARKCYAN              "CianoScuro"
#define LOCALIZED_COLOR_DARKGOLDENROD         "SolidagoScuro"
#define LOCALIZED_COLOR_DARKGRAY              "GrigioScuro"
#define LOCALIZED_COLOR_DARKGREEN             "VerdeScuro"
#define LOCALIZED_COLOR_DARKGREY              "GrigioScuro"
#define LOCALIZED_COLOR_DARKKHAKI             "KakiScuro"
#define LOCALIZED_COLOR_DARKMAGENTA           "MagentaScuro"
#define LOCALIZED_COLOR_DARKOLIVEGREEN        "VerdeOlivaScuro"
#define LOCALIZED_COLOR_DARKORANGE            "ArancioneScuro"
#define LOCALIZED_COLOR_DARKORCHID            "OrchideaScuro"
#define LOCALIZED_COLOR_DARKRED               "RossoScuro"
#define LOCALIZED_COLOR_DARKSALMON            "SalmoneScuro"
#define LOCALIZED_COLOR_DARKSEAGREEN          "VerdeMarinoScuro"
#define LOCALIZED_COLOR_DARKSLATEBLUE         "BluArdesiaScuro"
#define LOCALIZED_COLOR_DARKSLATEGRAY         "GrigioArdesiaScuro"
#define LOCALIZED_COLOR_DARKSLATEGREY         "GrigioArdesiaScuro"
#define LOCALIZED_COLOR_DARKTURQUOISE         "TurcheseScuro"
#define LOCALIZED_COLOR_DARKVIOLET            "ViolettaScuro"
#define LOCALIZED_COLOR_DEEPPINK              "RosaProfondo"
#define LOCALIZED_COLOR_DEEPSKYBLUE           "CelesteProfondo"
#define LOCALIZED_COLOR_DIMGRAY               "GrigioTenue"
#define LOCALIZED_COLOR_DIMGREY               "GrigioTenue"
#define LOCALIZED_COLOR_DODGERBLUE            "BluDodger"
#define LOCALIZED_COLOR_FIREBRICK             "RossoMattone"
#define LOCALIZED_COLOR_FLORALWHITE           "BiancoFloreale"
#define LOCALIZED_COLOR_FORESTGREEN           "VerdeForesta"
#define LOCALIZED_COLOR_FUCHSIA               "Fucsia"
#define LOCALIZED_COLOR_GAINSBORO             "Gainsboro"
#define LOCALIZED_COLOR_GHOSTWHITE            "BiancoFantasma"
#define LOCALIZED_COLOR_GOLD                  "Oro"
#define LOCALIZED_COLOR_GOLDENROD             "Solidago"
#define LOCALIZED_COLOR_GRAY                  "Grigio"
#define LOCALIZED_COLOR_GREEN                 "Verde"
#define LOCALIZED_COLOR_GREENYELLOW           "VerdeGiallo"
#define LOCALIZED_COLOR_GREY                  "Grigio"
#define LOCALIZED_COLOR_HONEYDEW              "MeloneVerde"
#define LOCALIZED_COLOR_HOTPINK               "RosaCaldo"
#define LOCALIZED_COLOR_INDIANRED             "Castagno"
#define LOCALIZED_COLOR_INDIGO                "Indaco"
#define LOCALIZED_COLOR_IVORY                 "Avorio"
#define LOCALIZED_COLOR_KHAKI                 "Kaki"
#define LOCALIZED_COLOR_LAVENDER              "Lavanda"
#define LOCALIZED_COLOR_LAVENDERBLUSH         "LavandaRosata"
#define LOCALIZED_COLOR_LAWNGREEN             "VerdePrato"
#define LOCALIZED_COLOR_LEMONCHIFFON          "LimoneCrema"
#define LOCALIZED_COLOR_LIGHTBLUE             "BluChiaro"
#define LOCALIZED_COLOR_LIGHTCORAL            "CoralloChiaro"
#define LOCALIZED_COLOR_LIGHTCYAN             "CianoChiaro"
#define LOCALIZED_COLOR_LIGHTGOLDENRODYELLOW  "SolidagoChiaro"
#define LOCALIZED_COLOR_LIGHTGRAY             "GrigioChiaro"
#define LOCALIZED_COLOR_LIGHTGREEN            "VerdeChiaro"
#define LOCALIZED_COLOR_LIGHTGREY             "GrigioChiaro"
#define LOCALIZED_COLOR_LIGHTPINK             "RosaChiaro"
#define LOCALIZED_COLOR_LIGHTSALMON           "SalmoneChiaro"
#define LOCALIZED_COLOR_LIGHTSEAGREEN         "VerdemareChiaro"
#define LOCALIZED_COLOR_LIGHTSKYBLUE          "CelesteChiaro"
#define LOCALIZED_COLOR_LIGHTSLATEGRAY        "GrigioArdesiaChiaro"
#define LOCALIZED_COLOR_LIGHTSLATEGREY        "GrigioArdesiaChiaro"
#define LOCALIZED_COLOR_LIGHTSTEELBLUE        "BluAcciaioChiaro"
#define LOCALIZED_COLOR_LIGHTYELLOW           "GialloChiaro"
#define LOCALIZED_COLOR_LIME                  "Lime"
#define LOCALIZED_COLOR_LIMEGREEN             "LimeVerde"
#define LOCALIZED_COLOR_LINEN                 "Lino"
#define LOCALIZED_COLOR_MAGENTA               "Magenta"
#define LOCALIZED_COLOR_MAROON                "Bordò"
#define LOCALIZED_COLOR_MEDIUMAQUAMARINE      "AcquamarinaMedio"
#define LOCALIZED_COLOR_MEDIUMBLUE            "BluMedio"
#define LOCALIZED_COLOR_MEDIUMORCHID          "OrchideaMedio"
#define LOCALIZED_COLOR_MEDIUMPURPLE          "ViolaMedio"
#define LOCALIZED_COLOR_MEDIUMSEAGREEN        "VerdemareMedio"
#define LOCALIZED_COLOR_MEDIUMSLATEBLUE       "BluArdesiaMedio"
#define LOCALIZED_COLOR_MEDIUMSPRINGGREEN     "VerdePrimaveraMedio"
#define LOCALIZED_COLOR_MEDIUMTURQUOISE       "TurcheseMedio"
#define LOCALIZED_COLOR_MEDIUMVIOLETRED       "RossoViolaceoMedio"
#define LOCALIZED_COLOR_MIDNIGHTBLUE          "BluNotte"
#define LOCALIZED_COLOR_MINTCREAM             "CremaMenta"
#define LOCALIZED_COLOR_MISTYROSE             "RosaRugiada"
#define LOCALIZED_COLOR_MOCCASIN              "Mocassino"
#define LOCALIZED_COLOR_NAVAJOWHITE           "BiancoNavajo"
#define LOCALIZED_COLOR_NAVY                  "BluMarino"
#define LOCALIZED_COLOR_OLDLACE               "VecchioPizzo"
#define LOCALIZED_COLOR_OLIVE                 "VerdeOliva"
#define LOCALIZED_COLOR_OLIVEDRAB             "VerdeOlivastro"
#define LOCALIZED_COLOR_ORANGE                "Arancione"
#define LOCALIZED_COLOR_ORANGERED             "Vermiglione"
#define LOCALIZED_COLOR_ORCHID                "Orchidea"
#define LOCALIZED_COLOR_PALEGOLDENROD         "SolidagoPallido"
#define LOCALIZED_COLOR_PALEGREEN             "VerdePallido"
#define LOCALIZED_COLOR_PALETURQUOISE         "TurchesePallido"
#define LOCALIZED_COLOR_PALEVIOLETRED         "RossoViolaceoPallido"
#define LOCALIZED_COLOR_PAPAYAWHIP            "Papaia"
#define LOCALIZED_COLOR_PEACHPUFF             "PescaScuro"
#define LOCALIZED_COLOR_PERU                  "MarroneChiaro"
#define LOCALIZED_COLOR_PINK                  "Rosa"
#define LOCALIZED_COLOR_PLUM                  "Prugna"
#define LOCALIZED_COLOR_POWDERBLUE            "BluPolvere"
#define LOCALIZED_COLOR_PURPLE                "Viola"
#define LOCALIZED_COLOR_RED                   "Rosso"
#define LOCALIZED_COLOR_ROSYBROWN             "MarroneRosato"
#define LOCALIZED_COLOR_ROYALBLUE             "BluReale"
#define LOCALIZED_COLOR_SADDLEBROWN           "MarroneSella"
#define LOCALIZED_COLOR_SALMON                "Salmone"
#define LOCALIZED_COLOR_SANDYBROWN            "Sabbia"
#define LOCALIZED_COLOR_SEAGREEN              "VerdeMarino"
#define LOCALIZED_COLOR_SEASHELL              "Conchiglia"
#define LOCALIZED_COLOR_SIENNA                "TerraDiSiena"
#define LOCALIZED_COLOR_SILVER                "Argento"
#define LOCALIZED_COLOR_SKYBLUE               "Celeste"
#define LOCALIZED_COLOR_SLATEBLUE             "BluArdesia"
#define LOCALIZED_COLOR_SLATEGRAY             "GrigioArdesia"
#define LOCALIZED_COLOR_SLATEGREY             "GrigioArdesia"
#define LOCALIZED_COLOR_SNOW                  "Neve"
#define LOCALIZED_COLOR_SPRINGGREEN           "VerdePrimavera"
#define LOCALIZED_COLOR_STEELBLUE             "BluAcciaio"
#define LOCALIZED_COLOR_TAN                   "Catrame"
#define LOCALIZED_COLOR_TEAL                  "BluTè"
#define LOCALIZED_COLOR_THISTLE               "Cardo"
#define LOCALIZED_COLOR_TOMATO                "RossoPomodoro"
#define LOCALIZED_COLOR_TURQUOISE             "Turchese"
#define LOCALIZED_COLOR_VIOLET                "Violetta"
#define LOCALIZED_COLOR_WHEAT                 "Grano"
#define LOCALIZED_COLOR_WHITE                 "Bianco"
#define LOCALIZED_COLOR_WHITESMOKE            "BiancoFumo"
#define LOCALIZED_COLOR_YELLOW                "Giallo"
#define LOCALIZED_COLOR_YELLOWGREEN           "GialloVerde"

//
// The name of each "window class" that DEBUGWINDOWS prints.
// These should match the corresponding terms that is used
// in the  LOCALIZED_ALTERNATE_*CREATE procedures.
//
#define LOCALIZED_WINDOWCLASSNAME_WINDOW       "Finestra"
#define LOCALIZED_WINDOWCLASSNAME_STATIC       "Etichetta"
#define LOCALIZED_WINDOWCLASSNAME_LISTBOX      "ListaScelta"
#define LOCALIZED_WINDOWCLASSNAME_COMBOBOX     "Combo"
#define LOCALIZED_WINDOWCLASSNAME_BUTTON       "Pulsante"
#define LOCALIZED_WINDOWCLASSNAME_SCROLLBAR    "BarraScorrimento"
#define LOCALIZED_WINDOWCLASSNAME_GROUPBOX     "Gruppo"
#define LOCALIZED_WINDOWCLASSNAME_RADIOBUTTON  "PulsanteRadio"
#define LOCALIZED_WINDOWCLASSNAME_CHECKBOX     "Casella"
#define LOCALIZED_WINDOWCLASSNAME_DIALOG       "Dialogo"


//
// The name of the default font face name.
// This should only be translated if the given font face doesn't include glyphs
// for characters in your language.  The specified font face name must be part
// of all Windows versions from Windows XP onward that would support your
// language.
//
#define LOCALIZED_DEFAULT_FONT_FACE "Courier New" // NOT_YET_LOCALIZED
