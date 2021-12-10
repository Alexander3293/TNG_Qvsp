#include "createproject.h"
#include "ui_createproject.h"


CreateProject::CreateProject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateProject)
{
    ui->setupUi(this);
    ui->textEditPath->setReadOnly(true);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    connect(ui->textEditPath, SIGNAL(textChanged()), this, SLOT(on_textEditPath_textChanged()));
    ui->textEditName->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"
                                                         "background-color: rgb(178, 178, 178);"
                                                         "width:10px;"
                                                         "margin: 0px 0px 0px 0px;"
                                                         "}"
                                                         "QScrollBar::handle:vertical {"
                                                         "background-color:rgb(24, 121, 155);"
                                                         "min-height: 35px;"
                                                         "width: 15px;"
                                                         "}");
    ui->textEditPath->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"
                                                         "background-color: rgb(178, 178, 178);"
                                                         "width:10px;"
                                                         "margin: 0px 0px 0px 0px;"
                                                         "}"
                                                         "QScrollBar::handle:vertical {"
                                                         "background-color:rgb(24, 121, 155);"
                                                         "min-height: 35px;"
                                                         "width: 15px;"
                                                         "}");
    name_ = "newProj";
    ui->textEditName->setPlainText(name_);
    resizeTextEditName();

    ui->textEditPath->setLineWrapMode(QTextEdit::FixedPixelWidth);
    ui->textEditPath->setLineWrapColumnOrWidth(280);
    ui->textEditPath->setFixedHeight(46);
    QString text = QString(QDir::homePath()+"/"+name_+"_"+QDate::currentDate().toString("dd_MM_yyyy")+"_"+QTime::currentTime().toString("hh_mm_ss"));
    setPath(QDir::homePath());
    //   ui->pushButtonPath->
    ui->textEditPath->setText(text);
    QPixmap pic(":/resources/arrowrigth.jpg");
    pic = pic.scaled(5, 5, Qt::KeepAspectRatio);
    ui->labelPicPlace->setFixedSize(5,5);
    ui->labelPicResult->setFixedSize(5,5);
    ui->labelPicPlace->setPixmap(pic);
    ui->labelPicResult->setPixmap(pic);
    ui->labelPicResult->setVisible(false);
    ui->labelResult->setStyleSheet("color: rgb(180, 180, 180); border: NONE; font-family: Arial; font-size: 12pt; font-weight: 470;");
    ui->labelPlace->setStyleSheet("color: rgb(50, 50, 50); border: NONE; font-family: Arial; font-size: 12pt; font-weight: 470;");
}

CreateProject::~CreateProject()
{
    delete ui;
}

void CreateProject::on_pushButtonPath_clicked()
{
    setPath(QFileDialog::getExistingDirectory(0, QString::fromUtf8("Укажите путь к папке"), QDir::homePath()));
    if (getPath() != "") {
        ui->textEditPath->setText(getPath()+"/"+name_+"_"+QDate::currentDate().toString("dd_MM_yyyy")+"_"+QTime::currentTime().toString("hh_mm_ss"));
        resizeTextEditPath();
    }
}

void CreateProject::on_pushButtonCancel_clicked()
{
    if(ui->pushButtonCancel->text() == "Отмена")
        QDialog::close();
    else if(ui->pushButtonCancel->text() == "Назад") {
        ui->pushButtonCancel->setText("Отмена");
        ui->pushButton_2->setText("Далее");
        ui->labelPicPlace->setVisible(true);
        ui->labelPicResult->setVisible(false);
        ui->labelResult->setStyleSheet("color: rgb(180, 180, 180); border: NONE; font-family: Arial; font-size: 12pt; font-weight: 470;");
        ui->labelPlace->setStyleSheet("color: rgb(50, 50, 50); border: NONE; font-family: Arial; font-size: 12pt; font-weight: 470;");
        ui->labelName->setText("Название проекта: ");
        ui->labelPath->setText("Путь к папке: ");
        ui->labelPath_3->setText("Добро пожаловать в мастер создания проекта. Задайте имя проекта и выберите папку для сохранения");
        ui->textEditName->setStyleSheet("background-color: #ffffff; color: rgb(55,55,55);  border-width: 1px; border-style: solid; border-color: #18799b;  font-family: Arial; font-size: 11pt; font-weight: 450;");
        ui->textEditPath->setStyleSheet("background-color: #ffffff; color: rgb(55,55,55);  border-width: 1px; border-style: solid; border-color: #18799b;  font-family: Arial; font-size: 11pt; font-weight: 450;");
        ui->textEditName->setReadOnly(false);
        ui->textEditName->setFixedWidth(300);
        ui->textEditPath->setFixedWidth(300);
        QString str2 = ui->textEditName->toPlainText();
        str2 = str2.left(str2.lastIndexOf("."));
        ui->textEditName->setText(str2);
        if(ui->textEditName->document()->size().height() > 30){
            if(ui->textEditName->document()->size().height() < 75)
                ui->textEditName->setFixedHeight(static_cast<int>(ui->textEditName->document()->size().height()) + 7);
        }
        else
            ui->textEditName->setFixedHeight(30);
        ui->textEditPath->setLineWrapColumnOrWidth(280);

        if(ui->textEditPath->document()->size().height() > 30){
            if(ui->textEditPath->document()->size().height() < 150)
                ui->textEditPath->setFixedHeight(static_cast<int>(ui->textEditPath->document()->size().height()) + 7);
        }
        else
            ui->textEditPath->setFixedHeight(30);
        QPushButton* pushButtonPath2 = new QPushButton("Обзор");
        pushButtonPath2->setStyleSheet("background-color: #ffffff; color: #18799b; border-width: 1px; border-style: solid; border-color: #18799b; font-family: Arial; font-size: 12pt; font-weight: 450; border-radius: 2px;");
        pushButtonPath2->setFixedSize(140,30);
        ui->gridLayout->addWidget(pushButtonPath2, 2, 2);
        connect(pushButtonPath2, SIGNAL(clicked()), this, SLOT(on_pushButtonPath_clicked()));
    }
}

void CreateProject::on_textEditPath_textChanged()
{
}

QString CreateProject::getName() const
{
    return name_;
}

void CreateProject::setName(const QString &value)
{
    name_ = value;
}

QString CreateProject::getPath() const
{
    return path_;
}

void CreateProject::setPath(const QString &value)
{
    path_ = value;
}

void CreateProject::on_textEditName_textChanged()
{
    name_ = ui->textEditName->toPlainText();
    if(ui->pushButtonCancel->text() == "Отмена") {
        bool isChanged = false;
        for(int i = 0; i < name_.size(); i++) {
            if(i >= name_.size())
                break;
            if(!((name_.at(i) >= "A" && name_.at(i) <= "Z") || (name_.at(i) >= "А" && name_.at(i) <= "Я") ||
                 (name_.at(i) >= "a" && name_.at(i) <= "z") || (name_.at(i) >= "а" && name_.at(i) <= "я") ||
                 (name_.at(i) >= "0" && name_.at(i) <= "9") || (name_.at(i) == "-" || name_.at(i) == "(" ||
                                                                name_.at(i) == ")" || name_.at(i) == "_" ||
                                                                name_.at(i) == "{" || name_.at(i) == "}")))
            {
                name_.remove(i,1);
                i--;
                isChanged = true;
            }
        }
        if(isChanged == true)
            ui->textEditName->setText(name_);
    }
    ui->textEditPath->setText(getPath()+"/"+name_+"_"+QDate::currentDate().toString("dd_MM_yyyy")+"_"+QTime::currentTime().toString("hh_mm_ss"));
    resizeTextEditName();
    resizeTextEditPath();
}

void CreateProject::resizeTextEditName()
{
    //    if(ui->textEditName->document()->size().height() > ui->textEditName->height() && ui->textEditName->height() < 75)
    //    {
    //        ui->textEditName->setFixedHeight(ui->textEditName->document()->size().height()+2);
    //    }

    //    if(ui->textEditName->document()->size().height()+2 < ui->textEditName->height() && ui->textEditName->height() > 75)
    //    {
    //        if(ui->textEditName->document()->size().height() > 75)
    //        {
    //            ui->textEditName->setFixedHeight(ui->textEditName->document()->size().height() + 2);
    //        }
    //        else
    //        {
    //            ui->textEditName->setFixedHeight(75);
    //        }
    //    }
    if(ui->textEditName->document()->size().height() > 30){
        if(ui->textEditName->document()->size().height() < 75)
            ui->textEditName->setFixedHeight(static_cast<int>(ui->textEditName->document()->size().height()) + 7);
    }
    else
        ui->textEditName->setFixedHeight(30);
}

void CreateProject::resizeTextEditPath()
{
    //    if(ui->textEditPath->document()->size().height() > ui->textEditPath->height() && ui->textEditPath->height() < 150)
    //    {
    //        ui->textEditPath->setFixedHeight(static_cast<int>(ui->textEditPath->document()->size().height()+static_cast<qreal>(7)));
    //    }

    //    if(ui->textEditPath->document()->size().height()+7 < ui->textEditPath->height() && ui->textEditPath->height() > 150)
    //    {
    //        if(ui->textEditPath->document()->size().height() > 150)
    //        {
    //            ui->textEditPath->setFixedHeight(static_cast<int>(ui->textEditPath->document()->size().height()+static_cast<qreal>(7)));
    //        }
    //        else
    //        {
    //            ui->textEditPath->setFixedHeight(150);
    //        }
    //    }

    //    if(ui->textEditPath->document()->size().height() > ui->textEditPath->height() && ui->textEditPath->height() < 150)
    if(ui->textEditPath->document()->size().height() > 30){
        if(ui->textEditPath->document()->size().height() < 150)
            ui->textEditPath->setFixedHeight(static_cast<int>(ui->textEditPath->document()->size().height()) + 7);
    }
    else
        ui->textEditPath->setFixedHeight(30);
}

void deleteChildWidgets(QLayoutItem *item) {
    if (item->layout()) {
        // Process all child items recursively.
        for (int i = 0; i < item->layout()->count(); i++) {
            deleteChildWidgets(item->layout()->itemAt(i));
        }
    }
    delete item->widget();
}

void remove(QGridLayout *layout, int row, int column, bool deleteWidgets) {
    // We avoid usage of QGridLayout::itemAtPosition() here to improve performance.
    for (int i = layout->count() - 1; i >= 0; i--) {
        int r, c, rs, cs;
        layout->getItemPosition(i, &r, &c, &rs, &cs);
        if ((r <= row && r + rs - 1 >= row) || (c <= column && c + cs - 1 >= column)) {
            // This layout item is subject to deletion.
            QLayoutItem *item = layout->takeAt(i);
            if (deleteWidgets) {
                deleteChildWidgets(item);
            }
            delete item;
        }
    }
}

void CreateProject::on_pushButton_2_clicked()
{
    if(ui->pushButton_2->text() == "Далее"){
        if(ui->textEditName->toPlainText() == ""){
            return;
        }
        if(ui->textEditPath->toPlainText() == ""){
            return;
        }
        //проверить папки на уже существующую и на невозможный путь

        //подтвердить
        ui->pushButtonCancel->setText("Назад");
        ui->pushButton_2->setText("Готово");
        ui->labelName->setText("Файл проекта: ");
        ui->labelPath->setText("Расположение: ");
        //ui->pushButtonPath->setVisible(false);
        remove(ui->gridLayout, -1, 2, true);
        ui->gridLayout->setColumnMinimumWidth(2, 0);
        ui->gridLayout->setColumnStretch(2, 0);
        ui->labelPath_3->setText("Проверьте и подтвердите название и расположение проекта");
        ui->textEditName->setStyleSheet("color: rgb(50, 50, 50); border: NONE; font-family: Arial; font-size: 12pt; font-weight: 470;");
        ui->textEditPath->setStyleSheet("color: rgb(50, 50, 50); border: NONE; font-family: Arial; font-size: 12pt; font-weight: 470;");
        QString str = ui->textEditPath->toPlainText();
        ui->textEditName->setReadOnly(true);
        ui->textEditName->append(".projgis");
        //ui->textEditPath->setPlainText(str);
        ui->textEditName->setFixedWidth(440);
        ui->textEditPath->setFixedWidth(440);
        QString str2 = ui->textEditName->toPlainText();
        str2.remove("\n");
        ui->textEditName->setText(str2);
        ui->textEditPath->setLineWrapColumnOrWidth(440);
        ui->textEditPath->setText(str);
        if(ui->textEditPath->document()->size().height() > 30){
            if(ui->textEditPath->document()->size().height() < 150)
                ui->textEditPath->setFixedHeight(static_cast<int>(ui->textEditPath->document()->size().height()) + 7);
        }
        else
            ui->textEditPath->setFixedHeight(30);
        ui->labelPicResult->setVisible(true);
        ui->labelPicPlace->setVisible(false);
        ui->labelResult->setStyleSheet("color: rgb(50, 50, 50); border: NONE; font-family: Arial; font-size: 12pt; font-weight: 470;");
        ui->labelPlace->setStyleSheet("color: rgb(180, 180, 180); border: NONE; font-family: Arial; font-size: 12pt; font-weight: 470;");
    }
    else if (ui->pushButton_2->text() == "Готово"){
        //отправить сигнал на создание проекта
        QString str2 = ui->textEditName->toPlainText();
        str2.remove("\n");
        str2 = str2.left(str2.indexOf("."));
        emit create(str2, ui->textEditPath->toPlainText());
        //закрыть
        QDialog::close();
    }
}
