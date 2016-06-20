#include "structurelistmodel.h"

#include <QTextStream>


QString textContent(const QDomNode &node)
{
    QString content;
    auto childs = node.childNodes();
    for ( int i = 0; i < childs.size(); ++i ) {
        QDomNode child = childs.at(i);
        if ( child.isText() ) {
            content += child.toText().data();
        }
        content += textContent(child);
    }
    return content;
}

QString textContent(const QList<QDomNode> &nodes)
{
    QString content;

    for ( auto node : nodes ) {
        content += textContent(node);
    }

    return content;
}


StructureContext::StructureContext() :
    bg_img()
{

}

StructureContext::StructureContext(const StructureContext::Ptr &ctx) :
    bg_img(ctx->bg_img)
{

}


StructureNode::StructureNode(const QDomElement &elem, const StructureContext::Ptr &ctx) :
    elem(elem),
    ctx(ctx)
{

}

StructureNode::~StructureNode()
{

}


QVariant UnknownNode::data(int role) const
{
    if ( role != Qt::DisplayRole ) {
        return QVariant();
    }
    return "<Unknown>";
}


QVariant SpeechNode::data(int role) const
{
    if ( role != Qt::DisplayRole ) {
        return QVariant();
    }
    auto childs = this->elem.childNodes();
    QString name = childs.item(0).toElement().text();
    QList<QDomNode> nodes;
    for ( int i = 1; i < childs.size(); ++i ) {
        nodes.append(childs.item(i));
    }
    QString speech = textContent(nodes);
    return QString::fromUtf8(u8"【%1】%2").arg(name).arg(speech);
}


QVariant DescriptionNode::data(int role) const
{
    if ( role != Qt::DisplayRole ) {
        return QVariant();
    }
    return textContent(this->elem);
}


QVariant CommentNode::data(int role) const
{
    if ( role != Qt::DisplayRole ) {
        return QVariant();
    }
    QString content = textContent(this->elem);
    return QString::fromUtf8(u8"※%1").arg(content);
}


QVariant BackgroundImageNode::data(int role) const
{
    if ( role != Qt::DisplayRole ) {
        return QVariant();
    }
    QString alt;
    if ( ! this->elem.attribute("alt").isEmpty() ) {
        alt = QString::fromUtf8("：%1").arg(this->elem.attribute("alt"));
    }
    return QString::fromUtf8(u8"※背景：%1%2").arg(this->elem.attribute("src")).arg(alt);
}

QString BackgroundImageNode::src() const
{
    return this->elem.attribute("src");
}


QList<StructureNode::Ptr> parse(const QDomElement &root)
{
    QList<StructureNode::Ptr> result;

    StructureContext::Ptr ctx = std::make_shared<StructureContext>();

    auto nodes = root.childNodes();
    for ( int i = 0; i < nodes.size(); ++i ) {
        QDomElement elem = nodes.at(i).toElement();
        if ( elem.isNull() || (elem.tagName() != "p" && elem.tagName() != "img") ) {
            result.append(std::make_shared<UnknownNode>(elem, ctx));
            continue;
        }

        StructureNode::Ptr tmp;
        QString cls = elem.attribute("class");
        if ( elem.tagName() == "p" ) {
            if ( cls.contains("speech") ) {
                tmp = std::make_shared<SpeechNode>(elem, ctx);
            } else if ( cls.contains("description") ) {
                tmp = std::make_shared<DescriptionNode>(elem, ctx);
            } else if ( cls.contains("comment") ) {
                tmp = std::make_shared<CommentNode>(elem, ctx);
            }
        } else if ( elem.tagName() == "img" ) {
            if ( cls.contains("background") ) {
                ctx = std::make_shared<StructureContext>(ctx);
                tmp = std::make_shared<BackgroundImageNode>(elem, ctx);
                ctx->setBackgroundImage(tmp);
            }
        }
        if ( ! tmp ) {
            tmp = std::make_shared<UnknownNode>(elem, ctx);
        }
        result.append(tmp);
    }

    return result;
}


StructureListModel::StructureListModel(QObject *parent) :
    QAbstractListModel(parent),
    root()
{

}

void StructureListModel::setRoot(const QDomElement &root)
{
    this->beginResetModel();
    this->root = parse(root);
    this->endResetModel();
}

int StructureListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

int StructureListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->root.size();
}

QVariant StructureListModel::data(const QModelIndex &index, int role) const
{
    if ( role != Qt::DisplayRole ) {
        return QVariant();
    }
    return this->root[index.row()]->data(role);
}

QModelIndex StructureListModel::index(int row, int column, const QModelIndex &parent) const
{
    if ( parent.isValid() ) {
        return QModelIndex();
    }
    if ( row < 0 || row >= this->root.size() ) {
        return QModelIndex();
    }
    return this->createIndex(row, column);
}

std::shared_ptr<StructureNode> StructureListModel::indexToNode(const QModelIndex &index) const
{
    if ( ! index.isValid() ) {
        return StructureNode::Ptr();
    }
    return this->root[index.row()];
}
