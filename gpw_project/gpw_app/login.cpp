#include "login.h"
#include "mainwindow.h"
#include "adduser.h"
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

    logsAndPass["superuser"] = "letmein";

    //set up connection
    connect(ui->LogIn, SIGNAL(returnPressed()), ui->GoIn, SLOT(click()));
    connect(ui->Pass, SIGNAL(returnPressed()), ui->GoIn, SLOT(click()));
}

Login::~Login()
{
    delete ui;
}

void Login::receiveUserData(QString login, QString pass)
{
    //add new user to logs and pass map
    logsAndPass[login] = pass;
}

void Login::on_GoIn_clicked()
{
      if((logsAndPass.find(ui->LogIn->text()) != logsAndPass.end()) && //find correct user in map
         (logsAndPass[ui->LogIn->text()] == ui->Pass->text())){        //and check if passwords are matching
                  hide();
                  MainWindow *main = new MainWindow(this);

                  //connect and send user data to main window
                  connect(this, SIGNAL(userData(QString)), main, SLOT(receiveUserData(QString)));
                  emit userData(ui->LogIn->text());

                  //main window main loop
                  main->show();
      }
      else
      {
                  QMessageBox::warning(this, "Upsss", "Inccorect user and password");
      }
}

void Login::on_AddNew_clicked()
{    
      AddUser newuser(this);
      newuser.setModal(true);
      newuser.exec();
}
