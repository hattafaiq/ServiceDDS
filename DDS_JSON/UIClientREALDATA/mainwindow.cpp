#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qwt_legend.h"
#include "datasetup.h"
#include "QWebSocket"

#include "qwt_plot_curve.h"
#include "qwt_plot_grid.h"

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
    this->setWindowTitle(DEF_JUDUL);
    this->init_websoc();
   // this->init_time();
    this->init_graph();
   // this->tampil();
    ui->horizontalLayout1->addWidget(&plot1);
//    ui->horizontalLayout2->addWidget(&plot2);
//    ui->horizontalLayout3->addWidget(&plot3);
//    ui->horizontalLayout4->addWidget(&plot4);
    this->setMinimumSize(800,600);
    this->setMaximumSize(1366,768);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete curve1;
    delete grid1;
}

void MainWindow::init_websoc()
{
    connect(&m_webSocket, &QWebSocket::connected, this, &MainWindow::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &MainWindow::closed);
    m_webSocket.open(QUrl(QStringLiteral("ws://localhost:1234")));
}

void MainWindow::hapus()
{
    //delete ui;
    delete timer;
}

void MainWindow::init_graph()
{
    curve1 = new QwtPlotCurve();
    grid1 = new QwtPlotGrid();
    qDebug()<<QDateTime::currentSecsSinceEpoch();
    QString sb_y_title1;
    QString sb_x_title1;
    sb_y_title1 = QString("Vib. Acc (G)");
    sb_x_title1 = QString("Time (ms)");

    QwtText kiri1;
    kiri1.setText(sb_y_title1);
    kiri1.setFont(QFont("Helvetica", 10));
    kiri1.setColor( Qt::red);

    QwtText bawah1;
    bawah1.setText(sb_x_title1);
    bawah1.setFont(QFont("Helvetica", 10));
    bawah1.setColor( Qt::red );

    QString jdl1;
    jdl1.append(QString("Channel: 1 \n"));
    jdl1.append(QString("RMS = %1, PK = %2, PK-PK = %3"));

    qDebug()<<"judul grafik = "<<jdl1;
    QwtText titles1;
    titles1.setText(jdl1);
    titles1.setFont(QFont("Heletica", 9, 2, false));

    plot1.setAxisTitle(QwtPlot::xBottom, bawah1);
    plot1.setAxisTitle(QwtPlot::yLeft, kiri1);
    plot1.setTitle(titles1);
    plot1.setCanvasBackground( Qt::white);
    plot1.setAxisAutoScale(QwtPlot::yLeft, true);
    grid1->attach( &plot1 );
    grid1->setMajorPen(QPen(Qt::gray, 0, Qt::DotLine));

    curve1->setPen( Qt::blue, 1 );
}

void MainWindow::tampil()
{
    qDebug("%s()", __FUNCTION__);


    curve1->detach();
    curve1->setRawSamples(x1s,y_preprosesing_data1s,2560);
    curve1->attach( &plot1 );



    qDebug()<<"tampil data "<< QDateTime::currentSecsSinceEpoch() <<" ----------------------------------------**//";
}

void MainWindow::init_time()
{
    qDebug("%s()", __FUNCTION__);
    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this, SLOT(tampil()));
    //timer->start(100);
}

void MainWindow::onBinMessageReceived(QString message)
{
    qDebug("%s()", __FUNCTION__);
    QJsonArray jsonArray1;// parsing ip1 kanal1
//    QJsonArray jsonArray2;//
//    QJsonArray jsonArray3;//
//    QJsonArray jsonArray4;// parsing ip1 kanal4
    QJsonObject rootObject;//
    QJsonValue response;//
    QJsonObject responseObj;// judul json
    itemDoc = QJsonDocument::fromJson(message.toUtf8());
    rootObject = itemDoc.object();
    response = rootObject.value("ip1");
    responseObj = response.toObject();
    jsonArray1 = responseObj["kanal1"].toArray();
//    jsonArray2 = responseObj["kanal2"].toArray();
//    jsonArray3 = responseObj["kanal3"].toArray();
//    jsonArray4 = responseObj["kanal4"].toArray();
    spsip1 = responseObj["spsip1"].toInt();
   // double sps= (double) spsip1 ;
    int flag=0;
    flagcount++;
    flag++;
    qDebug() << QDateTime::currentMSecsSinceEpoch()<< " sps  : " << spsip1 << "data masuk ke= "<< flagcount;
    //catatan fleksibel antara data yang dikirim dan yang diterima berdasarkan sps;
//    memcpy(y_preprosesing_data1,jsonArray1, 2560 * sizeof(double));
    memset(&y_preprosesing_data1,'\0',2560*8);
    memset(&y_preprosesing_data1s,'\0',2560*8);
    memset(&x1s,'\0',2560*8);
    memset(&x1,'\0',2560*8);

    for(int i=0; i<2560; i++)//sps
    {
       // y_preprosesing_data1.push_back(jsonArray1[i].toDouble());
        y_preprosesing_data1[i] = jsonArray1[i].toDouble();
//        y_preprosesing_data2[i] = jsonArray2[i].toDouble();
//        y_preprosesing_data3[i] = jsonArray3[i].toDouble();
//        y_preprosesing_data4[i] = jsonArray4[i].toDouble();
        //x1.push_back(i*(1000/(double)spsip1));
        x1[i]=i*(1000/(double)spsip1);
//        x2[i]=i*(1000/(double)spsip1);
//        x3[i]=i*(1000/(double)spsip1);
//        x4[i]=i*(1000/(double)spsip1);
    }
    memcpy(&y_preprosesing_data1s, y_preprosesing_data1, 2560 * sizeof(double));
    memcpy(&x1s, x1, 2560 * sizeof(double));
    qint64 start= QDateTime::currentMSecsSinceEpoch();
    tampil();
    plot1.replot();
    qint64 end= QDateTime::currentMSecsSinceEpoch();

    qDebug() << end <<start <<end-start<<"ms";
}

void MainWindow::onConnected()
{
    qDebug("%s()", __FUNCTION__);
    connect(&m_webSocket, &QWebSocket::textMessageReceived,this, &MainWindow::onBinMessageReceived);
    qDebug() << "____--WebSocket terhubung--____";
    m_webSocket.sendTextMessage(qs);
}







