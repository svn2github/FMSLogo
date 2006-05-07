#
# Borland C++ IDE generated makefile
# Generated 4/9/2006 at 6:30:40 PM 
#
.AUTODEPEND

!include ..\version.mk

#
# Borland C++ tools
#
IMPLIB  = Implib
BCC32   = Bcc32 +BccW32.cfg 
BCC32I  = Bcc32i +BccW32.cfg 
TLINK32 = TLink32
ILINK32 = Ilink32
TLIB    = TLib
BRC32   = Brc32
TASM32  = Tasm32
#
# IDE macros
#


#
# Options
#
IDE_LinkFLAGS32 =  -LC:\BC5\LIB
IDE_ResFLAGS32 = 
LinkerLocalOptsAtW32_fmslogoddexe =  -v -wdpl -went -wdup -wdef -wimt -wbdl -wsrf -wmsk -L\BC5\LIB -Tpe -aa -V4.0 -c
ResLocalOptsAtW32_fmslogoddexe = 
BLocalOptsAtW32_fmslogoddexe = 
CompInheritOptsAt_fmslogoddexe = -I"\BC5\INCLUDE;C:\PROGRAM FILES\HELP WORKSHOP\INCLUDE" -DSTRICT;_OWLPCH;NOASM;DEBUG;MEM_DEBUG
LinkerInheritOptsAt_fmslogoddexe = -x
LinkerOptsAt_fmslogoddexe = $(LinkerLocalOptsAtW32_fmslogoddexe)
ResOptsAt_fmslogoddexe = $(ResLocalOptsAtW32_fmslogoddexe)
BOptsAt_fmslogoddexe = $(BLocalOptsAtW32_fmslogoddexe)

#
# Dependency List
#
Dep_logo32d = \
   fmslogod.exe

logo32d : BccW32.cfg $(Dep_logo32d)
  echo MakeNode

Dep_fmslogoddexe = \
   DEBUG\3dsolid.obj\
   DEBUG\areawind.obj\
   DEBUG\assembly.obj\
   DEBUG\colordlg.obj\
   DEBUG\commanderbutton.obj\
   DEBUG\commandercheckbox.obj\
   DEBUG\coms.obj\
   DEBUG\cmdwind.obj\
   DEBUG\debugheap.obj\
   DEBUG\devwind.obj\
   DEBUG\dib.obj\
   DEBUG\dlgwind.obj\
   DEBUG\dllwind.obj\
   DEBUG\dllstack.obj\
   DEBUG\editwnd.obj\
   DEBUG\error.obj\
   DEBUG\eval.obj\
   DEBUG\files.obj\
   DEBUG\fileswnd.obj\
   DEBUG\gbm.obj\
   DEBUG\gbmbmp.obj\
   DEBUG\gbmhelp.obj\
   DEBUG\gbmgif.obj\
   DEBUG\gbmsize.obj\
   DEBUG\graphics.obj\
   DEBUG\graphwin.obj\
   DEBUG\ibmterm.obj\
   DEBUG\init.obj\
   DEBUG\intern.obj\
   DEBUG\lists.obj\
   logo32.def\
   DEBUG\logodata.obj\
   DEBUG\logorc.res\
   DEBUG\main.obj\
   DEBUG\mainwind.obj\
   DEBUG\math.obj\
   DEBUG\mem.obj\
   DEBUG\mmwind.obj\
   DEBUG\myfileed.obj\
   DEBUG\myfilewn.obj\
   DEBUG\netwind.obj\
   DEBUG\paren.obj\
   DEBUG\parse.obj\
   DEBUG\print.obj\
   DEBUG\richedpr.obj\
   DEBUG\savebeforeexitdialog.obj\
   DEBUG\sizedlg.obj\
   DEBUG\statwind.obj\
   DEBUG\term.obj\
   DEBUG\threed.obj\
   DEBUG\unix.obj\
   DEBUG\utils.obj\
   DEBUG\vector.obj\
   DEBUG\wrksp.obj

fmslogod.exe : $(Dep_fmslogoddexe)
  $(ILINK32) @&&|
 /v $(IDE_LinkFLAGS32) $(LinkerOptsAt_fmslogoddexe) $(LinkerInheritOptsAt_fmslogoddexe) +
\BC5\LIB\c0w32.obj+
DEBUG\3dsolid.obj+
DEBUG\areawind.obj+
DEBUG\assembly.obj+
DEBUG\colordlg.obj+
DEBUG\commanderbutton.obj+
DEBUG\commandercheckbox.obj+
DEBUG\coms.obj+
DEBUG\cmdwind.obj+
DEBUG\debugheap.obj+
DEBUG\devwind.obj+
DEBUG\dib.obj+
DEBUG\dlgwind.obj+
DEBUG\dllwind.obj+
DEBUG\dllstack.obj+
DEBUG\editwnd.obj+
DEBUG\error.obj+
DEBUG\eval.obj+
DEBUG\files.obj+
DEBUG\fileswnd.obj+
DEBUG\gbm.obj+
DEBUG\gbmbmp.obj+
DEBUG\gbmhelp.obj+
DEBUG\gbmgif.obj+
DEBUG\gbmsize.obj+
DEBUG\graphics.obj+
DEBUG\graphwin.obj+
DEBUG\ibmterm.obj+
DEBUG\init.obj+
DEBUG\intern.obj+
DEBUG\lists.obj+
DEBUG\logodata.obj+
DEBUG\main.obj+
DEBUG\mainwind.obj+
DEBUG\math.obj+
DEBUG\mem.obj+
DEBUG\mmwind.obj+
DEBUG\myfileed.obj+
DEBUG\myfilewn.obj+
DEBUG\netwind.obj+
DEBUG\paren.obj+
DEBUG\parse.obj+
DEBUG\print.obj+
DEBUG\richedpr.obj+
DEBUG\savebeforeexitdialog.obj+
DEBUG\sizedlg.obj+
DEBUG\statwind.obj+
DEBUG\term.obj+
DEBUG\threed.obj+
DEBUG\unix.obj+
DEBUG\utils.obj+
DEBUG\vector.obj+
DEBUG\wrksp.obj
$<,$*
\BC5\LIB\owlwf.lib+
\BC5\LIB\bidsf.lib+
\BC5\LIB\ctl3d32.lib+
\BC5\LIB\import32.lib+
\BC5\LIB\cw32.lib
logo32.def
DEBUG\logorc.res

|
DEBUG\3dsolid.obj :  3dsolid.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ 3dsolid.cpp
|

DEBUG\areawind.obj :  areawind.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ areawind.cpp
|

DEBUG\assembly.obj :  assembly.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ assembly.cpp
|

DEBUG\colordlg.obj :  colordlg.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ colordlg.cpp
|

DEBUG\commanderbutton.obj :  commanderbutton.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ commanderbutton.cpp
|

DEBUG\commandercheckbox.obj :  commandercheckbox.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ commandercheckbox.cpp
|

DEBUG\coms.obj :  coms.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ coms.cpp
|

DEBUG\cmdwind.obj :  cmdwind.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ cmdwind.cpp
|

DEBUG\debugheap.obj :  debugheap.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ debugheap.cpp
|

DEBUG\devwind.obj :  devwind.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ devwind.cpp
|

DEBUG\dib.obj :  dib.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ dib.cpp
|

DEBUG\dlgwind.obj :  dlgwind.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ dlgwind.cpp
|

DEBUG\dllwind.obj :  dllwind.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ dllwind.cpp
|

DEBUG\dllstack.obj :  dllstack.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ dllstack.c
|

DEBUG\editwnd.obj :  editwnd.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ editwnd.cpp
|

DEBUG\error.obj :  error.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ error.cpp
|

DEBUG\eval.obj :  eval.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ eval.cpp
|

DEBUG\files.obj :  files.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ files.cpp
|

DEBUG\fileswnd.obj :  fileswnd.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ fileswnd.cpp
|

DEBUG\gbm.obj :  gbm.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ gbm.cpp
|

DEBUG\gbmbmp.obj :  gbmbmp.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ gbmbmp.cpp
|

DEBUG\gbmhelp.obj :  gbmhelp.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ gbmhelp.cpp
|

DEBUG\gbmgif.obj :  gbmgif.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ gbmgif.cpp
|

DEBUG\gbmsize.obj :  gbmsize.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ gbmsize.cpp
|

DEBUG\graphics.obj :  graphics.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ graphics.cpp
|

DEBUG\graphwin.obj :  graphwin.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ graphwin.cpp
|

DEBUG\ibmterm.obj :  ibmterm.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ ibmterm.cpp
|

DEBUG\init.obj :  init.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ init.cpp
|

DEBUG\intern.obj :  intern.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ intern.cpp
|

DEBUG\lists.obj :  lists.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ lists.cpp
|

DEBUG\logodata.obj :  logodata.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ logodata.cpp
|

DEBUG\logorc.res :  logorc.rc
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe)  -FO$@ logorc.rc
|
DEBUG\printer.res :  ..\..\..\..\..\..\bc5\include\owl\printer.rc
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe)  -FO$@ ..\..\..\..\..\..\bc5\include\owl\printer.rc
|
DEBUG\inputdia.res :  ..\..\..\..\..\..\bc5\include\owl\inputdia.rc
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe)  -FO$@ ..\..\..\..\..\..\bc5\include\owl\inputdia.rc
|
DEBUG\picklist.res :  ..\..\..\..\..\..\bc5\include\owl\picklist.rc
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe)  -FO$@ ..\..\..\..\..\..\bc5\include\owl\picklist.rc
|
DEBUG\except.res :  ..\..\..\..\..\..\bc5\include\owl\except.rc
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe)  -FO$@ ..\..\..\..\..\..\bc5\include\owl\except.rc
|
DEBUG\stdwnds.res :  stdwnds.rc
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe)  -FO$@ stdwnds.rc
|
DEBUG\filemenu.res :  filemenu.rc
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe)  -FO$@ filemenu.rc
|
DEBUG\main.obj :  main.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ main.cpp
|

DEBUG\mainwind.obj :  mainwind.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ mainwind.cpp
|

DEBUG\math.obj :  math.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ math.cpp
|

DEBUG\mem.obj :  mem.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ mem.cpp
|

DEBUG\mmwind.obj :  mmwind.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ mmwind.cpp
|

DEBUG\myfileed.obj :  myfileed.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ myfileed.cpp
|

DEBUG\myfilewn.obj :  myfilewn.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ myfilewn.cpp
|

DEBUG\netwind.obj :  netwind.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ netwind.cpp
|

DEBUG\paren.obj :  paren.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ paren.cpp
|

DEBUG\parse.obj :  parse.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ parse.cpp
|

DEBUG\print.obj :  print.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ print.cpp
|

DEBUG\richedpr.obj :  richedpr.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ richedpr.cpp
|

DEBUG\savebeforeexitdialog.obj :  savebeforeexitdialog.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ savebeforeexitdialog.cpp
|

DEBUG\sizedlg.obj :  sizedlg.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ sizedlg.cpp
|

DEBUG\statwind.obj :  statwind.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ statwind.cpp
|

DEBUG\term.obj :  term.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ term.cpp
|

DEBUG\threed.obj :  threed.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ threed.cpp
|

DEBUG\unix.obj :  unix.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ unix.cpp
|

DEBUG\utils.obj :  utils.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ utils.cpp
|

DEBUG\vector.obj :  vector.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ vector.cpp
|

DEBUG\wrksp.obj :  wrksp.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ wrksp.cpp
|

# Compiler configuration file
BccW32.cfg : 
   Copy &&|
-w
-R
-v
-WM-
-vi
-H
-H=logo32x.csm
-v
-R
-k
-N
-H=LOGO.CSM
-O-c
-O-i
-O-v
-Z-
-O-
-O-e
-O-l
-O-b
-O-W
-O-a
-O-m
-O-p
-wbbf
-wpin
-wnak
-wdef
-wnod
-wamb
-wuse
-wstv
-wasm
-wamp
-wobs
-wpch
-wpia
-waus
-wcln
-wsig
-wucp
-u
-W
-H"owl\pch.h"
-d
-ff-
-y
-5
-Od
-a-
-A-
-VF-
-r-
| $@


