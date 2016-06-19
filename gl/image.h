#ifndef HESTIA_GL_IMAGE_H
#define HESTIA_GL_IMAGE_H

#include <QByteArray>
#include <QImage>
#include <QOpenGLTexture>

#include <GL/gl.h>

#include "base.h"

class Image : public DrawObject
{
public:
    Image(QOpenGLTexture *texture, double x, double y, int width, int height);

    void draw(const std::shared_ptr<DrawContext> &ctx);

    static DrawObject::Ptr create(QOpenGLTexture *texture, const QImage &image);

    QOpenGLTexture *texture;
    double x;
    double y;
    int width;
    int height;
    Rect rect;

};

#endif // HESTIA_GL_IMAGE_H
