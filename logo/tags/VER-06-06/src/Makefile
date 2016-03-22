.LIS_FILE shoebox.cmd
.KEEP_LIS
.PRECIOUS

.MEMSWAP lint

.INIT :
      %setenv INCLUDE=D:\BC5\INCLUDE

.cpp.lob:
        lint co-bc4.lnt opt.lnt -u -os($*.OUT) $< -oo($@)

# Declare the source files
CSRC= LIBLOC.CPP\
 UNIX.CPP\
 IBMTERM.CPP\
 TERM.CPP\
 VECTOR.CPP\
 INTERN.CPP\
 COMS.CPP\
 ERROR.CPP\
 COLORDLG.CPP\
 AREAWIND.CPP\
 CMDWIND.CPP\
 FILES.CPP\
 STATWIND.CPP\
 FILEWND.CPP\
 PARSE.CPP\
 DDECLNT.CPP\
 MAIN.CPP\
 LOGODATA.CPP\
 FILESWND.CPP\
 MATH.CPP\
 MEM.CPP\
 EVAL.CPP\
 PAREN.CPP\
 PRINT.CPP\
 WRKSP.CPP\
 INIT.CPP\
 GRAPHWIN.CPP\
 FIXEDIT.CPP\
 SIZEDLG.CPP\
 MAINWIND.CPP\
 GRAPHICS.CPP\
 MYFILEWN.CPP\
 DEVWIND.CPP\
 DIB.CPP\
 MMWIND.CPP\
 DLLWIND.CPP\
 DLGWIND.CPP\
 NETWIND.CPP\
 LISTS.CPP\
 THREED.CPP\
 RICHEDPR.CPP\
 EDITWND.CPP\
 MYFILEED.CPP\
 ASSEMBLY.CPP

LOBS = $[f,,$(CSRC),lob]

# Build Global dependency report
lint.out : $(LOBS)
     copy < <
$[s,"\n",$(LOBS)]
< tmp.lnt
    -lint opt.lnt -os($@) tmp.lnt

# Build Global proto.h (Protocal Definitions) from function defintions
proto.h : $(LOBS)
     copy < <
$[s,"\n",$(LOBS)]
< tmp.lnt
    -lint opt.lnt -odif(proto.h) tmp.lnt

#################  end of makefile

