#ifndef HESTIA_HIGHLIGHTER_H
#define HESTIA_HIGHLIGHTER_H

#include <QSyntaxHighlighter>

class ScenarioHighlighter : public QSyntaxHighlighter
{
public:
    ScenarioHighlighter(QTextDocument *parent);

    void highlightBlock(const QString &text);

protected:
    void applySpeechStyle(const QString &text, const QRegExp &reg);
    void applyCommentStyle(const QString &text, const QRegExp &reg);
    void applyDescriptionStyle(const QString &text);

private:
    const QRegExp SPEECH_RE;
    const QRegExp COMMENT_RE;

    static const int STATE_EMPTY = -1;
    static const int STATE_SPEECH = 1;
    static const int STATE_DESCRIPTION = 2;
    static const int STATE_COMMENT = 3;

};

#endif // HESTIA_HIGHLIGHTER_H
