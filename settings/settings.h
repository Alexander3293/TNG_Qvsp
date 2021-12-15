#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDir>
#include <QLineEdit>
#include <QSettings>
#include <QWidget>
#include "extrasettings.h"
#include <QTimer>
#include <QDebug>
#include <QTextCodec>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

    int numDnMod() const;

    int numWellsMod() const;

    int timeRecord() const;

    int countRecord() const;

    int timeWaiting() const;

    void setPosition(QPoint pos);

    QString syncCMD() const;

    QString syncChannel() const;

    QString corrSave() const;
    void setCorrSave(const QString &corrSave);

    QString corrDraw() const;

    int swipLen() const;

    QString depth() const;
    void setDepth(const QString &depth);

    QString numHole() const;
    void setNumHole(const QString &numHole);

    QString nameArea() const;
    void setNameArea(const QString &nameArea);

    QString operatorName() const;
    void setOperatorName(const QString &operatorName);

    bool isDefaultSavingPath() const;
    void setIsDefaultSavingPath(bool isDefaultSavingPath);

    bool isPaintZeroLines() const;
    void setIsPaintZeroLines(bool isPaintZeroLines);

    QString distBtwDevices() const;
    void setDistBtwDevices(const QString &distBtwDevices);

    int offsetDnHoleModemOn() const;
    void setOffsetDnHoleModemOn(int offsetDnHoleModemOn);

    int offsetDnHoleModemOff() const;
    void setOffsetDnHoleModemOff(int offsetDnHoleModemOff);

    int globalOffsetDnHole();
    int globalOffsetUpHole();

    int offsetUpHole() const;
    void setOffsetUpHole(int offsetUpHole);

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_toolButtonNumDnModMin_clicked();
    void on_toolButtonNumDnModPlus_clicked();
    void on_toolButtonNumWellsModMin_clicked();
    void on_toolButtonCountRecordMin_clicked();
    void on_toolButtonCountRecordPlus_clicked();
    void on_toolButtonNumWellsModPlus_clicked();
//    void on_comboBoxCMD_currentIndexChanged(int index);
    void on_comboBoxChannel_currentTextChanged(const QString &arg1);
    void on_comboBoxCorDraw_currentIndexChanged(const QString &arg1);
    void on_extraSettingsButton_clicked();
    void on_comboBoxChannel_currentIndexChanged(const QString &arg1);
    void on_startDwnHoleButton_clicked();
    void on_startUpHoleButton_clicked();
    void on_stopUpHoleButton_clicked();
    void on_buttonStopSync_clicked();
    void on_checkBoxSaveMod_stateChanged(int arg1);
    void on_checkBoxZeroLines_stateChanged(int arg1);
    void on_checkBoxModem_stateChanged(int arg1);
    void on_lineEditNumDnMod_textEdited(const QString &arg1);
    void on_startSyncButton_clicked();

    void on_pb_search_ground_clicked();

private:
    Ui::Settings *ui;
    void setStyleTextSheet();
    int numDnMod_;
    int numWellsMod_;
    int timeRecord_;
    int countRecord_;
    int timeWaiting_;
    int swipLen_;
    QString syncCMD_;
    QString syncChannel_;
    QSettings* settings_;
    QDir dir_;
    QTimer timerStartUpHole_;
    const QString fileName_ = "settings.conf";
    void readSettings();
    void writeSettings();
    QLineEdit* lineEditTimeRecord_;
    QLineEdit* lineEditTimeWaiting_;
    QLabel* labelSaveMod_;
    QString editVal(bool flag, QString inVal);
    QString corrSave_;
    QString corrDraw_;
    QString depth_;
    QString operatorName_;
    QString numHole_;
    QString nameArea_;
    QString distBtwDevices_;
    ExtraSettings* extraSettings_;
    QString detonationSource = "Взрывной";
    QString vibroSource = "Вибро";
    QString cmdS = "Вкл";
    QString cmdA = "Выкл";
    bool isDefaultSavingPath_ = false;
    bool isPaintZeroLines_ = false;
    bool isModemOn_ = false;
    int offsetDnHoleModemOn_ = 10;
    int offsetDnHoleModemOff_ = 13;
    int offsetUpHole_ = -10;

public slots:
    void onUpdateParametres();
    void setCorrDraw(const QString &corrDraw);

signals:
    void errorMsg(QString);
    void updateSettings();
    void startDwnHole();
    void startGround();
    void startSync(const QString, const QString);
    void stopGround();
    void searchGround();
    void inversAndGainChannels(const inversAndGainValue);
    void stopSync();
};

#endif // SETTINGS_H
