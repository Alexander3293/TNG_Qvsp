#ifndef GRAPHDOWNHOLE_H
#define GRAPHDOWNHOLE_H

#include <QWidget>
#include "network/transceiver_class.h"
typedef enum {
    trace_XYZ   = 0,
    trace_Y   = 1,
    trace_Z   = 2,
    trace_CMD = 3,
    trace_KU  = 4,
    moduleSync = 5,
    syncTBF  = 6,
    syncTBV  = 7
}OVSP_TRACES;

namespace Ui {
class graphDownHole;
}

class graphDownHole : public QWidget
{
    Q_OBJECT

public:
    explicit graphDownHole(Transceiver_class* transceiver, QWidget *parent = nullptr);
    ~graphDownHole();
    void setModNum(quint8 devCon);
    quint8 getModNum();
    void clearData();
    void setWidth(int width);
    void setTraceDnHole();
    void initGraphXYZ();
    void stopPlot();

public slots:
    void plotData();
    void slot_data_update (const int blk_cnt, const pointFromDownHoles &point);
signals:
    void updateSceneWidth();
private:
    Ui::graphDownHole *ui;
    QVector <double> xTime_, xTimeCpy_;
    int nowTime_;
    uint                num_module;
    Transceiver_class* transceiver_;
    int     trace_23_16_X, trace_23_16_Y, trace_23_16_Z;
    int     trace23_16ForKU_X_, trace23_16ForKU_Y_, trace23_16ForKU_Z_;
    int     trace15_8ForKU_X_, trace15_8ForKU_Y_, trace15_8ForKU_Z_;
    int     trace_15_8_X, trace_15_8_Y, trace_15_8_Z;
    int     trace_7_0_X, trace_7_0_Y, trace_7_0_Z;
    QVector<double> data_vectorX, data_cpyX, data_vectorY, data_cpyY, data_vectorZ, data_cpyZ;
    int    width_;

    qint32 mesX, mesY, mesZ;

};

#endif // GRAPHDOWNHOLE_H
