#include "paintlegend.h"
#include "ui_paintlegend.h"


PaintLegend::PaintLegend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaintLegend)
{
    ui->setupUi(this);
    mode_ = syncMod;
}

PaintLegend::PaintLegend(QWidget *parent, modOVSP mode):
    QWidget(parent),
    ui(new Ui::PaintLegend)
{
    ui->setupUi(this);
    mode_ = mode;
}

PaintLegend::PaintLegend(QWidget *parent, modOVSP mode, int numMode, axisPaintLegend axis):
    QWidget(parent),
    ui(new Ui::PaintLegend)
{
    ui->setupUi(this);
    mode_ = mode;
    numModule = numMode;
    axis_ = axis;
}

PaintLegend::~PaintLegend()
{
    delete ui;
}

void PaintLegend::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this); // Создаём объект отрисовщика

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawRect(rect());

    painter.setPen(Qt::black);
    painter.drawLine(0,0, width(),0);
    painter.drawLine(width()-1,0, width()-1,height()-1);
    painter.drawLine(width()-1,height()-1, 0,height()-1);
    painter.drawLine(0,height()-1, 0,0);

    if(mode_ == syncMod){
        // Устанавливаем кисть абриса
        painter.setPen(QPen((QColor(40, 110, 255)), 1, Qt::SolidLine, Qt::FlatCap));
        painter.drawLine(width()/12, height()/6, 2*width()/6, height()/6);
        painter.setPen(Qt::black);
        painter.drawText(width()/2 + 4,height()/6 + 4, "ADC");

        painter.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::FlatCap));
        painter.drawLine(width()/12, 3*height()/6, 2*width()/6, 3*height()/6);
        painter.setPen(Qt::black);
        painter.drawText(width()/2 + 4,3*height()/6 + 4, "TBF");

        painter.setPen(QPen(Qt::green, 1, Qt::SolidLine, Qt::FlatCap));
        painter.drawLine(width()/12, 5*height()/6, 2*width()/6, 5*height()/6);
        painter.setPen(Qt::black);
        painter.drawText(width()/2 + 4,5*height()/6 + 4, "CTB");
        //painter.drawText(rect(),  Qt::AlignCenter,  "Sync");
    }
    else if(mode_ == DownHoleMod){
        // Устанавливаем кисть абриса
        painter.setPen(QPen((QColor(40, 110, 255)), 1, Qt::SolidLine, Qt::FlatCap));
        painter.drawLine(width()/4, height()/2, 3*width()/4, height()/2);

        painter.setPen(Qt::black);
        switch (axis_) {
        case axisPaintLegend::X:
            painter.drawText(rect(), Qt::AlignTop, QString("Модуль %1X").arg(numModule));
            break;

        case axisPaintLegend::Y:
            painter.drawText(rect(), Qt::AlignTop, QString("Модуль %1Y").arg(numModule));
            break;

        case axisPaintLegend::Z:
            painter.drawText(rect(), Qt::AlignTop, QString("Модуль %1Z").arg(numModule));
            break;

        default:
            painter.drawText(rect(), Qt::AlignTop, QString("Модуль 0X"));
            break;
        }

    }
    else if(mode_ == GroundHoleMod){
        // Устанавливаем кисть абриса
        painter.setPen(QPen((QColor(40, 110, 255)), 1, Qt::SolidLine, Qt::FlatCap));
        painter.drawLine(0, height()/2, width()/2, height()/2);

        painter.setPen(Qt::black);
        painter.drawText(width()/2 + 4,height()/2 + 4, QString("Наземный %1").arg(numModule));
        //painter.drawText(rect(),  Qt::AlignCenter,  "Sync");

    }
}

void PaintLegend::setText(QString nameLegend)
{
    name_legend_ = nameLegend;
}

void PaintLegend::setMod(modOVSP mode)
{
    mode_ = mode;
    repaint();
}
