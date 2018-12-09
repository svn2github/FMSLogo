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
// This file contains localized strings for Russian by Igor Baglaev
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
//   "Impossible d'utiliser POUR (TO) dans une procйdure"
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
#define LOCALIZED_ALTERNATE_TRUE     "истина" 
#define LOCALIZED_ALTERNATE_FALSE    "ложь" 
#define LOCALIZED_ALTERNATE_END      "конец"
#define LOCALIZED_ALTERNATE_TOPLEVEL "верхнийуровень" 
#define LOCALIZED_ALTERNATE_SYSTEM   "система" 

//
// Localized "alternate" names of Logo special variables
//
#define LOCALIZED_ALTERNATE_CASEIGNOREDP    "игноририроватьрегистрпи" 
#define LOCALIZED_ALTERNATE_ERRACT          "альтош" 
#define LOCALIZED_ALTERNATE_STARTUP         "запуск" 
#define LOCALIZED_ALTERNATE_REDEFP          "переопрпи" 
#define LOCALIZED_ALTERNATE_PRINTWIDTHLIMIT "максширпеч" 
#define LOCALIZED_ALTERNATE_PRINTDEPTHLIMIT "максглубпеч"


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
#define LOCALIZED_ALTERNATE__DEFMACRO              ".опрмакрос"
#define LOCALIZED_ALTERNATE__EQ                    ".равн" 
#define LOCALIZED_ALTERNATE__MACRO                 ".макрос"
#define LOCALIZED_ALTERNATE__MAYBEOUTPUT           ".альтвывод" 
#define LOCALIZED_ALTERNATE__SETBF                 ".вставькпе" 
#define LOCALIZED_ALTERNATE__SETFIRST              ".вставьпервым" 
#define LOCALIZED_ALTERNATE__SETITEM               ".новэлемент" 
#define LOCALIZED_ALTERNATE_ACTIVEAREA             "активноеполе" 
#define LOCALIZED_ALTERNATE_ALLOPEN                "откройвсе" 
#define LOCALIZED_ALTERNATE_AND                    "кон"
#define LOCALIZED_ALTERNATE_APPLY                  "применить" 
#define LOCALIZED_ALTERNATE_ARCCOS                 "arccos" 
#define LOCALIZED_ALTERNATE_ARCSIN                 "arcsin" 
#define LOCALIZED_ALTERNATE_ARCTAN                 "arctg" 
#define LOCALIZED_ALTERNATE_ARITY                  "arity" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARRAY                  "массив"
#define LOCALIZED_ALTERNATE_ARRAYP                 "массивпи" 
#define LOCALIZED_ALTERNATE_ARRAY_                 "массив?" 
#define LOCALIZED_ALTERNATE_ASCII                  "код" 
#define LOCALIZED_ALTERNATE_ASHIFT                 "асдвиг" 
#define LOCALIZED_ALTERNATE_BACK                   "назад"
#define LOCALIZED_ALTERNATE_BACKSLASHEDP           "спецсимволпи" 
#define LOCALIZED_ALTERNATE_BACKSLASHED_           "спецсимвол?" 
#define LOCALIZED_ALTERNATE_BEFOREP                "передпи" 
#define LOCALIZED_ALTERNATE_BEFORE_                "передпи?" 
#define LOCALIZED_ALTERNATE_BF                     "кпе"
#define LOCALIZED_ALTERNATE_BFS                    "кпех" 
#define LOCALIZED_ALTERNATE_BITAND                 "поразряди" 
#define LOCALIZED_ALTERNATE_BITBLOCK               "растрблок" 
#define LOCALIZED_ALTERNATE_BITCOPY                "растркопируй" 
#define LOCALIZED_ALTERNATE_BITCUT                 "растрвырежи" 
#define LOCALIZED_ALTERNATE_BITFIT                 "растрподгони" 
#define LOCALIZED_ALTERNATE_BITINDEX               "растриндекс" 
#define LOCALIZED_ALTERNATE_BITLOAD                "растрзагрузи" 
#define LOCALIZED_ALTERNATE_BITLOADSIZE            "размеррастрзагрузки" 
#define LOCALIZED_ALTERNATE_BITSIZE                "размеррастра" 
#define LOCALIZED_ALTERNATE_BITMAPTURTLE           "растртортила" 
#define LOCALIZED_ALTERNATE_BITMODE                "режимрастра" 
#define LOCALIZED_ALTERNATE_BITNOT                 "поразрнет" 
#define LOCALIZED_ALTERNATE_BITOR                  "поразрили"
#define LOCALIZED_ALTERNATE_BITPASTE               "растрвставь"
#define LOCALIZED_ALTERNATE_BITPASTETOINDEX        "растрвставьпоинд"
#define LOCALIZED_ALTERNATE_BITSAVE                "растрсохрани"
#define LOCALIZED_ALTERNATE_BITXOR                 "поразрисклили"
#define LOCALIZED_ALTERNATE_BK                     "нд"
#define LOCALIZED_ALTERNATE_BL                     "кпо"
#define LOCALIZED_ALTERNATE_BURIED                 "скрытые" 
#define LOCALIZED_ALTERNATE_BURY                   "скрой" 
#define LOCALIZED_ALTERNATE_BUTFIRST               "кромепервого"
#define LOCALIZED_ALTERNATE_BUTFIRSTS              "кромепервых" 
#define LOCALIZED_ALTERNATE_BUTLAST                "кромепоследнего"
#define LOCALIZED_ALTERNATE_BUTTONCREATE           "кнопкусоздай"
#define LOCALIZED_ALTERNATE_BUTTONDELETE           "кнопкуудали" 
#define LOCALIZED_ALTERNATE_BUTTONENABLE           "кнопкудопусти" 
#define LOCALIZED_ALTERNATE_BUTTONUPDATE           "кнопкуобнови" 
#define LOCALIZED_ALTERNATE_BUTTONP                "кнопкапи" 
#define LOCALIZED_ALTERNATE_BUTTON_                "кнопка?" 
#define LOCALIZED_ALTERNATE_BYE                    "пока" 
#define LOCALIZED_ALTERNATE_CATCH                  "захват" 
#define LOCALIZED_ALTERNATE_CHAR                   "символ"
#define LOCALIZED_ALTERNATE_CHDIR                  "измпап" 
#define LOCALIZED_ALTERNATE_CHECKBOXCREATE         "переключсоздай" 
#define LOCALIZED_ALTERNATE_CHECKBOXDELETE         "переключудали"
#define LOCALIZED_ALTERNATE_CHECKBOXENABLE         "переключдопусти" 
#define LOCALIZED_ALTERNATE_CHECKBOXGET            "переключсост" 
#define LOCALIZED_ALTERNATE_CHECKBOXSET            "переключзадай" 
#define LOCALIZED_ALTERNATE_CLEAN                  "очисти" 
#define LOCALIZED_ALTERNATE_CLEARPALETTE           "сотрипалитру" 
#define LOCALIZED_ALTERNATE_CLEARSCREEN            "очистиэкран"
#define LOCALIZED_ALTERNATE_CLEARTEXT              "очиститекст" 
#define LOCALIZED_ALTERNATE_CLEARTIMER             "очиститаймер" 
#define LOCALIZED_ALTERNATE_CLOSE                  "закрой" 
#define LOCALIZED_ALTERNATE_CLOSEALL               "закройвсе" 
#define LOCALIZED_ALTERNATE_CO                     "прод" 
#define LOCALIZED_ALTERNATE_COMBOBOXADDSTRING      "добстрвполе" 
#define LOCALIZED_ALTERNATE_COMBOBOXCREATE         "полесоздай" 
#define LOCALIZED_ALTERNATE_COMBOBOXDELETE         "полеудали" 
#define LOCALIZED_ALTERNATE_COMBOBOXENABLE         "поледопусти" 
#define LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING   "удалистрокуполя" 
#define LOCALIZED_ALTERNATE_COMBOBOXGETTEXT        "текстполя" 
#define LOCALIZED_ALTERNATE_COMBOBOXSETTEXT        "задатьтекстполя" 
#define LOCALIZED_ALTERNATE_CONTENTS               "содержание" 
#define LOCALIZED_ALTERNATE_CONTINUE               "продолжи" 
#define LOCALIZED_ALTERNATE_COPYDEF                "переимен" 
#define LOCALIZED_ALTERNATE_COS                    "cos" 
#define LOCALIZED_ALTERNATE_COUNT                  "сколько"
#define LOCALIZED_ALTERNATE_CS                     "оэ"
#define LOCALIZED_ALTERNATE_CT                     "от" 
#define LOCALIZED_ALTERNATE_CURSOR                 "курсор" 
#define LOCALIZED_ALTERNATE_DEBUGWINDOWS           "окноотладки" 
#define LOCALIZED_ALTERNATE_DEFINE                 "определи" 
#define LOCALIZED_ALTERNATE_DEFINEDP               "определенпи" 
#define LOCALIZED_ALTERNATE_DEFINED_               "определен?" 
#define LOCALIZED_ALTERNATE_DIALOGCREATE           "диалогсоздай" 
#define LOCALIZED_ALTERNATE_DIALOGENABLE           "диалогдопусти" 
#define LOCALIZED_ALTERNATE_DIALOGDELETE           "диалогудали"
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         "диалогафайлоткрыть"
#define LOCALIZED_ALTERNATE_DIALOGFILESAVE         "окнофайлсохранить" 
#define LOCALIZED_ALTERNATE_DIFFERENCE             "разность"
#define LOCALIZED_ALTERNATE_DIRECTORIES            "папки" 
#define LOCALIZED_ALTERNATE_DLLCALL                "вызовбдк" 
#define LOCALIZED_ALTERNATE_DLLFREE                "снимибдк" 
#define LOCALIZED_ALTERNATE_DLLLOAD                "загрузиьбдк" 
#define LOCALIZED_ALTERNATE_DOWN                   "вниз" 
#define LOCALIZED_ALTERNATE_DOWNPITCH              "уклонвниз" 
#define LOCALIZED_ALTERNATE_DRIBBLE                "протокол" 
#define LOCALIZED_ALTERNATE_ED                     "ред" 
#define LOCALIZED_ALTERNATE_EDIT                   "редактировать" 
#define LOCALIZED_ALTERNATE_ELLIPSEARC             "дугаэллипса" 
#define LOCALIZED_ALTERNATE_EMPTYP                 "пустойпи" 
#define LOCALIZED_ALTERNATE_EMPTY_                 "пустой?" 
#define LOCALIZED_ALTERNATE_EOFP                   "кфлпи" 
#define LOCALIZED_ALTERNATE_EOF_                   "кфл?" 
#define LOCALIZED_ALTERNATE_EQUALP                 "равныйпи"
#define LOCALIZED_ALTERNATE_EQUAL_                 "equal?" 
#define LOCALIZED_ALTERNATE_ER                     "уд" 
#define LOCALIZED_ALTERNATE_ERASE                  "удали" 
#define LOCALIZED_ALTERNATE_ERASEFILE              "удалифайл" 
#define LOCALIZED_ALTERNATE_ERF                    "удф" 
#define LOCALIZED_ALTERNATE_ERROR                  "ошибка" 
#define LOCALIZED_ALTERNATE_EVENTCHECK             "контрсобытий" 
#define LOCALIZED_ALTERNATE_EXP                    "exp" 
#define LOCALIZED_ALTERNATE_FD                     "вп"
#define LOCALIZED_ALTERNATE_FENCE                  "ограждение" 
#define LOCALIZED_ALTERNATE_FILL                   "крась"
#define LOCALIZED_ALTERNATE_FILES                  "файлы" 
#define LOCALIZED_ALTERNATE_FIRST                  "первый"
#define LOCALIZED_ALTERNATE_FIRSTS                 "первые" 
#define LOCALIZED_ALTERNATE_FLOODCOLOR             "цветзаливки" 
#define LOCALIZED_ALTERNATE_FONTFACENAMES          "названиешрифта" 
#define LOCALIZED_ALTERNATE_FOREVER                "многократно" 
#define LOCALIZED_ALTERNATE_FORM                   "формат" 
#define LOCALIZED_ALTERNATE_FORWARD                "вперед"
#define LOCALIZED_ALTERNATE_FPUT                   "пвнач" 
#define LOCALIZED_ALTERNATE_FS                     "пэ" 
#define LOCALIZED_ALTERNATE_FULLSCREEN             "полныйэкран" 
#define LOCALIZED_ALTERNATE_FULLTEXT               "текстпроц" 
#define LOCALIZED_ALTERNATE_GETFOCUS               "активноеокно" 
#define LOCALIZED_ALTERNATE_GOTO                   "перейти" 
#define LOCALIZED_ALTERNATE_GIFLOAD                "загрузирис" 
#define LOCALIZED_ALTERNATE_GIFSIZE                "размеррис" 
#define LOCALIZED_ALTERNATE_GIFSAVE                "сохранирис" 
#define LOCALIZED_ALTERNATE_GPROP                  "выбсв" 
#define LOCALIZED_ALTERNATE_GREATEREQUALP          "больщеравнопи" 
#define LOCALIZED_ALTERNATE_GREATEREQUAL_          "большеравно?" 
#define LOCALIZED_ALTERNATE_GREATERP               "большепи"
#define LOCALIZED_ALTERNATE_GREATER_               "больше?" 
#define LOCALIZED_ALTERNATE_GROUPBOXCREATE         "группусоздай" 
#define LOCALIZED_ALTERNATE_GROUPBOXDELETE         "группуудали" 
#define LOCALIZED_ALTERNATE_HALT                   "останов" 
#define LOCALIZED_ALTERNATE_HASOWNPENP             "hasownpenp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HASOWNPEN_             "hasownpen?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HEADING                "направление" 
#define LOCALIZED_ALTERNATE_HELP                   "помощь" 
#define LOCALIZED_ALTERNATE_HIDETURTLE             "скройтортилу"
#define LOCALIZED_ALTERNATE_HOME                   "домой"
#define LOCALIZED_ALTERNATE_HT                     "ст"
#define LOCALIZED_ALTERNATE_IF                     "если"
#define LOCALIZED_ALTERNATE_IFELSE                 "еслииначе"
#define LOCALIZED_ALTERNATE_IFF                    "еслил" 
#define LOCALIZED_ALTERNATE_IFFALSE                "еслиложь" 
#define LOCALIZED_ALTERNATE_IFT                    "еслии" 
#define LOCALIZED_ALTERNATE_IFTRUE                 "еслиистина" 
#define LOCALIZED_ALTERNATE_INGAMEPORT             "портигры" 
#define LOCALIZED_ALTERNATE_INPORT                 "впорт" 
#define LOCALIZED_ALTERNATE_INPORTB                "впортб"
#define LOCALIZED_ALTERNATE_INT                    "целаячасть"
#define LOCALIZED_ALTERNATE_ITEM                   "элемент"
#define LOCALIZED_ALTERNATE_KEYBOARDOFF            "клавиатуруотключи" 
#define LOCALIZED_ALTERNATE_KEYBOARDON             "клавиатурувключи" 
#define LOCALIZED_ALTERNATE_KEYBOARDVALUE          "клавиатуруоцени" 
#define LOCALIZED_ALTERNATE_KEYP                   "клавищапи" 
#define LOCALIZED_ALTERNATE_KEY_                   "клавиша?" 
#define LOCALIZED_ALTERNATE_LABEL                  "надпись"
#define LOCALIZED_ALTERNATE_LABELFONT              "шрифтнадписи"
#define LOCALIZED_ALTERNATE_LABELSIZE              "размернадписи" 
#define LOCALIZED_ALTERNATE_LAST                   "последний"
#define LOCALIZED_ALTERNATE_LEFT                   "налево"
#define LOCALIZED_ALTERNATE_LEFTROLL               "левыйкрен" 
#define LOCALIZED_ALTERNATE_LESSEQUALP             "меньшеравнопи" 
#define LOCALIZED_ALTERNATE_LESSEQUAL_             "меньшеравно?" 
#define LOCALIZED_ALTERNATE_LESSP                  "меньшепи"
#define LOCALIZED_ALTERNATE_LESS_                  "меньше?" 
#define LOCALIZED_ALTERNATE_LIGHT                  "яркость" 
#define LOCALIZED_ALTERNATE_LIST                   "список"
#define LOCALIZED_ALTERNATE_LISTBOXADDSTRING       "спзапдобавьстроку" 
#define LOCALIZED_ALTERNATE_LISTBOXCREATE          "спзапсоздай" 
#define LOCALIZED_ALTERNATE_LISTBOXENABLE          "спзапдопусти" 
#define LOCALIZED_ALTERNATE_LISTBOXDELETE          "спзапудали" 
#define LOCALIZED_ALTERNATE_LISTBOXDELETESTRING    "спзапудалистроку" 
#define LOCALIZED_ALTERNATE_LISTBOXGETSELECT       "спзапвыбор" 
#define LOCALIZED_ALTERNATE_LISTP                  "списокпи" 
#define LOCALIZED_ALTERNATE_LIST_                  "списокпи?" 
#define LOCALIZED_ALTERNATE_LN                     "ln" 
#define LOCALIZED_ALTERNATE_LOAD                   "загрузи" 
#define LOCALIZED_ALTERNATE_LOCAL                  "локальный" 
#define LOCALIZED_ALTERNATE_LOG10                  "lg" 
#define LOCALIZED_ALTERNATE_LOGOVERSION            "версиялого" 
#define LOCALIZED_ALTERNATE_LOWERCASE              "строчный" 
#define LOCALIZED_ALTERNATE_LPUT                   "пвконец"
#define LOCALIZED_ALTERNATE_LR                     "лкр" 
#define LOCALIZED_ALTERNATE_LSHIFT                 "лсдвиг" 
#define LOCALIZED_ALTERNATE_LT                     "лв"
#define LOCALIZED_ALTERNATE_MACHINE                "машина" 
#define LOCALIZED_ALTERNATE_MACROP                 "макроспи" 
#define LOCALIZED_ALTERNATE_MACRO_                 "макрос?" 
#define LOCALIZED_ALTERNATE_MAKE                   "пусть"
#define LOCALIZED_ALTERNATE_MCI                    "мки" 
#define LOCALIZED_ALTERNATE_MEMBER                 "сэлемента"
#define LOCALIZED_ALTERNATE_MEMBERP                "элементпи"
#define LOCALIZED_ALTERNATE_MEMBER_                "элемент?" 
#define LOCALIZED_ALTERNATE_MESSAGEBOX             "окносообщений" 
#define LOCALIZED_ALTERNATE_MIDICLOSE              "мидизакрой" 
#define LOCALIZED_ALTERNATE_MIDIMESSAGE            "мидисообщение" 
#define LOCALIZED_ALTERNATE_MIDIOPEN               "мидиоткрой" 
#define LOCALIZED_ALTERNATE_MINUS                  "минус" 
#define LOCALIZED_ALTERNATE_MKDIR                  "сзпапку" 
#define LOCALIZED_ALTERNATE_MODULO                 "помодулю"
#define LOCALIZED_ALTERNATE_MOUSEOFF               "мышьвыкл"
#define LOCALIZED_ALTERNATE_MOUSEON                "мышьвкл"
#define LOCALIZED_ALTERNATE_MOUSEPOS               "мышьместо"
#define LOCALIZED_ALTERNATE_NAMEP                  "имяпи" 
#define LOCALIZED_ALTERNATE_NAME_                  "имя?" 
#define LOCALIZED_ALTERNATE_NAMES                  "имена" 
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           "подключениепосетивкл"
#define LOCALIZED_ALTERNATE_NETACCEPTON            "подключениепосетиоткл"
#define LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE  "значприемаполуч" 
#define LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE     "значотправкиполуч" 
#define LOCALIZED_ALTERNATE_NETCONNECTOFF          "связьпосетивыкл" 
#define LOCALIZED_ALTERNATE_NETCONNECTON           "связьпосетивкл" 
#define LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE "значприемасоед" 
#define LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE    "значотправкисоед" 
#define LOCALIZED_ALTERNATE_NETSHUTDOWN            "сетьоткл" 
#define LOCALIZED_ALTERNATE_NETSTARTUP             "сетьзапусти" 
#define LOCALIZED_ALTERNATE_NOBITMAPTURTLE         "нерастртортила" 
#define LOCALIZED_ALTERNATE_NODES                  "узлы" 
#define LOCALIZED_ALTERNATE_NODRIBBLE              "безпротокола" 
#define LOCALIZED_ALTERNATE_NOSTATUS               "безстатуса" 
#define LOCALIZED_ALTERNATE_NOT                    "не" 
#define LOCALIZED_ALTERNATE_NOTEQUALP              "неравнопи" 
#define LOCALIZED_ALTERNATE_NOTEQUAL_              "неравно?" 
#define LOCALIZED_ALTERNATE_NOYIELD                "неуступать" 
#define LOCALIZED_ALTERNATE_NUMBERP                "числопи" 
#define LOCALIZED_ALTERNATE_NUMBER_                "число?" 
#define LOCALIZED_ALTERNATE_OP                     "вд"
#define LOCALIZED_ALTERNATE_OPENAPPEND             "откройдляизм" 
#define LOCALIZED_ALTERNATE_OPENREAD               "откройдлячт" 
#define LOCALIZED_ALTERNATE_OPENUPDATE             "откройдляобн" 
#define LOCALIZED_ALTERNATE_OPENWRITE              "откройдлязап" 
#define LOCALIZED_ALTERNATE_OR                     "или" 
#define LOCALIZED_ALTERNATE_OUTPORT                "вдвпорт" 
#define LOCALIZED_ALTERNATE_OUTPORTB               "вдвпортб" 
#define LOCALIZED_ALTERNATE_OUTPUT                 "вывод"
#define LOCALIZED_ALTERNATE_PARSE                  "впредл" 
#define LOCALIZED_ALTERNATE_PAUSE                  "пауза" 
#define LOCALIZED_ALTERNATE_PC                     "цп" 
#define LOCALIZED_ALTERNATE_PD                     "по" 
#define LOCALIZED_ALTERNATE_PE                     "лк"
#define LOCALIZED_ALTERNATE_PENCOLOR               "цветпера"  
#define LOCALIZED_ALTERNATE_PENDOWN                "пероопусти"
#define LOCALIZED_ALTERNATE_PENDOWNP               "пероопущпи" 
#define LOCALIZED_ALTERNATE_PENDOWN_               "пероопущ?" 
#define LOCALIZED_ALTERNATE_PENERASE               "ластик"
#define LOCALIZED_ALTERNATE_PENMODE                "режимпера" 
#define LOCALIZED_ALTERNATE_PENPAINT               "пероручка"
#define LOCALIZED_ALTERNATE_PENPATTERN             "модельпера" 
#define LOCALIZED_ALTERNATE_PENREVERSE             "перообратное"
#define LOCALIZED_ALTERNATE_PENSIZE                "размерпера" 
#define LOCALIZED_ALTERNATE_PENUP                  "пероподними"
#define LOCALIZED_ALTERNATE_PERSPECTIVE            "пространственный" 
#define LOCALIZED_ALTERNATE_PITCH                  "уклон" 
#define LOCALIZED_ALTERNATE_PIXEL                  "пиксель" 
#define LOCALIZED_ALTERNATE_PLAYWAVE               "воспроизвзвук" 
#define LOCALIZED_ALTERNATE_PLIST                  "списоксв" 
#define LOCALIZED_ALTERNATE_PLISTS                 "спискисв" 
#define LOCALIZED_ALTERNATE_PO                     "ппроц" 
#define LOCALIZED_ALTERNATE_POPDIR                 "вверхпап" 
#define LOCALIZED_ALTERNATE_POLYSTART              "начмногоуг" 
#define LOCALIZED_ALTERNATE_POLYEND                "конмногоуг" 
#define LOCALIZED_ALTERNATE_POLYVIEW               "показмногоуг" 
#define LOCALIZED_ALTERNATE_PORTCLOSE              "портзакрой" 
#define LOCALIZED_ALTERNATE_PORTFLUSH              "портсбр" 
#define LOCALIZED_ALTERNATE_PORTMODE               "режимпорта" 
#define LOCALIZED_ALTERNATE_PORTOPEN               "портоткрой" 
#define LOCALIZED_ALTERNATE_PORTREADARRAY          "читмассизпорта" 
#define LOCALIZED_ALTERNATE_PORTREADCHAR           "читсимизпорта" 
#define LOCALIZED_ALTERNATE_PORTWRITEARRAY         "запмассвпорт" 
#define LOCALIZED_ALTERNATE_PORTWRITECHAR          "запсимвпорт" 
#define LOCALIZED_ALTERNATE_POS                    "место" 
#define LOCALIZED_ALTERNATE_POSXYZ                 "место_xyz" 
#define LOCALIZED_ALTERNATE_POT                    "вдзгстр" 
#define LOCALIZED_ALTERNATE_POWER                  "степень"
#define LOCALIZED_ALTERNATE_PPROP                  "дсвойство" 
#define LOCALIZED_ALTERNATE_PPT                    "прк"
#define LOCALIZED_ALTERNATE_PR                     "пш"
#define LOCALIZED_ALTERNATE_PRIMITIVEP             "базиснаяпи" 
#define LOCALIZED_ALTERNATE_PRIMITIVE_             "базисная?" 
#define LOCALIZED_ALTERNATE_PRINT                  "пиши"
#define LOCALIZED_ALTERNATE_PROCEDUREP             "процедурапи" 
#define LOCALIZED_ALTERNATE_PROCEDURE_             "процедура?" 
#define LOCALIZED_ALTERNATE_PROPLISTP              "спсвойствпи" 
#define LOCALIZED_ALTERNATE_PROPLIST_              "спсвойств?" 
#define LOCALIZED_ALTERNATE_PROCEDURES             "процедуры"
#define LOCALIZED_ALTERNATE_PRODUCT                "произведение"
#define LOCALIZED_ALTERNATE_PU                     "пп"
#define LOCALIZED_ALTERNATE_PX                     "поб"
#define LOCALIZED_ALTERNATE_QUESTIONBOX            "окновопроса" 
#define LOCALIZED_ALTERNATE_QUOTIENT               "частное"
#define LOCALIZED_ALTERNATE_RADARCCOS              "radarccos" 
#define LOCALIZED_ALTERNATE_RADARCSIN              "radarcsin" 
#define LOCALIZED_ALTERNATE_RADARCTAN              "radarctg" 
#define LOCALIZED_ALTERNATE_RADCOS                 "radcos" 
#define LOCALIZED_ALTERNATE_RADIOBUTTONCREATE      "радиопереклсоздай" 
#define LOCALIZED_ALTERNATE_RADIOBUTTONENABLE      "радиопереклдопусти" 
#define LOCALIZED_ALTERNATE_RADIOBUTTONDELETE      "радиопереклудали" 
#define LOCALIZED_ALTERNATE_RADIOBUTTONGET         "радиопереклсобытие" 
#define LOCALIZED_ALTERNATE_RADIOBUTTONSET         "радиопереклустанови" 
#define LOCALIZED_ALTERNATE_RADSIN                 "radsin" 
#define LOCALIZED_ALTERNATE_RADTAN                 "radtg" 
#define LOCALIZED_ALTERNATE_RANDOM                 "случайный"
#define LOCALIZED_ALTERNATE_RAWASCII               "альткод" 
#define LOCALIZED_ALTERNATE_RC                     "жсмв"
#define LOCALIZED_ALTERNATE_RCS                    "жсы" 
#define LOCALIZED_ALTERNATE_READCHAR               "ждисимвол" 
#define LOCALIZED_ALTERNATE_READCHARS              "ждисимволы" 
#define LOCALIZED_ALTERNATE_READER                 "считыватель" 
#define LOCALIZED_ALTERNATE_READLIST               "ждисписок" 
#define LOCALIZED_ALTERNATE_READPOS                "читайкол" 
#define LOCALIZED_ALTERNATE_READRAWLINE            "readrawline" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READWORD               "ждислово"
#define LOCALIZED_ALTERNATE_REMAINDER              "остаток"
#define LOCALIZED_ALTERNATE_REMPROP                "удалисв" 
#define LOCALIZED_ALTERNATE_REPCOUNT               "счетчик"
#define LOCALIZED_ALTERNATE_REPEAT                 "повтори"
#define LOCALIZED_ALTERNATE_RERANDOM               "повторисл" 
#define LOCALIZED_ALTERNATE_RIGHT                  "направо"
#define LOCALIZED_ALTERNATE_RIGHTROLL              "правыйкрен" 
#define LOCALIZED_ALTERNATE_RL                     "чс" 
#define LOCALIZED_ALTERNATE_RMDIR                  "удпап" 
#define LOCALIZED_ALTERNATE_ROLL                   "крен" 
#define LOCALIZED_ALTERNATE_ROUND                  "целое"
#define LOCALIZED_ALTERNATE_RR                     "пкр" 
#define LOCALIZED_ALTERNATE_RT                     "пр"
#define LOCALIZED_ALTERNATE_RUN                    "выполнить" 
#define LOCALIZED_ALTERNATE_RUNPARSE               "выпвпредл" 
#define LOCALIZED_ALTERNATE_RUNRESULT              "выпрез" 
#define LOCALIZED_ALTERNATE_RW                     "жс"
#define LOCALIZED_ALTERNATE_SAVE                   "сохрани" 
#define LOCALIZED_ALTERNATE_SCREENCOLOR            "цветэкрана" 
#define LOCALIZED_ALTERNATE_SCROLLBARCREATE        "полпроксоздать" 
#define LOCALIZED_ALTERNATE_SCROLLBARENABLE        "полпрокдопусти" 
#define LOCALIZED_ALTERNATE_SCROLLBARDELETE        "полпрокудали" 
#define LOCALIZED_ALTERNATE_SCROLLBARGET           "полпрокустанови" 
#define LOCALIZED_ALTERNATE_SCROLLBARSET           "полпрокзадай" 
#define LOCALIZED_ALTERNATE_SCROLLX                "прокрутка_x" 
#define LOCALIZED_ALTERNATE_SCROLLY                "прокрутка_y" 
#define LOCALIZED_ALTERNATE_SCRUNCH                "коррекция" 
#define LOCALIZED_ALTERNATE_SE                     "пе"
#define LOCALIZED_ALTERNATE_SELECTBOX              "окновыбора" 
#define LOCALIZED_ALTERNATE_SENTENCE               "предложение"
#define LOCALIZED_ALTERNATE_SETACTIVEAREA          "актполеустанови" 
#define LOCALIZED_ALTERNATE_SETBITINDEX            "индрастраустанови" 
#define LOCALIZED_ALTERNATE_SETBITMODE             "режрастраустанови" 
#define LOCALIZED_ALTERNATE_SETCLIP                "новклип" 
#define LOCALIZED_ALTERNATE_SETCURSOR              "новкурсор" 
#define LOCALIZED_ALTERNATE_SETCURSORNOWAIT        "курсорнечасы" 
#define LOCALIZED_ALTERNATE_SETCURSORWAIT          "курсорчасы" 
#define LOCALIZED_ALTERNATE_SETFC                  "новцз"
#define LOCALIZED_ALTERNATE_SETFLOODCOLOR          "новыйцветзаливки" 
#define LOCALIZED_ALTERNATE_SETFOCUS               "устактокно" 
#define LOCALIZED_ALTERNATE_SETH                   "новк"
#define LOCALIZED_ALTERNATE_SETHEADING             "новыйкурс"
#define LOCALIZED_ALTERNATE_SETITEM                "новыйэлемент"
#define LOCALIZED_ALTERNATE_SETLABELFONT           "новшрифтнадписи"
#define LOCALIZED_ALTERNATE_SETLIGHT               "установияркость" 
#define LOCALIZED_ALTERNATE_SETMARGINS             "новполя" 
#define LOCALIZED_ALTERNATE_SETPC                  "нц"
#define LOCALIZED_ALTERNATE_SETPENCOLOR            "новыйцветпера"
#define LOCALIZED_ALTERNATE_SETPENPATTERN          "новмодельпера" 
#define LOCALIZED_ALTERNATE_SETPENSIZE             "новыйразмерпера"
#define LOCALIZED_ALTERNATE_SETPITCH               "новуклон" 
#define LOCALIZED_ALTERNATE_SETPIXEL               "новпиксель" 
#define LOCALIZED_ALTERNATE_SETPOS                 "новоеместо"
#define LOCALIZED_ALTERNATE_SETPOSXYZ              "новместо_xyz" 
#define LOCALIZED_ALTERNATE_SETREAD                "новчтение" 
#define LOCALIZED_ALTERNATE_SETREADPOS             "чтениесместа" 
#define LOCALIZED_ALTERNATE_SETROLL                "новкрен" 
#define LOCALIZED_ALTERNATE_SETSC                  "нцэ" 
#define LOCALIZED_ALTERNATE_SETSCREENCOLOR         "новцветэкрана" 
#define LOCALIZED_ALTERNATE_SETSCRUNCH             "установикоррекцию" 
#define LOCALIZED_ALTERNATE_SETTIMER               "новтаймер" 
#define LOCALIZED_ALTERNATE_SETTURTLE              "новтортила" 
#define LOCALIZED_ALTERNATE_SETTURTLEMODE          "новрежимтортилы" 
#define LOCALIZED_ALTERNATE_SETWRITE               "новзапись" 
#define LOCALIZED_ALTERNATE_SETWRITEPOS            "записьсместа" 
#define LOCALIZED_ALTERNATE_SETX                   "нов_x" 
#define LOCALIZED_ALTERNATE_SETXY                  "нов_xy"
#define LOCALIZED_ALTERNATE_SETXYZ                 "нов_xyz" 
#define LOCALIZED_ALTERNATE_SETY                   "нов_y" 
#define LOCALIZED_ALTERNATE_SETZ                   "нов_z" 
#define LOCALIZED_ALTERNATE_SHELL                  "оболочка" 
#define LOCALIZED_ALTERNATE_SHOW                   "покажи"
#define LOCALIZED_ALTERNATE_SHOWNP                 "видимаяпи" 
#define LOCALIZED_ALTERNATE_SHOWN_                 "видимая?" 
#define LOCALIZED_ALTERNATE_SHOWTURTLE             "покажитортилу"
#define LOCALIZED_ALTERNATE_SIN                    "sin" 
#define LOCALIZED_ALTERNATE_SOUND                  "звук" 
#define LOCALIZED_ALTERNATE_SPLITSCREEN            "раздэкран" 
#define LOCALIZED_ALTERNATE_SQRT                   "корень"
#define LOCALIZED_ALTERNATE_SS                     "рэ" 
#define LOCALIZED_ALTERNATE_ST                     "пт"
#define LOCALIZED_ALTERNATE_STANDOUT               "выдел" 
#define LOCALIZED_ALTERNATE_STATICCREATE           "заголовоксоздай" 
#define LOCALIZED_ALTERNATE_STATICDELETE           "заголовокудали" 
#define LOCALIZED_ALTERNATE_STATICUPDATE           "заголовокобнови" 
#define LOCALIZED_ALTERNATE_STATUS                 "статус" 
#define LOCALIZED_ALTERNATE_STEP                   "шаг" 
#define LOCALIZED_ALTERNATE_STEPPED                "пройденные" 
#define LOCALIZED_ALTERNATE_STOP                   "стоп" 
#define LOCALIZED_ALTERNATE_SUBSTRINGP             "подстрокапи" 
#define LOCALIZED_ALTERNATE_SUBSTRING_             "подстрока?" 
#define LOCALIZED_ALTERNATE_SUM                    "сумма"
#define LOCALIZED_ALTERNATE_TAG                    "метка" 
#define LOCALIZED_ALTERNATE_TAN                    "tg" 
#define LOCALIZED_ALTERNATE_TEST                   "тест" 
#define LOCALIZED_ALTERNATE_TEXT                   "текст" 
#define LOCALIZED_ALTERNATE_TEXTSCREEN             "текстовыйэкран" 
#define LOCALIZED_ALTERNATE_THING                  "объект" 
#define LOCALIZED_ALTERNATE_THROW                  "перемести" 
#define LOCALIZED_ALTERNATE_TIME                   "время" 
#define LOCALIZED_ALTERNATE_TIMEMILLI              "систвремя" 
#define LOCALIZED_ALTERNATE_TO                     "это"
#define LOCALIZED_ALTERNATE_TONE                   "тон" 
#define LOCALIZED_ALTERNATE_TOWARDS                "внаправ" 
#define LOCALIZED_ALTERNATE_TOWARDSXYZ             "внаправ_xyz" 
#define LOCALIZED_ALTERNATE_TRACE                  "трасс" 
#define LOCALIZED_ALTERNATE_TRACED                 "трассированные" 
#define LOCALIZED_ALTERNATE_TS                     "тэ" 
#define LOCALIZED_ALTERNATE_TURTLE                 "тортила" 
#define LOCALIZED_ALTERNATE_TURTLEMODE             "режимтортилы" 
#define LOCALIZED_ALTERNATE_TURTLES                "тортилы" 
#define LOCALIZED_ALTERNATE_TYPE                   "набери" 
#define LOCALIZED_ALTERNATE_UNBURY                 "нескрывать" 
#define LOCALIZED_ALTERNATE_UNSTEP                 "безшага" 
#define LOCALIZED_ALTERNATE_UNTRACE                "безтрасс" 
#define LOCALIZED_ALTERNATE_UP                     "вверх" 
#define LOCALIZED_ALTERNATE_UPPERCASE              "заглавный" 
#define LOCALIZED_ALTERNATE_UPPITCH                "уклонвверх" 
#define LOCALIZED_ALTERNATE_WAIT                   "жди"
#define LOCALIZED_ALTERNATE_WINDOW                 "окно" 
#define LOCALIZED_ALTERNATE_WINDOWCREATE           "окносоздай"
#define LOCALIZED_ALTERNATE_WINDOWENABLE           "окнодопусти" 
#define LOCALIZED_ALTERNATE_WINDOWDELETE           "окноудали"
#define LOCALIZED_ALTERNATE_WINDOWFILEEDIT         "окнофайлоткрыть" 
#define LOCALIZED_ALTERNATE_WINDOWSET              "окнозадать" 
#define LOCALIZED_ALTERNATE_WINHELP                "окнопомощи" 
#define LOCALIZED_ALTERNATE_WORD                   "слово"
#define LOCALIZED_ALTERNATE_WORDP                  "словопи" 
#define LOCALIZED_ALTERNATE_WORD_                  "слово?" 
#define LOCALIZED_ALTERNATE_WRAP                   "обертка" 
#define LOCALIZED_ALTERNATE_WRITEPOS               "пишикол" 
#define LOCALIZED_ALTERNATE_WRITER                 "пишпоток" 
#define LOCALIZED_ALTERNATE_YESNOBOX               "данетокно" 
#define LOCALIZED_ALTERNATE_YIELD                  "уступать" 
#define LOCALIZED_ALTERNATE_ZOOM                   "масштаб" 

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      "ОК" 
#define LOCALIZED_GENERAL_CANCELBUTTON  "Отмена" 
#define LOCALIZED_GENERAL_APPLYBUTTON   "&Применить" 

#define LOCALIZED_GENERAL_PRODUCTNAME   "FMSLogo" 

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  "Среда программирования FMSLogo" 

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  "&Файл" 
#define LOCALIZED_FILE_NEW              "&Новый" 
#define LOCALIZED_FILE_LOAD             "&Загрузить..." 
#define LOCALIZED_FILE_OPEN             "&Открыть..."  
#define LOCALIZED_FILE_SAVE             "&Сохранить"  
#define LOCALIZED_FILE_SAVEAS           "Сохранить &как..." 
#define LOCALIZED_FILE_SETASSCREENSAVER "Se&t As Screen Saver" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_EDIT             "&Редактировать..." 
#define LOCALIZED_FILE_ERASE            "С&тереть..." 
#define LOCALIZED_FILE_EXIT             "&Выход" 

#define LOCALIZED_BITMAP               "&Рисунок" 
#define LOCALIZED_BITMAP_NEW           "&Новый" 
#define LOCALIZED_BITMAP_LOAD          "&Загрузить..." 
#define LOCALIZED_BITMAP_SAVE          "&Сохранить" 
#define LOCALIZED_BITMAP_SAVEAS        "Сохранить &как..." 
#define LOCALIZED_BITMAP_PRINT         "&Печать..." 
#define LOCALIZED_BITMAP_PRINTERSETUP  "С&войства принтера..." 
#define LOCALIZED_BITMAP_ACTIVEAREA    "&Активная зона..." 

#define LOCALIZED_SET                  "&Установить" 
#define LOCALIZED_SET_PENSIZE          "&Размер пера..." 
#define LOCALIZED_SET_LABELFONT        "&Шрифт надписей..." 
#define LOCALIZED_SET_COMMANDERFONT    "Шр&ифт командного окна..." 
#define LOCALIZED_SET_PENCOLOR         "Цв&ет пера..." 
#define LOCALIZED_SET_FLOODCOLOR       "Ц&вет заливки..." 
#define LOCALIZED_SET_SCREENCOLOR      "&Цвет экрана..." 

#define LOCALIZED_ZOOM                 "&Лупа"  
#define LOCALIZED_ZOOM_IN              "&Увеличить" 
#define LOCALIZED_ZOOM_OUT             "У&меньшить" 
#define LOCALIZED_ZOOM_NORMAL          "&Норма" 

#define LOCALIZED_HELP                 "&Помощь"  
#define LOCALIZED_HELP_INDEX           "&Индекс" 
#define LOCALIZED_HELP_TUTORIAL        "О&бучающая программа" 
#define LOCALIZED_HELP_DEMO            "&Демо"  
#define LOCALIZED_HELP_EXAMPLE         "&Примеры" 
#define LOCALIZED_HELP_RELEASENOTES    "П&римечания к выпуску" 
#define LOCALIZED_HELP_ABOUTFMSLOGO    "&О " LOCALIZED_GENERAL_PRODUCTNAME "..."
#define LOCALIZED_HELP_MS              "&О MS..." 
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   "Русско-Английский" 
#define LOCALIZED_HELP_ENGLISHTOLANG   "Англо-Русский" 

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              "Укажите активную зону" 
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       "Изменение свойств Печати и Сохранения растровых изображений" 
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        "Y-вверхний" 
#define LOCALIZED_SELECTACTIVEAREA_YLOW         "Y-нижний"  
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        "X-правый" 
#define LOCALIZED_SELECTACTIVEAREA_XLOW         "X-левый" 
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH "Количество шагов на дюйм:" 
#define LOCALIZED_SELECTACTIVEAREA_RESET        "&Сброс"  
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON 
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON 

// The screensaver strings
#define LOCALIZED_SCREENSAVER_NAME              LOCALIZED_GENERAL_PRODUCTNAME // NOT_YET_LOCALIZED
#define LOCALIZED_SCREENSAVER_DESCRIPTION       "FMSLogo Screensaver" // NOT_YET_LOCALIZED
#define LOCALIZED_SCREENSAVER_SETTINGS_TITLE    "FMSLogo Screensaver Settings" // NOT_YET_LOCALIZED
#define LOCALIZED_SCREENSAVER_LOCATE            "&Locate ..."  // NOT_YET_LOCALIZED
#define LOCALIZED_SCREENSAVER_FILE              "Logo &File:"  // NOT_YET_LOCALIZED
#define LOCALIZED_SCREENSAVER_OK                LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SCREENSAVER_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED

// The dialog box for selecting a Startup procedure
#define LOCALIZED_SELECTSTARTUP_CAPTION               "Select a " LOCALIZED_ALTERNATE_STARTUP " instruction" // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_UNDEFINED "Your workspace does not have a " LOCALIZED_ALTERNATE_STARTUP " instruction list defined, so nothing\nwill happen when the screensaver is loaded.\nPlease select a procedure to run when the program is loaded." // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_NOTLIST   "The " LOCALIZED_ALTERNATE_STARTUP " variable is not a list, so nothing will happen when the screensaver\nis loaded.\nPlease select a procedure to run when the program is loaded." // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTSTARTUP_EXPLAINTEXT_EMPTY     "Your workspace has an empty " LOCALIZED_ALTERNATE_STARTUP " instruction list defined, so nothing will\nhappen when the screensaver is loaded.\nPlease select a procedure to run when the program is loaded." // NOT_YET_LOCALIZED
#define LOCALIZED_SELECTSTARTUP_NOPROCEDURESDEFINED   "No procedures are defined" // NOT_YET_LOCALIZED

// The warning dialog box when the user saves an empty workspace
#define LOCALIZED_EMPTYWORKSPACE_TITLE                LOCALIZED_GENERAL_PRODUCTNAME // NOT_YET_LOCALIZED
#define LOCALIZED_EMPTYWORKSPACE_MESSAGE              "There are no procedures, variables, or property lists defined,\nso the workspace will be saved as an empty file.\n\nDo you want to save the workspace anyway?" // NOT_YET_LOCALIZED

//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     "Копировать" 
#define LOCALIZED_POPUP_CUT                      "Вырезать" 
#define LOCALIZED_POPUP_PASTE                    "Вставить" 
#define LOCALIZED_POPUP_DELETE                   "Удалить" 
#define LOCALIZED_POPUP_UNDO                     "Отменить" 
#define LOCALIZED_POPUP_REDO                     "Вернуть" 
#define LOCALIZED_POPUP_SELECTALL                "Выделить всё" 
#define LOCALIZED_POPUP_HELP                     "Поиск по разделу" 
#define LOCALIZED_POPUP_REMOVELINES              "Remove Selected Lines" // NOT_YET_LOCALIZED

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   "Редактор" 

#define LOCALIZED_EDITOR_FILE                    "&Файл" 
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        "&Сохранить и выйти\tCtrl+D" 
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    "С&охранить" 
#define LOCALIZED_EDITOR_FILE_PRINT              "&Печать..."  
#define LOCALIZED_EDITOR_FILE_EXIT               "&Выход"  

#define LOCALIZED_EDITOR_EDIT                    "&Редактировать" 
#define LOCALIZED_EDITOR_EDIT_UNDO               "&Отменить\tCtrl+Z" 
#define LOCALIZED_EDITOR_EDIT_REDO               "&Вернуть\tCtrl+Y" 
#define LOCALIZED_EDITOR_EDIT_CUT                "&Вырезать\tCtrl+X" 
#define LOCALIZED_EDITOR_EDIT_COPY               "&Копировать\tCtrl+C" 
#define LOCALIZED_EDITOR_EDIT_PASTE              "В&ставить\tCtrl+V" 
#define LOCALIZED_EDITOR_EDIT_DELETE             "&Удалить\tDel" 
#define LOCALIZED_EDITOR_EDIT_CLEARALL           "О&чистить всё\tCtrl+Del" 
#define LOCALIZED_EDITOR_EDIT_SELECTALL          "В&ыделить всё\tCtrl+A" 

#define LOCALIZED_EDITOR_SEARCH                  "&Поиск" 
#define LOCALIZED_EDITOR_SEARCH_FIND             "&Найти...\tCtrl+F" 
#define LOCALIZED_EDITOR_SEARCH_REPLACE          "&Замена...\tCtrl+H"  
#define LOCALIZED_EDITOR_SEARCH_NEXT             "&Следующий\tF3"  

#define LOCALIZED_EDITOR_SET                     "&Установить"  
#define LOCALIZED_EDITOR_SET_FONT                "&Шрифт..."  

#define LOCALIZED_EDITOR_TEST                    "Тест"
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      "&Run Selection\tCtrl+R" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITOR_HELP                    "&Помощь"  
#define LOCALIZED_EDITOR_HELP_INDEX              "&Индекс" 
#define LOCALIZED_EDITOR_HELP_EDITOR             "&Редактор" 
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        "П&оиск по разделу\tF1"


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES // NOT_YET_LOCALIZED
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    "&Сохранить и выйти" 
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       "&Не сохранять" 
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON 
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       "В рабочем пространстве есть не сохранённые данные. Если вы выйдете, эти данные будут потеряны.  " 
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       "Сохранить данные перед выходом?"  


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     "Редактор" 
#define LOCALIZED_COMMANDER_HALT                "Останов" 
#define LOCALIZED_COMMANDER_TRACE               "Трасс" 
#define LOCALIZED_COMMANDER_NOTRACE             "Безтрасс" 
#define LOCALIZED_COMMANDER_PAUSE               "Пауза" 
#define LOCALIZED_COMMANDER_STATUS              "Статус" 
#define LOCALIZED_COMMANDER_NOSTATUS            "Безстатуса" 
#define LOCALIZED_COMMANDER_STEP                "Шаг" 
#define LOCALIZED_COMMANDER_UNSTEP              "Безшага" 
#define LOCALIZED_COMMANDER_RESET               "Сброс" 
#define LOCALIZED_COMMANDER_EXECUTE             "Выполнить" 
#define LOCALIZED_COMMANDER_EDALL               "Редактор" 

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        "Статус" 
#define LOCALIZED_STATUS_PEN                    "Перо" 
#define LOCALIZED_STATUS_CONTACT                "Сост:" 
#define LOCALIZED_STATUS_WIDTH                  "Ширина:" 
#define LOCALIZED_STATUS_STYLE                  "Режим:" 
#define LOCALIZED_STATUS_ORIENTATION            "Ориентация" 
#define LOCALIZED_STATUS_PITCH                  "Уклон:" 
#define LOCALIZED_STATUS_HEADING                "Направление:" 
#define LOCALIZED_STATUS_ROLL                   "Крен:" 
#define LOCALIZED_STATUS_TURTLE                 "Тортила" 
#define LOCALIZED_STATUS_POSITION               "Позиция(XYZ):" 
#define LOCALIZED_STATUS_WHICH                  "Номер:" 
#define LOCALIZED_STATUS_VISIBILITY             "Видимость:" 
#define LOCALIZED_STATUS_COLOR                  "Цвет" 
#define LOCALIZED_STATUS_PENCOLOR               "Перо(RGB):" 
#define LOCALIZED_STATUS_FLOODCOLOR             "Заливка(RGB):" 
#define LOCALIZED_STATUS_SCREENCOLOR            "Экран(RGB):" 
#define LOCALIZED_STATUS_KERNEL                 "Ядро" 
#define LOCALIZED_STATUS_CALLS                  "Вызовы:" 
#define LOCALIZED_STATUS_PEAKMEMORY             "Пиковая память:" 

#define LOCALIZED_STATUS_PENREVERSE     "Реверс" 
#define LOCALIZED_STATUS_PENNORMAL      "Норма" 
#define LOCALIZED_STATUS_PENERASE       "Ластик" 
#define LOCALIZED_STATUS_PENUP          "Поднято" 
#define LOCALIZED_STATUS_PENDOWN        "Опущено" 
#define LOCALIZED_STATUS_PENSHOWN       "Видима" 
#define LOCALIZED_STATUS_PENHIDDEN      "Не видима" 
#define LOCALIZED_STATUS_POLYGONS       "Ломаные" 
#define LOCALIZED_STATUS_VECTORS        "Вектора" 
#define LOCALIZED_STATUS_NODES          "Записи" 
#define LOCALIZED_STATUS_NOT_APPLICABLE "N/A" 

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON 
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON 
#define LOCALIZED_SELECTPROCEDURE_ALL           "&Все" 
#define LOCALIZED_ERASEPROCEDURE                "Удалить процедуру" 
#define LOCALIZED_EDITPROCEDURE                 "Редактировать процедуру" 


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     "Установить цвет" 
#define LOCALIZED_SETCOLOR_PENCOLOR            "Цвет пера" 
#define LOCALIZED_SETCOLOR_FLOODCOLOR          "Цвет заливки" 
#define LOCALIZED_SETCOLOR_SCREENCOLOR         "Цвет экрана" 
#define LOCALIZED_SETCOLOR_RED                 "Красный" 
#define LOCALIZED_SETCOLOR_GREEN               "Зелёный" 
#define LOCALIZED_SETCOLOR_BLUE                "Синий" 
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON 
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON 
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON 

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   "Размер пера" 
#define LOCALIZED_SETPENSIZE_SIZE              "Толщина" 
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON 
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON 
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON 


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     "О " LOCALIZED_GENERAL_PRODUCTNAME 
#define LOCALIZED_ABOUTFMS_VERSION             "Версия"
#define LOCALIZED_ABOUTFMS_GUI                 "ГИП Джорджа Миллза\nSoftronics, Inc.\nhttp://www.softronix.com/" 
#define LOCALIZED_ABOUTFMS_CORE                "Ядро Брайена Харви\nКалифорнийский университет Беркли" 
#define LOCALIZED_ABOUTFMS_INSTALLER           "Инсталляция базируется на Nullsoft Scriptable Install \nhttp://nsis.sourceforge.net/" 
#define LOCALIZED_ABOUTFMS_ADVENTURE           "The Great Logo Adventure (ISBN 0-9651934-6-2)\nнаписанная и переданная Джимом Мюллером\nдоступна на http://www.softronix.com/" 
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       "Благодарим Йегуду Катца и Эриха Нейвиртза" 
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME " распространяется свободно\nСм. лицензию ГНУ"
#define LOCALIZED_ABOUTFMS_NEWSGROUP           "Группа новостей в Интернете: comp.lang.logo\nпосетите форум на\nhttp://groups.yahoo.com/group/LogoForum/" 
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     "Для Изучение внутренних свойств компьютера,\nиспользуйте  MultiMedia Logic от Softronics, Inc.\nАдаптация и локализация на русский язык Баглаева Игоря\nБурятский государственный университет, Улан-Удэ, bii@bsu.ru"
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON 


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      "О FMS" 
#define LOCALIZED_ABOUTMS_FMS                  "FMS означает 'Fight Multiple Sclerosis'." 
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     "Пожалуйста, рассмотрите возможность помощи\nNational Multiple Sclerosis Society.\nhttp://www.nmss.org\n1-800-FIGHT-MS" 
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

#define LOCALIZED_CHANGESINEDITORMAYBELOST  "Изменения в этом сеансе редактирования могут быть утеряны.\n\nВы действительно хотите выйти из " LOCALIZED_GENERAL_PRODUCTNAME "?"
#define LOCALIZED_EDITSESSIONISRUNNING      "Сеанс редактирования запущен" 

#define LOCALIZED_COULDNOTWRITEBMP            "Не могу записать .bmp" 
#define LOCALIZED_COULDNOTOPENBMP             "Не могу открыть .bmp" 
#define LOCALIZED_COULDNOTCREATEBMP           "Невозможно создать Windows 3.0 рисунок" 
#define LOCALIZED_NOTVALIDBMP                 "Не растровый рисунок Windows 3.0" 

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         "Вы не сохранили на диск" 
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     "Создание нового сотрет все данные из рабочей области.\n\nПродолжить Новый?" 
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE "Загружаемый файл будет объединен с данными вашей рабочей области\nи, может изменить ваши несохраненные данные.\n\nПродолжить Загрузить?" 
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    "Эта операция сотрет все ваши несохраненные данные.\n\nПродолжить Открыть?" 

#define LOCALIZED_EDITORISOPEN                  "Вы знаете, что запущен сеанс редактирования?\n\nВсе изменения в этом сеансе редактирования не были сохранены"

#define LOCALIZED_ERROR_CANTREADFILE            "Невозможно прочитать файл \"%s\" с диска" 
#define LOCALIZED_ERROR_CANTWRITEFILE           "Невозможно записать файл \"%s\" на диск" 

#define LOCALIZED_SAVETOWORKSPACE                "Сохраните в рабочую область" 
#define LOCALIZED_CONTENTSCHANGED                "Contents Changed" // NOT_YET_LOCALIZED
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE "Содержание изменено.\n Хотите вы сохранить изменения в рабочей области?" 



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  "Обнаружена проблема сохранения  содержания редактора  в рабочую область. Курсор будет помещен за последним успешным определением. \n\n Для установления возможной ошибки активизируйте Командное окно." 
#define LOCALIZED_RETURNTOEDIT                  "Вернуться в редактор?" 

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
#define LOCALIZED_FILEFILTER_ALLFILES "Все файлы (*.*)|*.*" 
#define LOCALIZED_FILEFILTER_LOGO     "Лого-файлы (*.lgo)|*.lgo|" LOCALIZED_FILEFILTER_ALLFILES 
#define LOCALIZED_FILEFILTER_IMAGE    "Растровые файлы (*.bmp)|*.bmp|GIF-файлы (*.gif)|*.gif|" LOCALIZED_FILEFILTER_ALLFILES



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             " останов\n" 
#define LOCALIZED_TRACING_OUTPUTS           " возвращает %s\n" 
#define LOCALIZED_TRACING_MAKE              "пусть %s %s" 
#define LOCALIZED_TRACING_PPROP             "Дсвойство %s %s %s" 
#define LOCALIZED_TRACING_LOCATION          " в %s\n%s" 

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  "Отдельный шаг" 

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  "%s определена\n" 


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    "ластик" 
#define LOCALIZED_PENMODE_REVERSE  "обратное" 
#define LOCALIZED_PENMODE_PAINT    "ручка" 

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          "Лого: Фатальная внутренняя ошибка" 
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       "Лого: Недостаточно памяти" 
#define LOCALIZED_ERROR_OUTOFMEMORY            "Недостаточно памяти" 
#define LOCALIZED_ERROR_STACKOVERFLOW          "Переполнение стека" 
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      "Тортила вышла за границы" 
#define LOCALIZED_ERROR_BADGRAPHINIT           "не могу инициализировать графику" 
#define LOCALIZED_ERROR_BADDATA                "%p не нравится %s как аргумент" 
#define LOCALIZED_ERROR_DIDNTOUTPUT            "%p не возвращает %p" 
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        "Не хватает аргументов в %p" 
#define LOCALIZED_ERROR_TOOMUCH                "Слишком много внутренних ()" 
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    "Вы не сказали что делать с %s" 
#define LOCALIZED_ERROR_PARENMISMATCH          "Слишком много (" 
#define LOCALIZED_ERROR_NOVALUE                "%s не имеет значения" 
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        "неопределенная ')'" 
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      "неопределенная ']'" 
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        "неопределенная '}'" 
#define LOCALIZED_ERROR_DONTKNOWHOWTO          "Я не знаю что делать с  %p" 
#define LOCALIZED_ERROR_NOCATCHTAG             "Не найдена метка для %p" 
#define LOCALIZED_ERROR_ALREADYDEFINED         "%p уже определена" 
#define LOCALIZED_ERROR_STOPPING               "Остановка..." 
#define LOCALIZED_ERROR_ALREADYDRIBBLING       "Уже запротоколирован" 
#define LOCALIZED_ERROR_FILESYSTEM                   "Ошибка файловой системы: %p" 
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          "Не могу открыть файл" 
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         "Невозможно открыть файл: %t" 
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       "Файл уже открыт" 
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           "Файл не открыт" 
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  "Не могу создать редактируемый файл"
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   "Не могу запустить редактор"  
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    "Не могу прочитать редактируемый файл" 
#define LOCALIZED_ERROR_IFWARNING              "Возможно вы имели ввиду ЕСЛИИНАЧЕ, а не ЕСЛИ" 
#define LOCALIZED_ERROR_SHADOWWARNING          "%p затенена локально в вызове процедуры" 
#define LOCALIZED_ERROR_USER                   "Перемести \"Ошибка" 
#define LOCALIZED_ERROR_ISPRIMITIVE            "%p базисная" 
#define LOCALIZED_ERROR_TONOTINSIDE            "Не могу использовать ЭТО внутри процедуры" 
#define LOCALIZED_ERROR_ATTOPLEVEL             "Можно использовать %p только внутри процедуры" 
#define LOCALIZED_ERROR_ATTOPLEVEL2            "Вы должны находиться внутри процедуры, чтобы использовать ВЫВОД или СТОП" 
#define LOCALIZED_ERROR_NOTEST                 "%p без ТЕСТ" 
#define LOCALIZED_ERROR_BADMACROOUTPUT         "Результат макроса %s вместо списка" 
#define LOCALIZED_ERROR_DEEPEND                "КОНЕЦ внутри мульти-строковой инструкции" 
#define LOCALIZED_ERROR_DEEPENDIN              "КОНЕЦ внутри мульти-строковой инструкции в %p" 
#define LOCALIZED_ERROR_UNKNOWN                "Неизвестное ошибочное условие - внутренняя ошибка." 
#define LOCALIZED_PAUSING                      "Пауза..." 


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION "Invalid state for instruction: %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MODE_ON_SPRITE             "cannot set the mode of a turtle with a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        "cannot make a special turtle use a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            "cannot use the clipboard as a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_SPECIALFORM                "%p doesn't like %p as input because it has a special form" // NOT_YET_LOCALIZED

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      "Ошибка" 
#define LOCALIZED_ERROR_BADINPUT             "Неверный аргумент" 
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    "Аргументы не сочетаются" 

#define LOCALIZED_ERROR_CANTOPENPORT         "Невозможно открыть порт" 
#define LOCALIZED_ERROR_CANTCLOSEPORT        "Невозможно закрыть порт" 
#define LOCALIZED_ERROR_CANTFLUSHPORT        "Невозможно сбросить порт"                                                                                                                           
#define LOCALIZED_ERROR_CANTDCBONPORT        "Невозможно настроить структуру dcb на порту" 
#define LOCALIZED_ERROR_CANTSETPORT          "Невозможно установить порт" 
#define LOCALIZED_ERROR_PORTALREADYOPEN      "Порт уже открыт" 
#define LOCALIZED_ERROR_PORTNOTOPEN          "Порт не открыт" 

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   "%s уже существует" 
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    "%s не существует" 

#define LOCALIZED_ERROR_DLLNOTLOADED          "DLL не загружена" 
#define LOCALIZED_ERROR_DLLLOADFAILED         "DLL загружен неудачно" 
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    "Недопустимый тип данных аргумента" 
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  "Недопустимый тип данных результата" 
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   "Функция не найдена" 
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  "Не все типы/Данные аргументов соединены" 

#define LOCALIZED_ERROR_NETWORK               "Ошибка сети" 
#define LOCALIZED_ERROR_NETWORKRECEIVE        "Ошибка загрузки данных" 
#define LOCALIZED_ERROR_NETWORKSEND           "Ошибка передачи данных" 
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       "Неизвестная ошибка, Сеть может быть недоступна" 
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     "Не запущена" 
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED "Уже запущена" 
#define LOCALIZED_ERROR_NETWORKALREADYON      "Уже включено" 
#define LOCALIZED_ERROR_NETWORKALREADYOFF     "Уже выключено" 

// The rest of the network errors shouldn't really be seen -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         "Слишком длинное имя" 
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

#define LOCALIZED_ERROR_POLYSTART               "Ошибка НАЧМНОГОУГ" 
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED "Многоугольник уже начат" 

#define LOCALIZED_ERROR_POLYEND                 "Ошибка КОНМНОГОУГ" 
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       "Многоугольник не начат" 
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     "Должно быть по крайней мере 3 вектора, чтобы определить многоугольник" 

#define LOCALIZED_ERROR_SOUND                 "Ошибка звука" 

#define LOCALIZED_ERROR_MIDI                  "Ошибка MIDI" 
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     "Недопустимое MIDI устройство" 
#define LOCALIZED_ERROR_MIDIALREADYOPEN       "Уже открыто" 
#define LOCALIZED_ERROR_MIDINOTOPEN           "Не открыто" 

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      "В буфере нет текста" 

#define LOCALIZED_ERROR_MCI                   "Ошибка МКИ" 

#define LOCALIZED_ERROR_TIMERNOTFOUND         "Таймер не найден" 

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       "Онлайн-помощь недоступна, т.к. hhctrl.ocx не может быть загружена." 

#define LOCALIZED_ERROR_BADCOMMANDLINE        "Ошибка командной строки"  

#define LOCALIZED_ERROR_TMPNOTDEFINED         "Переменная среды TMP не определена или не допустима.\n" LOCALIZED_GENERAL_PRODUCTNAME " будет использовать C: \\для хранения временных файлов"

#define LOCALIZED_ERROR_GIFSAVEFAILED         "Проблема создания GIF, проверьте память и дисковое пространство" 
#define LOCALIZED_ERROR_GIFREADFAILED         "Проблема чтения GIF, проверьте память и дисковое пространство" 

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  "Растровый индекс вне диапазона" 
#define LOCALIZED_ERROR_BITMAPCUTFAILED        "Операция Вырезать не удалась, возможно нехватает памяти" 

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    "Нечего вставить" 
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  "Растровый индекс должен калиброваться с битовым массивом" 

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      "Для тортилы %d нет рисунка, остановиться" 

#define LOCALIZED_ERROR_FONTNOTFOUND            "\nК сожалению, шрифт по имени %s, не найден. Выберите один из следующих:\n" 

#define LOCALIZED_ERROR_PRINTERCANTSCALE        "Драйвер печати не поддерживает эту функцию"  
#define LOCALIZED_ERROR_CANTDRAWIMAGE           "Невозможно прорисовать изображение" 
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        "Невозможно получить изображение" 
#define LOCALIZED_ERROR_SUBCODE                 "Дополнительный код" 

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         "Ввод:" 
#define LOCALIZED_PROMPT_TO     "Это (Отмена для окончания)" 
#define LOCALIZED_PROMPT_LIST   "Список (Отмена для останова)" 
#define LOCALIZED_PROMPT_PAUSE  "Pause Mode (Cancel to Continue)" // NOT_YET_LOCALIZED
#define LOCALIZED_PROMPT_INPUT  "Ввод (Отмена для останова)" 

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      "Измененный на \"%s\"" 
#define LOCALIZED_FILE_CHDIRFAILED         "Невозможно измпап на папку \"%s\"" 
#define LOCALIZED_FILE_POPPEDTO            "Выше к \"%s\"" 
#define LOCALIZED_FILE_MKDIRSUCCEEDED      "Теперь во вновь созданной папке \"%s\""  
#define LOCALIZED_FILE_MKDIRFAILED         "Невозможно создать папку \"%s\""  
#define LOCALIZED_FILE_RMDIRSUCCEEDED      "Перемещена папка \"%s\""  
#define LOCALIZED_FILE_RMDIRFAILED         "Не удалась операция перемещения папки \"%s\""  
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  "Такой папки не существует." 
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY "Убедитесь в том, что директория пуста перед её перемещением." 


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       "Лого-рисунок" 

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    "Активная область" 
#define LOCALIZED_INFORMATION   "Информация" 
#define LOCALIZED_WARNING       "Предупреждение" 
#define LOCALIZED_UNTITLED      "Без заголовка" 
#define LOCALIZED_UNKNOWN       "Неизвестно" 

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       "Неограниченно" 

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     "Найти"
#define LOCALIZED_EDITOR_TITLE_REPLACE  "Замена"

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING "%s не найден" 


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
#define LOCALIZED_COLOR_ALICEBLUE             "серебристо-голубой" 
#define LOCALIZED_COLOR_ANTIQUEWHITE          "белый_антик" 
#define LOCALIZED_COLOR_AQUA                  "аква" 
#define LOCALIZED_COLOR_AQUAMARINE            "аквамарин" 
#define LOCALIZED_COLOR_AZURE                 "лазурный" 
#define LOCALIZED_COLOR_BEIGE                 "бежевый" 
#define LOCALIZED_COLOR_BISQUE                "кремовый" 
#define LOCALIZED_COLOR_BLACK                 "Черный" 
#define LOCALIZED_COLOR_BLANCHEDALMOND        "бланшминдальный" 
#define LOCALIZED_COLOR_BLUE                  "синий" 
#define LOCALIZED_COLOR_BLUEVIOLET            "фиолетово-голубой" 
#define LOCALIZED_COLOR_BROWN                 "коричневый" 
#define LOCALIZED_COLOR_BURLYWOOD             "желтый_легкий" 
#define LOCALIZED_COLOR_CADETBLUE             "голубой_кадет" 
#define LOCALIZED_COLOR_CHARTREUSE            "шартрез" 
#define LOCALIZED_COLOR_CHOCOLATE             "шоколадный" 
#define LOCALIZED_COLOR_CORAL                 "коралл" 
#define LOCALIZED_COLOR_CORNFLOWERBLUE        "василек" 
#define LOCALIZED_COLOR_CORNSILK              "шелковистый" 
#define LOCALIZED_COLOR_CRIMSON               "малиновый" 
#define LOCALIZED_COLOR_CYAN                  "голубой" 
#define LOCALIZED_COLOR_DARKBLUE              "темно-синий" 
#define LOCALIZED_COLOR_DARKCYAN              "темно-голубой" 
#define LOCALIZED_COLOR_DARKGOLDENROD         "темно-золотистокрасный" 
#define LOCALIZED_COLOR_DARKGRAY              "темно-серый" 
#define LOCALIZED_COLOR_DARKGREEN             "темно-зеленый" 
#define LOCALIZED_COLOR_DARKGREY              "темно-серый" 
#define LOCALIZED_COLOR_DARKKHAKI             "хаки_темный" 
#define LOCALIZED_COLOR_DARKMAGENTA           "темно-сиреневый" 
#define LOCALIZED_COLOR_DARKOLIVEGREEN        "темно-оливкогозеленый" 
#define LOCALIZED_COLOR_DARKORANGE            "темно-оранжевый" 
#define LOCALIZED_COLOR_DARKORCHID            "темно-лиловый" 
#define LOCALIZED_COLOR_DARKRED               "темно-красный" 
#define LOCALIZED_COLOR_DARKSALMON            "темно-оранжеворозовый" 
#define LOCALIZED_COLOR_DARKSEAGREEN          "морской_волны_темный" 
#define LOCALIZED_COLOR_DARKSLATEBLUE         "темно-голубоватосерый" 
#define LOCALIZED_COLOR_DARKSLATEGRAY         "темно-синеватоватосерый" 
#define LOCALIZED_COLOR_DARKSLATEGREY         "темно-синеватоватосерый" 
#define LOCALIZED_COLOR_DARKTURQUOISE         "темно-бирюзовый" 
#define LOCALIZED_COLOR_DARKVIOLET            "темно-фиолетовый" 
#define LOCALIZED_COLOR_DEEPPINK              "темно-розовый" 
#define LOCALIZED_COLOR_DEEPSKYBLUE           "темно-небесносиний" 
#define LOCALIZED_COLOR_DIMGRAY               "тускло-серый" 
#define LOCALIZED_COLOR_DIMGREY               "тускло-серый" 
#define LOCALIZED_COLOR_DODGERBLUE            "тускло-васильковый" 
#define LOCALIZED_COLOR_FIREBRICK             "кирпичный" 
#define LOCALIZED_COLOR_FLORALWHITE           "цветочно-белый" 
#define LOCALIZED_COLOR_FORESTGREEN           "лесной_зелени" 
#define LOCALIZED_COLOR_FUCHSIA               "фуксия"
#define LOCALIZED_COLOR_GAINSBORO             "гейнсборо" 
#define LOCALIZED_COLOR_GHOSTWHITE            "туманно-белый" 
#define LOCALIZED_COLOR_GOLD                  "золотой" 
#define LOCALIZED_COLOR_GOLDENROD             "красно-золотой" 
#define LOCALIZED_COLOR_GRAY                  "серый" 
#define LOCALIZED_COLOR_GREEN                 "Зелёный" 
#define LOCALIZED_COLOR_GREENYELLOW           "желто-зеленый" 
#define LOCALIZED_COLOR_GREY                  "серый" 
#define LOCALIZED_COLOR_HONEYDEW              "желто-оранжевый" 
#define LOCALIZED_COLOR_HOTPINK               "ярко-розовый"
#define LOCALIZED_COLOR_INDIANRED             "ярко-красный" 
#define LOCALIZED_COLOR_INDIGO                "индиго" 
#define LOCALIZED_COLOR_IVORY                 "слоновой_кости" 
#define LOCALIZED_COLOR_KHAKI                 "хаки" 
#define LOCALIZED_COLOR_LAVENDER              "лавандовый" 
#define LOCALIZED_COLOR_LAVENDERBLUSH         "красновато-лавандовый" 
#define LOCALIZED_COLOR_LAWNGREEN             "зеленой_лужайки" 
#define LOCALIZED_COLOR_LEMONCHIFFON          "лимонный" 
#define LOCALIZED_COLOR_LIGHTBLUE             "светло-синий" 
#define LOCALIZED_COLOR_LIGHTCORAL            "светло-коралловый" 
#define LOCALIZED_COLOR_LIGHTCYAN             "светло-голубой" 
#define LOCALIZED_COLOR_LIGHTGOLDENRODYELLOW  "светло-жетлтокраснозолотой" 
#define LOCALIZED_COLOR_LIGHTGRAY             "светло-серый" 
#define LOCALIZED_COLOR_LIGHTGREEN            "светло-зеленый" 
#define LOCALIZED_COLOR_LIGHTGREY             "светло-серый" 
#define LOCALIZED_COLOR_LIGHTPINK             "светло-розовый" 
#define LOCALIZED_COLOR_LIGHTSALMON           "светло-оранжеворозовый" 
#define LOCALIZED_COLOR_LIGHTSEAGREEN         "морской_волны_светлый" 
#define LOCALIZED_COLOR_LIGHTSKYBLUE          "светло-небесносиний" 
#define LOCALIZED_COLOR_LIGHTSLATEGRAY        "светло-синеватоватосерый" 
#define LOCALIZED_COLOR_LIGHTSLATEGREY        "светло-синеватоватосерый" 
#define LOCALIZED_COLOR_LIGHTSTEELBLUE        "светло-стальной" 
#define LOCALIZED_COLOR_LIGHTYELLOW           "светло-желтый" 
#define LOCALIZED_COLOR_LIME                  "липовый" 
#define LOCALIZED_COLOR_LIMEGREEN             "зеленая_липа" 
#define LOCALIZED_COLOR_LINEN                 "льняной" 
#define LOCALIZED_COLOR_MAGENTA               "сиреневый" 
#define LOCALIZED_COLOR_MAROON                "каштановый" 
#define LOCALIZED_COLOR_MEDIUMAQUAMARINE      "умеренно-аквамариновый" 
#define LOCALIZED_COLOR_MEDIUMBLUE            "умеренно-синий" 
#define LOCALIZED_COLOR_MEDIUMORCHID          "умеренно-темнолиловый" 
#define LOCALIZED_COLOR_MEDIUMPURPLE          "умеренно-пурпурный" 
#define LOCALIZED_COLOR_MEDIUMSEAGREEN        "морской_волны_умеренный" 
#define LOCALIZED_COLOR_MEDIUMSLATEBLUE       "умеренно-голубоватосерый" 
#define LOCALIZED_COLOR_MEDIUMSPRINGGREEN     "весенней_зелени_умеренный " 
#define LOCALIZED_COLOR_MEDIUMTURQUOISE       "умеренно-бирюзовый" 
#define LOCALIZED_COLOR_MEDIUMVIOLETRED       "умеренно-фиолетовокрасный" 
#define LOCALIZED_COLOR_MIDNIGHTBLUE          "черно-синий" 
#define LOCALIZED_COLOR_MINTCREAM             "мятно-кремовый" 
#define LOCALIZED_COLOR_MISTYROSE             "туманно-розовый" 
#define LOCALIZED_COLOR_MOCCASIN              "болотный" 
#define LOCALIZED_COLOR_NAVAJOWHITE           "грязно-белый" 
#define LOCALIZED_COLOR_NAVY                  "морской" 
#define LOCALIZED_COLOR_OLDLACE               "старое_кружево" 
#define LOCALIZED_COLOR_OLIVE                 "оливковый" 
#define LOCALIZED_COLOR_OLIVEDRAB             "тускло-оливковый" 
#define LOCALIZED_COLOR_ORANGE                "оранжевый" 
#define LOCALIZED_COLOR_ORANGERED             "красно-оранжевый" 
#define LOCALIZED_COLOR_ORCHID                "лиловый" 
#define LOCALIZED_COLOR_PALEGOLDENROD         "бледно-золотой" 
#define LOCALIZED_COLOR_PALEGREEN             "бледно-зеленый" 
#define LOCALIZED_COLOR_PALETURQUOISE         "бледно-бирюзовый" 
#define LOCALIZED_COLOR_PALEVIOLETRED         "бледно-фиолетовокрасный" 
#define LOCALIZED_COLOR_PAPAYAWHIP            "побег_папайи" 
#define LOCALIZED_COLOR_PEACHPUFF             "персиковый" 
#define LOCALIZED_COLOR_PERU                  "светло-коричневый" 
#define LOCALIZED_COLOR_PINK                  "Розовый" 
#define LOCALIZED_COLOR_PLUM                  "сливовый" 
#define LOCALIZED_COLOR_POWDERBLUE            "туманно-синий" 
#define LOCALIZED_COLOR_PURPLE                "пурпурный" 
#define LOCALIZED_COLOR_RED                   "Красный" 
#define LOCALIZED_COLOR_ROSYBROWN             "розово-коричневый" 
#define LOCALIZED_COLOR_ROYALBLUE             "королевский_синий" 
#define LOCALIZED_COLOR_SADDLEBROWN           "кожаного_седла" 
#define LOCALIZED_COLOR_SALMON                "оранжево-розовый" 
#define LOCALIZED_COLOR_SANDYBROWN            "рыжеватый" 
#define LOCALIZED_COLOR_SEAGREEN              "морской_волны" 
#define LOCALIZED_COLOR_SEASHELL              "морской_раковины" 
#define LOCALIZED_COLOR_SIENNA                "охра" 
#define LOCALIZED_COLOR_SILVER                "серебристый" 
#define LOCALIZED_COLOR_SKYBLUE               "небесно-синий" 
#define LOCALIZED_COLOR_SLATEBLUE             "голубовато-серый" 
#define LOCALIZED_COLOR_SLATEGRAY             "синевато-серый" 
#define LOCALIZED_COLOR_SLATEGREY             "синевато-серый" 
#define LOCALIZED_COLOR_SNOW                  "снежный" 
#define LOCALIZED_COLOR_SPRINGGREEN           "весенней_зелени " 
#define LOCALIZED_COLOR_STEELBLUE             "синевато-стальной" 
#define LOCALIZED_COLOR_TAN                   "загар" 
#define LOCALIZED_COLOR_TEAL                  "зеленовато-голубой" 
#define LOCALIZED_COLOR_THISTLE               "чертополоха" 
#define LOCALIZED_COLOR_TOMATO                "томатный" 
#define LOCALIZED_COLOR_TURQUOISE             "бирюзовый" 
#define LOCALIZED_COLOR_VIOLET                "фиолетовый" 
#define LOCALIZED_COLOR_WHEAT                 "пшеничный" 
#define LOCALIZED_COLOR_WHITE                 "белый" 
#define LOCALIZED_COLOR_WHITESMOKE            "дымчато-белый" 
#define LOCALIZED_COLOR_YELLOW                "желтый" 
#define LOCALIZED_COLOR_YELLOWGREEN           "желто-зеленый" 

//
// The name of each "window class" that DEBUGWINDOWS prints.
// These should match the corresponding terms that is used
// in the  LOCALIZED_ALTERNATE_*CREATE procedures.
//
#define LOCALIZED_WINDOWCLASSNAME_WINDOW       "Окно" 
#define LOCALIZED_WINDOWCLASSNAME_STATIC       "Заголовок" 
#define LOCALIZED_WINDOWCLASSNAME_LISTBOX      "Список_записей" 
#define LOCALIZED_WINDOWCLASSNAME_COMBOBOX     "Поле" 
#define LOCALIZED_WINDOWCLASSNAME_BUTTON       "Кнопка" 
#define LOCALIZED_WINDOWCLASSNAME_SCROLLBAR    "Полоса_прорутки" 
#define LOCALIZED_WINDOWCLASSNAME_GROUPBOX     "Группа" 
#define LOCALIZED_WINDOWCLASSNAME_RADIOBUTTON  "Радио_кнопка" 
#define LOCALIZED_WINDOWCLASSNAME_CHECKBOX     "Переключатель" 
#define LOCALIZED_WINDOWCLASSNAME_DIALOG       "Диалог" 


//
// The name of the default font face name.
// This should only be translated if the given font face doesn't include glyphs
// for characters in your language.  The specified font face name must be part
// of all Windows versions from Windows XP onward that would support your
// language.
//
#define LOCALIZED_DEFAULT_FONT_FACE "Courier New" // NOT_YET_LOCALIZED
