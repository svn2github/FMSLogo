EXTRAS_VERSION=1.7

SOURCEZIP=fmslogo-extras-$(EXTRAS_VERSION).zip

all : $(SOURCEZIP) ;

TOINCLUDE= \
  README.TXT    \
  CHANGELOG.TXT \
  asteriodminer \
  boink         \
  domino        \
  lightcycle    \
  logoui        \
  ludo          \
  midipiano     \
  pacturtle     \
  snake         \
  sudoku        \
  tetrads       \
  turtlemaze    \

$(SOURCEZIP) :
	$(RM) $(shell /usr/bin/find . -iname '*~')
	$(RM) $(shell /usr/bin/find . -iname '*.bak')
	$(RM) asteriodminer/AM_Hiscores
	$(RM) logoui/transcript.lgo
	cd .. && zip -r -9 -X $(SOURCEZIP) $(addprefix extras/,$(TOINCLUDE)) -x */.cvsignore */CVS/ */CVS/* */*/.cvsignore */*/CVS/ */*/CVS/* */*/*/CVS/
	mv ../$(SOURCEZIP) .


test :
	@perl -w check-extra.pl $(shell /usr/bin/find . -name '*.lgo')
