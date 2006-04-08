EXTRAS_VERSION=0.9

SOURCEZIP=fmslogo-extras-$(EXTRAS_VERSION).zip

all : $(SOURCEZIP) ;

TOINCLUDE= \
  README.TXT    \
  asteriodminer \
  boink         \
  domino        \
  lightcycle    \
  ludo          \
  midipiano     \
  pacturtle     \
  snake         \
  sudoku        \

$(SOURCEZIP) :
	$(RM) **/*~
	cd .. && zip -r -9 -X $(SOURCEZIP) $(addprefix extras/,$(TOINCLUDE)) -x */.cvsignore */CVS/ */CVS/* */*/.cvsignore */*/CVS/ */*/CVS/* */*/*/CVS/
	mv ../$(SOURCEZIP) .
