#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QList>
#include <QStyleOptionSlider>
#include <QSlider>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    qRegisterMetaType<pointFromDownHoles>("pointFromDownHoles");
    numDnMod_ = 0;
    numWellsMod_ = 0;
    projThread_ = new QThread();
    proj_ = new project_files(projThread_);
    offset = false;
    width_ = 500;
    transceiver_ = new Transceiver_class();
    transceiver_ground_ = new Transceiver_ground();
    transceiver_sync_ = new SyncModuleTranciever();

    /*для записи в проект */
    //connect(transceiver_ground_, SIGNAL(dataGroundUpdate(pointsFromWGrounds*)), this, SLOT(plotExample(pointsFromGrounds*)));

    settingsWidget_ = new Settings();
    connect(this, SIGNAL(updateSettings()), settingsWidget_, SLOT(onUpdateParametres()));
    connect(settingsWidget_, SIGNAL(errorMsg(QString)), this, SLOT(messageProject(QString)));
    connect(settingsWidget_, SIGNAL(updateSettings()), this, SLOT(onUpdateSettings()));
    connect(settingsWidget_, SIGNAL(inversAndGainChannels(inversAndGainValue)), this, SLOT(inversAndGainChannels(inversAndGainValue)));
    connect(this, SIGNAL(setCorrDraw(const QString &)), settingsWidget_, SLOT(setCorrDraw(const QString &)));
    connect(settingsWidget_, SIGNAL(startDwnHole()), transceiver_, SLOT(send_start()));
    connect(settingsWidget_, SIGNAL(startGround()), transceiver_ground_, SLOT(send_Start()));
    connect(settingsWidget_, SIGNAL(startSync(const QString, const QString )), transceiver_sync_, SLOT(send_Start(const QString, const QString )));
    connect(settingsWidget_, SIGNAL(stopGround()), transceiver_ground_, SLOT(send_Stop()));
    connect(settingsWidget_, SIGNAL(searchGround()), transceiver_ground_, SLOT(send_search_devices()));
    // connect(settingsWidget_, SIGNAL(stopSync()), this, SLOT(stopSync()));

    /* Виджет легенды real-time модуля синхронизации */
//    listPaintLegend.append(new (PaintLegend));
//    listPaintLegend.at(0)->setMod(syncMod);

//    QPalette pal(listPaintLegend.at(0)->palette());
//    ui->gridLayout->addWidget(listPaintLegend.at(0));
    //ui->gridLayout->setColumnMinimumWidth(1, 5);
    ui->gridLayout->setColumnStretch(0,10);
    ui->gridLayout->setColumnStretch(1, 0);         // пустая колонка 2
    ui->gridLayout->setVerticalSpacing(0);

    /* График real-time модуля синхронизации */
    shiftGridLayout_ = 0;
    syncPlot_ = new graphSync(transceiver_sync_);
    ui->gridLayout->addWidget(syncPlot_,shiftGridLayout_++,0);
    syncPlot_->setWidth(width_);
    syncPlot_->initGraphSync();
    syncPlot_->clearData();

    /* SLIDER */
    initSliders();

    /* Совместное построение наземного и подземного */
//    testPlot_ = new plotDoubleGraph(transceiver_ground_, transceiver_);
//    ui->gridLayout->addWidget(testPlot_, shiftGridLayout_++, 0);
//    testPlot_->setTraceDnHole();
//    testPlot_->initGraphXYZ();
//    testPlot_->conectSignals();

    onUpdateSettings();
    /* set File name to the write data into the file */
//    QString fileName = QString("%1_%2")
//                .arg(QDate::currentDate().toString("yyyy_MM_dd"))
//                .arg(QTime::currentTime().toString("hh_mm_ss_zzz"));
//    transceiver_->setFileName(fileName);
//    transceiver_ground_->setFileName(fileName);
//    transceiver_sync_->setFileName(fileName);


    /* В будущем: запись проектовой инфы в файл */
//    connect(transceiver_, SIGNAL(data_update(int,pointFromDownHoles)),  this,
//            SLOT(slot_data_update(int,pointFromDownHoles)));
    connect(settingsWidget_, SIGNAL(startSync(const QString, const QString )), syncPlot_, SLOT(changeTimeBreakSlot(const QString, const QString )));
    //connect(settingsWidget_, SIGNAL(startDwnHole()), this, SLOT(setFileName()));

    powerSupplyController_ = new PowerSupplyController();
    connect(powerSupplyController_, SIGNAL(curr(double)), this, SLOT(updateCurrController(double)));
    connect(powerSupplyController_, SIGNAL(volt(double)), ui->voltLabel, SLOT(setNum(double)));
    connect(powerSupplyController_, SIGNAL(msgFromPowerSupply(QString)), this, SLOT(messageProject(QString)));
    powerSupplyController_->setUpdateTimeData(500);
    reconnectPowSupplytimer_ = new QTimer();
    reconnectPowSupplytimer_->setInterval(6000); // 60 sec interval for reconnect
    connect(reconnectPowSupplytimer_, SIGNAL(timeout()), this, SLOT(sendOffOnPwr()));

    endActionTimer_.reset(new QTimer);
    connect(endActionTimer_.data(), &QTimer::timeout, this, [=](){
        this->on_powerSupplyButton_clicked(false);
        endActionTimer_->stop();
        this->messageProject("Выключение блока питания для операции прижим/отжим по времени");
        qInfo() << "Выключение блока питания для операции прижим/отжим по времени";
    });

//    connect(transceiver_, SIGNAL(data_update(int,pointFromDownHoles)),  this,
//                SLOT(setGlobalOffset(int,pointFromDownHoles))); //Первое смещение задать

//    transceiver_ground_->initialize(ADDRESS_GROUND_, PORT_GROUND_);
//    transceiverGroundThread_ = new QThread();
//    transceiver_ground_->moveToThread(transceiverGroundThread_);
//    transceiver_sync_->initialize(ADDRESS_SYNC_, PORT_SYNC_);
//    transceiver_->initialize(ADDRESS_, PORT_);
//    transceiverThread_ = new QThread();
//    transceiver_->moveToThread(transceiverThread_);

//    connect(transceiverGroundThread_, SIGNAL(started()), transceiver_ground_, SLOT(start()));
//    connect(transceiver_ground_, SIGNAL(message(QString)), this, SLOT(messageProject(QString)));
//    transceiverGroundThread_->start();
//    transceiver_sync_->start();

    connect(transceiver_, SIGNAL(data_update(int,pointFromDownHoles)),  this,
                SLOT(setGlobalOffset(int,pointFromDownHoles))); //Первое смещение задать

    transceiver_ground_->initialize(ADDRESS_GROUND_, PORT_GROUND_);
    transceiverGroundThread_ = new QThread();
    transceiver_ground_->moveToThread(transceiverGroundThread_);
    connect(transceiverGroundThread_, SIGNAL(started()), transceiver_ground_, SLOT(start()));
    connect(transceiver_ground_, SIGNAL(message(QString)), this, SLOT(messageProject(QString)));

    transceiver_sync_->initialize(ADDRESS_SYNC_, PORT_SYNC_);
    transceiver_sync_->start();

    transceiver_->initialize(ADDRESS_, PORT_);
    transceiverThread_ = new QThread();
    transceiver_->moveToThread(transceiverThread_);
    connect(transceiverThread_, SIGNAL(started()), transceiver_, SLOT(start()));
    connect(transceiver_, SIGNAL(connectionClosed()), transceiverThread_, SLOT(quit()));
    connect(transceiverThread_, SIGNAL(finished()), transceiverThread_, SLOT(deleteLater()));
    connect(transceiver_, SIGNAL(newDepth(int)), this, SLOT(updateDepth(int)));

    connect(transceiver_, SIGNAL(newOffsetpckt(quint16)), transceiver_ground_, SLOT(getDataOffsetDownHoles(quint16)));
    connect(transceiver_, SIGNAL(newOffsetpckt(quint16)), transceiver_sync_, SLOT(getDataOffsetDownHoles(quint16)));

    transceiverThread_->start();
    transceiverGroundThread_->start();

}

MainWindow::~MainWindow()
{
    delete syncPlot_;
    if(proj_->isOpened() == true)
        proj_->setStopTime(); /* ПРоверить, было ли нажатие */
//    delete transceiver_;
//    for(int i=0; i < listGraphGround.count(); i++)
//        delete  listGraphGround.at(0);

//    for(int i=0; i < listGraphDnHole.count(); i++)
//        delete  listGraphDnHole.at(0);

//    for (int i=0; listPaintLegend.count(); i++)
//        delete listPaintLegend.at(0);

    delete ui;
}

void MainWindow::updateDepth(int depth)
{
    if(depth > 0){
        depth_ = QString::fromUtf8("%1.%2%3 м").arg(depth / 100, 4).arg((depth / 10) % 10).arg(depth % 10);
        //qDebug() << " in new Depth" << depth_;
    }
    //qDebug() << "new Depth" << depth_;
}

void MainWindow::on_pushButtonSupplyModules_clicked()
{
    PowerDevices* powerSupDev = new PowerDevices();
    powerSupDev->setAttribute(Qt::WA_DeleteOnClose);
    powerSupDev->show();
}

/* Init graphics Ground, downholes */
void MainWindow::plotWidgetLayout()
{
    shiftGridLayout_ = 2;
    /* График real-time для подземных модулей */
    for(int i=0; i < numDnMod_*3; i++)
        listGraphDnHole.append(new graphDownHole(transceiver_));

    //ui->gridLayout->setSpacing(0);



    for(int i=0; i<listGraphDnHole.count(); i++)
    {
        //ui->gridLayout->addWidget(new QPushButton(tr("add")), shiftGridLayout_, 1);
        ui->gridLayout->addWidget(listGraphDnHole.at(i), shiftGridLayout_++, 0);
        /* ширина построения */
        listGraphDnHole.at(i)->setWidth(width_);
        /* Передача номера модуля */
        listGraphDnHole.at(i)->setModNum(i/3);
        /*Стираем старые данные */
        listGraphDnHole.at(i)->clearData();

        switch (i%3) {
        case init_graph_DownHoles::graph_axis_X:
            listGraphDnHole.at(i)->initGraphXYZ(init_graph_DownHoles::graph_axis_X);
            break;
        case init_graph_DownHoles::graph_axis_Y:
            listGraphDnHole.at(i)->initGraphXYZ(init_graph_DownHoles::graph_axis_Y);
            break;
        case init_graph_DownHoles::graph_axis_Z:
            listGraphDnHole.at(i)->initGraphXYZ(init_graph_DownHoles::graph_axis_Z);
            break;
        }

        /*Выбираем необходимый модуль для данных */
        listGraphDnHole.at(i)->setTraceDnHole();
    }
//-------------------------------------------//
    /* Widget real-time наземных модулей - геофонов */
    for(int i=0; i < numWellsMod_; i++)
        listGraphGround.append(new graphGround(transceiver_ground_));

    for(int i=0; i<listGraphGround.count(); i++)
    {
        ui->gridLayout->addWidget(listGraphGround.at(i), shiftGridLayout_++, 0);
        /* Передача номера устройства */
        listGraphGround.at(i)->setDevNum(i);
        /* ширина построения */
        listGraphGround.at(i)->setWidth(width_);
        /* Отрисовка какого-то графика*/
        listGraphGround.at(i)->initGraphGround();
    }
//-------------------------------------------//
}


void MainWindow::plotExample(pointsFromWGrounds *data)
{
    Q_UNUSED(data);
}

void MainWindow::slot_data_update(const int blk_cnt, const pointFromDownHoles &point)
{
    Q_UNUSED(blk_cnt);
    Q_UNUSED(point);
//    volatile unsigned short int x = ntohs(point.n_pocket);
//    volatile unsigned short int y = (unsigned short int)(blk_cnt & 0x0FFFF);
//    if(x % 15000 == 0)
//    {
//        qsPort = QString::fromUtf8("%1 <--> %2. Time:%3").arg(y).arg(x).arg(QTime::currentTime().toString("hh:mm:ss.zzz"));
//        this->messageProject("Счетчик пакетов "+ qsPort);
//    }
//    bool isCRC = true;
////    for(int i = 0; i < controlSum_.size(); i++){
////        bool result = controlSum_.at(i)->zeroizeChkSum(point);
////        if (result == false)
////            isCRC = false;
////    }

//    if(isCRC == true)
//        emit dataToZeroOffsetCtrl(point);   //GOTO: куда????

}

void MainWindow::on_settingsButton_clicked()
{
    QPoint pos = ui->settingsButton->geometry().bottomRight();
    //   pos.setX(pos.x() + ui->settingsButton->width());
    settingsWidget_->setPosition(pos);
    settingsWidget_->show();
    emit updateSettings();
}

void MainWindow::onUpdateSettings()
{
    if(numDnMod_ != settingsWidget_->numDnMod() || numWellsMod_ != settingsWidget_->numWellsMod())
    {
        numDnMod_ = settingsWidget_->numDnMod();
        numWellsMod_ = settingsWidget_->numWellsMod();
        syncChannel_ = settingsWidget_->syncChannel();
        syncCMD_ = settingsWidget_->syncCMD();
        transceiver_->setNumModule(numDnMod_);
        transceiver_ground_->setNumModule(numWellsMod_);
        resizeNumModules(numDnMod_, numWellsMod_);
        plotWidgetLayout();
    }
    timeRecord_ = settingsWidget_->timeRecord();
    countRecord_ = settingsWidget_->countRecord();
    timeWaiting_ = settingsWidget_->timeWaiting();
//    syncCMD_ = settingsWidget_->syncCMD();
//    syncChannel_ = settingsWidget_->syncChannel();
//    corrDraw_ = settingsWidget_->corrDraw();
//    corrSave_ = settingsWidget_->corrSave();
    timeSwip_ = settingsWidget_->swipLen();

//    if(settingsWidget_->depth().size() > 0)
//        depth_ = settingsWidget_->depth();
//    operator_= settingsWidget_->operatorName();
//    numHole_= settingsWidget_->numHole();
//    nameArea_= settingsWidget_->nameArea();
//    distBtwDevices_ = settingsWidget_->distBtwDevices();
//    if(offsetDnHole_ <= 0 || offsetDnHole_ != settingsWidget_->globalOffsetDnHole()) {
//        offsetDnHole_ = settingsWidget_->globalOffsetDnHole();
//        sharedGraphicsWidget->setGlobalOffsetDnHole(offsetDnHole_);
//    }
//    if(offsetUpHole_ < -50 || offsetUpHole_ > 50 || offsetUpHole_ != settingsWidget_->globalOffsetUpHole()) {
//        offsetUpHole_ = settingsWidget_->globalOffsetUpHole();
//        sharedGraphicsWidget->setGlobalOffsetUpHole(offsetUpHole_);
//    }
//    isSaveToCustomDir_ = settingsWidget_->isDefaultSavingPath();
//    if(isPaintZeroLines_ != settingsWidget_->isPaintZeroLines()){
//        isPaintZeroLines_ = settingsWidget_->isPaintZeroLines();
//        sharedGraphicsWidget->setIsPaintZeroLines(isPaintZeroLines_);
//    }

//    int indexText = ui->comboBoxProccesing->findText(corrDraw_);
//    if(indexText >= 0)
//        ui->comboBoxProccesing->setCurrentIndex(indexText);
//    else
//        ui->comboBoxProccesing->setCurrentIndex(ui->comboBoxProccesing->findText(CORRELATION_TYPE_ORIG));
//    if(syncChannel_ == "F"){
//        ui->comboBoxProccesing->setCurrentIndex(ui->comboBoxProccesing->findText(CORRELATION_TYPE_ORIG));
//    }
//    on_comboBoxProccesing_currentIndexChanged(ui->comboBoxProccesing->currentText());
//    autoPressingWidget_->setNumModules(numDnMod_);
}
void MainWindow::resizeNumModules(int numDownHoleModules, int numWeelsModules)
{
    Q_UNUSED(numWeelsModules);
    Q_UNUSED(numDownHoleModules);

    sizeList_ = listGraphGround.size()*3;
    for(int i=0; i < sizeList_; i++)
    {
        ui->gridLayout->removeWidget(listGraphGround.at(0));
        delete  listGraphGround.at(0);
        listGraphGround.removeAt(0);
    }
    sizeList_ = listGraphDnHole.size()*3;
    for(int i=0; i < sizeList_; i++)
    {
        ui->gridLayout->removeWidget(listGraphDnHole.at(0));
        delete  listGraphDnHole.at(0);
        listGraphDnHole.removeAt(0);
    }

}
void MainWindow::setGainGroundHole(int value, quint8 numDev)
{
    transceiver_ground_->send_Settings_KU(value, numDev);
    qInfo() << qUtf8Printable(QString("КУ наземных модулей %1").arg(value));
    qDebug() << "num Dev" << numDev;
}

void MainWindow::setGainDnHole(int value)
{
    transceiver_->on_tool_set_KU(value);
    qInfo() << qUtf8Printable(QString("КУ скважинных модулей %1").arg(value));

}

void MainWindow::inversAndGainChannels(const inversAndGainValue value)
{
    qWarning() << "inversAndGainChannels";
    emit inversChannels(value.mapInversModules);

    //    На данный момент отправляется всей связки усиление,
    //взятое из массива ( если хотябы одно значение выставлено отличным от единицы)
    int kuDwn = 1;
    for(auto it = value.vecGainDwnModules.cbegin(); it < value.vecGainDwnModules.cend(); it++)
        if(std::get<0>(*it) >= 1 || std::get<1>(*it) >= 1 || std::get<2>(*it) >= 1)
        {
            if(std::get<0>(*it) > 1)
                kuDwn = std::get<0>(*it);
            else if(std::get<1>(*it) > 1)
                kuDwn = std::get<1>(*it);
            else
                kuDwn = std::get<2>(*it);
            setGainDnHole(kuDwn);
            break;
        }
    // вариант отправки каждому свое усиление
    //    for(int i = 0; i < value.vecGainUpModules.size(); i ++)
    //        transceiverWsdc_->send_KU(true, i, value.vecGainUpModules[i]);

    // вариант отправки всем одно усиление
    int ku = 1;
    uint8_t cntDevice = -1;
    uint8_t devNumber = 0;
    for(auto it = value.vecGainGroundModules.begin(); it < value.vecGainGroundModules.end(); it++) {
        cntDevice++;
        if((*it) != -65536)
        {
            ku = *it;
            devNumber |= (uint8_t) (1 << cntDevice);
        }
    }
    setGainGroundHole(ku, devNumber); //нумерация начинается с 0

    messageProject("Инверсия и усиление выбранных значений прошли успешно");
    gainDnHole_ = kuDwn;
    gainGroundHole_ = ku;
}

void MainWindow::messageProject(QString message)
{
   ui->textPlainEditInfrom->appendPlainText(QTime::currentTime().toString("hh:mm:ss")
                                             + " " +message);
    qInfo() << message;
}

auto replaceCommaToPoint = [](QString originStr){
    QString replaceStr = originStr;
    std::replace(replaceStr.begin(), replaceStr.end(), ',', '.');
    return replaceStr;
};

void MainWindow::updateCurrController(double value)
{
    //    qDebug() << "cur" << value;
    ui->currLabel->setNum(value);
    double maxValue;
    maxValue = replaceCommaToPoint(ui->currLimitOffEdit->text()).toDouble();
    if((value >= maxValue))
    {
        on_powerSupplyButton_clicked(false);
        messageProject("Операция прижима/отжима остановлена по току.");
        qInfo() << "Операция прижима/отжима остановлена по току.";
    }

}

void MainWindow::on_powerSupplyButton_clicked(bool checked)
{
    double vlotLimit = replaceCommaToPoint(ui->voltLimitlineEdit->text()).toDouble();
    double currLimit = replaceCommaToPoint(ui->currLimitlineEdit->text()).toDouble();
    auto compareValues = [](double val, double maxVal){return ( (val < maxVal) && (val > -maxVal) ); };

        if(checked){
            endActionTimer_->setInterval(ui->timeLimitOffEdit->text().toInt() * 1000);
            endActionTimer_->start();
        }
        else {
            //qInfo() << "Операция прижима/отжима остановлена оператором.";
            endActionTimer_->stop();
        }

    //        currLimit = maxValueForOffPowerSupply_;
    if(checked)
    {
        if(compareValues(vlotLimit, 1000) && compareValues(currLimit, 5.0))
        {
            messageProject(QString::fromUtf8("Установлены лимиты значений %1  %2").arg(currLimit).arg(vlotLimit));
        }
        else
        {
            messageProject("Установлены некорректные лимиты значений");
            return;
        }

        ui->powerSupplyButton->setStyleSheet("border-image: url(:/resources/elements/powerSupply_off.png);");
        powerSupplyController_->setVoltLimit(vlotLimit);
        powerSupplyController_->setCurrLimit(currLimit);
        powerSupplyController_->powerOn();
        ui->powerSupplyButton->setCheckable(false);
    }
    else
    {
        powerSupplyController_->powerOff();
        ui->powerSupplyButton->setStyleSheet("border-image: url(:/resources/elements/powerSupply_on.png);");
        ui->powerSupplyButton->setCheckable(true); //invert checked
    }
}

void MainWindow::sendOffOnPwr()
{
    transceiver_->on_panel_pwr_on();
    transceiver_->on_panel_pwr_off();
}

/* Устновить глобальное смещение для наземных датчиков (при открытии приложения, чтобы все норм было)*/
void MainWindow::setGlobalOffset(const int blk_cnt, const pointFromDownHoles &point)
{
   //Q_UNUSED(blk_cnt);
    static uint8_t offset_blk_cnt = 0;
    uint16_t numPcktDownHoles = ntohs(point.n_pocket);  //начало пакета с 1 у подземных модулей
    uint8_t numPcktGround = numPcktDownHoles / 256;
    uint8_t numMesGround = numPcktDownHoles %  256;
    if(numMesGround < 11){
        offset_blk_cnt++;
        return;
    }

    numMesGround-=11;                       // 10 задержка
    if(!offset){
        qDebug() << "tyt";
        syncPlot_->setOffset(numPcktGround, numMesGround, 1);

        for(int i=0; i<listGraphGround.count(); i++)
            listGraphGround.at(i)->setOffset(numPcktGround, numMesGround, 1);    //or use blk_cnt???
        disconnect(transceiver_, SIGNAL(data_update(int,pointFromDownHoles)),  this,
                    SLOT(setGlobalOffset(int,pointFromDownHoles))); //Первое смещение задать
        offset = true;
    }
}

void MainWindow::on_settingsLimitsButton_clicked()
{
    powerSupplyController_->setVoltLimit(replaceCommaToPoint(ui->voltLimitlineEdit->text()).toDouble());
    powerSupplyController_->setCurrLimit(replaceCommaToPoint(ui->currLimitlineEdit->text()).toDouble());
    double vlotLimit = replaceCommaToPoint(ui->voltLimitlineEdit->text()).toDouble();
    double currLimit = replaceCommaToPoint(ui->currLimitlineEdit->text()).toDouble();
    auto compareValues = [](double val, double maxVal){return ( (val < maxVal) && (val > -maxVal) ); };

    if(compareValues(vlotLimit, 1000) && compareValues(currLimit, 2))
    {
        messageProject(QString::fromUtf8("Установлены лимиты значений %1  %2").arg(currLimit).arg(vlotLimit));
    }
    else
    {
        messageProject("Установлены некорректные лимиты значений");
        return;
    }
}

void MainWindow::on_prigimOtgimButton_clicked(bool checked)
{
    if(checked)
    {
        transceiver_->send_otgim();
        qInfo() << "Переключатель установлен в режим отжим";
        ui->prigimOtgimButton->setStyleSheet("border-image: url(:/resources/elements/off.png);");
        ui->prigimOtgimButton->setCheckable(false); //invert checked
    }
    else
    {
        transceiver_->send_prigim();
        qInfo() << "Переключатель установлен в режим прижим";
        ui->prigimOtgimButton->setStyleSheet("border-image: url(:/resources/elements/on.png);");
        ui->prigimOtgimButton->setCheckable(true); //invert checked
    }
}

void MainWindow::on_relayModeButton_clicked(bool checked)
{

    if(checked)
    {

        transceiver_->on_tool_rele_on(1);   //num_module
        ui->relayModeButton->setText("Выкл Реле");
        ui->relayModeButton->setCheckable(false); //invert checked
    }
    else
    {

        transceiver_->on_tool_rele_off(1);  //num module
        ui->relayModeButton->setText("Вкл Реле");
        ui->relayModeButton->setCheckable(true); //invert checked
    }
}

void MainWindow::on_motorOnOffButton_clicked(bool checked)
{
    if(checked)
    {
        transceiver_->on_panel_motor_off();
        qInfo() << "Произведена операция включения мотора!";
        ui->motorOnOffButton->setText("Вкл Мотор");
        reconnectPowSupplytimer_->stop();
        ui->prigimOtgimButton->setEnabled(true);
    }
    else
    {
        transceiver_->on_panel_motor_on();
        ui->motorOnOffButton->setText("Выкл Мотор");
        qInfo() << "Произведена операция выключения мотора!";
        reconnectPowSupplytimer_->start();
        ui->prigimOtgimButton->setEnabled(false);
    }

    ui->motorOnOffButton->setCheckable(true); //invert checked
}

void MainWindow::setFileName(int idMeas, QString dirFile)
{
//    QFileInfo fileInfoGround(fileGround);
//    QFileInfo fileInfoDn(fileDn);
//    QFileInfo fileInfoSync(fileSync);

//    QVector<QString> vecFileName;                   //Vector с расположением файлов
//    vecFileName.append(fileInfoGround.fileName());
//    vecFileName.append(fileInfoDn.fileName());
//    vecFileName.append(fileInfoSync.fileName());

    transceiver_->setFileName(idMeas, dirFile);
    transceiver_->setRecord(true);
    transceiver_ground_->setFileName(idMeas, dirFile);
    transceiver_ground_->setRecord(true);
    transceiver_sync_->setFileName(idMeas, dirFile);
    transceiver_sync_->setRecord(true);


}

void MainWindow::writeFiles(QString fileName)
{
    QFile fileGround, fileDn, fileSync;
    QList<QFile *>  listFileGround;     //Сюда будут записываться измерения с наземных модулей
    QList<QFile *>  listFileDn;         //Сюда будут записываться измерения с подземных модулей
    QList<QFile *>  listFileSync;       //Сюда будут записываться измерения с синхро модуля (АЦП, TBF, ...)

    fileGround.setFileName(fileName);
    fileDn.setFileName(fileName.remove("Ground.txt") + "DownHole.txt");
    fileSync.setFileName(fileName.remove("Ground.txt") + "Syncro.txt");

/* Работа с подземными модулями */
    if(!fileDn.open(QFile::ReadOnly|QFile::Text)) //Открываем для чтения, если нельзя открыть: переходим к следующему
    {
       return;
    }

    bool ok;
    QString tmp_dev_num = fileDn.readLine();
    int numDev_dnHoles = tmp_dev_num.right(2).toInt(&ok, 16);  //Количество подземных модулей
    int sizePckt = 32 * numDev_dnHoles + 4;                    //Размер пакета исходя из количества подземных

    for(uint8_t i=0; i < numDev_dnHoles; i++){

        listFileDn.append(new QFile);
        listFileDn[i*3]->setFileName(QString("D:/Test/measure/DownHole_%1X.txt").arg(i));
        listFileDn[i*3]->remove();
        if(!listFileDn[i*3]->open(QIODevice::WriteOnly|QIODevice::Append)) //Открываем для чтения, если нельзя открыть: переходим к следующему
           return;

        listFileDn.append(new QFile);
        listFileDn[i*3+1]->setFileName(QString("D:/Test/measure/DownHole_%1Y.txt").arg(i));
        listFileDn[i*3+1]->remove();
        if(!listFileDn[i*3+1]->open(QIODevice::WriteOnly|QIODevice::Append)) //Открываем для чтения, если нельзя открыть: переходим к следующему
           return;

        listFileDn.append(new QFile);
        listFileDn[i*3+2]->setFileName(QString("D:/Test/measure/DownHole_%1Z.txt").arg(i));
        listFileDn[i*3+2]->remove();
        if(!listFileDn[i*3+2]->open(QIODevice::WriteOnly|QIODevice::Append)) //Открываем для чтения, если нельзя открыть: переходим к следующему
           return;
    }

    union {
        struct {
            quint8 x7_0;
            quint8 x15_8;
            quint8 x23_16;
            quint8 x31_24;
        };
        qint32 x31_0;
    } point;

    fileDn.read(sizePckt*11);                                  //Сделать сдвиг для пакетов
    uint16_t startPcktDwnHoles = 0;

    QString tmp;
    tmp = fileDn.read(sizePckt);
    startPcktDwnHoles = tmp.mid(0, 4).toInt(&ok, 16);

    int shiftDevice = 0;                                       //номер устройства, для построения (сдвигать на каждые 32 байта (помнить про шапку 4 байта)


    for(int i=0; i < numDev_dnHoles; i++){
        shiftDevice=i;
        shiftDevice*= 32;   //Сдвиг по номеру устройства
        shiftDevice+= 4;    //Сдвиг (убрать номер пакета)

        point.x23_16 = tmp.mid(shiftDevice+0, 2).toInt(&ok, 16);
        point.x15_8 = tmp.mid(shiftDevice+2*2, 2).toInt(&ok, 16);
        point.x7_0 = tmp.mid(shiftDevice+3*2, 2).toInt(&ok, 16);
        if ((point.x31_0 & 0x00800000) > 0) point.x31_24 = 0xFF;
        else point.x31_24 = 0;
        listFileDn[i*3]->write(QByteArray::number(point.x31_0)+'\n');

        point.x23_16 = tmp.mid(shiftDevice+4*2, 2).toInt(&ok, 16);
        point.x15_8 = tmp.mid(shiftDevice+5*2, 2).toInt(&ok, 16);
        point.x7_0 = tmp.mid(shiftDevice+6*2, 2).toInt(&ok, 16);
        if ((point.x31_0 & 0x00800000) > 0) point.x31_24 = 0xFF;
        else point.x31_24 = 0;
        listFileDn[i*3+1]->write(QByteArray::number(point.x31_0)+'\n');

        point.x23_16 = tmp.mid(shiftDevice+7*2, 2).toInt(&ok, 16);
        point.x15_8 = tmp.mid(shiftDevice+8*2, 2).toInt(&ok, 16);
        point.x7_0 = tmp.mid(shiftDevice+9*2, 2).toInt(&ok, 16);

        if ((point.x31_0 & 0x00800000) > 0) point.x31_24 = 0xFF;
        else point.x31_24 = 0;
        listFileDn[i*3+2]->write(QByteArray::number(point.x31_0)+'\n');
    }

    while(!fileDn.atEnd()) //Считываем файл, пока не считаем весь файл
    {
        tmp = fileDn.read(sizePckt);

        for(int i=0; i < numDev_dnHoles; i++){
            shiftDevice=i;
            shiftDevice*= 32;   //Сдвиг по номеру устройства
            shiftDevice+= 4;    //Сдвиг (убрать номер пакета)

            point.x23_16 = tmp.mid(shiftDevice+0, 2).toInt(&ok, 16);
            point.x15_8 = tmp.mid(shiftDevice+2*2, 2).toInt(&ok, 16);
            point.x7_0 = tmp.mid(shiftDevice+3*2, 2).toInt(&ok, 16);
            if ((point.x31_0 & 0x00800000) > 0) point.x31_24 = 0xFF;
            else point.x31_24 = 0;
            listFileDn[i*3+0]->write(QByteArray::number(point.x31_0)+'\n');

            point.x23_16 = tmp.mid(shiftDevice+4*2, 2).toInt(&ok, 16);
            point.x15_8 = tmp.mid(shiftDevice+5*2, 2).toInt(&ok, 16);
            point.x7_0 = tmp.mid(shiftDevice+6*2, 2).toInt(&ok, 16);
            if ((point.x31_0 & 0x00800000) > 0) point.x31_24 = 0xFF;
            else point.x31_24 = 0;

            listFileDn[i*3+1]->write(QByteArray::number(point.x31_0)+'\n');
            point.x23_16 = tmp.mid(shiftDevice+7*2, 2).toInt(&ok, 16);
            point.x15_8 = tmp.mid(shiftDevice+8*2, 2).toInt(&ok, 16);
            point.x7_0 = tmp.mid(shiftDevice+9*2, 2).toInt(&ok, 16);
            if ((point.x31_0 & 0x00800000) > 0) point.x31_24 = 0xFF;
            else point.x31_24 = 0;
            listFileDn[i*3+2]->write(QByteArray::number(point.x31_0)+'\n');
        }
    }

    fileDn.close();
    for(uint8_t i=0; i < listFileDn.size(); i++)
        listFileDn[i]->close();




/* ---------------Работа  с наземными модулями ---------------------------------------------------------------------------------------------------- */
    if(!fileGround.open(QFile::ReadOnly|QFile::Text)) //Открываем для чтения, если нельзя открыть, return
    {
       return;
    }

    QString tmp_dev_numGr = fileGround.readLine();
    int numDev_Ground= tmp_dev_numGr.right(2).toInt(&ok, 16);  //Количество наземных модулей
    for(uint8_t i=0; i < numDev_Ground; i++){

        listFileGround.append(new QFile);
        listFileGround[i]->setFileName(QString("D:/Test/measure/devGround_%1.txt").arg(i));
        listFileGround[i]->remove();
        if(!listFileGround[i]->open(QIODevice::WriteOnly|QIODevice::Append)) //Открываем для чтения, если нельзя открыть: переходим к следующему
           return;
    }

     volatile int device_id = -1;
     QString  tmp_str_iVal;  //Считываемое String
     QString  str_iVal;
     int32_t value = 0;
     int32_t tmp1 =0;
     int32_t tmp2 = 0;
     QString hand_package_Ground = "ed00ff";
     uint8_t number_packet_ground = 0;
     uint8_t startMeas = startPcktDwnHoles % 256;  //сдвиг Down Holes
     startPcktDwnHoles /= 256;                         //Пакет отностильеон Down Holes
     if(startMeas < 11) {
         startPcktDwnHoles--;
         startMeas-=11;
     }
     else
         startMeas -= 11;

     bool flagOffset[8] = {false,};    //чтобы первый  раз проверить нумерацию пакета
     uint16_t counter_offset = 0;  //Счетчик сдвига
     while(!fileGround.atEnd()){

        tmp_str_iVal = fileGround.read(6);        //read 2 bytes + 2 bytes
        if(tmp_str_iVal.startsWith(hand_package_Ground,Qt::CaseInsensitive)){  //Start of the package

            //Device ID
             tmp_str_iVal = fileGround.read(2);
             device_id = tmp_str_iVal.right(2).toInt();
             tmp_str_iVal = fileGround.read(2);
             number_packet_ground = tmp_str_iVal.toInt(&ok, 16);
             if(flagOffset[device_id] == false){

                 if(number_packet_ground == startPcktDwnHoles){
                     counter_offset = 0;
                     while(counter_offset < startMeas){        //Добиться необходимого смещения
                         tmp_str_iVal = fileGround.read(6);
                         counter_offset++;
                     }
                     flagOffset[device_id] = true;
                 }
             }
        }
        else {

            tmp1 = tmp_str_iVal.left(4).toInt(&ok,16);
            tmp2 = tmp_str_iVal.right(2).toInt(&ok,16);
            value = (tmp1 << 8) | (tmp2 >>8);
            if(value & 0x800000){
                value |= 0xff000000;
            }
            listFileGround[device_id]->write(QByteArray::number(value)+'\n');
        }
     }

     fileGround.close();
     for(uint8_t i=0; i < numDev_Ground; i++){

         (listFileGround[i])->close();

     }

     /* ---------------Работа  с синхро модулем -------------------------------------------------------------------------------------------------------------- */
     if(!fileSync.open(QFile::ReadOnly|QFile::Text)) //Открываем для чтения, если нельзя открыть: переходим к следующему
     {
        return;
     }


     listFileSync.append(new QFile);
     listFileSync[0]->setFileName(QString("D:/Test/measure/devSyncADC.txt"));
     listFileSync[0]->remove();
     if(!listFileSync[0]->open(QIODevice::WriteOnly|QIODevice::Append)) //Открываем для чтения, если нельзя открыть: переходим к следующему
        return;
     listFileSync.append(new QFile);
     listFileSync[1]->setFileName(QString("D:/Test/measure/devSyncTBV.txt"));
     listFileSync[1]->remove();
     if(!listFileSync[1]->open(QIODevice::WriteOnly|QIODevice::Append)) //Открываем для чтения, если нельзя открыть: переходим к следующему
        return;
     listFileSync.append(new QFile);
     listFileSync[2]->setFileName(QString("D:/Test/measure/devSyncTBF.txt"));
     listFileSync[2]->remove();
     if(!listFileSync[2]->open(QIODevice::WriteOnly|QIODevice::Append)) //Открываем для чтения, если нельзя открыть: переходим к следующему
        return;
     listFileSync.append(new QFile);
     listFileSync[3]->setFileName(QString("D:/Test/measure/devSyncCTB.txt"));
     listFileSync[3]->remove();
     if(!listFileSync[3]->open(QIODevice::WriteOnly|QIODevice::Append)) //Открываем для чтения, если нельзя открыть: переходим к следующему
        return;


     QString hand_package_Sync = "ffffff";

     uint8_t number_packet_sync = 0;
     startMeas = 91;
     startPcktDwnHoles = 240;

     bool flagOffsetSync = false;
     uint16_t counter_offset_sync = 0;  //Счетчик сдвига
     while(!fileSync.atEnd()){

        tmp_str_iVal = fileSync.read(8);        //read 2 bytes + 2 bytes
        if(tmp_str_iVal.startsWith(hand_package_Sync,Qt::CaseInsensitive)){  //Start of the package

             number_packet_sync = tmp_str_iVal.right(2).toUInt(&ok,16);

             if(flagOffsetSync == false){
                 if(number_packet_sync == startPcktDwnHoles){
                     counter_offset_sync = 0;
                     startMeas++;   //там сдвиг -10
                     while(counter_offset_sync < startMeas){        //Добиться необходимого смещения
                         tmp_str_iVal = fileSync.read(4);
                         counter_offset_sync++;
                     }
                     flagOffsetSync = true;
                     if(startMeas % 2){ //Если прочитаю нечетное
                         tmp_str_iVal = fileSync.read(4);
                         value =  (tmp_str_iVal.mid(2,2) + tmp_str_iVal.left(2)).toUInt(&ok,16);
                         listFileSync.at(0)->write(QByteArray::number(value & (0x0FFF))+'\n');
                         if(value & 0x1000)
                             listFileSync.at(1)->write(QByteArray::number(4095)+'\n');
                         else
                             listFileSync.at(1)->write(QByteArray::number(0)+'\n');
                         if(value & 0x2000)
                             listFileSync.at(2)->write(QByteArray::number(4095)+'\n');
                         else
                             listFileSync.at(2)->write(QByteArray::number(0)+'\n');
                         if(value & 0x4000)
                             listFileSync.at(3)->write(QByteArray::number(4095)+'\n');
                         else
                             listFileSync.at(3)->write(QByteArray::number(0)+'\n');
                     }
                 }
             }
        }
        else {
            value =  (tmp_str_iVal.mid(2,2) + tmp_str_iVal.left(2)).toUInt(&ok,16);
            listFileSync.at(0)->write(QByteArray::number(value & (0x0FFF))+'\n');
            if(value & 0x1000)
                listFileSync.at(1)->write(QByteArray::number(4095)+'\n');
            else
                listFileSync.at(1)->write(QByteArray::number(0)+'\n');
            if(value & 0x2000)
                listFileSync.at(2)->write(QByteArray::number(4095)+'\n');
            else
                listFileSync.at(2)->write(QByteArray::number(0)+'\n');
            if(value & 0x4000)
                listFileSync.at(3)->write(QByteArray::number(4095)+'\n');
            else
                listFileSync.at(3)->write(QByteArray::number(0)+'\n');

            value =  (tmp_str_iVal.right(2) + tmp_str_iVal.mid(4,2)).toUInt(&ok,16);
            listFileSync.at(0)->write(QByteArray::number(value & (0x0FFF))+'\n');
            if(value & 0x1000)
                listFileSync.at(1)->write(QByteArray::number(4095)+'\n');
            else
                listFileSync.at(1)->write(QByteArray::number(0)+'\n');
            if(value & 0x2000)
                listFileSync.at(2)->write(QByteArray::number(4095)+'\n');
            else
                listFileSync.at(2)->write(QByteArray::number(0)+'\n');
            if(value & 0x4000)
                listFileSync.at(3)->write(QByteArray::number(4095)+'\n');
            else
                listFileSync.at(3)->write(QByteArray::number(0)+'\n');
        }
     }

     fileSync.close();
     for(uint8_t i=0; i < 4; i++){

         (listFileSync[i])->close();

     }


}

///* save SGD version 2 */
//void MainWindow::on_pbSaveSGD_clicked()
//{
//    QString filter = "Meas File(*.meas)";
//    QString path_file = "D:/Tests";
//    QString meas_file = QFileDialog::getOpenFileName(this, "Open a File", path_file, filter);
//    if(meas_file == "")
//        return;

//    qDebug() << "fileName" << meas_file;
//    qDebug() << "fileName" << meas_file.mid(0, meas_file.lastIndexOf("/"));
//    QString dir_meas_file = meas_file.mid(0, meas_file.lastIndexOf("/")+1);

//    Measurement* meas_ = new Measurement(meas_file);
//    //QTime time_between =meas_->getTimeStop() - meas_->getTimeStart();
//    int count_measures = QTime(0,0,0).msecsTo(meas_->getTimeStop()) - QTime(0,0,0).msecsTo(meas_->getTimeStart());
//    qDebug() << "raznost msec" << count_measures;
//    qDebug() << "Time Start" << meas_->getTimeStart();
//    qDebug() << "Time Stop" << meas_->getTimeStop();

//    qDebug() << "num Dwnholes" << meas_->getNumDnHoleModules();
//    qDebug() << "num Upholes" << meas_->getNumUpHoleModules();
//    QDate date_tmp = meas_->getDate();
//    QTime time_tmp = meas_->getTime();

//    uint device_downHoles = 0;       //Количество подземных модулей
//    uint device_UpHoles = 0;
//    uint device_tbf  = 1;
//    uint device_sync = 1;

//    device_downHoles = meas_->getNumDnHoleModules() * 3;
//    device_UpHoles = meas_->getNumUpHoleModules();

//    /* Обработка SGD файлов в один файл */
//    QDir dir(dir_meas_file);
//    dir.setNameFilters(QStringList("*.sgd"));
//    QStringList lis_file = dir.entryList(QDir::Files, QDir::Name);
//    qDebug() << lis_file.count();

//    segd_ = new single_segd_files();
//    segd_->setFileName(dir_meas_file+"fileName.sgd");
//    QStringList lis_file_tmp;
//    /* Проверим на наличие данных в файлах измерений */
//    bool statusFileData = false;
//    for (const auto& filName : qAsConst(lis_file) )
//    {
//        statusFileData = segd_->checkData(dir_meas_file+filName);
//        qDebug() << filName << statusFileData;

//        if(filName.startsWith("DownnHole_device")){
//            if(statusFileData == false)
//                device_downHoles -= 1;
//            else
//                lis_file_tmp.append(filName);
//        }
//        else if(filName.startsWith("UpHole_device")){
//            if(statusFileData == false)
//                device_UpHoles -= 1;

//            else
//                lis_file_tmp.append(filName);
//        }
//        else if(filName.startsWith("Sync_device")){

//            if(statusFileData == false)
//                device_sync = 0;
//            else
//                lis_file_tmp.append(filName);
//        }
//        else if(filName.startsWith("TBF")){

//            if(statusFileData == false)
//                device_tbf = 0;
//            else
//                lis_file_tmp.append(filName);
//        }


//    }
//    /* Определяем количество устройств по названию файлов */
//    uint8_t cnt_chnl_sets = 0;
//    if(device_downHoles) cnt_chnl_sets++;
//    if(device_UpHoles) cnt_chnl_sets++;
//    if(device_sync) cnt_chnl_sets++;
//    if(device_tbf) cnt_chnl_sets++;

//    segd_->setData(date_tmp);
//    segd_->setTime(time_tmp);
//    segd_->setCounterByte(0);
//    segd_->setFileNumber(1);
//    //segd_->setRecordLenght(recLen);   //not used for rev 3.1
//    segd_->setChannelSets(cnt_chnl_sets);    //Количество используемых каналов (sync, tbf...)
//    segd_->write_general_header();
//    segd_->write_general_header_blk2();
//    segd_->write_general_header_blk3();

//    /* Заполняю Header конечного файла */
//    if(device_downHoles){
//        /* Down Holes */
//        segd_->setChannelSetNumber(1);
//        segd_->setChannelSetStartTime(0);
//        segd_->setChannelSetEndTime(0);       //length data
//        segd_->setDataLength(count_measures); //length data
//        segd_->setNumberOfChannels(device_downHoles);
//        segd_->setChannelType((quint8)CHANNELSETS_TYPE_SEIS);
//        segd_->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
//        segd_->setAliasFilterSlope((quint16)1);
//        segd_->write_header();
//    }
//    if(device_UpHoles){
//        /*Up Hole */
//        segd_->setChannelSetNumber(3);
//        segd_->setChannelSetStartTime(0);
//        segd_->setChannelSetEndTime(0);       //length data
//        segd_->setDataLength(count_measures); //length data
//        segd_->setNumberOfChannels(device_UpHoles);
//        segd_->setChannelType((quint8)CHANNELSETS_TYPE_UPHOLE);
//        segd_->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
//        segd_->setAliasFilterSlope((quint16)1);
//        segd_->write_header();
//    }
//    if(device_sync) {
//        /* Sync */
//        segd_->setChannelSetNumber(4);
//        segd_->setChannelSetStartTime(0);
//        segd_->setChannelSetEndTime(0);
//        segd_->setNumberOfChannels(device_sync);
//        segd_->setChannelType((quint8)CHANNELSETS_TYPE_OTHER);
//        segd_->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
//        segd_->setAliasFilterSlope((quint16)1);
//        segd_->write_header();
//    }
//    if(device_tbf){
//        /* TBF */
//        segd_->setChannelSetNumber(2);
//        segd_->setChannelSetStartTime(0);
//        segd_->setChannelSetEndTime(0);       //length data
//        segd_->setDataLength(count_measures); //length data
//        segd_->setNumberOfChannels(device_tbf);
//        segd_->setChannelType((quint8)CHANNELSETS_TYPE_TIMEBREAK);
//        segd_->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
//        segd_->setAliasFilterSlope((quint16)1);
//        segd_->write_header();
//    }
//    /* test */
//    for (int i=0; i<lis_file_tmp.count(); i++) {
//      qDebug() << "2" << lis_file_tmp.at(i);
//       segd_->openFile_test(dir_meas_file +lis_file_tmp.at(i));
//    }
//    delete segd_;

//    segd_ = new single_segd_files();
//    segd_->getHeaderData(dir_meas_file+"fileName.sgd");
//    /* Создаю множество файлов rev 2 */
//    lFileNameRev2.clear();
//    uint32_t max_num_rev2 = 131070;     //msec ~= 2min
//    uint32_t numberOfSamples = segd_->getNumOfSamples();

//    uint32_t cnt_files = numberOfSamples / max_num_rev2;
//    qDebug() << "КОЛИЧЕСТВО sgd файлов " << cnt_files+1;
//    uint32_t end_time = 0xffff;
//    /* Заполнить все segd revision 2.1 шапкой */
//    for (uint32_t cnt = 0; cnt < (cnt_files +1); cnt++) { //+1, так как округление в меньшую сторону
//        lFileNameRev2.append(new single_segd_rev2_files);
//        //lFileNameRev2.at(cnt)->setFileName(fileDir_+"/"+"dir/"+QString::number(cnt) + ".sgd");
//        lFileNameRev2.at(cnt)->setFileName(dir_meas_file+QString::number(cnt) + ".sgd");
//        lFileNameRev2.at(cnt)->setData(date_tmp);
//        lFileNameRev2.at(cnt)->setTime(time_tmp);
//        lFileNameRev2.at(cnt)->setCounterByte(0);
//        lFileNameRev2.at(cnt)->setFileNumber(1);
//        //segd_->setRecordLenght(recLen);   //not used for rev 3.1
//        lFileNameRev2.at(cnt)->setChannelSets(cnt_chnl_sets);    //Количество используемых каналов (sync, tbf...)
//        lFileNameRev2.at(cnt)->write_general_header();
//        lFileNameRev2.at(cnt)->write_general_header_blk2();

//        if(device_downHoles){
//            /* Down Holes */
//            lFileNameRev2.at(cnt)->setChannelSetNumber(1);
//            lFileNameRev2.at(cnt)->setChannelSetStartTime(0);
//            lFileNameRev2.at(cnt)->setChannelSetEndTime(end_time);       //length data
//            lFileNameRev2.at(cnt)->setDataLength(0); //length data
//            lFileNameRev2.at(cnt)->setNumberOfChannels(device_downHoles);
//            lFileNameRev2.at(cnt)->setChannelType((quint8)CHANNELSETS_TYPE_SEIS);
//            lFileNameRev2.at(cnt)->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
//            lFileNameRev2.at(cnt)->setAliasFilterSlope((quint16)1);
//            lFileNameRev2.at(cnt)->write_header();
//        }
//        if(device_UpHoles){
//            /*Up Hole */
//            lFileNameRev2.at(cnt)->setChannelSetNumber(3);
//            lFileNameRev2.at(cnt)->setChannelSetStartTime(0);
//            lFileNameRev2.at(cnt)->setChannelSetEndTime(end_time);       //length data
//            lFileNameRev2.at(cnt)->setDataLength(0); //length data
//            lFileNameRev2.at(cnt)->setNumberOfChannels(device_UpHoles);
//            lFileNameRev2.at(cnt)->setChannelType((quint8)CHANNELSETS_TYPE_UPHOLE);
//            lFileNameRev2.at(cnt)->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
//            lFileNameRev2.at(cnt)->setAliasFilterSlope((quint16)1);
//            lFileNameRev2.at(cnt)->write_header();
//        }
//        if(device_sync) {
//            /* Sync */
//            lFileNameRev2.at(cnt)->setChannelSetNumber(4);
//            lFileNameRev2.at(cnt)->setChannelSetStartTime(0);
//            lFileNameRev2.at(cnt)->setChannelSetEndTime(end_time);
//            lFileNameRev2.at(cnt)->setDataLength(0); //length data
//            lFileNameRev2.at(cnt)->setNumberOfChannels(device_sync);
//            lFileNameRev2.at(cnt)->setChannelType((quint8)CHANNELSETS_TYPE_OTHER);
//            lFileNameRev2.at(cnt)->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
//            lFileNameRev2.at(cnt)->setAliasFilterSlope((quint16)1);
//            lFileNameRev2.at(cnt)->write_header();
//        }
//        if(device_tbf){
//            /* TBF */
//            lFileNameRev2.at(cnt)->setChannelSetNumber(2);
//            lFileNameRev2.at(cnt)->setChannelSetStartTime(0);
//            lFileNameRev2.at(cnt)->setChannelSetEndTime(end_time);       //length data
//            lFileNameRev2.at(cnt)->setDataLength(0); //length data
//            lFileNameRev2.at(cnt)->setNumberOfChannels(device_tbf);
//            lFileNameRev2.at(cnt)->setChannelType((quint8)CHANNELSETS_TYPE_TIMEBREAK);
//            lFileNameRev2.at(cnt)->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
//            lFileNameRev2.at(cnt)->setAliasFilterSlope((quint16)1);
//            lFileNameRev2.at(cnt)->write_header();
//        }

//        lFileNameRev2.at(cnt)->write_extended_header();
//    }


//    uint32_t global_Cnt_samples = 0;
//    uint32_t remainder = numberOfSamples % max_num_rev2;    //сколько остается еще дозабить файл нулями
//    dem_trace_header demux_trace_rev3;

//    uint16_t cnt_meas = device_downHoles+device_UpHoles + device_sync+ device_tbf;
//    for (uint16_t i=0; i< cnt_meas; i++ ) {
//        demux_trace_rev3 = segd_->getDemuxTraceHeader();

//        for (uint32_t cnt = 0; cnt < cnt_files ; cnt++) {
//            lFileNameRev2.at(cnt)->setDemuxTraceHeader(demux_trace_rev3);
//            lFileNameRev2.at(cnt)->open_data(); //для записи
//            for (global_Cnt_samples =0; global_Cnt_samples < max_num_rev2; global_Cnt_samples+=255) //514*255 = 131 070
//            {
//                lFileNameRev2.at(cnt)->writeData(segd_->getDataRev3(255));
//            }
//            lFileNameRev2.at(cnt)->close_data(); //для записи

//        }
//        /* считывание отдельного файла */
//        lFileNameRev2.last()->setDemuxTraceHeader(demux_trace_rev3);
//        QVector<float> vecNull;
//        lFileNameRev2.last()->open_data(); //для записи
//        lFileNameRev2.last()->writeData(segd_->getDataRev3(remainder));
//        /* дозаполню нулями */
//        for(uint i=0; i < (max_num_rev2 - remainder); i++)
//            vecNull.append(0.0);
//        lFileNameRev2.last()->writeData(vecNull);
//        lFileNameRev2.last()->close_data(); //для записи
//    }
//    QApplication::beep();

//}

/* save SGD version 2 */
void MainWindow::on_pbSaveSGD_clicked()
{
    QString filter = "Meas File(*.meas)";
    QString path_file = "D:/Tests";
    QString meas_file = QFileDialog::getOpenFileName(this, "Open a File", path_file, filter);

    if(meas_file == "")
        return;

    qDebug() << "fileName" << meas_file;
    qDebug() << "fileName" << meas_file.mid(0, meas_file.lastIndexOf("/"));
    QString dir_meas_file = meas_file.mid(0, meas_file.lastIndexOf("/")+1);

    Measurement* meas_ = new Measurement(meas_file);
    //QTime time_between =meas_->getTimeStop() - meas_->getTimeStart();
//    int count_measures = QTime(0,0,0).msecsTo(meas_->getTimeStop()) - QTime(0,0,0).msecsTo(meas_->getTimeStart());
//    qDebug() << "raznost msec" << count_measures;
    qDebug() << "Time Start" << meas_->getTimeStart();
    qDebug() << "Time Stop" << meas_->getTimeStop();

    qDebug() << "num Dwnholes" << meas_->getNumDnHoleModules();
    qDebug() << "num Upholes" << meas_->getNumUpHoleModules();
//    QDate date_tmp = meas_->getDate();
//    QTime time_tmp = meas_->getTime();

    uint device_downHoles = 0;       //Количество подземных модулей
    uint device_UpHoles = 0;
    uint device_tbf  = 1;
    uint device_sync = 1;

    device_downHoles = meas_->getNumDnHoleModules() * 3;
    device_UpHoles = meas_->getNumUpHoleModules();

    /* Обработка SGD файлов в один файл */
    int number_files = 0;

    QDir dir(dir_meas_file);
    QStringList lis_file;

    head_rev2_1 header_sgd_rev2_1;

    /* Начинаем проверять наличие файлов и объединять их */
    do{
        lis_file.clear();
        dir.setNameFilters(QStringList(QString::number(number_files) + "*.sgd"));
        lis_file = dir.entryList(QDir::Files, QDir::Name);
        qDebug() << lis_file.count();
        if(lis_file.isEmpty())
            continue;
        segd_ = new single_segd_rev2_files();
        segd_->setFileName(dir_meas_file+QString::number(number_files)+"_meas_.sgd");

        QStringList lis_file_tmp;

        /* Проверим на наличие данных в файлах измерений и запишем в QStringList lis_file_tmp*/
        bool statusFileData = false;
        for (const auto& filName : qAsConst(lis_file) )
        {
            statusFileData = segd_->checkData(dir_meas_file+filName);
            qDebug() << filName << statusFileData;

            if(filName.contains("DownnHole_device")){
                if(statusFileData == false)
                    device_downHoles -= 1;
                else
                    lis_file_tmp.append(filName);
            }
            else if(filName.contains("UpHole_device")){
                if(statusFileData == false)
                    device_UpHoles -= 1;

                else{
                    qDebug() << "name files UpHole" << filName;
                    lis_file_tmp.append(filName);
                }
            }
            else if(filName.contains("Sync_device")){

                if(statusFileData == false)
                    device_sync = 0;
                else
                    lis_file_tmp.append(filName);
            }
            else if(filName.contains("TBF")){

                if(statusFileData == false)
                    device_tbf = 0;
                else
                    lis_file_tmp.append(filName);
            }
        }

        /* Определяем количество устройств по названию файлов */
        uint8_t cnt_chnl_sets = 0;
        if(device_downHoles) cnt_chnl_sets++;
        if(device_UpHoles) cnt_chnl_sets++;
        if(device_sync) cnt_chnl_sets++;
        if(device_tbf) cnt_chnl_sets++;

        /* Запись всех файлов осуществляется при наличии хотя бы 1 подземного модуля,
         * поэтому отсчет данные времени будут взяты из него */

        segd_->getHeaderDataRev2_1(lis_file_tmp.at(0), header_sgd_rev2_1);

        segd_->setData(&header_sgd_rev2_1.gen_head_1.yr, header_sgd_rev2_1.gen_head_1.dy);
        segd_->setTime(&header_sgd_rev2_1.gen_head_1.h, &header_sgd_rev2_1.gen_head_1.mi, &header_sgd_rev2_1.gen_head_1.se);
        segd_->setCounterByte(0);
        segd_->setFileNumber(1);
        segd_->setRecordLenght(1);   //not used for rev 3.1
        segd_->setChannelSets(cnt_chnl_sets);    //Количество используемых каналов (sync, tbf...)
        segd_->write_general_header();
        segd_->write_general_header_blk2();

        if(header_sgd_rev2_1.trace_length_ms > 131070){
            qDebug() << "trace length" << header_sgd_rev2_1.trace_length_ms;
            header_sgd_rev2_1.trace_length_ms = 131070;
        }
        /* Заполняю Header конечного файла */
        if(device_downHoles){
            /* Down Holes */
            segd_->setChannelSetNumber(1);
            segd_->setChannelSetStartTime(0);
            segd_->setChannelSetEndTime(header_sgd_rev2_1.trace_length_ms/2);       //length data
            segd_->setDataLength(0); //length data
            segd_->setNumberOfChannels(device_downHoles);
            segd_->setChannelType((quint8)CHANNELSETS_TYPE_SEIS);
            segd_->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
            segd_->setAliasFilterSlope((quint16)1);
            segd_->write_header();
        }
        if(device_UpHoles){
            /*Up Hole */
            segd_->setChannelSetNumber(3);
            segd_->setChannelSetStartTime(0);
            segd_->setChannelSetEndTime(header_sgd_rev2_1.trace_length_ms/2);       //length data
            segd_->setDataLength(0); //length data
            segd_->setNumberOfChannels(device_UpHoles);
            segd_->setChannelType((quint8)CHANNELSETS_TYPE_UPHOLE);
            segd_->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
            segd_->setAliasFilterSlope((quint16)1);
            segd_->write_header();
        }
        if(device_sync) {
            /* Sync */
            segd_->setChannelSetNumber(4);
            segd_->setChannelSetEndTime(header_sgd_rev2_1.trace_length_ms/2);       //length data
            segd_->setDataLength(0); //length data
            segd_->setNumberOfChannels(device_sync);
            segd_->setChannelType((quint8)CHANNELSETS_TYPE_OTHER);
            segd_->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
            segd_->setAliasFilterSlope((quint16)1);
            segd_->write_header();
        }
        if(device_tbf){
            /* TBF */
            segd_->setChannelSetNumber(2);
            segd_->setChannelSetStartTime(0);
            segd_->setChannelSetEndTime(header_sgd_rev2_1.trace_length_ms/2);       //length data
            segd_->setDataLength(0); //length data
            segd_->setNumberOfChannels(device_tbf);
            segd_->setChannelType((quint8)CHANNELSETS_TYPE_TIMEBREAK);
            segd_->setChannelGainControlMethod((quint8)CHANNELSETS_GAINMODE_FIXED);
            segd_->setAliasFilterSlope((quint16)1);
            segd_->write_header();
        }
        segd_->write_extended_header();
        segd_->setDataLength(header_sgd_rev2_1.trace_length_ms);

        /* test */
        for (int i=0; i<lis_file_tmp.count(); i++) {
          qDebug() << "2" << lis_file_tmp.at(i);
           segd_->openFile_test(dir_meas_file +lis_file_tmp.at(i));
        }

        number_files++;
        delete  segd_;

    }while (!lis_file.isEmpty());

    QApplication::beep();
}


/* Init Sliders */
void MainWindow::initSliders()
{
    ui->sliderDownHole->setValue(50);
    ui->sliderDownHole->setRange(10,100);                       /* range scale graph 10%-100% */
    ui->sliderDownHole->setTickInterval(10);
    ui->sliderDownHole->setSingleStep(10);

    ui->sliderDownHole->setFocusPolicy(Qt::StrongFocus);
    ui->sliderDownHole->setTickPosition(QSlider::TicksBothSides);
    ui->sliderDownHole->installEventFilter(this);               /* Filter need to set tick 10 count */

    //connect(ui->sliderDownHole, SIGNAL(valueChanged(int)), this, SLOT(setGraphRangeDownHoles(int)));

    ui->sliderUpHole->setValue(50);
    ui->sliderUpHole->setRange(10,100);
    ui->sliderUpHole->setTickInterval(5);

    ui->sliderUpHole->setFocusPolicy(Qt::StrongFocus);
    ui->sliderUpHole->setTickPosition(QSlider::TicksBothSides);
    ui->sliderUpHole->setTickInterval(10);
    ui->sliderUpHole->setSingleStep(10);
    ui->sliderUpHole->installEventFilter(this);

    //connect(ui->sliderUpHole, SIGNAL(valueChanged(int)), this, SLOT(setGraphRangeDownHoles(int)));
}

/* If range slider changed, change range Down hole graphics */
void MainWindow::rangeGraphDownHoleChanged(int val)
{
    double tmp = (val*0.01) * max_range_size_24bit;

    for (auto it : listGraphDnHole)
        it->rangeChanged(tmp);
}

/* If range slider changed, change range Up hole graphics */
void MainWindow::rangeGraphUpHoleChanged(int val)
{
    double tmp = (val*0.01) * max_range_size_24bit;

    for (auto it : listGraphGround)
        it->rangeChanged(tmp);


}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if((object == ui->sliderDownHole || object == ui->sliderUpHole) && ui->sliderDownHole->isEnabled())
    {
        QSlider* slider = qobject_cast<QSlider*>(object);
        int change_value = 0;
        if (event->type() == QEvent::MouseButtonPress){
            auto mevent = static_cast<QMouseEvent *>(event);
            int value = slider->minimum() + (slider->maximum() - slider->minimum()) * mevent->localPos().x() / slider->width();
            if (mevent->button() == Qt::LeftButton)
            {
                if (value % 10 >= 5){
                    change_value = value + (10 - (value % 10));
                    slider->setValue(change_value);
                }
                else{
                    change_value = value - (value % 10);
                    slider->setValue(change_value);
                }

                if(object == ui->sliderDownHole){
                    this->rangeGraphDownHoleChanged(change_value);
                }
                else if(object == ui->sliderUpHole){
                    this->rangeGraphUpHoleChanged(change_value);
                }
            }
            event->accept();
            return true;
        }
        if (event->type() == QEvent::MouseMove){
            auto mevent = static_cast<QMouseEvent *>(event);
            int value = slider->minimum() + (slider->maximum() - slider->minimum()) * mevent->localPos().x() / slider->width();
            if (mevent->buttons() & Qt::LeftButton)
            {
                if (value % 10 >= 5){
                    change_value = value + (10 - (value % 10));
                    slider->setValue(change_value);
                }
                else{
                    change_value = value - (value % 10);
                    slider->setValue(change_value);
                }

                if(object == ui->sliderDownHole){
                    this->rangeGraphDownHoleChanged(change_value);
                }
                else if(object == ui->sliderUpHole){
                    this->rangeGraphUpHoleChanged(change_value);
                }

            }
            event->accept();
            return true;
        }
        if (event->type() == QEvent::MouseButtonDblClick)
        {
            event->accept();
            return true;
        }
        if(object == ui->sliderDownHole){

        }
        else if(object == ui->sliderUpHole){

        }
    }
    return QMainWindow::eventFilter(object, event);
}

/* Start Measure */
void MainWindow::on_StartButton_clicked()
{
    CreateProject* newProjWindow = new CreateProject();
    disconnect(newProjWindow, SIGNAL(create(QString, QString)), this, SLOT(newProj(QString, QString)));
    connect(newProjWindow, SIGNAL(create(QString,QString)), this, SLOT(newProj(QString, QString)));
    newProjWindow->show();
}

void MainWindow::on_StopButton_clicked()
{
    proj_->setStopTime();
    transceiver_->setRecord(false);
    transceiver_sync_->setRecord(false);
    transceiver_ground_->setRecord(false); 
}

void MainWindow::newProj(QString name, QString path)
{
    disconnect(proj_, SIGNAL(projectCreated(QString)), this, SLOT(messageProject(QString)));
    disconnect(proj_, SIGNAL(projectCreatedError(QString)), this, SLOT(messageProject(QString)));
    connect(proj_, SIGNAL(projectCreated(QString)), this, SLOT(messageProject(QString)));
    connect(proj_, SIGNAL(projectCreatedError(QString)), this, SLOT(messageProject(QString)));
    connect(proj_, SIGNAL(measPath(int, QString)), this, SLOT(setFileName(int, QString)));

//    connect(transceiverThread_, SIGNAL(started()), transceiver_, SLOT(start()));
//    connect(transceiver_, SIGNAL(connectionClosed()), transceiverThread_, SLOT(quit()));
//    connect(transceiverThread_, SIGNAL(finished()), transceiverThread_, SLOT(deleteLater()));
//    connect(transceiver_, SIGNAL(newDepth(int)), this, SLOT(updateDepth(int)));
//    transceiverThread_->start();

    bool status = proj_->projectCreate(name, path);
    if(proj_->isOpened() == true)
        this->setWindowTitle(QString("TNG \r :: \r") + (QString::fromUtf8("Проект: ") + proj_->projectName().mid(0,proj_->projectName().indexOf("."))));
//    if(status == true)
//        clearRecordList();
    const int COUNT_TYPES_MODULES = 5;
    measId_ = proj_->addMeasurement(COUNT_TYPES_MODULES, numDnMod_, numWellsMod_, timeRecord_, timeSwip_, syncChannel_, syncCMD_, gainDnHole_, gainUpHole_);
    QMap <QString, QString> serviceInfo;
    serviceInfo.insert("Depth", depth_);
    serviceInfo.insert("Operator", operator_);
    serviceInfo.insert("NumHole", numHole_);
    serviceInfo.insert("NameArea", nameArea_);
    serviceInfo.insert("DistBtwDevices", distBtwDevices_);
    proj_->onUpdateServiceInfo(measId_ + 1, serviceInfo);

    transceiver_->send_start();

}

