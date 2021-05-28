#include "network/declarateTransceiveringData.h"
#include <winsock.h>
//-------------------------------------------------------------------
QDataStream& operator <<(QDataStream &out, const TDataPocket &data_pocket)
{
//    out.writeRawData("id:", sizeof("id:"));
//    out.writeRawData(QString::number(data_pocket.id).toLatin1().data(), QString::number(data_pocket.id).length() + 1 );

//    out.writeRawData(" ml:", sizeof(" ml:"));
//    out.writeRawData(QString::number(data_pocket.ml).toLatin1().data(), QString::number(data_pocket.ml).length() + 1 );

//    out.writeRawData(" dept:" ,sizeof(" dept:" ));
//    out.writeRawData(QString::number(data_pocket.dept).toLatin1().data(), QString::number(data_pocket.dept).length() + 1 );

//    out.writeRawData(" n_pocket:", sizeof(" n_pocket:"));
//    out.writeRawData(QString::number(ntohs(data_pocket.n_pocket)).toLatin1().data(), QString::number(ntohs(data_pocket.n_pocket)).length() + 1 );

//    out.writeRawData(" status:", sizeof(" status:"));
//    out.writeRawData(QString::number(data_pocket.status).toLatin1().data(), QString::number(data_pocket.status).length() + 1 );

//    out.writeRawData(" data:", sizeof(" data:"));
//    for(int i = 0; i < OVSP_NUM_POINTS; i++)
//    {
//        out.writeRawData(QString::number(data_pocket.data[i]).toLatin1().data(), QString::number(data_pocket.data[i]).length() + 1 );
//    }
//    out.writeRawData("\r\n", sizeof("\r\n"));

//    return out;
//    out << data_pocket.id;
//    out << data_pocket.ml;
//    out << data_pocket.dept;
//    out << data_pocket.n_pocket;
//    out << data_pocket.status;

//    out.writeRawData((char*)(&data_pocket), sizeof(TDataPocket));

    out.writeRawData((char*)(&data_pocket), sizeof(TDataPocket));
    return out;
}
//-------------------------------------------------------------------
QDataStream& operator >>(QDataStream &in, TDataPocket *data_pocket)
{
//    in>>data_pocket.id;
//    in>>data_pocket.ml;
//    in>>data_pocket.dept;
//    in>>data_pocket.n_pocket;
//    in>>data_pocket.status;
    in.readRawData((char*)(data_pocket), sizeof(TDataPocket));
    return in;
}
//-------------------------------------------------------------------

