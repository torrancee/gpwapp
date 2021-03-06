#ifndef ADDUSER_H
#define ADDUSER_H

#define PASSWORD_STRONG_ENOUGH 100

#include <QDialog>
#include <QPalette>

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
    void sendUserData(QString, QString);


private slots:
    void on_pushButton_clicked();

    void on_passEdit_textChanged(const QString &pass);

    void on_progressBar_valueChanged(int value);

private:
    Ui::AddUser *ui;
    QPalette red, green, yellow;
    int passwordStrength;

};

#endif // ADDUSER_H
