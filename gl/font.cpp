#include "font.h"

FontRegistry::FontRegistry() :
    fonts()
{

}

void FontRegistry::installFont(const QString &name, const std::shared_ptr<FTFont> &font)
{
    this->fonts[name] = font;
}

std::shared_ptr<FTFont> FontRegistry::font(const QString &name)
{
    if ( this->fonts.find(name) != this->fonts.end() ) {
        return this->fonts[name];
    }
    return nullptr;
}

FontRegistry::Ptr FontRegistry::create()
{
    return Ptr(new FontRegistry);
}
