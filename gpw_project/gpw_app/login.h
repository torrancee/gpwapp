#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
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

signals:
    void userData(QString);

public slots:
    void receiveUserData(QString, QString);

private slots:
    void on_GoIn_clicked();

    void on_AddNew_clicked();

private:
    Ui::Login *ui;
    std::map<QString, QString> logsAndPass;

};

#endif // LOGIN_H
