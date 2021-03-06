#include "graphground.h"
#include "ui_graphground.h"

graphGround::graphGround(Transceiver_ground *transceiver, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graphGround)

{
    ui->setupUi(this);
    deviceCount = 0;
    transceiver_ground_ = transceiver;
    width_ = 500;
    globalOffset = -1;
}

graphGround::~graphGround()
{
    delete ui;
}

void graphGround::plotData(pointsFromWGrounds *dataPckt)
{
    /* plot without offset
    if(dataPckt->numModule == deviceCount)  {

    timeMes_ = dataPckt->time;
    dataSize_ = dataPckt->data.size();
    y.clear();
    //y.resize(width_);
    for(int i=0; i< dataSize_; i++){
        y.append(dataPckt->data[i]);

    }
    ui->customPlot->graph()->setData(x, y);
    // set axes ranges, so we see all data:
    ui->customPlot->rescaleAxes();
    //ui->customPlot->yAxis->setRange(0, 1);

    ui->customPlot->replot();
        //x.clear();
    }                   */

    if(dataPckt->numModule == deviceCount)  {

        timeMes_ = dataPckt->time;
        dataSize_ = dataPckt->data.size();

        //y.resize(width_);
        for(int i=0; i< dataSize_; i++){
            y.append(dataPckt->data[i]);
            if(y.size() >= width_) {
                ui->customPlot->graph()->setData(x, y);
                ui->customPlot->rescaleAxes();
                ui->customPlot->replot();
                y.clear();
            }
        }
    }
}

/* ЧТобы 1 раз установить offset и все, дальше стандартно */
void graphGround::frstPlotData(pointsFromWGrounds *dataPckt)
{
    if(dataPckt->numModule == deviceCount)  {
        while(globalOffset == -1);
        connect(transceiver_ground_, SIGNAL(dataGroundUpdate(pointsFromWGrounds*)), this, SLOT(plotData(pointsFromWGrounds*)));
        disconnect(transceiver_ground_, SIGNAL(dataGroundUpdate(pointsFromWGrounds*)), this, SLOT(frstPlotData(pointsFromWGrounds*)));

        timeMes_ = dataPckt->time;
        dataSize_ = dataPckt->data.size();
        y.clear();
        //y.resize(width_);
        for(int i=globalOffset; i< dataSize_; i++){
            y.append(dataPckt->data[i]);

        }

        if(y.size() >= width_) {
            ui->customPlot->graph()->setData(x, y);
            ui->customPlot->rescaleAxes();
            ui->customPlot->replot();
            y.clear();
        }
    }
}

void graphGround::setDevNum(quint8 devCon) {
    deviceCount = devCon;
}

quint8 graphGround::getDevNum() {
    return deviceCount;
}

void graphGround::setWidth(int val)
{
    width_ = val;
   // y.resize(width_);
    for(int i=0; i < width_; i++) x.append(i);
}

/* задать смещение */
void graphGround::setOffset(int offset)
{
    globalOffset = offset;
}

void graphGround::initGraphGround()
{
    ui->customPlot->addGraph(); // blue line
    ui->customPlot->graph()->setPen(QPen(QColor(40, 110, 255)));

    ui->customPlot->xAxis->setTicks(0); //off ticks
    ui->customPlot->yAxis->setTicks(0);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->customPlot->xAxis->setTicker(timeTicker);

    ui->customPlot->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->legend->setSelectedFont(legendFont);
    ui->customPlot->legend->setSelectableParts(QCPLegend::spNone);

    ui->customPlot->graph()->setName(QString("Наземный %1").arg(deviceCount));
    /* every 1/4 sec ploting */
   // connect(transceiver_ground_, SIGNAL(dataGroundUpdate(pointsFromWGrounds*)), this, SLOT(plotData(pointsFromWGrounds*)));
    connect(transceiver_ground_, SIGNAL(dataGroundUpdate(pointsFromWGrounds*)), this, SLOT(frstPlotData(pointsFromWGrounds*)));
}
