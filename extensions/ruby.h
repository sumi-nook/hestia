#ifndef HESTIA_EXTENSIONS_RUBY_H
#define HESTIA_EXTENSIONS_RUBY_H

#include "QMarkdown/extensions/Extension.h"

class RubyExtension : public markdown::Extension
{
public:
    RubyExtension();

    void extendMarkdown(const std::shared_ptr<markdown::Markdown> &md/*, md_globals*/);

    static markdown::Extension::Ptr generate(void);

};

#endif // HESTIA_EXTENSIONS_RUBY_H
