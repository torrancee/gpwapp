#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPalette>
#include <QTreeWidgetItem>
#include <user.h>
#include "additemwindow.h"
#include <vector>
#include <map>

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
    void addItemsToUsersComboBox(std::map<QString, QString>&);
    void setAllConnections();

signals:

    void sendItemName(QString name);

public slots:

    void putTheItemToList(InputData);
    void receiveUserData(QString login, std::map<QString, QString>);

private slots:

    void on_ImportData_clicked();

    void on_AccountValue_textChanged(const QString &value);

    void on_AccountPercent_textChanged(const QString &value);

    void on_AddItem_clicked();

    void on_actionAbout_triggered();

    void on_buyItem_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<QTreeWidgetItem> items;

    void makePlot();
};

#endif // MAINWINDOW_H
