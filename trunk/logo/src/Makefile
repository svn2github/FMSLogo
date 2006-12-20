# A wrapper for the real Makefile, which uses Borland's "make"
# This wrapper helps integrate the Makefile into an otherwise
# GNU-based build system
.PHONY : clean fmslogod.exe

fmslogo.exe : fmslogo-1033.exe
	cp startup-1033.logoscript startup.logoscript
	-cp ..\manual\logohelp-1033.chm ..\manual\logohelp.chm
	cp $< $@

toenglish-1036.txt : make-translation-tables.pl
	perl -W make-translation-tables.pl

all : fmslogo-1033.exe fmslogo-1036.exe fmslogo-1032.exe
	perl -W make-translation-tables.pl

fmslogo-%.exe : FORCE
	make -fMakefile-borland.mk -DLOCALECODE=$* -DBUILD=RELEASE
	tdstrp32 $@

fmslogod.exe :
	make -fMakefile-borland.mk -DBUILD=DEBUG

debug : fmslogod.exe ;

clean :
	$(RM) version.h
	$(RM) $(shell /usr/bin/find . -name '*.obj')
	$(RM) $(shell /usr/bin/find . -name '*.res')
	$(RM) $(shell /usr/bin/find . -name '*.bak')
	$(RM) $(shell /usr/bin/find . -name '*~')
	$(RM) $(wildcard fmslogo*.exe)
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

tags : *.cpp *.h *.c
	etags $(shell /usr/bin/find . -name '*.cpp' -o -name '*.h' -o -name '*.c')

# a phony target that always gets remade
FORCE :

