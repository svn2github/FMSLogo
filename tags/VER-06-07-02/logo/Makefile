include version.mk

SOURCEZIP=fmslogo-src-$(FMSLOGO_VERSION).zip

all : $(SOURCEZIP) ;

$(SOURCEZIP) :
	$(RM) **/*~
	zip -r -9 -X $@ src manual setup -x */.cvsignore */CVS/ */CVS/* */*/.cvsignore */*/CVS/ */*/CVS/* */*/*/CVS/ */*/*/CVS/*
