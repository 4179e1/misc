<?xml version="1.0"?>
<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:template match="/">
    <dl>
      <xsl:apply-templates select="descendant::person"/>
    </dl>
  </xsl:template>

  <xsl:template match="person">
    <dt><xsl:value-of select="child::name"/></dt>
    <dd>
      <ul>
        <xsl:apply-templates select="child::name/following-sibling::*"/>
      </ul>
    </dd>
  </xsl:template>

  <xsl:template match="*">
    <li><xsl:value-of select="self::*"/></li>
  </xsl:template>

  <xsl:template match="homepage"
               xmlns:xlink="http://www.w3.org/1999/xlink">
    <li><xsl:value-of select="attribute::xlink:href"/></li>
  </xsl:template>
</xsl:stylesheet>
