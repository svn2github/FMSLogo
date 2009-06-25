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
BCC32   = Bcc32 +BccW32.cfg 
BCC32I  = Bcc32i +BccW32.cfg 
ILINK32 = Ilink32
BRC32   = Brc32

#
# Options
#
IDE_LinkFLAGS32 = -LC:\BC5\LIB
IDE_ResFLAGS32 = 
ResLocalOptsAtW32_fmslogodexe = -l$(LOCALECODE)

IncludePath = -I"C:\Program Files\HTML Help Workshop\include" -IC:\BC5\INCLUDE -Iscintilla\include -Iscintilla\src -Iscintilla\win32 -I.

CDefines = -DSTRICT;LOCALE=$(LOCALECODE);STATIC_BUILD;PLAT_WIN=1;_OWLPCH;SCI_NAMESPACE

CompInheritOptsAt_fmslogodexe = $(IncludePath) $(CDefines) -DNOASM;DEBUG;MEM_DEBUG;TRACE=1

!if "$(BUILD)"=="RELEASE"

LinkerLocalOptsAtW32_fmslogodexe =  -wdpl -went -wdup -wdef -wimt -wbdl -wsrf -wmsk -Tpe -aa -V4.0 -c
CompInheritOptsAt_fmslogodexe = $(IncludePath) $(CDefines) -DNDEBUG
LinkerOptsAt_fmslogodexe = $(LinkerLocalOptsAtW32_fmslogodexe)
ResOptsAt_fmslogodexe = $(ResLocalOptsAtW32_fmslogodexe)

ExecutableName=fmslogo-$(LOCALECODE).exe
IntermediateDirectory=RELEASE$(LOCALECODE)

OwlLib=owlwf.lib

!else

LinkerLocalOptsAtW32_fmslogodexe =  -v -wdpl -went -wdup -wdef -wimt -wbdl -wsrf -wmsk -Tpe -aa -V4.0 -c
CompInheritOptsAt_fmslogodexe = $(IncludePath) $(CDefines) -DNOASM;DEBUG;MEM_DEBUG;TRACE

ExecutableName=fmslogod.exe
IntermediateDirectory=DEBUG

OwlLib=owldwf.lib

!endif

LinkerInheritOptsAt_fmslogodexe = -x
LinkerOptsAt_fmslogodexe = $(LinkerLocalOptsAtW32_fmslogodexe)
ResOptsAt_fmslogodexe = $(ResLocalOptsAtW32_fmslogodexe)


# top-level target
logo32 : BccW32.cfg $(ExecutableName)
  echo MakeNode

version.h : ..\version.mk
  generate-version.bat $(FMSLOGO_MAJOR_VERSION) $(FMSLOGO_MINOR_VERSION) $(FMSLOGO_MICRO_VERSION) $(FMSLOGO_VERSION_SUFFIX)

Dep_fmslogodexe = \
   $(IntermediateDirectory)\AutoComplete.obj\
   $(IntermediateDirectory)\CallTip.obj\
   $(IntermediateDirectory)\CellBuffer.obj\
   $(IntermediateDirectory)\CharClassify.obj\
   $(IntermediateDirectory)\ContractionState.obj\
   $(IntermediateDirectory)\Decoration.obj\
   $(IntermediateDirectory)\Document.obj\
   $(IntermediateDirectory)\Editor.obj\
   $(IntermediateDirectory)\Indicator.obj\
   $(IntermediateDirectory)\KeyMap.obj\
   $(IntermediateDirectory)\LineMarker.obj\
   $(IntermediateDirectory)\PerLine.obj\
   $(IntermediateDirectory)\PlatWin.obj\
   $(IntermediateDirectory)\PositionCache.obj\
   $(IntermediateDirectory)\PropSet.obj\
   $(IntermediateDirectory)\RESearch.obj\
   $(IntermediateDirectory)\RunStyles.obj\
   $(IntermediateDirectory)\ScintillaBase.obj\
   $(IntermediateDirectory)\ScintillaWin.obj\
   $(IntermediateDirectory)\Style.obj\
   $(IntermediateDirectory)\UniConversion.obj\
   $(IntermediateDirectory)\ViewStyle.obj\
   $(IntermediateDirectory)\XPM.obj\
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
   $(IntermediateDirectory)\selectbox.obj\
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
$(IntermediateDirectory)\AutoComplete.obj+
$(IntermediateDirectory)\CallTip.obj+
$(IntermediateDirectory)\CellBuffer.obj+
$(IntermediateDirectory)\CharClassify.obj+
$(IntermediateDirectory)\ContractionState.obj+
$(IntermediateDirectory)\Decoration.obj+
$(IntermediateDirectory)\Document.obj+
$(IntermediateDirectory)\Editor.obj+
$(IntermediateDirectory)\Indicator.obj+
$(IntermediateDirectory)\KeyMap.obj+
$(IntermediateDirectory)\LineMarker.obj+
$(IntermediateDirectory)\PerLine.obj+
$(IntermediateDirectory)\PlatWin.obj+
$(IntermediateDirectory)\PositionCache.obj+
$(IntermediateDirectory)\PropSet.obj+
$(IntermediateDirectory)\RESearch.obj+
$(IntermediateDirectory)\RunStyles.obj+
$(IntermediateDirectory)\ScintillaBase.obj+
$(IntermediateDirectory)\ScintillaWin.obj+
$(IntermediateDirectory)\Style.obj+
$(IntermediateDirectory)\UniConversion.obj+
$(IntermediateDirectory)\ViewStyle.obj+
$(IntermediateDirectory)\XPM.obj+
$(IntermediateDirectory)\3dsolid.obj+
$(IntermediateDirectory)\appendablelist.obj+
$(IntermediateDirectory)\areawind.obj+
$(IntermediateDirectory)\assembly.obj+
$(IntermediateDirectory)\cmdwind.obj+
$(IntermediateDirectory)\colordlg.obj+
$(IntermediateDirectory)\commanderbutton.obj+
$(IntermediateDirectory)\commandercheckbox.obj+
$(IntermediateDirectory)\coms.obj+
!if "$(BUILD)"=="DEBUG"
$(IntermediateDirectory)\debugheap.obj+
!endif
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
$(IntermediateDirectory)\selectbox.obj+
$(IntermediateDirectory)\sizedlg.obj+
$(IntermediateDirectory)\statwind.obj+
$(IntermediateDirectory)\term.obj+
$(IntermediateDirectory)\threed.obj+
$(IntermediateDirectory)\utils.obj+
$(IntermediateDirectory)\unix.obj+
$(IntermediateDirectory)\vector.obj+
$(IntermediateDirectory)\wrksp.obj
$<,$*
$(OwlLib)+
bidsf.lib+
ctl3d32.lib+
import32.lib+
cw32.lib
logo32.def
$(IntermediateDirectory)\logorc.res

|

# rule for compiling .cxx files into .obj
{scintilla\src}.cxx{$(IntermediateDirectory)}.obj:
  $(BCC32) -P -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ $<
|

{scintilla\win32}.cxx{$(IntermediateDirectory)}.obj:
  $(BCC32) -P -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ $<
|

# rule for compiling .cpp files into .obj
{.}.cpp{$(IntermediateDirectory)}.obj:
  $(BCC32) -P -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ $<
|

# rule for compiling .c files into .obj
{.}.c{$(IntermediateDirectory)}.obj:
  $(BCC32) -P- -c @&&|
 $(CompOptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -o$@ $<
|

# rule for compiling .rc files into .res
{.}.rc{$(IntermediateDirectory)}.res:
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_fmslogodexe) $(CompInheritOptsAt_fmslogodexe) -FO$@ $<
|

# dependency information
$(IntermediateDirectory)\3dsolid.obj           : version.h
$(IntermediateDirectory)\appendablelist.obj    : version.h
$(IntermediateDirectory)\assembly.obj          : version.h
$(IntermediateDirectory)\areawind.obj          : version.h
$(IntermediateDirectory)\cmdwind.obj           : version.h
$(IntermediateDirectory)\colordlg.obj          : version.h
$(IntermediateDirectory)\commanderbutton.obj   : version.h
$(IntermediateDirectory)\commandercheckbox.obj : version.h
$(IntermediateDirectory)\coms.obj              : version.h
$(IntermediateDirectory)\debugheap.obj         : version.h
$(IntermediateDirectory)\devwind.obj           : version.h
$(IntermediateDirectory)\dib.obj               : version.h
$(IntermediateDirectory)\dlgwind.obj           : version.h
$(IntermediateDirectory)\dllstack.obj          : version.h
$(IntermediateDirectory)\dllwind.obj           : version.h
$(IntermediateDirectory)\dynamicbuffer.obj     : version.h
$(IntermediateDirectory)\editwnd.obj           : version.h
$(IntermediateDirectory)\error.obj             : version.h
$(IntermediateDirectory)\eval.obj              : version.h
$(IntermediateDirectory)\files.obj             : version.h
$(IntermediateDirectory)\fileswnd.obj          : version.h
$(IntermediateDirectory)\gbm.obj               : version.h
$(IntermediateDirectory)\gbmbmp.obj            : version.h
$(IntermediateDirectory)\gbmhelp.obj           : version.h
$(IntermediateDirectory)\gbmgif.obj            : version.h
$(IntermediateDirectory)\gbmsize.obj           : version.h
$(IntermediateDirectory)\graphics.obj          : version.h
$(IntermediateDirectory)\graphwin.obj          : version.h
$(IntermediateDirectory)\ibmterm.obj           : version.h
$(IntermediateDirectory)\init.obj              : version.h
$(IntermediateDirectory)\intern.obj            : version.h
$(IntermediateDirectory)\lists.obj             : version.h
$(IntermediateDirectory)\logodata.obj          : version.h
$(IntermediateDirectory)\logorc.res            : version.h localizedstrings*.h
$(IntermediateDirectory)\main.obj              : version.h
$(IntermediateDirectory)\mainwind.obj          : version.h
$(IntermediateDirectory)\math.obj              : version.h
$(IntermediateDirectory)\mem.obj               : version.h
$(IntermediateDirectory)\minieditor.obj        : version.h
$(IntermediateDirectory)\mmwind.obj            : version.h
$(IntermediateDirectory)\myfileed.obj          : version.h
$(IntermediateDirectory)\myfilewn.obj          : version.h
$(IntermediateDirectory)\netwind.obj           : version.h
$(IntermediateDirectory)\paren.obj             : version.h
$(IntermediateDirectory)\parse.obj             : version.h
$(IntermediateDirectory)\print.obj             : version.h
$(IntermediateDirectory)\richedpr.obj          : version.h
$(IntermediateDirectory)\savebeforeexitdialog.obj : version.h
$(IntermediateDirectory)\selectbox.obj         : version.h
$(IntermediateDirectory)\sizedlg.obj           : version.h
$(IntermediateDirectory)\statwind.obj          : version.h
$(IntermediateDirectory)\term.obj              : version.h
$(IntermediateDirectory)\threed.obj            : version.h
$(IntermediateDirectory)\utils.obj             : version.h
$(IntermediateDirectory)\unix.obj              : version.h
$(IntermediateDirectory)\vector.obj            : version.h
$(IntermediateDirectory)\wrksp.obj             : version.h
$(IntermediateDirectory)\scintillabase.obj     : version.h
$(IntermediateDirectory)\scintillawin.obj      : version.h


# Compiler configuration file

!if "$(BUILD)"=="RELEASE"

BccW32.cfg : 
   Copy &&|
-w
-R
-v
-WM-
-vi
-H
-v-
-R-
-k-
-N
-H=$(IntermediateDirectory)\LOGO.CSM
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
-d
| $@

!else

# Compiler configuration file
BccW32.cfg : 
   Copy &&|
-w
-R
-v
-WM-
-vi
-H
-v
-R
-k
-N
-H=$(IntermediateDirectory)\LOGO.CSM
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

!endif
