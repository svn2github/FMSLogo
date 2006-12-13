MAKENSIS="C:\Program Files\NSIS\makensis.exe"

all : fmslogo.exe

EXECUTABLES = $(addprefix ../src/,fmslogo-1032.exe fmslogo-1033.exe fmslogo-1036.exe)
HELPFILES   = $(addprefix ../manual/,logohelp-1032.chm logohelp-1032.chm logohelp-1036.chm)

fmslogo.exe : fmslogo.nsi ../version.mk $(EXECUTABLES) $(HELPFILES)
	$(MAKENSIS) $<

clean :
	$(RM) fmslogo.exe
