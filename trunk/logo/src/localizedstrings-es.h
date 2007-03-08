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
// This file contains localized strings for Spanish
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
#define LOCALIZED_ALTERNATE_TRUE    "cierto"
#define LOCALIZED_ALTERNATE_FALSE   "falso"
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
#define LOCALIZED_ALTERNATE__DEFMACRO              ".defMacro"
#define LOCALIZED_ALTERNATE__EQ                    ".ig"
#define LOCALIZED_ALTERNATE__MACRO                 ".macro"
#define LOCALIZED_ALTERNATE__MAYBEOUTPUT           ".quizaDevuelve"
#define LOCALIZED_ALTERNATE__SETBF                 ".ponMP"
#define LOCALIZED_ALTERNATE__SETFIRST              ".ponPrimero"
#define LOCALIZED_ALTERNATE__SETITEM               ".ponElemento"
#define LOCALIZED_ALTERNATE_ACTIVEAREA             "areaActiva"
#define LOCALIZED_ALTERNATE_ALLOPEN                "abiertos"
#define LOCALIZED_ALTERNATE_AND                    "y"
#define LOCALIZED_ALTERNATE_APPLY                  "aplica"
#define LOCALIZED_ALTERNATE_ARCCOS                 "arccos"
#define LOCALIZED_ALTERNATE_ARCSIN                 "arcsen"
#define LOCALIZED_ALTERNATE_ARCTAN                 "arctan"
#define LOCALIZED_ALTERNATE_ARRAY                  "vector"
#define LOCALIZED_ALTERNATE_ARRAYP                 "vector?"
#define LOCALIZED_ALTERNATE_ARRAY_                 "vector?"
#define LOCALIZED_ALTERNATE_ASCII                  "ascii"
#define LOCALIZED_ALTERNATE_ASHIFT                 "desplaza"
#define LOCALIZED_ALTERNATE_BACK                   "retrocede"
#define LOCALIZED_ALTERNATE_BACKSLASHEDP           "tieneBarra?"
#define LOCALIZED_ALTERNATE_BACKSLASHED_           "tieneBarra?"
#define LOCALIZED_ALTERNATE_BEFOREP                "anterior?"
#define LOCALIZED_ALTERNATE_BEFORE_                "anterior?"
#define LOCALIZED_ALTERNATE_BF                     "mp"
#define LOCALIZED_ALTERNATE_BFS                    "mps"
#define LOCALIZED_ALTERNATE_BITAND                 "bitand" // "bity"
#define LOCALIZED_ALTERNATE_BITBLOCK               "rectanguloRelleno"
#define LOCALIZED_ALTERNATE_BITCOPY                "copiaArea"
#define LOCALIZED_ALTERNATE_BITCUT                 "cortaArea"
#define LOCALIZED_ALTERNATE_BITFIT                 "ajusta"
#define LOCALIZED_ALTERNATE_BITINDEX               "indiceImagen"
#define LOCALIZED_ALTERNATE_BITLOAD                "cargaDib"
#define LOCALIZED_ALTERNATE_BITLOADSIZE            "tamañoCargaDib"
#define LOCALIZED_ALTERNATE_BITSIZE                "tamañoDibujo"
#define LOCALIZED_ALTERNATE_BITMAPTURTLE           "ponForma" // "ponformatortuga"
#define LOCALIZED_ALTERNATE_BITMODE                "modoBitmap?"
#define LOCALIZED_ALTERNATE_BITNOT                 "bitNot" // "bitinverso"
#define LOCALIZED_ALTERNATE_BITOR                  "bitOr" // "bito"
#define LOCALIZED_ALTERNATE_BITPASTE               "bitPega" // "pega"
#define LOCALIZED_ALTERNATE_BITPASTETOINDEX        "bitPegaEnIndice" // "pegaenindice"
#define LOCALIZED_ALTERNATE_BITSAVE                "guardaDib"
#define LOCALIZED_ALTERNATE_BITXOR                 "bitXor"
#define LOCALIZED_ALTERNATE_BK                     "re"
#define LOCALIZED_ALTERNATE_BL                     "mu"
#define LOCALIZED_ALTERNATE_BURIED                 "tapado"
#define LOCALIZED_ALTERNATE_BURY                   "tapa"
#define LOCALIZED_ALTERNATE_BUTFIRST               "menosPrimero"
#define LOCALIZED_ALTERNATE_BUTFIRSTS              "menosPrimeros"
#define LOCALIZED_ALTERNATE_BUTLAST                "menosUltimo"
#define LOCALIZED_ALTERNATE_BUTTONCREATE           "creaBoton"
#define LOCALIZED_ALTERNATE_BUTTONDELETE           "borraBoton"
#define LOCALIZED_ALTERNATE_BUTTONENABLE           "habilitarBoton"
#define LOCALIZED_ALTERNATE_BUTTONUPDATE           "actualizaBoton"
#define LOCALIZED_ALTERNATE_BUTTONP                "boton?"
#define LOCALIZED_ALTERNATE_BUTTON_                "boton?"
#define LOCALIZED_ALTERNATE_BYE                    "adios"
#define LOCALIZED_ALTERNATE_CATCH                  "atrapa" // "coge"
#define LOCALIZED_ALTERNATE_CHAR                   "car"
#define LOCALIZED_ALTERNATE_CHDIR                  "cambiaDir"
#define LOCALIZED_ALTERNATE_CHECKBOXCREATE         "creaCheckbox"
#define LOCALIZED_ALTERNATE_CHECKBOXDELETE         "borraCheckbox"
#define LOCALIZED_ALTERNATE_CHECKBOXENABLE         "habilitarCheckbox"
#define LOCALIZED_ALTERNATE_CHECKBOXGET            "estadoCheckbox"
#define LOCALIZED_ALTERNATE_CHECKBOXSET            "ponCheckbox"
#define LOCALIZED_ALTERNATE_CLEAN                  "limpia"
#define LOCALIZED_ALTERNATE_CLEARPALETTE           "borraPaleta"
#define LOCALIZED_ALTERNATE_CLEARSCREEN            "borraPantalla"
#define LOCALIZED_ALTERNATE_CLEARTEXT              "borraTexto"
#define LOCALIZED_ALTERNATE_CLEARTIMER             "contadorACero"
#define LOCALIZED_ALTERNATE_CLOSE                  "cierra"
#define LOCALIZED_ALTERNATE_CLOSEALL               "cierraTodo"
#define LOCALIZED_ALTERNATE_CO                     "co"
#define LOCALIZED_ALTERNATE_COMBOBOXADDSTRING      "añadeLineaCombobox"
#define LOCALIZED_ALTERNATE_COMBOBOXCREATE         "creaCombobox"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETE         "borraCombobox"
#define LOCALIZED_ALTERNATE_COMBOBOXENABLE         "habilitarCombobox"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING   "borralineaCombobox"
#define LOCALIZED_ALTERNATE_COMBOBOXGETTEXT        "leetextoCombobox"
#define LOCALIZED_ALTERNATE_COMBOBOXSETTEXT        "pontextoCombobox"
#define LOCALIZED_ALTERNATE_CONTENTS               "contenido"
#define LOCALIZED_ALTERNATE_CONTINUE               "sigue"
#define LOCALIZED_ALTERNATE_COPYDEF                "copiaDef"
#define LOCALIZED_ALTERNATE_COS                    "cos"
#define LOCALIZED_ALTERNATE_COUNT                  "cuenta"
#define LOCALIZED_ALTERNATE_CS                     "bp"
#define LOCALIZED_ALTERNATE_CT                     "bt"
#define LOCALIZED_ALTERNATE_CURSOR                 "cursor"
#define LOCALIZED_ALTERNATE_DEBUGWINDOWS           "ventanaDepurador"
#define LOCALIZED_ALTERNATE_DEFINE                 "define"
#define LOCALIZED_ALTERNATE_DEFINEDP               "definido?"
#define LOCALIZED_ALTERNATE_DEFINED_               "definido?"
#define LOCALIZED_ALTERNATE_DIALOGCREATE           "creaDialogo"
#define LOCALIZED_ALTERNATE_DIALOGENABLE           "habilitarDialogo"
#define LOCALIZED_ALTERNATE_DIALOGDELETE           "borraDialogo"
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         "abreDialogo"
#define LOCALIZED_ALTERNATE_DIALOGFILESAVE         "guardaDialogo"
#define LOCALIZED_ALTERNATE_DIFFERENCE             "diferencia"
#define LOCALIZED_ALTERNATE_DIRECTORIES            "directorios"
#define LOCALIZED_ALTERNATE_DLLCALL                "llamaDLL"
#define LOCALIZED_ALTERNATE_DLLFREE                "quitaDLL"
#define LOCALIZED_ALTERNATE_DLLLOAD                "cargaDLL"
#define LOCALIZED_ALTERNATE_DOWN                   "abajo"
#define LOCALIZED_ALTERNATE_DOWNPITCH              "bajaNariz"
#define LOCALIZED_ALTERNATE_DRIBBLE                "eco"
#define LOCALIZED_ALTERNATE_ED                     "ed"
#define LOCALIZED_ALTERNATE_EDIT                   "edita"
#define LOCALIZED_ALTERNATE_ELLIPSEARC             "arcoElipse"
#define LOCALIZED_ALTERNATE_EMPTYP                 "vacio?"
#define LOCALIZED_ALTERNATE_EMPTY_                 "vacio?"
#define LOCALIZED_ALTERNATE_EOFP                   "finlec?"
#define LOCALIZED_ALTERNATE_EOF_                   "finlec?"
#define LOCALIZED_ALTERNATE_EQUALP                 "iguales?"
#define LOCALIZED_ALTERNATE_EQUAL_                 "iguales?"
#define LOCALIZED_ALTERNATE_ER                     "bo"
#define LOCALIZED_ALTERNATE_ERASE                  "borra"
#define LOCALIZED_ALTERNATE_ERASEFILE              "borraArchivo"
#define LOCALIZED_ALTERNATE_ERF                    "boArchivo"
#define LOCALIZED_ALTERNATE_ERROR                  "error"
#define LOCALIZED_ALTERNATE_EVENTCHECK             "siEvento"
#define LOCALIZED_ALTERNATE_EXP                    "exp"
#define LOCALIZED_ALTERNATE_FD                     "av"
#define LOCALIZED_ALTERNATE_FENCE                  "modoJaula"
#define LOCALIZED_ALTERNATE_FILL                   "rellena"
#define LOCALIZED_ALTERNATE_FILES                  "listaArchivos" // "listaarch"
#define LOCALIZED_ALTERNATE_FIRST                  "primero"
#define LOCALIZED_ALTERNATE_FIRSTS                 "primeros"
#define LOCALIZED_ALTERNATE_FLOODCOLOR             "pintaColor"
#define LOCALIZED_ALTERNATE_FONTFACENAMES          "tiposDeLetra"
#define LOCALIZED_ALTERNATE_FOREVER                "siempre"
#define LOCALIZED_ALTERNATE_FORM                   "formatoNumero"
#define LOCALIZED_ALTERNATE_FORWARD                "avanza"
#define LOCALIZED_ALTERNATE_FPUT                   "ponPrimero"
#define LOCALIZED_ALTERNATE_FS                     "pg"
#define LOCALIZED_ALTERNATE_FULLSCREEN             "pantallaGrafica"
#define LOCALIZED_ALTERNATE_FULLTEXT               "textoCompleto"
#define LOCALIZED_ALTERNATE_GETFOCUS               "leeFoco"
#define LOCALIZED_ALTERNATE_GOTO                   "saltoA"
#define LOCALIZED_ALTERNATE_GIFLOAD                "cargaGif"
#define LOCALIZED_ALTERNATE_GIFSIZE                "tamañoGif"
#define LOCALIZED_ALTERNATE_GIFSAVE                "guardaGif"
#define LOCALIZED_ALTERNATE_GPROP                  "propiedad"
#define LOCALIZED_ALTERNATE_GREATEREQUALP          "mayor.o.igual?"
#define LOCALIZED_ALTERNATE_GREATEREQUAL_          "mayor.o.igual?"
#define LOCALIZED_ALTERNATE_GREATERP               "mayor?"
#define LOCALIZED_ALTERNATE_GREATER_               "mayor?"
#define LOCALIZED_ALTERNATE_GROUPBOXCREATE         "creaGroupbox"
#define LOCALIZED_ALTERNATE_GROUPBOXDELETE         "borraGroupbox"
#define LOCALIZED_ALTERNATE_HALT                   "alto"
#define LOCALIZED_ALTERNATE_HEADING                "rumbo"
#define LOCALIZED_ALTERNATE_HELP                   "ayuda"
#define LOCALIZED_ALTERNATE_HIDETURTLE             "ot"
#define LOCALIZED_ALTERNATE_HOME                   "centro"
#define LOCALIZED_ALTERNATE_HT                     "ocultaTortuga"
#define LOCALIZED_ALTERNATE_IF                     "si"
#define LOCALIZED_ALTERNATE_IFELSE                 "siSino"
#define LOCALIZED_ALTERNATE_IFF                    "siFalso"
#define LOCALIZED_ALTERNATE_IFFALSE                "siFalso"
#define LOCALIZED_ALTERNATE_IFT                    "sicierto"
#define LOCALIZED_ALTERNATE_IFTRUE                 "sicierto"
#define LOCALIZED_ALTERNATE_INGAMEPORT             "leePuertoJuego"
#define LOCALIZED_ALTERNATE_INPORT                 "leePuerto2"
#define LOCALIZED_ALTERNATE_INPORTB                "leePuerto"
#define LOCALIZED_ALTERNATE_INT                    "entero"
#define LOCALIZED_ALTERNATE_ITEM                   "elemento"
#define LOCALIZED_ALTERNATE_KEYBOARDOFF            "desHabilitaTeclado"
#define LOCALIZED_ALTERNATE_KEYBOARDON             "habilitaTeclado"
#define LOCALIZED_ALTERNATE_KEYBOARDVALUE          "leeTecla" // "leecar"
#define LOCALIZED_ALTERNATE_KEYP                   "tecla?" // "tecla"
#define LOCALIZED_ALTERNATE_KEY_                   "tecla?"
#define LOCALIZED_ALTERNATE_LABEL                  "rotulo"
#define LOCALIZED_ALTERNATE_LABELFONT              "tipo"
#define LOCALIZED_ALTERNATE_LABELSIZE              "rotuloTam"
#define LOCALIZED_ALTERNATE_LAST                   "ultimo"
#define LOCALIZED_ALTERNATE_LEFT                   "giraIzquierda"
#define LOCALIZED_ALTERNATE_LEFTROLL               "balanceaIzquierda"
#define LOCALIZED_ALTERNATE_LESSEQUALP             "mejor.o.igual?"
#define LOCALIZED_ALTERNATE_LESSEQUAL_             "mejor.o.igual?"
#define LOCALIZED_ALTERNATE_LESSP                  "menor?"
#define LOCALIZED_ALTERNATE_LESS_                  "menor?"
#define LOCALIZED_ALTERNATE_LIGHT                  "luz"
#define LOCALIZED_ALTERNATE_LIST                   "lista"
#define LOCALIZED_ALTERNATE_LISTBOXADDSTRING       "añadeCadenaListbox"
#define LOCALIZED_ALTERNATE_LISTBOXCREATE          "creaListbox"
#define LOCALIZED_ALTERNATE_LISTBOXENABLE          "habilitarListbox"
#define LOCALIZED_ALTERNATE_LISTBOXDELETE          "borraListbox"
#define LOCALIZED_ALTERNATE_LISTBOXDELETESTRING    "borraCadenaListbox"
#define LOCALIZED_ALTERNATE_LISTBOXGETSELECT       "leeseLeccionListbox"
#define LOCALIZED_ALTERNATE_LISTP                  "lista?"
#define LOCALIZED_ALTERNATE_LIST_                  "lista?"
#define LOCALIZED_ALTERNATE_LN                     "ln"
#define LOCALIZED_ALTERNATE_LOAD                   "carga"
#define LOCALIZED_ALTERNATE_LOCAL                  "local"
#define LOCALIZED_ALTERNATE_LOG10                  "log"
#define LOCALIZED_ALTERNATE_LOGOVERSION            "versionLogo"
#define LOCALIZED_ALTERNATE_LOWERCASE              "minusculas"
#define LOCALIZED_ALTERNATE_LPUT                   "ponUltimo"
#define LOCALIZED_ALTERNATE_LR                     "bi"
#define LOCALIZED_ALTERNATE_LSHIFT                 "desplazaIzquierda"
#define LOCALIZED_ALTERNATE_LT                     "gi"
#define LOCALIZED_ALTERNATE_MACHINE                "sistema"
#define LOCALIZED_ALTERNATE_MACROP                 "macro?"
#define LOCALIZED_ALTERNATE_MACRO_                 "macro?"
#define LOCALIZED_ALTERNATE_MAKE                   "haz"
#define LOCALIZED_ALTERNATE_MCI                    "mci"
#define LOCALIZED_ALTERNATE_MEMBER                 "miembro"
#define LOCALIZED_ALTERNATE_MEMBERP                "miembro?"
#define LOCALIZED_ALTERNATE_MEMBER_                "miembro?"
#define LOCALIZED_ALTERNATE_MESSAGEBOX             "mensaje"
#define LOCALIZED_ALTERNATE_MIDICLOSE              "cierraMidi"
#define LOCALIZED_ALTERNATE_MIDIMESSAGE            "mensajeMidi"
#define LOCALIZED_ALTERNATE_MIDIOPEN               "abreMidi"
#define LOCALIZED_ALTERNATE_MINUS                  "cambiaSigno"
#define LOCALIZED_ALTERNATE_MKDIR                  "creaDir"
#define LOCALIZED_ALTERNATE_MODULO                 "resto"
#define LOCALIZED_ALTERNATE_MOUSEOFF               "habilitaRaton"
#define LOCALIZED_ALTERNATE_MOUSEON                "inhabilitaRaton"
#define LOCALIZED_ALTERNATE_MOUSEPOS               "posRaton"
#define LOCALIZED_ALTERNATE_NAMEP                  "var?"
#define LOCALIZED_ALTERNATE_NAME_                  "var?"
#define LOCALIZED_ALTERNATE_NAMES                  "lVars"
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           "inhabilitaAceptaRed"
#define LOCALIZED_ALTERNATE_NETACCEPTON            "habilitaAceptaRed"
#define LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE  "recibeValorAceptaRed"
#define LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE     "enviaValorAceptaRed"
#define LOCALIZED_ALTERNATE_NETCONNECTOFF          "inhabilitaConectaRed"
#define LOCALIZED_ALTERNATE_NETCONNECTON           "habilitaConectaRed"
#define LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE "recibeValorConectaRed"
#define LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE    "enviaValorConectaRed"
#define LOCALIZED_ALTERNATE_NETSHUTDOWN            "finRed"
#define LOCALIZED_ALTERNATE_NETSTARTUP             "iniciaRed"
#define LOCALIZED_ALTERNATE_NOBITMAPTURTLE         "ponFormaTortuga" // "quitadibujotortuga"
#define LOCALIZED_ALTERNATE_NODES                  "nodos"
#define LOCALIZED_ALTERNATE_NODRIBBLE              "noEco"
#define LOCALIZED_ALTERNATE_NOSTATUS               "quitaEstado"
#define LOCALIZED_ALTERNATE_NOT                    "no"
#define LOCALIZED_ALTERNATE_NOTEQUALP              "noIguales?"
#define LOCALIZED_ALTERNATE_NOTEQUAL_              "noIguales?"
#define LOCALIZED_ALTERNATE_NOYIELD                "exclusivo"
#define LOCALIZED_ALTERNATE_NUMBERP                "numero?"
#define LOCALIZED_ALTERNATE_NUMBER_                "numero?"
#define LOCALIZED_ALTERNATE_OP                     "dev"
#define LOCALIZED_ALTERNATE_OPENAPPEND             "abreAñadir"
#define LOCALIZED_ALTERNATE_OPENREAD               "abreLectura"
#define LOCALIZED_ALTERNATE_OPENUPDATE             "abreActualizar"
#define LOCALIZED_ALTERNATE_OPENWRITE              "abreEscritura"
#define LOCALIZED_ALTERNATE_OR                     "o"
#define LOCALIZED_ALTERNATE_OUTPORT                "escribePuerto2"
#define LOCALIZED_ALTERNATE_OUTPORTB               "escribePuerto"
#define LOCALIZED_ALTERNATE_OUTPUT                 "devuelve"
#define LOCALIZED_ALTERNATE_PARSE                  "analiza"
#define LOCALIZED_ALTERNATE_PAUSE                  "pausa"
#define LOCALIZED_ALTERNATE_PC                     "cl"
#define LOCALIZED_ALTERNATE_PD                     "bl"
#define LOCALIZED_ALTERNATE_PE                     "goma"
#define LOCALIZED_ALTERNATE_PENCOLOR               "colorLapiz"
#define LOCALIZED_ALTERNATE_PENDOWN                "bajaLapiz"
#define LOCALIZED_ALTERNATE_PENDOWNP               "bajaLapiz?"
#define LOCALIZED_ALTERNATE_PENDOWN_               "bajaLapiz?"
#define LOCALIZED_ALTERNATE_PENERASE               "goma"
#define LOCALIZED_ALTERNATE_PENMODE                "lapizModo"
#define LOCALIZED_ALTERNATE_PENPAINT               "lapizNormal"
#define LOCALIZED_ALTERNATE_PENPATTERN             "patronLapiz"
#define LOCALIZED_ALTERNATE_PENREVERSE             "lapizInvierte"
#define LOCALIZED_ALTERNATE_PENSIZE                "grosor"
#define LOCALIZED_ALTERNATE_PENUP                  "subeLapiz"
#define LOCALIZED_ALTERNATE_PERSPECTIVE            "perspectiva"
#define LOCALIZED_ALTERNATE_PITCH                  "cabeceo"
#define LOCALIZED_ALTERNATE_PIXEL                  "pixel"
#define LOCALIZED_ALTERNATE_PLAYWAVE               "suenaWave"
#define LOCALIZED_ALTERNATE_PLIST                  "lProp"
#define LOCALIZED_ALTERNATE_PLISTS                 "lProps"
#define LOCALIZED_ALTERNATE_PO                     "imDefs"
#define LOCALIZED_ALTERNATE_POPDIR                 "directorioPadre"
#define LOCALIZED_ALTERNATE_POLYSTART              "empiezaPoligono"
#define LOCALIZED_ALTERNATE_POLYEND                "terminaPoligono"
#define LOCALIZED_ALTERNATE_POLYVIEW               "muestraPoligono"
#define LOCALIZED_ALTERNATE_PORTCLOSE              "cierraPuerto"
#define LOCALIZED_ALTERNATE_PORTFLUSH              "limpiaPuerto"
#define LOCALIZED_ALTERNATE_PORTMODE               "modoPuerto"
#define LOCALIZED_ALTERNATE_PORTOPEN               "abrePuerto"
#define LOCALIZED_ALTERNATE_PORTREADARRAY          "leeCadenaPuerto"
#define LOCALIZED_ALTERNATE_PORTREADCHAR           "leeCaracterPuerto"
#define LOCALIZED_ALTERNATE_PORTWRITEARRAY         "escribeCadenaPuerto"
#define LOCALIZED_ALTERNATE_PORTWRITECHAR          "escribeCaracterPuerto"
#define LOCALIZED_ALTERNATE_POS                    "pos"
#define LOCALIZED_ALTERNATE_POSXYZ                 "pos3d"
#define LOCALIZED_ALTERNATE_POT                    "imTitulosTodo"
#define LOCALIZED_ALTERNATE_POWER                  "potencia"
#define LOCALIZED_ALTERNATE_PPROP                  "ponprop"
#define LOCALIZED_ALTERNATE_PPT                    "lNormal"
#define LOCALIZED_ALTERNATE_PR                     "es"
#define LOCALIZED_ALTERNATE_PRIMITIVEP             "primitiva?"
#define LOCALIZED_ALTERNATE_PRIMITIVE_             "primitiva?"
#define LOCALIZED_ALTERNATE_PRINT                  "escribe"
#define LOCALIZED_ALTERNATE_PROCEDUREP             "procedimiento?" // "definido?"
#define LOCALIZED_ALTERNATE_PROCEDURE_             "procedimiento?"
#define LOCALIZED_ALTERNATE_PROPLISTP              "lProp?"
#define LOCALIZED_ALTERNATE_PROPLIST_              "lProp?"
#define LOCALIZED_ALTERNATE_PROCEDURES             "lProcs"
#define LOCALIZED_ALTERNATE_PRODUCT                "producto"
#define LOCALIZED_ALTERNATE_PU                     "sl"
#define LOCALIZED_ALTERNATE_PX                     "lInvierte"
#define LOCALIZED_ALTERNATE_QUESTIONBOX            "preguntaBox"
#define LOCALIZED_ALTERNATE_QUOTIENT               "cociente"
#define LOCALIZED_ALTERNATE_RADARCCOS              "radarcCos"
#define LOCALIZED_ALTERNATE_RADARCSIN              "radarcSen"
#define LOCALIZED_ALTERNATE_RADARCTAN              "radarcTan"
#define LOCALIZED_ALTERNATE_RADCOS                 "radCos"
#define LOCALIZED_ALTERNATE_RADIOBUTTONCREATE      "creaBotonRadio"
#define LOCALIZED_ALTERNATE_RADIOBUTTONENABLE      "habilitarBotonRadio"
#define LOCALIZED_ALTERNATE_RADIOBUTTONDELETE      "borraBotonRadio"
#define LOCALIZED_ALTERNATE_RADIOBUTTONGET         "leeBotonRadio"
#define LOCALIZED_ALTERNATE_RADIOBUTTONSET         "escribeBotonRadio"
#define LOCALIZED_ALTERNATE_RADSIN                 "radSen"
#define LOCALIZED_ALTERNATE_RADTAN                 "radTan"
#define LOCALIZED_ALTERNATE_RANDOM                 "azar"
#define LOCALIZED_ALTERNATE_RAWASCII               "asciiPuro" // "ascii"
#define LOCALIZED_ALTERNATE_RC                     "lc"
#define LOCALIZED_ALTERNATE_RCS                    "lcs"
#define LOCALIZED_ALTERNATE_READCHAR               "leeCar"
#define LOCALIZED_ALTERNATE_READCHARS              "leeCarcs"
#define LOCALIZED_ALTERNATE_READER                 "lectura"
#define LOCALIZED_ALTERNATE_READLIST               "leeLista"
#define LOCALIZED_ALTERNATE_READPOS                "posLectura"
#define LOCALIZED_ALTERNATE_READWORD               "leePalabra"
#define LOCALIZED_ALTERNATE_REMAINDER              "resto"
#define LOCALIZED_ALTERNATE_REMPROP                "boProp"
#define LOCALIZED_ALTERNATE_REPCOUNT               "cuentaRepite"
#define LOCALIZED_ALTERNATE_REPEAT                 "repite"
#define LOCALIZED_ALTERNATE_RERANDOM               "reazar"
#define LOCALIZED_ALTERNATE_RIGHT                  "giraDerecha"
#define LOCALIZED_ALTERNATE_RIGHTROLL              "balanceaDerecha" // "balancea"
#define LOCALIZED_ALTERNATE_RL                     "ll"
#define LOCALIZED_ALTERNATE_RMDIR                  "eliminaDir"
#define LOCALIZED_ALTERNATE_ROLL                   "balanceo" // "balanceo?"
#define LOCALIZED_ALTERNATE_ROUND                  "redondea"
#define LOCALIZED_ALTERNATE_RR                     "bd"
#define LOCALIZED_ALTERNATE_RT                     "gd"
#define LOCALIZED_ALTERNATE_RUN                    "ejecuta"
#define LOCALIZED_ALTERNATE_RUNPARSE               "ejecutaAnaliza"
#define LOCALIZED_ALTERNATE_RUNRESULT              "resultadoEjecuta"
#define LOCALIZED_ALTERNATE_RW                     "lp"
#define LOCALIZED_ALTERNATE_SAVE                   "guarda"
#define LOCALIZED_ALTERNATE_SCREENCOLOR            "colorf"
#define LOCALIZED_ALTERNATE_SCROLLBARCREATE        "creaBarraDesplazamiento"
#define LOCALIZED_ALTERNATE_SCROLLBARENABLE        "habilitarBarraDesplazamiento"
#define LOCALIZED_ALTERNATE_SCROLLBARDELETE        "borraBarraDesplazamiento"
#define LOCALIZED_ALTERNATE_SCROLLBARGET           "leeBarraDesplazamiento"
#define LOCALIZED_ALTERNATE_SCROLLBARSET           "ponBarraDesplazamiento"
#define LOCALIZED_ALTERNATE_SCROLLX                "desplazax"
#define LOCALIZED_ALTERNATE_SCROLLY                "desplazay"
#define LOCALIZED_ALTERNATE_SCRUNCH                "ronzal"
#define LOCALIZED_ALTERNATE_SE                     "fr"
#define LOCALIZED_ALTERNATE_SELECTBOX              "seleccionBox"
#define LOCALIZED_ALTERNATE_SENTENCE               "frase"
#define LOCALIZED_ALTERNATE_SETACTIVEAREA          "ponAreaActiva"
#define LOCALIZED_ALTERNATE_SETBITINDEX            "ponIndiceBit"
#define LOCALIZED_ALTERNATE_SETBITMODE             "ponModobit"
#define LOCALIZED_ALTERNATE_SETCLIP                "ponClip"
#define LOCALIZED_ALTERNATE_SETCURSOR              "ponCursor"
#define LOCALIZED_ALTERNATE_SETCURSORNOWAIT        "setCursorNoEspera"
#define LOCALIZED_ALTERNATE_SETCURSORWAIT          "ponCursorEspera"
#define LOCALIZED_ALTERNATE_SETFC                  "poncr"
#define LOCALIZED_ALTERNATE_SETFLOODCOLOR          "ponColorRelleno"
#define LOCALIZED_ALTERNATE_SETFOCUS               "ponFoco"
#define LOCALIZED_ALTERNATE_SETH                   "ponr"
#define LOCALIZED_ALTERNATE_SETHEADING             "ponRumbo"
#define LOCALIZED_ALTERNATE_SETITEM                "ponElemento"
#define LOCALIZED_ALTERNATE_SETLABELFONT           "ponTipo"
#define LOCALIZED_ALTERNATE_SETLIGHT               "ponLuz"
#define LOCALIZED_ALTERNATE_SETMARGINS             "ponMargenes"
#define LOCALIZED_ALTERNATE_SETPC                  "ponCL"
#define LOCALIZED_ALTERNATE_SETPENCOLOR            "ponColorLapiz"
#define LOCALIZED_ALTERNATE_SETPENPATTERN          "ponPatronLapiz"
#define LOCALIZED_ALTERNATE_SETPENSIZE             "ponGrosor"
#define LOCALIZED_ALTERNATE_SETPITCH               "ponCabeceo"
#define LOCALIZED_ALTERNATE_SETPIXEL               "ponPixel"
#define LOCALIZED_ALTERNATE_SETPOS                 "ponPos"
#define LOCALIZED_ALTERNATE_SETPOSXYZ              "posicionate"
#define LOCALIZED_ALTERNATE_SETREAD                "ponLectura"
#define LOCALIZED_ALTERNATE_SETREADPOS             "ponPosLectura"
#define LOCALIZED_ALTERNATE_SETROLL                "ponBalanceo"
#define LOCALIZED_ALTERNATE_SETSC                  "ponCF"
#define LOCALIZED_ALTERNATE_SETSCREENCOLOR         "ponColorFondo"
#define LOCALIZED_ALTERNATE_SETSCRUNCH             "ponRonzal"
#define LOCALIZED_ALTERNATE_SETTIMER               "ponTemporizador" // "poncontador"
#define LOCALIZED_ALTERNATE_SETTURTLE              "activa"
#define LOCALIZED_ALTERNATE_SETTURTLEMODE          "ponModoTortuga"
#define LOCALIZED_ALTERNATE_SETWRITE               "ponEscritura"
#define LOCALIZED_ALTERNATE_SETWRITEPOS            "ponPosEscritura"
#define LOCALIZED_ALTERNATE_SETX                   "ponx"
#define LOCALIZED_ALTERNATE_SETXY                  "ponxy"
#define LOCALIZED_ALTERNATE_SETXYZ                 "ponxyz"
#define LOCALIZED_ALTERNATE_SETY                   "pony"
#define LOCALIZED_ALTERNATE_SETZ                   "ponz"
#define LOCALIZED_ALTERNATE_SHELL                  "shell"
#define LOCALIZED_ALTERNATE_SHOW                   "muestra"
#define LOCALIZED_ALTERNATE_SHOWNP                 "visible?"
#define LOCALIZED_ALTERNATE_SHOWN_                 "visible?"
#define LOCALIZED_ALTERNATE_SHOWTURTLE             "muestraTortuga"
#define LOCALIZED_ALTERNATE_SIN                    "sen"
#define LOCALIZED_ALTERNATE_SOUND                  "tono"
#define LOCALIZED_ALTERNATE_SPLITSCREEN            "pantallaPartida"
#define LOCALIZED_ALTERNATE_SQRT                   "rc"
#define LOCALIZED_ALTERNATE_SS                     "pa"
#define LOCALIZED_ALTERNATE_ST                     "muestraTortuga"
#define LOCALIZED_ALTERNATE_STANDOUT               "standout"
#define LOCALIZED_ALTERNATE_STATICCREATE           "creaEstatico"
#define LOCALIZED_ALTERNATE_STATICDELETE           "borraEstatico"
#define LOCALIZED_ALTERNATE_STATICUPDATE           "actualizaEstatico"
#define LOCALIZED_ALTERNATE_STATUS                 "estado"
#define LOCALIZED_ALTERNATE_STEP                   "paso"
#define LOCALIZED_ALTERNATE_STEPPED                "procs.paso"
#define LOCALIZED_ALTERNATE_STOP                   "alto"
#define LOCALIZED_ALTERNATE_SUBSTRINGP             "contiene?"
#define LOCALIZED_ALTERNATE_SUBSTRING_             "contiene?"
#define LOCALIZED_ALTERNATE_SUM                    "adicion"
#define LOCALIZED_ALTERNATE_TAG                    "etiqueta"
#define LOCALIZED_ALTERNATE_TAN                    "tan"
#define LOCALIZED_ALTERNATE_TEST                   "prueba"
#define LOCALIZED_ALTERNATE_TEXT                   "texto"
#define LOCALIZED_ALTERNATE_TEXTSCREEN             "pantallaTexto"
#define LOCALIZED_ALTERNATE_THING                  "valor"
#define LOCALIZED_ALTERNATE_THROW                  "lanza" // "envia"
#define LOCALIZED_ALTERNATE_TIME                   "hora"
#define LOCALIZED_ALTERNATE_TIMEMILLI              "horaMili"
#define LOCALIZED_ALTERNATE_TO                     "para"
#define LOCALIZED_ALTERNATE_TONE                   "tono"
#define LOCALIZED_ALTERNATE_TOWARDS                "hacia"
#define LOCALIZED_ALTERNATE_TOWARDSXYZ             "haciaxyz"
#define LOCALIZED_ALTERNATE_TRACE                  "traza"
#define LOCALIZED_ALTERNATE_TRACED                 "trazados"
#define LOCALIZED_ALTERNATE_TS                     "pt"
#define LOCALIZED_ALTERNATE_TURTLE                 "quien"
#define LOCALIZED_ALTERNATE_TURTLEMODE             "modoTortuga"
#define LOCALIZED_ALTERNATE_TURTLES                "tortugas"
#define LOCALIZED_ALTERNATE_TYPE                   "muestrat"
#define LOCALIZED_ALTERNATE_UNBURY                 "destapa"
#define LOCALIZED_ALTERNATE_UNSTEP                 "noPaso"
#define LOCALIZED_ALTERNATE_UNTRACE                "noTraza"
#define LOCALIZED_ALTERNATE_UP                     "arriba"
#define LOCALIZED_ALTERNATE_UPPERCASE              "mayusculas"
#define LOCALIZED_ALTERNATE_UPPITCH                "cabecea"
#define LOCALIZED_ALTERNATE_WAIT                   "espera"
#define LOCALIZED_ALTERNATE_WINDOW                 "modoVentana"
#define LOCALIZED_ALTERNATE_WINDOWCREATE           "creaVentana"
#define LOCALIZED_ALTERNATE_WINDOWENABLE           "habilitarVentana"
#define LOCALIZED_ALTERNATE_WINDOWDELETE           "borraVentana"
#define LOCALIZED_ALTERNATE_WINDOWFILEEDIT         "editaArchivo" // "editafichero"
#define LOCALIZED_ALTERNATE_WINDOWSET              "activaVentana"
#define LOCALIZED_ALTERNATE_WINHELP                "ayudaDeWindows"
#define LOCALIZED_ALTERNATE_WORD                   "palabra"
#define LOCALIZED_ALTERNATE_WORDP                  "palabra?"
#define LOCALIZED_ALTERNATE_WORD_                  "palabra?"
#define LOCALIZED_ALTERNATE_WRAP                   "modoVuelta"
#define LOCALIZED_ALTERNATE_WRITEPOS               "posLectura"
#define LOCALIZED_ALTERNATE_WRITER                 "escritura"
#define LOCALIZED_ALTERNATE_YESNOBOX               "siNoBox"
#define LOCALIZED_ALTERNATE_YIELD                  "noExclusivo"
#define LOCALIZED_ALTERNATE_ZOOM                   "ponLupa"

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      "&OK"
#define LOCALIZED_GENERAL_CANCELBUTTON  "&Cancelar"

#define LOCALIZED_GENERAL_PRODUCTNAME   "FMSLogo"



//
// The menu options on the main window 
//
#define LOCALIZED_FILE        "&Archivo"
#define LOCALIZED_FILE_NEW    "&Nuevo\t(borra el trabajo actual)"
#define LOCALIZED_FILE_LOAD   "&Cargar...\t(une al trabajo actual)"
#define LOCALIZED_FILE_OPEN   "A&brir...\t(remplaza el trabajo actual)"
#define LOCALIZED_FILE_SAVE   "&Guardar"
#define LOCALIZED_FILE_SAVEAS "G&uardar como..."
#define LOCALIZED_FILE_EDIT   "&Editar..."
#define LOCALIZED_FILE_ERASE  "&Borrar..."
#define LOCALIZED_FILE_EXIT   "&Salir"

#define LOCALIZED_BITMAP               "&Bitmap"
#define LOCALIZED_BITMAP_NEW           "&Nuevo"
#define LOCALIZED_BITMAP_LOAD          "&Cargar..."
#define LOCALIZED_BITMAP_SAVE          "&Guardar"
#define LOCALIZED_BITMAP_SAVEAS        "G&uardar como..."
#define LOCALIZED_BITMAP_PRINT         "&Imprimir..."
#define LOCALIZED_BITMAP_PRINTERSETUP  "C&onfigurar impresora..."
#define LOCALIZED_BITMAP_ACTIVEAREA    "&Area Activa..."

#define LOCALIZED_SET                  "&Configurar"
#define LOCALIZED_SET_PENSIZE          "&Tamaño del lápiz..."
#define LOCALIZED_SET_LABELFONT        "Tipo de letra de &rotulador..."
#define LOCALIZED_SET_COMMANDERFONT    "Tipo de letra &comandos..."
#define LOCALIZED_SET_PENCOLOR         "Color de &lápiz..."
#define LOCALIZED_SET_FLOODCOLOR       "Color de r&elleno..."
#define LOCALIZED_SET_SCREENCOLOR      "Color de &fondo..."

#define LOCALIZED_ZOOM                 "&Zoom"
#define LOCALIZED_ZOOM_IN              "&Acercar"
#define LOCALIZED_ZOOM_OUT             "A&lejar"
#define LOCALIZED_ZOOM_NORMAL          "&Normal"

#define LOCALIZED_HELP                 "A&yuda"
#define LOCALIZED_HELP_INDEX           "&Indice"
#define LOCALIZED_HELP_MCI             "&MCI"
#define LOCALIZED_HELP_HELP            "&Uso de la ayuda"
#define LOCALIZED_HELP_TUTORIAL        "&Tutorial"
#define LOCALIZED_HELP_DEMO            "&Demostracion"
#define LOCALIZED_HELP_EXAMPLE         "&Ejemplos"
#define LOCALIZED_HELP_RELEASENOTES    "&Notas de la version"
#define LOCALIZED_HELP_ABOUTFMSLOGO    "&Acerca de "LOCALIZED_GENERAL_PRODUCTNAME"..."
#define LOCALIZED_HELP_MS              "Acerca de &FMS..."
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   "Español a Inglés"
#define LOCALIZED_HELP_ENGLISHTOLANG   "Inglés a Español"

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              "Seleccionar área activa"
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       "Esto afecta la impresión y grabación de bitmaps"
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        "Y-Sup"
#define LOCALIZED_SELECTACTIVEAREA_YLOW         "Y-Inf"
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        "X-Sup"
#define LOCALIZED_SELECTACTIVEAREA_XLOW         "X-Inf"
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH "Puntos por pulgada impresa:"
#define LOCALIZED_SELECTACTIVEAREA_RESET        "&Reset"
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON


//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     "Copiar"
#define LOCALIZED_POPUP_CUT                      "Cortar"
#define LOCALIZED_POPUP_PASTE                    "Pegar"
#define LOCALIZED_POPUP_DELETE                   "Borrar"
#define LOCALIZED_POPUP_UNDO                     "Deshacer"
#define LOCALIZED_POPUP_SELECTALL                "Seleccionar Todo"
#define LOCALIZED_POPUP_HELP                     "Búsqueda por Tema"

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   "Editor"

#define LOCALIZED_EDITOR_FILE                    "&Archivo"
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        "&Guardar y Salir\tCtrl+D"
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    "Guardar en &área de trabajo"
#define LOCALIZED_EDITOR_FILE_PRINT              "&Imprimir..."
#define LOCALIZED_EDITOR_FILE_EXIT               "&Salir"

#define LOCALIZED_EDITOR_EDIT                    "&Edit"
#define LOCALIZED_EDITOR_EDIT_UNDO               "&Deshacer\tCtrl+Z"
#define LOCALIZED_EDITOR_EDIT_CUT                "&Cortar\tCtrl+X"
#define LOCALIZED_EDITOR_EDIT_COPY               "C&opiar\tCtrl+C"
#define LOCALIZED_EDITOR_EDIT_PASTE              "&Pegar\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_DELETE             "&Borrar\tDel"
#define LOCALIZED_EDITOR_EDIT_CLEARALL           "Borrar &todo\tCtrl+Del"
#define LOCALIZED_EDITOR_EDIT_SELECTALL          "&Seleccionar Todo\tCtrl+A"

#define LOCALIZED_EDITOR_SEARCH                  "&Buscar"
#define LOCALIZED_EDITOR_SEARCH_FIND             "&Encontrar...\tCtrl+F"
#define LOCALIZED_EDITOR_SEARCH_REPLACE          "&Remplazar...\tCtrl+H"
#define LOCALIZED_EDITOR_SEARCH_NEXT             "&Siguiente\tF3"

#define LOCALIZED_EDITOR_SET                     "&Configurar"
#define LOCALIZED_EDITOR_SET_FONT                "&Tipo de letra..."

#define LOCALIZED_EDITOR_TEST                    "&Probar!"

#define LOCALIZED_EDITOR_HELP                    "A&yuda"
#define LOCALIZED_EDITOR_HELP_INDEX              "&Indice"
#define LOCALIZED_EDITOR_HELP_EDITOR             "&Editor"
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        "&Busqueda por tema\tF1"


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    "&Guardar y Salir"
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       "&No guardar"
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       "Hay cambios no guardados en tu espacio de trabajo. Si sales sin guardar, estos cambios se perderán."
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       "¿Deseas guardar tus cambios antes de salir?"


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     "Centro de Comandos"
#define LOCALIZED_COMMANDER_HALT                "Alto"
#define LOCALIZED_COMMANDER_TRACE               "Trazar"
#define LOCALIZED_COMMANDER_NOTRACE             "NoTrazar"
#define LOCALIZED_COMMANDER_PAUSE               "Pausa"
#define LOCALIZED_COMMANDER_STATUS              "Estado"
#define LOCALIZED_COMMANDER_NOSTATUS            "NoEstado"
#define LOCALIZED_COMMANDER_STEP                "Paso"
#define LOCALIZED_COMMANDER_UNSTEP              "NoPaso"
#define LOCALIZED_COMMANDER_RESET               "Reiniciar"
#define LOCALIZED_COMMANDER_EXECUTE             "Ejecutar"
#define LOCALIZED_COMMANDER_EDALL               "EdTodo"

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        "Estado"
#define LOCALIZED_STATUS_PEN                    "Lápiz"
#define LOCALIZED_STATUS_CONTACT                "Contacto:"
#define LOCALIZED_STATUS_WIDTH                  "Ancho:"
#define LOCALIZED_STATUS_STYLE                  "Estilo:"
#define LOCALIZED_STATUS_ORIENTATION            "Orientación"
#define LOCALIZED_STATUS_PITCH                  "Cabeceo:"
#define LOCALIZED_STATUS_HEADING                "Rumbo:"
#define LOCALIZED_STATUS_ROLL                   "Balanceo:"
#define LOCALIZED_STATUS_TURTLE                 "Tortuga"
#define LOCALIZED_STATUS_POSITION               "Posición(XYZ):"
#define LOCALIZED_STATUS_WHICH                  "Cuál:"
#define LOCALIZED_STATUS_VISIBILITY             "Visibilidad:"
#define LOCALIZED_STATUS_COLOR                  "Color"
#define LOCALIZED_STATUS_PENCOLOR               "Lápiz(RGB):"
#define LOCALIZED_STATUS_FLOODCOLOR             "Relleno(RGB):"
#define LOCALIZED_STATUS_SCREENCOLOR            "Fondo(RGB):"
#define LOCALIZED_STATUS_PALETTE                "Paleta usada:"
#define LOCALIZED_STATUS_KERNEL                 "Núcleo"
#define LOCALIZED_STATUS_CALLS                  "Llamadas:"
#define LOCALIZED_STATUS_PEAKMEMORY             "Memoria Pico:"

#define LOCALIZED_STATUS_PENREVERSE  "LapizInvierte"
#define LOCALIZED_STATUS_PENNORMAL   "LapizNormal"
#define LOCALIZED_STATUS_PENERASE    "Goma"
#define LOCALIZED_STATUS_PENUP       "Arriba"
#define LOCALIZED_STATUS_PENDOWN     "Abajo"
#define LOCALIZED_STATUS_PENSHOWN    "Mostrada"
#define LOCALIZED_STATUS_PENHIDDEN   "Oculta"
#define LOCALIZED_STATUS_POLYGONS    "Polígonos"
#define LOCALIZED_STATUS_VECTORS     "Vectores"
#define LOCALIZED_STATUS_NODES       "Nodos"

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           "&Todo"
#define LOCALIZED_ERASEPROCEDURE                "Borrar"
#define LOCALIZED_EDITPROCEDURE                 "Editar"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     "Poner Color"
#define LOCALIZED_SETCOLOR_PENCOLOR            "Color de Lápiz"
#define LOCALIZED_SETCOLOR_FLOODCOLOR          "Color de Relleno"
#define LOCALIZED_SETCOLOR_SCREENCOLOR         "Color de Fondo"
#define LOCALIZED_SETCOLOR_RED                 "Rojo"
#define LOCALIZED_SETCOLOR_GREEN               "Verde"
#define LOCALIZED_SETCOLOR_BLUE                "Azúl"
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   "Tamaño de Lápiz"
#define LOCALIZED_SETPENSIZE_SIZE              "Grosor"
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     "Acerca de "LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_ABOUTFMS_VERSION             LOCALIZED_GENERAL_PRODUCTNAME" Versión "FMSLOGO_VERSION
#define LOCALIZED_ABOUTFMS_GUI                 "GUI por George Mills (mills@softronix.com)\nSoftronics, Inc.\nhttp:\x2F/www.softronix.com/"
#define LOCALIZED_ABOUTFMS_CORE                "Núcleo por Brian Harvey (bh@eecs.berkeley.edu)\nUniversity of California Berkeley"
#define LOCALIZED_ABOUTFMS_INSTALLER           "Instalador basado en el Nullsoft Scriptable Install System\nhttp:\x2F/nsis.sourceforge.net/"
#define LOCALIZED_ABOUTFMS_ADVENTURE           "Recursos para Logo en Español\nDisponibles en http:\x2F/mondragon.angeltowns.net/paradiso/"
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       "Gracias a Yehuda Katz (yehuka@softhome.net)\n y a Erich Neuwirth (erich.neuwirth@univie.ac.at)"
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME" es software libre\nVer la Licencia Pública de GNU"
#define LOCALIZED_ABOUTFMS_NEWSGROUP           "¿Preguntas, comentarios, sugerencias?\nParticipa en la lista de Logo\nhttp:\x2F/mondragon.angeltowns.net/paradiso/ListaLogo.html"
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     "Traducción hecha por Daniel Ajoy"
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      "Acerca de FMS"
#define LOCALIZED_ABOUTMS_FMS                  "FMS quiere decir Fight Multiple Sclerosis."
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     "Considera hacer una donación a la\nNational Multiple Sclerosis Society.\nhttp:\x2F/www.nmss.org\n1-800-FIGHT-MS"
#define LOCALIZED_ABOUTMS_OK                   LOCALIZED_GENERAL_OKBUTTON


// 
// Strings in various other dialog boxes
// 

#define LOCALIZED_CHANGESINEDITORMAYBELOST  "Los cambios de la edición pueden perderse.\n\n¿Realmente quieres salir de "LOCALIZED_GENERAL_PRODUCTNAME"?"
#define LOCALIZED_EDITSESSIONISRUNNING      "Una sesión de edición está activa"

#define LOCALIZED_NOTHALTEDREALLYEXIT        LOCALIZED_GENERAL_PRODUCTNAME" no puede salir hasta estar parado.\n\n¿Realmente quieres salir de "LOCALIZED_GENERAL_PRODUCTNAME"?"
#define LOCALIZED_NOTHALTEDREALLYHALT        LOCALIZED_GENERAL_PRODUCTNAME" no puede salir hasta estar parado.\n\nDo you really want to Halt "LOCALIZED_GENERAL_PRODUCTNAME"?"
#define LOCALIZED_LOGOISNOTHALTED            LOCALIZED_GENERAL_PRODUCTNAME" no está parado"

#define LOCALIZED_WRITEFAILEDNOMEMORY         "Fallo de escritura, posible falta de memoria"
#define LOCALIZED_COULDNOTWRITEBMP            "No puedo guardar .bmp"
#define LOCALIZED_COULDNOTOPENBMP             "No puedo abrir .bmp"
#define LOCALIZED_COULDNOTCREATEBMP           "No puedo crear bitmat tipo Windows 3.0"
#define LOCALIZED_NOTVALIDBMP                 "No es un bitmap tipo Windows 3.0"

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         "Nos haz guardado a disco"
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     "Escoger Nuevo borrará todas las definiciones.\n\n¿Continuar con Nuevo?"
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE "El archivo que está siendo cargado será unido a tu trabajo actual\ny reemplazará tus cambios no guardados.\n\n¿Continuar con Cargar?"
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    "Esto borrará todos tus cambios no guardados.\n\n¿Continuar con Abrir?"

#define LOCALIZED_EDITORISOPEN                  "¿Sabes que tienes una sesión de edición activa?\n\nTodo cambio en esta sesión de edición no será guardado."

#define LOCALIZED_ERROR_CANTREADFILE            "No puedo leer el archivo \"%s\" desde disco"
#define LOCALIZED_ERROR_CANTWRITEFILE           "No puedo escribir el archivo \"%s\" a disco"

#define LOCALIZED_SAVEISFOREXPERTSONLY          "Esta característica es sólo para modo experto (usa "LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT")"
#define LOCALIZED_SAVETOWORKSPACE                "Guardar al área de trabajo"
#define LOCALIZED_CONTENTSCHANGED                "El contenido cambió"
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE "El contenido cambió.\n¿Deseas guardar los cambios al área de trabajo?"



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  "Hubo un error al guardar el contenido de editor en el área de trabajo.  El cursor se situará tras la última definición correcta.\n\nBusca un posible mensaje de error en el Area de Comandos."
#define LOCALIZED_RETURNTOEDIT                  "¿Regresar al editor?"

#define LOCALIZED_EDITFAILEDTOLOAD              LOCALIZED_SAVETOWORKSPACE



// 
//  Strings used in the File-Open filters
//
#define LOCALIZED_FILEFILTER_ALLFILES "Todos los Archivos (*.*)|*.*|"
#define LOCALIZED_FILEFILTER_LOGO     "Archivos de Logo (*.lgo)|*.lgo|"LOCALIZED_FILEFILTER_ALLFILES
#define LOCALIZED_FILEFILTER_IMAGE    "Archivos Bitmap (*.bmp)|*.bmp|Archivos GIF (*.gif)|*.gif|"LOCALIZED_FILEFILTER_ALLFILES



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             " se detuvo\n"
#define LOCALIZED_TRACING_OUTPUTS           " devuelve %s\n"
#define LOCALIZED_TRACING_MAKE              "HAZ %s %s"
#define LOCALIZED_TRACING_PPROP             "PONPROP %s %s %s"
#define LOCALIZED_TRACING_LOCATION          " en %s\n%s"

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  "Paso Simple"

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  "%s definido\n"


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    "Goma"
#define LOCALIZED_PENMODE_REVERSE  "LapizInvierte"
#define LOCALIZED_PENMODE_PAINT    "LapizNormal"

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          "Logo: Error Interno Fatal"
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       "Logo: Falta de Memoria"
#define LOCALIZED_ERROR_OUTOFMEMORY            "no hay espacio"
#define LOCALIZED_ERROR_STACKOVERFLOW          "desborde de pila"
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      "tortuga fuera de los límites"
#define LOCALIZED_ERROR_BADGRAPHINIT           "no pude inicializar gráficas"
#define LOCALIZED_ERROR_BADDATA                "a %p no le gustó recibir %s"
#define LOCALIZED_ERROR_DIDNTOUTPUT            "%p no devolvió nada a %p"
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        "%p necesita recibir más cosas"
#define LOCALIZED_ERROR_TOOMUCH                "demasiadas cosas entre paréntesis ()"
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    "No dices qué debo hacer con %s"
#define LOCALIZED_ERROR_PARENMISMATCH          "demasiados paréntesis '('"
#define LOCALIZED_ERROR_NOVALUE                "%s no tiene un valor todavía"
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        "paréntesis ')' inesperado"
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      "corchete ']' inesperado"
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        "llave '}' inesperada"
#define LOCALIZED_ERROR_DONTKNOWHOWTO          "no sé cómo realizar %p"
#define LOCALIZED_ERROR_NOCATCHTAG             "no puedo encontrar la etiqueta LANZA (THROW) para %p"
#define LOCALIZED_ERROR_ALREADYDEFINED         "%p ya está definido"
#define LOCALIZED_ERROR_STOPPING               "Parando..."
#define LOCALIZED_ERROR_ALREADYDRIBBLING       "ECO está activado"
#define LOCALIZED_ERROR_FILESYSTEM                   "Error del sistema de archivos: %p"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          "No puedo abrir ese archivo"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         "No puedo abrir ese archivo: %t"
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       "Archivo ya está abierto"
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           "Archivo no está abierto"
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  "No pude crear archivo para editor"
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   "No pude iniciar editor"
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    "No pude leer archivo de editor"
#define LOCALIZED_ERROR_IFWARNING              "Asumo que querías decir SISINO (IFELSE), no SI (IF)"
#define LOCALIZED_ERROR_SHADOWWARNING          "%p cubierta por local en llamada a procedimiento"
#define LOCALIZED_ERROR_USER                   "ATRAPA \"Error"
#define LOCALIZED_ERROR_ISPRIMITIVE            "%p es una primitiva"
#define LOCALIZED_ERROR_TONOTINSIDE            "No puedes usar PARA (TO) dentro de un procedimiento"
#define LOCALIZED_ERROR_ATTOPLEVEL             "Solo puedes usar %p dentro de un procedimiento"
#define LOCALIZED_ERROR_ATTOPLEVEL2            "Debes estar dentro de un procedimiento para usar DEVUELVE (OUTPUT) o ALTO (STOP)."
#define LOCALIZED_ERROR_NOTEST                 "%p sin PRUEBA (TEST)"
#define LOCALIZED_ERROR_BADMACROOUTPUT         "Macro devolvió %s en lugar de una lista"
#define LOCALIZED_ERROR_DEEPEND                "FIN (END) dentro de una instrucción multi-línea"
#define LOCALIZED_ERROR_DEEPENDIN              "FIN (END) dentro de una instrucción multi-línea en %p"
#define LOCALIZED_ERROR_UNKNOWN                "Estado de error desconocido  - error interno."

#define LOCALIZED_PAUSING                      "Pausando..."


//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      "Error"
#define LOCALIZED_ERROR_BADINPUT             "Entrada incorrecta"
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    "La entrada no tiene pareja"

#define LOCALIZED_ERROR_CANTOPENPORT         "No se puede abrir el PUERTO"
#define LOCALIZED_ERROR_CANTCLOSEPORT        "No se puede CERRAR el puerto"
#define LOCALIZED_ERROR_CANTFLUSHPORT        "No se pudo vaciar el PUERTO"
#define LOCALIZED_ERROR_CANTDCBONPORT        "No se puede construir dcb en el PUERTO"
#define LOCALIZED_ERROR_CANTSETPORT          "No se puede poner el PUERTO"
#define LOCALIZED_ERROR_PORTALREADYOPEN      "PUERTO ya abierto"
#define LOCALIZED_ERROR_PORTNOTOPEN          "PUERTO no abierto"
#define LOCALIZED_ERROR_FIRSTINPUTNOTANARRY  "El primer parámetro debe ser un vector"

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   "Ya existe"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    "No existe"

#define LOCALIZED_ERROR_DLL                   "Error en DLL"
#define LOCALIZED_ERROR_DLLNOTLOADED          "La DLL no está cargada"
#define LOCALIZED_ERROR_DLLALREADYLOADED      "La DLL ya fue cargada"
#define LOCALIZED_ERROR_DLLLOADFAILED         "Falló la carga de la DLL"
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    "Tipo de dato de la entrada inválido"
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  "Tipo de dato de retorno inválido"
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   "Función no encontrada"
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  "No coincide los tipos de datos"

#define LOCALIZED_ERROR_NETWORK                    "Error de Red"
#define LOCALIZED_ERROR_NETWORKRECEIVE             "Error de Recepción de Red"
#define LOCALIZED_ERROR_NETWORKSEND                "Error de Envío de Red"
#define LOCALIZED_ERROR_NETWORKSHUTDOWN            "Error Inesperado, la Red podría estar inactiva"
#define LOCALIZED_ERROR_NETWORKNOTSTARTED          "Not started"
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED      "Ya está activa"
#define LOCALIZED_ERROR_NETWORKALREADYON           "Ya está encendida"
#define LOCALIZED_ERROR_NETWORKALREADYOFF          "Ya está apagada"

// The rest of the network errors shouldn't really see -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         "Nombre Demasiado largo"
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      "No inicializado"
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      "El sistema no está listo"
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED "Versión desconocida"
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   "No puedo enviar después de desactivación de socket"
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         "Llamada al sistema interrumpida"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    "Respuesta Autoritativa: Dominio no encontrado"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH "No-Autoritativa: Dominio no encontrado. Ver INICIARED"
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      "Error sin posible recuperación"
#define LOCALIZED_ERROR_NETWORKNODATA              "Registro de datos no disponible"
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       "Número de archivo incorrecto"
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          "La operación bloquearía"
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       "Operación en progreso ahora"
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   "Operación ya en progreso"
#define LOCALIZED_ERROR_NETWORKBADADDRESS          "Dirección incorrecta"
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     "Necesito dirección de destino"
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      "Mensaje demasiado largo"
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      "Familia del protocolo desconocida"
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         "El directorio no está vacío"
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     "Se ha alcanzado el límite de la aplicación"
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           "Se ha excedido la cuota de disco"
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        "Demasiados archivos abiertos"
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        "Accesso negado"
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          "Operación de socket en algo que no es un socket"
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    "No puedo asignar dirección pedida"
#define LOCALIZED_ERROR_NETWORKADDRINUSE           "La dirección ya está en uso"
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      "La familia de la dirección no es conocida por la familia del protocolo"
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            "Tiempo de intento de conexión excedido"
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    "Tipo de socket desconocido"
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   "Protocolo desconocido"
#define LOCALIZED_ERROR_NETWORKNOBUFFER            "No hay espacio en memoria temporal"
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    "El socket ya está conectado"
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        "El socket no está conectado"
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         "Opción de protocolo incorrecta"
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     "Conexión reiniciada por interlocutor"
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     "El software ocasionó el cierre de la conexión"
#define LOCALIZED_ERROR_NETWORKISDOWN              "La red está caída"
#define LOCALIZED_ERROR_NETWORKRESET               "La red fue reiniciada"
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   "Conexión rechazada"
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          "Dominio está caido"
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   "Dominio inalcanzable"
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        "El protocolo es del tipo equivocado para el socket"
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   "Operación no permitida en el socket"
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         "No se encontró ruta al dominio remoto"
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         "Demasiadas referencias"

#define LOCALIZED_ERROR_POLYSTART               "Error en EmpiezaPoligono"
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED "Ya tienes un polígono empezado"

#define LOCALIZED_ERROR_POLYEND                 "Error en TerminaPoligono"
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       "No haz empezado un polígono"
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     "Debes tener al menos 3 vectores para definir un polígono"

#define LOCALIZED_ERROR_SOUND                 "Error de Sonido"

#define LOCALIZED_ERROR_MIDI                  "Error de MIDI"
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     "Dispositivo Midi incorrecto"
#define LOCALIZED_ERROR_MIDIALREADYOPEN       "Ya está abierto"
#define LOCALIZED_ERROR_MIDINOTOPEN           "No está abierto"

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      "No hay texto en el portapapeles"

#define LOCALIZED_ERROR_MCI                   "Error de MCI"

#define LOCALIZED_ERROR_TIMERTOOMANY          "Demasiados temporizadores"
#define LOCALIZED_ERROR_TIMERBADID            "Identificador de temporizador incorrecto"
#define LOCALIZED_ERROR_TIMERNOTFOUND         "Temporizador no encontrado"

#define LOCALIZED_ERROR_BITMODEBADBITMODE     "ModoBitmap incorrecto"

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       "Ayuda en línea no disponible porque no se pudo cargar hhctrl.ocx"
#define LOCALIZED_ERROR_HHCTRLATOMNOTFOUND    "Ayuda en línea no disponible porque hhctrl.ocx no contiene ATOM_HTMLHELP_API_ANSI"

#define LOCALIZED_ERROR_BADCOMMANDLINE        "Línea de comandos incorrecta"

#define LOCALIZED_ERROR_TMPNOTDEFINED         "La variable de ambiente TMP no está definida o es incorrecta.\n"LOCALIZED_GENERAL_PRODUCTNAME" intentará utilizar C:\\ para guardar archivos temporales"

#define LOCALIZED_ERROR_GIFSAVEFAILED         "Problema al generar GIF, revisa cantidad de memoria o espacio en disco"
#define LOCALIZED_ERROR_GIFREADFAILED         "Problema al leer GIF, revisa memoria o espacio en disco"

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  "Indice de BitMap fuera de rango"
#define LOCALIZED_ERROR_BITMAPCUTFAILED        "Cortar falló, posiblemente no hay memoria"
#define LOCALIZED_ERROR_BITMAPFITFAILED        "Ajustar falló, posiblemente no hay memoria"

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    "Nada para Pegar"
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  "El BitMap en índice debe ser inicializado con un mapa de bits"

#define LOCALIZED_ERROR_BADTURTLEID             "Identificador de Tortuga incorrecto"
#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      "La tortuga %d no tiene figura, realizaré un Alto"

#define LOCALIZED_ERROR_FONTNOTFOUND            "No encontré el tipo de letra llamado %s. Elige uno de lo siguientes:\n"

#define LOCALIZED_ERROR_PRINTERCANTSCALE        "El manejador de impresión no conoce esta función"
#define LOCALIZED_ERROR_CANTDRAWIMAGE           "No puedo dibujar la imagen"
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        "No pueda extraer la imagen"
#define LOCALIZED_ERROR_SUBCODE                 "Sub Código"

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         "Entrada:"
#define LOCALIZED_PROMPT_TO     "Modo Para (Cancel para Finalizar)"
#define LOCALIZED_PROMPT_LIST   "Modo de Lista (Cancel para Alto)"
#define LOCALIZED_PROMPT_PAUSE  "Modo de Pausa (Cancel para Continuar)"
#define LOCALIZED_PROMPT_INPUT  "Modo de Entrada (Cancel para Alto)"

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      "Cambiado a  \"%s\""
#define LOCALIZED_FILE_CHDIRFAILED         "No pude cambiar a directorio \"%s\""
#define LOCALIZED_FILE_POPPEDTO            "Cambiado a \"%s\""
#define LOCALIZED_FILE_MKDIRSUCCEEDED      "Ahora estamos en el nuevo directorio creado \"%s\""
#define LOCALIZED_FILE_MKDIRFAILED         "No pude crear directorio \"%s\""
#define LOCALIZED_FILE_RMDIRSUCCEEDED      "Directorio Eliminado \"%s\""
#define LOCALIZED_FILE_RMDIRFAILED         "No pude eliminar directorio \"%s\""
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  "El directorio no existe"
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY "Asegúrate que el directorio esté vacío antes de eliminarlo."


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       "Dibujo en Logo"

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    "Area Activa"
#define LOCALIZED_INFORMATION   "Información"
#define LOCALIZED_WARNING       "Atención"
#define LOCALIZED_UNTITLED      "Sin nombre"
#define LOCALIZED_UNKNOWN       "Desconocido"

#define LOCALIZED_UNBOUND       "No acotado"

//
// Strings that explain the purpose of each menu option.
// I don't think that any of these strings can be seen by the user, 
// so you probably don't have to translate these.
//
#define LOCALIZED_STRINGTABLE_FILESAVEAS "Saves the contents of the workspace to a new file" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILEOPEN "Erases the current workspace and loads a Logo program as the new workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILELOAD "Locates and loads a Logo program into the current workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILENEW "Erases the contents of the workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILESAVE "Saves the contents of the workspace" // NOT_YET_LOCALIZED
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
#define LOCALIZED_STRINGTABLE_EDITSETFONT "Sets the font for the editor window" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_TEST "Runs the selected Logo instructions" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPEDIT "Displays help on using the editor" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_HELPEDIT_TOPIC "Displays help for Logo" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILESAVEANDEXIT "Saves and exits the current workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILESAVETOWORKSPACE "Saves the current workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_FILEPRINT "Prints the current workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_STRINGTABLE_EDALLEXIT "Closes the workspace" // NOT_YET_LOCALIZED

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING "%s no encontrado"


//
// The words that describe color vectors.
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
