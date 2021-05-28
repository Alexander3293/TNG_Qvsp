#include "graphsync.h"
#include "ui_graphsync.h"

graphSync::graphSync(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graphSync)
{
    ui->setupUi(this);
}

graphSync::~graphSync()
{
    delete ui;
}

void graphSync::plot()
{

    for (int i=0; i<101; ++i)
    {
      x.append(i/50.0 - 1); // x goes from -1 to 1
      y.append(x[i]*x[i]); // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph()->setData(x, y);
    // give the axes some labels:
//    ui->customPlot->xAxis->setLabel("x");
//    ui->customPlot->yAxis->setLabel("y");

    ui->customPlot->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->legend->setSelectedFont(legendFont);
    ui->customPlot->legend->setSelectableParts(QCPLegend::spNone);

    ui->customPlot->graph()->setName(QString("Sync"));
    // now we move the legend from the inset layout of the axis rect into the main grid layout.
    // We create a sub layout so we can generate a small gap between the plot layout cell border
    // and the legend border:
    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    QCPAxisRect *leftAxisRect = new QCPAxisRect(ui->customPlot);
    ui->customPlot->plotLayout()->addElement(subLayout);

//    //subLayout->setMargins(QMargins(5, 0, 5, 5));
    subLayout->addElement(0,0,leftAxisRect);
    subLayout->addElement(0,1,ui->customPlot->legend);

    ui->customPlot->legend->setMaximumSize(1,1); // (width, heigth)
    // change the fill order of the legend, so it's filled left to right in columns:
    ui->customPlot->legend->setFillOrder(QCPLegend::foColumnsFirst);

    ui->customPlot->rescaleAxes();
    //ui->customPlot->yAxis->setRange(0, 1);
    ui->customPlot->replot();
}

quint8 graphSync::getDevNum() {
    return deviceCount;
}

void graphSync::test()
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

    ui->customPlot->graph()->setName(QString("Синхр"));

    for (int i=0; i<101; ++i)
    {
      x.append(i/50.0 - 1); // x goes from -1 to 1
      y.append(x[i]*x[i]); // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->customPlot->graph()->setData(x, y);
    ui->customPlot->rescaleAxes();
    //ui->customPlot->yAxis->setRange(0, 1);
    ui->customPlot->replot();
}
