<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="people">
		<html>
			<head><title>Famous scientists</title></head>
			<body>
				<xsl:apply-templates/>
			</body>
		</html>
	</xsl:template>
	<xsl:template match="name">
		<xsl:value-of select="last_name"/>,
		<xsl:value-of select="first_name"/>
	</xsl:template>
	<xsl:template match="person">
		<xsl:apply-templates select="name"/>
		<dd><ul>
			<li>Born: <xsl:apply-templates select="@born"/></li>
			<li>Died: <xsl:apply-templates select="@died"/></li>
		</ul></dd>
	</xsl:template>
</xsl:stylesheet>
