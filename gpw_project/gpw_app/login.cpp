#include "login.h"
#include "mainwindow.h"
#include "adduser.h"
#include "func.h"
#include "ui_login.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include <QFile>
#include <QTextStream>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    QPixmap picture(":/img/logo.png");
    ui->PicLabel->setPixmap(picture.scaled(ui->PicLabel->width(),
                                           ui->PicLabel->height(),
                                           Qt::KeepAspectRatio));

    getLogsAndPassFromFile();

    //set up connection for enter button clicked in login panel
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

    QString pathToFile = createPathToFile("logsandpass.txt");
    QFile outputUserFile(pathToFile);
    if (!outputUserFile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug() << "cannot open";
        return;
    }

    QTextStream out(&outputUserFile);
    out << login << " " << pass << endl;
    outputUserFile.flush();
    outputUserFile.close();

}

/*
 *  Function called after GoIn button clicked.
 *  Check if user is registered:
 *                      if yes go to main window
 *                      otherwise pop up warning message
 */

void Login::on_GoIn_clicked()
{
      if((logsAndPass.find(ui->LogIn->text()) != logsAndPass.end()) && //find correct user in map
         (logsAndPass[ui->LogIn->text()] == ui->Pass->text())){        //and check if passwords are matching
                  hide();
                  MainWindow *main = new MainWindow(this);

                  //connect and send user data to main window
                  connect(this, SIGNAL(userData(QString, std::map<QString, QString>)),
                          main, SLOT(receiveUserData(QString, std::map<QString, QString>)));
                  emit userData(ui->LogIn->text(), logsAndPass);

                  //main window main loop
                  main->show();
      }
      else{
                  QMessageBox::warning(this, "Upsss", "Inccorect user and password");

                  //clear edit lines for login and pass
                  ui->LogIn->setText("");
                  ui->Pass->setText("");
      }
}

void Login::on_AddNew_clicked()
{    
      AddUser newuser(this);
      newuser.setModal(true);
      newuser.exec();
}

void Login::getLogsAndPassFromFile()
{
    QString pathToFile =  createPathToFile("logsandpass.txt");
    QFile inputLogin(pathToFile);

    if (!inputLogin.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&inputLogin);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList logAndPass = line.split(" ");

        logsAndPass[logAndPass.at(0)] = logAndPass.at(1);
    }

    inputLogin.close();
}
