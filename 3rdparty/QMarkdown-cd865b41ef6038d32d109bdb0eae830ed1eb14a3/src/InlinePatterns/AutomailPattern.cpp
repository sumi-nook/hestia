#include "InlinePatterns/AutomailPattern.h"

#include "htmlentitydefs.hpp"
#include "util.h"

namespace markdown
{

AutomailPattern::AutomailPattern(const QString &pattern, const std::weak_ptr<Markdown> &md) :
    Pattern(pattern, md)
{}

Element AutomailPattern::handleMatch(const ElementTree &, const QRegularExpressionMatch &m)
{
    Element el = createElement("a");
    QString email = this->unescape(m.captured(2));
    if ( email.startsWith("mailto:") ) {
        email = email.mid(7);
    }

    QString letters;
    for ( const QChar &ch : email ) {
        if ( codepoint2name.contains(ch) ) {
            letters += QString("%1%2;").arg(util::AMP_SUBSTITUTE).arg(codepoint2name[ch]);
        } else {
            letters += QString("%1#%2;").arg(util::AMP_SUBSTITUTE).arg(QString::number(ch.unicode()));
        }
    }
    el->text = letters;
    el->atomic = true;

    QString mailto = "mailto:"+email;
    QString buff;
    for ( int i = 0; i < mailto.size(); ++i ) {
        QChar ch = mailto.at(i);
        buff.append(QString("%1#%2;").arg(util::AMP_SUBSTITUTE, QString::number(ch.unicode())));
    }
    mailto = buff;

    el->set("href", this->unescape(mailto));
    return el;
}

QString AutomailPattern::type(void) const
{ return "AutomailPattern"; }

} // namespace markdown
