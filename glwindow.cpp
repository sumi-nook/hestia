#include "glwindow.h"
#include "ui_glwindow.h"

#include <QKeyEvent>

GLWindow::GLWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GLWindow)
{
    this->ui->setupUi(this);

    connect(this->ui->openGLWidget, &OpenGLWidget::ready, this, &GLWindow::ready);
    connect(this->ui->openGLWidget, &OpenGLWidget::clicked, this, &GLWindow::next);
}

GLWindow::~GLWindow()
{

}

void GLWindow::setViewSize(int width, int height)
{
    this->ui->openGLWidget->setMaximumSize(16777215, 16777215);
    this->ui->openGLWidget->setMinimumSize(width, height);
    this->ui->openGLWidget->setMaximumSize(width, height);
}

void GLWindow::setDoubleBufferObject(const DoubleBufferObject::Ptr &obj)
{
    this->ui->openGLWidget->appendObject(obj);
    connect(obj.get(), &DoubleBufferObject::updated, this->ui->openGLWidget, static_cast<void(QWidget::*)()>(&OpenGLWidget::update));
}

DrawContext::Ptr GLWindow::context()
{
    return this->ui->openGLWidget->context();
}

void GLWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if ( key == Qt::Key_Return ||
         key == Qt::Key_Enter ||
         key == Qt::Key_Down ) {
        emit this->next();
    } else if ( key == Qt::Key_Up ) {
        emit this->prev();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

