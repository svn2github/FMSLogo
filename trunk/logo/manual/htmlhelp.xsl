<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:import href="/usr/share/sgml/docbook/xsl-stylesheets-1.68.1-1/htmlhelp/profile-htmlhelp.xsl"/>
  <xsl:param name="htmlhelp.chm" select="'logohelp.chm'"/>

  <xsl:param name="toc.section.depth"    select="5"/>
  <xsl:param name="chunk.section.depth"  select="5"/>
  <xsl:param name="use.id.as.filename"   select="1"/>
  <xsl:param name="chunk.first.sections" select="1"/>
</xsl:stylesheet>
