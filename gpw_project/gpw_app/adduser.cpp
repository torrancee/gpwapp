#include "adduser.h"
#include "ui_adduser.h"
#include <QMessageBox>

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
}

AddUser::~AddUser()
{
    delete ui;
}

void AddUser::on_pushButton_clicked()
{
    if(ui->passEdit->text() == ui->confirmEdit->text()){
        emit userData(ui->loginEdit->text(), ui->passEdit->text());
        close();}
    else{

        QMessageBox::warning(this, "Warning", "Incorrect data");
    }
}
