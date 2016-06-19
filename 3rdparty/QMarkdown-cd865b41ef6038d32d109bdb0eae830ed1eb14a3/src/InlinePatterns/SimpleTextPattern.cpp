#include "InlinePatterns/SimpleTextPattern.h"

#include "util.h"

namespace markdown
{

SimpleTextPattern::SimpleTextPattern(const QString &pattern, const std::weak_ptr<Markdown> &md) :
    Pattern(pattern, md)
{}

boost::optional<QString> SimpleTextPattern::handleMatch(const QRegularExpressionMatch &m)
{
    QString text = m.captured(2);
    if ( text == util::INLINE_PLACEHOLDER_PREFIX ) {
        return boost::none;
    }
    return text;
}

QString SimpleTextPattern::type(void) const
{ return "SimpleTextPattern"; }

} // namespace markdown
