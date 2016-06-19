#include "extensions/nl2br.h"

#include "InlinePatterns.h"
#include "Markdown.h"

#include "InlinePatterns/SimpleTagPattern.h"

namespace markdown
{

void Nl2BrExtension::extendMarkdown(const std::shared_ptr<Markdown> &md)
{
    std::shared_ptr<Pattern> br_tag = std::make_shared<SubstituteTagPattern>("\\n", "br");
    md->inlinePatterns.add("nl", br_tag, "_end");
}

Extension::Ptr Nl2BrExtension::generate()
{
    return std::shared_ptr<Extension>(new Nl2BrExtension);
}

} // namespace markdown
