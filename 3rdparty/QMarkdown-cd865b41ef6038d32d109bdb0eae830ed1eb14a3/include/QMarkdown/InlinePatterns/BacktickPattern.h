#ifndef BACKTICKPATTERN_H
#define BACKTICKPATTERN_H

#include "../InlinePatterns.h"

namespace markdown
{

/*!
 * Return a `<code>` element containing the matching text.
 */
class BacktickPattern : public Pattern
{
public:
    BacktickPattern(const QString &pattern, const std::weak_ptr<Markdown> &md=std::weak_ptr<Markdown>());

    virtual Element handleMatch(const ElementTree &, const QRegularExpressionMatch &m);

    virtual QString type(void) const;

private:
    QString tag;

};

} // namespace markdown

#endif // BACKTICKPATTERN_H
