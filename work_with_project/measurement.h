#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QTextStream>
#include <QDate>
#include <QTime>
#include <QDataStream>
#include <QThread>
#include <QSettings>
#include "network/declarateTransceiveringData.h"
//#include "network/transceiver_class.h"

class Measurement : public QObject
{
    Q_OBJECT
public:
    explicit Measurement(int id, QString projectName, int numDNHole, int numUpHole, int timeRec, int timeSwip, QString actionType, QString source, QObject *parent = nullptr);
    explicit Measurement(QString inPath, QObject *parent = nullptr);
    ~Measurement();

    QString path() const;
    void setPath(const QString &path);

    void createDir();
    void createMeasFile();

    int getId() const;
    void setId(int value);

    QString getMeasFileFormat() const;

    QString getProjectName() const;
    void setProjectName(const QString &projectName);

    QDate getDate() const;
    void setDate(const QDate &date);

    QTime getTime() const;
    void setTime(const QTime &time);

    void createDataFiles(int type, int numRecord);

    int getCountTypeModules() const;
    void setCountTypeModules(int countModules);
    QVector<int> getVectorIdRecords();
    void setNumRecord(int numberRecord);
    void writeData(const int type, int numberRecord, int countModules, universalTemporaryData *data);

    void readData(const int idRecord, int typeCorrelation);

    void openDataFiles();
    void deleteSyncFile();
    void deleteModFile();

    void newCalculation(QVector<int> listNumbers, int typeCorrelation, QString pathSEGD);
    void readCalcData(int calcId);

    int getNumDnHoleModules() const;
    int getNumUpHoleModules() const;

    int getTimeRecord() const;
    void setTimeRecord(int timeRecord);

    void setTimeStop(const QTime &time);
    QTime getTimeStop() const;
    void setTimeStart(const QTime &time);
    QTime getTimeStart() const;

    int getTimeSwip() const;
    void setTimeSwip(int timeSwip);

    QString getActionType() const;
    void setActionType(const QString &actionType);

    QString getSource() const;
    void setSource(const QString &source);

    int getGainDnHoles() const;
    void setGainDnHoles(int gainDnHoles);

    int getGainUpHoles() const;
    void setGainUpHoles(int gainUpHoles);

    void setServiceInfo(QMap<QString, QString> serviceInfo);
    QMap<QString, QString> getServiceInfo();

    QString getLastMeasPath() const;
    void setLastMeasPath(const QString &lastMeasPath);

    int getAccamulation() const;
    void setAccamulation(int accamulation);

    QString getDistBtwDevices() const;
    void setDistBtwDevices(QString distBtwDevices);

private:
    int id;
    QString path_; //относительно проекта
    QSettings* measFile_;
    int numberRecord_;
    const QString measFileFormat_ = ".meas";
    QString projectName_;
    QDate date_;
    QTime time_;
    int countTypeModules_ = 5;
    int gId_;
    QVector<QThread*> writeFileThreads_;
    QStringList readFileNames_;
    int readFileCalcCounter_;
    int countCalculationFiles_;
    int numDnHoleModules_;
    int numUpHoleModules_;
    int timeRecord_;
    int timeSwip_;
    bool isFinishCalc_;
    bool isFinishSEGD_;
    QString actionType_;
    QString source_;
    int gainDnHoles_;
    int gainUpHoles_;

    QString depth_;
    QString nameOperator_;
    QString numHole_;
    QString nameArea_;
    QString lastMeasPath_;

    bool checkReadedData(QString data);
    int accamulation_ = 0;
    QString distBtwDevices_;

signals:
    void measCompleted(QString mesg);
    void measError(QString mesg);
    void newData(int,int,typeModules,universalTemporaryData*);
//    void newCalcData(int,int,typeModules,universalTemporaryData*);
    void finishRead(int id);
    void writeFile(QString, int, universalTemporaryData*);
    void readFile(QString);
    void stopSpinner(int);
    void newTypeCorrelation(int );
    void finishWriteFile();

private slots:
    void onFinishReadFile(QString fileName, universalTemporaryData* data);
    void onFinishReadCalcFile(QString fileName, int type , universalTemporaryData* data, int typeCorrelation);
    void onFinishCalc(QString msg);
    void onFinishCalcSEGD();
    void onCorrelationCompleted(int idRecord, typeModules type, universalTemporaryData*data);
    void onFinishCorr(int idRecord);
    void onFinishWriteFile();

};
Q_DECLARE_METATYPE (QVector<int>)
#endif // MEASUREMENT_H
