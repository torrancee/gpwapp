#ifndef USER_H
#define USER_H

#include <string>
#include <stockitem.h>
#include <memory>
#include <QTreeWidgetItem>
#include <QString>

using std::string;
using std::shared_ptr;
using std::vector;

class User final
{
public:
    User() = delete;
    User(QString);
    QString getName();
    vector<StockItem> stockItems;

    void saveDataToTheFile();

private:
    const QString name;
    double account;
    int noOfStockCompany;


};

#endif // USER_H
