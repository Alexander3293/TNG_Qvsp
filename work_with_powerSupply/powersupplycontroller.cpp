#include "powersupplycontroller.h"


PowerSupplyController::PowerSupplyController(QObject *parent) : QObject(parent)
{
    timeUpdateDataMs_ = 2000;
    currentPowerTimer_ = new QTimer();
    connect(currentPowerTimer_, SIGNAL(timeout()), this, SLOT(updatePowerSupply()));
    tdkLambda_ = new tdkLambdaClass(this);

    connect(tdkLambda_, &tdkLambdaClass::updateState,             this, &PowerSupplyController::stateUpdated);
    connect(tdkLambda_, SIGNAL(response_Volt_Limit(double)),      this, SLOT(setVoltLimit(double)));
    connect(tdkLambda_, SIGNAL(response_Curr_Limit(double)),      this, SLOT(setCurrLimit(double)));
    connect(tdkLambda_, SIGNAL(response_Volt_Measuring(double)),  this, SLOT(sendVolt(double)));
    connect(tdkLambda_, SIGNAL(response_Curr_Measuring(double)),  this, SLOT(sendCurr(double)));
    connect(tdkLambda_, SIGNAL(response_Idntity_Query(QString)),  this, SLOT(return_Idntity_Query(QString)));

    this->setMode(remoteAndPowerSup);
}

void PowerSupplyController::setUpdateTimeData(int timeUpdateDataMs)
{
    timeUpdateDataMs_ = timeUpdateDataMs;
    currentPowerTimer_->setInterval(timeUpdateDataMs_);
}

QString PowerSupplyController::IdntityQueryMsg() const
{
    return IdntityQueryMsg_;
}

void PowerSupplyController::setIdntityQueryMsg(const QString &IdntityQueryMsg)
{
    IdntityQueryMsg_ = IdntityQueryMsg;
}

void PowerSupplyController::setLRM(quint8 mode)
{
    tdkLambda_->on_Write_Udp_LRM_Set(mode);
}

void PowerSupplyController::updatePowerSupply()
{
    if(surrOrVolt_)
        tdkLambda_->on_Write_Udp_Curr_Measuring();
    else
        tdkLambda_->on_Write_Udp_Volt_Measuring();
    surrOrVolt_ = !surrOrVolt_;
}

auto compareValues = [](double val, double maxVal){return ( (val < maxVal) && (val > -maxVal) ); };

void PowerSupplyController::sendVolt(double value)
{
    auto maximumPossibleValue = 1000.0;
    qInfo() << QString("Получено значение напряжения %1.").arg(value);
    if(compareValues(value, maximumPossibleValue) )
        emit volt(value);
    else return;
}

void PowerSupplyController::sendCurr(double value)
{
    auto maximumPossibleValue = 1000.0;
    qInfo() << QString("Получено значение тока %1.").arg(value);
    if(compareValues(value, maximumPossibleValue))
        emit curr(value);
    else return;
}

void PowerSupplyController::readVoltLimit(double value)
{
    auto maximumPossibleValue = 1000.0;
    if(compareValues(value, maximumPossibleValue))
        emit voltLimit(value);
    else return;
}

void PowerSupplyController::readCurrLimit(double value)
{
    auto maximumPossibleValue = 1000.0;
    if(compareValues(value, maximumPossibleValue))
        emit currLimit(value);
    else return;
}

// ответ на сообщение on_Write_Udp_Idntity_Query() в функции powerOn()
void PowerSupplyController::return_Idntity_Query(QString msg)
{
//    setIdntityQueryMsg(msg);
    emit msgFromPowerSupply(msg);
    setLRM(mode());
}

void PowerSupplyController::setVoltLimit(double voltLimit)
{
    tdkLambda_->on_Write_Udp_Volt_Limit(voltLimit);
    qInfo() << QString("Установлено напряжение %1").arg(voltLimit);
}

void PowerSupplyController::powerOn()
{
    tdkLambda_->on_Write_Udp_Out_On_Off(true);
    tdkLambda_->on_Write_Udp_Idntity_Query();
    currentPowerTimer_->start();
    qInfo() << QString("Включение блока питания для операций прижим/отжим");
}

void PowerSupplyController::powerOff()
{
    tdkLambda_->on_Write_Udp_Out_On_Off(false);
    currentPowerTimer_->stop();
    qInfo() << QString("Отключение блока питания для операций прижим/отжим");
}

void PowerSupplyController::setCurrLimit(double currLimit)
{
    qInfo() << QString("Установлено ограничение по току %1").arg(currLimit);
    tdkLambda_->on_Write_Udp_Curr_Limit(currLimit);
}
qint8 PowerSupplyController::mode() const
{
    return mode_;
}

void PowerSupplyController::stateUpdated(QString strState)
{
//    emit msgFromPowerSupply(strState);
}

void PowerSupplyController::setMode(const qint8 &mode)
{
    mode_ = mode;
}
