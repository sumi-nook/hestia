#include "InlinePatterns/HtmlPattern.h"

#include "Markdown.h"

namespace markdown
{

HtmlPattern::HtmlPattern(const QString &pattern, const std::weak_ptr<Markdown> &md) :
    Pattern(pattern, md)
{}

boost::optional<QString> HtmlPattern::handleMatch(const QRegularExpressionMatch &m)
{
    QString rawHtml = this->unescape(m.captured(2));
    return this->markdown.lock()->htmlStash.store(rawHtml);
}

QString HtmlPattern::type(void) const
{ return "HtmlPattern"; }

QString HtmlPattern::unescape(const QString &text)
{
    TreeProcessor::StashNodes stash;
    if ( this->markdown.lock()->treeprocessors.exists("inline") ) {
        stash = this->markdown.lock()->treeprocessors["inline"]->stashed_nodes;
    } else {
        return text;
    }
    auto get_stash = [&](const QRegularExpressionMatch &m) -> QString {
        QString id = m.captured(1);
        if ( stash.contains(id) ) {
            boost::optional<QString> str;
            boost::optional<Element> node;
            std::tie(str, node) = stash[id];
            if ( str ) {
                return "\\" + *str;
            } else {
                return this->markdown.lock()->serializer(*node);
            }
        }
        return QString();
    };
    return pypp::re::sub(util::INLINE_PLACEHOLDER_RE, get_stash, text);
}

} // namespace markdown
