#ifndef DATA_H
#define DATA_H

#include <QUdpSocket>
#include <QTimer>
#include <QObject>
#include <QList>
#include <QByteArray>
#include <QWebSocket>
#include <QTimer>
#include <QUdpSocket>
#include <QDate>
#include <QString>
#include "QWebSocketServer"
#include "setting.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QSqlDatabase>

class data : public QObject
{
    Q_OBJECT
public:
    QByteArray simpanan;
    explicit data(QObject *parent = nullptr);
    void req_UDP();
    virtual ~data();
    void init_database();
    ///// DDS (data management system)
    /// ip 1
    double ip1_k1_10[2560];
    double ip1_k2_10[2560];
    double ip1_k3_10[2560];
    double ip1_k4_10[2560];
    //ip2
    double ip2_k1_10[2560];
    double ip2_k2_10[2560];
    double ip2_k3_10[2560];
    double ip2_k4_10[2560];
    //// isi dds paket json
    unsigned short spsX;
    int kirim;
    ///////////////////////
//    bool isOpen() const;

//    /**
//     * @brief Creates a new 'people' table if it doesn't already exist
//     * @return true - 'people' table created successfully, false - table not created
//     */
//    bool createTable();

//    /**
//     * @brief Add person data to db
//     * @param name - name of person to add
//     * @return true - person added successfully, false - person not added
//     */
//    bool addPerson(QByteArray masuks);

//    /**
//     * @brief Remove person data from db
//     * @param name - name of person to remove.
//     * @return true - person removed successfully, false - person not removed
//     */
//    bool removePerson(QByteArray masuk);

//    /**
//     * @brief Check if person of name "name" exists in db
//     * @param name - name of person to check.
//     * @return true - person exists, false - person does not exist
//     */
//    bool personExists(QByteArray masuk) const;

//    /**
//     * @brief Print names of all persons in db
//     */
//    void printAllPersons() const;

//    /**
//     * @brief Remove all persons from db
//     * @return true - all persons removed successfully, false - not removed
//     */
//    bool removeAllPersons();




signals:

public slots:
    void readyReady(); //(QByteArray datagram);//data tidak mau masuk
    void init_time();
    void refresh_plot();
    void datamanagement();
    void datamanagement2();

private slots:
    void onNewConnection();
    void processMessage(QString message);
    void socketDisconnected();
    void showTime();
    void sendDataClient1(QString isipesan);
    void sendDataClient2(QString isipesan2);

private:
    int counterCH1;
    int counterCH2;
    int counterCH3;
    int counterCH4;
    int counterCH5;
    int counterCH6;
    int counterCH7;
    int counterCH8;
    ///
    //timer
    QTimer *timer;
    QTimer *timera;
    //websocket
    QWebSocketServer *m_pWebSocketServer1;
    QList<QWebSocket *> CG_NewClient;
    QList<QWebSocket *> CG_PenSub;
    QList<QWebSocket *> Subcribe_wave1;
    QList<QWebSocket *> Subcribe_wave2;

   // QWebSocket *C_angbaru;
   // QWebSocket *UNSUB_Client;
    QWebSocket *ind_Client;
    QWebSocket *C_NewCon;

    QWebSocket *pClient1;
    QWebSocket *pClientkirim;

    QString *datas;
    //date
    QTimer *jam;
    QTimer *timers;
    QDate date;
    QString dateTimeText;
    QString time_text;
    //
    //parsing UDP
    QByteArray datagram;
    quint16 senderPort;
    QHostAddress sendera;
    QUdpSocket *socket;
    int tim_count;
    // inisial data
    float data_y_voltage1[BESAR_PAKET_F];//256 data
    float data_y_voltage2[BESAR_PAKET_F];//256 data
    float data_y_voltage3[BESAR_PAKET_F];//256 data
    float data_y_voltage4[BESAR_PAKET_F];//256 data
    float data_y_voltage5[BESAR_PAKET_F];//256 data
    float data_y_voltage6[BESAR_PAKET_F];//256 data
    float data_y_voltage7[BESAR_PAKET_F];//256 data
    float data_y_voltage8[BESAR_PAKET_F];//256 data
    float data10paket_1[PAKET_10];
    float data10paket_2[PAKET_10];
    float data10paket_3[PAKET_10];
    float data10paket_4[PAKET_10];
    float data10paket_5[PAKET_10];
    float data10paket_6[PAKET_10];
    float data10paket_7[PAKET_10];
    float data10paket_8[PAKET_10];
    // SQL
    QSqlDatabase m_db;
    QString simpanaja;
    static QList<QWebSocket*> plist;


};
#endif // DATA_H
