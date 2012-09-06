# =========================================================================
# NOTE: this makefile is a stop-gap solution for me (david costanzo) to
# to build the experimental wxWidgets on my two dev boxes.  I don't expect
# this to work for anyone else.
# =========================================================================
include ../version.mk
include ../lcids.mk

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
CPPFLAGS = -D__WXDEBUG__ -DMEM_DEBUG -DDEBUG
CXXFLAGS = -O0 -g -ggdb
LDFLAGS  = -lwx_mswd_stc-2.8 -lwx_mswd-2.8
TOOLCHAIN_FULLNAME = msw-ansi-debug-static-2.8
else
CPPFLAGS = -DNDEBUG
CXXFLAGS = -O2
LDFLAGS  = -lwx_msw_stc-2.8 -lwx_msw-2.8 
TOOLCHAIN_FULLNAME = msw-ansi-release-static-2.8
endif

TARGET_PREFIX=i686-pc-mingw32-

LDFLAGS  += -mwindows

TOOLKIT = MSW
TOOLKIT_LOWERCASE = msw
TOOLKIT_VERSION = 
EXTRALIBS = -lrpcrt4 -loleaut32 -lole32 -luuid -lwinspool -lwinmm -lshell32 -lcomctl32 -lcomdlg32 -lctl3d32 -ladvapi32 -lwsock32 -lgdi32 -lkernel32 -luser32 -limm32 -static-libgcc -static-libstdc++

MANUAL = logohelp.chm

endif

CPPFLAGS += -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES -I$(wx_top_builddir)/lib/wx/include/$(TOOLCHAIN_FULLNAME) -I$(wx_top_builddir)/include -I$(wx_top_builddir)/contrib/include -I../src 
CXXFLAGS += -Wall -Wundef -Wno-ctor-dtor-privacy  -fno-strict-aliasing
CXXFLAGS += -DFMSLOGO_WXWIDGETS
CXXFLAGS += -DSCI_LEXER -DLCCWIN=0 # used by Scintilla.h
CXXFLAGS += -I"/cygdrive/c/Program Files/HTML Help Workshop/include"

# Meet FMSLogo's minimum system requirements
CXXFLAGS += -march=pentium


#BK_DEPS = $(wx_top_builddir)/bk-deps
srcdir = .
LIBS = -lm
CXX = $(TARGET_PREFIX)g++

### Variables: ###

DESTDIR = 
WX_RELEASE = 2.8
WX_VERSION = $(WX_RELEASE).4
LIBDIRNAME = $(wx_top_builddir)/lib
CXXFLAGS  += -D__WX$(TOOLKIT)__ -I$(srcdir) $(CPPFLAGS)

OBJECTS =                      \
    mainframe.o                \
    commander.o                \
    aboutfmslogo.o             \
    aboutmultiplesclerosis.o   \
    setactivearea.o            \
    workspaceeditor.o          \
    guiutils.o                 \
    fmslogo.o                  \
    logocodectrl.o             \
    logodialogboxes.o          \
    setpensize.o               \
    statusdialog.o             \
    savebeforeexitdialog.o     \
    screen.o                   \
    commanderbutton.o          \
    commandertogglebutton.o    \
    commanderinput.o           \
    commanderhistory.o         \
    selectstartupinstruction.o \
    selectproceduredialog.o    \
    editproceduredialog.o      \
    eraseproceduredialog.o     \
    minieditor.o               \
    minieditortextctrl.o       \
    fontutils.o                \
    utils.o                    \
    setcolor.o                 \
    3dsolid.o        \
    activearea.o     \
    appendablelist.o \
    argumentutils.o  \
    assembly.o       \
    coms.o           \
    cursor.o         \
    devwind.o        \
    dib.o            \
    dllwind.o        \
    dynamicbuffer.o  \
    error.o          \
    eval.o           \
    files.o          \
    fileswnd.o       \
    gbm.o            \
    gbmbmp.o         \
    gbmhelp.o        \
    gbmgif.o         \
    gbmsize.o        \
    graphics.o       \
    graphwin.o       \
    ibmterm.o        \
    init.o           \
    intern.o         \
    lists.o          \
    localizednode.o  \
    logodata.o       \
    logomath.o       \
    mainwind.o       \
    mem.o            \
    messagebox.o     \
    mmwind.o         \
    netwind.o        \
    paren.o          \
    parse.o          \
    print.o          \
    startup.o        \
    term.o           \
    threed.o         \
    unix.o           \
    vector.o         \
    wrksp.o          \
    LexFmsLogo.o     \

ifeq "$(TOOLKIT)" "MSW"
OBJECTS +=       \
    debugheap.o  \
    fmslogo_rc.o \

endif

### Conditionally set variables: ###

#CXXC = $(CXX)
CXXC = $(BK_DEPS) $(CXX)
PORTNAME = $(TOOLKIT_LOWERCASE)$(TOOLKIT_VERSION)
RCDEFDIR = --include-dir $(LIBDIRNAME)/wx/include/$(TOOLCHAIN_FULLNAME)

### Targets: ###

# Set the English version as the first target, which will get
# built if no target is provided to gmake.
default : fmslogo$(EXEEXT) logohelp.chm

fmslogo$(EXEEXT) : fmslogo-$(DEFAULT_LCID)$(EXEEXT)
	cp $< $@

logohelp.chm : ../manual/logohelp-1033.chm
	cp $< $@

# The "all" target is used to build all locales.
all : $(addsuffix $(EXEEXT),$(addprefix fmslogo-,$(LCIDS)));

install: all

uninstall: 

install-strip: install

clean: 
	rm -rf ./.deps ./.pch
	$(RM) obj/*.o
	$(RM) ./*.bak
	$(RM) ./*~
	$(RM) ./*.stackdump
	$(RM) fmslogo-*$(EXEEXT)
	$(RM) fmslogo$(EXEEXT)
	$(RM) logohelp.chm


#
# Generate the rules to build the release version of the screensaver for each locale
#
define FMSLOGO_template

fmslogo-$(1)$$(EXEEXT) : $$(addprefix obj/$(1)-,$$(OBJECTS))
	$(CXX) -o $$@ $$^ $(LDFLAGS) -L$(LIBDIRNAME) $(LIBS) $(EXTRALIBS)

obj/$(1)-%.o : $(srcdir)/%.cpp
	$(CXX) -c -o $$@ $(CXXFLAGS) -DLOCALE=$1 $$<

obj/$(1)-%.o : $(srcdir)/../src/%.cpp
	$(CXX) -c -o $$@ $(CXXFLAGS) -DLOCALE=$1 $$<

obj/$(1)-%.o : $(srcdir)/../src/scintilla/src/%.cxx
	$(CXX) -c -o $$@ $(CXXFLAGS) -DLOCALE=$1 -I$(srcdir)/../src/scintilla/include $$<

obj/$(1)-%_rc.o : %.rc
	$(WINDRES) -i$$< -o$$@ -DLOCALE=$1 --define __WX$(TOOLKIT)__ $(RCDEFDIR) --include-dir $(srcdir) --include-dir $(top_srcdir)/include --include-dir $(wx_top_builddir)/include


ifeq "$(TOOLKIT)" "GTK"

obj/$(1)-%.o: $(srcdir)/linux/%.cpp
	$(CXXC) -c -o $$@ $(CXXFLAGS) -DLOCALE=$1 $$<

endif

fmslogo_rc.o: $(srcdir)/fmslogo.rc

endef

$(foreach lcid,$(LCIDS),$(eval $(call FMSLOGO_template,$(lcid))))


# Include dependency info, if present:
-include .deps/*.d

.PHONY: all install uninstall clean default
