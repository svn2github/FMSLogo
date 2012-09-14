include version.mk
include lcids.mk

BINARYBASENAME=fmslogo-$(FMSLOGO_VERSION)
BINARYZIP=$(BINARYBASENAME).zip
BINARYEXE=$(BINARYBASENAME).exe
WXBINARYEXE=wx$(BINARYBASENAME).exe
SOURCEZIP=fmslogo-src-$(FMSLOGO_VERSION).zip

ZIPEXCLUDE=\*/.cvsignore \*/CVS/ \*/CVS/\* \*/\*/.cvsignore \*/\*/CVS/ \*/\*/CVS/\* \*/\*/\*/CVS/ \*/\*/\*/CVS/\*

MANUALS      = $(addprefix manual/logohelp-,     $(addsuffix .chm, $(LCIDS)))
EXES         = $(addprefix src/fmslogo-,         $(addsuffix .exe, $(LCIDS)))
WXEXES       = $(addprefix wxwidgets/fmslogo-,   $(addsuffix .exe, $(LCIDS)))
SCREENSAVERS = $(addprefix screensaver/fmslogo-, $(addsuffix .scr, $(LCIDS)))

.SECONDARY : $(MANUALS) $(EXES) $(SCREENSAVERS) setup/fmslogo.exe $(BINARYEXE) $(BINARYZIP) $(SOURCEZIP)

# top level targets
binaryexe : $(BINARYEXE) ;
binaryzip : $(BINARYZIP) ;
sourcezip : $(SOURCEZIP) ;
all : sourcezip binaryzip binaryexe;

# make the executables
src/fmslogo-%.exe : src/*.cpp src/*.h version.mk
	$(MAKE) -C src $(notdir $@)

# make the wxwidgets-based executables
wxwidgets/fmslogo-%.exe : wxwidgets/*.cpp wxwidgets/*.h src/*.cpp src/*.h version.mk
	$(MAKE) -C wxwidgets $(notdir $@)

# make the screensaver
screensaver/fmslogo-%.scr : screensaver/*.cpp screensaver/*.h src/*.cpp src/*.h version.mk
	$(MAKE) -C screensaver $(notdir $@)

# make the documentation
manual/logohelp-%.chm : manual/*.xml version.mk
	$(MAKE) -C manual $(notdir $@)

# make the installers
setup/fmslogo.exe : $(EXES) $(SCREENSAVERS) $(MANUALS)
	$(MAKE) -C setup $(notdir $@)

setup/wxfmslogo.exe : $(WXEXES) $(SCREENSAVERS) $(MANUALS)
	$(MAKE) -C setup $(notdir $@)

# make the binary self-extracting executable release
$(BINARYEXE) : setup/fmslogo.exe ;
	cp $< $@

$(WXBINARYEXE) : setup/wxfmslogo.exe ;
	cp $< $@


# make the binary ZIP release
$(BINARYZIP) : $(MANUALS) $(EXES) $(SCREENSAVERS)
	mkdir $(BINARYBASENAME)
	$(foreach EXE,$(EXES),                cp $(EXE)           $(BINARYBASENAME) &&) cp src/fmslogo-$(DEFAULT_LCID).exe         $(BINARYBASENAME)/fmslogo.exe
	$(foreach LCID,$(LCIDS),cp src/startup-$(LCID).logoscript $(BINARYBASENAME) &&) cp src/startup-$(DEFAULT_LCID).logoscript  $(BINARYBASENAME)/startup.logoscript
	$(foreach MANUAL,$(MANUALS),          cp $(MANUAL)        $(BINARYBASENAME) &&) cp manual/logohelp-$(DEFAULT_LCID).chm     $(BINARYBASENAME)/logohelp.chm
	$(foreach SCREENSAVER,$(SCREENSAVERS),cp $(SCREENSAVER)   $(BINARYBASENAME) &&) cp screensaver/fmslogo-$(DEFAULT_LCID).scr $(BINARYBASENAME)/fmslogo.scr
	cp src/README.TXT              $(BINARYBASENAME)
	cp src/LICENSE.TXT             $(BINARYBASENAME)
	cp src/turtle.bmp              $(BINARYBASENAME)
	cp --recursive src/Logolib     $(BINARYBASENAME)
	cp --recursive src/Examples    $(BINARYBASENAME)
	chmod --recursive a+rx $(BINARYBASENAME)
	$(RM) $(shell /usr/bin/find $(BINARYBASENAME) -name '*~')
	zip -r -9 -X $@ $(BINARYBASENAME) -x $(ZIPEXCLUDE)
	rm -rf $(BINARYBASENAME)

# make the source release
$(SOURCEZIP) :
	$(RM) $(shell /usr/bin/find -name '*~')
	$(RM) $(shell /usr/bin/find -name '*.obj')
	$(RM) $(shell /usr/bin/find -name '*.bak')
	zip -r -9 -X $@ Makefile lcids.mk version.mk HOWTO-BUILD.txt src screensaver manual setup -x $(ZIPEXCLUDE)

clean :
	-$(MAKE) -C src         $@
	-$(MAKE) -C manual      $@
	-$(MAKE) -C screensaver $@
	-$(MAKE) -C setup       $@
