#! bash

###########################################################################
# This file is a reminder of how I built wxwidgets on Windows.
#
# Use the script like:
#   bash
#   rm configarg.cache
#   cd <wxwidgets_top_dir>
#   <path_to_this_script>/configure-wxwidgets.sh
#   gmake clean all
#   gmake -C contrib/src/stc clean all
#
#
# Note that these configuration options will not build an executable that is compatible
# with Windows 95.  More specifically, the i686 MinGW runtime uses a CMOVNBE instruction
# in a static initializer.  CMOVcc is only supported on Pentium Pro CPUs and higher.
# Since Windows 95 is supported on lower CPUs, this can potentially cause FMSLogo to
# execute an illegal instruction.  For reference, the opcode is
#
#   0x0F 0x48
#
# To address this, the code must be compiled with a --host that uses a GCC from an older
# version of MinGW (3.4.2 seems to work).

export PATH=/usr/bin:$PATH
export MAKE=gmake

if [ "$DEBUG" == "1" ];
then
  export ADDITIONAL_OPTIONS="--enable-debug --enable-debug_gdb --enable-debug_info --disable-optimise"
else
  export ADDITIONAL_OPTIONS="--disable-debug --enable-optimise"
fi

./configure                \
    $ADDITIONAL_OPTIONS    \
    --with-msw             \
    --with-expat=builtin   \
    --enable-monolithic    \
    --disable-shared       \
    --disable-sockets      \
    --disable-protocols    \
    --disable-ftp          \
    --disable-http         \
    --disable-tarstream    \
    --disable-mdi          \
    --disable-tipdlg       \
    --disable-largefile    \
    --disable-tga          \
    --disable-pcx          \
    --disable-iff          \
    --disable-pnm          \
    --disable-wizarddlg    \
    --with-libstc          \
    --with-libstl          \
    --with-libjpeg=no      \
    --enable-no_deps       \
    --host=i686-pc-mingw32 \
