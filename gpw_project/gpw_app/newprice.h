#ifndef NEWPRICE_H
#define NEWPRICE_H

#include <QDialog>

namespace Ui {
class NewPrice;
}

class NewPrice : public QDialog
{
    Q_OBJECT

public:
    explicit NewPrice(QWidget *parent = 0);
    ~NewPrice();

private:
    Ui::NewPrice *ui;
};

#endif // NEWPRICE_H
