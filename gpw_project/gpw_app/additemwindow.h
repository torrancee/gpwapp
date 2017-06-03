#ifndef ADDITEMWINDOW_H
#define ADDITEMWINDOW_H

#include <QDialog>
#include <QDate>

struct InputData{

    QString name;
    QString price;
    QDate date;
    QString volume;
};

namespace Ui {
class AddItemWindow;
}

class AddItemWindow : public QDialog
{
    Q_OBJECT

signals:
    void mySignal(InputData data);

public:
    explicit AddItemWindow(QWidget *parent = 0);
    ~AddItemWindow();
    QString name;
    QString price;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddItemWindow *ui;
    void sendTheListOfStocks(InputData);
    void addStocksToComboBox();

};

#endif // ADDITEMWINDOW_H
