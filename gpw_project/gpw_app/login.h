#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "mainwindow.h"
#include <map>
#include <QString>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_GoIn_clicked();

private:
    Ui::Login *ui;
    MainWindow *main;
    std::map<QString, QString> logsAndPass;

};

#endif // LOGIN_H
