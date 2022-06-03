#include "mainwindow.h"
#include <QApplication>
#include "client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EchoClient client;
    QObject::connect(&client, &EchoClient::closed, &a, &QCoreApplication::quit);
    //client.tampil();
    //client.show();
    return a.exec();
}

