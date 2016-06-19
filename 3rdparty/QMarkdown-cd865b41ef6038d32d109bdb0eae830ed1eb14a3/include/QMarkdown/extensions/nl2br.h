#ifndef NL2BR_H
#define NL2BR_H

/*!
 * NL2BR Extension
 * ===============
 *
 * A Python-Markdown extension to treat newlines as hard breaks; like
 * GitHub-flavored Markdown does.
 *
 * See <https://pythonhosted.org/Markdown/extensions/nl2br.html>
 * for documentation.
 *
 * Oringinal code Copyright 2011 [Brian Neal](http://deathofagremmie.com/)
 *
 * All changes Copyright 2011-2014 The Python Markdown Project
 *
 * License: [BSD](http://www.opensource.org/licenses/bsd-license.php)
 *
 */

#include "Extension.h"

namespace markdown{

class Nl2BrExtension : public Extension
{
public:
    void extendMarkdown(const std::shared_ptr<Markdown> &md/*, md_globals*/);

public:
    static Extension::Ptr generate(void);

};

} // end of namespace markdown

#endif // NL2BR_H
