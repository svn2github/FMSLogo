#! bash

###########################################################################
# This file is a reminder of how I built wxwidgets on Windows.
#
# Use the script like:
#   cd <wxwidgets_top_dir>
#   bash <path_to_this_script>/configure-wxwidgets.sh
#   gmake all
#   gmake -D contrib all

export PATH=/usr/bin:$PATH
export MAKE=gmake
./configure --with-msw --with-expat=builtin --enable-debug_gdb --enable-debug-flag --enable-monolithic --disable-shared --disable-optimise --with-libstc --with-libstl --with-libjpeg=no
