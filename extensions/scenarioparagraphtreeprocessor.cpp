#include "scenarioparagraphtreeprocessor.h"

#include "QMarkdown/Markdown.h"
#include "QMarkdown/TreeProcessors.h"
#include "QMarkdown/ElementTree.hpp"

class ScenarioParagraphTreeprocessor : public markdown::TreeProcessor
{
public:
    ScenarioParagraphTreeprocessor(const std::weak_ptr<markdown::Markdown> &md_instance) :
        TreeProcessor(md_instance),
        NAME_RE(QString::fromUtf8(u8"^【([^】]+)】(.*)")),
        COMMENT_RE(QString::fromUtf8(u8"^※(.*)$"))
    {

    }

    markdown::Element run(const markdown::Element &root)
    {
        for ( const markdown::Element &elem : root->iter() ) {
            if ( elem->tag != "p" ) {
                continue;
            }
            if ( elem->text.isEmpty() ) {
                continue;
            }
            QString cls_type;
            QRegularExpressionMatch m = this->NAME_RE.match(elem->text);
            if ( m.hasMatch() ) {
                elem->text.clear();
                markdown::Element span = markdown::createElement("span");
                span->text = m.captured(1);
                span->tail = m.captured(2);
                span->set("class", "name");
                elem->insert(0, span);
                cls_type = "speech";
            } else if ( this->COMMENT_RE.match(elem->text).hasMatch() ) {
                elem->text = elem->text.mid(1);
                cls_type = "comment";
            } else {
                cls_type = "description";
            }
            QString cls = elem->get("class");
            if ( ! cls.isEmpty() ) {
                elem->set("class", QString("%1 %2").arg(cls).arg(cls_type));
            } else {
                elem->set("class", cls_type);
            }
            if ( ! elem->tail.trimmed().isEmpty() ) {
                markdown::Element span = markdown::createElement("span");
                span->text = elem->tail;
                span->set("class", "tail");
                elem->tail.clear();
                elem->insert(elem->size(), span);
            }
        }
        return markdown::Element();
    }

    QRegularExpression NAME_RE;
    QRegularExpression COMMENT_RE;

};



ScenarioParagraphExtension::ScenarioParagraphExtension()
{

}

void ScenarioParagraphExtension::extendMarkdown(const std::shared_ptr<markdown::Markdown> &md)
{
    md->treeprocessors.add("scenario_paragraph", std::shared_ptr<markdown::TreeProcessor>(new ScenarioParagraphTreeprocessor(md)), ">prettify");
}

markdown::Extension::Ptr ScenarioParagraphExtension::generate()
{
    return std::shared_ptr<markdown::Extension>(new ScenarioParagraphExtension);
}
