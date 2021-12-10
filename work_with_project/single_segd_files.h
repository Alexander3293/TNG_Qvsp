#ifndef SINGLE_SEGD_FILES_H
#define SINGLE_SEGD_FILES_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDate>
#include <QTime>
#include <QTextStream>
#include <QDataStream>
#include <QBitArray>
#include <qmath.h>

#include "work_with_project/measurement.h"
#include "work_with_project/measurementproperties.h"

#define recordTypeTest 2
#define recordTypeParallelTest 4
#define recordTypeDirectTest 6
#define recordTypeNormal 8
#define recordTypeOther 1

#define FORMATRECORD_20bit_Binary_Multi 0015	//20 bit binary multiplexed
#define FORMATRECORD_8bit_Quater_Multi 0022	//8 bit quaternary multiplexed
#define FORMATRECORD_16bit_Quater_Multi 0024	//16 bit quaternary multiplexed
#define FORMATRECORD_8bit_HEX_Multi 0042	//8 bit hexadecimal multiplexed
#define FORMATRECORD_16bit_HEX_Multi 0044	//16 bit hexadecimal multiplexed
#define FORMATRECORD_32bit_HEX_Multi 48	//32 bit hexadecimal multiplexed
#define FORMATRECORD_20bit_Binary_Demulti 8015	//20 bit binary demultiplexed
#define FORMATRECORD_16bit_Quater_Demulti 8024	//16 bit quaternary demultiplexed
#define FORMATRECORD_8bit_HEX_Demulti 8042	//8 bit hexadecimal demultiplexed
#define FORMATRECORD_16bit_HEX_Multi2 8044	//16 bit hexadecimal &multiplexed
#define FORMATRECORD_32bit_HEX_Demulti 8048	//32 bit hexadecimal demultiplexed

#define CHANNELSETS_TYPE_OTHER 7                    //0111b    Other
#define CHANNELSETS_TYPE_EXTREMALDATA 6             //0110b Extemaldata
#define CHANNELSETS_TYPE_TIMECOUNTER 5              //0101b Timecounter
#define CHANNELSETS_TYPE_WATERBREAK 4               //0100b Water break
#define CHANNELSETS_TYPE_UPHOLE 3                   //0011b	Up hole
#define CHANNELSETS_TYPE_TIMEBREAK 2                //0010b	Time break
#define CHANNELSETS_TYPE_SEIS 1                     //0001b	Seis
#define CHANNELSETS_TYPE_UNUSED 0                   //0000b	Unused
#define CHANNELSETS_TYPE_SINGNATURE_UNFILTERED 8    //1000b	Signature, unfiltered
#define CHANNELSETS_TYPE_SINGNATURE_FILTERED 9      //1001b	Signature, filtered

#define CHANNELSETS_GAINMODE_INDIVIDUAL_AGC 1       //0001b	 (1) Individual AGC
#define CHANNELSETS_GAINMODE_GANGED_AGC 2           //0010b	 (2) Ganged AGC
#define CHANNELSETS_GAINMODE_FIXED 3                //11b	 (3) Fixed gain
#define CHANNELSETS_GAINMODE_PROGRAMMED 4           //0100b	 (4) Programmed gain
#define CHANNELSETS_GAINMODE_BINARY 8               //1000b  (8) Binary gain control
#define CHANNELSETS_GAINMODE_IFP 9                  //1001b	 (9) IFP gain control

/* Version Seg-d 3.1 */
/*---------------- General header block #1 -------------------------*/

typedef struct {
    unsigned char f[2];   /* 01-02 File number (0-9999) */
    unsigned char y[2];   /* 03-04 Format code */
    char k[6];            /* 05-10    General constants */
    unsigned char yr;     /* 11    Year (0-99) */
    unsigned char dy[2];  /* 12    Number blocks in general header and day of year */
    unsigned char h;      /* 14    Hour of day */
    unsigned char mi;     /* 15    Minute of hour */
    unsigned char se;     /* 16    Second of minute */
    unsigned char m[3];   /* 17    Manufacturer's code */
                          /* 18-19 and serial number */
    unsigned char z1[3];  /* 20-22 only zeros */
    unsigned char i;      /* 23    Base scan interval */
    unsigned char p_sbx;  /* 24    Polarity */
    unsigned char z2;     /* 25    Zeros */
    unsigned char z_r[2]; /* 26-27    Record type and record length*/
    unsigned char str;    /* 28    Scan types/ record  */
    unsigned char cs;     /* 29    Channels sets /scan type */
    unsigned char sk;     /* 30    Skew blocks */
    unsigned char ec;     /* 31    Extended header length */
    unsigned char ex;     /* 32    External header length */
} general_header_1;


/*---------------- General header block #2 -------------------------*/

typedef struct {
    unsigned char ef[3];  /* 01-03 Extended file number */
    unsigned char en[2];  /* 04-05 Extended channel sets and scan types */
    unsigned char ecx[3]; /* 06-08 Extended header blocks */
    unsigned char es[2];  /* 09-10 Extended skew blocks */
    unsigned char rev[2]; /* 11-12 SEG-D revision number */
    unsigned char gt[4];  /* 13-16 General trailer number of blks */
    unsigned char erl[4]; /* 17-20 Extended record length */
    unsigned char rs[2];  /* 21-22 Record Set number */
    unsigned char exAB[2];/* 23-24 Extended additional blks in Gen Hdr */
    unsigned char dSI[3]; /* 25-27 Dominant Sampling Interval*/
    unsigned char exHB[3];/* 28-30 External header blks */
    unsigned char x;      /* 31 undefined */
    unsigned char type;   /* 32 Header block type */
} general_header_2;

/*---------------- General header block #3 -------------------------*/

typedef struct {
    unsigned char tz[8];  /* 01-08 Time Zero */
    unsigned char rs[8];  /* 09-16 Record Size */
    unsigned char ds[8];  /* 17-24 Data Size */
    unsigned char hs[4];  /* 25-28 Header Size */
    unsigned char erm;   /* 29 Extnd Rec Mode */
    unsigned char rtm;  /* 30 Rel Time Mode */
    unsigned char x;      /* 31 undefined */
    unsigned char type;   /* 32 Header block type */
} general_header_3;

/*---------------- Scan Type -------------------------*/
typedef struct {
    unsigned char st;     /* 01 Scan Type */
    unsigned char cs[2];  /* 02-03 Channel Set № */
    unsigned char c;      /* 04 Channel Type */
    unsigned char tf[4];  /* 05-08 Channel set start time */
    unsigned char te[4];  /* 09-12 Channel set end time */
    unsigned char ns[4];  /* 13-16 Number of samples */
    unsigned char dsm[4]; /* 17-20 Number of samples */
    unsigned char c_s[3]; /* 21-23 № of channels */
    unsigned char sr[3];  /* 24-26 Sampling Interval */
    unsigned char ary;    /* 27 Array Forming */
    unsigned char the;    /* 28 Trace Header Extensions */
    unsigned char efh;    /* 29 Extnd Header Flag/ channel gain */
    unsigned char vs;     /* 30 Vertical Stack */
    unsigned char cab;    /* 31 Streamer № */
    unsigned char type;   /* 32 Header block type */
    unsigned char af[4];  /* 33-36 Alias Filter Frequency */
    unsigned char lc[4];  /* 37-40 Low-cut  Filter */
    unsigned char as[4];  /* 41-44 Alias Filter Slope */
    unsigned char ls[4];  /* 45-48 Low-cut Filter Slope */
    unsigned char nt1[4]; /* 49-52 First notch filter */
    unsigned char nt2[4]; /* 53-56 Second notch filter */
    unsigned char nt3[4]; /* 57-60 Third notch filter */
    unsigned char fph;    /* 61 Filter phase */
    unsigned char phu;    /* 62 Physical unit */
    unsigned char x;      /* 63 undefined */
    unsigned char type2;  /* 64 Header block type */
    unsigned char fdl[4]; /* 65-68 Filter delay */
    unsigned char dsc[27];/* 69-95 Description */
    unsigned char type3;  /* 96 Header block type */
} scan_type_header;

/*--------------- Demux trace header -----------------------*/
typedef struct {
    unsigned char f[2];     /* 01-02 file number */
    unsigned char st;     /* 03    scan type number */
    unsigned char cn;     /* 04    channel set */
    unsigned char tn[2];  /* 05-06 trace number */
    unsigned char t[3];   /* 07-09 timing word of the first sample if
                                the data were written in the multiplexed
                                format */
    unsigned char the;    /* 10    trace header extensions */
    unsigned char ssk;     /* 11    sample skew of the first sample
                                of the trace. It is a part of
                                the fractional part of the base scan interval. Res :
                                1/256 scan interval */
    unsigned char tr;     /* 12    trace edit */
    unsigned char tw[3];  /* 13-15 time from time break to the end of
                                the internal time break window (binary
                                number, inc 1ms) */
    unsigned char en[2];  /* 16-17 extended channel set number */
    unsigned char efn[3]; /* 18-20 extended file number */
} dem_trace_header;

class single_segd_files : public QObject
{
    Q_OBJECT
public:
    explicit single_segd_files(QObject *parent = nullptr);
    ~single_segd_files();
    void setTime(const QTime &time);
    void setData(const QDate &data);
    void write_general_header();
    void write_general_header_blk2();
    void write_general_header_blk3();
    void write_header();
    void write_extended_header();
    void write_spacer();

    void write_data(double x1, unsigned int channelSet, quint16 channel);
    void write_data_header(unsigned int channelSet, quint16 channel);
    void close_data();
    void open_data();
    void append_data(QVector<float> data);
    void append_data(QVector<double> data);
    void append_data(QVector<bool> data);
    void append_data2(QVector<float> data);
    void append_data_test();

    void setRecordLenght(uint16_t recordLength)         {recordLength_ = recordLength;}
    void setChannelSetNumber(uint8_t channelSetNumber)  {channelSetNumber_ = channelSetNumber;}
    void setNumberOfChannels(uint16_t numberOfChannels) {numberOfChannels_ = numberOfChannels;}
    void setChannelType(uint8_t channelType)            {channelType_ = channelType;}

    int counterByte() const;
    void setCounterByte(int counterByte);

    quint16 fileNumber() const;
    void setFileNumber(const quint16 &fileNumber);
    void setFileName(QString fileName);
    QString getFileName();
    void setNumGenBlks(uint8_t num);

    void setScanTypeNumber(const quint8 &scanTypeNumber);
    void setChannelSetStartTime(const quint16 &channelSetStartTime);
    void setChannelSetEndTime(const quint16 &channelSetEndTime);
    void setChannelGainControlMethod(const quint8 &channelGainControlMethod);
    void setAliasFilterSlope(const quint16 &aliasFilterSlope);
    void setDataLength(const quint32 &numOfSamples);
    quint8 channelSets() const;
    void setChannelSets(const quint8 &channelSets);
    bool checkData(QString fileCheckName);

    void openFile(QString fileReadName);
    void openFile_test(QString fileReadName);
    void getHeaderData(QString fileReadName);
    void read_and_write();

    uint32_t getNumOfSamples();
    QVector<float> getDataRev3(uint32_t sizeData);
    dem_trace_header getDemuxTraceHeader();

private:
    uint16_t bit_to_byte(QBitArray* bitArray);
    void bit_to_byte(QBitArray* bitArray, uint8_t  returnValue);
    void bit_to_byte(QBitArray* bitArray, uint8_t *returnValue);
    void byte_to_bit(QBitArray* returnValue, int inValue);
    int hex_from_dec(int dec);
    int dec_from_hex(int hex);
//    unsigned char *convertData(double value);
    QString     fileName_;
    const QString fileFormat_ = QString::fromUtf8(".segd");
    QFile*      file_;
    QFile*      fileRead_;
    QDate       date_;
    QTime       time_;
    quint16    numGenBlks_;
    QBitArray*  bitArray_;
    int         bitArraySize_;

    // General Header
    quint16    fileNumber_; //2
    quint16    formatCode_; // 2
    quint64    generalConstant_; //need 6 bytes
    quint8     year_; // 1
    //    uint8_t     month_;
    quint16    day_; // 2 bytes
    quint8     hour_; // 1 bytes
    quint8     minute_; // 1
    quint8     second_; // 1
    // 16 bytes
    quint8     manufactureCode_; // 1
    quint16    manufactureSerialNumber_; // 2
    quint8*    bytesPerScan_; // 3
    qint8     baseScanInterval_; // 1
    //   uint8_t     baseScanInterval_hex;
    quint8     polarity_;  // 1            //Scans/Block exponent
    quint8     scansBlock_;  // 1
    quint8     recordType_; // 1            //uint16_t    recordType_hex;  //Record type + reord lenght (1111 0000:0000 0000)
    quint16     recordLength_; // 1         //For convert lenght from byte to bit
    quint8     scanTypes_; //1
    quint8     channelSets_; //1
    quint8     skewBlocks_; // 1
    quint8     extendedHeaderBlocks_;  //1
    quint8     externalHeaderBlocks_;  //1

    quint32    extendedRecord_;
    // 32 bytes
    static const int generalConstantSize_ = 6;
    static const int bytesPerScanSize_ = 3;

    //end General Header

    //Scan type header
    //Channel set header
    quint8      scanTypeNumber_;
    quint16     channelSetNumber_;
    quint16      traceNumber_;
    quint16     channelSetStartTime_;
    quint16     channelSetEndTime_;
    quint32     numOfSamples_;
    quint8      null_;
    quint8      descaleMultiplier_;
    quint32     numberOfChannels_;
    quint32     samplingInterval_;
    quint8      channelType_;
//    uint8_t     channelType_notUsed;
    quint8      channelGainControlMethod_;
    quint16     aliasFilterFrequency_;
    quint16     aliasFilterSlope_;
    //16 bytes
//    uint16_t    aliasFilterSlope_hex;
    quint16     lowCutFilter_;
    quint16     lowCutFilterSlope_;
    quint16     firstNotchFilter_;
    quint16     secondNotchFilter_;
    quint16     thirdNotchFilter_;
//    uint16_t    extendedChannelSetNumber_;
//    uint8_t     extendedChannelFlag_;
//    uint8_t     traceHeaderExtentions_;
//    uint8_t     verticalStack_;
//    uint8_t     streamerCableNumber_;
//    uint16_t     arrayForming_;
    static const int unusedChannelSetsFieldSize_ = 6;
    //end Channel set header

    //
    /*    //Sample skew header
    uint16_t    traceFileNumber_;
    uint8_t     traceScanFilenumber_;
    uint8_t     traceChannelSetNumber_;
    uint16_t    traceNumber_;
    uint8_t*    firstTimingWord_;
    uint8_t     traceHeaderExtentions_; //+
    uint8_t     sapleSkew_;
    uint8_t     traceEdit_;
    uint8_t*    timeBreakWindow_;
    uint8_t     extendedChannelSetNumber_;//+
    uint8_t*    extendedFileNumber_;    //+
        //*/
    //
    uint8_t*    extendedHeader_;        //32 bytes, fill 0

    quint8     startOfScan_;
    quint32    timingWord_;
    bool       TWI_;
    bool       ITB_;
    bool       DP_;
    int counterByte_;
    int counterSpace_;

    void addRecordLength(quint16 &inputVal , quint16 length);
    unsigned char* convertData(double value);
    unsigned char* convertData2(double value);

signals:
    void newMsg(QString str);

};

#endif // SINGLE_SEGD_FILES_H
