#ifndef INLINEPATTERNS_COMMON_H
#define INLINEPATTERNS_COMMON_H

#include "../ElementTree.hpp"

namespace markdown
{

extern const QString NOBRACKET;

extern const QString BRK;
extern const QString NOIMG;

//! `e=f()` or ``e=f("`")``
extern const QString BACKTICK_RE;

//! \<
extern const QString ESCAPE_RE;

//! *emphasis*
extern const QString EMPHASIS_RE;

//! **strong**
extern const QString STRONG_RE;

//! ***strongem*** or ***em*strong**
extern const QString EM_STRONG_RE;

//! ***strong**em*
extern const QString STRONG_EM_RE;

//! _smart_emphasis_
extern const QString SMART_EMPHASIS_RE;

//! _emphasis_
extern const QString EMPHASIS_2_RE;

//! [text](url) or [text](<url>) or [text](url "title")
extern const QString LINK_RE;

//! ![alttxt](http://x.com/) or ![alttxt](<http://x.com/>)
extern const QString IMAGE_LINK_RE;

//! [Google][3]
extern const QString REFERENCE_RE;

//! [Google]
extern const QString SHORT_REF_RE;

//! ![alt text][2]
extern const QString IMAGE_REFERENCE_RE;

//! stand-alone * or _
extern const QString NOT_STRONG_RE;

//!  <http://www.123.com>
extern const QString AUTOLINK_RE;

//! <me@example.com>
extern const QString AUTOMAIL_RE;

//! <...>
extern const QString HTML_RE;

//! &amp;
extern const QString ENTITY_RE;

//! two spaces at end of line
extern const QString LINE_BREAK_RE;

//! Remove quotes from around a string.
QString dequote(const QString &string);

QString itertext(const Element &elem);

extern const QRegularExpression ATTR_RE;

QString handleAttributes(const QString &text, const Element &parent);

} // namespace markdown

#endif // INLINEPATTERNS_COMMON_H
