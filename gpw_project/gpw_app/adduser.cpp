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

    if(ui->passEdit->text() == ui->confirmEdit->text()){ //check if password and confirm password label is same
        emit userData(ui->loginEdit->text(), ui->passEdit->text());
        close();}
    else{

        QMessageBox::warning(this, "Warning", "Incorrect data");
    }
}
/*
 * TO BE REFACTORED
 * KOMENTARZE W FUNKCJI DO INFORMACJI AKRZA i usunięcia
 */

void AddUser::on_passEdit_textChanged(const QString &pass)
{
    // qDebug() << pass; //możesz odkomentować na potrzeby poznania działania f-cji

    int totalProgress = 0; //int totalnego progresu - na początku równy zero, bo ten pasek progressu powinien zaczynać się od zera
                                  // docelowo zakończyć się powinien na 100

    QRegularExpression pattern1("[a-z]"); //wyrażenie regularne określające zbiór wszystkich małych liter
    QRegularExpression pattern2("[A-Z]"); //wyrażenie regularne określające zbiór wszystkich dużych liter
    QRegularExpression pattern3("[$&+,:;=?@#|'<>.^*()%!-]"); //wyrażenie regularne określające zbiór znaków specjalnych

    if(pass.count(pattern1) == 1) //gdy znajdziemy w naszym stringu 1 mała literę ...
        totalProgress+=15;       // ... to dodajemy do progresu 15
    else if(pass.count(pattern1) == 2) //gdy znajdziemy dwie małe litery
        totalProgress+=15;              // ... to dodajemy do progresu kolejne 15
    else if(pass.count(pattern2) == 1)
        totalProgress+=15;
    else if(pass.count(pattern2) == 2) // reszta analogicznie
        totalProgress+=15;
    else if(pass.count(pattern3) == 1)
        totalProgress+=15;
    else if(pass.count(pattern3) == 2)
        totalProgress+=15;
    else if(pass.length() == 8) // gdy string ma 8 znaków
        totalProgress+=10;     //  to dodajemy 10

    ui->progressBar->setValue(totalProgress); // ui -> wskaźnik do user interface, czyli naszego GUI
                                              // progressBar -> to jest ten zielony pasek postępu w interfejsie
                                              // setValue -> funkcja która ustawia wartośc total progress
                                              // jak podmienisz sobie setValue(totalProgress) na setValue(69) to zobaczysz, że nic się nie będzie zmieniać
                                              // a pasek postępu będzie stał w miejscu na 69%
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
