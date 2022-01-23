#include "graphsync.h"
#include "ui_graphsync.h"

graphSync::graphSync(SyncModuleTranciever* transceiver, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graphSync)
{
    ui->setupUi(this);
    transceiver_sync_ = transceiver;
    width_ = 500;
    numPckt_ = -1;
    numMeasure_ = -1;
    maxAmpl_ = 0x0FFF;
    isVibro_ = true;

    legendSync = new PaintLegend(this, modOVSP::syncMod);
    ui->grdLayoutPaintLegend->addWidget(legendSync);

    error_crc_ = 0;
    error_pckt_ = 0;
    //ui->gridLayout2->addWidget(legendSync);
}

graphSync::~graphSync()
{
    delete ui;
}

void graphSync::setWidth(int val)
{
    width_ = val;
   // y.resize(width_);
    ui->customPlot->xAxis->setRange(-1, width_ + 1);
    for(int i=0; i < width_; i++) x.append(i);
}

void graphSync::clearData()
{
    dataADC.clear();
    dataTB.clear();
    dataCTB.clear();
}

void graphSync::plot()
{
    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    QCPAxisRect *leftAxisRect = new QCPAxisRect(ui->customPlot);
    ui->customPlot->plotLayout()->addElement(subLayout);

//    //subLayout->setMargins(QMargins(5, 0, 5, 5));
    subLayout->addElement(0,0,leftAxisRect);
    subLayout->addElement(0,1,ui->customPlot->legend);

//    ui->customPlot->legend->setMaximumSize(1,1); // (width, heigth)
//    // change the fill order of the legend, so it's filled left to right in columns:
//    ui->customPlot->legend->setFillOrder(QCPLegend::foColumnsFirst);
}

void graphSync::initGraphSync()
{
    ui->customPlot->addGraph(); // blue line
    ui->customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));

    ui->customPlot->xAxis->setTicks(0); //off ticks
    ui->customPlot->yAxis->setTicks(0);

    ui->customPlot->legend->setVisible(false);
    QFont legendFont = font();
    legendFont.setPointSize(8);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->legend->setSelectedFont(legendFont);
    ui->customPlot->legend->setSelectableParts(QCPLegend::spNone);

    ui->customPlot->axisRect()->setMinimumMargins(QMargins(0,0,0,0));   // на весь экран расстянуть

    ui->customPlot->graph(0)->setName(QString("ADC"));
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::red));
    ui->customPlot->graph(1)->setName(QString("TBF"));

    ui->customPlot->addGraph();
    ui->customPlot->graph(2)->setPen(QPen(Qt::green));
    ui->customPlot->graph(2)->setName(QString("CTB"));
    ui->customPlot->yAxis->setRange(-100, 5100);

    connect(transceiver_sync_, SIGNAL(dataSyncUpdate(SyncModuleTranciever::pointsFromSync*)), this, SLOT(frstPlotData(SyncModuleTranciever::pointsFromSync*)));
}


/* ЧТобы 1 раз установить offset и все, дальше стандартно */
void graphSync::frstPlotData(SyncModuleTranciever::pointsFromSync *dataPckt)
{

    if(numPckt_ == dataPckt->numPckt)  {  //если тот девайс и тот пакет

        disconnect(transceiver_sync_, SIGNAL(dataSyncUpdate(SyncModuleTranciever::pointsFromSync*)), this, SLOT(frstPlotData(SyncModuleTranciever::pointsFromSync*)));
        connect(transceiver_sync_, SIGNAL(dataSyncUpdate(SyncModuleTranciever::pointsFromSync*)), this, SLOT(plotData(SyncModuleTranciever::pointsFromSync*)));

        dataSize_ = dataPckt->dataADC.size();
        dataADC.clear();
        dataTB.clear();
        dataCTB.clear();

        for(int i=numMeasure_; i< dataSize_; i++){

            dataADC.append(dataPckt->dataADC[i]);

            if(isVibro_){
                if(dataPckt->timeBreakVibro[i] == true)
                    dataTB.append(maxAmpl_);
                else
                    dataTB.append(0);
            }
            else{
                if(dataPckt->timeBreakDetonation[i] == true)
                    dataTB.append(maxAmpl_);
                else
                    dataTB.append(0);
            }

            if(dataPckt->timeBreakDetonationConfirm[i] == true)
                dataCTB.append(maxAmpl_);
            else
                dataCTB.append(0);


        }

        if(dataADC.size() >= width_) {
            ui->customPlot->graph(0)->setData(x, dataADC);
            ui->customPlot->graph(1)->setData(x, dataTB);
            ui->customPlot->graph(2)->setData(x, dataCTB);
            ui->customPlot->rescaleAxes();
            ui->customPlot->yAxis->setRange(-100, 5100);
            ui->customPlot->replot();
            dataADC.clear();
            dataTB.clear();
            dataCTB.clear();

        }
    }
}

void graphSync::plotData(SyncModuleTranciever::pointsFromSync *dataPckt)
{
//    qDebug() << "numPckt" <<numPckt_ << "need" << dataPckt->numPckt;

    //timeMes_ = dataPckt->time;
    dataSize_ = dataPckt->dataADC.size();
    switch(dataPckt->error){
    case -1:
        ++error_crc_;
        ui->label_ErrorCRC->setText(QString::number(error_crc_));
        break;
    case -2:
        break;
    }

    //y.resize(width_);
    for(int i=0; i< dataSize_; i++){
        dataADC.append(dataPckt->dataADC[i]);
        if(isVibro_){
            if(dataPckt->timeBreakVibro[i] == true)
                dataTB.append(maxAmpl_);
            else
                dataTB.append(0);
        }
        else{
            if(dataPckt->timeBreakDetonation[i] == true)
                dataTB.append(maxAmpl_);
            else
                dataTB.append(0);
        }

        if(dataPckt->timeBreakDetonationConfirm[i] == true)
            dataCTB.append(maxAmpl_);
        else
            dataCTB.append(0);

        if(dataADC.size() >= width_) {
//            qDebug() << "HERE";
            ui->customPlot->graph(0)->setData(x, dataADC);
            ui->customPlot->graph(1)->setData(x, dataTB);
            ui->customPlot->graph(2)->setData(x, dataCTB);
            ui->customPlot->rescaleAxes();
            //ui->customPlot->yAxis->setRange(-100, 1000);
            ui->customPlot->replot();
            dataADC.clear();
            dataTB.clear();
            dataCTB.clear();
        }
    }

}

/* задать смещение */
void graphSync::setOffset(uint8_t numPckt,uint8_t numMeasure, const int blk_cnt)
{
    if(blk_cnt == 1){
        numPckt_ = numPckt;
        numMeasure_ = numMeasure;
    }
}

void graphSync::changeTimeBreakSlot(const QString cmd, const QString chnl)
{
    Q_UNUSED(cmd);
    if(chnl == SyncModuleTranciever::SYNC_MODULE_CHANNEL_DETONATION){
        isVibro_ = false;
        ui->customPlot->graph(1)->setName(QString("TBF"));
        ui->customPlot->rescaleAxes();
        ui->customPlot->replot();
    }
    else if(chnl == SyncModuleTranciever::SYNC_MODULE_CHANNEL_VIBRO){
        isVibro_ = true;
        ui->customPlot->graph(1)->setName(QString("TBV"));
        ui->customPlot->rescaleAxes();
        ui->customPlot->replot();
    }
}
