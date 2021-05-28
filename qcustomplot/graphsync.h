#ifndef GRAPHSYNC_H
#define GRAPHSYNC_H

#include <QWidget>

namespace Ui {
class graphSync;
}

class graphSync : public QWidget
{
    Q_OBJECT

public:
    explicit graphSync(QWidget *parent = nullptr);
    ~graphSync();
    void plot();
    quint8 getDevNum();
    void test();

private:
    Ui::graphSync *ui;
    QVector <double>    x, y;
    uint                deviceCount;
};

#endif // GRAPHSYNC_H
