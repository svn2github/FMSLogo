#! bash

###########################################################################
# This file is a reminder of how I built wxwidgets on Windows.
#
# Use the script like:
#   bash
#   cd <wxwidgets_top_dir>
#   <path_to_this_script>/configure-wxwidgets.sh
#   gmake
#   gmake -C contrib
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
./configure --with-msw --with-expat=builtin --enable-debug_gdb --enable-debug-flag --enable-monolithic --disable-shared --disable-optimise --disable-sockets --with-libstc --with-libstl --with-libjpeg=no --host=i686-pc-mingw32
