.PHONY : all clean test

include ../version.mk
include ../lcids.mk

CC  = i686-w64-mingw32-gcc
CXX = i686-w64-mingw32-g++
RC  = windres --preprocessor=$(CXX) --preprocessor-arg=-E --preprocessor-arg=-xc-header

INCLUDES = -I../src -I"C:\Program Files\HTML Help Workshop\include"
DEFINES=FMSLOGO_SCREENSAVER
CPPFLAGS=$(INCLUDES) $(addprefix -D,$(DEFINES))

DEBUG_CFLAGS   += -Wall -Wundef -O0 -g -DDEBUG -DMEM_DEBUG
DEBUG_CXXFLAGS += $(DEBUG_CFLAGS) -Wno-ctor-dtor-privacy

RELEASE_CFLAGS   += -Wall -Wundef -O2 -fno-strict-aliasing -DNDEBUG
RELEASE_CXXFLAGS += $(RELEASE_CFLAGS) -Wno-ctor-dtor-privacy

LDFLAGS=-mwindows

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
    dlgwind.o           \
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
    sort.o              \
    startup.o           \
    status.o            \
    stringprintednode.o \
    screensaver.o       \
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
    uuid     \
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
$(TARGET)d.scr : $(addprefix obj/debug-,$(DEBUG_OBJECTS) scrnsave.o)
	$(CXX) -o$@ $(LDFLAGS) -def:screensaver.def $^ $(addprefix -l,$(LIBS)) -static-libgcc -static-libstdc++

obj/debug-%.o: %.c
	$(CC) -c -o$@ $(DEBUG_CFLAGS) $(CPPFLAGS) -DLOCALE=$1 $<

obj/debug-%.o: %.cpp
	$(CXX) -c -o$@ $(DEBUG_CXXFLAGS) $(CPPFLAGS) -DLOCALE=$(DEFAULT_LCID) $<

obj/debug-%.o: ../src/%.cpp
	$(CXX) -c -o$@ $(DEBUG_CXXFLAGS) $(CPPFLAGS) -DLOCALE=$(DEFAULT_LCID) $<

obj/debug-%res.o : %.rc
	$(RC) $(CPPFLAGS) -DLOCALE=$(DEFAULT_LCID) --output=$@ $<

#
# Rules for building a debug version of the screensaver with Microsoft's
# compilers so that .PDB files exist for debugging with windbg.exe.
#
msdbg : $(TARGET)msdbg.scr ;
MSLIBS     = $(LIBS)
MSCPPFLAGS = $(CPPFLAGS) -I"$(PROGRAMFILES)\Microsoft SDKs\Windows\v7.0\Include" -I"$(PROGRAMFILES)\Microsoft Visual Studio 9.0\VC\include" -D_CRT_SECURE_NO_WARNINGS

$(TARGET)msdbg.scr : $(addprefix obj/msdbg-,$(DEBUG_OBJECTS))
	link.exe /nologo /OUT:$@ /DEBUG /LIBPATH:"$(PROGRAMFILES)\Microsoft SDKs\Windows\v7.0\lib" /LIBPATH:"$(PROGRAMFILES)\Microsoft Visual Studio 9.0\VC\lib" /subsystem:windows /machine:I386 $(addsuffix .lib,$(MSLIBS)) -def:screensaver.def $^

obj/msdbg-%.o: %.cpp
	cl.exe /c /nologo -Fo$@ /Od /Zi /W4 /EHsc /MTd -DDEBUG -DMEM_DEBUG $(MSCPPFLAGS) -DLOCALE=$(DEFAULT_LCID) $<

obj/msdbg-%.o: ../src/%.cpp
	cl.exe /c /nologo -Fo$@ /Od /Zi /W4 /EHsc /MTd -DDEBUG -DMEM_DEBUG $(MSCPPFLAGS) -DLOCALE=$(DEFAULT_LCID) $<

obj/msdbg-%res.o : %.rc
	rc.exe $(MSCPPFLAGS) -DLOCALE=$(DEFAULT_LCID) /fo $@ $<


#
# Generate the rules to build the release version of the screensaver for each locale
#
define FMSLOGO_SCREENSAVER_template
$$(TARGET)-$(1).scr : $$(addprefix obj/$(1)-,$$(OBJECTS) scrnsave.o)
	$(CXX) -o$$@ $(LDFLAGS) -def:screensaver.def $$^ $(addprefix -l,$(LIBS)) -static-libgcc -static-libstdc++
	strip $$@

obj/$(1)-%.o: %.c
	$(CC) -c -o$$@ $(RELEASE_CFLAGS) $(CPPFLAGS) -DLOCALE=$1 $$<

obj/$(1)-%.o: %.cpp
	$(CXX) -c -o$$@ $(RELEASE_CXXFLAGS) $(CPPFLAGS) -DLOCALE=$1 $$<

obj/$(1)-%.o: ../src/%.cpp
	$(CXX) -c -o$$@ $(RELEASE_CXXFLAGS) $(CPPFLAGS) -DLOCALE=$1 $$<

obj/$(1)-%res.o : %.rc
	$(RC) $(CPPFLAGS) -DLOCALE=$1 --output=$$@ $$<

endef

$(foreach lcid,$(LCIDS),$(eval $(call FMSLOGO_SCREENSAVER_template,$(lcid))))

clean :
	$(RM) obj/*.o
	$(RM) $(TARGET).scr $(TARGET)*.scr
	$(RM) $(TARGET)msdbg.*
	$(RM) *~
	$(RM) *.pdb

test : $(TARGET)d.scr
	rundll32.exe desk.cpl,InstallScreenSaver "C:\Documents and Settings\Dave\My Documents\logo-cvs\logo\screensaver\$(TARGET)d.scr"
