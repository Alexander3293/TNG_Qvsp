#include "graphdownhole.h"
#include "ui_graphdownhole.h"

graphDownHole::graphDownHole(Transceiver_class *transceiver, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graphDownHole)
{
    ui->setupUi(this);
    transceiver_ = transceiver;
    num_module = 0;
    trace_XYZ = init_graph_DownHoles::graph_axis_X;

    connect(this, SIGNAL(updateSceneWidth()), this, SLOT(plotData()));
    for(int i =0; i< 500; i++)
        xTimeCpy_.append(i);
    KU_ = 0;

}

graphDownHole::~graphDownHole()
{
    delete ui;
}

void graphDownHole::plotData()
{
    ui->customPlot->graph(0)->setData(xTimeCpy_, data_cpyXYZ);
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
    switch (trace_XYZ) {

    case init_graph_DownHoles::graph_axis_X:

        trace_23_16 = num_module * 16 + 0;
        trace_15_8  = num_module * 16 + 2;
        trace_7_0   = num_module * 16 + 3;
        trace_KU    = num_module * 16 + 14;
        trace_status= num_module * 16 + 1;

        break;

    case init_graph_DownHoles::graph_axis_Y:

        trace_23_16 = num_module * 16 + 4;
        trace_15_8  = num_module * 16 + 5;
        trace_7_0   = num_module * 16 + 6;
        trace_KU    = num_module * 16 + 14;
        trace_status= num_module * 16 + 1;

        break;

    case init_graph_DownHoles::graph_axis_Z:

        trace_23_16 = num_module * 16 + 7;
        trace_15_8  = num_module * 16 + 8;
        trace_7_0   = num_module * 16 + 9;
        trace_KU    = num_module * 16 + 14;
        trace_status= num_module * 16 + 1;

        break;
    }
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
    }x;

    if(crc_.checkCRC(pdata, num_module)){
        x.x23_16 = *(pdata + trace_23_16);
        x.x15_8  = *(pdata + trace_15_8 );
        x.x7_0   = *(pdata + trace_7_0);

        if ((x.x31_0 & 0x00800000) > 0) x.x31_24 = 0xFF;
        else x.x31_24 = 0;

        set_state_KU(*(pdata + trace_KU));               //Установить KU в label
        set_state_rele((*(pdata + trace_status)) & 0x40);
    }
    else{
        x.x31_0 = maxValMissPacket;
    }
    mesX = x.x31_0;
    data_vector_XYZ.append(mesX);

//    nowTime_ = QTime(0,0,0).secsTo(QTime::currentTime());
//    xTime_.append(nowTime_);

    if ((data_vector_XYZ.count() >= width_)){
        data_cpyXYZ = data_vector_XYZ;
        data_vector_XYZ.clear();

        emit updateSceneWidth();
    }

}

void graphDownHole::rangeChanged(double axisY)
{
    ui->customPlot->yAxis->setRange(-axisY, axisY);
    ui->customPlot->replot();
}

void graphDownHole::clearData()
{
    data_vector_XYZ.clear();
}

void graphDownHole::setWidth(int width)
{
    width_ = width;
    data_cpyXYZ.resize(width_);
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

    connect(transceiver_, SIGNAL(data_update(int,pointFromDownHoles)), this, SLOT(slot_data_update(int,pointFromDownHoles)));
}

void graphDownHole::initGraphXYZ(init_graph_DownHoles axis)
{
    trace_XYZ = axis;
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
    double tmp = (50*0.01) * 8388607;
    ui->customPlot->xAxis->setRange(0, width_);
    ui->customPlot->yAxis->setRange(-tmp, tmp);

    switch (trace_XYZ) {
    case init_graph_DownHoles::graph_axis_X:
        ui->customPlot->graph(0)->setName(QString("Модуль %1 X").arg(num_module+1));
        ui->label_num_device->setText(QString("Модуль %1 X").arg(num_module+1));
        break;
    case init_graph_DownHoles::graph_axis_Y:
        ui->customPlot->graph(0)->setName(QString("Модуль %1 Y").arg(num_module+1));
        ui->label_num_device->setText(QString("Модуль %1 Y").arg(num_module+1));
        break;
    case init_graph_DownHoles::graph_axis_Z:
        ui->customPlot->graph(0)->setName(QString("Модуль %1 Z").arg(num_module+1));
        ui->label_num_device->setText(QString("Модуль %1 Z").arg(num_module+1));
        break;
    }
    ui->customPlot->replot();
    connect(transceiver_, SIGNAL(data_update(int,pointFromDownHoles)), this, SLOT(slot_data_update(int,pointFromDownHoles)));
}

void graphDownHole::stopPlot()
{
    this->clearData();
    disconnect(transceiver_, SIGNAL(data_update(int,pointFromDownHoles)), this, SLOT(slot_data_update(int,pointFromDownHoles)));
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

void graphDownHole::set_state_KU(quint8 ku)
{
    ui->label_state_ku->setText(QString::number(ku));
}

void graphDownHole::set_state_rele(quint8 rele)
{
    if(rele){
        ui->label_state_rele->setText("ON");
    }
    else{
        ui->label_state_rele->setText("OFF");
    }
}

