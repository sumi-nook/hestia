#ifndef HTMLBLOCKPROCESSOR_H
#define HTMLBLOCKPROCESSOR_H

#include "PreProcessors.h"

namespace markdown
{

/*!
 * Remove html blocks from the text and store them for later retrieval.
 */
class HtmlBlockProcessor : public PreProcessor
{
public:
    typedef QMap<QString, QString> Attributes;

public:
    HtmlBlockProcessor(const std::weak_ptr<Markdown> &markdown_instance);
    virtual ~HtmlBlockProcessor(void);

    QStringList run(const QStringList &lines);

private:
    std::tuple<QString, int, Attributes> get_left_tag(const QString &block);
    int recursive_tagfind(const QString &ltag, const QString &rtag, int start_index, const QString &block);
    std::tuple<QString, int> get_right_tag(const QString &left_tag, int left_index, const QString &block);
    bool equal_tags(const QString &left_tag, const QString &right_tag);
    bool is_oneliner(const QString &tag);

private:
    QStringList        right_tag_patterns;
    QString            attrs_pattern;
    QString            left_tag_pattern;
    QRegularExpression attrs_re;
    QRegularExpression left_tag_re;
    bool               markdown_in_raw;

};

} // namespace markdown

#endif // HTMLBLOCKPROCESSOR_H
