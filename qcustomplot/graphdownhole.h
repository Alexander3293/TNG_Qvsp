#ifndef GRAPHDOWNHOLE_H
#define GRAPHDOWNHOLE_H

#include <QWidget>
#include "network/transceiver_class.h"
#include "checksum.h"

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

typedef enum{
    graph_axis_X = 0,
    graph_axis_Y,
    graph_axis_Z
}init_graph_DownHoles ;

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
    void initGraphXYZ(init_graph_DownHoles axis);
    void stopPlot();
    void rangeChanged(double axisY);

public slots:
    void plotData();
    void slot_data_update (const int blk_cnt, const pointFromDownHoles &point);

signals:
    void updateSceneWidth();
private slots:
    void on_relayModeButton_clicked(bool checked);

private:
    Ui::graphDownHole *ui;
    QVector <double> xTime_, xTimeCpy_;
    int nowTime_;
    uint                num_module;
    Transceiver_class* transceiver_;
    int     trace_23_16;
    int     trace23_16ForKU_X_, trace23_16ForKU_Y_, trace23_16ForKU_Z_;
    int     trace15_8ForKU_X_, trace15_8ForKU_Y_, trace15_8ForKU_Z_;
    int     trace_15_8;
    int     trace_7_0;
    //QVector<double> data_vectorX, data_cpyX, data_vectorY, data_cpyY, data_vectorZ, data_cpyZ;
    QVector<double> data_vector_XYZ, data_cpyXYZ;
    int    width_;

    qint32 mesX;
    bool flagFirst = false;

    int maxValMissPacket = 0x7fffff;  //8 388 607 (int24)
    checksum crc_;

    uint8_t trace_XYZ;

};

#endif // GRAPHDOWNHOLE_H
