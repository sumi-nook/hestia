#include "TreeProcessors/InlineProcessor.h"

#include <QDebug>

#include "util.h"
#include "Markdown.h"

namespace markdown
{

InlineProcessor::InlineProcessor(const std::weak_ptr<Markdown> &md) :
    TreeProcessor(md),
    placeholder_prefix(util::INLINE_PLACEHOLDER_PREFIX),
    placeholder_suffix(util::ETX),
    placeholder_length(4 + this->placeholder_prefix.size() + this->placeholder_suffix.size()),
    placeholder_re(util::INLINE_PLACEHOLDER_RE)
{}

InlineProcessor::~InlineProcessor(void)
{}

std::tuple<QString, QString> InlineProcessor::makePlaceholder(const QString &/*type*/)
{
    QString id = QString("%1").arg(this->stashed_nodes.size(), 4, 10, QChar('0'));
    QString hash = util::INLINE_PLACEHOLDER.arg(id);
    return std::make_tuple(hash, id);
}

std::tuple<boost::optional<QString>, int> InlineProcessor::findPlaceholder(const QString &data, int index)
{
    QString regexTmp = data;
    if ( index != -1 ) {
        regexTmp = data.mid(index);
    }
    QRegularExpressionMatch m = this->placeholder_re.match(regexTmp);
    if ( m.hasMatch() ) {
        return std::make_tuple(m.captured(1), index+m.capturedEnd());
    } else {
        return std::make_tuple(boost::none, index+1);
    }
}

QString InlineProcessor::stashNode(const Element &node, const QString &type)
{
    QString placeholder, id;
    std::tie(placeholder, id) = this->makePlaceholder(type);
    this->stashed_nodes[id] = std::make_tuple(boost::none, node);
    return placeholder;
}
QString InlineProcessor::stashNode(const QString &node, const QString &type)
{
    QString placeholder, id;
    std::tie(placeholder, id) = this->makePlaceholder(type);
    this->stashed_nodes[id] = std::make_tuple(node, boost::none);
    return placeholder;
}

QString InlineProcessor::handleInline(const QString &data, int patternIndex)
{
    std::shared_ptr<Markdown> markdown = this->markdown.lock();

    int startIndex = 0;
    QString data_ = data;
    while ( patternIndex < markdown->inlinePatterns.size() ) {
        std::shared_ptr<Pattern> pattern = markdown->inlinePatterns.at(patternIndex);
        bool matched;
        std::tie(data_, matched, startIndex) = this->applyPattern(pattern, data_, patternIndex, startIndex);
        if ( ! matched ) {
            patternIndex += 1;
        }
    }
    return data_;
}

void InlineProcessor::processElementText(const Element &node, const Element &subnode, bool isText)
{
    QString text;
    if ( isText ) {
        if ( subnode->hasText() ) {
            text = subnode->text;
            subnode->text.clear();
        }
    } else {
        if ( subnode->hasTail() ) {
            text = subnode->tail;
            subnode->tail.clear();
        }
    }

    ElementList_t childResult = this->processPlaceholders(text, subnode, isText);

    int pos = 0;
    if ( ! isText && node != subnode ) {
        pos = node->child().indexOf(subnode) + 1;
    } else {
        pos = 0;
    }

    for ( const Element &newChild : childResult ) {
        node->insert(pos++, newChild);
    }
}

ElementList_t InlineProcessor::processPlaceholders(const QString &data, const Element &parent, bool isText)
{
    ElementList_t result;
    auto linkText = [&](const QString &text, bool atomic=false){
        if ( ! text.isEmpty() ) {
            if ( ! result.isEmpty() ) {
                Element target = result.back();
                if ( target->hasTail() ) {
                    target->tail = target->tail+text;
                } else {
                    target->tail = text;
                    result.pop_back();
                    result.push_back(target);
                }
            } else if ( ! isText ) {
                if ( parent->hasTail() ) {
                    parent->tail = parent->tail + text;
                } else {
                    parent->tail = text;
                }
            } else {
                if ( parent->hasText() ) {
                    parent->text = parent->text+text;
                    parent->atomic = atomic;
                } else {
                    parent->text = text;
                    parent->atomic = atomic;
                }
            }
        }
    };
    int startIndex = 0;
    QString data_ = data;
    while ( ! data_.isEmpty() ) {
        int index = data_.indexOf(this->placeholder_prefix, startIndex);
        if ( index != -1 ) {
            boost::optional<QString> id;
            int phEndIndex;
            std::tie(id, phEndIndex) = this->findPlaceholder(data_, index);
            if ( this->stashed_nodes.contains(*id) ) {
                boost::optional<QString> str;
                boost::optional<Element> nodeptr;
                std::tie(str, nodeptr) = this->stashed_nodes[*id];
                if ( index > 0 ) {
                    QString text = data_.mid(startIndex, index-startIndex);
                    linkText(text);
                }

                if ( ! str ) {
                    //! it's Element
                    ElementList_t nodes = {*nodeptr};
                    for ( const Element &e : (*nodeptr)->child() ) {
                        nodes.push_back(e);
                    }
                    for ( const Element &child : nodes ) {
                        if ( child->hasTail() ) {
                            if ( ! child->tail.trimmed().isEmpty() ) {
                                Element new_node = *nodeptr;
                                this->processElementText(new_node, child, false);
                            }
                        }
                        if ( child->hasText() ) {
                            if ( ! child->text.trimmed().isEmpty() ) {
                                this->processElementText(child, child);
                            }
                        }
                    }
                } else {
                    //! it's just a string
                    linkText(*str);
                    startIndex = phEndIndex;
                    continue;
                }

                startIndex = phEndIndex;
                result.push_back(*nodeptr);

            } else {
                //! wrong placeholder
                int end = index + this->placeholder_prefix.size();
                linkText(data_.mid(startIndex, end-startIndex));
                startIndex = end;
            }
        } else {
            QString text = data_.mid(startIndex);
            linkText(text, isText);
            data_ = QString();
        }
    }
    return result;
}

std::tuple<QString, bool, int> InlineProcessor::applyPattern(std::shared_ptr<Pattern> pattern, const QString &data, int patternIndex, int startIndex)
{
    QString regexTmp = data.mid(startIndex);
    QRegularExpressionMatch match = pattern->getCompiledRegExp().match(regexTmp);
    if ( ! match.hasMatch() ) {
        return std::make_tuple(data, false, 0);
    }
    QString leftData = data.left(startIndex);

    boost::optional<QString> result = pattern->handleMatch(match);  //!< first handleMatch (case String)
    QString placeholder;
    if ( ! result ) {
        Element node = pattern->handleMatch(ElementTree(), match);     //!< second handleMatch (case Node)
        if ( ! node ) {
            return std::make_tuple(data, true, leftData.size()+match.capturedStart(match.lastCapturedIndex()));
        }
        if ( ! node->atomic ) {
            //! We need to process current node too
            ElementList_t nodes = {node};
            nodes.append(node->child());
            for ( const Element &child : nodes ) {
                if ( child->hasText() ) {
                    QString text = child->text;
                    if ( ! child->atomic ) {
                        text = this->handleInline(text, patternIndex+1);
                    }
                    child->text = text;
                }
                if ( child->hasTail() ) {
                    QString tail = child->tail;
                    tail = this->handleInline(tail, patternIndex);
                    child->tail = tail;
                }
            }
        }

        placeholder = this->stashNode(node, pattern->type());
    } else {
        placeholder = this->stashNode(*result, pattern->type());
    }

    return std::make_tuple(QString("%1%2%3%4").arg(leftData).arg(match.captured(1)).arg(placeholder).arg(match.captured(match.lastCapturedIndex())), true, 0);
}

Element InlineProcessor::run(const Element &tree)
{
    std::shared_ptr<Markdown> markdown = this->markdown.lock();

    this->stashed_nodes = StashNodes();

    try{
        ElementList_t stack = {tree};
        while ( ! stack.isEmpty() ) {
            Element currElement = stack.back();
            stack.pop_back();
            typedef QPair<Element, ElementList_t> QueueItem;
            typedef QList<QueueItem> Queue;
            Queue insertQueue;
            for ( const Element &child : currElement->child() ) {
                if ( child->hasText() && ! child->atomic ) {
                    QString text = child->text;
                    child->text.clear();
                    ElementList_t lst = this->processPlaceholders(this->handleInline(text), child);
                    stack.append(lst);
                    insertQueue.push_back(qMakePair(child, lst));
                }
                if ( child->hasTail() ) {
                    QString tail = this->handleInline(child->tail);
                    Element dumby = createElement("d");
                    ElementList_t tailResult = this->processPlaceholders(tail, dumby, false);
                    if ( dumby->hasTail() ) {
                        child->tail = dumby->tail;
                    } else {
                        child->tail.clear();
                    }
                    int pos = currElement->child().indexOf(child) + 1;
                    for ( Element elem : pypp::reversed(tailResult) ) {
                        currElement->insert(pos, elem);
                    }
                }
                if ( child->size() > 0 ) {
                    stack.push_back(child);
                }
            }
            for ( const QueueItem &item : insertQueue ) {
                Element element = item.first;
                ElementList_t lst = item.second;
                if ( markdown->enable_attributes() ) {
                    if ( element->hasText() ) {
                        QString text = element->text;
                        text = handleAttributes(text, element);
                        element->text = text;
                    }
                }
                int i = 0;
                for ( const Element &newChild : lst ) {
                    if ( markdown->enable_attributes() ) {
                        //! Processing attributes
                        if ( newChild->hasTail() ) {
                            QString text = newChild->tail;
                            text = handleAttributes(text, element);
                            newChild->tail = text;
                        }
                        if ( newChild->hasText() ) {
                            QString text = newChild->text;
                            text = handleAttributes(text, newChild);
                            newChild->text = text;
                        }
                    }
                    element->insert(i++, newChild);
                }
            }
        }
        return tree;
    } catch (...) {
        qWarning() << "TreeProcessor::run() exception.";
    }
    return Element();
}

} // namespace markdown
