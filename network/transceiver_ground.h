#ifndef TRANSCEIVER_GROUND_H
#define TRANSCEIVER_GROUND_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QList>
#include <QMetaType>
#include <QFile>

/*--------- CMD gorund modules -----------------*/
#define NUMBER_DEVICES			0xa9
#define READY_DEVICE            0xaf

#define ADC_START               0xc1
#define ADC_SETTING             0xc0
#define ADC_STOP                0xc3

#define ADC_ENABLE              0xdedea0
#define ADC_DISABLE             0xdedea5
#define SEARCH_DEV              0xdedeaf
/*-----------------------------------------------*/

typedef struct
{
    int time;
    uint32_t numPckt;
    uint8_t	numModule;
    QVector<double> data;

} pointsFromWGrounds;

class Transceiver_ground: public QObject
{
Q_OBJECT

public:
    explicit Transceiver_ground(QObject *parent = 0);
    ~Transceiver_ground();
    void initialize(QString address, int port);
private:
    QUdpSocket              *udp_socket;
    QHostAddress            host_;
    quint16                 portDst_;
    quint16                 portBind_;
    QHostAddress            senderAdr;
    quint16                 senderPort;
    QList<pointsFromWGrounds* > listGroundModules;
    QList<QVector<double> *> listVector;
    volatile int device_id = -1;
    int nowTime_;

    QString handPackage = "ed00ff";
    int32_t tmpMSB;
    int32_t tmpLSB;
    int32_t valuePckt;
    uint32_t counterDatagram;
    uint32_t dataDatagramlen;
    bool ok;

    QString logFileName;
    QFile file_global;      // for the correct close fil

    void AddToLog(QString strLog);
    void WriteToFile (QByteArray data);

public slots:
    void on_udp_data_rx(void);
    void dataProcessingModuleGround (QByteArray);
    void start();
    void send_cmd(void);
    void send_Start(void);
    void send_Stop(void);
    void send_Settings_KU(int value);

signals:
    void dataGroundUpdate(pointsFromWGrounds *data);
    void message(QString strLog);


};

Q_DECLARE_METATYPE(pointsFromWGrounds);

#endif // TRANSCEIVER_GROUND_H
