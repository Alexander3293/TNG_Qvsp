#include "syncmoduletranciever.h"
#include <QTime>
#include <QNetworkDatagram>
QDataStream& operator <<(QDataStream &out, const SyncModuleTranciever::pocket &point)
{
    out.writeRawData((char*)(&point), sizeof(SyncModuleTranciever::pocket));
    return out;
}

QDataStream& operator >>(QDataStream &in, const SyncModuleTranciever::pocket *point)
{
    in.readRawData((char*)(point), sizeof(SyncModuleTranciever::pocket));
    return in;
}

SyncModuleTranciever::SyncModuleTranciever(QObject *parent) : QObject(parent)
{
    isTimeBreak_ = false;
    isRecording_ = false;
    listSyncModule.append(new(pointsFromSync));
    listSyncModule.at(0)->oldPckt = -1;

    cntFilesSgd = 0;

    checkBLKCount = false;
    blk_count = 0;
    dataPointTmp = new(pointsFromSync);
    for(int i =0; i < 256; i++){
        dataPointTmp->dataADC.append(maxValMissPacketADC);
        dataPointTmp->timeBreakVibro.append(maxValMissPacketDigit);
        dataPointTmp->timeBreakDetonation.append(maxValMissPacketDigit);
        dataPointTmp->timeBreakDetonationConfirm.append(maxValMissPacketDigit);
    }
}

SyncModuleTranciever::~SyncModuleTranciever()
{
    qDebug() << "SYNC DESTRUCTOR";
    delete udp_socket;
    delete dataPointTmp;
    delete listSyncModule.at(0);
    qDebug() << "SYNC DESTRUCTOR END";
    QThread::currentThread()->exit();
}

void SyncModuleTranciever::sendCmd(const QString cmdText, const QString channelText,  const int timeText) {
    //saveData_.clear();
    qDebug() << cmdText << channelText << timeText;
    int time = 1;
    //disconnectReadAll();
    char cmd = '0';
    if (cmdText == "S"){
        cmd = SyncModuleTranciever::SYNC_MODULE_CMD_START;
        isTimeBreak_ = false;
        isFirstPck_ = true;
    }
    else if (cmdText == "A"){
        cmd = SyncModuleTranciever::SYNC_MODULE_CMD_ADC;
        isTimeBreak_ = true;
        isFirstPck_ = false;
    }
    else if (cmdText == "R"){
        cmd = SyncModuleTranciever::SYNC_MODULE_CMD_RESET;
        isTimeBreak_ = true;
        isFirstPck_ = true;
    }
    char channel = '0';
    if (channelText == "F")
        channel = SyncModuleTranciever::SYNC_MODULE_CHANNEL_DETONATION;
    if (channelText == "V")
        channel = SyncModuleTranciever::SYNC_MODULE_CHANNEL_VIBRO;
    if (timeText > 0)
        time = timeText;
    if(time < 0)
        return;
    if(cmd != SYNC_MODULE_CMD_START && cmd != SYNC_MODULE_CMD_ADC && cmd != SYNC_MODULE_CMD_RESET )
        return;
    if(channel != SYNC_MODULE_CHANNEL_DETONATION && channel != SYNC_MODULE_CHANNEL_VIBRO)
        return;
    QByteArray sendCmd;
    sendCmd.append(cmd);
    sendCmd.append(channel);

    emit sendMessage(sendCmd);
    qDebug() << "CMD" << lastRecordTime_ << QTime::currentTime();
    buffer_.clear();
    timeBuffer_.clear();
}

void SyncModuleTranciever::run()
{
    statusSyncModule_ = false;
    connect(this, SIGNAL(bufferUpdate()), this, SLOT(onBufferUpdate()));
}

void SyncModuleTranciever::stop()
{

}

void SyncModuleTranciever::stopRecord(bool status)
{
    if(status == false){
        sendRst(lastChannel_);
    }
}

void SyncModuleTranciever::sendRst(char channel)
{
    qDebug() << "SYNC sendRSt" << QTime::currentTime();
    QByteArray sendCmd;
    sendCmd.append(SYNC_MODULE_CMD_RESET);
    sendCmd.append(channel);
    sendCmd.append('0');
    sendCmd.append('0');
    sendCmd.append('0');
    emit sendMessage(sendCmd);
    lastCMD_ = SYNC_MODULE_CMD_RESET;
    lastChannel_ = channel;
    lastRecordTime_ = 0;
    buffer_.clear();
    timeBuffer_.clear();
}

void SyncModuleTranciever::onDataUpdate(QTime time, QByteArray arr)
{
    for(int i = 0; i < arr.size(); i++){
        buffer_.enqueue(arr[i]);

        //saveData_.append(arr[i]);
    }
    timeBuffer_.enqueue(time);
    emit bufferUpdate();
}

void SyncModuleTranciever::onBufferUpdate()
{
    QTime timeVal = timeBuffer_.dequeue();
    int i = 0;
    while(buffer_.size() >= 2){
        if(i >= 10 && timeBuffer_.size() > 0){
            i = 0;
            timeVal = timeBuffer_.dequeue();
        }
        counter_++;

        quint16 tmpVal = static_cast<unsigned char>(buffer_.dequeue());
        tmpVal += static_cast<unsigned char>(buffer_.dequeue()) << 8;
        dataPoint tmpData;
        tmpData.ADC = (tmpVal & (0x0FFF));
        tmpData.timeBreakVibro = false;
        if((tmpVal & (0x0001 << 12)) != 0)
            tmpData.timeBreakVibro = true;
        tmpData.timeBreakDetonation = false;
        if((tmpVal & (0x0001 << 13)) != 0)
            tmpData.timeBreakDetonation = true;
        tmpData.timeBreakDetonationConfirm = false;
        if((tmpVal & (0x0001 << 14)) != 0)
            tmpData.timeBreakDetonationConfirm = true;
        pocket tmp;
        tmp.time = timeVal.msecsSinceStartOfDay() + i;
        //        qDebug() << tmp.time;
        tmp.value = tmpData;

        if(isTimeBreak_ == false) {
            if(tmp.value.timeBreakDetonation == true || tmp.value.timeBreakVibro == true){
                qDebug() << "TB" << QTime::currentTime() << tmp.time << i << timeVal.msecsSinceStartOfDay() << timeVal;
                //if(lastChannel_ == SYNC_MODULE_CHANNEL_DETONATION)
                startTimeTB_ = timeVal.msecsSinceStartOfDay() + i;
                if((startTimeTB_ - startTimeCmd_) < timeWaitingTB_ * 1000) {
                    onGlobalStart(timeVal.addMSecs(i));
                    qDebug() << "SYNC dataUpdate 1 ";
                    emit dataUpdate(tmp);
                   // SpinnerProgressController::getInstanse().incValue(0);
                }
                else{
                    //emit SYNCAckError();
                    qDebug() << "here ERROR";
                }
                isTimeBreak_ = true;
                emit message(SYNC_MODULE_MSG_TBF);
            }
            if(tmp.value.timeBreakDetonationConfirm == true)
                emit message(SYNC_MODULE_MSG_CTB);
            //        if(tmp.value.timeBreakVibro == true){
            //            startTimeTB_ = time.msecsSinceStartOfDay();
            //            //if(lastChannel_ == SYNC_MODULE_CHANNEL_VIBRO)
            //            onGlobalStart(time);
            //            isTimeBreak_ = true;
            //            emit message(SYNC_MODULE_MSG_TBV);
            //        }
            i++;
            continue;
        }
        if(isFirstPck_ == false){
            isFirstPck_ = true;
            onGlobalStart(timeVal.addMSecs(i));
            //SpinnerProgressController::getInstanse().incValue(0);
            qDebug() << "SYNC dataUpdate 2";
            emit dataUpdate(tmp);
            i++;
            continue;
        }
        //qDebug() << "Time: " << time.msecsSinceStartOfDay();
        i++;
        if(qAbs((startTimeTB_ - startTimeCmd_) - (lastRecordTime_) * 1000) > 2){
//            qDebug() << "SYNC dataUpdate 0" << startTimeTB_ << startTimeCmd_ << lastRecordTime_;
            emit dataUpdate(tmp);
        }
    }
}

void SyncModuleTranciever::finishRead()
{
    //qDebug() << counter_;
    emit finishReceive(true);
}

void SyncModuleTranciever::onNewMessage(QString msg)
{
    Q_UNUSED(msg);
}

void SyncModuleTranciever::onGlobalStart(const QTime startTime)
{
    qDebug() << "SEND GLOBAL START" << startTime;
    startTime_ = startTime;
    if(lastCMD_ == SYNC_MODULE_CMD_START)
        emit globalStart(startTime.msecsSinceStartOfDay(), (lastRecordTime_ - timeWaitingTB_) * 1000);
    else if(lastCMD_ == SYNC_MODULE_CMD_ADC)
        emit globalStart(startTime.msecsSinceStartOfDay(), lastRecordTime_ * 1000);
}


void SyncModuleTranciever::onStopData()
{
    qDebug() << "STOP SYNC" << QTime::currentTime() << lastCMD_;
    if(lastCMD_ == SYNC_MODULE_CMD_START){
        if(qAbs((startTimeTB_ - startTimeCmd_)) < ((timeWaitingTB_) * 1000))
            emit stopGlobalTimer(true);
        else
            emit stopGlobalTimer(false);
    }
    //    else if(lastCMD_ == SYNC_MODULE_CMD_ADC || lastCMD_ == SYNC_MODULE_CMD_RESET){
    //        //emit stopGlobalTimer(true);
    //        emit stopGlobalTimer(false);
    //    }
    else if(lastCMD_ == SYNC_MODULE_CMD_ADC){
        emit stopGlobalTimer(true);
    }
    else if(lastCMD_ == SYNC_MODULE_CMD_RESET){
        emit stopGlobalTimer(false);
    }
    buffer_.clear();
    timeBuffer_.clear();
}

bool SyncModuleTranciever::statusSyncModule() const
{
    return statusSyncModule_;
}

void SyncModuleTranciever::setStatusSyncModule(bool statusSyncModule)
{
    statusSyncModule_ = statusSyncModule;
}

void SyncModuleTranciever::disconnectFromHost()
{
    qDebug() << "SyncModuleTranciever :: Dicconnect from host" << isConnected_;
    if(isConnected_ == true){
        emit sendStopPck();
//        threadTCPClient_->sleep(50);
//        QThread::sleep(50);
        QThread::currentThread()->msleep(50);
        emit disconnectFromHostSig();
    }
    emit stopThread();
}

void SyncModuleTranciever::initialize(QString address, int port)
{
    this->portBind_ = port;
    host_ = QHostAddress(address);

}

void SyncModuleTranciever::start()
{
    udp_socket = new QUdpSocket();
    udp_socket->bind(portBind_);
    portDst_ = portBind_-1;
    connect(udp_socket, SIGNAL(readyRead()), this, SLOT(on_udp_data_rx()));
}

/* Прием данных */
void SyncModuleTranciever::on_udp_data_rx(void)
{
    QByteArray datagram;
    while(udp_socket->hasPendingDatagrams()){

        datagram.resize(udp_socket->pendingDatagramSize());
        QNetworkDatagram datagram_d = udp_socket->receiveDatagram(-1);
        datagram = datagram_d.data();

        dataProcessingModuleSync(datagram);
//        if(isRecording_)
//            WriteToFile(datagram);
    }
}

void SyncModuleTranciever::setRecord(bool isRecording)
{
    isRecording_ = isRecording;
}

bool SyncModuleTranciever::getRecord()
{
    return isRecording_;
}


void SyncModuleTranciever::send_Start(const QString cmdText, const QString channelText)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    if(cmdText == "S"){
        if(channelText == "F"){
            out <<(quint8)SYNC_MODULE_CMD_START;
            out << (quint8)SYNC_MODULE_CHANNEL_DETONATION;
        }
        else if(channelText == "V"){
            out <<(quint8)SYNC_MODULE_CMD_START;
            out << (quint8)SYNC_MODULE_CHANNEL_VIBRO;
        }
    }
    else if(cmdText == "A"){
        if(channelText == "F"){
            out <<(quint8)SYNC_MODULE_CMD_ADC;
            out << (quint8)SYNC_MODULE_CHANNEL_DETONATION;
        }
        else if(channelText == "V"){
            out <<(quint8)SYNC_MODULE_CMD_ADC;
            out << (quint8)SYNC_MODULE_CHANNEL_VIBRO;
        }
    }

    udp_socket->writeDatagram(block, host_, portDst_ );
}

void SyncModuleTranciever::send_Reset(void)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out <<(quint8)SYNC_MODULE_CMD_RESET;
    out <<(quint8)0xF;  //all

    udp_socket->writeDatagram(block, host_, portDst_ );
}

void SyncModuleTranciever::getDataOffsetDownHoles(quint16 numPckt)
{
    numPckt_ = numPckt / 256;
    numMeasure_ = numPckt %  256;
    Offset = true;
    //qDebug() << "Sync" << "numPckt Up" << numPckt_ << "num Meas" << numMeasure_;
}

/* Обработка данных */
void SyncModuleTranciever::dataProcessingModuleSync (QByteArray data)
{
    QString  tmp_str_iVal;  //Считываемое String
    QString  str_iVal;
    //isFrstDatagram = 0;     //Первое вхождение
    bool ok;
    dataDatagramlen = data.length()*2;
    QString str_data = data.toHex();
    listSyncModule.at(0)->dataADC.clear();
    listSyncModule.at(0)->timeBreakVibro.clear();
    listSyncModule.at(0)->timeBreakDetonation.clear();
    listSyncModule.at(0)->timeBreakDetonationConfirm.clear();
    counterDatagram=0;
    while(counterDatagram < dataDatagramlen) {

        tmp_str_iVal = str_data.mid(counterDatagram,8);
        counterDatagram += 8;

        if(tmp_str_iVal.startsWith(handPackage,Qt::CaseInsensitive)) {
            //if(isFrstDatagram)  emit dataSyncUpdate(listSyncModule.at(0));
            listSyncModule.at(0)->numPckt = tmp_str_iVal.right(2).toUInt(&ok,16);

            if(!checkBLKCount){
                blk_count = listSyncModule.at(0)->numPckt;
                checkBLKCount = true;
                blk_count++;
            }
            else{
                if(blk_count != listSyncModule.at(0)->numPckt){
                    qDebug() << "Error Packet Sync" << "CurrentPckt:" << listSyncModule.at(0)->numPckt
                             << "last Pckt : "<< blk_count;
                    dataPointTmp->numPckt = blk_count;
                    emit dataSyncUpdate(dataPointTmp);

                    if(isRecording_){
                        QVector<double> dataSync, dataTBF;
                        for(int i=0; i < dataPointTmp->dataADC.size(); i++)
                            dataSync.append(dataPointTmp->dataADC.at(i));

                        for(int i=0; i < dataPointTmp->timeBreakDetonation.size(); i++)
                            dataTBF.append(dataPointTmp->timeBreakDetonation.at(i));

                        if(Offset){
                            if(dataPointTmp->numPckt ==numPckt_){
                                    for(int i=0; i < numMeasure_; i++){
                                        dataSync.removeFirst();
                                        dataTBF.removeFirst();
                                    }

                                    Offset = false;
                                    listFileSgd.at(0)->append_data(dataSync);
                                    listFileSgd.at(1)->append_data(dataTBF);
                            }
                        }
                        else{
                            listFileSgd.at(0)->append_data(dataSync);
                            listFileSgd.at(1)->append_data(dataTBF);
                        }
                    }
                }
                blk_count++;
            }
        }
        else{
            //valuePckt = tmp_str_iVal.left(4).toUInt(&ok,16);
            valuePckt =  (tmp_str_iVal.mid(2,2) + tmp_str_iVal.left(2)).toUInt(&ok,16);
            listSyncModule.at(0)->dataADC.append(valuePckt & (0x0FFF));
            if(valuePckt & _TBV_msk)
               listSyncModule.at(0)->timeBreakVibro.append(true);
            else
                listSyncModule.at(0)->timeBreakVibro.append(false);
            if(valuePckt & _TBF_msk)
                listSyncModule.at(0)->timeBreakDetonation.append(true);
            else
                listSyncModule.at(0)->timeBreakDetonation.append(false);
            if(valuePckt & _CTB_msk)
                listSyncModule.at(0)->timeBreakDetonationConfirm.append(true);
            else
                listSyncModule.at(0)->timeBreakDetonationConfirm.append(false);

            valuePckt =  (tmp_str_iVal.right(2) + tmp_str_iVal.mid(4,2)).toUInt(&ok,16);
            //valuePckt = tmp_str_iVal.right(4).toUInt(&ok,16);
            listSyncModule.at(0)->dataADC.append(valuePckt & (0x0FFF));
            if(valuePckt & _TBV_msk)
               listSyncModule.at(0)->timeBreakVibro.append(true);
            else
                listSyncModule.at(0)->timeBreakVibro.append(false);
            if(valuePckt & _TBF_msk)
                listSyncModule.at(0)->timeBreakDetonation.append(true);
            else
                listSyncModule.at(0)->timeBreakDetonation.append(false);
            if(valuePckt & _CTB_msk)
                listSyncModule.at(0)->timeBreakDetonationConfirm.append(true);
            else
                listSyncModule.at(0)->timeBreakDetonationConfirm.append(false);
        }
    }
    emit dataSyncUpdate(listSyncModule.at(0));
//    if(isRecording_){
//        listFileSgd.at(0)->append_data(listSyncModule.at(0)->dataADC);
//        listFileSgd.at(1)->append_data(listSyncModule.at(0)->timeBreakDetonation);
//    }

    if(isRecording_){
        QVector<double> dataSync, dataTBF;
        for(int i=0; i < listSyncModule.at(0)->dataADC.size(); i++)
            dataSync.append(listSyncModule.at(0)->dataADC.at(i));

        for(int i=0; i < listSyncModule.at(0)->timeBreakDetonation.size(); i++)
            dataTBF.append(listSyncModule.at(0)->timeBreakDetonation.at(i));

        if(Offset){
            if(listSyncModule.at(0)->numPckt ==numPckt_){
                    for(int i=0; i < numMeasure_; i++){
                        dataSync.removeFirst();
                        dataTBF.removeFirst();
                    }

                    Offset = false;
                    listFileSgd.at(0)->append_data(dataSync);
                    listFileSgd.at(1)->append_data(dataTBF);
            }
        }
        else{
            listFileSgd.at(0)->append_data(dataSync);
            listFileSgd.at(1)->append_data(dataTBF);
        }
    }

}

void SyncModuleTranciever::AddToLog(QString strLog)
{
    emit message(strLog);
}

void SyncModuleTranciever::WriteToFile(QByteArray data)
{
    Q_UNUSED(data);
//    file_global.write(data.toHex());
//    file_global.flush();
}

void SyncModuleTranciever::setFileName(int idMeas, QString dirFile)
{
    Q_UNUSED(idMeas);
    if(listFileSgd.count() > 0){
        for(auto cnt=0; cnt<listFileSgd.count(); cnt++){
            if(listFileSgd.at(cnt)->getFileName()!="")
                listFileSgd.at(cnt)->close_data();
        }
    }
    else{
        listFileSgd.append(new single_segd_files());    //Sync
        listFileSgd.append(new single_segd_files());    //TBF
    }

    listFileSgd.at(0)->setFileName(dirFile+"/Sync_device.sgd"); //Sync
    listFileSgd.at(1)->setFileName(dirFile+"/TBF.sgd");         //TBF

    this->setSettings();

//    file_global.setFileName(dirFile+"/Syncro.txt");
//    if (!file_global.open(QIODevice::WriteOnly|QIODevice::Append))
//    {
//        qDebug() << "Ошибка при открытии файла";
//        return;
//    }
}

void SyncModuleTranciever::setSettings()
{
    QDate date_tmp = QDate::currentDate();
    QTime time_tmp = QTime::currentTime();
    int count_measures = 20000; //20 sec

    listFileSgd.at(0)->setData(date_tmp);
    listFileSgd.at(0)->setTime(time_tmp);
    listFileSgd.at(0)->setCounterByte(0);
    listFileSgd.at(0)->setFileNumber(1);
    listFileSgd.at(0)->setRecordLenght(1);
    listFileSgd.at(0)->setChannelSets(1);
    listFileSgd.at(0)->write_general_header();
    listFileSgd.at(0)->write_general_header_blk2();
    listFileSgd.at(0)->write_general_header_blk3();
    listFileSgd.at(0)->setChannelSetNumber(4);
    listFileSgd.at(0)->setChannelSetStartTime(0);
    listFileSgd.at(0)->setChannelSetEndTime(0);
    listFileSgd.at(0)->setDataLength(count_measures); //length data
    listFileSgd.at(0)->setNumberOfChannels(1);
    listFileSgd.at(0)->setChannelType((quint8)CHANNELSETS_TYPE_OTHER);
    listFileSgd.at(0)->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
    listFileSgd.at(0)->setAliasFilterSlope((quint16)1);
    listFileSgd.at(0)->write_header();
    listFileSgd.at(0)->open_data();
    listFileSgd.at(0)->write_data_header(4, 1);

    listFileSgd.at(1)->setData(date_tmp);
    listFileSgd.at(1)->setTime(time_tmp);
    listFileSgd.at(1)->setCounterByte(0);
    listFileSgd.at(1)->setFileNumber(1);
    listFileSgd.at(1)->setRecordLenght(1);
    listFileSgd.at(1)->setChannelSets(1);
    listFileSgd.at(1)->write_general_header();
    listFileSgd.at(1)->write_general_header_blk2();
    listFileSgd.at(1)->write_general_header_blk3();
    listFileSgd.at(1)->setChannelSetNumber(2);
    listFileSgd.at(1)->setChannelSetStartTime(0);
    listFileSgd.at(1)->setChannelSetEndTime(0);
    listFileSgd.at(1)->setDataLength(count_measures); //length data
    listFileSgd.at(1)->setNumberOfChannels(1);
    listFileSgd.at(1)->setChannelType((quint8)CHANNELSETS_TYPE_TIMEBREAK);
    listFileSgd.at(1)->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
    listFileSgd.at(1)->setAliasFilterSlope((quint16)1);
    listFileSgd.at(1)->write_header();
    listFileSgd.at(1)->open_data();
    listFileSgd.at(1)->write_data_header(2, 1);

}
