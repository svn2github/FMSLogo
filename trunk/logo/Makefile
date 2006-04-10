include version.mk

BINARYBASENAME=fmslogo-$(FMSLOGO_VERSION)
BINARYZIP=$(BINARYBASENAME).zip
BINARYEXE=$(BINARYBASENAME).exe
SOURCEZIP=fmslogo-src-$(FMSLOGO_VERSION).zip

ZIPEXCLUDE=*/.cvsignore */CVS/ */CVS/* */*/.cvsignore */*/CVS/ */*/CVS/* */*/*/CVS/ */*/*/CVS/*

# top level targets
binaryexe : $(BINARYEXE) ;
binaryzip : $(BINARYZIP) ;
sourcezip : $(SOURCEZIP) ;
all : sourcezip binaryzip binaryexe;

# make the executable
src/fmslogo.exe : src/*.cpp src/*.h version.mk
	$(MAKE) -C src -f makefile-gmake.mk all

# make the documentation
manual/logohelp.chm : manual/*.xml version.mk
	$(MAKE) -C manual logohelp.chm

# make the installer
setup/fmslogo.exe : src/fmslogo.exe manual/logohelp.chm
	$(MAKE) -C setup all

# make the binary self-extracting executable release
$(BINARYEXE) : setup/fmslogo.exe ;
	cp $< $@


# make the binary ZIP release
$(BINARYZIP) : setup/fmslogo.exe manual/logohelp.chm
	mkdir $(BINARYBASENAME)
	cp src/fmslogo.exe     $(BINARYBASENAME)
	cp manual/logohelp.chm $(BINARYBASENAME)
	cp src/FMSLOGO.TXT     $(BINARYBASENAME)
	cp src/LICENSE.TXT     $(BINARYBASENAME)
	cp src/mcistrwh.hlp    $(BINARYBASENAME)
	cp --recursive src/Logolib  $(BINARYBASENAME)
	cp --recursive src/Examples $(BINARYBASENAME)
	chmod --recursive a+rx $(BINARYBASENAME)
	touch $(BINARYBASENAME)/deleteme~
	/usr/bin/find $(BINARYBASENAME) -name '*~' | xargs rm
	zip -r -9 -X $@ $(BINARYBASENAME) -x $(ZIPEXCLUDE)
	rm -rf $(BINARYBASENAME)

# make the source release
$(SOURCEZIP) :
	touch deleteme~
	rm $(shell /usr/bin/find -name '*~')
	touch deleteme.obj
	rm $(shell /usr/bin/find -name '*.obj')
	zip -r -9 -X $@ Makefile version.mk src manual setup -x $(ZIPEXCLUDE)

clean :
	-$(MAKE) -C src    -f makefile-gmake.mk $@
	-$(MAKE) -C manual $@
	-$(MAKE) -C setup  $@
