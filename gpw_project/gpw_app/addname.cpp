#include "addname.h"
#include "ui_addname.h"

AddName::AddName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddName)
{
    ui->setupUi(this);
    connect(this, SIGNAL(newName(QString)), parent, SLOT(newName(QString)));
}

AddName::~AddName()
{
    delete ui;
}

void AddName::on_buttonBox_accepted()
{
    emit newName(ui->nameEdit->text());
}
