<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="people">
		<html>
			<head><title>Famous scientists</title></head>
			<body>
				<ul><xsl:apply-templates select="person" mode="toc"/></ul>
				<xsl:apply-templates select="person"/>
			</body>
		</html>
	</xsl:template>
	<!-- Table of Contents Mode Templates -->
	<xsl:template match="person" mode="toc">
		<xsl:apply-templates select="name" mode="toc"/>
	</xsl:template>
	<xsl:template match="name" mode="toc">
		<li><xsl:value-of select="last_name"/>,
		<xsl:value-of select="first_name"/></li>
	</xsl:template>
	<xsl:template match="person">
		<p><xsl:apply-templates/></p>
	</xsl:template>
</xsl:stylesheet>
