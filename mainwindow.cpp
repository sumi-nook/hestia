#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <QFileInfo>
#include <QSplitter>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QXmlQuery>

#include <FTGL/ftgl.h>

#include "gl/context.h"
#include "gl/image.h"
#include "glwindow.h"

#include "archive/container.h"
#include "archive/project.h"
#include "models/projecttreemodel.h"
#include "models/structurelistmodel.h"
#include "converter.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    targetActions(),
    highlighter(nullptr),
    previewHasReady(false),
    doubleBufferObject(nullptr),
    glWindow(new GLWindow(this)),
    project(),
    projectModel(),
    scenarioSelection(nullptr),
    structureSelection(nullptr),
    scriptSelection(nullptr),
    structureModel(),
    lineSelection(nullptr),
    currentScenario()
{
    ui->setupUi(this);

    this->targetActions.append(this->ui->actionMarkdown);
    this->targetActions.append(this->ui->actionKAG3);
    this->targetActions.append(this->ui->actionNScripter);

    int width = this->ui->splitterScenario->width();
    int w = width / 3;
    int m = width % 3;
    this->ui->splitterScenario->setSizes({w, w*2+m});
    this->ui->splitterScript->setSizes({w, w*2+m});

    this->highlighter = new ScenarioHighlighter(this->ui->textEditScenario->document());

    this->glWindow->setViewSize(1280, 720);
    connect(this->glWindow.get(), &GLWindow::ready, this, &MainWindow::previewWindow_ready);
    connect(this->glWindow.get(), &GLWindow::next, this, &MainWindow::previewWindow_toNext);
    connect(this->glWindow.get(), &GLWindow::prev, this, &MainWindow::previewWindow_toPrev);

    this->initialize();

    QMetaObject::invokeMethod(this->glWindow.get(), "show");
}

MainWindow::~MainWindow()
{

}

void MainWindow::initialize()
{
    this->projectModel = std::make_shared<ProjectTreeModel>(this);
    connect(this->projectModel.get(), &ProjectTreeModel::projectUpdated, this, &MainWindow::projectModel_projectUpdated);

    // file selection view
    this->ui->treeViewScenario->setModel(this->projectModel.get());
    this->ui->treeViewStructure->setModel(this->projectModel.get());
    this->ui->treeViewScript->setModel(this->projectModel.get());

    this->scenarioSelection = this->ui->treeViewScenario->selectionModel();
    this->structureSelection = this->ui->treeViewStructure->selectionModel();
    this->scriptSelection = this->ui->treeViewScript->selectionModel();
    connect(this->scenarioSelection, &QItemSelectionModel::currentRowChanged, this, &MainWindow::scenarioSelection_currentRowChanged, Qt::QueuedConnection);
    connect(this->structureSelection, &QItemSelectionModel::currentRowChanged, this, &MainWindow::structureSelection_currentRowChanged);
    connect(this->scriptSelection, &QItemSelectionModel::currentChanged, this, &MainWindow::scriptSelection_currentRowChanged);

    // scenario structure view
    this->structureModel = std::make_shared<StructureListModel>(this);

    this->ui->listViewStructure->setModel(this->structureModel.get());
    this->lineSelection = this->ui->listViewStructure->selectionModel();
    connect(this->lineSelection, &QItemSelectionModel::currentRowChanged, this, &MainWindow::lineSelection_currentRowChanged);

    this->setProject(Project::create());

    this->initializeScenario();
}

void MainWindow::initializeScenario()
{
    this->setCurrentScenario(std::make_shared<InMemoryScenario>(QString()));
    this->ui->textEditScenario->clear();
    this->scenarioSelection->setCurrentIndex(QModelIndex(), QItemSelectionModel::Clear);
}

void MainWindow::open(const QString &filepath)
{
    this->setProject(Project::create(filepath));
}

void MainWindow::setProject(const std::shared_ptr<Project> &project)
{
    this->project = project;
    connect(this->project.get(), &Project::changed, this, &MainWindow::projectChanged);
    connect(this->project.get(), &Project::changed, this->projectModel.get(), &ProjectTreeModel::projectUpdate);
    this->projectModel->setProject(this->project);
    this->projectModel->projectUpdate();
}

bool MainWindow::setCurrentScenario(const std::shared_ptr<Container> &scenario)
{
    if ( this->currentScenario == scenario ) {
        return false;
    }
    this->currentScenario = scenario;
    if ( this->currentScenario->filePath().isEmpty() ) {
        this->setWindowTitle(tr("Hestia [*]"));
    }
    return true;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if ( this->project->isChanged() ) {
        auto ret = QMessageBox::warning(this, tr("Project changed"), tr("Do you want to continue?"), QMessageBox::Cancel | QMessageBox::Discard);
        if ( ret == QMessageBox::Cancel ) {
            event->ignore();
            return;
        }
    }
}

QString MainWindow::indexToXHTML(const QModelIndex &index)
{
    if ( ! index.isValid() ) {
        return QString();
    }
    TreeItem *item = static_cast<TreeItem *>(index.internalPointer());
    if ( item->type() != TreeItemType::File ) {
        return QString();
    }
    FileItem *fileItem = dynamic_cast<FileItem *>(item);
    if ( fileItem->object->type() != ContainerType::Scenario ) {
        return QString();
    }

    QString text = getScenarioText(fileItem->object);
    return toXHTML(text);
}

QDomElement MainWindow::indexToDOM(const QModelIndex &index)
{
    QDomDocument doc;
    doc.setContent(this->indexToXHTML(index).toUtf8());
    return doc.documentElement();
}

QString MainWindow::makeScript(const QString &xhtml)
{
    if ( xhtml.isEmpty() ) {
        return QString();
    }

    QDir appDir(QCoreApplication::applicationDirPath());

    QString xslt_path;
    if ( this->ui->actionMarkdown->isChecked() ) {
        xslt_path = appDir.absoluteFilePath("transforms/Markdown.xsl");
    } else if ( this->ui->actionKAG3->isChecked() ) {
        xslt_path = appDir.absoluteFilePath("transforms/KAG3.xsl");
    } else if ( this->ui->actionNScripter->isChecked() ) {
        xslt_path = appDir.absoluteFilePath("transforms/NScripter.xsl");
    }
    if ( xslt_path.isEmpty() || ! QFileInfo(xslt_path).exists() ) {
        return QString();
    }

    QString result;

    QXmlQuery query(QXmlQuery::XSLT20);
    query.setFocus(xhtml);
    query.setQuery(QUrl::fromLocalFile(xslt_path));

    query.evaluateTo(&result);
    return result;
}

void MainWindow::previewWindow_ready()
{
    // set default font
    QString appDir = QCoreApplication::applicationDirPath();
    QString defaultFontPath = appDir + "/fonts/ipag.ttc";

    if ( ! QFileInfo(defaultFontPath).exists() ) {
        QMessageBox::critical(this, tr("Font not found"), tr("Font \"%1\" cannot open.").arg(defaultFontPath));
    } else {
        std::shared_ptr<FTFont> font(new FTPixmapFont(defaultFontPath.toLocal8Bit().constData()));
        if ( ! font->FaceSize(30) ) {
            qDebug() << "FaceSize error,";
        }
        this->glWindow->context()->fontRegistry->installFont(QString(), font);
    }

    // init double buffer
    this->doubleBufferObject = DoubleBufferObject::Ptr(new DoubleBufferObject);
    this->glWindow->setDoubleBufferObject(this->doubleBufferObject);

    // set to ready
    this->previewHasReady = true;
}

void MainWindow::previewWindow_toNext()
{
    if ( ! this->previewHasReady ) {
        return;
    }
    QModelIndex index = this->lineSelection->currentIndex();
    if ( ! index.isValid() ) {
        return;
    }
    QModelIndex next = index.sibling(index.row()+1, index.column());
    if ( ! next.isValid() ) {
        return;
    }
    this->lineSelection->setCurrentIndex(next, QItemSelectionModel::SelectCurrent);
}

void MainWindow::previewWindow_toPrev()
{
    if ( ! this->previewHasReady ) {
        return;
    }
    QModelIndex index = this->lineSelection->currentIndex();
    if ( ! index.isValid() ) {
        return;
    }
    QModelIndex prev = index.sibling(index.row()-1, index.column());
    if ( ! prev.isValid() ) {
        return;
    }
    this->lineSelection->setCurrentIndex(prev, QItemSelectionModel::SelectCurrent);
}

void MainWindow::projectChanged(const Container::Ptr &container)
{
    this->setWindowModified(true);
    if ( container ) {
        QString filepath = container->filePath();
        this->setWindowTitle(tr("%1 - Hestia [*]").arg(filepath));
    }
}

void MainWindow::projectModel_projectUpdated()
{
    this->ui->treeViewScenario->setRootIndex(this->projectModel->index(0, 0));
    this->ui->treeViewStructure->setRootIndex(this->projectModel->index(0, 0));
    this->ui->treeViewScript->setRootIndex(this->projectModel->index(0, 0));

    this->ui->treeViewScenario->expandAll();
    this->ui->treeViewStructure->expandAll();
    this->ui->treeViewScript->expandAll();
}

void MainWindow::scenarioSelection_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if ( ! current.isValid() ) {
        return;
    }
    TreeItem *currentItem = static_cast<TreeItem *>(current.internalPointer());
    TreeItem *previousItem = static_cast<TreeItem *>(previous.internalPointer());
    if ( ! currentItem || ! previousItem || currentItem == previousItem ) {
        return;
    }

    if ( currentItem->type() != TreeItemType::File ) {
        return;
    }

    FileItem *fileItem = dynamic_cast<FileItem *>(currentItem);
    if ( fileItem->object->type() != ContainerType::Scenario ) {
        return;
    }

    // TODO: currentIsChanged

    if ( this->setCurrentScenario(fileItem->object) ) {
        this->ui->textEditScenario->setScenario(this->currentScenario);
        QString filepath = this->currentScenario->filePath();
        this->setWindowTitle(tr("%1 - Hestia [*]").arg(filepath));
    }
}

void MainWindow::structureSelection_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if ( ! current.isValid() ) {
        return;
    }
    TreeItem *currentItem = static_cast<TreeItem *>(current.internalPointer());
    TreeItem *previousItem = static_cast<TreeItem *>(previous.internalPointer());
    if ( ! currentItem || ! previousItem || currentItem == previousItem ) {
        return;
    }

    if ( currentItem->type() != TreeItemType::File ) {
        return;
    }

    FileItem *fileItem = dynamic_cast<FileItem *>(currentItem);
    if ( fileItem->object->type() != ContainerType::Scenario ) {
        return;
    }

    QDomElement root = this->indexToDOM(current);
    this->structureModel->setRoot(root);
}

void MainWindow::scriptSelection_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    this->showScript(current);
}

void MainWindow::lineSelection_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if ( ! this->previewHasReady ) {
        return;
    }
    if ( ! current.isValid() ) {
        return;
    }

    StructureNode::Ptr node = this->structureModel->indexToNode(current);
    if ( ! node ) {
        return;
    }

    // background image
    if ( node->context() && node->context()->bg_img.lock() ) {
        std::shared_ptr<BackgroundImageNode> bgNode = std::dynamic_pointer_cast<BackgroundImageNode>(node->context()->bg_img.lock());
        if ( bgNode && ! bgNode->src().isEmpty() ) {
            QOpenGLTexture *texture = this->doubleBufferObject->backBuffer().backgroundTexture();
            QString path = bgNode->src();
            if ( ! QFileInfo(path).exists() ) {
                path = QDir(this->project->filePath()).absoluteFilePath(path);
            }
            if ( QFileInfo(path).exists() ) {
                DrawObject::Ptr img = Image::create(texture, QImage(path));
                this->doubleBufferObject->setBackgroundImage(img);
            }
        }
    }

    // message window
    this->doubleBufferObject->setMessageWindow(FunctionObject::create([](const DrawContext::Ptr &ctx) -> void {
        glLoadIdentity();
        ctx->ortho2D();

        AlphaBlendContext alphaBlend;
        Q_UNUSED(alphaBlend);

        glColor4d(0.0, 0.0, 0.0, 0.5);

        glBegin(GL_QUADS);
        // left, top
        glVertex2d(0, 0);
        // right, top
        glVertex2d(1280, 0);
        // right, bottom
        glVertex2d(1280, 300);
        // left, bottom
        glVertex2d(0, 300);
        glEnd();
    }));

    // message
    QString text = current.data().toString();
    this->doubleBufferObject->setMessage(FunctionObject::create([text](const DrawContext::Ptr &ctx) -> void {
        glLoadIdentity();
        ctx->ortho2D();
        glColor3d(1.0, 1.0, 1.0);
        Point2D point(100, 200);
        glRasterPos2d(point.x, point.y);
        std::shared_ptr<FTFont> font = ctx->fontRegistry->font();
        if ( ! font ) {
            return;
        }
        QString tmp;
        int line = 0;
        for ( const QChar &ch : text ) {
            tmp += ch;
            FTBBox bb = font->BBox(tmp.toStdWString().c_str());
            FTPoint u = bb.Upper();
            FTPoint l = bb.Lower();
            if ( (point.x * 2.0 + u.X() - l.X()) > ctx->width ) {
                font->Render(tmp.left(tmp.size() - 1).toStdWString().c_str());
                tmp = ch;
                ++line;
                glRasterPos2d(point.x, point.y - font->LineHeight() * line);
            }
        }
        font->Render(tmp.toStdWString().c_str());
    }));

    this->doubleBufferObject->flip();
}

void MainWindow::showScript(const QModelIndex &index)
{
    if ( ! index.isValid() ) {
        this->ui->textEditScript->clear();
        return;
    }
    TreeItem *currentItem = static_cast<TreeItem *>(index.internalPointer());
    if ( ! currentItem ) {
        this->ui->textEditScript->clear();
        return;
    }

    if ( currentItem->type() != TreeItemType::File ) {
        this->ui->textEditScript->clear();
        return;
    }

    QString xhtml = this->indexToXHTML(index);
    if ( xhtml.isEmpty() ) {
        this->ui->textEditScript->clear();
        return;
    }

    QString script = this->makeScript(xhtml);
    this->ui->textEditScript->setPlainText(script);
}

void MainWindow::on_actionOpen_triggered()
{
    QString filepath = QFileDialog::getExistingDirectory(this, tr(""), ".");
    if ( filepath.isEmpty() ) {
        return;
    }
    this->open(filepath);
}

void MainWindow::on_actionReloadProject_triggered()
{
    this->project->reload();
}

void MainWindow::on_actionShowPreview_triggered()
{
    this->glWindow->show();
}

void MainWindow::on_menuTarget_triggered(QAction *target)
{
    // force checked
    target->setChecked(true);
    // toggle target
    for ( QAction *action : this->targetActions ) {
        if ( action == target ) {
            continue;
        }
        if ( action->isChecked() ) {
            action->setChecked(false);
        }
    }
    QModelIndex current = this->scriptSelection->currentIndex();
    this->showScript(current);
}
