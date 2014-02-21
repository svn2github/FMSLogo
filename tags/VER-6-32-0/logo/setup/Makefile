MAKENSIS='C:\Program Files\NSIS\makensis.exe'

include ../lcids.mk
include ../version.mk

EXECUTABLES    = $(addprefix ../src/fmslogo-,       $(addsuffix .exe,        $(LCIDS)))
WXEXECUTABLES  = $(addprefix ../wxwidgets/fmslogo-, $(addsuffix .exe,        $(LCIDS)))
STARTUPFILES   = $(addprefix ../src/startup-,       $(addsuffix .logoscript, $(LCIDS)))
HELPFILES      = $(addprefix ../manual/logohelp-,   $(addsuffix .chm,        $(LCIDS)))

NSISDEFINES =
NSISDEFINES += /DFMSLOGO_MAJOR_VERSION=$(FMSLOGO_MAJOR_VERSION)
NSISDEFINES += /DFMSLOGO_MINOR_VERSION=$(FMSLOGO_MINOR_VERSION)
NSISDEFINES += /DFMSLOGO_MICRO_VERSION=$(FMSLOGO_MICRO_VERSION)
NSISDEFINES += /DFMSLOGO_VERSION=$(FMSLOGO_VERSION)

default : fmslogo.exe

all : fmslogo.exe wxfmslogo.exe

# Build the installer for the OWL project
fmslogo.exe : fmslogo.nsi ../version.mk $(EXECUTABLES) $(STARTUPFILES) $(HELPFILES)
	$(MAKENSIS) $(NSISDEFINES) /DFMSLOGO_OUTPUT_FILE=$@ /DFMSLOGO_EXE_PATH=src $<

# Build the installer for the wxWidgets project
wxfmslogo.exe : fmslogo.nsi ../version.mk $(WXEXECUTABLES) $(STARTUPFILES) $(HELPFILES)
	$(MAKENSIS) $(NSISDEFINES) /DFMSLOGO_OUTPUT_FILE=$@ /DFMSLOGO_EXE_PATH=wxwidgets $<

clean :
	$(RM) fmslogo.exe wxfmslogo.exe
	$(RM) *.bak
	$(RM) *~
