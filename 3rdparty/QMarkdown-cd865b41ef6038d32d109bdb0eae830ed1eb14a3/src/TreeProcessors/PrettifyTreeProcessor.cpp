#include "TreeProcessors/PrettifyTreeProcessor.h"

#include "util.h"

namespace markdown
{

void PrettifyTreeProcessor::prettifyETree(const Element &elem)
{
    if ( util::isBlockLevel(elem->tag) && elem->tag != "code" && elem->tag != "pre" ) {
        if ( ( ! elem->hasText() || elem->text.trimmed().isEmpty() )
             && elem->size() > 0 && util::isBlockLevel(elem->child().front()->tag) ) {
            elem->text = "\n";
        }
        for ( const Element &e : elem->child() ) {
            if ( util::isBlockLevel(e->tag) ) {
                this->prettifyETree(e);
            }
        }
        if ( ! elem->hasTail() || elem->tail.trimmed().isEmpty() ) {
            elem->tail = "\n";
        }
    }
    if ( ! elem->hasTail() || elem->tail.trimmed().isEmpty() ) {
        elem->tail = "\n";
    }
}

Element PrettifyTreeProcessor::run(const Element &root)
{
    this->prettifyETree(root);
    //! Do <br />'s seperately as they are often in the middle of
    //! inline content and missed by _prettifyETree.
    for ( const Element &br : root->iter("br") ) {
        if ( ! br->hasTail() || br->tail.trimmed().isEmpty() ) {
            br->tail = "\n";
        } else {
            br->tail = "\n"+br->tail;
        }
    }
    //! Clean up extra empty lines at end of code blocks.
    for ( const Element &pre : root->iter("pre") ) {
        if ( pre->size() > 0 && pre->child().front()->tag == "code" ) {
            pre->child().front()->text = pypp::rstrip(pre->child().front()->text)+"\n";
            pre->child().front()->atomic = true;
        }
    }
    return Element();
}

} // namespace markdown
