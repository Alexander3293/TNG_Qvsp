#include "checksum.h"
#include <QDebug>

checksum::checksum()
{
    traceCmd = 0;
    traceData=0;
}

bool checksum::checkCRC(quint8 *pdata, const uint8_t numModule)
{
    bool result = true;
    traceData = numModule * 16;
    traceCmd = numModule * 16 + 10;
    //quint8* pdata = (quint8*)&(point.data[0]);
    quint8 CRC7_cmd = (calc_CRC7_for_cmd(pdata + traceCmd) << 1) | 1;

    if (CRC7_cmd != *(pdata + traceCmd + 3)){
        result = false;
        //qDebug() << "error crc cmd" << "num module" << numModule;
    }

    quint8 CRC7_data = (calc_CRC7_for_data(pdata + traceData) << 1) | 1;

    if (CRC7_data != *(pdata + traceData + 15)){
        result = false;
        //qDebug() << "error crc data" << "num module" << numModule;
    }
    //delete [] pdata;
    return result;
}

quint8 checksum::calc_CRC7_for_cmd(const quint8* pcmd)
{
    quint8	mask;
    quint8	x;
    quint8	y;
    quint8  k;
    quint16	i;

    mask = 0x80;
    x = pcmd[0];
    if ((x & 0x80) != 0) x ^= 0x89;

    k  = pcmd[1];
    for (i = 0; i < 8; i++)
    {
        y = ((x << 1) & 0xFE);
        if ((k & mask) != 0) y++;

        if ((y & 0x80) != 0) x = y ^ 0x89;
        else x = y;
        mask = mask >> 1;
    }

    mask = 0x80;
    k = pcmd[2];
    for (i = 0; i < 8; i++)
    {
        y = ((x << 1) & 0xFE);
        if ((k & mask) != 0) y++;

        if ((y & 0x80) != 0) x = y ^ 0x89;
        else x = y;
        mask = mask >> 1;
    }

    for (i = 0; i < 7; i++)
    {
        y = ((x << 1) & 0xFE);

        if ((y & 0x80) != 0) x = y ^ 0x89;
        else x = y;
        mask = mask >> 1;
    }

    return x;
}
quint8 checksum::calc_CRC7_for_data(const quint8* pcmd)
{
    quint8	mask;
    quint8	x;
    quint8	y;
    quint8	k;
    quint16	i;
    quint16	j;

    x = pcmd[0];
    if ((x & 0x80) != 0) x ^= 0x89;

    for (j = 1; j < 15; j++)
    {
        mask = 0x80;
        k  = pcmd[j];
        for (i = 0; i < 8; i++)
        {
            y = ((x << 1) & 0xFE);
            if ((k & mask) != 0) y++;

            if ((y & 0x80) != 0) x = y ^ 0x89;
            else x = y;
            mask = mask >> 1;
        }
    }

    for (i = 0; i < 7; i++)
    {
        y = ((x << 1) & 0xFE);

        if ((y & 0x80) != 0) x = y ^ 0x89;
        else x = y;
        mask = mask >> 1;
    }

    return x;
}



/**
 * @brief Accumulate the MCRF4XX CRC16 by adding one char at a time.
 *
 * The checksum function adds the hash of one char at a time to the
 * 16 bit checksum (uint16_t).
 *
 * @param data new char to hash
 * @param crcAccum the already accumulated checksum
 **/


inline void checksum::crc_accumulate(uint8_t data, uint16_t *crcAccum)
{
        /*Accumulate one byte of data into the CRC*/
        uint8_t tmp;

        tmp = data ^ (uint8_t)(*crcAccum &0xff);
        tmp ^= (tmp<<4);
        *crcAccum = (*crcAccum>>8) ^ (tmp<<8) ^ (tmp <<3) ^ (tmp>>4);
}

/**
 * @brief Initiliaze the buffer for the MCRF4XX CRC16
 *
 * @param crcAccum the 16 bit MCRF4XX CRC16
 */
inline void crc_init(uint16_t* crcAccum)
{
    *crcAccum = X25_INIT_CRC;
}


/**
 * @brief Calculates the MCRF4XX CRC16 checksum on a byte buffer
 *
 * @param  pBuffer buffer containing the byte array to hash
 * @param  length  length of the byte array
 * @return the checksum over the buffer bytes
 **/
 inline uint16_t checksum::crc_calculate(const uint8_t* pBuffer, uint16_t length)
{
    uint16_t crcTmp;
    crc_init(&crcTmp);
    while (length--) {
        crc_accumulate(*pBuffer++, &crcTmp);
    }
    return crcTmp;
}


/**
 * @brief Accumulate the MCRF4XX CRC16 CRC by adding an array of bytes
 *
 * The checksum function adds the hash of one char at a time to the
 * 16 bit checksum (uint16_t).
 *
 * @param data new bytes to hash
 * @param crcAccum the already accumulated checksum
 **/
inline void checksum::crc_accumulate_buffer(uint16_t *crcAccum, const char *pBuffer, uint16_t length)
{
    const uint8_t *p = (const uint8_t *)pBuffer;
    while (length--) {
        crc_accumulate(*p++, crcAccum);
    }
}

bool checksum::checkCRC_UpHole(QVector<double> &data, uint16_t len, uint8_t crc_msb, uint8_t crc_lsb)
{
    uint16_t tmp_crc = 0;
    uint32_t data32 = 0;
    uint8_t *pdata = new uint8_t [len*3];
    for(int i = 0 ; i < len; i++){
        data32 = uint32_t(data.at(i));
        *(pdata+2+i*3) = (uint8_t)(data32 & 0x000000ff);
        *(pdata+1+i*3) = (uint8_t)((data32 & 0x0000ff00) >> 8);
        *(pdata+0+i*3) = (uint8_t)((data32 & 0x00ff0000) >> 16);
    }

    tmp_crc = crc_calculate(pdata, len*3);
    delete [] pdata;

    if(tmp_crc == (crc_lsb << 8 | crc_msb))
        return true;
    else
        return false;

}
