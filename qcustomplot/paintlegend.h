#ifndef PAINTLEGEND_H
#define PAINTLEGEND_H

#include <QWidget>
#include <QPainter>

typedef  enum{
    syncMod     = 0,
    VSPmod      = 1,
    groundmod   = 2
}modOVSP;

namespace Ui {
class PaintLegend;
}

class PaintLegend : public QWidget
{
    Q_OBJECT

public:
    explicit PaintLegend(QWidget *parent = nullptr);
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
};

#endif // PAINTLEGEND_H
