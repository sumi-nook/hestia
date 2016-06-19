#include "BlockProcessors/SetextHeaderProcessor.h"

#include "BlockParser.h"

namespace markdown
{

SetextHeaderProcessor::SetextHeaderProcessor(const std::weak_ptr<BlockParser> &parser) :
    BlockProcessor(parser),
    RE("^.*?\\n[=-]+[ ]*(\\n|$)", QRegularExpression::MultilineOption)
{}

bool SetextHeaderProcessor::test(const Element &, const QString &block)
{
    return this->RE.match(block).hasMatch();
}

bool SetextHeaderProcessor::run(const Element &parent, QStringList &blocks)
{
    QString block = blocks.front();
    blocks.pop_front();
    QStringList lines = block.split("\n");
    //! Determine level. ``=`` is 1 and ``-`` is 2.
    int level = 0;
    if ( lines.at(1).startsWith("=") ) {
        level = 1;
    } else {
        level = 2;
    }
    Element h = createSubElement(parent, QString("h%1").arg(level));
    h->text = lines.at(0).trimmed();
    if ( lines.size() > 2 ) {
        //! Block contains additional lines. Add to  master blocks for later.
        QStringList buff;
        int counter = 0;
        for ( const QString &line : lines ) {
            if ( counter++ < 2 ) {
                continue;
            }
            buff.push_back(line);
        }
        blocks.push_front(buff.join("\n"));
    }
    return true;
}

} // namespace markdown
