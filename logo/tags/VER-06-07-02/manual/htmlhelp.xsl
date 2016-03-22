<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<!--
  <xsl:import href="/usr/share/docbook-xsl/htmlhelp/profile-htmlhelp.xsl"/>
-->
  <xsl:import href="/usr/share/sgml/docbook/xsl-stylesheets/htmlhelp/profile-htmlhelp.xsl"/>

  <xsl:param name="htmlhelp.only" select="0"/>

  <xsl:param name="htmlhelp.chm" select="'logohelp.chm'"/>

  <xsl:param name="toc.section.depth"    select="5"/>
  <xsl:param name="chunk.section.depth"  select="5"/>
  <xsl:param name="use.id.as.filename"   select="1"/>
  <xsl:param name="chunk.first.sections" select="1"/>

  <xsl:param name="generate.section.toc.level" select="3"/>

  <xsl:param name="generate.toc">
book      toc,title,figure,table,example,equation
chapter   toc
preface   toc
section   toc
  </xsl:param>

  <xsl:param name="htmlhelp.hhc.folders.instead.books" select="1"/>
</xsl:stylesheet>
