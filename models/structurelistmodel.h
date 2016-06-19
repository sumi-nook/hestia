#ifndef HESTIA_MODELS_STRUCTURELISTMODEL_H
#define HESTIA_MODELS_STRUCTURELISTMODEL_H

#include <memory>

#include <QAbstractListModel>
#include <QList>
#include <QDomElement>


enum class StructureType
{
    Unknown = 0,
    Speech = 1,
    Description = 2,
    Comment = 3,
    BackgroundImage = 4,
};


class StructureNode;

class StructureContext
{
public:
    typedef std::shared_ptr<StructureContext> Ptr;

    StructureContext();

    StructureContext(const StructureContext::Ptr &ctx);

    void setBackgroundImage(const std::shared_ptr<StructureNode> &node)
    {
        this->bg_img = node;
    }

    std::shared_ptr<StructureNode> backgroundImage() const
    {
        return this->bg_img.lock();
    }

    std::weak_ptr<StructureNode> bg_img;

};


class StructureNode
{
public:
    typedef std::shared_ptr<StructureNode> Ptr;

    StructureNode(const QDomElement &elem, const StructureContext::Ptr &ctx);

    virtual ~StructureNode();

    virtual StructureType type() const = 0;
    virtual QVariant data(int role=Qt::DisplayRole) const = 0;

    StructureContext::Ptr context()
    { return this->ctx; }

protected:
    QDomElement elem;
    StructureContext::Ptr ctx;

};


class UnknownNode : public StructureNode
{
public:
    using StructureNode::StructureNode;

    StructureType type() const
    {
        return StructureType::Unknown;
    }

    QVariant data(int role=Qt::DisplayRole) const;

};


class SpeechNode : public StructureNode
{
public:
    using StructureNode::StructureNode;

    StructureType type() const
    {
        return StructureType::Speech;
    }

    QVariant data(int role=Qt::DisplayRole) const;

};


class DescriptionNode : public StructureNode
{
public:
    using StructureNode::StructureNode;

    StructureType type() const
    {
        return StructureType::Description;
    }

    QVariant data(int role=Qt::DisplayRole) const;

};


class CommentNode : public StructureNode
{
public:
    using StructureNode::StructureNode;

    StructureType type() const
    {
        return StructureType::Comment;
    }

    QVariant data(int role=Qt::DisplayRole) const;

};


class BackgroundImageNode : public StructureNode
{
public:
    using StructureNode::StructureNode;

    StructureType type() const
    {
        return StructureType::BackgroundImage;
    }

    QVariant data(int role=Qt::DisplayRole) const;

    QString src() const;

};


class StructureListModel : public QAbstractListModel
{
public:
    StructureListModel(QObject *parent);

    void setRoot(const QDomElement &root);

    int columnCount(const QModelIndex &parent=QModelIndex()) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;

    QModelIndex index(int row, int column, const QModelIndex &parent=QModelIndex()) const;

    std::shared_ptr<StructureNode> indexToNode(const QModelIndex &index) const;

private:
    QList<std::shared_ptr<StructureNode>> root;

};


#endif // HESTIA_MODELS_STRUCTURELISTMODEL_H
