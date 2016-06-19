#ifndef BLOCKQUOTEPROCESSOR_H
#define BLOCKQUOTEPROCESSOR_H

#include "../BlockProcessors.h"

namespace markdown
{

class BlockQuoteProcessor : public BlockProcessor
{
public:
    BlockQuoteProcessor(const std::weak_ptr<BlockParser> &parser);

    bool test(const Element &, const QString &block);

    bool run(const Element &parent, QStringList &blocks);

    /*!
     * Remove ``>`` from beginning of a line.
     */
    QString clean(const QString &line);

private:
    const QRegularExpression RE;

};

} // namespace markdown

#endif // BLOCKQUOTEPROCESSOR_H
