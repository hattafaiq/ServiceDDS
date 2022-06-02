#include "client.h"
#include "datasetup.h"
#include "QWebSocket"
#include "qwt_plot_curve.h"

QT_USE_NAMESPACE

EchoClient::EchoClient(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),m_url(url),m_debug(debug)
{
    qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &EchoClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &EchoClient::closed);
    m_webSocket.open(QUrl(url));
    //waktu
    jam = new QTimer(this);
    connect(jam, SIGNAL(timeout()),this, SLOT(showTime()));
    jam->start();
    date = QDate::currentDate();
    dateTimeText = date.toString();
    //count=0;
}

void EchoClient::showTime()
{
    QTime time = QTime::currentTime();
    time_text = time.toString("hh:mm:ss:z");
}

void EchoClient::onConnected()
{
    connect(&m_webSocket, &QWebSocket::binaryMessageReceived,this, &EchoClient::onBinMessageReceived);
    qDebug() << "____--WebSocket terhubung--____";

     kanal1 += qs;
     m_webSocket.sendBinaryMessage(kanal1);
}

void EchoClient::onBinMessageReceived(QByteArray message)
{
    for(int i=0; i<2560; i++)
    {
        memcpy(&outValue, message.data(), 2560 * sizeof(float));
        qDebug("%f", outValue[i]);
        //qDebug()<<"terima data";
    }
    qDebug()<<"terima data----------------------------------------**//";
}



