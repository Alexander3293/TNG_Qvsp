#include "work_with_project/single_segd_rev2_files.h"

single_segd_rev2_files::single_segd_rev2_files(QObject *parent) :
    QObject(parent),
    date_(QDate::currentDate()),
    time_(QTime::currentTime()),
    numGenBlks_(2),
    generalConstant_(0),
    manufactureCode_(0),
    manufactureSerialNumber_(0),
    baseScanInterval_(10),
    polarity_(0),
    scansBlock_(0),
    scanTypes_(1),
    channelSets_(4),
    skewBlocks_(0),
    extendedHeaderBlocks_(0),
    externalHeaderBlocks_(0),
    scanTypeNumber_(1),
    channelSetStartTime_(0),
    null_(0),
    descaleMultiplier_(0),
    channelGainControlMethod_(3),
    aliasFilterFrequency_(0),
    aliasFilterSlope_(100),
    lowCutFilter_(0),
    lowCutFilterSlope_(0),
    firstNotchFilter_(0),
    secondNotchFilter_(0),
    thirdNotchFilter_(0),
    extendedHeader_(new quint8(32))
{
    file_ = new QFile();
    fileRead_ = new QFile();
    bytesPerScan_ = new quint8[3];
    for(int i = 0; i < bytesPerScanSize_; i++)
        bytesPerScan_[i] = 0;
    counterByte_ = 0;
    counterSpace_ = 1000;
    numOfSamples_ = 0;

    year_   = (quint8) hex_from_dec(date_.year()%100);
    day_    = (quint16)hex_from_dec(date_.dayOfYear());
    numGenBlks_ = (quint16)hex_from_dec(numGenBlks_);
    hour_   = (quint8) hex_from_dec(time_.hour());
    minute_ = (quint8) hex_from_dec(time_.minute());
    second_ = (quint8) hex_from_dec(time_.second());
    baseScanInterval_ = (quint8) hex_from_dec(baseScanInterval_);
}

single_segd_rev2_files::~single_segd_rev2_files()
{
    delete bytesPerScan_;
    delete(extendedHeader_);
    if (file_->isOpen() == true)
    {
        file_->flush();
        file_->close();
    }
    delete(file_);
}

void single_segd_rev2_files::setTime(const QTime &time)
{
    hour_   = (quint8) hex_from_dec(time.hour());
    minute_ = (quint8) hex_from_dec(time.minute());
    second_ = (quint8) hex_from_dec(time.second());
}

void single_segd_rev2_files::setData(const QDate &date)
{
    year_   = (quint8) hex_from_dec(date.year()%100);
    day_    = (quint16)hex_from_dec(date.dayOfYear());
}

void single_segd_rev2_files::write_spacer()
{
    if (!file_->open(QIODevice::Append))
    {
        qDebug() << file_->errorString();
        return;
    }
    QDataStream spacer;
    //    header.setCodec("windows-1251");
    spacer.setDevice(file_);
    for(int i = counterByte_; i < counterSpace_; i++)
        spacer << (unsigned char) 43;
    file_->flush();
    file_->close();
}

unsigned char* single_segd_rev2_files::convertData(double value)
{
    unsigned char* result = new unsigned char[4];
    for(int i = 0; i < 4; i++)
        result[i] = 0;

    if(value != 0.0)
    {
        bool sign = value < 0.0 ? true : false;
        //        if(value < 0.0){
        //            sign = true;
        //        }

        unsigned int leftRadix = 0;
        double rightRadix = 0.0;
        if(sign == true){
            value *= -1;
        }
        leftRadix = qAbs(qFloor(value));    //округлить
        rightRadix = value - leftRadix;

        int degree = 0;
        quint64 tmp = 0;
        for( ; tmp <= static_cast<quint64>(leftRadix); degree++) {
            tmp = (static_cast<quint64>(1) << static_cast<quint64>(4)*static_cast<quint64>(degree));
        }
        degree-=1;
        int degree64 = (degree) + 64;
        //qDebug() << value << degree << degree64;

        unsigned char bytes[4];
        for (int i = 0; i < 4; i++) {
            bytes[i] = 0;
        }
        if(sign == true)
            bytes[0] ^= (1 << 7);

        if(degree64 < 127 && degree64 > 0)
            bytes[0] += degree64;

        else {
            bytes[0] ^= (1 << 6);
            degree = 0;
            degree64 = 64;
        }
        int degree4 = degree * 4;
        //        leftRadix = leftRadix >> degree4;
        //        quint32 rightRadix = quint32((value - leftRadix) * qPow(2, 23 - degree4));

        QBitArray bitArray;
        bitArray.clear();
        bitArray.resize(24);
        bitArray.fill(0);

        if (degree4 < 24) {
            int numByte = degree4 / 8;
            int offset = degree4 - numByte * 8;
            if(offset == 0)
                numByte--;
            int j = numByte * 8 + offset;
            if (numByte >= 0){
                for(int i = 0; i < degree4; i++) {
                    quint8 tmpVal = (quint8)(leftRadix >> (i));
                    if ( (tmpVal & (quint8) 0x01) == false){
                        bitArray.setBit(j, false);
                    }
                    else{
                        bitArray.setBit(j, true);
                    }
                    j++;
                    if(j % 8 == 0){
                        numByte--;
                        j = numByte * 8;
                    }
                }

            }
        }
        else {
            while(leftRadix >= ((quint32)(1 << 23))){
                leftRadix = leftRadix >> 4;
                degree4-=4;
            }

            int numByte = degree4 / 8;
            int offset = degree4 - numByte * 8;
            if(offset == 0)
                numByte--;

            int j = numByte * 8 + offset;

            if(numByte >= 0) {
                for(int i = 0; i < 23; i++) {
                    quint8 tmpVal = (quint8)(leftRadix >> (i));

                    if ( (tmpVal & (quint8)0x01) == false){
                        //qDebug() << "tmpVal" << tmpVal << "leftRadix" << leftRadix << "j" << j;
                        //TODO
                        bitArray.setBit(j, false);  // TODO //умирает здесь
                    }
                    else{
                        bitArray.setBit(j, true);
                    }
                    j++;
                    if(j % 8 == 0){
                        numByte--;
                        j = numByte * 8;
                    }
                }
            }
        }
        //        if(rightRadix != 0.0 && degree4 < 23) {
        if(degree4 < 23) {
            int numByte = degree4 / 8;
            int offset = degree4 - numByte * 8;

            int j = 0;
            if(offset == 0)
                j = (numByte + 1) * 8 + offset - 1;
            else
                j = numByte * 8 + offset - 1;

            if (numByte >= 0 && numByte <3)
                for(int i = degree4; i < 24; i++) {
                    //преобразование дроби из 10 системы в 2
                    rightRadix *= 2;
                    if (rightRadix == 0.0){
                        bitArray.setBit(j, false);
                    } else {
                        if (rightRadix >= 1){
                            bitArray.setBit(j, true); //23 - 1 - i + degree4
                            rightRadix -= 1;
                        }
                        else {
                            bitArray.setBit(j, false);
                        }
                    }
                    if(j % 8 == 0){
                        numByte++;
                        j = (numByte + 1) * 8;
                    }
                    j--;
                }
        }

        for(int i = 0; i < 8; i ++) {
            if (bitArray[i] == true)
                bytes[1] |= (1 << i);
        }
        for(int i = 8; i < 16; i ++) {
            if (bitArray[(i)] == true)
                //                bytes[2] |= (1 << (i % 8));
                bytes[2] |= (1 << (i % 8));
        }
        for(int i = 16; i < 23; i ++) {
            if (bitArray[(i)] == true)
                bytes[3] |= (1 << (i % 8));
        }

        bytes[3] &= ~(1 << 7);
        // result = (quint32)( (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3]);
        result[0] = bytes[0];
        result[1] = bytes[1];
        result[2] = bytes[2];
        result[3] = bytes[3];

        //        result[0] = bytes[3];
        //        result[1] = bytes[2];
        //        result[2] = bytes[1];
        //        result[3] = bytes[0];

        //        qDebug() << value << (quint32)( (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3]);
        return result;
    }
    //    result = (quint32)( ((quint8)0x00 << 24) | ((quint8)0x00 << 16) | ((quint8)0x00 << 8) | (quint8)0x00);
    return result;
}

unsigned char *single_segd_rev2_files::convertData2(double value)
{
    unsigned char* result = new unsigned char[4];
    for(int i = 0; i < 4; i++)
        result[i] = 0;

    if(value == 0.0)
        return result;

    //определяем бит знака +-
    bool sign = value < 0.0 ? true : false;

    //разделяем число на целое и дробь
    unsigned int leftRadix = qFloor(value);
    double rightRadix = (value - leftRadix);

    //определем степень СС (1 байт)
    int degree = 0;
    quint64 tmp = 0;
    for( ; tmp < static_cast<quint64>(leftRadix); degree++) {
        tmp = (static_cast<quint64>(1) << static_cast<quint64>(4 * degree));
    }
    degree-=1; //??? может 2
    int degree64 = (degree) + 64;

    //массив временного хранения данных
    unsigned char bytes[4];
    for (int i = 0; i < 4; i++) {
        bytes[i] = 0;
    }

    //установка бита знака на старший 7 бит 1 байт
    if(sign == true)
        bytes[0] ^= (1 << 7);

    //запись СС степени 64 в 1 байт
    if(degree64 < 127 && degree64 > 0){
        bytes[0] |= degree64;
    }
    else {
        bytes[0] ^= (1 << 6);
        degree64 = 64;
        degree = 0;
    }

    //сокращение числа по степени 16
    unsigned int remainder = leftRadix % (static_cast<int>(qPow(16, degree)));
    unsigned int quotient = leftRadix / (qPow(16, degree));

    int degree4 = degree * 4;
    QBitArray bitArray;
    bitArray.clear();
    bitArray.resize(23);
    bitArray.fill(0);

    if (degree4 < 24) {
        for(int i = 0; i < degree4; i++) {
            quint8 tmpVal = (quint8)(quotient >> (i));
            if ( (tmpVal & (quint8)0x01) == false)
                bitArray.setBit(i, false);
            else
                bitArray.setBit(i, true);
        }
    }
    else {
        while(leftRadix >= ((quint32)(1 << 23)))
            leftRadix = leftRadix >> 1;
        for(int i = 0; i < 23; i++) {
            quint8 tmpVal = (quint8)(leftRadix >> (i));
            if ( (tmpVal & (quint8)0x01) == false)
                bitArray.setBit(23 - 1 - i, false);
            else
                bitArray.setBit(23 - 1 - i, true);
        }
    }

}

void single_segd_rev2_files::write_general_header()
{
    if (!file_->open(QIODevice::WriteOnly))
    {
        qDebug() << file_->errorString();
        return;
    }
    recordType_ = recordTypeNormal;

    QDataStream generalHeader;
    generalHeader.setDevice(file_);
    generalHeader <<  (quint16) hex_from_dec(fileNumber_);  //[1-2]
    formatCode_ = hex_from_dec((quint16) FORMATRECORD_32bit_HEX_Demulti);   //[3-4]
    generalHeader << formatCode_;
    for(int i = 0; i < generalConstantSize_; i++) {
        generalHeader <<  (quint8) hex_from_dec((quint8) (generalConstant_ >> (i*8))); // General constant [5-10]

    }
    generalHeader << year_;     //[11]
    numGenBlks_ = 1; //for rev 2.1
    numGenBlks_ = (quint16)(numGenBlks_) << 12U;
    generalHeader << (quint16)(day_|numGenBlks_); //Тут количество блоков general header и julian day[12-13]
    generalHeader << hour_;     //[14]
    generalHeader << minute_;   //[15]
    generalHeader << second_;   //[16]
    generalHeader <<  (quint8) hex_from_dec(manufactureCode_);  //[17-19]
    generalHeader <<  (quint16) hex_from_dec(manufactureCode_);

    for(int i = 0; i < 3; i++)
    {
        generalHeader <<  (quint8) hex_from_dec((quint8)0); //3 bytes 0 [20-22]
    }
    generalHeader << baseScanInterval_;                      //[23]
    generalHeader <<  (quint8) hex_from_dec(polarity_);     //[24]
    generalHeader <<  (quint8) hex_from_dec(0);             //[25] must be 0
    recordLength_ = 10;
    uint16_t recordType = (uint16_t)hex_from_dec(recordType_*1000 + ((recordLength_ * 10)));//(uint16_t)0x8995;//hex_from_dec(recordType_);
    generalHeader << (uint16_t)0x8fff;
//    generalHeader <<  (quint8)0x1F;     //[26] rec type
//    generalHeader <<  (quint8) 0xFF;    //[27] rec length
    generalHeader <<  (quint8) hex_from_dec(scanTypes_);            //[28]
    generalHeader <<  (quint8) hex_from_dec(channelSets_);          //[29]
    generalHeader <<  (quint8) hex_from_dec(skewBlocks_);           //[30]
    extendedHeaderBlocks_ = 1;
    generalHeader <<  (quint8) hex_from_dec(extendedHeaderBlocks_); //[31]
    generalHeader <<  (quint8) hex_from_dec(externalHeaderBlocks_); //[32]

    file_->flush();
    file_->close();
}

void single_segd_rev2_files::write_general_header_blk2()
{
    if (!file_->open(QIODevice::Append))
    {
        qDebug() << file_->errorString();
        return;
    }

    QDataStream generalHeader;
    generalHeader.setDevice(file_);
    /* Extended Files Number (1-3 bytes) */
    generalHeader <<  (quint16) hex_from_dec(0);
    generalHeader <<  (quint8) hex_from_dec(1);
    /* Extended Channel set/scan types 4-5 bytes */
    generalHeader <<  (quint16) hex_from_dec(0);    //not used
    /* Extended Header Blks 6-7 bytes*/
    generalHeader <<  (quint16) hex_from_dec(0);    //not used
    /* External SKew Blks 8-9*/
    generalHeader <<  (quint16) hex_from_dec(0);    //not used
    /* Zeros 10*/
    generalHeader <<  (quint8) hex_from_dec(0);    //not used
    /* SEG-D Version. This version is 2.1  11-12 bytes*/
    generalHeader <<  (quint8) 2;   //major revision number and minor revision number
    generalHeader <<  (quint8) 1;   //major revision number and minor revision number
    //generalHeader <<  (quint8) hex_from_dec(2);   //
    /* Number of blocks General Trailer 13-14 bytes */
    generalHeader <<  (quint16) hex_from_dec(0);    //not used
    /* Extended Record  3 bytes general_header_blk1 bytes 26 & 27 sets 0xFFF, 15-17 bytes*/
//    generalHeader <<  (quint8) 0x01;
//    generalHeader <<  (quint8) 0xff;
//    generalHeader <<  (quint8) 0xfe;

    generalHeader <<  (quint8) 0x00;
    generalHeader <<  (quint8) 0x00;
    generalHeader <<  (quint8) 0x00;
    /* Zeros 18 */
    generalHeader <<  (quint8) 0;
    /* Num blk 19 */
    generalHeader <<  (quint8) hex_from_dec(2); //header block type
    /* Zeros 20 */
    generalHeader <<  (quint8) 0;
    /* Sequnce number 21-22 byte */
    generalHeader <<  (quint16) hex_from_dec(1);
    /* Zeros 22-32 */
    for (uint8_t i=22; i < 32; i++)
        generalHeader <<  (quint8) 0;

    file_->flush();
    file_->close();
}

void single_segd_rev2_files::write_header()
{
    if (!file_->open(QIODevice::Append))
    {
        qDebug() << file_->errorString();
        return;
    }
    QDataStream header;
    //    header.setCodec("windows-1251");
    header.setDevice(file_);

    //channelSetEndTime_ = recordLength_;

    header << (quint8) hex_from_dec (scanTypeNumber_);              // [1]
    header << (quint8) hex_from_dec (channelSetNumber_);            // [2]
    header << (quint16)((int)channelSetStartTime_*(1000/2));        // [3-4]
    header << (quint16)(channelSetEndTime_);                        // [5-6]
    header << (quint16) hex_from_dec (descaleMultiplier_);          // [7-8]
    header << (quint16) hex_from_dec (numberOfChannels_);           // [9-10]
    header << (quint8)  (channelType_<<4);                           // [11]

    header << (quint8) hex_from_dec(channelGainControlMethod_); //0[4 bits] + 3[4 bits] //12
    header << (quint16) hex_from_dec (aliasFilterFrequency_);               //13-14
    header << (quint8) (aliasFilterSlope_) <<  (quint8) (aliasFilterSlope_ >> 8);   //15-16
    header << (quint16) hex_from_dec (lowCutFilter_);                               //17-18
    header << (quint16) hex_from_dec (lowCutFilterSlope_); // нет такого ???        //19-20
    header << (quint16) hex_from_dec (firstNotchFilter_);                           //21-22
    header << (quint16) hex_from_dec (secondNotchFilter_);                          //23-24
    header << (quint16) hex_from_dec (thirdNotchFilter_);                           //25-26
    for (int i = 0; i < unusedChannelSetsFieldSize_; i++)
        header << (quint8) hex_from_dec (null_);

    file_->flush();
    file_->close();
}

void single_segd_rev2_files::write_extended_header()
{
    if (!file_->open(QIODevice::Append))
    {
        qWarning() << file_->errorString();
        return;
    }
    QDataStream extHead;
    extHead.setDevice(file_);

    for (int i = 0; i < 32; i++)
        extHead << (quint8) hex_from_dec (null_);

    file_->flush();
    file_->close();
}

int single_segd_rev2_files::counterByte() const
{
    return counterByte_;
}

void single_segd_rev2_files::setCounterByte(int counterByte)
{
    counterByte_ = counterByte;
}

uint16_t single_segd_rev2_files::bit_to_byte(QBitArray* bitArray)
{
    uint16_t returnValue_;
    QByteArray bytes;
    bytes.resize(bitArray->count()/8);
    bytes.fill(0);
    // Convert from QBitArray to QByteArray
    for(int b = 0; b < bitArray->count(); ++b)
    {
        bytes[b/8] = ( bytes.at(b/8) | ((bitArray->testBit(b))<<(b%8)));
    }
    returnValue_ = (bytes[1] << 8) + bytes[0];
    return returnValue_;
}

void single_segd_rev2_files::bit_to_byte(QBitArray* bitArray, uint8_t returnValue)
{
    QByteArray bytes;
    bytes.resize(bitArray->count()/8+1);
    bytes.fill(0);
    // Convert from QBitArray to QByteArray
    for(int b = 0; b < bitArray->count(); ++b)
    {
        bytes[b/8] = ( bytes.at(b/8) | ((bitArray->testBit(b))<<(b%8)));
    }
    returnValue = bytes[0];
}

void single_segd_rev2_files::bit_to_byte(QBitArray* bitArray, uint8_t* returnValue)
{
    QByteArray bytes;
    bytes.resize(bitArray->count()/8+1);
    bytes.fill(0);
    // Convert from QBitArray to QByteArray
    for(int b = 0; b < bitArray->count(); ++b)
    {
        bytes[b/8] = ( bytes.at(b/8) | ((bitArray->testBit(b))<<(b%8)));
    }
    for (int i = 0; i < bytes.count(); i++)
    {
        returnValue[i] = bytes[i];
    }
}

void single_segd_rev2_files::byte_to_bit(QBitArray *returnValue, int inValue)
{
    int ch = 2;
    for(int i = 0; i < ch; ++i)
    {
        for(int b = 0; b < 8; ++b)
            returnValue->setBit(i*8+b, (inValue>>(i*8))&(1 << b));
    }
    //qDebug() << returnValue << "=======";
}

int single_segd_rev2_files::hex_from_dec(int dec)
{
    int hex = 0;
    int tmp = dec;
    int i = 1;

    while (tmp != 0) {
        int add = tmp % 10;
        hex += add * i;
        i *= 16;
        tmp /= 10;
    }
    return hex;
}

int single_segd_rev2_files::dec_from_hex(int hex)
{
    int dec = 0;
    int tmp = hex;
    int i = 1;

    while (tmp != 0) {
        int add = tmp % 16;
        dec += add * i;
        i *= 10;
        tmp /= 16;
    }
    return dec;
}

quint8 single_segd_rev2_files::channelSets() const
{
    return channelSets_;
}

void single_segd_rev2_files::setChannelSets(const quint8 &channelSets)
{
    channelSets_ = channelSets;
}

void single_segd_rev2_files::openFile(QString fileReadName)
{
    fileRead_->setFileName(fileReadName);
    if (!fileRead_->open(QIODevice::ReadOnly))
    {
        qDebug() << fileRead_->errorString();
        return;
    }
    QDataStream streamData;
    streamData.setDevice(fileRead_);
    streamData.setVersion(QDataStream::Qt_5_9);

    int len = 2;
    char* buffer = new char[len];

    streamData.readRawData(buffer, len);
    fileNumber_ = static_cast<quint16>((static_cast<quint16>(buffer[0]) << 8)  + static_cast<quint8>(buffer[1]));

    streamData.readRawData(buffer, len);
    formatCode_ = static_cast<quint16>((static_cast<quint16>(buffer[0]) << 8) + static_cast<quint8>(buffer[1]));

    len = generalConstantSize_;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);
    for(int i = 0; i < generalConstantSize_; i++)
        generalConstant_ += static_cast<quint8>(buffer[i] << ((generalConstantSize_ - 1 - i) * 8));

    len = 1;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);
    year_ = static_cast<quint8>(buffer[0]);

    len = 2;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);
    day_ = static_cast<quint16>((static_cast<quint16>(buffer[0]) << 8) + static_cast<quint8>(buffer[1])) & 0x0fff;
    numGenBlks_ = static_cast<quint16>((static_cast<quint16>(buffer[0]) << 8 ) & 0xf000) >> 12;
    qDebug() << "day" << dec_from_hex(day_);
    qDebug() << "numGEn" << dec_from_hex(numGenBlks_);

    len = 1;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);
    hour_ = dec_from_hex(static_cast<quint8>(buffer[0]));
    streamData.readRawData(buffer, len);
    minute_ = dec_from_hex(static_cast<quint8>(buffer[0]));
    streamData.readRawData(buffer, len);
    second_ = dec_from_hex(static_cast<quint8>(buffer[0]));

    len = 3;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, 3);
    manufactureCode_ = static_cast<quint8>(buffer[0]);

    len = 3;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);

    len = 1;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);
    baseScanInterval_ = static_cast<qint8>(buffer[0]);

    streamData.readRawData(buffer, len);
    quint8 tmp = static_cast<quint8>(buffer[0]);
    polarity_ = tmp >> 4;

    streamData.readRawData(buffer, len);    // byte is 0

    streamData.readRawData(buffer, len);
    recordType_  = static_cast<quint8>(buffer[0]) >> 4;
    recordLength_ = static_cast<quint16>(buffer[0] & 0x0f) << 8;
    streamData.readRawData(buffer, len);
    recordLength_  += static_cast<quint8>(buffer[0]);

    streamData.readRawData(buffer, len);
    scanTypes_ = static_cast<quint8>(buffer[0]);

    streamData.readRawData(buffer, len);
    channelSets_ = static_cast<quint8>(buffer[0]);

    streamData.readRawData(buffer, len);
    skewBlocks_ = static_cast<quint8>(buffer[0]);

    streamData.readRawData(buffer, len);
    extendedHeaderBlocks_ = static_cast<quint8>(buffer[0]);

    streamData.readRawData(buffer, len);
    externalHeaderBlocks_ = static_cast<quint8>(buffer[0]);

    /* -----------------Header Block type 2------------------ */

    /*extended file number */
    len = 3;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);

    /* Extended Channel set/scan types 4-5 bytes */
    len = 2;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);

    /* Extended Header Blks 6-8 bytes*/
    len = 3;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);

    /* External SKew Blks 9-10*/
    len = 2;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);

    /* SEG-D Version. This version is 3.1  11-12 bytes*/
    streamData.readRawData(buffer, len);
    qDebug() << "seg-d version" << static_cast<quint8> (buffer[0]) << "." << static_cast<quint8> (buffer[1]);

    /* Number of blocks General Trailer 13-16 bytes */
    len = 4;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);
     /* Extended Record. general_header_blk1 bytes 26 & 27 sets 0xFFF, 17-20 bytes*/
    len = 4;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);

    extendedRecord_ = static_cast<quint32>(((static_cast<quint32>(buffer[0])& 0x000000ff) << 24) + ((static_cast<quint32>(buffer[1])& 0x000000ff) << 16) +
            ((static_cast<quint32>(buffer[2])& 0x000000ff) << 8) + ((static_cast<quint32>(buffer[3])& 0x000000ff)));
    qDebug() << "extended" << extendedRecord_;

    /* Record Set Number 21-22 byte */
    len = 2;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);

    /*Extended Additional Blks in Gen Hdr 23-24*/
    streamData.readRawData(buffer, len);

    /* Dominant Sampling Interval 25-27 byte */
    len = 3;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);

    /* Extended Header Blks 28-30 */
    streamData.readRawData(buffer, len);

    len = 1;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);  //Undefinded
    streamData.readRawData(buffer, len);  //header block type

    /* -----------------Header Block type 3------------------ */
    len = 8;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);     /* Time Zero (1-8 bytes) */
    streamData.readRawData(buffer, len);     /* Record Size (9-16 bytes) */
    streamData.readRawData(buffer, len);     /* Record Size (17-24 bytes) */

    len = 4;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);     /* Header Size (25-28 bytes) */

    len = 1;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);    /* Extnd Rec Mode (29 bytes) */
    streamData.readRawData(buffer, len);    /* Rel Time Mode (30 bytes) */
    streamData.readRawData(buffer, len);    //Undefinded

    streamData.readRawData(buffer, len);     /*Header Block Type  */

    /* ------------------Channel set Descriptor ----------------------------------------*/
    len = 1;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);
    scanTypeNumber_ = static_cast<quint8>(buffer[0]) ;              // [1]
    qDebug () << "scanTypeNumber" << scanTypeNumber_;
    len = 2;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);
    channelSetNumber_ = static_cast<quint16>(static_cast<quint16>((buffer[0]<<8)&0xff00)
            + static_cast<quint16>(buffer[1])) ; // [2-3]
    qDebug () << "channelSetNumber_" << channelSetNumber_;

    len = 1;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);
    channelType_ = static_cast<quint8>(buffer[0]) >> 4 ; // chtype[4 bits] + 0[4 bits]   //4
    qDebug () << "channelType_" << channelType_;

    len = 4;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);
    channelSetStartTime_ = static_cast<quint32>(((static_cast<quint32>(buffer[0])& 0x000000ff) << 24) + ((static_cast<quint32>(buffer[1])& 0x000000ff) << 16) +
            ((static_cast<quint32>(buffer[2])& 0x000000ff) << 8) + ((static_cast<quint32>(buffer[3])& 0x000000ff))); // [5-8]
    qDebug () << "channelSetStartTime_" << channelSetStartTime_;

    streamData.readRawData(buffer, len);
    channelSetStartTime_ = static_cast<quint32>(((static_cast<quint32>(buffer[0])& 0x000000ff) << 24) + ((static_cast<quint32>(buffer[1])& 0x000000ff) << 16) +
            ((static_cast<quint32>(buffer[2])& 0x000000ff) << 8) + ((static_cast<quint32>(buffer[3])& 0x000000ff)));// [9-12]
    qDebug () << "channelSetEndTime_" << channelSetEndTime_;

    streamData.readRawData(buffer, len);
    numOfSamples_ = static_cast<quint32>(((static_cast<quint32>(buffer[0])& 0x000000ff) << 24) + ((static_cast<quint32>(buffer[1])& 0x000000ff) << 16) +
            ((static_cast<quint32>(buffer[2])& 0x000000ff) << 8) + ((static_cast<quint32>(buffer[3])& 0x000000ff)));//[13-16] number of samples
    qDebug () << "number of samples" << numOfSamples_;

    streamData.readRawData(buffer, len);
    descaleMultiplier_ = static_cast<quint32>(((static_cast<quint32>(buffer[0])& 0x000000ff) << 24) + ((static_cast<quint32>(buffer[1])& 0x000000ff) << 16) +
            ((static_cast<quint32>(buffer[2])& 0x000000ff) << 8) + ((static_cast<quint32>(buffer[3])& 0x000000ff)));// [17-20]
    qDebug () << "descaleMultiplier_" << descaleMultiplier_;

    len = 3;
    delete[] buffer;
    buffer = new char[len];
    streamData.readRawData(buffer, len);
    numberOfChannels_ = static_cast<quint32>(((static_cast<quint32>(buffer[0])& 0x000000ff) << 16) +
            ((static_cast<quint32>(buffer[1])& 0x000000ff) << 8) + ((static_cast<quint32>(buffer[2])& 0x000000ff))); // [21-23]
    qDebug () << "numberOfChannels_" << numberOfChannels_;

    /* Sampling Interval 24- 26 (0x3 0xe8 = 1ms) */
    streamData.readRawData(buffer, len);
    samplingInterval_ = static_cast<quint32>(((static_cast<quint32>(buffer[0])& 0x000000ff) << 16) +
            ((static_cast<quint32>(buffer[1])& 0x000000ff) << 8) + ((static_cast<quint32>(buffer[2])& 0x000000ff))); // [21-23]
    qDebug () << "samplingInterval_" << samplingInterval_;

    len = 1;
    delete[] buffer;
    buffer = new char[len];
    /* Array Forming 27*/
    streamData.readRawData(buffer, len);
    /* Number of Trace Header Extensions 28*/
    streamData.readRawData(buffer, len);
    /* Gain 29*/
    streamData.readRawData(buffer, len);
    /* Vertical Stack 30*/
    streamData.readRawData(buffer, len);
    /* Streamer Cable number 31*/
    streamData.readRawData(buffer, len);
    /* Header Block Type 32*/
    streamData.readRawData(buffer, len);

    len = 4;
    delete[] buffer;
    buffer = new char[len];
    /* Alias filter Freq 33-36 */
    streamData.readRawData(buffer, len);
    aliasFilterFrequency_ = static_cast<quint32>(((static_cast<quint32>(buffer[0])& 0x000000ff) << 24) + ((static_cast<quint32>(buffer[1])& 0x000000ff) << 16) +
            ((static_cast<quint32>(buffer[2])& 0x000000ff) << 8) + ((static_cast<quint32>(buffer[3])& 0x000000ff)));
    /* Low-cut filter Setting 37-40*/
    streamData.readRawData(buffer, len);
    lowCutFilter_ = static_cast<quint32>(((static_cast<quint32>(buffer[0])& 0x000000ff) << 24) + ((static_cast<quint32>(buffer[1])& 0x000000ff) << 16) +
            ((static_cast<quint32>(buffer[2])& 0x000000ff) << 8) + ((static_cast<quint32>(buffer[3])& 0x000000ff)));
    /* Alias filter slope */
    streamData.readRawData(buffer, len);
    aliasFilterSlope_ = static_cast<quint32>(((static_cast<quint32>(buffer[0])& 0x000000ff) << 24) + ((static_cast<quint32>(buffer[1])& 0x000000ff) << 16) +
            ((static_cast<quint32>(buffer[2])& 0x000000ff) << 8) + ((static_cast<quint32>(buffer[3])& 0x000000ff)));
    /* Low-cut filter slope 45-48*/
    streamData.readRawData(buffer, len);
    lowCutFilterSlope_ = static_cast<quint32>(((static_cast<quint32>(buffer[0])& 0x000000ff) << 24) + ((static_cast<quint32>(buffer[1])& 0x000000ff) << 16) +
            ((static_cast<quint32>(buffer[2])& 0x000000ff) << 8) + ((static_cast<quint32>(buffer[3])& 0x000000ff)));
    /* Notch freq setting 49-52*/
    streamData.readRawData(buffer, len);
    /* Second notch filter 53-56*/
    streamData.readRawData(buffer, len);
    /* Third notch filter 57-60*/
    streamData.readRawData(buffer, len);

    len = 1;
    delete[] buffer;
    buffer = new char[len];
    /* Filter phase 61*/
    streamData.readRawData(buffer, len);
    /* Physical Unit 62*/
    streamData.readRawData(buffer, len);
    /* Undefinded 63*/
    streamData.readRawData(buffer, len);
    /* Header block type 64*/
    streamData.readRawData(buffer, len);

    len = 4;
    delete[] buffer;
    buffer = new char[len];
    /* Filter delay 65-68*/
    streamData.readRawData(buffer, len);

    len = 1;
    delete[] buffer;
    buffer = new char[len];
    /* ASCII Description 69-95 (27 bytes)*/
    for(int i=0; i < 27; i++)
        streamData.readRawData(buffer, len);
    /* Header block type 96*/
   streamData.readRawData(buffer, len);
   /* -------------------Read Measure ---------------------------*/

   len = 2;
   delete[] buffer;
   buffer = new char[len];
   streamData.readRawData(buffer, len);
   fileNumber_ = static_cast<quint16>(((static_cast<quint16>(buffer[0]) & 0x00ff) << 8) + (static_cast<quint16>(buffer[1])));
   qDebug() << "fileNumber" << fileNumber_;

   len = 1;
   delete[] buffer;
   buffer = new char[len];
   streamData.readRawData(buffer, len);
   scanTypeNumber_ =static_cast<quint8>(buffer[0]);
   qDebug() << "scanTypeNumber_" << scanTypeNumber_;

   streamData.readRawData(buffer, len);
   channelSetNumber_ =static_cast<quint8>(buffer[0]);
   qDebug() << "channelSetNumber_" << channelSetNumber_;

   len = 2;
   delete[] buffer;
   buffer = new char[len];
   streamData.readRawData(buffer, len);
   traceNumber_ = static_cast<quint16>(((static_cast<quint16>(buffer[0]) & 0x00ff) << 8) + (static_cast<quint16>(buffer[1])));
   qDebug() << "traceNumber_" << traceNumber_;
   len = 1;
   delete[] buffer;
   buffer = new char[len];
   for(int i = 7; i <= 20; i++)
       streamData.readRawData(buffer, len);


   /* Write data header into the file */
   open_data();
   QDataStream stream;
   stream.setDevice(file_);
   stream.setVersion(QDataStream::Qt_5_9);
   stream << static_cast<quint16>(hex_from_dec(fileNumber_));
   stream << static_cast<quint8>(hex_from_dec(scanTypeNumber_));
   stream << static_cast<quint8>(hex_from_dec(channelSetNumber_));
   stream << static_cast<quint16>(hex_from_dec(traceNumber_));  //trace number [5-6]
   for(int i = 7; i <= 20; i++)
       stream << static_cast<unsigned char>(0x00);

   read_and_write();
   close_data();
}

void single_segd_rev2_files::read_and_write()
{
    QDataStream streamData;
    streamData.setDevice(fileRead_);
    streamData.setVersion(QDataStream::Qt_5_9);
    int len = 4;
    char* buffer = new char[len];
    QVector<float> vecData;
    float tmp_var = 0;
    uint32_t globalCount = 0;
    qDebug() << "numOfSamples" << numOfSamples_;
    while(globalCount < numOfSamples_)
    {
        streamData.readRawData(buffer, len);
        tmp_var = static_cast<float>(((static_cast<quint32>(buffer[0])& 0x000000ff) << 24) + ((static_cast<quint32>(buffer[1])& 0x000000ff) << 16) +
                    ((static_cast<quint32>(buffer[2])& 0x000000ff) << 8) + ((static_cast<quint32>(buffer[3])& 0x000000ff)));
        vecData.append(tmp_var);
        globalCount++;

        if(vecData.size() >= 256){
            append_data2(vecData);
            vecData.clear();
        }
    }
    append_data2(vecData);
    fileRead_->close();
}

void single_segd_rev2_files::setAliasFilterSlope(const quint16 &aliasFilterSlope)
{
    aliasFilterSlope_ = aliasFilterSlope;
}

void single_segd_rev2_files::setDataLength(const quint32 &numOfSamples)
{
    numOfSamples_ = numOfSamples;
}

void single_segd_rev2_files::setChannelGainControlMethod(const quint8 &channelGainControlMethod)
{
    channelGainControlMethod_ = channelGainControlMethod;
}

void single_segd_rev2_files::setChannelSetEndTime(const quint16 &channelSetEndTime)
{
    channelSetEndTime_ = channelSetEndTime;
}

void single_segd_rev2_files::setChannelSetStartTime(const quint16 &channelSetStartTime)
{
    channelSetStartTime_ = channelSetStartTime;
}

void single_segd_rev2_files::setScanTypeNumber(const quint8 &scanTypeNumber)
{
    scanTypeNumber_ = scanTypeNumber;
}

quint16 single_segd_rev2_files::fileNumber() const
{
    return fileNumber_;
}

void single_segd_rev2_files::setFileNumber(const quint16 &fileNumber)
{
    fileNumber_ = fileNumber;
}

void single_segd_rev2_files::setFileName(QString fileName)
{
    fileName_ = fileName;
    file_->setFileName(fileName_);
}
QString single_segd_rev2_files::getFileName()
{
    return fileName_;
}

void single_segd_rev2_files::setFileDir(QString fileName)
{
    fileDir_ = fileName;
}
QString single_segd_rev2_files::getFileDir()
{
    return fileDir_;
}

void single_segd_rev2_files::setNumGenBlks(uint8_t num)
{
    numGenBlks_ = num;
}

void single_segd_rev2_files::addRecordLength(quint16 &inputVal, quint16 length)
{
    inputVal = length << 4;
}

void single_segd_rev2_files::write_data(double x1, unsigned int channelSet, quint16 channel)
{
    if (!file_->open(QIODevice::Append))
    {
        qDebug() << file_->errorString();
        return;
    }

    QDataStream stream;
    stream.setDevice(file_);
    stream.setVersion(QDataStream::Qt_5_9);

    stream << static_cast<quint16>(hex_from_dec(fileNumber_));
    stream << static_cast<quint8>(hex_from_dec(scanTypeNumber_));
    stream << static_cast<quint8>(hex_from_dec(channelSet));
    stream << static_cast<quint16>(hex_from_dec(channel));
    for(int i = 7; i <= 20; i++)
        stream << static_cast<unsigned char>(0x00);

    unsigned char* output = new unsigned char[4];
    output =  convertData(x1);
    for(int i = 0; i < 1000; i++){
        output =  convertData(0);
        if(i == 500){
           output =  convertData(x1);
        }
        stream << (unsigned char)output[0];
        stream << (unsigned char)output[1];
        stream << (unsigned char)output[2];
        stream << (unsigned char)output[3];
    }

    file_->flush();
    file_->close();
}
/* demux trace header */
void single_segd_rev2_files::write_data_header( unsigned int channelSet, quint16 channel)
{
    QDataStream stream;
    stream.setDevice(file_);
    stream.setVersion(QDataStream::Qt_5_9);
    traceNumber_ = channel;
    channelSetNumber_ = channelSet;
    stream << static_cast<quint16>(hex_from_dec(fileNumber_));
    stream << static_cast<quint8>(hex_from_dec(scanTypeNumber_));
    stream << static_cast<quint8>(hex_from_dec(channelSetNumber_));
    stream << static_cast<quint16>(hex_from_dec(traceNumber_));  //trace number [5-6]
    for(int i = 7; i <= 20; i++)
        stream << static_cast<unsigned char>(0x00);
}

void single_segd_rev2_files::append_data(QVector<double> data, int len){
    QDataStream stream;
    stream.setDevice(file_);
    stream.setVersion(QDataStream::Qt_5_9);
    unsigned char* output = new unsigned char[4];
    for(int i=0; i < len; i++){
        output =  convertData(data.at(i));
        stream << (unsigned char)output[0];
        stream << (unsigned char)output[1];
        stream << (unsigned char)output[2];
        stream << (unsigned char)output[3];
    }
    file_->flush();
    delete[] output;
}

void single_segd_rev2_files::append_data(QVector<float> data)
{
    QDataStream stream;
    stream.setDevice(file_);
    stream.setVersion(QDataStream::Qt_5_9);
    unsigned char* output = new unsigned char[4];
    for(int i=0; i < data.size(); i++){
        output =  convertData(data.at(i));
        stream << (unsigned char)output[0];
        stream << (unsigned char)output[1];
        stream << (unsigned char)output[2];
        stream << (unsigned char)output[3];
    }
    file_->flush();
    delete[] output;
}


void single_segd_rev2_files::append_data(QVector<double> data)
{
    QDataStream stream;
    stream.setDevice(file_);
    stream.setVersion(QDataStream::Qt_5_9);
    unsigned char* output = new unsigned char[4];
    for(int i=0; i < data.size(); i++){
        output =  convertData((float)data.at(i));
        stream << (unsigned char)output[0];
        stream << (unsigned char)output[1];
        stream << (unsigned char)output[2];
        stream << (unsigned char)output[3];
    }
    file_->flush();
    delete[] output;
}

void single_segd_rev2_files::append_data(QVector<bool> data)
{
    QDataStream stream;
    stream.setDevice(file_);
    stream.setVersion(QDataStream::Qt_5_9);
    unsigned char* output = new unsigned char[4];
    for(int i=0; i < data.size(); i++){
        if(data.at(i) == true)
            output =  convertData(4095.0);
        else
            output =  convertData(0.0);
        stream << (unsigned char)output[0];
        stream << (unsigned char)output[1];
        stream << (unsigned char)output[2];
        stream << (unsigned char)output[3];
    }
    file_->flush();
    delete[] output;
}

/* для считывания из sgd */
void single_segd_rev2_files::append_data2(QVector<float> data)
{
    QDataStream stream;
    stream.setDevice(file_);
    stream.setVersion(QDataStream::Qt_5_9);
    int32_t tmp = 0;
    for(int i=0; i < data.size(); i++){
        tmp = data.at(i);
        stream << (quint16)(tmp>>16);
        stream << (quint16)tmp;

    }
    file_->flush();
}

void single_segd_rev2_files::append_data_test()
{
    QDataStream stream;
    stream.setDevice(file_);
    stream.setVersion(QDataStream::Qt_5_9);

    unsigned char* output = new unsigned char[4];

    for(int i=0; i < 8000000; i++){
        output =  convertData(0);
//        if(i%510000000){
//            output =  convertData(13.7);
//        }
        stream << (unsigned char)output[0];
        stream << (unsigned char)output[1];
        stream << (unsigned char)output[2];
        stream << (unsigned char)output[3];
    }
}

void single_segd_rev2_files::open_data()
{
    if (!file_->open(QIODevice::Append))
    {
        qDebug() << file_->errorString();
        return;
    }
}

void single_segd_rev2_files::close_data()
{
    file_->flush();
    file_->close();
}

void single_segd_rev2_files::openFile_test(QString fileReadName)
{

}

void single_segd_rev2_files::getHeaderDataRev3(QString fileReadName)
{
    fileRead_->setFileName(fileReadName);
    if (!fileRead_->open(QIODevice::ReadOnly))
    {
        qDebug() << fileRead_->errorString();
        return;
    }

    QDataStream streamData;
    streamData.setDevice(fileRead_);
    streamData.setVersion(QDataStream::Qt_5_9);
    /* ----------------General Header Block 1--------------------- */
    general_header_1 header1;
    streamData.readRawData((char*)&header1, sizeof (header1));

    fileNumber_ = static_cast<quint16>((static_cast<quint16>(header1.f[0]) << 8)  + static_cast<quint8>(header1.f[1]));
    formatCode_ = static_cast<quint16>((static_cast<quint16>(header1.y[0]) << 8) + static_cast<quint8>(header1.y[1]));
    for(int i = 0; i < generalConstantSize_; i++)
        generalConstant_ += static_cast<quint8>(header1.k[i] << ((generalConstantSize_ - 1 - i) * 8));
    year_ = (static_cast<quint8>(header1.yr));
    day_ = (static_cast<quint16>((static_cast<quint16>(header1.dy[0]) << 8) + static_cast<quint8>(header1.dy[1])) & 0x0fff);
    numGenBlks_ = (static_cast<quint16>((static_cast<quint16>(header1.dy[0]) << 8 ) & 0xf000) >> 12);
    hour_ = (static_cast<quint8>(header1.h));
    minute_ = (static_cast<quint8>(header1.mi));
    second_ = (static_cast<quint8>(header1.se));
    manufactureCode_ = (static_cast<quint8>(header1.m[0]));
    baseScanInterval_ = (static_cast<qint8>(header1.i));
    qDebug() << "BASE SCAN INTERVAL" << baseScanInterval_;
    polarity_ = ((static_cast<quint8>(header1.p_sbx)) >> 4);
    recordType_  = (static_cast<quint8>(header1.z_r[0]) >> 4);
    recordLength_ = (static_cast<quint16>(header1.z_r[0] & 0x0f) << 8);
    recordLength_  += (static_cast<quint8>(header1.z_r[1]));
    scanTypes_ = (static_cast<quint8>(header1.str));
    channelSets_ = (static_cast<quint8>(header1.cs));
    skewBlocks_ = (static_cast<quint8>(header1.sk));
    extendedHeaderBlocks_ = (static_cast<quint8>(header1.ec));
    externalHeaderBlocks_ = (static_cast<quint8>(header1.ex));

    /* ----------------General Header Block 2--------------------- */
    general_header_2 header2;
    streamData.readRawData((char*)&header2, sizeof (header2));
    extendedRecord_ = static_cast<quint32>(((static_cast<quint32>(header2.erl[0])& 0x000000ff) << 24) + ((static_cast<quint32>(header2.erl[1])& 0x000000ff) << 16) +
            ((static_cast<quint32>(header2.erl[2])& 0x000000ff) << 8) + ((static_cast<quint32>(header2.erl[3])& 0x000000ff)));
    qDebug() << "extended" << extendedRecord_;

    /* ----------------General Header Block 3--------------------- */
    general_header_3 header3;
    streamData.readRawData((char*)&header3, sizeof (header3));

    /* ------------------Channel set Descriptor ----------------------------------------*/
    scan_type_header scn_type_hdr;
    streamData.readRawData((char*)&scn_type_hdr, sizeof (scn_type_hdr));

    scanTypeNumber_ = (static_cast<quint8>(scn_type_hdr.st)) ;
    qDebug () << "scanTypeNumber" << scanTypeNumber_;
    channelSetNumber_ = (static_cast<quint16>(static_cast<quint16>((scn_type_hdr.cs[0]<<8)&0xff00)
            + static_cast<quint16>(scn_type_hdr.cs[1]))) ;
    qDebug () << "channelSetNumber_" << channelSetNumber_;
    channelType_ = (static_cast<quint8>(scn_type_hdr.c) >> 4 );
    qDebug () << "channelType_" << channelType_;

    channelSetStartTime_ = static_cast<quint32>(((static_cast<quint32>(scn_type_hdr.tf[0])& 0x000000ff) << 24) + ((static_cast<quint32>(scn_type_hdr.tf[1])& 0x000000ff) << 16) +
            ((static_cast<quint32>(scn_type_hdr.tf[2])& 0x000000ff) << 8) + ((static_cast<quint32>(scn_type_hdr.tf[3])& 0x000000ff))); // [5-8]
    qDebug () << "channelSetStartTime_" << channelSetStartTime_;

    channelSetEndTime_ = static_cast<quint32>(((static_cast<quint32>(scn_type_hdr.te[0])& 0x000000ff) << 24) + ((static_cast<quint32>(scn_type_hdr.te[1])& 0x000000ff) << 16) +
            ((static_cast<quint32>(scn_type_hdr.te[2])& 0x000000ff) << 8) + ((static_cast<quint32>(scn_type_hdr.te[3])& 0x000000ff)));// [9-12]
    qDebug () << "channelSetEndTime_" << channelSetEndTime_;

    numOfSamples_ = static_cast<quint32>(((static_cast<quint32>(scn_type_hdr.ns[0])& 0x000000ff) << 24) + ((static_cast<quint32>(scn_type_hdr.ns[1])& 0x000000ff) << 16) +
            ((static_cast<quint32>(scn_type_hdr.ns[2])& 0x000000ff) << 8) + ((static_cast<quint32>(scn_type_hdr.ns[3])& 0x000000ff)));//[13-16] number of samples
    qDebug () << "number of samples rev 3" << numOfSamples_;

    descaleMultiplier_ = static_cast<quint32>(((static_cast<quint32>(scn_type_hdr.dsm[0])& 0x000000ff) << 24) + ((static_cast<quint32>(scn_type_hdr.dsm[1])& 0x000000ff) << 16) +
            ((static_cast<quint32>(scn_type_hdr.dsm[2])& 0x000000ff) << 8) + ((static_cast<quint32>(scn_type_hdr.dsm[3])& 0x000000ff)));// [17-20]
    qDebug () << "descaleMultiplier_" << descaleMultiplier_;

    numberOfChannels_ = static_cast<quint32>(((static_cast<quint32>(scn_type_hdr.c_s[0])& 0x000000ff) << 16) +
            ((static_cast<quint32>(scn_type_hdr.c_s[1])& 0x000000ff) << 8) + ((static_cast<quint32>(scn_type_hdr.c_s[2])& 0x000000ff))); // [21-23]
    qDebug () << "numberOfChannels_" << numberOfChannels_;



    /* Sampling Interval 24- 26 (0x3 0xe8 = 1ms) */
    samplingInterval_ = static_cast<quint32>(((static_cast<quint32>(scn_type_hdr.sr[0])& 0x000000ff) << 16) +
            ((static_cast<quint32>(scn_type_hdr.sr[1])& 0x000000ff) << 8) + ((static_cast<quint32>(scn_type_hdr.sr[2])& 0x000000ff))); // [21-23]
    qDebug () << "samplingInterval_" << samplingInterval_;

    aliasFilterFrequency_ = static_cast<quint32>(((static_cast<quint32>(scn_type_hdr.af[0])& 0x000000ff) << 24) + ((static_cast<quint32>(scn_type_hdr.af[1])& 0x000000ff) << 16) +
            ((static_cast<quint32>(scn_type_hdr.af[2])& 0x000000ff) << 8) + ((static_cast<quint32>(scn_type_hdr.af[3])& 0x000000ff)));
    /* Low-cut filter Setting 37-40*/
    lowCutFilter_ = static_cast<quint32>(((static_cast<quint32>(scn_type_hdr.lc[0])& 0x000000ff) << 24) + ((static_cast<quint32>(scn_type_hdr.lc[1])& 0x000000ff) << 16) +
            ((static_cast<quint32>(scn_type_hdr.lc[2])& 0x000000ff) << 8) + ((static_cast<quint32>(scn_type_hdr.lc[3])& 0x000000ff)));
    /* Alias filter slope */
    aliasFilterSlope_ = static_cast<quint32>(((static_cast<quint32>(scn_type_hdr.as[0])& 0x000000ff) << 24) + ((static_cast<quint32>(scn_type_hdr.as[1])& 0x000000ff) << 16) +
            ((static_cast<quint32>(scn_type_hdr.as[2])& 0x000000ff) << 8) + ((static_cast<quint32>(scn_type_hdr.as[3])& 0x000000ff)));
    /* Low-cut filter slope 45-48*/
    lowCutFilterSlope_ = static_cast<quint32>(((static_cast<quint32>(scn_type_hdr.ls[2])& 0x000000ff) << 24) + ((static_cast<quint32>(scn_type_hdr.ls[1])& 0x000000ff) << 16) +
            ((static_cast<quint32>(scn_type_hdr.ls[2])& 0x000000ff) << 8) + ((static_cast<quint32>(scn_type_hdr.ls[3])& 0x000000ff)));

    fileRead_->flush();
    fileRead_->close();
}

void single_segd_rev2_files::setDemuxTraceHeader(dem_trace_header str_demux)
{
    dem_trace_header strct_read_mes = str_demux;
    fileNumber_ = static_cast<quint16>(((static_cast<quint16>(strct_read_mes.f[0]) & 0x00ff) << 8) + (static_cast<quint16>(strct_read_mes.f[1])));
    qDebug() << "fileNumber" << fileNumber_;
    scanTypeNumber_ =static_cast<quint8>(strct_read_mes.st);
    qDebug() << "scanTypeNumber_" << scanTypeNumber_;
    channelSetNumber_ =static_cast<quint8>(strct_read_mes.cn);
    qDebug() << "channelSetNumber_" << channelSetNumber_;
    traceNumber_ = static_cast<quint16>(((static_cast<quint16>(strct_read_mes.tn[0]) & 0x00ff) << 8) + (static_cast<quint16>(strct_read_mes.tn[1])));
    qDebug() << "traceNumber_" << traceNumber_;

    /* Write data header into the file */
    open_data();
    QDataStream stream;
    stream.setDevice(file_);
    stream.setVersion(QDataStream::Qt_5_9);
    stream << static_cast<quint16>(fileNumber_);
    stream << static_cast<quint8>(scanTypeNumber_);
    stream << static_cast<quint8>(channelSetNumber_);
    stream << static_cast<quint16>(traceNumber_);  //trace number [5-6]
    for(int i = 7; i <= 20; i++)
        stream << static_cast<unsigned char>(0x00);
    close_data();
}

void single_segd_rev2_files::writeData(QVector<float> vecData)
{
    append_data2(vecData);
}
