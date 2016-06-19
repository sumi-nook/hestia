#include "wordlink.h"

#include "QMarkdown/Markdown.h"
#include "QMarkdown/InlinePatterns.h"

#include "QMarkdown/InlinePatterns/AutolinkPattern.h"

WordLinkExtension::WordLinkExtension()
{

}

void WordLinkExtension::extendMarkdown(const std::shared_ptr<markdown::Markdown> &md)
{
    md->inlinePatterns.add("wordlink", std::make_shared<markdown::AutolinkPattern>("<(?:word:)([^>]*)>", md), ">autolink");
}

markdown::Extension::Ptr WordLinkExtension::generate()
{
    return std::shared_ptr<markdown::Extension>(new WordLinkExtension);
}
