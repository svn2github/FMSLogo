!include version.mk

SOURCEZIP=fmslogo-src-$(FMSLOGO_VERSION).zip

all : $(SOURCEZIP) ;

$(SOURCEZIP) :
	$(RM) **/*~
	zip -r -9 -X $@ bc5 setup 

upload : $(SOURCEZIP)
	scp $(SOURCEZIP) root@et.bgcbellevue.org:/var/www/html/logo/download

