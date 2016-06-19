#include "extensions/attr_list.h"

#include "pypp/str.hpp"

#include "Markdown.h"
#include "TreeProcessors.h"
#include "util.h"

namespace markdown{

QPair<QString, QString> handle_double_quote(const QString &t)
{
    QStringList tmp = t.split("=");
    return qMakePair(tmp[0], pypp::strip(tmp[1], "\""));
}

QPair<QString, QString> handle_single_quote(const QString &t)
{
    QStringList tmp = t.split("=");
    return qMakePair(tmp[0], pypp::strip(tmp[1], "'"));
}

QPair<QString, QString> handle_key_value(const QString &t)
{
    QStringList tmp = t.split("=");
    return qMakePair(tmp[0], tmp[1]);
}

QPair<QString, QString> handle_word(const QString &t)
{
    if ( t.startsWith(".") ) {
        return qMakePair(QString("."), t.mid(1));
    }
    if ( t.startsWith("#") ) {
        return qMakePair(QString("id"), t.mid(1));
    }
    return qMakePair(t, t);
}

QList<QRegularExpression> SCAN_PATTERNS = {
    QRegularExpression("[^ ]+=\".*?\""),
    QRegularExpression("[^ ]+='.*?'"),
    QRegularExpression("[^ ]+=[^ =]+"),
    QRegularExpression("[^ =]+"),
    QRegularExpression(" "),
};

/*!
 * Parse attribute list and return a list of attribute tuples.
 */
QList<QPair<QString, QString>> get_attrs(const QString &str)
{
    QList<QPair<QString, QString>> result;
    int i = 0;
    while ( true ) {
        int i_re;
        QRegularExpressionMatch match;
        for ( i_re = 0; i_re < SCAN_PATTERNS.size(); ++i_re ) {
            QRegularExpression re = SCAN_PATTERNS[i_re];
            match = re.match(str.mid(i));
            if ( match.hasMatch() && match.capturedStart() == 0 ) {
                break;
            }
        }
        if ( ! match.hasMatch() ) {
            break;
        }
        int j = i + match.capturedEnd();
        if ( i == j ) {
            break;
        }
        switch ( i_re ) {
        case 0:
            result.append(handle_double_quote(match.captured()));
            break;
        case 1:
            result.append(handle_single_quote(match.captured()));
            break;
        case 2:
            result.append(handle_key_value(match.captured()));
            break;
        case 3:
            result.append(handle_word(match.captured()));
            break;
        default:
            break;
        };
        i = j;
    }
    return result;
}

QSet<QString> HEADERS = {"h1", "h2", "h3", "h4", "h5", "h6"};
QSet<QString> LISTS = {"ul", "ol"};

bool isheader(const Element &elem)
{
    return HEADERS.contains(elem->tag);
}

class AttrListTreeprocessor : public TreeProcessor
{
public:
    AttrListTreeprocessor(const std::weak_ptr<Markdown> &md_instance) :
        TreeProcessor(md_instance),
        BASE_RE("\\{\\:?([^\\}]*)\\}"),
        HEADER_RE(QString("[ ]+%1[ ]*$").arg(this->BASE_RE)),
        BLOCK_RE(QString("\\n[ ]*%1[ ]*$").arg(this->BASE_RE)),
        INLINE_RE(QString("^%1").arg(this->BASE_RE)),
        NAME_RE("[^A-Z_a-z\u00c0-\u00d6\u00d8-\u00f6\u00f8-\u02ff"
                "\u0370-\u037d\u037f-\u1fff\u200c-\u200d"
                "\u2070-\u218f\u2c00-\u2fef\u3001-\ud7ff"
                "\uf900-\ufdcf\ufdf0-\ufffd"
                "\\:\\-\\.0-9\u00b7\u0300-\u036f\u203f-\u2040]+")
    {}

    Element run(const Element &doc)
    {
        for ( const Element &elem : doc->iter() ) {
            if ( util::isBlockLevel(elem->tag) ) {
                //! Block level: check for attrs on last line of text
                QRegularExpression RE = this->BLOCK_RE;
                if ( isheader(elem) || elem->tag == "dt" ) {
                    //! header or def-term: check for attrs at end of line
                    RE = this->HEADER_RE;
                }
                if ( elem->size() > 0 && elem->tag == "li" ) {
                    //! special case list items. children may include a ul or ol.
                    int pos = -1;
                    //! find the ul or ol position
                    for ( int i = 0; i < elem->size(); ++i ) {
                        Element child = (*elem)[i];
                        if ( LISTS.contains(child->tag) ) {
                            pos = i;
                        }
                    }
                    if ( pos == -1 && (*elem)[-1]->hasTail() ) {
                        //! use tail of last child. no ul or ol.
                        QRegularExpressionMatch m = RE.match((*elem)[-1]->tail);
                        if ( m.hasMatch() ) {
                            this->assign_attrs(elem, m.captured(1));
                            (*elem)[-1]->tail = (*elem)[-1]->tail.left(m.capturedStart());
                        }
                    } else if ( pos != -1 && pos > 0 && (*elem)[pos-1]->hasTail() ) {
                        //! use tail of last child before ul or ol
                        QRegularExpressionMatch m = RE.match((*elem)[pos-1]->tail);
                        if ( m.hasMatch() ) {
                            this->assign_attrs(elem, m.captured(1));
                            (*elem)[pos-1]->tail = (*elem)[pos-1]->tail.left(m.capturedStart());
                        }
                    } else if ( elem->hasText() ) {
                        //! use text. ul is first child.
                        QRegularExpressionMatch m = RE.match(elem->text);
                        if ( m.hasMatch() ) {
                            this->assign_attrs(elem, m.captured(1));
                            elem->text = elem->text.left(m.capturedStart());
                        }
                    }
                } else if ( elem->size() > 0 && (*elem)[-1]->hasTail() ) {
                    //! has children. Get from tail of last child
                    QRegularExpressionMatch m = RE.match((*elem)[-1]->tail);
                    if ( m.hasMatch() ) {
                        this->assign_attrs(elem, m.captured(1));
                        (*elem)[-1]->tail = (*elem)[-1]->tail.left(m.capturedStart());
                        if ( isheader(elem) ) {
                            //! clean up trailing #s
                            (*elem)[-1]->tail = pypp::rstrip(pypp::rstrip((*elem)[-1]->tail, "#"));
                        }
                    }
                } else if ( elem->hasText() ) {
                    //! no children. Get from text.
                    QRegularExpressionMatch m = RE.match(elem->text);
                    if ( ! m.hasMatch() && elem->tag == "td" ) {
                        m = QRegularExpression(this->BASE_RE).match(elem->text);
                    }
                    if ( m.hasMatch() ) {
                        this->assign_attrs(elem, m.captured(1));
                        elem->text = elem->text.left(m.capturedStart());
                        if ( isheader(elem) ) {
                            //! clean up trailing #s
                            elem->text = pypp::rstrip(pypp::rstrip(elem->text, "#"));
                        }
                    }
                }
            } else {
                //! inline: check for attrs at start of tail
                if ( elem->hasTail() ) {
                    QRegularExpressionMatch m = this->INLINE_RE.match(elem->tail);
                    if ( m.hasMatch() ) {
                        this->assign_attrs(elem, m.captured(1));;
                        elem->tail = elem->tail.mid(m.capturedEnd());
                    }
                }
            }
        }
        return Element();
    }

    void assign_attrs(const Element &elem, const QString &attrs)
    {
        for ( const QPair<QString, QString> &item : get_attrs(attrs) ) {
            QString k = item.first;
            QString v = item.second;
            if ( k == "." ) {
                //! add to class
                QString cls = elem->get("class");
                if ( ! cls.isEmpty() ) {
                    elem->set("class", QString("%1 %2").arg(cls, v));
                } else {
                    elem->set("class", v);
                }
            } else {
                //! assign attr k with v
                elem->set(this->sanitize_name(k), v);
            }
        }
    }

    /*!
     * Sanitize name as 'an XML Name, minus the ":"'.
     * See http://www.w3.org/TR/REC-xml-names/#NT-NCName
     */
    QString sanitize_name(const QString &name)
    {
        return pypp::re::sub(this->NAME_RE, "_", name);
    }

protected:
    QString BASE_RE;
    QRegularExpression HEADER_RE;
    QRegularExpression BLOCK_RE;
    QRegularExpression INLINE_RE;
    QRegularExpression NAME_RE;

};

AttrListExtension::AttrListExtension() :
    Extension()
{}

void AttrListExtension::extendMarkdown(const std::shared_ptr<Markdown> &md/*, md_globals*/)
{
    md->treeprocessors.add("attr_list", std::shared_ptr<TreeProcessor>(new AttrListTreeprocessor(md)), ">prettify");
}

Extension::Ptr AttrListExtension::generate(void)
{
    return std::shared_ptr<Extension>(new AttrListExtension);
}

} // end of namespace markdown
