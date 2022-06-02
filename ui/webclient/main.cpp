#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    EchoClient client(QUrl(QStringLiteral("ws://localhost:1234")));
    QObject::connect(&client, &EchoClient::closed, &a, &QCoreApplication::quit);

    return a.exec();
}
