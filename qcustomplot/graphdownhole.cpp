#include "graphdownhole.h"
#include "ui_graphdownhole.h"

graphDownHole::graphDownHole(Transceiver_class *transceiver, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graphDownHole)
{
    ui->setupUi(this);
    transceiver_ = transceiver;
    num_module = 0;

    connect(this, SIGNAL(updateSceneWidth()), this, SLOT(plotData()));
    for(int i =0; i< 500; i++)
        xTimeCpy_.append(i);
}

graphDownHole::~graphDownHole()
{
    delete ui;
}

void graphDownHole::plotData()
{
    ui->customPlot->graph(0)->setData(xTimeCpy_, data_cpyX);
    ui->customPlot->graph(1)->setData(xTimeCpy_, data_cpyY);
    ui->customPlot->graph(2)->setData(xTimeCpy_, data_cpyZ);
    // set axes ranges, so we see all data:
    ui->customPlot->rescaleAxes();
    //ui->customPlot->yAxis->setRange(0, 1);
    ui->customPlot->replot();

    xTime_.clear();

}

void graphDownHole::setModNum(quint8 devCon) {
    num_module = devCon;
}

quint8 graphDownHole::getModNum() {
    return num_module;
}

void graphDownHole::setTraceDnHole()
{
        //            trace_23_16 = tool_No * 10 + 0;
        trace_23_16_X = num_module * 16 + 0;
        trace_15_8_X  = num_module * 16 + 2;
        trace_7_0_X   = num_module * 16 + 3;

        trace_23_16_Y = num_module * 16 + 4;
        trace_15_8_Y  = num_module * 16 + 5;
        trace_7_0_Y   = num_module * 16 + 6;

        trace_23_16_Z = num_module * 16 + 7;
        trace_15_8_Z  = num_module * 16 + 8;
        trace_7_0_Z   = num_module * 16 + 9;

}

void graphDownHole::slot_data_update (const int blk_cnt, const pointFromDownHoles &point)// прием и обработка данных
{
    Q_UNUSED(blk_cnt);

    quint8* pdata = (quint8*)&(point.data[0]);

    if(!flagFirst) {
        uint16_t numPcktDownHoles = ntohs(point.n_pocket);  //начало пакета с 1 у подземных модулей
        if((numPcktDownHoles%256) > 10)
        {
            flagFirst = true;
        }
        else return;
    }

    union {
        struct {
            quint8 x7_0;
            quint8 x15_8;
            quint8 x23_16;
            quint8 x31_24;
        };
        quint32 x31_0;
    } x, y, z;

    if(crc_.checkCRC(pdata, num_module)){
        x.x23_16 = *(pdata + trace_23_16_X);
        x.x15_8  = *(pdata + trace_15_8_X );
        x.x7_0   = *(pdata + trace_7_0_X);

        y.x23_16 = *(pdata + trace_23_16_Y);
        y.x15_8  = *(pdata + trace_15_8_Y );
        y.x7_0   = *(pdata + trace_7_0_Y);

        z.x23_16 = *(pdata + trace_23_16_Z);
        z.x15_8  = *(pdata + trace_15_8_Z );
        z.x7_0   = *(pdata + trace_7_0_Z);
    //    trace15_8ForKU_ = *(pdata + (tool_No * 16 + 14));;
    //    trace23_16ForKU_ = *(pdata + (tool_No * 16 + 14) );
        if ((x.x31_0 & 0x00800000) > 0) x.x31_24 = 0xFF;
        else x.x31_24 = 0;

        if ((y.x31_0 & 0x00800000) > 0) y.x31_24 = 0xFF;
        else y.x31_24 = 0;

        if ((z.x31_0 & 0x00800000) > 0) z.x31_24 = 0xFF;
        else z.x31_24 = 0;
    }
    else{
        x.x31_0 = maxValMissPacket;
        y.x31_0 = maxValMissPacket;
        z.x31_0 = maxValMissPacket;
    }

    mesX = x.x31_0;
    data_vectorX.append(mesX);

    mesY = y.x31_0;
    data_vectorY.append(mesY);

    mesZ = z.x31_0;
    data_vectorZ.append(mesZ);

//    nowTime_ = QTime(0,0,0).secsTo(QTime::currentTime());
//    xTime_.append(nowTime_);

    if ((data_vectorX.count() >= width_) ||
           (data_vectorY.count() >= width_) ||
            (data_vectorZ.count() >= width_) )  //Данные для построения, если есть:
    {
        data_cpyX = data_vectorX;
        data_cpyY = data_vectorY;
        data_cpyZ = data_vectorZ;

        //xTimeCpy_ = xTime_;
//        memcpy(&data_cpyX, &data_vectorX, width_);    //Вдруг придут новые данные, а старые не ушли
//        memcpy(&data_cpyY, &data_vectorY, width_);    //Вдруг придут новые данные, а старые не ушли
//        memcpy(&data_cpyZ, &data_vectorZ, width_);    //Вдруг придут новые данные, а старые не ушли
//        xTime_.clear();
        data_vectorX.clear();
        data_vectorY.clear();
        data_vectorZ.clear();

        emit updateSceneWidth();
    }

}

void graphDownHole::clearData()
{
    data_vectorX.clear();
    data_vectorY.clear();
    data_vectorZ.clear();
}

void graphDownHole::setWidth(int width)
{
    width_ = width;
    data_cpyX.resize(width_);
    data_cpyY.resize(width_);
    data_cpyZ.resize(width_);
}

void graphDownHole::initGraphXYZ()
{
    ui->customPlot->addGraph(); // blue line
    ui->customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->customPlot->addGraph(); // red line
    ui->customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));
    ui->customPlot->addGraph(); // green line
    ui->customPlot->graph(2)->setPen(QPen(QColor(110, 255, 40)));

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

    ui->customPlot->graph(0)->setName(QString("Модуль %1 X").arg(num_module+1));
    ui->customPlot->graph(1)->setName(QString("Модуль %1 Y").arg(num_module+1));
    ui->customPlot->graph(2)->setName(QString("Модуль %1 Z").arg(num_module+1));

    connect(transceiver_, SIGNAL(data_update(int,pointFromDownHoles)), this, SLOT(slot_data_update(int, pointFromDownHoles)));
}

void graphDownHole::stopPlot()
{
    disconnect(transceiver_, SIGNAL(data_update(int,pointFromDownHoles)), this, SLOT(slot_data_update(int, pointFromDownHoles)));
}

void graphDownHole::on_relayModeButton_clicked(bool checked)
{

    if(checked)
    {

        transceiver_->on_tool_rele_on(num_module);   //num_module
        ui->relayModeButton->setText("Выкл Реле");
        ui->relayModeButton->setCheckable(false); //invert checked
    }
    else
    {

        transceiver_->on_tool_rele_off(num_module);  //num module
        ui->relayModeButton->setText("Вкл Реле");
        ui->relayModeButton->setCheckable(true); //invert checked
    }
}
