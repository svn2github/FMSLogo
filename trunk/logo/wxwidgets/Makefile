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
EXTRALIBS = -pthread  -Wl,--version-script,$(wx_top_builddir)/version-script -lz -ldl -lm 
EXTRALIBS_GUI = -pthread -L/lib -lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lgdk_pixbuf-2.0 -lm -lpango-1.0 -lgobject-2.0 -lgmodule-2.0 -ldl -lgthread-2.0 -lrt -lglib-2.0 -lXinerama -lSM -lpng -lz -ljpeg -ltiff -lwx_gtk2-2.8

CXXFLAGS = -pthread
CPPFLAGS = -pthread -I/usr/include/gtk-2.0 -I/usr/lib/gtk-2.0/include -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/freetype2 -I/usr/include/libpng12
# TODO: CPPFLAGS += -DWX_PRECOMP

LDFLAGS = -pthread

MANUAL =

else

# assume this is my Windows XP box

EXEEXT = .exe
WINDRES = windres

wx_top_builddir = /cygdrive/c/wxWidgets-2.8.4

CXXFLAGS =
CPPFLAGS = 
LDFLAGS = -mwindows -lwx_msw-2.8 

TOOLKIT = MSW
TOOLKIT_LOWERCASE = msw
TOOLKIT_VERSION = 
TOOLCHAIN_FULLNAME = msw-ansi-release-static-2.8
EXTRALIBS =   -lz -lrpcrt4 -loleaut32 -lole32 -luuid -lwinspool -lwinmm -lshell32 -lcomctl32 -lcomdlg32 -lctl3d32 -ladvapi32 -lwsock32 -lgdi32 -lkernel32 -luser32 
EXTRALIBS_GUI = 

MANUAL = logohelp.chm

endif

CPPFLAGS += -DLOCALE=1033 -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES -I$(wx_top_builddir)/lib/wx/include/$(TOOLCHAIN_FULLNAME) -I$(wx_top_builddir)/include -I../src
CXXFLAGS += -Wall -Wundef -Wno-ctor-dtor-privacy -O0 -g -fno-strict-aliasing

prefix = /usr/local
exec_prefix = ${prefix}
INSTALL = /usr/bin/install -c
REZ = 
SETFILE = 
BK_DEPS = $(wx_top_builddir)/bk-deps
NM = nm
srcdir = .
LIBS = -lz -ldl -lm
LDFLAGS_GUI = 
CXX = g++
HOST_SUFFIX = 
SAMPLES_RPATH_FLAG = -Wl,-rpath,$(wx_top_builddir)/lib
SAMPLES_RPATH_POSTLINK = 

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
	splitter_setpensize.o \
	splitter_statusdialog.o \
	splitter_savebeforeexitdialog.o \
	splitter_screen.o \
	splitter_commanderbutton.o \
	splitter_commandertogglebutton.o \
	splitter_commanderinput.o \
	splitter_commanderhistory.o \
	splitter_help.o \
	splitter_dynamicbuffer.o \
	splitter_selectproceduredialog.o \
	splitter_editproceduredialog.o \
	splitter_eraseproceduredialog.o \
	splitter_minieditor.o \
	splitter_minieditortextctrl.o \
	splitter_fontutils.o \
	splitter_utils.o \
	splitter_logodata.o \
	splitter_setcolor.o \

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
#WXBASEPORT = _carbon
#WXDEBUGFLAG = d
#WXDEBUGFLAG = d
#WXUNICODEFLAG = u
#WXUNIVNAME = univ
EXTRALIBS_FOR_BASE = $(EXTRALIBS)
#EXTRALIBS_FOR_BASE = $(EXTRALIBS) $(EXTRALIBS_GUI)
EXTRALIBS_FOR_GUI = $(EXTRALIBS_GUI)
#EXTRALIBS_FOR_GUI = 
#__splitter___mac_setfilecmd = \
#	$(SETFILE) -a C splitter$(EXEEXT)
#__splitter___mac_rezcmd = $(__MACOSX_RESOURCES_p_1)
#__WXUNIV_DEFINE_p = -D__WXUNIVERSAL__
#__WXUNIV_DEFINE_p_1 = -d __WXUNIVERSAL__
#__WXUNIV_DEFINE_p_2 = --define __WXUNIVERSAL__
#__EXCEPTIONS_DEFINE_p = -DwxNO_EXCEPTIONS
#__EXCEPTIONS_DEFINE_p_1 = -d wxNO_EXCEPTIONS
#__EXCEPTIONS_DEFINE_p_2 = --define wxNO_EXCEPTIONS
#__RTTI_DEFINE_p = -DwxNO_RTTI
#__RTTI_DEFINE_p_1 = -d wxNO_RTTI
#__RTTI_DEFINE_p_2 = --define wxNO_RTTI
#__THREAD_DEFINE_p = -DwxNO_THREADS
#__THREAD_DEFINE_p_1 = -d wxNO_THREADS
#__THREAD_DEFINE_p_2 = --define wxNO_THREADS
#__DLLFLAG_p = -DWXUSINGDLL
#__DLLFLAG_p_1 = -d WXUSINGDLL
#__DLLFLAG_p_2 = --define WXUSINGDLL
COND_PLATFORM_OS2_1___splitter___os2_emxbindcmd = $(NM) splitter$(EXEEXT) | if \
	grep -q pmwin.763 ; then emxbind -ep splitter$(EXEEXT) ; fi
#__splitter___os2_emxbindcmd = $(COND_PLATFORM_OS2_1___splitter___os2_emxbindcmd)
__RCDEFDIR_p = -i \
	$(LIBDIRNAME)/wx/include/$(TOOLCHAIN_FULLNAME)
__RCDEFDIR_p_1 = --include-dir \
	$(LIBDIRNAME)/wx/include/$(TOOLCHAIN_FULLNAME)
#__splitter_bundle___depname = splitter_bundle
#____splitter_BUNDLE_TGT_REF_DEP = \
#	splitter.app/Contents/PkgInfo
#____splitter_BUNDLE_TGT_REF_DEP = \
#	splitter.app/Contents/PkgInfo
COND_MONOLITHIC_0___WXLIB_CORE_p = \
	-lwx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_core-$(WX_RELEASE)$(HOST_SUFFIX)
__WXLIB_CORE_p = $(COND_MONOLITHIC_0___WXLIB_CORE_p)
COND_MONOLITHIC_0___WXLIB_BASE_p = \
	-lwx_base$(WXBASEPORT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
__WXLIB_BASE_p = $(COND_MONOLITHIC_0___WXLIB_BASE_p)
#__splitter___win32rc = splitter_splitter_rc.o
COND_MONOLITHIC_1___WXLIB_MONO_p = \
	-lwx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
#__WXLIB_MONO_p = $(COND_MONOLITHIC_1___WXLIB_MONO_p)
#__LIB_TIFF_p \
#	= \
#	-lwxtiff$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
#__LIB_JPEG_p \
#	= \
#	-lwxjpeg$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
#__LIB_PNG_p \
#	= \
#	-lwxpng$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
#__LIB_ZLIB_p = \
#	-lwxzlib$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
#__LIB_ODBC_p = \
#	-lwxodbc$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
COND_WXUSE_REGEX_BUILTIN___LIB_REGEX_p = \
	-lwxregex$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
#__LIB_REGEX_p = $(COND_WXUSE_REGEX_BUILTIN___LIB_REGEX_p)
#__LIB_EXPAT_p = \
#	-lwxexpat$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
COND_TOOLKIT_MAC___MACOSX_RESOURCES_p_1 = $(REZ) -d __DARWIN__ -t APPL -d \
	__WX$(TOOLKIT)__ $(__WXUNIV_DEFINE_p_1) $(__EXCEPTIONS_DEFINE_p_1) \
	$(__RTTI_DEFINE_p_1) $(__THREAD_DEFINE_p_1) -i $(srcdir) $(__DLLFLAG_p_1) -i \
	$(srcdir)/../../samples $(__RCDEFDIR_p) -i $(top_srcdir)/include -o \
	splitter$(EXEEXT) Carbon.r sample.r
#__MACOSX_RESOURCES_p_1 = $(COND_TOOLKIT_MAC___MACOSX_RESOURCES_p_1)

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
	$(CXX) -o $@ $(SPLITTER_OBJECTS) $(LDFLAGS)   -L$(LIBDIRNAME) $(LDFLAGS_GUI) $(SAMPLES_RPATH_FLAG)  $(LIBS) $(__WXLIB_CORE_p)  $(__WXLIB_BASE_p)  $(__WXLIB_MONO_p) $(__LIB_TIFF_p) $(__LIB_JPEG_p) $(__LIB_PNG_p) $(EXTRALIBS_FOR_GUI) $(__LIB_ZLIB_p) $(__LIB_ODBC_p) $(__LIB_REGEX_p) $(__LIB_EXPAT_p) $(EXTRALIBS_FOR_BASE)
	$(__splitter___mac_rezcmd)
	$(__splitter___mac_setfilecmd)
	$(__splitter___os2_emxbindcmd)
	$(SAMPLES_RPATH_POSTLINK)


splitter_%.o: $(srcdir)/%.cpp
	$(CXXC) -c -o $@ $(SPLITTER_CXXFLAGS) $<

ifeq "$(TOOLKIT)" "MSW"

splitter_utils.o: $(srcdir)/../src/utils.cpp
	$(CXXC) -c -o $@ $(SPLITTER_CXXFLAGS) $<

else

splitter_utils.o: $(srcdir)/linux/utils.cpp
	$(CXXC) -c -o $@ $(SPLITTER_CXXFLAGS) $<

endif


splitter_dynamicbuffer.o: $(srcdir)/../src/dynamicbuffer.cpp
	$(CXXC) -c -o $@ $(SPLITTER_CXXFLAGS) $<

splitter_fmslogo_rc.o: $(srcdir)/fmslogo.rc
	$(WINDRES) -i$< -o$@   --define __WX$(TOOLKIT)__ $(__WXUNIV_DEFINE_p_2)  $(__EXCEPTIONS_DEFINE_p_2) $(__RTTI_DEFINE_p_2) $(__THREAD_DEFINE_p_2)   --include-dir $(srcdir) $(__DLLFLAG_p_2) --include-dir $(srcdir)/../../samples $(__RCDEFDIR_p_1) --include-dir $(top_srcdir)/include --include-dir $(wx_top_builddir)/include

logohelp.chm : ../manual/logohelp-1033.chm
	cp $< $@

# Include dependency info, if present:
-include .deps/*.d

.PHONY: all install uninstall clean distclean splitter_bundle
