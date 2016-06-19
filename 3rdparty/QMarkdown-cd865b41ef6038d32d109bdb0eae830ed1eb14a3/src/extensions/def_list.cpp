#include "extensions/def_list.h"

#include "Markdown.h"
#include "BlockParser.h"
#include "BlockProcessors.h"

#include "BlockProcessors/ListIndentProcessor.h"

namespace markdown
{

/*!
 * Process Definition Lists.
 */
class DefListProcessor : public BlockProcessor
{
public:
    DefListProcessor(const std::weak_ptr<BlockParser> &parser) :
        BlockProcessor(parser),
        RE("(^|\\n)[ ]{0,3}:[ ]{1,3}(.*?)(\\n|$)"),
        NO_INDENT_RE("^[ ]{0,3}[^ :]")
    {}

    bool test(const Element &, const QString &block)
    {
        return this->RE.match(block).hasMatch();
    }

    bool run(const Element &parent, QStringList &blocks)
    {
        QString raw_block = blocks.front();
        blocks.pop_front();
        QRegularExpressionMatch m = this->RE.match(raw_block);
        QStringList temp = raw_block.left(m.capturedStart()).split("\n");
        QStringList terms;
        for ( QString l : temp ) {
            if ( ! l.trimmed().isEmpty() ) {
                terms.append(l.trimmed());
            }
        }
        QString block = raw_block.mid(m.capturedEnd());
        QRegularExpressionMatch no_indent = this->NO_INDENT_RE.match(block);
        QString d;
        QString theRest;
        if ( no_indent.hasMatch() ) {
            d = block;
        } else {
            std::tie(d, theRest) = this->detab(block);
        }
        if ( ! d.isEmpty() ) {
            d = QString("%1\n%2").arg(m.captured(2)).arg(d);
        } else {
            d = m.captured(2);
        }
        Element sibling = this->lastChild(parent);
        if ( terms.isEmpty() && ! sibling ) {
            //! This is not a definition item. Most likely a paragraph that
            //! starts with a colon at the begining of a document or list.
            blocks.insert(0, raw_block);
            return false;
        }
        QString state;
        if ( terms.isEmpty() && sibling->tag == "p" ) {
            //! The previous paragraph contains the terms
            state = "looselist";
            terms = sibling->text.split("\n");
            parent->remove(sibling);
            //! Aquire new sibling
            sibling = this->lastChild(parent);
        } else {
            state = "list";
        }

        Element dl;
        if ( sibling && sibling->tag == "dl" ) {
            //! This is another item on an existing list
            dl = sibling;
            if ( terms.isEmpty() && dl->size() > 0 && (*dl)[-1]->tag == "dd" && (*dl)[-1]->size() > 0 ) {
                state = "looselist";
            }
        } else {
            //! This is a new list
            dl = createSubElement(parent, "dl");
        }
        //! Add terms
        for ( const QString &term : terms ) {
            Element dt = createSubElement(dl, "dt");
            dt->text = term;
        }
        //! Add definition
        std::shared_ptr<BlockParser> parser = this->parser.lock();
        parser->state.set(state);;
        Element dd = createSubElement(dl, "dd");
        QStringList new_block = {d};
        parser->parseBlocks(dd, new_block);
        parser->state.reset();

        if ( ! theRest.isEmpty() ) {
            blocks.insert(0, theRest);
        }

        return true;
    }

    QRegularExpression RE;
    QRegularExpression NO_INDENT_RE;
};


/*!
 * Process indented children of definition list items.
 */
class DefListIndentProcessor : public ListIndentProcessor
{
public:
    DefListIndentProcessor(const std::weak_ptr<BlockParser> &parser) :
        ListIndentProcessor(parser)
    {
        this->ITEM_TYPES = {"dd"};
        this->LIST_TYPES = {"dl"};
    }

    /*!
     * Create a new dd and parse the block with it as the parent.
     */
    void create_item(const Element &parent, const QString &block)
    {
        Element dd = createSubElement(parent, "dd");
        std::shared_ptr<BlockParser> parser = this->parser.lock();
        QStringList new_block = {block};
        parser->parseBlocks(dd, new_block);
    }

};

/*!
 * Add an instance of DefListProcessor to BlockParser.
 */
void DefListExtension::extendMarkdown(const std::shared_ptr<Markdown> &md)
{
    md->parser->blockprocessors.add("defindent", std::shared_ptr<BlockProcessor>(new DefListIndentProcessor(md->parser)), ">indent");
    md->parser->blockprocessors.add("deflist", std::shared_ptr<BlockProcessor>(new DefListProcessor(md->parser)), ">ulist");
}

Extension::Ptr DefListExtension::generate()
{
    return std::shared_ptr<Extension>(new DefListExtension);
}

} // namespace markdown
