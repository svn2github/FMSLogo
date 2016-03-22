#! bash
###########################################################################
# This file is a reminder of how I built wxwidgets on Windows.
#
# Use the script like:
#   bash
#   cd <wxwidgets_top_dir>
#   Patch wxwidgets with <path_to_this_script>/wxwidgets-2.8.12.patch
#
#   <path_to_this_script>/configure-wxwidgets.sh
#   gmake clean all
#   gmake -C contrib/src/stc clean all
#
#   export DEBUG=1
#   <path_to_this_script>/configure-wxwidgets.sh
#   gmake clean all
#   gmake -C contrib/src/stc clean all
#
###########################################################################

export PATH=/usr/bin:$PATH
export MAKE=gmake

#
# The minimum system requirements for the OWL FMSLogo are Windows 95, running
# on a Pentium.  To prevent the compiler from generating instructions that
# are not supported on a Pentium, we specify -march=i586.
#
# Without this, the i686 MinGW compiler emits a CMOVNBE instruction in a
# static initializers. Since CMOVcc is only supported on Pentium Pro CPUs
# and higher, the result is that FMSLogo raises an unknown instruction
# exception on startup when run on a Pentium.
#
# For reference, the opcode of a CMOVcc is
#
#   0x0F 0x48 ..
#
export CFLAGS=-march=i586
export CXXFLAGS=-march=i586

if [ -f configarg.cache ];
then
  rm configarg.cache
fi

if [ "$DEBUG" == "1" ];
then
  export ADDITIONAL_OPTIONS="--enable-debug --enable-debug_gdb --enable-debug_info --disable-optimise"
else
  export ADDITIONAL_OPTIONS="--disable-debug --enable-optimise"

  # Enable link-time optimization so that the resulting fmslogo.exe is smaller.
  # Without this, all of the uncalled member functions remain in the final executable.
  export CFLAGS=-flto
  export CXXFLAGS=-flto
  export LDFLAGS=-flto
fi

if [ "$PROFILE" == "1" ];
then
export ADDITIONAL_OPTIONS="$ADDITIONAL_OPTIONS --enable-profile"
fi

./configure                       \
    $ADDITIONAL_OPTIONS           \
    --with-msw                    \
    --disable-rtti                \
    --disable-exceptions          \
    --with-expat=no               \
    --with-regex=no               \
    --with-libpng=no              \
    --with-zlib=no                \
    --with-libjpeg=no             \
    --with-libtiff=no             \
    --enable-monolithic           \
    --disable-shared              \
    --disable-catch_segvs         \
    --disable-toolbar             \
    --disable-aui                 \
    --disable-toolbook            \
    --disable-joystick            \
    --disable-splash              \
    --disable-tooltips            \
    --disable-sockets             \
    --disable-aboutdlg            \
    --disable-protocol            \
    --disable-protocols           \
    --disable-protocol-http       \
    --disable-protocol-ftp        \
    --disable-protocol-file       \
    --disable-ftp                 \
    --disable-http                \
    --disable-fileproto           \
    --disable-fs_archive          \
    --disable-fs_inet             \
    --disable-fs_zip              \
    --disable-url                 \
    --disable-tarstream           \
    --disable-mdi                 \
    --disable-tipdlg              \
    --disable-tipwindow           \
    --disable-largefile           \
    --disable-animatectrl         \
    --disable-dynamicloader       \
    --disable-display             \
    --disable-tga                 \
    --disable-pcx                 \
    --disable-iff                 \
    --disable-pnm                 \
    --disable-png                 \
    --disable-gif                 \
    --disable-xrc                 \
    --disable-zipstream           \
    --disable-wizarddlg           \
    --disable-threads             \
    --disable-docview             \
    --disable-help                \
    --disable-metafile            \
    --disable-dnd                 \
    --disable-dragimage           \
    --disable-miniframe           \
    --disable-calendar            \
    --disable-datepick            \
    --disable-logwindow           \
    --disable-logdialog           \
    --disable-listbook            \
    --disable-numberdlg           \
    --disable-progressdlg         \
    --disable-postscript          \
    --disable-cmdline             \
    --disable-mimetype            \
    --disable-splines             \
    --disable-unicode             \
    --disable-sysoptions          \
    --enable-no_deps              \
    --disable-dependency-tracking \
    --host=i686-w64-mingw32       \
