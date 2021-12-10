#include "measurementproperties.h"
#include "ui_measurementproperties.h"

MeasurementProperties::MeasurementProperties(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeasurementProperties)
{
    ui->setupUi(this);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    setStyleAllSheet();
}

MeasurementProperties::~MeasurementProperties()
{
    delete ui;
}

void MeasurementProperties::updateProperties(int idMeas)
{
    this->setLastIdMeas(idMeas);
    emit readyUpdateProperties(idMeas);
}

int MeasurementProperties::lastIdMeas() const
{
    return lastIdMeas_;
}

void MeasurementProperties::setLastIdMeas(int lastIdMeas)
{
    lastIdMeas_ = lastIdMeas;
}

void MeasurementProperties::setStyleAllSheet()
{
    this->setStyleSheet("background-color: #ffffff; font-family: Arial; font-size: 14pt;");

    QString styleSheet = "color: rgb(50, 50, 50); border: NONE; font-family: Arial; font-size: 11pt; font-weight: 470;";
    ui->labelMainName->setStyleSheet("color: rgb(50, 50, 50); border: NONE; font-family: Arial; font-size: 14pt; font-weight: 500;");
    ui->labelNameProj->setStyleSheet(styleSheet);
    ui->labelIdMeas->setStyleSheet(styleSheet);
    ui->labelNumDnHole->setStyleSheet(styleSheet);
    ui->labelNumUpHole->setStyleSheet(styleSheet);
    ui->labelGainDnHole->setStyleSheet(styleSheet);
    ui->labelGainUpHole->setStyleSheet(styleSheet);
    ui->labelDate->setStyleSheet(styleSheet);
    ui->labelTime->setStyleSheet(styleSheet);
    ui->labelTimeRecord->setStyleSheet(styleSheet);
    ui->labelTimeSwip->setStyleSheet(styleSheet);
    ui->labelSource->setStyleSheet("color: rgb(50, 50, 50); border: NONE; font-family: Arial; font-size: 12pt; font-weight: 470;");
    ui->labelSourceType->setStyleSheet(styleSheet);
    ui->labelSourceStat->setStyleSheet(styleSheet);
    ui->labelDepth->setStyleSheet(styleSheet);
    ui->labelOperator->setStyleSheet(styleSheet);
    ui->labelNumHole->setStyleSheet(styleSheet);
    ui->labelNameArea->setStyleSheet(styleSheet);
    ui->labelDistBtwDevices->setStyleSheet(styleSheet);
    ui->labelServiceInfo->setStyleSheet("color: rgb(50, 50, 50); border: NONE; font-family: Arial; font-size: 12pt; font-weight: 490;");

    styleSheet = "color: rgb(50, 50, 50); border: NONE; font-family: Arial; font-size: 11pt; font-weight: 470;";
    ui->lineEditNameProj->setStyleSheet(styleSheet);
    ui->lineEditIdMeas->setStyleSheet(styleSheet);
    ui->lineEditNumDnHole->setStyleSheet(styleSheet);
    ui->lineEditNumUpHole->setStyleSheet(styleSheet);
    ui->lineEditGainDnHole->setStyleSheet(styleSheet);
    ui->lineEditGainUpHole->setStyleSheet(styleSheet);
    ui->lineEditDate->setStyleSheet(styleSheet);
    ui->lineEditTime->setStyleSheet(styleSheet);
    ui->lineEditTimeRecord->setStyleSheet(styleSheet);
    ui->lineEditTimeSwip->setStyleSheet(styleSheet);
    ui->lineEditSourceType->setStyleSheet(styleSheet);
    ui->lineEditSourceStat->setStyleSheet(styleSheet);
    ui->lineEditDepth->setStyleSheet(styleSheet);
    ui->lineEditOperator->setStyleSheet(styleSheet);
    ui->lineEditNumHole->setStyleSheet(styleSheet);
    ui->lineEditNameArea->setStyleSheet(styleSheet);
    ui->lineEditDistBtwDevices->setStyleSheet(styleSheet);

    styleSheet = "background-color: rgb(127, 199, 255);";
    ui->line->setStyleSheet(styleSheet);
    ui->line_2->setStyleSheet(styleSheet);
    ui->line_3->setStyleSheet(styleSheet);
    ui->line_4->setStyleSheet(styleSheet);
    ui->line_5->setStyleSheet(styleSheet);
    ui->line_6->setStyleSheet(styleSheet);
    ui->line_7->setStyleSheet(styleSheet);
    ui->line_8->setStyleSheet(styleSheet);
    ui->line_9->setStyleSheet(styleSheet);
    ui->line_10->setStyleSheet(styleSheet);
    ui->line_11->setStyleSheet(styleSheet);
    ui->line_12->setStyleSheet(styleSheet);
    ui->line_13->setStyleSheet(styleSheet);
    ui->line_14->setStyleSheet(styleSheet);
}

void MeasurementProperties::onUpdateProperties(QMap<QString, QString> properties)
{
    ui->labelMainName->setText("Измерение " + properties.value("IdMeas"));

    ui->lineEditNameProj->setText(properties.value("NameProj"));
    ui->lineEditIdMeas->setText(properties.value("IdMeas"));

    ui->lineEditDate->setText(properties.value("Date"));
    ui->lineEditTime->setText(properties.value("Time"));

    ui->lineEditNumDnHole->setText(properties.value("NumDnHole"));
    ui->lineEditNumUpHole->setText(properties.value("NumUpHole"));

    ui->lineEditGainDnHole->setText(properties.value("GateDnHole"));
    ui->lineEditGainUpHole->setText(properties.value("GateUpHole"));

    ui->lineEditSourceStat->setText(properties.value("SourceStat"));
    ui->lineEditSourceType->setText(properties.value("SourceType"));

    ui->lineEditTimeRecord->setText(properties.value("TimeRecord"));
    ui->lineEditTimeSwip->setText(properties.value("TimeSwip"));

    this->depth_ = properties.value("Depth");
    this->operator_ = properties.value("Operator");
    this->numHole_ = properties.value("NumHole");
    this->nameArea_ = properties.value("NameArea");
    this->distBtwDevices_ = properties.value("DistBtwDevices");

    ui->lineEditDepth->setText(depth_);
    ui->lineEditOperator->setText(operator_);
    ui->lineEditNumHole->setText(numHole_);
    ui->lineEditNameArea->setText(nameArea_);
    ui->lineEditDistBtwDevices->setText(distBtwDevices_);
}


void MeasurementProperties::on_pushButtonChange_clicked()
{
    ui->lineEditDepth->setReadOnly(false);
    ui->lineEditOperator->setReadOnly(false);
    ui->lineEditNumHole->setReadOnly(false);
    ui->lineEditNameArea->setReadOnly(false);
    ui->lineEditDistBtwDevices->setReadOnly(false);

    QString styleSheet = "color: rgb(50, 50, 50); border-width: 1px; border-style: solid;  font-family: Arial; font-size: 11pt; font-weight: 470;";
    ui->lineEditDepth->setStyleSheet(styleSheet);
    ui->lineEditOperator->setStyleSheet(styleSheet);
    ui->lineEditNumHole->setStyleSheet(styleSheet);
    ui->lineEditNameArea->setStyleSheet(styleSheet);
    ui->lineEditDistBtwDevices->setStyleSheet(styleSheet);
}

void MeasurementProperties::on_pushButtonSave_clicked()
{
    depth_ = ui->lineEditDepth->text();
    operator_ = ui->lineEditOperator->text();
    numHole_ =  ui->lineEditNumHole->text();
    nameArea_ = ui->lineEditNameArea->text();
    distBtwDevices_ = ui->lineEditDistBtwDevices->text();
    QMap <QString, QString> serviceInfo;
    serviceInfo.insert("Depth", depth_);
    serviceInfo.insert("Operator", operator_);
    serviceInfo.insert("NumHole", numHole_);
    serviceInfo.insert("NameArea", nameArea_);
    serviceInfo.insert("DistBtwDevices", distBtwDevices_);

    QString styleSheet = "color: rgb(50, 50, 50); border: NONE; font-family: Arial; font-size: 11pt; font-weight: 470;";
    ui->lineEditDepth->setReadOnly(true);
    ui->lineEditOperator->setReadOnly(true);
    ui->lineEditNumHole->setReadOnly(true);
    ui->lineEditNameArea->setReadOnly(true);
    ui->lineEditDistBtwDevices->setReadOnly(true);

    ui->lineEditDepth->setStyleSheet(styleSheet);
    ui->lineEditOperator->setStyleSheet(styleSheet);
    ui->lineEditNumHole->setStyleSheet(styleSheet);
    ui->lineEditNameArea->setStyleSheet(styleSheet);
    ui->lineEditDistBtwDevices->setStyleSheet(styleSheet);

    emit updateServiceInfo(lastIdMeas(), serviceInfo);
}
