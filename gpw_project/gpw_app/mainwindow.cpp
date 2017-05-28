#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addItemsToUsersComboBox();
    setAllConnections();

    //create users
    akrz = new User("Adam Krzywaniak");
    wpog = new User("Wiktor Pogoda");

    //create window for add item
    itemWindow = new AddItemWindow(this);

    //set text color for red, green and black palletes
    red.setColor(QPalette::Text, Qt::red);
    green.setColor(QPalette::Text, Qt::darkGreen);
    black.setColor(QPalette::Text, Qt::black);


}

MainWindow::~MainWindow()
{
    //delete users
    delete akrz;
    delete wpog;

    //delete add item window
    delete itemWindow;

    delete ui;
}

void MainWindow::on_ImportData_clicked()
{
    QMessageBox::warning(this, "Upsss", "Feature not available");
}

void MainWindow::addItemsToUsersComboBox()
{
    ui->UsersComboBox->addItems({"none", "AKRZ", "WPOG"});
}

void MainWindow::setAllConnections()
{
    connect(ui->UsersComboBox,SIGNAL(currentTextChanged(QString)), ui->AccountValue, SLOT(setText(QString)));
    connect(ui->UsersComboBox,SIGNAL(currentTextChanged(QString)), ui->AccountPercent, SLOT(setText(QString)));
}

void MainWindow::on_AccountValue_textChanged(const QString &value)
{
    if(value=="AKRZ"){
        ui->AccountValue->setText("10000");
    }
    else if(value=="WPOG"){
        ui->AccountValue->setText("5000");
    }
    else if(value=="none"){
        ui->AccountValue->setText("0");
    }
}

void MainWindow::on_AccountPercent_textChanged(const QString &value)
{
    if(value=="AKRZ"){
        ui->AccountPercent->setText("5%");
        ui->AccountPercent->setPalette(green);
    }
    else if(value=="WPOG"){
        ui->AccountPercent->setText("-6%");
        ui->AccountPercent->setPalette(red);
    }
    else if(value=="none"){
        ui->AccountPercent->setText("0%");
        ui->AccountPercent->setPalette(black);
    }
}

void MainWindow::on_AddItem_clicked()
{
    itemWindow->show();

}

void MainWindow::putTheItemToList(QString name, QString price)
{
    ui->StockList->addItem(name);
}
