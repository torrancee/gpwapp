#include "addname.h"
#include "ui_addname.h"

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

void AddName::on_buttonBox_accepted()
{
    emit sendNewItemName(ui->nameEdit->text());
}
