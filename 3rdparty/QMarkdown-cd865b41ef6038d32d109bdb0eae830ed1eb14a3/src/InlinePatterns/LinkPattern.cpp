#include "InlinePatterns/LinkPattern.h"

#include <QUrl>
#include <QUrlQuery>

#include "Markdown.h"
#include "InlinePatterns/common.h"

namespace markdown
{

LinkPattern::LinkPattern(const QString& pattern, const std::weak_ptr<Markdown> &md) :
    Pattern(pattern, md)
{}
LinkPattern::~LinkPattern(void)
{}

Element LinkPattern::handleMatch(const ElementTree &, const QRegularExpressionMatch &m)
{
    Element el = createElement("a");
    el->text = m.captured(2);
    QString title = m.captured(13);
    QString href  = m.captured(9);

    if ( ! href.isEmpty() ) {
        if ( href.startsWith('<') ) {
            href = href.mid(1, href.size()-2);
        }
        el->set("href", this->sanitize_url(this->unescape(href.trimmed())));
    } else {
        el->set("href", QString());
    }

    if ( ! title.isEmpty() ) {
        title = dequote(this->unescape(title));
        el->set("title", title);
    }

    return el;
}

QString LinkPattern::sanitize_url(QString url)
{
    QString result = url;
    if ( ! this->markdown.lock()->safeMode() ) {
        //! Return immediately bipassing parsing.
        return result;
    }
    QSet<QString> locless_schemes = {"", "mailto", "news"};
    QSet<QString> allowed_schemes = {"", "mailto", "news", "http", "https", "ftp", "ftps"};

    QUrl qurl(result);
    if ( ! allowed_schemes.contains(qurl.scheme()) ) {
        //! Not a known (allowed) scheme. Not safe.
        return QString();
    }
    if ( qurl.host().isEmpty() && ! locless_schemes.contains(qurl.scheme()) ) {
        //! This should not happen. Treat as suspect.
        return QString();
    }
    //! A colon in "path", "parameters", "query" or "fragment" is suspect.
    if ( qurl.path().contains(":") || qurl.fragment().contains(":") ) {
        return QString();
    }
    for ( const QPair<QString, QString> &item : QUrlQuery(qurl).queryItems() ) {
        if ( item.first.contains(":") || item.second.contains(":") ) {
            return QString();
        }
    }
    //! Url passes all tests. Return url as-is.
    return qurl.toString();

    /*
    int pos = result.indexOf(":");
    if ( pos == -1 ) {
        return QString();
    }
    QString scheme = result.left(pos);
    if ( ! allowed_schemes.contains(scheme) ) {
        //! Not a known (allowed) scheme. Not safe.
        return QString();
    }
    QRegularExpressionMatch m = QRegularExpression("[a-zA-Z][a-zA-Z0-9+\\-.]*://[^/]+/?(.*)").match(result);
    bool ret = m.hasMatch();
    if ( ! ret && ! locless_schemes.contains(scheme) ) {
        //! This should not happen. Treat as suspect.
        return QString();
    }
    QString path;
    if ( ret ) {
        path = m.captured(1);
    } else {
        ++pos;
        path = result.mid(pos);
    }
    if ( path.contains(":") ) {
        return QString();
    }
    return result;
    */
}

QString LinkPattern::type(void) const
{ return "LinkPattern"; }


ImagePattern::ImagePattern(const QString &pattern, const std::weak_ptr<Markdown> &md) :
    LinkPattern(pattern, md)
{}

Element ImagePattern::handleMatch(const ElementTree &, const QRegularExpressionMatch &m)
{
    std::shared_ptr<Markdown> markdown = this->markdown.lock();

    Element el = createElement("img");
    QString src_parts_source = m.captured(9);
    QStringList src_parts = pypp::split(src_parts_source);
    if ( ! src_parts.isEmpty() ) {
        QString src = src_parts.at(0);
        if ( src.startsWith('<') && src.endsWith('>') ) {
            src = src.mid(1, src.size()-2);
        }
        el->set("src", this->sanitize_url(src));
    } else {
        el->set("src", QString());
    }
    if ( src_parts.size() > 1 ) {
        src_parts.erase(src_parts.begin());
        el->set("title", dequote(this->unescape(src_parts.join(" "))));
    }

    QString truealt;
    if ( markdown->enable_attributes() ) {
        truealt = handleAttributes(m.captured(2), el);
    } else {
        truealt = m.captured(2);
    }

    el->set("alt", this->unescape(truealt));
    return el;
}

QString ImagePattern::type(void) const
{ return "ImagePattern"; }


ReferencePattern::ReferencePattern(const QString &pattern, const std::weak_ptr<Markdown> &md) :
    LinkPattern(pattern, md),
    NEWLINE_CLEANUP_RE("[ ]?\\n", QRegularExpression::MultilineOption)
{}
ReferencePattern::~ReferencePattern(void)
{}

Element ReferencePattern::handleMatch(const ElementTree &doc, const QRegularExpressionMatch &m)
{
    std::shared_ptr<Markdown> markdown = this->markdown.lock();

    QString id;
    if ( m.capturedTexts().size() > 8 && ! m.captured(9).isEmpty() ) {
        id = m.captured(9);
    } else {
        //! if we got something like "[Google][]" or "[Goggle]"
        //! we'll use "google" as the id
        id = m.captured(2);
    }
    id = id.toLower();

    //! Clean up linebreaks in id
    id = id.replace(this->NEWLINE_CLEANUP_RE, " ");
    if ( ! markdown->references.contains(id) ) {
        return Element();
    }
    Markdown::ReferenceItem item = markdown->references[id];

    QString text = m.captured(2);
    return this->makeTag(doc, item.first, item.second, text);
}

Element ReferencePattern::makeTag(const ElementTree &, const QString &href, const QString &title, const QString &text)
{
    Element el = createElement("a");

    el->set("href", this->sanitize_url(href));
    if ( ! title.isEmpty() ) {
        el->set("title", title);
    }

    el->text = text;
    return el;
}

QString ReferencePattern::type(void) const
{ return "ReferencePattern"; }


ImageReferencePattern::ImageReferencePattern(const QString &pattern, const std::weak_ptr<Markdown> &md) :
    ReferencePattern(pattern, md)
{}

Element ImageReferencePattern::makeTag(const ElementTree &, const QString &href, const QString &title, const QString &text)
{
    Element el = createElement("img");

    el->set("src", this->sanitize_url(href));
    if ( ! title.isEmpty() ) {
        el->set("title", title);
    }

    QString text_ = text;
    if ( this->markdown.lock()->enable_attributes() ) {
        text_ = handleAttributes(text, el);
    }

    el->set("alt", this->unescape(text_));
    return el;
}

QString ImageReferencePattern::type(void) const
{ return "ImageReferencePattern"; }

} // namespace markdown
