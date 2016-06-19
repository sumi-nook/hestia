タイトル: スクリプト変換
種類: 標準

# スクリプト変換

シナリオファイルから抽出した構造データはXSLTを用いてスクリプトへ変換されます。

## XSLT変換

[XSLT]はXMLを変換するための関数型言語で、XMLに適用することでテキストファイルを生成します。

XHTML:
```
<div>
<p class="description"><span class="text">こんにちは。</span></p>
<p class="description"><span class="text">ごきげんよろしゅう。</span></p>
</div>
```

XSLT:
```
<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" encoding="UTF-8"/>

<xsl:template match="/div">
<xsl:text>[wait time=200]
*start|スタート
[cm]
</xsl:text>
<xsl:apply-templates/>
</xsl:template>

<xsl:template match="p[contains(@class, 'description')]">
<xsl:apply-templates/>
<xsl:text>[l][r]</xsl:text>
</xsl:template>

<xsl:template match="span[contains(@class, 'text')]">
<xsl:value-of select="text()"/>
</xsl:template>
</xsl:stylesheet>
```

KAG3 Script:
```
[wait time=200]
*start|スタート
[cm]

こんにちは。[l][r]
ごきげんよろしゅう。[l][r]

```


[XSLT]: https://www.w3.org/TR/xslt20/
