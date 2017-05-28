#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <stockitem.h>
#include <memory>
#include <QTreeWidgetItem>

using std::string;
using std::shared_ptr;
using std::vector;

class User final
{
public:
    User() = delete;
    User(string);
    vector<shared_ptr<QTreeWidgetItem>> stockItems;

private:
    const string name;
    double account;
    int noOfStockCompany;
};

#endif // USER_H
