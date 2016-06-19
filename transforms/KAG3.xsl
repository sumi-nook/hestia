<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" encoding="UTF-8"/>
<xsl:template match="/div">
<xsl:text>
; see also &lt;http://kopacurve.blog33.fc2.com/blog-entry-206.html&gt;

[position layer=message1 color=0x000000 top=260 left=20 width=200 height=40 opacity=200 visible=true margint=4]
[position layer=message0 color=0x000000 top=310 left=20 height=150 width=600 opacity=200]

; [text]
[macro name=text][position layer=message1 visible=false][position layer=message0 color=0x000000 top=310 left=20 height=150 width=600 opacity=200][endmacro]

; [/text]
[macro name=/text][p][cm][endmacro]

; [NamePlate]
[macro name=NamePlate][position layer=message1 visible=true][current layer=message1][nowait][emb exp="mp.name"][endnowait][endmacro]

; [Name]
[macro name=Name][NamePlate *][current layer=message0][endmacro]

[cm]
</xsl:text>
<xsl:apply-templates/>
<xsl:text></xsl:text>
</xsl:template>

<xsl:template match="p[contains(@class, 'speech')]">
<xsl:text>[Name name="</xsl:text>
<xsl:apply-templates select="span[contains(@class, 'name')]"/>
<xsl:text>"]
</xsl:text>
<xsl:apply-templates select="span[contains(@class, 'name')]/following-sibling::node()"/>
<xsl:text>[p][cm]
</xsl:text>
</xsl:template>

<xsl:template match="p[contains(@class, 'description')]">
<xsl:text>
[text]
</xsl:text>
<xsl:apply-templates/>
<xsl:text>
[/text]</xsl:text>
</xsl:template>

<xsl:template match="a">
<xsl:text></xsl:text>
<xsl:value-of select="text()"/>
<xsl:text></xsl:text>
</xsl:template>

<xsl:template match="br">
<xsl:text>[r]
</xsl:text>
</xsl:template>

<xsl:template match="span[contains(@class, 'name')]">
<xsl:text></xsl:text>
<xsl:value-of select="text()"/>
<xsl:text></xsl:text>
</xsl:template>

<xsl:template match="span[contains(@class, 'text')]">
<xsl:text></xsl:text>
<xsl:value-of select="text()"/>
<xsl:text></xsl:text>
</xsl:template>

<xsl:template match="ruby">
<xsl:text></xsl:text>
<xsl:apply-templates select="rt"/>
<xsl:apply-templates select="rb"/>
<xsl:text></xsl:text>
</xsl:template>

<xsl:template match="rb">
<xsl:text></xsl:text>
<xsl:value-of select="text()"/>
<xsl:text></xsl:text>
</xsl:template>

<xsl:template match="rt">
<xsl:text>[ruby text=</xsl:text>
<xsl:value-of select="text()"/>
<xsl:text>]</xsl:text>
</xsl:template>

<xsl:template match="img[@class='background']">
<xsl:text>[image storage="</xsl:text>
<xsl:value-of select="@src"/>
<xsl:text>" page=fore layer=base]

</xsl:text>
</xsl:template>

</xsl:stylesheet>
