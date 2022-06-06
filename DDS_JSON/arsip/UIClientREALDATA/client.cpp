#include "client.h"
#include "datasetup.h"
#include "QWebSocket"
#include "qwt_plot_curve.h"
#include "qwt_legend.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>


QT_USE_NAMESPACE

EchoClient::EchoClient(QObject *parent) :
    QObject(parent)
{
    //websocket
    connect(&m_webSocket, &QWebSocket::connected, this, &EchoClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &EchoClient::closed);
    m_webSocket.open(QUrl(QStringLiteral("ws://localhost:1234")));
    //waktu
    jam = new QTimer(this);
    connect(jam, SIGNAL(timeout()),this, SLOT(showTime()));
    jam->start();
    date = QDate::currentDate();
    dateTimeText = date.toString();
   // init grafik
    plot.setTitle( "Plot Demo" );
    plot.setCanvasBackground( Qt::white );
    plot.insertLegend( new QwtLegend() );
    plot.setAxisAutoScale(QwtPlot::yLeft, true);
    curve = new QwtPlotCurve();
    curve->attach( &plot );
    plot.show();
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
//////////////////////////////////////////////////////////////////////////////////
//void EchoClient::onBinMessageReceived(QByteArray message)
//{
//    memcpy(&outValue, message.data(), 2560 * sizeof(float));
//    int i=0;
//    for(i=0; i<2560; i++)
//    {
//        y_preprosesing_data[i] = (double) outValue[i];
//       //qDebug("%f",  y_preprosesing_data[i]);
//        x[i]=i;
//    }
//    qDebug()<<"terima data------------------------------>>>>>>>>>>>>";
//    tampil();
//}
//////////////////////////////////////////////////////////////////////////////////

void EchoClient::onBinMessageReceived(QByteArray message)
{
    itemDoc = QJsonDocument::fromJson(message);
    rootObject = itemDoc.object();
    response = rootObject.value("ip1");
    responseObj = response.toObject();
    jsonArray = responseObj["kanal1"].toArray();

    //QJsonObject responseObj2 = response2.toObject();
//    for(int i=0; i<2560; i++)
//    {
//        qDebug() << jsonArray[i];
//    }

    for(int i=0; i<2560; i++)
    {
        y_preprosesing_data[i] = jsonArray[i].toDouble();
        //qDebug("%f",  y_preprosesing_data[i]);
        x[i]=i;
    }
    tampil();
}

///////////////////////////////////////////////////////////////////////////////////
void EchoClient::tampil()
{
    curve->setPen( Qt::blue, 2 );
    for(int i=0; i<2560; i++)
    {
        //qDebug()<<y_preprosesing_data[i];
    }
    curve->setSamples(x,y_preprosesing_data,2560);
    plot.resize( 600, 400 );
    plot.replot();
    qDebug()<<"tampil data----------------------------------------**//";
}
////////////////////////////////////////////////////////////////////////////////////
void EchoClient::init_time()
{
    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this, SLOT(tampil()));
    timer->start(2000);
}






