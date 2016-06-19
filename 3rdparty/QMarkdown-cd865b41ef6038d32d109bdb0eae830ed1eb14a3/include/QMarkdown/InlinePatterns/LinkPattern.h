#ifndef LINKPATTERN_H
#define LINKPATTERN_H

#include "../InlinePatterns.h"

namespace markdown
{

/*!
 * Return a link element from the given match.
 */
class LinkPattern : public Pattern
{
public:
    LinkPattern(const QString& pattern, const std::weak_ptr<Markdown> &md);
    virtual ~LinkPattern(void);

    virtual Element handleMatch(const ElementTree &, const QRegularExpressionMatch &m);

    /*!
     * Sanitize a url against xss attacks in "safe_mode".
     *
     * Rather than specifically blacklisting `javascript:alert("XSS")` and all
     * its aliases (see <http://ha.ckers.org/xss.html>), we whitelist known
     * safe url formats. Most urls contain a network location, however some
     * are known not to (i.e.: mailto links). Script urls do not contain a
     * location. Additionally, for `javascript:...`, the scheme would be
     * "javascript" but some aliases will appear to `urlparse()` to have no
     * scheme. On top of that relative links (i.e.: "foo/bar.html") have no
     * scheme. Therefore we must check "path", "parameters", "query" and
     * "fragment" for any literal colons. We don't check "scheme" for colons
     * because it *should* never have any and "netloc" must allow the form:
     * `username:password@host:port`.
     *
     */
    QString sanitize_url(QString url);

    virtual QString type(void) const;

};

/*!
 * Return a img element from the given match.
 */
class ImagePattern : public LinkPattern
{
public:
    ImagePattern(const QString &pattern, const std::weak_ptr<Markdown> &md);

    Element handleMatch(const ElementTree &, const QRegularExpressionMatch &m);

    QString type(void) const;

};

class ReferencePattern : public LinkPattern
{
public:
    ReferencePattern(const QString &pattern, const std::weak_ptr<Markdown> &md);
    virtual ~ReferencePattern(void);

    Element handleMatch(const ElementTree &doc, const QRegularExpressionMatch &m);

    virtual Element makeTag(const ElementTree &, const QString &href, const QString &title, const QString &text);

    virtual QString type(void) const;

private:
    QRegularExpression NEWLINE_CLEANUP_RE;

};

/*!
 * Match to a stored reference and return img element.
 */
class ImageReferencePattern : public ReferencePattern
{
public:
    ImageReferencePattern(const QString &pattern, const std::weak_ptr<Markdown> &md);

    Element makeTag(const ElementTree &, const QString &href, const QString &title, const QString &text);

    virtual QString type(void) const;

};

} // namespace markdown

#endif // LINKPATTERN_H
