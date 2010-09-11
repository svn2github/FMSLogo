include ../version.mk

ifndef LOCALECODE
   # English-US
   LOCALECODE=1033
endif


# I couldn't figure out how to get this to build under
# cygwin (I wasn't able to link to functions within scrnsave.lib),
# so this requires the Microsoft SDK.
CXX=cl.exe
LINK=link.exe
RC=rc.exe

INCLUDES = -I"$(PROGRAMFILES)\Microsoft SDKs\Windows\v7.0\Include" -I"$(PROGRAMFILES)\Microsoft Visual Studio 9.0\VC\include" -I../src
DEFINES=FMSLOGO_SCREENSAVER LOCALE=$(LOCALECODE) _CRT_SECURE_NO_WARNINGS
CPPFLAGS=$(INCLUDES) $(addprefix -D,$(DEFINES))

# TODO: debug and release modes
CXXFLAGS=/Od /Zi /W4 /EHsc

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

$(TARGET).scr : $(OBJECTS)
	$(LINK) /nologo /OUT:$@ /DEBUG $(LDFLAGS) $(addsuffix .lib,$(LIBS)) -def:screensaver.def $^

%.o: %.cpp
	$(CXX) /c /nologo -Fo$@ $(CXXFLAGS) $(CPPFLAGS) $<

%.o: ../src/%.cpp
	$(CXX) /c /nologo -Fo$@ $(CXXFLAGS) $(CPPFLAGS) $<

%.res : %.rc
	$(RC) $(CPPFLAGS) $<

clean :
	$(RM) $(OBJECTS) $(TARGET).scr $(TARGET).exp $(TARGET).lib $(TARGET).scr.manifest vc90.pdb $(TARGET).pdb RCa*

test : $(TARGET).scr
	rundll32.exe desk.cpl,InstallScreenSaver "C:\Documents and Settings\Dave\My Documents\logo-cvs\logo\screensaver\$(TARGET).scr"
