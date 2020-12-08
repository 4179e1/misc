<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="person">
		<century>
			<xsl:value-of select="(((@born - (@born mod 100)) div 100) + 1)" />
		</century>
	</xsl:template>
</xsl:stylesheet>
