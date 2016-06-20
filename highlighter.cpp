#include "highlighter.h"

ScenarioHighlighter::ScenarioHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent),
    SPEECH_RE(QString::fromUtf8("^(【[^】]+】)(「[^」]+(」?))$")),
    COMMENT_RE(QString::fromUtf8("^※(.*)$"))
{

}

void ScenarioHighlighter::highlightBlock(const QString &text)
{
    if ( text.isEmpty() ) {
        this->setCurrentBlockState(STATE_EMPTY);
        return;
    }

    bool matched = false;

    if ( this->SPEECH_RE.indexIn(text) != -1 ) {
        this->applySpeechStyle(text, this->SPEECH_RE);
        matched = true;
    }

    if ( ! matched && this->COMMENT_RE.indexIn(text) != -1 ) {
        this->applyCommentStyle(text, this->COMMENT_RE);
        matched = true;
    }

    if ( ! matched ) {
        this->applyDescriptionStyle(text);
    }
}

void ScenarioHighlighter::applySpeechStyle(const QString &text, const QRegExp &reg)
{
    QTextCharFormat fmt;
    fmt.setFontWeight(QFont::Bold);

    this->setFormat(0, text.size(), fmt);
    this->setFormat(0, reg.cap(1).size(), QColor("#0000cd"));
    if ( reg.cap(3).isEmpty() ) {
        this->setFormat(reg.cap(1).size(), reg.cap(2).size(), QColor(Qt::red));
    }
    this->setCurrentBlockState(STATE_SPEECH);
}

void ScenarioHighlighter::applyCommentStyle(const QString &, const QRegExp &reg)
{
    this->setFormat(0, reg.cap(0).size(), QColor("#228b22"));
    this->setCurrentBlockState(STATE_COMMENT);
}

void ScenarioHighlighter::applyDescriptionStyle(const QString &text)
{
    int state = this->previousBlockState();
    if ( state != STATE_EMPTY && state != STATE_DESCRIPTION ) {
        this->setFormat(0, text.size(), QColor(Qt::red));
        this->setCurrentBlockState(this->previousBlockState());
        return;
    }
    this->setFormat(0, text.size(), QColor("#191970"));
    this->setCurrentBlockState(STATE_DESCRIPTION);
}
