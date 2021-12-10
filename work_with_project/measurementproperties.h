#ifndef MEASUREMENTPROPERTIES_H
#define MEASUREMENTPROPERTIES_H

#include <QMap>
#include <QWidget>

namespace Ui {
class MeasurementProperties;
}

class MeasurementProperties : public QWidget
{
    Q_OBJECT

public:
    explicit MeasurementProperties(QWidget *parent = nullptr);
    ~MeasurementProperties();
    void updateProperties(int idMeas);

    int lastIdMeas() const;
    void setLastIdMeas(int lastIdMeas);

private:
    Ui::MeasurementProperties *ui;
    int lastIdMeas_;

    void setStyleAllSheet();

    QString depth_ = "";
    QString operator_ = "";
    QString numHole_ = "";
    QString nameArea_ = "";
    QString distBtwDevices_ = "";

public slots:
    void onUpdateProperties(QMap<QString, QString> properties);

signals:
    void readyUpdateProperties(int);
    void updateServiceInfo(int, QMap<QString,QString>);

private slots:
    void on_pushButtonChange_clicked();
    void on_pushButtonSave_clicked();
};

#endif // MEASUREMENTPROPERTIES_H
