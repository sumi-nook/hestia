#ifndef HESTIA_MODELS_PROJECTTREEMODEL_H
#define HESTIA_MODELS_PROJECTTREEMODEL_H

#include <memory>

#include <QAbstractItemModel>

class Project;
class Container;

enum class TreeItemType
{
    Directory = 1,
    File = 2,
};

class TreeItem
{
public:
    TreeItem(TreeItem *parent, const QString &name);
    virtual ~TreeItem();

    virtual TreeItemType type() const = 0;

    TreeItem *parent;
    QString name;

};


class FileItem : public TreeItem
{
public:
    FileItem(TreeItem *parent, const QString &name, const std::shared_ptr<Container> &object);
    ~FileItem();

    TreeItemType type() const;

    std::shared_ptr<Container> object;

};


class ProjectTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    ProjectTreeModel(QObject *parent=nullptr);
    ~ProjectTreeModel();

    QModelIndex index(int row, int column, const QModelIndex &parent=QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child=QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const;

    int columnCount(const QModelIndex &parent=QModelIndex()) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;

    bool hasChildren(const QModelIndex &parent=QModelIndex()) const;

    void setProject(const std::shared_ptr<Project> &project);

signals:
    void projectUpdated();

public slots:
    void projectUpdate();

private:
    std::shared_ptr<Project> project;
    TreeItem *root;

};

#endif // HESTIA_MODELS_PROJECTTREEMODEL_H
