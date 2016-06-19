#ifndef HESTIA_WIDGETS_PLAINTEXTEDIT_H
#define HESTIA_WIDGETS_PLAINTEXTEDIT_H

#include <memory>

#include <QtGlobal>

#include <QtWidgets/QTextEdit>


class Container;


class PlainTextEdit : public QTextEdit
{
public:
    using QTextEdit::QTextEdit;

    void setScenario(const std::shared_ptr<Container> &scenario);

protected:
    void insertFromMimeData(const QMimeData *source);

};

#endif // HESTIA_WIDGETS_PLAINTEXTEDIT_H
