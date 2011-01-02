.PHONY : all clean test

include ../version.mk
include ../lcids.mk

CXX=c:/mingw/bin/gcc.exe
WINDRES=c:/mingw/bin/windres.exe

INCLUDES = -I../src -I"C:\Program Files\HTML Help Workshop\include"
DEFINES=FMSLOGO_SCREENSAVER NOASM
CPPFLAGS=$(INCLUDES) $(addprefix -D,$(DEFINES))

DEBUG_CXXFLAGS += -Wall -Wundef -Wno-ctor-dtor-privacy -O0 -g -DDEBUG -DMEM_DEBUG
RELEASE_CXXFLAGS += -Wall -Wundef -Wno-ctor-dtor-privacy -O2 -fno-strict-aliasing -DNDEBUG

LDFLAGS=-mwindows

OBJECTS=\
    3dsolid.o        \
    activearea.o     \
    appendablelist.o \
    argumentutils.o  \
    assembly.o       \
    coms.o           \
    cursor.o         \
    devwind.o        \
    dib.o            \
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
    screensaver.o    \
    threed.o         \
    utils.o          \
    unix.o           \
    vector.o         \
    wrksp.o          \
    screensaverres.o \

DEBUG_OBJECTS=       \
    $(OBJECTS)       \
    debugheap.o      \

LIBS=\
    gdi32    \
    advapi32 \
    kernel32 \
    user32   \
    scrnsave \
    comctl32 \
    uuid     \
    msvcrt   \
    stdc++   \
    winmm    \
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
$(TARGET)d.scr : $(addprefix obj/debug-,$(DEBUG_OBJECTS))
	$(CXX) -o$@ $(LDFLAGS) -def:screensaver.def $^ $(addprefix -l,$(LIBS))

obj/debug-%.o: ../src/%.cpp
	$(CXX) -c -o$@ $(DEBUG_CXXFLAGS) $(CPPFLAGS) -DLOCALE=$(DEFAULT_LCID) $<

obj/debug-%.o: %.cpp
	$(CXX) -c -o$@ $(DEBUG_CXXFLAGS) $(CPPFLAGS) -DLOCALE=$(DEFAULT_LCID) $<

obj/debug-%res.o : %.rc
	$(WINDRES) $(CPPFLAGS) -DLOCALE=$(DEFAULT_LCID) --output=$@ $<

#
# Generate the rules to build the release version of the screensaver for each locale
#
define FMSLOGO_SCREENSAVER_template
$$(TARGET)-$(1).scr : $$(addprefix obj/$(1)-,$$(OBJECTS))
	$(CXX) -o$$@ $(LDFLAGS) -def:screensaver.def $$^ $(addprefix -l,$(LIBS))

obj/$(1)-%.o: ../src/%.cpp
	$(CXX) -c -o$$@ $(RELEASE_CXXFLAGS) $(CPPFLAGS) -DLOCALE=$1 $$<

obj/$(1)-%.o: %.cpp
	$(CXX) -c -o$$@ $(RELEASE_CXXFLAGS) $(CPPFLAGS) -DLOCALE=$1 $$<

obj/$(1)-%res.o : %.rc
	$(WINDRES) $(CPPFLAGS) -DLOCALE=$1 --output=$$@ $$<

endef

$(foreach lcid,$(LCIDS),$(eval $(call FMSLOGO_SCREENSAVER_template,$(lcid))))

clean :
	$(RM) obj/*.o
	$(RM) $(TARGET).scr $(TARGET)*.scr
	$(RM) *~

test : $(TARGET)d.scr
	rundll32.exe desk.cpl,InstallScreenSaver "C:\Documents and Settings\Dave\My Documents\logo-cvs\logo\screensaver\$(TARGET)d.scr"
