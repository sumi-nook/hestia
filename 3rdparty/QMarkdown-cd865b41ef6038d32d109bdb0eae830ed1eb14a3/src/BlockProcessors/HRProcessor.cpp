#include "BlockProcessors/HRProcessor.h"

#include "BlockParser.h"

namespace markdown
{

HRProcessor::HRProcessor(const std::weak_ptr<BlockParser> &parser) :
    BlockProcessor(parser),
    SEARCH_RE("^[ ]{0,3}((-+[ ]{0,2}){3,}|(_+[ ]{0,2}){3,}|(\\*+[ ]{0,2}){3,})[ ]*", QRegularExpression::MultilineOption),
    match()
{}

bool HRProcessor::test(const Element &, const QString &block)
{
    //! No atomic grouping in python so we simulate it here for performance.
    //! The regex only matches what would be in the atomic group - the HR.
    //! Then check if we are at end of block or if next char is a newline.
    QRegularExpressionMatch m = this->SEARCH_RE.match(block);
    if ( m.hasMatch()
         && ( m.capturedEnd() == block.size()
              || block.at(m.capturedStart()+m.capturedLength()) == '\n' ) ) {
        //! Save match object on class instance so we can use it later.
        this->match = m;
        return true;
    }
    return false;
}

bool HRProcessor::run(const Element &parent, QStringList &blocks)
{
    std::shared_ptr<BlockParser> parser = this->parser.lock();

    QString block = blocks.front();
    blocks.pop_front();
    //! Check for lines in block before hr.
    QString prelines = pypp::rstrip(block.left(this->match.capturedStart()), [](const QChar &ch) -> bool { return ch == '\n'; });
    if ( ! prelines.isEmpty() ) {
        //! Recursively parse lines before hr so they get parsed first.
        QStringList new_blocks = {prelines};
        parser->parseBlocks(parent, new_blocks);
    }
    //! create hr
    Element hr = createSubElement(parent, "hr");
    //! check for lines in block after hr.
    int begin = this->match.capturedStart()+this->match.capturedLength();
    QString postlines = pypp::lstrip(block.mid(begin), [](const QChar &ch) -> bool { return ch == '\n'; });
    if ( ! postlines.isEmpty() ) {
        //! Add lines after hr to master blocks for later parsing.
        blocks.push_front(postlines);
    }
    return true;
}

} // namespace markdown
