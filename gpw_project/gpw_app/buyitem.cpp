#include "buyitem.h"
#include "ui_buyitem.h"

BuyItem::BuyItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuyItem)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());

    //connect buyItem with mainWindow
    connect(this, SIGNAL(buyItemData(QString,QString,QDate)), parent, SLOT(receiveBuyItemData(QString,QString,QDate)));
}

BuyItem::~BuyItem()
{
    delete ui;
}

void BuyItem::getItemName(QString itemName)
{
    ui->stockItemName->setText(itemName);
}

void BuyItem::on_buttonBox_accepted()
{
    QString price = ui->priceEdit->text();
    QString volume = ui->volumeEdit->text();
    QDate date = ui->dateEdit->date();
    emit buyItemData(price, volume, date);
}
