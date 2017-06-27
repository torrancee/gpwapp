#include "sellitem.h"
#include "ui_sellitem.h"

SellItem::SellItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SellItem)
{
    ui->setupUi(this);
}

SellItem::~SellItem()
{
    delete ui;
}
