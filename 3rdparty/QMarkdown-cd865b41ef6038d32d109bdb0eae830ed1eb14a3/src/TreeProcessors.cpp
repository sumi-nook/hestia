/*
 * TreeProcessors.cpp
 *
 *  Created on: 2013/10/28
 *      Author: mugwort_rc
 */

#include "TreeProcessors.h"

#include "TreeProcessors/InlineProcessor.h"
#include "TreeProcessors/PrettifyTreeProcessor.h"

namespace markdown{

TreeProcessor::TreeProcessor(const std::weak_ptr<Markdown> &md_instance) :
    markdown(md_instance), stashed_nodes()
{}

TreeProcessor::~TreeProcessor(void)
{}


OrderedDictTreeProcessors build_treeprocessors(const std::shared_ptr<Markdown> &md_instance)
{
    OrderedDictTreeProcessors treeprocessors;
    treeprocessors.append("inline", std::shared_ptr<TreeProcessor>(new InlineProcessor(md_instance)));
    treeprocessors.append("prettify", std::shared_ptr<TreeProcessor>(new PrettifyTreeProcessor(md_instance)));
    return treeprocessors;
}

} // end of namespace markdown
