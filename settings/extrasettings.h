#ifndef EXTRASETTINGS_H
#define EXTRASETTINGS_H

#include <QWidget>
#include "checkboxincombowidget.h"
#include <QSettings>
#include <QDebug>
#include <QDir>
#include <tuple>
#include <QMessageBox>

namespace Ui {
class ExtraSettings;
}

typedef struct
{
    QMap<int,QVector<bool>> mapInversModules;
    std::vector<std::tuple<int,int,int>> vecGainDwnModules;
    std::vector<int> vecGainGroundModules;
}inversAndGainValue;

typedef enum {
    gainDwnHoleModules = 0,
    gainGroundHoleModules = 1,
    inversDwnModules = 2,
    inversDwnChannels = 3,
    inversGroundModules = 4,
    inversGroundChannels = 5,
    gainDwnHoleChannels = 6,
    gainGroundHoleChannels = 7,
    count = 8
}typeComboBox;

class ExtraSettings : public QWidget
{
    Q_OBJECT
    using axis = std::tuple<int,int,int>;
    enum channel{
        x = 0,
        y = 1,
        z = 2
    };

public:
    explicit ExtraSettings(int numDnMod, int numWellsMod, QWidget *parent = 0);
    ~ExtraSettings();
    void setDir(const QDir &dir);

private:
    Ui::ExtraSettings *ui;
    CheckBoxInComboWidget *createAndFillItemsBox(typeComboBox type,  int num);
    CheckBoxInComboWidget *fillChannelsBox(typeComboBox type);
    int numDnMod_;
    int numWellsMod_;
    QSettings* settings_;
    const QString fileName_ = "additionalSettings.conf";
    QDir dir_;

    QMap<int,CheckBoxInComboWidget*> mapComboWidgets_;
    QMap<int,QVector<bool>> mapSelectedValue_;
    inversAndGainValue inversAndGainValue_;
    void readSettings();
    void writeSettings();
    int minIntGround = -65536;

signals:
    void inversAndGainChannels(const inversAndGainValue);

private slots:
  void on_saveAndCloseButton_clicked();
  void on_readSettingsFileButton_clicked();
};

#endif // EXTRASETTINGS_H
