#ifndef CORRELATION_H
#define CORRELATION_H

/*
 * Класс корреляции
*/


#include <QObject>
#include <QVector>
#include <QList>
#include <correlation/fft/qfouriertransformer.h>
#include <QTime>

class Correlation : public QObject
{
    Q_OBJECT

public:
    Correlation(int id, int typeCorrelation, qint32 *firstArr, int N, qint32 *secArr, int M, QObject *parent = nullptr);
    ~Correlation();

    int id() const;
    void setId(int id);

    qint32 *result() const;

    int typeCorrelation() const;
    void setTypeCorrelation(int typeCorrelation);

    void setMaxValFirstArray(const qint32 &maxValFirstArray);
    void setLevels(int levels);

signals:
    void convCompleted(int id, qint32* result, int size, int maxElement);
    void stopThread();

public slots:
    void run();
    void stop();
    void startCalcCorrelation();

private:
    //double *conv(double * x, int N, double * h, int M);
    int id_;
    //взаимная корреляция в спектральной области
    void conv(qint32 *x, int N, qint32 *h, int M);
    void conv_fft(qint32 *x, int N, qint32 *h, int M);

    //взаимная корреляция во временной области
    void conv2(qint32 *x, int N, qint32 *h, int M);

    qint32* firstArr_;
    qint32 maxValFirstArray_ = -1;
    int firstArrSize_;
    int secArrSize_;
    int typeCorrelation_;
    qint32* secArr_;
    qint32* result_;
    static const int quantizationLevels_ = 1000;
    int levels_ = -1;
//    static const int quantizationOutLevels_ = 1000;

    double coef_;
};

#endif // CORRELATION_H
