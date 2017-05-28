#include "additemwindow.h"
#include "ui_additemwindow.h"

AddItemWindow::AddItemWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItemWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(mySignal(QString,QString)), parent, SLOT(putTheItemToList(QString, QString)));
}

AddItemWindow::~AddItemWindow()
{
    delete ui;
}

void AddItemWindow::on_buttonBox_accepted()
{
    name = ui->NameEdit->text();
    price = ui->PricEdit->text();
    sendTheListOfStocks(name, price);
}

void AddItemWindow::sendTheListOfStocks(QString name, QString price)
{
    emit mySignal(name, price);
}
