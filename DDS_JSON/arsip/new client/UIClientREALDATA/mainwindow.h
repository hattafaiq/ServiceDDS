#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebSocket>
#include <QTimer>
#include <QDate>
#include <QString>
#include "qwt_plot.h"
#include "qwt_plot_curve.h"
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

    double y_preprosesing_data[2560];
    double x[2560];
    double data_tampil[2560];
    float outValue[2560];

    QwtPlotCurve *curve;
    QJsonDocument itemDoc;// = QJsonDocument::fromJson(message);
    QJsonObject rootObject;// = itemDoc.object();

    QJsonValue response;// = rootObject.value("ip1");
    QJsonObject responseObj;// = response.toObject();
    QJsonArray jsonArray;// = responseObj["kanal1"].toArray();

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
    QByteArray kanal1;
    bool topik=false;
    QwtPlot plot;
    QTimer *timer;
    QHBoxLayout *hbox;



};
#endif // MAINWINDOW_H
