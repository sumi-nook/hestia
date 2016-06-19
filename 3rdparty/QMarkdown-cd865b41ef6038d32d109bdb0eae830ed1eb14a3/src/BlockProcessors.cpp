/*
 * BlockProcessors.cpp
 *
 *  Created on: 2013/10/27
 *      Author: mugwort_rc
 */

#include "BlockProcessors.h"

#include <QDebug>
#include <QRegularExpression>
#include <QSet>

#include <boost/algorithm/string.hpp>

#include "Markdown.h"
#include "BlockParser.h"

#include "BlockProcessors/EmptyBlockProcessor.h"
#include "BlockProcessors/ListIndentProcessor.h"
#include "BlockProcessors/CodeBlockProcessor.h"
#include "BlockProcessors/HashHeaderProcessor.h"
#include "BlockProcessors/SetextHeaderProcessor.h"
#include "BlockProcessors/HRProcessor.h"
#include "BlockProcessors/OListProcessor.h"
#include "BlockProcessors/BlockQuoteProcessor.h"
#include "BlockProcessors/ParagraphProcessor.h"

namespace markdown{

BlockProcessor::BlockProcessor(const std::weak_ptr<BlockParser> &parser) :
    parser(parser), tab_length(parser.lock()->markdown.lock()->tab_length())
{}

BlockProcessor::~BlockProcessor()
{}

Element BlockProcessor::lastChild(const Element &parent)
{
    if ( parent->size() > 0 ) {
        return (*parent)[-1];
    }
    return Element();
}

std::tuple<QString, QString> BlockProcessor::detab(const QString &text)
{
    QStringList newtext, lines = text.split(QRegularExpression("\n"));
    for ( const QString &line : lines ) {
        if ( line.startsWith(QString(this->tab_length, ' ')) ) {
            newtext.push_back(line.mid(this->tab_length));
        } else if ( line.trimmed().isEmpty() ) {
            newtext.push_back(QString());
		} else {
			break;
		}
	}
    QStringList resultLines;
    int counter = 0;
    for ( QStringList::const_iterator it = lines.begin(); it != lines.end(); ++it, ++counter ) {
		if ( counter < newtext.size() ) {
			continue;
		}
		resultLines.push_back(*it);
    }
    return std::make_tuple(newtext.join("\n"), resultLines.join("\n"));
}

QString BlockProcessor::looseDetab(const QString &text, unsigned int level)
{
	const unsigned int length = this->tab_length*level;
    QStringList lines = text.split(QRegularExpression("\n"));
    for ( int i = 0; i < lines.size(); ++i ) {
        if ( lines[i].startsWith(QString(length, ' ')) ) {
            lines[i] = lines[i].mid(length);
		}
	}
    return lines.join("\n");
}


std::shared_ptr<BlockParser> build_block_parser(const std::shared_ptr<Markdown> &md_instance)
{
    std::shared_ptr<BlockParser> parser(new BlockParser(md_instance));
    parser->blockprocessors.append("empty", std::shared_ptr<BlockProcessor>(new EmptyBlockProcessor(parser)));
    parser->blockprocessors.append("indent", std::shared_ptr<BlockProcessor>(new ListIndentProcessor(parser)));
    parser->blockprocessors.append("code", std::shared_ptr<BlockProcessor>(new CodeBlockProcessor(parser)));
    parser->blockprocessors.append("hashheader", std::shared_ptr<BlockProcessor>(new HashHeaderProcessor(parser)));
    parser->blockprocessors.append("setextheader", std::shared_ptr<BlockProcessor>(new SetextHeaderProcessor(parser)));
    parser->blockprocessors.append("hr", std::shared_ptr<BlockProcessor>(new HRProcessor(parser)));
    parser->blockprocessors.append("olist", std::shared_ptr<BlockProcessor>(new OListProcessor(parser)));
    parser->blockprocessors.append("ulist", std::shared_ptr<BlockProcessor>(new UListProcessor(parser)));
    parser->blockprocessors.append("quote", std::shared_ptr<BlockProcessor>(new BlockQuoteProcessor(parser)));
    parser->blockprocessors.append("paragraph", std::shared_ptr<BlockProcessor>(new ParagraphProcessor(parser)));
	return parser;
}

} // end of namespace markdown
