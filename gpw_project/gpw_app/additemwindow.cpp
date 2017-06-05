#include "additemwindow.h"
#include "ui_additemwindow.h"
#include "addname.h"
#include "func.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QDir>

AddItemWindow::AddItemWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItemWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(mySignal(InputData)), parent, SLOT(putTheItemToList(InputData)));

    //set date
    ui->dateEdit->setDate(QDate::currentDate());

    //add items to comboBox
    addStocksToComboBox();
}

AddItemWindow::~AddItemWindow()
{
    delete ui;
}

void AddItemWindow::newName(QString name)
{
    ui->comboBox->addItem(name);

    QString pathToFile = createPathToFile("stocks.txt");
    QFile file(pathToFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {   qDebug() << "cannot open";
        return; }

    QTextStream out(&file);
    out << name << endl;
    file.flush();
    file.close();
}

void AddItemWindow::on_buttonBox_accepted()
{
    InputData data;
    data.name = ui->comboBox->currentText();
    data.price = ui->PricEdit->text();
    data.volume = ui->volumeEdit->text();
    data.date = ui->dateEdit->date();
    sendTheListOfStocks(data);
}

void AddItemWindow::sendTheListOfStocks(InputData data)
{
    emit mySignal(data);
}

/*
 *  Read list of stocks from file and add it to user combo box
 */

void AddItemWindow::addStocksToComboBox()
{
    QString pathToFile = createPathToFile("stocks.txt");
    QFile inputStocks(pathToFile);

    if (!inputStocks.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&inputStocks);
    while (!in.atEnd()) {
        QString line = in.readLine();
        ui->comboBox->addItem(line);
    }

    inputStocks.close();

}

void AddItemWindow::on_addName_clicked()
{
    AddName newName(this);
    newName.setModal(true);
    newName.exec();
}
