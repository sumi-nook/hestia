#ifndef HESTIA_EXTENSIONS_SCENARIOPARAGRAPHTREEPROCESSOR_H
#define HESTIA_EXTENSIONS_SCENARIOPARAGRAPHTREEPROCESSOR_H

#include "QMarkdown/extensions/Extension.h"


class ScenarioParagraphExtension : public markdown::Extension
{
public:
    ScenarioParagraphExtension();

    void extendMarkdown(const std::shared_ptr<markdown::Markdown> &md);

    static markdown::Extension::Ptr generate(void);


};


#endif // HESTIA_EXTENSIONS_SCENARIOPARAGRAPHTREEPROCESSOR_H
