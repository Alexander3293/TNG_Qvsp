#ifndef TRACEALLDATA_WSDC_H
#define TRACEALLDATA_WSDC_H

/*
* Класс для отрисовки и хранения данных на время отображения с наземных модулей
*/

#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QRectF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QColor>
#include <QFont>
#include <QString>
#include <QList>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <winsock.h>

#include "network/declarateTransceiveringData.h"
#include "network/transceiver_wsdc.h"

class TraceAllData_wsdc: public QGraphicsObject
{
    Q_OBJECT
public:
    explicit TraceAllData_wsdc(const QRect &rect, QGraphicsScene *scene, int modulesNum);
    ~TraceAllData_wsdc();
    virtual QRectF  boundingRect() const {return QRectF(QRect(0, 0, width_, height_));}
    virtual void    paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void    setWidth(int new_width) {width_ = new_width;}
    int     width() const {return width_;}

    void    setHeight(int new_height) {height_ = new_height;}
    int     height() const {return height_;}
    void setRect(QRect &rect);
    void    setColorBack(QColor color) {clBack = color;}
    QColor  colorBack() const {return clBack;}

    void    setLineWidth(int new_width) {line_width = new_width;}
    int     lineWidth() const {return line_width;}

    void    setColorLine(QColor color) {clLine = color;}
    QColor  colorLine() const {return clLine;}

    void    setColorText(QColor newColor) {clText = newColor;}
    QColor  colorText() const {return clText;}

    void setXScale(int new_scale);
    QVector<double> XScale() const {return x_scale;}

    void setMaxAmpl(int new_max_ampl) {max_ampl = new_max_ampl;}
    int  maxAmpl() const {return max_ampl;}

    void setCaption(QString text) {Caption = text;}

    void setTrace();
    void setLeftIdnentationText(int leftIndentationText);
    void setInversVec(const QVector<bool> &inverseModules);
    void setUpdateInterval(int updateInterval);
    int  getTimeOfPoint(int numPoint, int numModule);
    int  getValueofPoint(int numPoint, int numModule);
    void clearDataList();
    void retraceData (const int blk_cnt, const int module, const TDataPocket &data);
    void setStartTime(int time);
    void setStopTime(int time);
    bool getIsPainter() const;
    void setIsPainter(bool isPainter);
    void retraceData (universalTemporaryData* data);
    void retraceData (int num, qint32 *data, int size);

    void updateModulesNum(int newMudulesum);
    universalTemporaryData *getUniversalTempData() const;
    void copyAllDataToUniversal();

    void setInverseModules(const QVector<bool> &inverseModules);
    void setScopePaint(int topLeftPoint, int topRightPoint);
    void setWidthZoomFactor(float widthZoomFactor);

    int  getStartTimeUpHole() const;
    void setStartTimeUpHole(int startTimeUpHole);

    bool getIsPaintZeroLines() const;
    void setIsPaintZeroLines(bool isPaintZeroLines);

    bool getIsPaintForReport() const;
    void setIsPaintForReport(bool isPaintForReport);

    int getGlobalWSDCOffset() const;
    void setGlobalWSDCOffset(int globalWSDCOffset);

private:
    int     width_;       //ширина
    int     height_;      //высота
    float widthZoomFactor_;
    QColor  clBack;
    int     typeGraphic_;
    int     line_width;  //толщина основной линии
    QColor  clLine;      //цвет линий сетки
    QColor  clText;      //цвет линий текста
    QTimer *timerUpdateScene_;
    QVector<double> x_scale;
    int     y_scale;
    int     zero;
    int     max_ampl;
    QFont   font;
    QString Caption;
    int topLeftPoint_;
    int topRightPoint_;
    int startTime_;
    int stopTime_;
//    int timeFirstPckt_[8];
    uint8_t smsPckType_;
    uint8_t smsPckNum_;
    uint32_t key_;
    uint8_t pointsInPckt_;
    uint32_t numOfCycle_; // Номер текущего цикла
    uint8_t bytes_;
    uint16_t shift_;
    uint8_t index_;
    QVector<QVector<int>> timeValue_;
    QVector<bool> inverseModules_;
    int numUpHoleChannel_;
    QVector<QList<qint32*>*> allData_vec;
    int modulesNum_;
    int leftIndentationText_;
    int partOfHeight;
    int newScale_;
    bool isPainter_;
    universalTemporaryData* universalTempData_;
    int linSearch(QVector<int> arr, int requiredKey);
    int startTimeUpHole_ = 0;
    bool isPaintZeroLines_ = false;
    bool isPaintForReport_ = false;
    void paintAll(QPainter *painter);
    bool isDrawingForReport_ = false;
    int counterDebug = 0;\
    int globalWSDCOffset_ = 10;

signals:
    void update(void);
    void updateSceneWidth();
    void setSceneWidth();
    void stopThread();

private slots:
    void updateScene();

public slots:
    void on_data_update (const pointsFromWells &points);
    void on_changeTimeScale(int newScale);
    void on_changeMaxAmpl(int newMaxAmpl);
    void startUpdateScene();
    void stopUpdateScene();
};

#endif // TRACEALLDATA_WSDC_H
