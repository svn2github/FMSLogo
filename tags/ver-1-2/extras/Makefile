EXTRAS_VERSION=1.2

SOURCEZIP=fmslogo-extras-$(EXTRAS_VERSION).zip

all : $(SOURCEZIP) ;

TOINCLUDE= \
  README.TXT    \
  CHANGELOG.TXT \
  asteriodminer \
  boink         \
  domino        \
  lightcycle    \
  ludo          \
  midipiano     \
  pacturtle     \
  snake         \
  sudoku        \
  tetrads       \

$(SOURCEZIP) :
	$(RM) $(shell /usr/bin/find release -name '*~')
	$(RM) $(shell /usr/bin/find release -name '*.bak')
	$(RM) $(shell /usr/bin/find release -name AM_Hiscores)
	cd .. && zip -r -9 -X $(SOURCEZIP) $(addprefix extras/,$(TOINCLUDE)) -x */.cvsignore */CVS/ */CVS/* */*/.cvsignore */*/CVS/ */*/CVS/* */*/*/CVS/
	mv ../$(SOURCEZIP) .

