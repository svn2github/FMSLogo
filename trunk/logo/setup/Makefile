MAKENSIS="C:\Program Files\NSIS\makensis.exe"

all : fmslogo.exe

fmslogo.exe : fmslogo.nsi ../version.mk ../src/fmslogo.exe ../manual/logohelp.chm
	$(MAKENSIS) $<

clean :
	rm fmslogo.exe
