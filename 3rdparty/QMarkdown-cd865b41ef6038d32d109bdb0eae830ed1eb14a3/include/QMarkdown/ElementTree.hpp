/*
 * ElementTree.hpp
 *
 *  Created on: 2013/11/09
 *      Author: mugwort_rc
 */

#ifndef ELEMENTTREE_HPP_
#define ELEMENTTREE_HPP_

#include "pypp/xml/etree/elementtree.hpp"

namespace markdown{

namespace impl {

class Element : public pypp::xml::etree::ElementImpl<Element>
{
public:
    Element(const pypp::str &tag, const Attribute_t &attrib=Attribute_t()) :
        ElementImpl(tag, attrib),
        atomic(false)
    {}

    ElementPtr copy() const
    {
        ElementPtr elem = Element::makeelement(this->tag, this->attrib);
        elem->text = this->text;
        elem->tail = this->tail;
        elem->_children = this->_children;
        elem->atomic = this->atomic;
        return elem;
    }

    bool atomic;

    ElementList_t child() const
    {
        return this->_children;
    }

    bool hasText() const
    {
        return ! this->text.isEmpty();
    }
    bool hasTail() const
    {
        return ! this->tail.isEmpty();
    }

};

} // namespace impl


typedef impl::Element::ElementPtr Element;
typedef pypp::xml::etree::ElementTreeImpl<impl::Element> ElementTree;
typedef impl::Element::ElementList_t ElementList_t;

inline Element createElement(const pypp::str &tag)
{
    return impl::Element::makeelement(tag);
}

inline Element createSubElement(const Element &element, const pypp::str &tag)
{
    return pypp::xml::etree::SubElement(element, tag);
}

} // end of namespace markdown

#endif // ELEMENTTREE_HPP_
