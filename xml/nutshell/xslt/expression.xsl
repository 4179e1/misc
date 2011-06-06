<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="profession">
		<xsl:if test=".='computer scientist' or .='physicist'">
			<xsl:value-of select="."/>
		</xsl:if>
	</xsl:template>
</xsl:stylesheet>
