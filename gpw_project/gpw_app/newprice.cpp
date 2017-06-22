#include "newprice.h"
#include "ui_newprice.h"

NewPrice::NewPrice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPrice)
{
    ui->setupUi(this);
}

NewPrice::~NewPrice()
{
    delete ui;
}
