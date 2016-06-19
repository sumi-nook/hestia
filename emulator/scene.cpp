#include "scene.h"

#include <QOpenGLTexture>

SceneObject::SceneObject() :
    objects(),
    bg_texture(new QOpenGLTexture(QOpenGLTexture::Target2D))
{

}

SceneObject::~SceneObject()
{

}

void SceneObject::clear()
{
    this->objects.clear();
}

void SceneObject::draw(const std::shared_ptr<DrawContext> &ctx)
{
    auto keys = this->objects.keys();
    qSort(keys);
    for ( auto key : keys ) {
        this->objects[key]->draw(ctx);
    }
}


DoubleBufferObject::DoubleBufferObject(QObject *parent) :
    QObject(parent),
    scenes(),
    current(true),
    back(false)
{
    this->scenes[true] = SceneObject();
    this->scenes[false] = SceneObject();
}

DoubleBufferObject::~DoubleBufferObject()
{

}

void DoubleBufferObject::clear()
{
    this->backBuffer().clear();
    this->flip();
}

void DoubleBufferObject::flip()
{
    this->current = ! current;
    this->back = ! this->current;
    this->backBuffer().clear();
    emit this->updated();
}

SceneObject &DoubleBufferObject::backBuffer()
{
    return this->scenes[this->back];
}

void DoubleBufferObject::draw(const std::shared_ptr<DrawContext> &ctx)
{
    this->scenes[this->current].draw(ctx);
}
