#ifndef ADDITEMWINDOW_H
#define ADDITEMWINDOW_H

#include <QDialog>
#include <QDate>

struct InputData{

    QString name;
    QString price;
};

namespace Ui {
class AddItemWindow;
}

class AddItemWindow : public QDialog
{
    Q_OBJECT

signals:
    void sendItemNameAndPrice(InputData data);

public:
    explicit AddItemWindow(QWidget *parent = 0);
    ~AddItemWindow();
    QString name;
    QString price;

public slots:
    void receiveNewItemName(QString name);

private slots:
    void on_buttonBox_accepted();

    void on_addName_clicked();

private:
    Ui::AddItemWindow *ui;
    void addStocksToComboBox();
};

#endif // ADDITEMWINDOW_H
