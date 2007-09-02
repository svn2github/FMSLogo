include version.mk
include lcids.mk

BINARYBASENAME=fmslogo-$(FMSLOGO_VERSION)
BINARYZIP=$(BINARYBASENAME).zip
BINARYEXE=$(BINARYBASENAME).exe
SOURCEZIP=fmslogo-src-$(FMSLOGO_VERSION).zip

ZIPEXCLUDE=\*/.cvsignore \*/CVS/ \*/CVS/\* \*/\*/.cvsignore \*/\*/CVS/ \*/\*/CVS/\* \*/\*/\*/CVS/ \*/\*/\*/CVS/\*

MANUALS = $(addprefix manual/logohelp-, $(addsuffix .chm, $(LCIDS)))
EXES    = $(addprefix src/fmslogo-, $(addsuffix .exe, $(LCIDS)))

.SECONDARY : $(MANUALS) $(EXES) setup/fmslogo.exe $(BINARYEXE) $(BINARYZIP) $(SOURCEZIP)

# top level targets
binaryexe : $(BINARYEXE) ;
binaryzip : $(BINARYZIP) ;
sourcezip : $(SOURCEZIP) ;
all : sourcezip binaryzip binaryexe;

# make the executable
src/fmslogo-%.exe : src/*.cpp src/*.h version.mk
	$(MAKE) -C src $(notdir $@)

# make the documentation
manual/logohelp-%.chm : manual/*.xml version.mk
	$(MAKE) -C manual $(notdir $@)

# make the installer
setup/fmslogo.exe : $(MANUALS) $(EXES)
	$(MAKE) -C setup all

# make the binary self-extracting executable release
$(BINARYEXE) : setup/fmslogo.exe ;
	cp $< $@


# make the binary ZIP release
$(BINARYZIP) : $(MANUALS) $(EXES)
	mkdir $(BINARYBASENAME)
	cp src/fmslogo-1032.exe        $(BINARYBASENAME)
	cp src/fmslogo-1033.exe        $(BINARYBASENAME)
	cp src/fmslogo-1034.exe        $(BINARYBASENAME)
	cp src/fmslogo-1036.exe        $(BINARYBASENAME)
	cp src/fmslogo-1040.exe        $(BINARYBASENAME)
	cp src/fmslogo-2070.exe        $(BINARYBASENAME)
	cp src/fmslogo-1033.exe        $(BINARYBASENAME)/fmslogo.exe
	cp src/startup-1032.logoscript $(BINARYBASENAME)
	cp src/startup-1033.logoscript $(BINARYBASENAME)
	cp src/startup-1034.logoscript $(BINARYBASENAME)
	cp src/startup-1036.logoscript $(BINARYBASENAME)
	cp src/startup-1040.logoscript $(BINARYBASENAME)
	cp src/startup-2070.logoscript $(BINARYBASENAME)
	cp src/startup-1033.logoscript $(BINARYBASENAME)/startup.logoscript
	cp manual/logohelp-1032.chm    $(BINARYBASENAME)
	cp manual/logohelp-1033.chm    $(BINARYBASENAME)
	cp manual/logohelp-1034.chm    $(BINARYBASENAME)
	cp manual/logohelp-1036.chm    $(BINARYBASENAME)
	cp manual/logohelp-1040.chm    $(BINARYBASENAME)
	cp manual/logohelp-2070.chm    $(BINARYBASENAME)
	cp manual/logohelp-1033.chm    $(BINARYBASENAME)/logohelp.chm
	cp src/FMSLOGO.TXT             $(BINARYBASENAME)
	cp src/LICENSE.TXT             $(BINARYBASENAME)
	cp src/mcistrwh.hlp            $(BINARYBASENAME)
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
	zip -r -9 -X $@ Makefile version.mk src manual setup -x $(ZIPEXCLUDE)

clean :
	-$(MAKE) -C src    $@
	-$(MAKE) -C manual $@
	-$(MAKE) -C setup  $@
