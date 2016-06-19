#ifndef EMPTYBLOCKPROCESSOR_H
#define EMPTYBLOCKPROCESSOR_H

#include "../BlockProcessors.h"

namespace markdown
{

/*!
 * Process blocks that are empty or start with an empty line.
 */
class EmptyBlockProcessor : public BlockProcessor
{
public:
    using BlockProcessor::BlockProcessor;

    bool test(const Element &, const QString &block);

    bool run(const Element &parent, QStringList &blocks);

};

} // namespace markdown

#endif // EMPTYBLOCKPROCESSOR_H
