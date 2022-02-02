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
    connect(transceiver_ground_, SIGNAL(devGroundState(quint8, bool)), this, SLOT(setGroundDevState(quint8, bool)));
    connect(transceiver_ground_, SIGNAL(timeVibroSig(uint)), this, SLOT(getTimerVibro(uint)));
    error_crc_ = 0;
    error_pckt_ = 0;
    realTime = true;
    //connect(transceiver_ground_, SIGNAL(devGroundState(quint8, bool)), this, SLOT(setGroundDevState(quint8, bool)));
    tmp_dataPckt = new pointsFromWGrounds();
    tmp_dataPckt->numPckt = -1;

}

graphGround::~graphGround()
{
    delete tmp_dataPckt;
    delete ui;
}

void graphGround::plotData(pointsFromWGrounds *dataPckt)
{
    if(deviceCount  == dataPckt->numModule)  {

        //timeMes_ = dataPckt->time;
        dataSize_ = dataPckt->data.size();
        switch(dataPckt->error){
        case -1:    //error CRC
            error_crc_++;
            ui->label_ErrorCRC->setText(QString::number(error_crc_));
            break;
        case -2:    //error Cnumber packet
            error_pckt_++;
            break;
        }

        tmp_dataPckt->numPckt = dataPckt->numPckt;
        tmp_dataPckt->data = dataPckt->data;

        if(realTime){
            for(int i=0; i< dataSize_; i++){
                y.append(dataPckt->data[i]);
                if(y.size() >= width_) {
                    ui->customPlot->graph(0)->setData(x, y);
                    ui->customPlot->replot();
                    y.clear();
                }
            }
        }
        else{
            if(cnt_meas_tim_vibro < width_ && cnt_meas_tim_vibro!= 0){
                for(int i=0; i< dataSize_; i++){
                    //y.append(dataPckt->data[i]);
                    ui->customPlot->graph(0)->addData(cnt_meas_tim_vibro++, dataPckt->data[i]);

                    if(!(cnt_meas_tim_vibro % 1000)){
                        ui->customPlot->replot();
                        //y.clear();
                    }
                }
            }
        }
    }
}

void graphGround::rangeChanged(double axisY)
{
    ui->customPlot->yAxis->setRange(-axisY, axisY);
    ui->customPlot->replot();
}

void graphGround::getTimerVibro(uint time)
{
    y.clear();
    y.reserve(time);
    this->setWidth(time);
    ui->customPlot->xAxis->setRange(0, width_);
    realTime = false;
    numPckt_ = -1;
    numMeasure_ = -1;
    cnt_meas_tim_vibro = 0;
    ui->customPlot->graph(0)->data().data()->clear();
    ui->customPlot->replot();
    disconnect(transceiver_ground_, SIGNAL(dataGroundUpdate(pointsFromWGrounds*)), this, SLOT(plotData(pointsFromWGrounds*)));
    connect(transceiver_ground_, SIGNAL(dataGroundUpdate(pointsFromWGrounds*)), this, SLOT(frstPlotData(pointsFromWGrounds*)));

}

/* ЧТобы 1 раз установить offset и все, дальше стандартно */
void graphGround::frstPlotData(pointsFromWGrounds *dataPckt)
{
    if(dataPckt->numModule == deviceCount){
        if(numPckt_ == dataPckt->numPckt)  {  //если тот девайс и тот пакет
            disconnect(transceiver_ground_, SIGNAL(dataGroundUpdate(pointsFromWGrounds*)), this, SLOT(frstPlotData(pointsFromWGrounds*)));
            connect(transceiver_ground_, SIGNAL(dataGroundUpdate(pointsFromWGrounds*)), this, SLOT(plotData(pointsFromWGrounds*)));

            dataSize_ = dataPckt->data.size();
            y.clear();

            ui->label_state->setStyleSheet("QLabel { background-color : green; color : black; }");  //device Enable
            if(realTime){

                for(int i=numMeasure_; i< dataSize_; i++){
                    y.append(dataPckt->data[i]);
                }

                if(y.size() >= width_) {
                    ui->customPlot->graph(0)->setData(x, y);
                    //ui->customPlot->rescaleAxes();
                    ui->customPlot->replot();
                    y.clear();
                }
            }

            else{
                for(int i=numMeasure_; i< dataSize_; i++)
                    ui->customPlot->graph(0)->addData(cnt_meas_tim_vibro++, dataPckt->data[i]);
            }
        }
        else if(tmp_dataPckt->numPckt == numPckt_){

            disconnect(transceiver_ground_, SIGNAL(dataGroundUpdate(pointsFromWGrounds*)), this, SLOT(frstPlotData(pointsFromWGrounds*)));
            connect(transceiver_ground_, SIGNAL(dataGroundUpdate(pointsFromWGrounds*)), this, SLOT(plotData(pointsFromWGrounds*)));

            dataSize_ = tmp_dataPckt->data.size();
            y.clear();

            ui->label_state->setStyleSheet("QLabel { background-color : green; color : black; }");  //device Enable
            if(realTime){

                for(int i=numMeasure_; i< dataSize_; i++){
                    y.append(tmp_dataPckt->data[i]);
                }

                if(y.size() >= width_) {
                    ui->customPlot->graph(0)->setData(x, y);
                    //ui->customPlot->rescaleAxes();
                    ui->customPlot->replot();
                    y.clear();
                }
            }
            else{
                cnt_meas_tim_vibro = 0;
                for(int i=numMeasure_; i< dataSize_; i++)
                    ui->customPlot->graph(0)->addData(cnt_meas_tim_vibro++, tmp_dataPckt->data[i]);
                qDebug() << "num Meas" << numMeasure_ << "data Size" << dataSize_ << "dev id" <<deviceCount;
            }

            if(tmp_dataPckt->numPckt < dataPckt->numPckt){
                dataSize_ = dataPckt->data.size();

                if(realTime){
                    for(int i=0; i< dataSize_; i++){
                        y.append(dataPckt->data[i]);
                    }

                    if(y.size() >= width_) {
                        ui->customPlot->graph(0)->setData(x, y);
                        //ui->customPlot->rescaleAxes();
                        ui->customPlot->replot();
                        y.clear();
                    }
                }
                else{
                    for(int i=0; i< dataSize_; i++)
                        ui->customPlot->graph(0)->addData(cnt_meas_tim_vibro++, dataPckt->data[i]);

                }
            }
        }

        else{
            tmp_dataPckt->numPckt = dataPckt->numPckt;
            tmp_dataPckt->data = dataPckt->data;
        }

    }
}

void graphGround::setGroundDevState(quint8 numDev, bool state)
{
    if(numDev == deviceCount){
        if(state){
            ui->label_state->setStyleSheet("QLabel { background-color : green; color : black; }");
        }
        else{
            ui->label_state->setStyleSheet("QLabel { background-color : red; color : black; }");
        }
    }
}

void graphGround::setDevNum(quint8 devCon) {

    deviceCount = devCon;
    tmp_dataPckt->numModule = deviceCount;
    ui->label_num_ground->setText(QString("Наземный %1").arg(deviceCount+1));  //нумерация с 1
}

quint8 graphGround::getDevNum() {
    return deviceCount;
}

void graphGround::setWidth(int val)
{
    width_ = val;
   // y.resize(width_);
    x.clear();
    for(int i=0; i < width_; i++) x.append(i);
}

/* задать смещение */
void graphGround::setOffset(uint8_t numPckt,uint8_t numMeasure, const int blk_cnt)
{
//    if(blk_cnt == 1){
        numPckt_ = numPckt;
        numMeasure_ = numMeasure;
//    }
}

void graphGround::initGraphGround()
{
    ui->customPlot->addGraph(); // blue line
    ui->customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));

    ui->customPlot->xAxis->setTicks(0); //off ticks
    ui->customPlot->yAxis->setTicks(0);

//    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
//    timeTicker->setTimeFormat("%h:%m:%s");
//    ui->customPlot->xAxis->setTicker(timeTicker);

//    ui->customPlot->legend->setVisible(true);
//    QFont legendFont = font();
//    legendFont.setPointSize(8);
//    ui->customPlot->legend->setFont(legendFont);
//    ui->customPlot->legend->setSelectedFont(legendFont);
//    ui->customPlot->legend->setSelectableParts(QCPLegend::spNone);

    ui->customPlot->axisRect()->setMinimumMargins(QMargins(0,0,0,0));   // на весь экран расстянуть

    ui->customPlot->graph(0)->setName(QString("Наземный %1").arg(deviceCount+1));
    y.resize(width_);
    y.clear();
    double tmp = (50*0.01) * 8388607;
    ui->customPlot->xAxis->setRange(0, width_);
    ui->customPlot->yAxis->setRange(-tmp, tmp);
    /* every 1/4 sec ploting */
    //connect(transceiver_ground_, SIGNAL(dataGroundUpdate(pointsFromWGrounds*)), this, SLOT(plotData(pointsFromWGrounds*)));
    connect(transceiver_ground_, SIGNAL(dataGroundUpdate(pointsFromWGrounds*)), this, SLOT(frstPlotData(pointsFromWGrounds*)));
}

