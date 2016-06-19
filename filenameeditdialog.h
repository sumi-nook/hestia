#ifndef HESTIA_FILENAMEEDITDIALOG_H
#define HESTIA_FILENAMEEDITDIALOG_H

#include <memory>

#include <QDialog>

namespace Ui {
class FileNameEditDialog;
}

class FileNameEditDialog : public QDialog
{
public:
    explicit FileNameEditDialog(QWidget *parent=nullptr);
    ~FileNameEditDialog();

    QString fileName() const;

private:
    std::shared_ptr<Ui::FileNameEditDialog> ui;

};

#endif // HESTIA_FILENAMEEDITDIALOG_H
