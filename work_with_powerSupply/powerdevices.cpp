#include "powerdevices.h"
#include "ui_powerdevices.h"

PowerDevices::PowerDevices(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PowerDevices),
    tdk_lambda(parent)
{
    ui->setupUi(this);

    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);

    this->tdk_lambda.setHost(QHostAddress("192.168.1.26"));

    connect(this, SIGNAL(write_Udp_Volt_Limit(double)),     &tdk_lambda, SLOT(on_Write_Udp_Volt_Limit(double)));
    connect(this, SIGNAL(write_Udp_Volt_Limit_Read(void)),  &tdk_lambda, SLOT(on_Write_Udp_Volt_Limit_Read(void)));
    connect(this, SIGNAL(write_Udp_Curr_Limit(double)),     &tdk_lambda, SLOT(on_Write_Udp_Curr_Limit(double)));
    connect(this, SIGNAL(write_Udp_Curr_Limit_Read(void)),  &tdk_lambda, SLOT(on_Write_Udp_Curr_Limit_Read(void)));
    connect(this, SIGNAL(write_Udp_Out_On_Off(bool)),       &tdk_lambda, SLOT(on_Write_Udp_Out_On_Off(bool)));
    connect(this, SIGNAL(write_Udp_Output_State(void)),     &tdk_lambda, SLOT(on_Write_Udp_Output_State(void)));
    connect(this, SIGNAL(write_Udp_Volt_Measuring()),       &tdk_lambda, SLOT(on_Write_Udp_Volt_Measuring()));
    connect(this, SIGNAL(write_Udp_Curr_Measuring()),       &tdk_lambda, SLOT(on_Write_Udp_Curr_Measuring()));
    connect(this, SIGNAL(write_Udp_Cv_Cc_Measuring()),      &tdk_lambda, SLOT(on_Write_Udp_Cv_Cc_Measuring()));
    connect(this, SIGNAL(write_Udp_LRM_Set(int)),           &tdk_lambda, SLOT(on_Write_Udp_LRM_Set(int)));
    connect(this, SIGNAL(write_Udp_LRM_Measuring()),        &tdk_lambda, SLOT(on_Write_Udp_LRM_Measuring()));
    connect(this, SIGNAL(write_Udp_Idntity_Query()),        &tdk_lambda, SLOT(on_Write_Udp_Idntity_Query()));
    connect(this, SIGNAL(write_Udp_System_Error()),         &tdk_lambda, SLOT(on_Write_Udp_System_Error()));

    connect(&tdk_lambda, SIGNAL(updateState(QString)),                  this, SLOT(newState(QString)));
    connect(&tdk_lambda, SIGNAL(response_Volt_Limit(double)),           this, SLOT(return_Volt_Limit(double)));
    connect(&tdk_lambda, SIGNAL(response_Volt_Limit_Read(double)),      this, SLOT(return_Volt_Limit_Read(double)));
    connect(&tdk_lambda, SIGNAL(response_Curr_Limit(double)),           this, SLOT(return_Curr_Limit(double)));
    connect(&tdk_lambda, SIGNAL(response_Curr_Limit_Read(double)),      this, SLOT(return_Curr_Limit_Read(double)));
    connect(&tdk_lambda, SIGNAL(response_Out_On_Off(bool)),             this, SLOT(return_Out_On_Off(bool)));
    connect(&tdk_lambda, SIGNAL(response_Output_State(bool)),           this, SLOT(return_Output_State(bool)));
    connect(&tdk_lambda, SIGNAL(response_Volt_Measuring(double)),       this, SLOT(return_Volt_Measuring(double)));
    connect(&tdk_lambda, SIGNAL(response_Curr_Measuring(double)),       this, SLOT(return_Curr_Measuring(double)));
    connect(&tdk_lambda, SIGNAL(response_Cv_Cc_Measuring(int)),         this, SLOT(return_Cv_Cc_Measuring(int)));
    connect(&tdk_lambda, SIGNAL(response_LRM_Set(int)),                 this, SLOT(return_LRM_Set(int)));
    connect(&tdk_lambda, SIGNAL(response_LRM_Measuring(int)),           this, SLOT(return_LRM_Measuring(int)));
    connect(&tdk_lambda, SIGNAL(response_Idntity_Query(QString)),       this, SLOT(return_Idntity_Query(QString)));
    connect(&tdk_lambda, SIGNAL(response_System_Error(int,QString,int)),this, SLOT(return_System_Error(int,QString,int)));

}
//---------------------------------------------------------------------------------------------------------------
PowerDevices::~PowerDevices()
{
    delete ui;
}
//-------------------------------------------------------------------------------
void PowerDevices::on_pushButton_Set_Volt_Limit_clicked()
{
    emit write_Udp_Volt_Limit(ui->doubleSpinBox_Volt_Limit->value());
}
//-------------------------------------------------------------------------------
void PowerDevices::on_pushButton_Set_Curr_Limit_clicked()
{
    emit write_Udp_Curr_Limit(ui->doubleSpinBox_Curr_Limit->value());

}
//-------------------------------------------------------------------------------
void PowerDevices::on_radioButton_On_Off_clicked(bool checked)
{
    emit this->write_Udp_Out_On_Off(checked);

}
//-------------------------------------------------------------------------------
void PowerDevices::on_pushButton_Set_LRM_clicked()
{
    emit this->write_Udp_LRM_Set(ui->spinBox_Set_LRM->value());
}

//-------------------------------------------------------------------------------
void PowerDevices::newState(QString strState)
{
    ui->labelState->setText(strState);
//    if(strState.contains("No")){
//        ui->labelState->setStyleSheet("background-color : red; color : black;");
//    }
//    else {
        ui->labelState->setStyleSheet("background-color : white; color : green;");
//    }
}

//-------------------------------------------------------------------------------
void PowerDevices:: return_Volt_Limit(double com)
{
    ui->doubleSpinBox_Volt_Limit->setValue(com);
}
//-------------------------------------------------------------------------------
void PowerDevices::return_Volt_Limit_Read(double com)
{
    ui->doubleSpinBox_Volt_Limit->setValue(com);
}
//-------------------------------------------------------------------------------
void PowerDevices::return_Curr_Limit(double com)
{
    ui->doubleSpinBox_Curr_Limit->setValue(com);
}
//-------------------------------------------------------------------------------
void PowerDevices::return_Curr_Limit_Read(double com)
{
    ui->doubleSpinBox_Curr_Limit->setValue(com);
}
//-------------------------------------------------------------------------------
void PowerDevices::return_Out_On_Off(bool checked)
{
    ui->radioButton_On_Off->setChecked(checked);

}
//-------------------------------------------------------------------------------
void PowerDevices::return_Output_State(bool checked)
{
    ui->radioButton_On_Off->setChecked(checked);
}

void PowerDevices::return_Volt_Measuring(double com)
{
    ui->doubleSpinBox_Volt_Meas->setValue(com);
}
//-------------------------------------------------------------------------------
void PowerDevices::return_Curr_Measuring(double com)
{
    ui->doubleSpinBox_Curr_Meas->setValue(com);
}
//-------------------------------------------------------------------------------
void PowerDevices::return_Cv_Cc_Measuring(int com)
{
    switch (com)
    {
    case CV:  ui->lineEdit_Get_CC_CV->setText("CV");break;
    case CC : ui->lineEdit_Get_CC_CV->setText("CC");break;
    case OFF_CC_CV: ui->lineEdit_Get_CC_CV->setText("OFF_CC_CV");break;
    }
}
//-------------------------------------------------------------------------------
void PowerDevices::return_LRM_Set(int com)
{
    ui->spinBox_Set_LRM->setValue(com);
}
//-------------------------------------------------------------------------------
void PowerDevices::return_LRM_Measuring(int com)
{
    ui->spinBox_Set_LRM->setValue(com);
}
//-------------------------------------------------------------------------------
void PowerDevices::return_Idntity_Query(QString str)
{
    ui->lineEdit_Get_Idntity_Query->setText(str);
}
//-------------------------------------------------------------------------------
void PowerDevices::return_System_Error(int error,QString str,int source_Comm)
{
    ui->lineEdit_Command_Error_Message->setText(QString::number(source_Comm));
    ui->lineEdit_Get_System_Error->setText(str);
    ui->spinBox_Error->setValue(error);
}

//-------------------------------------------------------------------------------

void PowerDevices::on_pushButton_Get_Volt_Limit_clicked()
{
    emit write_Udp_Volt_Limit_Read();
}

void PowerDevices::on_pushButton_Get_Idntity_Query_clicked()
{
    emit write_Udp_Idntity_Query();

}

void PowerDevices::on_pushButton_Get_LRM_clicked()
{
    emit this->write_Udp_LRM_Measuring();
}

void PowerDevices::on_pushButton_Get_Cv_Cc_clicked()
{
    emit write_Udp_Cv_Cc_Measuring();
}

void PowerDevices::on_pushButton_Get_Curr_Meas_clicked()
{
    emit write_Udp_Curr_Measuring();
}

void PowerDevices::on_pushButton_Get_Volt_Meas_clicked()
{
    emit write_Udp_Volt_Measuring();
}

void PowerDevices::on_pushButton_Get_On_Off_clicked()
{
    emit write_Udp_Output_State();
}

void PowerDevices::on_pushButton_Get_Curr_Limit_clicked()
{
    emit write_Udp_Curr_Limit_Read();
}

void PowerDevices::on_pushButton_Get_Error_clicked()
{
    emit write_Udp_System_Error();
}
