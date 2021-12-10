/*-------------------------------------------------------------------
                              ovsp2pc.h
    Описаны типы данных для обмена м/у ПК и Ethernet-контроллером

                                                     Петрухин А.С.
                                                 19 октября 2015г.
-------------------------------------------------------------------*/

//Список команд для работы с скважинными модулями (подземные)


#ifndef	DECLARATEDATAFORALLCLASSES
#define	DECLARATEDATAFORALLCLASSES
//-------------------------------------------------------------------
#include <QMetaType>
#include <QDataStream>
#include <QVector>
//-------------------------------------------------------------------
#define	PC_PORT	1500

#define COUNT_DOWNHOLE_MODULES 8
#define COUNT_WELLS_MODULES 8
//-------------------------------------------------------------------
#define	COMAND_SET_DEPT                 0x0001
#define	COMAND_READ_DEPT                0x0002
//--------------------------------------------
//#define	COMAND_REPEAT_LAST_DATA         0x0003  //в данном проекте не поддерживается
//#define	COMAND_DO_MESERMENT             0x0004  //в данном проекте не поддерживается
//#define	COMAND_VAK8N_DO_MESERMENT       0x0005  //в данном проекте не поддерживается
//#define	COMAND_VAK8N_SD_DO_MESERMENT    0x0006  //в данном проекте не поддерживается
//#define	COMAND_VAK8M09_DO_MESERMENT     0x0007  //в данном проекте не поддерживается
//#define	COMAND_VAK8_SLOW_DO_MESERMENT   0x0008  //в данном проекте не поддерживается
//#define	COMAND_SAS_BP_SLOW_DO_MESERMENT 0x0009  //в данном проекте не поддерживается
//#define	COMAND_VAK32_DO_MESERMENT       0x000A  //в данном проекте не поддерживается
//--------------------------------------------
// Группа команд для ВСП-модулей
//--------------------------------------------
#define	COMAND_OVSP_DO_MESERMENT        0x0100
#define	COMAND_OVSP_SET_KU              0x0101
#define	COMAND_OVSP_RELE_ON             0x0102
#define	COMAND_OVSP_RELE_OFF            0x0103
#define	COMAND_OVSP_TEST_MODE           0x0104
#define	COMAND_OVSP_WORK_MODE           0x0105
#define	COMAND_OVSP_PWR_ON				0x0108 //ctl pwr
#define	COMAND_OVSP_PWR_OFF				0x0109 //ctl pwr
#define	COMAND_OVSP_PRIGIM				0x0110 //ctl u1
#define	COMAND_OVSP_OTGIM				0x0111 //ctl u1
#define	COMAND_OVSP_MOTOR_ON			0x0112 //ctl u2
#define	COMAND_OVSP_MOTOR_OFF			0x0113 //ctl u2
#define COMMAND_OVSP_ILIMIT             0x0114
#define COMMAND_OVSP_INORMAL            0x0115
#define COMMAND_OVSP_OFFSET_CORECTION   0x0116
//-------------------------------------------------------------------
#define	CTRL_POCKET_LEN			20
#define OVSP_NUM_POINTS         320 //200
//-------------------------------------------------------------------


enum typeModules {
    SYNC,
    DN_HOLE_X,
    DN_HOLE_Y,
    DN_HOLE_Z,
    UP_HOLE
};

typedef struct	
{
    short int	id; //идентификатор команды или пакета данных
    short int	ml; //признак магнитной метки
    int     	dept; // глубина, в см.
    short int	KU; // коэффициент усиления
    short int	module_No; //номер модуля, которому предназначена команда
    short int	n_pocket;
    short int	status;
    short int	rezerv[40];
}	TCtrlPocket;

//-------------------------------------------------------------------
typedef struct	
{
    short int	id; //идентификатор команды или пакета данных
    short int	ml; // признак магнитной метки
    int     	dept; // глубина, в см.
    unsigned short int	n_pocket; //номер пакета, применяется для контроля пропусков данных
    short int	status; //состояние наземной платы
    short int	data[OVSP_NUM_POINTS];  // пакет данных от связки скважинных модулей
}	TDataPocket;

typedef struct
{
    short int	id_cmd;     //идентификатор команды или пакета данных
    short int	module_No;  //номер наземного устройства, которому предназначена команда
    short int	settings;   // (пустое поле для будущей настройки)
    short int	KU_usilenie;// коэффициент усиления/ослабления
}	TCmdGroundPocket;

typedef struct
{
    QVector<QVector<int>> timeValue;   // массив времени для каждой точки
    QVector<QList<qint32*>*> allData_list;// матрица данных
}	universalTemporaryData;

QDataStream& operator <<(QDataStream &out, const TDataPocket &data_pocket);
QDataStream& operator >>(QDataStream &in, TDataPocket* data_pocket);
Q_DECLARE_METATYPE(TDataPocket)
Q_DECLARE_METATYPE(universalTemporaryData)
//Q_DECLARE_METATYPE(typeModules)
//-------------------------------------------------------------------
#endif	//	DECLARATEDATAFORALLCLASSES
//-------------------------------------------------------------------

