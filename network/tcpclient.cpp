#include "tcpclient.h"

TcpClient::TcpClient(QHostAddress addr, int port, QObject *parent) : QObject(parent)
{
    addr_ = addr;
    port_ = port;
    isReadyReadFirst_ = false;
}

TcpClient::~TcpClient()
{
    if(timer_)
        delete timer_;
    if(sock_)
        delete sock_;
    QThread::currentThread()->exit();
    qDebug() << "TCP DESCRUCTOR";
}

void TcpClient::recieveMessage1()
{
//    qDebug() << "recieveMessage1()" << sock_->bytesAvailable();
    if(sock_->state() == QAbstractSocket::ConnectedState)
    {

        if(sock_->bytesAvailable() > 0){
            buffer_.append(sock_->readAll());
            emit bufferUpdate();
//            qDebug() << "recieveMessage1() 2" << buffer_.size();
        }
    }
}

void TcpClient::dataRead(bool status)
{
    if(status == false)
        return;

    counter_ = (lastCMD_->at(2) - '0') * 100 + (lastCMD_->at(3) - '0') * 10 + (lastCMD_->at(4) - '0');
    counter_ *= 1000 * sizeofdata_;
    connectReadAll(true);

    //qDebug() <<"in Data Read" << count << lastCMD_;
    //    QByteArray* data = new QByteArray();
    //    data->resize(sizeofdata_);
    //    emit globalStart(QTime::currentTime());
    //    for(int i = 0; i < count; i++)
    //    {
    //        data->fill(0);
    //bool status = recieveMessage2(data,sizeofdata_);
    //if(status == true){
    //qDebug() << "data" << i << QTime::currentTime() << (unsigned short)((data->at(1)) << (8)) + (data->at(0));
    //}
    //        else
    //            emit ack(false);
    //qDebug() << "Client Time " << QTime::currentTime().msecsSinceStartOfDay();
    //    }
    //    delete data;
    //    emit finishRecieve();
}

void TcpClient::parser()
{
//    qDebug() << "counter" << counter_ << buffer_.size();
    while(buffer_.size() >= sizeofPctLen_) {
//        qDebug() << "counter insight" << buffer_.size() << lastPacketSize_;
        QByteArray payloadSizeArray;
        quint16 payloadSize = 0;
        if(lastPacketSize_ <= 0){
            payloadSizeArray = buffer_.left(sizeofdata_);
            buffer_.remove(0, sizeofdata_);
            payloadSize = ((quint16)payloadSizeArray[1] << 8) + payloadSizeArray[0];
        }
        else {
            payloadSize = lastPacketSize_;
            lastPacketSize_ = -1;
        }
        if(buffer_.size() >= payloadSize){
            //get time
            QByteArray time = buffer_.left(sizeofTime_);
            buffer_.remove(0, sizeofTime_);
            std::reverse(time.begin(), time.end());
            QDataStream stream(time);
            quint64 timeFromEpoch = 0;
            stream >> timeFromEpoch; //check this
            QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(static_cast<qint64>((timeFromEpoch / 1000) + (timeFromEpoch % 1000 >= 500 ? 1 : 0)));
//            QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(std::roundl(static_cast<long double>(timeFromEpoch)) / static_cast<long double>(1000.0)));
            if(lastTime_.msecsTo(dateTime) != 10){
                qDebug() << "Time " << dateTime.toString("hh:mm:ss.zzz") << lastTime_.toString("hh:mm:ss.zzz") << counter_ << timeFromEpoch;
            }
            lastTime_ = dateTime;
            //get data
            QByteArray dataArr = buffer_.left(payloadSize - sizeofTime_);
            buffer_.remove(0, payloadSize - sizeofTime_);
            emit dataUpdate(dateTime.time(), dataArr);
//            qDebug() << dateTime.time() << dateTime.time().msecsSinceStartOfDay()    << "pct Time";
            counter_ -= dataArr.size();
            if(counter_ == 0){
                qDebug() << "finishRecieve";
                emit finishRecieve();
                buffer_.clear();
            }
        }
        else{
            qDebug() << "Else" << payloadSize << buffer_.size();
            lastPacketSize_ = payloadSize;
            break;
        }
    }
}

bool TcpClient::recieveMessage2(QByteArray* outputArray, int len)
{
    if(sock_->state() == QAbstractSocket::ConnectedState)
    {
        int counter = 0;
        while(sock_->bytesAvailable() < len && counter < 100) {
            counter ++;
            if(sock_->waitForReadyRead(200) == false)
                return false;
            if(sock_->isReadable() != true)
                return false;
        }
        if(sock_->bytesAvailable() < len)
            return false;

        if(len - sizeofPctLen_ != outputArray->size())
            outputArray->resize(len - sizeofPctLen_);

        //сюда можно добавить проверку переменной на первое вхождение
        //по нему отправлять globalStart
        if(isReadyReadFirst_ == true){
            isReadyReadFirst_ = false;
            emit globalStart(QTime::currentTime());
        }

        QByteArray arr = sock_->read(len);
        quint16 payLoad = static_cast<quint16>(((quint16)arr[1] << 8 ) + arr[0]);
        //        if(ntohs(payLoad) == sizeofACK_){
        if(payLoad == sizeofACK_){
            outputArray->replace(0, len - sizeofPctLen_, arr.right(sizeofACK_)); //check прием и ответа
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

void TcpClient::disconnectFromHost()
{
    qDebug() << "disconnectFromHost tcpClient";
    if(sock_->state() != QAbstractSocket::UnconnectedState){
        sock_->disconnectFromHost();
        sock_->abort();
    }
}

void TcpClient::sendDicconnectPck()
{
    qDebug() << "sendDicconnectPck tcpClient";
    if(sock_->state() == QAbstractSocket::ConnectedState){
        QByteArray endPacket;
        endPacket.append((char)1);
        endPacket.append((char)0);
        endPacket.append("X0000");
        sock_->write(endPacket);
        sock_->flush();
    }
}

void TcpClient::connectToHost()
{
    if(sock_->state() != QAbstractSocket::ConnectedState) {
        sock_->connectToHost(addr_, port_);
        sock_->waitForConnected(3000);
    }
}

void TcpClient::startTimer()
{
    emit connected(false);
    timer_->start(1500);
}

void TcpClient::run()
{
    sock_ = new QTcpSocket();
    timer_ = new QTimer();
    lastCMD_ = new QByteArray();
    lastCMD_->resize(sizeofACK_ - 1);
    startTimer();
    connect(sock_,SIGNAL(connected()),this,SLOT(stopTimer()));
    connect(sock_,SIGNAL(disconnected()),this,SLOT(startTimer()));
    connect(timer_,SIGNAL(timeout()),this,SLOT(connectToHost()));
    //    connect(sock_, SIGNAL(readyRead()),this,SLOT(recieveMessage()));
    connect(this, SIGNAL(ack(bool)), this, SLOT(dataRead(bool)));
}

void TcpClient::stop()
{
    qDebug() << "stop" << "tcpClient";
    timer_->stop();
    if(sock_->state() != QAbstractSocket::SocketState::UnconnectedState)
    {
        sock_->disconnectFromHost();
        sock_->abort();
    }
    emit stopThread();
    qDebug() << "TCP STOP";
}

void TcpClient::stopTimer()
{
    emit connected(true);
    timer_->stop();
}

void TcpClient::connectReadAll(bool stat)
{
    qDebug() << "connectReadAll" << stat;
    if(stat == true){
        disconnect(sock_, SIGNAL(readyRead()),this,SLOT(recieveMessage1()));
        connect(sock_, SIGNAL(readyRead()),this,SLOT(recieveMessage1()), Qt::QueuedConnection);
        disconnect(this, &TcpClient::bufferUpdate, this, &TcpClient::parser);
        connect(this, &TcpClient::bufferUpdate, this, &TcpClient::parser, Qt::QueuedConnection);
    }
    if(stat == false){
        disconnect(sock_, SIGNAL(readyRead()),this,SLOT(recieveMessage1()));
        disconnect(this, &TcpClient::bufferUpdate, this, &TcpClient::parser);
    }
}

void TcpClient::sendMessage(QByteArray data)
{
    if(sock_->state() != QAbstractSocket::ConnectedState){
        emit ack(false);
        return;
    }
    connectReadAll(false);
    buffer_.clear();
    if(sock_->state() == QAbstractSocket::ConnectedState){
        QByteArray tmp = sock_->readAll();
        tmp.clear();
        quint16 payloadSize = static_cast<quint16>(data.size());
        tmp.append(quint8(payloadSize));
        tmp.append(quint8(payloadSize >> 8));
        data.push_front(tmp);
        sock_->write(data);
        //        sock_->flush();
    }
    else {
        emit ack(false);
        qDebug() << "WORST ACK 1";
        return;
    }
    if (sock_->waitForBytesWritten(10) == true)
    {
        QByteArray* ackTmp = new QByteArray();
        ackTmp->resize(sizeofACK_);
        bool stat = recieveMessage2(ackTmp, sizeofACK_ + sizeofPctLen_);
        if(stat == false){
            emit ack(false);
            qDebug() << "WORST ACK 2";
            return;
        }
        if (checkAck(ackTmp, data.right(data.length() - sizeofPctLen_)) == true)
        {
            lastCMD_->replace(0, sizeofACK_ - 1, data.right(data.length() - sizeofPctLen_));
            isReadyReadFirst_ = true;
            emit ack(true);
            qDebug() <<"ack GOOD!!!";
        }
        else {
            emit ack(false);
            connectReadAll(true);
            qDebug() <<"ack WORST 3" << QString::fromStdString(ackTmp->toStdString());
        }
    }
}

bool TcpClient::checkAck(QByteArray* inputACK, QByteArray last)
{
    if(inputACK->size() < sizeofACK_ || last.size() < sizeofACK_ - 1)
        return false;
    for(int i = 0; i < sizeofACK_ - 1; i++)
        if(inputACK->at(i) != last.at(i))
            return false;
    quint8 status = inputACK->at(sizeofACK_ - 1);
    bool res = false;
    if((status & 0x01) != 0)
    {
        res = true;
    }
    return res;
}
