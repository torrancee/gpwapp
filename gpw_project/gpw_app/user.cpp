#include "user.h"
#include "func.h"
#include <QDebug>
#include <QString>
#include <QFile>

User::User(QString name_):
    name(name_){}

QString User::getName()
{
    return name;
}

void User::saveDataToTheFile()
{
    QString fileName = getName() + "_stockList.txt";
    QString pathToFile = createPathToFile(fileName);
    QFile file(pathToFile);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

    QTextStream out(&file);
    for(auto &stockItem : stockItems){
        out << stockItem.getName() << " " << stockItem.getPrice() << endl;
    }

    file.flush();
    file.close();

    for(auto &stockItem : stockItems){

        QString stockItemFileName = getName() + "_" + stockItem.getName() + "_details.txt";
        QString pathToFile = createPathToFile(stockItemFileName);

        QFile file(pathToFile);
        if (!file.open(QIODevice::ReadWrite))
            return;

        QTextStream out(&file);
        for(auto &details : stockItem.details){
            out << details << endl;
        }

        file.flush();
        file.close();
    }
}

void User::loadDataFromTheFile()
{
    QString fileName = getName() + "_stockList.txt";
    QString pathToFile = createPathToFile(fileName);
    QFile file(pathToFile);
    if (!file.open(QIODevice::ReadOnly))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList nameAndPrice = line.split(" ");

        QString name = nameAndPrice.at(0);
        QString price = nameAndPrice.at(1);

        StockItem newItem(name,price);
        stockItems.push_back(newItem);
    }

    for(auto &stockItem : stockItems){

        QString stockItemFileName = getName() + "_" + stockItem.getName() + "_details.txt";
        QString pathToFile = createPathToFile(stockItemFileName);

        QFile file(pathToFile);
        if (!file.open(QIODevice::ReadOnly))
            return;

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            stockItem.details.push_back(line);
        }
    }
}
