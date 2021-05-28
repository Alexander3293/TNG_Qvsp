#ifndef SYNCMODULETRANCIEVER_H
#define SYNCMODULETRANCIEVER_H

/*
 * Надстойка на TCP клиентом для общения с модулем синхронизации
*/

#include <QObject>
#include "tcpclient.h"
#include <QDataStream>
#include <QElapsedTimer>
#include <QTime>
#include <QThread>
#include <QQueue>
#include <QFile>
//#include "spinnerprogresscontroller.h"

class SyncModuleTranciever : public QObject
{
    Q_OBJECT
public:
    explicit SyncModuleTranciever(QObject *parent = nullptr);
    ~SyncModuleTranciever();
    struct dataPoint{
        uint16_t ADC;
        bool timeBreakVibro;
        bool timeBreakDetonation;
        bool timeBreakDetonationConfirm;
    };

    struct pocket
    {
        int time;
        dataPoint value;
    };

//    static const int PORT_SYNC_MODULE = 5000;
    static const int PORT_SYNC_MODULE = 42416;

    const QString IP_ADDR_SYNC_MODULE = QString("192.168.1.114"); // "127.0.0.1"

    static const char SYNC_MODULE_CMD_START = 'S';
    static const char SYNC_MODULE_CMD_ADC ='A';
    static const char SYNC_MODULE_CMD_RESET ='R';
    static const char SYNC_MODULE_CHANNEL_DETONATION = 'F';
    static const char SYNC_MODULE_CHANNEL_VIBRO = 'V';
    QString SYNC_MODULE_MSG_TBV = QString("TBV");
    QString SYNC_MODULE_MSG_TBF = QString("TBF");
    QString SYNC_MODULE_MSG_CTB = QString("CTB");
    void sendRst(char channel);

    bool statusSyncModule() const;
    void setStatusSyncModule(bool statusSyncModule);

    bool isConnected() const;
    void setIsConnected(bool isConnected);

    void recieveMessage(QByteArray* outputArray, int len);
    void connectReadAll() {emit connectReadAll(true);}
    void disconnectReadAll() {emit connectReadAll(false);}

    bool *SYNCACK() const;


private:
    bool isConnected_;
    TcpClient* TCPTranciever_;
    bool statusSyncModule_;
    int counter_;
    QThread* threadTCPClient_;
    QTime startTime_;
    int lastRecordTime_;
    bool * SYNCACK_;
    char lastCMD_;
    char lastChannel_;
    int timeWaitingTB_ = 3;
    bool isTimeBreak_;
    bool isFirstPck_;
    int startTimeTB_;
    int startTimeCmd_;
    QQueue<qint8> buffer_;
    QQueue<QTime> timeBuffer_;

//    QByteArray saveData_;

private slots:
    void onClientConnected(bool isConnected);
    void onDataUpdate(QTime time, QByteArray arr);
    void onBufferUpdate();
    void finishRead();
    void onNewMessage(QString msg);
    void onGlobalStart(const QTime startTime);
    void onSYNCAkc(bool ack);
    void onStopData();

signals:
    void connectReadAll(bool stat);
    void dataUpdate(SyncModuleTranciever::pocket);
    void finishReceive(bool flag);
    void message(QString msg);
    void sendMessage(QByteArray);
    void globalStart(const int, const int);
    void stopThread();
    void SYNCAckError();
    void stopGlobalTimer(bool);
    void bufferUpdate();
    void disconnectFromHostSig();
    void sendStopPck();
    void deleteTcpClient();

public slots:
    void sendCmd(const QString cmdText, const QString channelText, const int timeText);
    void run();
    void stop();
    void stopRecord(bool status);
    void disconnectFromHost();
};

QDataStream& operator <<(QDataStream &out, const SyncModuleTranciever::pocket &point);
QDataStream& operator >>(QDataStream &in, const SyncModuleTranciever::pocket *point);
Q_DECLARE_METATYPE(SyncModuleTranciever::dataPoint)
Q_DECLARE_METATYPE(SyncModuleTranciever::pocket)
#endif // SYNCMODULETRANCIEVER_H
