#ifndef STOCKITEM_H
#define STOCKITEM_H
#include <QString>

class StockItem
{
public:

    StockItem() =  delete;
    StockItem(QString name_, QString price_);
    QString getName();
    QString getPrice();

private:

    QString name;
    QString price;

};

#endif // STOCKITEM_H
