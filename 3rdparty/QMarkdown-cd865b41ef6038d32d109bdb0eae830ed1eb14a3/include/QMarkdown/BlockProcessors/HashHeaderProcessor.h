#ifndef HASHHEADERPROCESSOR_H
#define HASHHEADERPROCESSOR_H

#include "../BlockProcessors.h"

namespace markdown
{

/*!
 * Process Hash Headers.
 */
class HashHeaderProcessor : public BlockProcessor
{
public:
    HashHeaderProcessor(const std::weak_ptr<BlockParser> &parser);

    bool test(const Element &, const QString &block);

    bool run(const Element &parent, QStringList &blocks);

private:
    //! Detect a header at start of any line in block
    QRegularExpression RE;

};

} // namespace markdown

#endif // HASHHEADERPROCESSOR_H
