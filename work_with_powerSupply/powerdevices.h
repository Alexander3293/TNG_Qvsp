#ifndef POWERDEVICES_H
#define POWERDEVICES_H

#include <QWidget>
#include <QByteArray>

/*
* Класс для управления питанием скважинных (подземных) модулей tdk lambda
*
*/

#include "work_with_powerSupply/tdkLambdaClass.h"

namespace Ui {
class PowerDevices;
}

class PowerDevices : public QWidget
{
    Q_OBJECT

private:
    Ui::PowerDevices *ui;
    tdkLambdaClass tdk_lambda;
public:
    explicit PowerDevices(QWidget *parent = 0);
    ~PowerDevices();

signals:
    void write_Command(QByteArray);

    void write_Udp_Volt_Limit(double com);
    void write_Udp_Volt_Limit_Read();
    void write_Udp_Curr_Limit(double com);
    void write_Udp_Curr_Limit_Read();
    void write_Udp_Out_On_Off(bool checked);
    void write_Udp_Output_State();
    void write_Udp_Volt_Measuring();
    void write_Udp_Curr_Measuring();
    void write_Udp_Cv_Cc_Measuring();
    void write_Udp_LRM_Set(int com);
    void write_Udp_LRM_Measuring();
    void write_Udp_Idntity_Query();
    void write_Udp_System_Error();

private slots:
    void on_pushButton_Set_Volt_Limit_clicked();
    void on_pushButton_Set_Curr_Limit_clicked();
    void on_radioButton_On_Off_clicked(bool checked);
    void on_pushButton_Set_LRM_clicked();

    void newState(QString strState);
    void return_Volt_Limit(double com);
    void return_Volt_Limit_Read(double com);
    void return_Curr_Limit(double com);
    void return_Curr_Limit_Read(double com);
    void return_Out_On_Off(bool checked);
    void return_Output_State(bool checked);
    void return_Volt_Measuring(double com);
    void return_Curr_Measuring(double com);
    void return_Cv_Cc_Measuring(int com);
    void return_LRM_Set(int com);
    void return_LRM_Measuring(int com);
    void return_Idntity_Query(QString);
    void return_System_Error(int error,QString,int source_Comm);

    void on_pushButton_Get_Volt_Limit_clicked();

    void on_pushButton_Get_Idntity_Query_clicked();
    void on_pushButton_Get_LRM_clicked();
    void on_pushButton_Get_Cv_Cc_clicked();
    void on_pushButton_Get_Curr_Meas_clicked();
    void on_pushButton_Get_Volt_Meas_clicked();
    void on_pushButton_Get_On_Off_clicked();
    void on_pushButton_Get_Curr_Limit_clicked();
    void on_pushButton_Get_Error_clicked();
};

#endif // POWERDEVICES_H
