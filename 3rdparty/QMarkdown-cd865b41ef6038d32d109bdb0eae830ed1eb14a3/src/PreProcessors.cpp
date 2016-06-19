/*
 * PreProcessors.cpp
 *
 *  Created on: 2013/10/25
 *      Author: mugwort_rc
 */

#include "PreProcessors.h"

#include "Markdown.h"

#include "PreProcessors/NormalizeWhitespace.h"
#include "PreProcessors/HtmlBlockProcessor.h"
#include "PreProcessors/ReferencePreprocessor.h"

namespace markdown{

OrderedDictProcessors build_preprocessors(const std::shared_ptr<Markdown> &md_instance)
{
	OrderedDictProcessors preProcessors;
    preProcessors.append("normalize_whitespace", std::shared_ptr<Processor>(new NormalizeWhitespace(md_instance)));
	if ( md_instance->safeMode() != Markdown::escape_mode ) {
        preProcessors.append("html_block", std::shared_ptr<Processor>(new HtmlBlockProcessor(md_instance)));
	}
    preProcessors.append("reference", std::shared_ptr<Processor>(new ReferencePreprocessor(md_instance)));
	return preProcessors;
}

} // end of namespace markdown
