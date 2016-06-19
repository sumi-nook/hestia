#include "errormessagedialog.h"
#include "ui_errormessagedialog.h"

#include <QPushButton>
#include <QStringListModel>

ErrorMessageDialog::ErrorMessageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorMessageDialog),
    model(new QStringListModel(this))
{
    this->ui->setupUi(this);

    this->ui->listView->setModel(this->model);
}

ErrorMessageDialog::~ErrorMessageDialog()
{

}

void ErrorMessageDialog::appendMessage(const QString &msg)
{
    QStringList strs = this->model->stringList();
    strs.append(msg);;
    this->model->setStringList(strs);
}

void ErrorMessageDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if ( button == this->ui->buttonBox->button(QDialogButtonBox::Close) ) {
        this->close();
    } else if ( button == this->ui->buttonBox->button(QDialogButtonBox::Reset) ) {
        this->model->setStringList({});
    }
}

