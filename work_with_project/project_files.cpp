#include "work_with_project/project_files.h"
//#include <QDebug>


#include <QTextCodec>

project_files::project_files(QThread *projThread, QObject *parent) : QObject(parent)
{
    qRegisterMetaType<typeModules>("typeModules");
    //setTool_type(QString::fromUtf8("ВСП"));
    setTool_type(QString::fromUtf8("ГРП"));
    setDate(QDate::currentDate());
    setTime(QTime::currentTime());
    setIsOpened(false);
    projThread_ = projThread;
}

project_files::~project_files()
{
    meas_.clear();
    delete projectFile_;
}

QString project_files::projectName() const
{
    return projectName_;
}

void project_files::setProjectName(const QString &projectName)
{
    projectName_ = projectName;
}

QString project_files::projectPath() const
{
    return projectPath_;
}

void project_files::setProjectPath(const QString &projectPath)
{
    projectPath_ = projectPath;
}

QString project_files::projectFormat()
{
    return projectFormat_;
}

bool project_files::projectCreate(QString name, QString path)
{
    setProjectPath(path);
    setProjectName(name);

    if(isOpened() == true)
    {
        delete projectFile_;
        for(auto it = meas_.cbegin(); it < meas_.cend(); it++)
            delete *it;
        meas_.clear();
        setIsOpened(false);
    }
    QDir dir(projectPath());
    if (!dir.exists()){
        dir.mkdir(".");
    }
    else {
        emit projectCreatedError(QString::fromUtf8("Ошибка при создании проекта. Папка уже существует."));
        return false;
    }
    setProjectName(projectName()+projectFormat());
    projectFile_ = new QSettings(QString(projectPath()+"/"+projectName()), QSettings::IniFormat);
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    projectFile_->setIniCodec(codec);
    if (projectFile_->isWritable() != true)
    {
        emit projectCreatedError(QString::fromUtf8("Ошибка при создании проекта."));
        return false;
    }

    projectFile_->beginGroup("head");
    projectFile_->setValue(QString::fromUtf8("Format"), projectFormat());
    projectFile_->setValue(QString::fromUtf8("Version"), 1.07);
    projectFile_->endGroup();

    projectFile_->beginGroup("time");
    projectFile_->setValue(QString::fromUtf8("Date"), date().toString("dd.MM.yyyy"));
    projectFile_->setValue(QString::fromUtf8("Time"), time().toString("hh:mm:ss.zzz"));
    projectFile_->endGroup();

    projectFile_->beginGroup("tool");
    projectFile_->setValue(QString::fromUtf8("Tool"), tool_type());
    projectFile_->setValue(QString::fromUtf8("Model"), 1.1);
    projectFile_->endGroup();

    projectFile_->beginWriteArray("measurements");
    projectFile_->endArray();

    emit projectCreated(QString::fromUtf8("Проект успешно создан."));
    setIsOpened(true);
    return true;
}

QString project_files::tool_type() const
{
    return tool_type_;
}

void project_files::setTool_type(const QString &tool_type)
{
    tool_type_ = tool_type;
}

QDate project_files::date() const
{
    return date_;
}

void project_files::setDate(const QDate &date)
{
    date_ = date;
}

QTime project_files::time() const
{
    return time_;
}

void project_files::setTime(const QTime &time)
{
    time_ = time;
}

int project_files::addMeasurement(int countTypeModules, int numDnHole, int numUpHole, int timeRec, int timeSwip, QString actionType, QString source, int gainDnHole, int gainUpHole)
{
    if (isOpened() == false)
        return -1;
    if (!projectFile_)
    {
        emit projectCreatedError(QString::fromUtf8("Ошибка при добавлении измерения."));
        return -1;
    }

    int measId = -1;
    int* counter = new int[meas_.size()];
    for(int i = 0; i < meas_.size(); i++)
        counter[i] = 0;
    for(int i = 0; i < meas_.size(); i++)
    {
        int tmp = meas_.at(i)->getId();
        if(tmp >= 0)
            counter[meas_.at(i)->getId()]++;
        else
            return -1;
    }
    for(int i = 0; i < meas_.size(); i++)
        if(counter[i] == 0)
        {
            measId = i;
            break;
        }
    delete[] counter;
    if(measId < 0)
        measId = meas_.size();

    Measurement* tmp = new Measurement(measId, projectName(), numDnHole, numUpHole, timeRec, timeSwip, actionType, source);
    tmp->setPath(projectPath());
    tmp->createDir();
    tmp->createMeasFile();

    meas_.push_back(tmp);
    QFileInfo fi(meas_.last()->path());
    qDebug() << "projectPath" <<meas_.last()->path();    //Это передавать надо будет скорее всего
    emit measPath(measId, meas_.last()->path());
    projectFile_->beginWriteArray("measurements");
    projectFile_->setArrayIndex(measId);
    projectFile_->setValue("PATH", fi.fileName());
    projectFile_->endArray();
    meas_.last()->setCountTypeModules(countTypeModules);
    meas_.last()->setGainDnHoles(gainDnHole);
    meas_.last()->setGainUpHoles(gainUpHole);
    emit projectCreated(QString::fromUtf8("Измерение %1 успешно добавлено.").arg(measId+1));
    connect(meas_.last(),SIGNAL(measCompleted(QString)),this,SLOT(messageFromMeas(QString)));
    connect(meas_.last(),SIGNAL(measError(QString)),this,SLOT(messageFromMeas(QString)));
    connect(meas_.last(),SIGNAL(newTypeCorrelation(int)),this,SLOT(onNewTypeCorrelation(int)));

    meas_.last()->moveToThread(projThread_);
    return meas_.last()->getId();
}
void project_files::setStopTime()
{
    meas_.last()->setTimeStop(QTime::currentTime());
    //this->setIsOpened(false);
}
void project_files::getDataFromFile(int measId, int idRecord, int typeCorrelation)
{
    // qDebug() << "getDataFromFile" << measId << idRecord << typeCorrelation;

    int id = -1;
    for(int i = 0; i < meas_.size(); i++)
    {
        if (meas_.at(i)->getId() == measId){
            id = i;
            break;
        }
    }
    if(id < 0){
        emit finishRead();
        return;
    }
    QString actionType = meas_[id]->getActionType();
    if(typeCorrelation > 0 && actionType == "F"){
        emit finishRead();
        emit projectCreatedError("Для записи со взрывным типом воздействия корреляция не производится! PROJ");
    }
    else{
        disconnect(meas_[id], SIGNAL(newData(int,int,typeModules,universalTemporaryData*)),this, SLOT(onNewData(int,int,typeModules,universalTemporaryData*)));
        connect(meas_[id], SIGNAL(newData(int,int,typeModules,universalTemporaryData*)),this, SLOT(onNewData(int,int,typeModules,universalTemporaryData*)));
        disconnect(meas_[id], SIGNAL(finishRead(int)), this, SLOT(onFinishRead(int)));
        connect(meas_[id], SIGNAL(finishRead(int)), this, SLOT(onFinishRead(int)));
        meas_[id]->readData(idRecord, typeCorrelation);
    }
}

void project_files::getDataFromCalcFile(int measId, int idCalc)
{
    measId--;
    int id = -1;
    for(int i = 0; i < meas_.size(); i++)
    {
        if (meas_.at(i)->getId() == measId){
            id = i;
            break;
        }

    }
    if(id < 0){
        emit finishRead();
        return;
    }
    disconnect(meas_[id], SIGNAL(newData(int,int,typeModules,universalTemporaryData*)),this, SLOT(onNewData(int,int,typeModules,universalTemporaryData*)));
    connect(meas_[id], SIGNAL(newData(int,int,typeModules,universalTemporaryData*)),this, SLOT(onNewData(int,int,typeModules,universalTemporaryData*)));
    disconnect(meas_[id], SIGNAL(finishRead(int)), this, SLOT(onFinishRead(int)));
    connect(meas_[id], SIGNAL(finishRead(int)), this, SLOT(onFinishRead(int)));
    meas_[id]->readCalcData(idCalc);
}

void project_files::addCalculation(int idMeas, QVector<int> listNumbers, int typeCorrelation, QString pathSEGD)
{
    idMeas--;
    if(idMeas < meas_.size()) {
        meas_[idMeas]->newCalculation(listNumbers, typeCorrelation, pathSEGD);
        connect(meas_[idMeas], SIGNAL(stopSpinner(int)), this, SLOT(onStopSpinner(int)));
    }
}

void project_files::addCalculation(QVector<QVector<int> > listNumbers)
{

}

int project_files::getNumDnHoleModules(int idMeas)
{
    idMeas--;
    int id = -1;
    for(int i = 0; i < meas_.size(); i++)
    {
        if (meas_.at(i)->getId() == idMeas){
            id = i;
            break;
        }

    }
    if(id < 0)
        return id;
    return meas_[id]->getNumDnHoleModules();
}

int project_files::getNumUpHoleModules(int idMeas)
{
    idMeas--;
    int id = -1;
    for(int i = 0; i < meas_.size(); i++)
    {
        if (meas_.at(i)->getId() == idMeas){
            id = i;
            break;
        }

    }
    if(id < 0)
        return id;
    return meas_[id]->getNumUpHoleModules();
}

QString project_files::getMeasActionType(int idMeas)
{ 
    idMeas--;
    int id = -1;
    for(int i = 0; i < meas_.size(); i++)
    {
        if (meas_.at(i)->getId() == idMeas){
            id = i;
            break;
        }
    }
    if(id < 0)
        return "";
    return meas_[id]->getActionType();
}

QString project_files::getMeasSourceType(int idMeas)
{
    idMeas--;
    int id = -1;
    for(int i = 0; i < meas_.size(); i++)
    {
        if (meas_.at(i)->getId() == idMeas){
            id = i;
            break;
        }
    }
    if(id < 0)
        return "";
    return meas_[id]->getSource();
}

int project_files::getMeasTimeRecord(int idMeas)
{
    idMeas--;
    int id = -1;
    for(int i = 0; i < meas_.size(); i++)
    {
        if (meas_.at(i)->getId() == idMeas){
            id = i;
            break;
        }
    }
    if(id < 0)
        return -1;
    return meas_[id]->getTimeRecord();
}

int project_files::getMeasTimeSwip(int idMeas)
{
    idMeas--;
    int id = -1;
    for(int i = 0; i < meas_.size(); i++)
    {
        if (meas_.at(i)->getId() == idMeas){
            id = i;
            break;
        }
    }
    if(id < 0)
        return -1;
    return meas_[id]->getTimeSwip();
}

int project_files::getMeasDnHoleGain(int idMeas)
{
    idMeas--;
    int id = -1;
    for(int i = 0; i < meas_.size(); i++)
    {
        if (meas_.at(i)->getId() == idMeas){
            id = i;
            break;
        }
    }
    if(id < 0)
        return -1;
    return meas_[id]->getGainDnHoles();
}

int project_files::getMeasUpHoleGain(int idMeas)
{
    idMeas--;
    int id = -1;
    for(int i = 0; i < meas_.size(); i++)
    {
        if (meas_.at(i)->getId() == idMeas){
            id = i;
            break;
        }
    }
    if(id < 0)
        return -1;
    return meas_[id]->getGainUpHoles();
}

QMap<QString, QString> project_files::getProperties(int idMeas)
{
    QMap<QString, QString> properties;

    idMeas--;
    int id = -1;
    for(int i = 0; i < meas_.size(); i++)
    {
        if (meas_.at(i)->getId() == idMeas){
            id = i;
            break;
        }
    }
//    qDebug() << "show Properties" << idMeas << id;
    if(id < 0)
        return properties;

    properties.insert("NameProj", meas_[id]->getProjectName());
    properties.insert("IdMeas", QString::number(id + 1));

    properties.insert("Date", meas_[id]->getDate().toString("dd/MM/yyyy"));
    properties.insert("Time", meas_[id]->getTime().toString("hh:mm:ss"));

    properties.insert("NumDnHole", QString::number(meas_[id]->getNumDnHoleModules()));
    properties.insert("NumUpHole", QString::number(meas_[id]->getNumUpHoleModules()));

    properties.insert("GateDnHole", QString::number(meas_[id]->getGainDnHoles()));
    properties.insert("GateUpHole", QString::number(meas_[id]->getGainUpHoles()));

    properties.insert("LastMeasPath", meas_[id]->getLastMeasPath());

    QString tmp = meas_[id]->getSource();
    if(tmp == "S")
        properties.insert("SourceStat", "Вкл");
    else if(tmp == "A")
        properties.insert("SourceStat", "Выкл");

    tmp = meas_[id]->getActionType();
    if(tmp == "F")
        properties.insert("SourceType", "Взрывной");
    else if(tmp == "V")
        properties.insert("SourceType", "Вибрационный");

    properties.insert("TimeRecord", QString::number(meas_[id]->getTimeRecord()));
    if(tmp == "V")
        properties.insert("TimeSwip", QString::number(meas_[id]->getTimeSwip()));

    properties.unite(meas_[id]->getServiceInfo());
    return properties;
}

bool project_files::checkData(QString data)
{
    if(data.size() > 0)
        return true;
    else
        return false;
}

bool project_files::open(QString fileName)
{

    if(isOpened() == true)
    {
        delete projectFile_;
        for(auto it = meas_.cbegin(); it < meas_.cend(); it++)
            delete *it;
        meas_.clear();
        setIsOpened(false);
        projectFile_ = new QSettings(fileName, QSettings::IniFormat);
        QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
        projectFile_->setIniCodec(codec);
    }
    else{
        projectFile_ = new QSettings(fileName, QSettings::IniFormat);
    }
    QFileInfo fi(fileName);
    setProjectName(fi.fileName());
    setProjectPath(fi.absolutePath());
    if (projectFile_->status() != QSettings::NoError){
        emit projectCreatedError(QString::fromUtf8("Ошибка при открытии проекта."));
        emit finishRead();
        return false;
    }

    QString tmp;
    projectFile_->beginGroup("head");
    tmp = projectFile_->value(QString::fromUtf8("Format"),"").toString();
    if(checkData(tmp) == true){
        if(this->projectFormat() != tmp){
            emit projectCreatedError("Ошибка при открытии файла проекта! Неверный формат!");
            return false;
        }
    }
    tmp = projectFile_->value(QString::fromUtf8("Version"),"").toString();
    projectFile_->endGroup();

    projectFile_->beginGroup("time");
    tmp = projectFile_->value(QString::fromUtf8("Date"), "").toString();
    tmp = projectFile_->value(QString::fromUtf8("Time"), "").toString();
    projectFile_->endGroup();

    projectFile_->beginGroup("tool");
    tmp = projectFile_->value(QString::fromUtf8("Tool"), "").toString();
    tmp = projectFile_->value(QString::fromUtf8("Model"), "").toString();
    projectFile_->endGroup();


    int countMeas = projectFile_->beginReadArray("measurements");
    QStringList measurements;
    for (int i = 0; i < countMeas; ++i) {
        projectFile_->setArrayIndex(i);
        QString tmpLine = projectFile_->value("PATH","").toString();
        if(tmpLine.size() > 0)
        measurements.push_back(projectPath_ + "/"
                               + tmpLine);
    }

    projectFile_->endArray();
    if(meas_.size() > 0) {
        for(auto it = meas_.cbegin(); it < meas_.cend(); it++)
            delete *it;
        meas_.clear();
    }

    for(int i = 0; i < measurements.size(); i++) {
        Measurement* tmpMeas = new Measurement(measurements.at(i));
        if(QString::compare(projectName(), tmpMeas->getProjectName()) == 0) {
            meas_.push_back(tmpMeas);
            connect(meas_.last(),SIGNAL(measCompleted(QString)), this, SLOT(messageFromMeas(QString)));
            connect(meas_.last(),SIGNAL(measError(QString)), this, SLOT(messageFromMeas(QString)));
            connect(meas_.last(),SIGNAL(newTypeCorrelation(int)),this,SLOT(onNewTypeCorrelation(int)));
        }
    }

    setIsOpened(true);
    this->moveToThread(projThread_);
    emit projectCreated(QString::fromUtf8("Проект %1 успешно открыт!").arg(projectName()));
    emit finishRead();
    return true;
}

bool project_files::isOpened() const
{
    return isOpened_;
}

void project_files::setIsOpened(bool isOpened)
{
    isOpened_ = isOpened;
}

QVector<int> project_files::getVectorIdMeas()
{
    QVector<int> result;
    for (int i = 0; i < meas_.size(); i++) {
        result.push_back(meas_.at(i)->getId()+1);
    }
    return result;
}

QVector<int> project_files::getVectorIdRecords(int idMeas)
{
    QVector<int> result;
    if(meas_.size() < idMeas)
        return result;
    result = meas_[idMeas - 1]->getVectorIdRecords();
    return result;
}

void project_files::onStartedRecord()
{
    // StringList dataFiles
}

void project_files::onStopedRecord()
{

}

void project_files::start()
{
    //connect(transceiver_, SIGNAL(data_update(int,int,TDataPocket)),this, SLOT(onDataUpdate(int,int,TDataPocket)));
    projectFile_ = new QSettings();
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    projectFile_->setIniCodec(codec);
}

void project_files::startStopRecording(bool stat, int measId, int numberRecord, int type, int countModules, universalTemporaryData* data)
{

    if(stat == true) {
        //проверка на существование measID
        for(int i = 0; i < meas_.size(); i++)
            if(meas_[i]->getId() == (measId - 1)){
                //qDebug() << "in addRecordInMeas" << numberRecord_;
                meas_[i]->setNumRecord(numberRecord);
                meas_[i]->createDataFiles(type, numberRecord);
                disconnect(meas_.last(),SIGNAL(finishWriteFile()),this,SLOT(onFinishWriteFile()));
                connect(meas_.last(),SIGNAL(finishWriteFile()),this,SLOT(onFinishWriteFile()));
                meas_[i]->writeData(type, numberRecord, countModules, data);
                return;
            }
    }
    else if (stat == false)
    {

    }
}

void project_files::showProperties(int idMeas)
{
    idMeas--;
    int id = -1;
    for(int i = 0; i < meas_.size(); i++)
    {
        if (meas_.at(i)->getId() == idMeas){
            id = i;
            break;
        }
    }
//    qDebug() << "show Properties" << idMeas << id;
    if(id < 0)
        return;

    QMap<QString, QString> properties;
    properties.insert("NameProj", meas_[id]->getProjectName());
    properties.insert("IdMeas", QString::number(id + 1));

    properties.insert("Date", meas_[id]->getDate().toString("dd/MM/yyyy"));
    properties.insert("Time", meas_[id]->getTime().toString("hh:mm:ss"));

    properties.insert("NumDnHole", QString::number(meas_[id]->getNumDnHoleModules()));
    properties.insert("NumUpHole", QString::number(meas_[id]->getNumUpHoleModules()));

    properties.insert("GateDnHole", QString::number(meas_[id]->getGainDnHoles()));
    properties.insert("GateUpHole", QString::number(meas_[id]->getGainUpHoles()));

    QString tmp = meas_[id]->getSource();
    if(tmp == "S")
        properties.insert("SourceStat", "Вкл");
    else if(tmp == "A")
        properties.insert("SourceStat", "Выкл");

    tmp = meas_[id]->getActionType();
    if(tmp == "F")
        properties.insert("SourceType", "Взрывной");
    else if(tmp == "V")
        properties.insert("SourceType", "Вибрационный");

    properties.insert("TimeRecord", QString::number(meas_[id]->getTimeRecord()));
    if(tmp == "V")
        properties.insert("TimeSwip", QString::number(meas_[id]->getTimeSwip()));

    properties.unite(meas_[id]->getServiceInfo());

    emit updateProperties(properties);
}

void project_files::onUpdateServiceInfo(int idMeas, QMap<QString, QString> serviceInfo)
{
    idMeas--;
    int id = -1;
    for(int i = 0; i < meas_.size(); i++)
    {
        if (meas_.at(i)->getId() == idMeas){
            id = i;
            break;
        }
    }
//    qDebug() << "show Properties" << idMeas << id;
    if(id < 0)
        return;

    meas_[id]->setServiceInfo(serviceInfo);
}

void project_files::messageFromMeas(QString message)
{
    emit projectCreated(message);
}

void project_files::onNewData(const int idMeas, const int idRecord, const typeModules type, universalTemporaryData* data)
{
//    qDebug() << "WORKED";
    Q_UNUSED(idMeas);
    Q_UNUSED(idRecord);
//    for(int i = 0; i < data->allData_list.size(); i++) {
//        for(int j = 0; j < data->allData_list[i]->size(); j++)
//            delete data->allData_list[i]->at(j);
//        delete data->allData_list[i];
//    }
//    data->timeValue.clear();
//    delete data;
    emit newData(type, data);
}

//void project_files::onNewCalcData(const int idMeas, const int idRecord, const typeModules type, QVector<QVector<double> > data)
//{
//    Q_UNUSED(idMeas);
//    Q_UNUSED(idRecord);
//    emit newCalcData(type, data);
//    emit finishRead();
//}

void project_files::onFinishRead(int id)
{
    disconnect(meas_[id], SIGNAL(newData(int,int,typeModules,universalTemporaryData*)),this, SLOT(onNewData(int,int,typeModules,universalTemporaryData*)));
    disconnect(meas_[id], SIGNAL(finishRead(int)), this, SLOT(onFinishRead(int)));
    emit finishRead();
}

void project_files::onStopSpinner(int idMeas)
{
    int id = -1;
    for(int i = 0; i < meas_.size(); i++)
    {
        if (meas_.at(i)->getId() == idMeas){
            id = i;
            break;
        }
    }
    if(id < 0)
        return;
    else {
        emit stopSpinner();
        disconnect(meas_[id], SIGNAL(stopSpinner(int)), this, SLOT(onStopSpinner(int)));
    }
}

void project_files::onNewTypeCorrelation(int typeCorrelation)
{
    emit updateTypeCorrelation(typeCorrelation);
    //qDebug() << "new Type PROJ" << typeCorrelation;
}

void project_files::onFinishWriteFile()
{
    emit finishWriteFile();
}
