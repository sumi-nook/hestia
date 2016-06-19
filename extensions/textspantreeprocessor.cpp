#include "textspantreeprocessor.h"

#include "QMarkdown/Markdown.h"
#include "QMarkdown/TreeProcessors.h"
#include "QMarkdown/ElementTree.hpp"

class TextSpanTreeprocessor : public markdown::TreeProcessor
{
public:
    using markdown::TreeProcessor::TreeProcessor;

    markdown::Element run(const markdown::Element &root)
    {
        for ( const markdown::Element &elem : root->iter() ) {
            if ( elem->tag != "p" ) {
                continue;
            }
            if ( elem->get("class").contains("comment") ) {
                continue;
            }
            if ( ! elem->text.trimmed().isEmpty() ) {
                markdown::Element span = this->create_span();
                span->text = elem->text;
                elem->text.clear();
                elem->insert(0, span);
            }
            for ( int i = 0; i < elem->size(); ++i ) {
                markdown::Element child = (*elem)[i];
                if ( ! child->tail.trimmed().isEmpty() ) {
                    markdown::Element span = this->create_span();
                    span->text = child->tail;
                    child->tail.clear();
                    elem->insert(i+1, span);
                }
            }
        }
        return markdown::Element();
    }

    markdown::Element create_span()
    {
        markdown::Element span = markdown::createElement("span");
        span->set("class", "text");
        return span;
    }

};



TextSpanExtension::TextSpanExtension()
{

}

void TextSpanExtension::extendMarkdown(const std::shared_ptr<markdown::Markdown> &md)
{
    md->treeprocessors.add("text_span", std::shared_ptr<markdown::TreeProcessor>(new TextSpanTreeprocessor(md)), ">prettify");
}

markdown::Extension::Ptr TextSpanExtension::generate()
{
    return std::shared_ptr<markdown::Extension>(new TextSpanExtension);
}
