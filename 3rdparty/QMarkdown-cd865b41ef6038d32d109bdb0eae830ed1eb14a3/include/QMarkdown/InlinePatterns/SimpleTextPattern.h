#ifndef SIMPLETEXTPATTERN_H
#define SIMPLETEXTPATTERN_H

#include "../InlinePatterns.h"

namespace markdown
{

/*!
 * Return a simple text of group(2) of a Pattern.
 */
class SimpleTextPattern : public Pattern
{
public:
    SimpleTextPattern(const QString &pattern, const std::weak_ptr<Markdown> &md=std::weak_ptr<Markdown>());

    boost::optional<QString> handleMatch(const QRegularExpressionMatch &m);

    QString type(void) const;

};

} // namespace markdown

#endif // SIMPLETEXTPATTERN_H
