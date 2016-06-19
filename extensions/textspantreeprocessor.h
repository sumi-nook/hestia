#ifndef HESTIA_EXTENSIONS_TEXTSPANTREEPROCESSOR_H
#define HESTIA_EXTENSIONS_TEXTSPANTREEPROCESSOR_H

#include "QMarkdown/extensions/Extension.h"


class TextSpanExtension : public markdown::Extension
{
public:
    TextSpanExtension();

    void extendMarkdown(const std::shared_ptr<markdown::Markdown> &md);

    static markdown::Extension::Ptr generate(void);


};


#endif // HESTIA_EXTENSIONS_TEXTSPANTREEPROCESSOR_H
