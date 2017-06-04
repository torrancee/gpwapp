#include "buyitem.h"
#include "ui_buyitem.h"

BuyItem::BuyItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuyItem)
{
    ui->setupUi(this);
}

BuyItem::~BuyItem()
{
    delete ui;
}
