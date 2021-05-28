#ifndef TDKLAMBDACLASS
#define TDKLAMBDACLASS

/*
* Класс для приема передачи данных на tdk lambda
*
*/
//-----------------------------------------------------------------------------
#include <QObject>
#include <QString>
#include <QtNetwork/QUdpSocket>
#include <QByteArray>
#include <QTimer>
//-----------------------------------------------------------------------------
#define  COM_VOLT_LIMIT       1
#define  COM_VOLT_LIMIT_READ  2
#define  COM_CURR_LIMIT  3
#define  COM_CURR_LIMIT_READ  4
#define  COM_OUT_ON_OFF  5
#define  COM_VOLT_MEASURING  6
#define  COM_CURR_MEASURING  7
#define  COM_CV_CC_MEASURING  8
#define  COM_LOCAL_REMOTE_MODES_SET 9
#define  COM_LOCAL_REMOTE_MODES_MEASURING  10
#define  COM_IDENTITY_QUERY  11
#define  COM_OUTPUT_STATE 12
#define  COM_SYSTEM_ERROR 13

#define  CV  0
#define  CC  1
#define  OFF_CC_CV 2
#define  LOC  0
#define  REM 1
#define  LLO 2
//-----------------------------------------------------------------------------
typedef struct
{
    int         error;
    QString     error_Message;
}	TSYSTEMERROR;
//-----------------------------------------------------------------------------
class tdkLambdaClass : public QObject
{
    Q_OBJECT

public:
    explicit tdkLambdaClass(QObject *parent = 0);
    ~tdkLambdaClass();

    QHostAddress getHost() const;
    void setHost(const QHostAddress &value);

private:
    int             port;
    short int       p_count;
    short int       cmd_id;
    QUdpSocket      udp_socket;
    QHostAddress    host;
    int             flag1, flag2;
    bool            isBind_ = false;
    void            initializeParametres();

signals:
    void   updateState(QString strState);
    void   response_Volt_Limit(double com);
    void   response_Volt_Limit_Read(double com);
    void   response_Curr_Limit(double com);
    void   response_Curr_Limit_Read(double com);
    void   response_Out_On_Off(bool checked);
    void   response_Output_State(bool checked);
    void   response_Volt_Measuring(double com);
    void   response_Curr_Measuring(double com);
    void   response_Cv_Cc_Measuring(int com);
    void   response_LRM_Set(int com);
    void   response_LRM_Measuring(int com);
    void   response_Idntity_Query(QString);
    void   response_System_Error(int error,QString, int source_Comm);

public slots:
     void read_Udp_Data_Response(void);

     void on_Write_Udp_Volt_Limit(double com);
     void on_Write_Udp_Volt_Limit_Read();
     void on_Write_Udp_Curr_Limit(double com);
     void on_Write_Udp_Curr_Limit_Read();
     void on_Write_Udp_Out_On_Off(bool checked);
     void on_Write_Udp_Output_State();
     void on_Write_Udp_Volt_Measuring();
     void on_Write_Udp_Curr_Measuring();
     void on_Write_Udp_Cv_Cc_Measuring();
     void on_Write_Udp_LRM_Set(int com);
     void on_Write_Udp_LRM_Measuring();
     void on_Write_Udp_Idntity_Query();
     void on_Write_Udp_System_Error();

private slots:
     void rebind();

};
//-----------------------------------------------------------------------------
#endif // TDKLAMBDACLASS

//-----------------------------------------------------------------------------



