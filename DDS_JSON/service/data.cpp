#include "data.h"
#include "setting.h"


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
}

void data::init_time()
{
    timer = new QTimer(this);
    timera = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this, SLOT(refresh_plot()));
    QObject::connect(timera,SIGNAL(timeout()),this, SLOT(datamanagement()));
    timer->start(2200);//2200 // harus sesuai interval berdasarkan sps
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
    // int cnt_ch[JUM_PLOT];
    // float *data_send[JUM_PLOT];
    //   int no_module;
    //= -1;
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
                         //QJsonArray buff1;
                         int i;
                         for(i=0; i<256; i++)
                             {
                                //data_y_voltage1[i]=p_data[i%256]; //mengirim 1 paket
                                data10paket_1[(counterCH1-1)*256+i]=p_data[i];//tracking data dari 0-2560 per paket data sebanyak 256
                             }

                       }//counter
                     if(counterCH1==10) counterCH1=0;
//                     {
//                         counterCH1=0;
//                        datamanagement();
//                       // memset(&data10paket_1,'\0',sizeof (data10paket_1)/sizeof (float));
                     //kirim berdasarkan counter paket
//                     }
                 }//kanal 1

                 else if(i_kanal==1)//kanal 2
                 {
                    // qDebug()<<"-KANAL  2-" <<"ip pertama";
                     counterCH2++;
                     if (counterCH2<11)
                     {
                    //mengirim 1o paket kanal 2
                         int i;
                         for(i=0; i<256; i++)
                             {
                                // data_y_voltage1[i]=p_data[i%256]; //mengirim 1 paket
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
                         int i;
                         for(i=0; i<256; i++)
                             {
                                // data_y_voltage1[i]=p_data[i%256]; //mengirim 1 paket
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
                         int i;
                         for(i=0; i<256; i++)
                             {
                                // data_y_voltage1[i]=p_data[i%256]; //mengirim 1 paket
                                data10paket_4[(counterCH4-1)*256+i]=p_data[i%256];//tracking data dari 0-2560 per paket data sebanyak 256
                             }//for loop
                     }//counter channel
                     if(counterCH4==10) counterCH4=0;
                 }//kanal 4
             }//ip
#if 0
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
                         if(counterCH5==10)
                         {
                                 counterCH5=0;
                                 //sendDataClient1();
                         }
                     }
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
                 }//kanal 8
             }//ip KEDUA
#endif
    }// while
}//void

void data::sendDataClient1(QString isipesan)
{   
    Q_FOREACH (QWebSocket *pClient1, m_clients1)
    {
        pClient1->sendTextMessage(isipesan);
        //pClient1->sendTextMessage(docByteArray);
        //pClient1->sendBinaryMessage(docByteArray);
        QHostAddress join=pClient1->peerAddress();
        QString joinstr=join.toString();
        qDebug() << "kirim----ke : "<<joinstr;
    }
}

void data::datamanagement()
{
        QJsonObject isikanal;
        //kanal_p1
        QJsonObject kanalip1;
        QJsonObject kanalip2;
        QJsonObject kanalip3;
        QJsonObject kanalip4;
        QJsonObject ip1;

           qDebug() << "size data 1: " << sizeof(data10paket_1)<< "jumlah paket: " << sizeof(data10paket_1)/sizeof(data10paket_1[0]);
    //       qDebug() << "size data 2: " << sizeof(data10paket_2)<< "jumlah paket: " << sizeof(data10paket_2)/sizeof(data10paket_2[0]);
    //       qDebug() << "size data 3: " << sizeof(data10paket_3)<< "jumlah paket: " << sizeof(data10paket_3)/sizeof(data10paket_3[0]);
    //       qDebug() << "size data 4: " << sizeof(data10paket_4)<< "jumlah paket: " << sizeof(data10paket_4)/sizeof(data10paket_4[0]);

           //    if(counterCH1>=10);//);//>=10) && (counterCH2 >=10) && (counterCH3 >=10) && (counterCH4 >=10))
    //    {

            QJsonArray buff1;
            QJsonArray buff2;
            QJsonArray buff3;
            QJsonArray buff4;
            QJsonValue spsip1_;
            for(int i=0; i<2560; i++){
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

        // QJsonDocument doc(jsonObj);
        //     QString json = "{}";
        //     QJsonDocument jdoc = QJsonDocument::fromJson(json.toUtf8());
        QString sout = QString::fromUtf8(paket1Bro.toJson(QJsonDocument::JsonFormat::Compact));

       sendDataClient1(sout);
}

void data::refresh_plot()
{
    req_UDP();
    tim_count++;
    //qDebug("%s() == %d",__FUNCTION__,tim_count);
}

data::~data()
{
    m_pWebSocketServer1->close();
    qDeleteAll(m_clients1.begin(), m_clients1.end());
}

void data::onNewConnection()
{
    //qDebug("%s() == %d",__FUNCTION__,tim_count);
    QWebSocket *pSocket1 = m_pWebSocketServer1->nextPendingConnection();
    //connect(pSocket1, &QWebSocket::binaryMessageReceived, this, &data::processMessage);
    connect(pSocket1, &QWebSocket::textMessageReceived, this, &data::processMessage);
    connect(pSocket1, &QWebSocket::disconnected, this, &data::socketDisconnected);
    m_clients1 << pSocket1;

}

void data::processMessage(QString message)
{
    qDebug()<<message;
    QString bisa ="bisa";
    if(message==bisa)
    {
     timera->start(1000);//(2560*1000)/spsX); 2560=jumlah data dikali dengan 1000 milisecon dibagi sps
     //membuat 2 opsi antara timer sesuai denga sps atau dikirim langsung dari counter data
     //datamanagement();
    }
}

void data::socketDisconnected()
{
   QWebSocket *pClient1 = qobject_cast<QWebSocket *>(sender());
    if (pClient1)
    {
        //pClient1->peerAddress();
        m_clients1.removeAll(pClient1);
        pClient1->deleteLater();
        QHostAddress join=pClient1->peerAddress();
        QString loststr=join.toString();
        qDebug()<<"client loss" << loststr;
    }
}

//mencoba data 1 ip buffer apakah bagus atau tidak
//DDS (Data Distribution Service)
//OMG (Object Management Group)
//RTPS (Real Time Publish Subscribe)

//memastikan panjang data dan menghindari pengiriman data secara berulang
