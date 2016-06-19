#include "BlockProcessors/CodeBlockProcessor.h"

namespace markdown
{

bool CodeBlockProcessor::test(const Element &, const QString &block)
{
    return block.startsWith(QString(this->tab_length, ' '));
}

bool CodeBlockProcessor::run(const Element &parent, QStringList &blocks)
{
    Element sibling = this->lastChild(parent);
    QString block = blocks.front();
    blocks.pop_front();
    QString theRest;
    if ( sibling && sibling->tag == "pre" && sibling->size() > 0 && (*sibling)[0]->tag == "code" ) {
        //! The previous block was a code block. As blank lines do not start
        //! new code blocks, append this block to the previous, adding back
        //! linebreaks removed from the split into a list.
        Element code = (*sibling)[0];
        std::tie(block, theRest) = this->detab(block);
        code->text = QString("%1\n%2\n").arg(code->text).arg(pypp::rstrip(block));
        code->atomic = true;
    } else {
        //! This is a new codeblock. Create the elements and insert text.
        Element pre = createSubElement(parent, "pre");
        Element code = createSubElement(pre, "code");
        std::tie(block, theRest) = this->detab(block);
        code->text = QString("%1\n").arg(pypp::rstrip(block));
        code->atomic = true;
    }
    if ( ! theRest.isEmpty() ) {
        //! This block contained unindented line(s) after the first indented
        //! line. Insert these lines as the first block of the master blocks
        //! list for future processing.
        blocks.push_front(theRest);
    }
    return true;
}

} // namespace markdown
