#ifndef SIMPLETAGPATTERN_H
#define SIMPLETAGPATTERN_H

#include "../InlinePatterns.h"

namespace markdown
{

/*!
 * Return element of type `tag` with a text attribute of group(3)
 * of a Pattern.
 */
class SimpleTagPattern : public Pattern
{
public:
    SimpleTagPattern(const QString &pattern, const QString &tag, const std::weak_ptr<Markdown> &md=std::weak_ptr<Markdown>());
    virtual ~SimpleTagPattern();

    virtual Element handleMatch(const ElementTree &, const QRegularExpressionMatch &m);

    virtual QString type(void) const;

protected:
    QString tag;

};

/*!
 * Return an element of type `tag` with no children.
 */
class SubstituteTagPattern : public SimpleTagPattern
{
public:
    SubstituteTagPattern(const QString &pattern, const QString &tag, const std::weak_ptr<Markdown> &md=std::weak_ptr<Markdown>());

    Element handleMatch(const ElementTree &, const QRegularExpressionMatch &);

    QString type(void) const;

};

/*!
 * Return a Element element nested in tag2 nested in tag1.
 *
 * Useful for strong emphasis etc.
 *
 */
class DoubleTagPattern : public SimpleTagPattern
{
public:
    DoubleTagPattern(const QString &pattern, const QString &tag, const std::weak_ptr<Markdown> &md=std::weak_ptr<Markdown>());

    Element handleMatch(const ElementTree &, const QRegularExpressionMatch &m);

    QString type(void) const;

};

} // namespace markdown

#endif // SIMPLETAGPATTERN_H
