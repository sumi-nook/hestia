#ifndef AUTOLINKPATTERN_H
#define AUTOLINKPATTERN_H

#include "../InlinePatterns.h"

namespace markdown
{

/*!
 * Return a link Element given an autolink (`<http://example/com>`).
 */
class AutolinkPattern : public Pattern
{
public:
    AutolinkPattern(const QString &pattern, const std::weak_ptr<Markdown> &md);

    Element handleMatch(const ElementTree &, const QRegularExpressionMatch &m);

    QString type(void) const;

};

} // namespace markdown

#endif // AUTOLINKPATTERN_H
