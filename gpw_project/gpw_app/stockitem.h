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
    void setDetails(QString details_);

    //move to private later
    std::vector<QString> details; //"<price> <volume> <date>"

    ~StockItem();

private:

    QString name;
    QString price;


};

#endif // STOCKITEM_H
