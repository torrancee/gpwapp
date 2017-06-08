#ifndef BUYITEM_H
#define BUYITEM_H

#include <QDialog>
#include <QDate>

namespace Ui {
class BuyItem;
}

class BuyItem : public QDialog
{
    Q_OBJECT

public:
    explicit BuyItem(QWidget *parent = 0);
    ~BuyItem();

public slots:
    void getItemName(QString itemName);

signals:
    void buyItemData(QString price, QString volume, QDate date);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::BuyItem *ui;
};

#endif // BUYITEM_H
