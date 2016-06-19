#ifndef ATTR_LIST_H
#define ATTR_LIST_H

/*!
 * Attribute List Extension for Python-Markdown
 * ============================================
 *
 * Adds attribute list syntax. Inspired by
 * [maruku](http://maruku.rubyforge.org/proposal.html#attribute_lists)'s
 * feature of the same name.
 *
 * See <https://pythonhosted.org/Markdown/extensions/attr_list.html>
 * for documentation.
 *
 * Original code Copyright 2011 [Waylan Limberg](http://achinghead.com/).
 *
 * Python Markdown Copyright 2011-2014 The Python Markdown Project
 *
 * All changes Copyright 2016 mugwort_rc
 *
 * License: [BSD](http://www.opensource.org/licenses/bsd-license.php)
 */

#include "Extension.h"

namespace markdown{

class AttrListExtension : public Extension
{
public:
    AttrListExtension();

    void extendMarkdown(const std::shared_ptr<Markdown> &md/*, md_globals*/);

public:
    static Extension::Ptr generate(void);

};

} // end of namespace markdown

#endif // ATTR_LIST_H
