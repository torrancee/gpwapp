#ifndef ADDITEMWINDOW_H
#define ADDITEMWINDOW_H

#include <QDialog>

namespace Ui {
class AddItemWindow;
}

class AddItemWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddItemWindow(QWidget *parent = 0);
    ~AddItemWindow();
    QString name;
    QString price;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddItemWindow *ui;

};

#endif // ADDITEMWINDOW_H
