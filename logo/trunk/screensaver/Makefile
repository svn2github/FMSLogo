.PHONY : all clean test

include ../version.mk
include ../lcids.mk

CC  = i686-w64-mingw32-gcc
CXX = i686-w64-mingw32-g++
RC  = windres --preprocessor=$(CXX) --preprocessor-arg=-E --preprocessor-arg=-xc-header

wx_top_srcdir   = /cygdrive/e/wxMSW-2.8.12-src
wx_top_builddir = /cygdrive/e/wxMSW-2.8.12

INCLUDES   = -I. -I$(wx_top_srcdir)/include -I$(wx_top_srcdir)/contrib/include -I../src -I../src/pch -I"C:\Program Files\HTML Help Workshop\include"
DEFINES    = FMSLOGO_SCREENSAVER
LIBDIRNAME = $(wx_top_builddir)/lib

CPPFLAGS   = $(INCLUDES) $(addprefix -D,$(DEFINES))
LDFLAGS    = -mwindows -L$(LIBDIRNAME)

DEBUG_CFLAGS     += -Wall -Wundef -O0 -g -DDEBUG -DMEM_DEBUG -I$(wx_top_builddir)/lib/wx/include/msw-ansi-debug-static-2.8
DEBUG_CXXFLAGS   += $(DEBUG_CFLAGS) -Wno-ctor-dtor-privacy
DEBUG_LDFLAGS    += -lwx_mswd_stc-2.8 -lwx_mswd-2.8

RELEASE_CFLAGS   += -Wall -Wundef -O2 -fno-strict-aliasing -DNDEBUG -I$(wx_top_builddir)/lib/wx/include/msw-ansi-release-static-2.8
RELEASE_CXXFLAGS += $(RELEASE_CFLAGS) -Wno-ctor-dtor-privacy
RELEASE_LDFLAGS  += -lwx_msw_stc-2.8 -lwx_msw-2.8 


OBJECTS=\
    3dsolid.o           \
    activearea.o        \
    appendablelist.o    \
    argumentutils.o     \
    avltree.o           \
    coms.o              \
    cursor.o            \
    devwind.o           \
    dib.o               \
    dllwind.o           \
    dynamicbuffer.o     \
    error.o             \
    eval.o              \
    files.o             \
    fileswnd.o          \
    gbm.o               \
    gbmbmp.o            \
    gbmhelp.o           \
    gbmgif.o            \
    gbmsize.o           \
    graphics.o          \
    graphwin.o          \
    ibmterm.o           \
    init.o              \
    intern.o            \
    lists.o             \
    localizednode.o     \
    logodata.o          \
    logodialogboxes.o   \
    logoeventqueue.o    \
    logomath.o          \
    mainwind.o          \
    mem.o               \
    messagebox.o        \
    mmwind.o            \
    netwind.o           \
    paren.o             \
    parse.o             \
    print.o             \
    questionbox.o       \
    screensaver.o       \
    selectbox.o         \
    sort.o              \
    startup.o           \
    statusdialog.o      \
    stringprintednode.o \
    term.o              \
    threed.o            \
    utils.o             \
    unix.o              \
    vector.o            \
    wrksp.o             \
    screensaverres.o    \

DEBUG_OBJECTS=          \
    $(OBJECTS)          \
    debugheap.o         \

LIBS=\
    gdi32    \
    advapi32 \
    kernel32 \
    user32   \
    scrnsave \
    comctl32 \
    ole32    \
    oleaut32 \
    uuid     \
    winmm    \
    winspool \
    wsock32  \
    comdlg32 \

TARGET=fmslogo

$(TARGET).scr : $(TARGET)-$(DEFAULT_LCID).scr
	cp $< $@

all : $(addsuffix .scr,$(addprefix $(TARGET)-,$(LCIDS)));

debug : $(TARGET)d.scr ;

#
# Rules for building the debug version of the screensaver
#
$(TARGET)d.scr : $(addprefix obj/debug-,$(DEBUG_OBJECTS) scrnsave.o)
	$(CXX) -o$@ $(LDFLAGS) -def:screensaver.def $^ $(DEBUG_LDFLAGS) $(addprefix -l,$(LIBS)) -static-libgcc -static-libstdc++

obj/debug-%.o: %.c
	$(CC) -c -o$@ $(DEBUG_CFLAGS) $(CPPFLAGS) -DLOCALE=$1 $<

obj/debug-%.o: %.cpp
	$(CXX) -c -o$@ $(DEBUG_CXXFLAGS) $(CPPFLAGS) -DLOCALE=$(DEFAULT_LCID) $<

obj/debug-%.o: ../src/%.cpp
	$(CXX) -c -o$@ $(DEBUG_CXXFLAGS) $(CPPFLAGS) -DLOCALE=$(DEFAULT_LCID) $<

obj/debug-%res.o : %.rc ../src/fmslogo.ico
	$(RC) $(CPPFLAGS) -DLOCALE=$(DEFAULT_LCID) --output=$@ $<


#
# Generate the rules to build the release version of the screensaver for each locale
#
define FMSLOGO_SCREENSAVER_template
$$(TARGET)-$(1).scr : $$(addprefix obj/$(1)-,$$(OBJECTS) scrnsave.o)
	$(CXX) -o$$@ -def:screensaver.def $$^ $(LDFLAGS) $(RELEASE_LDFLAGS) $(addprefix -l,$(LIBS)) -static-libgcc -static-libstdc++
	strip $$@

obj/$(1)-%.o: %.c
	$(CC) -c -o$$@ $(RELEASE_CFLAGS) $(CPPFLAGS) -DLOCALE=$1 $$<

obj/$(1)-%.o: %.cpp
	$(CXX) -c -o$$@ $(RELEASE_CXXFLAGS) $(CPPFLAGS) -DLOCALE=$1 $$<

obj/$(1)-%.o: ../src/%.cpp
	$(CXX) -c -o$$@ $(RELEASE_CXXFLAGS) $(CPPFLAGS) -DLOCALE=$1 $$<

obj/$(1)-%res.o : %.rc ../src/fmslogo.ico
	$(RC) $(CPPFLAGS) -DLOCALE=$1 --output=$$@ $$<

endef

$(foreach lcid,$(LCIDS),$(eval $(call FMSLOGO_SCREENSAVER_template,$(lcid))))

clean :
	$(RM) obj/*.o
	$(RM) $(TARGET).scr $(TARGET)*.scr
	$(RM) *~

# "make test" shows the debug screensaver in the Windows UI for setting the screensaver.
# The full path to the executable must be given.
#
# For easier testing:
# fmslogod.scr /s      - runs the screensaver full screen
# fmslogod.scr /c      - runs the screensaver's configuration UI
# fmslogod.scr /p hwnd - runs the screensaver in a target window (preview)
# To run the screensaver directory, run "fmslogod.scr /s".
test : $(TARGET)d.scr
	rundll32.exe desk.cpl,InstallScreenSaver "C:\Documents and Settings\Dave\My Documents\fmslogo-source\trunk\logo\screensaver\$(TARGET)d.scr"
