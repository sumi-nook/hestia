#ifndef AUTOMAILPATTERN_H
#define AUTOMAILPATTERN_H

#include "../InlinePatterns.h"

namespace markdown
{

/*!
 * Return a mailto link Element given an automail link (`<foo@example.com>`).
 */
class AutomailPattern : public Pattern
{
public:
    AutomailPattern(const QString &pattern, const std::weak_ptr<Markdown> &md);

    Element handleMatch(const ElementTree &, const QRegularExpressionMatch &m);

    QString type(void) const;

};

} // namespace markdown

#endif // AUTOMAILPATTERN_H
