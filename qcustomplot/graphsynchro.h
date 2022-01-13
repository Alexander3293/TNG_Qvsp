#ifndef GRAPHSYNCHRO_H
#define GRAPHSYNCHRO_H

#include <QWidget>

#include <QWidget>
#include "network/syncmoduletranciever.h"
#include "qcustomplot/paintlegend.h"
namespace Ui {
class graphsynchro;
}

class graphsynchro : public QWidget
{
    Q_OBJECT

public:
    explicit graphsynchro(SyncModuleTranciever* transceiver, QWidget *parent = nullptr);
    ~graphsynchro();
    void plot();
    void initGraphSync();
    void setWidth(int val);
    void clearData();
    void setOffset(uint8_t numPckt,uint8_t numMeasure, const int blk_cnt);

public slots:
    void changeTimeBreakSlot(const QString cmd, const QString chnl);

private slots:
    void frstPlotData(SyncModuleTranciever::pointsFromSync *dataPckt);
    void plotData(SyncModuleTranciever::pointsFromSync *dataPckt);
private:
    Ui::graphsynchro *ui;
    PaintLegend *legendSync;
    QVector <double>    x, dataADC, dataTB, dataCTB;
    int dataSize_;
    SyncModuleTranciever *transceiver_sync_;
    int timeMes_;
    int width_;
    quint16 maxAmpl_;
    bool isVibro_;
    int16_t numPckt_;
    int16_t numMeasure_;
};

#endif // GRAPHSYNCHRO_H
