#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QList>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    qRegisterMetaType<pointFromDownHoles>("pointFromDownHoles");
    numDnMod_ = 0;
    numWellsMod_ = 0;

    transceiver_ = new Transceiver_class();
    transceiver_->initialize(ADDRESS_, PORT_);
    transceiverThread_ = new QThread();
    transceiver_->moveToThread(transceiverThread_);
    connect(transceiverThread_, SIGNAL(started()), transceiver_, SLOT(start()));
    connect(transceiver_, SIGNAL(connectionClosed()), transceiverThread_, SLOT(quit()));
    connect(transceiverThread_, SIGNAL(finished()), transceiverThread_, SLOT(deleteLater()));
    connect(transceiver_, SIGNAL(newDepth(int)), this, SLOT(updateDepth(int)));
    transceiverThread_->start();

    transceiver_ground_ = new Transceiver_ground();
    transceiver_ground_->initialize(ADDRESS_GROUND_, PORT_GROUND_);
    transceiverGroundThread_ = new QThread();
    transceiver_ground_->moveToThread(transceiverGroundThread_);
    connect(transceiverGroundThread_, SIGNAL(started()), transceiver_ground_, SLOT(start()));
    connect(transceiver_ground_, SIGNAL(message(QString)), this, SLOT(messageProject(QString)));
    transceiverGroundThread_->start();

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
    connect(settingsWidget_, SIGNAL(stopGround()), transceiver_ground_, SLOT(send_Stop()));
//    connect(settingsWidget_, SIGNAL(stopSync()), this, SLOT(stopSync()));

    /* График real-time модуля синхронизации */
    syncPlot_ = new(graphSync);
    ui->gridLayout->addWidget(syncPlot_);
    //syncPlot_->plot();
    syncPlot_->test();

    testPlot_ = new plotDoubleGraph(transceiver_ground_, transceiver_);
    ui->gridLayout->addWidget(testPlot_);
    testPlot_->setTraceDnHole();
    testPlot_->initGraphXYZ();
    testPlot_->conectSignals();


    /* Виджет легенды real-time модуля синхронизации */
//    listPaintLegend.append(new (PaintLegend));
//    listPaintLegend.at(0)->setMod(syncMod);

//    QPalette pal(listPaintLegend.at(0)->palette());
//    ui->gridLayout->addWidget(listPaintLegend.at(0));

    onUpdateSettings();
    //plotWidgetLayout();

    /* В будущем: запись проектовой инфы в файл */
//    connect(transceiver_, SIGNAL(data_update(int,pointFromDownHoles)),  this,
//            SLOT(slot_data_update(int,pointFromDownHoles)));

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

}

MainWindow::~MainWindow()
{
    delete syncPlot_;
    delete transceiver_;
    for(int i=0; i < listGraphGround.count(); i++)
        delete  listGraphGround.at(0);

    for(int i=0; i < listGraphDnHole.count(); i++)
        delete  listGraphDnHole.at(0);

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

void MainWindow::plotWidgetLayout()
{
    /* График real-time для подземных модулей */
    for(int i=0; i < numDnMod_; i++)
        listGraphDnHole.append(new graphDownHole(transceiver_));

    ui->gridLayout->setSpacing(0);
    for(int i=0; i<listGraphDnHole.count(); i++)
    {
        ui->gridLayout->addWidget(listGraphDnHole.at(i));
        /* ширина построения */
        listGraphDnHole.at(i)->setWidth(500);
        /* Передача номера модуля */
        listGraphDnHole.at(i)->setModNum(i);
        /*Стираем старые данные */
        listGraphDnHole.at(i)->clearData();
        /*Выбираем необходимый модуль для данных */
        listGraphDnHole.at(i)->setTraceDnHole();
        listGraphDnHole.at(i)->initGraphXYZ();
    }
//-------------------------------------------//
    /* Widget real-time наземных модулей - геофонов */
    for(int i=0; i < numWellsMod_; i++)
        listGraphGround.append(new graphGround(transceiver_ground_));

    for(int i=0; i<listGraphGround.count(); i++)
    {
        ui->gridLayout->addWidget(listGraphGround.at(i));
        /* Передача номера устройства */
        listGraphGround.at(i)->setDevNum(i+1);
        /* ширина построения */
        listGraphGround.at(i)->setWidth(500);
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

    sizeList_ = listGraphGround.size();
    for(int i=0; i < sizeList_; i++)
    {
        ui->gridLayout->removeWidget(listGraphGround.at(0));
        delete  listGraphGround.at(0);
        listGraphGround.removeAt(0);
    }
    sizeList_ = listGraphDnHole.size();
    for(int i=0; i < sizeList_; i++)
    {
        ui->gridLayout->removeWidget(listGraphDnHole.at(0));
        delete  listGraphDnHole.at(0);
        listGraphDnHole.removeAt(0);
    }

}
void MainWindow::setGainGroundHole(quint8 value)
{
    transceiver_ground_->send_Settings_KU(value);
    qInfo(qUtf8Printable(QString("КУ наземных модулей %1").arg(value)));
}

void MainWindow::setGainDnHole(int value)
{
    transceiver_->on_tool_set_KU(value);
    qInfo(qUtf8Printable(QString("КУ скважинных модулей %1").arg(value)));
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
    quint8 ku = 1;
    for(auto it = value.vecGainGroundModules.cbegin(); it < value.vecGainGroundModules.cend(); it++)
        if((*it) >= 1)
        {
            ku = *it;
           // setGainUpHole(true, 0, ku);
            setGainGroundHole(ku);
            break;
        }

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

void MainWindow::on_pushButton_clicked()
{

     QString file_name_Gr =QString("D:/Test/Gr.txt");
     QFile fileGr(file_name_Gr);

      if(!fileGr.open(QFile::ReadOnly|QFile::Text)) //Открываем для чтения, если нельзя открыть: переходим к следующему
      {
         return;
      }
      QVector<double> yGround, yDwnHole;

      /*----------------------------------------------------------*/
      /*Read Ground Holes */
      /*----------------------------------------------------------*/
      volatile int device_id = -1;
      QString  tmp_str_iVal;  //Считываемое String
      QString  str_iVal;
      int32_t value = 0;
      int32_t tmp1 =0;
      int32_t tmp2 = 0;
      QString hand_package_str_1 = "ed00ff";
      while(!fileGr.atEnd()) // leave, if End of file
      {
         bool ok;
         tmp_str_iVal = fileGr.read(8);        //read 2 bytes + 2 bytes
         if(tmp_str_iVal.startsWith(hand_package_str_1,Qt::CaseInsensitive))  //Start of the package
         {
             //Device ID
              device_id = tmp_str_iVal.right(2).toInt();
         }

         else
         {
             tmp1 = tmp_str_iVal.left(4).toInt(&ok,16);
             tmp2 = tmp_str_iVal.right(4).toInt(&ok,16);
             value = (tmp1 << 16) | (tmp2);

             switch(device_id)
             {
             case 0:

                 break;
             case 1:
                 yGround.append(value);
                 break;

             }
         }
      }
      fileGr.close();
      /*----------------------------------------------------------*/



      /*----------------------------------------------------------*/
      /* Read Down Holes */
      /*----------------------------------------------------------*/
      QString file_name_Dn =QString("D:/Test/Dn.txt");
      QFile fileDn(file_name_Dn);

       if(!fileDn.open(QFile::ReadOnly|QFile::Text)) //Открываем для чтения, если нельзя открыть: переходим к следующему
       {
          return;
       }

       QByteArray tmp;
       while(!fileDn.atEnd()) //Считываем файл, пока не считаем весь файл
       {
           bool ok;
           tmp = fileDn.readLine().simplified();

           value = tmp.toInt(&ok, 10);
                   yDwnHole.append(value);


       }

       fileDn.close();
       /*----------------------------------------------------------*/

       int  begin = ui->lineEditBeginPlot->text().toInt();
       int count = ui->lineEditMaxCount->text().toInt();

       int32_t maxGr=0, maxDnHoles=0;
       maxGr = yGround.size();
       maxDnHoles = yDwnHole.size();

       int shiftPlot = 0;

       if(maxGr > maxDnHoles)   maxGr = maxDnHoles;



       if(maxGr > count)
       {
           maxGr = count;
           shiftPlot = begin;
       }
       else
       {

       }
       QVector <double> newYGround, newYDnHoles;
       QVector<double> xModules_;
       for(int i=begin; i < maxGr+shiftPlot; i++)
       {
           xModules_.append(i);
           newYGround.append(yGround[i]);
           newYDnHoles.append(yDwnHole[i]);
       }

       ui->plotFromFile->clearGraphs();
       ui->plotFromFile->addGraph(); // blue line
       ui->plotFromFile->graph(0)->setPen(QPen(QColor(40, 110, 255)));
       ui->plotFromFile->addGraph(); // red line
       ui->plotFromFile->graph(1)->setPen(QPen(QColor(255, 110, 40)));


       ui->plotFromFile->yAxis->setTicks(0);

       ui->plotFromFile->legend->setVisible(true);
       QFont legendFont = font();
       legendFont.setPointSize(10);
       ui->plotFromFile->legend->setFont(legendFont);
       ui->plotFromFile->legend->setSelectedFont(legendFont);
       ui->plotFromFile->legend->setSelectableParts(QCPLegend::spNone);

       ui->plotFromFile->graph(0)->setName(QString("Наземный"));
       ui->plotFromFile->graph(1)->setName(QString("Скважин"));

       ui->plotFromFile->graph(0)->setData(xModules_, newYGround);
       ui->plotFromFile->graph(1)->setData(xModules_, newYDnHoles);

       ui->plotFromFile->rescaleAxes();

       ui->plotFromFile->replot();





}
