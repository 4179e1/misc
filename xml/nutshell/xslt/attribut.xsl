<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:template match="name">
		<name 	first="{first_name}"
				initial="{middle_initial}"
				last="{last_name}"/>
	</xsl:template>
</xsl:stylesheet>
