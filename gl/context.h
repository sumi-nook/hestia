#ifndef HESTIA_GL_CONTEXT_H
#define HESTIA_GL_CONTEXT_H

#include <memory>

#include <GL/gl.h>

#include "base.h"
#include "environment.h"
#include "font.h"

class DrawContext
{
public:
    typedef std::shared_ptr<DrawContext> Ptr;

    void ortho2D();

    static Ptr create();

    GlobalEnvironment::Ptr genv;
    int width;
    int height;
    FontRegistry::Ptr fontRegistry;
    Point2D raster;
    Point3D translated;

private:
    DrawContext();

};


template <GLenum S, GLenum D>
class BlendContext
{
public:
    BlendContext()
    {
        glEnable(GL_BLEND);
        glBlendFunc(S, D);
    }
    ~BlendContext()
    {
        glDisable(GL_BLEND);
    }

};

typedef BlendContext<GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA> AlphaBlendContext;
typedef BlendContext<GL_ONE_MINUS_DST_COLOR, GL_ZERO> ReverseBlendContext;
typedef BlendContext<GL_ONE, GL_ONE> AddBlendContext;
typedef BlendContext<GL_SRC_ALPHA, GL_ONE> AddAlphaBlendContext;
typedef BlendContext<GL_ONE_MINUS_DST_COLOR, GL_ONE> ScreenBlendContext;
typedef BlendContext<GL_ZERO, GL_SRC_COLOR> MultiplicationBlendContext;


class MatrixContext
{
public:
    MatrixContext()
    {
        glPushMatrix();
    }
    ~MatrixContext()
    {
        glPopMatrix();
    }

};


#endif // HESTIA_GL_CONTEXT_H
