#ifndef HESTIA_EXTENSIONS_WORDLINK_H
#define HESTIA_EXTENSIONS_WORDLINK_H


#include "QMarkdown/extensions/Extension.h"

class WordLinkExtension : public markdown::Extension
{
public:
    WordLinkExtension();

    void extendMarkdown(const std::shared_ptr<markdown::Markdown> &md/*, md_globals*/);

    static markdown::Extension::Ptr generate(void);

};

#endif // HESTIA_EXTENSIONS_WORDLINK_H
