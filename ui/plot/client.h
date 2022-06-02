#include "qwt_plot.h"

#ifndef CLIENT_H
#define CLIENT_H

#include <QWebSocket>
#include <QTimer>
#include <QDate>
#include <QString>

class EchoClient : public QObject
{
    Q_OBJECT
public:
    explicit EchoClient(QObject *parent = nullptr);
    void tampil();
    QwtPlot plot;
    void init_time();
    QTimer *timer;

Q_SIGNALS:
    void closed();

private Q_SLOTS:


private:

};


#endif // CLIENT_H
