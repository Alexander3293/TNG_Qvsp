#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

/*User Includes*/
#include "qcustomplot/graphground.h"
#include "qcustomplot/graphsync.h"
#include "qcustomplot/graphdownhole.h"
#include "qcustomplot/paintlegend.h"            //Отрисовка legend
#include  "qcustomplot/plotdoublegraph.h"
#include "work_with_powerSupply/powerdevices.h"
#include "work_with_powerSupply/powersupplycontroller.h"

#include "network/transceiver_class.h"
#include "network/transceiver_ground.h"
#include "network/syncmoduletranciever.h"

#include <QFile>

#include "settings/settings.h"

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

    void on_pushButton_clicked();

    void setGlobalOffset(const int blk_cnt, const pointFromDownHoles &point);

signals:
   void updateSettings();
   void inversChannels(const QMap<int,QVector<bool>>&);
   void dataToZeroOffsetCtrl(pointFromDownHoles point);   
   void setCorrDraw(const QString &);

private:
   void setGainDnHole(int value);
   void setGainGroundHole(quint8 value);

private:
    Ui::MainWindow *ui;
    graphSync *syncPlot_;
    QList <graphGround* > listGraphGround;
    QList <graphDownHole* > listGraphDnHole;
    QList <PaintLegend* > listPaintLegend;
    Transceiver_class* transceiver_;
    Transceiver_ground* transceiver_ground_;
    QThread *transceiverThread_;
    QThread *transceiverGroundThread_;

    const int PORT_ = 1500;         //Port down modules
    const QString ADDRESS_ = "10.2.22.245";

    const int PORT_GROUND_ = 3001;         //Port down modules
    const QString ADDRESS_GROUND_ = "169.254.153.204";

    Settings* settingsWidget_;
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

    uint16_t sizeList_ = 0;
    PowerSupplyController* powerSupplyController_;
    QTimer* reconnectPowSupplytimer_;
    QSharedPointer<QTimer> endActionTimer_;

    plotDoubleGraph * testPlot_;
};

#endif // MAINWINDOW_H
