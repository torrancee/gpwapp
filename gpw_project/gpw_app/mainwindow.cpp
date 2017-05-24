#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <user.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addItemsToUsersComboBox();

    //create users
    User *akrz = new User("Adam Krzywaniak");
    User *wpog = new User("Wiktor Pogoda");
}

MainWindow::~MainWindow()
{
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
