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
#include <QUdpSocket>
#include "work_with_project/single_segd_files.h"
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

    typedef struct
    {
        int time;
        uint8_t numPckt;
        int16_t oldPckt;        //Отлавливать битый пакет
        uint8_t	numModule;
        QVector<double> dataADC;
        QVector<bool> timeBreakVibro;
        QVector<bool> timeBreakDetonation;
        QVector<bool> timeBreakDetonationConfirm;

    } pointsFromSync;

    static const char SYNC_MODULE_CMD_START = 'S';
    static const char SYNC_MODULE_CMD_ADC ='A';
    static const char SYNC_MODULE_CMD_RESET ='R';
    static const char SYNC_MODULE_CHANNEL_DETONATION = 'F';
    static const char SYNC_MODULE_CHANNEL_VIBRO = 'V';
    QString SYNC_MODULE_MSG_TBV = QString("TBV");
    QString SYNC_MODULE_MSG_TBF = QString("TBF");
    QString SYNC_MODULE_MSG_CTB = QString("CTB");
    quint16 _TBV_msk = 0x1000;
    quint16 _TBF_msk = 0x2000;
    quint16 _CTB_msk = 0x4000;

    void sendRst(char channel);

    bool statusSyncModule() const;
    void setStatusSyncModule(bool statusSyncModule);

    bool isConnected() const;
    void setIsConnected(bool isConnected);

    void recieveMessage(QByteArray* outputArray, int len);
    void connectReadAll() {emit connectReadAll(true);}
    void disconnectReadAll() {emit connectReadAll(false);}

    bool *SYNCACK() const;

    void initialize(QString address, int port);
    void start();
    void setFileName(int idMeas, QString dirFile);
    void setSettings();
    void dataProcessingModuleSync (QByteArray data);
    void setRecord(bool isRecording);
    bool getRecord();

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

    /* My functions */
    QUdpSocket              *udp_socket;
    QHostAddress            host_;
    quint16                 portDst_;
    quint16                 portBind_;
    QHostAddress            senderAdr;
    quint16                 senderPort;
    //QFile                   file_global;
    QList<single_segd_files*> listFileSgd;
    void WriteToFile(QByteArray data);

    QList<pointsFromSync* > listSyncModule;
    int32_t tmpMSB;
    int32_t tmpLSB;
    uint16_t valuePckt;
    uint32_t counterDatagram;
    uint32_t dataDatagramlen;
    QString handPackage = "ffffff";
    bool isFrstDatagram;
    bool isRecording_;   //нужно ли записывать в файл

    bool Offset;
    bool frstPcktOffset = false;
    int16_t numPckt_;
    int16_t numMeasure_;

    quint8 blk_count;
    bool checkBLKCount; //Чтобы первый пакет был равен Pckt Number
    pointsFromSync* dataPointTmp;
    double maxValMissPacketADC = 0x7fffff;  //8 388 607 (int24)
    bool maxValMissPacketDigit = false;  //8 388 607 (int24)

    quint32 cntFilesSgd;


private slots:
    void onDataUpdate(QTime time, QByteArray arr);
    void onBufferUpdate();
    void finishRead();
    void onNewMessage(QString msg);
    void onGlobalStart(const QTime startTime);
    void onStopData();

    void on_udp_data_rx(void);

signals:
    void connectReadAll(bool stat);
    void dataUpdate(SyncModuleTranciever::pocket);
    void finishReceive(bool flag);
    void message(QString msg);
    void sendMessage(QByteArray);
    void globalStart(const int, const int);
    void stopThread();
    void stopGlobalTimer(bool);
    void bufferUpdate();
    void disconnectFromHostSig();
    void sendStopPck();
    void deleteTcpClient();
    void dataSyncUpdate(SyncModuleTranciever::pointsFromSync*);

public slots:
    void sendCmd(const QString cmdText, const QString channelText, const int timeText);
    void run();
    void stop();
    void stopRecord(bool status);
    void disconnectFromHost();
    void send_Start(const QString cmdText, const QString channelText);
    void send_Reset(void);
    void getDataOffsetDownHoles(quint16 numPckt);
    void AddToLog(QString strLog);
};

QDataStream& operator <<(QDataStream &out, const SyncModuleTranciever::pocket &point);
QDataStream& operator >>(QDataStream &in, const SyncModuleTranciever::pocket *point);
Q_DECLARE_METATYPE(SyncModuleTranciever::dataPoint)
Q_DECLARE_METATYPE(SyncModuleTranciever::pocket)
#endif // SYNCMODULETRANCIEVER_H
