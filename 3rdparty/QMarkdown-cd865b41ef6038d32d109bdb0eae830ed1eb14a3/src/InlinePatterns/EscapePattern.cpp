#include "InlinePatterns/EscapePattern.h"

#include "InlinePatterns/common.h"

#include "Markdown.h"

namespace markdown
{

EscapePattern::EscapePattern(const QString &pattern, const std::weak_ptr<Markdown> &md) :
    Pattern(pattern, md)
{}

boost::optional<QString> EscapePattern::handleMatch(const QRegularExpressionMatch &m)
{
    QString text = m.captured(2);
    if ( text.size() > 1 ) {
        return QString("\\%1").arg(text);
    }
    QChar ch = text.at(0);
    if ( this->markdown.lock()->ESCAPED_CHARS.contains(ch) ) {
        return QString("%1%2%3").arg(util::STX).arg(ch.unicode()).arg(util::ETX);
    } else {
        return boost::none;
    }
}

QString EscapePattern::type(void) const
{ return "EscapePattern"; }

} // namespace markdown
