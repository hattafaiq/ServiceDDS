#include <QWebSocket>
#include <QTimer>
#include <QDate>
#include <QString>
#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include <QTimer>

#ifndef CLIENT_H
#define CLIENT_H

class EchoClient : public QObject
{
    Q_OBJECT
public:
    explicit EchoClient(QObject *parent = nullptr);
    double y_preprosesing_data[2560];
    double x[2560];
    double data_tampil[2560];
    void tampil();
    void init_time();
    void onBinMessageReceived(QByteArray message);
    float outValue[2560];
    QwtPlotCurve *curve;


Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
   // void onTextMessageReceived(QString s_message);
    void showTime();
    //void onBinMessageReceived(QByteArray message);



private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
    QTimer *jam;
    QDate date;
    QString dateTimeText;
    QString time_text;
    int count;
    //////
    QString qs = "bisa";
    QByteArray kanal1;
    bool topik=false;
    QwtPlot plot;
    QTimer *timer;
};


#endif // CLIENT_H
