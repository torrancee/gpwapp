#include "addname.h"
#include "ui_addname.h"
#include <QMessageBox>

AddName::AddName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddName)
{
    ui->setupUi(this);
    connect(this, SIGNAL(sendNewItemName(QString)), parent, SLOT(receiveNewItemName(QString)));
}

AddName::~AddName()
{
    delete ui;
}

void AddName::on_okButton_clicked()
{
    QString currentText = ui->nameEdit->text();

    if(currentText == ""){
        QMessageBox::warning(this, "Ups", "This field cannot be empty");
    }
    else{
        emit sendNewItemName(ui->nameEdit->text());
    }
}
