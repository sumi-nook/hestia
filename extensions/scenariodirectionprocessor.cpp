#include "scenariodirectionprocessor.h"

#include <QDebug>

#include "QMarkdown/Markdown.h"
#include "QMarkdown/BlockParser.h"
#include "QMarkdown/BlockProcessors.h"
#include "QMarkdown/ElementTree.hpp"


class ScenarioDirectionProcessor : public markdown::BlockProcessor
{
public:
    ScenarioDirectionProcessor(const std::weak_ptr<markdown::BlockParser> &parser) :
        markdown::BlockProcessor(parser),
        RE(QString::fromUtf8(u8"(^|\\n)※(.+?)(\\n|$)")),
        BGIMG_RE(QString::fromUtf8(u8"背景[:：]([^:：]+)(?:[:：](.+))?"))
    {

    }

    bool test(const markdown::Element &, const QString &block)
    {
        return this->RE.match(block).hasMatch();
    }

    bool run(const markdown::Element &parent, QStringList &blocks)
    {
        QString block = blocks.first();
        blocks.pop_front();

        QRegularExpressionMatch m = this->RE.match(block);
        if ( m.hasMatch() ) {
            QString before = block.left(m.capturedStart());  // All lines before direction
            QString after = block.mid(m.capturedEnd());  // All lines after direction
            if ( ! before.isEmpty() ) {
                // As the direction was not the first line of the block and the
                // lines before the direction must be parsed first,
                // recursively parse this lines as a block.
                std::shared_ptr<markdown::BlockParser> parser = this->parser.lock();
                QStringList new_blocks = {before};
                parser->parseBlocks(parent, new_blocks);
            }
            // Create direction
            QString body = m.captured(2);
            // background-image
            m = this->BGIMG_RE.match(body);
            if ( m.hasMatch() ) {
                markdown::Element img = markdown::createSubElement(parent, "img");
                img->attrib["class"] = "background";
                img->attrib["src"] = m.captured(1);
                img->attrib["alt"] = m.captured(2);
            }
            // TODO: other direction
            if ( ! m.hasMatch() ) {
                markdown::Element p = markdown::createSubElement(parent, "p");
                p->attrib["class"] = "comment";
                p->text = body;
            }
            if ( ! after.isEmpty() ) {
                // Insert remaining lines as first block for future parsing.
                blocks.insert(0, after);
            }
            return true;
        } else {
            // This should never happen, but just in case...
            qDebug() << "We've got a problem header: " << block;
            return false;
        }
    }

    QRegularExpression RE;
    QRegularExpression BGIMG_RE;

};


ScenarioDirectionExtension::ScenarioDirectionExtension()
{

}

void ScenarioDirectionExtension::extendMarkdown(const std::shared_ptr<markdown::Markdown> &md)
{
    md->parser->blockprocessors.add("scenario_direction", std::shared_ptr<markdown::BlockProcessor>(new ScenarioDirectionProcessor(md->parser)), "<paragraph");
}

markdown::Extension::Ptr ScenarioDirectionExtension::generate()
{
    return std::shared_ptr<markdown::Extension>(new ScenarioDirectionExtension);
}
