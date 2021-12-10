#include "create_smsp.h"
#include <QDebug>

create_smsp::create_smsp()
{
    pckt_type_ = 0x01;
    pckt_num_ = 10;
}

create_smsp::~create_smsp()
{

}

QByteArray create_smsp::getStartPacket(uint64_t timeStart, uint32_t measNum)
{
    QByteArray array;
    QDataStream out(&array, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::LittleEndian);


    SMS_Start sms;
    sms.time_start = timeStart;
    sms.meas_num = measNum;

    uint16_t pcktLen = (uint16_t) (23);

    out << (uint32_t)SMSP_START_;
    out << (uint16_t)pcktLen;


    out << (quint8)1;
    out << (quint8)SMSP_CMD;
    out << (quint8)START;
    out << (uint64_t) sms.time_start;
    out << (uint32_t)0; //always
    out << (quint16)SMSP_END_;

    pckt_num_++;

//    uint8_t _buffer[22];
//    *(uint32_t*)_buffer = SMSP_START_;
//    *(uint16_t*)(_buffer + 4) = 22;
//    *(uint8_t*)(_buffer + 6) = 1;
//    *(uint8_t*)(_buffer + 7) = SMSP_CMD;
//    *(uint8_t*)(_buffer + 8) = START;
//    *(uint64_t*)(_buffer + 9) = timeStart;
//    *(uint32_t*)(_buffer + 17) = 0;
//    *(uint32_t*)(_buffer + 21) = SMSP_END_;

//    QByteArray array(reinterpret_cast<const unsigned char*>(_buffer, 22));

    return array;
}

uint8_t getIndexOfGain(uint8_t gain)
{
//    qDebug() << "gain" << gain << gain - 1;
//    gain--;
    switch (gain) {
    //old
//    case 1:{
//        return 0x00; //0x01
//        break;
//    }
//    case 2:{
//        return 0x01; //0x02
//        break;
//    }
//    case 4:{
//        return 0x02; //0x03
//        break;
//    }
//    case 8:{
//        return 0x03;
//        break;
//    }
//    case 16:{
//        return 0x04;
//        break;
//    }
//    case 32:
//        return 0x05;
//        break;
//    default:
//        break;
//    }    switch (gain) {
    //updated
    case 1:{
        return 0x01;
        break;
    }
    case 2:{
        return 0x02;
        break;
    }
    case 4:{
        return 0x03;
        break;
    }
    case 8:{
        return 0x04;
        break;
    }
    case 16:{
        return 0x05;
        break;
    }
    case 32:
        return 0x06;
        break;
    default:
        break;
    }
}

QByteArray create_smsp::getSetupPacket(bool isSetupAll, uint8_t addr_node, uint8_t gain)
{
    QByteArray array;
    QDataStream out(&array, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::LittleEndian);

    SMS_Setup sms;
    sms.addr_node = addr_node;
    sms.rf_channel = 0;
    sms.rf_mode = 0;
    sms.rf_reserve = 0;
    sms.rf_power = 0;
//    sms.adc_mode = 0x24;//0x23;
    sms.adc_mode = 0x23;//0x24;
    sms.adc_gain = getIndexOfGain(gain);
    qDebug() << getIndexOfGain(gain);

    out << (uint32_t)SMSP_START_; //4
    uint16_t pcktLen = (uint16_t) (SMSP_FILEDS_SIZE + sizeof((quint8)SMSP_CMD_TYPES::SETUP) + 7);
    out << (uint16_t)pcktLen; //2

//    out << (quint8)0xFF; //0x01
    out << (quint8)0x01; //0xFF //1

    out << (quint8)SMSP_PACKET_TYPE::SMSP_CMD; //1
    if(isSetupAll)
//        out << (quint8)SMSP_CMD_TYPES::SETUP_ALL; //setup
        out << (quint8)SMSP_CMD_TYPES::SETUP; //setup //1
    else
        out << (quint8)SMSP_CMD_TYPES::SETUP;

//    out << sms.addr_node; //1 to all
    out << (quint8)0x01;
    out << sms.rf_channel;
    out << sms.rf_mode;
    out << sms.rf_reserve;
    out << sms.rf_power;
    out << sms.adc_mode;
    out << sms.adc_gain;

    out << (quint16)SMSP_END_;

    qInfo() << "WSDC SETUP"  << (uint32_t)SMSP_START_ << (uint16_t)pcktLen << (quint8)0x01 << (quint8)SMSP_PACKET_TYPE::SMSP_CMD <<
               (quint8)SMSP_CMD_TYPES::SETUP << 0x01 << sms.rf_channel << sms.rf_mode << sms.rf_reserve << sms.rf_power
               << sms.adc_mode << sms.adc_gain << (quint16)SMSP_END_;

    return array;
}

QByteArray create_smsp::getStatusPacket()
{
    QByteArray array;
    QDataStream out(&array, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::LittleEndian);

    SMS_Status sms;
    uint16_t pcktLen = (uint16_t) (11);

    out << (uint32_t)SMSP_START_;
    out << (uint16_t)pcktLen;
    out << (quint8)1;
    out << (quint8)SMSP_CMD;
    out << (quint8)GET_STATUS_ALL;
    out << (quint16)SMSP_END_;
    return array;
}

QByteArray create_smsp::getStopPacket()
{
    QByteArray array;
    QDataStream out(&array, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::LittleEndian);

    uint16_t pcktLen = (uint16_t) (11);

    out << (uint32_t)SMSP_START_;
    out << (uint16_t)pcktLen;

//    out << (quint8)pckt_num_;
    out << (quint8)0x01;
    out << (quint8)SMSP_CMD;
    out << (quint8)STOP;
    out << (quint16)SMSP_END_;

    pckt_num_++;
    return array;
}

QByteArray create_smsp::toByteArraySMSSetup(SMS_Setup &s)
{
    QByteArray result;
    QDataStream out(&result, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::LittleEndian);
    out << s.addr_node;
    out << s.rf_channel;
    out << s.rf_mode;
    out << s.rf_reserve;
    out << s.rf_power;
    out << s.adc_mode;
    out << s.adc_gain;
    return result;
}

QByteArray create_smsp::toByteArraySMSStart(SMS_Start &s)
{
    QByteArray result;
    QDataStream out(&result, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::LittleEndian);
    out << s.time_start;
    out << s.meas_num;
    return result;
}


