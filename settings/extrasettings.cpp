#include "extrasettings.h"
#include "ui_extrasettings.h"

ExtraSettings::ExtraSettings(int numDnMod, int numWellsMod, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExtraSettings),
    numDnMod_(numDnMod),
    numWellsMod_(numWellsMod)
{
    ui->setupUi(this);

    //this->setWindowModality(Qt::ApplicationModal);
    //this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_DeleteOnClose);
    CheckBoxInComboWidget* checkBox; // указатель, необходимый для записи в список mapComboWidgets_

    checkBox = createAndFillItemsBox(typeComboBox::inversDwnModules, numDnMod_);
    mapComboWidgets_.insert(typeComboBox::inversDwnModules, checkBox);
    ui->gridLayout->addWidget(checkBox, 3, 0);

    //Добавить checkbox в строку 5
    checkBox = createAndFillItemsBox(typeComboBox::inversGroundModules, numWellsMod_);
    mapComboWidgets_.insert(typeComboBox::inversGroundModules, checkBox);
    ui->gridLayout->addWidget(checkBox, 5, 0);

    checkBox = createAndFillItemsBox(typeComboBox::gainDwnHoleModules, numDnMod_);
    mapComboWidgets_.insert(typeComboBox::gainDwnHoleModules, checkBox);
    ui->gridLayout->addWidget(checkBox, 11, 0);
    for(int i = 0; i < numDnMod_; i++)
        inversAndGainValue_.vecGainDwnModules.push_back(axis(-1,-1,-1)); //заполняем значение усиления по умолчанию
    for(int i = 0; i < numWellsMod_; i++)
        inversAndGainValue_.vecGainGroundModules.push_back(-1);

    checkBox = fillChannelsBox(typeComboBox::inversDwnChannels);
    mapComboWidgets_.insert(typeComboBox::inversDwnChannels, checkBox);
    ui->gridLayout->addWidget(checkBox, 3, 1);

    checkBox = fillChannelsBox(typeComboBox::inversGroundChannels);
    mapComboWidgets_.insert(typeComboBox::inversGroundChannels, checkBox);
    ui->gridLayout->addWidget(checkBox, 5, 1);

    checkBox = fillChannelsBox(typeComboBox::gainDwnHoleChannels);
    mapComboWidgets_.insert(typeComboBox::gainDwnHoleChannels, checkBox);
    ui->gridLayout->addWidget(checkBox, 11, 1);

    checkBox = createAndFillItemsBox(typeComboBox::gainGroundHoleModules, numWellsMod_);
    mapComboWidgets_.insert(typeComboBox::gainGroundHoleModules, checkBox);
    ui->gridLayout->addWidget(checkBox, 14, 0);

    checkBox = fillChannelsBox(typeComboBox::gainGroundHoleChannels);
    mapComboWidgets_.insert(typeComboBox::gainGroundHoleChannels, checkBox);
    ui->gridLayout->addWidget(checkBox, 14, 1);

    qRegisterMetaTypeStreamOperators<QVector<bool>>("QVector<bool>");
    settings_ = new QSettings(fileName_ , QSettings::IniFormat, this);
}

ExtraSettings::~ExtraSettings()
{
    for(int i = 0; i < typeComboBox::count; i++)
        delete mapComboWidgets_.value(i);
    delete settings_;
    delete ui;
}

void ExtraSettings::readSettings()
{

    settings_->beginGroup("CountModules");
    //qDebug() << settings_->value("DwnHoleModules") << settings_->value("GroundHoleModules");
    if (numDnMod_ != settings_->value("DwnHoleModules") || numWellsMod_!= settings_->value("GroundHoleModules"))
    {
        QMessageBox* pmbx =
                            new QMessageBox("Ошибка",
                            "<i>Загружаемое количество модулей отличаеться от текущего</i>",
                            QMessageBox::Information,
                            QMessageBox::NoButton,
                            QMessageBox::NoButton,
                            QMessageBox::Ok);
        pmbx->setWindowFlags(Qt::WindowStaysOnTopHint);
        pmbx->exec();
        delete pmbx;
        return;
    };

    settings_->endGroup();
    settings_->beginGroup("Gain");
    if(settings_->contains("DwnHoleModules"))
    {
        *mapSelectedValue_.find(typeComboBox::gainDwnHoleModules) = settings_->value("DwnHoleModules").value<QVector<bool> >();
        mapComboWidgets_.value(typeComboBox::gainDwnHoleModules)->setVecIsChangedValues(mapSelectedValue_.value(typeComboBox::gainDwnHoleModules));
    }
    if(settings_->contains("DwnHoleChannels"))
    {
        *mapSelectedValue_.find(typeComboBox::gainDwnHoleChannels) = settings_->value("DwnHoleChannels").value<QVector<bool> >();
         mapComboWidgets_.value(typeComboBox::gainDwnHoleChannels)->setVecIsChangedValues(mapSelectedValue_.value(typeComboBox::gainDwnHoleChannels));
    }
    if(settings_->contains("DwnHoleValueGain"))
        ui->dwnHoleGainComboBox->setCurrentText(QString::number(settings_->value("DwnHoleValueGain").value<int>()));
    if(settings_->contains("GroundHoleModules"))
    {
        *mapSelectedValue_.find(typeComboBox::gainGroundHoleModules) = settings_->value("GroundHoleModules").value<QVector<bool> >();
        mapComboWidgets_.value(typeComboBox::gainGroundHoleModules)->setVecIsChangedValues(mapSelectedValue_.value(typeComboBox::gainGroundHoleModules));
    }
    if(settings_->contains("GroundHoleChannels"))
    {
        *mapSelectedValue_.find(typeComboBox::gainGroundHoleChannels) = settings_->value("GroundHoleChannels").value<QVector<bool> >();
         mapComboWidgets_.value(typeComboBox::gainGroundHoleChannels)->setVecIsChangedValues(mapSelectedValue_.value(typeComboBox::gainGroundHoleChannels));
    }
    if(settings_->contains("GroundHoleValueGain"))
            ui->comboBox->setCurrentText(QString::number(settings_->value("GroundHoleValueGain").value<int>()));
    settings_->endGroup();

    settings_->beginGroup("Inversion");
    if(settings_->contains("DwnHoleModules"))
    {
        *mapSelectedValue_.find(typeComboBox::inversDwnModules) = settings_->value("DwnHoleModules").value<QVector<bool> >();
         mapComboWidgets_.value(typeComboBox::inversDwnModules)->setVecIsChangedValues(mapSelectedValue_.value(typeComboBox::inversDwnModules));
    }
    if(settings_->contains("DwnHoleChannels"))
    {
        *mapSelectedValue_.find(typeComboBox::inversDwnChannels) = settings_->value("DwnHoleChannels").value<QVector<bool> >();
        mapComboWidgets_.value(typeComboBox::inversDwnChannels)->setVecIsChangedValues(mapSelectedValue_.value(typeComboBox::inversDwnChannels));
    }
    if(settings_->contains("GroundHoleModules"))
    {
        *mapSelectedValue_.find(typeComboBox::inversGroundModules) = settings_->value("GroundHoleModules").value<QVector<bool> >();
        mapComboWidgets_.value(typeComboBox::inversGroundModules)->setVecIsChangedValues(mapSelectedValue_.value(typeComboBox::inversGroundModules));
    }
    if(settings_->contains("GroundHoleChannels"))
    {
        *mapSelectedValue_.find(typeComboBox::inversGroundChannels) = settings_->value("GroundHoleChannels").value<QVector<bool> >();
        mapComboWidgets_.value(typeComboBox::inversGroundChannels)->setVecIsChangedValues(mapSelectedValue_.value(typeComboBox::inversGroundChannels));
    }
    settings_->endGroup();
}

void ExtraSettings::writeSettings()
{
    settings_->beginGroup("CountModules");
    settings_->setValue("DwnHoleModules", numDnMod_);
    settings_->setValue("GroundHoleModules", numWellsMod_);
    settings_->endGroup();
    settings_->beginGroup("Gain");
    *mapSelectedValue_.find(typeComboBox::gainDwnHoleModules) = mapComboWidgets_.value(typeComboBox::gainDwnHoleModules)->getVectIsChangedValues();
    settings_->setValue("DwnHoleModules", QVariant::fromValue(mapSelectedValue_.value(typeComboBox::gainDwnHoleModules)));

    *mapSelectedValue_.find(typeComboBox::gainDwnHoleChannels) = mapComboWidgets_.value(typeComboBox::gainDwnHoleChannels)->getVectIsChangedValues();
    settings_->setValue("DwnHoleChannels", QVariant::fromValue(mapSelectedValue_.value(typeComboBox::gainDwnHoleChannels)));

    settings_->setValue("DwnHoleValueGain", ui->dwnHoleGainComboBox->currentText().toInt());

    *mapSelectedValue_.find(typeComboBox::gainGroundHoleModules) = mapComboWidgets_.value(typeComboBox::gainGroundHoleModules)->getVectIsChangedValues();
    settings_->setValue("GroundHoleModules", QVariant::fromValue(mapSelectedValue_.value(typeComboBox::gainGroundHoleModules)));

    *mapSelectedValue_.find(typeComboBox::gainGroundHoleChannels) = mapComboWidgets_.value(typeComboBox::gainGroundHoleChannels)->getVectIsChangedValues();
    settings_->setValue("GroundHoleChannels", QVariant::fromValue(mapSelectedValue_.value(typeComboBox::gainGroundHoleChannels)));

    settings_->setValue("GroundHoleValueGain", ui->comboBox->currentText().toInt());
    settings_->endGroup();

    settings_->beginGroup("Inversion");
    *mapSelectedValue_.find(typeComboBox::inversDwnModules) = mapComboWidgets_.value(typeComboBox::inversDwnModules)->getVectIsChangedValues();
    settings_->setValue("DwnHoleModules", QVariant::fromValue(mapSelectedValue_.value(typeComboBox::inversDwnModules)));

    *mapSelectedValue_.find(typeComboBox::inversDwnChannels) = mapComboWidgets_.value(typeComboBox::inversDwnChannels)->getVectIsChangedValues();
    settings_->setValue("DwnHoleChannels", QVariant::fromValue(mapSelectedValue_.value(typeComboBox::inversDwnChannels)));

    *mapSelectedValue_.find(typeComboBox::inversGroundModules) = mapComboWidgets_.value(typeComboBox::inversGroundModules)->getVectIsChangedValues();
    settings_->setValue("GroundHoleModules", QVariant::fromValue(mapSelectedValue_.value(typeComboBox::inversGroundModules)));

    *mapSelectedValue_.find(typeComboBox::inversGroundChannels) = mapComboWidgets_.value(typeComboBox::inversGroundChannels)->getVectIsChangedValues();
    settings_->setValue("GroundHoleChannels", QVariant::fromValue(mapSelectedValue_.value(typeComboBox::inversGroundChannels)));
    settings_->endGroup();
}

void ExtraSettings::setDir(const QDir &dir)
{
    dir_ = dir;
}

void ExtraSettings::on_saveAndCloseButton_clicked()
{
    int gainDwnHole = ui->dwnHoleGainComboBox->currentText().toInt();
    int gainGroundHole = parsingGroundGain(ui->comboBox->currentText().toInt());
    if((gainDwnHole <= 0 || gainDwnHole >= 1000) || (gainGroundHole <= 0 || gainGroundHole >= 256))
    {
        QMessageBox* pmbx =
                            new QMessageBox("Ошибка",
                            "<i>Некорректное значение</i>   <b>усиления</b>",
                            QMessageBox::Information,
                            QMessageBox::NoButton,
                            QMessageBox::NoButton,
                            QMessageBox::Ok);
        pmbx->setWindowFlags(Qt::WindowStaysOnTopHint);
        pmbx->exec();
        delete pmbx;
        return;
    }
    writeSettings();

    inversAndGainValue_.mapInversModules.insert(inversDwnModules, mapSelectedValue_.value(typeComboBox::inversDwnModules));
    inversAndGainValue_.mapInversModules.insert(inversDwnChannels, mapSelectedValue_.value(typeComboBox::inversDwnChannels));
    inversAndGainValue_.mapInversModules.insert(inversGroundModules, mapSelectedValue_.value(typeComboBox::inversGroundModules));
    inversAndGainValue_.mapInversModules.insert(inversGroundChannels, mapSelectedValue_.value(typeComboBox::inversGroundChannels));

    for(int i = 0; i < mapSelectedValue_.value(typeComboBox::gainDwnHoleModules).size(); i++)
        if(mapSelectedValue_.value(typeComboBox::gainDwnHoleModules)[i])
        {
            if (mapSelectedValue_.value(typeComboBox::gainDwnHoleChannels)[channel::x])
                std::get<channel::x>(inversAndGainValue_.vecGainDwnModules[i]) = gainDwnHole;
            if (mapSelectedValue_.value(typeComboBox::gainDwnHoleChannels)[channel::y])
                std::get<channel::y>(inversAndGainValue_.vecGainDwnModules[i]) = gainDwnHole;
            if (mapSelectedValue_.value(typeComboBox::gainDwnHoleChannels)[channel::z])
               std::get<channel::z>(inversAndGainValue_.vecGainDwnModules[i]) = gainDwnHole;
//            qDebug() << i + 1 << std::get<channel::x>(inversAndGainValue_.vecGainDwnModules[i]) <<
//                        std::get<channel::y>(inversAndGainValue_.vecGainDwnModules[i]) << std::get<channel::z>(inversAndGainValue_.vecGainDwnModules[i]);
        }
    for(int i = 0; i < mapSelectedValue_.value(typeComboBox::gainGroundHoleModules).size(); i++)
        if(mapSelectedValue_.value(typeComboBox::gainGroundHoleModules)[i])
        {
            if (mapSelectedValue_.value(typeComboBox::gainGroundHoleChannels)[0])
                inversAndGainValue_.vecGainGroundModules[i] = gainGroundHole;
//            qDebug() << i + 1 << inversAndGainValue_.vecGainUpModules[i] ;
        }
    emit inversAndGainChannels(inversAndGainValue_);
    delete this;
}

CheckBoxInComboWidget* ExtraSettings::createAndFillItemsBox(typeComboBox type, int num)
{
    CheckBoxInComboWidget *checkBox = new CheckBoxInComboWidget();
    for(int i = 0; i < num; i++)
    {
        checkBox->addItem(QString::fromUtf8("Модуль№%1").arg(i+1), i);
    }
    // здесь происходит заполнения списка векторов, в которые будут записаны выбранные в checkBox значения
    QVector<bool> vecIsChangedModules;
    mapSelectedValue_.insert(type,vecIsChangedModules);
    //-----------------------------------------
    return checkBox;

}

CheckBoxInComboWidget* ExtraSettings::fillChannelsBox(typeComboBox type)
{
    CheckBoxInComboWidget *checkBox = new CheckBoxInComboWidget();
    if(type == inversGroundModules || type == inversGroundChannels || type == gainGroundHoleModules || type == gainGroundHoleChannels)
        checkBox->addItem("Z", 0); // единствненный канал
    else
    {
        checkBox->addItem("X", channel::x);
        checkBox->addItem("Y", channel::y);
        checkBox->addItem("Z", channel::z);
    }
    checkBox->setMaximumWidth(90);
    // здесь происходит заполнения списка векторов, в которые будут записаны выбранные в checkBox значения
    QVector<bool> vecIsChangedChannels;
    mapSelectedValue_.insert(type,vecIsChangedChannels);
    return checkBox;
}

void ExtraSettings::on_readSettingsFileButton_clicked()
{
    readSettings();
}

int ExtraSettings::parsingGroundGain(int value)
{
    int tmp = 0;
    switch (value) {
    case 1000:
        tmp = 1 << 0U;
        break;
    case 100:
        tmp = 1 << 1U;
        break;
    case 10:
        tmp = 1 << 2U;
        break;
    case 2:
        tmp = 1 << 3U;
        break;
    case 1:
        tmp = 1 << 4U;
        break;
    case -10:
        tmp = 1 << 5U;
        break;
    case -100:
        tmp = 1 << 6U;
        break;
    case -1000:
        tmp = 1 << 7U;
        break;
    }

    return tmp;
}
