/*
 * tables.h
 *
 *  Created on: 2013/11/04
 *      Author: mugwort_rc
 */

#ifndef TABLES_H_
#define TABLES_H_

/*!
 * Tables Extension for Python-Markdown
 * ====================================
 *
 * Added parsing of tables to Python-Markdown.
 *
 * See <https://pythonhosted.org/Markdown/extensions/tables.html>
 * for documentation.
 *
 * Original code Copyright 2009 [Waylan Limberg](http://achinghead.com)
 *
 * Python-Markdown Copyright 2008-2014 The Python Markdown Project
 *
 * All changes Copyright 2016 mugwort_rc
 *
 * License: [BSD](http://www.opensource.org/licenses/bsd-license.php)
 */

#include "Extension.h"

namespace markdown{

/*!
 * Add tables to Markdown.
 */
class TableExtension : public Extension
{
public:
    TableExtension();

    void extendMarkdown(const std::shared_ptr<Markdown> &md/*, md_globals*/);

public:
    static Extension::Ptr generate(void);

};

} // end of namespace markdown

#endif // TABLES_H_
