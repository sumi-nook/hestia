#include "plaintextedit.h"

#include <QMimeData>

#include "archive/container.h"

void PlainTextEdit::setScenario(const std::shared_ptr<Container> &scenario)
{
    this->setPlainText(getScenarioText(scenario));
}

void PlainTextEdit::insertFromMimeData(const QMimeData *source)
{
    this->insertPlainText(source->text());
}

