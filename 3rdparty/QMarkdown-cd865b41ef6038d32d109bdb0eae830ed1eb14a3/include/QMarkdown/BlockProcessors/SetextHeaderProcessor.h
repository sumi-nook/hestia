#ifndef SETEXTHEADERPROCESSOR_H
#define SETEXTHEADERPROCESSOR_H

#include "../BlockProcessors.h"

namespace markdown
{

/*!
 * Process Setext-style Headers.
 */
class SetextHeaderProcessor : public BlockProcessor
{
public:
    SetextHeaderProcessor(const std::weak_ptr<BlockParser> &parser);

    bool test(const Element &, const QString &block);

    bool run(const Element &parent, QStringList &blocks);

private:
    //! Detect Setext-style header. Must be first 2 lines of block.
    const QRegularExpression RE;

};

} // namespace markdown

#endif // SETEXTHEADERPROCESSOR_H
