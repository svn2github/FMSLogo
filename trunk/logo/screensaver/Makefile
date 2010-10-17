.PHONY : all clean test

include ../version.mk
include ../lcids.mk

# I couldn't figure out how to get the screensaver to build under
# cygwin (I wasn't able to link to functions within scrnsave.lib),
# so this requires the Microsoft SDK.
CXX=cl.exe
LINK=link.exe
RC=rc.exe

INCLUDES = -I"$(PROGRAMFILES)\Microsoft SDKs\Windows\v7.0\Include" -I"$(PROGRAMFILES)\Microsoft Visual Studio 9.0\VC\include" -I../src
DEFINES=FMSLOGO_SCREENSAVER LOCALE=$(LOCALECODE) _CRT_SECURE_NO_WARNINGS
CPPFLAGS=$(INCLUDES) $(addprefix -D,$(DEFINES))

DEBUG_CXXFLAGS=/Od /Zi /W4 /EHsc -DDEBUG -DMEM_DEBUG
RELEASE_CXXFLAGS=/O2 /Zi /W4 /EHsc -DNDEBUG

LDFLAGS=/LIBPATH:"$(PROGRAMFILES)\Microsoft SDKs\Windows\v7.0\lib" /LIBPATH:"$(PROGRAMFILES)\Microsoft Visual Studio 9.0\VC\lib" /subsystem:windows /machine:I386

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
    screensaver.res  \


LIBS=\
    gdi32    \
    advapi32 \
    kernel32 \
    user32   \
    scrnsave \
    comctl32 \
    uuid     \
    libcmt   \
    winmm    \
    ws2_32   \
    comdlg32 \

TARGET=fmslogo

$(TARGET).scr : $(TARGET)-$(DEFAULT_LCID).scr
	cp $< $@

all : $(addsuffix .scr,$(addprefix $(TARGET)-,$(LCIDS)));

debug : $(TARGET)d.scr ;

#
# Rules for building the debug version of the screensaver
#
$(TARGET)d.scr : $(addprefix obj/debug-,$(OBJECTS))
	$(LINK) /nologo /OUT:$@ /DEBUG $(LDFLAGS) $(addsuffix .lib,$(LIBS)) -def:screensaver.def $^

obj/debug-%.o: ../src/%.cpp
	$(CXX) /c /nologo -Fo$@ $(DEBUG_CXXFLAGS) $(CPPFLAGS) -DLOCALE=$(DEFAULT_LCID) $<

obj/debug-%.o: %.cpp
	$(CXX) /c /nologo -Fo$@ $(DEBUG_CXXFLAGS) $(CPPFLAGS) -DLOCALE=$(DEFAULT_LCID) $<

obj/debug-%.res : %.rc
	$(RC) $(CPPFLAGS) -DLOCALE=$(DEFAULT_LCID) /fo $@ $<

#
# Generate the rules to build the release version of the screensaver for each locale
#
define FMSLOGO_SCREENSAVER_template
$$(TARGET)-$(1).scr : $$(addprefix obj/$(1)-,$$(OBJECTS))
	$$(LINK) /nologo /OUT:$$@ $$(LDFLAGS) $$(addsuffix .lib,$$(LIBS)) -def:screensaver.def $$^

obj/$(1)-%.o: ../src/%.cpp
	$(CXX) /c /nologo -Fo$$@ $(RELEASE_CXXFLAGS) $(CPPFLAGS) -DLOCALE=$(1) $$<

obj/$(1)-%.o: %.cpp
	$(CXX) /c /nologo -Fo$$@ $(RELEASE_CXXFLAGS) $(CPPFLAGS) -DLOCALE=$(1) $$<

obj/$(1)-%.res : %.rc
	$(RC) /fo $$@ $(CPPFLAGS) -DLOCALE=$(1) $$<

endef

$(foreach lcid,$(LCIDS),$(eval $(call FMSLOGO_SCREENSAVER_template,$(lcid))))

clean :
	$(RM) obj/*.o
	$(RM) obj/*screensaver.res
	$(RM) $(TARGET).scr $(TARGET)*.scr
	$(RM) $(TARGET).ilk $(TARGET)d.ilk
	$(RM) $(TARGET)*.exp
	$(RM) $(TARGET)*.lib 
	$(RM) $(TARGET)*.scr.manifest
	$(RM) vc90.pdb
	$(RM) $(TARGET)*.pdb
	$(RM) RCa*
	$(RM) *~
	$(RM) logohelp.chm

test : $(TARGET)d.scr
	rundll32.exe desk.cpl,InstallScreenSaver "C:\Documents and Settings\Dave\My Documents\logo-cvs\logo\screensaver\$(TARGET)d.scr"
