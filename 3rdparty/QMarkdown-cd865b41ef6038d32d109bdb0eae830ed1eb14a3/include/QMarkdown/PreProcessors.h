/*
 * PreProcessors.h
 *
 *  Created on: 2013/10/25
 *      Author: mugwort_rc
 */

#ifndef PREPROCESSORS_H_
#define PREPROCESSORS_H_

#include "Processor.hpp"

namespace markdown{

class Markdown;  //!< forward declaration

class PreProcessor : public Processor
{
public:
    using Processor::Processor;

    virtual ~PreProcessor(void)
    {}
};

OrderedDictProcessors build_preprocessors(const std::shared_ptr<Markdown> &md_instance);

} // end of namespace markdown

#endif /* PREPROCESSORS_H_ */
