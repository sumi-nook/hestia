#include "projecttreemodel.h"

#include <memory>

#include <QDebug>

#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QMap>
#include <QString>

#include "archive/project.h"

TreeItem::TreeItem(TreeItem *parent, const QString &name) :
    parent(parent),
    name(name)
{}

TreeItem::~TreeItem()
{

}

class DirectoryItem : public TreeItem
{
public:
    DirectoryItem(TreeItem *parent, const QString &name) :
        TreeItem(parent, name),
        items()
    {

    }

    ~DirectoryItem()
    {
        qDeleteAll(this->items);
    }

    TreeItemType type() const
    {
        return TreeItemType::Directory;
    }

    int size() const
    {
        return this->items.size();
    }

    TreeItem *at(int index)
    {
        return this->items.at(index);
    }

    void append(TreeItem *item)
    {
        this->items.append(item);
    }

    int index(TreeItem *item) const
    {
        return this->items.indexOf(item);
    }

    QList<TreeItem *> items;

};


FileItem::FileItem(TreeItem *parent, const QString &name, const Container::Ptr &object) :
    TreeItem(parent, name),
    object(object)
{

}

FileItem::~FileItem()
{

}

TreeItemType FileItem::type() const
{
    return TreeItemType::File;
}


TreeItem *make_project_tree(const Project::Ptr &project)
{
    DirectoryItem *root = new DirectoryItem(nullptr, "");
    if ( ! project ) {
        return root;
    }

    QMap<QString, DirectoryItem *> dirs;
    dirs[""] = root;

    QString absoluteRoot = QFileInfo(project->filePath()).absoluteFilePath();

    for ( auto container : project->containers() ) {
        QFileInfo info(container->filePath());
        QString head = info.dir().path();
        QString tail = info.fileName();
        if ( head.startsWith(absoluteRoot) ) {
            head = head.mid(absoluteRoot.size());
        }

        auto parent = root;
        QStringList current;
        for ( const QString &dirname : head.split("/") ) {
            current.append(dirname);
            QString path = current.join("/");
            if ( dirs.find(path) == dirs.end() ) {
                DirectoryItem *tmp = new DirectoryItem(parent, dirname);
                parent->append(tmp);
                parent = tmp;
                dirs[path] = tmp;
            } else {
                parent = dirs[path];
            }
        }

        if ( container->type() == ContainerType::Scenario ||
             container->type() == ContainerType::Image ) {
            parent->append(new FileItem(parent, tail, container));
        }
    }

    return root;
}


ProjectTreeModel::ProjectTreeModel(QObject *parent) :
    QAbstractItemModel(parent),
    project(),
    root(nullptr)
{

}

ProjectTreeModel::~ProjectTreeModel()
{
    if ( this->root ) {
        delete this->root;
        this->root = nullptr;
    }
}

QModelIndex ProjectTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if ( this->hasIndex(row, column, parent) ) {
        if ( ! parent.isValid() ) {
            return this->createIndex(row, column, this->root);
        } else {
            TreeItem *item_ = static_cast<TreeItem *>(parent.internalPointer());
            DirectoryItem *item = dynamic_cast<DirectoryItem *>(item_);
            return this->createIndex(row, column, item->at(row));
        }
    }
    return QModelIndex();
}

QModelIndex ProjectTreeModel::parent(const QModelIndex &child) const
{
    if ( ! child.isValid() ) {
        return QModelIndex();
    }
    TreeItem *item = static_cast<TreeItem *>(child.internalPointer());
    if ( item->parent == nullptr ) {
        return QModelIndex();
    }
    if ( item->parent->parent == nullptr ) {
        return this->index(0, 0);
    }
    TreeItem *grand_ = item->parent->parent;
    DirectoryItem *grand = dynamic_cast<DirectoryItem *>(grand_);
    return this->createIndex(grand->index(item->parent), 0, item->parent);
}

QVariant ProjectTreeModel::data(const QModelIndex &index, int role) const
{
    if ( this->root == nullptr ||
         ! index.isValid() ||
         role != Qt::DisplayRole ) {
        return QVariant();
    }
    TreeItem *item = static_cast<TreeItem *>(index.internalPointer());
    if ( index.column() == 0 ) {
        return item->name;
    }
    return QVariant();
}

QVariant ProjectTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ( role != Qt::DisplayRole ||
         orientation != Qt::Horizontal ) {
        return QVariant();
    }
    if ( section == 0 ) {
        return tr("Name");
    }
    return QVariant();
}

int ProjectTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

int ProjectTreeModel::rowCount(const QModelIndex &parent) const
{
    if ( this->root == nullptr ) {
        return 0;
    }
    // root case
    if ( ! parent.isValid() ) {
        return 1;
    }
    TreeItem *item_ = static_cast<TreeItem *>(parent.internalPointer());
    DirectoryItem *item = dynamic_cast<DirectoryItem *>(item_);
    return item->size();
}

bool ProjectTreeModel::hasChildren(const QModelIndex &parent) const
{
    if ( ! parent.isValid() ) {
        return true;
    }
    TreeItem *item = static_cast<TreeItem *>(parent.internalPointer());
    DirectoryItem *test = dynamic_cast<DirectoryItem *>(item);
    if ( test ) {
        return test->size() > 0;
    } else {
        return false;
    }
}

void ProjectTreeModel::setProject(const std::shared_ptr<Project> &project)
{
    this->project = project;
    this->projectUpdate();
}

void ProjectTreeModel::projectUpdate()
{
    this->beginResetModel();
    if ( this->root ) {
        delete this->root;
        this->root = nullptr;
    }
    this->root = make_project_tree(this->project);
    this->endResetModel();
    emit this->projectUpdated();
}
