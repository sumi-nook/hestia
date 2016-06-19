#include "BlockProcessors/EmptyBlockProcessor.h"


namespace markdown
{

bool EmptyBlockProcessor::test(const Element &, const QString &block)
{
    return block.isEmpty() || block.startsWith('\n');
}

bool EmptyBlockProcessor::run(const Element &parent, QStringList &blocks)
{
    QString block = blocks.front();
    blocks.pop_front();
    QString filler = "\n\n";
    if ( ! block.isEmpty() ) {
        //! Starts with empty line
        //! Only replace a single line.
        filler = "\n";
        //! Save the rest for later.
        QString theRest = block.mid(1);
        if ( ! theRest.isEmpty() ) {
            //! Add remaining lines to master blocks for later.
            blocks.push_front(theRest);
        }
    }
    Element sibling = this->lastChild(parent);
    if ( sibling && sibling->tag == "pre" && sibling->size() > 0 && (*sibling)[0]->tag == "code" ) {
        //! Last block is a codeblock. Append to preserve whitespace.
        QString codeText = (*sibling)[0]->text;
        (*sibling)[0]->text = QString("%1%2").arg(codeText).arg(filler);
        (*sibling)[0]->atomic = true;
    }
    return true;
}

} // namespace markdown
