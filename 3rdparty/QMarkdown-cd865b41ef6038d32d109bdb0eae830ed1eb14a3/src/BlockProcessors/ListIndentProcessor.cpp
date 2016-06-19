#include "BlockProcessors/ListIndentProcessor.h"

#include "BlockParser.h"

namespace markdown
{

ListIndentProcessor::ListIndentProcessor(const std::weak_ptr<BlockParser> &parser) :
    BlockProcessor(parser),
    ITEM_TYPES({"li"}),
    LIST_TYPES({"ul", "ol"}),
    INDENT_RE(QString("^(([ ]{%1})+)").arg(this->tab_length))
{}
ListIndentProcessor::~ListIndentProcessor(void)
{}

bool ListIndentProcessor::test(const Element &parent, const QString &block)
{
    std::shared_ptr<BlockParser> parser = this->parser.lock();

    return block.startsWith(QString(this->tab_length, ' '))
            && ! parser->state.isstate("detabbed")
            && ( this->ITEM_TYPES.contains(parent->tag)
                 || ( parent->size() > 0
                      && this->LIST_TYPES.contains((*parent)[-1]->tag) )
            );
}

bool ListIndentProcessor::run(const Element &parent, QStringList &blocks)
{
    std::shared_ptr<BlockParser> parser = this->parser.lock();

    QString block = blocks.front();
    blocks.pop_front();
    int level;
    Element sibling;
    std::tie(level, sibling) = this->get_level(parent, block);
    block = this->looseDetab(block, level);

    parser->state.set("detabbed");
    if ( this->ITEM_TYPES.contains(parent->tag) ) {
        //! It's possible that this parent has a 'ul' or 'ol' child list
        //! with a member.  If that is the case, then that should be the
        //! parent.  This is intended to catch the edge case of an indented
        //! list whose first member was parsed previous to this point
        //! see OListProcessor
        if ( parent->size() > 0 && this->LIST_TYPES.contains((*parent)[-1]->tag) ) {
            QStringList new_blocks = {block};
            Element new_parent = (*parent)[-1];
            parser->parseBlocks(new_parent, new_blocks);
        } else {
            QStringList new_blocks = {block};
            //! The parent is already a li. Just parse the child block.
            parser->parseBlocks(parent, new_blocks);
        }
    } else if ( this->ITEM_TYPES.contains(sibling->tag) ) {
        //! The sibling is a li. Use it as parent.
        QStringList new_blocks = {block};
        parser->parseBlocks(sibling, new_blocks);
    } else if ( sibling->size() > 0 && this->ITEM_TYPES.contains((*sibling)[-1]->tag) ) {
        //! The parent is a list (``ol`` or ``ul``) which has children.
        //! Assume the last child li is the parent of this block.
        if ( (*sibling)[-1]->hasText() ) {
            //! If the parent li has text, that text needs to be moved to a p
            //! The p must be 'inserted' at beginning of list in the event
            //! that other children already exist i.e.; a nested sublist.
            Element elem = (*sibling)[-1];
            QString text = elem->text;
            elem->text.clear();
            Element p = createElement("p");
            p->text = text;
            if ( elem->size() > 0 ) {
                elem->insert(0, p);
            } else {
                elem->append(p);
            }
        }
        Element new_parent = (*sibling)[-1];
        parser->parseChunk(new_parent, block);
    } else {
        this->create_item(sibling, block);
    }
    parser->state.reset();
    return true;
}

/*!
     * Create a new li and parse the block with it as the parent.
     */
void ListIndentProcessor::create_item(const Element &parent, const QString &block)
{
    std::shared_ptr<BlockParser> parser = this->parser.lock();

    Element li = createSubElement(parent, "li");
    QStringList new_blocks = {block};
    parser->parseBlocks(li, new_blocks);
}

/*!
     * Get level of indent based on list level.
     */
std::tuple<int, Element> ListIndentProcessor::get_level(const Element &parent, const QString &block)
{
    std::shared_ptr<BlockParser> parser = this->parser.lock();

    //! Get indent level
    int indent_level = 0;
    int level = 0;
    QRegularExpressionMatch m = this->INDENT_RE.match(block);
    if ( m.hasMatch() ) {
        indent_level = m.captured(1).size()/this->tab_length;
    }
    if ( parser->state.isstate("list") ) {
        //! We're in a tightlist - so we already are at correct parent.
        level = 1;
    } else {
        //! We're in a looselist - so we need to find parent.
        level = 0;
    }
    //! Step through children of tree to find matching indent level.
    Element parent_ = parent;
    while ( indent_level > level ) {
        Element child = this->lastChild(parent_);
        if ( child && ( this->LIST_TYPES.contains(child->tag) || this->ITEM_TYPES.contains(child->tag) ) ) {
            if ( this->LIST_TYPES.contains(child->tag) ) {
                level += 1;
            }
            parent_ = child;
        } else {
            //! No more child levels. If we're short of indent_level,
            //! we have a code block. So we stop here.
            break;
        }
    }
    return std::make_tuple(level, parent_);
}

} // namespace markdown
