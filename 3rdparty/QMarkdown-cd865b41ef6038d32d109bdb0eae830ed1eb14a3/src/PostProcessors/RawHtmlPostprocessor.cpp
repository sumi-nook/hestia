#include "PostProcessors/RawHtmlPostprocessor.h"

#include "Markdown.h"
#include "util.h"

namespace markdown
{

QString RawHtmlPostprocessor::run(const QString &text)
{
    std::shared_ptr<Markdown> markdown = this->markdown.lock();

    OrderedDict<QString> replacements;
    for ( int i = 0; i < markdown->htmlStash.html_counter; ++i ) {
        HtmlStash::Item item = markdown->htmlStash.rawHtmlBlocks[i];
        QString html = item.first;
        bool safe = item.second;
        if ( markdown->safeMode() != Markdown::default_mode && ! safe ) {
            if ( markdown->safeMode() == Markdown::escape_mode ) {
                html = this->escape(html);
            } else if ( markdown->safeMode() == Markdown::remove_mode ) {
                html = QString();
            } else {
                html = markdown->html_replacement_text();
            }
        }
        if ( this->isblocklevel(html) && ( safe || ! markdown->safeMode() ) ) {
            replacements[QString("<p>%1</p>").arg(markdown->htmlStash.get_placeholder(i))] = html+"\n";
        }
        replacements[markdown->htmlStash.get_placeholder(i)] = html;
    }
    QString result = text;
    if ( replacements.size() > 0 ) {
        pypp::str pattern = pypp::map(pypp::re::escape, replacements.keys()).join("|");
        result = pypp::re::sub(QRegularExpression(pattern), [&](const QRegularExpressionMatch &m) -> pypp::str {
            return replacements[m.captured()];
        }, result);
    }
    return result;
}

QString RawHtmlPostprocessor::escape(const QString &html)
{
    QString result = html;
    result = result.replace("&", "&amp;");
    result = result.replace("<", "&lt;");
    result = result.replace(">", "&gt;");
    result = result.replace("\"", "&quot;");
    return result;
}

bool RawHtmlPostprocessor::isblocklevel(const QString &html)
{
    QRegularExpressionMatch m = QRegularExpression("^\\<\\/?([^ >]+)").match(html);
    if ( m.hasMatch() ) {
        QChar ch = m.captured(1).at(0);
        // SPECIAL_CHARS: !, ?, @, %
        if ( SPECIAL_CHARS.contains(ch) ) {
            //! Comment, php etc...
            return true;
        }
        return util::isBlockLevel(m.captured(1));
    }
    return false;
}

const QSet<QChar> RawHtmlPostprocessor::SPECIAL_CHARS = {'!', '?', '@', '%'};


} // namespace markdown
