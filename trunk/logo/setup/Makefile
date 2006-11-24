MAKENSIS="C:\Program Files\NSIS\makensis.exe"

all : fmslogo.exe

fmslogo.exe : fmslogo.nsi ../version.mk ../src/fmslogo-1033.exe ../src/fmslogo-1036.exe ../manual/logohelp.chm
	$(MAKENSIS) $<

clean :
	$(RM) fmslogo.exe
