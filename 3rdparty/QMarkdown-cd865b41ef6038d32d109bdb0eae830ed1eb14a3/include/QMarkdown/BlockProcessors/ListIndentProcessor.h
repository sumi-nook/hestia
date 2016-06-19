#ifndef LISTINDENTPROCESSOR_H
#define LISTINDENTPROCESSOR_H

#include "../BlockProcessors.h"

#include <QSet>

namespace markdown
{

/*!
 * Process children of list items.
 *
 *  Example:
 *      * a list item
 *          process this part
 *
 *          or this part
 *
 */
class ListIndentProcessor : public BlockProcessor
{
public:
    ListIndentProcessor(const std::weak_ptr<BlockParser> &parser);
    virtual ~ListIndentProcessor(void);

    bool test(const Element &parent, const QString &block);

    bool run(const Element &parent, QStringList &blocks);

    /*!
     * Create a new li and parse the block with it as the parent.
     */
    virtual void create_item(const Element &parent, const QString &block);

    /*!
     * Get level of indent based on list level.
     */
    std::tuple<int, Element> get_level(const Element &parent, const QString &block);

protected:
    QSet<QString> ITEM_TYPES;
    QSet<QString> LIST_TYPES;

private:
    QRegularExpression INDENT_RE;

};

} // namespace markdown

#endif // LISTINDENTPROCESSOR_H
