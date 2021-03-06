# A wrapper for the real Makefile, which uses Borland's "make"
# This wrapper helps integrate the Makefile into an otherwise
# GNU-based build system
.PHONY : clean fmslogod.exe

include ../lcids.mk

EXES = $(addprefix fmslogo-, $(addsuffix .exe, $(LCIDS)))

fmslogo.exe : fmslogo-1033.exe
	cp startup-1033.logoscript startup.logoscript
	-cp ../manual/logohelp-1033.chm logohelp.chm
	cp $< $@

all : $(EXES)
	perl -W make-translation-tables.pl

fmslogo-%.exe : FORCE
	make -fMakefile-borland.mk -DLOCALECODE=$* -DBUILD=RELEASE
	tdstrp32 $@

fmslogod.exe :
	make -fMakefile-borland.mk -DBUILD=DEBUG

debug : fmslogod.exe ;

clean :
	$(RM) version.h
	$(RM) BccW32.cfg
	$(RM) $(shell /usr/bin/find . -iname '*.obj')
	$(RM) $(shell /usr/bin/find . -iname '*.res')
	$(RM) $(shell /usr/bin/find . -iname '*.bak')
	$(RM) $(shell /usr/bin/find . -iname '*~')
	$(RM) $(shell /usr/bin/find . -iname '*.csm')
	$(RM) $(wildcard toenglish-*.txt)
	$(RM) $(wildcard fromenglish-*.txt)
	$(RM) $(wildcard translations-*.xml)
	$(RM) $(wildcard fmslogo*.exe)
	$(RM) $(wildcard fmslogo*.ils)
	$(RM) $(wildcard fmslogo*.ilc)
	$(RM) $(wildcard fmslogo*.ild)
	$(RM) $(wildcard fmslogo*.ilf)
	$(RM) $(wildcard fmslogo*.tds)
	$(RM) $(wildcard logo32*.mrt)
	$(RM) $(wildcard logo32*.mbt)
	$(RM) $(wildcard *.fts)
	$(RM) $(wildcard *.gid)
	$(RM) $(shell /usr/bin/find . -iname 'logo.#*')

tags : *.cpp *.h *.c
	etags $(shell /usr/bin/find . -iname '*.cpp' -o -iname '*.h' -o -iname '*.c')

# a phony target that always gets remade
FORCE :

