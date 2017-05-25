#include "login.h"
#include "ui_login.h"
#include <QString>
#include <QMessageBox>
#include <QPixmap>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    QPixmap picture(":/img/logo.png");
    ui->PicLabel->setPixmap(picture.scaled(ui->PicLabel->width(),
                                           ui->PicLabel->height(),
                                           Qt::KeepAspectRatio));
}

Login::~Login()
{
    delete ui;
    delete main;
}

void Login::on_GoIn_clicked()
{
    QString login = "superuser";
    QString pass = "letmein";
    if(ui->LogIn->text()==login && ui->Pass->text()==pass){
        hide();
        main = new MainWindow;
        main->show();}
    else{
        QMessageBox::warning(this, "Upsss", "Inccorect user and password");
    }
}
