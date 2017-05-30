#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPalette>
#include <QTreeWidgetItem>
#include <user.h>
#include "additemwindow.h"
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    User *akrz, *wpog;
    QPalette red, green, black;
    void addItemsToUsersComboBox();
    void setAllConnections();

public slots:

    void putTheItemToList(QString name, QString price);

private slots:

    void on_ImportData_clicked();

    void on_AccountValue_textChanged(const QString &value);

    void on_AccountPercent_textChanged(const QString &value);

    void on_AddItem_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<QTreeWidgetItem> items;

    void makePlot();
};

#endif // MAINWINDOW_H
