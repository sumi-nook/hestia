#include "InlinePatterns/SimpleTagPattern.h"

#include "InlinePatterns/common.h"

namespace markdown
{

SimpleTagPattern::SimpleTagPattern(const QString &pattern, const QString &tag, const std::weak_ptr<Markdown> &md) :
    Pattern(pattern, md),
    tag(tag)
{}
SimpleTagPattern::~SimpleTagPattern()
{}

Element SimpleTagPattern::handleMatch(const ElementTree &, const QRegularExpressionMatch &m)
{
    Element el = createElement(this->tag);
    el->text = m.captured(3);
    return el;
}

QString SimpleTagPattern::type(void) const
{ return "SimpleTagPattern"; }


SubstituteTagPattern::SubstituteTagPattern(const QString &pattern, const QString &tag, const std::weak_ptr<Markdown> &md) :
    SimpleTagPattern(pattern, tag, md)
{}

Element SubstituteTagPattern::handleMatch(const ElementTree &, const QRegularExpressionMatch &)
{
    return createElement(this->tag);
}

QString SubstituteTagPattern::type(void) const
{ return "SubstituteTagPattern"; }


DoubleTagPattern::DoubleTagPattern(const QString &pattern, const QString &tag, const std::weak_ptr<Markdown> &md) :
    SimpleTagPattern(pattern, tag, md)
{}

Element DoubleTagPattern::handleMatch(const ElementTree &, const QRegularExpressionMatch &m)
{
    QStringList tags = this->tag.split(",");
    Element el1 = createElement(tags.at(0));
    Element el2 = createSubElement(el1, tags.at(1));
    el2->text = m.captured(3);
    if ( ! m.captured(4).isEmpty() ) {
        el2->tail = m.captured(4);
    }
    return el1;
}

QString DoubleTagPattern::type(void) const
{ return "DoubleTagPattern"; }

} // namespace markdown
