#ifndef PRETTIFYTREEPROCESSOR_H
#define PRETTIFYTREEPROCESSOR_H

#include "../TreeProcessors.h"

namespace markdown
{

/*!
 * Add linebreaks to the html document.
 */
class PrettifyTreeProcessor : public TreeProcessor
{
public:
    using TreeProcessor::TreeProcessor;

private:
    /*!
     * Recursively add linebreaks to ElementTree children.
     */
    void prettifyETree(const Element &elem);

public:
    /*!
     * Add linebreaks to ElementTree root object.
     */
    Element run(const Element &root);

};

} // namespace markdown

#endif // PRETTIFYTREEPROCESSOR_H
