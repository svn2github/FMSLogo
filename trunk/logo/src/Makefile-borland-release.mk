#
# Borland C++ IDE makefile
#
.AUTODEPEND

!include ..\version.mk

!ifndef LOCALECODE
   # English-US
   LOCALECODE=1033
!endif

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
# Options
#
IDE_LinkFLAGS32 =  -LC:\BC5\LIB
IDE_ResFLAGS32 = 
LinkerLocalOptsAtW32_fmslogodexe =  -wdpl -went -wdup -wdef -wimt -wbdl -wsrf -wmsk -Tpe -aa -V4.0 -c -LC:\BC5\LIB
ResLocalOptsAtW32_fmslogodexe = -l$(LOCALECODE)
BLocalOptsAtW32_fmslogodexe = 
CompInheritOptsAt_fmslogodexe = -I"C:\Program Files\Help Workshop\include" -IC:\BC5\INCLUDE -DSTRICT;_OWLPCH;NDEBUG;LOCALE=$(LOCALECODE)
LinkerInheritOptsAt_fmslogodexe = -x
LinkerOptsAt_fmslogodexe = $(LinkerLocalOptsAtW32_fmslogodexe)
ResOptsAt_fmslogodexe = $(ResLocalOptsAtW32_fmslogodexe)
BOptsAt_fmslogodexe = $(BLocalOptsAtW32_fmslogodexe)

ExecutableName=fmslogo-$(LOCALECODE).exe
IntermediateDirectory=RELEASE$(LOCALECODE)

#
# Dependency List
#
Dep_logo32 = $(ExecutableName)


# top-level target
logo32 : BccW32.cfg $(Dep_logo32)
  echo MakeNode

version.h : ..\version.mk
  generate-version.bat $(FMSLOGO_VERSION)

Dep_fmslogodexe = \
   $(IntermediateDirectory)\3dsolid.obj\
   $(IntermediateDirectory)\appendablelist.obj\
   $(IntermediateDirectory)\areawind.obj\
   $(IntermediateDirectory)\assembly.obj\
   $(IntermediateDirectory)\cmdwind.obj\
   $(IntermediateDirectory)\colordlg.obj\
   $(IntermediateDirectory)\commanderbutton.obj\
   $(IntermediateDirectory)\commandercheckbox.obj\
   $(IntermediateDirectory)\coms.obj\
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

$(ExecutableName) : $(Dep_fmslogodexe)
  $(ILINK32) @&&|
 /v $(IDE_LinkFLAGS32) $(LinkerOptsAt_fmslogodexe) $(LinkerInheritOptsAt_fmslogodexe) +
C:\BC5\LIB\c0w32.obj+
$(IntermediateDirectory)\3dsolid.obj+
$(IntermediateDirectory)\appendablelist.obj+
$(IntermediateDirectory)\areawind.obj+
$(IntermediateDirectory)\assembly.obj+
$(IntermediateDirectory)\cmdwind.obj+
$(IntermediateDirectory)\colordlg.obj+
$(IntermediateDirectory)\commanderbutton.obj+
$(IntermediateDirectory)\commandercheckbox.obj+
$(IntermediateDirectory)\coms.obj+
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

$(IntermediateDirectory)\3dsolid.obj :  3dsolid.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ 3dsolid.cpp
|

$(IntermediateDirectory)\appendablelist.obj :  appendablelist.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ appendablelist.cpp
|

$(IntermediateDirectory)\assembly.obj :  assembly.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ assembly.cpp
|

$(IntermediateDirectory)\areawind.obj :  areawind.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ areawind.cpp
|

$(IntermediateDirectory)\cmdwind.obj :  cmdwind.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ cmdwind.cpp
|

$(IntermediateDirectory)\colordlg.obj :  colordlg.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ colordlg.cpp
|

$(IntermediateDirectory)\commanderbutton.obj :  commanderbutton.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ commanderbutton.cpp
|

$(IntermediateDirectory)\commandercheckbox.obj :  commandercheckbox.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ commandercheckbox.cpp
|

$(IntermediateDirectory)\coms.obj :  coms.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ coms.cpp
|

$(IntermediateDirectory)\devwind.obj :  devwind.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ devwind.cpp
|

$(IntermediateDirectory)\dib.obj :  dib.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ dib.cpp
|

$(IntermediateDirectory)\dlgwind.obj :  dlgwind.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ dlgwind.cpp
|

$(IntermediateDirectory)\dllstack.obj :  dllstack.c version.h
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ dllstack.c
|

$(IntermediateDirectory)\dllwind.obj :  dllwind.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ dllwind.cpp
|

$(IntermediateDirectory)\dynamicbuffer.obj :  dynamicbuffer.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ dynamicbuffer.cpp
|

$(IntermediateDirectory)\editwnd.obj :  editwnd.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ editwnd.cpp
|

$(IntermediateDirectory)\error.obj :  error.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ error.cpp
|

$(IntermediateDirectory)\eval.obj :  eval.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ eval.cpp
|

$(IntermediateDirectory)\files.obj :  files.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ files.cpp
|

$(IntermediateDirectory)\fileswnd.obj :  fileswnd.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ fileswnd.cpp
|

$(IntermediateDirectory)\gbm.obj :  gbm.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ gbm.cpp
|

$(IntermediateDirectory)\gbmbmp.obj :  gbmbmp.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ gbmbmp.cpp
|

$(IntermediateDirectory)\gbmhelp.obj :  gbmhelp.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ gbmhelp.cpp
|

$(IntermediateDirectory)\gbmgif.obj :  gbmgif.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ gbmgif.cpp
|

$(IntermediateDirectory)\gbmsize.obj :  gbmsize.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ gbmsize.cpp
|

$(IntermediateDirectory)\graphics.obj :  graphics.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ graphics.cpp
|

$(IntermediateDirectory)\graphwin.obj :  graphwin.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ graphwin.cpp
|

$(IntermediateDirectory)\ibmterm.obj :  ibmterm.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ ibmterm.cpp
|

$(IntermediateDirectory)\init.obj :  init.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ init.cpp
|

$(IntermediateDirectory)\intern.obj :  intern.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ intern.cpp
|

$(IntermediateDirectory)\lists.obj :  lists.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ lists.cpp
|

$(IntermediateDirectory)\logodata.obj :  logodata.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ logodata.cpp
|

$(IntermediateDirectory)\logorc.res :  logorc.rc version.h localizedstrings*.h
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe)  -FO$@ logorc.rc
|

$(IntermediateDirectory)\stdwnds.res :  stdwnds.rc
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe)  -FO$@ stdwnds.rc
|

$(IntermediateDirectory)\filemenu.res :  filemenu.rc
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe)  -FO$@ filemenu.rc
|
$(IntermediateDirectory)\main.obj :  main.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ main.cpp
|

$(IntermediateDirectory)\mainwind.obj :  mainwind.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ mainwind.cpp
|

$(IntermediateDirectory)\math.obj :  math.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ math.cpp
|

$(IntermediateDirectory)\mem.obj :  mem.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ mem.cpp
|

$(IntermediateDirectory)\minieditor.obj :  minieditor.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ minieditor.cpp
|

$(IntermediateDirectory)\mmwind.obj :  mmwind.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ mmwind.cpp
|

$(IntermediateDirectory)\myfileed.obj :  myfileed.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ myfileed.cpp
|

$(IntermediateDirectory)\myfilewn.obj :  myfilewn.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ myfilewn.cpp
|

$(IntermediateDirectory)\netwind.obj :  netwind.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ netwind.cpp
|

$(IntermediateDirectory)\paren.obj :  paren.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ paren.cpp
|

$(IntermediateDirectory)\parse.obj :  parse.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ parse.cpp
|

$(IntermediateDirectory)\print.obj :  print.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ print.cpp
|

$(IntermediateDirectory)\richedpr.obj :  richedpr.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ richedpr.cpp
|

$(IntermediateDirectory)\savebeforeexitdialog.obj :  savebeforeexitdialog.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ savebeforeexitdialog.cpp
|

$(IntermediateDirectory)\sizedlg.obj :  sizedlg.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ sizedlg.cpp
|

$(IntermediateDirectory)\statwind.obj :  statwind.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ statwind.cpp
|

$(IntermediateDirectory)\term.obj :  term.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ term.cpp
|

$(IntermediateDirectory)\threed.obj :  threed.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ threed.cpp
|

$(IntermediateDirectory)\utils.obj :  utils.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ utils.cpp
|

$(IntermediateDirectory)\unix.obj :  unix.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ unix.cpp
|

$(IntermediateDirectory)\vector.obj :  vector.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ vector.cpp
|

$(IntermediateDirectory)\wrksp.obj :  wrksp.cpp version.h
  $(BCC32) -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ wrksp.cpp
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
-v-
-R-
-k-
-N
-H=LOGO.CSM
-Og
-Oi
-Ov
-Z
-O
-Oe
-Ol
-Ob
-OW
-O-a
-Om
-Op
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
-w-pia
-waus
-wcln
-w-sig
-w-ucp
-O-d
-OS
-5
-W
-H"owl\pch.h"
-d
| $@

