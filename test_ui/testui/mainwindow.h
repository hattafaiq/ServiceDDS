#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

   // QwtPlotCurve *curve;
    QJsonDocument itemDoc;// = QJsonDocument::fromJson(message);
    QJsonObject rootObject;// = itemDoc.object();

    QJsonValue response;// = rootObject.value("ip1");
    QJsonObject responseObj;// = response.toObject();
    QJsonArray jsonArray;// = responseObj["kanal1"].toArray();
    QwtPlot plot1;
    QwtPlot plot2;
    QwtPlot plot3;
    QwtPlot plot4;
    QHBoxLayout *hbox;
    QVBoxLayout *vbox;
    QVBoxLayout *mainLayout;

private:
    Ui::MainWindow *ui;
    //////
    QString qs = "bisa";
    QByteArray kanal1;
    bool topik=false;
    QTimer *timer;

};
#endif // MAINWINDOW_H
