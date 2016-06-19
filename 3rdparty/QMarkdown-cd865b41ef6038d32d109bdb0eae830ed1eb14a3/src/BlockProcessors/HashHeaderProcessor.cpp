#include "BlockProcessors/HashHeaderProcessor.h"

#include <QDebug>

#include "BlockParser.h"

namespace markdown
{

HashHeaderProcessor::HashHeaderProcessor(const std::weak_ptr<BlockParser> &parser) :
    BlockProcessor(parser),
    RE("(^|\\n)(?<level>#{1,6})(?<header>.*?)#*(\\n|$)")
{}

bool HashHeaderProcessor::test(const Element &, const QString &block)
{
    return this->RE.match(block).hasMatch();
}

bool HashHeaderProcessor::run(const Element &parent, QStringList &blocks)
{
    std::shared_ptr<BlockParser> parser = this->parser.lock();

    QString block = blocks.front();
    blocks.pop_front();
    QRegularExpressionMatch m = this->RE.match(block);
    if ( m.hasMatch() ) {
        QString before = block.left(m.capturedStart());  //!< All lines before header
        QString after  = block.mid(m.capturedEnd()); //!< All lines after header
        if ( ! before.isEmpty() ) {
            //! As the header was not the first line of the block and the
            //! lines before the header must be parsed first,
            //! recursively parse this lines as a block.
            QStringList new_blocks = {before};
            parser->parseBlocks(parent, new_blocks);
        }
        //! Create header using named groups from RE
        Element h = createSubElement(parent, QString("h%1").arg(m.captured("level").size()));
        h->text = m.captured("header").trimmed();
        if ( ! after.isEmpty() ) {
            //! Insert remaining lines as first block for future parsing.
            blocks.push_front(after);
        }
    } else {
        //! This should never happen, but just in case...
        qWarning() << "We've got a problem header: " << block;
    }
    return true;
}

} // namespace markdown
