#ifndef HESTIA_EXTENSIONS_SCENARIODIRECTIONPROCESSOR_H
#define HESTIA_EXTENSIONS_SCENARIODIRECTIONPROCESSOR_H


#include "QMarkdown/extensions/Extension.h"

class ScenarioDirectionExtension : public markdown::Extension
{
public:
    ScenarioDirectionExtension();

    void extendMarkdown(const std::shared_ptr<markdown::Markdown> &md);

    static markdown::Extension::Ptr generate(void);

};

#endif // HESTIA_EXTENSIONS_SCENARIODIRECTIONPROCESSOR_H
