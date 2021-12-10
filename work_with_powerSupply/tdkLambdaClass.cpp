//-----------------------------------------------------------------------------

//для Linux
//#include <sys/types.h>  //
//#include <sys/socket.h> //<winsock.h>
//#include <netdb.h>      //
//#include <netinet/in.h> //
//#include <arpa/inet.h>  //
#include <QDebug>
//для Windows
#include <winsock.h>
#include <memory>

#include "tdklambdaclass.h"
//-----------------------------------------------------------------------------
tdkLambdaClass::tdkLambdaClass(QObject *parent):
    QObject(parent)
{
    flag1 = 0;
    flag2 = 0;
    p_count = 0;
    port = 8005; // 5025
    host = QHostAddress("192.168.1.25");

    connect(&udp_socket, SIGNAL(readyRead()), this, SLOT(read_Udp_Data_Response()));

    emit updateState("Checking connection...");
    udp_socket.bind(host, port);
    rebind();
}

void tdkLambdaClass::initializeParametres()
{
    QTimer::singleShot(600, this, SLOT(on_Write_Udp_Volt_Limit_Read()));
    QTimer::singleShot(900, this, SLOT(on_Write_Udp_Curr_Limit_Read()));
    QTimer::singleShot(1100, this, SLOT(on_Write_Udp_Volt_Measuring()));
    QTimer::singleShot(1400, this, SLOT(on_Write_Udp_Curr_Measuring()));
    QTimer::singleShot(1700, this, SLOT(on_Write_Udp_Output_State()));
    QTimer::singleShot(2000, this, SLOT(on_Write_Udp_Cv_Cc_Measuring()));
    QTimer::singleShot(2300, this, SLOT(on_Write_Udp_LRM_Measuring()));
//    QTimer::singleShot(2700, this, SLOT(on_Write_Udp_Idntity_Query()));
    QTimer::singleShot(2700, this, SLOT(on_Write_Udp_System_Error()));
    emit updateState("Connected");
}
//-----------------------------------------------------------------------------
tdkLambdaClass::~tdkLambdaClass()
{
    udp_socket.deleteLater();
}

QHostAddress tdkLambdaClass::getHost() const
{
    return host;
}

void tdkLambdaClass::setHost(const QHostAddress &value)
{
    host = value;
}

void tdkLambdaClass::rebind()
{

//    qDebug() << "tdkLambdaClass rebind" << isBind_ << udp_socket.state();

    if(isBind_ == true){
        initializeParametres();
    }
    else{
        emit updateState("Connecting...");
        udp_socket.abort();
        udp_socket.bind();
        on_Write_Udp_Idntity_Query();
    }
    QTimer::singleShot(1500, this, &tdkLambdaClass::rebind);
}

//-----------------------------------------------------------------------------
void tdkLambdaClass::read_Udp_Data_Response(void)
{
    QHostAddress    sender;
    quint16         senderPort;
    QByteArray com;
    double num;
    bool checked;
    QString str;
    int n;

    do
    {
        com.resize(udp_socket.pendingDatagramSize());
        udp_socket.readDatagram(com.data(), com.size(), &sender, &senderPort);
    } while (udp_socket.hasPendingDatagrams());

//    qDebug() << this->flag2 << "in";
    switch(this->flag2)
    {
    case COM_VOLT_LIMIT:
    {
        com.remove(com.size()-1,2);
        num = com.toDouble();
        emit response_Volt_Limit(num);
        break;
    }

    case COM_VOLT_LIMIT_READ:
    {
        com.remove(com.size()-1,2);
        num = com.toDouble();
        emit response_Volt_Limit_Read(num);
        break;
    }

    case COM_CURR_LIMIT:
    {
        com.remove(com.size()-1,2);
        num = com.toDouble();
        emit response_Curr_Limit(num);
        break;
    }

    case COM_CURR_LIMIT_READ:
    {
        com.remove(com.size()-1,2);
        num = com.toDouble();
        emit response_Curr_Limit(num);
        break;
    }

    case COM_OUT_ON_OFF:
    {
        if (com.contains("on") || com.contains("ON")) checked = true;
        if (com.contains("off") || com.contains("OFF")) checked = false;
        emit response_Output_State(checked);
        break;
    }
    case COM_OUTPUT_STATE:
    {
        if (com.contains("on") || com.contains("ON")) checked = true;
        if (com.contains("off") || com.contains("OFF")) checked = false;
        emit response_Out_On_Off(checked);
        break;
    }

    case COM_VOLT_MEASURING:
    {
        com.remove(com.size()-1,2);
        num = com.toDouble();
        emit response_Volt_Measuring(num);
        break;
    }
    case COM_CURR_MEASURING:
    {
        com.remove(com.size()-1,2);
        num = com.toDouble();
        emit response_Curr_Measuring(num);
        break;
    }
    case COM_CV_CC_MEASURING:

        if (com.contains("cv") || com.contains("CV")) n=CV;
        if (com.contains("cc") || com.contains("CC")) n=CC;
        if (com.contains("off") || com.contains("OFF")) n=OFF_CC_CV;
        emit response_Cv_Cc_Measuring(n);
        break;

    case COM_LOCAL_REMOTE_MODES_SET:
        com.remove(com.size()-1,2);
        n = com.toInt();
        emit response_LRM_Set(n);
        break;

    case COM_LOCAL_REMOTE_MODES_MEASURING:
        if (com.contains("loc") || com.contains("LOC")) n=LOC;
        if (com.contains("rem") || com.contains("REM")) n=REM;
        if (com.contains("llo") || com.contains("LLO")) n=LLO;
        emit response_LRM_Measuring(n);
        break;

    case COM_IDENTITY_QUERY:
    {
        com.remove(com.size()-1,2);
        str=QString::fromUtf8(com);
        isBind_ = true;
        emit response_Idntity_Query(str);
        break;
    }

    case COM_SYSTEM_ERROR:
    {
        com.remove(com.size()-1,2);
        str=QString::fromUtf8(com);
        QString s1 = str.section(',',0,0);
        QString s2 = str.section(',',1,1);
        n= s1.toInt();
        emit response_System_Error(n,s2,flag1);
        break;
    }
    }
}
//-----------------------------------------------------------------------------
void tdkLambdaClass::on_Write_Udp_Volt_Limit(double com)
{
    QString s = ":volt "+ QString::number(com);
    QByteArray num = s.toUtf8().data();
    udp_socket.writeDatagram(num, host, port);
    this->flag1=flag2;
    this->flag2=COM_VOLT_LIMIT;
    QTimer::singleShot(300, this, SLOT(on_Write_Udp_System_Error()));
}
//-----------------------------------------------------------------------------
void tdkLambdaClass::on_Write_Udp_Volt_Limit_Read()
{
    QString s1 = ":volt?";
    QByteArray num = s1.toUtf8().data();;
    udp_socket.writeDatagram(num, host, port);
    this->flag1=flag2;
    this->flag2=COM_VOLT_LIMIT_READ;
}
//-----------------------------------------------------------------------------
void tdkLambdaClass::on_Write_Udp_Curr_Limit(double com)
{
    QString s = ":curr "+ QString::number(com);
    QByteArray num = s.toUtf8().data();
    udp_socket.writeDatagram(num, host, port);
    this->flag1=flag2;
    this->flag2=COM_CURR_LIMIT;
    QTimer::singleShot(300, this, SLOT(on_Write_Udp_System_Error()));
}
//-----------------------------------------------------------------------------
void tdkLambdaClass::on_Write_Udp_Curr_Limit_Read()
{
    QString s1 = ":curr?";
    QByteArray num = s1.toUtf8().data();;
    udp_socket.writeDatagram(num, host, port);
    this->flag1=flag2;
    this->flag2=COM_CURR_LIMIT_READ;
}
//-----------------------------------------------------------------------------
void tdkLambdaClass::on_Write_Udp_Out_On_Off(bool checked)
{
    QString s1 = "output:state on";
    QString s2 = "output:state off";
    QByteArray num;
    if (checked) num = s1.toUtf8().data();
    else num = s2.toUtf8().data();
    udp_socket.writeDatagram(num, host, port);
    this->flag1=flag2;
    this->flag2=COM_OUT_ON_OFF;
    QTimer::singleShot(300, this, SLOT(on_Write_Udp_System_Error()));
}
//-----------------------------------------------------------------------------
void tdkLambdaClass::on_Write_Udp_Output_State()
{
    QString s1 = "output:state?";

    QByteArray num = s1.toUtf8().data();
    udp_socket.writeDatagram(num, host, port);
    this->flag1=flag2;
    this->flag2=COM_OUTPUT_STATE;

}
//-----------------------------------------------------------------------------

void tdkLambdaClass::on_Write_Udp_Volt_Measuring()
{
    QString s1 = "meas:volt?";
    QByteArray num = s1.toUtf8().data();
    udp_socket.writeDatagram(num, host, port);
    this->flag1=flag2;
    this->flag2=COM_VOLT_MEASURING;
}
//-----------------------------------------------------------------------------
void tdkLambdaClass::on_Write_Udp_Curr_Measuring()
{
    QString s1 = "meas:curr?";
    QByteArray num = s1.toUtf8().data();
    udp_socket.writeDatagram(num, host, port);
    this->flag1=flag2;
    this->flag2=COM_CURR_MEASURING;
}
//-----------------------------------------------------------------------------
void tdkLambdaClass::on_Write_Udp_Cv_Cc_Measuring()
{
    QString s1 = "sour:mode?";
    QByteArray num = s1.toUtf8().data();;
    udp_socket.writeDatagram(num, host, port);
    this->flag1=flag2;
    this->flag2=COM_CV_CC_MEASURING;
}
//-----------------------------------------------------------------------------
void tdkLambdaClass::on_Write_Udp_LRM_Set(int com)
{
    QString s = "syst:set "+ QString::number(com);
    QByteArray num = s.toUtf8().data();
    udp_socket.writeDatagram(num, host, port);
    this->flag1=flag2;
    this->flag2=COM_LOCAL_REMOTE_MODES_SET;
    QTimer::singleShot(300, this, SLOT(on_Write_Udp_System_Error()));
}
//-----------------------------------------------------------------------------
void tdkLambdaClass::on_Write_Udp_LRM_Measuring()
{
    QString s1 = "syst:set?";
    QByteArray num = s1.toUtf8().data();;
    udp_socket.writeDatagram(num, host, port);
    this->flag1=flag2;
    this->flag2=COM_LOCAL_REMOTE_MODES_MEASURING;
}
//-----------------------------------------------------------------------------
void tdkLambdaClass::on_Write_Udp_Idntity_Query()
{
    QString s1 = "*IDN?";
    QByteArray num = s1.toUtf8().data();;
    udp_socket.writeDatagram(num, host, port);
    this->flag1=flag2;
    this->flag2=COM_IDENTITY_QUERY;
}
//-----------------------------------------------------------------------------
void tdkLambdaClass::on_Write_Udp_System_Error()
{
    QString s1 = "syst:err?";
    QByteArray num = s1.toUtf8().data();;
    udp_socket.writeDatagram(num, host, port);
    this->flag1=flag2;
    this->flag2=COM_SYSTEM_ERROR;

}
