#include "ruby.h"

#include "QMarkdown/Markdown.h"
#include "QMarkdown/InlinePatterns.h"


class Ruby : public markdown::Pattern
{
public:
    using markdown::Pattern::Pattern;

    markdown::Element handleMatch(const markdown::ElementTree &, const QRegularExpressionMatch &m)
    {
        QString kanji = m.captured(2).trimmed();
        QString kana = m.captured(3).trimmed();
        if ( ! kanji.isEmpty() && ! kana.isEmpty() ) {
            markdown::Element ruby = markdown::createElement("ruby");
            markdown::createSubElement(ruby, "rb")->text = kanji;
            markdown::createSubElement(ruby, "rp")->text = "(";
            markdown::createSubElement(ruby, "rt")->text = kana;
            markdown::createSubElement(ruby, "rp")->text = ")";
            return ruby;
        }
        return markdown::Element();
    }

    QString type() const
    {
        return "Ruby";
    }

};


RubyExtension::RubyExtension()
{

}

void RubyExtension::extendMarkdown(const std::shared_ptr<markdown::Markdown> &md)
{
    // append to inline patterns
    QString RUBY_RE = "\\[([^\\]]+)\\]\\(ruby:([^\\)]+)\\)";
    md->inlinePatterns.add("ruby", std::shared_ptr<markdown::Pattern>(new Ruby(RUBY_RE)), "<link");
}

markdown::Extension::Ptr RubyExtension::generate()
{
    return std::shared_ptr<markdown::Extension>(new RubyExtension);
}
