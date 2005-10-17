/*
*      init.c     logo init module                      dvb
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

#include "allwind.h"

typedef struct priminfo {
   char *name;
   short minargs;
   short defargs;
   short maxargs;
   short priority;
   NODE * (*prim) (NODE *); }
PRIMTYPE;

typedef NODE * (*lexone) (NODE *);
typedef NODE * (*lexzer)();

NODE *Truex, *Falsex, *Right_Paren, *Left_Paren, *Toplevel, *System, *Error,
*End, *Redefp, *Caseignoredp, *Erract, *Printdepthlimit,
*Printwidthlimit, *Pause,
*If, *Ifelse, *To, *Macro, *Unbound, *Not_Enough_Node,
*Minus_Sign, *Minus_Tight, *Startup, *Query, *Output, *Op, *Stop, *Goto, *Tag;
NODE *Null_Word = NIL;

PRIMTYPE far prims[] =
   {
      { "*", 1, 1, 1, PREFIX_PRIORITY + 3, (lexone) lmul },
      { "+", 1, 1, 1, PREFIX_PRIORITY + 2, (lexone) ladd },
      { "-", 1, 1, 1, PREFIX_PRIORITY + 2, (lexone) lsub },
      { "--", 1, 1, 1, PREFIX_PRIORITY + 4, (lexone) lsub },
      { ".defmacro", 2, 2, 2, PREFIX_PRIORITY, (lexone) ldefmacro },
      { ".eq", 2, 2, 2, PREFIX_PRIORITY, (lexone) l_eq },
      { ".macro", -1, -1, -1, PREFIX_PRIORITY, (lexone) lmacro },
      { ".maybeoutput", 1, 1, 1, TAIL_PRIORITY, (lexone) loutput },
      { ".setbf", 2, 2, 2, PREFIX_PRIORITY, (lexone) l_setbf },
      { ".setfirst", 2, 2, 2, PREFIX_PRIORITY, (lexone) l_setfirst },
      { ".setitem", 3, 3, 3, PREFIX_PRIORITY, (lexone) l_setitem },
      { "/", 1, 1, 1, PREFIX_PRIORITY + 3, (lexone) ldivide },
      { "<", 2, 2, 2, PREFIX_PRIORITY + 1, (lexone) llessp },
      { "=", 2, 2, 2, PREFIX_PRIORITY + 1, (lexone) lequalp },
      { ">", 2, 2, 2, PREFIX_PRIORITY + 1, (lexone) lgreaterp },
      { "?", 0, 0, 1, PREFIX_PRIORITY, (lexone) lqm },
      { "activearea", 0, 0, 0, PREFIX_PRIORITY, (lexone) lactivearea },
      { "allopen", 0, 0, 0, PREFIX_PRIORITY, (lexone) lallopen },
      { "and", 0, 2, -1, PREFIX_PRIORITY, (lexone) land },
      { "apply", 2, 2, 2, MACRO_PRIORITY, (lexone) lapply },
      { "arccos", 1, 1, 1, PREFIX_PRIORITY, (lexone) lacos },
      { "arcsin", 1, 1, 1, PREFIX_PRIORITY, (lexone) lasin },
      { "arctan", 1, 1, 2, PREFIX_PRIORITY, (lexone) latan },
      { "array", 1, 1, 2, PREFIX_PRIORITY, (lexone) larray },
      { "arrayp", 1, 1, 1, PREFIX_PRIORITY, (lexone) larrayp },
      { "array?", 1, 1, 1, PREFIX_PRIORITY, (lexone) larrayp },
      { "ascii", 1, 1, 1, PREFIX_PRIORITY, (lexone) lascii },
      { "ashift", 2, 2, 2, PREFIX_PRIORITY, (lexone) lashift },
      { "back", 1, 1, 1, PREFIX_PRIORITY, (lexone) lback },
      { "backslashedp", 1, 1, 1, PREFIX_PRIORITY, (lexone) lbackslashedp },
      { "backslashed?", 1, 1, 1, PREFIX_PRIORITY, (lexone) lbackslashedp },
      { "beforep", 2, 2, 2, PREFIX_PRIORITY, (lexone) lbeforep },
      { "before?", 2, 2, 2, PREFIX_PRIORITY, (lexone) lbeforep },
      { "bf", 1, 1, 1, PREFIX_PRIORITY, (lexone) lbutfirst },
      { "bfs", 1, 1, 1, PREFIX_PRIORITY, (lexone) lbfs },
      { "bitand", 0, 2, -1, PREFIX_PRIORITY, (lexone) lbitand },
      { "bitblock", 2, 2, 2, PREFIX_PRIORITY, (lexone) lbitblock },
      { "bitcopy", 2, 2, 2, PREFIX_PRIORITY, (lexone) lbitcopy },
      { "bitcut", 2, 2, 2, PREFIX_PRIORITY, (lexone) lbitcut },
      { "bitfit", 2, 2, 2, PREFIX_PRIORITY, (lexone) lbitfit },
      { "bitindex", 0, 0, 0, PREFIX_PRIORITY, (lexone) lbitindex },
      { "bitload", 1, 1, 1, PREFIX_PRIORITY, (lexone) lbitload },
      { "bitloadsize", 1, 1, 1, PREFIX_PRIORITY, (lexone) lbitloadsize },
      { "bitsize", 0, 0, 0, PREFIX_PRIORITY, (lexone) lbitsize },
      { "bitmapturtle", 0, 0, 0, PREFIX_PRIORITY, (lexone) lbitmapturtle },
      { "bitmode", 0, 0, 0, PREFIX_PRIORITY, (lexone) lbitmode },
      { "bitnot", 1, 1, 1, PREFIX_PRIORITY, (lexone) lbitnot },
      { "bitor", 0, 2, -1, PREFIX_PRIORITY, (lexone) lbitor },
      { "bitpaste", 0, 0, 0, PREFIX_PRIORITY, (lexone) lbitpaste },
      { "bitpastetoindex", 3, 3, 3, PREFIX_PRIORITY, (lexone) lbitpastetoindex },
      { "bitsave", 1, 1, 2, PREFIX_PRIORITY, (lexone) lbitsave },
      { "bitxor", 0, 2, -1, PREFIX_PRIORITY, (lexone) lbitxor },
      { "bk", 1, 1, 1, PREFIX_PRIORITY, (lexone) lback },
      { "bl", 1, 1, 1, PREFIX_PRIORITY, (lexone) lbutlast },
      { "buried", 0, 0, 0, PREFIX_PRIORITY, (lexone) lburied },
      { "bury", 1, 1, 1, PREFIX_PRIORITY, (lexone) lbury },
      { "butfirst", 1, 1, 1, PREFIX_PRIORITY, (lexone) lbutfirst },
      { "butfirsts", 1, 1, 1, PREFIX_PRIORITY, (lexone) lbfs },
      { "butlast", 1, 1, 1, PREFIX_PRIORITY, (lexone) lbutlast },
      { "buttoncreate", 8, 8, 8, PREFIX_PRIORITY, (lexone) lbuttoncreate },
      { "buttondelete", 1, 1, 1, PREFIX_PRIORITY, (lexone) lbuttondelete },
      { "buttonenable", 2, 2, 2, PREFIX_PRIORITY, (lexone) lbuttonenable },
      { "buttonupdate", 2, 2, 2, PREFIX_PRIORITY, (lexone) lbuttonupdate },
      { "buttonp", 0, 0, 0, PREFIX_PRIORITY, (lexone) lbuttonp },
      { "button?", 0, 0, 0, PREFIX_PRIORITY, (lexone) lbuttonp },
      { "bye", 0, 0, 0, PREFIX_PRIORITY, (lexone) lbye },
      { "catch", 2, 2, 2, MACRO_PRIORITY, (lexone) lcatch },
      { "char", 1, 1, 1, PREFIX_PRIORITY, (lexone) lchar },
      { "chdir", 1, 1, 1, PREFIX_PRIORITY, (lexone) lpushdir },
      { "checkboxcreate", 8, 8, 8, PREFIX_PRIORITY, (lexone) lcheckboxcreate },
      { "checkboxdelete", 1, 1, 1, PREFIX_PRIORITY, (lexone) lcheckboxdelete },
      { "checkboxenable", 2, 2, 2, PREFIX_PRIORITY, (lexone) lcheckboxenable },
      { "checkboxget", 1, 1, 1, PREFIX_PRIORITY, (lexone) lcheckboxget },
      { "checkboxset", 2, 2, 2, PREFIX_PRIORITY, (lexone) lcheckboxset },
      { "clean", 0, 0, 0, PREFIX_PRIORITY, (lexone) lclean },
      { "clearpalette", 0, 0, 0, PREFIX_PRIORITY, (lexone) lclearpalette },
      { "clearscreen", 0, 0, 0, PREFIX_PRIORITY, (lexone) lclearscreen },
      { "cleartext", 0, 0, 0, PREFIX_PRIORITY, (lexone) lcleartext },
      { "cleartimer", 1, 1, 1, PREFIX_PRIORITY, (lexone) lcleartimer },
      { "close", 1, 1, 1, PREFIX_PRIORITY, (lexone) lclose },
      { "co", OK_NO_ARG, 1, 1, PREFIX_PRIORITY, (lexone) lcontinue },
      { "comboboxaddstring", 2, 2, 2, PREFIX_PRIORITY, (lexone) lcomboboxaddstring },
      { "comboboxcreate", 6, 6, 6, PREFIX_PRIORITY, (lexone) lcomboboxcreate },
      { "comboboxdelete", 1, 1, 1, PREFIX_PRIORITY, (lexone) lcomboboxdelete },
      { "comboboxenable", 2, 2, 2, PREFIX_PRIORITY, (lexone) lcomboboxenable },
      { "comboboxdeletestring", 2, 2, 2, PREFIX_PRIORITY, (lexone) lcomboboxdeletestring },
      { "comboboxgettext", 1, 1, 1, PREFIX_PRIORITY, (lexone) lcomboboxgettext },
      { "comboboxsettext", 2, 2, 2, PREFIX_PRIORITY, (lexone) lcomboboxsettext },
      { "contents", 0, 0, 0, PREFIX_PRIORITY, (lexone) lcontents },
      { "continue", OK_NO_ARG, 1, 1, PREFIX_PRIORITY, (lexone) lcontinue },
      { "copydef", 2, 2, 2, PREFIX_PRIORITY, (lexone) lcopydef },
      { "cos", 1, 1, 1, PREFIX_PRIORITY, (lexone) lcos },
      { "count", 1, 1, 1, PREFIX_PRIORITY, (lexone) lcount },
      { "cs", 0, 0, 0, PREFIX_PRIORITY, (lexone) lclearscreen },
      { "ct", 0, 0, 0, PREFIX_PRIORITY, (lexone) lcleartext },
      { "cursor", 0, 0, 0, PREFIX_PRIORITY, (lexone) lcursor },
      { "debugwindows", 0, 0, 1, PREFIX_PRIORITY, (lexone) ldebugwindows },
      { "define", 2, 2, 2, PREFIX_PRIORITY, (lexone) ldefine },
      { "definedp", 1, 1, 1, PREFIX_PRIORITY, (lexone) ldefinedp },
      { "defined?", 1, 1, 1, PREFIX_PRIORITY, (lexone) ldefinedp },
      { "dialogcreate", 8, 8, 8, PREFIX_PRIORITY, (lexone) ldialogcreate },
      { "dialogenable", 2, 2, 2, PREFIX_PRIORITY, (lexone) ldialogenable },
      { "dialogdelete", 1, 1, 1, PREFIX_PRIORITY, (lexone) ldialogdelete },
      { "dialogfileopen", 1, 1, 1, PREFIX_PRIORITY, (lexone) ldialogfileopen },
      { "dialogfilesave", 1, 1, 1, PREFIX_PRIORITY, (lexone) ldialogfilesave },
      { "difference", 2, 2, 2, PREFIX_PRIORITY, (lexone) lsub },
      { "directories", 0, 0, 0, PREFIX_PRIORITY, (lexone) ldirectories },
      { "dllcall", 1, 1, 1, PREFIX_PRIORITY, (lexone) ldllcall },
      { "dllfree", 0, 0, 0, PREFIX_PRIORITY, (lexone) ldllfree },
      { "dllload", 1, 1, 1, PREFIX_PRIORITY, (lexone) ldllload },
      { "down", 1, 1, 1, PREFIX_PRIORITY, (lexone) ldownpitch },
      { "downpitch", 1, 1, 1, PREFIX_PRIORITY, (lexone) ldownpitch },
      { "dribble", 1, 1, 1, PREFIX_PRIORITY, (lexone) ldribble },
      { "ed", 1, 1, 1, PREFIX_PRIORITY, (lexone) ledit },
      { "edit", 1, 1, 1, PREFIX_PRIORITY, (lexone) ledit },
      { "ellipsearc", 4, 4, 4, PREFIX_PRIORITY, (lexone) lellipsearc },
      { "emptyp", 1, 1, 1, PREFIX_PRIORITY, (lexone) lemptyp },
      { "empty?", 1, 1, 1, PREFIX_PRIORITY, (lexone) lemptyp },
      { "eofp", 0, 0, 0, PREFIX_PRIORITY, (lexone) leofp },
      { "eof?", 0, 0, 0, PREFIX_PRIORITY, (lexone) leofp },
      { "equalp", 2, 2, 2, PREFIX_PRIORITY, (lexone) lequalp },
      { "equal?", 2, 2, 2, PREFIX_PRIORITY, (lexone) lequalp },
      { "er", 1, 1, 1, PREFIX_PRIORITY, (lexone) lerase },
      { "erase", 1, 1, 1, PREFIX_PRIORITY, (lexone) lerase },
      { "erasefile", 1, 1, 1, PREFIX_PRIORITY, (lexone) lerasefile },
      { "erf", 1, 1, 1, PREFIX_PRIORITY, (lexone) lerasefile },
      { "error", 0, 0, 0, PREFIX_PRIORITY, (lexone) lerror },
      { "eventcheck", 0, 0, 0, PREFIX_PRIORITY, (lexone) leventcheck },
      { "exp", 1, 1, 1, PREFIX_PRIORITY, (lexone) lexp },
      { "fd", 1, 1, 1, PREFIX_PRIORITY, (lexone) lforward },
      { "fence", 0, 0, 0, PREFIX_PRIORITY, (lexone) lfence },
      { "fill", 0, 0, 1, PREFIX_PRIORITY, (lexone) lfill },
      { "files", 0, 0, 0, PREFIX_PRIORITY, (lexone) lfiles },
      { "first", 1, 1, 1, PREFIX_PRIORITY, (lexone) lfirst },
      { "firsts", 1, 1, 1, PREFIX_PRIORITY, (lexone) lfirsts },
      { "floodcolor", 0, 0, 0, PREFIX_PRIORITY, (lexone) lfloodcolor },
      { "floodcolour", 0, 0, 0, PREFIX_PRIORITY, (lexone) lfloodcolor },
      { "forever", 1, 1, 1, MACRO_PRIORITY, (lexone) lforever },
      { "form", 3, 3, 3, PREFIX_PRIORITY, (lexone) lform },
      { "forward", 1, 1, 1, PREFIX_PRIORITY, (lexone) lforward },
      { "fput", 2, 2, 2, PREFIX_PRIORITY, (lexone) lfput },
//    { "fs", 0, 0, 0, PREFIX_PRIORITY, (lexone) lfullscreen },
//    { "fullscreen", 0, 0, 0, PREFIX_PRIORITY, (lexone) lfullscreen },
      { "fulltext", 1, 1, 1, PREFIX_PRIORITY, (lexone) lfulltext },
      { "getfocus", 0, 0, 0, PREFIX_PRIORITY, (lexone) lgetfocus },
//    { "goto", 1, 1, 1, MACRO_PRIORITY, (lexone) lgoto },
      { "gifload", 1, 1, 1, PREFIX_PRIORITY, (lexone) lgifload },
      { "gifsize", 1, 1, 1, PREFIX_PRIORITY, (lexone) lgifsize },
      { "gifsave", 1, 1, 6, PREFIX_PRIORITY, (lexone) lgifsave },
      { "gprop", 2, 2, 2, PREFIX_PRIORITY, (lexone) lgprop },
      { "greaterp", 2, 2, 2, PREFIX_PRIORITY, (lexone) lgreaterp },
      { "greater?", 2, 2, 2, PREFIX_PRIORITY, (lexone) lgreaterp },
      { "groupboxcreate", 6, 6, 6, PREFIX_PRIORITY, (lexone) lgroupboxcreate },
      { "groupboxdelete", 1, 1, 1, PREFIX_PRIORITY, (lexone) lgroupboxdelete },
      { "halt", 0, 0, 0, PREFIX_PRIORITY, (lexone) lhalt },
      { "heading", 0, 0, 0, PREFIX_PRIORITY, (lexone) lheading },
      { "help", OK_NO_ARG, 1, 1, PREFIX_PRIORITY, (lexone) lhelp },
      { "hideturtle", 0, 0, 0, PREFIX_PRIORITY, (lexone) lhideturtle },
      { "home", 0, 0, 0, PREFIX_PRIORITY, (lexone) lhome },
      { "ht", 0, 0, 0, PREFIX_PRIORITY, (lexone) lhideturtle },
      { "if", 2, 2, 3, MACRO_PRIORITY, (lexone) lif },
      { "ifelse", 3, 3, 3, MACRO_PRIORITY, (lexone) lifelse },
      { "iff", 1, 1, 1, MACRO_PRIORITY, (lexone) liffalse },
      { "iffalse", 1, 1, 1, MACRO_PRIORITY, (lexone) liffalse },
      { "ift", 1, 1, 1, MACRO_PRIORITY, (lexone) liftrue },
      { "iftrue", 1, 1, 1, MACRO_PRIORITY, (lexone) liftrue },
      { "ingameport", 1, 1, 2, PREFIX_PRIORITY, (lexone) lingameport },
      { "inport", 1, 1, 1, PREFIX_PRIORITY, (lexone) linport },
      { "inportb", 1, 1, 1, PREFIX_PRIORITY, (lexone) linportb },
      { "int", 1, 1, 1, PREFIX_PRIORITY, (lexone) linteg },
      { "item", 2, 2, 2, PREFIX_PRIORITY, (lexone) litem },
      { "keyboardoff", 0, 0, 0, PREFIX_PRIORITY, (lexone) lkeyboardoff },
      { "keyboardon", 1, 1, 2, PREFIX_PRIORITY, (lexone) lkeyboardon },
      { "keyboardvalue", 0, 0, 0, PREFIX_PRIORITY, (lexone) lkeyboardvalue },
      { "keyp", 0, 0, 0, PREFIX_PRIORITY, (lexone) lkeyp },
      { "key?", 0, 0, 0, PREFIX_PRIORITY, (lexone) lkeyp },
      { "label", 1, 1, 1, PREFIX_PRIORITY, (lexone) llabel },
      { "labelfont", 0, 0, 0, PREFIX_PRIORITY, (lexone) llabelfont },
      { "labelsize", 1, 1, 1, PREFIX_PRIORITY, (lexone) llabelsize },
      { "last", 1, 1, 1, PREFIX_PRIORITY, (lexone) llast },
      { "left", 1, 1, 1, PREFIX_PRIORITY, (lexone) lleft },
      { "leftroll", 1, 1, 1, PREFIX_PRIORITY, (lexone) lleftroll },
      { "lessp", 2, 2, 2, PREFIX_PRIORITY, (lexone) llessp },
      { "less?", 2, 2, 2, PREFIX_PRIORITY, (lexone) llessp },
      { "light", 0, 0, 0, PREFIX_PRIORITY, (lexone) llight },
      { "list", 1, 2, -1, PREFIX_PRIORITY, (lexone) llist },
      { "listboxaddstring", 2, 2, 2, PREFIX_PRIORITY, (lexone) llistboxaddstring },
      { "listboxcreate", 6, 6, 6, PREFIX_PRIORITY, (lexone) llistboxcreate },
      { "listboxenable", 2, 2, 2, PREFIX_PRIORITY, (lexone) llistboxenable },
      { "listboxdelete", 1, 1, 1, PREFIX_PRIORITY, (lexone) llistboxdelete },
      { "listboxdeletestring", 2, 2, 2, PREFIX_PRIORITY, (lexone) llistboxdeletestring },
      { "listboxgetselect", 1, 1, 1, PREFIX_PRIORITY, (lexone) llistboxgetselect },
      { "listp", 1, 1, 1, PREFIX_PRIORITY, (lexone) llistp },
      { "list?", 1, 1, 1, PREFIX_PRIORITY, (lexone) llistp },
      { "ln", 1, 1, 1, PREFIX_PRIORITY, (lexone) lln },
      { "load", 1, 1, 1, PREFIX_PRIORITY, (lexone) lload },
      { "local", 1, 1, -1, PREFIX_PRIORITY, (lexone) llocal },
      { "log10", 1, 1, 1, PREFIX_PRIORITY, (lexone) llog10 },
      { "lowercase", 1, 1, 1, PREFIX_PRIORITY, (lexone) llowercase },
      { "lput", 2, 2, 2, PREFIX_PRIORITY, (lexone) llput },
      { "lr", 1, 1, 1, PREFIX_PRIORITY, (lexone) lleftroll },
      { "lshift", 2, 2, 2, PREFIX_PRIORITY, (lexone) llshift },
      { "lt", 1, 1, 1, PREFIX_PRIORITY, (lexone) lleft },
      { "machine", 0, 0, 0, PREFIX_PRIORITY, (lexone) lmachine },
      { "macrop", 1, 1, 1, PREFIX_PRIORITY, (lexone) lmacrop },
      { "macro?", 1, 1, 1, PREFIX_PRIORITY, (lexone) lmacrop },
      { "make", 2, 2, 2, PREFIX_PRIORITY, (lexone) lmake },
      { "mci", 1, 1, 2, PREFIX_PRIORITY, (lexone) lmci },
      { "member", 2, 2, 2, PREFIX_PRIORITY, (lexone) lmember },
      { "memberp", 2, 2, 2, PREFIX_PRIORITY, (lexone) lmemberp },
      { "member?", 2, 2, 2, PREFIX_PRIORITY, (lexone) lmemberp },
      { "messagebox", 2, 2, 2, PREFIX_PRIORITY, (lexone) lmessagebox },
      { "midiclose", 0, 0, 0, PREFIX_PRIORITY, (lexone) lmidiclose },
      { "midimessage", 1, 1, 1, PREFIX_PRIORITY, (lexone) lmidimessage },
      { "midiopen", 0, 0, 1, PREFIX_PRIORITY, (lexone) lmidiopen },
      { "minus", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsub },
      { "mkdir", 1, 1, 1, PREFIX_PRIORITY, (lexone) lmkdir },
      { "modulo", 2, 2, 2, PREFIX_PRIORITY, (lexone) lmodulo },
      { "mouseoff", 0, 0, 0, PREFIX_PRIORITY, (lexone) lmouseoff },
      { "mouseon", 5, 5, 5, PREFIX_PRIORITY, (lexone) lmouseon },
      { "mousepos", 0, 0, 0, PREFIX_PRIORITY, (lexone) lmousepos },
      { "namep", 1, 1, 1, PREFIX_PRIORITY, (lexone) lnamep },
      { "name?", 1, 1, 1, PREFIX_PRIORITY, (lexone) lnamep },
      { "names", 0, 0, 0, PREFIX_PRIORITY, (lexone) lnames },
      { "netacceptoff", 0, 0, 0, PREFIX_PRIORITY, (lexone) lnetreceiveoff },
      { "netaccepton", 3, 3, 3, PREFIX_PRIORITY, (lexone) lnetreceiveon },
      { "netacceptreceivevalue", 0, 0, 0, PREFIX_PRIORITY, (lexone) lnetreceivereceivevalue },
      { "netacceptsendvalue", 1, 1, 1, PREFIX_PRIORITY, (lexone) lnetreceivesendvalue },
      { "netconnectoff", 0, 0, 0, PREFIX_PRIORITY, (lexone) lnetsendoff },
      { "netconnecton", 4, 4, 4, PREFIX_PRIORITY, (lexone) lnetsendon },
      { "netconnectreceivevalue", 0, 0, 0, PREFIX_PRIORITY, (lexone) lnetsendreceivevalue },
      { "netconnectsendvalue", 1, 1, 1, PREFIX_PRIORITY, (lexone) lnetsendsendvalue },
      { "netshutdown", 0, 0, 0, PREFIX_PRIORITY, (lexone) lnetshutdown },
      { "netstartup", 0, 0, 1, PREFIX_PRIORITY, (lexone) lnetstartup },
      { "nobitmapturtle", 0, 0, 0, PREFIX_PRIORITY, (lexone) lnobitmapturtle },
      { "nodes", 0, 0, 0, PREFIX_PRIORITY, (lexone) lnodes },
      { "nodribble", 0, 0, 0, PREFIX_PRIORITY, (lexone) lnodribble },
//    { "norefresh", 0, 0, 0, PREFIX_PRIORITY, (lexone) lnorefresh },
      { "nostatus", 0, 0, 0, PREFIX_PRIORITY, (lexone) lnostatus },
      { "not", 1, 1, 1, PREFIX_PRIORITY, (lexone) lnot },
      { "noyield", 0, 0, 0, PREFIX_PRIORITY, (lexone) lnoyield },
      { "numberp", 1, 1, 1, PREFIX_PRIORITY, (lexone) lnumberp },
      { "number?", 1, 1, 1, PREFIX_PRIORITY, (lexone) lnumberp },
      { "op", 1, 1, 1, TAIL_PRIORITY, (lexone) loutput },
      { "openappend", 1, 1, 2, PREFIX_PRIORITY, (lexone) lopenappend },
      { "openread", 1, 1, 2, PREFIX_PRIORITY, (lexone) lopenread },
      { "openupdate", 1, 1, 2, PREFIX_PRIORITY, (lexone) lopenupdate },
      { "openwrite", 1, 1, 2, PREFIX_PRIORITY, (lexone) lopenwrite },
      { "or", 0, 2, -1, PREFIX_PRIORITY, (lexone) lor },
      { "outport", 2, 2, 2, PREFIX_PRIORITY, (lexone) loutport },
      { "outportb", 2, 2, 2, PREFIX_PRIORITY, (lexone) loutportb },
      { "output", 1, 1, 1, TAIL_PRIORITY, (lexone) loutput },
      { "parse", 1, 1, 1, PREFIX_PRIORITY, (lexone) lparse },
      { "pause", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpause },
      { "pc", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpencolor },
      { "pd", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpendown },
      { "pe", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpenerase },
      { "pencolor", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpencolor },
      { "pencolour", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpencolor },
      { "pendown", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpendown },
      { "pendownp", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpendownp },
      { "pendown?", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpendownp },
      { "penerase", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpenerase },
      { "penmode", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpenmode },
      { "penpaint", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpenpaint },
      { "penpattern", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpenpattern },
      { "penreverse", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpenreverse },
      { "pensize", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpensize },
      { "penup", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpenup },
      { "perspective", 0, 0, 0, PREFIX_PRIORITY, (lexone) lperspective },
      { "pitch", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpitch },
      { "pixel", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpixel },
      { "playwave", 2, 2, 2, PREFIX_PRIORITY, (lexone) lplaywave },
      { "plist", 1, 1, 1, PREFIX_PRIORITY, (lexone) lplist },
      { "plists", 0, 0, 0, PREFIX_PRIORITY, (lexone) lplists },
      { "po", 1, 1, 1, PREFIX_PRIORITY, (lexone) lpo },
      { "popdir", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpopdir },
      { "polystart", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpolystart },
      { "polyend", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpolyend },
      { "polyview", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpolyview },
      { "portclose", 0, 0, 0, PREFIX_PRIORITY, (lexone) lportclose },
      { "portflush", 1, 1, 1, PREFIX_PRIORITY, (lexone) lportflush },
      { "portmode", 1, 1, 1, PREFIX_PRIORITY, (lexone) lportmode },
      { "portopen", 1, 1, 1, PREFIX_PRIORITY, (lexone) lportopen },
      { "portreadarray", 2, 2, 2, PREFIX_PRIORITY, (lexone) lportreadarray },
      { "portreadchar", 0, 0, 0, PREFIX_PRIORITY, (lexone) lportreadchar },
      { "portwritearray", 2, 2, 2, PREFIX_PRIORITY, (lexone) lportwritearray },
      { "portwritechar", 1, 1, 1, PREFIX_PRIORITY, (lexone) lportwritechar },
      { "pos", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpos },
      { "posxyz", 0, 0, 0, PREFIX_PRIORITY, (lexone) lposxyz },
      { "pot", 1, 1, 1, PREFIX_PRIORITY, (lexone) lpot },
      { "power", 2, 2, 2, PREFIX_PRIORITY, (lexone) lpower },
      { "pprop", 3, 3, 3, PREFIX_PRIORITY, (lexone) lpprop },
      { "ppt", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpenpaint },
      { "pr", 0, 1, -1, PREFIX_PRIORITY, (lexone) lprint },
      { "primitivep", 1, 1, 1, PREFIX_PRIORITY, (lexone) lprimitivep },
      { "primitive?", 1, 1, 1, PREFIX_PRIORITY, (lexone) lprimitivep },
      { "print", 0, 1, -1, PREFIX_PRIORITY, (lexone) lprint },
      { "procedurep", 1, 1, 1, PREFIX_PRIORITY, (lexone) lprocedurep },
      { "procedure?", 1, 1, 1, PREFIX_PRIORITY, (lexone) lprocedurep },
      { "proplistp", 1, 1, 1, PREFIX_PRIORITY, (lexone) lproplistp },
      { "proplist?", 1, 1, 1, PREFIX_PRIORITY, (lexone) lproplistp },
      { "procedures", 0, 0, 0, PREFIX_PRIORITY, (lexone) lprocedures },
      { "product", 0, 2, -1, PREFIX_PRIORITY, (lexone) lmul },
      { "pu", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpenup },
      { "px", 0, 0, 0, PREFIX_PRIORITY, (lexone) lpenreverse },
      { "questionbox", 2, 2, 2, PREFIX_PRIORITY, (lexone) lquestionbox },
      { "quotient", 1, 2, 2, PREFIX_PRIORITY, (lexone) ldivide },
      { "radarccos", 1, 1, 1, PREFIX_PRIORITY, (lexone) lradacos },
      { "radarcsin", 1, 1, 1, PREFIX_PRIORITY, (lexone) lradasin },
      { "radarctan", 1, 1, 2, PREFIX_PRIORITY, (lexone) lradatan },
      { "radcos", 1, 1, 1, PREFIX_PRIORITY, (lexone) lradcos },
      { "radiobuttoncreate", 8, 8, 8, PREFIX_PRIORITY, (lexone) lradiobuttoncreate },
      { "radiobuttonenable", 2, 2, 2, PREFIX_PRIORITY, (lexone) lradiobuttonenable },
      { "radiobuttondelete", 1, 1, 1, PREFIX_PRIORITY, (lexone) lradiobuttondelete },
      { "radiobuttonget", 1, 1, 1, PREFIX_PRIORITY, (lexone) lradiobuttonget },
      { "radiobuttonset", 2, 2, 2, PREFIX_PRIORITY, (lexone) lradiobuttonset },
      { "radsin", 1, 1, 1, PREFIX_PRIORITY, (lexone) lradsin },
      { "radtan", 1, 1, 1, PREFIX_PRIORITY, (lexone) lradtan },
      { "random", 1, 1, 1, PREFIX_PRIORITY, (lexone) lrandom },
      { "rawascii", 1, 1, 1, PREFIX_PRIORITY, (lexone) lrawascii },
      { "rc", 0, 0, 0, PREFIX_PRIORITY, (lexone) lreadchar },
      { "rcs", 1, 1, 1, PREFIX_PRIORITY, (lexone) lreadchars },
      { "readchar", 0, 0, 0, PREFIX_PRIORITY, (lexone) lreadchar },
      { "readchars", 1, 1, 1, PREFIX_PRIORITY, (lexone) lreadchars },
      { "reader", 0, 0, 0, PREFIX_PRIORITY, (lexone) lreader },
      { "readlist", 0, 0, 0, PREFIX_PRIORITY, (lexone) lreadlist },
      { "readpos", 0, 0, 0, PREFIX_PRIORITY, (lexone) lreadpos },
      { "readword", 0, 0, 0, PREFIX_PRIORITY, (lexone) lreadword },
//    { "refresh", 0, 0, 0, PREFIX_PRIORITY, (lexone) lrefresh },
      { "remainder", 2, 2, 2, PREFIX_PRIORITY, (lexone) lremainder },
      { "remprop", 2, 2, 2, PREFIX_PRIORITY, (lexone) lremprop },
      { "repcount", 0, 0, 0, PREFIX_PRIORITY, (lexone) lrepcount },
      { "repeat", 2, 2, 2, MACRO_PRIORITY, (lexone) lrepeat },
      { "rerandom", 0, 0, 1, PREFIX_PRIORITY, (lexone) lrerandom },
      { "right", 1, 1, 1, PREFIX_PRIORITY, (lexone) lright },
      { "rightroll", 1, 1, 1, PREFIX_PRIORITY, (lexone) lrightroll },
      { "rl", 0, 0, 0, PREFIX_PRIORITY, (lexone) lreadlist },
      { "rmdir", 1, 1, 1, PREFIX_PRIORITY, (lexone) lrmdir },
      { "roll", 0, 0, 0, PREFIX_PRIORITY, (lexone) lroll },
      { "round", 1, 1, 1, PREFIX_PRIORITY, (lexone) lround },
      { "rr", 1, 1, 1, PREFIX_PRIORITY, (lexone) lrightroll },
      { "rt", 1, 1, 1, PREFIX_PRIORITY, (lexone) lright },
      { "run", 1, 1, 1, MACRO_PRIORITY, (lexone) lrun },
      { "runparse", 1, 1, 1, PREFIX_PRIORITY, (lexone) lrunparse },
      { "runresult", 1, 1, 1, MACRO_PRIORITY, (lexone) lrunresult },
      { "rw", 0, 0, 0, PREFIX_PRIORITY, (lexone) lreadword },
      { "save", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsave },
//    { "scan", 1, 1, 1, PREFIX_PRIORITY, (lexone) lscan },
      { "screencolor", 0, 0, 0, PREFIX_PRIORITY, (lexone) lscreencolor },
      { "screencolour", 0, 0, 0, PREFIX_PRIORITY, (lexone) lscreencolor },
      { "scrollbarcreate", 7, 7, 7, PREFIX_PRIORITY, (lexone) lscrollbarcreate },
      { "scrollbarenable", 2, 2, 2, PREFIX_PRIORITY, (lexone) lscrollbarenable },
      { "scrollbardelete", 1, 1, 1, PREFIX_PRIORITY, (lexone) lscrollbardelete },
      { "scrollbarget", 1, 1, 1, PREFIX_PRIORITY, (lexone) lscrollbarget },
      { "scrollbarset", 4, 4, 4, PREFIX_PRIORITY, (lexone) lscrollbarset },
      { "scrollx", 1, 1, 1, PREFIX_PRIORITY, (lexone) lscrollx },
      { "scrolly", 1, 1, 1, PREFIX_PRIORITY, (lexone) lscrolly },
      { "scrunch", 0, 0, 0, PREFIX_PRIORITY, (lexone) lscrunch },
      { "se", 0, 2, -1, PREFIX_PRIORITY, (lexone) lsentence },
      { "selectbox", 2, 2, 2, PREFIX_PRIORITY, (lexone) lselectbox },
      { "sentence", 0, 2, -1, PREFIX_PRIORITY, (lexone) lsentence },
      { "setactivearea", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetactivearea },
      { "setbitindex", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetbitindex },
      { "setbitmode", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetbitmode },
      { "setclip", 3, 3, 3, PREFIX_PRIORITY, (lexone) lsetclip },
//    { "setcursor", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetcursor },
      { "setcursornowait", 0, 0, 0, PREFIX_PRIORITY, (lexone) lsetcursorarrow },
      { "setcursorwait", 0, 0, 0, PREFIX_PRIORITY, (lexone) lsetcursorwait },
      { "setfc", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetfloodcolor },
      { "setfloodcolor", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetfloodcolor },
      { "setfloodcolour", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetfloodcolor },
      { "setfocus", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetfocus },
      { "seth", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetheading },
      { "setheading", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetheading },
      { "setitem", 3, 3, 3, PREFIX_PRIORITY, (lexone) lsetitem },
      { "setlabelfont", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetlabelfont },
      { "setlight", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetlight },
      { "setmargins", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetmargins },
      { "setpc", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetpencolor },
      { "setpencolor", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetpencolor },
      { "setpencolour", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetpencolor },
      { "setpenpattern", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetpenpattern },
      { "setpensize", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetpensize },
      { "setpitch", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetpitch },
      { "setpixel", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetpixel },
      { "setpos", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetpos },
      { "setposxyz", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetposxyz },
      { "setread", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetread },
      { "setreadpos", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetreadpos },
      { "setroll", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetroll },
      { "setsc", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetscreencolor },
      { "setscreencolor", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetscreencolor },
      { "setscreencolour", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetscreencolor },
      { "setscrunch", 2, 2, 2, PREFIX_PRIORITY, (lexone) lsetscrunch },
      { "settimer", 3, 3, 3, PREFIX_PRIORITY, (lexone) lsettimer },
      { "setturtle", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetturtle },
      { "setturtlemode", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetturtlemode },
      { "setwrite", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetwrite },
      { "setwritepos", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetwritepos },
      { "setx", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetx },
      { "setxy", 2, 2, 2, PREFIX_PRIORITY, (lexone) lsetxy },
      { "setxyz", 3, 3, 3, PREFIX_PRIORITY, (lexone) lsetxyz },
      { "sety", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsety },
      { "setz", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsetz },
      { "shell", 1, 1, 2, PREFIX_PRIORITY, (lexone) lshell },
      { "show", 0, 1, -1, PREFIX_PRIORITY, (lexone) lshow },
      { "shownp", 0, 0, 0, PREFIX_PRIORITY, (lexone) lshownp },
      { "shown?", 0, 0, 0, PREFIX_PRIORITY, (lexone) lshownp },
      { "showturtle", 0, 0, 0, PREFIX_PRIORITY, (lexone) lshowturtle },
 //   { "silent", 0, 0, 0, PREFIX_PRIORITY, (lexone) lsilent },
      { "sin", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsin },
      { "sound", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsound },
 //   { "splitscreen", 0, 0, 0, PREFIX_PRIORITY, (lexone) lsplitscreen },
      { "sqrt", 1, 1, 1, PREFIX_PRIORITY, (lexone) lsqrt },
 //   { "ss", 0, 0, 0, PREFIX_PRIORITY, (lexone) lsplitscreen },
      { "st", 0, 0, 0, PREFIX_PRIORITY, (lexone) lshowturtle },
      { "standout", 1, 1, 1, PREFIX_PRIORITY, (lexone) lstandout },
      { "staticcreate", 7, 7, 7, PREFIX_PRIORITY, (lexone) lstaticcreate },
      { "staticdelete", 1, 1, 1, PREFIX_PRIORITY, (lexone) lstaticdelete },
      { "staticupdate", 2, 2, 2, PREFIX_PRIORITY, (lexone) lstaticupdate },
      { "status", 0, 0, 0, PREFIX_PRIORITY, (lexone) lstatus },
      { "step", 1, 1, 1, PREFIX_PRIORITY, (lexone) lstep },
      { "stepped", 0, 0, 0, PREFIX_PRIORITY, (lexone) lstepped },
      { "stop", 0, 0, 0, TAIL_PRIORITY, (lexone) lstop },
      { "substringp", 2, 2, 2, PREFIX_PRIORITY, (lexone) lsubstringp },
      { "substring?", 2, 2, 2, PREFIX_PRIORITY, (lexone) lsubstringp },
      { "sum", 0, 2, -1, PREFIX_PRIORITY, (lexone) ladd },
//    { "tag", 1, 1, 1, PREFIX_PRIORITY, (lexone) ltag },
      { "tan", 1, 1, 1, PREFIX_PRIORITY, (lexone) ltan },
      { "test", 1, 1, 1, PREFIX_PRIORITY, (lexone) ltest },
      { "text", 1, 1, 1, PREFIX_PRIORITY, (lexone) ltext },
//    { "textscreen", 0, 0, 0, PREFIX_PRIORITY, (lexone) ltextscreen },
      { "thing", 1, 1, 1, PREFIX_PRIORITY, (lexone) lthing },
      { "throw", 1, 1, 2, PREFIX_PRIORITY, (lexone) lthrow },
      { "time", 0, 0, 0, PREFIX_PRIORITY, (lexone) ltime },
      { "timemilli", 0, 0, 0, PREFIX_PRIORITY, (lexone) ltimemilli },
      { "to", -1, -1, -1, PREFIX_PRIORITY, (lexone) lto },
      { "tone", 2, 2, 2, PREFIX_PRIORITY, (lexone) ltone },
      { "towards", 1, 1, 1, PREFIX_PRIORITY, (lexone) ltowards },
      { "towardsxyz", 1, 1, 1, PREFIX_PRIORITY, (lexone) ltowardsxyz },
      { "trace", 1, 1, 1, PREFIX_PRIORITY, (lexone) ltrace },
      { "traced", 0, 0, 0, PREFIX_PRIORITY, (lexone) ltraced },
//    { "ts", 0, 0, 0, PREFIX_PRIORITY, (lexone) ltextscreen },
      { "turtle", 0, 0, 0, PREFIX_PRIORITY, (lexone) lturtle },
      { "turtlemode", 0, 0, 0, PREFIX_PRIORITY, (lexone) lturtlemode },
      { "turtles", 0, 0, 0, PREFIX_PRIORITY, (lexone) lturtles },
      { "type", 0, 1, -1, PREFIX_PRIORITY, (lexone) ltype },
      { "unbury", 1, 1, 1, PREFIX_PRIORITY, (lexone) lunbury },
//    { "unsilent", 0, 0, 0, PREFIX_PRIORITY, (lexone) lunsilent },
      { "unstep", 1, 1, 1, PREFIX_PRIORITY, (lexone) lunstep },
      { "untrace", 1, 1, 1, PREFIX_PRIORITY, (lexone) luntrace },
      { "up", 1, 1, 1, PREFIX_PRIORITY, (lexone) luppitch },
      { "uppercase", 1, 1, 1, PREFIX_PRIORITY, (lexone) luppercase },
      { "uppitch", 1, 1, 1, PREFIX_PRIORITY, (lexone) luppitch },
      { "wait", 1, 1, 1, PREFIX_PRIORITY, (lexone) lwait },
      { "window", 0, 0, 0, PREFIX_PRIORITY, (lexone) lwindow },
      { "windowcreate", 8, 8, 8, PREFIX_PRIORITY, (lexone) lwindowcreate },
      { "windowenable", 2, 2, 2, PREFIX_PRIORITY, (lexone) lwindowenable },
      { "windowdelete", 1, 1, 1, PREFIX_PRIORITY, (lexone) lwindowdelete },
      { "windowfileedit", 2, 2, 2, PREFIX_PRIORITY, (lexone) lwindowfileedit },
      { "windowset", 2, 2, 2, PREFIX_PRIORITY, (lexone) lwindowset },
      { "winhelp", 1, 1, 2, PREFIX_PRIORITY, (lexone) lwinhelp },
      { "word", 0, 2, -1, PREFIX_PRIORITY, (lexone) lword },
      { "wordp", 1, 1, 1, PREFIX_PRIORITY, (lexone) lwordp },
      { "word?", 1, 1, 1, PREFIX_PRIORITY, (lexone) lwordp },
      { "wrap", 0, 0, 0, PREFIX_PRIORITY, (lexone) lwrap },
      { "writepos", 0, 0, 0, PREFIX_PRIORITY, (lexone) lwritepos },
      { "writer", 0, 0, 0, PREFIX_PRIORITY, (lexone) lwriter },
      { "yesnobox", 2, 2, 2, PREFIX_PRIORITY, (lexone) lyesnobox },
      { "yield", 0, 0, 0, PREFIX_PRIORITY, (lexone) lyield },
      { "zoom", 1, 1, 1, PREFIX_PRIORITY, (lexone) lzoom },
      { 0, 0, 0, 0, 0, 0 }
   }
;

NODE *valref(NODE *p)
   {
   ref(p);
   return p;
   }

void init()
   {
   int i /* = 0 */;
   NODE *proc = NIL, *pname = NIL, *cnd = NIL;

   fill_reserve_tank();
   Unbound = newnode(PUNBOUND);

#ifdef bsd
   srandom((int) time((long *) NULL));
#else
   //    srand((int)time((long *)NULL));
   //    srand((int)12345);
#endif
#ifdef ecma
   for (i = 0; i < 128; i++)
      ecma_array[i] = i;
   for (i = 0; i < ecma_size; i++)
      ecma_array[special_chars[i]] = ecma_begin+i;
#endif

   //    logolib = getenv("LOGOLIB");
   //    if (logolib == NULL) logolib = libloc;
   //    editor = getenv("EDITOR");
   //    if (editor == NULL) editor = "jove";

   editor = "jove";
   editorname = strrchr(editor, (int) '/');
   editorname = (editorname ? editorname + 1 : editor);

   i = 0;
   while (prims[i].name) 
      {
      if (prims[i].priority == MACRO_PRIORITY)
         proc = reref(proc, newnode(MACRO));
      else if (prims[i].priority == TAIL_PRIORITY)
         proc = reref(proc, newnode(TAILFORM));
      else if ((prims[i].priority & ~4) == PREFIX_PRIORITY)
         proc = reref(proc, newnode(PRIM));/* incl. -- */
      else
         proc = reref(proc, newnode(INFIX));
      if (prims[i].priority < PREFIX_PRIORITY)
         setprimpri(proc, PREFIX_PRIORITY);
      else
         setprimpri(proc, prims[i].priority);
      setprimfun(proc, (lexzer) prims[i].prim);
      setprimdflt(proc, prims[i].defargs);
      setprimmax(proc, prims[i].maxargs);
      setprimmin(proc, prims[i].minargs);
      pname = reref(pname, make_static_strnode(prims[i].name));
      cnd = reref(cnd, make_instance(pname, pname));
      setprocnode__caseobj(cnd, proc);
      if (nodetype(proc) == MACRO)
         setflag__caseobj(cnd, PROC_MACRO);
      i++; 
      }
   deref(proc);
   deref(cnd);
   deref(pname);
   Truex = intern(make_static_strnode("true"));
   Falsex = intern(make_static_strnode("false"));
   Left_Paren = intern(make_static_strnode("("));
   Right_Paren = intern(make_static_strnode(")"));
   Minus_Sign = intern(make_static_strnode("-"));
   Minus_Tight = intern(make_static_strnode("--"));
   Query = intern(make_static_strnode("?"));
   Null_Word = intern(make_static_strnode("\0"));
   To = intern(make_static_strnode("to"));
   Macro = intern(make_static_strnode(".macro"));
   Toplevel = intern(make_static_strnode("toplevel"));
   System = intern(make_static_strnode("system"));
   Error = intern(make_static_strnode("error"));
   End = intern(make_static_strnode("end"));
   If = intern(make_static_strnode("if"));
   Ifelse = intern(make_static_strnode("ifelse"));
   Redefp = intern(make_static_strnode("redefp"));
   Caseignoredp = intern(make_static_strnode("caseignoredp"));
   setvalnode__caseobj(Caseignoredp, Truex);
   setflag__caseobj(Caseignoredp, VAL_BURIED);
   Erract = intern(make_static_strnode("erract"));
   Printdepthlimit = intern(make_static_strnode("printdepthlimit"));
   Printwidthlimit = intern(make_static_strnode("printwidthlimit"));
   Pause = intern(make_static_strnode("pause"));
   Startup = intern(make_static_strnode("startup"));
   Output = intern(make_static_strnode("output"));
   Op = intern(make_static_strnode("op"));
   Stop = intern(make_static_strnode("stop"));
   Goto = intern(make_static_strnode("goto"));
   Tag = intern(make_static_strnode("Tag"));
   the_generation = valref(cons(NIL, NIL));
   Not_Enough_Node = valref(cons(NIL, NIL));
   }

