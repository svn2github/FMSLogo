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
	$(RM) version.h
	$(RM) $(shell /usr/bin/find release -name '*.obj')
	$(RM) $(shell /usr/bin/find release -name '*.res')
	$(RM) $(shell /usr/bin/find -name '*.bak')
	$(RM) $(shell /usr/bin/find -name '*~')
	$(RM) $(wildcard fmslogo*.ils)
	$(RM) $(wildcard fmslogo*.ilc)
	$(RM) $(wildcard fmslogo*.ild)
	$(RM) $(wildcard fmslogo*.ilf)
	$(RM) $(wildcard fmslogo*.tds)
	$(RM) $(wildcard logo32*.mrt)
	$(RM) $(wildcard logo32*.mbt)
	$(RM) $(wildcard logo*.csm)
	$(RM) $(wildcard *.fts)
	$(RM) $(wildcard *.gid)
