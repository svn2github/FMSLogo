MAKENSIS='C:\Program Files\NSIS\makensis.exe'

include ../lcids.mk
include ../version.mk

EXECUTABLES  = $(addprefix ../src/fmslogo-,     $(addsuffix .exe,        $(LCIDS)))
STARTUPFILES = $(addprefix ../src/startup-,     $(addsuffix .logoscript, $(LCIDS)))
HELPFILES    = $(addprefix ../manual/logohelp-, $(addsuffix .chm,        $(LCIDS)))

NSISDEFINES =
NSISDEFINES += /DFMSLOGO_MAJOR_VERSION=$(FMSLOGO_MAJOR_VERSION)
NSISDEFINES += /DFMSLOGO_MINOR_VERSION=$(FMSLOGO_MINOR_VERSION)
NSISDEFINES += /DFMSLOGO_MICRO_VERSION=$(FMSLOGO_MICRO_VERSION)
NSISDEFINES += /DFMSLOGO_VERSION=$(FMSLOGO_VERSION)

all : fmslogo.exe

fmslogo.exe : fmslogo.nsi ../version.mk $(EXECUTABLES) $(STARTUPFILES) $(HELPFILES)
	$(MAKENSIS) $(NSISDEFINES) $<

clean :
	$(RM) fmslogo.exe
	$(RM) *.bak
	$(RM) *.~
