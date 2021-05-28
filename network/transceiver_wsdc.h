#ifndef CLIENT_H
#define CLIENT_H
/*
* Класс для работы с наземными модулями
*/

#include <QWidget>
#include <QTextEdit>
#include <QtNetwork/QTcpSocket>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>
#include <QTimer>
#include <QHostAddress>
#include <QDataStream>
#include "network/declarateTransceiveringData.h"
#include <stdio.h>
#include <sys/time.h>
#include "wsdc/create_smsp.h"
#include <QDebug>
typedef struct
{
    int time;
//    unsigned short int averageValueTime[COUNT_WELLS_MODULES];
    uint8_t	numModule;
    QByteArray data;
} pointsFromWells;

QDataStream& operator <<(QDataStream &out, const pointsFromWells &point);
QDataStream& operator >>(QDataStream &in, const pointsFromWells *point);

class transceiver_wsdc : public QObject
{
    Q_OBJECT

    enum wsdcCtrlCmd{
        TURN_OFF = 0,
        RESET_OS = 1,
        RESET_MODEM = 2
    };

private:
    QTcpSocket*     m_pTcpSocket;
    QTcpSocket*     setTimeSocket;
    QTextEdit*      m_ptxtInfo;
    QTextEdit*      m_ptxtInput;
    QTextEdit*      m_ptxtOutput;
    QVBoxLayout*    pvbxLayout;
    QPushButton*    pcmd;
    create_smsp     pckt;
    QHostAddress address_;
    int nPort_ ;
    int syncTimePort_;
    QTimer* reconnectTimer_;
    QDateTime currentTimeUNIX_;
    quint32 numMeas_; //число измерений
    uint8_t     addr_domain;    // номер домена (комплекса).
    uint8_t     addr_node;      // Сетевой адрес: номер узла в данном домене
    uint8_t     pktype;         // Тип пакета
    uint8_t     pknum;          // Номер пакета или временная метка
    QByteArray* data;           // Блок данных
    int startTime_;
//    int timeForDiff_[COUNT_WELLS_MODULES];
    bool firstInput;
    uint8_t cur_number[8];
    bool _system_start= false;
    int currPckt_[8];

    void sendCtrlPck(int val);
    void disconnectCtrlSocket();

public:
    explicit transceiver_wsdc(QObject *parent = 0);
    ~transceiver_wsdc();
    void initialize(QHostAddress address, int nPort);
    void setStartTime(int startTime);
    void send_KU(bool isSendAll, quint8 numModule, quint8 value);


    void send_GetStatus();

    int startTime() const;

    void disconnectFromServer();

signals:
    void data_from_wsdc(const pointsFromWells &points);
//    void data_from_wsdc(uint8_t numModule, QByteArray data);
    void connectionClosed();
    void sendByteData(QByteArray dataMsg);
    void msgForUpHole(QString msg);
private slots:
    void slotRead       ();
    void slotReadTimeSock();
    void slotSend       (const QByteArray dataBlock);
    void slotError      (QAbstractSocket::SocketError err);

    void slotConnected  ();
    void connectToHost();

public slots:
    void send_Stop();
    void send_Start();
    void sendCurrTime();
    void start();
    void turnOff();
    void resetWSDC();
    void resetModem();
};
Q_DECLARE_METATYPE(pointsFromWells)
#endif // CLIENT_H
