#include "paintlegend.h"
#include "ui_paintlegend.h"


PaintLegend::PaintLegend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaintLegend)
{
    ui->setupUi(this);
    mode_ = syncMod;
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
        painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::FlatCap));
        painter.drawLine(width()/12, height()/2, 2*width()/6, height()/2);

        painter.setPen(Qt::black);
        painter.drawText(width()/2 + 4,height()/2 + 4, "Синхр");
        //painter.drawText(rect(),  Qt::AlignCenter,  "Sync");
    }
    else if(mode_ == VSPmod){
        // Устанавливаем кисть абриса
        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
        painter.drawLine(width()/4, height()/2, 3*width()/4, height()/2);

        painter.setPen(Qt::blue);
        painter.drawText(rect(), Qt::AlignTop, "The Text");
    }
    else if(mode_ == groundmod){
        // Устанавливаем кисть абриса
        painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::FlatCap));
        painter.drawLine(0, height()/2, width()/2, height()/2);

        painter.setPen(Qt::black);
        painter.drawText(width()/2 + 4,height()/2 + 4, "Наземный");
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
