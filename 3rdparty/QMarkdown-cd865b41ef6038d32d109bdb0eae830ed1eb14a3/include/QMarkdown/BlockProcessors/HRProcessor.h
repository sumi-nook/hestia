#ifndef HRPROCESSOR_H
#define HRPROCESSOR_H

#include "../BlockProcessors.h"

namespace markdown
{

/*!
 * Process Horizontal Rules.
 */
class HRProcessor : public BlockProcessor
{
public:
    HRProcessor(const std::weak_ptr<BlockParser> &parser);

    bool test(const Element &, const QString &block);

    bool run(const Element &parent, QStringList &blocks);

private:
    //! Detect hr on any line of a block.
    QRegularExpression SEARCH_RE;
    QRegularExpressionMatch match;

};

} // namespace markdown

#endif // HRPROCESSOR_H
