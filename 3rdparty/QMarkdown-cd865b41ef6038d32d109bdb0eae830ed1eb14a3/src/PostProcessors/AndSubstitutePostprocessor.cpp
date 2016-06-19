#include "PostProcessors/AndSubstitutePostprocessor.h"

#include "util.h"

namespace markdown
{

AndSubstitutePostprocessor::AndSubstitutePostprocessor(const std::weak_ptr<Markdown> &markdown_instance) :
    PostProcessor(markdown_instance)
{}

QString AndSubstitutePostprocessor::run(const QString &text)
{
    return QString(text).replace(util::AMP_SUBSTITUTE, "&");
}

} // namespace markdown
