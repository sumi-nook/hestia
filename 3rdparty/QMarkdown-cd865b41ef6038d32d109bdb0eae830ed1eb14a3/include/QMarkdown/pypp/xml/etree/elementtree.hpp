#ifndef PYPP_ELEMENTTREE_HPP
#define PYPP_ELEMENTTREE_HPP

#include <functional>
#include <memory>

#include <QList>
#include <QMap>
#include <QPair>

#include "../../builtin.hpp"
#include "../../exceptions.hpp"
#include "../../str.hpp"

namespace pypp {

namespace xml {

namespace etree {

typedef QMap<pypp::str, pypp::str> Namespaces_t;
typedef QPair<pypp::str, pypp::str> Item_t;
typedef QList<Item_t> ItemList_t;

inline ItemList_t items(const Namespaces_t &ns)
{
    ItemList_t result;
    for ( const pypp::str &key : ns.keys() ) {
        result.append(qMakePair(key, ns[key]));
    }
    return result;
}

template <class Impl>
class SimpleElementPath
{
public:
    inline static typename Impl::ElementPtr find(const typename Impl::ElementPtr &element, const pypp::str &tag, const Namespaces_t &namespaces=Namespaces_t())
    {
        for ( const typename Impl::ElementPtr &elem : (*element) ) {
            if ( elem->tag == tag ) {
                return elem;
            }
        }
        return typename Impl::ElementPtr();
    }

    inline static pypp::str findtext(const typename Impl::ElementPtr &element, const pypp::str &tag, const pypp::str &default_, const Namespaces_t &namespaces=Namespaces_t())
    {
        typename Impl::ElementPtr elem = SimpleElementPath::find(element, tag);
        if ( ! elem ) {
            return default_;
        }
        return elem->text;
    }

    inline static typename Impl::ElementList_t iterfind(const typename Impl::ElementPtr &element, const pypp::str &tag, const Namespaces_t &namespaces=Namespaces_t())
    {
        typename Impl::ElementList_t result;
        if ( tag.startsWith(".//") ) {
            for ( const typename Impl::ElementPtr &elem : element->iter(tag.mid(3)) ) {
                result.append(elem);
            }
        }
        for ( const typename Impl::ElementPtr &elem : (*element) ) {
            if ( elem->tag == tag ) {
                result.append(elem);
            }
        }
        return result;
    }

    inline static typename Impl::ElementList_t findall(const typename Impl::ElementPtr &element, const pypp::str &tag, const Namespaces_t &namespaces=Namespaces_t())
    {
        return SimpleElementPath::iterfind(element, tag, namespaces);
    }

};


template <class Impl>
class ElementImpl : public std::enable_shared_from_this<Impl>
{
public:
    typedef std::shared_ptr<Impl> ElementPtr;
    typedef QMap<pypp::str, pypp::str> Attribute_t;
    typedef QList<ElementPtr> ElementList_t;

    typedef SimpleElementPath<Impl> ElementPath;

    /*!
      (Attribute) Element tag.
     */
    pypp::str tag;

    /*!
      (Attribute) Element attribute dictionary.  Where possible, use
      {@link #Element.get},
      {@link #Element.set},
      {@link #Element.keys}, and
      {@link #Element.items} to access
      element attributes.
     */
    Attribute_t attrib;

    /*!
      (Attribute) Text before first subelement.  This is either a
      string or the value None.  Note that if there was no text, this
      attribute may be either None or an empty string, depending on
      the parser.
     */
    pypp::str text;

    /*!
      (Attribute) Text after this element's end tag, but before the
      next sibling element's start tag.  This is either a string or
      the value None.  Note that if there was no text, this attribute
      may be either None or an empty string, depending on the parser.
     */
    pypp::str tail;

    /*!
      constructor
     */
    ElementImpl(const pypp::str &tag, const Attribute_t &attrib=Attribute_t()) :
        tag(tag),
        attrib(attrib),
        text(),
        tail(),
        _children()
    {}
    virtual ~ElementImpl()
    {}

    /*!
      Creates a new element object of the same type as this element.

      @param tag Element tag.
      @param attrib Element attributes, given as a dictionary.
      @return A new element instance.
     */
    static ElementPtr makeelement(const pypp::str &tag, const Attribute_t &attrib=Attribute_t())
    {
        return ElementPtr(new Impl(tag, attrib));
    }

    /*!
      (Experimental) Copies the current element.  This creates a
      shallow copy; subelements will be shared with the original tree.

      @return A new element instance.
     */
    virtual ElementPtr copy() const = 0;

    /*!
      Returns the number of subelements.  Note that this only counts
      full elements; to check if there's any content in an element, you
      have to check both the length and the <b>text</b> attribute.

      @return The number of subelements.
     */
    int size() const
    {
        return this->_children.size();
    }

    /*!
      Returns the given subelement, by index.

      @param index What subelement to return.
      @return The given subelement.
      @exception IndexError If the given element does not exist.
     */
    ElementPtr &operator [](int index)
    {
        return this->_children[this->normalize_index(index)];
    }
    const ElementPtr &operator [](int index) const
    {
        return this->_children.at(this->normalize_index(index));
    }

    /*!
      Deletes the given subelement, by index.

      @param index What subelement to delete.
      @exception IndexError If the given element does not exist.
     */
    void removeAt(int index)
    {
        this->_children.removeAt(this->normalize_index(index));
    }

    /*!
      Adds a subelement to the end of this element.  In document order,
      the new element will appear after the last existing subelement (or
      directly after the text, if it's the first subelement), but before
      the end tag for this element.

      @param element The element to add.
     */
    void append(const ElementPtr &element)
    {
        this->_children.append(element);
    }

    /*!
      Appends subelements from a sequence.

      @param elements A sequence object with zero or more elements.
      @since 1.3
     */
    void extend(const ElementList_t &elements)
    {
        this->_children.append(elements);
    }

    /*!
      Inserts a subelement at the given position in this element.

      @param index Where to insert the new subelement.
     */
    void insert(int index, const ElementPtr &element)
    {
        if ( index < 0 ) {
            index += this->size();
        }
        if ( index < 0 ) {
            index = 0;
        }
        if ( index > this->size() ) {
            index = this->size();
        }
        this->_children.insert(index, element);
    }

    /*!
      Removes a matching subelement.  Unlike the <b>find</b> methods,
      this method compares elements based on identity, not on tag
      value or contents.  To remove subelements by other means, the
      easiest way is often to use a list comprehension to select what
      elements to keep, and use slice assignment to update the parent
      element.

      @param element What element to remove.
      @exception ValueError If a matching element could not be found.
     */
    void remove(const ElementPtr &element)
    {
        this->_children.removeOne(element);
    }

    /*!
      Finds the first matching subelement, by tag name or path.

      @param path What element to look for.
      @keyparam namespaces Optional namespace prefix map.
      @return The first matching element, or None if no element was found.
      @defreturn Element or None
     */
    ElementPtr find(const pypp::str &path, const Namespaces_t &namespaces=Namespaces_t())
    {
        return ElementPath::find(this->shared_from_this(), path, namespaces);
    }

    /*!
      Finds text for the first matching subelement, by tag name or path.

      @param path What element to look for.
      @param default What to return if the element was not found.
      @keyparam namespaces Optional namespace prefix map.
      @return The text content of the first matching element, or the
          default value no element was found.  Note that if the element
          is found, but has no text content, this method returns an
          empty string.
      @defreturn string
     */
    pypp::str findtext(const pypp::str &path, const pypp::str &default_=pypp::str(), const Namespaces_t &namespaces=Namespaces_t())
    {
        return ElementPath::findtext(this->shared_from_this(), path, default_, namespaces);
    }

    /*!
      Finds all matching subelements, by tag name or path.

      @param path What element to look for.
      @keyparam namespaces Optional namespace prefix map.
      @return A list or other sequence containing all matching elements,
         in document order.
      @defreturn list of Element instances
     */
    ElementList_t findall(const pypp::str &path, const Namespaces_t &namespaces=Namespaces_t())
    {
        return ElementPath::findall(this->shared_from_this(), path, namespaces);
    }

    /*!
      Finds all matching subelements, by tag name or path.

      @param path What element to look for.
      @keyparam namespaces Optional namespace prefix map.
      @return An iterator or sequence containing all matching elements,
         in document order.
      @defreturn a generated sequence of Element instances
     */
    ElementList_t iterfind(const pypp::str &path, const Namespaces_t &namespaces=Namespaces_t())
    {
        return ElementPath::iterfind(this->shared_from_this(), path, namespaces);
    }

    /*!
      Resets an element.  This function removes all subelements, clears
      all attributes, and sets the <b>text</b> and <b>tail</b> attributes
      to None.
     */
    void clear()
    {
        this->attrib.clear();
        this->_children.clear();
        this->text.clear();
        this->tail.clear();
    }

    /*!
      Gets an element attribute.  Equivalent to <b>attrib.get</b>, but
      some implementations may handle this a bit more efficiently.

      @param key What attribute to look for.
      @param default What to return if the attribute was not found.
      @return The attribute value, or the default value, if the
          attribute was not found.
      @defreturn string or None
     */
    pypp::str get(const pypp::str &key, const pypp::str &default_=pypp::str()) const
    {
        if ( this->attrib.contains(key) ) {
            return this->attrib[key];
        }
        return default_;
    }

    /*!
      Sets an element attribute.  Equivalent to <b>attrib[key] = value</b>,
      but some implementations may handle this a bit more efficiently.

      @param key What attribute to set.
      @param value The attribute value.
     */
    void set(const pypp::str &key, const pypp::str &value)
    {
        this->attrib[key] = value;
    }

    /*!
      Gets a list of attribute names.  The names are returned in an
      arbitrary order (just like for an ordinary Python dictionary).
      Equivalent to <b>attrib.keys()</b>.

      @return A list of element attribute names.
      @defreturn list of strings
     */
    QStringList keys() const
    {
        return this->attrib.keys();
    }

    /*!
      Gets element attributes, as a sequence.  The attributes are
      returned in an arbitrary order.  Equivalent to <b>attrib.items()</b>.

      @return A list of (name, value) tuples for all attributes.
      @defreturn list of (string, string) tuples
     */
    ItemList_t items() const
    {
        ItemList_t result;
        for ( auto it = this->attrib.cbegin(); it != this->attrib.cend(); ++it ) {
            result.append(Item_t(it.key(), it.value()));
        }
        return result;
    }

    ElementList_t iter(pypp::str tag=pypp::str())
    {
        if ( tag == "*" ) {
            tag = "";
        }
        ElementList_t result;
        if ( tag.isEmpty() || this->tag == tag ) {
            result.append(this->shared_from_this());
        }
        for ( const ElementPtr &elem : this->_children ) {
            for ( const ElementPtr &e : elem->iter(tag) ) {
                result.append(e);
            }
        }
        return result;
    }

    typename ElementList_t::iterator begin()
    {
        return std::begin(this->_children);
    }
    typename ElementList_t::const_iterator begin() const
    {
        return std::begin(this->_children);
    }
    typename ElementList_t::iterator end()
    {
        return std::end(this->_children);
    }
    typename ElementList_t::const_iterator end() const
    {
        return std::end(this->_children);
    }

protected:
    int normalize_index(int index) const
    {
        if ( index < 0 ) {
            index += this->size();
        }
        if ( index < 0 || index >= this->size() ) {
            throw pypp::IndexError();
        }
        return index;
    }

    ElementList_t _children;

};

class Element : public ElementImpl<Element>
{
public:
    using ElementImpl::ElementImpl;

    ElementPtr copy() const
    {
        ElementPtr elem = Element::makeelement(this->tag, this->attrib);
        elem->text = this->text;
        elem->tail = this->tail;
        elem->_children = this->_children;
        return elem;
    }

};

typedef Element::ElementPtr ElementPtr;
typedef Element::ElementList_t ElementList_t;

template <class ElementPtr>
inline ElementPtr SubElement(const ElementPtr &parent, const pypp::str &tag, const Namespaces_t &attrib=Namespaces_t())
{
    ElementPtr element = ElementPtr::element_type::makeelement(tag, attrib);
    parent->append(element);
    return element;
}

template <class Impl>
class ElementTreeImpl
{
public:
    ElementTreeImpl(const typename Impl::ElementPtr &element=typename Impl::ElementPtr()) :
        _root(element)
    {}

    typename Impl::ElementPtr getroot() const
    {
        return this->_root;
    }
    void _setroot(const typename Impl::ElementPtr &element)
    {
        this->_root = element;
    }

    typename Impl::ElementList_t iter(const pypp::str &tag=pypp::str())
    {
        return this->_root->iter(tag);
    }

private:
    typename Impl::ElementPtr _root;

};

typedef ElementTreeImpl<Element> ElementTree;

inline pypp::str escape_cdata(pypp::str text)
{
    if ( text.contains("&") ) {
        text = text.replace("&", "&amp;");
    }
    if ( text.contains("<") ) {
        text = text.replace("<", "&lt;");
    }
    if ( text.contains(">") ) {
        text = text.replace(">", "&gt;");
    }
    return text;
}

inline QByteArray escape_cdata(pypp::str text, const pypp::str &encoding)
{
    text = escape_cdata(text);
    return pypp::encode(text, encoding);
}

inline pypp::str escape_attrib(pypp::str text)
{
    if ( text.contains("&") ) {
        text = text.replace("&", "&amp;");
    }
    if ( text.contains("<") ) {
        text = text.replace("<", "&lt;");
    }
    if ( text.contains(">") ) {
        text = text.replace(">", "&gt;");
    }
    if ( text.contains("\"") ) {
        text = text.replace("\"", "&quot;");
    }
    if ( text.contains("\n") ) {
        text = text.replace("\n", "&#10;");
    }
    return text;
}

///////////////////////////////////////////////////////////////
//! serialization support

static Namespaces_t namespace_map = {
    //! "well-known" namespace prefixes
    std::make_pair(pypp::str("http://www.w3.org/XML/1998/namespace"), pypp::str("xml")),
    std::make_pair(pypp::str("http://www.w3.org/1999/xhtml"), pypp::str("html")),
    std::make_pair(pypp::str("http://www.w3.org/1999/02/22-rdf-syntax-ns#"), pypp::str("rdf")),
    std::make_pair(pypp::str("http://schemas.xmlsoap.org/wsdl/"), pypp::str("wsdl")),
    //! xml schema
    std::make_pair(pypp::str("http://www.w3.org/2001/XMLSchema"), pypp::str("xs")),
    std::make_pair(pypp::str("http://www.w3.org/2001/XMLSchema-instance"), pypp::str("xsi")),
    //! dublin core
    std::make_pair(pypp::str("http://purl.org/dc/elements/1.1/"), pypp::str("dc")),
};

inline void throw_serialization_error(const std::string &text)
{
    throw TypeError("cannot serialize " + text);
}

//! identify namespaces used in this tree
template <class ElementPtr>
std::tuple<Namespaces_t, Namespaces_t> namespaces(const ElementPtr &elem, const pypp::str &default_namespace=pypp::str())
{
    Namespaces_t qnames;
    //! maps qnames to *encoded* prefix:local names
    qnames[pypp::str()] = pypp::str();

    //! maps uri:s to prefixes
    Namespaces_t ns;
    if ( ! default_namespace.isEmpty() ) {
        ns[default_namespace] = pypp::str();
    }

    auto add_qname = [&](const pypp::str &qname) {
        //! calculate serialized qname representation
        try {
            if ( qname.startsWith("{") ) {
                QStringList tmp = qname.mid(1).split("}");
                pypp::str uri = tmp[0];
                pypp::str tag = QStringList(tmp.mid(1)).join("}");
                pypp::str prefix;
                if ( ns.contains(uri) ) {
                    prefix = ns[uri];
                } else {
                    if ( namespace_map.contains(uri) ) {
                        prefix = namespace_map[uri];
                    } else {
                        prefix = QString("ns%1").arg(ns.size());
                    }
                    if ( prefix != "xml" ) {
                        ns[uri] = prefix;
                    }
                }
                if ( ! prefix.isEmpty() ) {
                    qnames[qname] = QString("%1:%2").arg(prefix).arg(tag);
                } else {
                    qnames[qname] = tag; //! default element
                }
            } else {
                if ( ! default_namespace.isEmpty() ) {
                    throw ValueError("cannot use non-qualified names with default_namespace option");
                }
                qnames[qname] = qname;
            }
        } catch (const TypeError &) {
            throw_serialization_error(qname.toStdString());
        }
    };

    //! populate qname and namespaces table
    for ( const ElementPtr &e : elem->iter() ) {
        pypp::str tag = e->tag;
        if ( ! qnames.contains(tag) ) {
            add_qname(tag);
        }
        for ( const Item_t item : e->items() ) {
            pypp::str key = item.first;
            if ( ! qnames.contains(key) ) {
                add_qname(key);
            }
        }
    }
    return std::make_tuple(qnames, ns);
}

template <class ElementPtr>
void serialize_xml(const std::function<void(const pypp::str &)> &write, const ElementPtr &elem, const Namespaces_t &qnames, const Namespaces_t &namespaces)
{
    {
        if ( ! qnames.contains(elem->tag) ) {
            // tag is None
            if ( ! elem->text.isEmpty() ) {
                write(escape_cdata(elem->text));
            }
            for ( const ElementPtr &e : (*elem) ) {
                serialize_xml(write, e, qnames, Namespaces_t());
            }
        } else {
            write("<" + elem->tag);
            ItemList_t items = elem->items();
            if ( ! items.isEmpty() || ! namespaces.isEmpty() ) {
                if ( ! namespaces.isEmpty() ) {
                    for ( const Item_t &item : pypp::sorted(pypp::xml::etree::items(namespaces), [](const Item_t &lhs, const Item_t &rhs) -> bool { return lhs.second < rhs.second; }) ) {
                        pypp::str v = item.first;
                        pypp::str k = item.second;
                        if ( ! k.isEmpty() ) {
                            k = ":" + k;
                        }
                        write(QString(" xmlns%1=\"%2\"").arg(k).arg(escape_attrib(v)));
                    }
                }
                for (const Item_t &item : pypp::sorted(items, [](const Item_t &lhs, const Item_t &rhs) -> bool { return lhs.first < rhs.first; })) {
                    pypp::str k = item.first;
                    pypp::str v = escape_attrib(item.second);
                    write(QString(" %1=\"%2\"").arg(qnames[k], v));
                }
            }
            if ( ! elem->text.isEmpty() || elem->size() > 0 ) {
                write(">");
                if ( ! elem->text.isEmpty() ) {
                    write(escape_cdata(elem->text));
                }
                for (const ElementPtr &e : (*elem)) {
                    serialize_xml(write, e, qnames, Namespaces_t());
                }
                write("</" + elem->tag + ">");
            } else {
                write("/>");
            }
        }
    }
    if ( ! elem->tail.isEmpty() ) {
        write(escape_cdata(elem->tail));
    }
}

template <class ElementPtr>
pypp::str tostring(const ElementPtr &elem, const pypp::str &default_namespace=pypp::str())
{
    Namespaces_t qnames, ns;
    std::tie(qnames, ns) = namespaces(elem, default_namespace);

    pypp::str result;
    auto write = [&](const pypp::str &x) { result += x; };
    serialize_xml(write, elem, qnames, ns);
    return result;
}

} // namespace etree

} // namespace xml

} // namespace pypp

#endif // PYPP_ELEMENTTREE_HPP
