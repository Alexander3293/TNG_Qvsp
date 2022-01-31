#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

/*User Includes*/
#include "qcustomplot/graphground.h"
#include "qcustomplot/graphsync.h"
#include "qcustomplot/graphdownhole.h"
#include "qcustomplot/paintlegend.h"            //Отрисовка legend
#include  "qcustomplot/plotdoublegraph.h"
#include  "qcustomplot/test.h"
#include "work_with_powerSupply/powerdevices.h"
#include "work_with_powerSupply/powersupplycontroller.h"

#include "network/transceiver_class.h"
#include "network/transceiver_ground.h"
#include "network/syncmoduletranciever.h"
#include "work_with_project/createproject.h"
#include "work_with_project/project_files.h"
#include "work_with_project/single_segd_files.h"
#include "work_with_project/single_segd_rev2_files.h"
#include <QFile>
#include <QButtonGroup>
#include "settings/settings.h"
#include "work_with_project/filecopyer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void plotWidgetLayout();
    void started();

private slots:
    void slot_data_update(const int blk_cnt, const pointFromDownHoles &point);
    void on_pushButtonSupplyModules_clicked();
    void onUpdateSettings();
    void on_settingsButton_clicked();
    void updateDepth(int depth);
    void messageProject(QString message);
    void inversAndGainChannels(const inversAndGainValue value);
    void resizeNumModules(int numDownHoleModules, int numWeelsMudules);
    void plotExample(pointsFromWGrounds *data);

    void updateCurrController(double value);
    void sendOffOnPwr();
    void on_powerSupplyButton_clicked(bool checked);

    void setGlobalOffset(const int blk_cnt, const pointFromDownHoles &point);

    void on_settingsLimitsButton_clicked();

    void on_prigimOtgimButton_clicked(bool checked);

    void on_relayModeButton_clicked(bool checked);

    void on_motorOnOffButton_clicked(bool checked);
    void setFileName(int, QString);

    void on_StartButton_clicked();
    void on_StopButton_clicked();

    void newProj(QString, QString);
    void addMeasurment();
    void on_pbSaveSGD_clicked();
    void handleResultSEGD(bool status);

    void selectRadioButton(int);

    void on_pBRealTime_clicked();

    void on_pBVibroOn_clicked();
    void timerEnd();

signals:
   void updateSettings();
   void inversChannels(const QMap<int,QVector<bool>>&);
   void dataToZeroOffsetCtrl(pointFromDownHoles point);   
   void setCorrDraw(const QString &);
   void operateSGD(QString);

private:
   void setGainDnHole(int value);
   void setGainGroundHole(int value, quint8 numDev);
   void writeFiles(QString fileName);
   void initSliders();
   void rangeGraphUpHoleChanged(int);
   void rangeGraphDownHoleChanged(int);
private:
    Ui::MainWindow *ui;
    graphSync *syncPlot_;
    QList <graphGround* > listGraphGround;
    QList <graphDownHole* > listGraphDnHole;
    QList <PaintLegend* > listPaintLegend;
    Transceiver_class* transceiver_;
    Transceiver_ground* transceiver_ground_;
    SyncModuleTranciever* transceiver_sync_;
    QThread *transceiverThread_;
    QThread *transceiverGroundThread_;
    int shiftGridLayout_;

    const int PORT_ = 1500;         //Port down modules
    const QString ADDRESS_ = "10.2.22.245";

    const int PORT_GROUND_ = 3001;         //Port down modules
    const QString ADDRESS_GROUND_ = "169.254.153.209";          // "169.254.153.204" - computer

    const int PORT_SYNC_ = 7001;         //Port sync modules
    const QString ADDRESS_SYNC_ = "169.253.153.219";

    Settings* settingsWidget_;
    QThread* projThread_;
    project_files* proj_;
    QString operator_= "";
    QString numHole_= "";
    QString nameArea_= "";
    QString distBtwDevices_ = "";
    QString syncCMD_;
    QString syncChannel_;
    int gainUpHole_ = 1;
    int numDnMod_=8;
    int numWellsMod_=8;
    int timeRecord_;
    int measId_;
    int countRecord_;
    int timeWaiting_;
    int timeSwip_;
    QString depth_ = "";
    int gainDnHole_ = 1;
    int gainGroundHole_ = 1;
    QString qsPort;
    uint32_t width_;
    bool offset;

    int rangeUpHole_   = 0;
    int rangeDownHole_   = 0;
    int chartDownHole_   = 0;

    uint16_t sizeList_ = 0;
    PowerSupplyController* powerSupplyController_;
    QTimer* reconnectPowSupplytimer_;
    QSharedPointer<QTimer> endActionTimer_;

    test * testPlot_;
    QString file_nameGN;

    /* SGD */
    single_segd_rev2_files* segd_;
    QList<single_segd_rev2_files*> lFileNameRev2;
    const qint32 max_range_size_24bit = 8388607;
    FileCopyer *segd_file_operate_;
    QThread segd_thread_;

    QButtonGroup *buttonGroup;
    axisPaintLegend rb_widget_;

    uint timeVibro;
    QTimer timerVibroOn;

protected:
    bool eventFilter(QObject *obj, QEvent *ev) override;
};

#endif // MAINWINDOW_H
