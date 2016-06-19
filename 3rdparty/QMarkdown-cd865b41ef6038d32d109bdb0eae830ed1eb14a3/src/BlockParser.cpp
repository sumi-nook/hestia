/*
 * BlockParser.cpp
 *
 *  Created on: 2013/10/27
 *      Author: mugwort_rc
 */

#include "BlockParser.h"

#include "Markdown.h"

namespace markdown{

BlockParser::BlockParser(const std::weak_ptr<Markdown> &markdown) :
	markdown(markdown),
    blockprocessors(), root()
{}

ElementTree BlockParser::parseDocument(const QStringList &lines)
{
    std::shared_ptr<Markdown> markdown = this->markdown.lock();

    this->root = ElementTree(createElement(markdown->doc_tag()));
    Element tmp = this->root.getroot();
    this->parseChunk(tmp, lines.join("\n"));
	return this->root;
}

void BlockParser::parseChunk(const Element &parent, const QString &text)
{
    QStringList buffer = text.split(QRegularExpression("\n\n"));
	this->parseBlocks(parent, buffer);
}

void BlockParser::parseBlocks(const Element &parent, QStringList &blocks)
{
	while ( blocks.size() > 0 ) {
        for (OrderedDictBlockProcessors::ValueType processor : this->blockprocessors.toList()) {
            if ( processor->test(parent, blocks.front()) ) {
                if ( processor->run(parent, blocks) ) {
                    //! run returns True
                    break;
                }
			}
		}
	}
}

} // end of namespace markdown
