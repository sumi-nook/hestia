#include "InlinePatterns/common.h"

#include "pypp/re.hpp"

namespace markdown
{

const QString NOBRACKET("[^\\]\\[]*");

const QString BRK = ( "\\[("
        + (NOBRACKET + "(\\[") + (NOBRACKET + "(\\[") + (NOBRACKET + "(\\[") + (NOBRACKET + "(\\[") + (NOBRACKET + "(\\[") + (NOBRACKET + "(\\[")
        + (NOBRACKET + "\\])*") + (NOBRACKET + "\\])*") + (NOBRACKET + "\\])*") + (NOBRACKET + "\\])*") + (NOBRACKET + "\\])*") + (NOBRACKET + "\\])*")
        + NOBRACKET + ")\\]" );
const QString NOIMG = "(?<!\\!)";

//! `e=f()` or ``e=f("`")``
const QString BACKTICK_RE = "(?<!\\\\)(`+)(.+?)(?<!`)\\2(?!`)";

//! \<
const QString ESCAPE_RE = "\\\\(.)";

//! *emphasis*
const QString EMPHASIS_RE = "(\\*)([^\\*]+)\\2";

//! **strong**
const QString STRONG_RE = "(\\*{2}|_{2})(.+?)\\2";

//! ***strongem*** or ***em*strong**
const QString EM_STRONG_RE = "(\\*|_)\\2{2}(.+?)\\2(.*?)\\2{2}";

//! ***strong**em*
const QString STRONG_EM_RE = "(\\*|_)\\2{2}(.+?)\\2{2}(.*?)\\2";

//! _smart_emphasis_
const QString SMART_EMPHASIS_RE = "(?<!\\w)(_)(?!_)(.+?)(?<!_)\\2(?!\\w)";

//! _emphasis_
const QString EMPHASIS_2_RE = "(_)(.+?)\\2";

//! [text](url) or [text](<url>) or [text](url "title")
const QString LINK_RE = NOIMG + BRK + "\\(\\s*(<.*?>|((?:(?:\\(.*?\\))|[^\\(\\)]))*?)\\s*((['\"])(.*?)\\12\\s*)?\\)";

//! ![alttxt](http://x.com/) or ![alttxt](<http://x.com/>)
const QString IMAGE_LINK_RE = "\\!" + BRK + "\\s*\\((<.*?>|([^\")]+\"[^\"]*\"|[^\\)]*))\\)";

//! [Google][3]
const QString REFERENCE_RE = NOIMG + BRK + "\\s?\\[([^\\]]*)\\]";

//! [Google]
const QString SHORT_REF_RE = NOIMG + "\\[([^\\]]+)\\]";

//! ![alt text][2]
const QString IMAGE_REFERENCE_RE = "\\!" + BRK + "\\s?\\[([^\\]]*)\\]";

//! stand-alone * or _
const QString NOT_STRONG_RE = "((^| )(\\*|_)( |$))";

//!  <http://www.123.com>
const QString AUTOLINK_RE = "<((?:[Ff]|[Hh][Tt])[Tt][Pp][Ss]?://[^>]*)>";

//! <me@example.com>
const QString AUTOMAIL_RE = "<([^> \\!]*@[^> ]*)>";

//! <...>
const QString HTML_RE = "(<([a-zA-Z/][^>]*?|\\!--.*?--)>)";

//! &amp;
const QString ENTITY_RE = "(&[\\#a-zA-Z0-9]*;)";

//! two spaces at end of line
const QString LINE_BREAK_RE = "  \\n";

//! Remove quotes from around a string.
QString dequote(const QString &string)
{
    if ( ( string.startsWith('"') && string.endsWith('"') ) || ( string.startsWith('\'') && string.endsWith('\'') ) ) {
        return string.mid(1, string.size()-2);
    } else {
        return string;
    }
}

QString itertext(const Element &elem)
{
    QString tag = elem->tag;
    if ( tag.isEmpty() ) {
        return QString();
    }
    QString result = elem->text;
    for ( int i = 0; i < elem->size(); ++i ) {
        result += itertext((*elem)[i]);
        result += (*elem)[i]->tail;
    }
    return result;
}

const QRegularExpression ATTR_RE("\\{@([^\\}]*)=([^\\}]*)\\}");

QString handleAttributes(const QString &text, const Element &parent)
{
    return pypp::re::sub(ATTR_RE, [&](const QRegularExpressionMatch &m) -> QString {
        parent->set(m.captured(1), m.captured(2).replace("\n",  " "));
        return pypp::str();
    }, text);
}

} // namespace markdown
