#include "mainwindow.h"
#include <QApplication>
#include "client.h"
#include "qwt_plot_curve.h"
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    EchoClient client(QUrl(QStringLiteral("ws://localhost:1234")));
//    QObject::connect(&client, &EchoClient::closed, &a, &QCoreApplication::quit);
//    MainWindow w;
//    w.tampil();
    QwtPlot plot;
    plot.setTitle( "Plot Demo" );
    plot.setCanvasBackground( Qt::white );
    plot.insertLegend( new QwtLegend() );
    plot.setAxisAutoScale(QwtPlot::yLeft, true);

//    QwtPlotGrid *grid = new QwtPlotGrid();
//    grid->attach( &plot );

      QwtPlotCurve *curve = new QwtPlotCurve();
//    curve->setTitle( "Some Points" );
      curve->setPen( Qt::blue, 1 );

    double x[256] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255};
    double y[256] = {0.00946552,
                    0.461464,
                    0.886914,
                    1.25868,
                    1.55448,
                    1.75798,
                    1.85614,
                    1.84294,
                    1.71865,
                    1.49158,
                    1.17539,
                    0.788496,
                    0.354395,
                    -0.0999957,
                    -0.54802,
                    -0.963751,
                    -1.32082,
                    -1.5991,
                    -1.78132,
                    -1.85525,
                    -1.81807,
                    -1.671,
                    -1.42267,
                    -1.08954,
                    -0.690939,
                    -0.250468,
                    0.204832,
                    0.648951,
                    1.05429,
                    1.39604,
                    1.65419,
                    1.81347,
                    1.86414,
                    1.80255,
                    1.6327,
                    1.36535,
                    1.01627,
                    0.606138,
                    0.159634,
                    -0.295273,
                    -0.732857,
                    -1.12637,
                    -1.45159,
                    -1.69069,
                    -1.82717,
                    -1.85338,
                    -1.76838,
                    -1.57604,
                    -1.28905,
                    -0.925112,
                    -0.504512,
                    -0.0541794,
                    0.399331,
                    0.830243,
                    1.21126,
                    1.51862,
                    1.7358,
                    1.84922,
                    1.85148,
                    1.74236,
                    1.52887,
                    1.22421,
                    0.845891,
                    0.416591,
                    -0.0366893,
                    -0.48733,
                    -0.909534,
                    -1.27604,
                    -1.56621,
                    -1.76283,
                    -1.85212,
                    -1.83037,
                    -1.69828,
                    -1.46309,
                    -1.14026,
                    -0.749188,
                    -0.31265,
                    0.142176,
                    0.589159,
                    1.00139,
                    1.35327,
                    1.62398,
                    1.79792,
                    1.86384,
                    1.81775,
                    1.66231,
                    1.40771,
                    1.06899,
                    0.665588,
                    0.222395,
                    -0.232905,
                    -0.674397,
                    -1.07554,
                    -1.41147,
                    -1.66339,
                    -1.8149,
                    -1.85665,
                    -1.78699,
                    -1.60892,
                    -1.33392,
                    -0.979468,
                    -0.565161,
                    -0.117087,
                    0.337583,
                    0.773188,
                    1.16237,
                    1.4811,
                    1.71149,
                    1.83993,
                    1.85773,
                    1.76375,
                    1.56396,
                    1.27126,
                    0.901724,
                    0.477987,
                    0.0263482,
                    -0.426027,
                    -0.853501,
                    -1.22914,
                    -1.53104,
                    -1.74142,
                    -1.8463,
                    -1.83998,
                    -1.72276,
                    -1.50086,
                    -1.18939,
                    -0.806752,
                    -0.375105,
                    0.0787571,
                    0.528564,
                    0.947481,
                    1.30901,
                    1.59199,
                    1.77994,
                    1.86141,
                    1.83075,
                    1.68994,
                    1.44823,
                    1.12009,
                    0.724286,
                    0.284974,
                    -0.170093,
                    -0.615042,
                    -1.02345,
                    -1.36938,
                    -1.63402,
                    -1.80015,
                    -1.85745,
                    -1.80326,
                    -1.6396,
                    -1.37697,
                    -1.03244,
                    -0.624989,
                    -0.180122,
                    0.274988,
                    0.71472,
                    1.11181,
                    1.44173,
                    1.68511,
                    1.82833,
                    1.86176,
                    1.78316,
                    1.59744,
                    1.31652,
                    0.956762,
                    0.53905,
                    0.0895056,
                    -0.364158,
                    -0.796813,
                    -1.18108,
                    -1.49424,
                    -1.71837,
                    -1.83842,
                    -1.84749,
                    -1.74558,
                    -1.53754,
                    -1.23733,
                    -0.863219,
                    -0.436742,
                    0.0156739,
                    0.467394,
                    0.892409,
                    1.26343,
                    1.55844,
                    1.76061,
                    1.85707,
                    1.84209,
                    1.71648,
                    1.48777,
                    1.17011,
                    0.782464,
                    0.347641,
                    -0.106911,
                    -0.554882,
                    -0.970106,
                    -1.32614,
                    -1.60309,
                    -1.78373,
                    -1.85596,
                    -1.81718,
                    -1.66834,
                    -1.41859,
                    -1.08421,
                    -0.684296,
                    -0.242842,
                    0.212611,
                    0.656112,
                    1.06087,
                    1.40133,
                    1.65781,
                    1.81553,
                    1.8643,
                    1.80108,
                    1.62951,
                    1.36077,
                    1.0107,
                    0.599501,
                    0.152691,
                    -0.302225,
                    -0.739344,
                    -1.13206,
                    -1.45606,
                    -1.69347,
                    -1.82822,
                    -1.85254,
                    -1.76563,
                    -1.57164,
                    -1.28335,
                    -0.918321,
                    -0.497865,
                    -0.0476742,
                    0.405981,
                    0.836262,
                    1.21617,
                    1.52284,
                    1.73846,
                    1.85009,
                    1.85048,
                    1.73976,
                    1.52462,1.21859,0.839363,0.409437,-0.0438341,-0.494163,-0.915425,-1.28116,-1.57007,-1.76503,-1.85275,-1.82928,-1.69552,-1.45853,-1.1349,-0.74259,-0.30497,};

    curve->setSamples(x,y,256);

    curve->attach( &plot );

    plot.resize( 600, 400 );

    plot.show();
    return a.exec();
}
