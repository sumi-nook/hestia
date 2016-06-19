/*
 * util.cpp
 *
 *  Created on: 2013/10/25
 *      Author: mugwort_rc
 */
#include "util.h"

#include <QRegularExpression>
#include <QString>

namespace markdown{

const QRegularExpression util::BLOCK_LEVEL_ELEMENTS("^(p|div|h[1-6]|blockquote|pre|table|dl|ol|ul"
                                                    "|script|noscript|form|fieldset|iframe|math"
                                                    "|hr|hr/|style|li|dt|dd|thead|tbody"
                                                    "|tr|th|td|section|footer|header|group|figure"
                                                    "|figcaption|aside|article|canvas|output"
                                                    "|progress|video)$", QRegularExpression::CaseInsensitiveOption);

const QString util::STX = QString(1, QChar(2));
const QString util::ETX = QString(1, QChar(3));
const QString util::INLINE_PLACEHOLDER_PREFIX = util::STX+"klzzwxh:";
const QString util::INLINE_PLACEHOLDER = util::INLINE_PLACEHOLDER_PREFIX + "%1" + util::ETX;
const QRegularExpression util::INLINE_PLACEHOLDER_RE(util::INLINE_PLACEHOLDER.arg("([0-9]{4})"));
const QString util::AMP_SUBSTITUTE = util::STX+"amp"+util::ETX;

bool util::isBlockLevel(const QString &tag)
{
    return util::BLOCK_LEVEL_ELEMENTS.match(tag).hasMatch();
}

HtmlStash::HtmlStash() :
    html_counter(0), rawHtmlBlocks()
{}

QString HtmlStash::store(const QString &html, bool safe)
{
    this->rawHtmlBlocks.push_back(Item(html, safe));
    QString placeholder = this->get_placeholder(this->html_counter);
    this->html_counter += 1;
	return placeholder;
}

void HtmlStash::reset(void)
{
    this->html_counter = 0;
    this->rawHtmlBlocks = Items();
}

QString HtmlStash::get_placeholder(int key)
{
    return QString("%1wzxhzdk:%2%3").arg(util::STX).arg(key).arg(util::ETX);
}

} // end of namespace markdown
