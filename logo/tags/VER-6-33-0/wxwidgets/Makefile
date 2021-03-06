# =========================================================================
# NOTE: this makefile is a stop-gap solution for me (david costanzo) to
# to build the experimental wxWidgets on my two dev boxes.  I don't expect
# this to work for anyone else.
# =========================================================================
include ../version.mk
include ../lcids.mk

ifeq "$(shell uname)" "Linux"

EXEEXT =

TOOLKIT = GTK

wx_top_builddir = $(shell wx-config --prefix)

ifeq "$(DEBUG)" "1"
LDFLAGS  = $(shell wx-config --debug=yes --libs base,core,stc,richtext)
TOOLCHAIN_FULLNAME = gtk2-unicode-debug-$(shell wx-config --release)
else
LDFLAGS  = $(shell wx-config --debug=no --libs base,core,stc,richtext)
TOOLCHAIN_FULLNAME = gtk2-unicode-release-$(shell wx-config --release)
endif

CPPFLAGS += $(shell wx-config --cppflags) -DWX_PURE
CXXFLAGS += -pthread -Wno-unused-variable -Wno-unused-local-typedefs -Wno-unused-function -Wno-unused-but-set-variable
LDFLAGS  += -pthread

# TODO: CPPFLAGS += -DWX_PRECOMP

else

# assume this is my Windows XP box

EXEEXT = .exe

# Compile with MinGW
RC = windres --preprocessor=$(CXX) --preprocessor-arg=-E --preprocessor-arg=-xc-header

wx_top_builddir = /cygdrive/e/wxMSW-2.8.12

ifeq "$(DEBUG)" "1"
LDFLAGS  = -lwx_mswd_stc-2.8 -lwx_mswd-2.8
TOOLCHAIN_FULLNAME = msw-ansi-debug-static-2.8
else
LDFLAGS  = -lwx_msw_stc-2.8 -lwx_msw-2.8 
TOOLCHAIN_FULLNAME = msw-ansi-release-static-2.8
endif

TARGET_PREFIX=i686-w64-mingw32-

LDFLAGS  += -mwindows

TOOLKIT = MSW

EXTRALIBS = -static-libgcc -static-libstdc++ -lrpcrt4 -loleaut32 -lole32 -luuid -lwinspool -lwinmm -lshell32 -lcomctl32 -lcomdlg32 -lctl3d32 -ladvapi32 -lwsock32 -lgdi32 -luser32 -limm32 

endif


ifeq "$(DEBUG)" "1"
CPPFLAGS += -D__WXDEBUG__ -DMEM_DEBUG -DDEBUG
CXXFLAGS += -O0 -g -ggdb
else
CPPFLAGS += -DNDEBUG
CXXFLAGS += -O2

ifneq "$(PROFILE)" "1"
# On retail builds, strip symbols unless we need them for profiling.
# CONSIDER: using a separate variable for offical releases to strip. 
LDFLAGS  += -s
endif
endif

# Setup the build for profiling, if requested.
ifeq "$(PROFILE)" "1"
CFLAGS   += -pg
CXXFLAGS += -pg
LDFLAGS  += -pg
endif

INCLUDES = . $(wx_top_builddir)/lib/wx/include/$(TOOLCHAIN_FULLNAME) $(wx_top_builddir)/include $(wx_top_builddir)/contrib/include ../src
CPPFLAGS += -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES $(addprefix -I, $(INCLUDES))
CXXFLAGS += -Wall -fno-strict-aliasing
CXXFLAGS += -DFMSLOGO_WXWIDGETS
CXXFLAGS += -DSCI_LEXER -DLCCWIN=0 # used by Scintilla.h
CXXFLAGS += -I"/cygdrive/c/Program Files/HTML Help Workshop/include"

# Meet FMSLogo's minimum system requirements
CXXFLAGS += -march=pentium


#BK_DEPS = $(wx_top_builddir)/bk-deps
LIBS = -lm
CXX = $(TARGET_PREFIX)g++

LIBDIRNAME = $(wx_top_builddir)/lib
CXXFLAGS  += -D__WX$(TOOLKIT)__ $(CPPFLAGS)

MSW_OBJECTS =                  \
    assembly.o                 \
    dib.o                      \
    dllwind.o                  \
    fmslogo_rc.o               \
    netwind.o                  \
    logodialogboxes.o          \
    mainwind.o                 \
    mmwind.o                   \

GTK_OBJECTS =                  \
    wxpurestubs.o              \

WX_OBJECTS =                   \
    LexFmsLogo.o               \
    3dsolid.o                  \
    aboutfmslogo.o             \
    aboutmultiplesclerosis.o   \
    activearea.o               \
    appendablelist.o           \
    argumentutils.o            \
    avltree.o                  \
    commander.o                \
    commanderbutton.o          \
    commanderhistory.o         \
    commanderinput.o           \
    commandertogglebutton.o    \
    coms.o                     \
    cursor.o                   \
    devwind.o                  \
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
    logoeventqueue.o           \
    logomath.o                 \
    mainframe.o                \
    mem.o                      \
    messagebox.o               \
    minieditor.o               \
    minieditortextctrl.o       \
    paren.o                    \
    parse.o                    \
    print.o                    \
    questionbox.o              \
    savebeforeexitdialog.o     \
    screen.o                   \
    selectbox.o                \
    selectproceduredialog.o    \
    selectstartupinstruction.o \
    setactivearea.o            \
    setcolor.o                 \
    setpensize.o               \
    sort.o                     \
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
    debugheap.o                \


ifeq "$(TOOLKIT)" "MSW"
OBJECTS = $(sort $(MSW_OBJECTS) $(WX_OBJECTS))
else
OBJECTS = $(sort $(GTK_OBJECTS) $(WX_OBJECTS)) 
endif

#CXXC = $(CXX)
CXXC = $(BK_DEPS) $(CXX)

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
	$(RM) $(foreach lcid,$(LCIDS),fmslogo-${lcid}$(EXEEXT))
	$(RM) fmslogo$(EXEEXT)
	$(RM) logohelp.chm


#
# Rules to create version.h
#
../src/version.h : ../version.mk
	echo \#define FMSLOGO_MAJOR_VERSION $(FMSLOGO_MAJOR_VERSION)  > $@
	echo \#define FMSLOGO_MINOR_VERSION $(FMSLOGO_MINOR_VERSION) >> $@
	echo \#define FMSLOGO_MICRO_VERSION $(FMSLOGO_MICRO_VERSION) >> $@
ifneq "$(FMSLOGO_VERSION_SUFFIX)" ""
	echo \#define FMSLOGO_PRIVATE_BUILD                          >> $@
endif
	echo \#define FMSLOGO_VERSION \"$(FMSLOGO_VERSION)\"         >> $@


#
# Generate the rules to build the release version of the screensaver for each locale
#
define FMSLOGO_template

fmslogo-$(1)$$(EXEEXT) : $$(addprefix obj/$(1)-,$$(OBJECTS))
	$(CXX) -o $$@ $$^ $(LDFLAGS) -L$(LIBDIRNAME) $(LIBS) $(EXTRALIBS)

ifeq "$(TOOLKIT)" "GTK"

obj/$(1)-%.o: linux/%.cpp
	$(CXXC) -c -o $$@ $(CXXFLAGS) -DLOCALE=$1 $$<

endif

obj/$(1)-%.o : %.cpp ../src/version.h
	$(CXX) -c -o $$@ $(CXXFLAGS) -DLOCALE=$1 $$<

obj/$(1)-%.o : ../src/%.cpp ../src/version.h
	$(CXX) -c -o $$@ $(CXXFLAGS) -DLOCALE=$1 $$<

obj/$(1)-%.o : ../src/scintilla/src/%.cxx
	$(CXX) -c -o $$@ $(CXXFLAGS) -DLOCALE=$1 -I../src/scintilla/include $$<

obj/$(1)-%_rc.o : %.rc ../src/version.h
	$(RC) -i$$< -o$$@ -DLOCALE=$1 --define __WX$(TOOLKIT)__ $(addprefix --include-dir ,$(INCLUDES))


fmslogo_rc.o: fmslogo.rc

endef

$(foreach lcid,$(LCIDS),$(eval $(call FMSLOGO_template,$(lcid))))

# Include dependency info, if present:
-include .deps/*.d

.PHONY: all clean default
