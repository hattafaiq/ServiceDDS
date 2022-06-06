#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow client;
    QMainWindow::connect(&client, &MainWindow::closed, &a , &QCoreApplication::quit);
    //client.resize(1200,200);
    client.show();
    return a.exec();
}

