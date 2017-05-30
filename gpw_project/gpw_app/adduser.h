#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>

namespace Ui {
class AddUser;
}

class AddUser : public QDialog
{
    Q_OBJECT

public:
    explicit AddUser(QWidget *parent = 0);
    ~AddUser();

signals:
    void userData(QString, QString);


private slots:
    void on_pushButton_clicked();

private:
    Ui::AddUser *ui;

};

#endif // ADDUSER_H
