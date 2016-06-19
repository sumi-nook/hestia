#include "converter.h"

#include "QMarkdown/Markdown.h"
#include "QMarkdown/extensions/nl2br.h"

#include "extensions/ruby.h"
#include "extensions/scenariodirectionprocessor.h"
#include "extensions/scenarioparagraphtreeprocessor.h"
#include "extensions/textspantreeprocessor.h"
#include "extensions/wordlink.h"

QString toXHTML(const QString &text)
{
    std::shared_ptr<markdown::Markdown> md = markdown::create_Markdown({
        std::shared_ptr<markdown::Extension>(new RubyExtension),
        std::shared_ptr<markdown::Extension>(new TextSpanExtension),
        std::shared_ptr<markdown::Extension>(new ScenarioDirectionExtension),
        std::shared_ptr<markdown::Extension>(new ScenarioParagraphExtension),
        std::shared_ptr<markdown::Extension>(new WordLinkExtension),
        std::shared_ptr<markdown::Extension>(new markdown::Nl2BrExtension),
    });

    return QString("<div>%1</div>").arg(md->convert(text));
}
