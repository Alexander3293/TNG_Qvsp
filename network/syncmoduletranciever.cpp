#include "syncmoduletranciever.h"

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
    //    TCPTranciever_->connectToHost();
}

SyncModuleTranciever::~SyncModuleTranciever()
{
    qDebug() << "SYNC DESTRUCTOR";
    //    if(isConnected_ == true)
    //        TCPTranciever_->disconnectFromHost();
    //    disconnect(TCPTranciever_, SIGNAL(connected(bool)), this, SLOT(onClientConnected(bool)));
    //    disconnect(TCPTranciever_, SIGNAL(newMessage(QString)), this, SLOT(onNewMessage(QString)));
    //    disconnect(this, SIGNAL(connectReadAll(bool)),TCPTranciever_, SLOT(connectReadAll(bool)));
    //    //threadTCPClient_->quit();
    //    emit stopTCPClient();
    //    delete TCPTranciever_;
//    disconnectFromHost();
    stop();
    emit deleteTcpClient();
    threadTCPClient_->wait(15000);
    delete threadTCPClient_;
    qDebug() << "SYNC DESTRUCTOR END";
//    emit stopThread();
    //    stop();
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
    lastRecordTime_ = -1;
    //    if(cmd == SYNC_MODULE_CMD_START && channel == SYNC_MODULE_CHANNEL_VIBRO){
    if(cmd == SYNC_MODULE_CMD_START && (channel == SYNC_MODULE_CHANNEL_VIBRO || channel == SYNC_MODULE_CHANNEL_DETONATION)){
        lastRecordTime_ = time + timeWaitingTB_;
        time = time + timeWaitingTB_;
    }
    else {
        lastRecordTime_ = time; // +10 мс для взрыва чтобы успеть записать все
    }
    int tmp = time % 1000;
    sendCmd.append('0' + (tmp/100));
    tmp %= 100;
    sendCmd.append('0' + (tmp/10));
    tmp %= 10;
    sendCmd.append('0' + (tmp));
    counter_ = 0;
    lastCMD_ = cmd;
    lastChannel_ = channel;
    QTime t = QTime::currentTime();
    startTimeCmd_ = t.msecsSinceStartOfDay();
    emit sendMessage(sendCmd);
    qDebug() << "CMD" << lastRecordTime_ << QTime::currentTime();
    buffer_.clear();
    timeBuffer_.clear();
}

void SyncModuleTranciever::run()
{
    isConnected_ = false;
    SYNCACK_ = new bool{false};
    statusSyncModule_ = false;
    threadTCPClient_ = new QThread;
    TCPTranciever_ = new TcpClient(QHostAddress(SyncModuleTranciever::IP_ADDR_SYNC_MODULE), SyncModuleTranciever::PORT_SYNC_MODULE);
    TCPTranciever_->moveToThread(threadTCPClient_);
    connect(threadTCPClient_, SIGNAL(started()), TCPTranciever_, SLOT(run()) );
    connect(TCPTranciever_, SIGNAL(stopThread()), TCPTranciever_, SLOT(deleteLater()));
    connect(TCPTranciever_, SIGNAL(stopThread()), threadTCPClient_, SLOT(quit()), Qt::DirectConnection);
    connect(threadTCPClient_, SIGNAL(finished()), threadTCPClient_, SLOT(deleteLater()), Qt::DirectConnection);
    connect(this, &SyncModuleTranciever::disconnectFromHostSig, TCPTranciever_, &TcpClient::disconnectFromHost);
    connect(this, &SyncModuleTranciever::sendStopPck, TCPTranciever_, &TcpClient::sendDicconnectPck);
    connect(this, &SyncModuleTranciever::deleteTcpClient, TCPTranciever_, &TcpClient::stop);

    threadTCPClient_->start();

    connect(TCPTranciever_, SIGNAL(connected(bool)), this, SLOT(onClientConnected(bool)));
    connect(TCPTranciever_, SIGNAL(newMessage(QString)), this, SLOT(onNewMessage(QString)));
    connect(TCPTranciever_, SIGNAL(ack(bool)), this, SLOT(onSYNCAkc(bool)));
    connect(this, SIGNAL(connectReadAll(bool)),TCPTranciever_, SLOT(connectReadAll(bool)));
    connect(this, SIGNAL(sendMessage(QByteArray)), TCPTranciever_, SLOT(sendMessage(QByteArray)));
    connect(TCPTranciever_, SIGNAL(finishRecieve()),this,SLOT(finishRead()));
    connect(TCPTranciever_, SIGNAL(dataUpdate(QTime, QByteArray)), this, SLOT(onDataUpdate(QTime, QByteArray)));
    //    connect(TCPTranciever_, SIGNAL(globalStart(QTime)), this, SLOT(onGlobalStart(QTime)));
    connect(TCPTranciever_, SIGNAL(finishRecieve()), this, SLOT(onStopData()));
    connect(this, SIGNAL(bufferUpdate()), this, SLOT(onBufferUpdate()));
}

void SyncModuleTranciever::stop()
{
    qDebug() << "SYNC STOP";
    disconnect(TCPTranciever_, SIGNAL(connected(bool)), this, SLOT(onClientConnected(bool)));
    disconnect(TCPTranciever_, SIGNAL(newMessage(QString)), this, SLOT(onNewMessage(QString)));
    disconnect(this, SIGNAL(connectReadAll(bool)),TCPTranciever_, SLOT(connectReadAll(bool)));
//    delete TCPTranciever_;
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
        //        if(counter_ == 1 || counter_ % 1000 == 0)
        //            qDebug() << counter_ << QTime::currentTime();
        //        if(counter_ > 1698 && counter_ < 1702)
        //            qDebug() << buffer_.size();
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
                    emit SYNCAckError();
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

void SyncModuleTranciever::onSYNCAkc(bool ack)
{
    *SYNCACK_ = ack;
    if(ack == false){
        onStopData();
        if(lastCMD_ != SYNC_MODULE_CMD_RESET){
            qDebug() <<  "emit SYNCAckError();" << lastCMD_;
            emit SYNCAckError();
        }
    }
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

bool SyncModuleTranciever::isConnected() const
{
    return isConnected_;
}

void SyncModuleTranciever::setIsConnected(bool isConnected)
{
    isConnected_ = isConnected;
}

bool *SyncModuleTranciever::SYNCACK() const
{
    return SYNCACK_;
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

void SyncModuleTranciever::onClientConnected(bool isConnected) {
    isConnected_ = isConnected;
    if(isConnected_ == true)
    {

    }
    if(isConnected_ == false)
    {

    }
}
