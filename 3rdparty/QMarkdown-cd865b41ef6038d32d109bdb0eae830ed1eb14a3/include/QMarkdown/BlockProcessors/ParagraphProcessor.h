#ifndef PARAGRAPHPROCESSOR_H
#define PARAGRAPHPROCESSOR_H

#include "../BlockProcessors.h"

namespace markdown
{

/*!
 * Process Paragraph blocks.
 */
class ParagraphProcessor : public BlockProcessor
{
public:
    using BlockProcessor::BlockProcessor;

    bool test(const Element &, const QString &);

    bool run(const Element &parent, QStringList &blocks);

};

} // namespace markdown

#endif // PARAGRAPHPROCESSOR_H
