# A wrapper for the real Makefile, which uses Borland's "make"
# This wrapper helps integrate the Makefile into an otherwise
# GNU-based build system
.PHONY : clean test fmslogod.exe

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
	$(RM) $(wildcard version.h)
	$(RM) $(wildcard BccW32.cfg)
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
	$(RM) $(wildcard Examples/3d/3dmovie.gif)

tags : *.cpp *.h *.c
	etags localizedstrings-en.h $(shell /usr/bin/find . -iname '*.cpp' -o -iname '*.h' -o -iname '*.c' -o -iname '*.cxx')

screensaver :
	$(MAKE) -C ../screensaver

test :
	perl ../../extras/check-extra.pl Logolib/*
	perl ../../extras/check-extra.pl Examples/3d/*.LGO
	perl ../../extras/check-extra.pl Examples/Misc/*.LGO
	perl ../../extras/check-extra.pl Examples/Multimed/*.LGO
	perl ../../extras/check-extra.pl Examples/Network/*.LGO
	perl ../../extras/check-extra.pl Examples/Pascal/*.LGO
	perl ../../extras/check-extra.pl Examples/UCBLogo/*.LGO
	perl ../../extras/check-extra.pl Examples/Windows/*.LGO


# a phony target that always gets remade
FORCE :

