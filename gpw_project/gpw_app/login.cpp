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

    logsAndPass["superuser"] = "letmein";

    connect(ui->LogIn, SIGNAL(returnPressed()), ui->GoIn, SLOT(click()));
    connect(ui->Pass, SIGNAL(returnPressed()), ui->GoIn, SLOT(click()));
}

Login::~Login()
{
    delete ui;
}

void Login::on_GoIn_clicked()
{
      QString login = ui->LogIn->text();
      if((logsAndPass.find(ui->LogIn->text()) != logsAndPass.end()) && //find correct user in map
         (logsAndPass[ui->LogIn->text()] == ui->Pass->text())){        //and check if passwords are matching
                  hide();
                  main = new MainWindow(this);
                  main->show();
      }
      else
      {
                  QMessageBox::warning(this, "Upsss", "Inccorect user and password");
      }
}
