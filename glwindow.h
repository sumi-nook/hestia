#ifndef HESTIA_GLWINDOW_H
#define HESTIA_GLWINDOW_H

#include <memory>

#include <QMainWindow>

#include "emulator/scene.h"

class DrawContext;

namespace Ui {
class GLWindow;
}

class GLWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GLWindow(QWidget *parent=nullptr);
    ~GLWindow();

    std::shared_ptr<DrawContext> context();
    void setViewSize(int width, int height);

    void setDoubleBufferObject(const DoubleBufferObject::Ptr &obj);

protected:
    void keyPressEvent(QKeyEvent *);

signals:
    void ready();
    void next();
    void prev();

private:
    std::shared_ptr<Ui::GLWindow> ui;

};

#endif // HESTIA_GLWINDOW_H
