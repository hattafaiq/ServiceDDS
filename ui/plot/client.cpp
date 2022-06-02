#include "client.h"
#include "qwt_plot_curve.h"
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>

QT_USE_NAMESPACE

EchoClient::EchoClient(QObject *parent) :
    QObject(parent)
{
tampil();
}

void EchoClient::tampil()
{
plot.setTitle( "Plot Demo" );
plot.setCanvasBackground( Qt::white );
plot.insertLegend( new QwtLegend() );
plot.setAxisAutoScale(QwtPlot::yLeft, true);

//    QwtPlotGrid *grid = new QwtPlotGrid();
//    grid->attach( &plot );

QwtPlotCurve *curve = new QwtPlotCurve();
//    curve->setTitle( "Some Points" );
curve->setPen( Qt::blue, 1 );
double x[260] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259};
double y[26] = {0.00946552, //1
            3.461464, //2
            3.886914, //3
            6.25868, //4
            6.55448, //5
            6.75798, //6
            6.85614, //7
            6.84294, //8
            6.71865, //9
            6.49158, //10
            6.17539, //11
            3.788496, //12
            3.354395, //13
            -3.0999957, //14
            -3.54802, //15
            -3.963751, //16
            -6.32082, //17
            -6.5991, // 18
            -6.78132, //19
            -6.85525, //20
            -6.81807, //21
            -6.671, //22
            -6.42267, //23
            -6.08954, //24
            -3.690939, //25
            -3.250468};
double ay[260];
int counter;
counter++;
    if (counter <10){
        for (int i=0; i<26; i++)
        {
          ay[(counter-1)*(260+i)]=y[i%26];
        }
    }
    counter=0;

    for (int a=0; a<260; a++){
        qDebug()<< "data ke: " << a << " = " <<ay[a];
    }
//curve->setSamples(x,ay,260);
//curve->attach( &plot );
//plot.resize( 600, 400 );
//plot.show();
}

void EchoClient::init_time()
{
    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this, SLOT(tampil()));
    timer->start(2200);
}



