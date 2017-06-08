#include "additemwindow.h"
#include "ui_additemwindow.h"
#include "addname.h"
#include "func.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>

AddItemWindow::AddItemWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItemWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(sendItemNameAndPrice(InputData)), parent, SLOT(receiveItemList(InputData)));

    //add items to comboBox
    addStocksToComboBox();
}

AddItemWindow::~AddItemWindow()
{
    delete ui;
}

void AddItemWindow::receiveNewItemName(QString name)
{
    ui->comboBox->addItem(name);

    QString pathToFile = createPathToFile("stocks.txt");
    QFile file(pathToFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
        return;

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
    emit sendItemNameAndPrice(data);
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
