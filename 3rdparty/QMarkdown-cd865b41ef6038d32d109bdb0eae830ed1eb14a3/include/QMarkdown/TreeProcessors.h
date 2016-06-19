/*
 * TreeProcessors.h
 *
 *  Created on: 2013/10/28
 *      Author: mugwort_rc
 */

#ifndef TREEPROCESSORS_H_
#define TREEPROCESSORS_H_

#include <tuple>

#include <boost/optional.hpp>

#include "ElementTree.hpp"
#include "odict.hpp"

namespace markdown{

class Markdown;  //!< forward declaration

/*!
 * Treeprocessors are run on the ElementTree object before serialization.
 *
 * Each Treeprocessor implements a "run" method that takes a pointer to an
 * ElementTree, modifies it as necessary and returns an ElementTree
 * object.
 *
 * Treeprocessors must extend markdown.Treeprocessor.
 *
 */
class TreeProcessor
{
public:
    TreeProcessor(const std::weak_ptr<Markdown> &md_instance);
    virtual ~TreeProcessor(void);

    virtual Element run(const Element &root) = 0;

public:
    std::weak_ptr<Markdown> markdown;
    typedef std::tuple<boost::optional<QString>, boost::optional<Element>> NodeItem;
    typedef QMap<QString, NodeItem> StashNodes;
    StashNodes stashed_nodes;


};

typedef OrderedDict<std::shared_ptr<TreeProcessor>> OrderedDictTreeProcessors;

/*!
 * Build the default treeprocessors for Markdown.
 */
OrderedDictTreeProcessors build_treeprocessors(const std::shared_ptr<Markdown> &md_instance);

} // end of namespace markdown

#endif // TREEPROCESSORS_H_
