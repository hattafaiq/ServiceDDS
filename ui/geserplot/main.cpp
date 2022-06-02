#include "mainwindow.h"
#include <QApplication>
#include "client.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow m;
    m.init_time();
    m.tampil();
    m.resize(600, 400);
    m.show();
    return a.exec();
}
