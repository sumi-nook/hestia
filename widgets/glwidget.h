#ifndef HESTIA_WIDGETS_OPENGLWIDGET_H
#define HESTIA_WIDGETS_OPENGLWIDGET_H

#include <QtGlobal>

#if QT_VERSION >= 0x050400
#include <QOpenGLWidget>
#else
#include <QGLWidget>
#endif

#include "gl/base.h"
#include "gl/context.h"


#if QT_VERSION >= 0x050400
class OpenGLWidget : public QOpenGLWidget
#else
class OpenGLWidget : public QGLWidget
#endif
{
    Q_OBJECT
public:
    OpenGLWidget(QWidget *parent=nullptr);
    virtual ~OpenGLWidget();

    void appendObject(const DrawObject::Ptr &obj);
    DrawContext::Ptr context()
    { return this->ctx; }
    const DrawContext::Ptr context() const
    { return this->ctx; }

protected:
    void mouseReleaseEvent(QMouseEvent *event);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

signals:
    void ready();
    void clicked();

private:
    bool initialized;
    QList<DrawObject::Ptr> objects;
    DrawContext::Ptr ctx;

};

#endif // HESTIA_WIDGETS_OPENGLWIDGET_H
