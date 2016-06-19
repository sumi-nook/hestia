#include "filenameeditdialog.h"
#include "ui_filenameeditdialog.h"


FileNameEditDialog::FileNameEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileNameEditDialog)
{
    this->ui->setupUi(this);
}

FileNameEditDialog::~FileNameEditDialog()
{

}

QString FileNameEditDialog::fileName() const
{
    return this->ui->lineEdit->text();
}
