HHP_STYLESHEET=/usr/share/sgml/docbook/xsl-stylesheets-1.68.1-1/htmlhelp/profile-htmlhelp.xsl

all : logohelp.hhp ;


logohelp.hhp : logohelp.xml
	xsltproc --nonet $(HHP_STYLESHEET) $<

logohelp.pdf : logohelp.xml
	docbook2pdf $<

logohelp.rtf : logohelp.xml
	docbook2rtf $<

clean :
	$(RM) logohelp.rtf logohelp.pdf logohelp.dvi *.html *.hhp *.hhc *.chm *~
