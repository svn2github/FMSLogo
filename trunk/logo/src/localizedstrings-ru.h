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
#define LOCALIZED_ALTERNATE_TRUE     "истина" 
#define LOCALIZED_ALTERNATE_FALSE    "ложь" 
#define LOCALIZED_ALTERNATE_END      "конец"
#define LOCALIZED_ALTERNATE_TOPLEVEL "верхнийуровень" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SYSTEM   "система" // NOT_YET_LOCALIZED

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
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         "окнофайлоткрыть" 
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
#define LOCALIZED_ALTERNATE_HEADING                "направление" 
#define LOCALIZED_ALTERNATE_HELP                   "помощь" 
#define LOCALIZED_ALTERNATE_HIDETURTLE             "скройчерепаху"
#define LOCALIZED_ALTERNATE_HOME                   "домой"
#define LOCALIZED_ALTERNATE_HT                     "сч"
#define LOCALIZED_ALTERNATE_IF                     "если"
#define LOCALIZED_ALTERNATE_IFELSE                 "еслииначе"
#define LOCALIZED_ALTERNATE_IFF                    "еслил" 
#define LOCALIZED_ALTERNATE_IFFALSE                "еслиложь" 
#define LOCALIZED_ALTERNATE_IFT                    "еслии" 
#define LOCALIZED_ALTERNATE_IFTRUE                 "еслиистина" 
#define LOCALIZED_ALTERNATE_INGAMEPORT             "портигры" 
#define LOCALIZED_ALTERNATE_INPORT                 "впорт" 
#define LOCALIZED_ALTERNATE_INPORTB                "впортб" 
#define LOCALIZED_ALTERNATE_INT                    "целое" 
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
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           "связьпосетивыкл" 
#define LOCALIZED_ALTERNATE_NETACCEPTON            "связьпосетивкл" 
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
#define LOCALIZED_ALTERNATE_RC                     "жс" 
#define LOCALIZED_ALTERNATE_RCS                    "жсы" 
#define LOCALIZED_ALTERNATE_READCHAR               "ждисимвол" 
#define LOCALIZED_ALTERNATE_READCHARS              "ждисимволы" 
#define LOCALIZED_ALTERNATE_READER                 "считыватель" 
#define LOCALIZED_ALTERNATE_READLIST               "ждисписок" 
#define LOCALIZED_ALTERNATE_READPOS                "читайкол" 
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
#define LOCALIZED_GENERAL_OKBUTTON      "&OK" // NOT_YET_LOCALIZED
#define LOCALIZED_GENERAL_CANCELBUTTON  "&Отмена" 
#define LOCALIZED_GENERAL_APPLYBUTTON   "&Применить" 

#define LOCALIZED_GENERAL_PRODUCTNAME   "FMSLogo" 



//
// The menu options on the main window 
//
#define LOCALIZED_FILE        "&Файл" 
#define LOCALIZED_FILE_NEW    "&Новый" 
#define LOCALIZED_FILE_LOAD   "&Загрузить..." 
#define LOCALIZED_FILE_OPEN   "&Открыть..."  
#define LOCALIZED_FILE_SAVE   "&Сохранить"  
#define LOCALIZED_FILE_SAVEAS "Сохранить &как..." 
#define LOCALIZED_FILE_EDIT   "&Редактировать..." 
#define LOCALIZED_FILE_ERASE  "С&тереть..." 
#define LOCALIZED_FILE_EXIT   "&Выход" 

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
#define LOCALIZED_HELP_ABOUTFMSLOGO    "&О "LOCALIZED_GENERAL_PRODUCTNAME"..."
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
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        "X-левый" 
#define LOCALIZED_SELECTACTIVEAREA_XLOW         "X-правый" 
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH "Количество шагов на дюйм:" 
#define LOCALIZED_SELECTACTIVEAREA_RESET        "&Сброс"  
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON 
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON 


//
// Menu options in the popup menu
//
#define LOCALIZED_POPUP_COPY                     "Копировать" 
#define LOCALIZED_POPUP_CUT                      "Вырезать" 
#define LOCALIZED_POPUP_PASTE                    "Вставить" 
#define LOCALIZED_POPUP_DELETE                   "Удалить" 
#define LOCALIZED_POPUP_UNDO                     "Отменить" 
#define LOCALIZED_POPUP_SELECTALL                "Выделить всё" 
#define LOCALIZED_POPUP_HELP                     "Поиск по разделу" 

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
#define LOCALIZED_EDITOR_EDIT_UNDO               "&Отмена\tCtrl+Z" 
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

#define LOCALIZED_EDITOR_TEST                    "Тест!" 

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
#define LOCALIZED_STATUS_PALETTE                "Используемая палитра:" 
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
#define LOCALIZED_ABOUTFMS                     "О "LOCALIZED_GENERAL_PRODUCTNAME 
#define LOCALIZED_ABOUTFMS_VERSION             LOCALIZED_GENERAL_PRODUCTNAME" Версия "FMSLOGO_VERSION 
#define LOCALIZED_ABOUTFMS_GUI                 "ГИП Джорджа Миллза by George Mills (mills@softronix.com)\nSoftronics, Inc.\nhttp:\x2F/www.softronix.com/" 
#define LOCALIZED_ABOUTFMS_CORE                "Ядро Брайена Харви (bh@cs.berkeley.edu)\nКалифорнийский университет Беркли" 
#define LOCALIZED_ABOUTFMS_INSTALLER           "Инсталляция базируется на Nullsoft Scriptable Install \nhttp:\x2F/nsis.sourceforge.net/" 
#define LOCALIZED_ABOUTFMS_ADVENTURE           "The Great Logo Adventure (ISBN 0-9651934-6-2)\nнаписанная и переданная Джимом Мюллером\nдоступна на http:\x2F/www.softronix.com/" 
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       "Благодарим Йегуду Катца (yehuka@softhome.net)\nи Эриха Непйвиртза (erich.neuwirth@univie.ac.at)" 
#define LOCALIZED_ABOUTFMS_GPL                 LOCALIZED_GENERAL_PRODUCTNAME" распространяется свободно\nСм. лицензию ГНУ" 
#define LOCALIZED_ABOUTFMS_NEWSGROUP           "Группа новостей в Интернете: comp.lang.logo\nпосетите форум на\nhttp:\x2F/groups.yahoo.com/group/LogoForum/" 
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     "Изучение внутренних свойств компьютера,\nот MultiMedia Logic из Softronics, Inc." 
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON 


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      "О FMS" 
#define LOCALIZED_ABOUTMS_FMS                  "FMS означает 'Fight Multiple Sclerosis'." 
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     "Пожалуйста, рассмотрите возможность помощи\nNational Multiple Sclerosis Society.\nhttp:\x2F/www.nmss.org\n1-800-FIGHT-MS" 
#define LOCALIZED_ABOUTMS_OK                   LOCALIZED_GENERAL_OKBUTTON 


//
// Strings on the SELECTBOX Dialog box
//
#define LOCALIZED_SELECTBOX_OK                 LOCALIZED_GENERAL_OKBUTTON 
#define LOCALIZED_SELECTBOX_CANCEL             LOCALIZED_GENERAL_CANCELBUTTON


// 
// Strings in various other dialog boxes
// 

#define LOCALIZED_CHANGESINEDITORMAYBELOST  "Changes in this edit session may be lost.\n\nDo you really want to exit "LOCALIZED_GENERAL_PRODUCTNAME"?" // NOT_YET_LOCALIZED
#define LOCALIZED_EDITSESSIONISRUNNING      "An Edit session is running" // NOT_YET_LOCALIZED

#define LOCALIZED_NOTHALTEDREALLYEXIT        LOCALIZED_GENERAL_PRODUCTNAME" does not like exiting while not halted.\n\nDo you really want to exit "LOCALIZED_GENERAL_PRODUCTNAME"?" // NOT_YET_LOCALIZED
#define LOCALIZED_NOTHALTEDREALLYHALT        LOCALIZED_GENERAL_PRODUCTNAME" does not like exiting while not halted.\n\nDo you really want to Halt "LOCALIZED_GENERAL_PRODUCTNAME"?" // NOT_YET_LOCALIZED
#define LOCALIZED_LOGOISNOTHALTED            LOCALIZED_GENERAL_PRODUCTNAME" is not Halted" // NOT_YET_LOCALIZED

#define LOCALIZED_COULDNOTWRITEBMP            "Could not write .bmp" // NOT_YET_LOCALIZED
#define LOCALIZED_COULDNOTOPENBMP             "Could not open .bmp" // NOT_YET_LOCALIZED
#define LOCALIZED_COULDNOTCREATEBMP           "Unable to create Windows 3.0 bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_NOTVALIDBMP                 "Not a Windows 3.0 bitmap" // NOT_YET_LOCALIZED

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         "You have not saved to disk" // NOT_YET_LOCALIZED
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     "Executing a new will erase all definitions.\n\nContinue with New?" // NOT_YET_LOCALIZED
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE "The file being loaded will be merged into your workspace\nand may overwrite your unsaved changes.\n\nContinue with Load?" // NOT_YET_LOCALIZED
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    "This will erase all of your unsaved changes.\n\nContinue with Open?" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITORISOPEN                  "Did you know you have an edit session running?\n\nAny changes in this edit session are not being saved." // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_CANTREADFILE            "Unable to read file \"%s\" from disk" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_CANTWRITEFILE           "Unable to write file \"%s\" to disk" // NOT_YET_LOCALIZED

#define LOCALIZED_SAVETOWORKSPACE                "Save to Workspace" // NOT_YET_LOCALIZED
#define LOCALIZED_CONTENTSCHANGED                "Contents Changed" // NOT_YET_LOCALIZED
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE "The contents have changed.\nWould you like to save the changes to the workspace?" // NOT_YET_LOCALIZED



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  "There was a problem saving the contents of the editor to the workspace.  The cursor will be positioned just after last successful definition.\n\nCheck the Commander for possible error message." // NOT_YET_LOCALIZED
#define LOCALIZED_RETURNTOEDIT                  "Return to the editor?" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITFAILEDTOLOAD              LOCALIZED_SAVETOWORKSPACE // NOT_YET_LOCALIZED



// 
//  Strings used in the File-Open filters
//
#define LOCALIZED_FILEFILTER_ALLFILES "All Files (*.*)|*.*|" // NOT_YET_LOCALIZED
#define LOCALIZED_FILEFILTER_LOGO     "Logo Files (*.lgo)|*.lgo|"LOCALIZED_FILEFILTER_ALLFILES // NOT_YET_LOCALIZED
#define LOCALIZED_FILEFILTER_IMAGE    "Bitmap Files (*.bmp)|*.bmp|GIF Files (*.gif)|*.gif|"LOCALIZED_FILEFILTER_ALLFILES // NOT_YET_LOCALIZED



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
#define LOCALIZED_STEPPING                  "Single Step" // NOT_YET_LOCALIZED

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  "%s defined\n" // NOT_YET_LOCALIZED


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    "erase" // NOT_YET_LOCALIZED
#define LOCALIZED_PENMODE_REVERSE  "reverse" // NOT_YET_LOCALIZED
#define LOCALIZED_PENMODE_PAINT    "paint" // NOT_YET_LOCALIZED

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          "Logo: Fatal Internal Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       "Logo: Out of memory" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_OUTOFMEMORY            "Out of memory" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_STACKOVERFLOW          "stack overflow" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      "turtle out of bounds" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BADGRAPHINIT           "couldn't initialize graphics" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BADDATA                "%p doesn't like %s as input" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DIDNTOUTPUT            "%p didn't output to %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        "not enough inputs to %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_TOOMUCH                "too much inside ()'s" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    "You don't say what to do with %s" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_PARENMISMATCH          "too many ('s" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NOVALUE                "%s has no value" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        "unexpected ')'" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      "unexpected ']'" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        "unexpected '}'" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DONTKNOWHOWTO          "I don't know how to %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NOCATCHTAG             "Can't find catch tag for %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_ALREADYDEFINED         "%p is already defined" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_STOPPING               "Stopping..." // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_ALREADYDRIBBLING       "Already dribbling" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM                   "File system error: %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          "Could not open file" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         "Unable to open file: %t" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       "File already open" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           "File not open" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  "Could not create editor file" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   "Could not launch the editor"  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    "Could not read editor file"  // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_IFWARNING              "Assuming you mean IFELSE, not IF" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_SHADOWWARNING          "%p shadowed by local in procedure call" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_USER                   "Throw \"Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_ISPRIMITIVE            "%p is a primitive" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_TONOTINSIDE            "Can't use TO inside a procedure" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_ATTOPLEVEL             "Can only use %p inside a procedure" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_ATTOPLEVEL2            "You must be in a procedure to use OUTPUT or STOP" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NOTEST                 "%p without TEST" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BADMACROOUTPUT         "Macro output %s instead of a list" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DEEPEND                "END inside multi-line instruction" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DEEPENDIN              "END inside multi-line instruction in %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_UNKNOWN                "Unknown error condition - internal error." // NOT_YET_LOCALIZED

#define LOCALIZED_PAUSING                      "Pausing..." // NOT_YET_LOCALIZED


//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      "Error" // NOT_YET_LOCALIZED
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

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   "%s already exists" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    "%s does not exist" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_DLLNOTLOADED          "DLL is not loaded" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLLOADFAILED         "DLL load failed" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    "Invalid data type input" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  "Invalid output type" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   "Function not found" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  "Not all Type/Data inputs are paired" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_NETWORK               "Network Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKRECEIVE        "Network Receive Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKSEND           "Network Send Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       "Unexpected Error, Network may be shutdown" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     "Not started" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED "Already started" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKALREADYON      "Already on" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_NETWORKALREADYOFF     "Already off" // NOT_YET_LOCALIZED

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

#define LOCALIZED_ERROR_POLYSTART               "PolyStart Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED "You already have a Polygon started" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_POLYEND                 "PolyEnd Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       "You have not started a Polygon" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     "You must have at least 3 vectors to define a polygon" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_SOUND                 "Sound Error" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_MIDI                  "MIDI Error" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     "Invalid MIDI device" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MIDIALREADYOPEN       "Already open" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MIDINOTOPEN           "Not open" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      "No Text in Clipboard" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_MCI                   "MCI Error" // NOT_YET_LOCALIZED

#define LOCALIZED_ERROR_TIMERNOTFOUND         "Timer not found" // NOT_YET_LOCALIZED

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
#define LOCALIZED_INPUT         "Input:" // NOT_YET_LOCALIZED
#define LOCALIZED_PROMPT_TO     "To Mode (Cancel to End)" // NOT_YET_LOCALIZED
#define LOCALIZED_PROMPT_LIST   "List Mode (Cancel to Halt)" // NOT_YET_LOCALIZED
#define LOCALIZED_PROMPT_PAUSE  "Pause Mode (Cancel to Continue)" // NOT_YET_LOCALIZED
#define LOCALIZED_PROMPT_INPUT  "Input Mode (Cancel to Halt)" // NOT_YET_LOCALIZED

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      "Changed to \"%s\"" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_CHDIRFAILED         "Could not chdir to directory \"%s\"" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_POPPEDTO            "Popped to \"%s\"" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_MKDIRSUCCEEDED      "Now in newly created directory \"%s\""  // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_MKDIRFAILED         "Failed to create directory \"%s\""  // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_RMDIRSUCCEEDED      "Removed directory \"%s\""  // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_RMDIRFAILED         "Failed to remove directory \"%s\""  // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  "The directory does not exist." // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY "Make sure the directory is empty before trying to remove it." // NOT_YET_LOCALIZED


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       "Logo Picture" // NOT_YET_LOCALIZED

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    "Active Area" // NOT_YET_LOCALIZED
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
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING "Cannot find %s" // NOT_YET_LOCALIZED


//
// The words that describe color vectors.
// These words were selected from a de facto HTML standard, so you may
// be able to find translations for the entire set on the Web.
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
// These should match the cooresponding terms that is used
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
