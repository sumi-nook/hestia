<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" encoding="UTF-8"/>
<xsl:template match="/div">
<xsl:text></xsl:text>
<xsl:apply-templates/>
<xsl:text></xsl:text>
</xsl:template>

<xsl:template match="p[contains(@class, 'speech')]">
<xsl:text></xsl:text>
<xsl:apply-templates/>
<xsl:text>
</xsl:text>
</xsl:template>

<xsl:template match="p[contains(@class, 'description')]">
<xsl:text></xsl:text>
<xsl:apply-templates/>
<xsl:text>
</xsl:text>
</xsl:template>

<xsl:template match="a">
<xsl:text></xsl:text>
<xsl:value-of select="text()"/>
<xsl:text></xsl:text>
</xsl:template>

<xsl:template match="br">
<xsl:text>
</xsl:text>
</xsl:template>

<xsl:template match="span[contains(@class, 'name')]">
<xsl:text>【</xsl:text>
<xsl:value-of select="text()"/>
<xsl:text>】</xsl:text>
</xsl:template>

<xsl:template match="span[contains(@class, 'text')]">
<xsl:text></xsl:text>
<xsl:value-of select="text()"/>
<xsl:text></xsl:text>
</xsl:template>

<xsl:template match="ruby">
<xsl:text></xsl:text>
<xsl:apply-templates select="rb"/>
<xsl:apply-templates select="rt"/>
<xsl:text></xsl:text>
</xsl:template>

<xsl:template match="rb">
<xsl:text>[</xsl:text>
<xsl:value-of select="text()"/>
<xsl:text>]</xsl:text>
</xsl:template>

<xsl:template match="rt">
<xsl:text>(ruby:</xsl:text>
<xsl:value-of select="text()"/>
<xsl:text>)</xsl:text>
</xsl:template>

<xsl:template match="img[@class='background']">
<xsl:text>※背景：</xsl:text>
<xsl:value-of select="@src"/>
<xsl:if test="@alt and @alt!=''">
<xsl:text>：</xsl:text>
<xsl:value-of select="@alt"/>
</xsl:if>
<xsl:text>

</xsl:text>
</xsl:template>

<xsl:template match="img">
<xsl:text>![</xsl:text>
<xsl:value-of select="@alt"/>
<xsl:text>](</xsl:text>
<xsl:value-of select="@src"/>
<xsl:text>)</xsl:text>
</xsl:template>

</xsl:stylesheet>
