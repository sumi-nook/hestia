#ifndef HESTIA_MAINWINDOW_H
#define HESTIA_MAINWINDOW_H

#include <memory>

#include <QMainWindow>
#include <QDomElement>

#include "highlighter.h"
#include "emulator/scene.h"

class QItemSelectionModel;

class Container;
class GLWindow;
class Project;
class ProjectTreeModel;
class StructureListModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent=nullptr);
    ~MainWindow();

    void initialize();
    void initializeScenario();
    void open(const QString &filepath);

    void setProject(const std::shared_ptr<Project> &project);
    bool setCurrentScenario(const std::shared_ptr<Container> &scenario);

protected:
    void closeEvent(QCloseEvent *);

    QString indexToXHTML(const QModelIndex &index);
    QDomElement indexToDOM(const QModelIndex &index);
    QString makeScript(const QString &xhtml);

public slots:
    void previewWindow_ready();
    void previewWindow_toNext();
    void previewWindow_toPrev();

    void projectChanged(const std::shared_ptr<Container> &container);
    void projectModel_projectUpdated();
    void scenarioSelection_currentRowChanged(const QModelIndex &current, const QModelIndex &previous);
    void structureSelection_currentRowChanged(const QModelIndex &current, const QModelIndex &previous);
    void scriptSelection_currentRowChanged(const QModelIndex &current, const QModelIndex &previous);

    void lineSelection_currentRowChanged(const QModelIndex &current, const QModelIndex &previous);

    void showScript(const QModelIndex &index);

    void on_actionOpen_triggered();
    void on_actionReloadProject_triggered();
    void on_actionShowPreview_triggered();
    void on_menuTarget_triggered(QAction *target);

private:
    std::shared_ptr<Ui::MainWindow> ui;
    QList<QAction *> targetActions;
    QSyntaxHighlighter *highlighter;

    bool previewHasReady;
    DoubleBufferObject::Ptr doubleBufferObject;
    std::shared_ptr<GLWindow> glWindow;

    std::shared_ptr<Project> project;
    std::shared_ptr<ProjectTreeModel> projectModel;
    QItemSelectionModel *scenarioSelection;
    QItemSelectionModel *structureSelection;
    QItemSelectionModel *scriptSelection;

    std::shared_ptr<StructureListModel> structureModel;
    QItemSelectionModel *lineSelection;

    std::shared_ptr<Container> currentScenario;

};

#endif // HESTIA_MAINWINDOW_H
