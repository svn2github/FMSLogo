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
CompInheritOptsAt_fmslogoddexe = -I"\BC5\INCLUDE;C:\PROGRAM FILES\HELP WORKSHOP\INCLUDE" -DSTRICT;_OWLPCH;NOASM;DEBUG;MEM_DEBUG;LOCALE=1033
LinkerInheritOptsAt_fmslogoddexe = -x
LinkerOptsAt_fmslogoddexe = $(LinkerLocalOptsAtW32_fmslogoddexe)
ResOptsAt_fmslogoddexe = $(ResLocalOptsAtW32_fmslogoddexe)
BOptsAt_fmslogoddexe = $(BLocalOptsAtW32_fmslogoddexe)

ExecutableName=fmslogod.exe
IntermediateDirectory=DEBUG

#
# Dependency List
#
Dep_logo32d = $(ExecutableName)

logo32d : BccW32.cfg $(Dep_logo32d)
  echo MakeNode

version.h : ..\version.mk
  generate-version.bat $(FMSLOGO_VERSION)

Dep_fmslogoddexe = \
   $(IntermediateDirectory)\3dsolid.obj\
   $(IntermediateDirectory)\appendablelist.obj\
   $(IntermediateDirectory)\areawind.obj\
   $(IntermediateDirectory)\assembly.obj\
   $(IntermediateDirectory)\cmdwind.obj\
   $(IntermediateDirectory)\colordlg.obj\
   $(IntermediateDirectory)\commanderbutton.obj\
   $(IntermediateDirectory)\commandercheckbox.obj\
   $(IntermediateDirectory)\coms.obj\
   $(IntermediateDirectory)\debugheap.obj\
   $(IntermediateDirectory)\devwind.obj\
   $(IntermediateDirectory)\dib.obj\
   $(IntermediateDirectory)\dlgwind.obj\
   $(IntermediateDirectory)\dllstack.obj\
   $(IntermediateDirectory)\dllwind.obj\
   $(IntermediateDirectory)\dynamicbuffer.obj\
   $(IntermediateDirectory)\editwnd.obj\
   $(IntermediateDirectory)\error.obj\
   $(IntermediateDirectory)\eval.obj\
   $(IntermediateDirectory)\files.obj\
   $(IntermediateDirectory)\fileswnd.obj\
   $(IntermediateDirectory)\gbm.obj\
   $(IntermediateDirectory)\gbmhelp.obj\
   $(IntermediateDirectory)\gbmgif.obj\
   $(IntermediateDirectory)\gbmbmp.obj\
   $(IntermediateDirectory)\gbmsize.obj\
   $(IntermediateDirectory)\graphics.obj\
   $(IntermediateDirectory)\graphwin.obj\
   $(IntermediateDirectory)\ibmterm.obj\
   $(IntermediateDirectory)\init.obj\
   $(IntermediateDirectory)\intern.obj\
   $(IntermediateDirectory)\lists.obj\
   logo32.def\
   $(IntermediateDirectory)\logodata.obj\
   $(IntermediateDirectory)\logorc.res\
   $(IntermediateDirectory)\main.obj\
   $(IntermediateDirectory)\mainwind.obj\
   $(IntermediateDirectory)\math.obj\
   $(IntermediateDirectory)\mem.obj\
   $(IntermediateDirectory)\minieditor.obj\
   $(IntermediateDirectory)\mmwind.obj\
   $(IntermediateDirectory)\myfileed.obj\
   $(IntermediateDirectory)\myfilewn.obj\
   $(IntermediateDirectory)\netwind.obj\
   $(IntermediateDirectory)\paren.obj\
   $(IntermediateDirectory)\parse.obj\
   $(IntermediateDirectory)\print.obj\
   $(IntermediateDirectory)\richedpr.obj\
   $(IntermediateDirectory)\savebeforeexitdialog.obj\
   $(IntermediateDirectory)\sizedlg.obj\
   $(IntermediateDirectory)\statwind.obj\
   $(IntermediateDirectory)\term.obj\
   $(IntermediateDirectory)\threed.obj\
   $(IntermediateDirectory)\utils.obj\
   $(IntermediateDirectory)\unix.obj\
   $(IntermediateDirectory)\vector.obj\
   $(IntermediateDirectory)\wrksp.obj

$(ExecutableName) : $(Dep_fmslogoddexe)
  $(ILINK32) @&&|
 /v $(IDE_LinkFLAGS32) $(LinkerOptsAt_fmslogoddexe) $(LinkerInheritOptsAt_fmslogoddexe) +
\BC5\LIB\c0w32.obj+
$(IntermediateDirectory)\3dsolid.obj+
$(IntermediateDirectory)\appendablelist.obj+
$(IntermediateDirectory)\areawind.obj+
$(IntermediateDirectory)\assembly.obj+
$(IntermediateDirectory)\cmdwind.obj+
$(IntermediateDirectory)\colordlg.obj+
$(IntermediateDirectory)\commanderbutton.obj+
$(IntermediateDirectory)\commandercheckbox.obj+
$(IntermediateDirectory)\coms.obj+
$(IntermediateDirectory)\debugheap.obj+
$(IntermediateDirectory)\devwind.obj+
$(IntermediateDirectory)\dib.obj+
$(IntermediateDirectory)\dlgwind.obj+
$(IntermediateDirectory)\dllstack.obj+
$(IntermediateDirectory)\dllwind.obj+
$(IntermediateDirectory)\dynamicbuffer.obj+
$(IntermediateDirectory)\editwnd.obj+
$(IntermediateDirectory)\error.obj+
$(IntermediateDirectory)\eval.obj+
$(IntermediateDirectory)\files.obj+
$(IntermediateDirectory)\fileswnd.obj+
$(IntermediateDirectory)\gbm.obj+
$(IntermediateDirectory)\gbmhelp.obj+
$(IntermediateDirectory)\gbmgif.obj+
$(IntermediateDirectory)\gbmbmp.obj+
$(IntermediateDirectory)\gbmsize.obj+
$(IntermediateDirectory)\graphics.obj+
$(IntermediateDirectory)\graphwin.obj+
$(IntermediateDirectory)\ibmterm.obj+
$(IntermediateDirectory)\init.obj+
$(IntermediateDirectory)\intern.obj+
$(IntermediateDirectory)\lists.obj+
$(IntermediateDirectory)\logodata.obj+
$(IntermediateDirectory)\main.obj+
$(IntermediateDirectory)\mainwind.obj+
$(IntermediateDirectory)\math.obj+
$(IntermediateDirectory)\mem.obj+
$(IntermediateDirectory)\minieditor.obj+
$(IntermediateDirectory)\mmwind.obj+
$(IntermediateDirectory)\myfileed.obj+
$(IntermediateDirectory)\myfilewn.obj+
$(IntermediateDirectory)\netwind.obj+
$(IntermediateDirectory)\paren.obj+
$(IntermediateDirectory)\parse.obj+
$(IntermediateDirectory)\print.obj+
$(IntermediateDirectory)\richedpr.obj+
$(IntermediateDirectory)\savebeforeexitdialog.obj+
$(IntermediateDirectory)\sizedlg.obj+
$(IntermediateDirectory)\statwind.obj+
$(IntermediateDirectory)\term.obj+
$(IntermediateDirectory)\threed.obj+
$(IntermediateDirectory)\utils.obj+
$(IntermediateDirectory)\unix.obj+
$(IntermediateDirectory)\vector.obj+
$(IntermediateDirectory)\wrksp.obj
$<,$*
C:\BC5\LIB\owlwf.lib+
C:\BC5\LIB\bidsf.lib+
C:\BC5\LIB\ctl3d32.lib+
C:\BC5\LIB\import32.lib+
C:\BC5\LIB\cw32.lib
logo32.def
$(IntermediateDirectory)\logorc.res

|

$(IntermediateDirectory)\3dsolid.obj :  3dsolid.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ 3dsolid.cpp
|

$(IntermediateDirectory)\appendablelist.obj :  appendablelist.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ appendablelist.cpp
|

$(IntermediateDirectory)\assembly.obj :  assembly.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ assembly.cpp
|

$(IntermediateDirectory)\areawind.obj :  areawind.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ areawind.cpp
|

$(IntermediateDirectory)\cmdwind.obj :  cmdwind.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ cmdwind.cpp
|

$(IntermediateDirectory)\colordlg.obj :  colordlg.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ colordlg.cpp
|

$(IntermediateDirectory)\commanderbutton.obj :  commanderbutton.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ commanderbutton.cpp
|

$(IntermediateDirectory)\commandercheckbox.obj :  commandercheckbox.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ commandercheckbox.cpp
|

$(IntermediateDirectory)\coms.obj :  coms.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ coms.cpp
|


$(IntermediateDirectory)\debugheap.obj :  debugheap.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ debugheap.cpp
|

$(IntermediateDirectory)\devwind.obj :  devwind.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ devwind.cpp
|

$(IntermediateDirectory)\dib.obj :  dib.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ dib.cpp
|

$(IntermediateDirectory)\dlgwind.obj :  dlgwind.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ dlgwind.cpp
|

$(IntermediateDirectory)\dllstack.obj :  dllstack.c
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ dllstack.c
|

$(IntermediateDirectory)\dllwind.obj :  dllwind.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ dllwind.cpp
|

$(IntermediateDirectory)\dynamicbuffer.obj :  dynamicbuffer.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ dynamicbuffer.cpp
|

$(IntermediateDirectory)\editwnd.obj :  editwnd.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ editwnd.cpp
|

$(IntermediateDirectory)\error.obj :  error.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ error.cpp
|

$(IntermediateDirectory)\eval.obj :  eval.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ eval.cpp
|

$(IntermediateDirectory)\files.obj :  files.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ files.cpp
|

$(IntermediateDirectory)\fileswnd.obj :  fileswnd.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ fileswnd.cpp
|

$(IntermediateDirectory)\gbm.obj :  gbm.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ gbm.cpp
|

$(IntermediateDirectory)\gbmbmp.obj :  gbmbmp.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ gbmbmp.cpp
|

$(IntermediateDirectory)\gbmhelp.obj :  gbmhelp.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ gbmhelp.cpp
|

$(IntermediateDirectory)\gbmgif.obj :  gbmgif.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ gbmgif.cpp
|

$(IntermediateDirectory)\gbmsize.obj :  gbmsize.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ gbmsize.cpp
|

$(IntermediateDirectory)\graphics.obj :  graphics.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ graphics.cpp
|

$(IntermediateDirectory)\graphwin.obj :  graphwin.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ graphwin.cpp
|

$(IntermediateDirectory)\ibmterm.obj :  ibmterm.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ ibmterm.cpp
|

$(IntermediateDirectory)\init.obj :  init.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ init.cpp
|

$(IntermediateDirectory)\intern.obj :  intern.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ intern.cpp
|

$(IntermediateDirectory)\lists.obj :  lists.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ lists.cpp
|

$(IntermediateDirectory)\logodata.obj :  logodata.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ logodata.cpp
|

$(IntermediateDirectory)\logorc.res :  logorc.rc version.h localizedstrings*.h
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe)  -FO$@ logorc.rc
|
$(IntermediateDirectory)\printer.res :  ..\..\..\..\..\..\bc5\include\owl\printer.rc
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe)  -FO$@ ..\..\..\..\..\..\bc5\include\owl\printer.rc
|
$(IntermediateDirectory)\inputdia.res :  ..\..\..\..\..\..\bc5\include\owl\inputdia.rc
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe)  -FO$@ ..\..\..\..\..\..\bc5\include\owl\inputdia.rc
|
$(IntermediateDirectory)\picklist.res :  ..\..\..\..\..\..\bc5\include\owl\picklist.rc
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe)  -FO$@ ..\..\..\..\..\..\bc5\include\owl\picklist.rc
|
$(IntermediateDirectory)\except.res :  ..\..\..\..\..\..\bc5\include\owl\except.rc
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe)  -FO$@ ..\..\..\..\..\..\bc5\include\owl\except.rc
|
$(IntermediateDirectory)\stdwnds.res :  stdwnds.rc
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe)  -FO$@ stdwnds.rc
|
$(IntermediateDirectory)\filemenu.res :  filemenu.rc
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe)  -FO$@ filemenu.rc
|
$(IntermediateDirectory)\main.obj :  main.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ main.cpp
|

$(IntermediateDirectory)\mainwind.obj :  mainwind.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ mainwind.cpp
|

$(IntermediateDirectory)\math.obj :  math.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ math.cpp
|

$(IntermediateDirectory)\mem.obj :  mem.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ mem.cpp
|

$(IntermediateDirectory)\minieditor.obj :  minieditor.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ minieditor.cpp
|

$(IntermediateDirectory)\mmwind.obj :  mmwind.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ mmwind.cpp
|

$(IntermediateDirectory)\myfileed.obj :  myfileed.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ myfileed.cpp
|

$(IntermediateDirectory)\myfilewn.obj :  myfilewn.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ myfilewn.cpp
|

$(IntermediateDirectory)\netwind.obj :  netwind.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ netwind.cpp
|

$(IntermediateDirectory)\paren.obj :  paren.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ paren.cpp
|

$(IntermediateDirectory)\parse.obj :  parse.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ parse.cpp
|

$(IntermediateDirectory)\print.obj :  print.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ print.cpp
|

$(IntermediateDirectory)\richedpr.obj :  richedpr.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ richedpr.cpp
|

$(IntermediateDirectory)\savebeforeexitdialog.obj :  savebeforeexitdialog.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ savebeforeexitdialog.cpp
|

$(IntermediateDirectory)\sizedlg.obj :  sizedlg.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ sizedlg.cpp
|

$(IntermediateDirectory)\statwind.obj :  statwind.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ statwind.cpp
|

$(IntermediateDirectory)\term.obj :  term.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ term.cpp
|

$(IntermediateDirectory)\threed.obj :  threed.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ threed.cpp
|

$(IntermediateDirectory)\utils.obj :  utils.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ utils.cpp
|

$(IntermediateDirectory)\unix.obj :  unix.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ unix.cpp
|

$(IntermediateDirectory)\vector.obj :  vector.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogoddexe) $(CompInheritOptsAt_fmslogoddexe) -o$@ vector.cpp
|

$(IntermediateDirectory)\wrksp.obj :  wrksp.cpp
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

