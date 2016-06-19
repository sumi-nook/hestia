#include "context.h"

#include "GL/glu.h"

DrawContext::DrawContext() :
    genv(GlobalEnvironment::create()),
    width(0),
    height(0),
    fontRegistry(FontRegistry::create()),
    raster(0, 0),
    translated(0, 0, 0)
{

}

void DrawContext::ortho2D()
{
    gluOrtho2D(0, this->width, 0, this->height);
}

DrawContext::Ptr DrawContext::create()
{
    return Ptr(new DrawContext);
}
