#ifndef HTMLPATTERN_H
#define HTMLPATTERN_H

#include "../InlinePatterns.h"

namespace markdown
{

class HtmlPattern : public Pattern
{
public:
    HtmlPattern(const QString &pattern, const std::weak_ptr<Markdown> &md);

    boost::optional<QString> handleMatch(const QRegularExpressionMatch &m);

    QString type(void) const;

    QString unescape(const QString &text);

};

} // namespace markdown

#endif // HTMLPATTERN_H
