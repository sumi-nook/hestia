#include "PreProcessors/ReferencePreprocessor.h"

#include "Markdown.h"

namespace markdown
{

ReferencePreprocessor::ReferencePreprocessor(const std::weak_ptr<Markdown> &markdown_instance) :
    PreProcessor(markdown_instance),
    TITLE("[ ]*(\\\"(.*)\\\"|\\'(.*)\\'|\\((.*)\\))[ ]*"),
    RE(QString("^[ ]{0,3}\\[([^\\]]*)\\]:\\s*([^ ]*)[ ]*(%1)?$").arg(this->TITLE), QRegularExpression::DotMatchesEverythingOption),
    TITLE_RE(QString("^%1$").arg(this->TITLE))
{}

QStringList ReferencePreprocessor::run(const QStringList &lines)
{
    std::shared_ptr<Markdown> markdown = this->markdown.lock();

    QStringList buffer = lines;
    QStringList new_text;
    while ( buffer.size() > 0 ) {
        QString line = buffer.front();
        buffer.pop_front();
        QRegularExpressionMatch m = this->RE.match(line);
        if ( m.hasMatch() ) {
            QString id = m.captured(1).trimmed().toLower();
            QString link = m.captured(2);
            link = pypp::lstrip(link, [](const QChar &ch) -> bool { return ch == '<'; });
            link = pypp::rstrip(link, [](const QChar &ch) -> bool { return ch == '>'; });
            QString t;
            for ( int i = 5; i <= 7; ++i ) {
                t = m.captured(i);
                if ( t.size() > 0 ) {
                    break;
                }
            }
            if ( t.isEmpty() ) {
                //! Check next line for title
                QRegularExpressionMatch tm = this->TITLE_RE.match(buffer.front());
                if ( tm.hasMatch() ) {
                    buffer.pop_front();
                    for ( int i = 2; i <= 4; ++i ) {
                        t = tm.captured(i);
                        if ( t.size() > 0 ) {
                            break;
                        }
                    }
                }
            }
            markdown->references[id] = Markdown::ReferenceItem(link, t);
        } else {
            new_text.push_back(line);
        }
    }
    return new_text;
}

} // namespace markdown
