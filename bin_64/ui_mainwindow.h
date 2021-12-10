/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButtonSupplyModules;
    QPushButton *settingsButton;
    QPlainTextEdit *textPlainEditInfrom;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_14;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_17;
    QLineEdit *currLimitlineEdit;
    QLabel *label_19;
    QLineEdit *voltLimitlineEdit;
    QLabel *label_20;
    QVBoxLayout *verticalLayout_15;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *horizontalSpacer_18;
    QLineEdit *currLimitOffEdit;
    QLabel *label_21;
    QHBoxLayout *horizontalLayout_21;
    QSpacerItem *horizontalSpacer_19;
    QLineEdit *timeLimitOffEdit;
    QLabel *label_22;
    QHBoxLayout *horizontalLayout_17;
    QSpacerItem *horizontalSpacer_20;
    QLabel *currLabel;
    QLabel *measurCurrLabel;
    QSpacerItem *horizontalSpacer_21;
    QLabel *voltLabel;
    QLabel *measurVoltLabel;
    QSpacerItem *horizontalSpacer_22;
    QPushButton *powerSupplyButton;
    QPushButton *autoPowerSupplyButton;
    QPushButton *settingsLimitsButton;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelPrigimModul_1;
    QPushButton *prigimOtgimButton;
    QLabel *labelPrigimModul_2;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *relayModeButton;
    QLabel *label_3;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *motorOnOffButton;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *pushButton_2;
    QPushButton *StartButton;
    QPushButton *StopButton;
    QPushButton *pbSaveSGD;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1701, 888);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(30, 10, 721, 831));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonSupplyModules = new QPushButton(centralwidget);
        pushButtonSupplyModules->setObjectName(QString::fromUtf8("pushButtonSupplyModules"));
        pushButtonSupplyModules->setGeometry(QRect(760, 80, 111, 23));
        settingsButton = new QPushButton(centralwidget);
        settingsButton->setObjectName(QString::fromUtf8("settingsButton"));
        settingsButton->setGeometry(QRect(1010, 80, 75, 23));
        textPlainEditInfrom = new QPlainTextEdit(centralwidget);
        textPlainEditInfrom->setObjectName(QString::fromUtf8("textPlainEditInfrom"));
        textPlainEditInfrom->setGeometry(QRect(900, 0, 461, 51));
        layoutWidget_2 = new QWidget(centralwidget);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(770, 120, 219, 147));
        verticalLayout_14 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(-1, -1, 11, -1);
        horizontalSpacer_17 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_17);

        currLimitlineEdit = new QLineEdit(layoutWidget_2);
        currLimitlineEdit->setObjectName(QString::fromUtf8("currLimitlineEdit"));
        currLimitlineEdit->setMinimumSize(QSize(70, 27));
        currLimitlineEdit->setMaximumSize(QSize(70, 27));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(11);
        currLimitlineEdit->setFont(font);
        currLimitlineEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(currLimitlineEdit);

        label_19 = new QLabel(layoutWidget_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setMaximumSize(QSize(20, 16777215));
        label_19->setFont(font);
        label_19->setStyleSheet(QString::fromUtf8("color: rgb(50, 50, 50);"));

        horizontalLayout_11->addWidget(label_19);

        voltLimitlineEdit = new QLineEdit(layoutWidget_2);
        voltLimitlineEdit->setObjectName(QString::fromUtf8("voltLimitlineEdit"));
        voltLimitlineEdit->setMinimumSize(QSize(70, 27));
        voltLimitlineEdit->setMaximumSize(QSize(70, 27));
        voltLimitlineEdit->setFont(font);
        voltLimitlineEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(voltLimitlineEdit);

        label_20 = new QLabel(layoutWidget_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setMaximumSize(QSize(20, 16777215));
        label_20->setFont(font);
        label_20->setStyleSheet(QString::fromUtf8("color: rgb(50, 50, 50);"));

        horizontalLayout_11->addWidget(label_20);


        verticalLayout_14->addLayout(horizontalLayout_11);

        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setSpacing(0);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        verticalLayout_15->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_6 = new QLabel(layoutWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(10);
        label_6->setFont(font1);

        verticalLayout_15->addWidget(label_6);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalSpacer_18 = new QSpacerItem(67, 5, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_18);

        currLimitOffEdit = new QLineEdit(layoutWidget_2);
        currLimitOffEdit->setObjectName(QString::fromUtf8("currLimitOffEdit"));
        currLimitOffEdit->setMinimumSize(QSize(70, 27));
        currLimitOffEdit->setMaximumSize(QSize(70, 27));
        currLimitOffEdit->setFont(font);
        currLimitOffEdit->setInputMethodHints(Qt::ImhNone);
        currLimitOffEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout_16->addWidget(currLimitOffEdit);

        label_21 = new QLabel(layoutWidget_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setMaximumSize(QSize(20, 16777215));
        label_21->setFont(font);
        label_21->setStyleSheet(QString::fromUtf8("color: rgb(50, 50, 50);"));

        horizontalLayout_16->addWidget(label_21);


        verticalLayout_15->addLayout(horizontalLayout_16);


        verticalLayout_14->addLayout(verticalLayout_15);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        horizontalSpacer_19 = new QSpacerItem(69, 5, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer_19);

        timeLimitOffEdit = new QLineEdit(layoutWidget_2);
        timeLimitOffEdit->setObjectName(QString::fromUtf8("timeLimitOffEdit"));
        timeLimitOffEdit->setMinimumSize(QSize(70, 27));
        timeLimitOffEdit->setMaximumSize(QSize(70, 27));
        timeLimitOffEdit->setFont(font);
        timeLimitOffEdit->setInputMethodHints(Qt::ImhNone);
        timeLimitOffEdit->setAlignment(Qt::AlignCenter);

        horizontalLayout_21->addWidget(timeLimitOffEdit);

        label_22 = new QLabel(layoutWidget_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setMaximumSize(QSize(26, 16777215));
        label_22->setFont(font);
        label_22->setStyleSheet(QString::fromUtf8("color: rgb(50, 50, 50);"));

        horizontalLayout_21->addWidget(label_22);


        verticalLayout_14->addLayout(horizontalLayout_21);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalSpacer_20 = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_20);

        currLabel = new QLabel(layoutWidget_2);
        currLabel->setObjectName(QString::fromUtf8("currLabel"));
        currLabel->setMinimumSize(QSize(40, 0));
        currLabel->setFont(font);
        currLabel->setStyleSheet(QString::fromUtf8("color: rgb(50, 50, 50);"));
        currLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_17->addWidget(currLabel);

        measurCurrLabel = new QLabel(layoutWidget_2);
        measurCurrLabel->setObjectName(QString::fromUtf8("measurCurrLabel"));
        measurCurrLabel->setMaximumSize(QSize(20, 16777215));
        measurCurrLabel->setFont(font);
        measurCurrLabel->setStyleSheet(QString::fromUtf8("color: rgb(50, 50, 50);"));
        measurCurrLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_17->addWidget(measurCurrLabel);

        horizontalSpacer_21 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_21);

        voltLabel = new QLabel(layoutWidget_2);
        voltLabel->setObjectName(QString::fromUtf8("voltLabel"));
        voltLabel->setMinimumSize(QSize(40, 0));
        voltLabel->setFont(font);
        voltLabel->setStyleSheet(QString::fromUtf8("color: rgb(50, 50, 50);"));
        voltLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_17->addWidget(voltLabel);

        measurVoltLabel = new QLabel(layoutWidget_2);
        measurVoltLabel->setObjectName(QString::fromUtf8("measurVoltLabel"));
        measurVoltLabel->setMaximumSize(QSize(20, 16777215));
        measurVoltLabel->setFont(font);
        measurVoltLabel->setStyleSheet(QString::fromUtf8("color: rgb(50, 50, 50);"));
        measurVoltLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_17->addWidget(measurVoltLabel);

        horizontalSpacer_22 = new QSpacerItem(7, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_22);


        verticalLayout_14->addLayout(horizontalLayout_17);

        verticalLayout_14->setStretch(0, 3);
        verticalLayout_14->setStretch(1, 1);
        verticalLayout_14->setStretch(3, 3);
        powerSupplyButton = new QPushButton(centralwidget);
        powerSupplyButton->setObjectName(QString::fromUtf8("powerSupplyButton"));
        powerSupplyButton->setGeometry(QRect(1020, 150, 161, 31));
        powerSupplyButton->setStyleSheet(QString::fromUtf8("#powerSupplyButton{\n"
"background-color: #18799b;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 12pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"#powerSupplyButton:pressed{\n"
"background-color: #ffffff;\n"
"color: #18799b;\n"
"border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 12pt; font-weight: 450; border-radius: 1;\n"
"}\n"
""));
        autoPowerSupplyButton = new QPushButton(centralwidget);
        autoPowerSupplyButton->setObjectName(QString::fromUtf8("autoPowerSupplyButton"));
        autoPowerSupplyButton->setGeometry(QRect(1020, 226, 162, 30));
        autoPowerSupplyButton->setMinimumSize(QSize(160, 30));
        autoPowerSupplyButton->setMaximumSize(QSize(162, 30));
        autoPowerSupplyButton->setStyleSheet(QString::fromUtf8("#autoPowerSupplyButton{\n"
"background-color: #18799b;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 12pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"#autoPowerSupplyButton:pressed{\n"
"background-color: #ffffff;\n"
"color: #18799b;\n"
"border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 12pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"\n"
""));
        settingsLimitsButton = new QPushButton(centralwidget);
        settingsLimitsButton->setObjectName(QString::fromUtf8("settingsLimitsButton"));
        settingsLimitsButton->setGeometry(QRect(1020, 190, 162, 30));
        settingsLimitsButton->setMinimumSize(QSize(162, 30));
        settingsLimitsButton->setMaximumSize(QSize(162, 30));
        settingsLimitsButton->setStyleSheet(QString::fromUtf8("#settingsLimitsButton{\n"
"background-color: #18799b;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 12pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"#settingsLimitsButton:pressed{\n"
"background-color: #ffffff;\n"
"color: #18799b;\n"
"border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 12pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"\n"
""));
        layoutWidget_3 = new QWidget(centralwidget);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(1190, 120, 163, 28));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_6->setSpacing(2);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        labelPrigimModul_1 = new QLabel(layoutWidget_3);
        labelPrigimModul_1->setObjectName(QString::fromUtf8("labelPrigimModul_1"));
        labelPrigimModul_1->setFont(font);
        labelPrigimModul_1->setStyleSheet(QString::fromUtf8("color: rgb(50, 50, 50);"));

        horizontalLayout_6->addWidget(labelPrigimModul_1);

        prigimOtgimButton = new QPushButton(layoutWidget_3);
        prigimOtgimButton->setObjectName(QString::fromUtf8("prigimOtgimButton"));
        prigimOtgimButton->setMinimumSize(QSize(52, 26));
        prigimOtgimButton->setMaximumSize(QSize(52, 26));
        prigimOtgimButton->setStyleSheet(QString::fromUtf8("#prigimOtgimButton{\n"
"background-color: transparent;\n"
"border-image: url(:/resources/elements/off.png);\n"
"background: none;\n"
"border: none;\n"
"background-repeat: none;\n"
"}\n"
"#prigimOtgimButton:pressed\n"
"{\n"
"border-image: url(:/resources/elements/on.png);\n"
"}"));

        horizontalLayout_6->addWidget(prigimOtgimButton);

        labelPrigimModul_2 = new QLabel(layoutWidget_3);
        labelPrigimModul_2->setObjectName(QString::fromUtf8("labelPrigimModul_2"));
        labelPrigimModul_2->setFont(font);
        labelPrigimModul_2->setStyleSheet(QString::fromUtf8("color: rgb(50, 50, 50);"));

        horizontalLayout_6->addWidget(labelPrigimModul_2);

        layoutWidget_4 = new QWidget(centralwidget);
        layoutWidget_4->setObjectName(QString::fromUtf8("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(1200, 160, 152, 32));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_6 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);

        relayModeButton = new QPushButton(layoutWidget_4);
        relayModeButton->setObjectName(QString::fromUtf8("relayModeButton"));
        relayModeButton->setMinimumSize(QSize(147, 30));
        relayModeButton->setMaximumSize(QSize(147, 30));
        relayModeButton->setStyleSheet(QString::fromUtf8("#relayModeButton{\n"
"background-color: #18799b;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"#relayModeButton:pressed{\n"
"background-color: #ffffff;\n"
"color: #18799b; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}"));
        relayModeButton->setCheckable(true);

        horizontalLayout_7->addWidget(relayModeButton);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(1180, 90, 180, 36));
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(50, 50, 50);"));
        label_3->setAlignment(Qt::AlignCenter);
        layoutWidget_5 = new QWidget(centralwidget);
        layoutWidget_5->setObjectName(QString::fromUtf8("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(1200, 210, 152, 32));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget_5);
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        motorOnOffButton = new QPushButton(layoutWidget_5);
        motorOnOffButton->setObjectName(QString::fromUtf8("motorOnOffButton"));
        motorOnOffButton->setMinimumSize(QSize(147, 30));
        motorOnOffButton->setMaximumSize(QSize(147, 30));
        motorOnOffButton->setStyleSheet(QString::fromUtf8("#motorOnOffButton{\n"
"background-color: #18799b;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"#motorOnOffButton:pressed{\n"
"background-color: #ffffff;\n"
"color: #18799b; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}"));

        horizontalLayout_8->addWidget(motorOnOffButton);

        horizontalSpacer_10 = new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_10);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(1100, 290, 131, 31));
        StartButton = new QPushButton(centralwidget);
        StartButton->setObjectName(QString::fromUtf8("StartButton"));
        StartButton->setGeometry(QRect(834, 290, 101, 31));
        StopButton = new QPushButton(centralwidget);
        StopButton->setObjectName(QString::fromUtf8("StopButton"));
        StopButton->setGeometry(QRect(950, 290, 111, 31));
        pbSaveSGD = new QPushButton(centralwidget);
        pbSaveSGD->setObjectName(QString::fromUtf8("pbSaveSGD"));
        pbSaveSGD->setGeometry(QRect(1250, 290, 131, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1701, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButtonSupplyModules->setText(QCoreApplication::translate("MainWindow", "\320\237\320\270\321\202\320\260\320\275\320\270\320\265 \320\277\321\200\320\270\320\261\320\276\321\200\320\276\320\262", nullptr));
        settingsButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260", nullptr));
        currLimitlineEdit->setText(QCoreApplication::translate("MainWindow", "0,4", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "\320\220", nullptr));
        voltLimitlineEdit->setText(QCoreApplication::translate("MainWindow", "100", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "\320\222", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\320\273. \320\261\320\273\320\276\320\272\320\260 \320\277\320\270\321\202\320\260\320\275\320\270\321\217 \320\277\321\200\320\270:", nullptr));
        currLimitOffEdit->setText(QCoreApplication::translate("MainWindow", "0,3", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "\320\220", nullptr));
        timeLimitOffEdit->setText(QCoreApplication::translate("MainWindow", "30", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "\321\201\320\265\320\272", nullptr));
        currLabel->setText(QCoreApplication::translate("MainWindow", "0 ", nullptr));
        measurCurrLabel->setText(QCoreApplication::translate("MainWindow", "A", nullptr));
        voltLabel->setText(QCoreApplication::translate("MainWindow", "0 ", nullptr));
        measurVoltLabel->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        powerSupplyButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\232\320\233 \320\277\320\270\321\202\320\260\320\275\320\270\320\265", nullptr));
        autoPowerSupplyButton->setText(QCoreApplication::translate("MainWindow", "\320\220\320\262\321\202\320\276 \321\203\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265", nullptr));
        settingsLimitsButton->setText(QCoreApplication::translate("MainWindow", "\320\243\321\201\321\202. \320\276\320\263\321\200\320\260\320\275\320\270\321\207\320\265\320\275\320\270\320\271", nullptr));
        labelPrigimModul_1->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\266\320\270\320\274", nullptr));
        prigimOtgimButton->setText(QString());
        labelPrigimModul_2->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\266\320\270\320\274", nullptr));
        relayModeButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\272\320\273 \320\240\320\265\320\273\320\265", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\224\320\273\321\217 \320\262\321\201\320\265\321\205 \320\274\320\276\320\264\321\203\320\273\320\265\320\271", nullptr));
        motorOnOffButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\272\320\273 \320\234\320\276\321\202\320\276\321\200", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Save SGD", nullptr));
        StartButton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        StopButton->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        pbSaveSGD->setText(QCoreApplication::translate("MainWindow", "Save SGD v2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
