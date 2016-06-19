#ifndef DEF_LIST_H
#define DEF_LIST_H

/*!
 * Definition List Extension for Python-Markdown
 * =============================================
 *
 * Adds parsing of Definition Lists to Python-Markdown.
 *
 * See <https://pythonhosted.org/Markdown/extensions/definition_lists.html>
 * for documentation.
 *
 * Original code Copyright 2008 [Waylan Limberg](http://achinghead.com)
 *
 * All changes Copyright 2008-2014 The Python Markdown Project
 *
 * License: [BSD](http://www.opensource.org/licenses/bsd-license.php)
 */

#include "Extension.h"

namespace markdown{

/*!
 * Process Definition Lists.
 */
class DefListExtension : public Extension
{
public:
    using Extension::Extension;

    void extendMarkdown(const std::shared_ptr<Markdown> &md/*, md_globals*/);

public:
    static Extension::Ptr generate(void);

};

} // end of namespace markdown

#endif // DEF_LIST_H
