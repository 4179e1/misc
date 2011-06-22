<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format">
	<xsl:template match="/">
		<fo:root>
			<fo:layout-master-set>
				<!-- page masters -->
				<fo:simple-page-master margin-right="1in" margin-left="1in"
					margin-bottom="1in" margin-top="1in"
					page-width="8.5in" page-height="11in"
					master-name="first">
					<fo:region-body/>
				</fo:simple-page-master>
			</fo:layout-master-set>
			<fo:page-sequence master-reference="first">
				<fo:flow flow-name="xsl-region-body">
					<xsl:apply-templates/>
				</fo:flow>
			</fo:page-sequence>
		</fo:root>
	</xsl:template>

	<xsl:template match="directions|story">
		<fo:block margin-top="12pt" margin-left="4pt">
			<xsl:apply-templates/>
		</fo:block>
	</xsl:template>

	<xsl:template match="dish">
		<fo:block font-family="Helvetica, Arial, sans-serif" font-size="20pt" font-weight="bold" text-align="center">
			<xsl:apply-templates/>
		</fo:block>
	</xsl:template>

	<xsl:template match="ingredients">
		<fo:list-block><xsl:apply-templates/></fo:list-block>
	</xsl:template>

	<xsl:template match="ingredient">
		<fo:list-item>
				<!-- Unicode Bullet Character -->
			<fo:list-item-label>
				<fo:block>&#x2022;</fo:block>
			</fo:list-item-label>
			<fo:list-item-body>
				<fo:block><xsl:apply-templates/></fo:block>
			</fo:list-item-body>
		</fo:list-item>
	</xsl:template>

</xsl:stylesheet>


