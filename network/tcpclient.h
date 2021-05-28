#ifndef TCPCLIENT_H
#define TCPCLIENT_H

/*
 * TCP клиент для свзяи с модулем синхронизации
 * */

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include <QTimer>
#include <QTime>
#include <QThread>
#include <winsock.h>
#include <QQueue>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QHostAddress addr, int port, QObject *parent = nullptr);
    virtual ~TcpClient();

private:
    QTcpSocket *sock_;
    QByteArray bytes_;
    QHostAddress addr_;
    int port_;
    QTimer *timer_;
    QByteArray* lastCMD_;
    int lastPacketSize_ = -1;
    QByteArray buffer_;
    bool checkAck(QByteArray *inputACK, QByteArray last);
    static const int sizeofdata_ = 2;
    static const int sizeofACK_ = 6;
    static const int sizeofPctLen_ = 2;
    static const int sizeofTime_ = 8;
    QDateTime lastTime_ = QDateTime::currentDateTime();
    bool isReadyReadFirst_;
    int counter_;
//    QTimer* readerTimer_;

//    static const int pointPerSec = 1000;

private slots:
    void dataRead(bool status);
    void parser();

signals:
    void newMessage(QString message);
    void connected(bool isConnected);
    void stopThread();
    void ack(bool);
    void dataUpdate(QTime, QByteArray);
    void finishRecieve();
    void globalStart(const QTime);
    void bufferUpdate();

public slots:
    void connectToHost();
    void startTimer();
    void run();
    void stop();
    void sendMessage(QByteArray data);
    void stopTimer();
    void connectReadAll(bool stat);
    void recieveMessage1();
    bool recieveMessage2(QByteArray* outputArray, int len);
    void disconnectFromHost();
    void sendDicconnectPck();
};

#endif // TCPCLIENT_H
