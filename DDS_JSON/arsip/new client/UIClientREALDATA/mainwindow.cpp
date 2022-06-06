#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qwt_legend.h"
#include "datasetup.h"
#include "QWebSocket"

#include "qwt_plot_curve.h"
#include "qwt_legend.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->init_websoc();
    this->init_graph();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete curve;
    delete timer;
}

void MainWindow::init_websoc()
{
    connect(&m_webSocket, &QWebSocket::connected, this, &MainWindow::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &MainWindow::closed);
    m_webSocket.open(QUrl(QStringLiteral("ws://localhost:1234")));
}

void MainWindow::init_graph()
{
    //catatan curvenya bikin 4 masuk ke 1 plot
    plot.setTitle( "Plot Demo" );
    plot.setCanvasBackground( Qt::white );
    plot.insertLegend( new QwtLegend() );
    plot.setAxisAutoScale(QwtPlot::yLeft, true);
    curve = new QwtPlotCurve();
    curve->attach( &plot );
    plot.show();
}

void MainWindow::tampil()
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

void MainWindow::init_time()
{
    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this, SLOT(initgraf()));
    timer->start(2000);
}

void MainWindow::onBinMessageReceived(QByteArray message)
{
    itemDoc = QJsonDocument::fromJson(message);
    rootObject = itemDoc.object();
    response = rootObject.value("ip1");
    responseObj = response.toObject();
    jsonArray = responseObj["kanal1"].toArray();

    for(int i=0; i<2560; i++)
    {
        y_preprosesing_data[i] = jsonArray[i].toDouble();
        //qDebug("%f",  y_preprosesing_data[i]);
        x[i]=i;
    }
    tampil();
}

void MainWindow::onConnected()
{
    connect(&m_webSocket, &QWebSocket::binaryMessageReceived,this, &MainWindow::onBinMessageReceived);
    qDebug() << "____--WebSocket terhubung--____";
    kanal1 += qs;
    m_webSocket.sendBinaryMessage(kanal1);
}







