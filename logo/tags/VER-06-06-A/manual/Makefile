STYLESHEET=/usr/share/sgml/docbook/xsl-stylesheets-1.68.1-1/htmlhelp/profile-htmlhelp.xsl

all : logohelp.hhp ;


logohelp.hhp : logohelp.xml
	xsltproc --nonet $(STYLESHEET) $<

clean :
	$(RM) *.html *.hhp *.hhc *.chm *~

