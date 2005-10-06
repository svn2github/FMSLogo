VERSION=6.6

SOURCEZIP=fmslogo-src-$(VERSION).zip

all : $(SOURCEZIP) ;

$(SOURCEZIP) :
	$(RM) **/*~
	zip -r -9 -X $@ bc5 setup 

upload : $(SOURCEZIP)
	scp $(SOURCEZIP) root@et.bgcbellevue.org:/var/www/html/logo/download

