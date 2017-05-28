#ifndef STOCKITEM_H
#define STOCKITEM_H
#include <QString>

class StockItem
{
public:
    StockItem();
private:
    QString name;
    QString id;
    int value;
    int percentChange;

};

#endif // STOCKITEM_H
