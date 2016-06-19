#ifndef ANDSUBSTITUTEPOSTPROCESSOR_H
#define ANDSUBSTITUTEPOSTPROCESSOR_H

#include "../PostProcessors.h"

namespace markdown
{

/*!
 * Restore valid entities
 */
class AndSubstitutePostprocessor : public PostProcessor
{
public:
    AndSubstitutePostprocessor(const std::weak_ptr<Markdown> &markdown_instance=std::weak_ptr<Markdown>());

    QString run(const QString &text);

};

} // namespace markdown

#endif // ANDSUBSTITUTEPOSTPROCESSOR_H
