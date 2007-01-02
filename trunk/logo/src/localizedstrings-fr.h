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
// This file contains localized strings for French
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
//    Tab         -  \t
//    Newline     -  \n
//    Backslash   -  \\
//    DoubleQuote -  \"
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
#define LOCALIZED_ALTERNATE_TRUE    "vrai"
#define LOCALIZED_ALTERNATE_FALSE   "faux"
#define LOCALIZED_ALTERNATE_END     "fin"

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
#define LOCALIZED_ALTERNATE_BITBLOCK               "blocbmp" // 
#define LOCALIZED_ALTERNATE_BITCOPY                "copiebmp"
#define LOCALIZED_ALTERNATE_BITCUT                 "coupebmp"
#define LOCALIZED_ALTERNATE_BITFIT                 "ajustebmp" // 
#define LOCALIZED_ALTERNATE_BITINDEX               "indexbmp"
#define LOCALIZED_ALTERNATE_BITLOAD                "ramènebmp"
#define LOCALIZED_ALTERNATE_BITLOADSIZE            "ramènetaillebmp"
#define LOCALIZED_ALTERNATE_BITSIZE                "taillebmp"
#define LOCALIZED_ALTERNATE_BITMAPTURTLE           "tortuebmp"
#define LOCALIZED_ALTERNATE_BITMODE                "modebmp" // 
#define LOCALIZED_ALTERNATE_BITNOT                 "nonbit" // 
#define LOCALIZED_ALTERNATE_BITOR                  "oubit" // 
#define LOCALIZED_ALTERNATE_BITPASTE               "collerbmp"
#define LOCALIZED_ALTERNATE_BITPASTETOINDEX        "collerbmpindex"
#define LOCALIZED_ALTERNATE_BITSAVE                "sauvebmp"
#define LOCALIZED_ALTERNATE_BITXOR                 "ouxbit" // 
#define LOCALIZED_ALTERNATE_BK                     "re"
#define LOCALIZED_ALTERNATE_BL                     "sd"
#define LOCALIZED_ALTERNATE_BURIED                 "enterré" // 
#define LOCALIZED_ALTERNATE_BURY                   "enterre" // 
#define LOCALIZED_ALTERNATE_BUTFIRST               "saufpremier"
#define LOCALIZED_ALTERNATE_BUTFIRSTS              "bsaufpremiers" // 
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
#define LOCALIZED_ALTERNATE_CHDIR                  "chrep" // 
#define LOCALIZED_ALTERNATE_CHECKBOXCREATE         "créecasechoix" // 
#define LOCALIZED_ALTERNATE_CHECKBOXDELETE         "ceffacecasechoix" // 
#define LOCALIZED_ALTERNATE_CHECKBOXENABLE         "activecasechoix" // 
#define LOCALIZED_ALTERNATE_CHECKBOXGET            "casexhoix" // 
#define LOCALIZED_ALTERNATE_CHECKBOXSET            "fixecasechoix" // 
#define LOCALIZED_ALTERNATE_CLEAN                  "nettoie"
#define LOCALIZED_ALTERNATE_CLEARPALETTE           "videpalette"
#define LOCALIZED_ALTERNATE_CLEARSCREEN            "videécran"
#define LOCALIZED_ALTERNATE_CLEARTEXT              "videtexte"
#define LOCALIZED_ALTERNATE_CLEARTIMER             "cvidechrono" // 
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
#define LOCALIZED_ALTERNATE_DEFINEDP               "procédurep"
#define LOCALIZED_ALTERNATE_DEFINED_               "procédure?"
#define LOCALIZED_ALTERNATE_DIALOGCREATE           "créedialogue" // 
#define LOCALIZED_ALTERNATE_DIALOGENABLE           "dialogueactive" // 
#define LOCALIZED_ALTERNATE_DIALOGDELETE           "effacedialogue" // 
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         "dialogueouvrir" // 
#define LOCALIZED_ALTERNATE_DIALOGFILESAVE         "dialoguesauver" // 
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
#define LOCALIZED_ALTERNATE_ELLIPSEARC             "arcellipse" // 
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
#define LOCALIZED_ALTERNATE_EVENTCHECK             "testévénement" // 
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
#define LOCALIZED_ALTERNATE_FS                     "pé" // 
#define LOCALIZED_ALTERNATE_FULLSCREEN             "pleinécran" // 
#define LOCALIZED_ALTERNATE_FULLTEXT               "pleintexte" // 
#define LOCALIZED_ALTERNATE_GETFOCUS               "focus" // 
#define LOCALIZED_ALTERNATE_GOTO                   "vavers" // 
#define LOCALIZED_ALTERNATE_GIFLOAD                "chargegif" // 
#define LOCALIZED_ALTERNATE_GIFSIZE                "taillegif" // 
#define LOCALIZED_ALTERNATE_GIFSAVE                "sauvegif" // 
#define LOCALIZED_ALTERNATE_GPROP                  "rprop" // 
#define LOCALIZED_ALTERNATE_GREATERP               "supérieurp" // 
#define LOCALIZED_ALTERNATE_GREATER_               "supérieur?" // 
#define LOCALIZED_ALTERNATE_GROUPBOXCREATE         "créegroupe" // 
#define LOCALIZED_ALTERNATE_GROUPBOXDELETE         "effacegroupe" // 
#define LOCALIZED_ALTERNATE_HALT                   "arrêtetout" // 
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
#define LOCALIZED_ALTERNATE_KEYBOARDVALUE          "kvaleurclavier" //
#define LOCALIZED_ALTERNATE_KEYP                   "touchep"
#define LOCALIZED_ALTERNATE_KEY_                   "touche?"
#define LOCALIZED_ALTERNATE_LABEL                  "étiquette"
#define LOCALIZED_ALTERNATE_LABELFONT              "police"
#define LOCALIZED_ALTERNATE_LABELSIZE              "taillepolice" // 
#define LOCALIZED_ALTERNATE_LAST                   "dernier" // 
#define LOCALIZED_ALTERNATE_LEFT                   "gauche"
#define LOCALIZED_ALTERNATE_LEFTROLL               "inclinegauche" // 
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
#define LOCALIZED_ALTERNATE_LPUT                   "metspremier"
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
#define LOCALIZED_ALTERNATE_MKDIR                  "fixerep" // 
#define LOCALIZED_ALTERNATE_MODULO                 "modulo"
#define LOCALIZED_ALTERNATE_MOUSEOFF               "désactivesouris" // 
#define LOCALIZED_ALTERNATE_MOUSEON                "activesouris" // 
#define LOCALIZED_ALTERNATE_MOUSEPOS               "possouris"
#define LOCALIZED_ALTERNATE_NAMEP                  "nomp"
#define LOCALIZED_ALTERNATE_NAME_                  "nom?"
#define LOCALIZED_ALTERNATE_NAMES                  "noms"
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           "refuseconnection" // 
#define LOCALIZED_ALTERNATE_NETACCEPTON            "accepteconnection" // 
#define LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE  "acceptevaleurréception" // 
#define LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE     "acceptevaleurenvoi" // 
#define LOCALIZED_ALTERNATE_NETCONNECTOFF          "désactiveconnection" //
#define LOCALIZED_ALTERNATE_NETCONNECTON           "activeconnection" //
#define LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE "valeurréception" // 
#define LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE    "valeurenvoie" // 
#define LOCALIZED_ALTERNATE_NETSHUTDOWN            "arrêteréseau" // 
#define LOCALIZED_ALTERNATE_NETSTARTUP             "démarreréseau" // 
#define LOCALIZED_ALTERNATE_NOBITMAPTURTLE         "fintortuebmp" // 
#define LOCALIZED_ALTERNATE_NODES                  "noeuds" // 
#define LOCALIZED_ALTERNATE_NODRIBBLE              "fintranscription" // 
#define LOCALIZED_ALTERNATE_NOSTATUS               "fermeétat" // 
#define LOCALIZED_ALTERNATE_NOT                    "non"
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
#define LOCALIZED_ALTERNATE_POPDIR                 "repparent" // 
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
#define LOCALIZED_ALTERNATE_READWORD               "lismot"
#define LOCALIZED_ALTERNATE_REMAINDER              "reste"
#define LOCALIZED_ALTERNATE_REMPROP                "eprop" // 
#define LOCALIZED_ALTERNATE_REPCOUNT               "compteur"
#define LOCALIZED_ALTERNATE_REPEAT                 "répète"
#define LOCALIZED_ALTERNATE_RERANDOM               "rehasard" // 
#define LOCALIZED_ALTERNATE_RIGHT                  "droite"
#define LOCALIZED_ALTERNATE_RIGHTROLL              "inclinedroite" // 
#define LOCALIZED_ALTERNATE_RL                     "ll" // 
#define LOCALIZED_ALTERNATE_RMDIR                  "efrep" // 
#define LOCALIZED_ALTERNATE_ROLL                   "inclinaison" // 
#define LOCALIZED_ALTERNATE_ROUND                  "arrondi"
#define LOCALIZED_ALTERNATE_RR                     "id" // 
#define LOCALIZED_ALTERNATE_RT                     "dr"
#define LOCALIZED_ALTERNATE_RUN                    "exécute"
#define LOCALIZED_ALTERNATE_RUNPARSE               "exécuteanalyse" // 
#define LOCALIZED_ALTERNATE_RUNRESULT              "exécuterésultat" // 
#define LOCALIZED_ALTERNATE_RW                     "lm" // 
#define LOCALIZED_ALTERNATE_SAVE                   "sauve"
#define LOCALIZED_ALTERNATE_SCREENCOLOR            "couleurfond" // 
#define LOCALIZED_ALTERNATE_SCROLLBARCREATE        "créeascenseur" // 
#define LOCALIZED_ALTERNATE_SCROLLBARENABLE        "sactiveascenseur" // 
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
#define LOCALIZED_ALTERNATE_SETCURSORNOWAIT        "fincurseurnormal" // 
#define LOCALIZED_ALTERNATE_SETCURSORWAIT          "fixecurseurattente" // 
#define LOCALIZED_ALTERNATE_SETFC                  "fcr"
#define LOCALIZED_ALTERNATE_SETFLOODCOLOR          "fixecouleurremplissage"
#define LOCALIZED_ALTERNATE_SETFOCUS               "fixefocus" // 
#define LOCALIZED_ALTERNATE_SETH                   "fcap" // 
#define LOCALIZED_ALTERNATE_SETHEADING             "fixecap"
#define LOCALIZED_ALTERNATE_SETITEM                "remplace"
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
#define LOCALIZED_ALTERNATE_SS                     "ém" // 
#define LOCALIZED_ALTERNATE_ST                     "mt"
#define LOCALIZED_ALTERNATE_STANDOUT               "contour" // 
#define LOCALIZED_ALTERNATE_STATICCREATE           "créetexte" // 
#define LOCALIZED_ALTERNATE_STATICDELETE           "effacetexte" // 
#define LOCALIZED_ALTERNATE_STATICUPDATE           "actualisetexte" // 
#define LOCALIZED_ALTERNATE_STATUS                 "état" // 
#define LOCALIZED_ALTERNATE_STEP                   "pasàpas" // 
#define LOCALIZED_ALTERNATE_STEPPED                "pasàpas?" // 
#define LOCALIZED_ALTERNATE_STOP                   "arrête" // 
#define LOCALIZED_ALTERNATE_SUBSTRINGP             "appartientp" // 
#define LOCALIZED_ALTERNATE_SUBSTRING_             "appartient??" // 
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
#define LOCALIZED_ALTERNATE_TS                     "ét" // 
#define LOCALIZED_ALTERNATE_TURTLE                 "tortue"
#define LOCALIZED_ALTERNATE_TURTLEMODE             "modetortue"
#define LOCALIZED_ALTERNATE_TURTLES                "tortues"
#define LOCALIZED_ALTERNATE_TYPE                   "tape"
#define LOCALIZED_ALTERNATE_UNBURY                 "déterre" // 
#define LOCALIZED_ALTERNATE_UNSTEP                 "finpasàpas" // 
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
#define LOCALIZED_ALTERNATE_YESNOBOX               "messageouinon"
#define LOCALIZED_ALTERNATE_YIELD                  "partage" // 
#define LOCALIZED_ALTERNATE_ZOOM                   "zoom" // 

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      "&Valider"
#define LOCALIZED_GENERAL_CANCELBUTTON  "&Annuler"

#define LOCALIZED_GENERAL_PRODUCTNAME   "FMSLogo"



//
// The menu options on the main window 
//
#define LOCALIZED_FILE        "&Fichier"
#define LOCALIZED_FILE_NEW    "&Nouveau\t(supprime l'espace de travail)"
#define LOCALIZED_FILE_LOAD   "&Ramène...\t(fusionne avec l'espace de travail)"
#define LOCALIZED_FILE_OPEN   "&Ouvrir...\t(remplace l'espace de travail)"
#define LOCALIZED_FILE_SAVE   "&Enregistrer"
#define LOCALIZED_FILE_SAVEAS "En&registrer sous..."
#define LOCALIZED_FILE_EDIT   "E&diter..."
#define LOCALIZED_FILE_ERASE  "E&ffacer..."
#define LOCALIZED_FILE_EXIT   "&Quitter"

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
#define LOCALIZED_SET_LABELFONT        "&Police de Caractères de l'Étiquette..."
#define LOCALIZED_SET_COMMANDERFONT    "Police de Caractères de la &Poste de Pilotage..."
#define LOCALIZED_SET_PENCOLOR         "&Couleur Crayon..."
#define LOCALIZED_SET_FLOODCOLOR       "Couleur &Remplissage..."
#define LOCALIZED_SET_SCREENCOLOR      "Couleur &Fond..."

#define LOCALIZED_ZOOM                 "&Zoom"
#define LOCALIZED_ZOOM_IN              "&Avant"
#define LOCALIZED_ZOOM_OUT             "&Arrière"
#define LOCALIZED_ZOOM_NORMAL          "&Normal"

#define LOCALIZED_HELP                 "&Aide"
#define LOCALIZED_HELP_INDEX           "&Manuel (en Anglais)"
#define LOCALIZED_HELP_MCI             "M&anuel MCI (en Anglais)"
#define LOCALIZED_HELP_HELP            "&Utilisation Help"
#define LOCALIZED_HELP_TUTORIAL        "&Tutoriel (en Anglais)"
#define LOCALIZED_HELP_DEMO            "&Démo"
#define LOCALIZED_HELP_EXAMPLE         "&Exemples"
#define LOCALIZED_HELP_RELEASENOTES    "&MAJ Notes"
#define LOCALIZED_HELP_ABOUTFMSLOGO    "&A propos de "LOCALIZED_GENERAL_PRODUCTNAME"..."
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
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH "Pixels tortue par pouce"
#define LOCALIZED_SELECTACTIVEAREA_RESET        "&Raz"
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON


//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     "Copier"
#define LOCALIZED_POPUP_CUT                      "Couper"
#define LOCALIZED_POPUP_PASTE                    "Coller"
#define LOCALIZED_POPUP_DELETE                   "Effacer"
#define LOCALIZED_POPUP_UNDO                     "Annuler" // 
#define LOCALIZED_POPUP_SELECTALL                "Sélectionner tout" // 
#define LOCALIZED_POPUP_HELP                     "Recherche thématique" //

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
#define LOCALIZED_EDITOR_EDIT_CUT                "&Couper\tCtrl+X"
#define LOCALIZED_EDITOR_EDIT_COPY               "C&opier\tCtrl+C"
#define LOCALIZED_EDITOR_EDIT_PASTE              "&Coller\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_DELETE             "&Effacer\tDel"
#define LOCALIZED_EDITOR_EDIT_CLEARALL           "E&ffacer Tout\tCtrl+Del"
#define LOCALIZED_EDITOR_EDIT_SELECTALL          "S&electionner tout\tCtrl+A" // N

#define LOCALIZED_EDITOR_SEARCH                  "&Outils"
#define LOCALIZED_EDITOR_SEARCH_FIND             "Re&chercher...\tCtrl+F"
#define LOCALIZED_EDITOR_SEARCH_REPLACE          "&Remplacer...\tCtrl+H"
#define LOCALIZED_EDITOR_SEARCH_NEXT             "&Suivant\tF3"

#define LOCALIZED_EDITOR_SET                     "&Options"
#define LOCALIZED_EDITOR_SET_FONT                "&Police..."  // NOT_YET_LOCALIZED

#define LOCALIZED_EDITOR_TEST                    "Test!" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITOR_HELP                    "&Aide"  // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_HELP_INDEX              "&Index" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_HELP_EDITOR             "&Editeurr" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        "&Recherche thématique\tF1" // NOT_YET_LOCALIZED


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES // NOT_YET_LOCALIZED
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    "&Enregistrer et quitter" // 
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       "&Ne pas enregistrer" // 
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       "Il y a des changements non enregistrés dans l'espace de travail. Si vous quittez sans enregistrer les changements seront perdus.  " // 
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       "Voulez-vous enregistrer les modifications avant de quitter?"  // 


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     "Poste de pilotage"
#define LOCALIZED_COMMANDER_HALT                "Arrêt"
#define LOCALIZED_COMMANDER_TRACE               "Trace"
#define LOCALIZED_COMMANDER_NOTRACE             "Sup. Trace"
#define LOCALIZED_COMMANDER_PAUSE               "Pause"
#define LOCALIZED_COMMANDER_STATUS              "Etat"
#define LOCALIZED_COMMANDER_NOSTATUS            "Eff. Etat"
#define LOCALIZED_COMMANDER_STEP                "Pas"
#define LOCALIZED_COMMANDER_UNSTEP              "Sup. Pas"
#define LOCALIZED_COMMANDER_RESET               "Initial."
#define LOCALIZED_COMMANDER_EXECUTE             "Execute"
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
#define LOCALIZED_STATUS_PITCH                  "Tang:"
#define LOCALIZED_STATUS_HEADING                "Cap:"
#define LOCALIZED_STATUS_ROLL                   "Roul:"
#define LOCALIZED_STATUS_TURTLE                 "Tortue"
#define LOCALIZED_STATUS_POSITION               "Position(XYZ):"
#define LOCALIZED_STATUS_WHICH                  "Laquelle:"
#define LOCALIZED_STATUS_VISIBILITY             "Visibilité:"
#define LOCALIZED_STATUS_COLOR                  "Couleurs"
#define LOCALIZED_STATUS_PENCOLOR               "Crayon(RVB):"
#define LOCALIZED_STATUS_FLOODCOLOR             "Remplis(RVB):"
#define LOCALIZED_STATUS_SCREENCOLOR            "Ecran(RVB):"
#define LOCALIZED_STATUS_PALETTE                "Palette:"
#define LOCALIZED_STATUS_KERNEL                 "Noyau"
#define LOCALIZED_STATUS_CALLS                  "Appels:"
#define LOCALIZED_STATUS_PEAKMEMORY             "Mémoire:"

#define LOCALIZED_STATUS_PENREVERSE  "Inverse"
#define LOCALIZED_STATUS_PENNORMAL   "Normal"
#define LOCALIZED_STATUS_PENERASE    "Efface"
#define LOCALIZED_STATUS_PENUP       "Haut"
#define LOCALIZED_STATUS_PENDOWN     "Bas"
#define LOCALIZED_STATUS_PENSHOWN    "Visible"
#define LOCALIZED_STATUS_PENHIDDEN   "Caché"
#define LOCALIZED_STATUS_POLYGONS    "Polygones"
#define LOCALIZED_STATUS_VECTORS     "Vecteurs"
#define LOCALIZED_STATUS_NODES       "Noeuds"

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
#define LOCALIZED_SETCOLOR                     "Fixe Couleur"
#define LOCALIZED_SETCOLOR_PENCOLOR            "Fixe Couleur Crayon"
#define LOCALIZED_SETCOLOR_FLOODCOLOR          "Fixe Couleur de Remplissage"
#define LOCALIZED_SETCOLOR_SCREENCOLOR         "Fixe Couleur Fond"
#define LOCALIZED_SETCOLOR_RED                 "Rouge"
#define LOCALIZED_SETCOLOR_GREEN               "Vert"
#define LOCALIZED_SETCOLOR_BLUE                "Bleu"
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   "Taille Crayon"
#define LOCALIZED_SETPENSIZE_SIZE              "Dimension"
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     "A propos de "LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_ABOUTFMS_VERSION             LOCALIZED_GENERAL_PRODUCTNAME" Version "FMSLOGO_VERSION // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_GUI                 "GUI by George Mills (mills@softronix.com)\nSoftronics, Inc.\nhttp:\x2F/www.softronix.com/" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_CORE                "Core by Brian Harvey (bh@cs.berkeley.edu)\nUniversity of California Berkeley" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_INSTALLER           "Installer based on Nullsoft Scriptable Install System\nhttp:\x2F/nsis.sourceforge.net" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_ADVENTURE           "The Great Logo Adventure (ISBN 0-9651934-6-2)\nWritten and donated by Jim Muller\nAvailable at http:\x2F/www.softronix.com/" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       "Thanks to Yehuda Katz (yehuka@softhome.net)\nand Erich Neuwirth (erich.neuwirth@univie.ac.at)" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME" is free software\nSee GNU Public License" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_NEWSGROUP           "Internet News Group: comp.lang.logo\nVisit the Logo-Forum at\nhttp:\x2F/groups.yahoo.com/group/LogoForum/" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     "To learn the internals of computers,\ntry MultiMedia Logic from Softronics, Inc." // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      "A propos de FMS"
#define LOCALIZED_ABOUTMS_FMS                  "FMS stands for Fight Multiple Sclerosis." // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     "Please consider donating to the\nNational Multiple Sclerosis Society.\nhttp:\x2F/www.nmss.org\n1-800-FIGHT-MS" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTMS_OK                   LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED


// 
// Strings in various other dialog boxes
// 

#define LOCALIZED_CHANGESINEDITORMAYBELOST  "Changes in this edit session may be lost.\n\nDo you really want to exit "LOCALIZED_GENERAL_PRODUCTNAME"?" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITSESSIONISRUNNING      "An Edit session is running" // NOT_YET_LOCALIZED

#define LOCALIZED_NOTHALTEDREALLYEXIT        LOCALIZED_GENERAL_PRODUCTNAME" does not like exiting while not halted.\n\nDo you really want to exit "LOCALIZED_GENERAL_PRODUCTNAME"?" // NOT_YET_LOCALIZED
#define LOCALIZED_NOTHALTEDREALLYHALT        LOCALIZED_GENERAL_PRODUCTNAME" does not like exiting while not halted.\n\nDo you really want to Halt "LOCALIZED_GENERAL_PRODUCTNAME"?" // NOT_YET_LOCALIZED
#define LOCALIZED_LOGOISNOTHALTED            LOCALIZED_GENERAL_PRODUCTNAME" is not Halted" // NOT_YET_LOCALIZED

#define LOCALIZED_WRITEFAILEDNOMEMORY         "Write failed, Possibly no Memory" // NOT_YET_LOCALIZED
#define LOCALIZED_COULDNOTWRITEBMP            "Could not write .bmp" // NOT_YET_LOCALIZED
#define LOCALIZED_COULDNOTOPENBMP             "Could not open .bmp" // NOT_YET_LOCALIZED
#define LOCALIZED_COULDNOTCREATEBMP           "Unable to create Windows 3.0 bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_NOTVALIDBMP                 "Not a Windows 3.0 bitmap" // NOT_YET_LOCALIZED

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         "Non sauvegardé sur disque"
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     "Nouveau supprime toutes les définitions.\n\nContinuer avec nouveau?"
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE "The file being loaded will be merged into your workspace\nand may overwrite your unsaved changes.\n\nContinue with Load?" // NOT_YET_LOCALIZED
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    "Le chargement du fichier va écraser l'espace de travail.\n\nContinuer le chargement?"

#define LOCALIZED_EDITORISOPEN                  "Did you know you have an edit session running?\n\nAny changes in this edit session are not being saved." // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_CANTREADFILE            "Unable to read file \"%s\" from disk" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTWRITEFILE           "Unable to write file \"%s\" to disk" // NOT_YET_LOCALIZED

#define LOCALIZED_SAVEISFOREXPERTSONLY          "Cette possibilité est réservée au mode expert (utiliser "LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT")"
#define LOCALIZED_SAVETOWORKSPACE                "Sauve l'espace de travail"
#define LOCALIZED_CONTENTSCHANGED                "Changement du contenu"
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE "Le contenu a été modifié. Voulez-vous interpréter l'espace de travail?"



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  "Le curseur est placé après la dernière bonne définition.\nRegarde la fenêtre de pilotage pour le message d'erreur."
#define LOCALIZED_RETURNTOEDIT                  "Retour à l'éditeur?"

#define LOCALIZED_EDITFAILEDTOLOAD              "L'éditeur n'a pas réussi le chargement"



// 
//  Strings used in the File-Open filters
//
#define LOCALIZED_FILEFILTER_ALLFILES "All Files (*.*)|*.*|" // NOT_YET_LOCALIZED
#define LOCALIZED_FILEFILTER_LOGO     "Logo Files (*.lgo)|*.lgo|"LOCALIZED_FILEFILTER_ALLFILES // NOT_YET_LOCALIZED
#define LOCALIZED_FILEFILTER_IMAGE    "Bitmap Files (*.bmp)|*.bmp|GIF Files (*.gif)|*.gif|"LOCALIZED_FILEFILTER_ALLFILES // NOT_YET_LOCALIZED



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
#define LOCALIZED_STEPPING                  "Single Step" // NOT_YET_LOCALIZED

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  "%s définie\n"


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    "erase" // NOT_YET_LOCALIZED
#define LOCALIZED_PENMODE_REVERSE  "reverse" // NOT_YET_LOCALIZED
#define LOCALIZED_PENMODE_PAINT    "paint" // NOT_YET_LOCALIZED

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
#define LOCALIZED_ERROR_NOCATCHTAG             "Pas de CATCH correspondant à l'étiquette (tag) %p"
#define LOCALIZED_ERROR_ALREADYDEFINED         "%p est déjà définie"
#define LOCALIZED_ERROR_STOPPING               "Arrêt..."
#define LOCALIZED_ERROR_ALREADYDRIBBLING       "Déjà en train d'appliquer DRIBBLE"
#define LOCALIZED_ERROR_FILESYSTEM                   "Erreur système de fichiers: %p"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          "Impossible d'ouvrir fichier"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         "Impossible d'ouvrir fichier: %t"
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       "Fichier déjà ouvert"
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           "Fichier non ouvert"
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  "Could not create editor file" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   "Could not launch the editor"  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    "Could not read editor file"  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_IFWARNING              "Supposant que vous voulez dire SINON (IFELSE) et non SI (IF)"
#define LOCALIZED_ERROR_SHADOWWARNING          "%p masquée dans un appel de procédure"
#define LOCALIZED_ERROR_USER                   "Throw \"Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_ISPRIMITIVE            "%p est une primitive"
#define LOCALIZED_ERROR_TONOTINSIDE            "Impossible d'utiliser POUR (TO) dans une procédure"
#define LOCALIZED_ERROR_ATTOPLEVEL             "Ne peux utiliser %p que dans une procédure" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_ATTOPLEVEL2            "Ne peux utiliser RETOURNE (OUTPUT) ou STOPPE (STOP) que dans une procédure"
#define LOCALIZED_ERROR_NOTEST                 "%p sans TEST"
#define LOCALIZED_ERROR_BADMACROOUTPUT         "La macro retourne %s au lieu d'une liste"
#define LOCALIZED_ERROR_DEEPEND                "FIN (END) dans une instruction multi-ligne"
#define LOCALIZED_ERROR_DEEPENDIN              "FIN (END) dans une instruction multi-ligne dans %p"
#define LOCALIZED_ERROR_UNKNOWN                "Unknown error condition - internal error." // NOT_YET_LOCALIZED

#define LOCALIZED_PAUSING                      "Pause..."


//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      "Erreur"
#define LOCALIZED_ERROR_BADINPUT             "Bad input" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    "Input is not paired" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_CANTOPENPORT         "Could not open port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTCLOSEPORT        "Could not close port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTFLUSHPORT        "Could not flush port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTDCBONPORT        "Could not build dcb on port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTSETPORT          "Could not set port" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_PORTALREADYOPEN      "Port is already open" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_PORTNOTOPEN          "Port is not open" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FIRSTINPUTNOTANARRY  "First input must be an array" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   "Already exists" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    "Does not exist" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_DLL                   "DLL Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLNOTLOADED          "DLL is not loaded" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLALREADYLOADED      "DLL is already loaded" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLLOADFAILED         "DLL load failed" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    "Invalid data type input" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  "Invalid output type" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   "Function not found" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  "Not all Type/Data inputs are paired" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_NETWORK                    "Network Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKRECEIVE             "Network Receive Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKSEND                "Network Send Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKSHUTDOWN            "Unexpected Error, Network may be shutdown" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOTSTARTED          "Not started" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED      "Already started" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKALREADYON           "Already on" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKALREADYOFF          "Already off" // NOT_YET_LOCALIZED

// The rest of the network errors shouldn't really see -- may be okay not to localize
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

#define LOCALIZED_ERROR_POLYSTART               "PolyStart Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED "You already have a Polygon started" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_POLYEND                 "PolyEnd Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       "You have not started a Polygon" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     "You must have at least 3 vectors to define a polygon"  // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_SOUND                 "Sound Error" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_MIDI                  "Erreur Midi"
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     "Invalid MIDI device" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MIDIALREADYOPEN       "Déja ouvert"
#define LOCALIZED_ERROR_MIDINOTOPEN           "Déja fermé"

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      "No Text in Clipboard" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_MCI                   "Erreur MCI"

#define LOCALIZED_ERROR_TIMERTOOMANY          "Too Many Timers" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_TIMERBADID            "Mauvais numéro de timer"
#define LOCALIZED_ERROR_TIMERNOTFOUND         "Timer non trouvé"

#define LOCALIZED_ERROR_BITMODEBADBITMODE     "Illegal Bitmode" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       "Online help is unavailable because hhctrl.ocx could not be loaded."  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_HHCTRLATOMNOTFOUND    "Online help is unavailable because hhctrl.ocx does not contain ATOM_HTMLHELP_API_ANSI."  // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_BADCOMMANDLINE        "Invalid Command Line"  // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_TMPNOTDEFINED         "The environment variable TMP is not defined or invalid.\n"LOCALIZED_GENERAL_PRODUCTNAME" will attempt to use C:\\ for storing temporary files" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_GIFSAVEFAILED         "Problem Generating GIF, check memory and diskspace" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_GIFREADFAILED         "Problem Reading GIF, check memory and diskspace" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  "BitMap Index out of range" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPCUTFAILED        "Cut failed, Possibly not enough Memory" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPFITFAILED        "Fit failed, Possibly not enough Memory" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    "Nothing to Paste"  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  "BitMap at Index must be initialized with a bitmap"  // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_BADTURTLEID             "Bad Turtle Id" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      "Turtle %d has no picture, will Halt" // NOT_YET_LOCALIZED

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
#define LOCALIZED_FILE_POPPEDTO            "Depiler dans \"%s\""
#define LOCALIZED_FILE_MKDIRSUCCEEDED      "Le répertoire \"%s\" est créé"
#define LOCALIZED_FILE_MKDIRFAILED         "Imposible de créer le répertoire \"%s\""
#define LOCALIZED_FILE_RMDIRSUCCEEDED      "Le répertoire \"%s\" est supprimé"
#define LOCALIZED_FILE_RMDIRFAILED         "Imposible de supprimé le répertoire \"%s\""
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  "Le répertoire n'éxiste pas"
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY "Le répertoire est-il vide?"


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       "Logo Picture" // NOT_YET_LOCALIZED

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    "Zone Active"
#define LOCALIZED_INFORMATION   "Information" // NOT_YET_LOCALIZED
#define LOCALIZED_WARNING       "Warning" // NOT_YET_LOCALIZED
#define LOCALIZED_UNTITLED      "Untitled" // NOT_YET_LOCALIZED
#define LOCALIZED_UNKNOWN       "Unknown" // NOT_YET_LOCALIZED

#define LOCALIZED_UNBOUND       "Unbound" // NOT_YET_LOCALIZED

//
// Strings that explain the purpose of each menu option.
// I don't think that any of these strings can be seen by the user, 
// so you probably don't have to translate these.
//
#define LOCALIZED_STRINGTABLE_FILESAVEAS "Saves the contents of the EDALL window to a new file" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILEOPEN "Erases the current workspace and loads a Logo program as the new workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILELOAD "Locates and loads a Logo program into the current workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILENEW "Erases the contents of the EDALL session" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILESAVE "Saves the contents of the EDALL window" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILEEDIT "Selects a procedure to edit" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILEERASE "Selects a procedure to erase" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EXIT "Exits Logo" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_BITMAPNEW "Clears the screen" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_BITMAPOPEN "Loads a new screen from a Windows bitmap file" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_BITMAPSAVE "Saves the contents of the screen to a bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_BITMAPSAVEAS "Saves the contents of the screen to a different file" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_BITMAPPRINT "Prints the contents of the screen" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_BITMAPPRINTERSETUP "Configures your printer" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_BITMAPPRINTERAREA "Sets the area of the screen that will be printed or saved to a bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_SETPENSIZE "Sets the thickness of the turtle's pen" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_SETFONT "Sets the font that is used by the LABEL command" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_SETCOMMANDERFONT "Sets the font used in the commander window" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_SETPENCOLOR "Sets the color of the turtle's pen" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_SETFLOODCOLOR "Sets the color used by the FILL command" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_SETSCREENCOLOR "Clears the screen and sets it to a new color" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_ZOOMIN "Zooms in on the screen" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_ZOOMOUT "Zooms out on the screen" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_ZOOMNORMAL "Restores the screen to its original size" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELP "Opens an index of help topics" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPMCI "Opens an index of help topics for the Media Control Interface" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPHELP "Opens help on using help" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPTUTORIAL "Opens a short tutorial on using "LOCALIZED_GENERAL_PRODUCTNAME // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPDEMO "Shows a demonstration of some things you can do in "LOCALIZED_GENERAL_PRODUCTNAME // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPEXAMPLES "Displays an index of the sample programs" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPRELEASENOTES "Displays the release notes for this version of "LOCALIZED_GENERAL_PRODUCTNAME // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPABOUT "Displays version and copyright information" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPABOUTMS "Displays a message about Multiple Sclerosis" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITDELETE "Deletes the current selection (and does not copy to the clipboard)" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITCLEAR "Deletes all text" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITUNDO "Undoes the previous action" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITCUT "Removes the selected text and puts it on the clipboard" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITCOPY "Copies the selected text to the clipboard" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITPASTE "Inserts the text from the clipboard at the current position" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITSELECTALL "Selects all text" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITFIND "Searches for text" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITREPLACE "Searches for text and replaces it with other text" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITFINDNEXT "Repeats the previous Find or Replace command" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDITSETFONT "Sets the font for the EDALL window" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_TEST "Runs the selected Logo instructions" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPEDIT "Displays help on using the editor" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPEDIT_TOPIC "Displays help for Logo" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILESAVEANDEXIT "Saves and exits the current EDALL session" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILESAVETOWORKSPACE "Saves the current EDALL session" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILEPRINT "Prints the current EDALL session" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDALLEXIT "Closes the EDALL session" // NOT_YET_LOCALIZED

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING "'%s' non trouvé"
