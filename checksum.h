#ifndef CHECKSUM_H
#define CHECKSUM_H
#include <QObject>
#include <stdint.h>

#define X25_INIT_CRC 0xffff
#define X25_VALIDATE_CRC 0xf0b8

class checksum: public QObject
{
Q_OBJECT
public:
    checksum();
    bool checkCRC(quint8 *pdata, const uint8_t numModule);
    quint8 calc_CRC7_for_cmd(const quint8* pcmd);
    quint8 calc_CRC7_for_data(const quint8* pcmd);
    inline uint16_t crc_calculate_x25(const uint8_t* pBuffer, uint16_t length);
    inline void crc_accumulate(uint8_t data, uint16_t *crcAccum);
    inline void crc_accumulate_buffer(uint16_t *crcAccum, const char *pBuffer, uint16_t length);
private:
    int traceData;
    int traceCmd;
};

#endif // CHECKSUM_H
