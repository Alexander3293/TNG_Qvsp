#ifndef CORRELATION2_H
#define CORRELATION2_H

/*
 * Класс корреляции
*/

#include <QObject>
#include "correlation/fft/qfouriertransformer.h"
#include <QRunnable>
#include <QDebug>

class Correlation2 : public QObject, public QRunnable
{
    Q_OBJECT

public:
    Correlation2(int id, int typeCorrelation, qint64 *firstArr, int N, qint64 *secArr, int M, QObject *parent = nullptr);
    //~Correlation2();

    int id() const;
    void setId(int id);

    qint64 *result() const;

    int typeCorrelation() const;
    void setTypeCorrelation(int typeCorrelation);

    void setLevels(int levels);

    void run() override;

signals:
    void convCompleted(int id, qint64* result, int size, qint64 maxElement);
    void stopThread();

public slots:
    void stop();
    void startCalcCorrelation();

private:
    //double *conv(double * x, int N, double * h, int M);
    int id_;
    void conv(qint64* x, int N, qint64* h, int M); //cross-correlation
    void conv_fft(qint64 *x, int N, qint64 *h, int M); //cross-correlation fft
    void conv2(qint64 *x, int N, qint64 *h, int M); //correlation_2

    qint64* firstArr_;
    int firstArrSize_;
    int secArrSize_;
    int typeCorrelation_;
    qint64* secArr_;
    qint64* result_;
//    static const int quantizationLevels_ = 1000;
//    static const int quantizationOutLevels_ = ((1 << 23) - 1);
    int levels_ = -1;

};

#endif // CORRELATION2_H
