/*
 * Serializers.h
 *
 *  Created on: 2013/10/28
 *      Author: mugwort_rc
 */

#ifndef SERIALIZERS_H_
#define SERIALIZERS_H_

#include "ElementTree.hpp"

namespace markdown{

QString to_html_string(const Element &element);

QString to_xhtml_string(const Element &element);

} // end of namespace markdown

#endif // SERIALIZERS_H_
