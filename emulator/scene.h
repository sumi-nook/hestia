#ifndef HESTIA_EMULATOR_SCENE_H
#define HESTIA_EMULATOR_SCENE_H

#include <QObject>
#include <QMap>

#include "gl/base.h"

class QOpenGLTexture;

typedef enum {
    BackGroundImage = 0,
    MessageWindow = 1000,
    Message = 1001,
} SceneType;

class SceneObject : public DrawObject
{
public:
    SceneObject();
    ~SceneObject();

    void clear();
    void draw(const std::shared_ptr<DrawContext> &ctx);

    QOpenGLTexture *backgroundTexture()
    { return this->bg_texture; }

    void setBackgroundImage(const DrawObject::Ptr &img)
    { this->objects[BackGroundImage] = img; }

    void setMessageWindow(const DrawObject::Ptr &window)
    { this->objects[MessageWindow] = window; }

    void setMessage(const DrawObject::Ptr &msg)
    { this->objects[Message] = msg; }

    QMap<SceneType, DrawObject::Ptr> objects;
    QOpenGLTexture *bg_texture;

};

class DoubleBufferObject : public QObject, public DrawObject
{
    Q_OBJECT
public:
    typedef std::shared_ptr<DoubleBufferObject> Ptr;

    DoubleBufferObject(QObject *parent=nullptr);
    ~DoubleBufferObject();

    void clear();
    void flip();

    SceneObject &backBuffer();

    void draw(const std::shared_ptr<DrawContext> &ctx);

    void setBackgroundImage(const DrawObject::Ptr &img)
    { this->backBuffer().setBackgroundImage(img); }

    void setMessageWindow(const DrawObject::Ptr &window)
    { this->backBuffer().setMessageWindow(window); }

    void setMessage(const DrawObject::Ptr &msg)
    { this->backBuffer().setMessage(msg); }

protected:
    QMap<bool, SceneObject> scenes;
    bool current;
    bool back;

signals:
    void updated();

};

#endif // HESTIA_EMULATOR_SCENE_H
