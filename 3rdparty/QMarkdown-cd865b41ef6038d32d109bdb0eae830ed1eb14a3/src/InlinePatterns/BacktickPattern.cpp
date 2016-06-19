#include "InlinePatterns/BacktickPattern.h"

namespace markdown
{

BacktickPattern::BacktickPattern(const QString &pattern, const std::weak_ptr<Markdown> &md) :
    Pattern(pattern, md),
    tag("code")
{}

Element BacktickPattern::handleMatch(const ElementTree &, const QRegularExpressionMatch &m)
{
    Element el = createElement(this->tag);
    el->text = m.captured(3).trimmed();
    el->atomic = true;
    return el;
}

QString BacktickPattern::type() const
{ return "BacktickPattern"; }

} // namespace markdown
