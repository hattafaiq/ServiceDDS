#include "data.h"
#include "setting.h"


data::data(QObject *parent) : QObject(parent)
{
    //INIT_udp
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, 5008);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyReady()));
    //INIT_websocket
    m_pWebSocketServer1 = new QWebSocketServer(QStringLiteral("Chat Server"),QWebSocketServer::NonSecureMode,this);
    m_pWebSocketServer1->listen(QHostAddress::Any, 1234);
    connect(m_pWebSocketServer1, SIGNAL(newConnection()),this, SLOT(onNewConnection()));
  //  qDebug()<<"client connect"<<&address;
    //INIT_waktu
    jam = new QTimer(this);
    connect(jam, SIGNAL(timeout()),this, SLOT(showTime()));
    jam->start();
    date = QDate::currentDate();
    dateTimeText = date.toString();
}

void data::init_time()
{
    timer = new QTimer(this);
    timera = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this, SLOT(refresh_plot()));
    QObject::connect(timera,SIGNAL(timeout()),this, SLOT(sendDataClient1()));
    timer->start(2200);
}

void data::req_UDP()
{
    QByteArray Data;
    Data.append("getdata");
    socket->writeDatagram(Data,QHostAddress("192.168.0.101"), 5006);
    socket->writeDatagram(Data,QHostAddress("192.168.0.102"), 5006);
    counterCH1=0;
    counterCH2=0;
    counterCH3=0;
    counterCH4=0;
    counterCH5=0;
    counterCH6=0;
    counterCH7=0;
    counterCH8=0;
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
    unsigned short spsX;
   // int cnt_ch[JUM_PLOT];
   // float *data_send[JUM_PLOT];
    int no_module;
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
        if(sendera.toIPv4Address() == ip_modul_1.toIPv4Address())
        {
            no_module = 0;
          //  qDebug()<<"module 1 aktif";
           //qDebug()<<"ip setup modul 1 = "<< ip_modul_1.toIPv4Address();
            //qDebug()<<"ip pengirim modul 1 = "<< sendera.toIPv4Address();
        }
        else if(sendera.toIPv4Address() == ip_modul_2.toIPv4Address())
        {
            no_module = 1;
           // qDebug()<<"module 2 aktif";
            //qDebug()<<"ip setup modul 2 = "<< ip_modul_1.toIPv4Address();
            //qDebug()<<"ip pengirim modul 2 = "<< sendera.toIPv4Address();
        }
         p_req2 = (struct tt_req2 *) datagram.data();
         p_data = (float *) p_req2->buf;
         i_kanal = p_req2->cur_kanal;
         spsX = p_req2->sps;

        //QByteArray paketkirim;
        //float data10paket_1[2560];
        //qDebug()<<"sps :"<<spsX;
             if(no_module==0) //ip pertama
             {
                // qDebug()<<"ip pertama";
                 //counterCH1++;// ikut 1 paket
                 if(i_kanal==0)//kanal 1
                 {
                     qDebug()<<"-KANAL  1-" <<"ip pertama";
                     counterCH1++;
                     if (counterCH1<11)
                     {

        ///////////////////////////////////////////////////////////////////////////////////////////////////
                    //mengirim 1o paket kanal 1
                         int i;
                         for(i=0; i<256; i++)
                             {
                                // data_y_voltage1[i]=p_data[i%256]; //mengirim 1 paket
                                data10paket_1[(counterCH1-1)*256+i]=p_data[i%256];//tracking data dari 0-2560 per paket data sebanyak 256

                             }
                        if(counterCH1==10)
                            {
                                counterCH1=0;
                               // sendDataClient1();
                            }

                       }//channel

                 }//kanal 1

                 else if(i_kanal==1)//kanal 2
                 {
                    // qDebug()<<"-KANAL  2-" <<"ip pertama";
                     counterCH2++;
                     if (counterCH2<11)
                     {

        ///////////////////////////////////////////////////////////////////////////////////////////////////
                    //mengirim 1o paket kanal 2
                         int i;
                         for(i=0; i<256; i++)
                             {
                                // data_y_voltage1[i]=p_data[i%256]; //mengirim 1 paket
                                data10paket_2[(counterCH2-1)*256+i]=p_data[i%256];//tracking data dari 0-2560 per paket data sebanyak 256
                             }

                     }
                 }//kanal 2

                 else if(i_kanal==2)//kanal 3
                 {
                   //  qDebug()<<"-KANAL  3-" <<"ip pertama";
                     counterCH3++;
                     if (counterCH3<11)
                     {

        ///////////////////////////////////////////////////////////////////////////////////////////////////
                    //mengirim 1o paket kanal 3
                         int i;
                         for(i=0; i<256; i++)
                             {
                                // data_y_voltage1[i]=p_data[i%256]; //mengirim 1 paket
                                data10paket_3[(counterCH3-1)*256+i]=p_data[i%256];//tracking data dari 0-2560 per paket data sebanyak 256
                             }

                     }
                 }// kanal 3

                 else if(i_kanal==3)//kanal 3
                 {
                    // qDebug()<<"-KANAL  4-" <<"ip pertama";
                     counterCH4++;
                     if (counterCH4<11)
                     {

        ///////////////////////////////////////////////////////////////////////////////////////////////////
                    //mengirim 1o paket kanal 4
                         int i;
                         for(i=0; i<256; i++)
                             {
                                // data_y_voltage1[i]=p_data[i%256]; //mengirim 1 paket
                                data10paket_4[(counterCH4-1)*256+i]=p_data[i%256];//tracking data dari 0-2560 per paket data sebanyak 256
                             }//for loop

                     }//counter channel

                 }//kanal 4

             }//ip

//-----------------------------------------batas sortir IP------------------------------------------------//
             else if(no_module==1) //ip kedua
             {
                // qDebug()<<"ip kedua";
                 //counterCH1++;// ikut 1 paket
                 if(i_kanal==0)//kanal 5
                 {
                     //qDebug()<<"-KANAL  5-" <<"ip kedua";
                     counterCH5++;
                     if (counterCH5<11)
                     {

        ///////////////////////////////////////////////////////////////////////////////////////////////////
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

        ///////////////////////////////////////////////////////////////////////////////////////////////////
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

        ///////////////////////////////////////////////////////////////////////////////////////////////////
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

        ///////////////////////////////////////////////////////////////////////////////////////////////////
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

        //datamanagement();

    }// while

}//void

void data::sendDataClient1()
{
    QByteArray byteArray1(reinterpret_cast<const char*>(&data10paket_1), 2560 * sizeof(float));
//   QWebSocket *pSender1 = qobject_cast<QWebSocket *>(sender());
    Q_FOREACH (QWebSocket *pClient1, m_clients1)
    {
       // pClient1->sendTextMessage(QString::number(byteArray1.size()));
       // pClient1->sendTextMessage(byteArray1.toHex());
          pClient1->sendBinaryMessage(byteArray1);
    }

}

void data::datamanagement()
{

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
    connect(pSocket1, &QWebSocket::binaryMessageReceived, this, &data::processMessage);
   // connect(pSocket1, &QWebSocket::textMessageReceived, this, &data::processMessage);
    connect(pSocket1, &QWebSocket::disconnected, this, &data::socketDisconnected);
    m_clients1 << pSocket1;
//    Q_FOREACH (QWebSocket *pClient1, m_clients1)
//    {
//        pClient1->sendBinaryMessage();
//    }
}

void data::processMessage(QByteArray message)
{
    qDebug()<<message;
    QString bisa ="bisa";
    if(message==bisa)
    {
      timera->start(1000);
    }
    else
    {
        timera->stop();
    }


}

void data::socketDisconnected()
{
   QWebSocket *pClient1 = qobject_cast<QWebSocket *>(sender());
    if (pClient1)
    {
        m_clients1.removeAll(pClient1);
        pClient1->deleteLater();
        qDebug()<<"client loss";
    }
}

//mencoba data 1 ip buffer apakah bagus atau tidak
//DDS (Data Distribution Service)
//OMG (Object Management Group)
//RTPS (Real Time Publish Subscribe)
