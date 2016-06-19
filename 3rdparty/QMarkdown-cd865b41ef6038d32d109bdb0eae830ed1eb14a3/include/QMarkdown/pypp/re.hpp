#ifndef PYPP_RE_HPP
#define PYPP_RE_HPP

#include <functional>

#include <QRegularExpression>

#include "./str.hpp"

namespace pypp {

namespace re {

inline pypp::str escape(const pypp::str &string)
{
    pypp::str result;
    for ( const QChar &ch : string ) {
        if ( ch.isLetterOrNumber() || ch == '_' ) {
            result += ch;
        } else {
            result += '\\';
            result += ch;
        }
    }
    return result;
}

inline pypp::str sub(const QRegularExpression &pattern, const std::function<pypp::str(const QRegularExpressionMatch &)> &repl, const pypp::str &string)
{
    QStringList temp;
    int before = 0;
    QRegularExpressionMatchIterator it = pattern.globalMatch(string);
    if ( ! it.hasNext() ) {
        return string;
    }
    while ( it.hasNext() ) {
        QRegularExpressionMatch match = it.next();
        temp.append(string.mid(before, match.capturedStart()-before));
        before = match.capturedEnd();
        temp.append(repl(match));
    }
    temp.append(string.mid(before));
    return temp.join(QString());
}

inline pypp::str sub(const QRegularExpression &pattern, const QString &repl, const pypp::str &string)
{
    return sub(pattern, [repl](const QRegularExpressionMatch) -> pypp::str { return repl; }, string);
}

} // namespace re

} // namespace pypp

#endif // PYPP_RE_HPP

