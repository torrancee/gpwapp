#include "adduser.h"
#include "ui_adduser.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QDebug>
#include <QPalette>

AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);

    connect(this, SIGNAL(sendUserData(QString,QString)), parent, SLOT(receiveUserData(QString, QString)));

    QPixmap picture(":/img/users.png");
    ui->pic->setPixmap(picture.scaled(ui->pic->width(),
                                           ui->pic->height(),
                                           Qt::KeepAspectRatio));

    // colors for progress bar
    red.setBrush(QPalette::Highlight, QBrush(QColor("red")));   
    green.setBrush(QPalette::Highlight, QBrush(QColor("green")));
    yellow.setBrush(QPalette::Highlight, QBrush(QColor("yellow")));

}

AddUser::~AddUser()
{
    delete ui;
}

void AddUser::on_pushButton_clicked()
{

    if(loginAccepted == LOGIN_OK && passwordStrength == PASSWORD_STRONG_ENOUGH && ui->passEdit->text() == ui->confirmEdit->text()){ //check if password and confirm password label is same
        emit sendUserData(ui->loginEdit->text(), ui->passEdit->text());
        close();}
    else{

        QMessageBox::warning(this, "Warning", "Incorrect data");
    }
}

void AddUser::on_passEdit_textChanged(const QString &pass)
{
    passwordStrength = 0;
    QRegularExpression pattern1("[a-z]");
    QRegularExpression pattern2("[A-Z]");
    QRegularExpression pattern3("[$&+,:;=?@#|'<>.^*()%!-]");

    if(pass.count(pattern1) == 1)
        passwordStrength +=15;
    else if(pass.count(pattern1) >= 2)
        passwordStrength +=30;
    if(pass.count(pattern2) == 1)
        passwordStrength +=15;
    else if(pass.count(pattern2) >= 2)
        passwordStrength +=30;
    if(pass.count(pattern3) == 1)
        passwordStrength +=15;
    else if(pass.count(pattern3) >= 2)
        passwordStrength +=30;
    if(pass.length() >= 8)
        passwordStrength +=10;

    ui->progressBar->setValue(passwordStrength);
}

void AddUser::on_progressBar_valueChanged(int value)
{
    if(value <= 30)
        ui->progressBar->setPalette(red);
    else if(value > 30 && value < 80)
        ui->progressBar->setPalette(yellow);
    else if(value >=80)
        ui->progressBar->setPalette(green);
}

void AddUser::on_loginEdit_textChanged(const QString &login)
{
//    loginAccepted = LOGIN_NOK;
//    if(login.length() > 0 && login.length() < 2){
//        QPixmap picture(":/img/users_green_bottom.png");
//    }else if (login.length() == 2){
//        QPixmap picture(":/img/users_green_middle.png");
//    }else if(login.length() > 2){
//        if(logsAndPass.find(login) == logsAndPass.end()){
//            QPixmap picture(":/img/users_green_full.png");
//            loginAccepted = LOGIN_OK;
//        }else{
//            QPixmap picture(":/img/users_red.png");
//        }
//    }else{
//        QPixmap picture(":/img/users.png");
//    }
//    ui->pic->setPixmap(picture.scaled(ui->pic->width(),
//                                           ui->pic->height(),
//                                           Qt::KeepAspectRatio));
}
