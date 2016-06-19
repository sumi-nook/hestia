#include "BlockProcessors/ParagraphProcessor.h"

#include "BlockParser.h"

namespace markdown
{

bool ParagraphProcessor::test(const Element &, const QString &)
{
    return true;
}

bool ParagraphProcessor::run(const Element &parent, QStringList &blocks)
{
    std::shared_ptr<BlockParser> parser = this->parser.lock();

    QString block = blocks.front();
    blocks.pop_front();
    if ( ! block.trimmed().isEmpty() ) {
        //! Not a blank block. Add to parent, otherwise throw it away.
        if ( parser->state.isstate("list") ) {
            //! The parent is a tight-list.
            //!
            //! Check for any children. This will likely only happen in a
            //! tight-list when a header isn't followed by a blank line.
            //! For example:
            //!
            //!     * # Header
            //!     Line 2 of list item - not part of header.
            Element sibling = this->lastChild(parent);
            if ( sibling ) {
                //! Insetrt after sibling.
                if ( sibling->hasTail() ) {
                    QString tailText = sibling->tail;
                    sibling->tail = QString("%1\n%2").arg(tailText).arg(block);
                } else {
                    sibling->tail = QString("\n%1").arg(block);
                }
            } else {
                //! Append to parent.text
                if ( parent->hasText() ) {
                    QString parentText = parent->text;
                    parent->text = QString("%1\n%2").arg(parentText).arg(block);
                } else {
                    parent->text = pypp::lstrip(block);
                }
            }
        } else {
            //! Create a regular paragraph
            Element p = createSubElement(parent, "p");
            p->text = pypp::lstrip(block);
        }
    }
    return true;
}

} // namespace markdown
