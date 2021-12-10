
#include "tracealldata_wsdc.h"
#include "math.h"
#include "stdlib.h"

#include <QMutex>

TraceAllData_wsdc::TraceAllData_wsdc(const QRect &rect, QGraphicsScene *scene, int modulesNum):
    QGraphicsObject(),
    width_(rect.width()),
    height_(rect.height()),
    clBack(QColor(Qt::transparent)),
    line_width(1),
    clLine(QColor(Qt::black)),
    clText(QColor(Qt::black)),
    y_scale(6553),      // y_scale = max_ampl / zero;
    zero(5),            // zero = height / 2;
    max_ampl(0x7FFFFF),
    font(QFont()),
    Caption(QString::fromUtf8("")),
    modulesNum_(modulesNum)
{
    isPainter_ = false;
    //transceiver_wsdc wsdcTransceiver(QHostAddress("192.168.169.24"), 42424);
    //    x_scale.clear();
    topLeftPoint_ = 0;
    topRightPoint_ = 0;
    widthZoomFactor_ = 1.0;
    for(int i = 0; i < modulesNum_; i++)
    {
        QList<qint32*>* data_list(new QList<qint32*>);
        allData_vec.push_back(data_list);
        //        x_scale.push_back(1);
        timeValue_.push_back(QVector<int>());
        inverseModules_.push_back(false);
        //        timeValue_[i]
    }
    partOfHeight = height_ / (modulesNum * 3);
    timerUpdateScene_ = new QTimer(this);
    connect(timerUpdateScene_, SIGNAL(timeout()), this, SLOT(updateScene()) );
    setPos(rect.topLeft());
    scene->addItem(this);
    numUpHoleChannel_ = 0;
    startTime_ = 0;
    universalTempData_ = new universalTemporaryData{};
    //    for(auto i = 0; i < 8; i++)
    //    {
    //        timeFirstPckt_[i] = -1;
    //    }
}

TraceAllData_wsdc::~TraceAllData_wsdc()
{
    delete timerUpdateScene_;
    emit stopThread();
}

void TraceAllData_wsdc::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(isPainter_ == false){
        if(isPaintForReport_ == true){
            isDrawingForReport_ = false;
            paintAll(painter);
        }
        return;
    }
    //    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing);
    int             x1;
    int             y1;
    int             x2;
    int             y2;
    QRect           r;
    QFont           font;
    QFontMetrics    fm(font);
    QBrush          brush_back;
    QPen            pen_line;
    QPen            pen_text;

    painter->save();
    // Метка

    //    Width = widget->width();
    //    Height = widget->height() / modulesNum_;

    zero = partOfHeight / 2;

    y_scale = max_ampl / zero;
    if (y_scale == 0) y_scale = 1;

    brush_back.setColor(clBack);
    brush_back.setStyle(Qt::SolidPattern);

    pen_line.setColor(clLine);
    pen_line.setStyle(Qt::SolidLine);
    pen_line.setWidth(2);

    pen_text.setColor(clText);
    pen_text.setStyle(Qt::SolidLine);
    pen_text.setWidth(1);

    //    painter->setRenderHint(QPainter::Antialiasing, false);

    r.setCoords(0, 0, width_, height_);
    painter->fillRect(r, brush_back);

    //Построение трассы

    //    painter->drawLine(0, zero, Width, zero);

    if (allData_vec.empty())
    {
        painter->restore();
        return;
    }
    for(int num = 0; num < allData_vec.size(); num++)
    {
        if(!allData_vec[num]->isEmpty())
        {
            pen_line.setColor(clLine);
            painter->setPen(pen_line);
            x1 = topLeftPoint_; //  x1 = topLeftPoint_;
            y1 = zero - qRound((double)( (*allData_vec[num]->first() ) ) / y_scale);
            if (y1 > partOfHeight) y1 = partOfHeight;
            if (y1 < 0) y1 = 0;
            int numPoint = topLeftPoint_; // int numPoint = topLeftPoint_;
            if(numPoint <= 0)
                numPoint = 1;
            int maxRightSize = topRightPoint_;
            if(maxRightSize > allData_vec[num]->size())
                maxRightSize = allData_vec[num]->size();

            for(;numPoint < maxRightSize; numPoint++)
            {
                //                if(i >= timeValue_[num].size())
                //                    break;
                x2 = qRound((timeValue_[num][numPoint])  * widthZoomFactor_);//x_scale; // x2 = x1 + 1;
                y2 = zero - qRound((double)((*allData_vec[num]->at(numPoint) ) ) / y_scale);

                //        if (y2 > Height) y2 = Height;
                //        if (y2 < 0) y2 = 0;

                y2 = y2 > partOfHeight ? partOfHeight : y2 < 0 ? 0 : y2;
                int offsetValues = (num * 3 * partOfHeight) + (1 * partOfHeight);
                painter->drawLine(x1, y1 + offsetValues,
                                  x2, y2 + offsetValues);
                //            if( i % 100 == 0)
                //                painter->drawText(QRect(x1, y1 - 100, x2, y2 - 100),
                //                                  QString::fromUtf8("%1.%2").arg(time_sec_[i]).arg(time_msec_[i]));
                x1 = x2;
                y1 = y2;

            }
            //раскомменитровать для рисования линии 0 ->
            if(isPaintZeroLines_ == true){
                QColor zeroLineColor = QColor(50,50,50);
                zeroLineColor.setAlphaF(0.3);
                pen_line.setColor(zeroLineColor);
                painter->setPen(pen_line);

                //                int yVal = qRound((double)zero / y_scale);
                int yVal = zero;
                yVal = yVal > partOfHeight ? partOfHeight : yVal < 0 ? 0 : yVal;
                yVal += (num * 3 * partOfHeight) + (1 * partOfHeight);
                painter->drawLine(qRound(topLeftPoint_ * widthZoomFactor_), yVal, qRound(maxRightSize * widthZoomFactor_), yVal);
                painter->setPen(pen_text);
                painter->setFont(font);
            }
            // <- раскомменитровать для рисования линии 0
        }

        r.setLeft(10);// Метка
        r.setTop(10);
        r.setHeight(1.5 * fm.height());
        r.setWidth(1.5 * fm.width(Caption));
        painter->drawText(QRect(r.left() + leftIndentationText_, r.top(), r.width(), r.height()), Caption);
    }
    painter->restore();
}

void TraceAllData_wsdc::setRect(QRect &rect)
{
    //    qDebug() << rect;
    width_ = rect.width();
    height_ = rect.height();
    partOfHeight = height_ / (modulesNum_ * 3);
    setPos(rect.topLeft());
}

void TraceAllData_wsdc::setXScale(int new_scale)
{
    //    for(int i = 0; i < modulesNum_; i++)
    //        if(!allData_vec[i]->isEmpty()) {
    //            x_scale[i] = (double)new_scale/allData_vec[i]->size();
    //            //qDebug() <<"data is" << new_scale << allData_vec[i]->size() << i;
    //        }
    newScale_ = new_scale;
}
void TraceAllData_wsdc::retraceData(universalTemporaryData *data)
{
    //    Q_UNUSED(blk_cnt);
    for(int numChannel = 0; numChannel < data->allData_list.size(); numChannel++)
    {
        for(auto it = data->allData_list[numChannel]->cbegin(); it < data->allData_list[numChannel]->cend(); it++ )
        {
            qint32* value = new(qint32);
            memcpy(value, *it, sizeof(qint32));
            this->allData_vec[numChannel]->push_back(value);
        }
    }
    //    this->allData_vec = data->allData_list;
    this->timeValue_ = data->timeValue;
    for(int numModule = 0; numModule < allData_vec.size(); numModule++)
        if(this->timeValue_.size() > 0)
            if(this->timeValue_[numModule].size() > 0)
                if(width_ < this->timeValue_[numModule].last())
                    width_ = this->timeValue_[numModule].last();
    emit update();
    for(int i = 0; i < data->allData_list.size(); i++) {
        for(int j = 0; j < data->allData_list[i]->size(); j++)
            delete data->allData_list[i]->at(j);
        data->allData_list[i]->clear();
        delete data->allData_list[i];
    }
    data->timeValue.clear();
    delete data;
}

void TraceAllData_wsdc::retraceData(int num, qint32 *data, int size)
{
    if(num >= this->allData_vec.size() || num < 0)
        return;
    if(allData_vec.isEmpty() != true) {
        for (auto it = allData_vec[num]->begin(); it < allData_vec[num]->end(); it++)
        {
            delete *it;
        }

        allData_vec[num]->clear();
    }
    for(int i = 0; i < size; i++)
    {
        qint32* value = new(qint32);
        *value = data[i];
        this->allData_vec[num]->push_back(value);
    }
    emit update();
    //очистка data
    delete [] data;
}

void TraceAllData_wsdc::updateModulesNum(int newMudulesum)
{
    modulesNum_ = newMudulesum;

    if (modulesNum_ > allData_vec.size())
        for(int i = allData_vec.size(); i < modulesNum_; i++)
        {
            QList<qint32*>* data_list(new QList<qint32*>);
            allData_vec.push_back(data_list);
            //        x_scale.push_back(1);
            timeValue_.push_back(QVector<int>());
            //        timeValue_[i]
        }
    else if (modulesNum_ < allData_vec.size() && modulesNum_ != 0){
        for(int i = allData_vec.size(); i > modulesNum_; i--)
        {
            delete allData_vec.last();
            allData_vec.pop_back();
            timeValue_.pop_back();
        }
        //        for(int i = timeValue_.size(); i > modulesNum_; i--)
        //        {
        //            timeValue_.pop_back();
        //        }
    }
}
void TraceAllData_wsdc::setStopTime(int stopTime)
{
    stopTime_ = stopTime;
}
void TraceAllData_wsdc::setStartTime(int time)
{
    startTime_ = time;
}

bool TraceAllData_wsdc::getIsPainter() const
{
    return isPainter_;
}

void TraceAllData_wsdc::setIsPainter(bool isPainter)
{
    isPainter_ = isPainter;
}
universalTemporaryData *TraceAllData_wsdc::getUniversalTempData() const
{
    return universalTempData_;
}

void TraceAllData_wsdc::copyAllDataToUniversal()
{
    QMutex mutex;
    while(mutex.tryLock() == false);
    delete universalTempData_;
    universalTempData_ = new universalTemporaryData{};
    //qDebug() <<"is 2d and 3d number "<< timeValue_[1].first() << timeValue_[2].first();
    QVector<QVector<int>> tmpTimeValue_;
    for(int numChannel = 0; numChannel < this->allData_vec.size(); numChannel++)
    {
        QList<qint32*>* data_list(new QList<qint32*>);
        universalTempData_->allData_list.push_back(data_list);

        int beginCopy = 0;
        //qDebug() << numChannel << allData_vec[numChannel]->size();
        tmpTimeValue_.push_back(QVector<int>());
        for(auto it = this->allData_vec[numChannel]->cbegin(); it < this->allData_vec[numChannel]->cend(); it++ )
        {
            //            qDebug() << numChannel << timeValue_[numChannel][beginCopy];
            timeValue_[numChannel][beginCopy] = timeValue_[numChannel][beginCopy] + startTimeUpHole_ - startTime_ - globalWSDCOffset_;
            if(timeValue_[numChannel][beginCopy] >= 0)
            {
                tmpTimeValue_[numChannel].push_back(timeValue_[numChannel][beginCopy]);
                qint32* value = new(qint32);
                memcpy(value, (*it), sizeof(qint32) );
                universalTempData_->allData_list[numChannel]->push_back(value);
                //            }
            }
            beginCopy++;
        }
    }
    //    QVector<QVector<int>> tmpTimeValue_;
    //    for(int numChannel = 0; numChannel < this->allData_vec.size(); numChannel++)
    //    {
    //        QVector<int> timeChannel;
    //        tmpTimeValue_.push_back(timeChannel);
    //        for(auto it = 0; it < this->allData_vec[numChannel]->size(); it++ )
    //        {
    //            if(timeValue_[numChannel][it] >= 0)
    //            {
    //                int valueTime = (timeValue_[numChannel][it] * it) + it;
    //                tmpTimeValue_[numChannel].push_back(valueTime);
    //            }
    //        }
    //    }

    universalTempData_->timeValue = tmpTimeValue_;
//    qDebug() << "UP HOLE LAST TIME VAL" << universalTempData_->timeValue[0].last() << universalTempData_->timeValue[2].last();
    mutex.unlock();
}

void TraceAllData_wsdc::setInverseModules(const QVector<bool> &inverseModules)
{
    inverseModules_ = inverseModules;
}

void TraceAllData_wsdc::setScopePaint(int topLeftPoint, int topRightPoint)
{
    // береться диапазон чуть больше чем viewPort на 100
    topLeftPoint_ = std::round(topLeftPoint/ widthZoomFactor_) - 100 ;
    if(topLeftPoint_ <= 0)
        topLeftPoint_ = 1;
    topRightPoint_ = std::round(topRightPoint / widthZoomFactor_) + 100;
}

void TraceAllData_wsdc::setWidthZoomFactor(float widthZoomFactor)
{
    widthZoomFactor_ = widthZoomFactor;
}

//-----------------------------------------------------------------------------
void TraceAllData_wsdc::on_changeTimeScale(int newScale)
{
    x_scale[0] = newScale;
    //emit update();
}
//-----------------------------------------------------------------------------
void TraceAllData_wsdc::on_changeMaxAmpl(int newMaxAmpl)
{
    max_ampl = newMaxAmpl;
    // emit update();
}
//-----------------------------------------------------------------------------
void TraceAllData_wsdc::on_data_update (const pointsFromWells &points)
{
    //    qDebug() << "before";
    numUpHoleChannel_ = points.numModule;
    if(numUpHoleChannel_ < modulesNum_)
    {
        //        smsPckType_ = points.data[2];
        //        smsPckNum_ = points.data[3];
        //if(chForDataList > 7)
        //    chForDataList = 0;
        //qDebug() << chForDataList;

        //        int lastValueTimePack = 0;
        //        if(!timeValue_[numUpHoleChannel_].isEmpty())
        //            lastValueTimePack = timeValue_[numUpHoleChannel_].last();
        int beginCicle = 0;
        int endCicle = points.data.size();

        //        int normTime = (points.time  - startTime_);

        //        if(timeFirstPckt_[numUpHoleChannel_] == -1)
        //        {
        //            QTime time;
        //            time = QTime::currentTime();
        //            qDebug() << "module is " << numUpHoleChannel_;
        //            qDebug() << time;
        //            timeFirstPckt_[numUpHoleChannel_] = 0;
        //        }

        //            qDebug() << startTime_ << points.time;

        //        int normTime = (points.time  - startTime_);

        //        int averg = std::round((float)(normTime - lastValueTimePack)
        //                               / (points.data.size() / 2));
        //        if((points.time  - startTime_) - lastValueTimePack <= points.data.size())
        //            endCicle = ((points.time  - startTime_) - lastValueTimePack);
        int currTimePoint = 0;

        for (int j = beginCicle; j < endCicle; j += 2)
        {
            qint32* val = new(qint32) ;
            *val = (static_cast<int16_t>(points.data[j] << 8)) + static_cast<int16_t>(points.data[j + 1]);
            if(inverseModules_[numUpHoleChannel_])
                *val = -(*val);


            //                qDebug() << "come_1";
            //            int shiftForDistribution = (j/2);

            //            if(normTime - (shiftForDistribution * averg) > 0 && lastValueTimePack != (lastValueTimePack + (shiftForDistribution * averg)))
            //            {

            timeValue_[numUpHoleChannel_].push_back((points.time - endCicle/100 + 1) * 50 + currTimePoint);
            if(counterDebug < 10){
                if(timeValue_.isEmpty() != true && timeValue_.size() > numUpHoleChannel_)
                    if(timeValue_[numUpHoleChannel_].size() > 0)
                        qDebug() << QString::number(timeValue_[numUpHoleChannel_].last()) << "Time WSDC";
                counterDebug++;
            }
            currTimePoint++;
            allData_vec[numUpHoleChannel_]->push_back(val);
            //            }
            //                currTime++;
            //            else emit finishRead();
        }

        //        qDebug() << "END Cicle";
        //qDebug() << chForDataList << allData_vec[chForDataList]->size();



        if (!allData_vec[numUpHoleChannel_]->isEmpty())
        {
            if (allData_vec[0]->count() >= (width_ - 200))
            {
                if(allData_vec[0]->count() <= (width_ - 100))
                    emit updateSceneWidth();
            }
        }
    }
    //chForDataList++;
    //    qDebug() << "after";
    //emit update();
}
void TraceAllData_wsdc::setTrace()
{
    for(int k = 0; k < allData_vec.size(); k++)
    {
        allData_vec[k]->clear();
    }
}
//-----------------------------------------------------------------------------
void TraceAllData_wsdc::setLeftIdnentationText(int leftIndentationText)
{
    leftIndentationText_ = leftIndentationText;
}

void TraceAllData_wsdc::setInversVec(const QVector<bool> &inverseModules)
{
    inverseModules_ = inverseModules;
}

void TraceAllData_wsdc::setUpdateInterval(int updateInterval)
{

    if(updateInterval >= 1 && updateInterval <= 2000)
        timerUpdateScene_->setInterval(updateInterval);
    else
    {
        timerUpdateScene_->setInterval(1);
    }
}

int TraceAllData_wsdc::getTimeOfPoint(int numPoint, int numModule)
{
    if(numPoint >= 0 && timeValue_.size() > 0)
    {
        if(!timeValue_[numModule].isEmpty() && numPoint < timeValue_[numModule].size()){
            //width zoom factor ???
            float a = (float)numPoint/timeValue_[0].last() ;
            return qRound(timeValue_[numModule].size() * a);
        }
    }
    else
        return -1;

    return -1;
}

int TraceAllData_wsdc::linSearch(QVector<int> arr, int requiredKey)
{
    if(arr.size() > 0) {
        int minDist = qAbs(arr[0] - requiredKey);
        int minDistId = 0;
        for (int i = 1; i < arr.size(); i++)
        {
            if (arr[i] == requiredKey)
                return i;
            else {
                int tmpDist = qAbs(arr[i] - requiredKey);
                if (tmpDist < minDist){
                    minDist = tmpDist;
                    minDistId = i;
                }
            }
        }
        return minDistId;
    }
    return -1;
}

void TraceAllData_wsdc::paintAll(QPainter *painter)
{
    if(isPainter_ == false) {
        if(isPaintForReport_ == true) {
            if(isDrawingForReport_ == true)
                return;
            else
                isDrawingForReport_ = false;
        }
        else
            return;
    }
    else
        return;

    painter->setRenderHint(QPainter::Antialiasing); //???
    int             x1;
    int             y1;
    int             x2;
    int             y2;
    QRect           r;
    QFont           font;
    QFontMetrics    fm(font);
    QBrush          brush_back;
    QPen            pen_line;
    QPen            pen_text;

    painter->save();

    zero = partOfHeight / 2;

    y_scale = max_ampl / zero;
    if (y_scale == 0) y_scale = 1;

    brush_back.setColor(clBack);
    brush_back.setStyle(Qt::SolidPattern);

    pen_line.setColor(clLine);
    pen_line.setStyle(Qt::SolidLine);
    pen_line.setWidth(line_width);

    pen_text.setColor(clText);
    pen_text.setStyle(Qt::SolidLine);
    pen_text.setWidth(1);

    r.setCoords(0, 0, width_, height_);
    painter->fillRect(r, brush_back);

    if(allData_vec.isEmpty() != true)
        for(int num = 0; num < allData_vec.size(); num++)
        {
            if(allData_vec[num]->isEmpty() != true && timeValue_[num].isEmpty() != true) {
                pen_line.setColor(clLine);
                painter->setPen(pen_line);
                y1 = zero - ( *(allData_vec[num]->first() ) ) / y_scale;

                if (y1 > partOfHeight) y1 = partOfHeight;

                x1 = timeValue_[num].first();

                y1 = zero - ( *(allData_vec[num]->first() ) ) / y_scale;
                if (y1 > partOfHeight) y1 = partOfHeight;
                if (y1 < 0) y1 = 0;
                int numPoint = 0;
                for( ; numPoint < allData_vec[num]->size(); numPoint++)
                {
                    if(numPoint >= timeValue_[num].size())
                        break;

                    x2 = qRound(timeValue_[num][numPoint] * widthZoomFactor_);
                    //                x2 = std::round((numPoint) * widthZoomFactor_);//x_scale;

                    y2 = zero - ( *(allData_vec[num]->at(numPoint) ) ) / y_scale;

                    y2 = y2 > partOfHeight ? partOfHeight : y2 < 0 ? 0 : y2;
                    int offsetValues = (num * 3 * partOfHeight) + (1 * partOfHeight);
                    painter->drawLine(x1, y1 + offsetValues,
                                      x2, y2 + offsetValues);

                    x1 = x2;
                    y1 = y2;
                }
                //раскомменитровать для рисования линии 0 ->
                if(isPaintZeroLines_ == true){
                    QColor zeroLineColor = QColor(50,50,50);
                    zeroLineColor.setAlphaF(0.3);
                    pen_line.setColor(zeroLineColor);
                    painter->setPen(pen_line);

                    int yVal = zero / y_scale;
                    yVal = yVal > partOfHeight ? partOfHeight : yVal < 0 ? 0 : yVal;
                    yVal += (num * 3 * partOfHeight) + (1 * partOfHeight);
                    painter->drawLine(qRound(topLeftPoint_ * widthZoomFactor_), yVal, qRound(timeValue_[num].last() * widthZoomFactor_), yVal);
                    painter->setPen(pen_text);
                    painter->setFont(font);
                }
                // <- раскомменитровать для рисования линии 0


                r.setLeft(10);// Метка
                r.setTop(10);
                r.setHeight(1.5 * fm.height());
                r.setWidth(1.5 * fm.width(Caption));
                painter->drawText(QRect(r.left() + leftIndentationText_, r.top(), r.width(), r.height()), Caption);
            }
        }
    painter->restore();
}

int TraceAllData_wsdc::getGlobalWSDCOffset() const
{
    return globalWSDCOffset_;
}

void TraceAllData_wsdc::setGlobalWSDCOffset(int globalWSDCOffset)
{
    globalWSDCOffset_ = globalWSDCOffset;
}

bool TraceAllData_wsdc::getIsPaintForReport() const
{
    return isPaintForReport_;
}

void TraceAllData_wsdc::setIsPaintForReport(bool isPaintForReport)
{
    isPaintForReport_ = isPaintForReport;
}

bool TraceAllData_wsdc::getIsPaintZeroLines() const
{
    return isPaintZeroLines_;
}

void TraceAllData_wsdc::setIsPaintZeroLines(bool isPaintZeroLines)
{
    isPaintZeroLines_ = isPaintZeroLines;
}

int TraceAllData_wsdc::getStartTimeUpHole() const
{
    return startTimeUpHole_;
}

void TraceAllData_wsdc::setStartTimeUpHole(int startTimeUpHole)
{
    startTimeUpHole_ = startTimeUpHole;
}

int TraceAllData_wsdc::getValueofPoint(int numPoint, int numModule)
{
    if(timeValue_.size() > numModule){
        //        int num = linSearch(timeValue_[numModule], qRound((double)numPoint / widthZoomFactor_));
        int num = linSearch(timeValue_[numModule], numPoint);

        int value;
        if(numPoint < allData_vec[numModule]->size() && num >= 0)
        {
            //        qDebug() << zero << "-" << ( *(allData_vec[numModule]->at(num) ) ) / y_scale;
            //            value = ( *(allData_vec[numModule]->at(num) ) ) / y_scale;
            value = (*(allData_vec[numModule]->at(num))); /// y_scale;

            //        y2 = y2 > partOfHeigt ? partOfHeigt : y2 < 0 ? 0 : y2;
            return value;
        }
        else
            return -1;
    }
    else
        return -1;
}

void TraceAllData_wsdc::clearDataList()
{
    for(int numModClear = 0; numModClear < allData_vec.size(); numModClear++)
    {
        if(allData_vec.isEmpty() != true) {
            for (auto it = allData_vec[numModClear]->begin(); it < allData_vec[numModClear]->end(); it++)
            {
                delete *it;
            }
            allData_vec[numModClear]->clear();
            if(timeValue_.size() < numModClear && !timeValue_.isEmpty())
                timeValue_[numModClear].clear();
        }
    }
    for(int numModClear = 0; numModClear < timeValue_.size(); numModClear++)
        timeValue_[numModClear].clear();
}

void TraceAllData_wsdc::updateScene()
{
    emit update();
}

void TraceAllData_wsdc::startUpdateScene()
{
    timerUpdateScene_->start();
}

void TraceAllData_wsdc::stopUpdateScene()
{
    timerUpdateScene_->stop();
}
