#include "mainwindow.h"
#include <QApplication>
#include "client.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EchoClient m;
    m.tampil();
    return a.exec();
}
