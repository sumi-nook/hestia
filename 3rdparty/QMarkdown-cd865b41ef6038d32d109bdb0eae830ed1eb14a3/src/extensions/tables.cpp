/*
 * tables.cpp
 *
 *  Created on: 2013/11/04
 *      Author: mugwort_rc
 */

#include "extensions/tables.h"

#include <QString>
#include <QStringList>

#include "Markdown.h"
#include "BlockParser.h"
#include "BlockProcessors.h"

#include "InlinePatterns/common.h"
#include "InlinePatterns/BacktickPattern.h"

namespace markdown{

/*!
 * Process Tables.
 */
class TableProcessor : public BlockProcessor
{
public:
    TableProcessor(const std::weak_ptr<BlockParser> &parser) :
        BlockProcessor(parser),
        CHECK_CHARS({'|', ':', '-'})
    {}

    bool test(const Element &, const QString &block)
    {
        QStringList rows = block.split("\n");
        return rows.size() > 1
                && rows[0].contains('|')
                && rows[1].contains('|')
                && rows[1].contains('-')
                && this->CHECK_CHARS.contains(rows[1].trimmed().at(0));
    }

    /*!
     * Parse a table block and build table.
     */
    bool run(const Element &parent, QStringList &blocks)
    {
        QString blocksTmp = blocks.front();
        blocks.pop_front();
        QStringList block = blocksTmp.split("\n");
        QString header = block[0].trimmed();
        QString separator = block[1].trimmed();
        QStringList rows;
        if ( block.size() >= 3 ) {
            rows = block.mid(2);
        }
        //! Get format type (bordered by pipes or not)
        bool border = false;
        if ( header.startsWith('|') ) {
            border = true;
        }
        //! Get alignment of columns
        QList<boost::optional<QString>> align;
        for ( const QString &c : this->split_row(separator, border) ) {
            if ( c.startsWith(':') && c.endsWith(':') ) {
                align.push_back(QString("center"));
            } else if ( c.startsWith(':') ) {
                align.push_back(QString("left"));
            } else if ( c.endsWith(':') ) {
                align.push_back(QString("right"));
            } else {
                align.push_back(boost::none);
            }
        }
        //! Build table
        Element table = createSubElement(parent, "table");
        Element thead = createSubElement(table, "thead");
        this->build_row(header, thead, align, border);
        Element tbody = createSubElement(table, "tbody");
        for ( const QString &row : rows ) {
            this->build_row(row.trimmed(), tbody, align, border);
        }
        return true;
    }

private:
    /*!
     * Given a row of text, build table cells.
     */
    void build_row(const QString &row, const Element &parent, const QList<boost::optional<QString>> &align, bool border)
    {
        Element tr = createSubElement(parent, "tr");
        QString tag = "td";
        if ( parent->tag == "thead" ) {
            tag = "th";
        }
        QStringList cells = this->split_row(row, border);
        //! We use align here rather than cells to ensure every row
        //! contains the same number of columns.
        for ( int i = 0; i < align.size(); ++i ) {
            boost::optional<QString> a = align.at(i);
            Element c = createSubElement(tr, tag);
            if ( cells.size() > i ) {
                QString cell = cells.at(i).trimmed();
                c->text = cell;
            } else {
                c->text = QString();
            }
            if ( a ) {
                c->set("align", *a);
            }
        }
    }
    /*!
     * split a row of text into list of cells.
     */
    QStringList split_row(const QString &row, bool border)
    {
        QString tmp = row;
        if ( border ) {
            if ( tmp.startsWith('|') ) {
                tmp = tmp.mid(1);
            }
            if ( tmp.endsWith('|') ) {
                tmp = tmp.left(tmp.size()-1);
            }
        }
        return this->split(tmp, '|');
    }

    /*!
     * split a row of text with some code into a list of cells.
     */
    QStringList split(const QString &row, const QChar &marker)
    {
        if ( this->row_has_unpaired_backticks(row) ) {
            //! fallback on old behaviour
            return row.split(marker);
        }
        //! modify the backtick pattern to only match at the beginning of the search string
        std::shared_ptr<Pattern> backtick_pattern = std::shared_ptr<Pattern>(new BacktickPattern("^" + BACKTICK_RE));
        QStringList elements;
        QString current;
        for ( int i = 0; i < row.size(); ) {
            QChar letter = row.at(i);
            if ( letter == marker ) {
                if ( ! current.isEmpty() || elements.size() == 0 ) {
                    //! Don't append empty string unless it is the first element
                    //! The border is already removed when we get the row, then the line is strip()'d
                    //! If the first element is a marker, then we have an empty first cell
                    elements.append(current);
                }
                current.clear();
            } else {
                QRegularExpressionMatch match = backtick_pattern->getCompiledRegExp().match(row.mid(i));
                if ( ! match.hasMatch() ) {
                    current += letter;
                } else {
                    QString delim = match.captured(2);  //! the code block delimeter (ie 1 or more backticks)
                    QString row_contents = match.captured(3);  //! the text contained inside the code block
                    i += match.capturedStart(4) - 1;  //! jump pointer to the beginning of the rest of the text (group #4)
                    current += delim + row_contents + delim;  //! reinstert backticks
                }
            }
            ++i;
        }
        elements.append(current);
        return elements;
    }

    bool row_has_unpaired_backticks(const QString &row)
    {
        int count_total_backtick = row.count('`');
        int count_escaped_backtick = row.count("\\`");
        int count_backtick = count_total_backtick - count_escaped_backtick;
        //! odd number of backticks,
        //! we won't be able to build correct code blocks
        return bool(count_backtick & 1);
    }

private:
    QSet<QChar> CHECK_CHARS;

};

TableExtension::TableExtension() :
    Extension()
{}

void TableExtension::extendMarkdown(const std::shared_ptr<Markdown> &md/*, md_globals*/)
{
    md->parser->blockprocessors.add("table", std::shared_ptr<BlockProcessor>(new TableProcessor(md->parser)), "<hashheader");
}

Extension::Ptr TableExtension::generate(void)
{
    return std::shared_ptr<Extension>(new TableExtension);
}

} // end of namespace markdown
