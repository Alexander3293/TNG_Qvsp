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
    isRecording_ = false;
    startFile = true;
    numModule_ = 0;
    sizeFile_=0;
    frstPcktOffset = false;

    cntFileSGD = 0;
    cntMeasSGD   = 0;
    checkBLKCount = false;

    dataPointTmp = new (pointFromDownHoles);
    for(int i=0; i < 20;i++){    //max 8 modules
        dataPointTmp->data[i * 16 + 0] = MSBvalMissPacket;
        dataPointTmp->data[i * 16 + 2] = LSBvalMissPacket;
        dataPointTmp->data[i * 16 + 3] = LSBvalMissPacket;

        dataPointTmp->data[i * 16 + 4] = MSBvalMissPacket;
        dataPointTmp->data[i * 16 + 5] = LSBvalMissPacket;
        dataPointTmp->data[i * 16 + 6] = LSBvalMissPacket;

        dataPointTmp->data[i * 16 + 7] = MSBvalMissPacket;
        dataPointTmp->data[i * 16 + 8] = LSBvalMissPacket;
        dataPointTmp->data[i * 16 + 9] = LSBvalMissPacket;
    }

}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Transceiver_class::~Transceiver_class()
{
//    delete udp_socket;
    delete dataPointTmp;
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

//        timeOfPoint = QTime::currentTime();
////        qSwap(((char*) pdata)[8], ((char*) pdata)[9]); //check
//        dataPoint->time = timeOfPoint.msecsSinceStartOfDay();
        memcpy(dataPoint->data, pdata->data, sizeFile_); // корректировка
        dataPoint->n_pocket = pdata->n_pocket;
//        qWarning() << "recieve" <<  QTime::currentTime() << htons((ushort) pdata->n_pocket) << blk_count;

//        qWarning() << pdata->dept;
        if((qAbs(this->depth_ - pdata->dept) / 100 ) > 5 && pdata->dept > 0)
        {
            this->depth_ = pdata->dept;
            emit newDepth(this->depth_);
        }

        /*Назначаем номер пакета в самый первый раз */
        if(!checkBLKCount){
            blk_count = ntohs(pdata->n_pocket);
            qDebug() << "BLK count" << blk_count;
            checkBLKCount = true;
        }
        else{
            /* Проверяем нумерацию пакета, если не совпадает, то добавляем пакет "зашкала" вручную */
            if(blk_count != ntohs(pdata->n_pocket)){
                qDebug() << "Error Pckt DownHole" << "CurrentPckt:" << ntohs(pdata->n_pocket)
                         << "last Pckt : "<<  blk_count;
                dataPointTmp->n_pocket = blk_count;
                emit data_update(blk_count, (*dataPointTmp));
                blk_count++;
                if(isRecording_ && (flagFirst)){
                    if(!frstPcktOffset){
                        quint16 numPcktDownHoles = ntohs(pdata->n_pocket);  //начало пакета с 1 у подземных модулей
                        if((numPcktDownHoles%256) > 11){
                            qDebug() << "num Pckt DownHoles" << ntohs(pdata->n_pocket);
                            frstPcktOffset = true;
                            numPcktDownHoles -= 12;
                            emit newOffsetpckt(numPcktDownHoles);//отослать наземным и синхро номер пакета
                            WriteToFile(*dataPointTmp, sizeFile_);
                        }
                    }
                    else{
                       WriteToFile(*dataPoint, sizeFile_);
                    }
                }
            }
        }
        emit data_update(blk_count, (*dataPoint));
        blk_count++;
        if(!flagFirst) {
            uint16_t numPcktDownHoles = ntohs(pdata->n_pocket);
            if((numPcktDownHoles%256) > 10)
                flagFirst = true;

            else {
               delete pdata;
               delete dataPoint;
               return;
            }
        }
        if(isRecording_ && (flagFirst)){
            if(!frstPcktOffset){
                quint16 numPcktDownHoles = ntohs(pdata->n_pocket);  //начало пакета с 1 у подземных модулей
                if((numPcktDownHoles%256) > 11){
                    qDebug() << "num Pckt DownHoles" << ntohs(pdata->n_pocket);
                    frstPcktOffset = true;
                    numPcktDownHoles -= 12;
                    emit newOffsetpckt(numPcktDownHoles);//отослать наземным и синхро номер пакета
                    WriteToFile(*dataPoint, sizeFile_);
                }
            }
            else{
               WriteToFile(*dataPoint, sizeFile_);
            }
        }
    }
    else{
//        qWarning() << "no datagram";
    }
    delete pdata;
    delete dataPoint;
//    qWarning() << "udp_socket->bytesAvailable() after"  << udp_socket->bytesAvailable();
}

/* Add to the Test Write File */
//void Transceiver_class::WriteToFile(pointFromDownHoles &point)
//{
//    if(startFile)
//    {
//        QByteArray tmp;
//        tmp.setNum(ntohs(point.n_pocket));
//        file_global.write(tmp+'\n');
//        startFile = false;
//    }
//    QByteArray tmpByte;
//    quint8* pdata = (quint8*)&(point.data[0]);

//    union {
//        struct {
//            quint8 x7_0;
//            quint8 x15_8;
//            quint8 x23_16;
//            quint8 x31_24;
//        };
//        qint32 x31_0;
//    } y;

//    y.x23_16 = *(pdata + 4);
//    y.x15_8  = *(pdata + 5 );
//    y.x7_0   = *(pdata + 6);


//    if ((y.x31_0 & 0x00800000) > 0) y.x31_24 = 0xFF;
//    else y.x31_24 = 0;

//    tmpByte.setNum(y.x31_0);

//    file_global.write(tmpByte+'\n');
//    file_global.flush();
//}

void Transceiver_class::WriteToFile(pointFromDownHoles &point, uint size)
{
    QByteArray buff;
    buff.resize(size);
    memmove(buff.data(), &point, size);

    QByteArray tmpByte;
    quint8* pdata = (quint8*)&(point.data[0]);

    union {
        struct {
            quint8 x7_0;
            quint8 x15_8;
            quint8 x23_16;
            quint8 x31_24;
        };
        qint32 x31_0;
    } x, y, z;

    QVector<float> data_tmp;
    data_tmp.append(0.0);

    if(cntMeasSGD >= sizeSgdFile_){  //131070 or more
        cntMeasSGD = 0;
        cntFileSGD++;
        this->update_sgd_files("");
    }

    for(uint8_t numMod=0; numMod<numModule_; numMod++){
        /* Check CRC data */
        if(!crc_.checkCRC(pdata,numMod )){
        //if(!1){
            data_tmp[0] = maxValMissPacket;

            listFileSgd.at(3*numMod)->append_data(data_tmp);
            listFileSgd.at(3*numMod+1)->append_data(data_tmp);
            listFileSgd.at(3*numMod+2)->append_data(data_tmp);

        }
        else{
            x.x23_16 = *(pdata + 0 + numMod*16);
            x.x15_8  = *(pdata + 2 + numMod*16);
            x.x7_0   = *(pdata + 3 + numMod*16);

            y.x23_16 = *(pdata + 4 + numMod*16);
            y.x15_8  = *(pdata + 5 + numMod*16);
            y.x7_0   = *(pdata + 6 + numMod*16);

            z.x23_16 = *(pdata + 7 + numMod*16);
            z.x15_8  = *(pdata + 8 + numMod*16);
            z.x7_0   = *(pdata + 9 + numMod*16);

            if ((x.x31_0 & 0x00800000) > 0) x.x31_24 = 0xFF;
            else x.x31_24 = 0;

            if ((y.x31_0 & 0x00800000) > 0) y.x31_24 = 0xFF;
            else y.x31_24 = 0;

            if ((z.x31_0 & 0x00800000) > 0) z.x31_24 = 0xFF;
            else z.x31_24 = 0;

            data_tmp[0] = float(x.x31_0);
            listFileSgd.at(3*numMod)->append_data(data_tmp);

            data_tmp[0] = float(y.x31_0);
            listFileSgd.at(3*numMod+1)->append_data(data_tmp);

            data_tmp[0] = float(z.x31_0);
            listFileSgd.at(3*numMod+2)->append_data(data_tmp);
        }
    }

    cntMeasSGD++;
}

void Transceiver_class::setRecord(bool isRecording)
{
    isRecording_ = isRecording;
}

bool Transceiver_class::getRecord()
{
    return isRecording_;
}

void Transceiver_class::setFileName(int idMeas, QString dirFile)
{
    Q_UNUSED(idMeas);
//    file_global.setFileName(dirFile+"/DownHole.txt");
//    if (!file_global.open(QIODevice::WriteOnly|QIODevice::Append))
//    {
//        qDebug() << "Ошибка при открытии файла";
//        return;
//    }

//    if(listFileSgd.count() > 0){
//        for(auto cnt=0; cnt<listFileSgd.count(); cnt++){
//            if(listFileSgd.at(cnt)->getFileName()!="")
//                listFileSgd.at(cnt)->close_data();
//        }
//    }
    cntFileSGD = 0;
    cntMeasSGD = 0;
    update_sgd_files(dirFile);

}

void Transceiver_class::update_sgd_files(QString dirFile)
{
    /* Если пустой, то создать просто новый файл */
    if(dirFile == ""){
        QString fileName = listFileSgd.at(0)->getFileName();
        uint cnt = fileName.lastIndexOf("_DownnHole_device_");     //Найти номер файла sgd и заменить его на текущий

        for(auto fileSgd: listFileSgd){
            fileSgd->close_data();
            if(cntFileSGD > 10)
                fileSgd->setFileName(fileSgd->getFileName().replace(cnt-2, 2, QString::number(cntFileSGD)));
            else
                fileSgd->setFileName(fileSgd->getFileName().replace(cnt-1, 1, QString::number(cntFileSGD)));
        }
    }

    else{
        for(auto i=0; i<numModule_; i++){

            listFileSgd.at(3*i+0)->setFileName((dirFile+"/" +QString::number(cntFileSGD)+
                                                "_DownnHole_device_%1X.sgd").arg(i+1));
            listFileSgd.at(3*i+1)->setFileName((dirFile+"/" +QString::number(cntFileSGD)+
                                                "_DownnHole_device_%1Y.sgd").arg(i+1));
            listFileSgd.at(3*i+2)->setFileName((dirFile+"/" +QString::number(cntFileSGD)+
                                                "_DownnHole_device_%1Z.sgd").arg(i+1));
        }
    }

    this->setSettings();
}

void Transceiver_class::setSettings()
{
    QDate date_tmp = QDate::currentDate();
    QTime time_tmp = QTime::currentTime();
    quint16 count_measures = 65535; //20 sec

    for(auto i= 0; i < numModule_; i++ ){
        listFileSgd.at(3*i)->setData(date_tmp);
        listFileSgd.at(3*i)->setTime(time_tmp);
        listFileSgd.at(3*i)->setCounterByte(0);
        listFileSgd.at(3*i)->setFileNumber(1);
        listFileSgd.at(3*i)->setRecordLenght(1);
        listFileSgd.at(3*i)->setChannelSets(1);
        listFileSgd.at(3*i)->write_general_header();
        listFileSgd.at(3*i)->write_general_header_blk2();
        //listFileSgd.at(3*i)->write_general_header_blk3();
        listFileSgd.at(3*i)->setChannelSetNumber(1);
        listFileSgd.at(3*i)->setChannelSetStartTime(0);
        listFileSgd.at(3*i)->setChannelSetEndTime(count_measures);
        //listFileSgd.at(3*i)->setDataLength(count_measures); //length data
        listFileSgd.at(3*i)->setNumberOfChannels(numModule_*3);
        listFileSgd.at(3*i)->setChannelType((quint8)CHANNELSETS_TYPE_SEIS);
        listFileSgd.at(3*i)->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
        listFileSgd.at(3*i)->setAliasFilterSlope((quint16)1);
        listFileSgd.at(3*i)->write_header();
        listFileSgd.at(3*i)->write_extended_header();
        listFileSgd.at(3*i+0)->open_data();
        listFileSgd.at(3*i+0)->write_data_header(1, 3*i+1);

        listFileSgd.at(3*i+1)->setData(date_tmp);
        listFileSgd.at(3*i+1)->setTime(time_tmp);
        listFileSgd.at(3*i+1)->setCounterByte(0);
        listFileSgd.at(3*i+1)->setFileNumber(1);
        listFileSgd.at(3*i+1)->setRecordLenght(1);
        listFileSgd.at(3*i+1)->setChannelSets(1);
        listFileSgd.at(3*i+1)->write_general_header();
        listFileSgd.at(3*i+1)->write_general_header_blk2();
        //listFileSgd.at(3*i+1)->write_general_header_blk3();
        listFileSgd.at(3*i+1)->setChannelSetNumber(1);
        listFileSgd.at(3*i+1)->setChannelSetStartTime(0);
        listFileSgd.at(3*i+1)->setChannelSetEndTime(count_measures);
        //listFileSgd.at(3*i+1)->setDataLength(count_measures); //length data
        listFileSgd.at(3*i+1)->setNumberOfChannels(numModule_*3);
        listFileSgd.at(3*i+1)->setChannelType((quint8)CHANNELSETS_TYPE_SEIS);
        listFileSgd.at(3*i+1)->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
        listFileSgd.at(3*i+1)->setAliasFilterSlope((quint16)1);
        listFileSgd.at(3*i+1)->write_header();
        listFileSgd.at(3*i+1)->write_extended_header();
        listFileSgd.at(3*i+1)->open_data();
        listFileSgd.at(3*i+1)->write_data_header(1, 3*i+2);

        listFileSgd.at(3*i+2)->setData(date_tmp);
        listFileSgd.at(3*i+2)->setTime(time_tmp);
        listFileSgd.at(3*i+2)->setCounterByte(0);
        listFileSgd.at(3*i+2)->setFileNumber(1);
        listFileSgd.at(3*i+2)->setRecordLenght(1);
        listFileSgd.at(3*i+2)->setChannelSets(1);
        listFileSgd.at(3*i+2)->write_general_header();
        listFileSgd.at(3*i+2)->write_general_header_blk2();
        //listFileSgd.at(3*i+2)->write_general_header_blk3();
        listFileSgd.at(3*i+2)->setChannelSetNumber(1);
        listFileSgd.at(3*i+2)->setChannelSetStartTime(0);
        listFileSgd.at(3*i+2)->setChannelSetEndTime(count_measures);
        //listFileSgd.at(3*i+2)->setDataLength(count_measures); //length data
        listFileSgd.at(3*i+2)->setNumberOfChannels(numModule_*3);
        listFileSgd.at(3*i+2)->setChannelType((quint8)CHANNELSETS_TYPE_SEIS);
        listFileSgd.at(3*i+2)->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
        listFileSgd.at(3*i+2)->setAliasFilterSlope((quint16)1);
        listFileSgd.at(3*i+2)->write_header();
        listFileSgd.at(3*i+2)->write_extended_header();
        listFileSgd.at(3*i+2)->open_data();
        listFileSgd.at(3*i+2)->write_data_header(1, 3*i+3);
    }
}

void Transceiver_class::setNumModule(int numModule)
{
    numModule_ = numModule;
    /* Размер записи пакета в файл */
    sizeFile_ = 16*numModule_ + 2;  // 2bytes - n_pocket + 16 bytes is data one module

    if(listFileSgd.count() > 0){
        for(auto cnt=0; cnt<listFileSgd.count(); cnt++){
            listFileSgd.at(cnt)->close_data();
            delete listFileSgd.at(cnt);
        }
        listFileSgd.clear();
    }
    for(auto i=0; i<numModule_; i++){
        listFileSgd.append(new single_segd_rev2_files()); //x
        listFileSgd.append(new single_segd_rev2_files()); //y
        listFileSgd.append(new single_segd_rev2_files()); //z
    }
}

void Transceiver_class::clearFlags()
{
    flagFirst = false;
    isRecording_ = false;
}
