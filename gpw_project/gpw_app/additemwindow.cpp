#include "additemwindow.h"
#include "ui_additemwindow.h"

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

void AddItemWindow::addStocksToComboBox()
{
    //to be filled from file
    ui->comboBox->addItems({"SFINKS", "KERNEL", "CDPROJECT", "CORMAY", "FON"});
}
