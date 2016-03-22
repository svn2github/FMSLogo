MAKENSIS="C:\Program Files\NSIS\makensis.exe"

include ../lcids.mk

EXECUTABLES  = $(addprefix ../src/fmslogo-,     $(addsuffix .exe,        $(LCIDS)))
STARTUPFILES = $(addprefix ../src/startup-,     $(addsuffix .logoscript, $(LCIDS)))
HELPFILES    = $(addprefix ../manual/logohelp-, $(addsuffix .chm,        $(LCIDS)))

all : fmslogo.exe

fmslogo.exe : fmslogo.nsi ../version.mk $(EXECUTABLES) $(STARTUPFILES) $(HELPFILES)
	$(MAKENSIS) $<

clean :
	$(RM) fmslogo.exe
