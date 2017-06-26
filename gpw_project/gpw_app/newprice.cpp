#include "newprice.h"
#include "ui_newprice.h"

NewPrice::NewPrice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPrice)
{
    ui->setupUi(this);
    connect(this, SIGNAL(sendNewPrice(QString, QString)), parent, SLOT(receiveItemNewPrice(QString, QString)));
}

NewPrice::~NewPrice()
{
    delete ui;
}

void NewPrice::receiveItemName(QString name)
{
    ui->nameEdit->setText(name);
}

void NewPrice::on_pushButton_clicked()
{
    QString name = ui->nameEdit->text();
    QString price = ui->priceEdit->text();
    emit sendNewPrice(name, price);
    this->close();
}
