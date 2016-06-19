#include "BlockProcessors/BlockQuoteProcessor.h"

#include "BlockParser.h"

namespace markdown
{

BlockQuoteProcessor::BlockQuoteProcessor(const std::weak_ptr<BlockParser> &parser) :
        BlockProcessor(parser),
        RE("(^|\\n)[ ]{0,3}>[ ]?(.*)")
    {}

bool BlockQuoteProcessor::test(const Element &, const QString &block)
{
    return this->RE.match(block).hasMatch();
}

bool BlockQuoteProcessor::run(const Element &parent, QStringList &blocks)
{
    std::shared_ptr<BlockParser> parser = this->parser.lock();

    QString block = blocks.front();
    blocks.pop_front();
    QRegularExpressionMatch m = this->RE.match(block);
    if ( m.hasMatch() ) {
        QString before = block.left(m.capturedStart());  //!< Lines before blockquote
        //! Pass lines before blockquote in recursively for parsing forst.
        QStringList new_blocks = {before};
        parser->parseBlocks(parent, new_blocks);
        //! Remove ``> `` from begining of each line.
        QString after = block.mid(m.capturedStart());
        QStringList lines = after.split("\n");
        QStringList new_lines;
        for ( const QString &line : lines ) {
            new_lines.push_back(this->clean(line));
        }
        block = new_lines.join("\n");
    }
    Element sibling = this->lastChild(parent);
    Element quote = Element();
    if ( sibling && sibling->tag == "blockquote" ) {
        //! Previous block was a blockquote so set that as this blocks parent
        quote = sibling;
    } else {
        //! This is a new blockquote. Create a new parent element.
        quote = createSubElement(parent, "blockquote");
    }
    //! Recursively parse block with blockquote as parent.
    //! change parser state so blockquotes embedded in lists use p tags
    parser->state.set("blockquote");
    parser->parseChunk(quote, block);
    parser->state.reset();
    return true;
}

QString BlockQuoteProcessor::clean(const QString &line)
{
    QRegularExpressionMatch m = this->RE.match(line);
    if ( line.trimmed() == ">" ) {
        return QString();
    } else if ( m.hasMatch() ) {
        return m.captured(2);
    } else {
        return line;
    }
}

} // namespace markdown
