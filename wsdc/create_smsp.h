#ifndef SMSP_H
#define SMSP_H

#include <QByteArray>
#include <QDataStream>

enum SMSP_PACKET_TYPE : uint8_t // use SMSP_MASK to response
{
    SMSP_RSP = 0x00,//response
    SMSP_CMD = 0x01,//command
    SMSP_STATUS = 0x02,
    SMSP_DATA = 0x04,
    SMSP_MSG = 0x08
};
struct SMS_Status
{
    uint8_t addr_node;      // Сетевой адрес: номер МПГ
    int8_t rf_rssi;         // Уровень принимаемого сигнала (дБм)
    uint32_t pkts_recv;     // Общее число принятых пакетов
    uint32_t pkts_err;      // Общее число принятых пакетов с ошибками
    uint32_t pkts_sent;     // Общее число отправленных пакетов
    uint16_t bat_voltage;   // АКБ: напряжение (мВ)
    int16_t  bat_temp;      // АКБ: температура (градусы со знаком х10): -500..700
    uint16_t bat_chrg;      // АКБ: процент заряда от номинального (х100): 0..10000
};
class create_smsp
{
public:
   create_smsp();
   ~create_smsp();
   QByteArray getStartPacket(uint64_t timeStart, uint32_t measNum);
   QByteArray getSetupPacket(bool isSetupAll, uint8_t addr_node, uint8_t gain);
   QByteArray getStatusPacket();
   QByteArray getStopPacket();
private:

   struct SMS_Start
   {
       uint64_t time_start; // Время начала измерений
       uint32_t meas_num;   // Число измерений
   };

   struct SMS_Setup
   {
       uint8_t addr_node;   // Сетевой адрес: номер узла (МСП) в данном домене
       uint8_t rf_channel;  // Номер частотного канала
       uint8_t rf_mode;     // Режим модуляции
       uint8_t rf_reserve;  // Резервный параметр
       uint8_t rf_power;    // Выходная мощность передатчика
       uint8_t adc_mode;    // Режим измерений: частота дискретизации и разрядность АЦП
       uint8_t adc_gain;    // Коэффициент усиления предусилителя
   };


private:
   QByteArray toByteArraySMSSetup(SMS_Setup &s);

   QByteArray toByteArraySMSStart(SMS_Start &s);

   uint8_t pckt_num_;
   uint8_t pckt_type_;
   const uint32_t SMSP_START_ = 'S' | 'M' << 8 | 'S' << 16 | 'P' << 24;
   const uint16_t SMSP_END_ = 'S' | 'N' << 8;
   const uint16_t SMSP_FILEDS_SIZE = 4 + 2 + 1 + 1 + 2;//число байт для обязательных полей



   enum SMSP_CMD_TYPES : uint8_t
   {
       GET_STATUS = 0x00,
       GET_STATUS_ALL,
       GET_STATUS_CLUSTER,
       GET_STATUS_DOMAIN,
       SETUP,
       SETUP_ALL,
       START,
       STOP
   };
};

#endif // SMSP_H
