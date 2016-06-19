/*
 * Serializers.cpp
 *
 *  Created on: 2013/10/28
 *      Author: mugwort_rc
 */

#include "Serializers.h"

#include <functional>
#include <tuple>
#include <utility>

#include <boost/range/algorithm.hpp>

#include <QPair>
#include <QSet>

namespace markdown{

typedef enum {
    html,
    xhtml
} Format;

typedef QMap<QString, QString> NamespaceMap;

static const QSet<QString> HTML_EMPTY = {"area", "base", "basefont", "br", "col", "frame", "hr",
                                         "img", "input", "isindex", "link", "meta", "param"};

static const NamespaceMap namespace_map = {
    // "well-known" namespace prefixes
    std::make_pair("http://www.w3.org/XML/1998/namespace", "xml"),
    std::make_pair("http://www.w3.org/1999/xhtml", "html"),
    std::make_pair("http://www.w3.org/1999/02/22-rdf-syntax-ns#", "rdf"),
    std::make_pair("http://schemas.xmlsoap.org/wsdl/", "wsdl"),
    // xml schema
    std::make_pair("http://www.w3.org/2001/XMLSchema", "xs"),
    std::make_pair("http://www.w3.org/2001/XMLSchema-instance", "xsi"),
    // dublic core
    std::make_pair("http://purl.org/dc/elements/1.1/", "dc")
};

QString escape_cdata(const QString &text)
{
    //! escape character data
    QString result = text;

    //! it's worth avoiding do-nothing calls for strings that are
    //! shorter than 500 character, or so.  assume that's, by far,
    //! the most common case in most applications.
    if ( result.contains('&') ) {
        result = result.replace("&", "&amp;");
    }
    if ( result.contains('<') ) {
        result = result.replace("<", "&lt;");
    }
    if ( result.contains('>') ) {
        result = result.replace(">", "&gt;");
    }
    return result;
}

QString escape_attrib(const QString &text)
{
    //! escape attribute value
    QString result = text;
    if ( result.contains('&') ) {
        result = result.replace("&", "&amp;");
    }
    if ( result.contains('<') ) {
        result = result.replace("<", "&lt;");
    }
    if ( result.contains('>') ) {
        result = result.replace(">", "&gt;");
    }
    if ( result.contains('"') ) {
        result = result.replace("\"", "&quot;");
    }
    if ( result.contains('\n') ) {
        result = result.replace("\n", "&#10;");
    }
    return result;
}

QString escape_attrib_html(const QString &text)
{
    //! escape attribute value
    QString result = text;
    if ( result.contains('&') ) {
        result = result.replace("&", "&amp;");
    }
    if ( result.contains('<') ) {
        result = result.replace("<", "&lt;");
    }
    if ( result.contains('>') ) {
        result = result.replace(">", "&gt;");
    }
    if ( result.contains('"') ) {
        result = result.replace("\"", "&quot;");
    }
    return result;
}

void serialize_html(const std::function<void(const QString &)> &write, const Element &elem, const NamespaceMap &qnames, const NamespaceMap &namespaces, Format format)
{
    /*
    if ( elem->getNodeType() == xercesc::DOMNode::COMMENT_NODE ) {
        xercesc::DOMComment* comment = reinterpret_cast<xercesc::DOMComment*>(elem);
        write((boost::wformat(L"<!--%s-->")%escape_cdata(wconvert(comment->getData()))).str());
    } else if ( elem->getNodeType() == xercesc::DOMNode::PROCESSING_INSTRUCTION_NODE ) {
        xercesc::DOMProcessingInstruction* pi = reinterpret_cast<xercesc::DOMProcessingInstruction*>(elem);
        write((boost::wformat(L"<?%s %s?>")%escape_cdata(wconvert(pi->getTarget()))%escape_cdata(wconvert(pi->getData()))).str());
    } else */{
        QString tag = elem->tag;
        write("<"+tag);
        QStringList keys = elem->keys();
        if ( keys.size() > 0 ) {
            qSort(keys);  //!< lexical order
            for ( const QString &key : keys ) {
                const QString value = escape_attrib_html(elem->get(key));
                if ( format == html && qnames.contains(key) && qnames[key] == value ) {
                    //! handle boolean attributes
                    write(QString(" %1").arg(value));
                } else if ( qnames.contains(key) ) {
                    write(QString(" %1=\"%2\"").arg(qnames[key]).arg(value));
                }
            }
            if ( ! namespaces.isEmpty() ) {
                typedef QPair<QString, QString> Pair;
                typedef QList<Pair> Pairs;
                Pairs ns_list;
                for ( NamespaceMap::const_iterator it = namespaces.begin(); it != namespaces.end(); ++it ) {
                    ns_list.push_back(Pair(it.key(), it.value()));
                }
                auto ns_list_ = ns_list.toStdList();
                ns_list_.sort([](const Pair &a, const Pair &b) -> bool { return a.second < b.second; });  //!< sort on prefix
                for ( const Pair &pair : ns_list_ ) {
                    QString key = pair.first;
                    if ( ! key.isEmpty() ) {
                        key = ":"+key;
                    }
                    write(QString(" xmlns%1=\"%2\"").arg(key).arg(escape_attrib(pair.second)));
                }
            }
        }
        if ( format == xhtml && HTML_EMPTY.contains(tag) ) {
            write(" />");
        } else {
            write(">");
            tag = tag.toLower();
            if ( elem->hasText() ) {
                if ( tag == "script" || tag == "style" ) {
                    write(elem->text);
                } else {
                    write(escape_cdata(elem->text));
                }
            }
            for ( int i = 0; i < elem->size(); ++i ) {
                serialize_html(write, (*elem)[i], qnames, NamespaceMap(), format);
            }
            if ( ! HTML_EMPTY.contains(tag) ) {
                write(QString("</%1>").arg(tag));
            }
        }
    }
    if ( elem->hasTail() ) {
        write(escape_cdata(elem->tail));
    }
}

std::tuple<NamespaceMap, NamespaceMap> namespaces(const Element &elem, const QString &default_namespace=QString())
{
    //! identify namespaces used in this tree

    //! maps qnames to *encoded* prefix:local names
    NamespaceMap qnames;

    //! maps uri:s to prefixes
    NamespaceMap nss;
    if ( ! default_namespace.isEmpty() ) {
        nss[default_namespace] = QString();
    }

    auto add_qname = [&](const QString &qname){
        //! calculate serialized qname representation
        if ( qname.startsWith('{') ) {
            QStringList temp = qname.mid(1).split("}");
            QString uri = temp.at(0), tag = temp.at(1);
            QString prefix;
            if ( ! nss.contains(uri) ) {
                if ( ! namespace_map.contains(uri) ) {
                    prefix = QString("ns%1").arg(nss.size());
                }
                if ( prefix != "xml" ) {
                    nss[uri] = prefix;
                }
            }
            if ( ! prefix.isEmpty() ) {
                qnames[qname] = QString("%1:%2").arg(prefix).arg(tag);
            } else {
                qnames[qname] = tag;  //!< default element
            }
        } else {
            if ( ! default_namespace.isEmpty() ) {
                throw std::invalid_argument("cannot use non-qualified names with default_namespace option");
            }
            qnames[qname] = qname;
        }
    };

    //! populate qname and namespaces table
    for ( Element &node : elem->iter() ) {
        QString nsURI = QString(); // node.getNamespaceURI();
        QString tag   = node->tag;
        if ( ! nsURI.isEmpty() ) {
            tag = QString("{%1}%2").arg(nsURI).arg(tag);
        }
        if ( qnames.contains(tag) ) {
            add_qname(tag);
        }
        for ( const QString &key : node->keys() ) {
            if ( ! qnames.contains(key) ) {
                add_qname(key);
            }
        }
    }
    return std::make_tuple(qnames, nss);
}

QString write_html(const Element &root, const Format &format)
{
    if ( ! root ) {
        return QString();
    }
    QStringList data;
    NamespaceMap qnames, namespaces_map;
    std::tie(qnames, namespaces_map) = namespaces(root);
    serialize_html([&](const QString &text){ data.push_back(text); }, root, qnames, namespaces_map, format);
    return data.join(QString());
}

QString to_html_string(const Element &element)
{
    return write_html(element, html);
}

QString to_xhtml_string(const Element &element)
{
    return write_html(element, xhtml);
}

} // end of namespace markdown
