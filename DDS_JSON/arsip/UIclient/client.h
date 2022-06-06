#ifndef CLIENT_H
#define CLIENT_H

#include <QWebSocket>
#include <QTimer>
#include <QDate>
#include <QString>

class EchoClient : public QObject
{
    Q_OBJECT
public:
    explicit EchoClient(const QUrl &url, bool debug = false, QObject *parent = nullptr);

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
    void onBinMessageReceived(QByteArray message);
   // void onTextMessageReceived(QString s_message);
    void showTime();

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
    QTimer *jam;
    QDate date;
    QString dateTimeText;
    QString time_text;
    int count;
    //////
    QString qs = "bisa";
     QByteArray kanal1;
     bool topik=false;
     float outValue[2560];
};


#endif // CLIENT_H
