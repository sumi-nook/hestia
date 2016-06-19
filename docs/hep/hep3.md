タイトル: シナリオファイル
種類: 標準

# シナリオファイル

シナリオファイルはMarkdownの文法を基にして、基本的な表現を行います。

シナリオファイルは内部でXHTML形式に変換され、構造データを構築します。

## エンコーディング

シナリオファイルのテキストエンコーディングは[UTF-8]を使用しなければなりません。

## Markdown

MarkdownはJohn Gruber氏によって提案された書式です。 \[[Markdown]]

### 用いる表現

#### 段落

Markdown:
```
行と行の間には空行が必要になります。

空行を挟まない行は
改行命令を挟んで一つのパラグラフにまとめられます。
```

XHTML:
```
<div>
<p><span class="text">行と行の間には空行が必要になります。</span></p>
<p><span class="text">空行を挟まない行は</span><br /><span class="text">改行命令を挟んで一つのパラグラフにまとめられます。</span></p>
</div>
```

## Markdown Hestia拡張

ただのMarkdownではシナリオ表現に必要な表現が不足しています。

そのため、MarkdownにHestia拡張を施します。

### 台詞表現

ADV形式のノベルゲーム等では名前が独立した表現となっています。

Markdown:
```
【名前】「セリフ」

台詞表現以外は地の文。
```

XHTML:
```
<div>
<p class="speech"><span class="name">名前</span><span class="text">「セリフ」</span></p>
<p class="description"><span class="text">台詞表現以外は地の文。</span></p>
</div>
```

### ルビ表現

いくつかのノベルエンジンではルビ機能が実装されています。

Markdown:
```
これは[Ruby](ruby:ルビ)表現
```

XHTML:
```
<div>
<p class="description"><span class="text">これは</span><ruby><rb>Ruby</rb><rp>(</rp><rt>ルビ</rt><rp>)</rp></ruby><span class="text">表現</span></p>
</div>
```

### 木構造化

前述のXHTML表現でも既に登場していましたが、テキストを処理しやすい木構造XMLにします。

Markdown:
```
テキストを完全な**木構造**化します。
```

XHTML:
```
<div>
<p class="description"><span class="text">テキストを完全な</span><strong>木構造</strong><span class="text">化します。</span></p>
</div>
```


[UTF-8]: https://tools.ietf.org/html/rfc3629 "RFC3629 - UTF-8, a transformation format of ISO 10646"
[Markdown]: http://daringfireball.net/projects/markdown/
