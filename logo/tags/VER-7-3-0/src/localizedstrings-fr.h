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
// This file contains localized strings for French by Bertrand CARETTE
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
#define LOCALIZED_ALTERNATE_TRUE     "vrai"
#define LOCALIZED_ALTERNATE_FALSE    "faux"
#define LOCALIZED_ALTERNATE_END      "fin"
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
#define LOCALIZED_ALTERNATE__DEFMACRO              ".défmacro" // 
#define LOCALIZED_ALTERNATE__EQ                    ".identique?" // 
#define LOCALIZED_ALTERNATE__MACRO                 ".macro" // 
#define LOCALIZED_ALTERNATE__MAYBEOUTPUT           ".retournepeutêtre" // 
#define LOCALIZED_ALTERNATE__SETBF                 ".fixesp"
#define LOCALIZED_ALTERNATE__SETFIRST              ".fixepremier"
#define LOCALIZED_ALTERNATE__SETITEM               ".fixeitem"
#define LOCALIZED_ALTERNATE_ACTIVEAREA             "zoneactive" 
#define LOCALIZED_ALTERNATE_ALLOPEN                "fluxouverts" // 
#define LOCALIZED_ALTERNATE_AND                    "et"
#define LOCALIZED_ALTERNATE_APPLY                  "applique" // 
#define LOCALIZED_ALTERNATE_ARCCOS                 "arccos"
#define LOCALIZED_ALTERNATE_ARCSIN                 "arcsin"
#define LOCALIZED_ALTERNATE_ARCTAN                 "arctan"
#define LOCALIZED_ALTERNATE_ARITY                  "arity" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARRAY                  "tableau" // 
#define LOCALIZED_ALTERNATE_ARRAYP                 "tableaup" // 
#define LOCALIZED_ALTERNATE_ARRAY_                 "tableau?" // 
#define LOCALIZED_ALTERNATE_ASCII                  "ascii" // 
#define LOCALIZED_ALTERNATE_ASHIFT                 "décale" // 
#define LOCALIZED_ALTERNATE_BACK                   "recule"
#define LOCALIZED_ALTERNATE_BACKSLASHEDP           "antislash" // 
#define LOCALIZED_ALTERNATE_BACKSLASHED_           "antislash?" // 
#define LOCALIZED_ALTERNATE_BEFOREP                "précèdep"
#define LOCALIZED_ALTERNATE_BEFORE_                "précède?"
#define LOCALIZED_ALTERNATE_BF                     "sp"
#define LOCALIZED_ALTERNATE_BFS                    "sps"
#define LOCALIZED_ALTERNATE_BITAND                 "etbit" // 
#define LOCALIZED_ALTERNATE_BITBLOCK               "pavé" // 
#define LOCALIZED_ALTERNATE_BITCOPY                "copiedessin"
#define LOCALIZED_ALTERNATE_BITCUT                 "coupedessin"
#define LOCALIZED_ALTERNATE_BITFIT                 "ajustedessin" // 
#define LOCALIZED_ALTERNATE_BITINDEX               "indexdessin"
#define LOCALIZED_ALTERNATE_BITLOAD                "ramènedessin"
#define LOCALIZED_ALTERNATE_BITLOADSIZE            "ramènetailledes"
#define LOCALIZED_ALTERNATE_BITSIZE                "tailledessin"
#define LOCALIZED_ALTERNATE_BITMAPTURTLE           "formetortue"
#define LOCALIZED_ALTERNATE_BITMODE                "modedessin" // 
#define LOCALIZED_ALTERNATE_BITNOT                 "nonbit" // 
#define LOCALIZED_ALTERNATE_BITOR                  "oubit" // 
#define LOCALIZED_ALTERNATE_BITPASTE               "colledessin"
#define LOCALIZED_ALTERNATE_BITPASTETOINDEX        "collesurindex"
#define LOCALIZED_ALTERNATE_BITSAVE                "sauvedessin"
#define LOCALIZED_ALTERNATE_BITXOR                 "ouxbit" // 
#define LOCALIZED_ALTERNATE_BK                     "re"
#define LOCALIZED_ALTERNATE_BL                     "sd"
#define LOCALIZED_ALTERNATE_BURIED                 "enterrées" // 
#define LOCALIZED_ALTERNATE_BURY                   "enterre" // 
#define LOCALIZED_ALTERNATE_BUTFIRST               "saufpremier"
#define LOCALIZED_ALTERNATE_BUTFIRSTS              "saufpremiers" // 
#define LOCALIZED_ALTERNATE_BUTLAST                "saufdernier" // 
#define LOCALIZED_ALTERNATE_BUTTONCREATE           "créebouton" // 
#define LOCALIZED_ALTERNATE_BUTTONDELETE           "effacebouton" // 
#define LOCALIZED_ALTERNATE_BUTTONENABLE           "activebouton" // 
#define LOCALIZED_ALTERNATE_BUTTONUPDATE           "actualisebouton" // 
#define LOCALIZED_ALTERNATE_BUTTONP                "boutonp" // 
#define LOCALIZED_ALTERNATE_BUTTON_                "bouton?" // 
#define LOCALIZED_ALTERNATE_BYE                    "aurevoir"
#define LOCALIZED_ALTERNATE_CATCH                  "attrape"
#define LOCALIZED_ALTERNATE_CHAR                   "car"
#define LOCALIZED_ALTERNATE_CHDIR                  "chrép" // 
#define LOCALIZED_ALTERNATE_CHECKBOXCREATE         "créecasechoix" // 
#define LOCALIZED_ALTERNATE_CHECKBOXDELETE         "effacecasechoix" // 
#define LOCALIZED_ALTERNATE_CHECKBOXENABLE         "activecasechoix" // 
#define LOCALIZED_ALTERNATE_CHECKBOXGET            "casechoix" // 
#define LOCALIZED_ALTERNATE_CHECKBOXSET            "fixecasechoix" // 
#define LOCALIZED_ALTERNATE_CLEAN                  "nettoie"
#define LOCALIZED_ALTERNATE_CLEARPALETTE           "videpalette"
#define LOCALIZED_ALTERNATE_CLEARSCREEN            "videécran"
#define LOCALIZED_ALTERNATE_CLEARTEXT              "videtexte"
#define LOCALIZED_ALTERNATE_CLEARTIMER             "videchrono" // 
#define LOCALIZED_ALTERNATE_CLOSE                  "ferme"
#define LOCALIZED_ALTERNATE_CLOSEALL               "fermetout"
#define LOCALIZED_ALTERNATE_CO                     "co"
#define LOCALIZED_ALTERNATE_COMBOBOXADDSTRING      "ajouteitemcombo" // 
#define LOCALIZED_ALTERNATE_COMBOBOXCREATE         "créecombo" // 
#define LOCALIZED_ALTERNATE_COMBOBOXDELETE         "effacecombo" // 
#define LOCALIZED_ALTERNATE_COMBOBOXENABLE         "activecombo" // 
#define LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING   "effaceitemcombo" // 
#define LOCALIZED_ALTERNATE_COMBOBOXGETTEXT        "textecombo" // 
#define LOCALIZED_ALTERNATE_COMBOBOXSETTEXT        "fixetextecombo" // 
#define LOCALIZED_ALTERNATE_CONTENTS               "contenu" // 
#define LOCALIZED_ALTERNATE_CONTINUE               "continue"
#define LOCALIZED_ALTERNATE_COPYDEF                "donnedéf" // 
#define LOCALIZED_ALTERNATE_COS                    "cos"
#define LOCALIZED_ALTERNATE_COUNT                  "compte"
#define LOCALIZED_ALTERNATE_CS                     "vé"
#define LOCALIZED_ALTERNATE_CT                     "vt"
#define LOCALIZED_ALTERNATE_CURSOR                 "curseur" // 
#define LOCALIZED_ALTERNATE_DEBUGWINDOWS           "déboguefenêtres" // 
#define LOCALIZED_ALTERNATE_DEFINE                 "définis"
#define LOCALIZED_ALTERNATE_DEFINEDP               "definedp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DEFINED_               "defined?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DIALOGCREATE           "créedialogue" // 
#define LOCALIZED_ALTERNATE_DIALOGENABLE           "activedialogue" // 
#define LOCALIZED_ALTERNATE_DIALOGDELETE           "effacedialogue" // 
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         "ouvrefichier" // 
#define LOCALIZED_ALTERNATE_DIALOGFILESAVE         "sauvefichier" // 
#define LOCALIZED_ALTERNATE_DIFFERENCE             "différence"
#define LOCALIZED_ALTERNATE_DIRECTORIES            "répertoires"
#define LOCALIZED_ALTERNATE_DLLCALL                "appelledll" // 
#define LOCALIZED_ALTERNATE_DLLFREE                "libèredll" // 
#define LOCALIZED_ALTERNATE_DLLLOAD                "chargedll" // 
#define LOCALIZED_ALTERNATE_DOWN                   "pique" // 
#define LOCALIZED_ALTERNATE_DOWNPITCH              "pique" // 
#define LOCALIZED_ALTERNATE_DRIBBLE                "transcription" // 
#define LOCALIZED_ALTERNATE_ED                     "éd"
#define LOCALIZED_ALTERNATE_EDIT                   "édite"
#define LOCALIZED_ALTERNATE_ELLIPSEARC             "ellipsearc" // 
#define LOCALIZED_ALTERNATE_EMPTYP                 "videp"
#define LOCALIZED_ALTERNATE_EMPTY_                 "vide?"
#define LOCALIZED_ALTERNATE_EOFP                   "eofp" // 
#define LOCALIZED_ALTERNATE_EOF_                   "ff?" // 
#define LOCALIZED_ALTERNATE_EQUALP                 "égalp"
#define LOCALIZED_ALTERNATE_EQUAL_                 "égal?"
#define LOCALIZED_ALTERNATE_ER                     "ef" // 
#define LOCALIZED_ALTERNATE_ERASE                  "efface"
#define LOCALIZED_ALTERNATE_ERASEFILE              "effacefichier" // 
#define LOCALIZED_ALTERNATE_ERF                    "eff" // 
#define LOCALIZED_ALTERNATE_ERROR                  "erreur"
#define LOCALIZED_ALTERNATE_EVENTCHECK             "testév" // 
#define LOCALIZED_ALTERNATE_EXP                    "exp" // 
#define LOCALIZED_ALTERNATE_FD                     "av"
#define LOCALIZED_ALTERNATE_FENCE                  "clos"
#define LOCALIZED_ALTERNATE_FILL                   "remplis"
#define LOCALIZED_ALTERNATE_FILES                  "fichiers"
#define LOCALIZED_ALTERNATE_FIRST                  "premier"
#define LOCALIZED_ALTERNATE_FIRSTS                 "premiers"
#define LOCALIZED_ALTERNATE_FLOODCOLOR             "couleurremplissage"
#define LOCALIZED_ALTERNATE_FONTFACENAMES          "listepolices" // 
#define LOCALIZED_ALTERNATE_FOREVER                "pourtoujours" // 
#define LOCALIZED_ALTERNATE_FORM                   "formate" // 
#define LOCALIZED_ALTERNATE_FORWARD                "avance"
#define LOCALIZED_ALTERNATE_FPUT                   "metspremier"
#define LOCALIZED_ALTERNATE_FS                     "péc" // 
#define LOCALIZED_ALTERNATE_FULLSCREEN             "pleinécran" // 
#define LOCALIZED_ALTERNATE_FULLTEXT               "pleintexte" // 
#define LOCALIZED_ALTERNATE_GETFOCUS               "focus" // 
#define LOCALIZED_ALTERNATE_GOTO                   "vavers" // 
#define LOCALIZED_ALTERNATE_GIFLOAD                "ramènegif" // 
#define LOCALIZED_ALTERNATE_GIFSIZE                "taillegif" // 
#define LOCALIZED_ALTERNATE_GIFSAVE                "sauvegif" // 
#define LOCALIZED_ALTERNATE_GPROP                  "rprop" // 
#define LOCALIZED_ALTERNATE_GREATEREQUALP          "supérieurégalp" // 
#define LOCALIZED_ALTERNATE_GREATEREQUAL_          "supérieurégal?" // 
#define LOCALIZED_ALTERNATE_GREATERP               "supérieurp" // 
#define LOCALIZED_ALTERNATE_GREATER_               "supérieur?" // 
#define LOCALIZED_ALTERNATE_GROUPBOXCREATE         "créegroupe" // 
#define LOCALIZED_ALTERNATE_GROUPBOXDELETE         "effacegroupe" // 
#define LOCALIZED_ALTERNATE_HALT                   "arrêtetout" // 
#define LOCALIZED_ALTERNATE_HASOWNPENP             "hasownpenp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HASOWNPEN_             "hasownpen?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HEADING                "cap" //
#define LOCALIZED_ALTERNATE_HELP                   "aide" // 
#define LOCALIZED_ALTERNATE_HIDETURTLE             "cachetortue"
#define LOCALIZED_ALTERNATE_HOME                   "origine"
#define LOCALIZED_ALTERNATE_HT                     "ct"
#define LOCALIZED_ALTERNATE_IF                     "si"
#define LOCALIZED_ALTERNATE_IFELSE                 "sisinon"
#define LOCALIZED_ALTERNATE_IFF                    "sif"
#define LOCALIZED_ALTERNATE_IFFALSE                "sifaux"
#define LOCALIZED_ALTERNATE_IFT                    "siv"
#define LOCALIZED_ALTERNATE_IFTRUE                 "sivrai"
#define LOCALIZED_ALTERNATE_INGAMEPORT             "lisportjeu" // 
#define LOCALIZED_ALTERNATE_INPORT                 "lisport" // 
#define LOCALIZED_ALTERNATE_INPORTB                "lisportb" // 
#define LOCALIZED_ALTERNATE_INT                    "tronque"
#define LOCALIZED_ALTERNATE_ITEM                   "item" // 
#define LOCALIZED_ALTERNATE_KEYBOARDOFF            "désactiveclavier" //
#define LOCALIZED_ALTERNATE_KEYBOARDON             "activeclavier" //
#define LOCALIZED_ALTERNATE_KEYBOARDVALUE          "clavier" //
#define LOCALIZED_ALTERNATE_KEYP                   "touchep"
#define LOCALIZED_ALTERNATE_KEY_                   "touche?"
#define LOCALIZED_ALTERNATE_LABEL                  "étiquette"
#define LOCALIZED_ALTERNATE_LABELFONT              "policeétiquette"
#define LOCALIZED_ALTERNATE_LABELSIZE              "tailleétiquette" // 
#define LOCALIZED_ALTERNATE_LAST                   "dernier" // 
#define LOCALIZED_ALTERNATE_LEFT                   "gauche"
#define LOCALIZED_ALTERNATE_LEFTROLL               "inclinegauche" // 
#define LOCALIZED_ALTERNATE_LESSEQUALP             "inférieurégalp" // 
#define LOCALIZED_ALTERNATE_LESSEQUAL_             "inférieurégal?" // 
#define LOCALIZED_ALTERNATE_LESSP                  "inférieurp" // 
#define LOCALIZED_ALTERNATE_LESS_                  "inférieur?" // 
#define LOCALIZED_ALTERNATE_LIGHT                  "lumière" // 
#define LOCALIZED_ALTERNATE_LIST                   "liste"
#define LOCALIZED_ALTERNATE_LISTBOXADDSTRING       "ajouteitemliste" // 
#define LOCALIZED_ALTERNATE_LISTBOXCREATE          "créeliste" // 
#define LOCALIZED_ALTERNATE_LISTBOXENABLE          "activeliste" // 
#define LOCALIZED_ALTERNATE_LISTBOXDELETE          "effaceliste" // 
#define LOCALIZED_ALTERNATE_LISTBOXDELETESTRING    "effaceitemliste" // 
#define LOCALIZED_ALTERNATE_LISTBOXGETSELECT       "choixliste" // 
#define LOCALIZED_ALTERNATE_LISTP                  "listep"
#define LOCALIZED_ALTERNATE_LIST_                  "liste?"
#define LOCALIZED_ALTERNATE_LN                     "ln" // 
#define LOCALIZED_ALTERNATE_LOAD                   "ramène"
#define LOCALIZED_ALTERNATE_LOCAL                  "locale"
#define LOCALIZED_ALTERNATE_LOG10                  "log10"
#define LOCALIZED_ALTERNATE_LOGOVERSION            "versionlogo" // 
#define LOCALIZED_ALTERNATE_LOWERCASE              "minuscule"
#define LOCALIZED_ALTERNATE_LPUT                   "metsdernier"
#define LOCALIZED_ALTERNATE_LR                     "ig" // 
#define LOCALIZED_ALTERNATE_LSHIFT                 "décaleg" // 
#define LOCALIZED_ALTERNATE_LT                     "ga"
#define LOCALIZED_ALTERNATE_MACHINE                "machine" // 
#define LOCALIZED_ALTERNATE_MACROP                 "macrop" // 
#define LOCALIZED_ALTERNATE_MACRO_                 "macro?" // 
#define LOCALIZED_ALTERNATE_MAKE                   "donne"
#define LOCALIZED_ALTERNATE_MCI                    "mci"
#define LOCALIZED_ALTERNATE_MEMBER                 "membre"
#define LOCALIZED_ALTERNATE_MEMBERP                "membrep"
#define LOCALIZED_ALTERNATE_MEMBER_                "membre?"
#define LOCALIZED_ALTERNATE_MESSAGEBOX             "message"
#define LOCALIZED_ALTERNATE_MIDICLOSE              "fermemidi" // 
#define LOCALIZED_ALTERNATE_MIDIMESSAGE            "messagemidi" // 
#define LOCALIZED_ALTERNATE_MIDIOPEN               "ouvremidi" // 
#define LOCALIZED_ALTERNATE_MINUS                  "moins"
#define LOCALIZED_ALTERNATE_MKDIR                  "fixerép" // 
#define LOCALIZED_ALTERNATE_MODULO                 "modulo"
#define LOCALIZED_ALTERNATE_MOUSEOFF               "désactivesouris" // 
#define LOCALIZED_ALTERNATE_MOUSEON                "activesouris" // 
#define LOCALIZED_ALTERNATE_MOUSEPOS               "possouris"
#define LOCALIZED_ALTERNATE_NAMEP                  "nomp"
#define LOCALIZED_ALTERNATE_NAME_                  "nom?"
#define LOCALIZED_ALTERNATE_NAMES                  "noms"
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           "finaccepte" // 
#define LOCALIZED_ALTERNATE_NETACCEPTON            "accepte" // 
#define LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE  "accepte.reçu" // 
#define LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE     "accepte.envoyé" // 
#define LOCALIZED_ALTERNATE_NETCONNECTOFF          "finconnecte" //
#define LOCALIZED_ALTERNATE_NETCONNECTON           "connecte" //
#define LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE "connecte.reçu" // 
#define LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE    "connecte.envoyé" // 
#define LOCALIZED_ALTERNATE_NETSHUTDOWN            "fermeréseau" // 
#define LOCALIZED_ALTERNATE_NETSTARTUP             "ouvreréseau" // 
#define LOCALIZED_ALTERNATE_NOBITMAPTURTLE         "finformetortue" // 
#define LOCALIZED_ALTERNATE_NODES                  "noeuds" // 
#define LOCALIZED_ALTERNATE_NODRIBBLE              "fintranscription" // 
#define LOCALIZED_ALTERNATE_NOSTATUS               "fermeétat" // 
#define LOCALIZED_ALTERNATE_NOT                    "non"
#define LOCALIZED_ALTERNATE_NOTEQUALP              "nonégalp" // 
#define LOCALIZED_ALTERNATE_NOTEQUAL_              "nonégal?" // 
#define LOCALIZED_ALTERNATE_NOYIELD                "finpartage" // 
#define LOCALIZED_ALTERNATE_NUMBERP                "nombrep" // 
#define LOCALIZED_ALTERNATE_NUMBER_                "nombre?" // 
#define LOCALIZED_ALTERNATE_OP                     "ret" // 
#define LOCALIZED_ALTERNATE_OPENAPPEND             "ajouteflux" // 
#define LOCALIZED_ALTERNATE_OPENREAD               "lisflux" // 
#define LOCALIZED_ALTERNATE_OPENUPDATE             "actualiseflux" // 
#define LOCALIZED_ALTERNATE_OPENWRITE              "écrisflux" // 
#define LOCALIZED_ALTERNATE_OR                     "ou" // 
#define LOCALIZED_ALTERNATE_OUTPORT                "écrisport" // 
#define LOCALIZED_ALTERNATE_OUTPORTB               "écrisportb" // 
#define LOCALIZED_ALTERNATE_OUTPUT                 "retourne"
#define LOCALIZED_ALTERNATE_PARSE                  "analyse" // 
#define LOCALIZED_ALTERNATE_PAUSE                  "pause" // 
#define LOCALIZED_ALTERNATE_PC                     "cc"
#define LOCALIZED_ALTERNATE_PD                     "bc"
#define LOCALIZED_ALTERNATE_PE                     "go"
#define LOCALIZED_ALTERNATE_PENCOLOR               "couleurcrayon"
#define LOCALIZED_ALTERNATE_PENDOWN                "baissecrayon"
#define LOCALIZED_ALTERNATE_PENDOWNP               "baissecrayonp"
#define LOCALIZED_ALTERNATE_PENDOWN_               "baissecrayon?"
#define LOCALIZED_ALTERNATE_PENERASE               "gomme"
#define LOCALIZED_ALTERNATE_PENMODE                "modecrayon"
#define LOCALIZED_ALTERNATE_PENPAINT               "dessine"
#define LOCALIZED_ALTERNATE_PENPATTERN             "motifcrayon" // 
#define LOCALIZED_ALTERNATE_PENREVERSE             "inversecrayon"
#define LOCALIZED_ALTERNATE_PENSIZE                "taillecrayon" // 
#define LOCALIZED_ALTERNATE_PENUP                  "lèvecrayon"
#define LOCALIZED_ALTERNATE_PERSPECTIVE            "perspective"
#define LOCALIZED_ALTERNATE_PITCH                  "cabrement" // 
#define LOCALIZED_ALTERNATE_PIXEL                  "point"
#define LOCALIZED_ALTERNATE_PLAYWAVE               "jouewave" // 
#define LOCALIZED_ALTERNATE_PLIST                  "lprop" // 
#define LOCALIZED_ALTERNATE_PLISTS                 "lprops" // 
#define LOCALIZED_ALTERNATE_PO                     "im" // 
#define LOCALIZED_ALTERNATE_POPDIR                 "répparent" // 
#define LOCALIZED_ALTERNATE_POLYSTART              "débutpoly" // 
#define LOCALIZED_ALTERNATE_POLYEND                "finpoly" // 
#define LOCALIZED_ALTERNATE_POLYVIEW               "affichepoly" // 
#define LOCALIZED_ALTERNATE_PORTCLOSE              "fermeport" // 
#define LOCALIZED_ALTERNATE_PORTFLUSH              "purgeport" // 
#define LOCALIZED_ALTERNATE_PORTMODE               "modeport" // 
#define LOCALIZED_ALTERNATE_PORTOPEN               "ouvreport" // 
#define LOCALIZED_ALTERNATE_PORTREADARRAY          "listableauport" // 
#define LOCALIZED_ALTERNATE_PORTREADCHAR           "liscarport" // 
#define LOCALIZED_ALTERNATE_PORTWRITEARRAY         "écristableauport" // 
#define LOCALIZED_ALTERNATE_PORTWRITECHAR          "écriscarport" // 
#define LOCALIZED_ALTERNATE_POS                    "pos" // 
#define LOCALIZED_ALTERNATE_POSXYZ                 "posxyz" // 
#define LOCALIZED_ALTERNATE_POT                    "imt" // 
#define LOCALIZED_ALTERNATE_POWER                  "puissance"
#define LOCALIZED_ALTERNATE_PPROP                  "dprop" // 
#define LOCALIZED_ALTERNATE_PPT                    "de"
#define LOCALIZED_ALTERNATE_PR                     "éc"
#define LOCALIZED_ALTERNATE_PRIMITIVEP             "primitivep"
#define LOCALIZED_ALTERNATE_PRIMITIVE_             "primitive?"
#define LOCALIZED_ALTERNATE_PRINT                  "écris"
#define LOCALIZED_ALTERNATE_PROCEDUREP             "procédurep" // 
#define LOCALIZED_ALTERNATE_PROCEDURE_             "procédure?" // 
#define LOCALIZED_ALTERNATE_PROPLISTP              "lpropp" // 
#define LOCALIZED_ALTERNATE_PROPLIST_              "lprop?" // 
#define LOCALIZED_ALTERNATE_PROCEDURES             "procédures" // 
#define LOCALIZED_ALTERNATE_PRODUCT                "produit"
#define LOCALIZED_ALTERNATE_PU                     "lc"
#define LOCALIZED_ALTERNATE_PX                     "ic"
#define LOCALIZED_ALTERNATE_QUESTIONBOX            "question" // 
#define LOCALIZED_ALTERNATE_QUOTIENT               "divise"
#define LOCALIZED_ALTERNATE_RADARCCOS              "radarccos"
#define LOCALIZED_ALTERNATE_RADARCSIN              "radarcsin"
#define LOCALIZED_ALTERNATE_RADARCTAN              "radarctan"
#define LOCALIZED_ALTERNATE_RADCOS                 "radcos"
#define LOCALIZED_ALTERNATE_RADIOBUTTONCREATE      "créeboutonradio" // 
#define LOCALIZED_ALTERNATE_RADIOBUTTONENABLE      "activeboutonradio" // 
#define LOCALIZED_ALTERNATE_RADIOBUTTONDELETE      "effaceboutonradio" // 
#define LOCALIZED_ALTERNATE_RADIOBUTTONGET         "boutonradio" // 
#define LOCALIZED_ALTERNATE_RADIOBUTTONSET         "fixeboutonradio" // 
#define LOCALIZED_ALTERNATE_RADSIN                 "radsin"
#define LOCALIZED_ALTERNATE_RADTAN                 "radtan"
#define LOCALIZED_ALTERNATE_RANDOM                 "hasard"
#define LOCALIZED_ALTERNATE_RAWASCII               "asciibrut" // 
#define LOCALIZED_ALTERNATE_RC                     "lcar"
#define LOCALIZED_ALTERNATE_RCS                    "lcars"
#define LOCALIZED_ALTERNATE_READCHAR               "liscar"
#define LOCALIZED_ALTERNATE_READCHARS              "liscars"
#define LOCALIZED_ALTERNATE_READER                 "fluxlecture"
#define LOCALIZED_ALTERNATE_READLIST               "lisliste"
#define LOCALIZED_ALTERNATE_READPOS                "poslecture"
#define LOCALIZED_ALTERNATE_READRAWLINE            "readrawline" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READWORD               "lismot"
#define LOCALIZED_ALTERNATE_REMAINDER              "reste"
#define LOCALIZED_ALTERNATE_REMPROP                "eprop" // 
#define LOCALIZED_ALTERNATE_REPCOUNT               "compteur"
#define LOCALIZED_ALTERNATE_REPEAT                 "répète"
#define LOCALIZED_ALTERNATE_RERANDOM               "rehasard" // 
#define LOCALIZED_ALTERNATE_RIGHT                  "droite"
#define LOCALIZED_ALTERNATE_RIGHTROLL              "inclinedroite" // 
#define LOCALIZED_ALTERNATE_RL                     "ll" // 
#define LOCALIZED_ALTERNATE_RMDIR                  "efrép" // 
#define LOCALIZED_ALTERNATE_ROLL                   "inclinaison" // 
#define LOCALIZED_ALTERNATE_ROUND                  "arrondis"
#define LOCALIZED_ALTERNATE_RR                     "id" // 
#define LOCALIZED_ALTERNATE_RT                     "dr"
#define LOCALIZED_ALTERNATE_RUN                    "exécute"
#define LOCALIZED_ALTERNATE_RUNPARSE               "exécuteanalyse" // 
#define LOCALIZED_ALTERNATE_RUNRESULT              "exécuterésultat" // 
#define LOCALIZED_ALTERNATE_RW                     "lm" // 
#define LOCALIZED_ALTERNATE_SAVE                   "sauve"
#define LOCALIZED_ALTERNATE_SCREENCOLOR            "couleurfond" // 
#define LOCALIZED_ALTERNATE_SCROLLBARCREATE        "créeascenseur" // 
#define LOCALIZED_ALTERNATE_SCROLLBARENABLE        "activeascenseur" // 
#define LOCALIZED_ALTERNATE_SCROLLBARDELETE        "effaceascenceur" // 
#define LOCALIZED_ALTERNATE_SCROLLBARGET           "ascenseur" // 
#define LOCALIZED_ALTERNATE_SCROLLBARSET           "fixeascenseur" // 
#define LOCALIZED_ALTERNATE_SCROLLX                "défilex" // 
#define LOCALIZED_ALTERNATE_SCROLLY                "défiley" // 
#define LOCALIZED_ALTERNATE_SCRUNCH                "échelle" // 
#define LOCALIZED_ALTERNATE_SE                     "ph"
#define LOCALIZED_ALTERNATE_SELECTBOX              "choix" // 
#define LOCALIZED_ALTERNATE_SENTENCE               "phrase"
#define LOCALIZED_ALTERNATE_SETACTIVEAREA          "fixezoneactive"
#define LOCALIZED_ALTERNATE_SETBITINDEX            "fixeindexbmp" // 
#define LOCALIZED_ALTERNATE_SETBITMODE             "fixemodebmp" // 
#define LOCALIZED_ALTERNATE_SETCLIP                "setclip" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETCURSOR              "fixecurseur" // 
#define LOCALIZED_ALTERNATE_SETCURSORNOWAIT        "fincurseurattente" // 
#define LOCALIZED_ALTERNATE_SETCURSORWAIT          "fixecurseurattente" // 
#define LOCALIZED_ALTERNATE_SETFC                  "fcr"
#define LOCALIZED_ALTERNATE_SETFLOODCOLOR          "fixecouleurremplissage"
#define LOCALIZED_ALTERNATE_SETFOCUS               "fixefocus" // 
#define LOCALIZED_ALTERNATE_SETH                   "fcap" // 
#define LOCALIZED_ALTERNATE_SETHEADING             "fixecap"
#define LOCALIZED_ALTERNATE_SETITEM                "fixeitem"
#define LOCALIZED_ALTERNATE_SETLABELFONT           "fixepolice"
#define LOCALIZED_ALTERNATE_SETLIGHT               "fixelumière" // 
#define LOCALIZED_ALTERNATE_SETMARGINS             "fixemarges" // 
#define LOCALIZED_ALTERNATE_SETPC                  "fcc"
#define LOCALIZED_ALTERNATE_SETPENCOLOR            "fixecouleurcrayon"
#define LOCALIZED_ALTERNATE_SETPENPATTERN          "fixemotifcrayon" // 
#define LOCALIZED_ALTERNATE_SETPENSIZE             "fixetaillecrayon"
#define LOCALIZED_ALTERNATE_SETPITCH               "fixecabrement" // 
#define LOCALIZED_ALTERNATE_SETPIXEL               "fixepoint" // 
#define LOCALIZED_ALTERNATE_SETPOS                 "fixeposition"
#define LOCALIZED_ALTERNATE_SETPOSXYZ              "fixepositionxyz"
#define LOCALIZED_ALTERNATE_SETREAD                "fixelecture" // 
#define LOCALIZED_ALTERNATE_SETREADPOS             "fixeposlecture" // 
#define LOCALIZED_ALTERNATE_SETROLL                "fixeinclinaison" // 
#define LOCALIZED_ALTERNATE_SETSC                  "fcf"
#define LOCALIZED_ALTERNATE_SETSCREENCOLOR         "fixecouleurfond"
#define LOCALIZED_ALTERNATE_SETSCRUNCH             "fixeéchelle" // 
#define LOCALIZED_ALTERNATE_SETTIMER               "fixechrono" // 
#define LOCALIZED_ALTERNATE_SETTURTLE              "fixetortue"
#define LOCALIZED_ALTERNATE_SETTURTLEMODE          "fixemodetortue" 
#define LOCALIZED_ALTERNATE_SETWRITE               "fixeécriture" // 
#define LOCALIZED_ALTERNATE_SETWRITEPOS            "fixeposécriture" // 
#define LOCALIZED_ALTERNATE_SETX                   "fixex"
#define LOCALIZED_ALTERNATE_SETXY                  "fixexy"
#define LOCALIZED_ALTERNATE_SETXYZ                 "fixexyz"
#define LOCALIZED_ALTERNATE_SETY                   "fixey"
#define LOCALIZED_ALTERNATE_SETZ                   "fixez"
#define LOCALIZED_ALTERNATE_SHELL                  "lance" // 
#define LOCALIZED_ALTERNATE_SHOW                   "montre"
#define LOCALIZED_ALTERNATE_SHOWNP                 "visiblep"
#define LOCALIZED_ALTERNATE_SHOWN_                 "visible?"
#define LOCALIZED_ALTERNATE_SHOWTURTLE             "montretortue"
#define LOCALIZED_ALTERNATE_SIN                    "sin"
#define LOCALIZED_ALTERNATE_SOUND                  "son" // 
#define LOCALIZED_ALTERNATE_SPLITSCREEN            "écranmixte" // 
#define LOCALIZED_ALTERNATE_SQRT                   "racine"
#define LOCALIZED_ALTERNATE_SS                     "écm" // 
#define LOCALIZED_ALTERNATE_ST                     "mt"
#define LOCALIZED_ALTERNATE_STANDOUT               "contour" // 
#define LOCALIZED_ALTERNATE_STATICCREATE           "créetexte" // 
#define LOCALIZED_ALTERNATE_STATICDELETE           "effacetexte" // 
#define LOCALIZED_ALTERNATE_STATICUPDATE           "actualisetexte" // 
#define LOCALIZED_ALTERNATE_STATUS                 "état" // 
#define LOCALIZED_ALTERNATE_STEP                   "pas" // 
#define LOCALIZED_ALTERNATE_STEPPED                "pas?" // 
#define LOCALIZED_ALTERNATE_STOP                   "arrête" // 
#define LOCALIZED_ALTERNATE_SUBSTRINGP             "appartientp" // 
#define LOCALIZED_ALTERNATE_SUBSTRING_             "appartient?" // 
#define LOCALIZED_ALTERNATE_SUM                    "somme"
#define LOCALIZED_ALTERNATE_TAG                    "balise" // 
#define LOCALIZED_ALTERNATE_TAN                    "tan"
#define LOCALIZED_ALTERNATE_TEST                   "teste" // 
#define LOCALIZED_ALTERNATE_TEXT                   "définition" // 
#define LOCALIZED_ALTERNATE_TEXTSCREEN             "écrantexte" // 
#define LOCALIZED_ALTERNATE_THING                  "chose"
#define LOCALIZED_ALTERNATE_THROW                  "renvoie"
#define LOCALIZED_ALTERNATE_TIME                   "temps"
#define LOCALIZED_ALTERNATE_TIMEMILLI              "tempsms" // 
#define LOCALIZED_ALTERNATE_TO                     "pour"
#define LOCALIZED_ALTERNATE_TONE                   "ton" // 
#define LOCALIZED_ALTERNATE_TOWARDS                "vers"
#define LOCALIZED_ALTERNATE_TOWARDSXYZ             "versxyz"
#define LOCALIZED_ALTERNATE_TRACE                  "suivi" // 
#define LOCALIZED_ALTERNATE_TRACED                 "suivi?" // 
#define LOCALIZED_ALTERNATE_TS                     "éct" // 
#define LOCALIZED_ALTERNATE_TURTLE                 "tortue"
#define LOCALIZED_ALTERNATE_TURTLEMODE             "modetortue"
#define LOCALIZED_ALTERNATE_TURTLES                "tortues"
#define LOCALIZED_ALTERNATE_TYPE                   "tape"
#define LOCALIZED_ALTERNATE_UNBURY                 "déterre" // 
#define LOCALIZED_ALTERNATE_UNSTEP                 "finpas" // 
#define LOCALIZED_ALTERNATE_UNTRACE                "finsuivi" // 
#define LOCALIZED_ALTERNATE_UP                     "cabre" // 
#define LOCALIZED_ALTERNATE_UPPERCASE              "majuscule"
#define LOCALIZED_ALTERNATE_UPPITCH                "cabre" // 
#define LOCALIZED_ALTERNATE_WAIT                   "attends"
#define LOCALIZED_ALTERNATE_WINDOW                 "fenêtre"
#define LOCALIZED_ALTERNATE_WINDOWCREATE           "créefenêtre" // 
#define LOCALIZED_ALTERNATE_WINDOWENABLE           "activefenêtre" // 
#define LOCALIZED_ALTERNATE_WINDOWDELETE           "effacefenêtre" // 
#define LOCALIZED_ALTERNATE_WINDOWFILEEDIT         "éditefichier" // 
#define LOCALIZED_ALTERNATE_WINDOWSET              "modefenêtre" // 
#define LOCALIZED_ALTERNATE_WINHELP                "aidewin" // 
#define LOCALIZED_ALTERNATE_WORD                   "mot"
#define LOCALIZED_ALTERNATE_WORDP                  "motp"
#define LOCALIZED_ALTERNATE_WORD_                  "mot?"
#define LOCALIZED_ALTERNATE_WRAP                   "enroule"
#define LOCALIZED_ALTERNATE_WRITEPOS               "posécriture" // 
#define LOCALIZED_ALTERNATE_WRITER                 "fluxécriture"
#define LOCALIZED_ALTERNATE_YESNOBOX               "choixouinon"
#define LOCALIZED_ALTERNATE_YIELD                  "partage" // 
#define LOCALIZED_ALTERNATE_ZOOM                   "zoom"

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      "Valider"
#define LOCALIZED_GENERAL_CANCELBUTTON  "Annuler"
#define LOCALIZED_GENERAL_APPLYBUTTON   "&Appliquer"

#define LOCALIZED_GENERAL_PRODUCTNAME   "FMSLogo"

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  "L'environnement de programmation FMSLogo"

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  "&Fichier"
#define LOCALIZED_FILE_NEW              "&Nouveau\t(supprime l'espace de travail)"
#define LOCALIZED_FILE_LOAD             "&Ramène...\t(fusionne avec l'espace de travail)"
#define LOCALIZED_FILE_OPEN             "&Ouvrir...\t(remplace l'espace de travail)"
#define LOCALIZED_FILE_SAVE             "&Enregistrer"
#define LOCALIZED_FILE_SAVEAS           "En&registrer sous..."
#define LOCALIZED_FILE_SETASSCREENSAVER "&Mettre comme Économiseur d'Écran"
#define LOCALIZED_FILE_EDIT             "E&diter..."
#define LOCALIZED_FILE_ERASE            "E&ffacer..."
#define LOCALIZED_FILE_EXIT             "&Quitter"

#define LOCALIZED_BITMAP               "&Dessin"
#define LOCALIZED_BITMAP_NEW           "&Nouveau"
#define LOCALIZED_BITMAP_LOAD          "&Ramène..."
#define LOCALIZED_BITMAP_SAVE          "&Enregistrer"
#define LOCALIZED_BITMAP_SAVEAS        "En&registrer sous..."
#define LOCALIZED_BITMAP_PRINT         "&Imprimer..."
#define LOCALIZED_BITMAP_PRINTERSETUP  "&Paramètres Impr...."
#define LOCALIZED_BITMAP_ACTIVEAREA    "&Zone active..."

#define LOCALIZED_SET                  "&Options"
#define LOCALIZED_SET_PENSIZE          "&Taille Crayon..."
#define LOCALIZED_SET_LABELFONT        "&Police de Caractères pour Étiquette..."
#define LOCALIZED_SET_COMMANDERFONT    "Police de Caractères du &Poste de Commande..."
#define LOCALIZED_SET_PENCOLOR         "&Couleur Crayon..."
#define LOCALIZED_SET_FLOODCOLOR       "Couleur &Remplissage..."
#define LOCALIZED_SET_SCREENCOLOR      "Couleur &Fond..."

#define LOCALIZED_ZOOM                 "&Zoom"
#define LOCALIZED_ZOOM_IN              "&Avant"
#define LOCALIZED_ZOOM_OUT             "&Arrière"
#define LOCALIZED_ZOOM_NORMAL          "&Normal"

#define LOCALIZED_HELP                 "&Aide"
#define LOCALIZED_HELP_INDEX           "&Manuel (en Anglais)"
#define LOCALIZED_HELP_TUTORIAL        "&Tutoriel (en Anglais)"
#define LOCALIZED_HELP_DEMO            "&Démo"
#define LOCALIZED_HELP_EXAMPLE         "&Exemples"
#define LOCALIZED_HELP_RELEASENOTES    "&Notes MàJ"
#define LOCALIZED_HELP_ABOUTFMSLOGO    "&A propos de " LOCALIZED_GENERAL_PRODUCTNAME "..."
#define LOCALIZED_HELP_MS              "A &propos de MS..."
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   "Français à Anglais"
#define LOCALIZED_HELP_ENGLISHTOLANG   "Anglais à Français"

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              "Zone active"
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       "Zone d'impression et de sauvegarde"
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        "Y-Haut"
#define LOCALIZED_SELECTACTIVEAREA_YLOW         "Y-Bas"
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        "X-Droite"
#define LOCALIZED_SELECTACTIVEAREA_XLOW         "X-Gauche"
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH "Points Tortue par pouce"
#define LOCALIZED_SELECTACTIVEAREA_RESET        "&RàZ"
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON

// The screensaver strings
#define LOCALIZED_SCREENSAVER_NAME              LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_SCREENSAVER_DESCRIPTION       "L'économiseur d'écran de FMSLogo"
#define LOCALIZED_SCREENSAVER_SETTINGS_TITLE    "Paramètres de l'économiseur d'écran de FMSLogo"
#define LOCALIZED_SCREENSAVER_LOCATE            "&Recherchez ..."
#define LOCALIZED_SCREENSAVER_FILE              "Logo &fichier:"
#define LOCALIZED_SCREENSAVER_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SCREENSAVER_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON

// The dialog box for selecting a Startup procedure
#define LOCALIZED_SELECTSTARTUP_CAPTION               "Sélectionnez une instruction de " LOCALIZED_ALTERNATE_STARTUP
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED "L'espace de travail n'a pas d'une liste d'instructions de " LOCALIZED_ALTERNATE_STARTUP " définie, donc rien\nne se passera lorsque l'économiseur d'écran est chargé.\nVeuillez sélectionner une procédure à exécuter lorsque le programme est chargé."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST   "La variable " LOCALIZED_ALTERNATE_STARTUP " n'est pas une liste, donc rien\nne se passera lorsque l'économiseur d'écran est chargé.\nVeuillez sélectionner une procédure à exécuter lorsque le programme est chargé."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY     "Votre espace de travail a une liste d'instructions vide " LOCALIZED_ALTERNATE_STARTUP " définie, donc rien\nne se passera lorsque l'économiseur d'écran est chargé.\nVeuillez sélectionner une procédure à exécuter lorsque le programme est chargé."
#define LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED   "Aucuns procédures ne sont définis"

// The warning dialog box when the user saves an empty workspace
#define LOCALIZED_EMPTYWORKSPACE_TITLE                LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_EMPTYWORKSPACE_MESSAGE              "Il n'y a aucune procédures, variables ou des listes de propriété définies,\ndonc l'espace de travail sera enregistré comme un fichier vide.\n\nVous voulez enregistrer l'espace de travail de toute façon?"

//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     "Copier"
#define LOCALIZED_POPUP_CUT                      "Couper"
#define LOCALIZED_POPUP_PASTE                    "Coller"
#define LOCALIZED_POPUP_DELETE                   "Effacer"
#define LOCALIZED_POPUP_UNDO                     "Annuler"
#define LOCALIZED_POPUP_REDO                     "Rétablir"
#define LOCALIZED_POPUP_SELECTALL                "Sélectionner tout"
#define LOCALIZED_POPUP_HELP                     "Recherche thématique"
#define LOCALIZED_POPUP_REMOVELINES              "Remove Selected Lines" // NOT_YET_LOCALIZED

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   "Editeur"

#define LOCALIZED_EDITOR_FILE                    "&Espace de travail"
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        "&Interpréter et Quitter\tCtrl+D"
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    "E&nregistrer"
#define LOCALIZED_EDITOR_FILE_PRINT              "&Imprimer..."
#define LOCALIZED_EDITOR_FILE_EXIT               "&Quitter"

#define LOCALIZED_EDITOR_EDIT                    "&Edition"
#define LOCALIZED_EDITOR_EDIT_UNDO               "&Annuler frappe\tCtrl+Z"
#define LOCALIZED_EDITOR_EDIT_REDO               "&Rétablir\tCtrl+Y"
#define LOCALIZED_EDITOR_EDIT_CUT                "&Couper\tCtrl+X"
#define LOCALIZED_EDITOR_EDIT_COPY               "C&opier\tCtrl+C"
#define LOCALIZED_EDITOR_EDIT_PASTE              "&Coller\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_DELETE             "&Effacer\tDel"
#define LOCALIZED_EDITOR_EDIT_CLEARALL           "E&ffacer Tout\tCtrl+Del"
#define LOCALIZED_EDITOR_EDIT_SELECTALL          "&Sélectionner tout\tCtrl+A"

#define LOCALIZED_EDITOR_SEARCH                  "&Outils"
#define LOCALIZED_EDITOR_SEARCH_FIND             "Re&chercher...\tCtrl+F"
#define LOCALIZED_EDITOR_SEARCH_REPLACE          "&Remplacer...\tCtrl+H"
#define LOCALIZED_EDITOR_SEARCH_NEXT             "&Suivant\tF3"

#define LOCALIZED_EDITOR_SET                     "&Options"
#define LOCALIZED_EDITOR_SET_FONT                "&Police..."

#define LOCALIZED_EDITOR_TEST                    "Test" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      "&Run Selection\tCtrl+R" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITOR_HELP                    "&Aide"
#define LOCALIZED_EDITOR_HELP_INDEX              "&Index" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_HELP_EDITOR             "&Editeur"
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        "&Recherche thématique\tF1"


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES // NOT_YET_LOCALIZED
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    "&Enregistrer et quitter" // 
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       "&Ne pas enregistrer" // 
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       "Il y a des changements non enregistrés dans l'espace de travail. Si vous quittez sans enregistrer les changements seront perdus.  " // 
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       "Voulez-vous enregistrer les changements avant de quitter?"  // 


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     "Poste de commande"
#define LOCALIZED_COMMANDER_HALT                "Arrêt"
#define LOCALIZED_COMMANDER_TRACE               "Suivi"
#define LOCALIZED_COMMANDER_NOTRACE             "Fin Suivi"
#define LOCALIZED_COMMANDER_PAUSE               "Pause"
#define LOCALIZED_COMMANDER_STATUS              "Etat"
#define LOCALIZED_COMMANDER_NOSTATUS            "Fin Etat"
#define LOCALIZED_COMMANDER_STEP                "Pas"
#define LOCALIZED_COMMANDER_UNSTEP              "Fin Pas"
#define LOCALIZED_COMMANDER_RESET               "RàZ"
#define LOCALIZED_COMMANDER_EXECUTE             "Exécute"
#define LOCALIZED_COMMANDER_EDALL               "Edite tout" // 

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        "Etat"
#define LOCALIZED_STATUS_PEN                    "Crayon"
#define LOCALIZED_STATUS_CONTACT                "Position:"
#define LOCALIZED_STATUS_WIDTH                  "Largeur:"
#define LOCALIZED_STATUS_STYLE                  "Style:"
#define LOCALIZED_STATUS_ORIENTATION            "Orientation"
#define LOCALIZED_STATUS_PITCH                  "Cabr:"
#define LOCALIZED_STATUS_HEADING                "Cap:"
#define LOCALIZED_STATUS_ROLL                   "Incl:"
#define LOCALIZED_STATUS_TURTLE                 "Tortue"
#define LOCALIZED_STATUS_POSITION               "Position(XYZ):"
#define LOCALIZED_STATUS_WHICH                  "Laquelle:"
#define LOCALIZED_STATUS_VISIBILITY             "Visibilité:"
#define LOCALIZED_STATUS_COLOR                  "Couleurs"
#define LOCALIZED_STATUS_PENCOLOR               "Crayon(RVB):"
#define LOCALIZED_STATUS_FLOODCOLOR             "Remplis(RVB):"
#define LOCALIZED_STATUS_SCREENCOLOR            "Ecran(RVB):"
#define LOCALIZED_STATUS_KERNEL                 "Noyau"
#define LOCALIZED_STATUS_CALLS                  "Appels:"
#define LOCALIZED_STATUS_PEAKMEMORY             "Mémoire:"

#define LOCALIZED_STATUS_PENREVERSE     "Inverse"
#define LOCALIZED_STATUS_PENNORMAL      "Normal"
#define LOCALIZED_STATUS_PENERASE       "Efface"
#define LOCALIZED_STATUS_PENUP          "Haut"
#define LOCALIZED_STATUS_PENDOWN        "Bas"
#define LOCALIZED_STATUS_PENSHOWN       "Visible"
#define LOCALIZED_STATUS_PENHIDDEN      "Caché"
#define LOCALIZED_STATUS_POLYGONS       "Polygones" // 
#define LOCALIZED_STATUS_VECTORS        "Vecteurs"
#define LOCALIZED_STATUS_NODES          "Noeuds"
#define LOCALIZED_STATUS_NOT_APPLICABLE "N/A" // NOT_YET_LOCALIZED

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           "&Toutes"
#define LOCALIZED_ERASEPROCEDURE                "Procédure à effacer"
#define LOCALIZED_EDITPROCEDURE                 "Procédure à éditer"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     "Couleur"
#define LOCALIZED_SETCOLOR_PENCOLOR            "Couleur Crayon"
#define LOCALIZED_SETCOLOR_FLOODCOLOR          "Couleur de Remplissage"
#define LOCALIZED_SETCOLOR_SCREENCOLOR         "Couleur Fond"
#define LOCALIZED_SETCOLOR_RED                 "Rouge"
#define LOCALIZED_SETCOLOR_GREEN               "Vert"
#define LOCALIZED_SETCOLOR_BLUE                "Bleu"
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON // NOT_YET_LOCALIZED

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   "Taille Crayon"
#define LOCALIZED_SETPENSIZE_SIZE              "Dimension"
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON // NOT_YET_LOCALIZED


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     "A propos de " LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_ABOUTFMS_VERSION             "Version" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_GUI                 "GUI by George Mills\nSoftronics, Inc.\nhttp://www.softronix.com/" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_CORE                "Core by Brian Harvey\nUniversity of California Berkeley" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_INSTALLER           "Installer based on Nullsoft Scriptable Install System\nhttp://nsis.sourceforge.net/" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_ADVENTURE           "The Great Logo Adventure (ISBN 0-9651934-6-2)\nWritten and donated by Jim Muller\nAvailable at http://www.softronix.com/" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       "Special thanks to Yehuda Katz and Erich Neuwirth" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME " is free software\nSee GNU Public License" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_NEWSGROUP           "Internet News Group: comp.lang.logo\nVisit the Logo-Forum at\nhttp://groups.yahoo.com/group/LogoForum/" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     "Adaptation française partielle de Bertrand Carette" // 
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      "A propos de FMS"
#define LOCALIZED_ABOUTMS_FMS                  "FMS stands for Fight Multiple Sclerosis." // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     "Please consider donating to the\nNational Multiple Sclerosis Society.\nhttp://www.nmss.org\n1-800-FIGHT-MS" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTMS_OK                   LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED


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

#define LOCALIZED_CHANGESINEDITORMAYBELOST  "Des modifications dans l'éditeur peuvent être perdues.\n\nVoulez-vous vraiment quitter " LOCALIZED_GENERAL_PRODUCTNAME "?" // 
#define LOCALIZED_EDITSESSIONISRUNNING      "L'éditeur est déjà ouvert" // 

#define LOCALIZED_COULDNOTWRITEBMP            "Impossible d'écrire .bmp" //
#define LOCALIZED_COULDNOTOPENBMP             "Impossible d'ouvrir .bmp" // 
#define LOCALIZED_COULDNOTCREATEBMP           "Ne peut pas créer un bitmap Windows 3.0" // 
#define LOCALIZED_NOTVALIDBMP                 "Ce n'est pas un bitmap Windows 3.0 valide" // 

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         "Non enregistré"
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     "Nouveau supprime toutes les définitions.\n\nContinuer avec nouveau?"
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE "Le fichier sera fusionné dans l'espace de travail\net peut écraser des modifications non enregistréesand may overwrite your unsaved changes.\n\nContinuer le chargement?" // 
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    "Le chargement du fichier va écraser l'espace de travail.\n\nContinuer le chargement?"

#define LOCALIZED_EDITORISOPEN                  "Savez-vous que l'éditeur est ouvert?\n\nDes changements dans cette session ne sont pas enregistrés." // 

#define LOCALIZED_ERROR_CANTREADFILE            "Impossible de lire le fichier  \"%s\" sur le disque" // 
#define LOCALIZED_ERROR_CANTWRITEFILE           "Impossible d'écrire le fichier \"%s\" tsur le disque" // 

#define LOCALIZED_SAVETOWORKSPACE                "Sauve l'espace de travail"
#define LOCALIZED_CONTENTSCHANGED                "Changement du contenu"
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE "Le contenu a été modifié. Voulez-vous interpréter l'espace de travail?"



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  "Le curseur est placé après la dernière bonne définition.\nRegarder la fenêtre de commande pour le message d'erreur."
#define LOCALIZED_RETURNTOEDIT                  "Retour à l'éditeur?"

#define LOCALIZED_EDITFAILEDTOLOAD              "L'éditeur n'a pas réussi le chargement"

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
#define LOCALIZED_FILEFILTER_ALLFILES "Tous les fichiers (*.*)|*.*"
#define LOCALIZED_FILEFILTER_LOGO     "Fichiers Logo (*.lgo)|*.lgo|" LOCALIZED_FILEFILTER_ALLFILES
#define LOCALIZED_FILEFILTER_IMAGE    "Fichiers Bitmap (*.bmp)|*.bmp|Fichiers GIF (*.gif)|*.gif|" LOCALIZED_FILEFILTER_ALLFILES



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             " arrête\n"
#define LOCALIZED_TRACING_OUTPUTS           " sort %s\n"
#define LOCALIZED_TRACING_MAKE              "Donne %s %s"  // 
#define LOCALIZED_TRACING_PPROP             "Dprop %s %s %s" // 
#define LOCALIZED_TRACING_LOCATION          " dans %s\n%s"

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  "Simple pas" // 

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  "%s définie\n"


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    "erase" //
#define LOCALIZED_PENMODE_REVERSE  "reverse" // 
#define LOCALIZED_PENMODE_PAINT    "paint" // 

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          "Logo: erreur interne fatale"
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       "Logo: Plus assez de mémoire (fatale)"
#define LOCALIZED_ERROR_OUTOFMEMORY            "Plus assez de mémoire"
#define LOCALIZED_ERROR_STACKOVERFLOW          "Débordement de pile"
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      "Tortue en dehors des limites"
#define LOCALIZED_ERROR_BADGRAPHINIT           "Impossible d'initialiser le graphisme"
#define LOCALIZED_ERROR_BADDATA                "%p n'aime pas l'argument %s"
#define LOCALIZED_ERROR_DIDNTOUTPUT            "%p ne donne pas de valeur à %p"
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        "Pas assez d'arguments pour %p"
#define LOCALIZED_ERROR_TOOMUCH                "Trop de choses entre les ( )"
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    "Vous ne dites pas ce qu'il faut faire de %s"
#define LOCALIZED_ERROR_PARENMISMATCH          "Trop de '('"
#define LOCALIZED_ERROR_NOVALUE                "%s n'a pas de valeur"
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        "')' inattendue"
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      "']' inattendue"
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        "'}' inattendue"
#define LOCALIZED_ERROR_DONTKNOWHOWTO          "Je ne connais pas la procédure %p"
#define LOCALIZED_ERROR_NOCATCHTAG             "Pas de ATTRAPE (CATCH) correspondant à la balise (tag) %p"
#define LOCALIZED_ERROR_ALREADYDEFINED         "%p est déjà définie"
#define LOCALIZED_ERROR_STOPPING               "Arrêt..."
#define LOCALIZED_ERROR_ALREADYDRIBBLING       "Déjà en train d'appliquer TRANSCRIPTION (DRIBBLE)"
#define LOCALIZED_ERROR_FILESYSTEM                   "Erreur système de fichiers: %p"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          "Impossible d'ouvrir fichier"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         "Impossible d'ouvrir fichier: %t"
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       "Fichier déjà ouvert"
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           "Fichier non ouvert"
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  "Impossible de créer un fichier éditeur" // 
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   "Impossible de lancer l'éditeur"  // 
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    "Impossible de lire un fichier éditeur"  // 
#define LOCALIZED_ERROR_IFWARNING              "Vous voulez sans doute dire SISINON (IFELSE) et non SI (IF)"
#define LOCALIZED_ERROR_SHADOWWARNING          "%p masquée dans un appel de procédure"
#define LOCALIZED_ERROR_USER                   "RENVOIE (THROW) \"Erreur" // 
#define LOCALIZED_ERROR_ISPRIMITIVE            "%p est une primitive"
#define LOCALIZED_ERROR_TONOTINSIDE            "Impossible d'utiliser POUR (TO) dans une procédure"
#define LOCALIZED_ERROR_ATTOPLEVEL             "Ne peux utiliser %p que dans une procédure" // 
#define LOCALIZED_ERROR_ATTOPLEVEL2            "Ne peux utiliser RETOURNE (OUTPUT) ou ARRÊTE (STOP) que dans une procédure"
#define LOCALIZED_ERROR_NOTEST                 "%p sans TESTE (TEST)"
#define LOCALIZED_ERROR_BADMACROOUTPUT         "La macro retourne %s au lieu d'une liste"
#define LOCALIZED_ERROR_DEEPEND                "FIN (END) dans une instruction multi-ligne"
#define LOCALIZED_ERROR_DEEPENDIN              "FIN (END) dans une instruction multi-ligne dans %p"
#define LOCALIZED_ERROR_UNKNOWN                "Unknown error condition - internal error." // NOT_YET_LOCALIZED
#define LOCALIZED_PAUSING                      "Pause..."


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION "Invalid state for instruction: %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MODE_ON_SPRITE             "cannot set the mode of a turtle with a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        "cannot make a special turtle use a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            "cannot use the clipboard as a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_SPECIALFORM                "%p doesn't like %p as input because it has a special form" // NOT_YET_LOCALIZED

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      "Erreur"
#define LOCALIZED_ERROR_BADINPUT             "Entrée invalide" // 
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    "Input is not paired" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_CANTOPENPORT         "Impossible d'ouvrir le port" // 
#define LOCALIZED_ERROR_CANTCLOSEPORT        "Impossible de fermer le port" // 
#define LOCALIZED_ERROR_CANTFLUSHPORT        "Impossible de purger le port" // 
#define LOCALIZED_ERROR_CANTDCBONPORT        "Could not build dcb on port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTSETPORT          "Impossible de paramétrer le port" // 
#define LOCALIZED_ERROR_PORTALREADYOPEN      "Le port est déjà ouvert" // 
#define LOCALIZED_ERROR_PORTNOTOPEN          "Le port n'est pas ouvert" // 

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   "%s existe déjà"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    "%s n'existe pas"

#define LOCALIZED_ERROR_DLLNOTLOADED          "DLL non chargée" // 
#define LOCALIZED_ERROR_DLLLOADFAILED         "Echec chargement DLL" // 
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    "Type de donnée en entrée invalide" //
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  "Type de donnée en sortie invalide" // 
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   "Fonction introuvable" // 
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  "Not all Type/Data inputs are paired" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_NETWORK               "Erreur réseau" // 
#define LOCALIZED_ERROR_NETWORKRECEIVE        "Erreur réseau en réception" // 
#define LOCALIZED_ERROR_NETWORKSEND           "Erreur réseau en émission" // 
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       "Erreur inattendue, coupure du réseau" // 
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     "Non démarré" // 
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED "Déjà démarré" // 
#define LOCALIZED_ERROR_NETWORKALREADYON      "Déjà connecté" // 
#define LOCALIZED_ERROR_NETWORKALREADYOFF     "Déjà déconnecté" // 

// The rest of the network errors shouldn't really be seen -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         "Nom trop long" // 
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      "Non initialisé" // 
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      "Le système n'est pas prêt" // 
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED "Cette version n'est pas supportée" // 
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   "Envoi impossible après coupure socket" // 
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         "Appel système interrompu" // 
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    "Authoritative Answer: Host not found" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH "Non-Authoritative: Host not found. See NETSTARTUP" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      "Erreur irrécupérable" // 
#define LOCALIZED_ERROR_NETWORKNODATA              "Pas d'enregistrement disponible" // 
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       "Mauvais numéro de fichier" //
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          "Operation would block" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       "Opération en cours de démarrage" // 
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   "Opération déjà en cours" // 
#define LOCALIZED_ERROR_NETWORKBADADDRESS          "Mauvaise addresse" // 
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     "Adresse de destination demandée" // 
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      "Message trop long" // 
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      "Famille de protocole non supportée" // 
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         "Répertoire non vide" // 
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     "Limite de l'application atteinte" // 
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           "Quota disque dépassé" // 
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        "Trop de fichiers ouverts" // 
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        "Accès refusé"
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          "Socket operation on non-socket" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    "Impossible d'assigner l'adresse demandée" // 
#define LOCALIZED_ERROR_NETWORKADDRINUSE           "Adresse déjà utilisée" // 
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      "Address family not supported by protocol family" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            "Temps de connection dépassé" // 
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    "Tye de socket non supporté" // 
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   "Protocole non supporté" // 
#define LOCALIZED_ERROR_NETWORKNOBUFFER            "Tampon plein" // 
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    "Socket déjà connecté" // 
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        "Socket non connecté" // 
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         "Option de protocole non valide" // 
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     "Connection reset by peer" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     "Le programme a causé l'abandon de la connection" // 
#define LOCALIZED_ERROR_NETWORKISDOWN              "Le réseau est coupé" // 
#define LOCALIZED_ERROR_NETWORKRESET               "Le réseau a été réinitialisé" // 
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   "Connection refusée" // 
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          "Host is down" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   "Host is unreachable" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        "Protocol is wrong type for socket" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   "Operation not supported on socket" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         "No path to remote host was found" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         "Trop de références" // 

#define LOCALIZED_ERROR_POLYSTART               "Erreur DébutPoly" // 
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED "Il y a déjà un Polygone en cours" // 

#define LOCALIZED_ERROR_POLYEND                 "Erreur FinPoly" // 
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       "Aucun Polygone n'est démarré" // 
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     "Il faut au moins 3 vecteurs pour définir un polygone"  // 

#define LOCALIZED_ERROR_SOUND                 "Erreur Son" // 

#define LOCALIZED_ERROR_MIDI                  "Erreur Midi"
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     "Périphérique MIDI non valide" // 
#define LOCALIZED_ERROR_MIDIALREADYOPEN       "Déja ouvert"
#define LOCALIZED_ERROR_MIDINOTOPEN           "Déja fermé"

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      "Le presse-papier est vide" // 

#define LOCALIZED_ERROR_MCI                   "Erreur MCI"

#define LOCALIZED_ERROR_TIMERNOTFOUND         "Chrono non trouvé"

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       "L'aide en ligne n'est pas disponible car hhctrl.ocx ne peut être chargé."  // 

#define LOCALIZED_ERROR_BADCOMMANDLINE        "Ligne de commande non valide"  // 

#define LOCALIZED_ERROR_TMPNOTDEFINED         "La variable d'environnement TMP est non définie ou non valide.\n" LOCALIZED_GENERAL_PRODUCTNAME " va essayer d'utiliser C:\\ pour stocker les fichiers temporaires" // 

#define LOCALIZED_ERROR_GIFSAVEFAILED         "Problème pour créer un GIF, vérifier la mémoire et l'espace disque" // 
#define LOCALIZED_ERROR_GIFREADFAILED         "Problem Reading GIF, check memory and diskspace" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  "Index BitMap hors limite" // 
#define LOCALIZED_ERROR_BITMAPCUTFAILED        "Echec Coupe, probablement pas assez de mémoire" // 

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    "Rien à coller"  // 
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  "BitMap at Index must be initialized with a bitmap"  // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      "La TortueT %d n'a pas d'image, arrêt" // 

#define LOCALIZED_ERROR_FONTNOTFOUND            "Sorry, no font named %s was found.  Choose one of the following:\n" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_PRINTERCANTSCALE        "Print driver does not support this function"  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTDRAWIMAGE           "Cannot draw image" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        "Cannot extract image" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_SUBCODE                 "Sub Code" // NOT_YET_LOCALIZED

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         "Entrée:"
#define LOCALIZED_PROMPT_TO     "Mode POUR (TO) - Annuler pour FIN (END)"
#define LOCALIZED_PROMPT_LIST   "Mode List Annuler pour HALT"
#define LOCALIZED_PROMPT_PAUSE  "Mode Pause - Annuler pour CONTINUE"
#define LOCALIZED_PROMPT_INPUT  "Mode Entrée - Annuler pour HALT"

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      "Changement vers \"%s\""
#define LOCALIZED_FILE_CHDIRFAILED         "Impossible changement vers le répertoire \"%s\""
#define LOCALIZED_FILE_POPPEDTO            "Désempiler dans \"%s\""
#define LOCALIZED_FILE_MKDIRSUCCEEDED      "Le répertoire \"%s\" est créé"
#define LOCALIZED_FILE_MKDIRFAILED         "Impossible de créer le répertoire \"%s\""
#define LOCALIZED_FILE_RMDIRSUCCEEDED      "Le répertoire \"%s\" est supprimé"
#define LOCALIZED_FILE_RMDIRFAILED         "Imposible de supprimer le répertoire \"%s\""
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  "Le répertoire n'existe pas"
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY "Le répertoire est-il vide?"


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       "Image Logo" // 

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    "Zone Active"
#define LOCALIZED_INFORMATION   "Information" // 
#define LOCALIZED_WARNING       "Attention" // 
#define LOCALIZED_UNTITLED      "Sans titre" // 
#define LOCALIZED_UNKNOWN       "Inconnu" // 

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       "nothing" // NOT_YET_LOCALIZED

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     "Rechercher"
#define LOCALIZED_EDITOR_TITLE_REPLACE  "Remplacer"

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING "'%s' non trouvé"


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
#define LOCALIZED_COLOR_ALICEBLUE             "Bleu Alice"
#define LOCALIZED_COLOR_ANTIQUEWHITE          "Blanc antique"
#define LOCALIZED_COLOR_AQUA                  "Vert d'eau"
#define LOCALIZED_COLOR_AQUAMARINE            "Bleu vert"
#define LOCALIZED_COLOR_AZURE                 "Azur"
#define LOCALIZED_COLOR_BEIGE                 "Beige"
#define LOCALIZED_COLOR_BISQUE                "Bisque"
#define LOCALIZED_COLOR_BLACK                 "Noir"
#define LOCALIZED_COLOR_BLANCHEDALMOND        "Amande blanchie"
#define LOCALIZED_COLOR_BLUE                  "Bleu"
#define LOCALIZED_COLOR_BLUEVIOLET            "Bleu violet"
#define LOCALIZED_COLOR_BROWN                 "Brun"
#define LOCALIZED_COLOR_BURLYWOOD             "Bois brut"
#define LOCALIZED_COLOR_CADETBLUE             "Blue cadet"
#define LOCALIZED_COLOR_CHARTREUSE            "Chartreuse"
#define LOCALIZED_COLOR_CHOCOLATE             "Chocolat"
#define LOCALIZED_COLOR_CORAL                 "Corail"
#define LOCALIZED_COLOR_CORNFLOWERBLUE        "Bleu barbeau"
#define LOCALIZED_COLOR_CORNSILK              "Barbe de maïs"
#define LOCALIZED_COLOR_CRIMSON               "Cramoisi"
#define LOCALIZED_COLOR_CYAN                  "Cyan"
#define LOCALIZED_COLOR_DARKBLUE              "Bleu foncé"
#define LOCALIZED_COLOR_DARKCYAN              "Cyan foncé"
#define LOCALIZED_COLOR_DARKGOLDENROD         "Verge d'or foncé"
#define LOCALIZED_COLOR_DARKGRAY              "Gris foncé"
#define LOCALIZED_COLOR_DARKGREEN             "Vert foncé"
#define LOCALIZED_COLOR_DARKGREY              "Gris foncé"
#define LOCALIZED_COLOR_DARKKHAKI             "Kaki foncé"
#define LOCALIZED_COLOR_DARKMAGENTA           "Magenta foncé"
#define LOCALIZED_COLOR_DARKOLIVEGREEN        "Olive foncé"
#define LOCALIZED_COLOR_DARKORANGE            "Orange foncé"
#define LOCALIZED_COLOR_DARKORCHID            "Orchidée foncé"
#define LOCALIZED_COLOR_DARKRED               "Rouge foncé"
#define LOCALIZED_COLOR_DARKSALMON            "Saumon foncé"
#define LOCALIZED_COLOR_DARKSEAGREEN          "Vert marin foncé"
#define LOCALIZED_COLOR_DARKSLATEBLUE         "Bleu ardoise foncé"
#define LOCALIZED_COLOR_DARKSLATEGRAY         "Gris ardoise foncé"
#define LOCALIZED_COLOR_DARKSLATEGREY         "Gris ardoise foncé"
#define LOCALIZED_COLOR_DARKTURQUOISE         "Turquoise foncé"
#define LOCALIZED_COLOR_DARKVIOLET            "Violet foncé"
#define LOCALIZED_COLOR_DEEPPINK              "Rose soutenu"
#define LOCALIZED_COLOR_DEEPSKYBLUE           "Bleu ciel intense"
#define LOCALIZED_COLOR_DIMGRAY               "Gris pâle"
#define LOCALIZED_COLOR_DIMGREY               "Gris pâle"
#define LOCALIZED_COLOR_DODGERBLUE            "Bleuté"
#define LOCALIZED_COLOR_FIREBRICK             "Brique feu"
#define LOCALIZED_COLOR_FLORALWHITE           "Blanc floral"
#define LOCALIZED_COLOR_FORESTGREEN           "Vert forêt"
#define LOCALIZED_COLOR_FUCHSIA               "Fuchsia"
#define LOCALIZED_COLOR_GAINSBORO             "Gainsborough"
#define LOCALIZED_COLOR_GHOSTWHITE            "Blanc fantôme"
#define LOCALIZED_COLOR_GOLD                  "Or"
#define LOCALIZED_COLOR_GOLDENROD             "Verge d'or"
#define LOCALIZED_COLOR_GRAY                  "Gris"
#define LOCALIZED_COLOR_GREEN                 "Vert"
#define LOCALIZED_COLOR_GREENYELLOW           "Vert jaune"
#define LOCALIZED_COLOR_GREY                  "Gris"
#define LOCALIZED_COLOR_HONEYDEW              "Miellé"
#define LOCALIZED_COLOR_HOTPINK               "Cuisse de nymphe émue"
#define LOCALIZED_COLOR_INDIANRED             "Rouge indien"
#define LOCALIZED_COLOR_INDIGO                "Indigo"
#define LOCALIZED_COLOR_IVORY                 "Ivoire"
#define LOCALIZED_COLOR_KHAKI                 "Kaki"
#define LOCALIZED_COLOR_LAVENDER              "Lavande"
#define LOCALIZED_COLOR_LAVENDERBLUSH         "Bleu lavande"
#define LOCALIZED_COLOR_LAWNGREEN             "Vert herbe"
#define LOCALIZED_COLOR_LEMONCHIFFON          "Mousseline citron"
#define LOCALIZED_COLOR_LIGHTBLUE             "Bleu clair"
#define LOCALIZED_COLOR_LIGHTCORAL            "Corail clair"
#define LOCALIZED_COLOR_LIGHTCYAN             "Cyan clair"
#define LOCALIZED_COLOR_LIGHTGOLDENRODYELLOW  "Verge d'or jaunâtre"
#define LOCALIZED_COLOR_LIGHTGRAY             "Gris clair"
#define LOCALIZED_COLOR_LIGHTGREEN            "Vert clair"
#define LOCALIZED_COLOR_LIGHTGREY             "Gris clair"
#define LOCALIZED_COLOR_LIGHTPINK             "Rose clair"
#define LOCALIZED_COLOR_LIGHTSALMON           "Saumon clair"
#define LOCALIZED_COLOR_LIGHTSEAGREEN         "Vert marin clair"
#define LOCALIZED_COLOR_LIGHTSKYBLUE          "Bleu ciel clair"
#define LOCALIZED_COLOR_LIGHTSLATEGRAY        "Gris ardoise clair"
#define LOCALIZED_COLOR_LIGHTSLATEGREY        "Gris ardoise clair"
#define LOCALIZED_COLOR_LIGHTSTEELBLUE        "Bleu acier clair"
#define LOCALIZED_COLOR_LIGHTYELLOW           "Jaune clair"
#define LOCALIZED_COLOR_LIME                  "Tilleul"
#define LOCALIZED_COLOR_LIMEGREEN             "Citrone vert"
#define LOCALIZED_COLOR_LINEN                 "Linon"
#define LOCALIZED_COLOR_MAGENTA               "Magenta"
#define LOCALIZED_COLOR_MAROON                "Marron"
#define LOCALIZED_COLOR_MEDIUMAQUAMARINE      "Bleu vert moyen"
#define LOCALIZED_COLOR_MEDIUMBLUE            "Bleu moyen"
#define LOCALIZED_COLOR_MEDIUMORCHID          "Orchidée moyen"
#define LOCALIZED_COLOR_MEDIUMPURPLE          "Pourpre moyen"
#define LOCALIZED_COLOR_MEDIUMSEAGREEN        "Vert marin moyen"
#define LOCALIZED_COLOR_MEDIUMSLATEBLUE       "Bleu ardoise moyen"
#define LOCALIZED_COLOR_MEDIUMSPRINGGREEN     "Vert printemps moyen"
#define LOCALIZED_COLOR_MEDIUMTURQUOISE       "Turquoise moyen"
#define LOCALIZED_COLOR_MEDIUMVIOLETRED       "Rouge violet moyen"
#define LOCALIZED_COLOR_MIDNIGHTBLUE          "Bleu nuit moyen"
#define LOCALIZED_COLOR_MINTCREAM             "Creme de menthe"
#define LOCALIZED_COLOR_MISTYROSE             "Rose fané"
#define LOCALIZED_COLOR_MOCCASIN              "Moccasin"
#define LOCALIZED_COLOR_NAVAJOWHITE           "Blanc navajo"
#define LOCALIZED_COLOR_NAVY                  "Marine"
#define LOCALIZED_COLOR_OLDLACE               "Vieille dentelle"
#define LOCALIZED_COLOR_OLIVE                 "Olive"
#define LOCALIZED_COLOR_OLIVEDRAB             "Olive terne"
#define LOCALIZED_COLOR_ORANGE                "Orange"
#define LOCALIZED_COLOR_ORANGERED             "Rouge orangé"
#define LOCALIZED_COLOR_ORCHID                "Orchidée"
#define LOCALIZED_COLOR_PALEGOLDENROD         "Verge d'or pâle"
#define LOCALIZED_COLOR_PALEGREEN             "Vert pâle"
#define LOCALIZED_COLOR_PALETURQUOISE         "Turquoise pâle"
#define LOCALIZED_COLOR_PALEVIOLETRED         "Rouge violet pâle"
#define LOCALIZED_COLOR_PAPAYAWHIP            "Mousse a la papaye"
#define LOCALIZED_COLOR_PEACHPUFF             "Fleur de pêcher"
#define LOCALIZED_COLOR_PERU                  "Pérou"
#define LOCALIZED_COLOR_PINK                  "Rose"
#define LOCALIZED_COLOR_PLUM                  "Prune"
#define LOCALIZED_COLOR_POWDERBLUE            "Bleu léger"
#define LOCALIZED_COLOR_PURPLE                "Pourpre"
#define LOCALIZED_COLOR_RED                   "Rouge"
#define LOCALIZED_COLOR_ROSYBROWN             "Brun rosé"
#define LOCALIZED_COLOR_ROYALBLUE             "Bleu roi"
#define LOCALIZED_COLOR_SADDLEBROWN           "Brun selle"
#define LOCALIZED_COLOR_SALMON                "Saumon"
#define LOCALIZED_COLOR_SANDYBROWN            "Brun sable"
#define LOCALIZED_COLOR_SEAGREEN              "Vert marin"
#define LOCALIZED_COLOR_SEASHELL              "Coquillage"
#define LOCALIZED_COLOR_SIENNA                "Terre de Sienne"
#define LOCALIZED_COLOR_SILVER                "Argent"
#define LOCALIZED_COLOR_SKYBLUE               "Bleu ciel"
#define LOCALIZED_COLOR_SLATEBLUE             "Bleu ardoise"
#define LOCALIZED_COLOR_SLATEGRAY             "Gris ardoise"
#define LOCALIZED_COLOR_SLATEGREY             "Gris ardoise"
#define LOCALIZED_COLOR_SNOW                  "Neige"
#define LOCALIZED_COLOR_SPRINGGREEN           "Vert printemps"
#define LOCALIZED_COLOR_STEELBLUE             "Bleu acier"
#define LOCALIZED_COLOR_TAN                   "Tan"
#define LOCALIZED_COLOR_TEAL                  "Sarcelle"
#define LOCALIZED_COLOR_THISTLE               "Chardon"
#define LOCALIZED_COLOR_TOMATO                "Tomate"
#define LOCALIZED_COLOR_TURQUOISE             "Turquoise"
#define LOCALIZED_COLOR_VIOLET                "Violet"
#define LOCALIZED_COLOR_WHEAT                 "Froment"
#define LOCALIZED_COLOR_WHITE                 "Blanc"
#define LOCALIZED_COLOR_WHITESMOKE            "Fumée blanche"
#define LOCALIZED_COLOR_YELLOW                "Jaune"
#define LOCALIZED_COLOR_YELLOWGREEN           "Jaune vert"

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
