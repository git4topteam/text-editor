#include "mainwindow.h"

#include <QApplication>
//#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.menuBar()->ac
    w.show();
    return a.exec();
}
