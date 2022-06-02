#ifndef DATA_H
#define DATA_H

#include <QUdpSocket>
#include <QTimer>
#include <QObject>
#include <QList>
#include <QByteArray>
#include <QWebSocket>
#include <QTimer>
#include <QUdpSocket>
#include <QDate>
#include <QString>
#include "QWebSocketServer"
#include "setting.h"

class data : public QObject
{
    Q_OBJECT
public:
    explicit data(QObject *parent = nullptr);
    void req_UDP();
    virtual ~data();
    QByteArray ba;

signals:

public slots:
    void readyReady(); //(QByteArray datagram);//data tidak mau masuk
    void init_time();
    void refresh_plot();


private slots:
    void onNewConnection();
    void processMessage(QByteArray message);
    void socketDisconnected();
    void showTime();
    void datamanagement();
    void sendDataClient1();;

private:
    int counterCH1;
    int counterCH2;
    int counterCH3;
    int counterCH4;
    int counterCH5;
    int counterCH6;
    int counterCH7;
    int counterCH8;
    ///
    //timer
    QTimer *timer;
    QTimer *timera;
    //websocket
    QWebSocketServer *m_pWebSocketServer1;
    QWebSocketServer *m_pWebSocketServer2;
    QWebSocketServer *m_pWebSocketServer3;
    QWebSocketServer *m_pWebSocketServer4;
    QList<QWebSocket *> m_clients1;
    QList<QWebSocket *> m_clients2;
    QList<QWebSocket *> m_clients3;
    QList<QWebSocket *> m_clients4;
    QString *datas;
    //date
    QTimer *jam;
    QTimer *timers;
    QDate date;
    QString dateTimeText;
    QString time_text;
    //
    //parsing UDP
    QByteArray datagram;
    quint16 senderPort;
    QHostAddress sendera;
    QUdpSocket *socket;
    int tim_count;
    // inisial data
    float data_y_voltage1[BESAR_PAKET_F];//256 data
    float data_y_voltage2[BESAR_PAKET_F];//256 data
    float data_y_voltage3[BESAR_PAKET_F];//256 data
    float data_y_voltage4[BESAR_PAKET_F];//256 data
    float data_y_voltage5[BESAR_PAKET_F];//256 data
    float data_y_voltage6[BESAR_PAKET_F];//256 data
    float data_y_voltage7[BESAR_PAKET_F];//256 data
    float data_y_voltage8[BESAR_PAKET_F];//256 data
    float data10paket_1[2560];
    float data10paket_2[2560];
    float data10paket_3[2560];
    float data10paket_4[2560];
    float data10paket_5[2560];
    float data10paket_6[2560];
    float data10paket_7[2560];
    float data10paket_8[2560];
    /////
    float siapkirim[2560];



};
#endif // DATA_H
