/*
 *      init.cpp     logo init module                      dvb
 *
 *       Copyright (C) 1995 by the Regents of the University of California
 *       Copyright (C) 1995 by George Mills
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include "localizednode.h"
#include "eval.h"
#include "paren.h"
#include "intern.h"
#include "logodata.h"
#include "logomath.h"
#include "wrksp.h"
#include "coms.h"
#include "lists.h"
#include "areawind.h"
#include "files.h"
#include "graphics.h"
#include "unix.h"
#include "error.h"
#include "mem.h"
#include "parse.h"
#include "print.h"
#include "term.h"
#include "logocore.h"

#include "mmwind.h"
#include "dllwind.h"
#include "devwind.h"
#include "dlgwind.h"
#include "netwind.h"
#include "graphwin.h"

#include "localizedstrings.h"

struct PRIMTYPE
{
    const char * name;
    short        minargs;
    short        defargs;
    short        maxargs;
    short        priority;
    logofunc     prim;
    const char * alternatename;
};

CLocalizedNode Truex;
CLocalizedNode Falsex;
NODE *Right_Paren;
NODE *Left_Paren;
CLocalizedNode Toplevel;
CLocalizedNode System;
CLocalizedNode Error;
CLocalizedNode End;
CLocalizedNode Redefp;
CLocalizedNode Caseignoredp;
CLocalizedNode Erract;
CLocalizedNode Printdepthlimit;
CLocalizedNode Printwidthlimit;
NODE *Pause;
NODE *If;
NODE *Ifelse;
CLocalizedNode To;
NODE *Macro;
NODE *Unbound;         // a special node that means nothing (or void) was returned
                       // This is different from NIL, which is the empty list.
NODE *Not_Enough_Node;
NODE *Minus_Sign;
NODE *Minus_Tight;
CLocalizedNode Startup;
NODE *Query;
NODE *Output;
NODE *Stop;
NODE *Goto;
NODE *Tag;
NODE *Null_Word = NIL;

const PRIMTYPE prims[] =
{
    { "*", 1, 1, 1, PREFIX_PRIORITY + 3, lmul },
    { "+", 1, 1, 1, PREFIX_PRIORITY + 2, ladd },
    { "-", 1, 1, 1, PREFIX_PRIORITY + 2, lsub },
    { "--", 1, 1, 1, PREFIX_PRIORITY + 4, lsub },
    { ".defmacro", 2, 2, 2, PREFIX_PRIORITY, ldefmacro, LOCALIZED_ALTERNATE__DEFMACRO },
    { ".eq", 2, 2, 2, PREFIX_PRIORITY, l_eq, LOCALIZED_ALTERNATE__EQ },
    { ".macro", -1, -1, -1, PREFIX_PRIORITY, lmacro, LOCALIZED_ALTERNATE__MACRO },
    { ".maybeoutput", 1, 1, 1, MAYBE_PRIORITY, loutput, LOCALIZED_ALTERNATE__MAYBEOUTPUT },
    { ".setbf", 2, 2, 2, PREFIX_PRIORITY, l_setbf, LOCALIZED_ALTERNATE__SETBF },
    { ".setfirst", 2, 2, 2, PREFIX_PRIORITY, l_setfirst, LOCALIZED_ALTERNATE__SETFIRST },
    { ".setitem", 3, 3, 3, PREFIX_PRIORITY, l_setitem, LOCALIZED_ALTERNATE__SETITEM },
    { "/", 1, 1, 1, PREFIX_PRIORITY + 3, ldivide },
    { "<", 2, 2, 2, PREFIX_PRIORITY + 1, llessp },
    { "=", 2, 2, 2, PREFIX_PRIORITY + 1, lequalp },
    { ">", 2, 2, 2, PREFIX_PRIORITY + 1, lgreaterp },
    { "<=", 2, 2, 2, PREFIX_PRIORITY + 1, llessequalp },
    { "<>", 2, 2, 2, PREFIX_PRIORITY + 1, lnotequalp },
    { ">=", 2, 2, 2, PREFIX_PRIORITY + 1, lgreaterequalp },
    { "?", 0, 0, 1, PREFIX_PRIORITY, lqm },
    { "activearea", 0, 0, 0, PREFIX_PRIORITY, lactivearea, LOCALIZED_ALTERNATE_ACTIVEAREA },
    { "allopen", 0, 0, 0, PREFIX_PRIORITY, lallopen, LOCALIZED_ALTERNATE_ALLOPEN },
    { "and", 0, 2, -1, PREFIX_PRIORITY, land, LOCALIZED_ALTERNATE_AND },
    { "apply", 2, 2, 2, MACRO_PRIORITY, lapply, LOCALIZED_ALTERNATE_APPLY },
    { "arccos", 1, 1, 1, PREFIX_PRIORITY, lacos, LOCALIZED_ALTERNATE_ARCCOS },
    { "arcsin", 1, 1, 1, PREFIX_PRIORITY, lasin, LOCALIZED_ALTERNATE_ARCSIN },
    { "arctan", 1, 1, 2, PREFIX_PRIORITY, latan, LOCALIZED_ALTERNATE_ARCTAN },
    { "array", 1, 1, 2, PREFIX_PRIORITY, larray, LOCALIZED_ALTERNATE_ARRAY },
    { "arrayp", 1, 1, 1, PREFIX_PRIORITY, larrayp, LOCALIZED_ALTERNATE_ARRAYP },
    { "array?", 1, 1, 1, PREFIX_PRIORITY, larrayp, LOCALIZED_ALTERNATE_ARRAY_ },
    { "ascii", 1, 1, 1, PREFIX_PRIORITY, lascii, LOCALIZED_ALTERNATE_ASCII },
    { "ashift", 2, 2, 2, PREFIX_PRIORITY, lashift, LOCALIZED_ALTERNATE_ASHIFT },
    { "back", 1, 1, 1, PREFIX_PRIORITY, lback, LOCALIZED_ALTERNATE_BACK },
    { "backslashedp", 1, 1, 1, PREFIX_PRIORITY, lbackslashedp, LOCALIZED_ALTERNATE_BACKSLASHEDP },
    { "backslashed?", 1, 1, 1, PREFIX_PRIORITY, lbackslashedp, LOCALIZED_ALTERNATE_BACKSLASHED_ },
    { "beforep", 2, 2, 2, PREFIX_PRIORITY, lbeforep, LOCALIZED_ALTERNATE_BEFOREP },
    { "before?", 2, 2, 2, PREFIX_PRIORITY, lbeforep, LOCALIZED_ALTERNATE_BEFORE_ },
    { "bf", 1, 1, 1, PREFIX_PRIORITY, lbutfirst, LOCALIZED_ALTERNATE_BF },
    { "bfs", 1, 1, 1, PREFIX_PRIORITY, lbfs, LOCALIZED_ALTERNATE_BFS },
    { "bitand", 0, 2, -1, PREFIX_PRIORITY, lbitand, LOCALIZED_ALTERNATE_BITAND },
    { "bitblock", 2, 2, 2, PREFIX_PRIORITY, lbitblock, LOCALIZED_ALTERNATE_BITBLOCK },
    { "bitcopy", 2, 2, 2, PREFIX_PRIORITY, lbitcopy, LOCALIZED_ALTERNATE_BITCOPY },
    { "bitcut", 2, 2, 2, PREFIX_PRIORITY, lbitcut, LOCALIZED_ALTERNATE_BITCUT },
    { "bitfit", 2, 2, 2, PREFIX_PRIORITY, lbitfit, LOCALIZED_ALTERNATE_BITFIT },
    { "bitindex", 0, 0, 0, PREFIX_PRIORITY, lbitindex, LOCALIZED_ALTERNATE_BITINDEX },
    { "bitload", 1, 1, 1, PREFIX_PRIORITY, lbitload, LOCALIZED_ALTERNATE_BITLOAD },
    { "bitloadsize", 1, 1, 1, PREFIX_PRIORITY, lbitloadsize, LOCALIZED_ALTERNATE_BITLOADSIZE },
    { "bitsize", 0, 0, 0, PREFIX_PRIORITY, lbitsize, LOCALIZED_ALTERNATE_BITSIZE },
    { "bitmapturtle", 0, 0, 1, PREFIX_PRIORITY, lbitmapturtle, LOCALIZED_ALTERNATE_BITMAPTURTLE },
    { "bitmode", 0, 0, 0, PREFIX_PRIORITY, lbitmode, LOCALIZED_ALTERNATE_BITMODE },
    { "bitnot", 1, 1, 1, PREFIX_PRIORITY, lbitnot, LOCALIZED_ALTERNATE_BITNOT },
    { "bitor", 0, 2, -1, PREFIX_PRIORITY, lbitor, LOCALIZED_ALTERNATE_BITOR },
    { "bitpaste", 0, 0, 0, PREFIX_PRIORITY, lbitpaste, LOCALIZED_ALTERNATE_BITPASTE },
    { "bitpastetoindex", 3, 3, 3, PREFIX_PRIORITY, lbitpastetoindex, LOCALIZED_ALTERNATE_BITPASTETOINDEX },
    { "bitsave", 1, 1, 2, PREFIX_PRIORITY, lbitsave, LOCALIZED_ALTERNATE_BITSAVE },
    { "bitxor", 0, 2, -1, PREFIX_PRIORITY, lbitxor, LOCALIZED_ALTERNATE_BITXOR },
    { "bk", 1, 1, 1, PREFIX_PRIORITY, lback, LOCALIZED_ALTERNATE_BK },
    { "bl", 1, 1, 1, PREFIX_PRIORITY, lbutlast, LOCALIZED_ALTERNATE_BL },
    { "buried", 0, 0, 0, PREFIX_PRIORITY, lburied, LOCALIZED_ALTERNATE_BURIED },
    { "bury", 1, 1, 1, PREFIX_PRIORITY, lbury, LOCALIZED_ALTERNATE_BURY },
    { "butfirst", 1, 1, 1, PREFIX_PRIORITY, lbutfirst, LOCALIZED_ALTERNATE_BUTFIRST },
    { "butfirsts", 1, 1, 1, PREFIX_PRIORITY, lbfs, LOCALIZED_ALTERNATE_BUTFIRSTS },
    { "butlast", 1, 1, 1, PREFIX_PRIORITY, lbutlast, LOCALIZED_ALTERNATE_BUTLAST },
    { "buttoncreate", 8, 8, 8, PREFIX_PRIORITY, lbuttoncreate, LOCALIZED_ALTERNATE_BUTTONCREATE },
    { "buttondelete", 1, 1, 1, PREFIX_PRIORITY, lbuttondelete, LOCALIZED_ALTERNATE_BUTTONDELETE },
    { "buttonenable", 2, 2, 2, PREFIX_PRIORITY, lbuttonenable, LOCALIZED_ALTERNATE_BUTTONENABLE },
    { "buttonupdate", 2, 2, 2, PREFIX_PRIORITY, lbuttonupdate, LOCALIZED_ALTERNATE_BUTTONUPDATE },
    { "buttonp", 0, 0, 0, PREFIX_PRIORITY, lbuttonp, LOCALIZED_ALTERNATE_BUTTONP },
    { "button?", 0, 0, 0, PREFIX_PRIORITY, lbuttonp, LOCALIZED_ALTERNATE_BUTTON_ },
    { "bye", 0, 0, 0, PREFIX_PRIORITY, lbye, LOCALIZED_ALTERNATE_BYE },
    { "catch", 2, 2, 2, MACRO_PRIORITY, lcatch, LOCALIZED_ALTERNATE_CATCH },
    { "char", 1, 1, 1, PREFIX_PRIORITY, lchar, LOCALIZED_ALTERNATE_CHAR },
    { "chdir", 1, 1, 1, PREFIX_PRIORITY, lchdir, LOCALIZED_ALTERNATE_CHDIR },
    { "checkboxcreate", 8, 8, 8, PREFIX_PRIORITY, lcheckboxcreate, LOCALIZED_ALTERNATE_CHECKBOXCREATE },
    { "checkboxdelete", 1, 1, 1, PREFIX_PRIORITY, lcheckboxdelete, LOCALIZED_ALTERNATE_CHECKBOXDELETE },
    { "checkboxenable", 2, 2, 2, PREFIX_PRIORITY, lcheckboxenable, LOCALIZED_ALTERNATE_CHECKBOXENABLE },
    { "checkboxget", 1, 1, 1, PREFIX_PRIORITY, lcheckboxget, LOCALIZED_ALTERNATE_CHECKBOXGET },
    { "checkboxset", 2, 2, 2, PREFIX_PRIORITY, lcheckboxset, LOCALIZED_ALTERNATE_CHECKBOXSET },
    { "clean", 0, 0, 0, PREFIX_PRIORITY, lclean, LOCALIZED_ALTERNATE_CLEAN },
    { "clearpalette", 0, 0, 0, PREFIX_PRIORITY, lclearpalette, LOCALIZED_ALTERNATE_CLEARPALETTE },
    { "clearscreen", 0, 0, 0, PREFIX_PRIORITY, lclearscreen, LOCALIZED_ALTERNATE_CLEARSCREEN },
    { "cleartext", 0, 0, 0, PREFIX_PRIORITY, lcleartext, LOCALIZED_ALTERNATE_CLEARTEXT },
    { "cleartimer", 1, 1, 1, PREFIX_PRIORITY, lcleartimer, LOCALIZED_ALTERNATE_CLEARTIMER },
    { "close", 1, 1, 1, PREFIX_PRIORITY, lclose, LOCALIZED_ALTERNATE_CLOSE },
    { "closeall", 0, 0, 0, PREFIX_PRIORITY, lcloseall, LOCALIZED_ALTERNATE_CLOSEALL },
    { "co", OK_NO_ARG, 1, 1, PREFIX_PRIORITY, lcontinue, LOCALIZED_ALTERNATE_CO },
    { "comboboxaddstring", 2, 2, 2, PREFIX_PRIORITY, lcomboboxaddstring, LOCALIZED_ALTERNATE_COMBOBOXADDSTRING },
    { "comboboxcreate", 6, 6, 6, PREFIX_PRIORITY, lcomboboxcreate, LOCALIZED_ALTERNATE_COMBOBOXCREATE },
    { "comboboxdelete", 1, 1, 1, PREFIX_PRIORITY, lcomboboxdelete, LOCALIZED_ALTERNATE_COMBOBOXDELETE },
    { "comboboxenable", 2, 2, 2, PREFIX_PRIORITY, lcomboboxenable, LOCALIZED_ALTERNATE_COMBOBOXENABLE },
    { "comboboxdeletestring", 2, 2, 2, PREFIX_PRIORITY, lcomboboxdeletestring, LOCALIZED_ALTERNATE_COMBOBOXDELETESTRING },
    { "comboboxgettext", 1, 1, 1, PREFIX_PRIORITY, lcomboboxgettext, LOCALIZED_ALTERNATE_COMBOBOXGETTEXT },
    { "comboboxsettext", 2, 2, 2, PREFIX_PRIORITY, lcomboboxsettext, LOCALIZED_ALTERNATE_COMBOBOXSETTEXT },
    { "contents", 0, 0, 0, PREFIX_PRIORITY, lcontents, LOCALIZED_ALTERNATE_CONTENTS },
    { "continue", OK_NO_ARG, 1, 1, PREFIX_PRIORITY, lcontinue, LOCALIZED_ALTERNATE_CONTINUE },
    { "copydef", 2, 2, 2, PREFIX_PRIORITY, lcopydef, LOCALIZED_ALTERNATE_COPYDEF },
    { "cos", 1, 1, 1, PREFIX_PRIORITY, lcos, LOCALIZED_ALTERNATE_COS },
    { "count", 1, 1, 1, PREFIX_PRIORITY, lcount, LOCALIZED_ALTERNATE_COUNT },
    { "cs", 0, 0, 0, PREFIX_PRIORITY, lclearscreen, LOCALIZED_ALTERNATE_CS },
    { "ct", 0, 0, 0, PREFIX_PRIORITY, lcleartext, LOCALIZED_ALTERNATE_CT },
    { "cursor", 0, 0, 0, PREFIX_PRIORITY, lcursor, LOCALIZED_ALTERNATE_CURSOR },
    { "debugwindows", 0, 0, 1, PREFIX_PRIORITY, ldebugwindows, LOCALIZED_ALTERNATE_DEBUGWINDOWS },
    { "define", 2, 2, 2, PREFIX_PRIORITY, ldefine, LOCALIZED_ALTERNATE_DEFINE },
    { "definedp", 1, 1, 1, PREFIX_PRIORITY, ldefinedp, LOCALIZED_ALTERNATE_DEFINEDP },
    { "defined?", 1, 1, 1, PREFIX_PRIORITY, ldefinedp, LOCALIZED_ALTERNATE_DEFINED_ },
    { "dialogcreate", 8, 8, 8, PREFIX_PRIORITY, ldialogcreate, LOCALIZED_ALTERNATE_DIALOGCREATE },
    { "dialogenable", 2, 2, 2, PREFIX_PRIORITY, ldialogenable, LOCALIZED_ALTERNATE_DIALOGENABLE },
    { "dialogdelete", 1, 1, 1, PREFIX_PRIORITY, ldialogdelete, LOCALIZED_ALTERNATE_DIALOGDELETE },
    { "dialogfileopen", 1, 1, 1, PREFIX_PRIORITY, ldialogfileopen, LOCALIZED_ALTERNATE_DIALOGFILEOPEN },
    { "dialogfilesave", 1, 1, 1, PREFIX_PRIORITY, ldialogfilesave, LOCALIZED_ALTERNATE_DIALOGFILESAVE },
    { "difference", 2, 2, 2, PREFIX_PRIORITY, lsub, LOCALIZED_ALTERNATE_DIFFERENCE },
    { "directories", 0, 0, 0, PREFIX_PRIORITY, ldirectories, LOCALIZED_ALTERNATE_DIRECTORIES },
    { "dllcall", 1, 1, 2, PREFIX_PRIORITY, ldllcall, LOCALIZED_ALTERNATE_DLLCALL },
    { "dllfree", 0, 0, 1, PREFIX_PRIORITY, ldllfree, LOCALIZED_ALTERNATE_DLLFREE },
    { "dllload", 1, 1, 1, PREFIX_PRIORITY, ldllload, LOCALIZED_ALTERNATE_DLLLOAD },
    { "down", 1, 1, 1, PREFIX_PRIORITY, ldownpitch, LOCALIZED_ALTERNATE_DOWN },
    { "downpitch", 1, 1, 1, PREFIX_PRIORITY, ldownpitch, LOCALIZED_ALTERNATE_DOWNPITCH },
    { "dribble", 1, 1, 1, PREFIX_PRIORITY, ldribble, LOCALIZED_ALTERNATE_DRIBBLE },
    { "ed", 1, 1, 1, PREFIX_PRIORITY, ledit, LOCALIZED_ALTERNATE_ED },
    { "edit", 1, 1, 1, PREFIX_PRIORITY, ledit, LOCALIZED_ALTERNATE_EDIT },
    { "ellipsearc", 4, 4, 4, PREFIX_PRIORITY, lellipsearc, LOCALIZED_ALTERNATE_ELLIPSEARC },
    { "emptyp", 1, 1, 1, PREFIX_PRIORITY, lemptyp, LOCALIZED_ALTERNATE_EMPTYP },
    { "empty?", 1, 1, 1, PREFIX_PRIORITY, lemptyp, LOCALIZED_ALTERNATE_EMPTY_ },
    { "eofp", 0, 0, 0, PREFIX_PRIORITY, leofp, LOCALIZED_ALTERNATE_EOFP },
    { "eof?", 0, 0, 0, PREFIX_PRIORITY, leofp, LOCALIZED_ALTERNATE_EOF_ },
    { "equalp", 2, 2, 2, PREFIX_PRIORITY, lequalp, LOCALIZED_ALTERNATE_EQUALP },
    { "equal?", 2, 2, 2, PREFIX_PRIORITY, lequalp, LOCALIZED_ALTERNATE_EQUAL_ },
    { "er", 1, 1, 1, PREFIX_PRIORITY, lerase, LOCALIZED_ALTERNATE_ER },
    { "erase", 1, 1, 1, PREFIX_PRIORITY, lerase, LOCALIZED_ALTERNATE_ERASE },
    { "erasefile", 1, 1, 1, PREFIX_PRIORITY, lerasefile, LOCALIZED_ALTERNATE_ERASEFILE },
    { "erf", 1, 1, 1, PREFIX_PRIORITY, lerasefile, LOCALIZED_ALTERNATE_ERF },
    { "error", 0, 0, 0, PREFIX_PRIORITY, lerror, LOCALIZED_ALTERNATE_ERROR },
    { "eventcheck", 0, 0, 0, PREFIX_PRIORITY, leventcheck, LOCALIZED_ALTERNATE_EVENTCHECK },
    { "exp", 1, 1, 1, PREFIX_PRIORITY, lexp, LOCALIZED_ALTERNATE_EXP },
    { "fd", 1, 1, 1, PREFIX_PRIORITY, lforward, LOCALIZED_ALTERNATE_FD },
    { "fence", 0, 0, 0, PREFIX_PRIORITY, lfence, LOCALIZED_ALTERNATE_FENCE },
    { "fill", 0, 0, 1, PREFIX_PRIORITY, lfill, LOCALIZED_ALTERNATE_FILL },
    { "files", 0, 0, 0, PREFIX_PRIORITY, lfiles, LOCALIZED_ALTERNATE_FILES },
    { "first", 1, 1, 1, PREFIX_PRIORITY, lfirst, LOCALIZED_ALTERNATE_FIRST },
    { "firsts", 1, 1, 1, PREFIX_PRIORITY, lfirsts, LOCALIZED_ALTERNATE_FIRSTS },
    { "floodcolor", 0, 0, 0, PREFIX_PRIORITY, lfloodcolor, LOCALIZED_ALTERNATE_FLOODCOLOR },
    { "fontfacenames", 0, 0, 0, PREFIX_PRIORITY, lfontfacenames, LOCALIZED_ALTERNATE_FONTFACENAMES },
    { "forever", 1, 1, 1, MACRO_PRIORITY, lforever, LOCALIZED_ALTERNATE_FOREVER },
    { "form", 3, 3, 3, PREFIX_PRIORITY, lform, LOCALIZED_ALTERNATE_FORM },
    { "forward", 1, 1, 1, PREFIX_PRIORITY, lforward, LOCALIZED_ALTERNATE_FORWARD },
    { "fput", 2, 2, 2, PREFIX_PRIORITY, lfput, LOCALIZED_ALTERNATE_FPUT },
    { "fs", 0, 0, 0, PREFIX_PRIORITY, lfullscreen, LOCALIZED_ALTERNATE_FS },
    { "fullscreen", 0, 0, 0, PREFIX_PRIORITY, lfullscreen, LOCALIZED_ALTERNATE_FULLSCREEN },
    { "fulltext", 1, 1, 1, PREFIX_PRIORITY, lfulltext, LOCALIZED_ALTERNATE_FULLTEXT },
    { "getfocus", 0, 0, 0, PREFIX_PRIORITY, lgetfocus, LOCALIZED_ALTERNATE_GETFOCUS },
    // { "goto", 1, 1, 1, MACRO_PRIORITY, lgoto, LOCALIZED_ALTERNATE_GOTO },
    { "gifload", 1, 1, 1, PREFIX_PRIORITY, lgifload, LOCALIZED_ALTERNATE_GIFLOAD },
    { "gifsize", 1, 1, 1, PREFIX_PRIORITY, lgifsize, LOCALIZED_ALTERNATE_GIFSIZE },
    { "gifsave", 1, 1, 6, PREFIX_PRIORITY, lgifsave, LOCALIZED_ALTERNATE_GIFSAVE },
    { "gprop", 2, 2, 2, PREFIX_PRIORITY, lgprop, LOCALIZED_ALTERNATE_GPROP },
    { "greater?", 2, 2, 2, PREFIX_PRIORITY, lgreaterp, LOCALIZED_ALTERNATE_GREATER_ },
    { "greaterequal?", 2, 2, 2, PREFIX_PRIORITY, lgreaterequalp, LOCALIZED_ALTERNATE_GREATEREQUAL_ },
    { "greaterequalp", 2, 2, 2, PREFIX_PRIORITY, lgreaterequalp, LOCALIZED_ALTERNATE_GREATEREQUALP },
    { "greaterp", 2, 2, 2, PREFIX_PRIORITY, lgreaterp, LOCALIZED_ALTERNATE_GREATERP },
    { "groupboxcreate", 6, 6, 6, PREFIX_PRIORITY, lgroupboxcreate, LOCALIZED_ALTERNATE_GROUPBOXCREATE },
    { "groupboxdelete", 1, 1, 1, PREFIX_PRIORITY, lgroupboxdelete, LOCALIZED_ALTERNATE_GROUPBOXDELETE },
    { "halt", 0, 0, 0, PREFIX_PRIORITY, lhalt, LOCALIZED_ALTERNATE_HALT },
    { "hasownpen?", 0, 0, 0, PREFIX_PRIORITY, lhasownpenp, LOCALIZED_ALTERNATE_HASOWNPEN_ },
    { "hasownpenp", 0, 0, 0, PREFIX_PRIORITY, lhasownpenp, LOCALIZED_ALTERNATE_HASOWNPENP },
    { "heading", 0, 0, 0, PREFIX_PRIORITY, lheading, LOCALIZED_ALTERNATE_HEADING },
    { "help", OK_NO_ARG, 1, 1, PREFIX_PRIORITY, lhelp, LOCALIZED_ALTERNATE_HELP },
    { "hideturtle", 0, 0, 0, PREFIX_PRIORITY, lhideturtle, LOCALIZED_ALTERNATE_HIDETURTLE },
    { "home", 0, 0, 0, PREFIX_PRIORITY, lhome, LOCALIZED_ALTERNATE_HOME },
    { "ht", 0, 0, 0, PREFIX_PRIORITY, lhideturtle, LOCALIZED_ALTERNATE_HT },
    { "if", 2, 2, 3, MACRO_PRIORITY, lif, LOCALIZED_ALTERNATE_IF },
    { "ifelse", 3, 3, 3, MACRO_PRIORITY, lifelse, LOCALIZED_ALTERNATE_IFELSE },
    { "iff", 1, 1, 1, MACRO_PRIORITY, liffalse, LOCALIZED_ALTERNATE_IFF },
    { "iffalse", 1, 1, 1, MACRO_PRIORITY, liffalse, LOCALIZED_ALTERNATE_IFFALSE },
    { "ift", 1, 1, 1, MACRO_PRIORITY, liftrue, LOCALIZED_ALTERNATE_IFT },
    { "iftrue", 1, 1, 1, MACRO_PRIORITY, liftrue, LOCALIZED_ALTERNATE_IFTRUE },
    { "ingameport", 1, 1, 2, PREFIX_PRIORITY, lingameport, LOCALIZED_ALTERNATE_INGAMEPORT },
    { "inport", 1, 1, 1, PREFIX_PRIORITY, linport, LOCALIZED_ALTERNATE_INPORT },
    { "inportb", 1, 1, 1, PREFIX_PRIORITY, linportb, LOCALIZED_ALTERNATE_INPORTB },
    { "int", 1, 1, 1, PREFIX_PRIORITY, linteg, LOCALIZED_ALTERNATE_INT },
    { "item", 2, 2, 2, PREFIX_PRIORITY, litem, LOCALIZED_ALTERNATE_ITEM },
    { "keyboardoff", 0, 0, 0, PREFIX_PRIORITY, lkeyboardoff, LOCALIZED_ALTERNATE_KEYBOARDOFF },
    { "keyboardon", 1, 1, 2, PREFIX_PRIORITY, lkeyboardon, LOCALIZED_ALTERNATE_KEYBOARDON },
    { "keyboardvalue", 0, 0, 0, PREFIX_PRIORITY, lkeyboardvalue, LOCALIZED_ALTERNATE_KEYBOARDVALUE },
    { "keyp", 0, 0, 0, PREFIX_PRIORITY, lkeyp, LOCALIZED_ALTERNATE_KEYP },
    { "key?", 0, 0, 0, PREFIX_PRIORITY, lkeyp, LOCALIZED_ALTERNATE_KEY_ },
    { "label", 1, 1, 1, PREFIX_PRIORITY, llabel, LOCALIZED_ALTERNATE_LABEL },
    { "labelfont", 0, 0, 0, PREFIX_PRIORITY, llabelfont, LOCALIZED_ALTERNATE_LABELFONT },
    { "labelsize", 1, 1, 1, PREFIX_PRIORITY, llabelsize, LOCALIZED_ALTERNATE_LABELSIZE },
    { "last", 1, 1, 1, PREFIX_PRIORITY, llast, LOCALIZED_ALTERNATE_LAST },
    { "left", 1, 1, 1, PREFIX_PRIORITY, lleft, LOCALIZED_ALTERNATE_LEFT },
    { "leftroll", 1, 1, 1, PREFIX_PRIORITY, lleftroll, LOCALIZED_ALTERNATE_LEFTROLL },
    { "less?", 2, 2, 2, PREFIX_PRIORITY, llessp, LOCALIZED_ALTERNATE_LESS_ },
    { "lessequal?", 2, 2, 2, PREFIX_PRIORITY, llessequalp, LOCALIZED_ALTERNATE_LESSEQUAL_ },
    { "lessequalp", 2, 2, 2, PREFIX_PRIORITY, llessequalp, LOCALIZED_ALTERNATE_LESSEQUALP },
    { "lessp", 2, 2, 2, PREFIX_PRIORITY, llessp, LOCALIZED_ALTERNATE_LESSP },
    { "light", 0, 0, 0, PREFIX_PRIORITY, llight, LOCALIZED_ALTERNATE_LIGHT },
    { "list", 0, 2, -1, PREFIX_PRIORITY, llist, LOCALIZED_ALTERNATE_LIST },
    { "listboxaddstring", 2, 2, 2, PREFIX_PRIORITY, llistboxaddstring, LOCALIZED_ALTERNATE_LISTBOXADDSTRING },
    { "listboxcreate", 6, 6, 6, PREFIX_PRIORITY, llistboxcreate, LOCALIZED_ALTERNATE_LISTBOXCREATE },
    { "listboxenable", 2, 2, 2, PREFIX_PRIORITY, llistboxenable, LOCALIZED_ALTERNATE_LISTBOXENABLE },
    { "listboxdelete", 1, 1, 1, PREFIX_PRIORITY, llistboxdelete, LOCALIZED_ALTERNATE_LISTBOXDELETE },
    { "listboxdeletestring", 2, 2, 2, PREFIX_PRIORITY, llistboxdeletestring, LOCALIZED_ALTERNATE_LISTBOXDELETESTRING },
    { "listboxgetselect", 1, 1, 1, PREFIX_PRIORITY, llistboxgetselect, LOCALIZED_ALTERNATE_LISTBOXGETSELECT },
    { "listp", 1, 1, 1, PREFIX_PRIORITY, llistp, LOCALIZED_ALTERNATE_LISTP },
    { "list?", 1, 1, 1, PREFIX_PRIORITY, llistp, LOCALIZED_ALTERNATE_LIST_ },
    { "ln", 1, 1, 1, PREFIX_PRIORITY, lln, LOCALIZED_ALTERNATE_LN },
    { "load", 1, 1, 1, PREFIX_PRIORITY, lload, LOCALIZED_ALTERNATE_LOAD },
    { "local", 1, 1, -1, PREFIX_PRIORITY, llocal, LOCALIZED_ALTERNATE_LOCAL },
    { "log10", 1, 1, 1, PREFIX_PRIORITY, llog10, LOCALIZED_ALTERNATE_LOG10 },
    { "logoversion", 0, 0, 0, PREFIX_PRIORITY, llogoversion, LOCALIZED_ALTERNATE_LOGOVERSION },
    { "lowercase", 1, 1, 1, PREFIX_PRIORITY, llowercase, LOCALIZED_ALTERNATE_LOWERCASE },
    { "lput", 2, 2, 2, PREFIX_PRIORITY, llput, LOCALIZED_ALTERNATE_LPUT },
    { "lr", 1, 1, 1, PREFIX_PRIORITY, lleftroll, LOCALIZED_ALTERNATE_LR },
    { "lshift", 2, 2, 2, PREFIX_PRIORITY, llshift, LOCALIZED_ALTERNATE_LSHIFT },
    { "lt", 1, 1, 1, PREFIX_PRIORITY, lleft, LOCALIZED_ALTERNATE_LT },
    { "machine", 0, 0, 0, PREFIX_PRIORITY, lmachine, LOCALIZED_ALTERNATE_MACHINE },
    { "macrop", 1, 1, 1, PREFIX_PRIORITY, lmacrop, LOCALIZED_ALTERNATE_MACROP },
    { "macro?", 1, 1, 1, PREFIX_PRIORITY, lmacrop, LOCALIZED_ALTERNATE_MACRO_ },
    { "make", 2, 2, 2, PREFIX_PRIORITY, lmake, LOCALIZED_ALTERNATE_MAKE },
    { "mci", 1, 1, 2, PREFIX_PRIORITY, lmci, LOCALIZED_ALTERNATE_MCI },
    { "member", 2, 2, 2, PREFIX_PRIORITY, lmember, LOCALIZED_ALTERNATE_MEMBER },
    { "memberp", 2, 2, 2, PREFIX_PRIORITY, lmemberp, LOCALIZED_ALTERNATE_MEMBERP },
    { "member?", 2, 2, 2, PREFIX_PRIORITY, lmemberp, LOCALIZED_ALTERNATE_MEMBER_ },
    { "messagebox", 2, 2, 2, PREFIX_PRIORITY, lmessagebox, LOCALIZED_ALTERNATE_MESSAGEBOX },
    { "midiclose", 0, 0, 0, PREFIX_PRIORITY, lmidiclose, LOCALIZED_ALTERNATE_MIDICLOSE },
    { "midimessage", 1, 1, 1, PREFIX_PRIORITY, lmidimessage, LOCALIZED_ALTERNATE_MIDIMESSAGE },
    { "midiopen", 0, 0, 1, PREFIX_PRIORITY, lmidiopen, LOCALIZED_ALTERNATE_MIDIOPEN },
    { "minus", 1, 1, 1, PREFIX_PRIORITY, lsub, LOCALIZED_ALTERNATE_MINUS },
    { "mkdir", 1, 1, 1, PREFIX_PRIORITY, lmkdir, LOCALIZED_ALTERNATE_MKDIR },
    { "modulo", 2, 2, 2, PREFIX_PRIORITY, lmodulo, LOCALIZED_ALTERNATE_MODULO },
    { "mouseoff", 0, 0, 0, PREFIX_PRIORITY, lmouseoff, LOCALIZED_ALTERNATE_MOUSEOFF },
    { "mouseon", 5, 5, 5, PREFIX_PRIORITY, lmouseon, LOCALIZED_ALTERNATE_MOUSEON },
    { "mousepos", 0, 0, 0, PREFIX_PRIORITY, lmousepos, LOCALIZED_ALTERNATE_MOUSEPOS },
    { "namep", 1, 1, 1, PREFIX_PRIORITY, lnamep, LOCALIZED_ALTERNATE_NAMEP },
    { "name?", 1, 1, 1, PREFIX_PRIORITY, lnamep, LOCALIZED_ALTERNATE_NAME_ },
    { "names", 0, 0, 0, PREFIX_PRIORITY, lnames, LOCALIZED_ALTERNATE_NAMES },
    { "netacceptoff", 0, 0, 0, PREFIX_PRIORITY, lnetacceptoff, LOCALIZED_ALTERNATE_NETACCEPTOFF },
    { "netaccepton", 3, 3, 3, PREFIX_PRIORITY, lnetaccepton, LOCALIZED_ALTERNATE_NETACCEPTON },
    { "netacceptreceivevalue", 0, 0, 0, PREFIX_PRIORITY, lnetacceptreceivevalue, LOCALIZED_ALTERNATE_NETACCEPTRECEIVEVALUE },
    { "netacceptsendvalue", 1, 1, 1, PREFIX_PRIORITY, lnetacceptsendvalue, LOCALIZED_ALTERNATE_NETACCEPTSENDVALUE },
    { "netconnectoff", 0, 0, 0, PREFIX_PRIORITY, lnetconnectoff, LOCALIZED_ALTERNATE_NETCONNECTOFF },
    { "netconnecton", 4, 4, 4, PREFIX_PRIORITY, lnetconnecton, LOCALIZED_ALTERNATE_NETCONNECTON },
    { "netconnectreceivevalue", 0, 0, 0, PREFIX_PRIORITY, lnetconnectreceivevalue, LOCALIZED_ALTERNATE_NETCONNECTRECEIVEVALUE },
    { "netconnectsendvalue", 1, 1, 1, PREFIX_PRIORITY, lnetconnectsendvalue, LOCALIZED_ALTERNATE_NETCONNECTSENDVALUE },
    { "netshutdown", 0, 0, 0, PREFIX_PRIORITY, lnetshutdown, LOCALIZED_ALTERNATE_NETSHUTDOWN },
    { "netstartup", 0, 0, 1, PREFIX_PRIORITY, lnetstartup, LOCALIZED_ALTERNATE_NETSTARTUP },
    { "nobitmapturtle", 0, 0, 0, PREFIX_PRIORITY, lnobitmapturtle, LOCALIZED_ALTERNATE_NOBITMAPTURTLE },
    { "nodes", 0, 0, 0, PREFIX_PRIORITY, lnodes, LOCALIZED_ALTERNATE_NODES },
    { "nodribble", 0, 0, 0, PREFIX_PRIORITY, lnodribble, LOCALIZED_ALTERNATE_NODRIBBLE },
    { "nostatus", 0, 0, 0, PREFIX_PRIORITY, lnostatus, LOCALIZED_ALTERNATE_NOSTATUS },
    { "not", 1, 1, 1, PREFIX_PRIORITY, lnot, LOCALIZED_ALTERNATE_NOT },
    { "notequal?", 2, 2, 2, PREFIX_PRIORITY, lnotequalp, LOCALIZED_ALTERNATE_NOTEQUAL_ },
    { "notequalp", 2, 2, 2, PREFIX_PRIORITY, lnotequalp, LOCALIZED_ALTERNATE_NOTEQUALP },
    { "noyield", 0, 0, 0, PREFIX_PRIORITY, lnoyield, LOCALIZED_ALTERNATE_NOYIELD },
    { "numberp", 1, 1, 1, PREFIX_PRIORITY, lnumberp, LOCALIZED_ALTERNATE_NUMBERP },
    { "number?", 1, 1, 1, PREFIX_PRIORITY, lnumberp, LOCALIZED_ALTERNATE_NUMBER_ },
    { "op", 1, 1, 1, OUTPUT_PRIORITY, loutput, LOCALIZED_ALTERNATE_OP },
    { "openappend", 1, 1, 2, PREFIX_PRIORITY, lopenappend, LOCALIZED_ALTERNATE_OPENAPPEND },
    { "openread", 1, 1, 2, PREFIX_PRIORITY, lopenread, LOCALIZED_ALTERNATE_OPENREAD },
    { "openupdate", 1, 1, 2, PREFIX_PRIORITY, lopenupdate, LOCALIZED_ALTERNATE_OPENUPDATE },
    { "openwrite", 1, 1, 2, PREFIX_PRIORITY, lopenwrite, LOCALIZED_ALTERNATE_OPENWRITE },
    { "or", 0, 2, -1, PREFIX_PRIORITY, lor, LOCALIZED_ALTERNATE_OR },
    { "outport", 2, 2, 2, PREFIX_PRIORITY, loutport, LOCALIZED_ALTERNATE_OUTPORT },
    { "outportb", 2, 2, 2, PREFIX_PRIORITY, loutportb, LOCALIZED_ALTERNATE_OUTPORTB },
    { "output", 1, 1, 1, OUTPUT_PRIORITY, loutput, LOCALIZED_ALTERNATE_OUTPUT },
    { "parse", 1, 1, 1, PREFIX_PRIORITY, lparse, LOCALIZED_ALTERNATE_PARSE },
    { "pause", 0, 0, 0, PREFIX_PRIORITY, lpause, LOCALIZED_ALTERNATE_PAUSE },
    { "pc", 0, 0, 0, PREFIX_PRIORITY, lpencolor, LOCALIZED_ALTERNATE_PC },
    { "pd", 0, 0, 0, PREFIX_PRIORITY, lpendown, LOCALIZED_ALTERNATE_PD },
    { "pe", 0, 0, 0, PREFIX_PRIORITY, lpenerase, LOCALIZED_ALTERNATE_PE },
    { "pencolor", 0, 0, 0, PREFIX_PRIORITY, lpencolor, LOCALIZED_ALTERNATE_PENCOLOR },
    { "pendown", 0, 0, 0, PREFIX_PRIORITY, lpendown, LOCALIZED_ALTERNATE_PENDOWN },
    { "pendownp", 0, 0, 0, PREFIX_PRIORITY, lpendownp, LOCALIZED_ALTERNATE_PENDOWNP },
    { "pendown?", 0, 0, 0, PREFIX_PRIORITY, lpendownp, LOCALIZED_ALTERNATE_PENDOWN_ },
    { "penerase", 0, 0, 0, PREFIX_PRIORITY, lpenerase, LOCALIZED_ALTERNATE_PENERASE },
    { "penmode", 0, 0, 0, PREFIX_PRIORITY, lpenmode, LOCALIZED_ALTERNATE_PENMODE },
    { "penpaint", 0, 0, 0, PREFIX_PRIORITY, lpenpaint, LOCALIZED_ALTERNATE_PENPAINT },
    { "penpattern", 0, 0, 0, PREFIX_PRIORITY, lpenpattern, LOCALIZED_ALTERNATE_PENPATTERN },
    { "penreverse", 0, 0, 0, PREFIX_PRIORITY, lpenreverse, LOCALIZED_ALTERNATE_PENREVERSE },
    { "pensize", 0, 0, 0, PREFIX_PRIORITY, lpensize, LOCALIZED_ALTERNATE_PENSIZE },
    { "penup", 0, 0, 0, PREFIX_PRIORITY, lpenup, LOCALIZED_ALTERNATE_PENUP },
    { "perspective", 0, 0, 0, PREFIX_PRIORITY, lperspective, LOCALIZED_ALTERNATE_PERSPECTIVE },
    { "pitch", 0, 0, 0, PREFIX_PRIORITY, lpitch, LOCALIZED_ALTERNATE_PITCH },
    { "pixel", 0, 0, 0, PREFIX_PRIORITY, lpixel, LOCALIZED_ALTERNATE_PIXEL },
    { "playwave", 2, 2, 2, PREFIX_PRIORITY, lplaywave, LOCALIZED_ALTERNATE_PLAYWAVE },
    { "plist", 1, 1, 1, PREFIX_PRIORITY, lplist, LOCALIZED_ALTERNATE_PLIST },
    { "plists", 0, 0, 0, PREFIX_PRIORITY, lplists, LOCALIZED_ALTERNATE_PLISTS },
    { "po", 1, 1, 1, PREFIX_PRIORITY, lpo, LOCALIZED_ALTERNATE_PO },
    { "popdir", 0, 0, 0, PREFIX_PRIORITY, lpopdir, LOCALIZED_ALTERNATE_POPDIR },
    { "polystart", 0, 0, 0, PREFIX_PRIORITY, lpolystart, LOCALIZED_ALTERNATE_POLYSTART },
    { "polyend", 0, 0, 0, PREFIX_PRIORITY, lpolyend, LOCALIZED_ALTERNATE_POLYEND },
    { "polyview", 0, 0, 0, PREFIX_PRIORITY, lpolyview, LOCALIZED_ALTERNATE_POLYVIEW },
    { "portclose", 0, 0, 0, PREFIX_PRIORITY, lportclose, LOCALIZED_ALTERNATE_PORTCLOSE },
    { "portflush", 1, 1, 1, PREFIX_PRIORITY, lportflush, LOCALIZED_ALTERNATE_PORTFLUSH },
    { "portmode", 1, 1, 1, PREFIX_PRIORITY, lportmode, LOCALIZED_ALTERNATE_PORTMODE },
    { "portopen", 1, 1, 1, PREFIX_PRIORITY, lportopen, LOCALIZED_ALTERNATE_PORTOPEN },
    { "portreadarray", 2, 2, 2, PREFIX_PRIORITY, lportreadarray, LOCALIZED_ALTERNATE_PORTREADARRAY },
    { "portreadchar", 0, 0, 0, PREFIX_PRIORITY, lportreadchar, LOCALIZED_ALTERNATE_PORTREADCHAR },
    { "portwritearray", 2, 2, 2, PREFIX_PRIORITY, lportwritearray, LOCALIZED_ALTERNATE_PORTWRITEARRAY },
    { "portwritechar", 1, 1, 1, PREFIX_PRIORITY, lportwritechar, LOCALIZED_ALTERNATE_PORTWRITECHAR },
    { "pos", 0, 0, 0, PREFIX_PRIORITY, lpos, LOCALIZED_ALTERNATE_POS },
    { "posxyz", 0, 0, 0, PREFIX_PRIORITY, lposxyz, LOCALIZED_ALTERNATE_POSXYZ },
    { "pot", 1, 1, 1, PREFIX_PRIORITY, lpot, LOCALIZED_ALTERNATE_POT },
    { "power", 2, 2, 2, PREFIX_PRIORITY, lpower, LOCALIZED_ALTERNATE_POWER },
    { "pprop", 3, 3, 3, PREFIX_PRIORITY, lpprop, LOCALIZED_ALTERNATE_PPROP },
    { "ppt", 0, 0, 0, PREFIX_PRIORITY, lpenpaint, LOCALIZED_ALTERNATE_PPT },
    { "pr", 0, 1, -1, PREFIX_PRIORITY, lprint, LOCALIZED_ALTERNATE_PR },
    { "primitivep", 1, 1, 1, PREFIX_PRIORITY, lprimitivep, LOCALIZED_ALTERNATE_PRIMITIVEP },
    { "primitive?", 1, 1, 1, PREFIX_PRIORITY, lprimitivep, LOCALIZED_ALTERNATE_PRIMITIVE_ },
    { "print", 0, 1, -1, PREFIX_PRIORITY, lprint, LOCALIZED_ALTERNATE_PRINT },
    { "procedurep", 1, 1, 1, PREFIX_PRIORITY, lprocedurep, LOCALIZED_ALTERNATE_PROCEDUREP },
    { "procedure?", 1, 1, 1, PREFIX_PRIORITY, lprocedurep, LOCALIZED_ALTERNATE_PROCEDURE_ },
    { "proplistp", 1, 1, 1, PREFIX_PRIORITY, lproplistp, LOCALIZED_ALTERNATE_PROPLISTP },
    { "proplist?", 1, 1, 1, PREFIX_PRIORITY, lproplistp, LOCALIZED_ALTERNATE_PROPLIST_ },
    { "procedures", 0, 0, 0, PREFIX_PRIORITY, lprocedures, LOCALIZED_ALTERNATE_PROCEDURES },
    { "product", 0, 2, -1, PREFIX_PRIORITY, lmul, LOCALIZED_ALTERNATE_PRODUCT },
    { "pu", 0, 0, 0, PREFIX_PRIORITY, lpenup, LOCALIZED_ALTERNATE_PU },
    { "px", 0, 0, 0, PREFIX_PRIORITY, lpenreverse, LOCALIZED_ALTERNATE_PX },
    { "questionbox", 2, 2, 2, PREFIX_PRIORITY, lquestionbox, LOCALIZED_ALTERNATE_QUESTIONBOX },
    { "quotient", 1, 2, 2, PREFIX_PRIORITY, ldivide, LOCALIZED_ALTERNATE_QUOTIENT },
    { "radarccos", 1, 1, 1, PREFIX_PRIORITY, lradacos, LOCALIZED_ALTERNATE_RADARCCOS },
    { "radarcsin", 1, 1, 1, PREFIX_PRIORITY, lradasin, LOCALIZED_ALTERNATE_RADARCSIN },
    { "radarctan", 1, 1, 2, PREFIX_PRIORITY, lradatan, LOCALIZED_ALTERNATE_RADARCTAN },
    { "radcos", 1, 1, 1, PREFIX_PRIORITY, lradcos, LOCALIZED_ALTERNATE_RADCOS },
    { "radiobuttoncreate", 8, 8, 8, PREFIX_PRIORITY, lradiobuttoncreate, LOCALIZED_ALTERNATE_RADIOBUTTONCREATE },
    { "radiobuttonenable", 2, 2, 2, PREFIX_PRIORITY, lradiobuttonenable, LOCALIZED_ALTERNATE_RADIOBUTTONENABLE },
    { "radiobuttondelete", 1, 1, 1, PREFIX_PRIORITY, lradiobuttondelete, LOCALIZED_ALTERNATE_RADIOBUTTONDELETE },
    { "radiobuttonget", 1, 1, 1, PREFIX_PRIORITY, lradiobuttonget, LOCALIZED_ALTERNATE_RADIOBUTTONGET },
    { "radiobuttonset", 2, 2, 2, PREFIX_PRIORITY, lradiobuttonset, LOCALIZED_ALTERNATE_RADIOBUTTONSET },
    { "radsin", 1, 1, 1, PREFIX_PRIORITY, lradsin, LOCALIZED_ALTERNATE_RADSIN },
    { "radtan", 1, 1, 1, PREFIX_PRIORITY, lradtan, LOCALIZED_ALTERNATE_RADTAN },
    { "random", 1, 1, 1, PREFIX_PRIORITY, lrandom, LOCALIZED_ALTERNATE_RANDOM },
    { "rawascii", 1, 1, 1, PREFIX_PRIORITY, lrawascii, LOCALIZED_ALTERNATE_RAWASCII },
    { "rc", 0, 0, 0, PREFIX_PRIORITY, lreadchar, LOCALIZED_ALTERNATE_RC },
    { "rcs", 1, 1, 1, PREFIX_PRIORITY, lreadchars, LOCALIZED_ALTERNATE_RCS },
    { "readchar", 0, 0, 0, PREFIX_PRIORITY, lreadchar, LOCALIZED_ALTERNATE_READCHAR },
    { "readchars", 1, 1, 1, PREFIX_PRIORITY, lreadchars, LOCALIZED_ALTERNATE_READCHARS },
    { "reader", 0, 0, 0, PREFIX_PRIORITY, lreader, LOCALIZED_ALTERNATE_READER },
    { "readlist", 0, 0, 0, PREFIX_PRIORITY, lreadlist, LOCALIZED_ALTERNATE_READLIST },
    { "readpos", 0, 0, 0, PREFIX_PRIORITY, lreadpos, LOCALIZED_ALTERNATE_READPOS },
    { "readrawline", 0, 0, 0, PREFIX_PRIORITY, lreadrawline, LOCALIZED_ALTERNATE_READRAWLINE },
    { "readword", 0, 0, 0, PREFIX_PRIORITY, lreadword, LOCALIZED_ALTERNATE_READWORD },
    { "remainder", 2, 2, 2, PREFIX_PRIORITY, lremainder, LOCALIZED_ALTERNATE_REMAINDER },
    { "remprop", 2, 2, 2, PREFIX_PRIORITY, lremprop, LOCALIZED_ALTERNATE_REMPROP },
    { "repcount", 0, 0, 0, PREFIX_PRIORITY, lrepcount, LOCALIZED_ALTERNATE_REPCOUNT },
    { "repeat", 2, 2, 2, MACRO_PRIORITY, lrepeat, LOCALIZED_ALTERNATE_REPEAT },
    { "rerandom", 0, 0, 1, PREFIX_PRIORITY, lrerandom, LOCALIZED_ALTERNATE_RERANDOM },
    { "right", 1, 1, 1, PREFIX_PRIORITY, lright, LOCALIZED_ALTERNATE_RIGHT },
    { "rightroll", 1, 1, 1, PREFIX_PRIORITY, lrightroll, LOCALIZED_ALTERNATE_RIGHTROLL },
    { "rl", 0, 0, 0, PREFIX_PRIORITY, lreadlist, LOCALIZED_ALTERNATE_RL },
    { "rmdir", 1, 1, 1, PREFIX_PRIORITY, lrmdir, LOCALIZED_ALTERNATE_RMDIR },
    { "roll", 0, 0, 0, PREFIX_PRIORITY, lroll, LOCALIZED_ALTERNATE_ROLL },
    { "round", 1, 1, 1, PREFIX_PRIORITY, lround, LOCALIZED_ALTERNATE_ROUND },
    { "rr", 1, 1, 1, PREFIX_PRIORITY, lrightroll, LOCALIZED_ALTERNATE_RR },
    { "rt", 1, 1, 1, PREFIX_PRIORITY, lright, LOCALIZED_ALTERNATE_RT },
    { "run", 1, 1, 1, MACRO_PRIORITY, lrun, LOCALIZED_ALTERNATE_RUN },
    { "runparse", 1, 1, 1, PREFIX_PRIORITY, lrunparse, LOCALIZED_ALTERNATE_RUNPARSE },
    { "runresult", 1, 1, 1, MACRO_PRIORITY, lrunresult, LOCALIZED_ALTERNATE_RUNRESULT },
    { "rw", 0, 0, 0, PREFIX_PRIORITY, lreadword, LOCALIZED_ALTERNATE_RW },
    { "save", 1, 1, 1, PREFIX_PRIORITY, lsave, LOCALIZED_ALTERNATE_SAVE },
    { "screencolor", 0, 0, 0, PREFIX_PRIORITY, lscreencolor, LOCALIZED_ALTERNATE_SCREENCOLOR },
    { "scrollbarcreate", 7, 7, 7, PREFIX_PRIORITY, lscrollbarcreate, LOCALIZED_ALTERNATE_SCROLLBARCREATE },
    { "scrollbarenable", 2, 2, 2, PREFIX_PRIORITY, lscrollbarenable, LOCALIZED_ALTERNATE_SCROLLBARENABLE },
    { "scrollbardelete", 1, 1, 1, PREFIX_PRIORITY, lscrollbardelete, LOCALIZED_ALTERNATE_SCROLLBARDELETE },
    { "scrollbarget", 1, 1, 1, PREFIX_PRIORITY, lscrollbarget, LOCALIZED_ALTERNATE_SCROLLBARGET },
    { "scrollbarset", 4, 4, 4, PREFIX_PRIORITY, lscrollbarset, LOCALIZED_ALTERNATE_SCROLLBARSET },
    { "scrollx", 1, 1, 1, PREFIX_PRIORITY, lscrollx, LOCALIZED_ALTERNATE_SCROLLX },
    { "scrolly", 1, 1, 1, PREFIX_PRIORITY, lscrolly, LOCALIZED_ALTERNATE_SCROLLY },
    { "scrunch", 0, 0, 0, PREFIX_PRIORITY, lscrunch, LOCALIZED_ALTERNATE_SCRUNCH },
    { "se", 0, 2, -1, PREFIX_PRIORITY, lsentence, LOCALIZED_ALTERNATE_SE },
    { "selectbox", 2, 2, 2, PREFIX_PRIORITY, lselectbox, LOCALIZED_ALTERNATE_SELECTBOX },
    { "sentence", 0, 2, -1, PREFIX_PRIORITY, lsentence, LOCALIZED_ALTERNATE_SENTENCE },
    { "setactivearea", 1, 1, 1, PREFIX_PRIORITY, lsetactivearea, LOCALIZED_ALTERNATE_SETACTIVEAREA },
    { "setbitindex", 1, 1, 1, PREFIX_PRIORITY, lsetbitindex, LOCALIZED_ALTERNATE_SETBITINDEX },
    { "setbitmode", 1, 1, 1, PREFIX_PRIORITY, lsetbitmode, LOCALIZED_ALTERNATE_SETBITMODE },
    { "setclip", 3, 3, 3, PREFIX_PRIORITY, lsetclip, LOCALIZED_ALTERNATE_SETCLIP },
    // { "setcursor", 1, 1, 1, PREFIX_PRIORITY, lsetcursor, LOCALIZED_ALTERNATE_SETCURSOR },
    { "setcursornowait", 0, 0, 0, PREFIX_PRIORITY, lsetcursorarrow, LOCALIZED_ALTERNATE_SETCURSORNOWAIT },
    { "setcursorwait", 0, 0, 0, PREFIX_PRIORITY, lsetcursorwait, LOCALIZED_ALTERNATE_SETCURSORWAIT },
    { "setfc", 1, 1, 1, PREFIX_PRIORITY, lsetfloodcolor, LOCALIZED_ALTERNATE_SETFC },
    { "setfloodcolor", 1, 1, 1, PREFIX_PRIORITY, lsetfloodcolor, LOCALIZED_ALTERNATE_SETFLOODCOLOR },
    { "setfocus", 1, 1, 1, PREFIX_PRIORITY, lsetfocus, LOCALIZED_ALTERNATE_SETFOCUS },
    { "seth", 1, 1, 1, PREFIX_PRIORITY, lsetheading, LOCALIZED_ALTERNATE_SETH },
    { "setheading", 1, 1, 1, PREFIX_PRIORITY, lsetheading, LOCALIZED_ALTERNATE_SETHEADING },
    { "setitem", 3, 3, 3, PREFIX_PRIORITY, lsetitem, LOCALIZED_ALTERNATE_SETITEM },
    { "setlabelfont", 1, 1, 1, PREFIX_PRIORITY, lsetlabelfont, LOCALIZED_ALTERNATE_SETLABELFONT },
    { "setlight", 1, 1, 1, PREFIX_PRIORITY, lsetlight, LOCALIZED_ALTERNATE_SETLIGHT },
    { "setmargins", 1, 1, 1, PREFIX_PRIORITY, lsetmargins, LOCALIZED_ALTERNATE_SETMARGINS },
    { "setpc", 1, 1, 1, PREFIX_PRIORITY, lsetpencolor, LOCALIZED_ALTERNATE_SETPC },
    { "setpencolor", 1, 1, 1, PREFIX_PRIORITY, lsetpencolor, LOCALIZED_ALTERNATE_SETPENCOLOR },
    { "setpenpattern", 1, 1, 1, PREFIX_PRIORITY, lsetpenpattern, LOCALIZED_ALTERNATE_SETPENPATTERN },
    { "setpensize", 1, 1, 1, PREFIX_PRIORITY, lsetpensize, LOCALIZED_ALTERNATE_SETPENSIZE },
    { "setpitch", 1, 1, 1, PREFIX_PRIORITY, lsetpitch, LOCALIZED_ALTERNATE_SETPITCH },
    { "setpixel", 1, 1, 1, PREFIX_PRIORITY, lsetpixel, LOCALIZED_ALTERNATE_SETPIXEL },
    { "setpos", 1, 1, 1, PREFIX_PRIORITY, lsetpos, LOCALIZED_ALTERNATE_SETPOS },
    { "setposxyz", 1, 1, 1, PREFIX_PRIORITY, lsetposxyz, LOCALIZED_ALTERNATE_SETPOSXYZ },
    { "setread", 1, 1, 1, PREFIX_PRIORITY, lsetread, LOCALIZED_ALTERNATE_SETREAD },
    { "setreadpos", 1, 1, 1, PREFIX_PRIORITY, lsetreadpos, LOCALIZED_ALTERNATE_SETREADPOS },
    { "setroll", 1, 1, 1, PREFIX_PRIORITY, lsetroll, LOCALIZED_ALTERNATE_SETROLL },
    { "setsc", 1, 1, 1, PREFIX_PRIORITY, lsetscreencolor, LOCALIZED_ALTERNATE_SETSC },
    { "setscreencolor", 1, 1, 1, PREFIX_PRIORITY, lsetscreencolor, LOCALIZED_ALTERNATE_SETSCREENCOLOR },
    { "setscrunch", 2, 2, 2, PREFIX_PRIORITY, lsetscrunch, LOCALIZED_ALTERNATE_SETSCRUNCH },
    { "settimer", 3, 3, 3, PREFIX_PRIORITY, lsettimer, LOCALIZED_ALTERNATE_SETTIMER },
    { "setturtle", 1, 1, 2, PREFIX_PRIORITY, lsetturtle, LOCALIZED_ALTERNATE_SETTURTLE },
    { "setturtlemode", 1, 1, 1, PREFIX_PRIORITY, lsetturtlemode, LOCALIZED_ALTERNATE_SETTURTLEMODE },
    { "setwrite", 1, 1, 1, PREFIX_PRIORITY, lsetwrite, LOCALIZED_ALTERNATE_SETWRITE },
    { "setwritepos", 1, 1, 1, PREFIX_PRIORITY, lsetwritepos, LOCALIZED_ALTERNATE_SETWRITEPOS },
    { "setx", 1, 1, 1, PREFIX_PRIORITY, lsetx, LOCALIZED_ALTERNATE_SETX },
    { "setxy", 2, 2, 2, PREFIX_PRIORITY, lsetxy, LOCALIZED_ALTERNATE_SETXY },
    { "setxyz", 3, 3, 3, PREFIX_PRIORITY, lsetxyz, LOCALIZED_ALTERNATE_SETXYZ },
    { "sety", 1, 1, 1, PREFIX_PRIORITY, lsety, LOCALIZED_ALTERNATE_SETY },
    { "setz", 1, 1, 1, PREFIX_PRIORITY, lsetz, LOCALIZED_ALTERNATE_SETZ },
    { "shell", 1, 1, 2, PREFIX_PRIORITY, lshell, LOCALIZED_ALTERNATE_SHELL },
    { "show", 0, 1, -1, PREFIX_PRIORITY, lshow, LOCALIZED_ALTERNATE_SHOW },
    { "shownp", 0, 0, 0, PREFIX_PRIORITY, lshownp, LOCALIZED_ALTERNATE_SHOWNP },
    { "shown?", 0, 0, 0, PREFIX_PRIORITY, lshownp, LOCALIZED_ALTERNATE_SHOWN_ },
    { "showturtle", 0, 0, 0, PREFIX_PRIORITY, lshowturtle, LOCALIZED_ALTERNATE_SHOWTURTLE },
    { "sin", 1, 1, 1, PREFIX_PRIORITY, lsin, LOCALIZED_ALTERNATE_SIN },
    { "sound", 1, 1, 1, PREFIX_PRIORITY, lsound, LOCALIZED_ALTERNATE_SOUND },
    { "splitscreen", 0, 0, 0, PREFIX_PRIORITY, lsplitscreen, LOCALIZED_ALTERNATE_SPLITSCREEN },
    { "sqrt", 1, 1, 1, PREFIX_PRIORITY, lsqrt, LOCALIZED_ALTERNATE_SQRT },
    { "ss", 0, 0, 0, PREFIX_PRIORITY, lsplitscreen, LOCALIZED_ALTERNATE_SS },
    { "st", 0, 0, 0, PREFIX_PRIORITY, lshowturtle, LOCALIZED_ALTERNATE_ST },
    { "standout", 1, 1, 1, PREFIX_PRIORITY, lstandout, LOCALIZED_ALTERNATE_STANDOUT },
    { "staticcreate", 7, 7, 7, PREFIX_PRIORITY, lstaticcreate, LOCALIZED_ALTERNATE_STATICCREATE },
    { "staticdelete", 1, 1, 1, PREFIX_PRIORITY, lstaticdelete, LOCALIZED_ALTERNATE_STATICDELETE },
    { "staticupdate", 2, 2, 2, PREFIX_PRIORITY, lstaticupdate, LOCALIZED_ALTERNATE_STATICUPDATE },
    { "status", 0, 0, 0, PREFIX_PRIORITY, lstatus, LOCALIZED_ALTERNATE_STATUS },
    { "step", 1, 1, 1, PREFIX_PRIORITY, lstep, LOCALIZED_ALTERNATE_STEP },
    { "stepped", 0, 0, 0, PREFIX_PRIORITY, lstepped, LOCALIZED_ALTERNATE_STEPPED },
    { "stop", 0, 0, 0, STOP_PRIORITY, lstop, LOCALIZED_ALTERNATE_STOP },
    { "substringp", 2, 2, 2, PREFIX_PRIORITY, lsubstringp, LOCALIZED_ALTERNATE_SUBSTRINGP },
    { "substring?", 2, 2, 2, PREFIX_PRIORITY, lsubstringp, LOCALIZED_ALTERNATE_SUBSTRING_ },
    { "sum", 0, 2, -1, PREFIX_PRIORITY, ladd, LOCALIZED_ALTERNATE_SUM },
    // { "tag", 1, 1, 1, PREFIX_PRIORITY, ltag, LOCALIZED_ALTERNATE_TAG },
    { "tan", 1, 1, 1, PREFIX_PRIORITY, ltan, LOCALIZED_ALTERNATE_TAN },
    { "test", 1, 1, 1, PREFIX_PRIORITY, ltest, LOCALIZED_ALTERNATE_TEST },
    { "text", 1, 1, 1, PREFIX_PRIORITY, ltext, LOCALIZED_ALTERNATE_TEXT },
    { "textscreen", 0, 0, 0, PREFIX_PRIORITY, ltextscreen, LOCALIZED_ALTERNATE_TEXTSCREEN },
    { "thing", 1, 1, 1, PREFIX_PRIORITY, lthing, LOCALIZED_ALTERNATE_THING },
    { "throw", 1, 1, 3, PREFIX_PRIORITY, lthrow, LOCALIZED_ALTERNATE_THROW },
    { "time", 0, 0, 0, PREFIX_PRIORITY, ltime, LOCALIZED_ALTERNATE_TIME },
    { "timemilli", 0, 0, 0, PREFIX_PRIORITY, ltimemilli, LOCALIZED_ALTERNATE_TIMEMILLI },
    { "to", -1, -1, -1, PREFIX_PRIORITY, lto, LOCALIZED_ALTERNATE_TO },
    { "tone", 2, 2, 2, PREFIX_PRIORITY, ltone, LOCALIZED_ALTERNATE_TONE },
    { "towards", 1, 1, 1, PREFIX_PRIORITY, ltowards, LOCALIZED_ALTERNATE_TOWARDS },
    { "towardsxyz", 1, 1, 1, PREFIX_PRIORITY, ltowardsxyz, LOCALIZED_ALTERNATE_TOWARDSXYZ },
    { "trace", 1, 1, 1, PREFIX_PRIORITY, ltrace, LOCALIZED_ALTERNATE_TRACE },
    { "traced", 0, 0, 0, PREFIX_PRIORITY, ltraced, LOCALIZED_ALTERNATE_TRACED },
    { "ts", 0, 0, 0, PREFIX_PRIORITY, ltextscreen, LOCALIZED_ALTERNATE_TS },
    { "turtle", 0, 0, 0, PREFIX_PRIORITY, lturtle, LOCALIZED_ALTERNATE_TURTLE },
    { "turtlemode", 0, 0, 0, PREFIX_PRIORITY, lturtlemode, LOCALIZED_ALTERNATE_TURTLEMODE },
    { "turtles", 0, 0, 0, PREFIX_PRIORITY, lturtles, LOCALIZED_ALTERNATE_TURTLES },
    { "type", 0, 1, -1, PREFIX_PRIORITY, ltype, LOCALIZED_ALTERNATE_TYPE },
    { "unbury", 1, 1, 1, PREFIX_PRIORITY, lunbury, LOCALIZED_ALTERNATE_UNBURY },
    { "unstep", 1, 1, 1, PREFIX_PRIORITY, lunstep, LOCALIZED_ALTERNATE_UNSTEP },
    { "untrace", 1, 1, 1, PREFIX_PRIORITY, luntrace, LOCALIZED_ALTERNATE_UNTRACE },
    { "up", 1, 1, 1, PREFIX_PRIORITY, luppitch, LOCALIZED_ALTERNATE_UP },
    { "uppercase", 1, 1, 1, PREFIX_PRIORITY, luppercase, LOCALIZED_ALTERNATE_UPPERCASE },
    { "uppitch", 1, 1, 1, PREFIX_PRIORITY, luppitch, LOCALIZED_ALTERNATE_UPPITCH },
    { "wait", 1, 1, 1, PREFIX_PRIORITY, lwait, LOCALIZED_ALTERNATE_WAIT },
    { "window", 0, 0, 0, PREFIX_PRIORITY, lwindow, LOCALIZED_ALTERNATE_WINDOW },
    { "windowcreate", 8, 8, 8, PREFIX_PRIORITY, lwindowcreate, LOCALIZED_ALTERNATE_WINDOWCREATE },
    { "windowenable", 2, 2, 2, PREFIX_PRIORITY, lwindowenable, LOCALIZED_ALTERNATE_WINDOWENABLE },
    { "windowdelete", 1, 1, 1, PREFIX_PRIORITY, lwindowdelete, LOCALIZED_ALTERNATE_WINDOWDELETE },
    { "windowfileedit", 2, 2, 2, PREFIX_PRIORITY, lwindowfileedit, LOCALIZED_ALTERNATE_WINDOWFILEEDIT },
    { "windowset", 2, 2, 2, PREFIX_PRIORITY, lwindowset, LOCALIZED_ALTERNATE_WINDOWSET },
    { "winhelp", 1, 1, 2, PREFIX_PRIORITY, lwinhelp, LOCALIZED_ALTERNATE_WINHELP },
    { "word", 0, 2, -1, PREFIX_PRIORITY, lword, LOCALIZED_ALTERNATE_WORD },
    { "wordp", 1, 1, 1, PREFIX_PRIORITY, lwordp, LOCALIZED_ALTERNATE_WORDP },
    { "word?", 1, 1, 1, PREFIX_PRIORITY, lwordp, LOCALIZED_ALTERNATE_WORD_ },
    { "wrap", 0, 0, 0, PREFIX_PRIORITY, lwrap, LOCALIZED_ALTERNATE_WRAP },
    { "writepos", 0, 0, 0, PREFIX_PRIORITY, lwritepos, LOCALIZED_ALTERNATE_WRITEPOS },
    { "writer", 0, 0, 0, PREFIX_PRIORITY, lwriter, LOCALIZED_ALTERNATE_WRITER },
    { "yesnobox", 2, 2, 2, PREFIX_PRIORITY, lyesnobox, LOCALIZED_ALTERNATE_YESNOBOX },
    { "yield", 0, 0, 0, PREFIX_PRIORITY, lyield, LOCALIZED_ALTERNATE_YIELD },
    { "zoom", 1, 1, 1, PREFIX_PRIORITY, lzoom, LOCALIZED_ALTERNATE_ZOOM },
};

static
void
intern_primitive(
    const char * Name,
    short        MinimumArgs,
    short        DefaultArgs,
    short        MaximumArgs,
    short        Priority,
    logofunc     Primitive
    )
{
    NODE *proc;
    if (Priority == MACRO_PRIORITY)
    {
        proc = vref(newnode(MACRO));
    }
    else if (Priority <= TAIL_PRIORITY)
    {
        // .MAYBEOUTPUT, OUTPUT, or STOP.
        proc = vref(newnode(TAILFORM));
    }
    else if ((Priority & ~4) == (PREFIX_PRIORITY & ~4))
    {
        proc = vref(newnode(PRIM)); // include "--"
    }
    else
    {
        proc = vref(newnode(INFIX));
    }
   
    setprimpri(proc,  Priority);
    setprimfun(proc,  Primitive);
    setprimdflt(proc, DefaultArgs);
    setprimmax(proc,  MaximumArgs);
    setprimmin(proc,  MinimumArgs);

    NODE * primitive_name = vref(make_static_strnode(Name));
    NODE * lowercase_name = vref(make_lowercase_strnode_from_strnode(primitive_name));
    NODE * case_node      = vref(make_instance(primitive_name, lowercase_name));
    setprocnode__caseobj(case_node, proc);

    if (nodetype(proc) == MACRO)
    {
        setflag__caseobj(case_node, PROC_MACRO);
    }

    deref(proc);
    deref(case_node);
    deref(primitive_name);
    deref(lowercase_name);
}


// Initialize the language engine and all associated variables.
void init()
{
    fill_reserve_tank();
    Unbound = newnode(PUNBOUND);

    init_ecma_array();
   
    // intern all of the primitives.
    //
    // We intern all of the English forms first so if there
    // are conflicts between an English command and a localized command,
    // the localized one will win.  For example, in the French version,
    // we want "ct" to mean "cachetortue" (HIDETURTLE), not "CLEARTEXT",
    // even though all other locales will use "ct" to mean "CLEARTEXT".
    // 

    // intern all of the primitives by their English name
    for (int i = 0; i < ARRAYSIZE(prims); i++)
    {
        // intern the current primitive
        intern_primitive(
            prims[i].name,
            prims[i].minargs,
            prims[i].defargs,
            prims[i].maxargs,
            prims[i].priority,
            prims[i].prim);
    }

    // Now intern the commands by their localized name
    for (int i = 0; i < ARRAYSIZE(prims); i++)
    {
        // If there is an alternate name for the primitive,
        // and it's different from the normal name, make a
        // primivite out of it, too.
        if (prims[i].alternatename != NULL && 
            0 != strcmp(prims[i].name, prims[i].alternatename))
        {
            intern_primitive(
                prims[i].alternatename,
                prims[i].minargs,
                prims[i].defargs,
                prims[i].maxargs,
                prims[i].priority,
                prims[i].prim);
        }
    }


    Truex.Initialize("true",   LOCALIZED_ALTERNATE_TRUE);
    Falsex.Initialize("false", LOCALIZED_ALTERNATE_FALSE);
    To.Initialize("to",        LOCALIZED_ALTERNATE_TO);
    End.Initialize("end",      LOCALIZED_ALTERNATE_END);

    Toplevel.Initialize("toplevel",  LOCALIZED_ALTERNATE_TOPLEVEL);
    System.Initialize("system",      LOCALIZED_ALTERNATE_SYSTEM);
    Error.Initialize("error",        LOCALIZED_ALTERNATE_ERROR);

    Left_Paren = intern(make_static_strnode("("));
    Right_Paren = intern(make_static_strnode(")"));
    Minus_Sign = intern(make_static_strnode("-"));
    Minus_Tight = intern(make_static_strnode("--"));
    Query = intern(make_static_strnode("?"));
    Null_Word = intern(make_static_strnode(""));
    Macro = intern(make_static_strnode(".macro"));
    If = intern(make_static_strnode("if"));
    Ifelse = intern(make_static_strnode("ifelse"));
    Redefp.Initialize("redefp",                   LOCALIZED_ALTERNATE_REDEFP);
    Caseignoredp.Initialize("caseignoredp",       LOCALIZED_ALTERNATE_CASEIGNOREDP);
    Erract.Initialize("erract",                   LOCALIZED_ALTERNATE_ERRACT);
    Printdepthlimit.Initialize("printdepthlimit", LOCALIZED_ALTERNATE_PRINTDEPTHLIMIT);
    Printwidthlimit.Initialize("printwidthlimit", LOCALIZED_ALTERNATE_PRINTWIDTHLIMIT);
    Pause = intern(make_static_strnode("pause"));
    Startup.Initialize("startup",           LOCALIZED_ALTERNATE_STARTUP);
    Output = intern(make_static_strnode("output"));
    Stop = intern(make_static_strnode("stop"));
    Goto = intern(make_static_strnode("goto"));
    Tag = intern(make_static_strnode("Tag"));
    the_generation = vref(cons_list(NIL));   // some unique pointer
    Not_Enough_Node = vref(cons_list(NIL));  // some unique pointer

    repcountup = -1;
}

void uninit()
{
    // uninitialize the network subsystem
    lnetshutdown(NIL);

    // uninitialize the file subsystem
    uninitialize_files();

    deref(Not_Enough_Node);
    deref(the_generation);

    // free the nodes associated with error handling
    uninitialize_error();

    // free the state associated with the evaluator
    uninitialize_eval();

    // free the state associated with the windowing subsystem
    uninitialize_windows();

    // free the objects
    release_all_objects();

    // free our reserve tank of nodes
    use_reserve_tank();

    // free all outstanding nodes
    free_segment_list();

    // free the parser
    uninitialize_parser();

    // free the internal buffer for the combobox
    uninitialize_combobox();
   
    // free the memory associated with keyboard capture
    keyboard_uninit();

    // free the memory associated with mouse capture
    mouse_uninit();

    // free the state associated with the timer events
    uninitialize_timers();
}
