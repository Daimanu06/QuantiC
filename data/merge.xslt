<?xml version="1.0" encoding="utf-8"?>
<xsl:transform version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="xml" indent="yes" standalone="yes" encoding="utf-8" />
	<!-- Command-line parameters -->
	<xsl:param name="trfile" />
	<xsl:param name="lang" />
	<!-- Constants -->
	<xsl:variable name="symbol">unicode</xsl:variable> <!-- Type of symbol -->
	<xsl:variable name="trnode" select="document( concat('translations/', $lang, '/', $trfile) )/translation" />

	<!-- Main template -->
	<xsl:template match="/quantity">
		<quantity name="{$trnode/@name}" lang="{$lang}" prefixsAllowed="{@prefixsAllowed}">
			<xsl:apply-templates select="legalunit" />
			<xsl:apply-templates select="unit" />
		</quantity>
	</xsl:template>

	<xsl:template match="legalunit">
		<legalunit name="{$trnode/legalunit/name/singular/text()}">
			<symbol>
				<xsl:value-of select="*[name()=$symbol]" />
			</symbol>
			<xsl:if test="minimum">
			<minimum>
				<xsl:value-of select="minimum" />
			</minimum>
			</xsl:if>
			<xsl:if test="maximum">
				<maximum>
					<xsl:value-of select="maximum" />
				</maximum>
			</xsl:if>
		</legalunit>
	</xsl:template>

	<xsl:template match="unit">
		<unit name="{$trnode/unit[@name=current()/@name]/name/singular/text()}">
			<symbol>
				<xsl:value-of select="*[name()=$symbol]" />
			</symbol>
			<fromLegal>
				<xsl:copy-of select="fromLegalUnit/*" />
			</fromLegal>
			<toLegal>
				<xsl:copy-of select="toLegalUnit/*" />
			</toLegal>
		</unit>
	</xsl:template>
</xsl:transform>
