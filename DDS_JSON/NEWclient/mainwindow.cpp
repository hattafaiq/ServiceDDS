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
    ui->horizontalLayout2->addWidget(&plot2);
    ui->horizontalLayout3->addWidget(&plot3);
    ui->horizontalLayout4->addWidget(&plot4);
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
    curve2 = new QwtPlotCurve();
    grid2 = new QwtPlotGrid();
    curve3 = new QwtPlotCurve();
    grid3 = new QwtPlotGrid();
    curve4 = new QwtPlotCurve();
    grid4 = new QwtPlotGrid();

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

   // qDebug()<<"judul grafik = "<<jdl1;
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
#if 1
    QString jdl2;
    jdl2.append(QString("Channel: 2 \n"));
    jdl2.append(QString("RMS = %1, PK = %2, PK-PK = %3"));
   // qDebug()<<"judul grafik = "<<jdl1;
    QwtText titles2;
    titles2.setText(jdl2);
    titles2.setFont(QFont("Heletica", 9, 2, false));
    plot2.setAxisTitle(QwtPlot::xBottom, bawah1);
    plot2.setAxisTitle(QwtPlot::yLeft, kiri1);
    plot2.setTitle(titles2);
    plot2.setCanvasBackground( Qt::white);
    plot2.setAxisAutoScale(QwtPlot::yLeft, true);
    grid2->attach( &plot2 );
    grid2->setMajorPen(QPen(Qt::gray, 0, Qt::DotLine));
    curve2->setPen( Qt::blue, 1 );

    QString jdl3;
    jdl3.append(QString("Channel: 3 \n"));
    jdl3.append(QString("RMS = %1, PK = %2, PK-PK = %3"));
    QwtText titles3;
    titles3.setText(jdl3);
    titles3.setFont(QFont("Heletica", 9, 2, false));
    plot3.setAxisTitle(QwtPlot::xBottom, bawah1);
    plot3.setAxisTitle(QwtPlot::yLeft, kiri1);
    plot3.setTitle(titles3);
    plot3.setCanvasBackground( Qt::white);
    plot3.setAxisAutoScale(QwtPlot::yLeft, true);
    grid3->attach( &plot3 );
    grid3->setMajorPen(QPen(Qt::gray, 0, Qt::DotLine));
    curve3->setPen( Qt::blue, 1 );

    QString jdl4;
    jdl4.append(QString("Channel: 3 \n"));
    jdl4.append(QString("RMS = %1, PK = %2, PK-PK = %3"));
    QwtText titles4;
    titles4.setText(jdl4);
    titles4.setFont(QFont("Heletica", 9, 2, false));
    plot4.setAxisTitle(QwtPlot::xBottom, bawah1);
    plot4.setAxisTitle(QwtPlot::yLeft, kiri1);
    plot4.setTitle(titles4);
    plot4.setCanvasBackground( Qt::white);
    plot4.setAxisAutoScale(QwtPlot::yLeft, true);
    grid4->attach( &plot4 );
    grid4->setMajorPen(QPen(Qt::gray, 0, Qt::DotLine));
    curve4->setPen( Qt::blue, 1 );
#endif
}

void MainWindow::tampil()
{
    curve1->detach();
    curve2->detach();
    curve3->detach();
    curve4->detach();
    curve1->setRawSamples(x1,y_preprosesing_data1,PAKET_10);
    curve2->setRawSamples(x2,y_preprosesing_data2,PAKET_10);
    curve3->setRawSamples(x3,y_preprosesing_data3,PAKET_10);
    curve4->setRawSamples(x4,y_preprosesing_data4,PAKET_10);
    curve1->attach( &plot1 );
    curve2->attach( &plot2 );
    curve3->attach( &plot3 );
    curve4->attach( &plot4 );
//    qDebug() << "plot----- ";
}

void MainWindow::init_time()
{
    //qDebug("%s()", __FUNCTION__);
    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this, SLOT(tampil()));
    //timer->start(100);
}

void MainWindow::onBinMessageReceived(QString message)
{
   // qDebug("%s()", __FUNCTION__);
    QJsonArray jsonArray1;// parsing ip1 kanal1
    QJsonArray jsonArray2;//
    QJsonArray jsonArray3;//
    QJsonArray jsonArray4;// parsing ip1 kanal4
    QJsonObject rootObject;//
    QJsonValue response;//
    QJsonObject responseObj;// judul json
    QJsonDocument itemDoc;//
    itemDoc = QJsonDocument::fromJson(message.toUtf8());
    rootObject = itemDoc.object();
    response = rootObject.value("ip1");
    responseObj = response.toObject();
    jsonArray1 = responseObj["kanal1"].toArray();
    jsonArray2 = responseObj["kanal2"].toArray();
    jsonArray3 = responseObj["kanal3"].toArray();
    jsonArray4 = responseObj["kanal4"].toArray();
    spsip1 = responseObj["spsip1"].toInt();
   // double sps= (double) spsip1 ;
    int flag=0;
    flagcount++;
    flag++;
   // qDebug() << QDateTime::currentMSecsSinceEpoch()<< " sps  : " << spsip1 << "data masuk ke= "<< flagcount;
    //catatan fleksibel antara data yang dikirim dan yang diterima berdasarkan sps;
//    memcpy(y_preprosesing_data1,jsonArray1, 2560 * sizeof(double));
  //  memset(&y_preprosesing_data1,'\0',2560*8);
  //  memset(&y_preprosesing_data1s,'\0',2560*8);
   // memset(&x1s,'\0',2560*8);
  //  memset(&x1,'\0',2560*8);

    for(int i=0; i<LEN_PLOT; i++)//sps
    {
       // y_preprosesing_data1.push_back(jsonArray1[i].toDouble());
        y_preprosesing_data1[i] = jsonArray1[i].toDouble();
        y_preprosesing_data2[i] = jsonArray2[i].toDouble();
        y_preprosesing_data3[i] = jsonArray3[i].toDouble();
        y_preprosesing_data4[i] = jsonArray4[i].toDouble();
        //x1.push_back(i*(1000/(double)spsip1));
        x1[i]=i*(TIME_FRAME1s/(double)spsip1);
        x2[i]=i*(TIME_FRAME1s/(double)spsip1);
        x3[i]=i*(TIME_FRAME1s/(double)spsip1);
        x4[i]=i*(TIME_FRAME1s/(double)spsip1);
    }
  //  memcpy(&y_preprosesing_data1s, y_preprosesing_data1, 2560 * sizeof(double));
 //   memcpy(&x1s, x1, 2560 * sizeof(double));

    tampil();
    plot1.replot();
    plot2.replot();
    plot3.replot();
    plot4.replot();
}

void MainWindow::onConnected()
{
    //qDebug("%s()", __FUNCTION__);
    connect(&m_webSocket, &QWebSocket::textMessageReceived,this, &MainWindow::onBinMessageReceived);
    qDebug() << "____--WebSocket terhubung--____";
    m_webSocket.sendTextMessage(qs);
}

//memastikan panjang data sudah sesuai







