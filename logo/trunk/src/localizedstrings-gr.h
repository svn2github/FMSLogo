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
// This file contains localized strings for Greek by Theodoros Chatzigiannakis
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
//   "Impossible d'utiliser POUR (TO) dans une procιdure"
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
#define LOCALIZED_ALTERNATE_TRUE     "ΑΛΗΘΗΣ" // 
#define LOCALIZED_ALTERNATE_FALSE    "ΨΕΥΔΗΣ" // 
#define LOCALIZED_ALTERNATE_END      "ΤΕΛΟΣ" // 
#define LOCALIZED_ALTERNATE_TOPLEVEL "ΑΡΧΗ" // 
#define LOCALIZED_ALTERNATE_SYSTEM   "ΣΥΣΤΗΜΑ" // 

//
// Localized "alternate" names of Logo special variables
//
#define LOCALIZED_ALTERNATE_CASEIGNOREDP    "caseignoredp"
#define LOCALIZED_ALTERNATE_ERRACT          "ΟΔΗΓΙΕΣ_ΣΦΑΛΜΑΤΟΣ"
#define LOCALIZED_ALTERNATE_STARTUP         "ΕΚΚΙΝΗΣΗ"
#define LOCALIZED_ALTERNATE_REDEFP          "ΕΠΑΝΑΠΡΟΣΔΙΟΡΙΣΜΟΣ" 
#define LOCALIZED_ALTERNATE_PRINTWIDTHLIMIT "ΠΛΑΤΟΣ_ΕΚΤΥΠΩΣΗΣ"
#define LOCALIZED_ALTERNATE_PRINTDEPTHLIMIT "ΒΑΘΟΣ_ΕΚΤΥΠΩΣΗΣ"


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
#define LOCALIZED_ALTERNATE__DEFMACRO              ".ΟΡΙΣΜΟΣ_ΜΑΚΡΟΕΝΤΛΗ" // 
#define LOCALIZED_ALTERNATE__EQ                    ".ΙΣΟ" // 
#define LOCALIZED_ALTERNATE__MACRO                 ".ΜΑΚΡΟΕΝΤΟΛΗ" // 
#define LOCALIZED_ALTERNATE__MAYBEOUTPUT           ".ΠΙΘΑΝΗ_ΕΞΟΔΟΣ" // 
#define LOCALIZED_ALTERNATE__SETBF                 ".setbf" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE__SETFIRST              ".setfirst" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE__SETITEM               ".setitem" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ACTIVEAREA             "ΕΝΕΡΓΗ_ΠΕΡΙΟΧΗ" // 
#define LOCALIZED_ALTERNATE_ALLOPEN                "ΑΝΟΙΧΤΑ" // 
#define LOCALIZED_ALTERNATE_AND                    "ΚΑΙ" // 
#define LOCALIZED_ALTERNATE_APPLY                  "ΕΦΑΡΜΟΓΗ" // 
#define LOCALIZED_ALTERNATE_ARCCOS                 "arccos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARCSIN                 "arcsin" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARCTAN                 "arctan" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARITY                  "arity" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARRAY                  "ΠΙΝΑΚΑΣ" // 
#define LOCALIZED_ALTERNATE_ARRAYP                 "arrayp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ARRAY_                 "ΠΙΝΑΚΑΣ?" // 
#define LOCALIZED_ALTERNATE_ASCII                  "ascii" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ASHIFT                 "ΠΡΟΣΗΜΑΣΜΕΝΗ_ΟΛΙΣΘΗΣΗ" // 
#define LOCALIZED_ALTERNATE_BACK                   "ΠΙΣΩ" // 
#define LOCALIZED_ALTERNATE_BACKSLASHEDP           "backslashedp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BACKSLASHED_           "backslashed?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BEFOREP                "beforep" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BEFORE_                "ΠΡΙΝ?" // 
#define LOCALIZED_ALTERNATE_BF                     "bf" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BFS                    "bfs" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITAND                 "ΔΥΑΔΙΚΟ_ΚΑΙ" // 
#define LOCALIZED_ALTERNATE_BITBLOCK               "bitblock" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITCOPY                "bitcopy" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITCUT                 "bitcut" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITFIT                 "bitfit" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITINDEX               "bitindex" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITLOAD                "bitload" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITLOADSIZE            "bitloadsize" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITSIZE                "bitsize" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITMAPTURTLE           "bitmapturtle" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITMODE                "bitmode" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITNOT                 "ΔΥΑΔΙΚΟ_ΟΧΙ" // 
#define LOCALIZED_ALTERNATE_BITOR                  "ΔΥΑΔΙΚΟ_Η" // 
#define LOCALIZED_ALTERNATE_BITPASTE               "bitpaste" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITPASTETOINDEX        "bitpastetoindex" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITSAVE                "bitsave" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BITXOR                 "ΔΥΑΔΙΚΟ_ΑΠ0ΟΚΛΕΙΣΤΙΚΟ_Η" // 
#define LOCALIZED_ALTERNATE_BK                     "bk" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BL                     "bl" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BURIED                 "buried" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BURY                   "bury" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTFIRST               "ΧΩΡΙΣ_ΠΡΩΤΟ" // 
#define LOCALIZED_ALTERNATE_BUTFIRSTS              "ΧΩΡΙΣ_ΠΡΩΤΑ" // 
#define LOCALIZED_ALTERNATE_BUTLAST                "ΧΩΡΙΣ_ΤΕΛΕΥΤΑΙΟ" // 
#define LOCALIZED_ALTERNATE_BUTTONCREATE           "ΚΟΥΜΠΙ_ΔΗΜΙΟΥΡΓΙΑ" // 
#define LOCALIZED_ALTERNATE_BUTTONDELETE           "ΚΟΥΜΠΙ_ΔΙΑΓΡΑΦΗ" // 
#define LOCALIZED_ALTERNATE_BUTTONENABLE           "ΚΟΥΜΠΙ_ΕΝΕΡΓΟΠΟΙΗΣΗ" // 
#define LOCALIZED_ALTERNATE_BUTTONUPDATE           "ΚΟΥΜΠΙ_ΕΝΗΜΕΡΩΣΗ" // 
#define LOCALIZED_ALTERNATE_BUTTONP                "buttonp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_BUTTON_                "ΚΟΥΜΠΙ?" // 
#define LOCALIZED_ALTERNATE_BYE                    "ΑΝΤΙΟ" // 
#define LOCALIZED_ALTERNATE_CATCH                  "catch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CHAR                   "ΧΑΡΑΚΤΗΡΑΣ" // 
#define LOCALIZED_ALTERNATE_CHDIR                  "ΚΑΤΑΛΟΓΟΣ_ΑΛΛΑΓΗ" // 
#define LOCALIZED_ALTERNATE_CHECKBOXCREATE         "ΠΛΑΙΣΙΟ_ΕΛΕΓΧΟΥ_ΔΗΜΙΟΥΡΓΙΑ" // 
#define LOCALIZED_ALTERNATE_CHECKBOXDELETE         "ΠΛΑΙΣΙΟ_ΕΛΕΓΧΟΥ_ΔΙΑΓΡΑΦΗ" // 
#define LOCALIZED_ALTERNATE_CHECKBOXENABLE         "ΠΛΑΙΣΙΟ_ΕΛΕΓΧΟΥ_ΕΝΕΡΓΟΠΟΙΗΣΗ" // 
#define LOCALIZED_ALTERNATE_CHECKBOXGET            "ΠΛΑΙΣΙΟ_ΕΛΕΓΧΟΥ_ΤΙΜΗ" // 
#define LOCALIZED_ALTERNATE_CHECKBOXSET            "ΠΛΑΙΣΙΟ_ΕΛΕΓΧΟΥ_ΟΡΙΣΜΟΣ" // 
#define LOCALIZED_ALTERNATE_CLEAN                  "ΚΑΘΑΡΙΣΜΟΣ" // 
#define LOCALIZED_ALTERNATE_CLEARPALETTE           "clearpalette" //
#define LOCALIZED_ALTERNATE_CLEARSCREEN            "ΚΑΘΑΡΙΣΜΟΣ_ΟΘΟΝΗΣ" // 
#define LOCALIZED_ALTERNATE_CLEARTEXT              "ΚΑΘΑΡΙΜΣΟΣ_ΚΕΙΜΕΝΟΥ" // 
#define LOCALIZED_ALTERNATE_CLEARTIMER             "ΚΑΘΑΡΙΣΜΟΣ_ΧΡΟΝΟΜΕΤΡΟΥ" // 
#define LOCALIZED_ALTERNATE_CLOSE                  "ΚΛΕΙΣΙΜΟ" // 
#define LOCALIZED_ALTERNATE_CLOSEALL               "ΚΛΕΙΣΙΜΟ_ΟΛΩΝ" // 
#define LOCALIZED_ALTERNATE_CO                     "co" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_COMBOBOXADDSTRING      "ΠΛΑΙΣΙΟ_ΚΕΙΜΕΝΟΥ_ΠΡΟΣΘΗΚΗ" // 
#define LOCALIZED_ALTERNATE_COMBOBOXCREATE         "ΠΛΑΙΣΙΟ_ΚΕΙΜΕΝΟΥ_ΔΗΜΙΟΥΡΓΙΑ" // 
#define LOCALIZED_ALTERNATE_COMBOBOXDELETE         "ΠΛΑΙΣΙΟ_ΚΕΙΜΕΝΟΥ_ΔΙΑΓΡΑΦΗ" // 
#define LOCALIZED_ALTERNATE_COMBOBOXENABLE         "ΠΛΑΙΣΙΟ_ΚΕΙΜΕΝΟΥ_ΕΝΕΡΓΟΠΟΙΗΣΗ" // 
#define LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING   "ΠΛΑΙΣΙΟ_ΚΕΙΜΕΝΟΥ_ΑΦΑΙΡΕΣΗ" // 
#define LOCALIZED_ALTERNATE_COMBOBOXGETTEXT        "ΠΛΑΙΣΙΟ_ΚΕΙΜΕΝΟΥ_ΤΙΜΗ" // 
#define LOCALIZED_ALTERNATE_COMBOBOXSETTEXT        "ΠΛΑΙΣΙΟ_ΚΕΙΜΕΝΟΥ_ΟΡΙΣΜΟΣ" // 
#define LOCALIZED_ALTERNATE_CONTENTS               "ΠΕΡΙΕΧΟΜΕΝΑ" // 
#define LOCALIZED_ALTERNATE_CONTINUE               "ΣΥΝΕΧΕΙΑ" // 
#define LOCALIZED_ALTERNATE_COPYDEF                "ΑΝΤΙΓΡΑΦΗ_ΟΡΙΣΜΟΥ" // 
#define LOCALIZED_ALTERNATE_COS                    "ΣΥΝΗΜΙΤΟΝΟ" // 
#define LOCALIZED_ALTERNATE_COUNT                  "ΜΕΤΡΗΣΗ" // 
#define LOCALIZED_ALTERNATE_CS                     "cs" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CT                     "ct" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_CURSOR                 "cursor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DEBUGWINDOWS           "debugwindows" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DEFINE                 "ΟΡΙΣΜΟΣ" // 
#define LOCALIZED_ALTERNATE_DEFINEDP               "definedp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DEFINED_               "ΟΡΙΣΤΗΚΕ?" // 
#define LOCALIZED_ALTERNATE_DIALOGCREATE           "ΠΑΡΑΘΥΡΟ_ΔΙΑΛΟΓΟΥ_ΔΗΜΙΟΥΡΓΙΑ" // 
#define LOCALIZED_ALTERNATE_DIALOGENABLE           "ΠΑΡΑΘΥΡΟ_ΔΙΑΛΟΓΟΥ_ΕΝΕΡΓΟΠΟΙΗΣΗ" // 
#define LOCALIZED_ALTERNATE_DIALOGDELETE           "ΠΑΡΑΘΥΡΟ_ΔΙΑΛΟΓΟΥ_ΔΙΑΓΡΑΦΗ" // 
#define LOCALIZED_ALTERNATE_DIALOGFILEOPEN         "ΠΑΡΑΘΥΡΟ_ΑΡΧΕΙΟ_ΑΝΟΙΓΜΑ" // 
#define LOCALIZED_ALTERNATE_DIALOGFILESAVE         "ΠΑΡΑΘΥΡΟ_ΑΡΧΕΙΟ_ΑΠΟΘΗΚΕΥΣΗ" // 
#define LOCALIZED_ALTERNATE_DIFFERENCE             "ΔΙΑΦΟΡΑ" // 
#define LOCALIZED_ALTERNATE_DIRECTORIES            "ΚΑΤΑΛΟΓΟΙ" // 
#define LOCALIZED_ALTERNATE_DLLCALL                "DLL_ΚΛΗΣΗ" // 
#define LOCALIZED_ALTERNATE_DLLFREE                "DLL_ΚΛΕΙΣΙΜΟ" // 
#define LOCALIZED_ALTERNATE_DLLLOAD                "DLL_ΑΝΟΙΓΜΑ" // 
#define LOCALIZED_ALTERNATE_DOWN                   "ΚΑΤΩ" // 
#define LOCALIZED_ALTERNATE_DOWNPITCH              "downpitch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_DRIBBLE                "ΚΑΤΑΓΡΑΦΗ" // 
#define LOCALIZED_ALTERNATE_ED                     "ed" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EDIT                   "edit" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ELLIPSEARC             "ellipsearc" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EMPTYP                 "emptyp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EMPTY_                 "ΑΔΕΙΟ?" // 
#define LOCALIZED_ALTERNATE_EOFP                   "eofp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EOF_                   "ΤΕΛΟΣ_ΑΡΧΕΙΟΥ?" // 
#define LOCALIZED_ALTERNATE_EQUALP                 "equalp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_EQUAL_                 "ΙΣΟ?" // 
#define LOCALIZED_ALTERNATE_ER                     "er" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ERASE                  "ΣΒΗΣΙΜΟ" // 
#define LOCALIZED_ALTERNATE_ERASEFILE              "ΣΒΗΣΙΜΟ_ΑΡΧΕΙΟΥ" // 
#define LOCALIZED_ALTERNATE_ERF                    "erf" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ERROR                  "ΣΦΑΛΜΑ" // 
#define LOCALIZED_ALTERNATE_EVENTCHECK             "ΕΛΕΓΧΟΣ_ΓΕΓΟΝΟΤΩΝ" // 
#define LOCALIZED_ALTERNATE_EXP                    "exp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FD                     "fd" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FENCE                  "fence" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FILL                   "ΓΕΜΙΣΜΑ" // 
#define LOCALIZED_ALTERNATE_FILES                  "ΑΡΧΕΙΑ" // 
#define LOCALIZED_ALTERNATE_FIRST                  "ΠΡΩΤΟ" // 
#define LOCALIZED_ALTERNATE_FIRSTS                 "ΠΡΩΤΑ" // 
#define LOCALIZED_ALTERNATE_FLOODCOLOR             "ΧΡΩΜΑ_ΓΕΜΙΣΜΑΤΟΣ" // 
#define LOCALIZED_ALTERNATE_FONTFACENAMES          "ΓΡΑΜΜΑΤΟΣΕΙΡΕΣ" // 
#define LOCALIZED_ALTERNATE_FOREVER                "forever" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FORM                   "form" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FORWARD                "ΕΜΠΡΟΣ" // 
#define LOCALIZED_ALTERNATE_FPUT                   "fput" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FS                     "fs" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_FULLSCREEN             "ΠΛΗΡΗΣ_ΟΘΟΝΗ" // 
#define LOCALIZED_ALTERNATE_FULLTEXT               "ΠΛΗΡΕΣ_ΚΕΙΜΕΝΟ" // 
#define LOCALIZED_ALTERNATE_GETFOCUS               "ΕΣΤΙΑ" // 
#define LOCALIZED_ALTERNATE_GOTO                   "ΠΗΓΑΙΝΕ" // 
#define LOCALIZED_ALTERNATE_GIFLOAD                "GIF_ΑΝΟΙΓΜΑ" // 
#define LOCALIZED_ALTERNATE_GIFSIZE                "GIF_ΜΕΓΕΘΟΣ" // 
#define LOCALIZED_ALTERNATE_GIFSAVE                "GIF_ΑΠΟΘΗΚΕΥΣΗ" // 
#define LOCALIZED_ALTERNATE_GPROP                  "ΙΔΙΟΤΗΤΑ_ΤΙΜΗ" // 
#define LOCALIZED_ALTERNATE_GREATEREQUALP          "greaterequalp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GREATEREQUAL_          "ΜΕΓΑΛΥΤΕΡΟ_ΙΣΟ?" // 
#define LOCALIZED_ALTERNATE_GREATERP               "greaterp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_GREATER_               "ΜΕΓΑΛΥΤΕΡΟ?" // 
#define LOCALIZED_ALTERNATE_GROUPBOXCREATE         "ΠΛΑΙΣΙΟ_ΟΜΑΔΑΣ_ΔΗΜΙΟΥΡΓΙΑ" // 
#define LOCALIZED_ALTERNATE_GROUPBOXDELETE         "ΠΛΑΙΣΙΟ_ΟΜΑΔΑΣ_ΔΙΑΓΡΑΦΗ" // 
#define LOCALIZED_ALTERNATE_HALT                   "halt" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HASOWNPENP             "hasownpenp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HASOWNPEN_             "hasownpen?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HEADING                "ΚΑΤΕΥΘΥΝΣΗ" // 
#define LOCALIZED_ALTERNATE_HELP                   "ΒΟΗΘΕΙΑ" // 
#define LOCALIZED_ALTERNATE_HIDETURTLE             "hideturtle" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_HOME                   "ΣΠΙΤΙ" // 
#define LOCALIZED_ALTERNATE_HT                     "ht" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_IF                     "ΑΝ" // 
#define LOCALIZED_ALTERNATE_IFELSE                 "ΑΝ_ΑΛΛΙΩΣ" // 
#define LOCALIZED_ALTERNATE_IFF                    "iff" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_IFFALSE                "ΑΝ_ΨΕΥΔΗΣ" // 
#define LOCALIZED_ALTERNATE_IFT                    "ift" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_IFTRUE                 "ΑΝ_ΑΛΗΘΗΣ" // 
#define LOCALIZED_ALTERNATE_INGAMEPORT             "ingameport" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_INPORT                 "inport" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_INPORTB                "inportb" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_INT                    "ΑΚΕΡΑΙΟΣ" // 
#define LOCALIZED_ALTERNATE_ITEM                   "ΣΤΟΙΧΕΙΟ" // 
#define LOCALIZED_ALTERNATE_KEYBOARDOFF            "ΠΛΗΚΤΡΟΛΟΓΙΟ_ΑΠΕΝΕΡΓΟΠΟΙΗΣΗ" // 
#define LOCALIZED_ALTERNATE_KEYBOARDON             "ΠΛΗΚΤΡΟΛΟΓΙΟ_ΕΝΕΡΓΟΠΟΙΗΣΗ" // 
#define LOCALIZED_ALTERNATE_KEYBOARDVALUE          "ΠΛΗΚΤΡΟΛΟΓΙΟ_ΤΙΜΗ" // 
#define LOCALIZED_ALTERNATE_KEYP                   "keyp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_KEY_                   "ΠΛΗΚΤΡΟ?" // 
#define LOCALIZED_ALTERNATE_LABEL                  "ΕΤΙΚΕΤΑ" // 
#define LOCALIZED_ALTERNATE_LABELFONT              "ΕΤΙΚΕΤΑ_ΓΡΑΜΜΑΤΟΣΕΙΡΑ" // 
#define LOCALIZED_ALTERNATE_LABELSIZE              "ΕΤΙΚΕΤΑ_ΜΕΓΕΘΟΣ" // 
#define LOCALIZED_ALTERNATE_LAST                   "ΤΕΛΕΥΤΑΙΟ" // 
#define LOCALIZED_ALTERNATE_LEFT                   "ΑΡΙΣΤΕΡΑ" // 
#define LOCALIZED_ALTERNATE_LEFTROLL               "leftroll" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LESSEQUALP             "lessequalp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LESSEQUAL_             "ΜΙΚΡΟΤΕΡΟ_ΙΣΟ?" // 
#define LOCALIZED_ALTERNATE_LESSP                  "lessp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LESS_                  "ΜΙΚΡΟΤΕΡΟ?" // 
#define LOCALIZED_ALTERNATE_LIGHT                  "ΦΩΣ" // 
#define LOCALIZED_ALTERNATE_LIST                   "ΛΙΣΤΑ" // 
#define LOCALIZED_ALTERNATE_LISTBOXADDSTRING       "ΠΛΑΙΣΙΟ_ΛΙΣΤΑΣ_ΠΡΟΣΘΗΚΗ" // 
#define LOCALIZED_ALTERNATE_LISTBOXCREATE          "ΠΛΑΙΣΙΟ_ΛΙΣΤΑΣ_ΔΗΜΙΟΥΡΓΙΑ" // 
#define LOCALIZED_ALTERNATE_LISTBOXENABLE          "ΠΛΑΙΣΙΟ_ΛΙΣΤΑΣ_ΕΝΕΡΓΟΠΙΟΗΣΗ" // 
#define LOCALIZED_ALTERNATE_LISTBOXDELETE          "ΠΛΑΙΣΙΟ_ΛΙΣΤΑΣ_ΔΙΑΓΡΑΦΗ" // 
#define LOCALIZED_ALTERNATE_LISTBOXDELETESTRING    "ΠΛΑΙΣΙΟ_ΛΙΣΤΑΣ_ΑΦΑΙΡΕΣΗ" // 
#define LOCALIZED_ALTERNATE_LISTBOXGETSELECT       "ΠΛΑΙΣΙΟ_ΛΙΣΤΑΣ_ΕΠΙΛΟΓΗ" // 
#define LOCALIZED_ALTERNATE_LISTP                  "listp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LIST_                  "ΛΙΣΤΑ?" // 
#define LOCALIZED_ALTERNATE_LN                     "ln" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LOAD                   "ΦΟΡΤΩΣΗ" // 
#define LOCALIZED_ALTERNATE_LOCAL                  "ΤΟΠΙΚΟ" // 
#define LOCALIZED_ALTERNATE_LOG10                  "log10" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LOGOVERSION            "ΕΚΔΟΣΗ" // 
#define LOCALIZED_ALTERNATE_LOWERCASE              "ΠΕΖΑ" // 
#define LOCALIZED_ALTERNATE_LPUT                   "ΠΡΟΣΘΗΚΗ_ΤΕΛΟΣ" // 
#define LOCALIZED_ALTERNATE_LR                     "lr" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_LSHIFT                 "ΟΛΙΣΘΗΣΗ" // 
#define LOCALIZED_ALTERNATE_LT                     "lt" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MACHINE                "ΜΗΧΑΝΗ" // 
#define LOCALIZED_ALTERNATE_MACROP                 "macrop" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MACRO_                 "ΜΑΚΡΟΕΝΤΟΛΗ?" // 
#define LOCALIZED_ALTERNATE_MAKE                   "ΜΕΤΑΒΛΗΤΗ" // 
#define LOCALIZED_ALTERNATE_MCI                    "mci" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MEMBER                 "ΜΕΛΟΣ" // 
#define LOCALIZED_ALTERNATE_MEMBERP                "memberp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MEMBER_                "ΜΕΛΟΣ?" // 
#define LOCALIZED_ALTERNATE_MESSAGEBOX             "ΜΗΝΥΜΑ" // 
#define LOCALIZED_ALTERNATE_MIDICLOSE              "MIDI_ΚΛΕΙΣΙΜΟ" // 
#define LOCALIZED_ALTERNATE_MIDIMESSAGE            "MIDI_ΜΗΝΥΜΑ" // 
#define LOCALIZED_ALTERNATE_MIDIOPEN               "MIDI_ΑΝΟΙΓΜΑ" // 
#define LOCALIZED_ALTERNATE_MINUS                  "ΜΕΙΟΝ" // 
#define LOCALIZED_ALTERNATE_MKDIR                  "ΚΑΤΑΛΟΓΟΣ_ΔΗΜΙΟΥΡΓΙΑ" // 
#define LOCALIZED_ALTERNATE_MODULO                 "modulo" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_MOUSEOFF               "ΠΟΝΤΙΚΙ_ΑΠΕΝΕΡΓΟΠΟΙΗΣΗ" // 
#define LOCALIZED_ALTERNATE_MOUSEON                "ΠΟΝΤΙΚΙ_ΕΝΕΡΓΟΠΟΙΗΣΗ" // 
#define LOCALIZED_ALTERNATE_MOUSEPOS               "ΠΟΝΤΙΚΙ_ΘΕΣΗ" // 
#define LOCALIZED_ALTERNATE_NAMEP                  "namep" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NAME_                  "ΟΝΟΜΑ?" // 
#define LOCALIZED_ALTERNATE_NAMES                  "ΟΝΟΜΑΤΑ" // 
#define LOCALIZED_ALTERNATE_NETACCEPTOFF           "ΔΙΚΤΥΟ_ΑΠΟΔΟΧΗ_ΑΠΕΝΕΡΓΟΠΟΙΗΣΗ" // 
#define LOCALIZED_ALTERNATE_NETACCEPTON            "ΔΙΚΤΥΟ_ΑΠΟΔΟΧΗ_ΕΝΕΡΓΟΠΟΙΗΣΗ" // 
#define LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE  "ΔΙΚΤΥΟ_ΑΠΟΔΟΧΗ_ΤΙΜΗ_ΛΗΨΗΣ" // 
#define LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE     "ΔΙΚΤΥΟ_ΑΠΟΔΟΧΗ_ΤΙΜΗ_ΑΠΟΣΤΟΛΗΣ" // 
#define LOCALIZED_ALTERNATE_NETCONNECTOFF          "ΔΙΚΤΥΟ_ΣΥΝΔΕΣΗ_ΑΠΕΝΕΡΓΟΠΟΙΗΣΗ" // 
#define LOCALIZED_ALTERNATE_NETCONNECTON           "ΔΙΚΤΥΟ_ΣΥΝΔΕΣΗ_ΕΝΕΡΓΟΠΟΙΗΣΗ" // 
#define LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE "ΔΙΚΤΥΟ_ΣΥΝΔΕΣΗ_ΤΙΜΗ_ΛΗΨΗΣ" // 
#define LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE    "ΔΙΚΤΥΟ_ΣΥΝΔΕΣΗ_ΤΙΜΗ_ΑΠΟΣΤΟΛΗΣ" // 
#define LOCALIZED_ALTERNATE_NETSHUTDOWN            "ΔΙΚΤΥΟ_ΑΠΕΝΕΡΓΟΠΟΙΗΣΗ" // 
#define LOCALIZED_ALTERNATE_NETSTARTUP             "ΔΙΚΤΥΟ_ΕΝΕΡΓΟΠΟΙΗΣΗ" // 
#define LOCALIZED_ALTERNATE_NOBITMAPTURTLE         "nobitmapturtle" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NODES                  "ΚΟΜΒΟΙ" // 
#define LOCALIZED_ALTERNATE_NODRIBBLE              "nodribble" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NOSTATUS               "nostatus" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NOT                    "ΟΧΙ" // 
#define LOCALIZED_ALTERNATE_NOTEQUALP              "notequalp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NOTEQUAL_              "ΟΧΙ_ΙΣΟ?" // 
#define LOCALIZED_ALTERNATE_NOYIELD                "noyield" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NUMBERP                "numberp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_NUMBER_                "ΑΡΙΘΜΟΣ?" // 
#define LOCALIZED_ALTERNATE_OP                     "op" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OPENAPPEND             "ΑΝΟΙΓΜΑ_ΠΡΟΣΑΡΤΗΣΗ" // 
#define LOCALIZED_ALTERNATE_OPENREAD               "ΑΝΟΙΓΜΑ_ΑΝΑΓΝΩΣΗ" // 
#define LOCALIZED_ALTERNATE_OPENUPDATE             "ΑΝΟΙΓΜΑ_ΕΝΗΜΕΡΩΣΗ" // 
#define LOCALIZED_ALTERNATE_OPENWRITE              "ΑΝΟΙΓΜΑ_ΕΓΓΡΑΦΗ" // 
#define LOCALIZED_ALTERNATE_OR                     "Η" // 
#define LOCALIZED_ALTERNATE_OUTPORT                "outport" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OUTPORTB               "outportb" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_OUTPUT                 "ΕΞΟΔΟΣ" // 
#define LOCALIZED_ALTERNATE_PARSE                  "ΕΠΕΞΕΡΓΑΣΙΑ" // 
#define LOCALIZED_ALTERNATE_PAUSE                  "ΠΑΥΣΗ" // 
#define LOCALIZED_ALTERNATE_PC                     "pc" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PD                     "pd" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PE                     "pe" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENCOLOR               "ΠΕΝΑ_ΧΡΩΜΑ" // 
#define LOCALIZED_ALTERNATE_PENDOWN                "ΠΕΝΑ_ΚΑΤΩ" // 
#define LOCALIZED_ALTERNATE_PENDOWNP               "pendownp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PENDOWN_               "ΠΕΝΑ_ΚΑΤΩ?" // 
#define LOCALIZED_ALTERNATE_PENERASE               "ΠΕΝΑ_ΣΒΗΣΙΜΟ" // 
#define LOCALIZED_ALTERNATE_PENMODE                "ΠΕΝΑ_ΣΥΣΤΗΜΑ" // 
#define LOCALIZED_ALTERNATE_PENPAINT               "ΠΕΝΑ_ΣΧΕΔΙΑΣΗ" // 
#define LOCALIZED_ALTERNATE_PENPATTERN             "ΠΕΝΑ_ΜΟΤΙΒΟ" // 
#define LOCALIZED_ALTERNATE_PENREVERSE             "ΠΕΝΑ_ΑΝΤΙΣΤΡΟΦΗ" // 
#define LOCALIZED_ALTERNATE_PENSIZE                "ΠΕΝΑ_ΜΕΓΕΘΟΣ" // 
#define LOCALIZED_ALTERNATE_PENUP                  "ΠΕΝΑ_ΠΑΝΩ" // 
#define LOCALIZED_ALTERNATE_PERSPECTIVE            "ΠΡΟΟΠΤΙΚΗ" // 
#define LOCALIZED_ALTERNATE_PITCH                  "pitch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PIXEL                  "pixel" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PLAYWAVE               "ΑΝΑΠΑΡΑΓΩΓΗ" // 
#define LOCALIZED_ALTERNATE_PLIST                  "ΙΔΙΟΤΗΤΑ_ΛΙΣΤΑ" // 
#define LOCALIZED_ALTERNATE_PLISTS                 "ΙΔΙΟΤΗΤΑ_ΛΙΣΤΕΣ" // 
#define LOCALIZED_ALTERNATE_PO                     "po" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_POPDIR                 "ΚΑΤΑΛΟΓΟΣ_ΠΑΝΩ" // 
#define LOCALIZED_ALTERNATE_POLYSTART              "ΠΟΛΥΓΩΝΟ_ΑΡΧΗ" // 
#define LOCALIZED_ALTERNATE_POLYEND                "ΠΟΛΥΓΩΝΟ_ΤΕΛΟΣ" // 
#define LOCALIZED_ALTERNATE_POLYVIEW               "ΠΟΛΥΓΩΝΟ_ΠΡΟΒΟΛΗ" // 
#define LOCALIZED_ALTERNATE_PORTCLOSE              "ΘΥΡΑ_ΚΛΕΙΣΙΜΟ" // 
#define LOCALIZED_ALTERNATE_PORTFLUSH              "ΘΥΡΑ_ΚΑΘΑΡΙΣΜΟΣ" // 
#define LOCALIZED_ALTERNATE_PORTMODE               "ΘΥΡΑ_ΣΥΣΤΗΜΑ" // 
#define LOCALIZED_ALTERNATE_PORTOPEN               "ΘΥΡΑ_ΑΝΟΙΓΜΑ" // 
#define LOCALIZED_ALTERNATE_PORTREADARRAY          "ΘΥΡΑ_ΑΝΑΓΝΩΣΗ_ΠΙΝΑΚΑ" // 
#define LOCALIZED_ALTERNATE_PORTREADCHAR           "ΘΥΡΑ_ΑΝΑΓΝΩΣΗ_ΧΑΡΑΚΤΗΡΑ" // 
#define LOCALIZED_ALTERNATE_PORTWRITEARRAY         "ΘΥΡΑ_ΕΓΓΡΑΦΗ_ΠΙΝΑΚΑ" // 
#define LOCALIZED_ALTERNATE_PORTWRITECHAR          "ΘΥΡΑ_ΕΓΓΡΑΦΗ_ΧΑΡΑΚΤΗΡΑ" // 
#define LOCALIZED_ALTERNATE_POS                    "ΘΕΣΗ" // 
#define LOCALIZED_ALTERNATE_POSXYZ                 "ΘΕΣΗ_XYZ" // XYZ is Engilsh, copy XYZ in Greek
#define LOCALIZED_ALTERNATE_POT                    "pot" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_POWER                  "ΔΥΝΑΜΗ" // 
#define LOCALIZED_ALTERNATE_PPROP                  "ΙΔΙΟΤΗΤΑ_ΟΡΙΣΜΟΣ" // 
#define LOCALIZED_ALTERNATE_PPT                    "ppt" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PR                     "pr" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PRIMITIVEP             "primitivep" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PRIMITIVE_             "primitive?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PRINT                  "ΕΚΤΥΠΩΣΗ" // 
#define LOCALIZED_ALTERNATE_PROCEDUREP             "procedurep" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PROCEDURE_             "procedure?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PROPLISTP              "proplistp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PROPLIST_              "proplist?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PROCEDURES             "procedures" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PRODUCT                "ΓΙΝΟΜΕΝΟ" // 
#define LOCALIZED_ALTERNATE_PU                     "pu" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_PX                     "px" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_QUESTIONBOX            "ΜΗΝΥΜΑ_ΕΡΩΤΗΣΗ" // 
#define LOCALIZED_ALTERNATE_QUOTIENT               "ΔΙΑΙΡΕΣΗ" // 
#define LOCALIZED_ALTERNATE_RADARCCOS              "radarccos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADARCSIN              "radarcsin" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADARCTAN              "radarctan" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADCOS                 "radcos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADIOBUTTONCREATE      "ΠΛΑΙΣΙΟ_ΕΠΙΛΟΓΗΣ_ΔΗΜΙΟΥΡΓΙΑ" // 
#define LOCALIZED_ALTERNATE_RADIOBUTTONENABLE      "ΠΛΑΙΣΙΟ_ΕΠΙΛΟΓΗΣ_ΕΝΕΡΓΟΠΟΙΗΣΗ" // 
#define LOCALIZED_ALTERNATE_RADIOBUTTONDELETE      "ΠΛΑΙΣΙΟ_ΕΠΙΛΟΓΗΣ_ΔΙΑΓΡΑΦΗ" // 
#define LOCALIZED_ALTERNATE_RADIOBUTTONGET         "ΠΛΑΙΣΙΟ_ΕΠΙΛΟΓΗΣ_ΤΙΜΗ" // 
#define LOCALIZED_ALTERNATE_RADIOBUTTONSET         "ΠΛΑΙΣΙΟ_ΕΠΙΛΟΓΗΣ_ΟΡΙΣΜΟΣ" // 
#define LOCALIZED_ALTERNATE_RADSIN                 "radsin" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RADTAN                 "radtan" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RANDOM                 "random" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RAWASCII               "rawascii" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RC                     "rc" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RCS                    "rcs" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READCHAR               "ΑΝΑΓΝΩΣΗ_ΧΑΡΑΚΤΗΡΑ" // 
#define LOCALIZED_ALTERNATE_READCHARS              "ΑΝΑΓΝΩΣΗ_ΧΑΡΑΚΤΗΡΩΝ" // 
#define LOCALIZED_ALTERNATE_READER                 "ΑΝΑΓΝΩΣΗ_ΠΗΓΗ" // 
#define LOCALIZED_ALTERNATE_READLIST               "ΑΝΑΓΝΩΣΗ_ΛΙΣΤΑΣ" // 
#define LOCALIZED_ALTERNATE_READPOS                "ΑΝΑΓΝΩΣΗ_ΘΕΣΗ" // 
#define LOCALIZED_ALTERNATE_READRAWLINE            "readrawline" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_READWORD               "ΑΝΑΓΝΩΣΗ_ΛΕΞΗΣ" // 
#define LOCALIZED_ALTERNATE_REMAINDER              "ΥΠΟΛΟΙΠΟ" // 
#define LOCALIZED_ALTERNATE_REMPROP                "ΙΔΙΟΤΗΤΑ_ΑΦΑΙΡΕΣΗ" // 
#define LOCALIZED_ALTERNATE_REPCOUNT               "ΕΠΑΝΑΛΗΨΗ_ΑΡΙΘΜΟΣ" // 
#define LOCALIZED_ALTERNATE_REPEAT                 "ΕΠΑΝΑΛΗΨΗ" // 
#define LOCALIZED_ALTERNATE_RERANDOM               "rerandom" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RIGHT                  "right" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RIGHTROLL              "rightroll" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RL                     "rl" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RMDIR                  "ΚΑΤΑΛΟΓΟΣ_ΔΙΑΓΡΑΦΗ" // 
#define LOCALIZED_ALTERNATE_ROLL                   "roll" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ROUND                  "ΣΤΡΟΓΓΥΛΟΠΟΙΗΣΗ" // 
#define LOCALIZED_ALTERNATE_RR                     "rr" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RT                     "rt" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_RUN                    "ΕΚΤΕΛΕΣΗ" // 
#define LOCALIZED_ALTERNATE_RUNPARSE               "ΕΚΤΕΛΕΣΗ_ΕΠΕΞΕΡΓΑΣΙΑ" // 
#define LOCALIZED_ALTERNATE_RUNRESULT              "ΕΚΤΕΛΕΣΗ_ΑΠΟΤΕΛΕΣΜΑ" // 
#define LOCALIZED_ALTERNATE_RW                     "rw" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SAVE                   "ΑΠΟΘΗΚΕΥΣΗ" // 
#define LOCALIZED_ALTERNATE_SCREENCOLOR            "screencolor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCROLLBARCREATE        "scrollbarcreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCROLLBARENABLE        "scrollbarenable" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCROLLBARDELETE        "scrollbardelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCROLLBARGET           "scrollbarget" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCROLLBARSET           "scrollbarset" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCROLLX                "scrollx" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCROLLY                "scrolly" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SCRUNCH                "scrunch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SE                     "se" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SELECTBOX              "ΜΗΝΥΜΑ_ΕΠΙΛΟΓΗ" // 
#define LOCALIZED_ALTERNATE_SENTENCE               "ΠΡΟΤΑΣΗ" // 
#define LOCALIZED_ALTERNATE_SETACTIVEAREA          "ΕΝΕΡΓΗ_ΠΕΡΙΟΧΗ_ΟΡΙΣΜΟΣ" // 
#define LOCALIZED_ALTERNATE_SETBITINDEX            "setbitindex" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETBITMODE             "setbitmode" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETCLIP                "setclip" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETCURSOR              "setcursor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETCURSORNOWAIT        "setcursornowait" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETCURSORWAIT          "setcursorwait" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETFC                  "setfc" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETFLOODCOLOR          "setfloodcolor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETFOCUS               "setfocus" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETH                   "seth" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETHEADING             "setheading" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETITEM                "setitem" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETLABELFONT           "setlabelfont" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETLIGHT               "setlight" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETMARGINS             "setmargins" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPC                  "setpc" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPENCOLOR            "setpencolor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPENPATTERN          "setpenpattern" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPENSIZE             "setpensize" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPITCH               "setpitch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPIXEL               "setpixel" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPOS                 "setpos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETPOSXYZ              "setposxyz" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETREAD                "setread" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETREADPOS             "setreadpos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETROLL                "setroll" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETSC                  "setsc" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETSCREENCOLOR         "setscreencolor" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETSCRUNCH             "setscrunch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETTIMER               "settimer" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETTURTLE              "setturtle" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETTURTLEMODE          "setturtlemode" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETWRITE               "setwrite" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETWRITEPOS            "setwritepos" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETX                   "setx" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETXY                  "setxy" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETXYZ                 "setxyz" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETY                   "sety" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SETZ                   "setz" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SHELL                  "shell" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SHOW                   "ΕΜΦΑΝΙΣΗ" // 
#define LOCALIZED_ALTERNATE_SHOWNP                 "shownp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SHOWN_                 "shown?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SHOWTURTLE             "showturtle" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SIN                    "ΗΜΙΤΟΝΟ" // 
#define LOCALIZED_ALTERNATE_SOUND                  "ΗΧΟΣ" // 
#define LOCALIZED_ALTERNATE_SPLITSCREEN            "splitscreen" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SQRT                   "ΡΙΖΑ" // 
#define LOCALIZED_ALTERNATE_SS                     "ss" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ST                     "st" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STANDOUT               "standout" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STATICCREATE           "staticcreate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STATICDELETE           "staticdelete" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STATICUPDATE           "staticupdate" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STATUS                 "status" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STEP                   "ΒΗΜΑ" // 
#define LOCALIZED_ALTERNATE_STEPPED                "stepped" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_STOP                   "ΣΤΑΜΑΤΗΜΑ" // 
#define LOCALIZED_ALTERNATE_SUBSTRINGP             "substringp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SUBSTRING_             "substring?" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_SUM                    "ΑΘΡΟΙΣΜΑ" // 
#define LOCALIZED_ALTERNATE_TAG                    "tag" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TAN                    "tan" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TEST                   "ΔΟΚΙΜΗ" // 
#define LOCALIZED_ALTERNATE_TEXT                   "text" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TEXTSCREEN             "textscreen" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_THING                  "ΤΙΜΗ" // 
#define LOCALIZED_ALTERNATE_THROW                  "throw" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TIME                   "ΩΡΑ"
#define LOCALIZED_ALTERNATE_TIMEMILLI              "ΧΡΟΝΟΣ" // 
#define LOCALIZED_ALTERNATE_TO                     "to" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TONE                   "tone" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TOWARDS                "ΠΡΟΣ" // 
#define LOCALIZED_ALTERNATE_TOWARDSXYZ             "ΠΡΟΣ_XYZ" // 
#define LOCALIZED_ALTERNATE_TRACE                  "trace" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TRACED                 "traced" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TS                     "ts" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_TURTLE                 "ΧΕΛΩΝΑ" //
#define LOCALIZED_ALTERNATE_TURTLEMODE             "ΧΕΛΩΝΑ_ΣΥΣΤΗΜΑ" // 
#define LOCALIZED_ALTERNATE_TURTLES                "ΧΕΛΩΝΕΣ" // 
#define LOCALIZED_ALTERNATE_TYPE                   "type" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UNBURY                 "unbury" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UNSTEP                 "unstep" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UNTRACE                "untrace" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UP                     "up" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_UPPERCASE              "ΚΕΦΑΛΑΙΑ" // 
#define LOCALIZED_ALTERNATE_UPPITCH                "uppitch" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WAIT                   "ΑΝΑΜΟΝΗ" // 
#define LOCALIZED_ALTERNATE_WINDOW                 "ΠΑΡΑΘΥΡΟ" // 
#define LOCALIZED_ALTERNATE_WINDOWCREATE           "ΠΑΡΑΘΥΡΟ_ΔΗΜΙΟΥΡΓΙΑ" // 
#define LOCALIZED_ALTERNATE_WINDOWENABLE           "ΠΑΡΑΘΥΡΟ_ΕΝΕΡΓΟΠΟΙΗΣΗ" // 
#define LOCALIZED_ALTERNATE_WINDOWDELETE           "ΠΑΡΑΘΥΡΟ_ΔΙΑΓΡΑΦΗ" // 
#define LOCALIZED_ALTERNATE_WINDOWFILEEDIT         "windowfileedit" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WINDOWSET              "windowset" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WINHELP                "BOHUEIA" // 
#define LOCALIZED_ALTERNATE_WORD                   "ΛΕΞΗ" // 
#define LOCALIZED_ALTERNATE_WORDP                  "wordp" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WORD_                  "ΛΕΞΗ?" // 
#define LOCALIZED_ALTERNATE_WRAP                   "wrap" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_WRITEPOS               "ΕΓΓΡΑΦΗ_ΘΕΣΗ" // 
#define LOCALIZED_ALTERNATE_WRITER                 "ΕΓΓΡΑΦΗ_ΠΡΟΟΡΙΣΜΟΣ" // 
#define LOCALIZED_ALTERNATE_YESNOBOX               "ΜΗΝΥΜΑ_ΝΑΙ_ΟΧΙ" // 
#define LOCALIZED_ALTERNATE_YIELD                  "yield" // NOT_YET_LOCALIZED
#define LOCALIZED_ALTERNATE_ZOOM                   "ΜΕΓΕΘΥΝΣΗ" // 

//
// General localized strings
//
#define LOCALIZED_GENERAL_OKBUTTON      "OK"
#define LOCALIZED_GENERAL_CANCELBUTTON  "’κυρο"
#define LOCALIZED_GENERAL_APPLYBUTTON   "&Apply" // NOT_YET_LOCALIZED

#define LOCALIZED_GENERAL_PRODUCTNAME   "FMSLogo"

// Embedded description of fmslogo.exe
#define LOCALIZED_FMSLOGO_FILE_DESCRIPTION  "The FMSLogo programming environment" // NOT_YET_LOCALIZED

//
// The menu options on the main window 
//
#define LOCALIZED_FILE                  "&Αρχείο" // 
#define LOCALIZED_FILE_NEW              "&Νέο\t(διαγράφει εντολές και μεταβλητές)" // I'm sure "workspace" can have a better translation.
#define LOCALIZED_FILE_LOAD             "&Φόρτωση...\t(προσθέτει εντολές και μεταβλητές από αρχείο)" // 
#define LOCALIZED_FILE_OPEN             "’ν&οιγμα...\t(διαγράφει εντολές και μεταβλητές και ανοίγει ένα νέο αρχείο)" // 
#define LOCALIZED_FILE_SAVE             "&Αποθήκευση"  // 
#define LOCALIZED_FILE_SAVEAS           "Αποθήκευση &ως..." // 
#define LOCALIZED_FILE_SETASSCREENSAVER "Se&t As Screen Saver" // NOT_YET_LOCALIZED
#define LOCALIZED_FILE_EDIT             "&Επεξεργασία..." // 
#define LOCALIZED_FILE_ERASE            "&Σβήσιμο..." // 
#define LOCALIZED_FILE_EXIT             "Έ&ξοδος" // 

#define LOCALIZED_BITMAP               "Ει&κόνα" // 
#define LOCALIZED_BITMAP_NEW           "&Νέο" // 
#define LOCALIZED_BITMAP_LOAD          "’ν&οιγμα..." // 
#define LOCALIZED_BITMAP_SAVE          "&Αποθήκευση" // 
#define LOCALIZED_BITMAP_SAVEAS        "Αποθήκευση &ως..." // 
#define LOCALIZED_BITMAP_PRINT         "&Εκτύπωση..." // 
#define LOCALIZED_BITMAP_PRINTERSETUP  "Ε&πιλογές εκτύπωσης..." // 
#define LOCALIZED_BITMAP_ACTIVEAREA    "Ενε&ργή Περιοχή..." // 

#define LOCALIZED_SET                  "&Ρύθμιση" // 
#define LOCALIZED_SET_PENSIZE          "&Μέγεθος πένας..." // 
#define LOCALIZED_SET_LABELFONT        "Γραμματοσειρά &χελωνας..." // 
#define LOCALIZED_SET_COMMANDERFONT    "Γραμματοσειρά παραθύρου &ελέγχου (commander)..." // 
#define LOCALIZED_SET_PENCOLOR         "Χρώμα &πένας..." // 
#define LOCALIZED_SET_FLOODCOLOR       "Χρώμα &γεμίσματος..." // 
#define LOCALIZED_SET_SCREENCOLOR      "Χρώμα &οθόνης..." // 

#define LOCALIZED_ZOOM                 "&Ζουμ"  // 
#define LOCALIZED_ZOOM_IN              "&Μεγέθυνση" // 
#define LOCALIZED_ZOOM_OUT             "&Σμίκρυνση" // 
#define LOCALIZED_ZOOM_NORMAL          "&Κανονικό" // 

#define LOCALIZED_HELP                 "&Βοήθεια"  // 
#define LOCALIZED_HELP_INDEX           "&Θέματα στη βοήθεια" // 
#define LOCALIZED_HELP_TUTORIAL        "&Μάθημα" // 
#define LOCALIZED_HELP_DEMO            "&Επίδειξη"  // 
#define LOCALIZED_HELP_EXAMPLE         "&Παραδείγματα" // 
#define LOCALIZED_HELP_RELEASENOTES    "&Σημειώσεις έκδοσης" // 
#define LOCALIZED_HELP_ABOUTFMSLOGO    "&Πληροφορίες για την " LOCALIZED_GENERAL_PRODUCTNAME "..." 
#define LOCALIZED_HELP_MS              "&Πληροφορίες για την MS..." // 
// The following two help options display tables for translating to/from English
// These tables are built from the LOCALIZED_ALTERNATE_* macros above and the
// and startup-xxxx.logoscript file.
#define LOCALIZED_HELP_LANGTOENGLISH   "LANGUAGE to English" // NOT_YET_LOCALIZED
#define LOCALIZED_HELP_ENGLISHTOLANG   "English to LANGUAGE" // NOT_YET_LOCALIZED

// The "Set Active Area" dialog box
#define LOCALIZED_SELECTACTIVEAREA              "Επιλογή ενεργής περιοχής" // 
#define LOCALIZED_SELECTACTIVEAREA_EFFECT       "Αυτές οι επιλογές επηρεάζουν την εκτύπωση και αποθήκευση εικόνων" // 
#define LOCALIZED_SELECTACTIVEAREA_YHIGH        "Πάνω όριο" // 
#define LOCALIZED_SELECTACTIVEAREA_YLOW         "Κάτω όριο"  // 
#define LOCALIZED_SELECTACTIVEAREA_XHIGH        "Δεξί όριο" // 
#define LOCALIZED_SELECTACTIVEAREA_XLOW         "Αριστερό όριο" // 
#define LOCALIZED_SELECTACTIVEAREA_STEPSPERINCH "Βήματα χελώνας ανά ίντσα:" // 
#define LOCALIZED_SELECTACTIVEAREA_RESET        "&Επαναφορά"  // 
#define LOCALIZED_SELECTACTIVEAREA_OK           LOCALIZED_GENERAL_OKBUTTON // Localized above
#define LOCALIZED_SELECTACTIVEAREA_CANCEL       LOCALIZED_GENERAL_CANCELBUTTON // 

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
#define LOCALIZED_POPUP_COPY                     "Αντι&γραφή" // 
#define LOCALIZED_POPUP_CUT                      "Απ&οκοπή" // 
#define LOCALIZED_POPUP_PASTE                    "&Επικόλληση" // 
#define LOCALIZED_POPUP_DELETE                   "&Διαγραφή" // 
#define LOCALIZED_POPUP_UNDO                     "Α&ναίρεση" // 
#define LOCALIZED_POPUP_REDO                     "Ακύρωση αναίρεσης" // 
#define LOCALIZED_POPUP_SELECTALL                "Ε&πιλογή όλων" // 
#define LOCALIZED_POPUP_HELP                     "Ανα&ζήτηση στη βοήθεια" // 
#define LOCALIZED_POPUP_REMOVELINES              "Remove Selected Lines" // NOT_YET_LOCALIZED

//
// The menu options on the editor
//
#define LOCALIZED_EDITOR_TITLE                   "Επεξεργαστής" // 

#define LOCALIZED_EDITOR_FILE                    "&Αρχείο" // 
#define LOCALIZED_EDITOR_FILE_SAVEANDEXIT        "Αποθήκευση και έ&ξοδος\tCtrl+D" // 
#define LOCALIZED_EDITOR_FILE_SAVETOWORKSPACE    "Απο&θήκευση" // 
#define LOCALIZED_EDITOR_FILE_PRINT              "&Εκτύπωση..."  // 
#define LOCALIZED_EDITOR_FILE_EXIT               "Έ&ξοδος"  // 

#define LOCALIZED_EDITOR_EDIT                    "&Επεξεργασία" // 
#define LOCALIZED_EDITOR_EDIT_UNDO               "Αναίρεσ&η\tCtrl+Z" // 
#define LOCALIZED_EDITOR_EDIT_REDO               "Ακύρωση αναίρεσης\tCtrl+Y" // 
#define LOCALIZED_EDITOR_EDIT_CUT                "Απ&οκοπή\tCtrl+X" // 
#define LOCALIZED_EDITOR_EDIT_COPY               "Αντι&γραφή\tCtrl+C" // 
#define LOCALIZED_EDITOR_EDIT_PASTE              "&Επικόλληση\tCtrl+V" // 
#define LOCALIZED_EDITOR_EDIT_DELETE             "&Διαγραφή\tDel" // 
#define LOCALIZED_EDITOR_EDIT_CLEARALL           "Κα&θαρισμός όλων\tCtrl+Del" // 
#define LOCALIZED_EDITOR_EDIT_SELECTALL          "Ε&πιλογή όλων\tCtrl+A" // 

#define LOCALIZED_EDITOR_SEARCH                  "Ανα&ζήτηση" // 
#define LOCALIZED_EDITOR_SEARCH_FIND             "Εύ&ρεση...\tCtrl+F" // 
#define LOCALIZED_EDITOR_SEARCH_REPLACE          "Αντι&κατάσταση...\tCtrl+H"  // 
#define LOCALIZED_EDITOR_SEARCH_NEXT             "Ε&πόμενο\tF3"  // 

#define LOCALIZED_EDITOR_SET                     "&Ρυθμίση"  // 
#define LOCALIZED_EDITOR_SET_FONT                "&Γραμματοσειρά..."  // 

#define LOCALIZED_EDITOR_TEST                    "Δοκιμή"
#define LOCALIZED_EDITOR_TEST_RUN_SELECTION      "&Run Selection\tCtrl+R" // NOT_YET_LOCALIZED

#define LOCALIZED_EDITOR_HELP                    "&Βοήθεια"  // 
#define LOCALIZED_EDITOR_HELP_INDEX              "&Θέματα στη βοήθεια" // 
#define LOCALIZED_EDITOR_HELP_EDITOR             "Επε&ξεργαστής" // 
#define LOCALIZED_EDITOR_HELP_TOPICSEARCH        "Ανα&ζήτηση θέματος\tF1" // 


//
// The strings in the "You have unsaved changes" dialog
//
#define LOCALIZED_UNSAVEDCHANGES                LOCALIZED_YOUHAVEUNSAVEDCHANGES //
#define LOCALIZED_UNSAVEDCHANGES_SAVEANDEXIT    "Απο&θήκευση και έξοδος" // 
#define LOCALIZED_UNSAVEDCHANGES_DONTSAVE       "Χωρίς αποθήκευση" // 
#define LOCALIZED_UNSAVEDCHANGES_CANCEL         LOCALIZED_GENERAL_CANCELBUTTON // 
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE1       "Υπάρχουν αλλαγές που δεν έχουν αποθηκευθεί.  Αν δεν τις αποθηκεύσετε, αυτές οι αλλαγές θα χαθούν.  " // 
#define LOCALIZED_UNSAVEDCHANGES_MESSAGE2       "Θέλετε να αποθηκεύσετε τις αλλαγές σας πριν την έξοδο;"  // 


//
// Strings on the Commander window
//
#define LOCALIZED_COMMANDER                     "Παράθυρο ελέγχου" // 
#define LOCALIZED_COMMANDER_HALT                "Σταμάτημα" // 
#define LOCALIZED_COMMANDER_TRACE               "Ανίχνευση" // 
#define LOCALIZED_COMMANDER_NOTRACE             "Χωρίς" // 
#define LOCALIZED_COMMANDER_PAUSE               "Παύση" // 
#define LOCALIZED_COMMANDER_STATUS              "Κατάσταση" // 
#define LOCALIZED_COMMANDER_NOSTATUS            "Χωρίς" // 
#define LOCALIZED_COMMANDER_STEP                "Βήμα" // 
#define LOCALIZED_COMMANDER_UNSTEP              "Χωρίς" // 
#define LOCALIZED_COMMANDER_RESET               "Επαναφορά" // 
#define LOCALIZED_COMMANDER_EXECUTE             "Εκτέλεση" // 
#define LOCALIZED_COMMANDER_EDALL               "Επεξεργασία" // If that's too long, please replace it again with EDALL

//
// Strings on the Status window
//
#define LOCALIZED_STATUS                        "Κατάσταση" // 
#define LOCALIZED_STATUS_PEN                    "Πένα" // 
#define LOCALIZED_STATUS_CONTACT                "Επαφή:" // 
#define LOCALIZED_STATUS_WIDTH                  "Πλάτος:" // 
#define LOCALIZED_STATUS_STYLE                  "Στυλ:" // 
#define LOCALIZED_STATUS_ORIENTATION            "Προσανατολισμός" // 
#define LOCALIZED_STATUS_PITCH                  "Κλίση:" // 
#define LOCALIZED_STATUS_HEADING                "Κατεύθυνση:" // 
#define LOCALIZED_STATUS_ROLL                   "Στροφή:" // 
#define LOCALIZED_STATUS_TURTLE                 "Χελώνα" // 
#define LOCALIZED_STATUS_POSITION               "Θέση (XYZ):" //
#define LOCALIZED_STATUS_WHICH                  "Χελώνα:" // 
#define LOCALIZED_STATUS_VISIBILITY             "Ορατότητα:" // 
#define LOCALIZED_STATUS_COLOR                  "Χρώμα" // 
#define LOCALIZED_STATUS_PENCOLOR               "Πένα (ΚΠΓ/RGB):" //
#define LOCALIZED_STATUS_FLOODCOLOR             "Γέμισμα (ΚΠΓ/RGB):" // 
#define LOCALIZED_STATUS_SCREENCOLOR            "Οθόνη (ΚΠΓ/RGB):" // 
#define LOCALIZED_STATUS_KERNEL                 "Πυρήνας" // 
#define LOCALIZED_STATUS_CALLS                  "Κλήσεις:" // 
#define LOCALIZED_STATUS_PEAKMEMORY             "Μνήμη:" // 

#define LOCALIZED_STATUS_PENREVERSE     "Αντίστροφο" // 
#define LOCALIZED_STATUS_PENNORMAL      "Κανονικό" // 
#define LOCALIZED_STATUS_PENERASE       "Σβήσιμο" // 
#define LOCALIZED_STATUS_PENUP          "Πάνω" // 
#define LOCALIZED_STATUS_PENDOWN        "Κάτω" // 
#define LOCALIZED_STATUS_PENSHOWN       "Ορατή" //  
#define LOCALIZED_STATUS_PENHIDDEN      "Αόρατη" // 
#define LOCALIZED_STATUS_POLYGONS       "Πολύγωνα" // 
#define LOCALIZED_STATUS_VECTORS        "Διανύσματα" // 
#define LOCALIZED_STATUS_NODES          "Κόμβοι" // 
#define LOCALIZED_STATUS_NOT_APPLICABLE "N/A" // NOT_YET_LOCALIZED

//
// Strings on the Erase|Edit Procedure dialog box
//
#define LOCALIZED_SELECTPROCEDURE_OK            LOCALIZED_GENERAL_OKBUTTON
#define LOCALIZED_SELECTPROCEDURE_CANCEL        LOCALIZED_GENERAL_CANCELBUTTON
#define LOCALIZED_SELECTPROCEDURE_ALL           "&Όλες"
#define LOCALIZED_ERASEPROCEDURE                "Σβήσιμο εντολής"
#define LOCALIZED_EDITPROCEDURE                 "Επεξεργασία εντολής"


//
// Strings on the Color Picker Dialog box
//
#define LOCALIZED_SETCOLOR                     "Ρύθμιση χρώματος" // 
#define LOCALIZED_SETCOLOR_PENCOLOR            "Χρώμα πένας" // 
#define LOCALIZED_SETCOLOR_FLOODCOLOR          "Χρώμα γεμίσματος" // 
#define LOCALIZED_SETCOLOR_SCREENCOLOR         "Χρώμα οθόνης" // 
#define LOCALIZED_SETCOLOR_RED                 "Κόκκινο" // 
#define LOCALIZED_SETCOLOR_GREEN               "Πράσινο" // 
#define LOCALIZED_SETCOLOR_BLUE                "Γαλάζιο" // 
#define LOCALIZED_SETCOLOR_OK                  LOCALIZED_GENERAL_OKBUTTON // 
#define LOCALIZED_SETCOLOR_CANCEL              LOCALIZED_GENERAL_CANCELBUTTON // 
#define LOCALIZED_SETCOLOR_APPLY               LOCALIZED_GENERAL_APPLYBUTTON // NOT_YET_LOCALIZED

//
// Strings on the Pen Size Picker Dialog box
//
#define LOCALIZED_SETPENSIZE                   "Μέγεθος πένας" // 
#define LOCALIZED_SETPENSIZE_SIZE              "Μέγεθος" // 
#define LOCALIZED_SETPENSIZE_OK                LOCALIZED_GENERAL_OKBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SETPENSIZE_CANCEL            LOCALIZED_GENERAL_CANCELBUTTON // NOT_YET_LOCALIZED
#define LOCALIZED_SETPENSIZE_APPLY             LOCALIZED_GENERAL_APPLYBUTTON // NOT_YET_LOCALIZED


//
// Strings on the "About FMSLogo" Dialog box
//
#define LOCALIZED_ABOUTFMS                     "Πληροφορίες για την " LOCALIZED_GENERAL_PRODUCTNAME 
#define LOCALIZED_ABOUTFMS_VERSION             "έκδοση"
#define LOCALIZED_ABOUTFMS_GUI                 "GUI από τον George Mills\nSoftronics, Inc.\nhttp://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_CORE                "Πυρήνας από τον Brian Harvey\nUniversity of California Berkeley"
#define LOCALIZED_ABOUTFMS_INSTALLER           "Εγκαταστάτης βασισμένος στο Nullsoft Scriptable Install System\nhttp://nsis.sourceforge.net"
#define LOCALIZED_ABOUTFMS_ADVENTURE           "The Great Logo Adventure (ISBN 0-9651934-6-2)\nΓράφτηκε και δωρίστηκε από τον Jim Muller\nΔιαθέσιμο στο http://www.softronix.com/"
#define LOCALIZED_ABOUTFMS_SPECIALTHANKS       "Ευχαριστούμε τους Yehuda Katz και Erich Neuwirth"
#define LOCALIZED_ABOUTFMS_GPL                 "Η " LOCALIZED_GENERAL_PRODUCTNAME " είναι ελεύθερο λογισμικό\nΔείτε τη GNU Public License"
#define LOCALIZED_ABOUTFMS_NEWSGROUP           "News Group στο Διαδίκτυο: comp.lang.logo\nΕπισκεφθείτε το Logo-Forum στο\nhttp://groups.yahoo.com/group/LogoForum/"
#define LOCALIZED_ABOUTFMS_MULTIMEDIALOGIC     "Μετάφραση στα Ελληνικά:\nΘοδωρής Χατζηγιαννάκης (teo64x@yahoo.gr)"
#define LOCALIZED_ABOUTFMS_OK                  LOCALIZED_GENERAL_OKBUTTON


//
// Strings on the "About FMS" Dialog box
//
#define LOCALIZED_ABOUTMS                      "Πληροφορίες για το FMS" // 
#define LOCALIZED_ABOUTMS_FMS                  "FMS σημαίνει Fight Multiple Sclerosis." //
#define LOCALIZED_ABOUTMS_CONSIDERDONATING     "Please consider donating to the\nNational Multiple Sclerosis Society.\nhttp://www.nmss.org\n1-800-FIGHT-MS" // NOT_YET_LOCALIZED
#define LOCALIZED_ABOUTMS_OK                   LOCALIZED_GENERAL_OKBUTTON // 


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

#define LOCALIZED_CHANGESINEDITORMAYBELOST  "Αλλαγές σε αυτή την περίοδο λειτουργίας ίσως χαθούν.\n\nΘέλετε πραγματικά να κλείσετε την " LOCALIZED_GENERAL_PRODUCTNAME ";" //
#define LOCALIZED_EDITSESSIONISRUNNING      "Ο επεξεργαστής κώδικα είναι ήδη ανοιχτός" // 

#define LOCALIZED_COULDNOTWRITEBMP            "Αδύνατη η εγγραφή στο .bmp" // 
#define LOCALIZED_COULDNOTOPENBMP             "Αδύνατη η ανάγνωση από το .bmp" // 
#define LOCALIZED_COULDNOTCREATEBMP           "Αδύνατο να δημιουργηθεί η εικόνα Windows 3.0 bitmap" // 
#define LOCALIZED_NOTVALIDBMP                 "Η εικόν δεν είναι Windows 3.0 bitmap" // 

#define LOCALIZED_YOUHAVEUNSAVEDCHANGES         "Δεν αποθηκεύσατε στο δίσκο" // 
#define LOCALIZED_FILENEWWILLERASEWORKSPACE     "Η εκτέλεση ενός νέου αρχείου θα σβήσει τις υπάρχουσες εντολές και μεταβλητές.\n\nΣυνέχεια;" // 
#define LOCALIZED_FILELOADMAYOVERWRITEWORKSPACE "Το αρχείο που φορτώνεται θα προστεθεί στις υπάρχουσες εντολές και μεταβλητές\nκαι ίσως σβήσει όποιες αλλαγές δεν έχετε αποθηκεύσει.\n\nΣυνέχεια;" // 
#define LOCALIZED_FILEOPENWILLERASEWORKSPACE    "Αυτό θα σβήσει όλες τις αλλαγές που δεν έχετε αποθηκεύσει.\n\nΣυνέχεια;" // 

#define LOCALIZED_EDITORISOPEN                  "Ξέρετε ότι ήδη έχετε μια περίοδο επεξεργασίας ανοιχτή;\n\nΟποιαδήποτε αλλαγή σε αυτή την περίοδο δε θα αποθηκευθεί." // 

#define LOCALIZED_ERROR_CANTREADFILE            "Αδυναμία ανάγνωσης του αρχείου \"%s\" από το δίσκο" // 
#define LOCALIZED_ERROR_CANTWRITEFILE           "Αδυναμία εγγραφής του αρχείου \"%s\" στο δίσκο" // 

#define LOCALIZED_SAVETOWORKSPACE                "Αποθήκευση" // 
#define LOCALIZED_CONTENTSCHANGED                "Τα περιεχόμενα άλλαξαν" // 
#define LOCALIZED_SAVECHANGEDCONTENTSTOWORKSPACE "Τα περιεχόμενα έχουν αλλάξει.\nΘέλετε να τα αποθηκεύσετε;" // 



#define LOCALIZED_CURSORISATLASTGOODDEFINITION  "Ο δείκτης θα τοποθετηθεί μετά τον τελευταίο επιτυχημένο ορισμό.\nΕλέγξτε το παράθυρο ελέγχου για πιθανό μήνυμα λάθους." // 
#define LOCALIZED_RETURNTOEDIT                  "Επιστροφή στην επεξεργασία;" // 

#define LOCALIZED_EDITFAILEDTOLOAD              "Η επεξεργασία σας ΑΠΕΤΥΧΕ να φορτωθεί" // Isn't the use of capitals like shouting to the programmer for making a mistake? ;P

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
#define LOCALIZED_FILEFILTER_ALLFILES "Όλα τα αρχεία (*.*)|*.*"
#define LOCALIZED_FILEFILTER_LOGO     "Αρχεία Logo (*.lgo)|*.lgo|" LOCALIZED_FILEFILTER_ALLFILES
#define LOCALIZED_FILEFILTER_IMAGE    "Αρχεία εικόνας Bitmap (*.bmp)|*.bmp|Αρχεία εικόνας GIF (*.gif)|*.gif|" LOCALIZED_FILEFILTER_ALLFILES



//
// strings seen when tracing is enabled
//
#define LOCALIZED_TRACING_STOPS             " σταματάει\n"
#define LOCALIZED_TRACING_OUTPUTS           " επιστρέφει %s\n"
#define LOCALIZED_TRACING_MAKE              "Μεταβλητή %s %s"
#define LOCALIZED_TRACING_PPROP             "Ιδιότητα %s %s %s"
#define LOCALIZED_TRACING_LOCATION          " στο %s\n%s"

//
// strings seen when single-stepping execution
//
#define LOCALIZED_STEPPING                  "Βήμα-βήμα"

//
// Notification when defining a procedure with TO in the commander
//
#define LOCALIZED_PROCEDUREDEFINED  "%s ορίστηκε\n" // 


//
// Words that represent the pen's mode
//
#define LOCALIZED_PENMODE_ERASE    "σβήσιμο" // 
#define LOCALIZED_PENMODE_REVERSE  "αντίστροφο" // 
#define LOCALIZED_PENMODE_PAINT    "σχεδιασμός" // 

//
// Error message thrown by Logo
//
#define LOCALIZED_ERROR_FATALINTERNAL          "Logo: Εσωτερικό σφάλμα" // 
#define LOCALIZED_ERROR_OUTOFMEMORYUNREC       "Logo: Ανεπάρκεια μνήμης" // 
#define LOCALIZED_ERROR_OUTOFMEMORY            "Ανεπάρκεια μνήμης" // 
#define LOCALIZED_ERROR_STACKOVERFLOW          "υπερχείλιση στοίβας" // 
#define LOCALIZED_ERROR_TURTLEOUTOFBOUNDS      "χελώνα εκτός ορίων" // 
#define LOCALIZED_ERROR_BADGRAPHINIT           "αδυναμία εκκίνησης γραφικών" // 
#define LOCALIZED_ERROR_BADDATA                "Στο %p δεν αρέσει το %s ως παράμετρος" // 
#define LOCALIZED_ERROR_DIDNTOUTPUT            "Το %p δεν επέστρεψε τιμή για το %p" // 
#define LOCALIZED_ERROR_NOTENOUGHINPUTS        "ανεπάρκεια παραμέτρων για το %p" // 
#define LOCALIZED_ERROR_TOOMUCH                "υπερβολικά μεγάλη παράσταση ανάμεσα στα ()" // 
#define LOCALIZED_ERROR_DONTSAYWHATTODOWITH    "Δεν είπες τί να κάνω με το %s" // 
#define LOCALIZED_ERROR_PARENMISMATCH          "Υπερβολικά πολλά ('s" // 
#define LOCALIZED_ERROR_NOVALUE                "Το %s δεν έχει τιμή" // 
#define LOCALIZED_ERROR_UNEXPECTEDPAREN        "μη προβλεπόμενο ')'" // 
#define LOCALIZED_ERROR_UNEXPECTEDBRACKET      "μη προβλεπόμενο ']'" // 
#define LOCALIZED_ERROR_UNEXPECTEDBRACE        "μη προβλεπόμενο '}'" // 
#define LOCALIZED_ERROR_DONTKNOWHOWTO          "Δεν ξέρω το %p" // 
#define LOCALIZED_ERROR_NOCATCHTAG             "Δε μπορώ να βρω ετικέτα συνέχειας για το %p" // 
#define LOCALIZED_ERROR_ALREADYDEFINED         "Το %p έχει ήδη οριστεί" // 
#define LOCALIZED_ERROR_STOPPING               "Σταμάτημα..." // 
#define LOCALIZED_ERROR_ALREADYDRIBBLING       "Γίνεται ήδη καταγραφή" // 
#define LOCALIZED_ERROR_FILESYSTEM                   "Σφάλμα συστήματος αρχείων: %p" // 
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN          "Αδυναμία ανοίγματος" // 
#define LOCALIZED_ERROR_FILESYSTEM_CANTOPEN2         "Αδυναμία ανοίγματος του %t" // 
#define LOCALIZED_ERROR_FILESYSTEM_ALREADYOPEN       "Το αρχείο είναι ήδη ανοιχτό" // 
#define LOCALIZED_ERROR_FILESYSTEM_NOTOPEN           "Το αρχείο δεν είναι ανοιχτό" // 
#define LOCALIZED_ERROR_FILESYSTEM_CANTCREATEEDITOR  "Αδυναμία δημιουργία του αρχείου επεξεργαστή κώδικα"// 
#define LOCALIZED_ERROR_FILESYSTEM_CANTSTARTEDITOR   "Αδυναμία ανοίγματος του επεξεργαστή κώδικα"  // 
#define LOCALIZED_ERROR_FILESYSTEM_CANTREADEDITOR    "Αδυναμία ανάγνωσης του αρχείου επεξεργαστή κώδικα"  // 
#define LOCALIZED_ERROR_IFWARNING              "Θεωρώ ότι εννοούσες IFELSE, όχι IF" // This should change a little when primitives are localized
#define LOCALIZED_ERROR_SHADOWWARNING          "Το %p υποσκιάζεται από τοπικό στην κλήση της εντολής" // I could make it a little more accurate if I knew whether it refers to a variable or something else
#define LOCALIZED_ERROR_USER                   "Throw \"Error" // 
#define LOCALIZED_ERROR_ISPRIMITIVE            "Το %p είναι στοιχειώδης εντολή" // 
#define LOCALIZED_ERROR_TONOTINSIDE            "Αδύνατη η χρήση του TO μέσα σε εντολή" // But why? :D
#define LOCALIZED_ERROR_ATTOPLEVEL             "Το %p χρησιμοποιείται μόνο μέσα σε εντολές" // 
#define LOCALIZED_ERROR_ATTOPLEVEL2            "Μπορείτε να χρησιμοποιήσετε OUTPUT ή STOP μόνο μέσα σε εντολή" // 
#define LOCALIZED_ERROR_NOTEST                 "%p χωρίς TEST" // 
#define LOCALIZED_ERROR_BADMACROOUTPUT         "Η μακροεντολή επέστρεψε %s αντί για λίστα" // 
#define LOCALIZED_ERROR_DEEPEND                "Το END βρίσκεται μέσα σε οδηγία πολλαπλών γραμμών" // 
#define LOCALIZED_ERROR_DEEPENDIN              "Το END βρίσκεται μέσα σε οδηγία πολλαπλών γραμμών στο %p" // 
#define LOCALIZED_ERROR_UNKNOWN                "’γνωστη κατάσταση σφάλματος - εσωτερικό σφάλμα." // 
#define LOCALIZED_PAUSING                      "Παύση..." // 


// FMSLogo-specific error messages.
#define LOCALIZED_ERROR_INVALIDSTATEFORINSTRUCTION "Invalid state for instruction: %p" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_MODE_ON_SPRITE             "cannot set the mode of a turtle with a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPSPECIALTUTRLE        "cannot make a special turtle use a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_BITMAPCLIPBOARD            "cannot use the clipboard as a rotating bitmap" // NOT_YET_LOCALIZED
#define LOCALIZED_ERROR_SPECIALFORM                "%p doesn't like %p as input because it has a special form" // NOT_YET_LOCALIZED

//
// Error messages displayed in Message Boxes.
//
#define LOCALIZED_ERROR                      "Σφάλμα" // 
#define LOCALIZED_ERROR_BADINPUT             "Κακή παράμετρος" // 
#define LOCALIZED_ERROR_BADINPUTNOTPAIRED    "Η παράμετρος δεν ταιριάζει" // 

#define LOCALIZED_ERROR_CANTOPENPORT         "Αδύνατο το άνοιγμα της θύρας" // 
#define LOCALIZED_ERROR_CANTCLOSEPORT        "Αδύνατο το κλείσιμο της θύρας" // 
#define LOCALIZED_ERROR_CANTFLUSHPORT        "Αδύνατο το άδειασμα της θύρας" // 
#define LOCALIZED_ERROR_CANTDCBONPORT        "Αδύνατη η δημιουργία dcb στη θύρα" // 
#define LOCALIZED_ERROR_CANTSETPORT          "Αδύνατη η ρύθμιση της θύρας" // 
#define LOCALIZED_ERROR_PORTALREADYOPEN      "Η θύρα είναι ήδη ανοιχτή" // 
#define LOCALIZED_ERROR_PORTNOTOPEN          "Η θύρα δεν είναι ανοιχτή" // 

#define LOCALIZED_ERROR_WINDOWALREADYEXISTS   "Υπάρχει ήδη: %s"
#define LOCALIZED_ERROR_WINDOWDOESNOTEXIST    "Δεν υπάρχει: %s"

#define LOCALIZED_ERROR_DLLNOTLOADED          "Το DLL δεν έχει φορτωθεί" // 
#define LOCALIZED_ERROR_DLLLOADFAILED         "Η φόρτωση του DLL απέτυχε" // 
#define LOCALIZED_ERROR_DLLINVALIDDATATYPE    "’κυρος τύπος δεδομένων" // 
#define LOCALIZED_ERROR_DLLINVALIDOUTPUTTYPE  "’κυρος τύπος επιστροφής" // 
#define LOCALIZED_ERROR_DLLFUNCTIONNOTFOUND   "Η συνάρτηση δε βρέθηκε" // 
#define LOCALIZED_ERROR_DLLTYPEDATANOTPAIRED  "Δεν ταιριάζουιν όλες οι παράμετροι Τύπου/Δεδομένων" // 

#define LOCALIZED_ERROR_NETWORK               "Σφάλμα δικτύου" // 
#define LOCALIZED_ERROR_NETWORKRECEIVE        "Σφάλμα αποδοχής από το δίκτυο" // 
#define LOCALIZED_ERROR_NETWORKSEND           "Σφάλμα αποστολής στο δίκτυο" // 
#define LOCALIZED_ERROR_NETWORKSHUTDOWN       "Μη προβλεπόμενο σφάλμα, ίσως το δίκτυο να έκλεισε" // 
#define LOCALIZED_ERROR_NETWORKNOTSTARTED     "Δεν άρχισε" // 
#define LOCALIZED_ERROR_NETWORKALREADYSTARTED "Έχει ήδη αρχίσει" // 
#define LOCALIZED_ERROR_NETWORKALREADYON      "Ήδη ανοιχτό" // 
#define LOCALIZED_ERROR_NETWORKALREADYOFF     "Ήδη κλειστό" // 

// The rest of the network errors shouldn't really be seen -- may be okay not to localize
#define LOCALIZED_ERROR_NETWORKNAMETOOLONG         "Πολύ μεγάλο όνομα" // 
#define LOCALIZED_ERROR_NETWORKNOTINITIALIZED      "Δεν άρχισε" // 
#define LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY      "Το σύστημα δεν είναι έτοιμο" // 
#define LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED "Η έκδοση δεν υποστηρίζεται" // 
#define LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN   "Αδύνατη η αποστολή μετά το κλείσιμο της υποδοχής" // 
#define LOCALIZED_ERROR_NETWORKINTERRUPTED         "Η κλήση συστήματος διακόπηκε" // 
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH    "Επίσημη απάντηση: δε βρέθηκε ο κεντρικός υπολογιστής" // 
#define LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH "Ανεπίσημη: δε βρέθηκε ο κεντρικός υπολογιστής. Δείτε το NETSTARTUP" // 
#define LOCALIZED_ERROR_NETWORKNOTRECOVERABLE      "Μη ανανήψιμο σφάλμα" // 
#define LOCALIZED_ERROR_NETWORKNODATA              "Δεν υπάρχει εγγραφή δεδομένων" // 
#define LOCALIZED_ERROR_NETWORKBADFILENUMBER       "Λάθος αριθμός αρχείου" // 
#define LOCALIZED_ERROR_NETWORKWOULDBLOCK          "Η διαδικασία θα εμπόδιζε" // 
#define LOCALIZED_ERROR_NETWORKNOWINPROGRESS       "Η διαδικασία εκτελείται τώρα" // 
#define LOCALIZED_ERROR_NETWORKALREADYINPROGRESS   "Η διαδικασία εκτελείται ήδη" // 
#define LOCALIZED_ERROR_NETWORKBADADDRESS          "Κακή διεύθυνση" // 
#define LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS     "Χρειάζεται διεύθυνση προορισμού" // 
#define LOCALIZED_ERROR_NETWORKMESSAGETOOLONG      "Το μήνυμα είναι πολύ μεγάλο" // 
#define LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED      "Η οικογένεια πρωτοκόλλου δεν υποστηρίζεται" // 
#define LOCALIZED_ERROR_NETWORKDIRNOTEMPTY         "Ο κατάλογος δεν είναι άδειος" // 
#define LOCALIZED_ERROR_NETWORKAPPLIMITREACHED     "Όριο εφαρμογών" // 
#define LOCALIZED_ERROR_NETWORKDISKQUOTA           "Η αναλογία δίσκου ξεπεράστηκε" // 
#define LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS    LOCALIZED_ERROR_BADINPUT // 
#define LOCALIZED_ERROR_NETWORKTOOMANYFILES        "Πολλά ανοιχτά αρχεία" // 
#define LOCALIZED_ERROR_NETWORKACCESSDENIED        "Η πρόσβαση απαγορεύτηκε" // 
#define LOCALIZED_ERROR_NETWORKNOTASOCKET          "Διαδικασία υποδοχής σε μη υποδοχή" // 
#define LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE    "Αδύνατη η εκχώρηση των ζητούμενων διευθύνσεων" // 
#define LOCALIZED_ERROR_NETWORKADDRINUSE           "Η διεύθυνση χρησιμοποιείται ήδη" // 
#define LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED      "Η οικογένεια διευθύνσεων δεν υποστηρίζεται από την οικογένεια πρωτοκόλλου" // 
#define LOCALIZED_ERROR_NETWORKTIMEDOUT            "Ο χρόνος σύνδεσης έληξε" // 
#define LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED    "Ο τύπος υποδοχής δεν υποστηρίζεται" // 
#define LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED   "Ο τύπος πρωτοκόλλου δεν υποστηρίζεται" // 
#define LOCALIZED_ERROR_NETWORKNOBUFFER            "Δεν υπάρχει χώρος στην προσωρινή μνήμη (buffer)" // 
#define LOCALIZED_ERROR_NETWORKALREADYCONNECTED    "Η υποδοχή είναι ήδη συνδεδεμένη" // 
#define LOCALIZED_ERROR_NETWORKNOTCONNECTED        "Η υποδοχή δεν είναι συνδεδεμένη" // 
#define LOCALIZED_ERROR_NETWORKBADPROTOOPT         "Κακή επιλογή στο πρωτόκολλο" // 
#define LOCALIZED_ERROR_NETWORKCONNECTIONRESET     "Η σύνδεση επανήλθε" // 
#define LOCALIZED_ERROR_NETWORKCONNECTIONABORT     "Το λογισμικό προκάλεσε κλείσιμο της σύνδεσης" // 
#define LOCALIZED_ERROR_NETWORKISDOWN              "Το δίκτυο δε λειτουργεί" // 
#define LOCALIZED_ERROR_NETWORKRESET               "Το δίκτυο επανήλθε" // 
#define LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED   "Η σύνδεση δεν έγινε δεκτή" // 
#define LOCALIZED_ERROR_NETWORKHOSTISDOWN          "Ο κεντρικός υπολογιστής δε λειτουργεί" // 
#define LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE   "Αδύνατη η επαφή με τον κεντρικό υπολογιστή" // 
#define LOCALIZED_ERROR_NETWORKBADPROTOTYPE        "Το πρωτόκολλο είναι λάθος τύπου για την υποδοχή" // 
#define LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED   "Η διαδικασία δεν υποστηρίζεται στην υποδοχή" // 
#define LOCALIZED_ERROR_NETWORKUNREACHABLE         "Δε βρέθηκε διαδρομή στον απομακρυσμένο κεντρικό υπολογιστή" // 
#define LOCALIZED_ERROR_NETWORKTOOMANYREFS         "Υπερβολικά πολλές αναφορές" // 

#define LOCALIZED_ERROR_POLYSTART               "Σφάλμα PolyStart" // 
#define LOCALIZED_ERROR_POLYSTARTALREADYSTARTED "Έχετε ήδη ξεκινήσει ένα πολύγωνο" // 

#define LOCALIZED_ERROR_POLYEND                 "Σφάλμα PolyEnd" // 
#define LOCALIZED_ERROR_POLYENDNOTSTARTED       "Δεν έχετε ξεκινήσει πολύγωνο" // 
#define LOCALIZED_ERROR_POLYENDNEED3VECTORS     "Χρειάζεστε τουλάχιστον 3 διανύσματα για να ορίσετε ένα πολύγωνο" // 

#define LOCALIZED_ERROR_SOUND                 "Σφάλμα ήχου" // 

#define LOCALIZED_ERROR_MIDI                  "Σφάλμα MIDI" // 
#define LOCALIZED_ERROR_MIDIINVALIDDEVICE     "’κυρη συσκευή MIDI" // 
#define LOCALIZED_ERROR_MIDIALREADYOPEN       "Είναι ήδη ανοιχτή" // 
#define LOCALIZED_ERROR_MIDINOTOPEN           "Δεν είναι ανοιχτή" // 

#define LOCALIZED_ERROR_CLIPBOARDISEMPTY      "Δεν υπάρχει κείμενο στο πρόχειρο" // 

#define LOCALIZED_ERROR_MCI                   "Σφάλμα MCI" // 

#define LOCALIZED_ERROR_TIMERNOTFOUND         "Ο χρονοδιακόπτης δε βρέθηκε" // 

#define LOCALIZED_ERROR_HHCTRLNOTLOADED       "Η online βοήθεια δεν είναι διαθέσιμη γιατί το hhctrl.ocx δε φορτώθηκε."  // 

#define LOCALIZED_ERROR_BADCOMMANDLINE        "Λάθος εντολή γραμμής εντολών"  // 

#define LOCALIZED_ERROR_TMPNOTDEFINED         "Η μεταβλητή περιβάλλοντος TMP δεν έχει οριστεί ή είναι άκυρη.\nΗ " LOCALIZED_GENERAL_PRODUCTNAME " θα προσπαθήσει να χρησιμοποιήσει το C:\\ για την αποθήκευση προσωρινών αρχείων" //

#define LOCALIZED_ERROR_GIFSAVEFAILED         "Αδύνατη η δημιουργία του GIF, ελέγξτε τη μνήμη και το χώρο στο δίσκο" // 
#define LOCALIZED_ERROR_GIFREADFAILED         "Αδύνατη η ανάγνωση του GIF, ελέγξτε τη μνήμη και το χώρο στο δίσκο" // 

#define LOCALIZED_ERROR_BITMAPINDEXOUTOFRANGE  "Ο δείκτης BitMap είναι εκτός ορίου" // 
#define LOCALIZED_ERROR_BITMAPCUTFAILED        "Η αποκοπή (cut) απέτυχε, ίσως δεν υπάρχει αρκετή μνήμη" // 

#define LOCALIZED_ERROR_BITMAPNOTHINGTOPASTE    "Δεν υπάρχει τίποτα για επικόλληση"  // 
#define LOCALIZED_ERROR_BITMAPINDEXISNOTBITMAP  "Το BitMap στον κατάλογο πρέπει να έχει εκκινηθεί με μια εικόνα"  // 

#define LOCALIZED_ERROR_TURTLEHASNOPICTURE      "Η χελώνα %d δεν έχει εικόνα, θα σταματήσει" // 

#define LOCALIZED_ERROR_FONTNOTFOUND            "Η γραμματοσειρά %s δε βρέθηκε.  Επιλέξτε μία από τις παρακάτω:\n" // 

#define LOCALIZED_ERROR_PRINTERCANTSCALE        "Ο οδηγός του εκτυπωτή δεν υποστηρίζει αυτή τη δυνατότητα."  // 
#define LOCALIZED_ERROR_CANTDRAWIMAGE           "Η εικόνα δε μπορεί να σχεδιαστεί" // 
#define LOCALIZED_ERROR_CANTEXTRACTIMAGE        "Η εικόνα δε μπορεί να εξαχθεί" // 
#define LOCALIZED_ERROR_SUBCODE                 "Υποκώδικας" // 

//
// Strings in the dialog box for reading from "stdin"
//
#define LOCALIZED_INPUT         "Παράμετρος:" // 
#define LOCALIZED_PROMPT_TO     "Σύστημα To (Ακύρωση για End)" // 
#define LOCALIZED_PROMPT_LIST   "Σύστημα List (Ακύρωση για Σταμάτημα)" // 
#define LOCALIZED_PROMPT_PAUSE  "Σύστημα Pause (Ακύρωση για Συνέχεια)" // 
#define LOCALIZED_PROMPT_INPUT  "Σύστημα Input (Ακύρωση για Σταμάτημα)" // 

//
// Messages shown by the FILE API.
//
#define LOCALIZED_FILE_CHDIRSUCCEEDED      "Είσοδος στον κατάλογο \"%s\"" // 
#define LOCALIZED_FILE_CHDIRFAILED         "Αδύνατη η είσοδος τον κατάλογο \"%s\"" // 
#define LOCALIZED_FILE_POPPEDTO            "Έξοδος στον κατάλογο \"%s\"" // 
#define LOCALIZED_FILE_MKDIRSUCCEEDED      "Είσοδος στο νέο κατάλογο \"%s\""  // 
#define LOCALIZED_FILE_MKDIRFAILED         "Αδυναμία δημιουργίας του καταλόγου \"%s\""  // 
#define LOCALIZED_FILE_RMDIRSUCCEEDED      "Αφαιρέθηκε κατάλογος \"%s\""  // 
#define LOCALIZED_FILE_RMDIRFAILED         "Αδυναμία αφαίρεσης του καταλόγου \"%s\""  // 
#define LOCALIZED_FILE_RMDIRFAILEDNOEXIST  "Ο κατάλογος δεν υπάρχει" // 
#define LOCALIZED_FILE_RMDIRFAILEDNOTEMPTY "Σιγουρευτείτε ότι ο κατάλογος είναι άδειος πριν προσπαθήσετε να τον αφαιρέσετε." // 


//
// The default title of a Logo picture when it is printed
//
#define LOCALIZED_BITMAPPRINTOUTTITLE       "Logo Picture" // NOT_YET_LOCALIZED

//
// Other strings
//
#define LOCALIZED_ACTIVEAREA    "Ενεργή περιοχή" // 
#define LOCALIZED_INFORMATION   "Πληροφορίες" // 
#define LOCALIZED_WARNING       "Προσοχή" // 
#define LOCALIZED_UNTITLED      "Χωρίς τίτλο" // 
#define LOCALIZED_UNKNOWN       "’γνωστο" // 

// The text which is shown when the Unbound node is formatted.
// This happens when a macro outputs nothing (instead of a list)
#define LOCALIZED_UNBOUND       "(Εκτός ορίου)" // 

// The title of the Editor's Find/Replace dialog box
#define LOCALIZED_EDITOR_TITLE_FIND     "Εύρεση"
#define LOCALIZED_EDITOR_TITLE_REPLACE  "Αντικατάσταση"

//
// The text that's displayed when the Editor's Search->Find fails.
//
#define LOCALIZED_STRINGTABLE_CANNOTFINDSTRING "{ Δε βρέθηκε το %s }" // 


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
