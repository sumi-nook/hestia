#include "PreProcessors/NormalizeWhitespace.h"

#include "util.h"
#include "Markdown.h"

namespace markdown
{

NormalizeWhitespace::~NormalizeWhitespace(void)
{}

QStringList NormalizeWhitespace::run(const QStringList &lines)
{
    std::shared_ptr<Markdown> markdown = this->markdown.lock();

    QString source = lines.join("\n");
    source = source.replace(util::STX, QString());
    source = source.replace(util::ETX, QString());
    source = source.replace("\r\n", "\n");
    source = source.replace("\r", "\n");
    source += "\n\n";
    source = pypp::expandtabs(source, markdown->tab_length());
    source = source.replace(QRegularExpression("(?<=\n) +\n"), "\n");
    return source.split("\n");
}

} // namespace markdown
