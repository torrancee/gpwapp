#ifndef ADDITEMWINDOW_H
#define ADDITEMWINDOW_H

#include <QDialog>

namespace Ui {
class AddItemWindow;
}

class AddItemWindow : public QDialog
{
    Q_OBJECT

signals:
    void mySignal(QString name, QString price);

public:
    explicit AddItemWindow(QWidget *parent = 0);
    ~AddItemWindow();
    QString name;
    QString price;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddItemWindow *ui;
    void sendTheListOfStocks(QString name, QString price);

};

#endif // ADDITEMWINDOW_H
