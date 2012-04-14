# =========================================================================
# NOTE: this makefile is a stop-gap solution for me (david costanzo) to
# to build the experimental wxWidgets on my two dev boxes.  I don't expect
# this to work for anyone else.
# =========================================================================

ifeq "$(HOSTNAME)" "dcostanz.davidcostanzo.com"

# assume this is my Fedora Core box
EXEEXT =
WINDRES = 

wx_top_builddir = /home/dcostanz/wxGTK-2.8.4

TOOLKIT = GTK
TOOLKIT_LOWERCASE = gtk
TOOLKIT_VERSION = 2
TOOLCHAIN_FULLNAME = gtk2-ansi-release-2.8
EXTRALIBS = -pthread -Wl,--version-script,$(wx_top_builddir)/version-script -lz -ldl -lm -pthread -L/lib -lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lgdk_pixbuf-2.0 -lm -lpango-1.0 -lgobject-2.0 -lgmodule-2.0 -ldl -lgthread-2.0 -lrt -lglib-2.0 -lXinerama -lSM -lpng -lz -ljpeg -ltiff -lwx_gtk2-2.8

CXXFLAGS = -pthread
CPPFLAGS = -pthread -I/usr/include/gtk-2.0 -I/usr/lib/gtk-2.0/include -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/freetype2 -I/usr/include/libpng12
# TODO: CPPFLAGS += -DWX_PRECOMP

LDFLAGS = -pthread

MANUAL =

else

# assume this is my Windows XP box

EXEEXT = .exe
WINDRES = windres

wx_top_builddir = /cygdrive/c/wxMSW-2.8.12

ifeq "$(DEBUG)" "1"
CPPFLAGS = -D__WXDEBUG__
CXXFLAGS = -O0 -g -ggdb
LDFLAGS  = -lwx_mswd_stc-2.8 -lwx_mswd-2.8
TOOLCHAIN_FULLNAME = msw-ansi-debug-static-2.8
else
CPPFLAGS =
CXXFLAGS = -Os
LDFLAGS  = -lwx_msw-2.8 -lwx_msw_stc-2.8
TOOLCHAIN_FULLNAME = msw-ansi-release-static-2.8
endif

LDFLAGS += -mwindows

TOOLKIT = MSW
TOOLKIT_LOWERCASE = msw
TOOLKIT_VERSION = 
EXTRALIBS = -lz -lrpcrt4 -loleaut32 -lole32 -luuid -lwinspool -lwinmm -lshell32 -lcomctl32 -lcomdlg32 -lctl3d32 -ladvapi32 -lwsock32 -lgdi32 -lkernel32 -luser32 -limm32 

MANUAL = logohelp.chm

endif

CPPFLAGS += -DLOCALE=1033 -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES -I$(wx_top_builddir)/lib/wx/include/$(TOOLCHAIN_FULLNAME) -I$(wx_top_builddir)/include -I$(wx_top_builddir)/contrib/include -I../src 
CXXFLAGS += -Wall -Wundef -Wno-ctor-dtor-privacy  -fno-strict-aliasing
CXXFLAGS += -DFMSLOGO_SCREENSAVER -DNOASM
CXXFLAGS += -DPLAT_WIN -DSCI_LEXER -DLCCWIN=0 # used by Scintilla.h
CXXFLAGS += -I"C:\Program Files\HTML Help Workshop\include"

prefix = /usr/local
exec_prefix = ${prefix}
INSTALL = /usr/bin/install -c
REZ = 
SETFILE = 
#BK_DEPS = $(wx_top_builddir)/bk-deps
NM = nm
srcdir = .
LIBS = -lz -ldl -lm
CXX = g++
HOST_SUFFIX = 

### Variables: ###

DESTDIR = 
WX_RELEASE = 2.8
WX_VERSION = $(WX_RELEASE).4
LIBDIRNAME = $(wx_top_builddir)/lib
SPLITTER_CXXFLAGS = -D__WX$(TOOLKIT)__ $(__WXUNIV_DEFINE_p) \
	$(__EXCEPTIONS_DEFINE_p) $(__RTTI_DEFINE_p) $(__THREAD_DEFINE_p) \
	-I$(srcdir) $(__DLLFLAG_p) $(CPPFLAGS) $(CXXFLAGS)

SPLITTER_OBJECTS =  \
        splitter_mainframe.o \
        splitter_commander.o \
        splitter_aboutfmslogo.o \
        splitter_aboutmultiplesclerosis.o \
        splitter_setactivearea.o \
        splitter_workspaceeditor.o \
        splitter_guiutils.o \
        splitter_fmslogo.o \
        splitter_logocodectrl.o \
        splitter_setpensize.o \
        splitter_statusdialog.o \
        splitter_savebeforeexitdialog.o \
        splitter_screen.o \
        splitter_commanderbutton.o \
        splitter_commandertogglebutton.o \
        splitter_commanderinput.o \
        splitter_commanderhistory.o \
        splitter_help.o \
        splitter_selectproceduredialog.o \
        splitter_editproceduredialog.o \
        splitter_eraseproceduredialog.o \
        splitter_minieditor.o \
        splitter_minieditortextctrl.o \
        splitter_fontutils.o \
        platform_utils.o \
        splitter_setcolor.o \
        core_3dsolid.o        \
        core_activearea.o     \
        core_appendablelist.o \
        core_argumentutils.o  \
        core_assembly.o       \
        core_coms.o           \
        core_cursor.o         \
        core_devwind.o        \
        core_dib.o            \
        core_dynamicbuffer.o  \
        core_error.o          \
        core_eval.o           \
        core_files.o          \
        core_fileswnd.o       \
        core_gbm.o            \
        core_gbmbmp.o         \
        core_gbmhelp.o        \
        core_gbmgif.o         \
        core_gbmsize.o        \
        core_graphics.o       \
        core_graphwin.o       \
        core_ibmterm.o        \
        core_init.o           \
        core_intern.o         \
        core_lists.o          \
        core_localizednode.o  \
        core_logodata.o       \
        core_logomath.o       \
        core_mainwind.o       \
        core_mem.o            \
        core_messagebox.o     \
        core_mmwind.o         \
        core_netwind.o        \
        core_paren.o          \
        core_parse.o          \
        core_print.o          \
        core_startup.o        \
        core_threed.o         \
        core_unix.o           \
        core_vector.o         \
        core_wrksp.o          \
        scintilla_LexFmsLogo.o \

ifeq "$(TOOLKIT)" "MSW"
SPLITTER_OBJECTS +=  \
	splitter_debugheap.o \
        splitter_fmslogo_rc.o \
	$(__splitter___win32rc)
endif

### Conditionally set variables: ###

#CXXC = $(CXX)
CXXC = $(BK_DEPS) $(CXX)
#PORTNAME = base
PORTNAME = $(TOOLKIT_LOWERCASE)$(TOOLKIT_VERSION)
__RCDEFDIR_p_1 = --include-dir \
	$(LIBDIRNAME)/wx/include/$(TOOLCHAIN_FULLNAME)

### Targets: ###

all: fmslogo$(EXEEXT) $(__splitter_bundle___depname) $(MANUAL)

install: all

uninstall: 

install-strip: install

clean: 
	rm -rf ./.deps ./.pch
	$(RM) ./*.o
	$(RM) fmslogo$(EXEEXT)
	$(RM) logohelp.chm

distclean: clean
	rm -f config.cache config.log config.status bk-deps bk-make-pch shared-ld-sh Makefile

fmslogo$(EXEEXT): $(SPLITTER_OBJECTS) $(__splitter___win32rc)
	$(CXX) -o $@ $(SPLITTER_OBJECTS) $(LDFLAGS) -L$(LIBDIRNAME) $(LIBS) $(EXTRALIBS)

splitter_%.o: $(srcdir)/%.cpp
	$(CXXC) -c -o $@ $(SPLITTER_CXXFLAGS) $<

core_%.o: $(srcdir)/../src/%.cpp
	$(CXXC) -c -o $@ $(SPLITTER_CXXFLAGS) $<

scintilla_%.o: $(srcdir)/../src/scintilla/src/%.cxx
	$(CXXC) -c -o $@ $(SPLITTER_CXXFLAGS) -I$(srcdir)/../src/scintilla/include $<

ifeq "$(TOOLKIT)" "MSW"

platform_%.o: $(srcdir)/../src/%.cpp
	$(CXXC) -c -o $@ $(SPLITTER_CXXFLAGS) $<

else

platform_%.o: $(srcdir)/linux/%.cpp
	$(CXXC) -c -o $@ $(SPLITTER_CXXFLAGS) $<

endif


splitter_fmslogo_rc.o: $(srcdir)/fmslogo.rc
	$(WINDRES) -i$< -o$@   --define __WX$(TOOLKIT)__ $(__WXUNIV_DEFINE_p_2)  $(__EXCEPTIONS_DEFINE_p_2) $(__RTTI_DEFINE_p_2) $(__THREAD_DEFINE_p_2)   --include-dir $(srcdir) $(__DLLFLAG_p_2) $(__RCDEFDIR_p_1) --include-dir $(top_srcdir)/include --include-dir $(wx_top_builddir)/include

logohelp.chm : ../manual/logohelp-1033.chm
	cp $< $@

# Include dependency info, if present:
-include .deps/*.d

.PHONY: all install uninstall clean distclean splitter_bundle
