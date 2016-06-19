/*
 * PostProcessors.cpp
 *
 *  Created on: 2013/10/31
 *      Author: mugwort_rc
 */

#include "PostProcessors.h"

#include "PostProcessors/RawHtmlPostprocessor.h"
#include "PostProcessors/AndSubstitutePostprocessor.h"
#include "PostProcessors/UnescapePostprocessor.h"

namespace markdown{

PostProcessor::PostProcessor(const std::weak_ptr<Markdown> &markdown_instance) :
    markdown(markdown_instance)
{}

PostProcessor::~PostProcessor(void)
{}


OrderedDictPostProcessors build_postprocessors(const std::shared_ptr<Markdown> &md_instance)
{
    OrderedDictPostProcessors postprocessors;
    postprocessors.append("raw_html", std::shared_ptr<PostProcessor>(new RawHtmlPostprocessor(md_instance)));
    postprocessors.append("amp_substitute", std::shared_ptr<PostProcessor>(new AndSubstitutePostprocessor()));
    postprocessors.append("unescape", std::shared_ptr<PostProcessor>(new UnescapePostprocessor()));
    return postprocessors;
}

} // end of namespace markdown
