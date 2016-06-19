#ifndef RAWHTMLPOSTPROCESSOR_H
#define RAWHTMLPOSTPROCESSOR_H

#include "../PostProcessors.h"

namespace markdown
{

/*!
 * Restore raw html to the document.
 */
class RawHtmlPostprocessor : public PostProcessor
{
public:
    using PostProcessor::PostProcessor;

    /*!
     * Iterate over html stash and restore "safe" html.
     */
    QString run(const QString &text);

    /*!
     * Basic html escaping
     */
    QString escape(const QString &html);

    bool isblocklevel(const QString &html);

private:
    static const QSet<QChar> SPECIAL_CHARS;

};

} // namespace markdown

#endif // RAWHTMLPOSTPROCESSOR_H
