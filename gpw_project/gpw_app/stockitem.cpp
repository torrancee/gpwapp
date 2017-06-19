#include "stockitem.h"
#include <QDebug>

StockItem::StockItem(QString name_, QString price_):
    name(name_), price(price_) {}

QString StockItem::getName()
{
    return name;
}

QString StockItem::getPrice()
{
    return price;
}

void StockItem::setDetails(QString details_)
{
    details.push_back(details_);
}

StockItem::~StockItem()
{

}
