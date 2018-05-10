#include "ceshi.h"
#include <QApplication>
#include<QDebug>
#include <QDir>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   // qDebug() <<"ceshi"<< QDir::currentPath();
    Ceshi w;

    w.show();

    return a.exec();
}
