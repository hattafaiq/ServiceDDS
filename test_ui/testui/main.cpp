#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    //mainWindow.tampil();
    //mainWindow.plot.resize( 600, 400 );
    mainWindow.resize( 600, 400 );
    mainWindow.show();
    return a.exec();
}
