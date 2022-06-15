#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebSocket>

#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_plot_grid.h"
#include <QTimer>
#include "datasetup.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <QDate>
#include <QString>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>

//#include "libme/fft/fourier.h"
//#include "libme/windowing/buat_filter.h"
//#include "libme/windowing/windowkan.h"
//#include "signalprocessing.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void tampil();
    void init_time();
    void init_graph();
    void onBinMessageReceived(QString message);
    void init_websoc();
    void hapus();

    double y_preprosesing_data1[PAKET_10];
    double y_preprosesing_data2[PAKET_10];
    double y_preprosesing_data3[PAKET_10];
    double y_preprosesing_data4[PAKET_10];

    double x1[PAKET_10];
    double x2[PAKET_10];
    double x3[PAKET_10];
    double x4[PAKET_10];

    QwtPlot plot1;
    QwtPlot plot2;
    QwtPlot plot3;
    QwtPlot plot4;
    QwtPlotCurve *curve1;
    QwtPlotCurve *curve2;
    QwtPlotCurve *curve3;
    QwtPlotCurve *curve4;
    QwtPlotGrid *grid1;
    QwtPlotGrid *grid2;
    QwtPlotGrid *grid3;
    QwtPlotGrid *grid4;


    int spsip1;
    int flagcount;

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();

private:
    Ui::MainWindow *ui;
    QWebSocket m_webSocket;
    int count;
    QString qs = "bisa";
    QByteArray ip1;
    QTimer *timer;
};
#endif // MAINWINDOW_H
