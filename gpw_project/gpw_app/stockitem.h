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

    ~StockItem();

private:

    QString name;
    QString price;
    std::vector<QString> details;

};

#endif // STOCKITEM_H
