#ifndef POWERSUPPLYCONTROLLER_H
#define POWERSUPPLYCONTROLLER_H

/*
* Класс для управления питанием tdk lambda для приижмного механизма
*
*/

#include <QDebug>
#include "tdklambdaclass.h"
#include <QTimer>
#include <QObject>

class PowerSupplyController : public QObject
{
    Q_OBJECT
    enum mode
    {
        jastPowerSup  = 0,
        remoteAndPowerSup = 1,
        jastRemoteAccess = 2
    };

private:
    QTimer* currentPowerTimer_;
    tdkLambdaClass* tdkLambda_;
    int timeUpdateDataMs_;
    QString IdntityQueryMsg_;
    qint8 mode_;
    bool surrOrVolt_ = false;

public:
    explicit PowerSupplyController(QObject *parent = nullptr);
    void setIdntityQueryMsg(const QString &IdntityQueryMsg);

signals:
    void curr(double);
    void volt(double);
    void voltLimit(double);
    void currLimit(double);
    void msgFromPowerSupply(QString);

private slots:
    void updatePowerSupply();
    void sendVolt(double value);
    void sendCurr(double value);
    void return_Idntity_Query(QString msg);
    void setLRM(quint8 mode);
    qint8 mode() const;
    void stateUpdated(QString strState);

public slots:
    void setUpdateTimeData(int timeUpdateDataMs);
    void setCurrLimit(double currLimit);
    void setVoltLimit(double voltLimit);
    void readVoltLimit(double value);
    void readCurrLimit(double value);
    void powerOn();
    void powerOff();
    QString IdntityQueryMsg() const;
    void setMode(const qint8 &mode);

};

#endif // POWERSUPPLYCONTROLLER_H
