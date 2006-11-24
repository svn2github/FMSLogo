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

#include "allwind.h"

struct PRIMTYPE
   {
   const char *name;
   short minargs;
   short defargs;
   short maxargs;
   short priority;
   logofunc prim;
   };

NODE *Truex;
NODE *Falsex;
NODE *Right_Paren;
NODE *Left_Paren;
NODE *Toplevel;
NODE *System;
NODE *Error;
NODE *End;
NODE *Redefp;
NODE *Caseignoredp;
NODE *Erract;
NODE *Printdepthlimit;
NODE *Printwidthlimit;
NODE *Pause;
NODE *If;
NODE *Ifelse;
NODE *To;
NODE *Macro;
NODE *Unbound;         // a special node that means nothing (or void) was returned
                       // This is different from NIL, which is the empty list.
NODE *Not_Enough_Node;
NODE *Minus_Sign;
NODE *Minus_Tight;
NODE *Startup;
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
      { ".defmacro", 2, 2, 2, PREFIX_PRIORITY, ldefmacro },
      { ".eq", 2, 2, 2, PREFIX_PRIORITY, l_eq },
      { ".macro", -1, -1, -1, PREFIX_PRIORITY, lmacro },
      { ".maybeoutput", 1, 1, 1, MAYBE_PRIORITY, loutput },
      { ".setbf", 2, 2, 2, PREFIX_PRIORITY, l_setbf },
      { ".setfirst", 2, 2, 2, PREFIX_PRIORITY, l_setfirst },
      { ".setitem", 3, 3, 3, PREFIX_PRIORITY, l_setitem },
      { "/", 1, 1, 1, PREFIX_PRIORITY + 3, ldivide },
      { "<", 2, 2, 2, PREFIX_PRIORITY + 1, llessp },
      { "=", 2, 2, 2, PREFIX_PRIORITY + 1, lequalp },
      { ">", 2, 2, 2, PREFIX_PRIORITY + 1, lgreaterp },
      { "?", 0, 0, 1, PREFIX_PRIORITY, lqm },
      { "activearea", 0, 0, 0, PREFIX_PRIORITY, lactivearea },
      { "allopen", 0, 0, 0, PREFIX_PRIORITY, lallopen },
      { "and", 0, 2, -1, PREFIX_PRIORITY, land },
      { "apply", 2, 2, 2, MACRO_PRIORITY, lapply },
      { "arccos", 1, 1, 1, PREFIX_PRIORITY, lacos },
      { "arcsin", 1, 1, 1, PREFIX_PRIORITY, lasin },
      { "arctan", 1, 1, 2, PREFIX_PRIORITY, latan },
      { "array", 1, 1, 2, PREFIX_PRIORITY, larray },
      { "arrayp", 1, 1, 1, PREFIX_PRIORITY, larrayp },
      { "array?", 1, 1, 1, PREFIX_PRIORITY, larrayp },
      { "ascii", 1, 1, 1, PREFIX_PRIORITY, lascii },
      { "ashift", 2, 2, 2, PREFIX_PRIORITY, lashift },
      { "back", 1, 1, 1, PREFIX_PRIORITY, lback },
      { "backslashedp", 1, 1, 1, PREFIX_PRIORITY, lbackslashedp },
      { "backslashed?", 1, 1, 1, PREFIX_PRIORITY, lbackslashedp },
      { "beforep", 2, 2, 2, PREFIX_PRIORITY, lbeforep },
      { "before?", 2, 2, 2, PREFIX_PRIORITY, lbeforep },
      { "bf", 1, 1, 1, PREFIX_PRIORITY, lbutfirst },
      { "bfs", 1, 1, 1, PREFIX_PRIORITY, lbfs },
      { "bitand", 0, 2, -1, PREFIX_PRIORITY, lbitand },
      { "bitblock", 2, 2, 2, PREFIX_PRIORITY, lbitblock },
      { "bitcopy", 2, 2, 2, PREFIX_PRIORITY, lbitcopy },
      { "bitcut", 2, 2, 2, PREFIX_PRIORITY, lbitcut },
      { "bitfit", 2, 2, 2, PREFIX_PRIORITY, lbitfit },
      { "bitindex", 0, 0, 0, PREFIX_PRIORITY, lbitindex },
      { "bitload", 1, 1, 1, PREFIX_PRIORITY, lbitload },
      { "bitloadsize", 1, 1, 1, PREFIX_PRIORITY, lbitloadsize },
      { "bitsize", 0, 0, 0, PREFIX_PRIORITY, lbitsize },
      { "bitmapturtle", 0, 0, 0, PREFIX_PRIORITY, lbitmapturtle },
      { "bitmode", 0, 0, 0, PREFIX_PRIORITY, lbitmode },
      { "bitnot", 1, 1, 1, PREFIX_PRIORITY, lbitnot },
      { "bitor", 0, 2, -1, PREFIX_PRIORITY, lbitor },
      { "bitpaste", 0, 0, 0, PREFIX_PRIORITY, lbitpaste },
      { "bitpastetoindex", 3, 3, 3, PREFIX_PRIORITY, lbitpastetoindex },
      { "bitsave", 1, 1, 2, PREFIX_PRIORITY, lbitsave },
      { "bitxor", 0, 2, -1, PREFIX_PRIORITY, lbitxor },
      { "bk", 1, 1, 1, PREFIX_PRIORITY, lback },
      { "bl", 1, 1, 1, PREFIX_PRIORITY, lbutlast },
      { "buried", 0, 0, 0, PREFIX_PRIORITY, lburied },
      { "bury", 1, 1, 1, PREFIX_PRIORITY, lbury },
      { "butfirst", 1, 1, 1, PREFIX_PRIORITY, lbutfirst },
      { "butfirsts", 1, 1, 1, PREFIX_PRIORITY, lbfs },
      { "butlast", 1, 1, 1, PREFIX_PRIORITY, lbutlast },
      { "buttoncreate", 8, 8, 8, PREFIX_PRIORITY, lbuttoncreate },
      { "buttondelete", 1, 1, 1, PREFIX_PRIORITY, lbuttondelete },
      { "buttonenable", 2, 2, 2, PREFIX_PRIORITY, lbuttonenable },
      { "buttonupdate", 2, 2, 2, PREFIX_PRIORITY, lbuttonupdate },
      { "buttonp", 0, 0, 0, PREFIX_PRIORITY, lbuttonp },
      { "button?", 0, 0, 0, PREFIX_PRIORITY, lbuttonp },
      { "bye", 0, 0, 0, PREFIX_PRIORITY, lbye },
      { "catch", 2, 2, 2, MACRO_PRIORITY, lcatch },
      { "char", 1, 1, 1, PREFIX_PRIORITY, lchar },
      { "chdir", 1, 1, 1, PREFIX_PRIORITY, lchdir },
      { "checkboxcreate", 8, 8, 8, PREFIX_PRIORITY, lcheckboxcreate },
      { "checkboxdelete", 1, 1, 1, PREFIX_PRIORITY, lcheckboxdelete },
      { "checkboxenable", 2, 2, 2, PREFIX_PRIORITY, lcheckboxenable },
      { "checkboxget", 1, 1, 1, PREFIX_PRIORITY, lcheckboxget },
      { "checkboxset", 2, 2, 2, PREFIX_PRIORITY, lcheckboxset },
      { "clean", 0, 0, 0, PREFIX_PRIORITY, lclean },
      { "clearpalette", 0, 0, 0, PREFIX_PRIORITY, lclearpalette },
      { "clearscreen", 0, 0, 0, PREFIX_PRIORITY, lclearscreen },
      { "cleartext", 0, 0, 0, PREFIX_PRIORITY, lcleartext },
      { "cleartimer", 1, 1, 1, PREFIX_PRIORITY, lcleartimer },
      { "close", 1, 1, 1, PREFIX_PRIORITY, lclose },
      { "closeall", 0, 0, 0, PREFIX_PRIORITY, lcloseall },
      { "co", OK_NO_ARG, 1, 1, PREFIX_PRIORITY, lcontinue },
      { "comboboxaddstring", 2, 2, 2, PREFIX_PRIORITY, lcomboboxaddstring },
      { "comboboxcreate", 6, 6, 6, PREFIX_PRIORITY, lcomboboxcreate },
      { "comboboxdelete", 1, 1, 1, PREFIX_PRIORITY, lcomboboxdelete },
      { "comboboxenable", 2, 2, 2, PREFIX_PRIORITY, lcomboboxenable },
      { "comboboxdeletestring", 2, 2, 2, PREFIX_PRIORITY, lcomboboxdeletestring },
      { "comboboxgettext", 1, 1, 1, PREFIX_PRIORITY, lcomboboxgettext },
      { "comboboxsettext", 2, 2, 2, PREFIX_PRIORITY, lcomboboxsettext },
      { "contents", 0, 0, 0, PREFIX_PRIORITY, lcontents },
      { "continue", OK_NO_ARG, 1, 1, PREFIX_PRIORITY, lcontinue },
      { "copydef", 2, 2, 2, PREFIX_PRIORITY, lcopydef },
      { "cos", 1, 1, 1, PREFIX_PRIORITY, lcos },
      { "count", 1, 1, 1, PREFIX_PRIORITY, lcount },
      { "cs", 0, 0, 0, PREFIX_PRIORITY, lclearscreen },
      { "ct", 0, 0, 0, PREFIX_PRIORITY, lcleartext },
      { "cursor", 0, 0, 0, PREFIX_PRIORITY, lcursor },
      { "debugwindows", 0, 0, 1, PREFIX_PRIORITY, ldebugwindows },
      { "define", 2, 2, 2, PREFIX_PRIORITY, ldefine },
      { "definedp", 1, 1, 1, PREFIX_PRIORITY, ldefinedp },
      { "defined?", 1, 1, 1, PREFIX_PRIORITY, ldefinedp },
      { "dialogcreate", 8, 8, 8, PREFIX_PRIORITY, ldialogcreate },
      { "dialogenable", 2, 2, 2, PREFIX_PRIORITY, ldialogenable },
      { "dialogdelete", 1, 1, 1, PREFIX_PRIORITY, ldialogdelete },
      { "dialogfileopen", 1, 1, 1, PREFIX_PRIORITY, ldialogfileopen },
      { "dialogfilesave", 1, 1, 1, PREFIX_PRIORITY, ldialogfilesave },
      { "difference", 2, 2, 2, PREFIX_PRIORITY, lsub },
      { "directories", 0, 0, 0, PREFIX_PRIORITY, ldirectories },
      { "dllcall", 1, 1, 1, PREFIX_PRIORITY, ldllcall },
      { "dllfree", 0, 0, 0, PREFIX_PRIORITY, ldllfree },
      { "dllload", 1, 1, 1, PREFIX_PRIORITY, ldllload },
      { "down", 1, 1, 1, PREFIX_PRIORITY, ldownpitch },
      { "downpitch", 1, 1, 1, PREFIX_PRIORITY, ldownpitch },
      { "dribble", 1, 1, 1, PREFIX_PRIORITY, ldribble },
      { "ed", 1, 1, 1, PREFIX_PRIORITY, ledit },
      { "edit", 1, 1, 1, PREFIX_PRIORITY, ledit },
      { "ellipsearc", 4, 4, 4, PREFIX_PRIORITY, lellipsearc },
      { "emptyp", 1, 1, 1, PREFIX_PRIORITY, lemptyp },
      { "empty?", 1, 1, 1, PREFIX_PRIORITY, lemptyp },
      { "eofp", 0, 0, 0, PREFIX_PRIORITY, leofp },
      { "eof?", 0, 0, 0, PREFIX_PRIORITY, leofp },
      { "equalp", 2, 2, 2, PREFIX_PRIORITY, lequalp },
      { "equal?", 2, 2, 2, PREFIX_PRIORITY, lequalp },
      { "er", 1, 1, 1, PREFIX_PRIORITY, lerase },
      { "erase", 1, 1, 1, PREFIX_PRIORITY, lerase },
      { "erasefile", 1, 1, 1, PREFIX_PRIORITY, lerasefile },
      { "erf", 1, 1, 1, PREFIX_PRIORITY, lerasefile },
      { "error", 0, 0, 0, PREFIX_PRIORITY, lerror },
      { "eventcheck", 0, 0, 0, PREFIX_PRIORITY, leventcheck },
      { "exp", 1, 1, 1, PREFIX_PRIORITY, lexp },
      { "fd", 1, 1, 1, PREFIX_PRIORITY, lforward },
      { "fence", 0, 0, 0, PREFIX_PRIORITY, lfence },
      { "fill", 0, 0, 1, PREFIX_PRIORITY, lfill },
      { "files", 0, 0, 0, PREFIX_PRIORITY, lfiles },
      { "first", 1, 1, 1, PREFIX_PRIORITY, lfirst },
      { "firsts", 1, 1, 1, PREFIX_PRIORITY, lfirsts },
      { "floodcolor", 0, 0, 0, PREFIX_PRIORITY, lfloodcolor },
      { "floodcolour", 0, 0, 0, PREFIX_PRIORITY, lfloodcolor },
      { "fontfacenames", 0, 0, 0, PREFIX_PRIORITY, lfontfacenames },
      { "forever", 1, 1, 1, MACRO_PRIORITY, lforever },
      { "form", 3, 3, 3, PREFIX_PRIORITY, lform },
      { "forward", 1, 1, 1, PREFIX_PRIORITY, lforward },
      { "fput", 2, 2, 2, PREFIX_PRIORITY, lfput },
      { "fs", 0, 0, 0, PREFIX_PRIORITY, lfullscreen },
      { "fullscreen", 0, 0, 0, PREFIX_PRIORITY, lfullscreen },
      { "fulltext", 1, 1, 1, PREFIX_PRIORITY, lfulltext },
      { "getfocus", 0, 0, 0, PREFIX_PRIORITY, lgetfocus },
//    { "goto", 1, 1, 1, MACRO_PRIORITY, lgoto },
      { "gifload", 1, 1, 1, PREFIX_PRIORITY, lgifload },
      { "gifsize", 1, 1, 1, PREFIX_PRIORITY, lgifsize },
      { "gifsave", 1, 1, 6, PREFIX_PRIORITY, lgifsave },
      { "gprop", 2, 2, 2, PREFIX_PRIORITY, lgprop },
      { "greaterp", 2, 2, 2, PREFIX_PRIORITY, lgreaterp },
      { "greater?", 2, 2, 2, PREFIX_PRIORITY, lgreaterp },
      { "groupboxcreate", 6, 6, 6, PREFIX_PRIORITY, lgroupboxcreate },
      { "groupboxdelete", 1, 1, 1, PREFIX_PRIORITY, lgroupboxdelete },
      { "halt", 0, 0, 0, PREFIX_PRIORITY, lhalt },
      { "heading", 0, 0, 0, PREFIX_PRIORITY, lheading },
      { "help", OK_NO_ARG, 1, 1, PREFIX_PRIORITY, lhelp },
      { "hideturtle", 0, 0, 0, PREFIX_PRIORITY, lhideturtle },
      { "home", 0, 0, 0, PREFIX_PRIORITY, lhome },
      { "ht", 0, 0, 0, PREFIX_PRIORITY, lhideturtle },
      { "if", 2, 2, 3, MACRO_PRIORITY, lif },
      { "ifelse", 3, 3, 3, MACRO_PRIORITY, lifelse },
      { "iff", 1, 1, 1, MACRO_PRIORITY, liffalse },
      { "iffalse", 1, 1, 1, MACRO_PRIORITY, liffalse },
      { "ift", 1, 1, 1, MACRO_PRIORITY, liftrue },
      { "iftrue", 1, 1, 1, MACRO_PRIORITY, liftrue },
      { "ingameport", 1, 1, 2, PREFIX_PRIORITY, lingameport },
      { "inport", 1, 1, 1, PREFIX_PRIORITY, linport },
      { "inportb", 1, 1, 1, PREFIX_PRIORITY, linportb },
      { "int", 1, 1, 1, PREFIX_PRIORITY, linteg },
      { "item", 2, 2, 2, PREFIX_PRIORITY, litem },
      { "keyboardoff", 0, 0, 0, PREFIX_PRIORITY, lkeyboardoff },
      { "keyboardon", 1, 1, 2, PREFIX_PRIORITY, lkeyboardon },
      { "keyboardvalue", 0, 0, 0, PREFIX_PRIORITY, lkeyboardvalue },
      { "keyp", 0, 0, 0, PREFIX_PRIORITY, lkeyp },
      { "key?", 0, 0, 0, PREFIX_PRIORITY, lkeyp },
      { "label", 1, 1, 1, PREFIX_PRIORITY, llabel },
      { "labelfont", 0, 0, 0, PREFIX_PRIORITY, llabelfont },
      { "labelsize", 1, 1, 1, PREFIX_PRIORITY, llabelsize },
      { "last", 1, 1, 1, PREFIX_PRIORITY, llast },
      { "left", 1, 1, 1, PREFIX_PRIORITY, lleft },
      { "leftroll", 1, 1, 1, PREFIX_PRIORITY, lleftroll },
      { "lessp", 2, 2, 2, PREFIX_PRIORITY, llessp },
      { "less?", 2, 2, 2, PREFIX_PRIORITY, llessp },
      { "light", 0, 0, 0, PREFIX_PRIORITY, llight },
      { "list", 0, 2, -1, PREFIX_PRIORITY, llist },
      { "listboxaddstring", 2, 2, 2, PREFIX_PRIORITY, llistboxaddstring },
      { "listboxcreate", 6, 6, 6, PREFIX_PRIORITY, llistboxcreate },
      { "listboxenable", 2, 2, 2, PREFIX_PRIORITY, llistboxenable },
      { "listboxdelete", 1, 1, 1, PREFIX_PRIORITY, llistboxdelete },
      { "listboxdeletestring", 2, 2, 2, PREFIX_PRIORITY, llistboxdeletestring },
      { "listboxgetselect", 1, 1, 1, PREFIX_PRIORITY, llistboxgetselect },
      { "listp", 1, 1, 1, PREFIX_PRIORITY, llistp },
      { "list?", 1, 1, 1, PREFIX_PRIORITY, llistp },
      { "ln", 1, 1, 1, PREFIX_PRIORITY, lln },
      { "load", 1, 1, 1, PREFIX_PRIORITY, lload },
      { "local", 1, 1, -1, PREFIX_PRIORITY, llocal },
      { "log10", 1, 1, 1, PREFIX_PRIORITY, llog10 },
      { "logoversion", 0, 0, 0, PREFIX_PRIORITY, llogoversion },
      { "lowercase", 1, 1, 1, PREFIX_PRIORITY, llowercase },
      { "lput", 2, 2, 2, PREFIX_PRIORITY, llput },
      { "lr", 1, 1, 1, PREFIX_PRIORITY, lleftroll },
      { "lshift", 2, 2, 2, PREFIX_PRIORITY, llshift },
      { "lt", 1, 1, 1, PREFIX_PRIORITY, lleft },
      { "machine", 0, 0, 0, PREFIX_PRIORITY, lmachine },
      { "macrop", 1, 1, 1, PREFIX_PRIORITY, lmacrop },
      { "macro?", 1, 1, 1, PREFIX_PRIORITY, lmacrop },
      { "make", 2, 2, 2, PREFIX_PRIORITY, lmake },
      { "mci", 1, 1, 2, PREFIX_PRIORITY, lmci },
      { "member", 2, 2, 2, PREFIX_PRIORITY, lmember },
      { "memberp", 2, 2, 2, PREFIX_PRIORITY, lmemberp },
      { "member?", 2, 2, 2, PREFIX_PRIORITY, lmemberp },
      { "messagebox", 2, 2, 2, PREFIX_PRIORITY, lmessagebox },
      { "midiclose", 0, 0, 0, PREFIX_PRIORITY, lmidiclose },
      { "midimessage", 1, 1, 1, PREFIX_PRIORITY, lmidimessage },
      { "midiopen", 0, 0, 1, PREFIX_PRIORITY, lmidiopen },
      { "minus", 1, 1, 1, PREFIX_PRIORITY, lsub },
      { "mkdir", 1, 1, 1, PREFIX_PRIORITY, lmkdir },
      { "modulo", 2, 2, 2, PREFIX_PRIORITY, lmodulo },
      { "mouseoff", 0, 0, 0, PREFIX_PRIORITY, lmouseoff },
      { "mouseon", 5, 5, 5, PREFIX_PRIORITY, lmouseon },
      { "mousepos", 0, 0, 0, PREFIX_PRIORITY, lmousepos },
      { "namep", 1, 1, 1, PREFIX_PRIORITY, lnamep },
      { "name?", 1, 1, 1, PREFIX_PRIORITY, lnamep },
      { "names", 0, 0, 0, PREFIX_PRIORITY, lnames },
      { "netacceptoff", 0, 0, 0, PREFIX_PRIORITY, lnetacceptoff },
      { "netaccepton", 3, 3, 3, PREFIX_PRIORITY, lnetaccepton },
      { "netacceptreceivevalue", 0, 0, 0, PREFIX_PRIORITY, lnetacceptreceivevalue },
      { "netacceptsendvalue", 1, 1, 1, PREFIX_PRIORITY, lnetacceptsendvalue },
      { "netconnectoff", 0, 0, 0, PREFIX_PRIORITY, lnetconnectoff },
      { "netconnecton", 4, 4, 4, PREFIX_PRIORITY, lnetconnecton },
      { "netconnectreceivevalue", 0, 0, 0, PREFIX_PRIORITY, lnetconnectreceivevalue },
      { "netconnectsendvalue", 1, 1, 1, PREFIX_PRIORITY, lnetconnectsendvalue },
      { "netshutdown", 0, 0, 0, PREFIX_PRIORITY, lnetshutdown },
      { "netstartup", 0, 0, 1, PREFIX_PRIORITY, lnetstartup },
      { "nobitmapturtle", 0, 0, 0, PREFIX_PRIORITY, lnobitmapturtle },
      { "nodes", 0, 0, 0, PREFIX_PRIORITY, lnodes },
      { "nodribble", 0, 0, 0, PREFIX_PRIORITY, lnodribble },
      { "nostatus", 0, 0, 0, PREFIX_PRIORITY, lnostatus },
      { "not", 1, 1, 1, PREFIX_PRIORITY, lnot },
      { "noyield", 0, 0, 0, PREFIX_PRIORITY, lnoyield },
      { "numberp", 1, 1, 1, PREFIX_PRIORITY, lnumberp },
      { "number?", 1, 1, 1, PREFIX_PRIORITY, lnumberp },
      { "op", 1, 1, 1, OUTPUT_PRIORITY, loutput },
      { "openappend", 1, 1, 2, PREFIX_PRIORITY, lopenappend },
      { "openread", 1, 1, 2, PREFIX_PRIORITY, lopenread },
      { "openupdate", 1, 1, 2, PREFIX_PRIORITY, lopenupdate },
      { "openwrite", 1, 1, 2, PREFIX_PRIORITY, lopenwrite },
      { "or", 0, 2, -1, PREFIX_PRIORITY, lor },
      { "outport", 2, 2, 2, PREFIX_PRIORITY, loutport },
      { "outportb", 2, 2, 2, PREFIX_PRIORITY, loutportb },
      { "output", 1, 1, 1, OUTPUT_PRIORITY, loutput },
      { "parse", 1, 1, 1, PREFIX_PRIORITY, lparse },
      { "pause", 0, 0, 0, PREFIX_PRIORITY, lpause },
      { "pc", 0, 0, 0, PREFIX_PRIORITY, lpencolor },
      { "pd", 0, 0, 0, PREFIX_PRIORITY, lpendown },
      { "pe", 0, 0, 0, PREFIX_PRIORITY, lpenerase },
      { "pencolor", 0, 0, 0, PREFIX_PRIORITY, lpencolor },
      { "pencolour", 0, 0, 0, PREFIX_PRIORITY, lpencolor },
      { "pendown", 0, 0, 0, PREFIX_PRIORITY, lpendown },
      { "pendownp", 0, 0, 0, PREFIX_PRIORITY, lpendownp },
      { "pendown?", 0, 0, 0, PREFIX_PRIORITY, lpendownp },
      { "penerase", 0, 0, 0, PREFIX_PRIORITY, lpenerase },
      { "penmode", 0, 0, 0, PREFIX_PRIORITY, lpenmode },
      { "penpaint", 0, 0, 0, PREFIX_PRIORITY, lpenpaint },
      { "penpattern", 0, 0, 0, PREFIX_PRIORITY, lpenpattern },
      { "penreverse", 0, 0, 0, PREFIX_PRIORITY, lpenreverse },
      { "pensize", 0, 0, 0, PREFIX_PRIORITY, lpensize },
      { "penup", 0, 0, 0, PREFIX_PRIORITY, lpenup },
      { "perspective", 0, 0, 0, PREFIX_PRIORITY, lperspective },
      { "pitch", 0, 0, 0, PREFIX_PRIORITY, lpitch },
      { "pixel", 0, 0, 0, PREFIX_PRIORITY, lpixel },
      { "playwave", 2, 2, 2, PREFIX_PRIORITY, lplaywave },
      { "plist", 1, 1, 1, PREFIX_PRIORITY, lplist },
      { "plists", 0, 0, 0, PREFIX_PRIORITY, lplists },
      { "po", 1, 1, 1, PREFIX_PRIORITY, lpo },
      { "popdir", 0, 0, 0, PREFIX_PRIORITY, lpopdir },
      { "polystart", 0, 0, 0, PREFIX_PRIORITY, lpolystart },
      { "polyend", 0, 0, 0, PREFIX_PRIORITY, lpolyend },
      { "polyview", 0, 0, 0, PREFIX_PRIORITY, lpolyview },
      { "portclose", 0, 0, 0, PREFIX_PRIORITY, lportclose },
      { "portflush", 1, 1, 1, PREFIX_PRIORITY, lportflush },
      { "portmode", 1, 1, 1, PREFIX_PRIORITY, lportmode },
      { "portopen", 1, 1, 1, PREFIX_PRIORITY, lportopen },
      { "portreadarray", 2, 2, 2, PREFIX_PRIORITY, lportreadarray },
      { "portreadchar", 0, 0, 0, PREFIX_PRIORITY, lportreadchar },
      { "portwritearray", 2, 2, 2, PREFIX_PRIORITY, lportwritearray },
      { "portwritechar", 1, 1, 1, PREFIX_PRIORITY, lportwritechar },
      { "pos", 0, 0, 0, PREFIX_PRIORITY, lpos },
      { "posxyz", 0, 0, 0, PREFIX_PRIORITY, lposxyz },
      { "pot", 1, 1, 1, PREFIX_PRIORITY, lpot },
      { "power", 2, 2, 2, PREFIX_PRIORITY, lpower },
      { "pprop", 3, 3, 3, PREFIX_PRIORITY, lpprop },
      { "ppt", 0, 0, 0, PREFIX_PRIORITY, lpenpaint },
      { "pr", 0, 1, -1, PREFIX_PRIORITY, lprint },
      { "primitivep", 1, 1, 1, PREFIX_PRIORITY, lprimitivep },
      { "primitive?", 1, 1, 1, PREFIX_PRIORITY, lprimitivep },
      { "print", 0, 1, -1, PREFIX_PRIORITY, lprint },
      { "procedurep", 1, 1, 1, PREFIX_PRIORITY, lprocedurep },
      { "procedure?", 1, 1, 1, PREFIX_PRIORITY, lprocedurep },
      { "proplistp", 1, 1, 1, PREFIX_PRIORITY, lproplistp },
      { "proplist?", 1, 1, 1, PREFIX_PRIORITY, lproplistp },
      { "procedures", 0, 0, 0, PREFIX_PRIORITY, lprocedures },
      { "product", 0, 2, -1, PREFIX_PRIORITY, lmul },
      { "pu", 0, 0, 0, PREFIX_PRIORITY, lpenup },
      { "px", 0, 0, 0, PREFIX_PRIORITY, lpenreverse },
      { "questionbox", 2, 2, 2, PREFIX_PRIORITY, lquestionbox },
      { "quotient", 1, 2, 2, PREFIX_PRIORITY, ldivide },
      { "radarccos", 1, 1, 1, PREFIX_PRIORITY, lradacos },
      { "radarcsin", 1, 1, 1, PREFIX_PRIORITY, lradasin },
      { "radarctan", 1, 1, 2, PREFIX_PRIORITY, lradatan },
      { "radcos", 1, 1, 1, PREFIX_PRIORITY, lradcos },
      { "radiobuttoncreate", 8, 8, 8, PREFIX_PRIORITY, lradiobuttoncreate },
      { "radiobuttonenable", 2, 2, 2, PREFIX_PRIORITY, lradiobuttonenable },
      { "radiobuttondelete", 1, 1, 1, PREFIX_PRIORITY, lradiobuttondelete },
      { "radiobuttonget", 1, 1, 1, PREFIX_PRIORITY, lradiobuttonget },
      { "radiobuttonset", 2, 2, 2, PREFIX_PRIORITY, lradiobuttonset },
      { "radsin", 1, 1, 1, PREFIX_PRIORITY, lradsin },
      { "radtan", 1, 1, 1, PREFIX_PRIORITY, lradtan },
      { "random", 1, 1, 1, PREFIX_PRIORITY, lrandom },
      { "rawascii", 1, 1, 1, PREFIX_PRIORITY, lrawascii },
      { "rc", 0, 0, 0, PREFIX_PRIORITY, lreadchar },
      { "rcs", 1, 1, 1, PREFIX_PRIORITY, lreadchars },
      { "readchar", 0, 0, 0, PREFIX_PRIORITY, lreadchar },
      { "readchars", 1, 1, 1, PREFIX_PRIORITY, lreadchars },
      { "reader", 0, 0, 0, PREFIX_PRIORITY, lreader },
      { "readlist", 0, 0, 0, PREFIX_PRIORITY, lreadlist },
      { "readpos", 0, 0, 0, PREFIX_PRIORITY, lreadpos },
      { "readword", 0, 0, 0, PREFIX_PRIORITY, lreadword },
      { "remainder", 2, 2, 2, PREFIX_PRIORITY, lremainder },
      { "remprop", 2, 2, 2, PREFIX_PRIORITY, lremprop },
      { "repcount", 0, 0, 0, PREFIX_PRIORITY, lrepcount },
      { "repeat", 2, 2, 2, MACRO_PRIORITY, lrepeat },
      { "rerandom", 0, 0, 1, PREFIX_PRIORITY, lrerandom },
      { "right", 1, 1, 1, PREFIX_PRIORITY, lright },
      { "rightroll", 1, 1, 1, PREFIX_PRIORITY, lrightroll },
      { "rl", 0, 0, 0, PREFIX_PRIORITY, lreadlist },
      { "rmdir", 1, 1, 1, PREFIX_PRIORITY, lrmdir },
      { "roll", 0, 0, 0, PREFIX_PRIORITY, lroll },
      { "round", 1, 1, 1, PREFIX_PRIORITY, lround },
      { "rr", 1, 1, 1, PREFIX_PRIORITY, lrightroll },
      { "rt", 1, 1, 1, PREFIX_PRIORITY, lright },
      { "run", 1, 1, 1, MACRO_PRIORITY, lrun },
      { "runparse", 1, 1, 1, PREFIX_PRIORITY, lrunparse },
      { "runresult", 1, 1, 1, MACRO_PRIORITY, lrunresult },
      { "rw", 0, 0, 0, PREFIX_PRIORITY, lreadword },
      { "save", 1, 1, 1, PREFIX_PRIORITY, lsave },
      { "screencolor", 0, 0, 0, PREFIX_PRIORITY, lscreencolor },
      { "screencolour", 0, 0, 0, PREFIX_PRIORITY, lscreencolor },
      { "scrollbarcreate", 7, 7, 7, PREFIX_PRIORITY, lscrollbarcreate },
      { "scrollbarenable", 2, 2, 2, PREFIX_PRIORITY, lscrollbarenable },
      { "scrollbardelete", 1, 1, 1, PREFIX_PRIORITY, lscrollbardelete },
      { "scrollbarget", 1, 1, 1, PREFIX_PRIORITY, lscrollbarget },
      { "scrollbarset", 4, 4, 4, PREFIX_PRIORITY, lscrollbarset },
      { "scrollx", 1, 1, 1, PREFIX_PRIORITY, lscrollx },
      { "scrolly", 1, 1, 1, PREFIX_PRIORITY, lscrolly },
      { "scrunch", 0, 0, 0, PREFIX_PRIORITY, lscrunch },
      { "se", 0, 2, -1, PREFIX_PRIORITY, lsentence },
      { "selectbox", 2, 2, 2, PREFIX_PRIORITY, lselectbox },
      { "sentence", 0, 2, -1, PREFIX_PRIORITY, lsentence },
      { "setactivearea", 1, 1, 1, PREFIX_PRIORITY, lsetactivearea },
      { "setbitindex", 1, 1, 1, PREFIX_PRIORITY, lsetbitindex },
      { "setbitmode", 1, 1, 1, PREFIX_PRIORITY, lsetbitmode },
      { "setclip", 3, 3, 3, PREFIX_PRIORITY, lsetclip },
//    { "setcursor", 1, 1, 1, PREFIX_PRIORITY, lsetcursor },
      { "setcursornowait", 0, 0, 0, PREFIX_PRIORITY, lsetcursorarrow },
      { "setcursorwait", 0, 0, 0, PREFIX_PRIORITY, lsetcursorwait },
      { "setfc", 1, 1, 1, PREFIX_PRIORITY, lsetfloodcolor },
      { "setfloodcolor", 1, 1, 1, PREFIX_PRIORITY, lsetfloodcolor },
      { "setfloodcolour", 1, 1, 1, PREFIX_PRIORITY, lsetfloodcolor },
      { "setfocus", 1, 1, 1, PREFIX_PRIORITY, lsetfocus },
      { "seth", 1, 1, 1, PREFIX_PRIORITY, lsetheading },
      { "setheading", 1, 1, 1, PREFIX_PRIORITY, lsetheading },
      { "setitem", 3, 3, 3, PREFIX_PRIORITY, lsetitem },
      { "setlabelfont", 1, 1, 1, PREFIX_PRIORITY, lsetlabelfont },
      { "setlight", 1, 1, 1, PREFIX_PRIORITY, lsetlight },
      { "setmargins", 1, 1, 1, PREFIX_PRIORITY, lsetmargins },
      { "setpc", 1, 1, 1, PREFIX_PRIORITY, lsetpencolor },
      { "setpencolor", 1, 1, 1, PREFIX_PRIORITY, lsetpencolor },
      { "setpencolour", 1, 1, 1, PREFIX_PRIORITY, lsetpencolor },
      { "setpenpattern", 1, 1, 1, PREFIX_PRIORITY, lsetpenpattern },
      { "setpensize", 1, 1, 1, PREFIX_PRIORITY, lsetpensize },
      { "setpitch", 1, 1, 1, PREFIX_PRIORITY, lsetpitch },
      { "setpixel", 1, 1, 1, PREFIX_PRIORITY, lsetpixel },
      { "setpos", 1, 1, 1, PREFIX_PRIORITY, lsetpos },
      { "setposxyz", 1, 1, 1, PREFIX_PRIORITY, lsetposxyz },
      { "setread", 1, 1, 1, PREFIX_PRIORITY, lsetread },
      { "setreadpos", 1, 1, 1, PREFIX_PRIORITY, lsetreadpos },
      { "setroll", 1, 1, 1, PREFIX_PRIORITY, lsetroll },
      { "setsc", 1, 1, 1, PREFIX_PRIORITY, lsetscreencolor },
      { "setscreencolor", 1, 1, 1, PREFIX_PRIORITY, lsetscreencolor },
      { "setscreencolour", 1, 1, 1, PREFIX_PRIORITY, lsetscreencolor },
      { "setscrunch", 2, 2, 2, PREFIX_PRIORITY, lsetscrunch },
      { "settimer", 3, 3, 3, PREFIX_PRIORITY, lsettimer },
      { "setturtle", 1, 1, 1, PREFIX_PRIORITY, lsetturtle },
      { "setturtlemode", 1, 1, 1, PREFIX_PRIORITY, lsetturtlemode },
      { "setwrite", 1, 1, 1, PREFIX_PRIORITY, lsetwrite },
      { "setwritepos", 1, 1, 1, PREFIX_PRIORITY, lsetwritepos },
      { "setx", 1, 1, 1, PREFIX_PRIORITY, lsetx },
      { "setxy", 2, 2, 2, PREFIX_PRIORITY, lsetxy },
      { "setxyz", 3, 3, 3, PREFIX_PRIORITY, lsetxyz },
      { "sety", 1, 1, 1, PREFIX_PRIORITY, lsety },
      { "setz", 1, 1, 1, PREFIX_PRIORITY, lsetz },
      { "shell", 1, 1, 2, PREFIX_PRIORITY, lshell },
      { "show", 0, 1, -1, PREFIX_PRIORITY, lshow },
      { "shownp", 0, 0, 0, PREFIX_PRIORITY, lshownp },
      { "shown?", 0, 0, 0, PREFIX_PRIORITY, lshownp },
      { "showturtle", 0, 0, 0, PREFIX_PRIORITY, lshowturtle },
      { "sin", 1, 1, 1, PREFIX_PRIORITY, lsin },
      { "sound", 1, 1, 1, PREFIX_PRIORITY, lsound },
      { "splitscreen", 0, 0, 0, PREFIX_PRIORITY, lsplitscreen },
      { "sqrt", 1, 1, 1, PREFIX_PRIORITY, lsqrt },
      { "ss", 0, 0, 0, PREFIX_PRIORITY, lsplitscreen },
      { "st", 0, 0, 0, PREFIX_PRIORITY, lshowturtle },
      { "standout", 1, 1, 1, PREFIX_PRIORITY, lstandout },
      { "staticcreate", 7, 7, 7, PREFIX_PRIORITY, lstaticcreate },
      { "staticdelete", 1, 1, 1, PREFIX_PRIORITY, lstaticdelete },
      { "staticupdate", 2, 2, 2, PREFIX_PRIORITY, lstaticupdate },
      { "status", 0, 0, 0, PREFIX_PRIORITY, lstatus },
      { "step", 1, 1, 1, PREFIX_PRIORITY, lstep },
      { "stepped", 0, 0, 0, PREFIX_PRIORITY, lstepped },
      { "stop", 0, 0, 0, STOP_PRIORITY, lstop },
      { "substringp", 2, 2, 2, PREFIX_PRIORITY, lsubstringp },
      { "substring?", 2, 2, 2, PREFIX_PRIORITY, lsubstringp },
      { "sum", 0, 2, -1, PREFIX_PRIORITY, ladd },
//    { "tag", 1, 1, 1, PREFIX_PRIORITY, ltag },
      { "tan", 1, 1, 1, PREFIX_PRIORITY, ltan },
      { "test", 1, 1, 1, PREFIX_PRIORITY, ltest },
      { "text", 1, 1, 1, PREFIX_PRIORITY, ltext },
      { "textscreen", 0, 0, 0, PREFIX_PRIORITY, ltextscreen },
      { "thing", 1, 1, 1, PREFIX_PRIORITY, lthing },
      { "throw", 1, 1, 2, PREFIX_PRIORITY, lthrow },
      { "time", 0, 0, 0, PREFIX_PRIORITY, ltime },
      { "timemilli", 0, 0, 0, PREFIX_PRIORITY, ltimemilli },
      { "to", -1, -1, -1, PREFIX_PRIORITY, lto },
      { "tone", 2, 2, 2, PREFIX_PRIORITY, ltone },
      { "towards", 1, 1, 1, PREFIX_PRIORITY, ltowards },
      { "towardsxyz", 1, 1, 1, PREFIX_PRIORITY, ltowardsxyz },
      { "trace", 1, 1, 1, PREFIX_PRIORITY, ltrace },
      { "traced", 0, 0, 0, PREFIX_PRIORITY, ltraced },
      { "ts", 0, 0, 0, PREFIX_PRIORITY, ltextscreen },
      { "turtle", 0, 0, 0, PREFIX_PRIORITY, lturtle },
      { "turtlemode", 0, 0, 0, PREFIX_PRIORITY, lturtlemode },
      { "turtles", 0, 0, 0, PREFIX_PRIORITY, lturtles },
      { "type", 0, 1, -1, PREFIX_PRIORITY, ltype },
      { "unbury", 1, 1, 1, PREFIX_PRIORITY, lunbury },
      { "unstep", 1, 1, 1, PREFIX_PRIORITY, lunstep },
      { "untrace", 1, 1, 1, PREFIX_PRIORITY, luntrace },
      { "up", 1, 1, 1, PREFIX_PRIORITY, luppitch },
      { "uppercase", 1, 1, 1, PREFIX_PRIORITY, luppercase },
      { "uppitch", 1, 1, 1, PREFIX_PRIORITY, luppitch },
      { "wait", 1, 1, 1, PREFIX_PRIORITY, lwait },
      { "window", 0, 0, 0, PREFIX_PRIORITY, lwindow },
      { "windowcreate", 8, 8, 8, PREFIX_PRIORITY, lwindowcreate },
      { "windowenable", 2, 2, 2, PREFIX_PRIORITY, lwindowenable },
      { "windowdelete", 1, 1, 1, PREFIX_PRIORITY, lwindowdelete },
      { "windowfileedit", 2, 2, 2, PREFIX_PRIORITY, lwindowfileedit },
      { "windowset", 2, 2, 2, PREFIX_PRIORITY, lwindowset },
      { "winhelp", 1, 1, 2, PREFIX_PRIORITY, lwinhelp },
      { "word", 0, 2, -1, PREFIX_PRIORITY, lword },
      { "wordp", 1, 1, 1, PREFIX_PRIORITY, lwordp },
      { "word?", 1, 1, 1, PREFIX_PRIORITY, lwordp },
      { "wrap", 0, 0, 0, PREFIX_PRIORITY, lwrap },
      { "writepos", 0, 0, 0, PREFIX_PRIORITY, lwritepos },
      { "writer", 0, 0, 0, PREFIX_PRIORITY, lwriter },
      { "yesnobox", 2, 2, 2, PREFIX_PRIORITY, lyesnobox },
      { "yield", 0, 0, 0, PREFIX_PRIORITY, lyield },
      { "zoom", 1, 1, 1, PREFIX_PRIORITY, lzoom },
      { 0, 0, 0, 0, 0, 0 }
   }
;

void init()
   {
   fill_reserve_tank();
   Unbound = newnode(PUNBOUND);

#ifdef ecma
   init_ecma_array();
#endif

   for (int i = 0; prims[i].name != NULL; i++)
      {
      NODE *proc;
      if (prims[i].priority == MACRO_PRIORITY)
         {
         proc = vref(newnode(MACRO));
         }
      else if (prims[i].priority <= TAIL_PRIORITY)
         {
         proc = vref(newnode(TAILFORM));
         }
      else if ((prims[i].priority & ~4) == (PREFIX_PRIORITY & ~4))
         {
         proc = vref(newnode(PRIM));/* incl. -- */
         }
      else
         {
         proc = vref(newnode(INFIX));
         }

      setprimpri(proc, prims[i].priority);
      setprimfun(proc, prims[i].prim);
      setprimdflt(proc, prims[i].defargs);
      setprimmax(proc, prims[i].maxargs);
      setprimmin(proc, prims[i].minargs);

      NODE * pname  = vref(make_static_strnode(prims[i].name));
      NODE * casend = vref(make_instance(pname, pname));
      setprocnode__caseobj(casend, proc);

      if (nodetype(proc) == MACRO)
         {
         setflag__caseobj(casend, PROC_MACRO);
         }

      deref(proc);
      deref(casend);
      deref(pname);
      }

   Truex = intern(make_static_strnode("true"));
   Falsex = intern(make_static_strnode("false"));
   Left_Paren = intern(make_static_strnode("("));
   Right_Paren = intern(make_static_strnode(")"));
   Minus_Sign = intern(make_static_strnode("-"));
   Minus_Tight = intern(make_static_strnode("--"));
   Query = intern(make_static_strnode("?"));
   Null_Word = intern(make_static_strnode(""));
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
   Stop = intern(make_static_strnode("stop"));
   Goto = intern(make_static_strnode("goto"));
   Tag = intern(make_static_strnode("Tag"));
   the_generation = vref(cons_list(NIL));
   Not_Enough_Node = vref(cons_list(NIL));

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
