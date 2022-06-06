#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebSocket>
#include <QTimer>
#include <QDate>
#include <QString>
#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_plot_grid.h"
#include <QTimer>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>


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
    void onBinMessageReceived(QByteArray message);
    void init_websoc();

    double y_preprosesing_data1[2560];
    double y_preprosesing_data2[2560];
    double y_preprosesing_data3[2560];
    double y_preprosesing_data4[2560];
    double x1[2560];
    double x2[2560];
    double x3[2560];
    double x4[2560];
    double data_tampil[2560];
    float outValue[2560];

    QwtPlotCurve *curve1;
    QwtPlotCurve *curve2;
    QwtPlotCurve *curve3;
    QwtPlotCurve *curve4;
    QwtPlotGrid *grid1;
    QwtPlotGrid *grid2;
    QwtPlotGrid *grid3;
    QwtPlotGrid *grid4;
    QwtPlot plot1;
    QwtPlot plot2;
    QwtPlot plot3;
    QwtPlot plot4;
    QHBoxLayout *mainLayout1;
    QHBoxLayout *mainLayout2;
    QHBoxLayout *mainLayout3;
    QHBoxLayout *mainLayout4;

    QHBoxLayout *layout1;
    QHBoxLayout *layout2;
    QHBoxLayout *layout3;
    QHBoxLayout *layout4;

    QJsonDocument itemDoc;// = QJsonDocument::fromJson(message);
    QJsonObject rootObject;// = itemDoc.object();

    QJsonValue response;// = rootObject.value("ip1");
    QJsonObject responseObj;// = response.toObject();
    QJsonArray jsonArray1;// = responseObj["kanal1"].toArray();
    QJsonArray jsonArray2;// = responseObj["kanal2"].toArray();
    QJsonArray jsonArray3;// = responseObj["kanal3"].toArray();
    QJsonArray jsonArray4;// = responseObj["kanal4"].toArray();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();

private:
    Ui::MainWindow *ui;
    QWebSocket m_webSocket;
    int count;
    //////
    QString qs = "bisa";
    QByteArray ip1;
    bool topik=false;
    QTimer *timer;

};
#endif // MAINWINDOW_H
