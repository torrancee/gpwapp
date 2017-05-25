#include "login.h"
#include <QApplication>
#include <user.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login l;
    l.show();
    //MainWindow w;
    //w.show();

    return a.exec();
}
