#include "extensions/admonition.h"

#include "Markdown.h"
#include "BlockParser.h"
#include "BlockProcessors.h"

namespace markdown
{

class AdmonitionProcessor : public BlockProcessor
{
public:
    AdmonitionProcessor(const std::weak_ptr<BlockParser> &parser) :
        BlockProcessor(parser),
        RE("(?:^|\\n)!!!\\ ?([\\w\\-]+)(?:\\ \"(.*?)\")?")
    {}

    bool test(const Element &parent, const QString &block)
    {
        Element sibling = this->lastChild(parent);
        return this->RE.match(block).hasMatch() ||
                (block.startsWith(QString(this->tab_length, ' ')) && sibling && sibling->get("class").indexOf(this->classname()) != -1);
    }

    bool run(const Element &parent, QStringList &blocks)
    {
        Element sibling = this->lastChild(parent);
        QString block = blocks.front();
        blocks.pop_front();
        QRegularExpressionMatch m = this->RE.match(block);

        if ( m.hasMatch() ) {
            block = block.mid(m.capturedEnd()+1);  //! removes the first line
        }

        QString theRest;
        std::tie(block, theRest) = this->detab(block);

        Element div;
        if ( m.hasMatch() ) {
            QString klass, title;
            std::tie(klass, title) = this->get_class_and_title(m);
            div = createSubElement(parent, "div");
            div->set("class", QString("%1 %2").arg(this->classname()).arg(klass));
            if ( ! title.isEmpty() ) {
                Element p = createSubElement(div, "p");
                p->text = title;
                p->set("class", this->classname_title());
            }
        } else {
            div = sibling;
        }

        std::shared_ptr<BlockParser> parser = this->parser.lock();
        parser->parseChunk(div, block);

        if ( ! theRest.isEmpty() ) {
            //! This block contained unindented line(s) after the first indented
            //! line. Insert these lines as the first block of the master blocks
            //! list for future processing.
            blocks.insert(0, theRest);
        }
        return true;
    }

    std::tuple<QString, QString> get_class_and_title(const QRegularExpressionMatch &match)
    {
        QString klass = match.captured(1).toLower();
        QString title = match.captured(2);
        if ( match.capturedEnd(2) == -1 ) {
            //! no title was provided, use the capitalized classname as title
            //! e.g.: `!!! note` will render
            //! `<p class="admonition-title">Note</p>`
            title = pypp::capitalize(klass);
        } else if ( title.isEmpty() ) {
            //! an explicit blank title should not be rendered
            //! e.g.: `!!! warning ""` will *not* render `p` with a title
            //title = QString();
        }
        return std::make_tuple(klass, title);
    }

    virtual QString classname() const
    { return "admonition"; }

    virtual QString classname_title() const
    { return "admonition-title"; }

    QRegularExpression RE;

};

/*!
 * Admonition extension for Python-Markdown.
 */
AdmonitionExtension::AdmonitionExtension()
{

}

/*!
 * Add Admonition to Markdown instance.
 */
void AdmonitionExtension::extendMarkdown(const std::shared_ptr<Markdown> &md)
{
    md->registerExtension(this->shared_from_this());
    md->parser->blockprocessors.add("admonition", std::make_shared<AdmonitionProcessor>(md->parser), "_begin");
}

Extension::Ptr AdmonitionExtension::generate()
{
    return std::shared_ptr<Extension>(new AdmonitionExtension);
}



} // namespace markdown
