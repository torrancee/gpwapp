#ifndef BUYITEM_H
#define BUYITEM_H

#include <QDialog>

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

private:
    Ui::BuyItem *ui;
};

#endif // BUYITEM_H
