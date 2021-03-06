#include "transceiver_ground.h"
#include <QTime>
Transceiver_ground::Transceiver_ground(QObject *parent) :
    QObject(parent)
{
    /* todo TODO: */
    for (int numberModule=0; numberModule < 8; numberModule++)
    {

        listGroundModules.append(new (pointsFromWGrounds));
        listGroundModules.at(numberModule)->numModule = numberModule;
        listVector.append(new QVector<double>);
    }

    logFileName  = QString("D:/Test/Gr.txt");
//            .arg(QDate::currentDate().toString("yyyy_MM_dd"))
//            .arg(QTime::currentTime().toString("hh_mm_ss_zzz"));

    file_global.setFileName(logFileName);
    if (!file_global.open(QIODevice::WriteOnly|QIODevice::Append))
    {
        qDebug() << "Ошибка при открытии файла";
        return;
    }

}

Transceiver_ground::~Transceiver_ground()
{
   delete udp_socket;
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
    if(Byt < 65)
    {

        QString tmp_str = datagram.toHex();
        QString hand_package;
        hand_package = QString::number(ADC_ENABLE, 16); //define in hex to str
        //= "dedea0"; //adc enable
        if(tmp_str.startsWith(hand_package,Qt::CaseInsensitive))  //Start of the package
        {
                //AddToLog("ADC ENABLE device: " + tmp_str.right(2), Qt::red);
            AddToLog("ADC ENABLE device: ");
            qInfo() << "Enable";
                return;
        }
        //hand_package = "dedea5";
        hand_package = QString::number(ADC_DISABLE, 16);
        if(tmp_str.startsWith(hand_package,Qt::CaseInsensitive))
        {
           // AddToLog("ADC NOT ENABLE device: " + tmp_str.right(2), Qt::red);
            AddToLog("ADC NOT ENABLE device: ");
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

            for(uint i=0; i < tmp_counter; i++ ) {
             //   AddToLog("Device " + message_str.mid(2*i, 2) + " is ready", Qt::red);
            }
            return;
        }

    }

    dataProcessingModuleGround(datagram);
    WriteToFile(datagram);

    }
}

void Transceiver_ground::send_cmd(void)
{

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

void Transceiver_ground::send_Settings_KU(int value)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out <<(quint8)ADC_SETTING;
    out <<(quint8)0xF;  //all

    /* Передача нескольким устройствам коэф-та усилиения
     * и ослабления */
    out <<(quint8)value; // резерв
    out <<(quint8)value; // настройки АЦП

    udp_socket->writeDatagram(block, host_, portDst_ );
}
/* Здесь будет обработка всех данных от коммутаторов ~0.5 сек*/
void Transceiver_ground::dataProcessingModuleGround (QByteArray data)
{
    QString  tmp_str_iVal;  //Считываемое String
    QString  str_iVal;

    dataDatagramlen = data.length()*2;
    QString str_data = data.toHex();
    counterDatagram = 0;
    device_id = -1;

    for(int i=0; i < 8; i++)    {
        listGroundModules.at(i)->data.clear();
    }

    while(counterDatagram < dataDatagramlen) {              // Length Files
       tmp_str_iVal = str_data.mid(counterDatagram,8);      //read 2 bytes + 2 bytes
       counterDatagram += 8;

       if(tmp_str_iVal.startsWith(handPackage,Qt::CaseInsensitive)) {  //Start of the package

           if(device_id> -1) emit dataGroundUpdate(listGroundModules.at(device_id));

           device_id = tmp_str_iVal.right(2).toInt();
           //nowTime_ = QTime(0,0,0).secsTo(QTime::currentTime());
           tmp_str_iVal = str_data.mid(counterDatagram,2);     //get number packet
           counterDatagram += 2;
           listGroundModules.at(device_id)->numPckt = tmp_str_iVal.toInt(&ok,16);
           //listGroundModules.at(device_id)->numModule = device_id;    //передаю в конструкторе
       }

       else {
           tmpMSB = tmp_str_iVal.left(4).toInt(&ok,16);
           tmpLSB = tmp_str_iVal.right(4).toInt(&ok,16);

           //value = (tmp1 << 16) | (tmp2);// & 0x00ffffff;   //24-bit ADC
           valuePckt = (tmpMSB << 8) | (tmpLSB >> 8);// & 0x00ffffff;   //24-bit ADC
           if(valuePckt & 0x800000){
               valuePckt |= 0xff000000;
           }

           listGroundModules.at(device_id)->data.append(valuePckt);
       }
    }

    emit dataGroundUpdate(listGroundModules.at(device_id));
}

void Transceiver_ground::AddToLog(QString strLog)
{
    emit message(strLog);
}

void Transceiver_ground::WriteToFile(QByteArray data)
{
    file_global.write(data.toHex());
    file_global.flush();
}
