//#include "ceshi.h"
#include "livemainwin.h"
#include <QApplication>
#include<QDebug>
#include <QDir>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

   // qDebug() <<"ceshi"<< QDir::currentPath();
    Livemainwin w;

    w.show();

    return a.exec();
}
