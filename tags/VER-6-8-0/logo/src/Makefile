# A wrapper for the real Makefile, which uses Borland's "make"
# This wrapper helps integrate the Makefile into an otherwise
# GNU-based build system
.PHONY : fmslogod.exe fmslogo.exe

all : fmslogo.exe ;
debug : fmslogod.exe ;

fmslogo.exe :
	make -fMakefile-borland-release.mk
	tdstrp32 fmslogo.exe

fmslogod.exe :
	make -fMakefile-borland-debug.mk

clean :
	$(RM) $(shell /usr/bin/find release -name '*.obj')
	$(RM) $(shell /usr/bin/find release -name '*.res')
	$(RM) $(shell /usr/bin/find -name '*.bak')
	$(RM) $(shell /usr/bin/find -name '*~')
	$(RM) fmslogo*.ils
	$(RM) fmslogo*.ilc
	$(RM) fmslogo*.ild
	$(RM) fmslogo*.ilf
	$(RM) fmslogo*.tds
	$(RM) logo32*.mrt
	$(RM) logo32*.mbt
	$(RM) logo*.csm
	$(RM) *.fts
	$(RM) *.gid
