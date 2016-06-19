#ifndef REFERENCEPREPROCESSOR_H
#define REFERENCEPREPROCESSOR_H

#include "PreProcessors.h"

namespace markdown
{

/*!
 * Remove reference definitions from text and store for later use.
 */
class ReferencePreprocessor : public PreProcessor
{
public:
    ReferencePreprocessor(const std::weak_ptr<Markdown> &markdown_instance);

    QStringList run(const QStringList &lines);

private:
    const QString TITLE;
    const QRegularExpression RE;
    const QRegularExpression TITLE_RE;

};

} // namespace markdown

#endif // REFERENCEPREPROCESSOR_H
