SRCS += 3dsolid.cpp
SRCS += areawind.cpp
SRCS += assembly.cpp
SRCS += cmdwind.cpp
SRCS += colordlg.cpp
SRCS += commanderbutton.cpp
SRCS += coms.cpp
SRCS += devwind.cpp
SRCS += dib.cpp
SRCS += dlgwind.cpp 
SRCS += dllwind.cpp 
SRCS += editwnd.cpp 
SRCS += error.cpp 
SRCS += eval.cpp 
SRCS += files.cpp 
SRCS += fileswnd.cpp 
SRCS += gbm.cpp 
SRCS += gbmbmp.cpp 
SRCS += gbmgif.cpp 
SRCS += gbmhelp.cpp 
SRCS += gbmsize.cpp 
SRCS += graphics.cpp 
SRCS += graphwin.cpp 
SRCS += ibmterm.cpp 
SRCS += init.cpp 
SRCS += intern.cpp 
SRCS += lists.cpp 
SRCS += logodata.cpp 
SRCS += main.cpp 
SRCS += mainwind.cpp 
SRCS += math.cpp 
SRCS += mem.cpp 
SRCS += mmwind.cpp 
SRCS += myfileed.cpp 
SRCS += myfilewn.cpp 
SRCS += netwind.cpp 
SRCS += paren.cpp 
SRCS += parse.cpp 
SRCS += print.cpp 
SRCS += richedpr.cpp 
SRCS += sizedlg.cpp 
SRCS += statwind.cpp 
SRCS += term.cpp 
SRCS += threed.cpp 
SRCS += unix.cpp 
SRCS += utils.cpp 
SRCS += vector.cpp 
SRCS += wrksp.cpp
SRCS += dllstack.c

# CPPFLAGS += -I c:/cygwin/usr/include -I c:/cygwin/usr/include/w32api 
CPPFLAGS += -I c:\bc5\include
CPPFLAGS += -D_far -D_MSC_VER -D__FLAT__ -DBI_PLAT_WIN32 -DSTRICT -D_M_IX86

gccfmslogo.exe : $(SRCS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -Wall -Wshadow -Werror $< -o $@


%.i : %.cpp
	$(CPP) $(CPPFLAGS) $(INCLUDES) $< > $@

