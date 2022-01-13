#include "test.h"
#include "ui_test.h"

test::test(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::test)
{
    ui->setupUi(this);
    deviceCount = 1;
    width_ = 500;

    for(int i=0; i < 700; i++)
    {
        X.append(i);
    }
}

test::~test()
{
    delete ui;
}

//void test::plotData(pointsFromWGrounds *dataPckt)
//{
//    if(dataPckt->numModule == deviceCount)  {

//    timeMes_ = dataPckt->time;
//    dataSize_ = dataPckt->data.size();
//    y.clear();
//    //y.resize(width_);
//    for(int i=0; i< dataSize_; i++){
//        y.append(dataPckt->data[i]);

//    }
//    ui->customPlot->graph(1)->setData(X, y);
//    // set axes ranges, so we see all data:
//    ui->customPlot->rescaleAxes();
//    //ui->customPlot->yAxis->setRange(0, 1);

//    ui->customPlot->replot();

//        //x.clear();



//    }
//}

//void test::conectSignals()
//{
//    connect(transceiver_ground_, SIGNAL(dataGroundUpdate(pointsFromWGrounds*)), this, SLOT(plotData(pointsFromWGrounds*)));
//    connect(trasceiver_down_, SIGNAL(data_update(int,pointFromDownHoles)), this, SLOT(slot_data_update(int, pointFromDownHoles)));
//}

//void test::slot_data_update (const int blk_cnt, const pointFromDownHoles &point)// прием и обработка данных
//{
//    Q_UNUSED(blk_cnt);

//    quint8* pdata = (quint8*)&(point.data[0]);

//    union {
//        struct {
//            quint8 x7_0;
//            quint8 x15_8;
//            quint8 x23_16;
//            quint8 x31_24;
//        };
//        quint32 x31_0;
//    } x, y, z;
//    x.x23_16 = *(pdata + trace_23_16_X);
//    x.x15_8  = *(pdata + trace_15_8_X );
//    x.x7_0   = *(pdata + trace_7_0_X);

//    y.x23_16 = *(pdata + trace_23_16_Y);
//    y.x15_8  = *(pdata + trace_15_8_Y );
//    y.x7_0   = *(pdata + trace_7_0_Y);

//    z.x23_16 = *(pdata + trace_23_16_Z);
//    z.x15_8  = *(pdata + trace_15_8_Z );
//    z.x7_0   = *(pdata + trace_7_0_Z);
////    trace15_8ForKU_ = *(pdata + (tool_No * 16 + 14));;
////    trace23_16ForKU_ = *(pdata + (tool_No * 16 + 14) );
//    if ((x.x31_0 & 0x00800000) > 0) x.x31_24 = 0xFF;
//    else x.x31_24 = 0;

//    if ((y.x31_0 & 0x00800000) > 0) y.x31_24 = 0xFF;
//    else y.x31_24 = 0;

//    if ((z.x31_0 & 0x00800000) > 0) z.x31_24 = 0xFF;
//    else z.x31_24 = 0;

////    mesX = x.x31_0;
////    data_vectorX.append(mesX);

//    mesY = y.x31_0;
//    data_vectorY.append(mesY);


////    mesZ = z.x31_0;
////    data_vectorZ.append(mesZ);



//    if ((data_vectorY.count() >= width_) )  //Данные для построения, если есть:
//    {
////        data_cpyX = data_vectorX;
//        data_cpyY = data_vectorY;
////        data_cpyZ = data_vectorZ;

//        data_vectorX.clear();
//        data_vectorY.clear();
//        data_vectorZ.clear();

//        ui->customPlot->graph(0)->setData(X, data_cpyY);
//        ui->customPlot->rescaleAxes();
//        //ui->customPlot->yAxis->setRange(0, 1);

//        ui->customPlot->replot();
//    }

//    delete [] pdata;
//}

void test::setTraceDnHole()
{
    int num_module =0;
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

void test::initGraphXYZ()
{
    ui->customPlot->addGraph(); // blue line
    ui->customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->customPlot->addGraph(); // red line
    ui->customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));
   // ui->customPlot->addGraph(); // green line
   // ui->customPlot->graph(2)->setPen(QPen(QColor(110, 255, 40)));

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

    ui->customPlot->graph(0)->setName(QString("Скважный %1 X"));
    ui->customPlot->graph(1)->setName(QString("Наземный "));
   //ui->customPlot->graph(2)->setName(QString("Модуль %1 Z").arg(num_module));
}
