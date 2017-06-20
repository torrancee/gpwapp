#ifndef ADDNAME_H
#define ADDNAME_H

#include <QDialog>

namespace Ui {
class AddName;
}

class AddName : public QDialog
{
    Q_OBJECT

signals:
    void sendNewItemName(QString);

public:
    explicit AddName(QWidget *parent = 0);
    ~AddName();

private slots:
    void on_okButton_clicked();

private:
    Ui::AddName *ui;
};

#endif // ADDNAME_H
