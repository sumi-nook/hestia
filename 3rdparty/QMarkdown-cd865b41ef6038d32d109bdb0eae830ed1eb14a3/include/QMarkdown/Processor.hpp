/*
 * Processor.h
 *
 *  Created on: 2013/10/25
 *      Author: mugwort_rc
 */

#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include "odict.hpp"

namespace markdown{

class Markdown;  //!< forward declaration

class Processor
{
public:
    Processor(const std::weak_ptr<Markdown> &markdown_instance=std::weak_ptr<Markdown>()) :
		markdown(markdown_instance)
	{}
	virtual ~Processor(void)
	{}

    virtual QStringList run(const QStringList &lines) = 0;

protected:
    std::weak_ptr<Markdown> markdown;

};

typedef OrderedDict<std::shared_ptr<Processor>> OrderedDictProcessors;

} // end of namespace markdown

#endif /* PROCESSOR_H_ */
