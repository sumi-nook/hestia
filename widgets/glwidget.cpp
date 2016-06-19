#include "glwidget.h"

#include <QMouseEvent>

OpenGLWidget::OpenGLWidget(QWidget *parent) :
#if QT_VERSION >= 0x050400
    QOpenGLWidget(parent)
#else
    QGLWidget(parent)
#endif
{

}

OpenGLWidget::~OpenGLWidget()
{

}

void OpenGLWidget::appendObject(const DrawObject::Ptr &obj)
{
    this->objects.append(obj);
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton ) {
        emit this->clicked();
    } else {
#if QT_VERSION >= 0x050400
        QOpenGLWidget::mouseReleaseEvent(event);
#else
        QGLWidget::mouseReleaseEvent(event);
#endif
    }
}

void OpenGLWidget::initializeGL()
{
    if ( ! this->initialized ) {
        this->ctx = DrawContext::create();
        this->initialized = true;
        emit this->ready();
    }

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClearDepth(1.0);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    this->ctx->width = w;
    this->ctx->height = h;
    glViewport(0, 0, w, h);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    for ( const auto &obj : this->objects ) {
        MatrixContext mat;
        obj->draw(this->ctx);
    }
}

