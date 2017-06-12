#include "stockitem.h"

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
