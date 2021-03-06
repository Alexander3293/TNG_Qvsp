//-----------------------------------------------------------------------------
// Класс приема-передачи с платой скважинных (подземных) модулей
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
#ifndef OVSP_CLASS_H
#define OVSP_CLASS_H
//-----------------------------------------------------------------------------
#include <Windows.h>
#include <winsock.h>
//#pragma comment(lib, "wsock32.lib")
#include <QObject>
#include <QString>
#include <QtNetwork/QUdpSocket>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QThread>
#include <QTime>
#include <QtMath>

#include <QFile>
//#include <QTimer>
//#include <QList>
//-----------------------------------------------------------------------------
#include "network/declarateTransceiveringData.h"
//-----------------------------------------------------------------------------
//Определение выводов проекта
//-----------------------------------------------------------------------------
#define DEPT_RESET_PIN			0x0001		//PF0
#define AD25256_CS_PIN			0x0002		//PF1
#define IIM7010_IRQ_PIN			0x0004		//PF2
#define W3100_RESET_PIN			0x0008		//PF3
#define RTL8201L_RESET_PIN		0x0010		//PF4
#define RX_EN_PIN               0x0020		//PF5
#define TX_EN_PIN               0x0040		//PF6
#define OTGIM_PIN               0x0080		//PF7
#define PRIGIM_PIN              0x0100		//PF8
#define ML_PIN             		0x0200		//PF9
#define INIT_OK_PIN             0x0400		//PF10
#define ERROR_PIN               0x0800		//PF11
#define CURENT_LIMIT_PIN        0x1000		//PF12
#define CTL_U2_PIN              0x2000		//PF13
#define CTL_U1_PIN              0x4000		//PF14
#define CTL_PWR_PIN             0x8000		//PF15
//-----------------------------------------------------------------------------
typedef struct
{
    int time;
    unsigned short int	n_pocket;
    short int	data[OVSP_NUM_POINTS];
} pointFromDownHoles;

QDataStream& operator <<(QDataStream &out, const pointFromDownHoles &point);
QDataStream& operator >>(QDataStream &in, const pointFromDownHoles *point);

class Transceiver_class : public QObject
{
    Q_OBJECT
public:
    explicit Transceiver_class(QObject *parent = 0);
    ~Transceiver_class();

private:
    volatile int            blk_count;
    quint16                 p_count;
    quint16                 cmd_id;
    QUdpSocket              *udp_socket;
    QHostAddress            host_;
    quint16                 port_;
    QHostAddress            senderAdr;
    quint16                 senderPort;
    QTime timeOfPoint;
    void send_cmd(u_short cmd);
    int depth_ = 0;

    QString logFileName;
    QFile file_global;      // for the correct close fil

    void WriteToFile(pointFromDownHoles &point);

signals:
    void data_update(const int blk_cnt, const pointFromDownHoles &point);
    //void data_update        (const int blk_cnt, const int module, const TDataPocket &data);
    void connectionClosed();
    void newDepth(int depth);

public slots:
    void on_udp_data_rx     (void);

public slots:
    void start();
    void send_start      (void);
    void on_tool_work_mode  (void); //(int module_No);

public:
    void initialize(QString address,int port_);
    void on_cmd_set_dept    (int dept);
    void on_cmd_read_dept   (void);

    void on_panel_pwr_on    (void);
    void on_panel_pwr_off   (void);
    void on_panel_motor_on  (void);
    void on_panel_motor_off (void);
    void send_prigim    (void);
    void send_otgim     (void);
    void on_panel_Ilimit    (void);
    void on_panel_Inormal   (void);


    void on_tool_set_KU     (int value);
    void on_tool_rele_on    (int module_No);
    void on_tool_rele_off   (int module_No);
    void on_tool_test_mode  (void); //(int module_No);
    void on_tool_offset_corection(void);
};
Q_DECLARE_METATYPE(pointFromDownHoles)
//-----------------------------------------------------------------------------
#endif // OVSP_CLASS_H
//-----------------------------------------------------------------------------
