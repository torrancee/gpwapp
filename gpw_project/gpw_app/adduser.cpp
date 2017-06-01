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

    connect(this, SIGNAL(userData(QString,QString)), parent, SLOT(receiveUserData(QString, QString)));

    QPixmap picture(":/img/users.png");
    ui->pic->setPixmap(picture.scaled(ui->pic->width(),
                                           ui->pic->height(),
                                           Qt::KeepAspectRatio));

    // http://www.qtcentre.org/threads/56235-could-not-change-QProgressBar-color
    // to be tested on Linux machine
    red.setBrush(QPalette::Highlight, QBrush(QColor("red")));
    ui->progressBar->setPalette(red);

}

AddUser::~AddUser()
{
    delete ui;
}

void AddUser::on_pushButton_clicked()
{
    QString password = ui->passEdit->text();
    QRegularExpression patter1("[a-z]");
    QRegularExpression patter2("[A-Z]");
    QRegularExpression patter3("[$&+,:;=?@#|'<>.^*()%!-]");

    qDebug() << password.count(patter1);
    qDebug() << password.count(patter2);
    qDebug() << password.count(patter3);

    if(ui->passEdit->text() == ui->confirmEdit->text()){ //check if password and confirm password label is same
        emit userData(ui->loginEdit->text(), ui->passEdit->text());
        close();}
    else{

        QMessageBox::warning(this, "Warning", "Incorrect data");
    }
}
/*
 * TO BE REFACTORED
 */

void AddUser::on_passEdit_textChanged(const QString &pass)
{
    static int totalProgress = 0;

    QString password = ui->passEdit->text();
    QRegularExpression pattern1("[a-z]");
    QRegularExpression pattern2("[A-Z]");
    QRegularExpression pattern3("[$&+,:;=?@#|'<>.^*()%!-]");

    if(pass.count(pattern1) == 1)
        totalProgress+=15;
    else if(pass.count(pattern1) == 2)
        totalProgress+=15;
    else if(pass.count(pattern2) == 1)
        totalProgress+=15;
    else if(pass.count(pattern2) == 2)
        totalProgress+=15;
    else if(pass.count(pattern3) == 1)
        totalProgress+=15;
    else if(pass.count(pattern3) == 2)
        totalProgress+=15;
    else if(pass.length() == 8)
        totalProgress+=10;

    ui->progressBar->setValue(totalProgress);
}

void AddUser::on_progressBar_valueChanged(int value)
{

}
