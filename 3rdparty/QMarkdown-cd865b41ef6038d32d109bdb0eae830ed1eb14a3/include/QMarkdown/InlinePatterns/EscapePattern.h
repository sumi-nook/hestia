#ifndef ESCAPEPATTERN_H
#define ESCAPEPATTERN_H

#include "../InlinePatterns.h"

namespace markdown
{

/*!
 * Return an escaped character.
 */
class EscapePattern : public Pattern
{
public:
    EscapePattern(const QString &pattern, const std::weak_ptr<Markdown> &md);

    boost::optional<QString> handleMatch(const QRegularExpressionMatch &m);

    QString type(void) const;

};

} // namespace markdown

#endif // ESCAPEPATTERN_H
