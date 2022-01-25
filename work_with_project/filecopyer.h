#ifndef FILECOPYER_H
#define FILECOPYER_H

/* Класс обработки SEGD в потоке */

#include <QObject>
#include <QThread>
#include <QDebug>
#include "work_with_project/createproject.h"
#include "work_with_project/project_files.h"
#include "work_with_project/single_segd_rev2_files.h"
class FileCopyer : public QObject
{
    Q_OBJECT
    //explicit FileCopyer();
public:
    QString meas_file;
signals:
    void resultReady(bool result);
public slots:
    void startThread(QString fileName);
};

#endif // FILECOPYER_H
