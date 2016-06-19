/*
 * util.h
 *
 *  Created on: 2013/10/25
 *      Author: mugwort_rc
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <QList>
#include <QPair>
#include <QString>

namespace markdown{

class util
{
public:

static const QRegularExpression BLOCK_LEVEL_ELEMENTS;

//! Placeholders
static const QString STX;  //!< Use STX ("Start of text") for start-of-placeholder
static const QString ETX;  //!< Use ETX ("End of text") for end-of-placeholder
static const QString INLINE_PLACEHOLDER_PREFIX;
static const QString INLINE_PLACEHOLDER;
static const QRegularExpression INLINE_PLACEHOLDER_RE;
static const QString AMP_SUBSTITUTE;

static bool isBlockLevel(const QString &tag);

private:
	util(void);
    util(const util &);
	~util(void);
    util &operator=(const util &);

};

class HtmlStash
{
public:
    typedef QPair<QString, bool> Item;
    typedef QList<Item> Items;

public:
	HtmlStash(void);

    QString store(const QString &html, bool safe=false);
	void reset(void);

    QString get_placeholder(int key);

public:
    int   html_counter;
    Items rawHtmlBlocks;

};

} // end of namespace markdown

#endif /* UTIL_H_ */
