#ifndef INLINEPROCESSOR_H
#define INLINEPROCESSOR_H

#include "../InlinePatterns.h"
#include "../TreeProcessors.h"

namespace markdown
{

/*!
 * A Treeprocessor that traverses a tree, applying inline patterns.
 */
class InlineProcessor : public TreeProcessor
{
public:
    InlineProcessor(const std::weak_ptr<Markdown> &md);

    ~InlineProcessor(void);

private:
    /*!
     * Generate a placeholder
     */
    std::tuple<QString, QString> makePlaceholder(const QString &/*type*/);

    /*!
     * Extract id from data string, start from index
     *
     * Keyword arguments:
     *
     * * data: string
     * * index: index, from which we start search
     *
     * Returns: placeholder id and string index, after the found placeholder.
     *
     */
    std::tuple<boost::optional<QString>, int> findPlaceholder(const QString &data, int index);

    /*!
     * Add node to stash
     */
    QString stashNode(const Element &node, const QString &type);
    QString stashNode(const QString &node, const QString &type);

    /*!
     * Process string with inline patterns and replace it
     * with placeholders
     *
     * Keyword arguments:
     *
     * * data: A line of Markdown text
     * * patternIndex: The index of the inlinePattern to start with
     *
     * Returns: String with placeholders.
     *
     */
    QString handleInline(const QString &data, int patternIndex = 0);

    /*!
     * Process placeholders in Element.text or Element.tail
     * of Elements popped from self.stashed_nodes.
     *
     * Keywords arguments:
     *
     * * node: parent node
     * * subnode: processing node
     * * isText: bool variable, True - it's text, False - it's tail
     *
     * Returns: None
     *
     */
    void processElementText(const Element &node, const Element &subnode, bool isText=true);

    /*!
     * Process string with placeholders and generate ElementTree tree.
     *
     * Keyword arguments:
     *
     * * data: string with placeholders instead of ElementTree elements.
     * * parent: Element, which contains processing inline data
     *
     * Returns: list with ElementTree elements with applied inline patterns.
     *
     */
    ElementList_t processPlaceholders(const QString &data, const Element &parent, bool isText=true);

    /*!
     * Check if the line fits the pattern, create the necessary
     * elements, add it to stashed_nodes.
     *
     * Keyword arguments:
     *
     * * data: the text to be processed
     * * pattern: the pattern to be checked
     * * patternIndex: index of current pattern
     * * startIndex: string index, from which we start searching
     *
     * Returns: String with placeholders instead of ElementTree elements.
     *
     */
    std::tuple<QString, bool, int> applyPattern(std::shared_ptr<Pattern> pattern, const QString &data, int patternIndex, int startIndex=0);

    /*!
     * Apply inline patterns to a parsed Markdown tree.
     *
     * Iterate over ElementTree, find elements with inline tag, apply inline
     * patterns and append newly created Elements to tree.  If you don't
     * want to process your data with inline paterns, instead of normal string,
     * use subclass AtomicString:
     *
     *     node.text = markdown.AtomicString("This will not be processed.")
     *
     * Arguments:
     *
     * * tree: ElementTree object, representing Markdown tree.
     *
     * Returns: ElementTree object with applied inline patterns.
     *
     */
    Element run(const Element &tree);

private:
    QString placeholder_prefix;
    QString placeholder_suffix;
    unsigned int placeholder_length;
    QRegularExpression placeholder_re;

};

} // namespace markdown

#endif // INLINEPROCESSOR_H
