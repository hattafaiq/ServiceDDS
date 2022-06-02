#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "qwt_plot_curve.h"
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    timer = new QTimer(this);
//    QObject::connect(timer,SIGNAL(timeout()),this, SLOT(tampil()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::tampil()
{
    plot->setTitle( "Plot Demo" );
    plot->setCanvasBackground( Qt::white );
    plot->insertLegend( new QwtLegend() );
    plot->setAxisAutoScale(QwtPlot::yLeft, true);

    QwtPlotCurve *curve = new QwtPlotCurve();
    curve->setPen( Qt::blue, 1 );
    //int a;

        counter++;
        for(int a=0; a<200; a++) //size
        {
            ay[a]=y[a%26];
            qDebug()<<ay[a] << " : " << a;
            //break;
        }
        counter=0;
        curve->setSamples(x,ay,200); //size
        curve->attach(plot);

//    plot.resize( 600, 400 );
        plot->replot();
       // plot.show();


//    timer->start(500);
//    qDebug()<<"re plot";
}

void MainWindow::init_time()
{
    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this, SLOT(tampil()));
   // timer->start(100);
    //qDebug()<<"re plot";
}

void MainWindow::data()
{

}



