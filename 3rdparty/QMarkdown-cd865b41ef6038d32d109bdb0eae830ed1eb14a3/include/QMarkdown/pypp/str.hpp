#ifndef PYPP_STR_HPP
#define PYPP_STR_HPP

#include <QRegularExpression>
#include <QString>
#include <QTextCodec>

#include "./exceptions.hpp"

namespace pypp {

typedef QString str;

inline QByteArray encode(const pypp::str &text, const pypp::str &encoding)
{
    QTextCodec *codec = QTextCodec::codecForName(encoding.toUtf8());
    if ( ! codec ) {
        throw LookupError();
    }
    return codec->fromUnicode(text);
}

inline pypp::str decode(const QByteArray &bytes, const pypp::str &encoding)
{
    QTextCodec *codec = QTextCodec::codecForName(encoding.toUtf8());
    if ( ! codec ) {
        throw LookupError();
    }
    return codec->toUnicode(bytes);
}

inline pypp::str capitalize(const pypp::str &in)
{
    return pypp::str(in.at(0).toUpper()) + in.mid(1);
}

inline pypp::str expandtabs(const pypp::str &in, int tabsize)
{
    pypp::str result;
    int n = 0;
    for ( const auto &ch : in ) {
        if ( n >= tabsize ) {
            n = 0;
        }
        if ( ch == '\t' ) {
            result += pypp::str(tabsize-n, ' ');
        } else {
            result += ch;
            if ( ch == '\n' ) {
                n = 0;
            } else {
                ++n;
            }
        }
    }
    return result;
}

inline QStringList split(const pypp::str &in)
{
    return in.split(QRegularExpression("\\s"));
}

inline pypp::str lstrip(const pypp::str &in)
{
    for (int i = 0; i < in.size(); ++i) {
        if ( ! in.at(i).isSpace() ) {
            return in.mid(i);
        }
    }
    return pypp::str();
}

inline pypp::str rstrip(const pypp::str &in)
{
    for (int i = in.size()-1; i >= 0; --i) {
        if ( ! in.at(i).isSpace() ) {
            return in.left(i + 1);
        }
    }
    return pypp::str();
}

inline pypp::str lstrip(const pypp::str &in, const std::function<bool(const QChar &)> &isSpace)
{
    for (int i = 0; i < in.size(); ++i) {
        if ( ! isSpace(in.at(i)) ) {
            return in.mid(i);
        }
    }
    return pypp::str();
}

inline pypp::str rstrip(const pypp::str &in, const std::function<bool(const QChar &)> &isSpace)
{
    for (int i = in.size()-1; i >= 0; --i) {
        if ( ! isSpace(in.at(i)) ) {
            return in.left(i + 1);
        }
    }
    return pypp::str();
}

inline pypp::str lstrip(const pypp::str &in, const pypp::str &chars)
{
    auto removeChars = [chars](const QChar &ch) -> bool { return QString(ch) == chars; };
    return lstrip(in, removeChars);
}

inline pypp::str rstrip(const pypp::str &in, const pypp::str &chars)
{
    auto removeChars = [chars](const QChar &ch) -> bool { return QString(ch) == chars; };
    return rstrip(in, removeChars);
}

inline pypp::str strip(const pypp::str &in, const pypp::str &chars)
{
    return rstrip(lstrip(in, chars), chars);
}

} // namespace pypp

#endif // PYPP_STR_HPP

