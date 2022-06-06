#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include <QTimer>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include "qwt_legend.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->tampil();
    ui->verticalLayout->addLayout(mainLayout);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::tampil()
{
    //QwtPlot *plot = new QwtPlot();
    double x[9] = {1,20,30,40,50,60,70,200,500};
    double y[9] = {1,500,3,1,200,100,2,1,0};
    QwtPlotCurve *curve = new QwtPlotCurve();

    plot1.setTitle( "Plot Demo" );
    plot1.setCanvasBackground( Qt::white );
    plot1.insertLegend( new QwtLegend() );
    plot1.setAxisAutoScale(QwtPlot::yLeft, true);

    plot2.setTitle( "Plot Demo" );
    plot2.setCanvasBackground( Qt::white );
    plot2.insertLegend( new QwtLegend() );
    plot2.setAxisAutoScale(QwtPlot::yLeft, true);

    plot3.setTitle( "Plot Demo" );
    plot3.setCanvasBackground( Qt::white );
    plot3.insertLegend( new QwtLegend() );
    plot3.setAxisAutoScale(QwtPlot::yLeft, true);

    plot4.setTitle( "Plot Demo" );
    plot4.setCanvasBackground( Qt::white );
    plot4.insertLegend( new QwtLegend() );
    plot4.setAxisAutoScale(QwtPlot::yLeft, true);

    curve->setPen( Qt::blue, 2 );
    curve->setRawSamples(x,y,9);

    curve->attach( &plot1 );
    curve->attach( &plot2 );
    curve->attach( &plot3 );
    curve->attach( &plot4 );

    curve->show();

    plot1.replot();
    plot2.replot();
    plot3.replot();
    plot4.replot();

//    vbox->addWidget(&plot1);
//    vbox->addWidget(&plot2);
//    vbox->addWidget(&plot3);
//    vbox->addWidget(&plot4);

//    ui->verticalLayout->addWidget(&plot1);
//    ui->verticalLayout->addWidget(&plot2);
//    ui->verticalLayout->addWidget(&plot3);
//    ui->verticalLayout->addWidget(&plot4);
    //plot.show();

       QHBoxLayout *queryLayout1 = new QHBoxLayout();
       queryLayout1->addWidget(&plot1);
       queryLayout1->addWidget(&plot2);
       QHBoxLayout *queryLayout2 = new QHBoxLayout();
       queryLayout2->addWidget(&plot3);
       queryLayout2->addWidget(&plot4);

       mainLayout = new QVBoxLayout();
       mainLayout->addLayout(queryLayout1);
       mainLayout->addLayout(queryLayout2);
       //mainLayout->addWidget(resultView);
      // window.setLayout(mainLayout);
}
