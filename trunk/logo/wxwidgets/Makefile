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

ifneq "$(PROFILE)" "1"
# On retail builds, strip symbols unless we need them for profiling.
# CONSIDER: using a separate variable for offiical releases to strip. 
LDFLAGS  += -s
endif

TOOLCHAIN_FULLNAME = msw-ansi-release-static-2.8
endif

TARGET_PREFIX=i686-pc-mingw32-

LDFLAGS  += -mwindows

TOOLKIT = MSW
TOOLKIT_LOWERCASE = msw
TOOLKIT_VERSION = 
EXTRALIBS = -static-libgcc -static-libstdc++ -lrpcrt4 -loleaut32 -lole32 -luuid -lwinspool -lwinmm -lshell32 -lcomctl32 -lcomdlg32 -lctl3d32 -ladvapi32 -lwsock32 -lgdi32 -luser32 -limm32 

MANUAL = logohelp.chm

endif

# Setup the build for profiling, if requested.
ifeq "$(PROFILE)" "1"
CFLAGS   += -pg
CXXFLAGS += -pg
LDFLAGS  += -pg
endif

INCLUDES = . $(wx_top_builddir)/lib/wx/include/$(TOOLCHAIN_FULLNAME) $(wx_top_builddir)/include $(wx_top_builddir)/contrib/include ../src
CPPFLAGS += -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES $(addprefix -I, $(INCLUDES))
CXXFLAGS += -Wall -Wundef -Wno-ctor-dtor-privacy -fno-strict-aliasing
CXXFLAGS += -DFMSLOGO_WXWIDGETS
CXXFLAGS += -DSCI_LEXER -DLCCWIN=0 # used by Scintilla.h
CXXFLAGS += -I"/cygdrive/c/Program Files/HTML Help Workshop/include"

# Meet FMSLogo's minimum system requirements
CXXFLAGS += -march=pentium


#BK_DEPS = $(wx_top_builddir)/bk-deps
LIBS = -lm
CXX = $(TARGET_PREFIX)g++

### Variables: ###

WX_RELEASE = 2.8
WX_VERSION = $(WX_RELEASE).4
LIBDIRNAME = $(wx_top_builddir)/lib
CXXFLAGS  += -D__WX$(TOOLKIT)__ $(CPPFLAGS)

OBJECTS =                      \
    3dsolid.o                  \
    LexFmsLogo.o               \
    aboutfmslogo.o             \
    aboutmultiplesclerosis.o   \
    activearea.o               \
    appendablelist.o           \
    argumentutils.o            \
    assembly.o                 \
    commander.o                \
    commanderbutton.o          \
    commanderhistory.o         \
    commanderinput.o           \
    commandertogglebutton.o    \
    coms.o                     \
    cursor.o                   \
    devwind.o                  \
    dib.o                      \
    dllwind.o                  \
    dynamicbuffer.o            \
    editproceduredialog.o      \
    eraseproceduredialog.o     \
    error.o                    \
    eval.o                     \
    files.o                    \
    fileswnd.o                 \
    fmslogo.o                  \
    fontutils.o                \
    gbm.o                      \
    gbmbmp.o                   \
    gbmgif.o                   \
    gbmhelp.o                  \
    gbmsize.o                  \
    graphics.o                 \
    graphwin.o                 \
    guiutils.o                 \
    helputils.o                \
    ibmterm.o                  \
    init.o                     \
    intern.o                   \
    lists.o                    \
    localizednode.o            \
    logocodectrl.o             \
    logodata.o                 \
    logodialogboxes.o          \
    logoeventqueue.o           \
    logomath.o                 \
    mainframe.o                \
    mainwind.o                 \
    mem.o                      \
    messagebox.o               \
    minieditor.o               \
    minieditortextctrl.o       \
    mmwind.o                   \
    netwind.o                  \
    paren.o                    \
    parse.o                    \
    print.o                    \
    savebeforeexitdialog.o     \
    screen.o                   \
    selectproceduredialog.o    \
    selectstartupinstruction.o \
    setactivearea.o            \
    setcolor.o                 \
    setpensize.o               \
    startup.o                  \
    statusdialog.o             \
    stringprintednode.o        \
    term.o                     \
    threed.o                   \
    unix.o                     \
    utils.o                    \
    vector.o                   \
    workspaceeditor.o          \
    wrksp.o                    \

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

obj/$(1)-%.o : %.cpp
	$(CXX) -c -o $$@ $(CXXFLAGS) -DLOCALE=$1 $$<

obj/$(1)-%.o : ../src/%.cpp
	$(CXX) -c -o $$@ $(CXXFLAGS) -DLOCALE=$1 $$<

obj/$(1)-%.o : ../src/scintilla/src/%.cxx
	$(CXX) -c -o $$@ $(CXXFLAGS) -DLOCALE=$1 -I../src/scintilla/include $$<

obj/$(1)-%_rc.o : %.rc
	$(WINDRES) -i$$< -o$$@ -DLOCALE=$1 --define __WX$(TOOLKIT)__ $(addprefix --include-dir ,$(INCLUDES))


ifeq "$(TOOLKIT)" "GTK"

obj/$(1)-%.o: linux/%.cpp
	$(CXXC) -c -o $$@ $(CXXFLAGS) -DLOCALE=$1 $$<

endif

fmslogo_rc.o: fmslogo.rc

endef

$(foreach lcid,$(LCIDS),$(eval $(call FMSLOGO_template,$(lcid))))

# Include dependency info, if present:
-include .deps/*.d

.PHONY: all clean default
