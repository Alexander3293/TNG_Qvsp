#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include "network/transceiver_class.h"
#include "network/transceiver_ground.h"

namespace Ui {
class test;
}

class test : public QWidget
{
    Q_OBJECT

public:
    explicit test(Transceiver_ground *transceiver_ground,Transceiver_class *transceiver_down,QWidget *parent = nullptr);
    ~test();
    void conectSignals();
    void initGraphXYZ();
public slots:
    void plotData(pointsFromWGrounds* dataPckt);
    void slot_data_update (const int blk_cnt, const pointFromDownHoles &point);

private:
    Ui::test *ui;
    QVector <double>    X, y;
    int dataSize_;
    uint                deviceCount;
    Transceiver_ground *transceiver_ground_;
    Transceiver_class *trasceiver_down_;
    int timeMes_;
    int width_;
    double frequnce = 998.5;

    int     trace_23_16_X, trace_23_16_Y, trace_23_16_Z;
    int     trace23_16ForKU_X_, trace23_16ForKU_Y_, trace23_16ForKU_Z_;
    int     trace15_8ForKU_X_, trace15_8ForKU_Y_, trace15_8ForKU_Z_;
    int     trace_15_8_X, trace_15_8_Y, trace_15_8_Z;
    int     trace_7_0_X, trace_7_0_Y, trace_7_0_Z;
    QVector<double> data_vectorX, data_cpyX, data_vectorY, data_cpyY, data_vectorZ, data_cpyZ;

    void setTraceDnHole();
    qint32 mesX, mesY, mesZ;


};

#endif // TEST_H
