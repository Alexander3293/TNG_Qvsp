#include "work_with_project/measurement.h"

#include <QTextCodec>

Measurement::Measurement(int id, QString projectName, int numDNHole, int numUpHole, int timeRec, int timeSwip, QString actionType, QString source, QObject *parent) : QObject(parent)
{
    setId(id);
    countCalculationFiles_ = 0;
    setProjectName(projectName);
    setDate(QDate::currentDate());
    setTime(QTime::currentTime());
    measFile_ = new QSettings();
    gId_ = 0;
    numDnHoleModules_ = numDNHole;
    numUpHoleModules_ = numUpHole;
    timeRecord_ = timeRec;
    timeSwip_ = timeSwip;
    actionType_ = actionType;
    source_ = source;
    gainDnHoles_ = 1;
    gainUpHoles_ = 1;
}

Measurement::Measurement(QString inPath, QObject *parent)
{
    gId_ = 0;
    countCalculationFiles_ = 0;
    actionType_ = "";
    Q_UNUSED(parent);
    setPath(inPath);
    QString fileName = path(); //+ inPath.mid(inPath.lastIndexOf("/")) + measFileFormat_;

    measFile_ = new QSettings(fileName, QSettings::IniFormat);
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    measFile_->setIniCodec(codec);
    if (measFile_->status() != QSettings::NoError)
    {
        emit measError(QString::fromUtf8("Ошибка при открытии файлов измерений."));
        return;
    }

    QString tmp = "";
    measFile_->beginGroup(QString::fromUtf8("Head"));
    tmp = measFile_->value(QString::fromUtf8("Project"), "").toString();
    if(checkReadedData(tmp) == false && tmp.size() != 0){
        measFile_->endGroup();
        return;
    }
    else {
        setProjectName(tmp);
    }
    tmp = measFile_->value(QString::fromUtf8("Id"), "").toString();
    if(checkReadedData(tmp) == false && tmp.size() != 0){
        measFile_->endGroup();
        return;
    }
    else {
        setId(tmp.toInt() - 1);
    }
    measFile_->endGroup();

    measFile_->beginGroup(QString::fromUtf8("Well"));
    tmp = measFile_->value(QString::fromUtf8("Data"), "").toString();
    if(checkReadedData(tmp) == false && tmp.size() != 0){
        measFile_->endGroup();
        return;
    }
    else {
        setDate(QDate::fromString(tmp,"dd.MM.yyyy"));
    }
    tmp = measFile_->value(QString::fromUtf8("Time"), "").toString();
    if(checkReadedData(tmp) == false && tmp.size() != 0){
        measFile_->endGroup();
        return;
    }
    else {
        setTime(QTime::fromString(tmp,"hh:mm:ss.zzz"));
    }
    measFile_->endGroup();

    measFile_->beginGroup(QString::fromUtf8("NumModules"));
    tmp = measFile_->value(QString::fromUtf8("DnHole"), "").toString();
    if(checkReadedData(tmp) == false && tmp.size() != 0){
        measFile_->endGroup();
        return;
    }
    else {
        numDnHoleModules_ = tmp.toInt();
    }
    tmp = measFile_->value(QString::fromUtf8("UpHole"), "").toString();
    if(checkReadedData(tmp) == false && tmp.size() != 0){
        measFile_->endGroup();
        return;
    }
    else {
        numUpHoleModules_ = tmp.toInt();
    }
    measFile_->endGroup();

    measFile_->beginGroup(QString::fromUtf8("GainModules"));
    tmp = measFile_->value(QString::fromUtf8("DnHole"), "").toString();
    if(checkReadedData(tmp) == false && tmp.size() != 0){
        measFile_->endGroup();
        return;
    }
    else {
        gainDnHoles_ = tmp.toInt();
    }
    tmp = measFile_->value(QString::fromUtf8("UpHole"), "").toString();
    if(checkReadedData(tmp) == false && tmp.size() != 0){
        measFile_->endGroup();
        return;
    }
    else {
        gainUpHoles_ = tmp.toInt();
    }
    measFile_->endGroup();

    measFile_->beginGroup(QString::fromUtf8("Times"));
    tmp = measFile_->value(QString::fromUtf8("TimeRecord"), "").toString();

    if(checkReadedData(tmp) == false && tmp.size() != 0){
        measFile_->endGroup();
        return;
    }
    else {
        timeRecord_ = tmp.toInt();
    }
    tmp = measFile_->value(QString::fromUtf8("TimeSwip"), "").toString();

    if(checkReadedData(tmp) == false && tmp.size() != 0){
        measFile_->endGroup();
        return;
    }
    else {
        timeSwip_ = tmp.toInt();
    }
    measFile_->endGroup();

    measFile_->beginGroup(QString::fromUtf8("Action"));
    tmp = measFile_->value(QString::fromUtf8("Source"), "").toString();

    if(checkReadedData(tmp) == false && tmp.size() != 0){
        measFile_->endGroup();
        return;
    }
    else {
        source_  = tmp;
    }
    tmp = measFile_->value(QString::fromUtf8("Type"), "").toString();
    if(checkReadedData(tmp) == false && tmp.size() != 0){
        measFile_->endGroup();
        return;
    }
    else {
        actionType_  = tmp;
    }
    measFile_->endGroup();

    measFile_->beginGroup(QString::fromUtf8("ServiceInfo"));
    tmp = measFile_->value(QString::fromUtf8("Depth"), "").toString();

    if(checkReadedData(tmp) == false && tmp.size() != 0){
        measFile_->endGroup();
        return;
    }
    else {
        depth_  = tmp;
    }
    tmp = measFile_->value(QString::fromUtf8("Operator"), "").toString();

    if(checkReadedData(tmp) == false && tmp.size() != 0){
        measFile_->endGroup();
        return;
    }
    else {
        nameOperator_  = tmp;
    }
    tmp = measFile_->value(QString::fromUtf8("NumHole"), "").toString();
    if(checkReadedData(tmp) == false && tmp.size() != 0){
        measFile_->endGroup();
        return;
    }
    else {
        numHole_  = tmp;
    }
    tmp = measFile_->value(QString::fromUtf8("NameArea"), "").toString();

    if(checkReadedData(tmp) == false && tmp.size() != 0){
        measFile_->endGroup();
        return;
    }
    else {
        nameArea_  = tmp;
    }
    tmp = measFile_->value(QString::fromUtf8("Accumulation"), "").toString();
    if(checkReadedData(tmp) == false && tmp.size() != 0){
        measFile_->endGroup();
        return;
    }
    else {
        accamulation_  = tmp.toInt();
    }
    tmp = measFile_->value(QString::fromUtf8("DistBtwDevices"), "").toString();
    distBtwDevices_ = tmp;

    measFile_->endGroup();

    int countModules = measFile_->beginReadArray(QString::fromUtf8("Modules"));
    QStringList dataPath;
    for(int i = 0; i < countModules; i++){
        measFile_->setArrayIndex(i);
        tmp = measFile_->value("PATH", "").toString();
        if(tmp.size() > 0)
            dataPath.push_back(tmp);
    }
    measFile_->endArray();
}

Measurement::~Measurement()
{
    delete measFile_;
}

QString Measurement::path() const
{
    return path_;
}

void Measurement::setPath(const QString &path)
{
    path_ = path;
}

void Measurement::createDir()
{
    setPath(path()+"/"+"Measurement_"+QString::number(getId()+1));
    //qDebug() << path();
    QDir dir(path());
    if (!dir.exists()){
        dir.mkdir(".");
    }
    else {
        emit measError(QString::fromUtf8("Ошибка при добавлении измерения."));
        return;
    }
}

void Measurement::createMeasFile()
{
    measFile_ = new QSettings(QString(path_+"/"+"Measurement_"+QString::number(getId()+1)+getMeasFileFormat()), QSettings::IniFormat);
    if (measFile_->status() != QSettings::NoError)
    {
        emit measError(QString::fromUtf8("Ошибка при добавлении измерения."));
        return;
    }

    measFile_->beginGroup(QString::fromUtf8("Head"));
    measFile_->setValue(QString::fromUtf8("Project"), getProjectName());
    measFile_->setValue(QString::fromUtf8("Id"), getId()+1);
    measFile_->endGroup();

    measFile_->beginGroup(QString::fromUtf8("Well"));
    measFile_->setValue(QString::fromUtf8("Data"), getDate().toString("dd.MM.yyyy"));
    measFile_->setValue(QString::fromUtf8("Time"), getTime().toString("hh:mm:ss.zzz"));
    measFile_->endGroup();

    measFile_->beginGroup(QString::fromUtf8("NumModules"));
    measFile_->setValue(QString::fromUtf8("DnHole"), numDnHoleModules_);
    measFile_->setValue(QString::fromUtf8("UpHole"), numUpHoleModules_);
    measFile_->endGroup();

    measFile_->beginGroup(QString::fromUtf8("GainModules"));
    measFile_->setValue(QString::fromUtf8("DnHole"), gainDnHoles_);
    measFile_->setValue(QString::fromUtf8("UpHole"), gainUpHoles_);
    measFile_->endGroup();

    measFile_->beginGroup(QString::fromUtf8("Times"));
    measFile_->setValue(QString::fromUtf8("TimeRecord"), timeRecord_);
    measFile_->setValue(QString::fromUtf8("TimeSwip"), timeSwip_);
    measFile_->endGroup();

    measFile_->beginGroup(QString::fromUtf8("Start"));
    measFile_->setValue(QString::fromUtf8("Time_Start"), getTime().toString("hh:mm:ss.zzz"));
    measFile_->endGroup();

    measFile_->beginGroup(QString::fromUtf8("Stop"));
    measFile_->setValue(QString::fromUtf8("Time_Stop"), "0");
    measFile_->endGroup();

    measFile_->beginGroup(QString::fromUtf8("Action"));
    measFile_->setValue(QString::fromUtf8("Source"), source_);
    measFile_->setValue(QString::fromUtf8("Type"), actionType_);
    measFile_->endGroup();

    measFile_->beginGroup(QString::fromUtf8("ServiceInfo"));
    measFile_->setValue(QString::fromUtf8("Depth"), depth_);
    measFile_->setValue(QString::fromUtf8("Operator"), nameOperator_);
    measFile_->setValue(QString::fromUtf8("NumHole"), numHole_);
    measFile_->setValue(QString::fromUtf8("NameArea"), nameArea_);
    measFile_->setValue(QString::fromUtf8("DistBtwDevices"), distBtwDevices_);
    measFile_->endGroup();

    measFile_->beginWriteArray(QString::fromUtf8("Modules"));
    measFile_->endArray();

    emit measCompleted(QString::fromUtf8("Измерение добавлено."));
}

int Measurement::getId() const
{
    return id;
}

void Measurement::setId(int value)
{
    id = value;
}

QString Measurement::getMeasFileFormat() const
{
    return measFileFormat_;
}

QString Measurement::getProjectName() const
{
    return projectName_;
}

void Measurement::setProjectName(const QString &projectName)
{
    projectName_ = projectName;
}

QDate Measurement::getDate() const
{
    return date_;
}

void Measurement::setDate(const QDate &date)
{
    date_ = date;
}

QTime Measurement::getTime() const
{
    return time_;
}

void Measurement::setTimeStart(const QTime &time)
{
    measFile_->beginGroup(QString::fromUtf8("Start"));
    measFile_->setValue(QString::fromUtf8("Time_Start"), time.toString("hh:mm:ss.zzz"));
    measFile_->endGroup();
}

QTime Measurement::getTimeStart() const
{
    measFile_->beginGroup("Start");
    QString tmp = measFile_->value("Time_Start", "").toString();
    measFile_->endGroup();
    return QTime::fromString(tmp, "hh:mm:ss.zzz");
}


void Measurement::setTimeStop(const QTime &time)
{
    measFile_->beginGroup(QString::fromUtf8("Stop"));
    measFile_->setValue(QString::fromUtf8("Time_Stop"), time.toString("hh:mm:ss.zzz"));
    measFile_->endGroup();
}

QTime Measurement::getTimeStop() const
{
    measFile_->beginGroup("Stop");
    QString tmp = measFile_->value("Time_Stop", "").toString();
    measFile_->endGroup();
    return QTime::fromString(tmp, "hh:mm:ss.zzz");
}

void Measurement::setTime(const QTime &time)
{
    time_ = time;
}

int Measurement::getCountTypeModules() const
{
    return countTypeModules_;
}

void Measurement::setCountTypeModules(int countModules)
{
    countTypeModules_ = countModules;
}

QVector<int> Measurement::getVectorIdRecords()
{
    QVector<int> result;
    if(measFile_->status() == QSettings::NoError)
    {
        int countFiles = measFile_->beginReadArray("Modules");
        for(int i = 0; i < countFiles; ++i){
            measFile_->setArrayIndex(i);
            QString tmp = measFile_->value("PATH", "").toString();
            if(tmp.size() > 0){
                tmp = tmp.mid(tmp.indexOf("record_") + 7, -1);
                tmp = tmp.left(tmp.lastIndexOf("_"));
                if(result.size() > 0) {
                    if(result.last() != tmp.toInt())
                        result.push_back(tmp.toInt());
                }
                else
                    result.push_back(tmp.toInt());
            }
        }
        measFile_->endArray();
    }
    return result;
}

void Measurement::setNumRecord(int numberRecord)
{
    numberRecord_ = numberRecord;
}

void Measurement::writeData(const int type, int numberRecord, int countModules, universalTemporaryData *data)
{
    Q_UNUSED(type);
    Q_UNUSED(numberRecord);
    Q_UNUSED(countModules);
    Q_UNUSED(data);
}

void Measurement::readData(const int idRecord, int typeCorrelation)
{
    readFileNames_.clear();
    int idRec = idRecord;
    //find Id of Last Record
    if(idRec < 0){
        QDir curDir = QDir(path()+"/");
        QStringList tmpFilesList = curDir.entryList(QDir::Files | QDir::NoSymLinks);
        for(int iter = 0; iter < tmpFilesList.size(); iter++ ) {
            QString tmp = tmpFilesList[iter].mid(tmpFilesList[iter].indexOf("_")+1,
                                                 tmpFilesList[iter].size());
            tmp = tmp.left(tmp.indexOf("_"));
            if(tmp.toInt() > idRec)
                idRec = tmp.toInt();
        }
    }
    QStringList files;
    QStringList fileNames;
    fileNames.push_back(path()+"/"+QString("record_%1").arg(QString::number(idRec))+"_sync.dat");
    fileNames.push_back(path()+"/"+QString("record_%1").arg(QString::number(idRec))+"_downHoleX.dat");
    fileNames.push_back(path()+"/"+QString("record_%1").arg(QString::number(idRec))+"_downHoleY.dat");
    fileNames.push_back(path()+"/"+QString("record_%1").arg(QString::number(idRec))+"_downHoleZ.dat");
    fileNames.push_back(path()+"/"+QString("record_%1").arg(QString::number(idRec))+"_upHole.dat");
    QDir currentDir = QDir(path()+"/");
    QStringList tmp;
    for(int i = 0; i < fileNames.size(); i++) {
        QString str = fileNames[i];
        tmp.push_back(str.mid(str.lastIndexOf("/")+1, str.size()));
    }
    tmp = currentDir.entryList(QStringList(tmp), QDir::Files | QDir::NoSymLinks);
    if(fileNames.size() == tmp.size())
        files += fileNames;
    else {
        emit finishRead(getId());
        emit measCompleted(QString("Файлы записи не найдены! Измерение %1.").arg(getId()+1));
        return;
    }
    if(typeCorrelation == 0) {
//        for(int i = 0; i < files.size(); i++){
//            readFileNames_.push_back(files[i]);
//            ReadWriteDataFile *reader = new ReadWriteDataFile(gId_++);
//            reader->setTimeRecord(this->timeRecord_);
//            reader->setTimeSwip(-1);
//            reader->setTypeCorrelation(typeCorrelation);
//            QThread* readerThread = new QThread();
//            //            writeFileThreads_.push_back(readerThread);
//            //            for(int ii = 0; ii < writeFileThreads_.size(); ii++)
//            //                qDebug() << writeFileThreads_[ii]->isRunning() << ii << "Вывод";
//            reader->moveToThread(readerThread);
//            connect(readerThread, SIGNAL(started()), reader, SLOT(run()) );
//            connect(reader, SIGNAL(stopThread()), reader, SLOT(stop()));
//            connect(reader, SIGNAL(stopThread()), readerThread, SLOT(quit()));
//            // connect(reader, SIGNAL(stopThread()), reader, SLOT(deleteLater()));
//            connect(readerThread, SIGNAL(finished()), readerThread, SLOT(deleteLater()));
//            readerThread->start();
//            connect(this, SIGNAL(readFile(QString)), reader, SLOT(readFile(QString)));
//            connect(reader, SIGNAL(finishReadFile(QString,universalTemporaryData*)),
//                    this, SLOT(onFinishReadFile(QString,universalTemporaryData*)));
//            emit readFile(files[i]);
//            disconnect(this, SIGNAL(readFile(QString)), reader, SLOT(readFile(QString)));

//        }
    }
    else if(typeCorrelation == 1)
    {
//        CorrelationManager* corr = new CorrelationManager(1);
//        //установка значений времени
//        corr->setReadFileNames(files);
//        corr->setIdRecord(idRecord);
//        corr->setTypeCorrelation(typeCorrelation);
//        corr->setTimeRecord(this->timeRecord_);
//        corr->setTimeSwip(this->timeSwip_);
//        QThread* corrThread = new QThread();
//        corr->moveToThread(corrThread);
//        connect(corrThread, SIGNAL(started()), corr, SLOT(run()));
//        connect(corr, SIGNAL(stopThread()), corr, SLOT(stop()));
//        connect(corr, SIGNAL(stopThread()), corrThread, SLOT(quit()));
//        connect(corrThread, SIGNAL(finished()), corrThread, SLOT(deleteLater()));
//        connect(corr, SIGNAL(correlationCompleted(int, typeModules, universalTemporaryData*)), this, SLOT(onCorrelationCompleted(int, typeModules, universalTemporaryData*)));
//        connect(corr, SIGNAL(readyDraw(int)), this, SLOT(onFinishCorr(int)));
//        corrThread->start();
//        //qDebug() << "Start MEAS Calculating" << this->thread();

//        for(int i = 0; i < files.size(); i++)
//        {
//            ReadWriteDataFile *readerCorr = new ReadWriteDataFile(i);
//            readerCorr->setTimeRecord(this->timeRecord_);
//            readerCorr->setTimeSwip(-1);
//            readerCorr->setTypeCorrelation(typeCorrelation);
//            QThread* readerCorrThread = new QThread();
//            readerCorr->moveToThread(readerCorrThread);
//            connect(readerCorrThread, SIGNAL(started()), readerCorr, SLOT(run()) );
//            connect(readerCorr, SIGNAL(stopThread()), readerCorr, SLOT(stop()));
//            connect(readerCorr, SIGNAL(stopThread()), readerCorrThread, SLOT(quit()));
//            connect(readerCorrThread, SIGNAL(finished()), readerCorrThread, SLOT(deleteLater()));
//            readerCorrThread->start();
//            connect(this, SIGNAL(readFile(QString)), readerCorr, SLOT(readFile(QString)));
//            connect(readerCorr, SIGNAL(finishReadFile(QString,universalTemporaryData*)),
//                    corr, SLOT(onFinishReadFile(QString,universalTemporaryData*)));
//            emit readFile(files[i]);
//            disconnect(this, SIGNAL(readFile(QString)), readerCorr, SLOT(readFile(QString)));
//        }
    }
    else if(typeCorrelation == 2) {
//        CorrelationManager* corr = new CorrelationManager(1);
//        //установка значений времени
//        corr->setIdRecord(idRecord);
//        corr->setReadFileNames(files);
//        corr->setTypeCorrelation(typeCorrelation);
//        corr->setTimeRecord(this->timeRecord_);
//        corr->setTimeSwip(this->timeSwip_);
//        QThread* corrThread = new QThread();
//        corr->moveToThread(corrThread);
//        connect(corrThread, SIGNAL(started()), corr, SLOT(run()));
//        connect(corr, SIGNAL(stopThread()), corr, SLOT(stop()));
//        connect(corr, SIGNAL(stopThread()), corrThread, SLOT(quit()));
//        connect(corrThread, SIGNAL(finished()), corrThread, SLOT(deleteLater()));
//        connect(corr, SIGNAL(correlationCompleted(int, typeModules, universalTemporaryData*)), this, SLOT(onCorrelationCompleted(int, typeModules, universalTemporaryData*)));
//        connect(corr, SIGNAL(readyDraw(int)), this, SLOT(onFinishCorr(int)));
//        corrThread->start();
//        //qDebug() << "Start MEAS Calculating" << this->thread();

//        for(int i = 0; i < files.size(); i++)
//        {
//            ReadWriteDataFile *readerCorr = new ReadWriteDataFile(i);
//            if(files[i].contains("sync") == true){
//                readerCorr->setTimeRecord(this->timeSwip_);
//                readerCorr->setTimeSwip(-1);
//            }
//            else{
//                readerCorr->setTimeRecord(this->timeRecord_ + this->timeSwip_);
//                readerCorr->setTimeSwip(-1);
//            }
//            readerCorr->setTypeCorrelation(typeCorrelation);
//            QThread* readerCorrThread = new QThread();
//            readerCorr->moveToThread(readerCorrThread);
//            connect(readerCorrThread, SIGNAL(started()), readerCorr, SLOT(run()) );
//            connect(readerCorr, SIGNAL(stopThread()), readerCorr, SLOT(stop()));
//            connect(readerCorr, SIGNAL(stopThread()), readerCorrThread, SLOT(quit()));
//            connect(readerCorrThread, SIGNAL(finished()), readerCorrThread, SLOT(deleteLater()));
//            readerCorrThread->start();
//            connect(this, SIGNAL(readFile(QString)), readerCorr, SLOT(readFile(QString)));
//            connect(readerCorr, SIGNAL(finishReadFile(QString,universalTemporaryData*)),
//                    corr, SLOT(onFinishReadFile(QString,universalTemporaryData*)));
//            emit readFile(files[i]);
//            disconnect(this, SIGNAL(readFile(QString)), readerCorr, SLOT(readFile(QString)));
//        }
    }
}

void Measurement::newCalculation(QVector<int> listNumbers, int typeCorrelation, QString pathSEGD)
{
    Q_UNUSED(listNumbers);
    Q_UNUSED(typeCorrelation);
    Q_UNUSED(pathSEGD);
}

void Measurement::readCalcData(int calcId)
{
    Q_UNUSED(calcId);
}

int Measurement::getNumDnHoleModules() const
{
    return numDnHoleModules_;
}

int Measurement::getNumUpHoleModules() const
{
    return numUpHoleModules_;
}

int Measurement::getTimeRecord() const
{
    return timeRecord_;
}

void Measurement::setTimeRecord(int timeRecord)
{
    timeRecord_ = timeRecord;
}

int Measurement::getTimeSwip() const
{
    return timeSwip_;
}

void Measurement::setTimeSwip(int timeSwip)
{
    timeSwip_ = timeSwip;
}

QString Measurement::getActionType() const
{
    return actionType_;
}

void Measurement::setActionType(const QString &actionType)
{
    actionType_ = actionType;
}

QString Measurement::getSource() const
{
    return source_;
}

void Measurement::setSource(const QString &source)
{
    source_ = source;
}

int Measurement::getGainDnHoles() const
{
    return gainDnHoles_;
}

void Measurement::setGainDnHoles(int gainDnHoles)
{
    gainDnHoles_ = gainDnHoles;
    measFile_->beginGroup(QString::fromUtf8("GainModules"));
    measFile_->setValue(QString::fromUtf8("DnHole"), gainDnHoles_);
    measFile_->endGroup();
}

int Measurement::getGainUpHoles() const
{
    return gainUpHoles_;
}

void Measurement::setGainUpHoles(int gainUpHoles)
{
    gainUpHoles_ = gainUpHoles;
    measFile_->beginGroup(QString::fromUtf8("GainModules"));
    measFile_->setValue(QString::fromUtf8("UpHole"), gainUpHoles_);
    measFile_->endGroup();
}

void Measurement::setServiceInfo(QMap<QString, QString> serviceInfo)
{ 
    QString tmp = serviceInfo.value("Depth");
    if(tmp.size() > 0){
        depth_ = tmp;
    }

    tmp = serviceInfo.value("Operator");
    if(tmp.size() > 0){
        nameOperator_ = tmp;
    }

    tmp = serviceInfo.value("NumHole");
    if(tmp.size() > 0){
        numHole_ = tmp;
    }

    tmp = serviceInfo.value("NameArea");
    if(tmp.size() > 0){
        nameArea_ = tmp;
    }

    tmp = serviceInfo.value("DistBtwDevices");
    if(tmp.size() > 0){
        distBtwDevices_ = tmp;
    }
    measFile_->beginGroup(QString::fromUtf8("ServiceInfo"));
    measFile_->setValue(QString::fromUtf8("Depth"), depth_);
    measFile_->setValue(QString::fromUtf8("Operator"), nameOperator_);
    measFile_->setValue(QString::fromUtf8("NumHole"), numHole_);
    measFile_->setValue(QString::fromUtf8("NameArea"), nameArea_);
    measFile_->setValue(QString::fromUtf8("DistBtwDevices"), distBtwDevices_);
    measFile_->endGroup();
}

QMap<QString, QString> Measurement::getServiceInfo()
{
    QMap<QString, QString> serviceInfo;
    serviceInfo.insert("Depth", depth_);
    serviceInfo.insert("Operator", nameOperator_);
    serviceInfo.insert("NumHole", numHole_);
    serviceInfo.insert("NameArea", nameArea_);
    serviceInfo.insert("Accumulation", QString::number(accamulation_));
    serviceInfo.insert("DistBtwDevices", distBtwDevices_);
    return serviceInfo;
}

QString Measurement::getLastMeasPath() const
{
    return lastMeasPath_;
}

void Measurement::setLastMeasPath(const QString &lastMeasPath)
{
    lastMeasPath_ = lastMeasPath;
}

bool Measurement::checkReadedData(QString data)
{
    if(data.size() > 0)
        return true;
    else {
        emit measError(QString("Ошибка чтения файла измерения %1!").arg(getId() + 1));
        return false;
    }
}

QString Measurement::getDistBtwDevices() const
{
    return distBtwDevices_;
}

void Measurement::setDistBtwDevices(QString distBtwDevices)
{
    distBtwDevices_ = distBtwDevices;
}

int Measurement::getAccamulation() const
{
    return accamulation_;
}

void Measurement::setAccamulation(int accamulation)
{
    accamulation_ = accamulation;
}

void Measurement::onFinishReadFile(QString fileName, universalTemporaryData *data)
{
    int idRecord = -1;
    typeModules type = SYNC; //неопредел значение
    if(readFileNames_.contains(fileName) == true){
        readFileNames_.removeAt(readFileNames_.indexOf(fileName));
        QString tmp = fileName.mid(fileName.indexOf("record_") + 7, -1);
        tmp = tmp.left(tmp.lastIndexOf("_"));
        idRecord = tmp.toInt();
        if (fileName.contains("_sync.dat"))
            type = SYNC;
        else  if (fileName.contains("_downHoleX.dat"))
            type = DN_HOLE_X;
        else  if (fileName.contains("_downHoleY.dat"))
            type = DN_HOLE_Y;
        else  if (fileName.contains("_downHoleZ.dat"))
            type = DN_HOLE_Z;
        else  if (fileName.contains("_upHole.dat"))
            type = UP_HOLE;

        emit newData(getId(), idRecord, type, data);

        if(readFileNames_.size() == 0){
            emit finishRead(getId());
            emit measCompleted(QString("Файлы записи %1 измерения %2 успешно открыты!").arg(idRecord+1).arg(getId()+1));
        }
    }
}

void Measurement::onFinishReadCalcFile(QString fileName,int type ,universalTemporaryData* data, int typeCorrelation)
{
    if(readFileCalcCounter_ <= 0)
        return;

    readFileCalcCounter_--;

    QString str = fileName;
    str = str.mid(str.lastIndexOf("/")+1, str.size() - str.lastIndexOf("/") - 1);
    int tmpNum = -1;
    if(str.contains("calculation_") == true && str.contains(".dat")){
        int start = str.indexOf("_") + 1;
        str = str.mid(start, str.size() - start);
        int stop = str.indexOf("_");
        tmpNum = str.mid(0,stop).toInt();
    }
    else {
        return;
    }
    if(tmpNum <= 0)
        return;

    emit newData(getId(), tmpNum, (typeModules)type, data);
    if(static_cast<typeModules>(type) == SYNC){
        emit newTypeCorrelation(typeCorrelation);
        //qDebug() << "new Type" << typeCorrelation;
    }

    if(readFileCalcCounter_ == 0){
        emit finishRead(getId());
        emit measCompleted(QString("Файлы измерения %1 успешно открыты!").arg(getId()+1));
    }

}

void Measurement::onFinishCalc(QString msg)
{
    qDebug() << "onFinishCalc";
    emit measCompleted(QString(msg + " Измерение %1.").arg(getId() + 1));
    if (isFinishSEGD_ == true) {
        emit stopSpinner(getId());
        emit measCompleted("Расчет успешно выполнен!");
//        SpinnerProgressController::getInstanse().incValue(5);
    }
    isFinishCalc_ = true;
}

void Measurement::onFinishCalcSEGD()
{
    qDebug() << "onFinishCalcSEGD";
    if (isFinishCalc_ == true){
        emit stopSpinner(getId());
        emit measCompleted("Расчет успешно выполнен!");
//        SpinnerProgressController::getInstanse().incValue(5);
    }
    isFinishSEGD_ = true;
}

void Measurement::onCorrelationCompleted(int idRecord, typeModules type, universalTemporaryData* data)
{
    emit newData(this->getId(), idRecord, type, data);
}

void Measurement::onFinishCorr(int idRecord)
{
    emit finishRead(getId());
    emit measCompleted(QString("Файлы записи %1 измерения %2 успешно открыты!").arg(idRecord+1).arg(getId()+1));
    emit measCompleted("Корреляция успешно произведена!");
}

void Measurement::onFinishWriteFile()
{
    emit finishWriteFile();
}

void Measurement::createDataFiles(int type, int numRecord)
{
    if (measFile_->status() != QSettings::NoError)
    {
        emit measError(QString::fromUtf8("Ошибка при добавлении файла модуля."));
        return;
    }

    QFile* dataFile = new QFile();
    QString dataFileName;
    if(type == SYNC)
        dataFileName = QString("record_%1").arg(QString::number(numRecord))+"_sync.dat";
    else if(type == DN_HOLE_X)
        dataFileName = QString("record_%1").arg(QString::number(numRecord))+"_downHoleX.dat";
    else if(type == DN_HOLE_Y)
        dataFileName = QString("record_%1").arg(QString::number(numRecord))+"_downHoleY.dat";
    else if(type == DN_HOLE_Z)
        dataFileName = QString("record_%1").arg(QString::number(numRecord))+"_downHoleZ.dat";
    else if(type == UP_HOLE)
        dataFileName = QString("record_%1").arg(QString::number(numRecord))+"_upHole.dat";

    dataFile->setFileName(path() + "/" + dataFileName);
    if (!dataFile->open(QIODevice::WriteOnly))
    {
        emit measError(QString::fromUtf8("Ошибка при создании файла данных."));
        return;
    }

    int countFiles = measFile_->beginReadArray("Modules");
    measFile_->endArray();
    measFile_->beginWriteArray("Modules");
    if(countFiles == type + (numRecord * getCountTypeModules()))
        measFile_->setArrayIndex(countFiles);
    measFile_->setValue(QString::fromUtf8("PATH"), dataFileName);
    measFile_->endArray();

    dataFile->flush();
    dataFile->close();
    delete dataFile;
}
