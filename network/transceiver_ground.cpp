#include "transceiver_ground.h"
#include "transceiver_ground.h"
#include <QTime>
#include <QDataStream>
Transceiver_ground::Transceiver_ground(QObject *parent) :
    QObject(parent)
{
    /* todo TODO: */
    for (int numberModule=0; numberModule < 8; numberModule++)
    {

        listGroundModules.append(new (pointsFromWGrounds));
        listGroundModules.at(numberModule)->numModule = numberModule;
        listGroundModules.at(numberModule)->oldPckt = -1;
        listVector.append(new QVector<double>);
        listOffset.append(true);
        //blk_count.append(new unsigned short int);
        blk_count.append(0);
        checkBLKCount.append(false);
    }

    numModule_ = 0;
    isRecording_ = false;
    dataPointTmp = new(pointsFromWGrounds);

    for(int i =0; i < 256; i++)
        dataPointTmp->data.append(maxValMissPacket);

    for(auto i =0 ; i < 4; i++){
        listCntFileSGD.append(0);
        listCntMeasSGD.append(0);
    }

}

Transceiver_ground::~Transceiver_ground()
{
    delete udp_socket;
    delete dataPointTmp;
    for (int i=0; listGroundModules.count(); i++)
        delete listGroundModules.at(0);
}

void Transceiver_ground::initialize(QString address, int port)
{
    this->portBind_ = port;
    host_ = QHostAddress(address);

}

void Transceiver_ground::start()
{
    udp_socket = new QUdpSocket();
    udp_socket->bind(portBind_);
    portDst_ = portBind_-1;
    connect(udp_socket, SIGNAL(readyRead()), this, SLOT(on_udp_data_rx()));
}

/* Прием данных */
void Transceiver_ground::on_udp_data_rx(void)
{
    QByteArray datagram;

    while(udp_socket->hasPendingDatagrams())
    {
    //datagram.fill(0, _sok_udp->pendingDatagramSize());
    datagram.resize(udp_socket->pendingDatagramSize());
    //QHostAddress address;
    //uint16_t port;
    //_sok_udp->readDatagram(datagram.data(), datagram.size(), &address, &port);
    QNetworkDatagram datagram_d = udp_socket->receiveDatagram(-1);

    datagram = datagram_d.data();
    //QDataStream in(&datagram, QIODevice::ReadOnly);
    quint64 Byt =  datagram.size() ;
    /* Если пришла команда настройки */
    if(Byt < 65){

        QString tmp_str = datagram.toHex();
        QString hand_package;
        hand_package = QString::number(ADC_ENABLE, 16); //define in hex to str
        //= "dedea0"; //adc enable
        if(tmp_str.startsWith(hand_package,Qt::CaseInsensitive))  //Start of the package
        {
            qDebug() << "Команда ВКЛ устройств:" << tmp_str;
            int devNum = tmp_str.mid(6,2).toInt();
            AddToLog(QString("Наземный модуль %1 ВКЛ ").arg(devNum));
            tmp_str.remove(0, 8);
            while(tmp_str.length()){
                devNum = tmp_str.mid(6,2).toInt();
                AddToLog(QString("Наземный модуль %1 ВКЛ ").arg(devNum));
                tmp_str.remove(0, 8);
            }
            return;
        }
        //hand_package = "dedea5";
        hand_package = QString::number(ADC_DISABLE, 16);
        if(tmp_str.startsWith(hand_package,Qt::CaseInsensitive))
        {
            int devNum = tmp_str.mid(6,2).toInt();
            AddToLog(QString("ОШИБКА Наземного модуля : %1").arg(devNum+1));
            return;
        }

        //hand_package = "dedeaf"; //search devices
        hand_package = QString::number(SEARCH_DEV, 16);
        if(tmp_str.startsWith(hand_package,Qt::CaseInsensitive))  //Find devices
        {

            QString message_str = tmp_str;
            uint8_t tmp_counter = message_str.count(hand_package, Qt::CaseInsensitive);
            //CounterDevicesReady += tmp_counter; //Подсчет количества девайсов
            message_str = message_str.remove(hand_package, Qt::CaseInsensitive); //Str without handler
           // ui->lineEdit->setText(QString::number(CounterDevicesReady));

            int dev_num_tmp = 0;
            for(uint i=0; i < tmp_counter; i++ ) {
                //AddToLog("Device " + message_str.mid(2*i,2) + " is ready", Qt::red);
                dev_num_tmp = message_str.mid(0,2).toInt();
                qDebug() << "DEvice " << dev_num_tmp;
                emit devGroundState(dev_num_tmp, true);
            }
            return;
        }

    }

    dataProcessingModuleGround(datagram);

//    if(isRecording_)
//        WriteToFile(datagram);
    }
}

void Transceiver_ground::send_cmd(void)
{

}

void Transceiver_ground::setRecord(bool isRecording)
{
    isRecording_ = isRecording;
}

bool Transceiver_ground::getRecord()
{
    return isRecording_;
}


void Transceiver_ground::send_Start(void)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out <<(quint8)ADC_START;
    out <<(quint8)0xF;  //all

    udp_socket->writeDatagram(block, host_, portDst_ );
}

void Transceiver_ground::send_Stop(void)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out <<(quint8)ADC_STOP;
    out <<(quint8)0xF;  //all

    udp_socket->writeDatagram(block, host_, portDst_ );
}

void Transceiver_ground::send_Settings_KU(int value, uint8_t numDev)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    int tmp = 0;
    switch (value) {
    case 1000:
        tmp = 1 << 0U;
        break;
    case 100:
        tmp = 1 << 1U;
        break;
    case 10:
        tmp = 1 << 2U;
        break;
    case 2:
        tmp = 1 << 3U;
        break;
    case 1:
        tmp = 1 << 4U;
        break;
    case -10:
        tmp = 1 << 5U;
        break;
    case -100:
        tmp = 1 << 6U;
        break;
    case -1000:
        tmp = 1 << 7U;
        break;
    }

    out <<(quint8)ADC_SETTING;
    out <<(quint8)0xF;  //all

    /* Передача нескольким устройствам коэф-та усилиения и ослабления */
    out <<(quint8)tmp; // резерв
    out <<(quint8)tmp; // настройки АЦП

    udp_socket->writeDatagram(block, host_, portDst_ );
}

void Transceiver_ground::send_search_devices()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out <<(quint8)SEARCH_NUMBER_DEVICES;
    out <<(quint8)0;

    /* Передача нескольким устройствам коэф-та усилиения и ослабления */

    udp_socket->writeDatagram(block, host_, portDst_ );
}

void Transceiver_ground::getDataOffsetDownHoles(quint16 numPckt)
{
        qDebug() << "num Pckt UP holes" << numPckt;
        numPckt_ = numPckt / 256;
        numMeasure_ = numPckt %  256;
        for (int numberModule=0; numberModule < 8; numberModule++)
            listOffset[numberModule] = true;
        qDebug() << "I am here" << "numPckt Up" << numPckt_ << "num Meas" << numMeasure_;

}
/* Здесь будет обработка всех данных от коммутаторов ~0.5 сек*/
void Transceiver_ground::dataProcessingModuleGround (QByteArray data)
{
    QString  tmp_str_iVal = "";  //Считываемое String
    QString  str_iVal = "";

    dataDatagramlen = data.length()*2;

    QString str_data = data.toHex();
    counterDatagram = 0;
    device_id = -1;

//    for(int i=0; i < 8; i++)    {
//        listGroundModules.at(i)->data.clear();
//    }

    while(counterDatagram < dataDatagramlen) {              // Length Files
       tmp_str_iVal = str_data.mid(counterDatagram,8);      //read 2 bytes + 2 bytes
       counterDatagram += 6;

       if(tmp_str_iVal.startsWith(handPackage,Qt::CaseInsensitive)) {  //Start of the package

           if(device_id> -1) {
                    emit dataGroundUpdate(listGroundModules.at(device_id));
               //listFileSgd.at(device_id)->append_data(*(QVector<float>*)(&listGroundModules.at(device_id)->data));

               if(isRecording_){
                   QVector<double> data;
                   for(int i=0; i < listGroundModules.at(device_id)->data.size(); i++)
                       data.append(listGroundModules.at(device_id)->data.at(i));

                   if(listOffset.at(device_id)){
                       if(listGroundModules.at(device_id)->numPckt ==numPckt_){
                               for(int i=0; i < numMeasure_; i++)
                                   data.removeFirst();

                               listOffset[device_id] = false;
                               qDebug() << "смещение" << "device" << device_id+1;
                               listFileSgd.at(device_id)->append_data(data);
                       } 
                   }
                   else
                       listFileSgd.at(device_id)->append_data(data);

               }
//               if(isRecording_)
//                   listFileSgd.at(device_id)->append_data(listGroundModules.at(device_id)->data);
           }

           device_id = str_data.mid(counterDatagram,2).toUInt();
           counterDatagram += 2;
           if(device_id >= 9)   qDebug() << "Error, data";
           else if(device_id < 0)   qDebug() << "Error, data";

           listGroundModules.at(device_id)->data.clear();

           tmp_str_iVal = str_data.mid(counterDatagram,2);     //get number packet
           counterDatagram += 2;
           listGroundModules.at(device_id)->numPckt = tmp_str_iVal.toInt(&ok,16);

           tmp_str_iVal = str_data.mid(counterDatagram,2);     //get crc msb
           counterDatagram += 2;
           listGroundModules.at(device_id)->CRC_MSB = tmp_str_iVal.toInt(&ok,16);

           tmp_str_iVal = str_data.mid(counterDatagram,2);     //get crc lsb
           counterDatagram += 2;
           listGroundModules.at(device_id)->CRC_LSB = tmp_str_iVal.toInt(&ok,16);

           /* Начнем отсчет и сравнение пакетов */
           if(!checkBLKCount.at(device_id)){
               blk_count[device_id] = listGroundModules.at(device_id)->numPckt;
               checkBLKCount[device_id] = true;
               blk_count[device_id]++;
               qDebug() << "blk" << blk_count[device_id] << "num Pckt" << listGroundModules.at(device_id)->numPckt;
           }
           else{
               if(blk_count[device_id] != listGroundModules.at(device_id)->numPckt){
                   qDebug() << "Error Packet Up hole. Device ID:" << device_id
                        << "CurrentPckt:" << listGroundModules.at(device_id)->numPckt << "last Pckt : "<< blk_count[device_id];
                   dataPointTmp->numPckt = blk_count[device_id];
                   dataPointTmp->numModule = device_id;

                   emit dataGroundUpdate(dataPointTmp);

                   if(isRecording_){
                       QVector<double> data;
                       for(int i=0; i < dataPointTmp->data.size(); i++)
                           data.append(dataPointTmp->data.at(i));

                       /* Сделать смещение */
                       if(listOffset.at(device_id)){
                           if(dataPointTmp->numPckt ==numPckt_){
                                   for(int i=0; i < numMeasure_; i++)
                                       data.removeFirst();

                                   listOffset[device_id] = false;
                                   qDebug() << "смещение" << "device" << device_id+1;
                                   listCntMeasSGD[device_id] += data.size();

                                   if(listCntMeasSGD[device_id] >= max_len_sgd){
                                       uint16_t ostatok = listCntMeasSGD[device_id]  - max_len_sgd;
                                       listFileSgd.at(device_id)->append_data(data, data.size()-ostatok);
                                       qDebug() << "ostatok" << ostatok;
                                       listCntFileSGD[device_id]+=1;
                                       this->update_sgd_files(device_id, "");

                                       listCntMeasSGD[device_id] = ostatok;
                                       listFileSgd.at(device_id)->append_data(data, ostatok);
                                   }
                                   else
                                       listFileSgd.at(device_id)->append_data(data);

                           }
                       }
                       else{
                           listCntMeasSGD[device_id] += data.size();
                           if(listCntMeasSGD[device_id] >= max_len_sgd){
                               uint16_t ostatok = listCntMeasSGD[device_id]  - max_len_sgd;
                               listFileSgd.at(device_id)->append_data(data, data.size()-ostatok);
                               qDebug() << "ostatok" << ostatok;
                               listCntFileSGD[device_id]+=1;
                               this->update_sgd_files(device_id, "");
                               listCntMeasSGD[device_id] = ostatok;
                               listFileSgd.at(device_id)->append_data(data, ostatok);
                           }
                           else
                               listFileSgd.at(device_id)->append_data(data);


                       }
                   }
               }
               blk_count[device_id]++;
           }
       }

       else {
           tmpMSB = tmp_str_iVal.left(4).toInt(&ok,16);
           tmpLSB = tmp_str_iVal.right(2).toInt(&ok,16);

           //value = (tmp1 << 16) | (tmp2);// & 0x00ffffff;   //24-bit ADC
           valuePckt = (tmpMSB << 8) | (tmpLSB >> 8);// & 0x00ffffff;   //24-bit ADC
           if(valuePckt & 0x800000){
               valuePckt |= 0xff000000;
           }

           listGroundModules.at(device_id)->data.append(valuePckt);
       }
    }
    emit dataGroundUpdate(listGroundModules.at(device_id));
    /* Выставлен offset */
    if(isRecording_){
        QVector<double> data;
        for(int i=0; i < listGroundModules.at(device_id)->data.size(); i++)
            data.append(listGroundModules.at(device_id)->data.at(i));

        if(listOffset.at(device_id)){
            if(listGroundModules.at(device_id)->numPckt ==numPckt_){
                    for(int i=0; i < numMeasure_; i++)
                        data.removeFirst();

                    listOffset[device_id] = false;
                    qDebug() << "смещение" << "device" << device_id+1;

                    listCntMeasSGD[device_id] += data.size();
                    if(listCntMeasSGD[device_id] >= max_len_sgd){
                        uint16_t ostatok = listCntMeasSGD[device_id]  - max_len_sgd;
                        qDebug() << "ostatok" << ostatok;
                        listFileSgd.at(device_id)->append_data(data, data.size()-ostatok);

                        listCntFileSGD[device_id]+=1;
                        this->update_sgd_files(device_id, "");
                        listCntMeasSGD[device_id] = ostatok;
                        listFileSgd.at(device_id)->append_data(data, ostatok);
                    }
                    else
                        listFileSgd.at(device_id)->append_data(data);

            }
        }
        else{
            listCntMeasSGD[device_id] += data.size();
            if(listCntMeasSGD[device_id] >= max_len_sgd){

                uint16_t ostatok = listCntMeasSGD[device_id]  - max_len_sgd;
                listFileSgd.at(device_id)->append_data(data, data.size()-ostatok);
qDebug() << "ostatok" << ostatok;
                listCntFileSGD[device_id]+=1;
                this->update_sgd_files(device_id, "");
                listCntMeasSGD[device_id] = ostatok;
                listFileSgd.at(device_id)->append_data(data, ostatok);
            }
            else
                listFileSgd.at(device_id)->append_data(data);
        }
    }

}

void Transceiver_ground::AddToLog(QString strLog)
{
    emit message(strLog);
}

void Transceiver_ground::WriteToFile(QByteArray data)
{
    Q_UNUSED(data);
//    file_global.write(data.toHex());
//    file_global.flush();
}

void Transceiver_ground::setFileName(int idMeas, QString dirFile)
{
    Q_UNUSED(idMeas);
//    if(file_global.isOpen()){
//        file_global.flush();
//        file_global.close();
//    }
//    file_global.setFileName(dirFile+"/Ground.txt");ф
//    if (!file_global.open(QIODevice::WriteOnly|QIODevice::Append))
//    {
//        qDebug() << "Ошибка при открытии файла";
//        return;
//    }
//    file_global.write(QString("Devices " + QString::number(numModule_) +'\n' ).toUtf8());
//    file_global.flush();

    for(auto i =0 ; i < 4; i++){
        listCntFileSGD[i] = 0;
    }

    for(uint8_t i=0; i<4; i++)
         update_sgd_files(i, dirFile);
}

void Transceiver_ground::update_sgd_files(quint8 numModule, QString dirFile)
{
    /* Если пустой, то создать просто новый файл */
    if(dirFile == ""){
        QString fileName = listFileSgd.at(numModule)->getFileName();
        listFileSgd.at(numModule)->close_data();
        uint cnt = fileName.lastIndexOf("_UpHole_device_");     //Найти номер файла sgd и заменить его на текущий
        listFileSgd.at(numModule)->setFileName(fileName.replace(cnt-1, 1, QString::number(listCntFileSGD[numModule])));
    }
    else{
        listFileSgd.at(numModule)->setFileName((dirFile+"/" + QString::number(listCntFileSGD[numModule]) + "_UpHole_device_%1.sgd").arg(numModule+1));
    }

    this->setSettings(numModule);
}
void Transceiver_ground::setSettings(quint8 numModule)
{
    QDate date_tmp = QDate::currentDate();
    QTime time_tmp = QTime::currentTime();
    int count_measures = 131070; //было 20sec

    listFileSgd.at(numModule)->setData(date_tmp);
    listFileSgd.at(numModule)->setTime(time_tmp);
    listFileSgd.at(numModule)->setCounterByte(0);
    listFileSgd.at(numModule)->setFileNumber(1);
    listFileSgd.at(numModule)->setRecordLenght(1);
    listFileSgd.at(numModule)->setChannelSets(1);
    listFileSgd.at(numModule)->write_general_header();
    listFileSgd.at(numModule)->write_general_header_blk2();
    listFileSgd.at(numModule)->write_general_header_blk3();
    listFileSgd.at(numModule)->setChannelSetNumber(3);
    listFileSgd.at(numModule)->setChannelSetStartTime(0);    /* Инкремент 2 мс) */
    listFileSgd.at(numModule)->setChannelSetEndTime(0);
    listFileSgd.at(numModule)->setDataLength(20000); //length data
    listFileSgd.at(numModule)->setNumberOfChannels(numModule_);
    listFileSgd.at(numModule)->setChannelType((quint8)CHANNELSETS_TYPE_UPHOLE);
    listFileSgd.at(numModule)->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
    listFileSgd.at(numModule)->setAliasFilterSlope((quint16)1);
    listFileSgd.at(numModule)->write_header();
    listFileSgd.at(numModule)->open_data();
    listFileSgd.at(numModule)->write_data_header(3, numModule+1);
}

void Transceiver_ground::setNumModule(int numModule)
{
    numModule_ = numModule;

    if(listFileSgd.count() > 0){
        for(auto cnt=0; cnt<listFileSgd.count(); cnt++){
            listFileSgd.at(cnt)->close_data();
            delete listFileSgd.at(cnt);
        }
        listFileSgd.clear();
    }
    for(auto i=0; i<4; i++)
        listFileSgd.append(new single_segd_files());
}
