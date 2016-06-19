#ifndef CODEBLOCKPROCESSOR_H
#define CODEBLOCKPROCESSOR_H

#include "../BlockProcessors.h"

namespace markdown
{

/*!
 * Process code blocks.
 */
class CodeBlockProcessor : public BlockProcessor
{
public:
    using BlockProcessor::BlockProcessor;

    bool test(const Element &, const QString &block);

    bool run(const Element &parent, QStringList &blocks);

};

} // namespace markdown

#endif // CODEBLOCKPROCESSOR_H
