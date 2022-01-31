#ifndef GRAPHGROUND_H
#define GRAPHGROUND_H

#include <QWidget>
#include "network/transceiver_ground.h"


namespace Ui {
class graphGround;
}

class graphGround : public QWidget
{
    Q_OBJECT

public:
    explicit graphGround(Transceiver_ground *transceiver, QWidget *parent = nullptr);
    ~graphGround();
    void setDevNum(quint8 devCon);
    quint8 getDevNum();
    void initGraphGround();
    void setWidth(int val);
    void setOffset(uint8_t , uint8_t, const int );
    void rangeChanged(double axisY);
    void getTimerVibro(uint time);

public slots:
    void plotData(pointsFromWGrounds *dataPckt);
    void frstPlotData(pointsFromWGrounds *dataPckt);
    void setGroundDevState(quint8 numDev, bool state);

private:
    Ui::graphGround     *ui;
    QVector <double>    x, y;
    int dataSize_;
    uint                deviceCount;
    Transceiver_ground *transceiver_ground_;
    int timeMes_;
    int width_;

    int16_t numPckt_;
    int16_t numMeasure_;
    uint32_t error_crc_;
    uint32_t error_pckt_;

    bool realTime;
};

#endif // GRAPHGROUND_H
