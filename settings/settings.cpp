#include "settings.h"
#include "ui_settings.h"


Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    lineEditTimeRecord_ = new QLineEdit();
    lineEditTimeWaiting_ = new QLineEdit();
    labelSaveMod_ = new QLabel("Сохранение расчетов в папку по умолчанию");

    setStyleTextSheet();

    dir_ = QDir::currentPath();
    settings_ = new QSettings(fileName_ , QSettings::IniFormat, this);
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    settings_->setIniCodec(codec);

    numDnMod_ = 6;
    numWellsMod_ = 8;
    timeRecord_ = 3;
    countRecord_ = 5;
    timeWaiting_ = 1000;
    depth_ = "";
    operatorName_= "";
    numHole_= "";
    nameArea_= "";
    isDefaultSavingPath_ = false;
    isPaintZeroLines_ = false;
    //syncCMD_ = ui->comboBoxCMD->currentText();
    if(ui->comboBoxCMD->currentText() == cmdS)
        syncCMD_ = "S";
    else  if(ui->comboBoxCMD->currentText() == cmdA)
        syncCMD_ = "A";

    if(ui->comboBoxChannel->currentText() == vibroSource)
        syncChannel_ = "V";
    else  if(ui->comboBoxChannel->currentText() == detonationSource)
        syncChannel_ = "F";
    swipLen_ = 10;
//    timerStartUpHole_.setInterval(500);
//    connect(&timerStartUpHole_, QTimer::timeout, [=]() {
//        emit startGround();
//        timerStartUpHole_.stop();
//        qDebug() << "startUpHole";
//    });

    offsetDnHoleModemOn_ = 10;
    offsetDnHoleModemOff_ = 7;
    offsetUpHole_ = -10;

    readSettings();

    ui->lineEditCountRecord->setText(QString::number(countRecord_));
    ui->lineEditNumDnMod->setText(QString::number(numDnMod_));
    ui->lineEditNumWellsMod->setText(QString::number(numWellsMod_));
    ui->lineSwipLen->setText(QString::number(swipLen_));
    lineEditTimeRecord_->setText(QString::number(timeRecord_));
    lineEditTimeWaiting_->setText(QString::number(timeWaiting_));
    ui->comboBoxCorDraw->setCurrentIndex(ui->comboBoxCorDraw->findText(corrDraw_));
    ui->comboBoxCorDraw->setVisible(false);
    ui->checkBoxSaveMod->setCheckState(isDefaultSavingPath_ == true ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    ui->checkBoxZeroLines->setCheckState(isPaintZeroLines_ == true ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    ui->checkBoxModem->setCheckState(isModemOn_ == true ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    ui->lineEditDepth->setText(depth_);
    ui->lineEditOperator->setText(operatorName_);
    ui->lineEditNumHole->setText(numHole());
    ui->lineEditNameArea->setText(nameArea_);
    ui->lineEditDistBtwDevices->setText(distBtwDevices_);

    //    ui->comboBoxCMD->setCurrentIndex(ui->comboBoxCMD->findText(syncCMD()));
    if(syncCMD() == "S")
        ui->comboBoxCMD->setCurrentIndex(ui->comboBoxCMD->findText(cmdS));
    else if(syncCMD() == "A")
        ui->comboBoxCMD->setCurrentIndex(ui->comboBoxCMD->findText(cmdA));

    if(syncChannel() == "V")
        ui->comboBoxChannel->setCurrentIndex(ui->comboBoxChannel->findText(vibroSource));
    else if(syncChannel() == "F")
        ui->comboBoxChannel->setCurrentIndex(ui->comboBoxChannel->findText(detonationSource));
    emit updateSettings();
    if(corrDraw_ != "Корреляция 2"){
        //ui->labelSaveMod->setVisible(false);
        //ui->checkBox->setVisible(false);

        //ui->lineSwipLen->setVisible(false);
        //ui->labelCorSave->setEnabled(false);
        //    ui->lineSwipLen->setEnabled(false);
        //ui->labelSwipTime->setVisible(false);
    }
    //   this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint);
}

Settings::~Settings()
{
    delete ui;
    writeSettings();
    this->destroy();
    //delete settings_;
}

void Settings::setStyleTextSheet()
{
    this->setStyleSheet("background-color: #ffffff; font-family: Arial; font-size: 16pt;");
    ui->gridLayout_4->addWidget(lineEditTimeRecord_,0,3,1,2);
    ui->gridLayout_4->addWidget(lineEditTimeWaiting_,2,3,1,2);
    ui->gridLayout_2->addWidget(labelSaveMod_,2,1,1,3);

    QString styleSheet = "color: rgb(50, 50, 50); border: NONE; font-family: Arial; font-size: 11pt; font-weight: 470;";
    ui->labelChannel->setStyleSheet(styleSheet);
    ui->labelCmd->setStyleSheet(styleSheet);
    ui->labelCountRecord->setStyleSheet(styleSheet);
    ui->labelNumDnMod->setStyleSheet(styleSheet);
    ui->labelNumWellsMod->setStyleSheet(styleSheet);
    ui->labelTime1->setStyleSheet(styleSheet);
    ui->labelSwipTime->setStyleSheet(styleSheet);
    ui->labelTime2->setStyleSheet(styleSheet);
    ui->labelTimeRecord->setStyleSheet(styleSheet);
    ui->labelTimeWaiting->setStyleSheet(styleSheet);
    ui->labelDistBtwDevices->setStyleSheet(styleSheet);
    labelSaveMod_->setStyleSheet(styleSheet);
    ui->labelCorSave->setStyleSheet(styleSheet);
    ui->labelDepth->setStyleSheet(styleSheet);
    ui->labelOperator->setStyleSheet(styleSheet);
    ui->labelNumHole->setStyleSheet(styleSheet);
    ui->labelNameArea->setStyleSheet(styleSheet);
    ui->labelZeroLines->setStyleSheet(styleSheet);
    ui->labelModem->setStyleSheet(styleSheet);

    ui->lineEditCountRecord->setMaximumSize(45,20);
    ui->lineSwipLen->setMaximumSize(65+30,20);
    ui->lineEditNumDnMod->setMaximumSize(45,20);
    ui->lineEditNumWellsMod->setMaximumSize(45,20);
    lineEditTimeRecord_->setMaximumSize(75,20);
    lineEditTimeWaiting_->setMaximumSize(75,20);
    ui->lineEditDepth->setMaximumSize(65+30*2,20);
    ui->lineEditOperator->setMaximumSize(65+30*2,20);
    ui->lineEditNumHole->setMaximumSize(65+30*2,20);
    ui->lineEditNameArea->setMaximumSize(65+30*2,20);
    ui->lineEditDistBtwDevices->setMaximumSize(65+30*2,20);

    ui->lineEditCountRecord->setMinimumSize(45,20);
    ui->lineSwipLen->setMinimumSize(65+30,20);
    ui->lineEditNumDnMod->setMinimumSize(45,20);
    ui->lineEditNumWellsMod->setMinimumSize(45,20);
    lineEditTimeRecord_->setMinimumSize(75,20);
    lineEditTimeWaiting_->setMinimumSize(75,20);
    ui->lineEditDepth->setMinimumSize(65+30*2,20);
    ui->lineEditOperator->setMinimumSize(65+30*2,20);
    ui->lineEditNumHole->setMinimumSize(65+30*2,20);
    ui->lineEditNameArea->setMinimumSize(65+30*2,20);
    ui->lineEditDistBtwDevices->setMinimumSize(65+30*2,20);

    ui->toolButtonNumDnModMin->setMaximumSize(30,20);
    ui->toolButtonNumDnModPlus->setMaximumSize(30,20);
    ui->toolButtonCountRecordMin->setMaximumSize(30,20);
    ui->toolButtonNumWellsModMin->setMaximumSize(30,20);
    ui->toolButtonCountRecordPlus->setMaximumSize(30,20);
    ui->toolButtonNumWellsModPlus->setMaximumSize(30,20);

    ui->toolButtonNumDnModMin->setMinimumSize(30,20);
    ui->toolButtonNumDnModPlus->setMinimumSize(30,20);
    ui->toolButtonCountRecordMin->setMinimumSize(30,20);
    ui->toolButtonNumWellsModMin->setMinimumSize(30,20);
    ui->toolButtonCountRecordPlus->setMinimumSize(30,20);
    ui->toolButtonNumWellsModPlus->setMinimumSize(30,20);

    ui->labelCountRecord->setAlignment(Qt::AlignLeft);
    ui->labelNumDnMod->setAlignment(Qt::AlignLeft);
    ui->labelNumWellsMod->setAlignment(Qt::AlignLeft);
    ui->labelTime1->setAlignment(Qt::AlignRight);
    ui->labelSwipTime->setAlignment(Qt::AlignRight);
    ui->labelTime2->setAlignment(Qt::AlignRight);
    ui->labelTimeRecord->setAlignment(Qt::AlignLeft);
    ui->labelTimeWaiting->setAlignment(Qt::AlignLeft);
    ui->labelDistBtwDevices->setAlignment(Qt::AlignLeft);

    styleSheet = "background-color: #ffffff; color: rgb(24, 121, 155); border-width: 1px; border-style: solid; border-color: rgb(181, 181, 181); font-family: Arial; font-size: 11pt; font-weight: 450;";
    lineEditTimeRecord_->setStyleSheet(styleSheet);
    lineEditTimeWaiting_->setStyleSheet(styleSheet);
    ui->lineSwipLen->setStyleSheet(styleSheet);
    ui->lineEditDepth->setStyleSheet(styleSheet);
    ui->lineEditOperator->setStyleSheet(styleSheet);
    ui->lineEditNumHole->setStyleSheet(styleSheet);
    ui->lineEditNameArea->setStyleSheet(styleSheet);
    ui->lineEditDistBtwDevices->setStyleSheet(styleSheet);

    styleSheet = "background-color: #ffffff; color: rgb(24, 121, 155); border-width: 1px; border-style: solid; border-color: rgb(181, 181, 181); border-left: NONE; border-right: NONE; font-family: Arial; font-size: 11pt; font-weight: 450;";
    ui->lineEditCountRecord->setStyleSheet(styleSheet);
    ui->lineEditNumDnMod->setStyleSheet(styleSheet);
    ui->lineEditNumWellsMod->setStyleSheet(styleSheet);

    ui->lineEditCountRecord->setAlignment(Qt::AlignCenter);
    ui->lineSwipLen->setAlignment(Qt::AlignCenter);
    ui->lineEditNumDnMod->setAlignment(Qt::AlignCenter);
    ui->lineEditNumWellsMod->setAlignment(Qt::AlignCenter);
    lineEditTimeRecord_->setAlignment(Qt::AlignCenter);
    lineEditTimeWaiting_->setAlignment(Qt::AlignCenter);
    ui->lineEditDepth->setAlignment(Qt::AlignCenter);
    ui->lineEditOperator->setAlignment(Qt::AlignCenter);
    ui->lineEditNumHole->setAlignment(Qt::AlignCenter);
    ui->lineEditNameArea->setAlignment(Qt::AlignCenter);
    ui->lineEditDistBtwDevices->setAlignment(Qt::AlignCenter);

    ui->toolButtonNumDnModMin->setText("–");
    ui->toolButtonCountRecordMin->setText("–");
    ui->toolButtonNumWellsModMin->setText("–");
    ui->toolButtonNumDnModPlus->setText("+");
    ui->toolButtonCountRecordPlus->setText("+");
    ui->toolButtonNumWellsModPlus->setText("+");

    ui->comboBoxCMD->setMaximumSize(65+30*2,20);
    ui->comboBoxCMD->setMinimumSize(65+30*2,20);
    ui->comboBoxChannel->setMaximumSize(65+30*2,20);
    ui->comboBoxChannel->setMinimumSize(65+30*2,20);
    ui->comboBoxCorDraw->setMinimumSize(65+30*2,20);
    ui->comboBoxCorDraw->setMaximumSize(65+30*2,20);
    ui->buttonStopSync->setMaximumSize(65+30*2,20);
    ui->buttonStopSync->setMinimumSize(65+30*2,20);

    styleSheet = "color: rgb(50, 50, 50); border: NONE; font-family: Arial; font-size: 12pt; font-weight: 470;";
    ui->label->setStyleSheet(styleSheet);
    ui->label_2->setStyleSheet(styleSheet);
    ui->label_3->setStyleSheet(styleSheet);
    ui->labelCorr->setStyleSheet(styleSheet);
    ui->labelServiceInfo->setStyleSheet(styleSheet);

    styleSheet = "background-color: #ffffff; color: #18799b; border-width: 1px; border-style: solid; border-color: #18799b; font-family: Arial; font-size: 12pt; font-weight: 450; border-radius: 2px;";
    ui->pushButton_2->setStyleSheet(styleSheet);
    styleSheet = "background-color: #18799b; color: #ffffff; border-width: 1px; border-style: solid; border-color: rgb(181,181,181); font-family: Arial; font-size: 12pt; font-weight: 450; border-radius: 1;";
    ui->pushButton_3->setStyleSheet(styleSheet);

    styleSheet = "background-color: #ffffff; color: #18799b; border-width: 1px; border-style: solid; border-color: rgb(181,181,181); font-family: Arial; font-size: 12pt; font-weight: 600; border-radius: 1px 0 0 1px;";
    ui->toolButtonNumDnModMin->setStyleSheet(styleSheet);
    ui->toolButtonCountRecordMin->setStyleSheet(styleSheet);
    ui->toolButtonNumWellsModMin->setStyleSheet(styleSheet);

    styleSheet = "background-color: #ffffff; color: #18799b; border-width: 1px; border-style: solid; border-color: rgb(181,181,181); font-family: Arial; font-size: 12pt; font-weight: 520; border-radius: 0 1;";
    ui->toolButtonNumDnModPlus->setStyleSheet(styleSheet);
    ui->toolButtonCountRecordPlus->setStyleSheet(styleSheet);
    ui->toolButtonNumWellsModPlus->setStyleSheet(styleSheet);

    styleSheet = "color: rgb(24, 121, 155); font-family: Arial; font-size: 11pt; border-width: 1px; border-style: solid; border-color: rgb(181,181,181);";
    ui->comboBoxCMD->setEditable(true);
    ui->comboBoxCMD->lineEdit()->setReadOnly(true);
    ui->comboBoxCMD->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->comboBoxCMD->addItem(cmdS);
    ui->comboBoxCMD->addItem(cmdA);
    //    ui->comboBoxCMD->addItem("R");

    for (int i = 0 ; i < ui->comboBoxCMD->count() ; ++i)
        ui->comboBoxCMD->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    //    ui->comboBoxCMD->setCurrentIndex(ui->comboBoxCMD->findText(cmdS));

    ui->comboBoxChannel->setEditable(true);
    ui->comboBoxChannel->lineEdit()->setReadOnly(true);
    ui->comboBoxChannel->lineEdit()->setAlignment(Qt::AlignCenter);
    //    ui->comboBoxChannel->addItem("F");
    //    ui->comboBoxChannel->addItem("V");
    ui->comboBoxChannel->addItem(detonationSource);
    ui->comboBoxChannel->addItem(vibroSource);
    for (int i = 0 ; i < ui->comboBoxChannel->count() ; ++i)
        ui->comboBoxChannel->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    //    ui->comboBoxChannel->setCurrentIndex(ui->comboBoxChannel->findText(vibroSource));

    //    ui->comboBoxCorDraw->setEditable(true);
    //    ui->comboBoxCorDraw->lineEdit()->setReadOnly(true);
    //    ui->comboBoxCorDraw->lineEdit()->setAlignment(Qt::AlignCenter);
    //    ui->comboBoxCorDraw->addItem("Оригинал");
    //    ui->comboBoxCorDraw->addItem("Вз.корреляция");
    //    ui->comboBoxCorDraw->addItem("Корреляция 2");
    //    for (int i = 0 ; i < ui->comboBoxCorDraw->count() ; ++i)
    //        ui->comboBoxCorDraw->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    //    ui->comboBoxCorDraw->setCurrentIndex(ui->comboBoxCorDraw->findText("Оригинал"));
}

int Settings::swipLen() const
{
    return swipLen_;
}

QString Settings::syncChannel() const
{
    return syncChannel_;
}

QString Settings::syncCMD() const
{
    return syncCMD_;
}

int Settings::timeWaiting() const
{
    return timeWaiting_;
}

void Settings::setPosition(QPoint pos)
{
    Q_UNUSED(pos);
    //  pos.setX(pos.x() - this->width());

    //   move(pos);
}

int Settings::countRecord() const
{
    return countRecord_;
}

int Settings::timeRecord() const
{
    return timeRecord_;
}

int Settings::numWellsMod() const
{
    return numWellsMod_;
}

int Settings::numDnMod() const
{
    return numDnMod_;
}

void Settings::readSettings()
{
    settings_->beginGroup("Modules");
    numDnMod_ = settings_->value("NumDownModules", QString::number(numDnMod_)).toInt();
    numWellsMod_ = settings_->value("NumWellsModules", QString::number(numWellsMod_)).toInt();
    settings_->endGroup();

    settings_->beginGroup("Record");
    timeRecord_ = settings_->value("TimeRecord", QString::number(timeRecord_)).toInt();
    countRecord_ = settings_->value("CountRerods", QString::number(countRecord_)).toInt();
    timeWaiting_ = settings_->value("TimeWaiting", QString::number(timeWaiting_)).toInt();
    settings_->endGroup();

    settings_->beginGroup("Sync");
    syncCMD_ = settings_->value("Cmd", syncCMD_).toString();
    //    QString tmp = settings_->value("Cmd", ui->comboBoxCMD->currentText()).toString();
    //    if(tmp == cmdS)
    //        syncCMD_ = "S";
    //    else     if(tmp == cmdA)
    //        syncCMD_ = "A";
    syncChannel_ = settings_->value("Channel", syncChannel_).toString();

    //    tmp = settings_->value("Channel", ui->comboBoxChannel->currentText()).toString();
    //    if(tmp == detonationSource)
    //        syncChannel_ = "F";
    //    else     if(tmp == vibroSource)
    //        syncChannel_ = "V";
    settings_->endGroup();

    settings_->beginGroup("ServiceInfo");
    depth_ = settings_->value("Depth", depth_).toString();
    operatorName_ = settings_->value("Operator", operatorName_).toString();
    numHole_ = settings_->value("NumHole", numHole()).toString();
    nameArea_ = settings_->value("NameArea", nameArea()).toString();
    distBtwDevices_ = settings_->value("DistBtwDevices", distBtwDevices()).toString();
    settings_->endGroup();

    settings_->beginGroup("Optional");
    corrDraw_ = settings_->value("Draw", ui->comboBoxCorDraw->currentText()).toString();
    swipLen_ = settings_->value("SwipLength", QString::number(swipLen_)).toInt();
    isDefaultSavingPath_ = settings_->value("SavingPath", ui->checkBoxSaveMod->checkState() == Qt::CheckState::Checked ? true : false).toBool();
    isPaintZeroLines_ = settings_->value("PaintZeroLines", ui->checkBoxZeroLines->checkState() == Qt::CheckState::Checked ? true : false).toBool();
    settings_->endGroup();

//    settings_->beginGroup("Modem");
//    isModemOn_ = settings_->value("State", ui->checkBoxZeroLines->checkState() == Qt::CheckState::Checked ? true : false).toBool();
//    int tmpVal = -1;
//    tmpVal = settings_->value("OffsetDnHoleModemOff", QString::number(offsetDnHoleModemOff_)).toInt();
//    offsetDnHoleModemOff_ = tmpVal > 0 ? (tmpVal < 50 ? tmpVal : offsetDnHoleModemOff_) : offsetDnHoleModemOff_;
//    tmpVal = settings_->value("OffsetDnHoleModemOn", QString::number(offsetDnHoleModemOn_)).toInt();
//    offsetDnHoleModemOn_ = tmpVal > 0 ? (tmpVal < 50 ? tmpVal : offsetDnHoleModemOn_) : offsetDnHoleModemOn_;
//    tmpVal = settings_->value("OffsetUpHole", QString::number(offsetUpHole_)).toInt();
//    offsetUpHole_ = tmpVal > -50 ? (tmpVal < 50 ? tmpVal : offsetUpHole_) : offsetUpHole_;
//    settings_->endGroup();
}

void Settings::writeSettings()
{
    settings_->beginGroup("Modules");
    settings_->setValue("NumDownModules", QString::number(numDnMod_));
    settings_->setValue("NumWellsModules", QString::number(numWellsMod_));
    settings_->endGroup();

    settings_->beginGroup("Record");
    settings_->setValue("TimeRecord", QString::number(timeRecord_));
    settings_->setValue("CountRerods", QString::number(countRecord_));
    settings_->setValue("TimeWaiting", QString::number(timeWaiting_));
    settings_->endGroup();

    settings_->beginGroup("Sync");
    //  if(syncCMD_.size() > 0)
    settings_->setValue("Cmd", syncCMD_);
    //  if(syncChannel_.size() > 0)
    settings_->setValue("Channel", syncChannel_);
    settings_->endGroup();

    settings_->beginGroup("ServiceInfo");
    settings_->setValue("Depth", depth_);
    settings_->setValue("Operator", operatorName_);
    settings_->setValue("NumHole", numHole_);
    settings_->setValue("NameArea", nameArea_);
    settings_->setValue("DistBtwDevices", distBtwDevices_);
    settings_->endGroup();

    settings_->beginGroup("Optional");
    settings_->setValue("Draw", corrDraw_);
    settings_->setValue("SwipLength", QString::number(swipLen_));
    settings_->setValue("SavingPath", isDefaultSavingPath_);
    settings_->setValue("PaintZeroLines", isPaintZeroLines_);
    settings_->endGroup();

    settings_->beginGroup("Modem");
    settings_->setValue("State", isModemOn_);
    settings_->setValue("OffsetDnHoleModemOff", offsetDnHoleModemOff());
    settings_->setValue("OffsetDnHoleModemOn", offsetDnHoleModemOn());
    settings_->setValue("OffsetUpHole", offsetUpHole());
    settings_->endGroup();
}

QString Settings::editVal(bool flag, QString inVal)
{
    bool *isInt = new bool();
    *isInt = false;
    int tmp = inVal.toInt(isInt);
    if(*isInt == false)
        return "";
    delete isInt;
    if (flag == false)
        tmp--;
    if(flag == true)
        tmp++;
    if(tmp < 1)
        return "";
    else
        return QString::number(tmp);
}

int Settings::offsetUpHole() const
{
    return offsetUpHole_;
}

void Settings::setOffsetUpHole(int offsetUpHole)
{
    offsetUpHole_ = offsetUpHole;
}

int Settings::offsetDnHoleModemOff() const
{
    return offsetDnHoleModemOff_;
}

void Settings::setOffsetDnHoleModemOff(int offsetDnHoleModemOff)
{
    offsetDnHoleModemOff_ = offsetDnHoleModemOff;
}

int Settings::offsetDnHoleModemOn() const
{
    return offsetDnHoleModemOn_;
}

void Settings::setOffsetDnHoleModemOn(int offsetDnHoleModemOn)
{
    offsetDnHoleModemOn_ = offsetDnHoleModemOn;
}

QString Settings::distBtwDevices() const
{
    return distBtwDevices_;
}

void Settings::setDistBtwDevices(const QString &distBtwDevices)
{
    distBtwDevices_ = distBtwDevices;
}

bool Settings::isPaintZeroLines() const
{
    return isPaintZeroLines_;
}

void Settings::setIsPaintZeroLines(bool isPaintZeroLines)
{
    isPaintZeroLines_ = isPaintZeroLines;
}

bool Settings::isDefaultSavingPath() const
{
    return isDefaultSavingPath_;
}

void Settings::setIsDefaultSavingPath(bool isDefaultSavingPath)
{
    isDefaultSavingPath_ = isDefaultSavingPath;
}

QString Settings::operatorName() const
{
    return operatorName_;
}

void Settings::setOperatorName(const QString &operatorName)
{
    operatorName_ = operatorName;
}

QString Settings::nameArea() const
{
    return nameArea_;
}

void Settings::setNameArea(const QString &nameArea)
{
    nameArea_ = nameArea;
}

QString Settings::numHole() const
{
    return numHole_;
}

void Settings::setNumHole(const QString &numHole)
{
    numHole_ = numHole;
}

QString Settings::depth() const
{
    return depth_;
}

void Settings::setDepth(const QString &depth)
{
    depth_ = depth;
}

void Settings::setCorrDraw(const QString &corrDraw)
{
    //qDebug() << corrDraw;
    corrDraw_ = corrDraw;
    settings_->beginGroup("Optional");
    settings_->setValue("Draw", corrDraw_);
    settings_->endGroup();
}

QString Settings::corrDraw() const
{
    return corrDraw_;
}

QString Settings::corrSave() const
{
    return corrSave_;
}

void Settings::setCorrSave(const QString &corrSave)
{
    corrSave_ = corrSave;
}

void Settings::onUpdateParametres()
{
    readSettings();
}

void Settings::on_pushButton_2_clicked()
{
    this->hide();
    ui->lineEditCountRecord->setText(QString::number(countRecord_));
    ui->lineSwipLen->setText(QString::number(swipLen_));
    ui->lineEditNumDnMod->setText(QString::number(numDnMod_));
    ui->lineEditNumWellsMod->setText(QString::number(numWellsMod_));
    lineEditTimeRecord_->setText(QString::number(timeRecord_));
    lineEditTimeWaiting_->setText(QString::number(timeWaiting_));
    //    ui->comboBoxCMD->setCurrentIndex(ui->comboBoxCMD->findText(syncCMD()));
    if(syncCMD() == "S")
        ui->comboBoxCMD->setCurrentIndex(ui->comboBoxChannel->findText(cmdS));
    else if(syncCMD() == "A")
        ui->comboBoxCMD->setCurrentIndex(ui->comboBoxChannel->findText(cmdA));
    //    ui->comboBoxChannel->setCurrentIndex(ui->comboBoxChannel->findText(syncChannel()));
    if(syncChannel() == "V")
        ui->comboBoxChannel->setCurrentIndex(ui->comboBoxChannel->findText(vibroSource));
    else if(syncChannel() == "F")
        ui->comboBoxChannel->setCurrentIndex(ui->comboBoxChannel->findText(detonationSource));
    ui->lineEditDepth->setText(depth_);
    ui->lineEditOperator->setText(operatorName_);
    ui->lineEditNumHole->setText(numHole_);
    ui->lineEditNameArea->setText(nameArea_);
    ui->lineEditDistBtwDevices->setText(distBtwDevices_);

    //ui->comboBoxCorDraw->setCurrentIndex(ui->comboBoxCMD->findText(corrDraw_));
    //ui->comboBoxCorSave->setCurrentIndex(ui->comboBoxChannel->findText(corrSave_));
    //ui->labelSwipTime->setText(QString::number(swipLen_));
}

void Settings::on_pushButton_3_clicked()
{
    bool* flag = new bool();
    *flag = false;

    int numDnMod = ui->lineEditNumDnMod->text().toInt(flag);
    if (*flag == false)
    {
        emit errorMsg("Ошибка при чтении значения <Кол-во подземных модулей> в окне настройки!");
        return;
    }
    int numWellsMod = ui->lineEditNumWellsMod->text().toInt(flag);
    if (*flag == false)
    {
        emit errorMsg("Ошибка при чтении значения <Кол-во наземных модулей> в окне настройки!");
        return;
    }
    int timeRecord = lineEditTimeRecord_->text().toInt(flag);
    if (*flag == false)
    {
        emit errorMsg("Ошибка при чтении значения <Время записи> в окне настройки!");
        return;
    }
    int countRecord = ui->lineEditCountRecord->text().toInt(flag);
    if (*flag == false)
    {
        emit errorMsg("Ошибка при чтении значения <Кол-во записей> в окне настройки!");
        return;
    }
    int timeWaiting = lineEditTimeWaiting_->text().toInt(flag);
    if (*flag == false)
    {
        emit errorMsg("Ошибка при чтении значения <Время ожидания> в окне настройки!");
        return;
    }
    int swipLen = ui->lineSwipLen->text().toInt(flag);
    if (*flag == false)
    {
        emit errorMsg("Ошибка при чтении значения <Длина свип-сигнала> в окне настройки!");
        return;
    }

    numDnMod_ = numDnMod;
    numWellsMod_ = numWellsMod;
    timeRecord_ = timeRecord;
    countRecord_ = countRecord;
    timeWaiting_ = timeWaiting;
    //    syncCMD_ = ui->comboBoxCMD->currentText();
    QString tmp = ui->comboBoxCMD->currentText();
    if(tmp == cmdS)
        syncCMD_ = "S";
    else   if(tmp == cmdA)
        syncCMD_ = "A";
    //syncChannel_ = ui->comboBoxChannel->currentText();
    tmp = ui->comboBoxChannel->currentText();
    if(tmp == detonationSource)
        syncChannel_ = "F";
    else     if(tmp == vibroSource)
        syncChannel_ = "V";
    //corrDraw_ = ui->comboBoxCorDraw->currentText();
    swipLen_ = swipLen;
    depth_ = ui->lineEditDepth->text();
    operatorName_ = ui->lineEditOperator->text();
    numHole_ = ui->lineEditNumHole->text();
    nameArea_ = ui->lineEditNameArea->text();
    distBtwDevices_ = ui->lineEditDistBtwDevices->text();
    isDefaultSavingPath_ = ui->checkBoxSaveMod->checkState() == Qt::CheckState::Checked ? true : false;
    isPaintZeroLines_ = ui->checkBoxZeroLines->checkState() == Qt::CheckState::Checked ? true : false;
    isModemOn_ = ui->checkBoxModem->checkState() == Qt::CheckState::Checked ? true : false;

    writeSettings();
    emit updateSettings();
    this->hide();
}

void Settings::on_toolButtonNumDnModMin_clicked()
{
    QString tmp = editVal(false, ui->lineEditNumDnMod->text());
    if(tmp == "")
        return;
    else
        ui->lineEditNumDnMod->setText(tmp);
}

void Settings::on_toolButtonNumDnModPlus_clicked()
{
    QString tmp = editVal(true, ui->lineEditNumDnMod->text());
    if(tmp == "")
        return;
    else{
        if(tmp.toInt() > 40)
            tmp = QString::number(40);
        ui->lineEditNumDnMod->setText(tmp);
    }
}

void Settings::on_toolButtonNumWellsModMin_clicked()
{
    QString tmp = editVal(false, ui->lineEditNumWellsMod->text());
    if(tmp == "")
        return;
    else
        ui->lineEditNumWellsMod->setText(tmp);
}

void Settings::on_toolButtonNumWellsModPlus_clicked()
{
    QString tmp = editVal(true, ui->lineEditNumWellsMod->text());
    if(tmp == "")
        return;
    else
        ui->lineEditNumWellsMod->setText(tmp);
}

void Settings::on_toolButtonCountRecordMin_clicked()
{
    QString tmp = editVal(false, ui->lineEditCountRecord->text());
    if(tmp == "")
        return;
    else
        ui->lineEditCountRecord->setText(tmp);
}

void Settings::on_toolButtonCountRecordPlus_clicked()
{
    QString tmp = editVal(true, ui->lineEditCountRecord->text());
    if(tmp == "")
        return;
    else
        ui->lineEditCountRecord->setText(tmp);
}

void Settings::on_comboBoxChannel_currentTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    //    if(arg1 == "F"){
    //        ui->comboBoxCorDraw->setCurrentIndex(ui->comboBoxCorDraw->findText("Оригинал"));
    //    }
}

void Settings::on_comboBoxCorDraw_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    //    if(arg1 == "Вз.корреляция")
    //    {
    //        if(ui->comboBoxChannel->currentText() == "F")
    //            ui->comboBoxCorDraw->setCurrentIndex(ui->comboBoxCorDraw->findText("Оригинал"));
    //        ui->labelCorSave->setVisible(false);
    //        ui->lineSwipLen->setVisible(false);
    //        ui->labelSwipTime->setVisible(false);
    //    }
    //    else if(arg1 == "Корреляция 2") {
    //        if(ui->comboBoxChannel->currentText() == "F")
    //            ui->comboBoxCorDraw->setCurrentIndex(ui->comboBoxCorDraw->findText("Оригинал"));
    //        else{
    //            ui->labelCorSave->setVisible(true);
    //            ui->lineSwipLen->setVisible(true);
    //            ui->labelSwipTime->setVisible(true);
    //        }
    //    } else {
    //        ui->labelCorSave->setVisible(false);
    //        ui->lineSwipLen->setVisible(false);
    //        ui->labelSwipTime->setVisible(false);
    //    }
}

void Settings::on_extraSettingsButton_clicked()
{
    extraSettings_  = new ExtraSettings(numDnMod_, numWellsMod_);
    connect(extraSettings_, SIGNAL(inversAndGainChannels(const inversAndGainValue)), this, SIGNAL(inversAndGainChannels(const inversAndGainValue)));
    extraSettings_->show();
}

void Settings::on_comboBoxChannel_currentIndexChanged(const QString &arg1)
{
    if(arg1 == detonationSource)
    {
        //ui->labelCorr->setVisible(false);
        ui->labelCorSave->setVisible(false);
        ui->lineSwipLen->setVisible(false);
        ui->labelSwipTime->setVisible(false);
        ui->labelTimeRecord->setText("Время записи");
    }
    else if(arg1 == vibroSource)
    {
        //ui->labelCorr->setVisible(true);
        ui->labelCorSave->setVisible(true);
        ui->lineSwipLen->setVisible(true);
        ui->labelSwipTime->setVisible(true);
        ui->labelTimeRecord->setText("Время кореллограммы");
    }
}

void Settings::on_startDwnHoleButton_clicked()
{
    emit startDwnHole();
}

void Settings::on_startUpHoleButton_clicked()
{
    emit startGround();
    qDebug() << "startGroundHole";
}

void Settings::on_stopUpHoleButton_clicked()
{
    emit stopGround();
}

void Settings::on_buttonStopSync_clicked()
{
    emit stopSync();
}

void Settings::on_checkBoxSaveMod_stateChanged(int arg1)
{
    this->isDefaultSavingPath_ = arg1 == 2 ? true : false;
}

void Settings::on_checkBoxZeroLines_stateChanged(int arg1)
{
    this->isPaintZeroLines_ = arg1 == 2 ? true : false;
}

void Settings::on_checkBoxModem_stateChanged(int arg1)
{
    this->isModemOn_ = arg1 == 2 ? true : false;
}

int Settings::globalOffsetDnHole()
{
    settings_->sync();
    settings_->beginGroup("Modem");
    int tmpVal = -1;
    tmpVal = settings_->value("OffsetDnHoleModemOff", QString::number(offsetDnHoleModemOff_)).toInt();
    offsetDnHoleModemOff_ = tmpVal >= 0 ? (tmpVal < 50 ? tmpVal : offsetDnHoleModemOff_) : offsetDnHoleModemOff_;
    tmpVal = settings_->value("OffsetDnHoleModemOn", QString::number(offsetDnHoleModemOn_)).toInt();
    offsetDnHoleModemOn_ = tmpVal >= 0 ? (tmpVal < 50 ? tmpVal : offsetDnHoleModemOn_) : offsetDnHoleModemOn_;
    settings_->endGroup();

    if(isModemOn_ == true)
        return offsetDnHoleModemOn();
    else
        return offsetDnHoleModemOff();
}

int Settings::globalOffsetUpHole()
{
    settings_->sync();
    settings_->beginGroup("Modem");
    int tmpVal = -1;
    tmpVal = settings_->value("OffsetUpHole", QString::number(offsetUpHole_)).toInt();
    offsetUpHole_ = tmpVal > -50 ? (tmpVal < 50 ? tmpVal : offsetUpHole_) : offsetUpHole_;
    settings_->endGroup();

    return offsetUpHole_;
}

void Settings::on_lineEditNumDnMod_textEdited(const QString &arg1)
{
    if(arg1.isEmpty())
        return;
    int tmp = arg1.toInt();
    bool flag = false;
    if(tmp <= 0){
        tmp = 1;
        flag = true;
    }
    else if(tmp > 40){
        tmp = 40;
        flag = true;
    }
    if(flag == true)
        ui->lineEditNumDnMod->setText(QString::number(tmp));
}
