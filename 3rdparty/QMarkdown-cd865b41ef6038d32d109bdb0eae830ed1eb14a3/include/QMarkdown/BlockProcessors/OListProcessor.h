#ifndef OLISTPROCESSOR_H
#define OLISTPROCESSOR_H

#include "../BlockProcessors.h"

#include <QSet>

namespace markdown
{

/*!
 * Process ordered list blocks.
 */
class OListProcessor : public BlockProcessor
{
public:
    OListProcessor(const std::weak_ptr<BlockParser> &parser);
    virtual ~OListProcessor();

    bool test(const Element &, const QString &block);

    bool run(const Element &parent, QStringList &blocks);

    /*!
     * Break a block into list items.
     */
    QStringList get_items(const QString &block);

protected:
    QString TAG;
    //! Detect an item (``1. item``). ``group(1)`` contains contents of item.
    QRegularExpression RE;

private:
    //! Detect items on secondary lines. they can be of either list type.
    const QRegularExpression CHILD_RE;
    //! Detect indented (nested) items of either type
    const QRegularExpression INDENT_RE;
    //! The integer (python string) with which the lists starts (default=1)
    //! Eg: If list is intialized as)
    //!   3. Item
    //! The ol tag will get starts="3" attribute
    QString STARTSWITH;
    //! List of allowed sibling tags.
    const QSet<QString> SIBLING_TAGS;

};

class UListProcessor : public OListProcessor
{
public:
    UListProcessor(const std::weak_ptr<BlockParser> &parser);

};

} // namespace markdown

#endif // OLISTPROCESSOR_H
