<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="people">
		<xsl:apply-templates select="person"/>
	</xsl:template>

	<xsl:template match="person">
			Person <xsl:value-of select="position()" /> of <xsl:value-of select="count(//person)"/>
			<xsl:value-of select="name"/>
	</xsl:template>
</xsl:stylesheet>
