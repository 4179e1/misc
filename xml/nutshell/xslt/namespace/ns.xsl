<?xml version="1.0"?>
<xsl:stylesheet version="1.0"
		xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
		xmlns:pe="http://www.cafeconleche.org/namespaces/people">
	<xsl:template match="pe:name">
		<xsl:value-of select="pe:last_name"/>,
		<xsl:value-of select="pe:first_name"/>
	</xsl:template>
	<xsl:template match="pe:person">
		<xsl:apply-templates select="pe:name"/>
	</xsl:template>
</xsl:stylesheet>
