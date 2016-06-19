/*
 * MarkdownCpp.cpp
 *
 *  Created on: 2013/10/25
 *      Author: mugwort_rc
 */

#include "Markdown.h"

#include <QDebug>

#include "PreProcessors.h"
#include "BlockParser.h"
#include "BlockProcessors.h"
#include "Serializers.h"

namespace markdown{

Markdown::Markdown(const safe_mode_type &safe_mode) :
    _doc_tag("div"),
    _html_replacement_text("[HTML_REMOVED]"), _tab_length(4), _enable_attributes(true), _smart_emphasis(true), _lazy_ol(true),
    _safeMode(safe_mode),
    //todo
    stripTopLevelTags(true),

    initialized(false),

    ESCAPED_CHARS({'\\', '`', '*', '_', '{', '}', '[', ']',
                   '(', ')', '>', '#', '+', '-', '.', '!'}),

    //! Initalize in build_parser()
    preprocessors(),
    parser(),
    inlinePatterns(),
    treeprocessors(),
    postprocessors(),

    references(),
    htmlStash(),

    serializer()
{}

void Markdown::initialize()
{
    this->build_parser();
    this->set_output_format();
    this->reset();
    this->initialized = true;
}

void Markdown::initialize(const Extensions &extensions)
{
    this->build_parser();
    this->set_output_format();
    this->registerExtensions(extensions);
    this->reset();
    this->initialized = true;
}

std::shared_ptr<Markdown> Markdown::build_parser(void)
{
    this->preprocessors = build_preprocessors(this->shared_from_this());
    this->parser = build_block_parser(this->shared_from_this());
    this->inlinePatterns = build_inlinepatterns(this->shared_from_this());
    this->treeprocessors = build_treeprocessors(this->shared_from_this());
    this->postprocessors = build_postprocessors(this->shared_from_this());
    return this->shared_from_this();
}

std::shared_ptr<Markdown> Markdown::registerExtensions(const Extensions &extensions/*, configs*/)
{
    for ( const Extension::Ptr &ext : extensions ) {
        ext->extendMarkdown(this->shared_from_this());
    }
    return this->shared_from_this();
}

std::shared_ptr<Markdown> Markdown::registerExtension(const Extension::Ptr &extension)
{
    this->registeredExtensions.append(extension);
    return this->shared_from_this();
}

std::shared_ptr<Markdown> Markdown::reset(void)
{
    this->htmlStash.reset();
    this->references.clear();
    //! TODO: extension
    return this->shared_from_this();
}

std::shared_ptr<Markdown> Markdown::set_output_format(const output_formats format)
{
    if ( format == html || format == html4 || format == html5 ) {
        this->serializer = to_html_string;
    } else if ( format == xhtml || format == xhtml1 || format == xhtml5 ) {
        this->serializer = to_xhtml_string;
    }
    return this->shared_from_this();
}

QString Markdown::convert(const QString &source)
{
    if ( ! this->initialized ) {
        this->initialize();
    }

    //! Fixup the source text
    if ( source.trimmed().isEmpty() ) {
        return QString();  //!< a blank unicode string
	}

    QString source_ = source;

    //! Split into lines and run the line preprocessors.
    QStringList lines = source_.split("\n");
    for ( OrderedDictProcessors::ValueType pre : this->preprocessors.toList() ) {
        lines = pre->run(lines);
    }

    //! Parse the high-level elements.
    ElementTree doc = this->parser->parseDocument(lines);
    Element root = doc.getroot();

    //! Run the tree-processors
    for ( OrderedDictTreeProcessors::ValueType tree : this->treeprocessors.toList() ) {
        Element newRoot = tree->run(root);
        if ( newRoot ) {
            root = newRoot;
        }
    }

    //! Serialize _properly_.  Strip top-level tags.
    QString output;
    output = this->serializer(root);
    if ( this->stripTopLevelTags ) {
        int begin = output.indexOf(QString("<%1>").arg(this->doc_tag()));
        int end   = output.lastIndexOf(QString("</%1>").arg(this->doc_tag()));
        if ( begin != -1 && end != -1 ) {
            output = output.mid(begin+this->doc_tag().size()+2, end-this->doc_tag().size()-2);
        } else {
            return QString();
        }
    }

    //! Run the text post-processors
    for ( OrderedDictPostProcessors::ValueType post : this->postprocessors.toList() ) {
        output = post->run(output);
    }

    return output.trimmed();
}

std::shared_ptr<Markdown> Markdown::convertFile(/*input, output, encoding=L"utf-8"*/)
{
    return this->shared_from_this();
}

std::shared_ptr<Markdown> create_Markdown(const Markdown::safe_mode_type &safe_mode)
{
    std::shared_ptr<Markdown> result(new Markdown(safe_mode));
    result->initialize();
    return result;
}

std::shared_ptr<Markdown> create_Markdown(const Markdown::Extensions &extensions)
{
    std::shared_ptr<Markdown> result(new Markdown());
    result->initialize(extensions);
    return result;
}

} // end of namespace markdown
