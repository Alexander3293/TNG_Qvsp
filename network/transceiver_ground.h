#ifndef TRANSCEIVER_GROUND_H
#define TRANSCEIVER_GROUND_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QList>
#include <QMetaType>
#include <QFile>

#include "work_with_project/single_segd_rev2_files.h"
#include "network/transceiver_class.h"

/*--------- CMD ground modules -----------------*/
#define SEARCH_NUMBER_DEVICES	0xa9
#define READY_DEVICE            0xaf

#define ADC_START               0xc1
#define ADC_SETTING             0xc0
#define ADC_STOP                0xc3

#define ADC_ENABLE              0xdedea0
#define ADC_DISABLE             0xdede05
#define SEARCH_DEV              0xdedeaf


/*-----------------------------------------------*/

typedef struct
{
    int time;
    uint8_t numPckt;
    int16_t oldPckt;        //Отлавливать битый пакет
    uint8_t	numModule;
    QVector<double> data;
    uint8_t	CRC_MSB;
    uint8_t	CRC_LSB;

} pointsFromWGrounds;

class Transceiver_ground: public QObject
{
Q_OBJECT

public:
    explicit Transceiver_ground(QObject *parent = 0);
    ~Transceiver_ground();
    void initialize(QString address, int port);
    void setFileName(int idMeas, QString dirFile);
    void setSettings(quint8 numModule);
    void setNumModule(int numModule);
    void setRecord(bool isRecording);
    bool getRecord();

private:
    QUdpSocket              *udp_socket;
    QHostAddress            host_;
    quint16                 portDst_;
    quint16                 portBind_;
    QHostAddress            senderAdr;
    quint16                 senderPort;
    QList<pointsFromWGrounds* > listGroundModules;
    QList<bool> listOffset;
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
    int16_t numPckt_;
    int16_t numMeasure_;
    Transceiver_class* trans_;

    //QFile file_global;      // for the correct close fil
    QList<single_segd_rev2_files*> listFileSgd;     //rev2.1
    int numModule_;     //Количество устройств для записи
    QList<quint32> listCntMeasSGD;      //количество измерений в файле
    QList<quint16> listCntFileSGD;      //номер sgd файла
    quint32 max_len_sgd = 131070;       //максимальная длина файла segd rev2.1

    void AddToLog(QString strLog);
    void WriteToFile (QByteArray data);
    bool isRecording_;   //нужно ли записывать в файл

    QList<quint8> blk_count;
    QList<bool> checkBLKCount; //Чтобы первый пакет был равен Pckt Number
    pointsFromWGrounds* dataPointTmp;
    double maxValMissPacket = 0x7fffff;  //8 388 607 (int24)

    quint32 cntFilesSgd;

public slots:
    void on_udp_data_rx(void);
    void dataProcessingModuleGround (QByteArray);
    void start();
    void send_cmd(void);
    void send_Start(void);
    void send_Stop(void);
    void send_Settings_KU(int value, uint8_t numDev);
    void getDataOffsetDownHoles(quint16 numPckt);
    void send_search_devices();
    void update_sgd_files(quint8 numModule, QString dirFile);

signals:
    void dataGroundUpdate(pointsFromWGrounds *data);
    void message(QString strLog);
    void devGroundState(quint8 numDev, bool state);
};

Q_DECLARE_METATYPE(pointsFromWGrounds);

#endif // TRANSCEIVER_GROUND_H
