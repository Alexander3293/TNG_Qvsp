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
    numPckt_ = -1;
    numMeasure_ = -1;
}

graphGround::~graphGround()
{
    delete ui;
}

void graphGround::plotData(pointsFromWGrounds *dataPckt)
{
    if(deviceCount  == dataPckt->numModule)  {

        //timeMes_ = dataPckt->time;
        dataSize_ = dataPckt->data.size();

        for(int i=0; i< dataSize_; i++){
            y.append(dataPckt->data[i]);
            if(y.size() >= width_) {
                ui->customPlot->graph(0)->setData(x, y);
                ui->customPlot->rescaleAxes();
                ui->customPlot->replot();
                y.clear();
            }
        }
    }
}

void graphGround::rangeChanged(double axisY)
{
    ui->customPlot->yAxis->setRange(-axisY, axisY);
    ui->customPlot->replot();
}

/* ЧТобы 1 раз установить offset и все, дальше стандартно */
void graphGround::frstPlotData(pointsFromWGrounds *dataPckt)
{
    if((dataPckt->numModule == deviceCount) && (numPckt_ == dataPckt->numPckt))  {  //если тот девайс и тот пакет

        disconnect(transceiver_ground_, SIGNAL(dataGroundUpdate(pointsFromWGrounds*)), this, SLOT(frstPlotData(pointsFromWGrounds*)));
        connect(transceiver_ground_, SIGNAL(dataGroundUpdate(pointsFromWGrounds*)), this, SLOT(plotData(pointsFromWGrounds*)));

        timeMes_ = dataPckt->time;
        dataSize_ = dataPckt->data.size();
        y.clear();

        for(int i=numMeasure_; i< dataSize_; i++){
            y.append(dataPckt->data[i]);

        }

        if(y.size() >= width_) {
            ui->customPlot->graph(0)->setData(x, y);
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
void graphGround::setOffset(uint8_t numPckt,uint8_t numMeasure, const int blk_cnt)
{
    if(blk_cnt == 1){
        numPckt_ = numPckt;
        numMeasure_ = numMeasure;
    }
}

void graphGround::initGraphGround()
{
    ui->customPlot->addGraph(); // blue line
    ui->customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));

    ui->customPlot->xAxis->setTicks(0); //off ticks
    ui->customPlot->yAxis->setTicks(0);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->customPlot->xAxis->setTicker(timeTicker);

    ui->customPlot->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(8);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->legend->setSelectedFont(legendFont);
    ui->customPlot->legend->setSelectableParts(QCPLegend::spNone);

    ui->customPlot->axisRect()->setMinimumMargins(QMargins(0,0,0,0));   // на весь экран расстянуть

    ui->customPlot->graph(0)->setName(QString("Наземный %1").arg(deviceCount+1));
    y.resize(width_);
    y.clear();
    /* every 1/4 sec ploting */
    //connect(transceiver_ground_, SIGNAL(dataGroundUpdate(pointsFromWGrounds*)), this, SLOT(plotData(pointsFromWGrounds*)));
    connect(transceiver_ground_, SIGNAL(dataGroundUpdate(pointsFromWGrounds*)), this, SLOT(frstPlotData(pointsFromWGrounds*)));
}
