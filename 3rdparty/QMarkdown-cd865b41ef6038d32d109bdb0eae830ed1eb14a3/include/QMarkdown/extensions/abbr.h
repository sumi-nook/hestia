#ifndef ABBR_H
#define ABBR_H

/*!
 * Abbreviation Extension for Python-Markdown
 * ==========================================
 *
 * This extension adds abbreviation handling to Python-Markdown.
 *
 * See <https://pythonhosted.org/Markdown/extensions/abbreviations.html>
 * for documentation.
 *
 * Oringinal code Copyright 2007-2008 [Waylan Limberg](http://achinghead.com/) and
 *  [Seemant Kulleen](http://www.kulleen.org/)
 *
 * All changes Copyright 2008-2014 The Python Markdown Project
 *
 * License: [BSD](http://www.opensource.org/licenses/bsd-license.php)
 */

#include "Extension.h"

namespace markdown{

/*!
 * Abbreviation Extension for Python-Markdown.
 */
class AbbrExtension : public Extension
{
public:
    AbbrExtension();

    void extendMarkdown(const std::shared_ptr<Markdown> &md/*, md_globals*/);

public:
    static Extension::Ptr generate(void);

};

} // end of namespace markdown

#endif // ABBR_H
