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
    void setOffset(int);

public slots:
    void plotData(pointsFromWGrounds *dataPckt);
    void frstPlotData(pointsFromWGrounds *dataPckt);

private:
    Ui::graphGround     *ui;
    QVector <double>    x, y;
    int dataSize_;
    uint                deviceCount;
    Transceiver_ground *transceiver_ground_;
    int timeMes_;
    int width_;
    int globalOffset;
    double frequnce = 998.5;

};

#endif // GRAPHGROUND_H
