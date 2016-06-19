#include "PostProcessors/UnescapePostprocessor.h"

#include "util.h"

namespace markdown
{

UnescapePostprocessor::UnescapePostprocessor(const std::weak_ptr<Markdown> &markdown_instance) :
    PostProcessor(markdown_instance),
    RE(QString("%1(\\d+)%2").arg(util::STX).arg(util::ETX))
{}

QString UnescapePostprocessor::run(const QString &text)
{
    auto unescape = [](const QRegularExpressionMatch &m) -> QString {
        int i = m.captured(1).toInt();
        return QString(QChar(i));
    };
    return pypp::re::sub(this->RE, unescape, text);
}

} // namespace markdown
