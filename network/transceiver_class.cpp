 //-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#include "transceiver_class.h"
#include "network/declarateTransceiveringData.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

QDataStream& operator <<(QDataStream &out, const pointFromDownHoles &point)
{
    out.writeRawData((char*)(&point), sizeof(pointFromDownHoles));
    return out;
}

QDataStream& operator >>(QDataStream &in, const pointFromDownHoles *point)
{
    in.readRawData((char*)(point), sizeof(pointFromDownHoles));
    return in;
}

Transceiver_class::Transceiver_class(QObject *parent) :
    QObject(parent)//QAbstractTableModel(parent)
{
    blk_count = 0;
    p_count = 0;

    logFileName  = QString("D:/Test/Dn.txt");

    file_global.setFileName(logFileName);
    if (!file_global.open(QIODevice::WriteOnly|QIODevice::Append))
    {
        qDebug() << "Ошибка при открытии файла";
        return;
    }
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Transceiver_class::~Transceiver_class()
{
//    delete udp_socket;
    emit connectionClosed();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Transceiver_class::initialize(QString address, int port)
{
    this->port_ = port;
    host_ = QHostAddress(address);
}
void Transceiver_class::start()
{
    udp_socket = new QUdpSocket();
    udp_socket->bind(port_);

    connect(udp_socket, SIGNAL(readyRead()), this, SLOT(on_udp_data_rx()));
}

void Transceiver_class::send_cmd(u_short cmd)
{
    TCtrlPocket ctl_pocket;

    memset((char*)&ctl_pocket, 0, sizeof(TCtrlPocket));
    ctl_pocket.id = htons(cmd);
    p_count++;
    ctl_pocket.n_pocket = htons(p_count);
    // qDebug() << "sending comand = " << cmd;
    udp_socket->writeDatagram((char*)&ctl_pocket, sizeof(TCtrlPocket), host_, port_);
}

void Transceiver_class::on_cmd_set_dept(int dept)
{
    TCtrlPocket ctl_pocket;
    u_short     cmd = (u_short)COMAND_SET_DEPT;

    memset((char*)&ctl_pocket, 0, sizeof(TCtrlPocket));
    ctl_pocket.id = htons(cmd);
    ctl_pocket.dept = htonl(dept);
    p_count++;
    ctl_pocket.n_pocket = htons(p_count);

    udp_socket->writeDatagram((char*)&ctl_pocket, sizeof(TCtrlPocket), host_, port_);
}

//-----------------------------------------------------------------------------
void Transceiver_class::on_cmd_read_dept(void)
{
    send_cmd((u_short)COMAND_READ_DEPT);
}
//-----------------------------------------------------------------------------
void Transceiver_class::on_panel_pwr_on(void)
{
    send_cmd((u_short)COMAND_OVSP_PWR_ON);
}
//-----------------------------------------------------------------------------
void Transceiver_class::on_panel_pwr_off(void)
{
    send_cmd((u_short)COMAND_OVSP_PWR_OFF);
}
//-----------------------------------------------------------------------------
void Transceiver_class::on_panel_motor_on(void)
{
    send_cmd((u_short)COMAND_OVSP_MOTOR_ON);
}
//-----------------------------------------------------------------------------
void Transceiver_class::on_panel_motor_off(void)
{
    send_cmd((u_short)COMAND_OVSP_MOTOR_OFF);
}
//-----------------------------------------------------------------------------
void Transceiver_class::send_prigim(void)
{
    send_cmd((u_short)COMAND_OVSP_PRIGIM);
}
//-----------------------------------------------------------------------------
void Transceiver_class::send_otgim(void)
{
    send_cmd((u_short)COMAND_OVSP_OTGIM);
}
//-----------------------------------------------------------------------------
void Transceiver_class::on_panel_Ilimit(void)
{
    send_cmd((u_short)COMMAND_OVSP_ILIMIT);
}
//-----------------------------------------------------------------------------
void Transceiver_class::on_panel_Inormal(void)
{
    send_cmd((u_short)COMMAND_OVSP_INORMAL);
}
//-----------------------------------------------------------------------------
void Transceiver_class::send_start(void)
{
    send_cmd((u_short)COMAND_OVSP_DO_MESERMENT);
}

void Transceiver_class::on_tool_set_KU(int value)
{
    TCtrlPocket ctl_pocket;

    u_short     cmd = (u_short)COMAND_OVSP_SET_KU;

    memset((char*)&ctl_pocket, 0, sizeof(TCtrlPocket));
    ctl_pocket.id = htons(cmd);
    ctl_pocket.KU = htons(std::log2(value));
    p_count++;
    ctl_pocket.n_pocket = htons(p_count);

    udp_socket->writeDatagram((char*)&ctl_pocket, sizeof(TCtrlPocket), host_, port_);
}

void Transceiver_class::on_tool_rele_on(int module_No)
{
    TCtrlPocket ctl_pocket;
    u_short     cmd = (u_short)COMAND_OVSP_RELE_ON;

    memset((char*)&ctl_pocket, 0, sizeof(TCtrlPocket));
    ctl_pocket.id = htons(cmd);
    ctl_pocket.module_No = htons(module_No);
    p_count++;
    ctl_pocket.n_pocket = htons(p_count);

    udp_socket->writeDatagram((char*)&ctl_pocket, sizeof(TCtrlPocket), host_, port_);
}

void Transceiver_class::on_tool_rele_off(int module_No)
{
    TCtrlPocket ctl_pocket;// __attribute__((packed));
    u_short     cmd = (u_short)COMAND_OVSP_RELE_OFF;
//    qDebug() << "sending comand = " << cmd;
    memset((char*)&ctl_pocket, 0, sizeof(TCtrlPocket));
    ctl_pocket.id = htons(cmd);
    ctl_pocket.module_No = htons(module_No);
    p_count++;
    ctl_pocket.n_pocket = htons(p_count);

    udp_socket->writeDatagram((char*)&ctl_pocket, sizeof(TCtrlPocket), host_, port_);
}

void Transceiver_class::on_tool_test_mode(void)    //(int module_No)
{
/*
    TCtrlPocket ctl_pocket;
    u_short     cmd = (u_short)COMAND_OVSP_TEST_MODE;

    memset((char*)&ctl_pocket, 0, sizeof(TCtrlPocket));
    ctl_pocket.id = htons(cmd);
    ctl_pocket.module_No = htons(module_No);
    p_count++;
    ctl_pocket.n_pocket = htons(p_count);

    udp_socket.writeDatagram((char*)&ctl_pocket, sizeof(TCtrlPocket), host, port);
*/
    send_cmd((u_short)COMAND_OVSP_TEST_MODE);
}

void Transceiver_class::on_tool_work_mode(void)    //(int module_No)
{
/*
    TCtrlPocket ctl_pocket;
    u_short     cmd = (u_short)COMAND_OVSP_WORK_MODE;

    memset((char*)&ctl_pocket, 0, sizeof(TCtrlPocket));
    ctl_pocket.id = htons(cmd);
    ctl_pocket.module_No = htons(module_No);
    p_count++;
    ctl_pocket.n_pocket = htons(p_count);

    udp_socket.writeDatagram((char*)&ctl_pocket, sizeof(TCtrlPocket), host, port);
*/
    send_cmd((u_short)COMAND_OVSP_WORK_MODE);
}

void Transceiver_class::on_tool_offset_corection(void)
{
    qDebug() << "COMMAND_OVSP_OFFSET_CORECTION";
    send_cmd((u_short)COMMAND_OVSP_OFFSET_CORECTION);
}

//-----------------------------------------------------------------------------

void Transceiver_class::on_udp_data_rx(void)
{
    TDataPocket* pdata = new(TDataPocket);
    pointFromDownHoles* dataPoint = new (pointFromDownHoles);
//    qWarning() << "udp_socket->bytesAvailable() before" << udp_socket->bytesAvailable();
    if (udp_socket->hasPendingDatagrams())
    {
        udp_socket->readDatagram((char*) pdata, sizeof(TDataPocket), &senderAdr, &senderPort);

        timeOfPoint = QTime::currentTime();
//        qSwap(((char*) pdata)[8], ((char*) pdata)[9]); //check
        dataPoint->time = timeOfPoint.msecsSinceStartOfDay();
        memcpy(dataPoint->data, pdata->data, sizeof(short) * OVSP_NUM_POINTS); // корректировка
        dataPoint->n_pocket = pdata->n_pocket;


//        qWarning() << "recieve" <<  QTime::currentTime() << htons((ushort) pdata->n_pocket) << blk_count;

//        qWarning() << pdata->dept;
        if((qAbs(this->depth_ - pdata->dept) / 100 ) > 5 && pdata->dept > 0)
        {
            this->depth_ = pdata->dept;
            emit newDepth(this->depth_);
        }
//        qDebug() << blk_count
//                 <<"data";
//        for(int i = 0; i < OVSP_NUM_POINTS; i++)
//            if(pdata->data[i]!= 0)
//                qDebug()<<i<<"="<<pdata->data[i];
        blk_count++;
//    qDebug() << "blk_count = " << blk_count;
//    qDebug() << "in protocol = " << ntohs(pdata->n_pocket) ;
        WriteToFile(*dataPoint);
        emit data_update(blk_count, (*dataPoint));
//        qDebug() << "Transceiver_class data_update emited";
//        emit data_update(blk_count, 1 ,(*pdata));
    }
    else{
//        qWarning() << "no datagram";
    }
    delete pdata;
    delete dataPoint;
//    qWarning() << "udp_socket->bytesAvailable() after"  << udp_socket->bytesAvailable();
}

void Transceiver_class::WriteToFile(pointFromDownHoles &point)
{
    QByteArray tmpByte;
    quint8* pdata = (quint8*)&(point.data[0]);

    union {
        struct {
            quint8 x7_0;
            quint8 x15_8;
            quint8 x23_16;
            quint8 x31_24;
        };
        quint32 x31_0;
    } y;

    y.x23_16 = *(pdata + 4);
    y.x15_8  = *(pdata + 5 );
    y.x7_0   = *(pdata + 6);


    if ((y.x31_0 & 0x00800000) > 0) y.x31_24 = 0xFF;
    else y.x31_24 = 0;

    tmpByte.setNum(y.x31_0);

    file_global.write(tmpByte+'\n');
    file_global.flush();

    delete pdata;
}
