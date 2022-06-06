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
    this->init_websoc();
    this->init_graph();
    this->tampil();
    ui->horizontalLayout->addWidget(&plot1);
    ui->horizontalLayout_2->addWidget(&plot2);
    ui->horizontalLayout_3->addWidget(&plot3);
    ui->horizontalLayout_4->addWidget(&plot4);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete curve1;
    delete curve2;
    delete curve3;
    delete curve4;
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

    plot1.setAxisTitle(QwtPlot::xBottom, bawah1);
    plot1.setAxisTitle(QwtPlot::yLeft, kiri1);

    QString jdl1;
    jdl1.append(QString("Channel: 1 \n"));
    jdl1.append(QString("RMS = %1, PK = %2, PK-PK = %3"));

    qDebug()<<"judul grafik = "<<jdl1;
    QwtText titles1;
    titles1.setText(jdl1);
    titles1.setFont(QFont("Heletica", 9, 2, false));

    plot1.setTitle(titles1);
    plot1.setCanvasBackground( Qt::white);
    plot1.setAxisAutoScale(QwtPlot::yLeft, true);
    curve1 = new QwtPlotCurve();
    grid1 = new QwtPlotGrid();
    grid1->setMajorPen(QPen(Qt::gray, 0, Qt::DotLine));
    grid1->attach( &plot1 );
    curve1->attach( &plot1 );
   // plot1.show();

    QString sb_y_title2;
    QString sb_x_title2;
    sb_y_title2 = QString("Vib. Acc (G)");
    sb_x_title2 = QString("Time (ms)");

    QwtText kiri2;
    kiri2.setText(sb_y_title2);
    kiri2.setFont(QFont("Helvetica", 10));
    kiri2.setColor( Qt::red);

    QwtText bawah2;
    bawah2.setText(sb_x_title2);
    bawah2.setFont(QFont("Helvetica", 10));
    bawah2.setColor( Qt::red );

    plot2.setAxisTitle(QwtPlot::xBottom, bawah2);
    plot2.setAxisTitle(QwtPlot::yLeft, kiri2);

    QString jdl2;
    jdl2.append(QString("Channel: 2 \n"));
    jdl2.append(QString("RMS = %1, PK = %2, PK-PK = %3"));

    qDebug()<<"judul grafik = "<<jdl2;
    QwtText titles2;
    titles2.setText(jdl2);
    titles2.setFont(QFont("Heletica", 9, 2, false));

    plot2.setTitle(titles2);
    plot2.setCanvasBackground( Qt::white );
    plot2.setAxisAutoScale(QwtPlot::yLeft, true);
    curve2 = new QwtPlotCurve();
    grid2 = new QwtPlotGrid();
    grid2->setMajorPen(QPen(Qt::gray, 0, Qt::DotLine));
    grid2->attach( &plot2 );
    curve2->attach( &plot2 );
   // plot2.show();

    QString sb_y_title3;
    QString sb_x_title3;
    sb_y_title3 = QString("Vib. Acc (G)");
    sb_x_title3 = QString("Time (ms)");

    QwtText kiri3;
    kiri3.setText(sb_y_title3);
    kiri3.setFont(QFont("Helvetica", 10));
    kiri3.setColor( Qt::red);

    QwtText bawah3;
    bawah3.setText(sb_x_title3);
    bawah3.setFont(QFont("Helvetica", 10));
    bawah3.setColor( Qt::red );

    plot3.setAxisTitle(QwtPlot::xBottom, bawah3);
    plot3.setAxisTitle(QwtPlot::yLeft, kiri3);

    QString jdl3;
    jdl3.append(QString("Channel: 3 \n"));
    jdl3.append(QString("RMS = %1, PK = %2, PK-PK = %3"));

    qDebug()<<"judul grafik = "<<jdl3;
    QwtText titles3;
    titles3.setText(jdl3);
    titles3.setFont(QFont("Heletica", 9, 2, false));

    plot3.setTitle(titles3);
    plot3.setCanvasBackground( Qt::white );
    plot3.setAxisAutoScale(QwtPlot::yLeft, true);
    curve3 = new QwtPlotCurve();
    grid3 = new QwtPlotGrid();
    grid3->setMajorPen(QPen(Qt::gray, 0, Qt::DotLine));
    grid3->attach( &plot3 );
    curve3->attach( &plot3 );
//    plot1.show();

    QString sb_y_title4;
    QString sb_x_title4;
    sb_y_title4 = QString("Vib. Acc (G)");
    sb_x_title4 = QString("Time (ms)");

    QwtText kiri4;
    kiri4.setText(sb_y_title4);
    kiri4.setFont(QFont("Helvetica", 10));
    kiri4.setColor( Qt::red);

    QwtText bawah4;
    bawah4.setText(sb_x_title4);
    bawah4.setFont(QFont("Helvetica", 10));
    bawah4.setColor( Qt::red );

    plot4.setAxisTitle(QwtPlot::xBottom, bawah4);
    plot4.setAxisTitle(QwtPlot::yLeft, kiri4);

    QString jdl4;
    jdl4.append(QString("Channel: 4 \n"));
    jdl4.append(QString("RMS = %1, PK = %2, PK-PK = %3"));

    qDebug()<<"judul grafik = "<<jdl4;
    QwtText titles4;
    titles4.setText(jdl4);
    titles4.setFont(QFont("Heletica", 9, 2, false));

    plot4.setTitle(titles4);
    plot4.setCanvasBackground( Qt::white );
    plot4.setAxisAutoScale(QwtPlot::yLeft, true);
    curve4 = new QwtPlotCurve();
    grid4 = new QwtPlotGrid();
    grid4->setMajorPen(QPen(Qt::gray, 0, Qt::DotLine));
    grid4->attach( &plot4 );
    curve4->attach( &plot4 );
//    plot1.show();

}

void MainWindow::tampil()
{
    curve1->setPen( Qt::blue, 1 );
    curve1->setSamples(x1,y_preprosesing_data1,2560);
    //plot1.resize( 420, 250);
    plot1.replot();

    curve2->setPen( Qt::blue, 1 );
    curve2->setSamples(x2,y_preprosesing_data2,2560);
  //  plot2.resize( 420, 250);
    plot2.replot();

    curve3->setPen( Qt::blue, 1 );
    curve3->setSamples(x3,y_preprosesing_data3,2560);
  //  plot3.resize( 420, 250);
    plot3.replot();

    curve4->setPen( Qt::blue, 1 );
    curve4->setSamples(x4,y_preprosesing_data4,2560);
   // plot4.resize( 420, 250);
    plot4.replot();

//    QHBoxLayout *layout1 = new QHBoxLayout();
//    QHBoxLayout *layout2 = new QHBoxLayout();
//    QHBoxLayout *layout3 = new QHBoxLayout();
//    QHBoxLayout *layout4 = new QHBoxLayout();

//    layout1->addWidget(&plot1);
//    layout2->addWidget(&plot2);
//    layout3->addWidget(&plot3);
//    layout4->addWidget(&plot4);

//    mainLayout1 = new QHBoxLayout();
//    mainLayout2 = new QHBoxLayout();
//    mainLayout3 = new QHBoxLayout();
//    mainLayout4 = new QHBoxLayout();

//    mainLayout1->addLayout(layout1);
//    mainLayout2->addLayout(layout2);
//    mainLayout3->addLayout(layout3);
//    mainLayout4->addLayout(layout4);

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
    jsonArray1 = responseObj["kanal1"].toArray();
    jsonArray2 = responseObj["kanal2"].toArray();
    jsonArray3 = responseObj["kanal3"].toArray();
    jsonArray4 = responseObj["kanal4"].toArray();
    //sps=
    //2560 = sps
    //catatan fleksibel antara data yang dikirim dan yang diterima berdasarkan sps;
    for(int i=0; i<2560; i++)//sps
    {
        y_preprosesing_data1[i] = jsonArray1[i].toDouble();
        y_preprosesing_data2[i] = jsonArray2[i].toDouble();
        y_preprosesing_data3[i] = jsonArray3[i].toDouble();
        y_preprosesing_data4[i] = jsonArray4[i].toDouble();
        //x1[i]=i*1/sps;
        x1[i]=i;
        x2[i]=i;
        x3[i]=i;
        x4[i]=i;
    }
    tampil();
}

void MainWindow::onConnected()
{
    connect(&m_webSocket, &QWebSocket::binaryMessageReceived,this, &MainWindow::onBinMessageReceived);
    qDebug() << "____--WebSocket terhubung--____";
    ip1 += qs;
    m_webSocket.sendBinaryMessage(ip1);
}







