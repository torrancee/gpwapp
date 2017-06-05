#include "func.h"
#include <QDebug>

QString createPathToFile(QString file)
{
    qDebug() << "createPathToFile";
    QString path = QDir::currentPath();
    int position;
    for(QString::iterator it = path.end(); *it!= '/'; it--){

        position = path.indexOf(*it);
    }
    path.remove(position, 50);
    QString pathToFile = path + "gpw_app/txt/" + file;

    return pathToFile;
}
