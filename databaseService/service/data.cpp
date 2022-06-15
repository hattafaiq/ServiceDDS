#include "data.h"
#include "setting.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>


data::data(QObject *parent) : QObject(parent)
{
    //INIT_udp
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, 5008);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyReady()));
    //INIT_websocket
    m_pWebSocketServer1 = new QWebSocketServer(QStringLiteral("OVM"),QWebSocketServer::NonSecureMode,this);
    m_pWebSocketServer1->listen(QHostAddress::Any, 1234);
    connect(m_pWebSocketServer1, SIGNAL(newConnection()),this, SLOT(onNewConnection()));
//    init_database();
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("datakuc.db");
}

void data::init_time()
{
    timer = new QTimer(this);
    timera = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this, SLOT(refresh_plot()));
    QObject::connect(timera,SIGNAL(timeout()),this, SLOT(datamanagement()));
    timer->start(TIME_REQ);//2200 // harus sesuai interval berdasarkan sps
}

void data::req_UDP()
{
    QByteArray Data;
    Data.append("getdata");
    socket->writeDatagram(Data,QHostAddress("192.168.0.101"), 5006);
    socket->writeDatagram(Data,QHostAddress("192.168.0.102"), 5006);
    kirim=0;
}

void data::showTime()
{
    QTime time = QTime::currentTime();
    time_text = time.toString("hh:mm:ss:z");
}


void data::readyReady()
{
    struct tt_req2 *p_req2;
    float *p_data;
    int i_kanal;
  // Creates a table if it doens't exist. Otherwise, it will use existing table.


    while (socket->hasPendingDatagrams())
    {

        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size(), &sendera, &senderPort);
        //QHostAddress modul1_ip("192.168.0.101");
        QString ip1 =QString::fromUtf8("192.168.0.101");
        QString ip2 =QString::fromUtf8("192.168.0.102");
        QHostAddress ip_modul_1, ip_modul_2;
        ip_modul_1.setAddress(ip1);
        ip_modul_2.setAddress(ip2);
         p_req2 = (struct tt_req2 *) datagram.data();
         p_data = (float *) p_req2->buf;
         i_kanal = p_req2->cur_kanal;
         spsX = p_req2->sps;

             if(sendera.toIPv4Address() == ip_modul_1.toIPv4Address()) //ip pertama
             {
                // qDebug()<<"ip pertama";
                 // ikut 1 paket
                 if(i_kanal==0)//kanal 1
                 {
                     //qDebug()<<"-KANAL  1-" <<"ip pertama";
                     counterCH1++;
                     qDebug()<<"paket ke "<<counterCH1;
                     if (counterCH1<11)
                     {
                    //mengirim 1o paket kanal 1
                         for(int i=0; i<256; i++)
                             {
                                data_y_voltage1[i]=p_data[i]; //mengirim 1 paket
                                data10paket_1[(counterCH1-1)*256+i]=p_data[i];//tracking data dari 0-2560 per paket data sebanyak 256
                             }
                       }//counter
                     if(counterCH1==10)counterCH1=0;
                 }//kanal 1

                 else if(i_kanal==1)//kanal 2
                 {
                    // qDebug()<<"-KANAL  2-" <<"ip pertama";
                     counterCH2++;
                     if (counterCH2<11)
                     {
                    //mengirim 1o paket kanal 2
                         for(int i=0; i<256; i++)
                             {
                                data_y_voltage2[i]=p_data[i%256]; //mengirim 1 paket
                                data10paket_2[(counterCH2-1)*256+i]=p_data[i%256];//tracking data dari 0-2560 per paket data sebanyak 256

                             }
                     }
                     if(counterCH2==10) counterCH2=0;
                 }//kanal 2
                 else if(i_kanal==2)//kanal 3
                 {
                   //  qDebug()<<"-KANAL  3-" <<"ip pertama";
                     counterCH3++;
                     if (counterCH3<11)
                     {
                    //mengirim 1o paket kanal 3
                         for(int i=0; i<256; i++)
                             {
                                data_y_voltage3[i]=p_data[i%256]; //mengirim 1 paket
                                data10paket_3[(counterCH3-1)*256+i]=p_data[i%256];//tracking data dari 0-2560 per paket data sebanyak 256
                             }
                     }
                     if(counterCH3==10) counterCH3=0;
                 }// kanal 3
                 else if(i_kanal==3)//kanal 3
                 {
                    // qDebug()<<"-KANAL  4-" <<"ip pertama";
                     counterCH4++;
                     if (counterCH4<11)
                     {
                    //mengirim 1o paket kanal 4
                         for(int i=0; i<256; i++)
                             {
                                data_y_voltage4[i]=p_data[i%256]; //mengirim 1 paket
                                data10paket_4[(counterCH4-1)*256+i]=p_data[i%256];//tracking data dari 0-2560 per paket data sebanyak 256
                             }//for loop
                     }//counter channel
                     if(counterCH4==10)
                     {
                        counterCH4=0;
                        datamanagement();
                     }
                 }//kanal 4

             }//ip

#if 1
//-----------------------------------------batas sortir IP------------------------------------------------//
             else if(sendera.toIPv4Address() == ip_modul_2.toIPv4Address()) //ip kedua
             {
                // qDebug()<<"ip kedua";
                 //counterCH1++;// ikut 1 paket
                 if(i_kanal==0)//kanal 5
                 {
                     //qDebug()<<"-KANAL  5-" <<"ip kedua";
                     counterCH5++;
                     if (counterCH5<11)
                     {
                    //mengirim 1o paket kanal 5
                         int i;
                         for(i=0; i<256; i++)
                             {
                                // data_y_voltage1[i]=p_data[i%256]; //mengirim 1 paket
                                data10paket_5[(counterCH5-1)*256+i]=p_data[i%256];//tracking data dari 0-2560 per paket data sebanyak 256
                             //   qDebug()<<data10paket_5[(counterCH5-1)*256+i];
                             }
                                // qDebug()<<"oke masuk ke " << counterCH1 << "CH1" << "-jumlah data " << (counterCH1-1)*256+i;

                     }
                     if(counterCH5==10)counterCH5=0;
                 }//kanal 5
                 else if(i_kanal==1)//kanal 6
                 {
                   //  qDebug()<<"-KANAL  6-"<<"ip kedua";
                     counterCH6++;
                     if (counterCH6<11)
                     {
                    //mengirim 1o paket kanal 6
                         int i;
                         for(i=0; i<256; i++)
                             {
                                // data_y_voltage1[i]=p_data[i%256]; //mengirim 1 paket
                                data10paket_6[(counterCH6-1)*256+i]=p_data[i%256];//tracking data dari 0-2560 per paket data sebanyak 256
                             }
                     }
                     if(counterCH6==10)counterCH6=0;
                 }//kanal 6
                 else if(i_kanal==2)//kanal 7
                 {
                    // qDebug()<<"-KANAL  7-"<<"ip kedua";
                     counterCH7++;
                     if (counterCH7<11)
                     {
                    //mengirim 1o paket kanal 7
                         int i;
                         for(i=0; i<256; i++)
                             {
                                // data_y_voltage1[i]=p_data[i%256]; //mengirim 1 paket
                                data10paket_7[(counterCH7-1)*256+i]=p_data[i%256];//tracking data dari 0-2560 per paket data sebanyak 256
                             }
                                // qDebug()<<"oke masuk ke " << counterCH1 << "CH1" << "-jumlah data " << (counterCH1-1)*256+i;
                     }
                     if(counterCH7==10)counterCH7=0;
                 }// kanal 7
                 else if(i_kanal==3)//kanal 8
                 {
                   //  qDebug()<<"-KANAL  8-"<<"ip kedua";
                     counterCH8++;
                     if (counterCH8<11)
                     {
                    //mengirim 1o paket kanal 8
                         int i;
                         for(i=0; i<256; i++)
                             {
                                // data_y_voltage1[i]=p_data[i%256]; //mengirim 1 paket
                                data10paket_8[(counterCH8-1)*256+i]=p_data[i%256];//tracking data dari 0-2560 per paket data sebanyak 256
                             }//for loop
                              // qDebug()<<"oke masuk ke " << counterCH1 << "CH1" << "-jumlah data " << (counterCH1-1)*256+i;
                     }//counter channel
                     if(counterCH8==10)
                     {
                         counterCH8=0;
                         datamanagement2();
                     }
                 }//kanal 8
             }//ip KEDUA
#endif

    }// while
}//void


void data::datamanagement()
{
    QJsonObject isikanal;
    //kanal_p1
    QJsonObject kanalip1;
    QJsonObject ip1;
    //qDebug() << "size 1 data kanal1: " << sizeof(data_y_voltage1)<< "jumlah data: " << sizeof(data_y_voltage1)/sizeof(data_y_voltage1[0]);
    //qDebug() << "size 1 data kanal2: " << sizeof(data_y_voltage2)<< "jumlah data: " << sizeof(data_y_voltage2)/sizeof(data_y_voltage2[0]);
    //qDebug() << "size 1 data kanal3: " << sizeof(data_y_voltage3)<< "jumlah data: " << sizeof(data_y_voltage3)/sizeof(data_y_voltage3[0]);
    //qDebug() << "size 1 data kanal4: " << sizeof(data_y_voltage4)<< "jumlah data: " << sizeof(data_y_voltage4)/sizeof(data_y_voltage4[0]);

    //qDebug() << "size 10 data kanal1: " << sizeof(data10paket_1)<< "jumlah data: " << sizeof(data10paket_1)/sizeof(data10paket_1[0]);
    //qDebug() << "size 10 data kanal2: " << sizeof(data10paket_2)<< "jumlah data: " << sizeof(data10paket_2)/sizeof(data10paket_2[0]);
    //qDebug() << "size 10 data kanal3: " << sizeof(data10paket_3)<< "jumlah data: " << sizeof(data10paket_3)/sizeof(data10paket_3[0]);
    //qDebug() << "size 10 data kanal4: " << sizeof(data10paket_4)<< "jumlah data: " << sizeof(data10paket_4)/sizeof(data10paket_4[0]);

    QJsonArray buff1;
    QJsonArray buff2;
    QJsonArray buff3;
    QJsonArray buff4;
    QJsonValue spsip1_;


    for(int i=0; i<PAKET_10; i++)
    {
        buff1.push_back(data10paket_1[i]);
        buff2.push_back(data10paket_2[i]);
        buff3.push_back(data10paket_3[i]);
        buff4.push_back(data10paket_4[i]);
    }

    kanalip1.insert("kanal1",buff1);
    kanalip1.insert("kanal2",buff2);
    kanalip1.insert("kanal3",buff3);
    kanalip1.insert("kanal4",buff4);
    kanalip1.insert("spsip1",spsX);

    //memasukkan seluruh data kanal ke doc json
    //jika sudah melakukan parsing dan membaca dan ditampilkan

    ip1.insert("ip1",kanalip1);
    QJsonDocument paket1Bro(ip1);
    QString sout = QString::fromUtf8(paket1Bro.toJson(QJsonDocument::JsonFormat::Compact));
    sendDataClient1(sout);
}

void data::datamanagement2()
{
#if 1
    QJsonObject isikanal;
    //kanal_p1
    QJsonObject kanalip2;
    QJsonObject ip2;
    //qDebug() << "size 1 data kanal1: " << sizeof(data_y_voltage1)<< "jumlah data: " << sizeof(data_y_voltage1)/sizeof(data_y_voltage1[0]);
    //qDebug() << "size 1 data kanal2: " << sizeof(data_y_voltage2)<< "jumlah data: " << sizeof(data_y_voltage2)/sizeof(data_y_voltage2[0]);
    //qDebug() << "size 1 data kanal3: " << sizeof(data_y_voltage3)<< "jumlah data: " << sizeof(data_y_voltage3)/sizeof(data_y_voltage3[0]);
    //qDebug() << "size 1 data kanal4: " << sizeof(data_y_voltage4)<< "jumlah data: " << sizeof(data_y_voltage4)/sizeof(data_y_voltage4[0]);

    //qDebug() << "size 10 data kanal1: " << sizeof(data10paket_1)<< "jumlah data: " << sizeof(data10paket_1)/sizeof(data10paket_1[0]);
    //qDebug() << "size 10 data kanal2: " << sizeof(data10paket_2)<< "jumlah data: " << sizeof(data10paket_2)/sizeof(data10paket_2[0]);
    //qDebug() << "size 10 data kanal3: " << sizeof(data10paket_3)<< "jumlah data: " << sizeof(data10paket_3)/sizeof(data10paket_3[0]);
    //qDebug() << "size 10 data kanal4: " << sizeof(data10paket_4)<< "jumlah data: " << sizeof(data10paket_4)/sizeof(data10paket_4[0]);

    QJsonArray buff1;
    QJsonArray buff2;
    QJsonArray buff3;
    QJsonArray buff4;
    QJsonValue spsip2_;


    for(int i=0; i<PAKET_10; i++)
    {
        buff1.push_back(data10paket_5[i]);
        buff2.push_back(data10paket_6[i]);
        buff3.push_back(data10paket_7[i]);
        buff4.push_back(data10paket_8[i]);
    }

    kanalip2.insert("kanal1",buff1);
    kanalip2.insert("kanal2",buff2);
    kanalip2.insert("kanal3",buff3);
    kanalip2.insert("kanal4",buff4);
    kanalip2.insert("spsip1",spsX);

    //memasukkan seluruh data kanal ke doc json
    //jika sudah melakukan parsing dan membaca dan ditampilkan

    ip2.insert("ip1",kanalip2);
    QJsonDocument paket2Bro(ip2);
    QString sout2 = QString::fromUtf8(paket2Bro.toJson(QJsonDocument::JsonFormat::Compact));
    sendDataClient2(sout2);
#endif
}

void data::refresh_plot()
{

    req_UDP();
    tim_count++;
//    if (!m_db.open())
//    {
//        qDebug() << "Error: connection with database fail";
//    }
//    else
//    {
//        if (m_db.isOpen())
//        {
//           // int masuk=120;
//            createTable();
//            addPerson(simpanan);
//        }
//    }
}

data::~data()
{
    m_pWebSocketServer1->close();
    qDeleteAll(Subcribe_wave1.begin(), Subcribe_wave1.end());//paket10
    qDeleteAll(Subcribe_wave2.begin(), Subcribe_wave2.end());//paket10
}

void data::onNewConnection()
{
    C_NewCon = m_pWebSocketServer1->nextPendingConnection();
    //connect(pSocket1, &QWebSocket::binaryMessageReceived, this, &data::processMessage);
    connect(C_NewCon, &QWebSocket::textMessageReceived, this, &data::processMessage);
    connect(C_NewCon, &QWebSocket::disconnected, this, &data::socketDisconnected);
    //CG_NewClient << C_NewCon; //grup conneksi
}

void data::processMessage(QString message)
{
    QWebSocket *C_NewReq = qobject_cast<QWebSocket *>(sender());
        qDebug()<<message;
        QString wave1 ="wave1";
        //QString wave2 ="wave2";
        QString unsub_wave1 ="unsub_wave1";
        //QString unsub_wave2 ="unsub_wave2";
        QString bukanAnggota ="Maaf req anda tidak terdaftar";
        if((C_NewReq)&&(message==wave1))
            {
                   Subcribe_wave1.removeAll(C_NewReq);
                   Subcribe_wave1 << C_NewReq;
                   qDebug()<<"req wave 1 dari:"<<C_NewReq->peerAddress().toString();
//                }
            }

       if((C_NewReq)&&(message==unsub_wave1))
           {
               Subcribe_wave1.removeAll(C_NewReq);
               C_NewReq->deleteLater();
               QHostAddress join=C_NewReq->peerAddress();
               QString loststr=join.toString();
               qDebug()<<"client unsub wave1" << loststr;
           }
#if 0
       else if((Subcribe_wave1.indexOf(C_NewCon))&&(message==wave2))
        {
           Subcribe_wave2 << C_NewCon;////paket10
           qDebug()<<"req wave 2 dari:"<<C_NewCon->peerAddress().toString();
        }
       else if(message==unsub_wave2)
       {
           Subcribe_wave2.removeAll(C_NewCon);
           C_NewCon->deleteLater();
           QHostAddress join=C_NewCon->peerAddress();
           QString loststr=join.toString();
           qDebug()<<"client unsub wave1" << loststr;
       }
#endif
       else
       {
           message=bukanAnggota;
           C_NewReq->sendTextMessage(message);
       }

//    }
//    }


}
void data::sendDataClient1(QString isipesan)
{
    Q_FOREACH (pClientkirim, Subcribe_wave1)//paket10
    {
        QHostAddress join=pClientkirim->peerAddress();
        QString joinstr=join.toString();
        qDebug() << "kirim paket 1----ke : "<<joinstr;
        pClientkirim->sendTextMessage(isipesan);
    }
}

void data::sendDataClient2(QString isipesan2)
{
#if 1
    Q_FOREACH (pClientkirim, Subcribe_wave2)//paket10
    {
        QHostAddress join=pClientkirim->peerAddress();
        QString joinstr=join.toString();
        qDebug() << "kirim paket 2----ke : "<<joinstr;
        pClientkirim->sendTextMessage(isipesan2);
    }
#endif
}



void data::socketDisconnected()
{
    pClient1 = qobject_cast<QWebSocket *>(sender());
    if (pClient1)
    {
        //pClient1->peerAddress();
        Subcribe_wave1.removeAll(pClient1);//paket10
        Subcribe_wave2.removeAll(pClient1);//paket10
        pClient1->deleteLater();
        QHostAddress join=pClient1->peerAddress();
        QString loststr=join.toString();
        qDebug()<<"client loss" << loststr;
    }
}


//////////////////////////////////////////////////////"DATABASE"//////////////////////////////////////////////////////
//void data::init_database()
//{
////    //database
//////    m_db = QSqlDatabase::addDatabase("QSQLITE");
//////    m_db.setDatabaseName("dataku.db");

////    if (!m_db.open())
////    {
////        qDebug() << "Error: connection with database fail";
////    }
////    else
////    {
////        if (m_db.isOpen())
////        {
////            createTable();   // Creates a table if it doens't exist. Otherwise, it will use existing table.
////          //  QString DataAsString = QString(datasimpan);
////            addPerson("B");
////           // addPerson("B");
////         //   addPerson("C");
////        //    printAllPersons();
////           //removePerson("A");
////           //printAllPersons();
////               // removeAllPersons();
////            }
////            qDebug() << "End";
////    }
//}

//bool data::createTable()
//{
//    bool success = false;

//    QSqlQuery query;
//    query.prepare("CREATE TABLE people(id INTEGER PRIMARY KEY, data BLOB);");

//    if (!query.exec())
//    {
//        qDebug() << "Couldn't create the table 'people': one might already exist.";
//        success = false;
//    }

//    return success;
//}

//bool data::addPerson(QByteArray masuks)
//{
//    bool success = false;
//    QSqlQuery queryAdd;
//    queryAdd.prepare("INSERT INTO people (data) VALUES (:data)");

//    queryAdd.bindValue(":data", masuks);
//    //queryAdd.bindValue(":name", name);

//    if(queryAdd.exec())
//    {
//        success = true;
//        qDebug() << "add data sukses";
//    }
//    else
//    {
//        qDebug() << "add data failed: " << queryAdd.lastError();
//    }

//    return success;
//}

//bool data::removePerson(QByteArray masuk)
//{
//    bool success = false;

//    if (personExists(masuk))
//    {
//        QSqlQuery queryDelete;
//        queryDelete.prepare("DELETE FROM people WHERE data = (:data)");
//        queryDelete.bindValue(":data", masuk);
//        success = queryDelete.exec();

//        if(!success)
//        {
//            qDebug() << "remove data failed: " << queryDelete.lastError();
//        }
//    }
//    else
//    {
//        qDebug() << "remove data failed: data doesnt exist";
//    }

//    return success;
//}

//void data::printAllPersons() const
//{
//    qDebug() << "Persons in db:";
//    QSqlQuery query("SELECT * FROM people");
//    int idName = query.record().indexOf("data");
//    while (query.next())
//    {
//        QString data = query.value(idName).toString();
//        qDebug() << "===" << data;
//    }
//}

//bool data::personExists(QByteArray masuk) const
//{
//    bool exists = false;

//    QSqlQuery checkQuery;
//    checkQuery.prepare("SELECT name FROM people WHERE data = (:data)");
//    checkQuery.bindValue(":data", masuk);

//    if (checkQuery.exec())
//    {
//        if (checkQuery.next())
//        {
//            exists = true;
//        }
//    }
//    else
//    {
//        qDebug() << "data exists failed: " << checkQuery.lastError();
//    }

//    return exists;
//}

//bool data::removeAllPersons()
//{
//    bool success = false;

//    QSqlQuery removeQuery;
//    removeQuery.prepare("DELETE FROM people");

//    if (removeQuery.exec())
//    {
//        success = true;
//    }
//    else
//    {
//        qDebug() << "remove all persons failed: " << removeQuery.lastError();
//    }

//    return success;
//}

//mencoba data 1 ip buffer apakah bagus atau tidak
//DDS (Data Distribution Service)
//OMG (Object Management Group)
//RTPS (Real Time Publish Subscribe)

//memastikan panjang data dan menghindari pengiriman data secara berulang
