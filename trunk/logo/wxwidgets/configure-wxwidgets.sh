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

export PATH=/usr/bin:$PATH
export MAKE=gmake
./configure --with-msw --with-expat=builtin --enable-debug_gdb --enable-debug-flag --enable-monolithic --disable-shared --disable-optimise --disable-sockets --with-libstc --with-libstl --with-libjpeg=no --host=i686-pc-mingw32
