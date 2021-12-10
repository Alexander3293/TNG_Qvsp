#ifndef GRAPHSYNC_H
#define GRAPHSYNC_H

#include <QWidget>
#include "network/syncmoduletranciever.h"
namespace Ui {
class graphSync;
}

class graphSync : public QWidget
{
    Q_OBJECT

public:
    explicit graphSync(SyncModuleTranciever* transceiver, QWidget *parent = nullptr);
    ~graphSync();
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
    Ui::graphSync *ui;
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

#endif // GRAPHSYNC_H
