#ifndef SELLITEM_H
#define SELLITEM_H

#include <QDialog>

namespace Ui {
class SellItem;
}

class SellItem : public QDialog
{
    Q_OBJECT

public:
    explicit SellItem(QWidget *parent = 0);
    ~SellItem();

private:
    Ui::SellItem *ui;
};

#endif // SELLITEM_H
