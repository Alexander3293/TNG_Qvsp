#ifndef PAINTLEGEND_H
#define PAINTLEGEND_H

#include <QWidget>
#include <QPainter>

typedef  enum{
    syncMod        = 0,
    DownHoleMod    = 1,
    GroundHoleMod  = 2
}modOVSP;

typedef  enum{
    X   = 0,
    Y   = 1,
    Z   = 2
}axisPaintLegend;

namespace Ui {
class PaintLegend;
}

class PaintLegend : public QWidget
{
    Q_OBJECT

public:
    //explicit PaintLegend(QWidget *parent = nullptr);
    explicit PaintLegend(QWidget *parent, modOVSP mode);
    explicit PaintLegend(QWidget *parent, modOVSP mode, int numMode, axisPaintLegend axis);
    ~PaintLegend();
    void setText(QString);
    void setMod(modOVSP mode);
protected:
    /* Определяем виртуальный метод родительского класса
     * для отрисовки содержимого виджета
     * */
    void paintEvent(QPaintEvent *event);
private:
    Ui::PaintLegend *ui;
    QString name_legend_;
    modOVSP mode_;
    int numModule;
    axisPaintLegend axis_;
};

#endif // PAINTLEGEND_H
