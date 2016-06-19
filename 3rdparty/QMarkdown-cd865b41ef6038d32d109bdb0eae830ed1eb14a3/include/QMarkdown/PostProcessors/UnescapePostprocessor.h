#ifndef UNESCAPEPOSTPROCESSOR_H
#define UNESCAPEPOSTPROCESSOR_H

#include "../PostProcessors.h"

namespace markdown
{

/*!
 * Restore escaped chars
 */
class UnescapePostprocessor : public PostProcessor
{
public:
    UnescapePostprocessor(const std::weak_ptr<Markdown> &markdown_instance=std::weak_ptr<Markdown>());

    QString run(const QString &text);

private:
    QRegularExpression RE;

};

} // namespace markdown

#endif // UNESCAPEPOSTPROCESSOR_H
