#ifndef CORRELATIONMANAGER_H
#define CORRELATIONMANAGER_H

/*
 * Класс для выполенения корреляции
*/

#include <QObject>
#include <QVector>
#include <QThread>
#include <QThreadPool>
#include <QMutex>

#include "network/declarateTransceiveringData.h"
#include "correlation/correlation.h"
#include "correlation2.h"

struct dataForCorrelationInt64 {
    typeModules type;
    int id;
    qint64* dataOrig;
    int sizeArrOrig;
    qint64* dataCrossCorrelation;
    int sizeCrossCorrelation;
    bool isSweep;
    bool isCompleted;
    double coef;
    qint64  maxValue;
};

enum maxValues{
    MAX_VALUE_DN_HOLE = (1 << 24),
    MAX_VALUE_UP_HOLE = (1 << 16),
    MAX_VALUE_SYNC = (1 << 12)
};

class CorrelationManager : public QObject
{
    Q_OBJECT

public:
    CorrelationManager(int typeInt64or32, QObject *parent = nullptr);
    ~CorrelationManager();
    void addChannels(typeModules type, universalTemporaryData* data);

    void setReadFileNames(const QStringList &readFileNames);

    void setTypeCorrelation(int typeCorrelation);

    int timeRecord() const;
    void setTimeRecord(int timeRecord);

    int timeSwip() const;
    void setTimeSwip(int timeSwip);

    int idRecord() const;
    void setIdRecord(int idRecord);

    int typeInt64or32() const;
    void setTypeInt64or32(int typeInt64or32);

private:
    QVector<dataForCorrelationInt64*> channelsInt64_;
    int counter_;
    QVector<int> minIdTypes_;
    QVector<QVector<int>> timeDataDnHole_;
    QVector<QVector<int>> timeDataSync_;
    QVector<QVector<int>> timeDataUpHole_;
    bool isDnHoleDataExists_;
    bool isSyncDataExists_;
    QStringList readFileNames_;
    int typeCorrelation_;
    int timeRecord_;
    int timeSwip_;
    int idRecord_;
    static const int quantizationLevels_ = 1000;
    static const int quantizationLevelsUpHole_ = ((1 << 16) - 1);
    static const int quantizationLevelsSync_ = ((1 << 12) - 1);
    static const int quantizationLevelsDnHole_ = ((1 << 23) - 1);
    QString fileName_;
    int typeInt64or32_;

private slots:
    void onConvCompletedInt64(int id, qint64 *result, int size, qint64 maxElement);

    void sendCorrelationData();
    void startCrossCorrelation();
//    void startCorrelation2();

signals:
    void correlationCompleted(int, typeModules, universalTemporaryData*);
    void allCorrelationCompleted();
    void readyDraw(int idRec);
    void stopThread();

public slots:
    void run();
    void stop();
    void onFinishReadFile(QString fileName, universalTemporaryData *data);
    void onFinishReadCalc(QString dataFileName, QVector<int> types, QVector<universalTemporaryData*> data);
};

#endif // CORRELATIONMANAGER_H
