#include "correlation2.h"

Correlation2::Correlation2(int id, int typeCorrelation, qint64 *firstArr, int firstArrSize, qint64 *secArr, int secArrSize,  QObject *parent) : QObject(parent)
{
    //qDebug() << "INIT" << this->thread();
    setId(id);
    firstArrSize_ = firstArrSize;
    secArrSize_ = secArrSize;
    firstArr_ = new qint64[firstArrSize_];
    memcpy(firstArr_, firstArr, sizeof(quint64)*static_cast<unsigned int>(firstArrSize_));
    secArr_ = new qint64[secArrSize_];
    memcpy(secArr_, secArr, sizeof(quint64)*static_cast<unsigned int>(secArrSize_));
    this->typeCorrelation_ = typeCorrelation;
}

//Correlation2::~Correlation2()
//{
//    //qDebug() << "очистка";
//    if(result_ != nullptr)
//        delete []  result_;
//    if(firstArr_ != nullptr)
//        delete []  firstArr_;
//    if(secArr_ != nullptr)
//        delete []  secArr_;
//}

void Correlation2::run()
{
    //qDebug() << "run" << this->thread() << QString::number(this->id_) << QString::number(firstArrSize_) << QString::number(secArrSize_);
    //qDebug() << (result_ == NULL) << (result_ == nullptr);
    if(!result_)
        delete [] result_;
    double meanVal = 0.0;
    for (int i = 0; i < secArrSize_; i++) {
        meanVal += (double)(secArr_[i]) / secArrSize_;
    }
    for (int i = 0; i < secArrSize_; i++) {
        secArr_[i] -= meanVal;
    }
    switch (typeCorrelation_) {
    case 1:{
        if(firstArrSize_ > 0 || secArrSize_ > 0) {
//            result_ = new double[firstArrSize_ + secArrSize_ - 1];
            result_ = new qint64[qMin(firstArrSize_, secArrSize_)];
//            for (int i = 0; i < secArrSize_ / 2; i++) {
//                double temp = secArr_[i];
//                secArr_[i] = secArr_[secArrSize_ - 1 - i];
//                secArr_[secArrSize_ - 1 - i] = temp;
//            }

            //conv(firstArr_, firstArrSize_, secArr_, secArrSize_);
            conv_fft(firstArr_, firstArrSize_, secArr_, secArrSize_);
        }
        break;
    }

    case 2:{
        if(firstArrSize_ > 0 || secArrSize_ > 0) {
            if(secArrSize_ < firstArrSize_) {
                result_ = new qint64[firstArrSize_ - secArrSize_];
//                for (int i = 0; i < secArrSize_ / 2; i++) {
//                    double temp = secArr_[i];
//                    secArr_[i] = secArr_[secArrSize_ - 1 - i];
//                    secArr_[secArrSize_ - 1 - i] = temp;
//                }
            }
            else if(secArrSize_ >= firstArrSize_) {
                result_ = new qint64[secArrSize_ - firstArrSize_];
//                for (int i = 0; i < firstArrSize_ / 2; i++) {
//                    double temp = firstArr_[i];
//                    firstArr_[i] = firstArr_[firstArrSize_ - 1 - i];
//                    firstArr_[firstArrSize_ - 1 - i] = temp;
//                }
            }
            conv2(firstArr_, firstArrSize_, secArr_, secArrSize_);
        }
        break;
    }

    default:
        break;

        //qDebug() << "END run" << QString::number(this->id_) << QString::number(firstArrSize_) << QString::number(secArrSize_);
    }
    emit stopThread();
}

void Correlation2::stop()
{
    //    if(result_ != nullptr)
    //        delete []  result_;
    if(firstArr_ != nullptr)
        delete []  firstArr_;
    if(secArr_ != nullptr)
        delete []  secArr_;
}

void Correlation2::startCalcCorrelation()
{

}

qint64 *Correlation2::result() const
{
    return result_;
}

int Correlation2::id() const
{
    return id_;
}

void Correlation2::setId(int id)
{
    id_ = id;
}

//double *Correlation::conv(double *x, int N, double *h, int M)
//{
//    double * result = new double[N + M - 1];
//    memset(result, 0, sizeof(double) * (N + M - 1));

//    for (int i = 0; i < N + M - 1; i++)
//    {
//        for (int j = 0; j < i + 1; j++)
//        {
//            double val = 0;
//            if(i-j >= 0)
//                val = h[i-j];
//            double val2 = 0;
//            if(N > j)
//                val2 = x[j];
//            result[i] += val2 * val;
//        }
//    }
//    return result;
//}

void Correlation2::conv(qint64 *x, int N, qint64 *h, int M)
{
    //qDebug() << "CONV" << QString::number(this->id_) << QString::number(firstArrSize_) << QString::number(secArrSize_);

    memset(result_, 0, sizeof(quint64) * static_cast<unsigned int>(N + M - 1));

    for (int i = 0; i < N + M - 1; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            qint64 val = 0;
            if(i-j >= 0 && i-j < M)
                val = h[i-j];
            qint64 val2 = 0;
            if(N > j)
                val2 = x[j];
            result_[i] += val2 * val;
        }
    }
    //qDebug() << "END CONV" << QString::number(this->id_) << QString::number(firstArrSize_) << QString::number(secArrSize_);
    //norm
    quint64 tmpMax = 0;
    for(int i = 0; i < N + M - 1; i++){
       if(qAbs(result_[i]) > tmpMax)
           tmpMax = qAbs(result_[i]);
    }
    quint64 coef = static_cast<quint64>(levels_) / qAbs((tmpMax));
    for(int i = 0; i < N + M - 1; i++){
        result_[i] = result_[i] * coef;
    }
    emit convCompleted(id(), result_, N + M - 1, static_cast<qint64>(tmpMax));
}

void Correlation2::conv_fft(qint64 *x, int N, qint64 *h, int M)
{
    int minSizeArr = qMin(N,M);
    //рассчитать размер по степени 2

    int tmpSize = 1;
    while (tmpSize < minSizeArr) {
        tmpSize *= 2;
    }

    float xFFT[tmpSize], hFFT[tmpSize], arrTmp[tmpSize];
    for(int i = 0; i < minSizeArr; i++){
        arrTmp[i] = static_cast<float>(x[i]);
    }
    for(int i = minSizeArr; i < tmpSize; i++)
        arrTmp[i] = static_cast<float>(0);

    QFourierTransformer transformer;
    if(transformer.setSize(tmpSize) == QFourierTransformer::InvalidSize){
        emit convCompleted(id(), x, N, -1);
        //qDebug() << "size FFT error" << minSizeArr << N << M;
        return;
    }

    if(transformer.setWindowFunction("Hamming") == false){
        emit convCompleted(id(), x, N, -1);
        return;
    }
    //qDebug() << "size FFT OK" << minSizeArr << N << M;
    transformer.forwardTransform(arrTmp, xFFT);

    for(int i = 0; i < minSizeArr; i++){
        arrTmp[i] = static_cast<float>(h[i]);
    }
    for(int i = minSizeArr; i < tmpSize; i++){
        arrTmp[i] = 0.0;
    }

    transformer.forwardTransform(arrTmp, hFFT);

    transformer.conjugate(xFFT);

    for(int i = 0; i < tmpSize; i++)
        arrTmp[i] = 0;

    //произведение complex num
    tmpSize = tmpSize / 2 + 1;
    for(int i = 0; i < minSizeArr / 2 + 1; i++) {
        arrTmp[i] = xFFT[i] * hFFT[i] - xFFT[i + tmpSize] * hFFT[i + tmpSize];
        arrTmp[i + tmpSize] = xFFT[i] * hFFT[i + tmpSize] + xFFT[i + tmpSize] * hFFT[i];
    }

    transformer.inverseTransform(arrTmp, xFFT);

//    result_ = new qint32 [minSizeArr];
    float tmpMax = 0.0;

    for(int i = 0; i < minSizeArr; i++){
       if(qAbs(xFFT[i]) > tmpMax)
           tmpMax = qAbs(xFFT[i]);
    }
//    float coef = static_cast<float>(levels_) / tmpMax;
//    for(int i = 0; i < minSizeArr; i++){
//        xFFT[i] = xFFT[i] * coef;
//    }

    for(int i = 0; i < minSizeArr; i++)
        result_[i] = static_cast<qint64>(xFFT[i]);

    emit convCompleted(id(), result_, minSizeArr, static_cast<qint64>(tmpMax));
}


void Correlation2::conv2(qint64 *x, int N, qint64 *h, int M)
{
    //qDebug() << "CONV" << QString::number(this->id_) << QString::number(firstArrSize_) << QString::number(secArrSize_);
    int resSize = qMax(N,M) - qMin(N,M);
    int countIters = qMin(N,M);
    memset(result_, 0, sizeof(qint64) * static_cast<unsigned int>(resSize));
    if(N > M){
        for (int i = 0; i < resSize; i++)
        {
            for(int j = 0; j < countIters; j++){
                result_[i] += h[j] * x[i+j];
            }
        }
    }
    else if(N <= M){
        for (int i = 0; i < resSize; i++)
        {
            for(int j = 0; j < countIters; j++){
                result_[i] += x[j] * h[i+j];
            }
        }
    }
    //qDebug() << "END CONV" << QString::number(this->id_) << QString::number(firstArrSize_) << QString::number(secArrSize_);
    qint64 tmpMax = 0;
    for(int i = 0; i < resSize; i++){
       if(qAbs(result_[i]) > tmpMax)
           tmpMax = qAbs(result_[i]);
    }

//    long double coef = static_cast<long double>(levels_) / tmpMax;
//    for(int i = 0; i < resSize; i++){
//        result_[i] *= coef;
//    }

//    qint64 outTest = 0;
//    for(int i = 0; i < resSize; i++){
//        if(outTest < result_[i])
//            outTest = result_[i];
//    }
//    qWarning() << "Size" << id_ << outTest << tmpMax;
    emit convCompleted(id(), result_, resSize, static_cast<qint64>(tmpMax));
}

void Correlation2::setLevels(int levels)
{
    levels_ = levels;
}

int Correlation2::typeCorrelation() const
{
    return typeCorrelation_;
}

void Correlation2::setTypeCorrelation(int typeCorrelation)
{
    typeCorrelation_ = typeCorrelation;
}
