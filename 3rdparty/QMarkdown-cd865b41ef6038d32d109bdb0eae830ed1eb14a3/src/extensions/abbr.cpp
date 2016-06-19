#include "extensions/abbr.h"

#include "Markdown.h"
#include "PreProcessors.h"

namespace markdown
{

const QRegularExpression ABBR_REF_RE(R"([*]\[(?<abbr>[^\]]*)\][ ]?:\s*(?<title>.*))");

/*!
 * Abbreviation inline pattern.
 */
class AbbrPattern : public Pattern
{
public:
    AbbrPattern(const QString &pattern, const QString &title) :
        Pattern(pattern),
        title(title)
    {}

    Element handleMatch(const ElementTree &, const QRegularExpressionMatch &m)
    {
        Element abbr = createElement("abbr");
        abbr->text = m.captured("abbr");
        abbr->atomic = true;
        abbr->set("title", this->title);
        return abbr;
    }

    QString type() const
    { return "AbbrPattern"; }

    QString title;

};

/*!
 * Abbreviation Preprocessor - parse text for abbr references.
 */
class AbbrPreprocessor : public PreProcessor
{
public:
    using PreProcessor::PreProcessor;

    /*!
     * Find and remove all Abbreviation references from the text.
     * Each reference is set as a new AbbrPattern in the markdown instance.
     */
    QStringList run(const QStringList &lines)
    {
        std::shared_ptr<Markdown> markdown = this->markdown.lock();

        QStringList new_text;
        for ( const QString &line : lines ) {
            QRegularExpressionMatch m = ABBR_REF_RE.match(line);
            if ( m.hasMatch() ) {
                QString abbr = m.captured("abbr").trimmed();
                QString title = m.captured("title").trimmed();
                markdown->inlinePatterns[QString("abbr-%1").arg(abbr)] = std::make_shared<AbbrPattern>(this->generate_pattern(abbr), title);
            } else {
                new_text.append(line);
            }
        }
        return new_text;
    }

    /*!
     * Given a string, returns an regex pattern to match that string.
     *
     * 'HTML' -> r'(?P<abbr>[H][T][M][L])'
     *
     * Note: we force each char as a literal match (in brackets) as we don't
     * know what they will be beforehand.
     */
    QString generate_pattern(const QString &text)
    {
        QString chars;
        for ( int i = 0; i < text.size(); ++i ) {
            chars += QString("[%1]").arg(text.at(i));
        }
        return QString("(?<abbr>\\b%1\\b)").arg(chars);
    }

};

AbbrExtension::AbbrExtension() :
    Extension()
{

}

/*!
 * Insert AbbrPreprocessor before ReferencePreprocessor.
 */
void AbbrExtension::extendMarkdown(const std::shared_ptr<Markdown> &md)
{
    md->preprocessors.add("abbr", std::shared_ptr<Processor>(new AbbrPreprocessor(md)), "<reference");
}

Extension::Ptr AbbrExtension::generate()
{
    return std::shared_ptr<Extension>(new AbbrExtension);
}



} // namespace markdown
