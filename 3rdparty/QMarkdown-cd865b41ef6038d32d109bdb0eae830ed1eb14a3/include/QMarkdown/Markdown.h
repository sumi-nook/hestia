/*
 * MarkdownCpp.h
 *
 *  Created on: 2013/10/25
 *      Author: mugwort_rc
 */

#ifndef MARKDOWN_H_
#define MARKDOWN_H_

/*!
 * Python Markdown
 * ===============
 *
 * Python Markdown converts Markdown to HTML and can be used as a library or
 * called from the command line.
 *
 * ## Basic usage as a module:
 *
 *  import markdown
 *  html = markdown.markdown(your_text_string)
 *
 * See <http://packages.python.org/Markdown/> for more
 * information and instructions on how to extend the functionality of
 * Python Markdown.  Read that before you try modifying this file.
 *
 * ## Authors and License
 *
 * Started by [Manfred Stienstra](http://www.dwerg.net/).  Continued and
 * maintained  by [Yuri Takhteyev](http://www.freewisdom.org), [Waylan
 * Limberg](http://achinghead.com/) and [Artem Yunusov](http://blog.splyer.com).
 *
 * Contact: markdown@freewisdom.org
 *
 * Copyright 2007-2013 The Python Markdown Project (v. 1.7 and later)
 * Copyright 200? Django Software Foundation (OrderedDict implementation)
 * Copyright 2004, 2005, 2006 Yuri Takhteyev (v. 0.2-1.6b)
 * Copyright 2004 Manfred Stienstra (the original version)
 *
 * License: BSD (see LICENSE for details).
 */

#include <functional>

#include <QPair>
#include <QSet>

#include "Processor.hpp"
#include "InlinePatterns.h"
#include "TreeProcessors.h"
#include "PostProcessors.h"
#include "util.h"
#include "extensions/Extension.h"

namespace markdown{

class BlockParser;  //!< forward declaration

/*!
 * Convert Markdown to HTML.
 */
class Markdown : public std::enable_shared_from_this<Markdown>
{
public:
    typedef QPair<QString, QString> ReferenceItem;
    typedef QMap<QString, ReferenceItem>  Reference;

    typedef QList<Extension::Ptr> Extensions;

public:
    typedef enum{
        default_mode,
        replace_mode,
        remove_mode,
        escape_mode,
    } safe_mode_type;

    typedef enum{
        html,
        html4,
        html5,
        xhtml,
        xhtml1,
        xhtml5
    } output_formats;

    friend std::shared_ptr<Markdown> create_Markdown(const safe_mode_type &);
    friend std::shared_ptr<Markdown> create_Markdown(const Extensions &);

protected:
    /*!
     * Creates a new Markdown instance.
     *
     * Keyword arguments:
     *
     * * extensions: A list of extensions.
     *    If they are of type string, the module mdx_name.py will be loaded.
     *    If they are a subclass of markdown.Extension, they will be used
     *    as-is.
     * * extension_configs: Configuration settingis for extensions.
     * * output_format: Format of output. Supported formats are:
     *     * "xhtml1": Outputs XHTML 1.x. Default.
     *     * "xhtml5": Outputs XHTML style tags of HTML 5
     *     * "xhtml": Outputs latest supported version of XHTML (currently XHTML 1.1).
     *     * "html4": Outputs HTML 4
     *     * "html5": Outputs HTML style tags of HTML 5
     *     * "html": Outputs latest supported version of HTML (currently HTML 4).
     *     Note that it is suggested that the more specific formats ("xhtml1"
     *     and "html4") be used as "xhtml" or "html" may change in the future
     *     if it makes sense at that time.
     * * safe_mode: Disallow raw html. One of "remove", "replace" or "escape".
     * * html_replacement_text: Text used when safe_mode is set to "replace".
     * * tab_length: Length of tabs in the source. Default: 4
     * * enable_attributes: Enable the conversion of attributes. Default: True
     * * smart_emphasis: Treat `_connected_words_` intelegently Default: True
     * * lazy_ol: Ignore number of first item of ordered lists. Default: True
     *
     */
    Markdown(const safe_mode_type &safe_mode=default_mode);

public:
    void initialize();
    void initialize(const Extensions &extensions);

    /*!
     * Build the parser from the various parts.
     */
    std::shared_ptr<Markdown> build_parser(void);
    /*!
     * Register extensions with this instance of Markdown.
     *
     * Keyword arguments:
     *
     * * extensions: A list of extensions, which can either
     *    be strings or objects.  See the docstring on Markdown.
     * * configs: A dictionary mapping module names to config options.
     *
     */
    std::shared_ptr<Markdown> registerExtensions(const Extensions &extensions/*, configs*/);
    /*!
     * This gets called by the extension
     */
    std::shared_ptr<Markdown> registerExtension(const Extension::Ptr &extension);
    /*!
     * Resets all state variables so that we can start with a new text.
     */
    std::shared_ptr<Markdown> reset(void);
    /*!
     * Set the output format for the class instance.
     */
    std::shared_ptr<Markdown> set_output_format(const output_formats format=xhtml1);
    /*!
     * Convert markdown to serialized XHTML or HTML.
     *
     * Keyword arguments:
     *
     * * source: Source text as a Unicode string.
     *
     * Markdown processing takes place in five steps:
     *
     * 1. A bunch of "preprocessors" munge the input text.
     * 2. BlockParser() parses the high-level structural elements of the
     *    pre-processed text into an ElementTree.
     * 3. A bunch of "treeprocessors" are run against the ElementTree. One
     *    such treeprocessor runs InlinePatterns against the ElementTree,
     *    detecting inline markup.
     * 4. Some post-processors are run against the text after the ElementTree
     *    has been serialized into text.
     * 5. The output is written to a string.
     *
     */
    QString convert(const QString &source);
    /*!
     * Converts a markdown file and returns the HTML as a unicode string.
     *
     * Decodes the file using the provided encoding (defaults to utf-8),
     * passes the file content to markdown, and outputs the html to either
     * the provided stream or the file with provided name, using the same
     * encoding as the source file. The 'xmlcharrefreplace' error handler is
     * used when encoding the output.
     *
     * **Note:** This is the only place that decoding and encoding of unicode
     * takes place in Python-Markdown.  (All other code is unicode-in /
     * unicode-out.)
     *
     * Keyword arguments:
     *
     * * input: File object or path. Reads from stdin if `None`.
     * * output: File object or path. Writes to stdout if `None`.
     * * encoding: Encoding of input and output files. Defaults to utf-8.
     *
     */
    std::shared_ptr<Markdown> convertFile(/*input, output, encoding="utf-8"*/);

public:
    QString doc_tag(void) const
	{ return this->_doc_tag; }
    void set_doc_tag(const QString &doc_tag)
	{ this->_doc_tag = doc_tag; }

    QString html_replacement_text(void) const
	{ return this->_html_replacement_text; }
    void set_html_replacement_text(const QString &html_replacement_text)
	{ this->_html_replacement_text = html_replacement_text; }

	int tab_length(void) const
	{ return this->_tab_length; }
	void set_tab_length(int tab_length)
	{ this->_tab_length = tab_length; }

	bool enable_attributes(void) const
	{ return this->_enable_attributes; }
	void set_enable_attributes(bool enable_attributes)
	{ this->_enable_attributes = enable_attributes; }

	bool smart_emphasis(void) const
	{ return this->_smart_emphasis; }
	void set_smart_emphasis(bool smart_emphasis)
    { this->_smart_emphasis = smart_emphasis; this->initialize(); }

	bool lazy_ol(void) const
	{ return this->_lazy_ol; }
	void set_lazy_ol(bool lazy_ol)
	{ this->_lazy_ol = lazy_ol; }

	safe_mode_type safeMode(void) const
	{ return this->_safeMode; }
	void setSafeMode(safe_mode_type mode)
	{ this->_safeMode = mode; }

private:
    QString _doc_tag;  //!< Element used to wrap document -later removed

    QString _html_replacement_text;
	int           _tab_length;
	bool          _enable_attributes;
	bool          _smart_emphasis;
	bool          _lazy_ol;

    //output_formats

	safe_mode_type _safeMode;

	//registeredExtensions
	//docType
	bool stripTopLevelTags;

    bool initialized;

public:
    QSet<QChar> ESCAPED_CHARS;

    OrderedDictProcessors preprocessors;
    std::shared_ptr<BlockParser> parser;
    OrderedDictPatterns inlinePatterns;
    OrderedDictTreeProcessors treeprocessors;
    OrderedDictPostProcessors postprocessors;

    QList<Extension::Ptr> registeredExtensions;
    Reference references;
	HtmlStash htmlStash;

    std::function<QString(Element &)> serializer;

};

std::shared_ptr<Markdown> create_Markdown(const Markdown::safe_mode_type &safe_mode=Markdown::default_mode);
std::shared_ptr<Markdown> create_Markdown(const Markdown::Extensions &extensions);

} // end of namespace markdown

#endif /* MARKDOWN_H_ */
