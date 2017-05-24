#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPalette>
#include <user.h>

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

private slots:

    void on_ImportData_clicked();

    void on_AccountValue_textChanged(const QString &value);

    void on_AccountPercent_textChanged(const QString &value);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
