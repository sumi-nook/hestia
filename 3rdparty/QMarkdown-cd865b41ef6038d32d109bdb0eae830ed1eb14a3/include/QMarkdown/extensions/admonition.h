#ifndef ADMONITION_H
#define ADMONITION_H

/*!
 * Admonition extension for Python-Markdown
 * ========================================
 *
 * Adds rST-style admonitions. Inspired by [rST][] feature with the same name.
 *
 * [rST]: http://docutils.sourceforge.net/docs/ref/rst/directives.html#specific-admonitions  # noqa
 *
 * See <https://pythonhosted.org/Markdown/extensions/admonition.html>
 * for documentation.
 *
 * Original code Copyright [Tiago Serafim](http://www.tiagoserafim.com/).
 *
 * All changes Copyright The Python Markdown Project
 *
 * License: [BSD](http://www.opensource.org/licenses/bsd-license.php)
 */

#include "Extension.h"

namespace markdown{

class AdmonitionExtension : public Extension, public std::enable_shared_from_this<AdmonitionExtension>
{
public:
    AdmonitionExtension();

    void extendMarkdown(const std::shared_ptr<Markdown> &md/*, md_globals*/);

public:
    static Extension::Ptr generate(void);

};

} // end of namespace markdown

#endif // ADMONITION_H
