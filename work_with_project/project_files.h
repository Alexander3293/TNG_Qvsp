#ifndef PROJECT_FILES_H
#define PROJECT_FILES_H

#include <QObject>
#include <QFile>
#include <QFileDialog>
#include <QInputDialog>
#include <QDate>
#include <QTime>
#include <work_with_project/measurement.h>
#include <QVector>
#include <QDataStream>
#include <QSettings>
#include "network/declarateTransceiveringData.h"
#include "network/transceiver_class.h"
#include "network/syncmoduletranciever.h"
#include "work_with_project/measurementproperties.h"
#include "work_with_project/measurement.h"

class project_files : public QObject
{
    Q_OBJECT
public:
    explicit project_files(QThread* projThread, QObject *parent = nullptr);
    ~project_files();

    QString projectName() const;
    void setProjectName(const QString &projectName);

    QString projectPath() const;
    void setProjectPath(const QString &projectPath);

    QString projectFormat();

    bool projectCreate(QString name, QString path);

    QString tool_type() const;
    void setTool_type(const QString &tool_type);

    QDate date() const;
    void setDate(const QDate &date);

    QTime time() const;
    void setTime(const QTime &time);

    bool open(QString fileName);

    bool isOpened() const;
    void setIsOpened(bool isOpened);
    QVector<int> getVectorIdMeas();
    QVector<int> getVectorIdRecords(int idMeas);
//  QStringList getDataFilesName(Measurement* meas);
//  Measurement *getMeasurement(int id);
//  Measurement *getMeasurement(QString name);
    SyncModuleTranciever* syncModule_;
    int addMeasurement(int countTypeModules, int numDnHole, int numUpHole, int timeRec, int timeSwip, QString actionType, QString source, int gainDnHole, int gainUpHole);

    void getDataFromFile(int measId, int idRecord, int typeCorrelation);
    void getDataFromCalcFile(int measId, int idCalc);

    void addCalculation(int idMeas , QVector<int> listNumbers, int typeCorrelation, QString pathSEGD);
    void addCalculation(QVector<QVector<int>> listNumbers);

    int getNumDnHoleModules(int idMeas);
    int getNumUpHoleModules(int idMeas);

    QString getMeasActionType(int idMeas);
    QString getMeasSourceType(int idMeas);
    int getMeasTimeRecord(int idMeas);
    int getMeasTimeSwip(int idMeas);
    int getMeasDnHoleGain(int idMeas);
    int getMeasUpHoleGain(int idMeas);
    QMap<QString, QString> getProperties(int idMeas);
    void setStopTime();

private:
    QString projectName_;
    QString projectPath_;
    const QString projectFormat_ = QString::fromUtf8(".projgis");
    QSettings   *projectFile_;
    QVector<Measurement*> meas_;

    QString tool_type_;
    QDate date_;
    QTime time_;
    bool isOpened_;
    QThread* projThread_;

    bool checkData(QString data);

signals:
    void projectCreated(QString projectName);
    void projectCreatedError(QString error);
    void newData(const typeModules type, universalTemporaryData* data);
    void newCalcData(const typeModules type, QVector<QVector<double>> data);
    void finishRead();
    void stopSpinner();
    void updateTypeCorrelation(int typeCorrelation);
    void finishWriteFile();
    void updateProperties(QMap<QString, QString>);
    void measPath(int idMeas, QString path);

public slots:
    void onStartedRecord ();
    void onStopedRecord ();
    void start();
    void startStopRecording(bool stat, int measId, int numberRecord, int type, int countModules, universalTemporaryData *data);
    void showProperties(int idMeas);
    void onUpdateServiceInfo(int idMeas, QMap<QString,QString> serviceInfo);

private slots:
    void messageFromMeas (QString message);
    void onNewData(const int idMeas, const int idRecord, const typeModules type, universalTemporaryData* data);
//    void onNewCalcData(const int idMeas, const int idRecord, const typeModules type, QVector<QVector<double>> data);

    void onFinishRead(int id);
    void onStopSpinner(int idMeas);
    void onNewTypeCorrelation(int typeCorrelation);
    void onFinishWriteFile();
};
Q_DECLARE_METATYPE(QVector<universalTemporaryData*>)
#endif // PROJECT_FILES_H
