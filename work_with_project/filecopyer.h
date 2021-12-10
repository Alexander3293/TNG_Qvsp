#ifndef FILECOPYER_H
#define FILECOPYER_H

#include <QObject>
#include <QVector>
class FileCopyer : public QObject
{
    Q_OBJECT
public:
    FileCopyer(QThread*);
    ~FileCopyer();
    static const int DEFAULT_CHUNK_SIZE = 1024 * 1024 * 1;

    qint64 chunkSize() const {
        return _chunk;
    }
    void setChunkSize(qint64 ch) {
        _chunk = ch;
    }

    QVector<QString> sourcePaths() const {
        return src;
    }
    void setSourcePaths(const QVector<QString>& _src) {
        src = _src;
    }

    QVector<QString> destinationPaths() const {
        return dst;
    }
    void setDestinationPaths(const QVector<QString>& _dst) {
        dst = _dst;
    }

    void interrupt()
    {
        _interrupt = true;
    }
private:
    QVector<QString> src, dst;
    qint64 _chunk;
    bool _interrupt;

protected slots:
    void copy();

signals:
    void copyProgress(qint64 bytesCopied, qint64 bytesTotal);
    void finished(bool success);
    void oneBegin(QString srcFileName);
    void oneFinished(QString dstPath, bool result);

};

#endif // FILECOPYER_H
