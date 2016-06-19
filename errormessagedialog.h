#ifndef HESTIA_ERRORMESSAGEDIALOG_H
#define HESTIA_ERRORMESSAGEDIALOG_H

#include <memory>

#include <QDialog>

class QAbstractButton;
class QStringListModel;

namespace Ui {
class ErrorMessageDialog;
}

class ErrorMessageDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ErrorMessageDialog(QWidget *parent=nullptr);
    ~ErrorMessageDialog();

public slots:
    void appendMessage(const QString &msg);

protected slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    std::shared_ptr<Ui::ErrorMessageDialog> ui;
    QStringListModel *model;

};

#endif // HESTIA_ERRORMESSAGEDIALOG_H
