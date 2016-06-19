#include "InlinePatterns/AutolinkPattern.h"

namespace markdown
{

AutolinkPattern::AutolinkPattern(const QString &pattern, const std::weak_ptr<Markdown> &md) :
    Pattern(pattern, md)
{}

Element AutolinkPattern::handleMatch(const ElementTree &, const QRegularExpressionMatch &m)
{
    Element el = createElement("a");
    el->set("href", this->unescape(m.captured(2)));
    el->text = m.captured(2);
    el->atomic = true;
    return el;
}

QString AutolinkPattern::type(void) const
{ return "AutolinkPattern"; }

} // namespace markdown
