#include "BlockProcessors/OListProcessor.h"

#include "BlockParser.h"
#include "Markdown.h"

namespace markdown
{

OListProcessor::OListProcessor(const std::weak_ptr<BlockParser> &parser) :
    BlockProcessor(parser),
    TAG("ol"),
    RE(QString("^[ ]{0,%1}\\d+\\.[ ]+(.*)").arg(this->tab_length-1)),
    CHILD_RE(QString("^[ ]{0,%1}((\\d+\\.)|[*+-])[ ]+(.*)").arg(this->tab_length-1)),
    INDENT_RE(QString("^[ ]{%1,%2}((\\d+\\.)|[*+-])[ ]+.*").arg(this->tab_length).arg(this->tab_length*2-1)),
    STARTSWITH("1"),
    SIBLING_TAGS({"ol", "ul"})
{}
OListProcessor::~OListProcessor()
{}

bool OListProcessor::test(const Element &, const QString &block)
{
    return this->RE.match(block).hasMatch();
}

bool OListProcessor::run(const Element &parent, QStringList &blocks)
{
    std::shared_ptr<BlockParser> parser = this->parser.lock();

    //! Check fr multiple items in one block.
    QString block = blocks.front();
    blocks.pop_front();
    QStringList items = this->get_items(block);
    Element sibling = this->lastChild(parent);
    Element lst;

    if ( sibling && this->SIBLING_TAGS.contains(sibling->tag) ) {
        //! Previous block was a list item, so set that as parent
        lst = sibling;
        //! make sure previous item is in a p- if the item has text, then it
        //! it isn't in a p
        if ( lst->size() > 0 && (*lst)[-1]->hasText() ) {
            //! since it's possible there are other children for this sibling,
            //! we can't just SubElement the p, we need to insert it as the
            //! first item
            Element elem = (*lst)[-1];
            Element p = createElement("p");
            p->text = elem->text;
            elem->text.clear();
            if ( elem->size() > 0 ) {
                elem->insert(0, p);
            } else {
                elem->append(p);
            }
        }
        //! if the last item has a tail, then the tail needs to be put in a p
        //! likely only when a header is not followed by a blank line
        Element lch = this->lastChild((*lst)[-1]);
        if ( lch && lch->hasTail() ) {
            Element p = createSubElement((*lst)[-1], "p");
            p->text = pypp::lstrip(lch->tail);
            lch->tail.clear();
        }

        //! parse first block differently as it gets wrapped in a p.
        Element li = createSubElement(lst, "li");
        parser->state.set("looselist");
        QString firstitem = items.front();
        items.pop_front();
        QStringList new_blocks = {firstitem};
        parser->parseBlocks(li, new_blocks);
        parser->state.reset();
    } else if ( parent->tag == "ol" || parent->tag == "ul" ) {
        //! this catches the edge case of a multi-item indented list whose
        //! first item is in a blank parent-list item:
        //! * * subitem1
        //!     * subitem2
        //! see also ListIndentProcessor
        lst = parent;
    } else {
        //! This is a new list so create parent with appropriate tag.
        lst = createSubElement(parent, this->TAG);
        //! Check if a custom start integer is set
        if ( ! parser->markdown.lock()->lazy_ol() && this->STARTSWITH != "1" ) {
            lst->set("start", this->STARTSWITH);
        }
    }

    parser->state.set("list");
    //! Loop through items in block, recursively parsing each with the
    //! appropriate parent.
    for ( const QString &item : items ) {
        QStringList new_blocks = {item};
        if ( item.startsWith(QString(this->tab_length, ' ')) ) {
            Element new_parent = (*lst)[-1];
            //! Item is indented. Parse with last item as parent
            parser->parseBlocks(new_parent, new_blocks);
        } else {
            //! New item. Create li and parse with it as parent
            Element li = createSubElement(lst, "li");
            parser->parseBlocks(li, new_blocks);
        }
    }
    parser->state.reset();
    return true;
}

QStringList OListProcessor::get_items(const QString &block)
{
    QStringList items;
    QStringList lines = block.split("\n");
    for ( const QString &line : lines ) {
        QRegularExpressionMatch m = this->CHILD_RE.match(line);
        if ( m.hasMatch() ) {
            //! This is a new list item
            //! Check first item for the start index
            if ( items.empty() && this->TAG == "ol" ) {
                //! Detect the integer value of first list item
                QRegularExpression INTEGER_RE("(\\d+)");
                QRegularExpressionMatch im = INTEGER_RE.match(m.captured(1));
                this->STARTSWITH = im.captured();
            }
            //! Append to the list
            items.push_back(m.captured(3));
        } else if ( this->INDENT_RE.match(line).hasMatch() ) {
            //! This is an indented (possibly nested) item.
            if ( ! items.empty() && items.back().startsWith(QString(this->tab_length, ' ')) ) {
                //! Previous item was indented. Append to that item.
                items.back() = QString("%1\n%2").arg(items.back()).arg(line);
            } else {
                items.push_back(line);
            }
        } else {
            //! This is another line of previous item. Append to that item.
            items.back() = QString("%1\n%2").arg(items.back()).arg(line);
        }
    }
    return items;
}


UListProcessor::UListProcessor(const std::weak_ptr<BlockParser> &parser) :
    OListProcessor(parser)
{
    OListProcessor::TAG = "ul";
    OListProcessor::RE = QRegularExpression(QString("^[ ]{0,%1}[*+-][ ]+(.*)").arg(this->tab_length-1));
}

} // namespace markdown
