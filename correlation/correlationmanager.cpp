#include "correlationmanager.h"
#include <QDebug>

CorrelationManager::CorrelationManager(int typeInt64or32, QObject *parent) : QObject(parent)
{
    for(int i = 0; i <= UP_HOLE; i++){
        minIdTypes_.push_back(-1);
    }
    counter_ = 0;
    isDnHoleDataExists_ = false;
    isSyncDataExists_ = false;
    typeInt64or32_ = typeInt64or32;
}

CorrelationManager::~CorrelationManager()
{
    minIdTypes_.clear();
    if(channelsInt64_.isEmpty() == false){
        for(int i = 0; i < channelsInt64_.size(); i++) {
            if(channelsInt64_[i]->dataCrossCorrelation != nullptr)
                delete [] channelsInt64_[i]->dataCrossCorrelation;
            if(channelsInt64_[i]->dataOrig != nullptr)
                delete [] channelsInt64_[i]->dataOrig;
        }
        channelsInt64_.clear();
    }
}

void CorrelationManager::addChannels(typeModules type, universalTemporaryData* data)
{
    QMutex mutex;
    while(mutex.tryLock() == false);
    if(type != SYNC) {
        minIdTypes_[type] = counter_;
        if(data->allData_list.size() > 0)
            for(int i = 0; i < data->allData_list.size(); i++) {
                if(data->allData_list[i]->size() > 0) {
                    dataForCorrelationInt64* tmp = new dataForCorrelationInt64();
                    tmp->type = type;
                    tmp->id = counter_++;
                    tmp->isSweep = false;
                    tmp->isCompleted = false;
                    tmp->sizeArrOrig = data->allData_list[i]->size();
                    if(tmp->sizeArrOrig > 0)
                    {
                        tmp->dataOrig = new qint64[tmp->sizeArrOrig];
                        qint64 tmpMax = -1;
                        for(int j = 0; j < tmp->sizeArrOrig; j++) {
                            qint64 tmpVal = static_cast<qint64>(*data->allData_list[i]->at(j));
                            if(j > 0) {
                                if(qAbs(tmpVal) > tmpMax)
                                    tmpMax = qAbs(tmpVal);
                            }
                            else {
                                tmpMax = qAbs(tmpVal);
                            }
                            tmp->dataOrig[j] = tmpVal;
                        }
                        tmp->coef = tmpMax;
                        channelsInt64_.push_back(tmp);
                    }
                }
                else {
                    dataForCorrelationInt64* tmp = new dataForCorrelationInt64();
                    tmp->type = type;
                    tmp->id = counter_++;
                    tmp->isSweep = false;
                    tmp->isCompleted = false;
                    tmp->sizeArrOrig = 0;
                    channelsInt64_.push_back(tmp);
                }
            }
    }
    else {
        if(data->allData_list.size() > 0) {
            minIdTypes_[type] = counter_;
            dataForCorrelationInt64* tmp = new dataForCorrelationInt64();
            tmp->type = type;
            tmp->id = counter_++;
            tmp->sizeArrOrig = data->allData_list[0]->size();
            tmp->isSweep = true;
            tmp->isCompleted = true;
            tmp->dataOrig = new qint64[tmp->sizeArrOrig];
            qint64 tmpMax = -1;
            for(int j = 0; j < tmp->sizeArrOrig; j++) {
                qint64 tmpVal = static_cast<qint64>(*data->allData_list[0]->at(j));
                if(j > 0) {
                    if(qAbs(tmpVal) > tmpMax)
                        tmpMax = qAbs(tmpVal);
                }
                else {
                    tmpMax = qAbs(tmpVal);
                }
                tmp->dataOrig[j] = tmpVal;
            }
            tmp->dataCrossCorrelation = new qint64[tmp->sizeArrOrig];
            tmp->sizeCrossCorrelation = tmp->sizeArrOrig;
            memcpy(tmp->dataCrossCorrelation, tmp->dataOrig, sizeof(qint64)*static_cast<unsigned int>(tmp->sizeArrOrig));
            channelsInt64_.push_back(tmp);

            if(data->allData_list.size() > 1){
                for(int i = 1; i < data->allData_list.size(); i++) {
                    if(data->allData_list[i]->size() > 0) {
                        dataForCorrelationInt64* tmp = new dataForCorrelationInt64();
                        tmp->type = type;
                        tmp->id = counter_++;
                        tmp->isSweep = false;
                        tmp->isCompleted = true;
                        tmp->sizeArrOrig = data->allData_list[i]->size();
                        tmp->sizeCrossCorrelation = tmp->sizeArrOrig;
                        tmp->dataCrossCorrelation = new qint64[tmp->sizeCrossCorrelation];
                        if(tmp->sizeArrOrig > 0)
                        {
                            tmp->dataOrig = new qint64[tmp->sizeArrOrig];
                            qint64 tmpMax = -1;
                            for(int j = 0; j < tmp->sizeArrOrig; j++){
                                qint64 tmpVal = static_cast<qint64>(*data->allData_list[i]->at(j));
                                if(j > 0) {
                                    if(qAbs(tmpVal) > tmpMax)
                                        tmpMax = qAbs(tmpVal);
                                }
                                else {
                                    tmpMax = tmpVal;
                                }
                                tmp->dataOrig[j] = tmpVal;
                            }
                            memcpy(tmp->dataCrossCorrelation, tmp->dataOrig, sizeof(qint64)*static_cast<unsigned int>(tmp->sizeArrOrig));

                            channelsInt64_.push_back(tmp);
                        }
                    }
                }
            }
        }
    }
    //копирование массивов времени
    switch (type) {
    case SYNC: {
        if(isSyncDataExists_ == false){
            if(timeDataSync_.size() > 0){
                for(int i = 0; i < timeDataSync_.size(); i++)
                    if(timeDataSync_[i].size() > 0)
                        timeDataSync_[i].clear();
                timeDataSync_.clear();
            }
            for(int i = 0; i < data->timeValue.size(); i++){
                QVector<int> tmpVec;
                for(int j = 0; j < data->timeValue[i].size(); j++)
                    tmpVec.push_back(data->timeValue[i][j]);
                timeDataSync_.push_back(tmpVec);
            }
            isSyncDataExists_ = true;
        }
        break;
    }
    case DN_HOLE_X: {
        if(isDnHoleDataExists_ == false){
            if(timeDataDnHole_.size() > 0){
                for(int i = 0; i < timeDataDnHole_.size(); i++)
                    if(timeDataDnHole_[i].size() > 0)
                        timeDataDnHole_[i].clear();
                timeDataDnHole_.clear();
            }
            for(int i = 0; i < data->timeValue.size(); i++){
                QVector<int> tmpVec;
                for(int j = 0; j < data->timeValue[i].size(); j++)
                    tmpVec.push_back(data->timeValue[i][j]);
                timeDataDnHole_.push_back(tmpVec);
            }
            isDnHoleDataExists_ = true;
        }
        break;
    }
    case DN_HOLE_Y: {
        if(isDnHoleDataExists_ == false){
            if(timeDataDnHole_.size() > 0){
                for(int i = 0; i < timeDataDnHole_.size(); i++)
                    if(timeDataDnHole_[i].size() > 0)
                        timeDataDnHole_[i].clear();
                timeDataDnHole_.clear();
            }
            for(int i = 0; i < data->timeValue.size(); i++){
                QVector<int> tmpVec;
                for(int j = 0; j < data->timeValue[i].size(); j++)
                    tmpVec.push_back(data->timeValue[i][j]);
                timeDataDnHole_.push_back(tmpVec);
            }
            isDnHoleDataExists_ = true;
        }
        break;
    }
    case DN_HOLE_Z: {
        if(isDnHoleDataExists_ == false){
            if(timeDataDnHole_.size() > 0){
                for(int i = 0; i < timeDataDnHole_.size(); i++)
                    if(timeDataDnHole_[i].size() > 0)
                        timeDataDnHole_[i].clear();
                timeDataDnHole_.clear();
            }
            for(int i = 0; i < data->timeValue.size(); i++){
                QVector<int> tmpVec;
                for(int j = 0; j < data->timeValue[i].size(); j++)
                    tmpVec.push_back(data->timeValue[i][j]);
                timeDataDnHole_.push_back(tmpVec);
            }
            isDnHoleDataExists_ = true;
        }
        break;
    }
    case UP_HOLE: {
        int numUpHoleModules = data->timeValue.size();
        for(int i = 0; i < numUpHoleModules; i++){
            QVector<int> tmpVec;
            timeDataUpHole_.push_back(tmpVec);
        }
        for(int i = 0; i < numUpHoleModules; i++){
            for(int j = 0; j < data->timeValue[i].size(); j++)
                timeDataUpHole_[i].push_back(data->timeValue[i][j]);
        }
        break;
    }
    }
    mutex.unlock();
}

void CorrelationManager::setReadFileNames(const QStringList &readFileNames)
{
    readFileNames_ = readFileNames;
}

void CorrelationManager::setTypeCorrelation(int typeCorrelation)
{
    typeCorrelation_ = typeCorrelation;
}

int CorrelationManager::timeRecord() const
{
    return timeRecord_;
}

void CorrelationManager::setTimeRecord(int timeRecord)
{
    timeRecord_ = timeRecord;
}

int CorrelationManager::timeSwip() const
{
    return timeSwip_;
}

void CorrelationManager::setTimeSwip(int timeSwip)
{
    timeSwip_ = timeSwip;
}

int CorrelationManager::idRecord() const
{
    return idRecord_;
}

void CorrelationManager::setIdRecord(int idRecord)
{
    idRecord_ = idRecord;
}

int CorrelationManager::typeInt64or32() const
{
    return typeInt64or32_;
}

void CorrelationManager::setTypeInt64or32(int typeInt64or32)
{
    typeInt64or32_ = typeInt64or32;
}

void CorrelationManager::startCrossCorrelation()
{
    bool isComp = false;

    int idSweep = -1;
    for(int i = 0; i < channelsInt64_.size(); i++){
        if(channelsInt64_[i]->isSweep == true){
            idSweep = i;
            break;
        }
    }

    if(idSweep < 0)
        return;

    channelsInt64_[idSweep]->isCompleted = true;
    connect(this, SIGNAL(allCorrelationCompleted()), this, SLOT(sendCorrelationData()));

    for(int i = 0; i < channelsInt64_.size(); i++){
        if(i != idSweep && channelsInt64_[i]->sizeArrOrig > 0 && channelsInt64_[i]->isCompleted == false){
            isComp = true;
            channelsInt64_[i]->isCompleted = false;
            Correlation2* cor = new Correlation2(channelsInt64_[i]->id, typeCorrelation_, channelsInt64_[i]->dataOrig,
                                                 channelsInt64_[i]->sizeArrOrig,
                                                 channelsInt64_[idSweep]->dataOrig,
                                                 channelsInt64_[idSweep]->sizeArrOrig);
            int levels = -1;
            switch (channelsInt64_[i]->type) {
            case typeModules::SYNC: {
                levels = quantizationLevelsSync_;
                break;
            }
            case typeModules::UP_HOLE: {
                levels = quantizationLevelsUpHole_;
                break;
            }
            case typeModules::DN_HOLE_X: {
                levels = quantizationLevelsDnHole_;
                break;
            }
            case typeModules::DN_HOLE_Y: {
                levels = quantizationLevelsDnHole_;
                break;
            }
            case typeModules::DN_HOLE_Z: {
                levels = quantizationLevelsDnHole_;
                break;
            }
            }
            cor->setLevels(levels);

//            QThread* corThread = new QThread();
//            cor->moveToThread(corThread);
//            connect(corThread, SIGNAL(started()), cor, SLOT(run()));
//            connect(cor, SIGNAL(stopThread()), cor, SLOT(stop()));
//            connect(cor, SIGNAL(stopThread()), corThread, SLOT(quit()));
//            connect(corThread, SIGNAL(finished()), corThread, SLOT(deleteLater()));

            connect(cor, &Correlation2::convCompleted, this, &CorrelationManager::onConvCompletedInt64);
//            corThread->start();
            QThreadPool::globalInstance()->start(cor);
        }
        else{
            channelsInt64_[i]->isCompleted = true;
        }
    }

    if(isComp == false){
        sendCorrelationData();
    }
}

void CorrelationManager::run()
{
    fileName_ = "";
}

void CorrelationManager::stop()
{
    minIdTypes_.clear();
    if(channelsInt64_.isEmpty() == false){
        for(int i = 0; i < channelsInt64_.size(); i++) {
            if(channelsInt64_[i]->dataCrossCorrelation != nullptr)
                delete [] channelsInt64_[i]->dataCrossCorrelation;
            if(channelsInt64_[i]->dataOrig != nullptr)
                delete [] channelsInt64_[i]->dataOrig;
        }
        channelsInt64_.clear();
    }
}

void CorrelationManager::onFinishReadFile(QString fileName, universalTemporaryData *data)
{
    int type = -1;
    if(readFileNames_.contains(fileName) == true) {
        //определить тип
        readFileNames_.removeAt(readFileNames_.indexOf(fileName));
        if (fileName.contains("_sync.dat"))
            type = SYNC;
        else  if (fileName.contains("_downHoleX.dat")) {
            type = DN_HOLE_X;
        }
        else  if (fileName.contains("_downHoleY.dat")){
            type = DN_HOLE_Y;
        }
        else  if (fileName.contains("_downHoleZ.dat")){
            type = DN_HOLE_Z;
        }
        else  if (fileName.contains("_upHole.dat")){
            type = UP_HOLE;
        }

        //скопировать в add сhanel
        this->addChannels(static_cast<typeModules>(type), data);

        //если все файлы то по выбранному типу начать корреляцию
        if(readFileNames_.size() == 0){
            startCrossCorrelation();
        }
    }
}

void CorrelationManager::onFinishReadCalc(QString dataFileName, QVector<int> types, QVector<universalTemporaryData *> data)
{
    fileName_ = dataFileName;
    for(int i = 0; i < types.size(); i++){
        this->addChannels(static_cast<typeModules>(types[i]), data[i]);
        qDebug() << "in Corr" << data[i]->timeValue.size() << data[i]->timeValue[0].size();
    }
    startCrossCorrelation();
}

void CorrelationManager::onConvCompletedInt64(int id, qint64 *result, int size, qint64 maxElement)
{
    for(int i = 0; i < channelsInt64_.size(); i++) {
        if(channelsInt64_[i]->id == id){
            if(channelsInt64_[i]->isCompleted == false){
                channelsInt64_[i]->isCompleted = true;
                channelsInt64_[i]->dataCrossCorrelation = new qint64[size];
                memcpy(channelsInt64_[i]->dataCrossCorrelation, result, sizeof(qint64) * static_cast<unsigned int>(size));
                delete [] result;
                channelsInt64_[i]->sizeCrossCorrelation = size;
                channelsInt64_[i]->maxValue = maxElement;
            }
        }
    }
    bool isAllCompleted = true;
    for(int i = 0; i < channelsInt64_.size(); i++){
        if(channelsInt64_[i]->isCompleted == false){
            isAllCompleted = false;
            break;
        }
    }

    if(isAllCompleted == true){
        emit allCorrelationCompleted();
    }
}

void CorrelationManager::sendCorrelationData()
{
    //скомпоновать по typeModules, сортировка внутри по id
    bool isWrittenTypes[UP_HOLE + 1];
    for(int i = 0; i <= UP_HOLE; i++)
        isWrittenTypes[i] = false;

    for(int iterType = SYNC; iterType <= UP_HOLE; iterType++) {
        universalTemporaryData* tmpData = new universalTemporaryData();
        qint64 maxValue = -1;

        if(iterType != SYNC){
            for(int i = 0; i < channelsInt64_.size(); i++)
                if(iterType < UP_HOLE && channelsInt64_[i]->type < UP_HOLE && channelsInt64_[i]->type > SYNC){
                    if(maxValue < channelsInt64_[i]->maxValue)
                        maxValue = channelsInt64_[i]->maxValue;
                }
                else if (iterType == channelsInt64_[i]->type) {
                    if(maxValue < channelsInt64_[i]->maxValue)
                        maxValue = channelsInt64_[i]->maxValue;
                }
        }

        int level = -1;
        switch (iterType) {
        case typeModules::SYNC: {
            level = quantizationLevelsSync_;
            break;
        }
        case typeModules::UP_HOLE: {
            level = quantizationLevelsUpHole_;
            break;
        }
        case typeModules::DN_HOLE_X: {
            level = quantizationLevelsDnHole_;
            break;
        }
        case typeModules::DN_HOLE_Y: {
            level = quantizationLevelsDnHole_;
            break;
        }
        case typeModules::DN_HOLE_Z: {
            level = quantizationLevelsDnHole_;
            break;
        }
        }
        double coef = static_cast<double>(level) / maxValue;
        if(iterType == SYNC){
            coef = 1;
        }

        for(int i = 0; i < channelsInt64_.size(); i++){
            if(channelsInt64_[i]->type == iterType){
                QList<qint32*>* data_list(new QList<qint32*>);
                tmpData->allData_list.push_back(data_list);
//                qint64 tmpMax = -1;
                for(int j = 0; j < channelsInt64_[i]->sizeCrossCorrelation; j++)
                {
                    qint32* value = new(qint32);
                    *value = static_cast<qint32>(channelsInt64_[i]->dataCrossCorrelation[j] * coef);//*coef
//                    if(tmpMax < channelsInt64_[i]->dataCrossCorrelation[j])
//                        tmpMax = channelsInt64_[i]->dataCrossCorrelation[j];
                    tmpData->allData_list[channelsInt64_[i]->id - minIdTypes_[channelsInt64_[i]->type]]->push_back(value);
                }
//                qDebug() << "MAX: " << i << tmpMax;
            }
        }

        if(tmpData->allData_list.size() > 0){
            switch (iterType) {
            case SYNC:{
                tmpData->timeValue = this->timeDataSync_;
                emit correlationCompleted(this->idRecord(), static_cast<typeModules>(iterType), tmpData);
                isWrittenTypes[iterType] = true;
                break;
            }
            case DN_HOLE_X:{
                tmpData->timeValue = this->timeDataDnHole_;
                emit correlationCompleted(this->idRecord(), static_cast<typeModules>(iterType), tmpData);
                isWrittenTypes[iterType] = true;
                break;
            }
            case DN_HOLE_Y:{
                tmpData->timeValue = this->timeDataDnHole_;
                emit correlationCompleted(this->idRecord(), static_cast<typeModules>(iterType), tmpData);
                isWrittenTypes[iterType] = true;
                break;
            }
            case DN_HOLE_Z:{
                tmpData->timeValue = this->timeDataDnHole_;
                emit correlationCompleted(this->idRecord(), static_cast<typeModules>(iterType), tmpData);
                isWrittenTypes[iterType] = true;
                break;
            }
            case UP_HOLE:{
                tmpData->timeValue = this->timeDataUpHole_;
                emit correlationCompleted(this->idRecord(), static_cast<typeModules>(iterType), tmpData);
                isWrittenTypes[iterType] = true;
                break;
            }
            }
        }
    }

    emit readyDraw(this->idRecord_);
}
