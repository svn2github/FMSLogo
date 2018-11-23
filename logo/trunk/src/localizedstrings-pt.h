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
// This file contains localized strings for Portuguese by Alexandre R Soares
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
#define LOCALIZED_ALTERNATE_TRUE     "verd"
#define LOCALIZED_ALTERNATE_FALSE    "falso"
#define LOCALIZED_ALTERNATE_END      "fim"
#define LOCALIZED_ALTERNATE_TOPLEVEL "nívelacima"
#define LOCALIZED_ALTERNATE_SYSTEM   "sistema"

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
#define LOCALIZED_ALTERNATE__DEFMACRO              ".defMacro"
#define LOCALIZED_ALTERNATE__EQ                    ".ig"
#define LOCALIZED_ALTERNATE__MACRO                 ".macro"
#define LOCALIZED_ALTERNATE__MAYBEOUTPUT           ".talvezDevolva"
#define LOCALIZED_ALTERNATE__SETBF                 ".mudeÚltimos"
#define LOCALIZED_ALTERNATE__SETFIRST              ".mudePrimeiro"
#define LOCALIZED_ALTERNATE__SETITEM               ".mudeItem"
#define LOCALIZED_ALTERNATE_ACTIVEAREA             "áreaAtiva"
#define LOCALIZED_ALTERNATE_ALLOPEN                "arqabertos"
#define LOCALIZED_ALTERNATE_AND                    "e"
#define LOCALIZED_ALTERNATE_APPLY                  "aplique"
#define LOCALIZED_ALTERNATE_ARCCOS                 "arccos"
#define LOCALIZED_ALTERNATE_ARCSIN                 "arcsen"
#define LOCALIZED_ALTERNATE_ARCTAN                 "arctan"
#define LOCALIZED_ALTERNATE_ARITY                  "arity" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARRAY                  "vetor"
#define LOCALIZED_ALTERNATE_ARRAYP                 "évetor?"
#define LOCALIZED_ALTERNATE_ARRAY_                 "evetor?"
#define LOCALIZED_ALTERNATE_ASCII                  "ascii"
#define LOCALIZED_ALTERNATE_ASHIFT                 "desloquebitsa"
#define LOCALIZED_ALTERNATE_BACK                   "paratrás"
#define LOCALIZED_ALTERNATE_BACKSLASHEDP           "tembarrainvertida?"
#define LOCALIZED_ALTERNATE_BACKSLASHED_           "tembarrainv?"
#define LOCALIZED_ALTERNATE_BEFOREP                "éanterior?"
#define LOCALIZED_ALTERNATE_BEFORE_                "eant?"
#define LOCALIZED_ALTERNATE_BF                     "sp"
#define LOCALIZED_ALTERNATE_BFS                    "sps"
#define LOCALIZED_ALTERNATE_BITAND                 "bitE"
#define LOCALIZED_ALTERNATE_BITBLOCK               "blocobmp"
#define LOCALIZED_ALTERNATE_BITCOPY                "copiebmp"
#define LOCALIZED_ALTERNATE_BITCUT                 "recortebmp"
#define LOCALIZED_ALTERNATE_BITFIT                 "mudebmp"
#define LOCALIZED_ALTERNATE_BITINDEX               "índicebmp"
#define LOCALIZED_ALTERNATE_BITLOAD                "carreguebmp"
#define LOCALIZED_ALTERNATE_BITLOADSIZE            "tamcarreguebmp"
#define LOCALIZED_ALTERNATE_BITSIZE                "tamBmp"
#define LOCALIZED_ALTERNATE_BITMAPTURTLE           "tatbmp"
#define LOCALIZED_ALTERNATE_BITMODE                "modobmp"
#define LOCALIZED_ALTERNATE_BITNOT                 "bitNão" // "bitInverso"
#define LOCALIZED_ALTERNATE_BITOR                  "bitOu"
#define LOCALIZED_ALTERNATE_BITPASTE               "colebmp"
#define LOCALIZED_ALTERNATE_BITPASTETOINDEX        "colebmpÍndice"
#define LOCALIZED_ALTERNATE_BITSAVE                "salvebmp"
#define LOCALIZED_ALTERNATE_BITXOR                 "bitXou"
#define LOCALIZED_ALTERNATE_BK                     "pt"
#define LOCALIZED_ALTERNATE_BL                     "su"
#define LOCALIZED_ALTERNATE_BURIED                 "enterrados"
#define LOCALIZED_ALTERNATE_BURY                   "enterre"
#define LOCALIZED_ALTERNATE_BUTFIRST               "semPrimeiro"
#define LOCALIZED_ALTERNATE_BUTFIRSTS              "semPrimeiros"
#define LOCALIZED_ALTERNATE_BUTLAST                "semÚltimo"
#define LOCALIZED_ALTERNATE_BUTTONCREATE           "crieBotão"
#define LOCALIZED_ALTERNATE_BUTTONDELETE           "apagueBotão"
#define LOCALIZED_ALTERNATE_BUTTONENABLE           "ativeBotão"
#define LOCALIZED_ALTERNATE_BUTTONUPDATE           "atualizeBotão"
#define LOCALIZED_ALTERNATE_BUTTONP                "ébotão?"
#define LOCALIZED_ALTERNATE_BUTTON_                "ebotao?"
#define LOCALIZED_ALTERNATE_BYE                    "adeus"
#define LOCALIZED_ALTERNATE_CATCH                  "pegue"
#define LOCALIZED_ALTERNATE_CHAR                   "car"
#define LOCALIZED_ALTERNATE_CHDIR                  "mudeDir"
#define LOCALIZED_ALTERNATE_CHECKBOXCREATE         "crieCaixamarcação"
#define LOCALIZED_ALTERNATE_CHECKBOXDELETE         "apagueCaixamarcação"
#define LOCALIZED_ALTERNATE_CHECKBOXENABLE         "ativeCaixamarcação"
#define LOCALIZED_ALTERNATE_CHECKBOXGET            "estadoCaixamarcação"
#define LOCALIZED_ALTERNATE_CHECKBOXSET            "mudeCaixamarcação"
#define LOCALIZED_ALTERNATE_CLEAN                  "apagueDesenho"
#define LOCALIZED_ALTERNATE_CLEARPALETTE           "limpePaleta"
#define LOCALIZED_ALTERNATE_CLEARSCREEN            "tartaruga"
#define LOCALIZED_ALTERNATE_CLEARTEXT              "limpeJanelaComandos"
#define LOCALIZED_ALTERNATE_CLEARTIMER             "desativeTemporizador"
#define LOCALIZED_ALTERNATE_CLOSE                  "fechearq"
#define LOCALIZED_ALTERNATE_CLOSEALL               "fecheTodosArq"
#define LOCALIZED_ALTERNATE_CO                     "co"
#define LOCALIZED_ALTERNATE_COMBOBOXADDSTRING      "adicionenaCaixaCombo"
#define LOCALIZED_ALTERNATE_COMBOBOXCREATE         "crieCaixaCombo"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETE         "apagueCaixaCombo"
#define LOCALIZED_ALTERNATE_COMBOBOXENABLE         "ativeCaixaCombo"
#define LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING   "retiredaCaixaCombo"
#define LOCALIZED_ALTERNATE_COMBOBOXGETTEXT        "leiatextoCaixaCombo"
#define LOCALIZED_ALTERNATE_COMBOBOXSETTEXT        "mudetextoCaixaCombo"
#define LOCALIZED_ALTERNATE_CONTENTS               "desenterrados"
#define LOCALIZED_ALTERNATE_CONTINUE               "continue"
#define LOCALIZED_ALTERNATE_COPYDEF                "copieDef"
#define LOCALIZED_ALTERNATE_COS                    "cos"
#define LOCALIZED_ALTERNATE_COUNT                  "conteItem" //"numelem"
#define LOCALIZED_ALTERNATE_CS                     "tat"
#define LOCALIZED_ALTERNATE_CT                     "ljc"
#define LOCALIZED_ALTERNATE_CURSOR                 "cursor"
#define LOCALIZED_ALTERNATE_DEBUGWINDOWS           "rastreieJanela"
#define LOCALIZED_ALTERNATE_DEFINE                 "defina"
#define LOCALIZED_ALTERNATE_DEFINEDP               "édefinido?"
#define LOCALIZED_ALTERNATE_DEFINED_               "edef?"
#define LOCALIZED_ALTERNATE_DIALOGCREATE           "crieDiálogo"
#define LOCALIZED_ALTERNATE_DIALOGENABLE           "ativeDiálogo"
#define LOCALIZED_ALTERNATE_DIALOGDELETE           "apagueDiálogo"
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         "diálogoAbreArq"
#define LOCALIZED_ALTERNATE_DIALOGFILESAVE         "diálogoSalveArq"
#define LOCALIZED_ALTERNATE_DIFFERENCE             "diferença"
#define LOCALIZED_ALTERNATE_DIRECTORIES            "diretórios"
#define LOCALIZED_ALTERNATE_DLLCALL                "chameDLL"
#define LOCALIZED_ALTERNATE_DLLFREE                "libereDLL"
#define LOCALIZED_ALTERNATE_DLLLOAD                "carregueDLL"
#define LOCALIZED_ALTERNATE_DOWN                   "baixenz"
#define LOCALIZED_ALTERNATE_DOWNPITCH              "baixeNariz"
#define LOCALIZED_ALTERNATE_DRIBBLE                "registre"
#define LOCALIZED_ALTERNATE_ED                     "ed"
#define LOCALIZED_ALTERNATE_EDIT                   "edite"
#define LOCALIZED_ALTERNATE_ELLIPSEARC             "arcoElipse"
#define LOCALIZED_ALTERNATE_EMPTYP                 "évazia?"
#define LOCALIZED_ALTERNATE_EMPTY_                 "evazia?"
#define LOCALIZED_ALTERNATE_EOFP                   "efimarq?"
#define LOCALIZED_ALTERNATE_EOF_                   "éfimarq?"
#define LOCALIZED_ALTERNATE_EQUALP                 "sãoiguais?"
#define LOCALIZED_ALTERNATE_EQUAL_                 "saoig?"
#define LOCALIZED_ALTERNATE_ER                     "el"
#define LOCALIZED_ALTERNATE_ERASE                  "apague"
#define LOCALIZED_ALTERNATE_ERASEFILE              "apagueArquivo"
#define LOCALIZED_ALTERNATE_ERF                    "apagueArq"
#define LOCALIZED_ALTERNATE_ERROR                  "erro"
#define LOCALIZED_ALTERNATE_EVENTCHECK             "verifiqueEventos"
#define LOCALIZED_ALTERNATE_EXP                    "exp"
#define LOCALIZED_ALTERNATE_FD                     "pf"
#define LOCALIZED_ALTERNATE_FENCE                  "ponhalimite"
#define LOCALIZED_ALTERNATE_FILL                   "pinte"
#define LOCALIZED_ALTERNATE_FILES                  "arquivos"
#define LOCALIZED_ALTERNATE_FIRST                  "primeiro"
#define LOCALIZED_ALTERNATE_FIRSTS                 "primeiros"
#define LOCALIZED_ALTERNATE_FLOODCOLOR             "cordePreenchimento"
#define LOCALIZED_ALTERNATE_FONTFACENAMES          "tiposDeLetra"
#define LOCALIZED_ALTERNATE_FOREVER                "parasempre"
#define LOCALIZED_ALTERNATE_FORM                   "formatoNúmero"
#define LOCALIZED_ALTERNATE_FORWARD                "parafrente"
#define LOCALIZED_ALTERNATE_FPUT                   "juntenoInício"
#define LOCALIZED_ALTERNATE_FS                     "tc"
#define LOCALIZED_ALTERNATE_FULLSCREEN             "telaCheia"
#define LOCALIZED_ALTERNATE_FULLTEXT               "todoTexto"
#define LOCALIZED_ALTERNATE_GETFOCUS               "foco"
#define LOCALIZED_ALTERNATE_GOTO                   "váPara"
#define LOCALIZED_ALTERNATE_GIFLOAD                "carregueGif"
#define LOCALIZED_ALTERNATE_GIFSIZE                "tamGif"
#define LOCALIZED_ALTERNATE_GIFSAVE                "salveGif"
#define LOCALIZED_ALTERNATE_GPROP                  "propriedade"
#define LOCALIZED_ALTERNATE_GREATEREQUALP          "maior.ou.igual?"
#define LOCALIZED_ALTERNATE_GREATEREQUAL_          "maiorig?"
#define LOCALIZED_ALTERNATE_GREATERP               "émaior?"
#define LOCALIZED_ALTERNATE_GREATER_               "maior?"
#define LOCALIZED_ALTERNATE_GROUPBOXCREATE         "criecaixagrupo"
#define LOCALIZED_ALTERNATE_GROUPBOXDELETE         "apaguecaixagrupo"
#define LOCALIZED_ALTERNATE_HALT                   "paretudo"
#define LOCALIZED_ALTERNATE_HASOWNPENP             "hasownpenp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HASOWNPEN_             "hasownpen?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HEADING                "direção"
#define LOCALIZED_ALTERNATE_HELP                   "ajuda"
#define LOCALIZED_ALTERNATE_HIDETURTLE             "oculteTat"
#define LOCALIZED_ALTERNATE_HOME                   "paracentro"
#define LOCALIZED_ALTERNATE_HT                     "ot"
#define LOCALIZED_ALTERNATE_IF                     "se"
#define LOCALIZED_ALTERNATE_IFELSE                 "seSenão"
#define LOCALIZED_ALTERNATE_IFF                    "sef"
#define LOCALIZED_ALTERNATE_IFFALSE                "seFalso"
#define LOCALIZED_ALTERNATE_IFT                    "sev"
#define LOCALIZED_ALTERNATE_IFTRUE                 "seVerd"
#define LOCALIZED_ALTERNATE_INGAMEPORT             "portaJoystick"
#define LOCALIZED_ALTERNATE_INPORT                 "portaEntrada"
#define LOCALIZED_ALTERNATE_INPORTB                "portaEntradab"
#define LOCALIZED_ALTERNATE_INT                    "inteiro"
#define LOCALIZED_ALTERNATE_ITEM                   "item"
#define LOCALIZED_ALTERNATE_KEYBOARDOFF            "desativeTecla"
#define LOCALIZED_ALTERNATE_KEYBOARDON             "ativeTecla"
#define LOCALIZED_ALTERNATE_KEYBOARDVALUE          "asciiTecla"
#define LOCALIZED_ALTERNATE_KEYP                   "tecla?"
#define LOCALIZED_ALTERNATE_KEY_                   "temarq"
#define LOCALIZED_ALTERNATE_LABEL                  "rotule"
#define LOCALIZED_ALTERNATE_LABELFONT              "tiporotule"
#define LOCALIZED_ALTERNATE_LABELSIZE              "tamanhorotule"
#define LOCALIZED_ALTERNATE_LAST                   "último"
#define LOCALIZED_ALTERNATE_LEFT                   "paraesquerda"
#define LOCALIZED_ALTERNATE_LEFTROLL               "roleparaesquerda"
#define LOCALIZED_ALTERNATE_LESSEQUALP             "menor.ou.igual?"
#define LOCALIZED_ALTERNATE_LESSEQUAL_             "menorig?"
#define LOCALIZED_ALTERNATE_LESSP                  "émenor?"
#define LOCALIZED_ALTERNATE_LESS_                  "menor?"
#define LOCALIZED_ALTERNATE_LIGHT                  "luz"
#define LOCALIZED_ALTERNATE_LIST                   "lista"
#define LOCALIZED_ALTERNATE_LISTBOXADDSTRING       "adicioneCaixaListagem"
#define LOCALIZED_ALTERNATE_LISTBOXCREATE          "crieCaixaListagem"
#define LOCALIZED_ALTERNATE_LISTBOXENABLE          "ativeCaixaListagem"
#define LOCALIZED_ALTERNATE_LISTBOXDELETE          "apagueCaixaListagem"
#define LOCALIZED_ALTERNATE_LISTBOXDELETESTRING    "retiredaCaixaListagem"
#define LOCALIZED_ALTERNATE_LISTBOXGETSELECT       "selecioneCaixaListagem"
#define LOCALIZED_ALTERNATE_LISTP                  "élista?"
#define LOCALIZED_ALTERNATE_LIST_                  "elista?"
#define LOCALIZED_ALTERNATE_LN                     "ln"
#define LOCALIZED_ALTERNATE_LOAD                   "carregue"
#define LOCALIZED_ALTERNATE_LOCAL                  "local"
#define LOCALIZED_ALTERNATE_LOG10                  "log"
#define LOCALIZED_ALTERNATE_LOGOVERSION            "versãoLogo"
#define LOCALIZED_ALTERNATE_LOWERCASE              "minúsculas"
#define LOCALIZED_ALTERNATE_LPUT                   "juntenofim"
#define LOCALIZED_ALTERNATE_LR                     "rolepe"
#define LOCALIZED_ALTERNATE_LSHIFT                 "desloquebitsl"
#define LOCALIZED_ALTERNATE_LT                     "pe"
#define LOCALIZED_ALTERNATE_MACHINE                "meupc"
#define LOCALIZED_ALTERNATE_MACROP                 "émacro?"
#define LOCALIZED_ALTERNATE_MACRO_                 "emacro?"
#define LOCALIZED_ALTERNATE_MAKE                   "atribua"
#define LOCALIZED_ALTERNATE_MCI                    "mci"
#define LOCALIZED_ALTERNATE_MEMBER                 "membro"
#define LOCALIZED_ALTERNATE_MEMBERP                "émembro?"
#define LOCALIZED_ALTERNATE_MEMBER_                "emembro?"
#define LOCALIZED_ALTERNATE_MESSAGEBOX             "mensagem"
#define LOCALIZED_ALTERNATE_MIDICLOSE              "fecheMidi"
#define LOCALIZED_ALTERNATE_MIDIMESSAGE            "mensagemMidi"
#define LOCALIZED_ALTERNATE_MIDIOPEN               "abraMidi"
#define LOCALIZED_ALTERNATE_MINUS                  "oposto"
#define LOCALIZED_ALTERNATE_MKDIR                  "crieDir"
#define LOCALIZED_ALTERNATE_MODULO                 "módulo"
#define LOCALIZED_ALTERNATE_MOUSEOFF               "ativeMouse"
#define LOCALIZED_ALTERNATE_MOUSEON                "desativeMouse"
#define LOCALIZED_ALTERNATE_MOUSEPOS               "posMouse"
#define LOCALIZED_ALTERNATE_NAMEP                  "énome?"
#define LOCALIZED_ALTERNATE_NAME_                  "enome?"
#define LOCALIZED_ALTERNATE_NAMES                  "nomes"
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           "recuseRede" // "nãoaceiteconexão"
#define LOCALIZED_ALTERNATE_NETACCEPTON            "aceiteRede" // "aceiteconexão"
#define LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE  "recebaValorRedeAceita" // "Recebavalorconexãoaceita"
#define LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE     "envieValorRedeAceita" // "Envievalorconexãoaceita"
#define LOCALIZED_ALTERNATE_NETCONNECTOFF          "desconecteRede" // "desligueConexão"
#define LOCALIZED_ALTERNATE_NETCONNECTON           "conecteRede" // "ligueConexão"
#define LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE "recebavalorRede" // "recebavalorconexão"
#define LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE    "envieValorRede" // "envievalorconexão"
#define LOCALIZED_ALTERNATE_NETSHUTDOWN            "termineRede"
#define LOCALIZED_ALTERNATE_NETSTARTUP             "inicieRede" // "inicializeRede"
#define LOCALIZED_ALTERNATE_NOBITMAPTURTLE         "semtatbmp"
#define LOCALIZED_ALTERNATE_NODES                  "nós"
#define LOCALIZED_ALTERNATE_NODRIBBLE              "nãoregistre"
#define LOCALIZED_ALTERNATE_NOSTATUS               "semEstado"
#define LOCALIZED_ALTERNATE_NOT                    "não"
#define LOCALIZED_ALTERNATE_NOTEQUALP              "sãodiferentes?"
#define LOCALIZED_ALTERNATE_NOTEQUAL_              "saodif?"
#define LOCALIZED_ALTERNATE_NOYIELD                "monotarefa"
#define LOCALIZED_ALTERNATE_NUMBERP                "énúmero?"
#define LOCALIZED_ALTERNATE_NUMBER_                "enum?"
#define LOCALIZED_ALTERNATE_OP                     "dev"
#define LOCALIZED_ALTERNATE_OPENAPPEND             "abraparaAdicionar"
#define LOCALIZED_ALTERNATE_OPENREAD               "abraparaLer"
#define LOCALIZED_ALTERNATE_OPENUPDATE             "abraparaAtualizar"
#define LOCALIZED_ALTERNATE_OPENWRITE              "abraparaEscrever"
#define LOCALIZED_ALTERNATE_OR                     "ou"
#define LOCALIZED_ALTERNATE_OUTPORT                "escrevaPorta"
#define LOCALIZED_ALTERNATE_OUTPORTB               "escrevaPortab"
#define LOCALIZED_ALTERNATE_OUTPUT                 "devolva"
#define LOCALIZED_ALTERNATE_PARSE                  "analise"
#define LOCALIZED_ALTERNATE_PAUSE                  "pausa"
#define LOCALIZED_ALTERNATE_PC                     "cl"
#define LOCALIZED_ALTERNATE_PD                     "pd" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PE                     "ub"
#define LOCALIZED_ALTERNATE_PENCOLOR               "cordoLápis"
#define LOCALIZED_ALTERNATE_PENDOWN                "useLápis"
#define LOCALIZED_ALTERNATE_PENDOWNP               "éuseLápis?"
#define LOCALIZED_ALTERNATE_PENDOWN_               "euseLapis?"
#define LOCALIZED_ALTERNATE_PENERASE               "useborracha"
#define LOCALIZED_ALTERNATE_PENMODE                "modoLápis"
#define LOCALIZED_ALTERNATE_PENPAINT               "useRisco"
#define LOCALIZED_ALTERNATE_PENPATTERN             "padrãoLápis"
#define LOCALIZED_ALTERNATE_PENREVERSE             "useInversor"
#define LOCALIZED_ALTERNATE_PENSIZE                "espL"
#define LOCALIZED_ALTERNATE_PENUP                  "useNada"
#define LOCALIZED_ALTERNATE_PERSPECTIVE            "Logo3D"
#define LOCALIZED_ALTERNATE_PITCH                  "direçãoNariz"
#define LOCALIZED_ALTERNATE_PIXEL                  "pixel"
#define LOCALIZED_ALTERNATE_PLAYWAVE               "toqueWave"
#define LOCALIZED_ALTERNATE_PLIST                  "listaProp"
#define LOCALIZED_ALTERNATE_PLISTS                 "listaProps"
#define LOCALIZED_ALTERNATE_PO                     "moDefs" // "mot"
#define LOCALIZED_ALTERNATE_POPDIR                 "voltedir"
#define LOCALIZED_ALTERNATE_POLYSTART              "iniciePolígono"
#define LOCALIZED_ALTERNATE_POLYEND                "terminePolígono"
#define LOCALIZED_ALTERNATE_POLYVIEW               "mostrePolígono"
#define LOCALIZED_ALTERNATE_PORTCLOSE              "fechePorta"
#define LOCALIZED_ALTERNATE_PORTFLUSH              "descarregaPorta"
#define LOCALIZED_ALTERNATE_PORTMODE               "mudemodoPorta"
#define LOCALIZED_ALTERNATE_PORTOPEN               "abraPorta"
#define LOCALIZED_ALTERNATE_PORTREADARRAY          "leiaVetorPorta"
#define LOCALIZED_ALTERNATE_PORTREADCHAR           "leiaCarPorta"
#define LOCALIZED_ALTERNATE_PORTWRITEARRAY         "escrevaVetorPorta"
#define LOCALIZED_ALTERNATE_PORTWRITECHAR          "escrevaCarPorta"
#define LOCALIZED_ALTERNATE_POS                    "pos"
#define LOCALIZED_ALTERNATE_POSXYZ                 "posxyz"
#define LOCALIZED_ALTERNATE_POT                    "mostreTítulo"
#define LOCALIZED_ALTERNATE_POWER                  "potência"
#define LOCALIZED_ALTERNATE_PPROP                  "mudeprop"
#define LOCALIZED_ALTERNATE_PPT                    "ul"
#define LOCALIZED_ALTERNATE_PR                     "esc"
#define LOCALIZED_ALTERNATE_PRIMITIVEP             "éprimitiva?"
#define LOCALIZED_ALTERNATE_PRIMITIVE_             "eprim?"
#define LOCALIZED_ALTERNATE_PRINT                  "escreva"
#define LOCALIZED_ALTERNATE_PROCEDUREP             "éprocedimento?" // "édefinido?"
#define LOCALIZED_ALTERNATE_PROCEDURE_             "eproced?"
#define LOCALIZED_ALTERNATE_PROPLISTP              "lProp?"
#define LOCALIZED_ALTERNATE_PROPLIST_              "lProp?"
#define LOCALIZED_ALTERNATE_PROCEDURES             "lProcs"
#define LOCALIZED_ALTERNATE_PRODUCT                "produto"
#define LOCALIZED_ALTERNATE_PU                     "un"
#define LOCALIZED_ALTERNATE_PX                     "ui"
#define LOCALIZED_ALTERNATE_QUESTIONBOX            "caixadeQuestão"
#define LOCALIZED_ALTERNATE_QUOTIENT               "quociente"
#define LOCALIZED_ALTERNATE_RADARCCOS              "arcCosRad"
#define LOCALIZED_ALTERNATE_RADARCSIN              "arcSenRad"
#define LOCALIZED_ALTERNATE_RADARCTAN              "arcTanRad"
#define LOCALIZED_ALTERNATE_RADCOS                 "cosRad"
#define LOCALIZED_ALTERNATE_RADIOBUTTONCREATE      "crieBotãoRádio"
#define LOCALIZED_ALTERNATE_RADIOBUTTONENABLE      "ativeBotãoRádio"
#define LOCALIZED_ALTERNATE_RADIOBUTTONDELETE      "apagueBotãoRádio"
#define LOCALIZED_ALTERNATE_RADIOBUTTONGET         "botãoRádio"
#define LOCALIZED_ALTERNATE_RADIOBUTTONSET         "mudeBotãoRádio"
#define LOCALIZED_ALTERNATE_RADSIN                 "senRad"
#define LOCALIZED_ALTERNATE_RADTAN                 "tanRad"
#define LOCALIZED_ALTERNATE_RANDOM                 "sorteienúmero"
#define LOCALIZED_ALTERNATE_RAWASCII               "rawascii" // "asciiPuro"
#define LOCALIZED_ALTERNATE_RC                     "leiacar"
#define LOCALIZED_ALTERNATE_RCS                    "leiacars"
#define LOCALIZED_ALTERNATE_READCHAR               "leiaCaractere"
#define LOCALIZED_ALTERNATE_READCHARS              "leiaCaracteres"
#define LOCALIZED_ALTERNATE_READER                 "arqLeitura"
#define LOCALIZED_ALTERNATE_READLIST               "leiaLista"
#define LOCALIZED_ALTERNATE_READPOS                "readpos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READRAWLINE            "readrawline" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READWORD               "leiaPalavra"
#define LOCALIZED_ALTERNATE_REMAINDER              "resto"
#define LOCALIZED_ALTERNATE_REMPROP                "retireProp"
#define LOCALIZED_ALTERNATE_REPCOUNT               "conteVezes"
#define LOCALIZED_ALTERNATE_REPEAT                 "repita"
#define LOCALIZED_ALTERNATE_RERANDOM               "repitasorteie"
#define LOCALIZED_ALTERNATE_RIGHT                  "paradireita"
#define LOCALIZED_ALTERNATE_RIGHTROLL              "roleparadireita"
#define LOCALIZED_ALTERNATE_RL                     "rl" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RMDIR                  "apagueDir"
#define LOCALIZED_ALTERNATE_ROLL                   "direçãoRolagem"
#define LOCALIZED_ALTERNATE_ROUND                  "arredonde"
#define LOCALIZED_ALTERNATE_RR                     "rolepd"
#define LOCALIZED_ALTERNATE_RT                     "pd"
#define LOCALIZED_ALTERNATE_RUN                    "faça"
#define LOCALIZED_ALTERNATE_RUNPARSE               "façaAnalise"
#define LOCALIZED_ALTERNATE_RUNRESULT              "façaDevolva"
#define LOCALIZED_ALTERNATE_RW                     "leiap"
#define LOCALIZED_ALTERNATE_SAVE                   "salve"
#define LOCALIZED_ALTERNATE_SCREENCOLOR            "cordofundo"
#define LOCALIZED_ALTERNATE_SCROLLBARCREATE        "crieBarraRolagem"
#define LOCALIZED_ALTERNATE_SCROLLBARENABLE        "ativeBarraRolagem"
#define LOCALIZED_ALTERNATE_SCROLLBARDELETE        "apagueBarraRolagem"
#define LOCALIZED_ALTERNATE_SCROLLBARGET           "barraRolagem"
#define LOCALIZED_ALTERNATE_SCROLLBARSET           "mudeBarraRolagem"
#define LOCALIZED_ALTERNATE_SCROLLX                "rolex"
#define LOCALIZED_ALTERNATE_SCROLLY                "roley"
#define LOCALIZED_ALTERNATE_SCRUNCH                "proporção"
#define LOCALIZED_ALTERNATE_SE                     "fr"
#define LOCALIZED_ALTERNATE_SELECTBOX              "caixaseleção"
#define LOCALIZED_ALTERNATE_SENTENCE               "frase"
#define LOCALIZED_ALTERNATE_SETACTIVEAREA          "mudeÁreaAtiva"
#define LOCALIZED_ALTERNATE_SETBITINDEX            "mudeÍndicebmp"
#define LOCALIZED_ALTERNATE_SETBITMODE             "mudeModobmp"
#define LOCALIZED_ALTERNATE_SETCLIP                "mudeClip"
#define LOCALIZED_ALTERNATE_SETCURSOR              "mudeCursor"
#define LOCALIZED_ALTERNATE_SETCURSORNOWAIT        "mudeCursorSeta"
#define LOCALIZED_ALTERNATE_SETCURSORWAIT          "mudeCursorEspera"
#define LOCALIZED_ALTERNATE_SETFC                  "mudecp"
#define LOCALIZED_ALTERNATE_SETFLOODCOLOR          "mudeCordePreenchimento"
#define LOCALIZED_ALTERNATE_SETFOCUS               "mudeFoco"
#define LOCALIZED_ALTERNATE_SETH                   "mudedc"
#define LOCALIZED_ALTERNATE_SETHEADING             "mudeDireção"
#define LOCALIZED_ALTERNATE_SETITEM                "mudeItem"
#define LOCALIZED_ALTERNATE_SETLABELFONT           "mudeTipo"
#define LOCALIZED_ALTERNATE_SETLIGHT               "mudeLuz"
#define LOCALIZED_ALTERNATE_SETMARGINS             "mudeMargens"
#define LOCALIZED_ALTERNATE_SETPC                  "mudeCL"
#define LOCALIZED_ALTERNATE_SETPENCOLOR            "mudeCordoLápis"
#define LOCALIZED_ALTERNATE_SETPENPATTERN          "mudePadrãoLápis"
#define LOCALIZED_ALTERNATE_SETPENSIZE             "mudeEspL"
#define LOCALIZED_ALTERNATE_SETPITCH               "mudeDireçãoNariz"
#define LOCALIZED_ALTERNATE_SETPIXEL               "mudePixel"
#define LOCALIZED_ALTERNATE_SETPOS                 "mudePos"
#define LOCALIZED_ALTERNATE_SETPOSXYZ              "mudeposxyz"
#define LOCALIZED_ALTERNATE_SETREAD                "mudeLeitura"
#define LOCALIZED_ALTERNATE_SETREADPOS             "mudePosLeitura"
#define LOCALIZED_ALTERNATE_SETROLL                "mudeDireçãoRolagem"
#define LOCALIZED_ALTERNATE_SETSC                  "mudeCF"
#define LOCALIZED_ALTERNATE_SETSCREENCOLOR         "mudeCordoFundo"
#define LOCALIZED_ALTERNATE_SETSCRUNCH             "mudeProporção"
#define LOCALIZED_ALTERNATE_SETTIMER               "mudeTemporizador" // "mudecontador"
#define LOCALIZED_ALTERNATE_SETTURTLE              "ativetat"
#define LOCALIZED_ALTERNATE_SETTURTLEMODE          "mudeModoTat"
#define LOCALIZED_ALTERNATE_SETWRITE               "mudeEscrita"
#define LOCALIZED_ALTERNATE_SETWRITEPOS            "mudePosEscrita"
#define LOCALIZED_ALTERNATE_SETX                   "mudex"
#define LOCALIZED_ALTERNATE_SETXY                  "mudexy"
#define LOCALIZED_ALTERNATE_SETXYZ                 "mudexyz"
#define LOCALIZED_ALTERNATE_SETY                   "mudey"
#define LOCALIZED_ALTERNATE_SETZ                   "mudez"
#define LOCALIZED_ALTERNATE_SHELL                  "shell"
#define LOCALIZED_ALTERNATE_SHOW                   "mostre"
#define LOCALIZED_ALTERNATE_SHOWNP                 "évisível?"
#define LOCALIZED_ALTERNATE_SHOWN_                 "evisivel?"
#define LOCALIZED_ALTERNATE_SHOWTURTLE             "mostreTat"
#define LOCALIZED_ALTERNATE_SIN                    "sen"
#define LOCALIZED_ALTERNATE_SOUND                  "som"
#define LOCALIZED_ALTERNATE_SPLITSCREEN            "fixeJanelaComandos"
#define LOCALIZED_ALTERNATE_SQRT                   "raizq"
#define LOCALIZED_ALTERNATE_SS                     "fixeJC"
#define LOCALIZED_ALTERNATE_ST                     "mt"
#define LOCALIZED_ALTERNATE_STANDOUT               "standout" //
#define LOCALIZED_ALTERNATE_STATICCREATE           "crieEstático"
#define LOCALIZED_ALTERNATE_STATICDELETE           "apagueEstático"
#define LOCALIZED_ALTERNATE_STATICUPDATE           "mudeEstático"
#define LOCALIZED_ALTERNATE_STATUS                 "estado"
#define LOCALIZED_ALTERNATE_STEP                   "siga" //"passoapasso"
#define LOCALIZED_ALTERNATE_STEPPED                "seguidos"
#define LOCALIZED_ALTERNATE_STOP                   "pare"
#define LOCALIZED_ALTERNATE_SUBSTRINGP             "ésubseqüência?"
#define LOCALIZED_ALTERNATE_SUBSTRING_             "esubseq?"
#define LOCALIZED_ALTERNATE_SUM                    "soma"
#define LOCALIZED_ALTERNATE_TAG                    "etiqueta"
#define LOCALIZED_ALTERNATE_TAN                    "tan"
#define LOCALIZED_ALTERNATE_TEST                   "teste"
#define LOCALIZED_ALTERNATE_TEXT                   "texto"
#define LOCALIZED_ALTERNATE_TEXTSCREEN             "libereJanelaComandos"
#define LOCALIZED_ALTERNATE_THING                  "valor"
#define LOCALIZED_ALTERNATE_THROW                  "lance"
#define LOCALIZED_ALTERNATE_TIME                   "diahora"
#define LOCALIZED_ALTERNATE_TIMEMILLI              "tempoMili"
#define LOCALIZED_ALTERNATE_TO                     "aprenda"
#define LOCALIZED_ALTERNATE_TONE                   "tom"
#define LOCALIZED_ALTERNATE_TOWARDS                "direçãopara"
#define LOCALIZED_ALTERNATE_TOWARDSXYZ             "direçãoparaxyz"
#define LOCALIZED_ALTERNATE_TRACE                  "rastreie"
#define LOCALIZED_ALTERNATE_TRACED                 "rastreados"
#define LOCALIZED_ALTERNATE_TS                     "libereJC"
#define LOCALIZED_ALTERNATE_TURTLE                 "tatativa"
#define LOCALIZED_ALTERNATE_TURTLEMODE             "modoTat"
#define LOCALIZED_ALTERNATE_TURTLES                "tartarugas"
#define LOCALIZED_ALTERNATE_TYPE                   "guardeparaescrever"
#define LOCALIZED_ALTERNATE_UNBURY                 "desenterre"
#define LOCALIZED_ALTERNATE_UNSTEP                 "nãoSiga" //"nãoPassoaPasso"
#define LOCALIZED_ALTERNATE_UNTRACE                "nãoRastreie"
#define LOCALIZED_ALTERNATE_UP                     "levantenz"
#define LOCALIZED_ALTERNATE_UPPERCASE              "maiúsculas"
#define LOCALIZED_ALTERNATE_UPPITCH                "levantenariz"
#define LOCALIZED_ALTERNATE_WAIT                   "espere"
#define LOCALIZED_ALTERNATE_WINDOW                 "semlimite"
#define LOCALIZED_ALTERNATE_WINDOWCREATE           "crieJanela"
#define LOCALIZED_ALTERNATE_WINDOWENABLE           "ativeJanela"
#define LOCALIZED_ALTERNATE_WINDOWDELETE           "apagueJanela"
#define LOCALIZED_ALTERNATE_WINDOWFILEEDIT         "janelaediteArquivo"
#define LOCALIZED_ALTERNATE_WINDOWSET              "mudeEstadoJanela"
#define LOCALIZED_ALTERNATE_WINHELP                "socorro"
#define LOCALIZED_ALTERNATE_WORD                   "palavra"
#define LOCALIZED_ALTERNATE_WORDP                  "épalavra?"
#define LOCALIZED_ALTERNATE_WORD_                  "epal?"
#define LOCALIZED_ALTERNATE_WRAP                   "dobrejanela"
#define LOCALIZED_ALTERNATE_WRITEPOS               "posLeitura"
#define LOCALIZED_ALTERNATE_WRITER                 "arqescrita"
#define LOCALIZED_ALTERNATE_YESNOBOX               "CaixaSimNão"
#define LOCALIZED_ALTERNATE_YIELD                  "multiTarefa"
#define LOCALIZED_ALTERNATE_ZOOM                   "zoom"

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      "&OK"
#define LOCALIZED_GENERAL_CANCELBUTTON  "&Cancelar"
#define LOCALIZED_GENERAL_APPLYBUTTON   "&Aplicar"

#define LOCALIZED_GENERAL_PRODUCTNAME   "FMSLogo"

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  "O ambiente de programação FMSLogo"

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  "&Arquivo"
#define LOCALIZED_FILE_NEW              "&Novo\t(apaga o trabalho atual)"
#define LOCALIZED_FILE_LOAD             "&Carregar...\t(une ao trabalho atual)"
#define LOCALIZED_FILE_OPEN             "A&brir...\t(substitui o trabalho atual)"
#define LOCALIZED_FILE_SAVE             "&Guardar"
#define LOCALIZED_FILE_SAVEAS           "G&uardar como..."
#define LOCALIZED_FILE_SETASSCREENSAVER "Coloque como Protetor de &Tela"
#define LOCALIZED_FILE_EDIT             "&Editar..."
#define LOCALIZED_FILE_ERASE            "A&pagar..."
#define LOCALIZED_FILE_EXIT             "&Sair"

#define LOCALIZED_BITMAP               "&Bitmap"
#define LOCALIZED_BITMAP_NEW           "&Novo"
#define LOCALIZED_BITMAP_LOAD          "&Carregar..."
#define LOCALIZED_BITMAP_SAVE          "&Guardar"
#define LOCALIZED_BITMAP_SAVEAS        "G&uardar como..."
#define LOCALIZED_BITMAP_PRINT         "&Imprimir..."
#define LOCALIZED_BITMAP_PRINTERSETUP  "C&onfigurar página..."
#define LOCALIZED_BITMAP_ACTIVEAREA    "Área &Ativa..."

#define LOCALIZED_SET                  "&Configurar"
#define LOCALIZED_SET_PENSIZE          "&Tamanho do lápis..."
#define LOCALIZED_SET_LABELFONT        "Tipo de letra para &rótulo..."
#define LOCALIZED_SET_COMMANDERFONT    "Tipo de letra para &comandos..."
#define LOCALIZED_SET_PENCOLOR         "Cor de &lápis..."
#define LOCALIZED_SET_FLOODCOLOR       "Cor de &preenchimento..."
#define LOCALIZED_SET_SCREENCOLOR      "Color de &fundo..."

#define LOCALIZED_ZOOM                 "&Zoom"
#define LOCALIZED_ZOOM_IN              "&Ampliar"
#define LOCALIZED_ZOOM_OUT             "&Reduzir"
#define LOCALIZED_ZOOM_NORMAL          "&Normal"

#define LOCALIZED_HELP                 "A&juda"
#define LOCALIZED_HELP_INDEX           "&Início"
#define LOCALIZED_HELP_TUTORIAL        "&Tutorial"
#define LOCALIZED_HELP_DEMO            "&Demo"
#define LOCALIZED_HELP_EXAMPLE         "&Exemplos"
#define LOCALIZED_HELP_RELEASENOTES    "&Notas da versão"
#define LOCALIZED_HELP_ABOUTFMSLOGO    "&Sobre o " LOCALIZED_GENERAL_PRODUCTNAME "..."
#define LOCALIZED_HELP_MS              "Sobre o &FMS..."
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   "Português para Inglês"
#define LOCALIZED_HELP_ENGLISHTOLANG   "Inglês para Português"

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              "Selecionar área activa"
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       "Isto afeta a impressão e gravação de bitmaps"
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        "Y-Sup"
#define LOCALIZED_SELECTACTIVEAREA_YLOW         "Y-Inf"
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        "X-Sup"
#define LOCALIZED_SELECTACTIVEAREA_XLOW         "X-Inf"
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH "pontos por polegada impressa:"
#define LOCALIZED_SELECTACTIVEAREA_RESET        "&Restaurar"
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON

// The screensaver strings
#define LOCALIZED_SCREENSAVER_NAME              LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_SCREENSAVER_DESCRIPTION       "Protetor de tela de FMSLogo"
#define LOCALIZED_SCREENSAVER_SETTINGS_TITLE    "Protetor de tela de FMSLogo"
#define LOCALIZED_SCREENSAVER_LOCATE            "&Localize ..."
#define LOCALIZED_SCREENSAVER_FILE              "Logo &Arquivo:"
#define LOCALIZED_SCREENSAVER_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SCREENSAVER_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON

// The dialog box for selecting a Startup procedure
#define LOCALIZED_SELECTSTARTUP_CAPTION               "Selecione uma instrução de " LOCALIZED_ALTERNATE_STARTUP
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED "O espaço de trabalho não possui uma lista de instrução de " LOCALIZED_ALTERNATE_STARTUP " definida, nada vai\nacontecer quando o protetor de tela é carregado.\nPor favor, selecione um procedimento para executar quando o programa é carregado."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST   "A variável " LOCALIZED_ALTERNATE_STARTUP " não é uma lista, nada vai\nacontecer quando o protetor de tela é carregado.\nPor favor, selecione um procedimento para executar quando o programa é carregado."
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY     "Seu espaço de trabalho tem uma lista de instrução de vazio " LOCALIZED_ALTERNATE_STARTUP " definida, nada vai\nacontecer quando o protetor de tela é carregado.\nPor favor, selecione um procedimento para executar quando o programa é carregado."
#define LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED   "Não há procedimentos definidos"

// The warning dialog box when the user saves an empty workspace
#define LOCALIZED_EMPTYWORKSPACE_TITLE                LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_EMPTYWORKSPACE_MESSAGE              "Não há nenhum procedimentos, variáveis ou listas de propriedades definidas,\nassim que o espaço de trabalho será salvo como um arquivo vazio.\n\nVocê quer salvar o espaço de trabalho de qualquer maneira?"

//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     "Copiar"
#define LOCALIZED_POPUP_CUT                      "Cortar"
#define LOCALIZED_POPUP_PASTE                    "Colar"
#define LOCALIZED_POPUP_DELETE                   "Apagar"
#define LOCALIZED_POPUP_UNDO                     "Desfazer"
#define LOCALIZED_POPUP_REDO                     "Refazer"
#define LOCALIZED_POPUP_SELECTALL                "Selecionar Tudo"
#define LOCALIZED_POPUP_HELP                     "Busca por Tema"
#define LOCALIZED_POPUP_REMOVELINES              "Remove Selected Lines" // NOT_YET_LOCALIZED

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   "Editor"

#define LOCALIZED_EDITOR_FILE                    "&Arquivo"
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        "&Guardar e Sair\tCtrl+D"
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    "Guardar na &área de trabalho"
#define LOCALIZED_EDITOR_FILE_PRINT              "&Imprimir..."
#define LOCALIZED_EDITOR_FILE_EXIT               "&Sair"

#define LOCALIZED_EDITOR_EDIT                    "&Editar"
#define LOCALIZED_EDITOR_EDIT_UNDO               "&Desfazer\tCtrl+Z"
#define LOCALIZED_EDITOR_EDIT_REDO               "&Refazer\tCtrl+Y"
#define LOCALIZED_EDITOR_EDIT_CUT                "Recor&tar\tCtrl+X"
#define LOCALIZED_EDITOR_EDIT_COPY               "&Copiar\tCtrl+C"
#define LOCALIZED_EDITOR_EDIT_PASTE              "Co&lar\tCtrl+V"
#define LOCALIZED_EDITOR_EDIT_DELETE             "&Apagar\tDel"
#define LOCALIZED_EDITOR_EDIT_CLEARALL           "Apagar &tudo\tCtrl+Del"
#define LOCALIZED_EDITOR_EDIT_SELECTALL          "&Selecionar Tudo\tCtrl+A"

#define LOCALIZED_EDITOR_SEARCH                  "&Buscar"
#define LOCALIZED_EDITOR_SEARCH_FIND             "&Localizar...\tCtrl+F"
#define LOCALIZED_EDITOR_SEARCH_REPLACE          "&Substituir...\tCtrl+H"
#define LOCALIZED_EDITOR_SEARCH_NEXT             "&Próximo\tF3"

#define LOCALIZED_EDITOR_SET                     "&Configurar"
#define LOCALIZED_EDITOR_SET_FONT                "&Tipo de letra..."

#define LOCALIZED_EDITOR_TEST                    "&Testar"
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      "&Run Selection\tCtrl+R" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITOR_HELP                    "Aj&uda"
#define LOCALIZED_EDITOR_HELP_INDEX              "Í&ndice"
#define LOCALIZED_EDITOR_HELP_EDITOR             "&Editor"
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        "&Busca contextual\tF1"


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    "&Guardar e Sair"
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       "&Não guardar"
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       "Há alterações não salvas em sua área de trabalho. Se sair sem guardar, estas alterações serão perdidas."
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       "Deseja guardar suas alterações antes de sair?"


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     "Janela de Comandos"
#define LOCALIZED_COMMANDER_HALT                "PareTudo"
#define LOCALIZED_COMMANDER_TRACE               "Rastreie"
#define LOCALIZED_COMMANDER_NOTRACE             "Não Rastreie"
#define LOCALIZED_COMMANDER_PAUSE               "Pause"
#define LOCALIZED_COMMANDER_STATUS              "Estado"
#define LOCALIZED_COMMANDER_NOSTATUS            "SemEstado"
#define LOCALIZED_COMMANDER_STEP                "Siga"
#define LOCALIZED_COMMANDER_UNSTEP              "NãoSiga"
#define LOCALIZED_COMMANDER_RESET               "Tat"
#define LOCALIZED_COMMANDER_EXECUTE             "Execute"
#define LOCALIZED_COMMANDER_EDALL               "EdTudo"

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        "Estado"
#define LOCALIZED_STATUS_PEN                    "Lápis"
#define LOCALIZED_STATUS_CONTACT                "Contato:"
#define LOCALIZED_STATUS_WIDTH                  "Largura:"
#define LOCALIZED_STATUS_STYLE                  "Estilo:"
#define LOCALIZED_STATUS_ORIENTATION            "Orientação"
#define LOCALIZED_STATUS_PITCH                  "Cabeceio:"
#define LOCALIZED_STATUS_HEADING                "Direção:"
#define LOCALIZED_STATUS_ROLL                   "Rolamento:"
#define LOCALIZED_STATUS_TURTLE                 "Tartaruga"
#define LOCALIZED_STATUS_POSITION               "Posição(XYZ):"
#define LOCALIZED_STATUS_WHICH                  "Tat Ativa:"
#define LOCALIZED_STATUS_VISIBILITY             "Visibilidade:"
#define LOCALIZED_STATUS_COLOR                  "Cor"
#define LOCALIZED_STATUS_PENCOLOR               "Lápis(RGB):"
#define LOCALIZED_STATUS_FLOODCOLOR             "Preenchimento(RGB):"
#define LOCALIZED_STATUS_SCREENCOLOR            "Fundo(RGB):"
#define LOCALIZED_STATUS_KERNEL                 "Núcleo"
#define LOCALIZED_STATUS_CALLS                  "Chamadas:"
#define LOCALIZED_STATUS_PEAKMEMORY             "Memória:"

#define LOCALIZED_STATUS_PENREVERSE     "Invertido"
#define LOCALIZED_STATUS_PENNORMAL      "Normal"
#define LOCALIZED_STATUS_PENERASE       "Borracha"
#define LOCALIZED_STATUS_PENUP          "Erguido"
#define LOCALIZED_STATUS_PENDOWN        "Baixado"
#define LOCALIZED_STATUS_PENSHOWN       "Visível"
#define LOCALIZED_STATUS_PENHIDDEN      "Oculta"
#define LOCALIZED_STATUS_POLYGONS       "Polígonos"
#define LOCALIZED_STATUS_VECTORS        "Vetores"
#define LOCALIZED_STATUS_NODES          "Nós"
#define LOCALIZED_STATUS_NOT_APPLICABLE "N/A" // NOT_YET_LOCALIZED

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           "&Tudo"
#define LOCALIZED_ERASEPROCEDURE                "Apagar"
#define LOCALIZED_EDITPROCEDURE                 "Editar"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     "Mudar Cor"
#define LOCALIZED_SETCOLOR_PENCOLOR            "Cor do Lápis"
#define LOCALIZED_SETCOLOR_FLOODCOLOR          "Cor de Preenchimento"
#define LOCALIZED_SETCOLOR_SCREENCOLOR         "Cor de Fundo"
#define LOCALIZED_SETCOLOR_RED                 "Vermelho"
#define LOCALIZED_SETCOLOR_GREEN               "Verde"
#define LOCALIZED_SETCOLOR_BLUE                "Azul"
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON // NOT_YET_LOCALIZED

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   "Tamanho do Lápis"
#define LOCALIZED_SETPENSIZE_SIZE              "Espessura"
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     "Sobre o " LOCALIZED_GENERAL_PRODUCTNAME
#define LOCALIZED_ABOUTFMS_VERSION             "Versão"
#define LOCALIZED_ABOUTFMS_GUI                 "GUI por George Mills\nSoftronics, Inc.\nhttp://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_CORE                "Núcleo por Brian Harvey\nUniversity of California Berkeley"
#define LOCALIZED_ABOUTFMS_INSTALLER           "Instalador baseado no Nullsoft Scriptable Install System\nhttp://nsis.sourceforge.net/"
#define LOCALIZED_ABOUTFMS_ADVENTURE           "Recursos para Logo em Português\nDisponíveis em http://mondragon.angeltowns.net/paradiso/"
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       "Agradecimento a Yehuda Katz e a Erich Neuwirth"
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME " é software livre\nVer a Licença Pública GNU"
#define LOCALIZED_ABOUTFMS_NEWSGROUP           "Perguntas, comentários, sugestões?\nParticipe da lista Logo em Espanhol\nhttp://mondragon.angeltowns.net/paradiso/ListaLogo.html"
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     "Tradução feita por Alexandre R. Soares"
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      "Sobre o FMS"
#define LOCALIZED_ABOUTMS_FMS                  "FMS quer dizer Fight Multiple Sclerosis."
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     "Considere fazer uma doação à\nNational Multiple Sclerosis Society.\nhttp://www.nmss.org\n1-800-FIGHT-MS"
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

#define LOCALIZED_CHANGESINEDITORMAYBELOST  "As mudanças da edição podem ser perdidas.\n\nRealmente quer sair do " LOCALIZED_GENERAL_PRODUCTNAME "?"
#define LOCALIZED_EDITSESSIONISRUNNING      "Uma sessão de edição está ativa"

#define LOCALIZED_COULDNOTWRITEBMP            "Não pude guardar .bmp"
#define LOCALIZED_COULDNOTOPENBMP             "Não pude abrir .bmp"
#define LOCALIZED_COULDNOTCREATEBMP           "Não pude criar bitmat tipo Windows 3.0"
#define LOCALIZED_NOTVALIDBMP                 "Não é um bitmap tipo Windows 3.0"

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         "Não foi guardado no disco"
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     "Escolher Novo apagará todas as definições.\n\nContinuar com Novo?"
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE "O arquivo que está sendo carregado será unido ao seu trabalho atual\ne substituirá suas alterações não guardadas.\n\nContinuar com Carregar?"
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    "Isto apagará todas as suas alterações não guardadas.\n\nContinuar com Abrir?"

#define LOCALIZED_EDITORISOPEN                  "Sabia que está com uma sessão de edição ativa?\n\nToda alteração nesta sessão de edição não será guardada."

#define LOCALIZED_ERROR_CANTREADFILE            "Não posso ler o arquivo \"%s\" do disco"
#define LOCALIZED_ERROR_CANTWRITEFILE           "Não posso escrever o arquivo \"%s\" no disco"

#define LOCALIZED_SAVETOWORKSPACE                "Guardar na área de trabalho"
#define LOCALIZED_CONTENTSCHANGED                "O conteúdo foi alterado"
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE "O conteúdo foi alterado.\nDeseja guardá-los na área de trabalho?"



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  "Houve um erro ao guardar o conteúdo do editor na área de trabalho.  O cursor será posicionado ante a última definição correta.\n\nVerifique uma possível mensagem de erro na Área de Comandos."
#define LOCALIZED_RETURNTOEDIT                  "Voltar ao editor?"

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

#define LOCALIZED_LOGO_FILE_EXTENSION "lgo"
#define LOCALIZED_FILEFILTER_ALLFILES "Todos os Arquivos (*.*)|*.*"
#define LOCALIZED_FILEFILTER_LOGO     "Arquivos do Logo (*.lgo)|*.lgo|" LOCALIZED_FILEFILTER_ALLFILES
#define LOCALIZED_FILEFILTER_IMAGE    "Arquivos Bitmap (*.bmp)|*.bmp|Arquivos GIF (*.gif)|*.gif|" LOCALIZED_FILEFILTER_ALLFILES



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             " interrompido\n"
#define LOCALIZED_TRACING_OUTPUTS           " devolve %s\n"
#define LOCALIZED_TRACING_MAKE              "atribua %s %s"
#define LOCALIZED_TRACING_PPROP             "mudePROP %s %s %s"
#define LOCALIZED_TRACING_LOCATION          " em %s\n%s"

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  "Passo Simples"

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  "%s definido\n"


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    "Borracha"
#define LOCALIZED_PENMODE_REVERSE  "UseInversor"
#define LOCALIZED_PENMODE_PAINT    "UseLápis"

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          "Logo: Erro Interno Fatal"
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       "Logo: Falta de Memória"
#define LOCALIZED_ERROR_OUTOFMEMORY            "sem espaço"
#define LOCALIZED_ERROR_STACKOVERFLOW          "esvaziamento de pilha"
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      "tat fora dos limites"
#define LOCALIZED_ERROR_BADGRAPHINIT           "não pude inicializar gráfico"
#define LOCALIZED_ERROR_BADDATA                "%p não sabe o que fazer com %s"
#define LOCALIZED_ERROR_DIDNTOUTPUT            "%p não devolveu nada para %p"
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        "%p necessita de algum complemento"
#define LOCALIZED_ERROR_TOOMUCH                "muitas coisas entre parênteses ()"
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    "Você não disse o que devo fazer com %s"
#define LOCALIZED_ERROR_PARENMISMATCH          "muitos parênteses '('"
#define LOCALIZED_ERROR_NOVALUE                "%s não possui um valor"
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        "parênteses ')' inesperado"
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      "colchete ']' inesperado"
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        "chave '}' inesperada"
#define LOCALIZED_ERROR_DONTKNOWHOWTO          "não sei como fazer %p"
#define LOCALIZED_ERROR_NOCATCHTAG             "não pude encontrar a etiqueta LANCE (THROW) para %p"
#define LOCALIZED_ERROR_ALREADYDEFINED         "%p já está definido"
#define LOCALIZED_ERROR_STOPPING               "Parando..."
#define LOCALIZED_ERROR_ALREADYDRIBBLING       "ECO está ativado"
#define LOCALIZED_ERROR_FILESYSTEM                   "Erro do sistema de arquivos: %p"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          "Não pude abrir esse arquivo"
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         "Não pude abrir o arquivo: %t"
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       "Arquivo já está aberto"
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           "Arquivo não está aberto"
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  "Não pude criar arquivo para editor"
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   "Não pude iniciar editor"
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    "Não pude ler arquivo do editor"
#define LOCALIZED_ERROR_IFWARNING              "Creio que queira usar SESENÃO (IFELSE), não SEFOR (IF)"
#define LOCALIZED_ERROR_SHADOWWARNING          "%p coberta por local em chamada a procedimento"
#define LOCALIZED_ERROR_USER                   "PEGUE \"Erro"
#define LOCALIZED_ERROR_ISPRIMITIVE            "%p é uma primitiva"
#define LOCALIZED_ERROR_TONOTINSIDE            "Só é possível usar APRENDA (TO) dentro de um procedimento"
#define LOCALIZED_ERROR_ATTOPLEVEL             "Só é possível usar %p dentro de um procedimento"
#define LOCALIZED_ERROR_ATTOPLEVEL2            "É necessário estar dentro de um procedimento para usar DEVOLVA (OUTPUT) ou PARE (STOP)."
#define LOCALIZED_ERROR_NOTEST                 "%p sem TESTE"
#define LOCALIZED_ERROR_BADMACROOUTPUT         "Macro devolveu %s em lugar de uma lista"
#define LOCALIZED_ERROR_DEEPEND                "FIM dentro de uma instrução multilinha"
#define LOCALIZED_ERROR_DEEPENDIN              "FIM dentro de uma instrução multilinha em %p"
#define LOCALIZED_ERROR_UNKNOWN                "Estado de erro desconhecido  - erro interno."
#define LOCALIZED_PAUSING                      "Pausando..."


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION "Invalid state for instruction: %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MODE_ON_SPRITE             "cannot set the mode of a turtle with a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        "cannot make a special turtle use a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            "cannot use the clipboard as a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_SPECIALFORM                "%p doesn't like %p as input because it has a special form" // NOT_YET_LOCALIZED

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      "Erro"
#define LOCALIZED_ERROR_BADINPUT             "Entrada incorreta"
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    "Entrada sem par"

#define LOCALIZED_ERROR_CANTOPENPORT         "Não foi possível ABRIR a porta"
#define LOCALIZED_ERROR_CANTCLOSEPORT        "Não foi possível FECHAR a porta"
#define LOCALIZED_ERROR_CANTFLUSHPORT        "Não foi possível ESVAZIAR a porta"
#define LOCALIZED_ERROR_CANTDCBONPORT        "Não foi possível construir dcb na porta"
#define LOCALIZED_ERROR_CANTSETPORT          "Não foi possível mudar a porta"
#define LOCALIZED_ERROR_PORTALREADYOPEN      "PORTA já aberta"
#define LOCALIZED_ERROR_PORTNOTOPEN          "PORTA não aberta"

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   "%s já existe"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    "%s não existe"

#define LOCALIZED_ERROR_DLLNOTLOADED          "A DLL não está carregada"
#define LOCALIZED_ERROR_DLLLOADFAILED         "Falha ao carregar a DLL"
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    "Tipo inválido de entrada"
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  "Tipo inválido de saída"
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   "Função não encontrada"
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  "Nem todas as entradas estão emparelhadas"

#define LOCALIZED_ERROR_NETWORK               "Erro de Rede"
#define LOCALIZED_ERROR_NETWORKRECEIVE        "Erro de Recepção de Rede"
#define LOCALIZED_ERROR_NETWORKSEND           "Erro de Envio de Rede"
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       "Erro Inesperado, a Rede poderia estar inativa"
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     "Não iniciada"
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED "Já iniciada"
#define LOCALIZED_ERROR_NETWORKALREADYON      "Já está pronta"
#define LOCALIZED_ERROR_NETWORKALREADYOFF     "Já desligada"

// The rest of the network errors shouldn't really be seen -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         "Nome muito longo"
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      "Não inicializado"
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      "O sistema não está pronto"
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED "Versão desconhecida"
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   "Não posso enviar após desativar o soquete"
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         "Chamada o sistema interrompida"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    "Resposta Autoritativa: Dominio não encontrado"
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH "Não-Autoritativa: Dominio no encontrado. Ver INICIARED"
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      "Erro irrecuperável"
#define LOCALIZED_ERROR_NETWORKNODATA              "Registro de dados não disponível"
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       "Número de arquivo incorreto"
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          "A operação bloquearia"
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       "Operação em curso"
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   "Operação já em curso"
#define LOCALIZED_ERROR_NETWORKBADADDRESS          "Endereço incorreto"
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     "Necessito endereço de destino"
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      "Mensagem muito longa"
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      "Familía do protocolo desconhecida"
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         "O diretório não está vazio"
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     "Atingido limite da aplicação"
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           "Superado limite do disco"
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        "Muitos arquivos abertos"
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        "Acesso negado"
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          "Operação de soquete em algo que não é um soquete"
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    "Não pude encontrar endereço pedido"
#define LOCALIZED_ERROR_NETWORKADDRINUSE           "O endereço já está em uso"
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      "Família de endereço não é reconhecida pelo protocolo"
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            "Tempo de tentativa de conexão excedido"
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    "Tipo de soquete desconhecido"
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   "Protocolo desconhecido"
#define LOCALIZED_ERROR_NETWORKNOBUFFER            "Sem espaço na memória temporária"
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    "Soquete já está conectado"
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        "Soquete não está conectado"
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         "Opção de protocolo incorreta"
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     "Conexão reiniciada pelo interlocutor"
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     "O software ocasionou o fim da conexão"
#define LOCALIZED_ERROR_NETWORKISDOWN              "A rede caiu"
#define LOCALIZED_ERROR_NETWORKRESET               "A rede foi reiniciada"
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   "Conexão recusada"
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          "Domínio caiu"
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   "Domínio não alcançável"
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        "O protocolo é de tipo equivocado para o soquete"
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   "Operação não permitida no soquete"
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         "Não foi encontrada rota para o domínio remoto"
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         "Demasiadas referências"

#define LOCALIZED_ERROR_POLYSTART               "Erro em IniciePolígono"
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED "Você já havia iniciado um polígono"

#define LOCALIZED_ERROR_POLYEND                 "Erro em MostrePolígono"
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       "Você não iniciou um polígono"
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     "É necessário ao menos 3 vetores para definir um polígono"

#define LOCALIZED_ERROR_SOUND                 "Erro de Som"

#define LOCALIZED_ERROR_MIDI                  "Erro de MIDI"
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     "Dispositivo Midi incorreto"
#define LOCALIZED_ERROR_MIDIALREADYOPEN       "Já está aberto"
#define LOCALIZED_ERROR_MIDINOTOPEN           "Não está aberto"

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      "Não há texto no clipboard"

#define LOCALIZED_ERROR_MCI                   "Erro de MCI"

#define LOCALIZED_ERROR_TIMERNOTFOUND         "Temporizador não encontrado"

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       "Ajuda on line não disponível pois não pude carregar hhctrl.ocx"

#define LOCALIZED_ERROR_BADCOMMANDLINE        "Linha de comandos incorreta"

#define LOCALIZED_ERROR_TMPNOTDEFINED         "A variável de ambiente TMP não está definida ou é incorreta.\n" LOCALIZED_GENERAL_PRODUCTNAME " tentará usar C:\\ para guardar arquivos temporários"

#define LOCALIZED_ERROR_GIFSAVEFAILED         "Problema ao criar GIF, revise quantidade de memória ou espaço em disco"
#define LOCALIZED_ERROR_GIFREADFAILED         "Problema ao ler GIF, revise quantidade de memória ou espaço em disco"

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  "Índice de BitMap fora do campo"
#define LOCALIZED_ERROR_BITMAPCUTFAILED        "Recortar falhou, possivelmente não haja memória suficiente"

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    "Nada para Colar"
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  "O BitMap no índice deve ser inicializado com um mapa de bits"

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      "A Tat %d não tem figura, farei uma parada"

#define LOCALIZED_ERROR_FONTNOTFOUND            "Não encontrei o tipo de letra chamado %s. Escolhe um dos seguintes:\n"

#define LOCALIZED_ERROR_PRINTERCANTSCALE        "O gerenciador de impressão não conhece esta função"
#define LOCALIZED_ERROR_CANTDRAWIMAGE           "Não posso desenhar a imagem"
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        "Não posso extrair a imagem"
#define LOCALIZED_ERROR_SUBCODE                 "Subcódigo"

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         "Entrada:"
#define LOCALIZED_PROMPT_TO     "Modo Para (Cancelar para Finalizar)"
#define LOCALIZED_PROMPT_LIST   "Modo de Lista (Cancelar para Parar)"
#define LOCALIZED_PROMPT_PAUSE  "Modo de Pausa (Cancelar para Continuar)"
#define LOCALIZED_PROMPT_INPUT  "Modo de Entrada (Cancelar para Parar)"

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      "Mudado para  \"%s\""
#define LOCALIZED_FILE_CHDIRFAILED         "Não pude mudar para o diretório \"%s\""
#define LOCALIZED_FILE_POPPEDTO            "Mudado para \"%s\""
#define LOCALIZED_FILE_MKDIRSUCCEEDED      "Agora estamos no novo diretório criado \"%s\""
#define LOCALIZED_FILE_MKDIRFAILED         "Não pude criar diretório \"%s\""
#define LOCALIZED_FILE_RMDIRSUCCEEDED      "Diretório Eliminado \"%s\""
#define LOCALIZED_FILE_RMDIRFAILED         "Não pude eliminar o diretório \"%s\""
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  "O diretório não existe"
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY "Assegure-se que o diretório esteja vazio antes de eliminá-lo."


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       "Desenho no Logo"

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    "Área Ativa"
#define LOCALIZED_INFORMATION   "Informação"
#define LOCALIZED_WARNING       "Atenção"
#define LOCALIZED_UNTITLED      "Sem nome"
#define LOCALIZED_UNKNOWN       "Desconhecido"

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       "Não demarcado"

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     "Localizar"
#define LOCALIZED_EDITOR_TITLE_REPLACE  "Substituir"

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING "%s no encontrado"


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
#define LOCALIZED_COLOR_ALICEBLUE             "AzulAlice"
#define LOCALIZED_COLOR_ANTIQUEWHITE          "BrancoAntigo"
#define LOCALIZED_COLOR_AQUA                  "Água"
#define LOCALIZED_COLOR_AQUAMARINE            "Águamarinha"
#define LOCALIZED_COLOR_AZURE                 "AzulCeleste"
#define LOCALIZED_COLOR_BEIGE                 "Bege"
#define LOCALIZED_COLOR_BISQUE                "CremeDeMarisco"
#define LOCALIZED_COLOR_BLACK                 "Preto"
#define LOCALIZED_COLOR_BLANCHEDALMOND        "Amêndoa"
#define LOCALIZED_COLOR_BLUE                  "Azul"
#define LOCALIZED_COLOR_BLUEVIOLET            "AzulVioleta"
#define LOCALIZED_COLOR_BROWN                 "MarromClaro"
#define LOCALIZED_COLOR_BURLYWOOD             "Madeira"
#define LOCALIZED_COLOR_CADETBLUE             "AzulCadete"
#define LOCALIZED_COLOR_CHARTREUSE            "VerdeParis"
#define LOCALIZED_COLOR_CHOCOLATE             "Chocolate"
#define LOCALIZED_COLOR_CORAL                 "Coral"
#define LOCALIZED_COLOR_CORNFLOWERBLUE        "AzulFlordeMilho"
#define LOCALIZED_COLOR_CORNSILK              "Milho"
#define LOCALIZED_COLOR_CRIMSON               "Carmim"
#define LOCALIZED_COLOR_CYAN                  "Ciano"
#define LOCALIZED_COLOR_DARKBLUE              "AzulEscuro"
#define LOCALIZED_COLOR_DARKCYAN              "CianoEscuro"
#define LOCALIZED_COLOR_DARKGOLDENROD         "DouradoEscuro"
#define LOCALIZED_COLOR_DARKGRAY              "CinzaEscuro"
#define LOCALIZED_COLOR_DARKGREEN             "VerdeEscuro"
#define LOCALIZED_COLOR_DARKGREY              "CinzaEscuro"
#define LOCALIZED_COLOR_DARKKHAKI             "CaquiEscuro"
#define LOCALIZED_COLOR_DARKMAGENTA           "MagentaEscuro"
#define LOCALIZED_COLOR_DARKOLIVEGREEN        "OlivaEscuro"
#define LOCALIZED_COLOR_DARKORANGE            "LaranjaEscuro"
#define LOCALIZED_COLOR_DARKORCHID            "OrquídeaEscuro"
#define LOCALIZED_COLOR_DARKRED               "VermelhoEscuro"
#define LOCALIZED_COLOR_DARKSALMON            "SalmãoEscuro"
#define LOCALIZED_COLOR_DARKSEAGREEN          "VerdeMarEscuro"
#define LOCALIZED_COLOR_DARKSLATEBLUE         "AzulPardoEscuro"
#define LOCALIZED_COLOR_DARKSLATEGRAY         "CinzaPardoEscuro"
#define LOCALIZED_COLOR_DARKSLATEGREY         "CinzaPardoEscuro"
#define LOCALIZED_COLOR_DARKTURQUOISE         "TurquesaEscuro"
#define LOCALIZED_COLOR_DARKVIOLET            "VioletaEscuro"
#define LOCALIZED_COLOR_DEEPPINK              "RosaProfundo"
#define LOCALIZED_COLOR_DEEPSKYBLUE           "AzulCelesteProfundo"
#define LOCALIZED_COLOR_DIMGRAY               "CinzaFosco"
#define LOCALIZED_COLOR_DIMGREY               "CinzaSuave"
#define LOCALIZED_COLOR_DODGERBLUE            "AzulFurtivo"
#define LOCALIZED_COLOR_FIREBRICK             "VermelhoTijolo"
#define LOCALIZED_COLOR_FLORALWHITE           "BrancoFloral"
#define LOCALIZED_COLOR_FORESTGREEN           "VerdeFloresta"
#define LOCALIZED_COLOR_FUCHSIA               "Fúcsia"
#define LOCALIZED_COLOR_GAINSBORO             "CinzaMédio"
#define LOCALIZED_COLOR_GHOSTWHITE            "BrancoLigeiro"
#define LOCALIZED_COLOR_GOLD                  "Ouro"
#define LOCALIZED_COLOR_GOLDENROD             "Dourado"
#define LOCALIZED_COLOR_GRAY                  "Prata"
#define LOCALIZED_COLOR_GREEN                 "Verde"
#define LOCALIZED_COLOR_GREENYELLOW           "AmareloEsverdeado"
#define LOCALIZED_COLOR_GREY                  "Cinza"
#define LOCALIZED_COLOR_HONEYDEW              "Maná"
#define LOCALIZED_COLOR_HOTPINK               "RosaQuente"
#define LOCALIZED_COLOR_INDIANRED             "VermelhoIndiano"
#define LOCALIZED_COLOR_INDIGO                "Anil"
#define LOCALIZED_COLOR_IVORY                 "Marfim"
#define LOCALIZED_COLOR_KHAKI                 "Caqui"
#define LOCALIZED_COLOR_LAVENDER              "Lavanda"
#define LOCALIZED_COLOR_LAVENDERBLUSH         "RosaLavanda"
#define LOCALIZED_COLOR_LAWNGREEN             "VerdeGrama"
#define LOCALIZED_COLOR_LEMONCHIFFON          "Seda"
#define LOCALIZED_COLOR_LIGHTBLUE             "AzulClaro"
#define LOCALIZED_COLOR_LIGHTCORAL            "CoralClaro"
#define LOCALIZED_COLOR_LIGHTCYAN             "CianoClaro"
#define LOCALIZED_COLOR_LIGHTGOLDENRODYELLOW  "AmareloDouradoClaro"
#define LOCALIZED_COLOR_LIGHTGRAY             "CinzaClaro"
#define LOCALIZED_COLOR_LIGHTGREEN            "VerdeClaro"
#define LOCALIZED_COLOR_LIGHTGREY             "CinzaClaro"
#define LOCALIZED_COLOR_LIGHTPINK             "RosaClaro"
#define LOCALIZED_COLOR_LIGHTSALMON           "SalmãoClaro"
#define LOCALIZED_COLOR_LIGHTSEAGREEN         "VerdeMarinhoClaro"
#define LOCALIZED_COLOR_LIGHTSKYBLUE          "AzulCelesteClaro"
#define LOCALIZED_COLOR_LIGHTSLATEGRAY        "CinzaPardoClaro"
#define LOCALIZED_COLOR_LIGHTSLATEGREY        "CinzaPardoClaro"
#define LOCALIZED_COLOR_LIGHTSTEELBLUE        "AzulAçoClaro"
#define LOCALIZED_COLOR_LIGHTYELLOW           "AmareloClaro"
#define LOCALIZED_COLOR_LIME                  "Lima"
#define LOCALIZED_COLOR_LIMEGREEN             "VerdeLima"
#define LOCALIZED_COLOR_LINEN                 "Linho"
#define LOCALIZED_COLOR_MAGENTA               "Magenta"
#define LOCALIZED_COLOR_MAROON                "Marrom"
#define LOCALIZED_COLOR_MEDIUMAQUAMARINE      "ÁguaMarinhaMédio"
#define LOCALIZED_COLOR_MEDIUMBLUE            "AzulMédio"
#define LOCALIZED_COLOR_MEDIUMORCHID          "OrquídeaMédio"
#define LOCALIZED_COLOR_MEDIUMPURPLE          "PúrpuraMédio"
#define LOCALIZED_COLOR_MEDIUMSEAGREEN        "VerdeMarMédio"
#define LOCALIZED_COLOR_MEDIUMSLATEBLUE       "AzulPardoMédio"
#define LOCALIZED_COLOR_MEDIUMSPRINGGREEN     "VerdePrimaveraMédio"
#define LOCALIZED_COLOR_MEDIUMTURQUOISE       "TurquesaMédio"
#define LOCALIZED_COLOR_MEDIUMVIOLETRED       "VioletaMédio"
#define LOCALIZED_COLOR_MIDNIGHTBLUE          "AzulMeiaNoite"
#define LOCALIZED_COLOR_MINTCREAM             "CremeDeMenta"
#define LOCALIZED_COLOR_MISTYROSE             "RosaBrumoso"
#define LOCALIZED_COLOR_MOCCASIN              "Mocassim"
#define LOCALIZED_COLOR_NAVAJOWHITE           "BrancoNavajo"
#define LOCALIZED_COLOR_NAVY                  "Marinho"
#define LOCALIZED_COLOR_OLDLACE               "RendaAntiga"
#define LOCALIZED_COLOR_OLIVE                 "Oliva"
#define LOCALIZED_COLOR_OLIVEDRAB             "OlivaPardo"
#define LOCALIZED_COLOR_ORANGE                "Laranja"
#define LOCALIZED_COLOR_ORANGERED             "Alaranjado"
#define LOCALIZED_COLOR_ORCHID                "Orquídea"
#define LOCALIZED_COLOR_PALEGOLDENROD         "DouradoPálido"
#define LOCALIZED_COLOR_PALEGREEN             "VerdePálido"
#define LOCALIZED_COLOR_PALETURQUOISE         "TurquesaPálido"
#define LOCALIZED_COLOR_PALEVIOLETRED         "VioletaPálido"
#define LOCALIZED_COLOR_PAPAYAWHIP            "Papaia"
#define LOCALIZED_COLOR_PEACHPUFF             "Pêssego"
#define LOCALIZED_COLOR_PERU                  "Peru"
#define LOCALIZED_COLOR_PINK                  "Rosa"
#define LOCALIZED_COLOR_PLUM                  "Ameixa"
#define LOCALIZED_COLOR_POWDERBLUE            "AzulPólvora"
#define LOCALIZED_COLOR_PURPLE                "Púrpura"
#define LOCALIZED_COLOR_RED                   "Vermelho"
#define LOCALIZED_COLOR_ROSYBROWN             "MarromRosado"
#define LOCALIZED_COLOR_ROYALBLUE             "AzulReal"
#define LOCALIZED_COLOR_SADDLEBROWN           "MarromTelha"
#define LOCALIZED_COLOR_SALMON                "Salmão"
#define LOCALIZED_COLOR_SANDYBROWN            "MarromAreia"
#define LOCALIZED_COLOR_SEAGREEN              "VerdeMarinho"
#define LOCALIZED_COLOR_SEASHELL              "Concha"
#define LOCALIZED_COLOR_SIENNA                "Siena"
#define LOCALIZED_COLOR_SILVER                "Prata"
#define LOCALIZED_COLOR_SKYBLUE               "AzulCéu"
#define LOCALIZED_COLOR_SLATEBLUE             "AzulPardo"
#define LOCALIZED_COLOR_SLATEGRAY             "CinzaPardo"
#define LOCALIZED_COLOR_SLATEGREY             "CinzaPardo"
#define LOCALIZED_COLOR_SNOW                  "Neve"
#define LOCALIZED_COLOR_SPRINGGREEN           "VerdePrimavera"
#define LOCALIZED_COLOR_STEELBLUE             "AzulAço"
#define LOCALIZED_COLOR_TAN                   "Bronzeado"
#define LOCALIZED_COLOR_TEAL                  "VerdeAzulado"
#define LOCALIZED_COLOR_THISTLE               "Cardo"
#define LOCALIZED_COLOR_TOMATO                "Tomate"
#define LOCALIZED_COLOR_TURQUOISE             "Turquesa"
#define LOCALIZED_COLOR_VIOLET                "Violeta"
#define LOCALIZED_COLOR_WHEAT                 "Trigo"
#define LOCALIZED_COLOR_WHITE                 "Branco"
#define LOCALIZED_COLOR_WHITESMOKE            "FumaçaBranca"
#define LOCALIZED_COLOR_YELLOW                "Amarelo"
#define LOCALIZED_COLOR_YELLOWGREEN           "VerdeAmarelado"

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
