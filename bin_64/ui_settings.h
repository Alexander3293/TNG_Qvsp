/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Settings
{
public:
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButtonNumDnModMin;
    QPushButton *startDwnHoleButton;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *startUpHoleButton;
    QPushButton *stopUpHoleButton;
    QToolButton *toolButtonNumWellsModMin;
    QLineEdit *lineEditNumWellsMod;
    QPushButton *pushButton;
    QLineEdit *lineEditNumDnMod;
    QToolButton *toolButtonNumDnModPlus;
    QToolButton *toolButtonNumWellsModPlus;
    QLabel *labelNumWellsMod;
    QLabel *labelNumDnMod;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *extraSettingsButton;
    QSpacerItem *horizontalSpacer_12;
    QFrame *line;
    QSpacerItem *verticalSpacer_6;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QGridLayout *gridLayout_5;
    QLabel *labelCmd;
    QSpacerItem *horizontalSpacer_16;
    QLabel *labelChannel;
    QComboBox *comboBoxCMD;
    QSpacerItem *horizontalSpacer_17;
    QSpacerItem *horizontalSpacer_5;
    QComboBox *comboBoxChannel;
    QPushButton *buttonStopSync;
    QPushButton *startSyncButton;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_3;
    QFrame *line_2;
    QSpacerItem *verticalSpacer_9;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QGridLayout *gridLayout_4;
    QLabel *labelTimeRecord;
    QLabel *labelCountRecord;
    QLabel *labelTimeWaiting;
    QToolButton *toolButtonCountRecordMin;
    QToolButton *toolButtonCountRecordPlus;
    QSpacerItem *horizontalSpacer_14;
    QLabel *labelTime1;
    QLineEdit *lineEditCountRecord;
    QSpacerItem *horizontalSpacer_13;
    QLabel *labelTime2;
    QSpacerItem *horizontalSpacer_15;
    QSpacerItem *verticalSpacer_3;
    QFrame *line_4;
    QVBoxLayout *verticalLayout_7;
    QLabel *labelServiceInfo;
    QGridLayout *gridLayout_3;
    QLabel *labelOperator;
    QLineEdit *lineEditNameArea;
    QLabel *labelNameArea;
    QLineEdit *lineEditDepth;
    QLabel *labelNumHole;
    QLabel *labelDepth;
    QLineEdit *lineEditOperator;
    QLineEdit *lineEditNumHole;
    QSpacerItem *horizontalSpacer_18;
    QSpacerItem *horizontalSpacer_19;
    QLabel *labelDistBtwDevices;
    QLineEdit *lineEditDistBtwDevices;
    QFrame *line_3;
    QSpacerItem *verticalSpacer_4;
    QVBoxLayout *verticalLayout_6;
    QLabel *labelCorr;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_61;
    QSpacerItem *horizontalSpacer_10;
    QLabel *labelZeroLines;
    QComboBox *comboBoxCorDraw;
    QCheckBox *checkBoxZeroLines;
    QLabel *labelCorSave;
    QLineEdit *lineSwipLen;
    QLabel *labelSwipTime;
    QCheckBox *checkBoxSaveMod;
    QLabel *labelModem;
    QCheckBox *checkBoxModem;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Settings)
    {
        if (Settings->objectName().isEmpty())
            Settings->setObjectName(QString::fromUtf8("Settings"));
        Settings->setWindowModality(Qt::WindowModal);
        Settings->resize(507, 1000);
        Settings->setMinimumSize(QSize(425, 1000));
        Settings->setMaximumSize(QSize(507, 1200));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(12);
        Settings->setFont(font);
        Settings->setContextMenuPolicy(Qt::ActionsContextMenu);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/SettingsLogo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Settings->setWindowIcon(icon);
        verticalLayout_5 = new QVBoxLayout(Settings);
        verticalLayout_5->setSpacing(8);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(15, 15, 15, 15);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(Settings);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 20));
        label->setMaximumSize(QSize(16777215, 20));

        verticalLayout_2->addWidget(label);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(0);
        gridLayout->setVerticalSpacing(15);
        gridLayout->setContentsMargins(0, -1, -1, -1);
        horizontalSpacer = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 0, 1, 1);

        toolButtonNumDnModMin = new QToolButton(Settings);
        toolButtonNumDnModMin->setObjectName(QString::fromUtf8("toolButtonNumDnModMin"));

        gridLayout->addWidget(toolButtonNumDnModMin, 0, 3, 1, 1);

        startDwnHoleButton = new QPushButton(Settings);
        startDwnHoleButton->setObjectName(QString::fromUtf8("startDwnHoleButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(startDwnHoleButton->sizePolicy().hasHeightForWidth());
        startDwnHoleButton->setSizePolicy(sizePolicy);
        startDwnHoleButton->setMinimumSize(QSize(100, 23));
        startDwnHoleButton->setMaximumSize(QSize(100, 16777215));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setWeight(56);
        startDwnHoleButton->setFont(font1);
        startDwnHoleButton->setStyleSheet(QString::fromUtf8("#startDwnHoleButton{\n"
"background-color: #18799b;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"#startDwnHoleButton:pressed{\n"
"background-color: #ffffff;\n"
"color: #18799b;\n"
"border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"\n"
""));

        gridLayout->addWidget(startDwnHoleButton, 2, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        startUpHoleButton = new QPushButton(Settings);
        startUpHoleButton->setObjectName(QString::fromUtf8("startUpHoleButton"));
        startUpHoleButton->setMinimumSize(QSize(100, 23));
        startUpHoleButton->setMaximumSize(QSize(100, 23));
        startUpHoleButton->setFont(font1);
        startUpHoleButton->setStyleSheet(QString::fromUtf8("#startUpHoleButton{\n"
"background-color: #18799b;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"#startUpHoleButton:pressed{\n"
"background-color: #ffffff;\n"
"color: #18799b;\n"
"border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"\n"
""));

        horizontalLayout_3->addWidget(startUpHoleButton);

        stopUpHoleButton = new QPushButton(Settings);
        stopUpHoleButton->setObjectName(QString::fromUtf8("stopUpHoleButton"));
        stopUpHoleButton->setMinimumSize(QSize(100, 23));
        stopUpHoleButton->setMaximumSize(QSize(100, 23));
        stopUpHoleButton->setFont(font1);
        stopUpHoleButton->setStyleSheet(QString::fromUtf8("#stopUpHoleButton{\n"
"background-color: #ffffff;\n"
"color: #18799b; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"#stopUpHoleButton:pressed{\n"
"background-color: #18799b;\n"
"color: #ffffff;\n"
"border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"\n"
""));

        horizontalLayout_3->addWidget(stopUpHoleButton);


        gridLayout->addLayout(horizontalLayout_3, 4, 1, 1, 1);

        toolButtonNumWellsModMin = new QToolButton(Settings);
        toolButtonNumWellsModMin->setObjectName(QString::fromUtf8("toolButtonNumWellsModMin"));

        gridLayout->addWidget(toolButtonNumWellsModMin, 3, 3, 1, 1);

        lineEditNumWellsMod = new QLineEdit(Settings);
        lineEditNumWellsMod->setObjectName(QString::fromUtf8("lineEditNumWellsMod"));
        lineEditNumWellsMod->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(lineEditNumWellsMod, 3, 4, 1, 1);

        pushButton = new QPushButton(Settings);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(45, 0));
        pushButton->setMaximumSize(QSize(45, 16777215));
        pushButton->setStyleSheet(QString::fromUtf8("#pushButton{\n"
"background-color: #000000;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"#pushButton:pressed{\n"
"background-color: #ffffff;\n"
"color:  #000000;\n"
"border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"\n"
""));

        gridLayout->addWidget(pushButton, 4, 4, 1, 1);

        lineEditNumDnMod = new QLineEdit(Settings);
        lineEditNumDnMod->setObjectName(QString::fromUtf8("lineEditNumDnMod"));
        lineEditNumDnMod->setMinimumSize(QSize(0, 0));
        lineEditNumDnMod->setMaximumSize(QSize(100, 16777215));
        lineEditNumDnMod->setTabletTracking(false);

        gridLayout->addWidget(lineEditNumDnMod, 0, 4, 1, 1);

        toolButtonNumDnModPlus = new QToolButton(Settings);
        toolButtonNumDnModPlus->setObjectName(QString::fromUtf8("toolButtonNumDnModPlus"));

        gridLayout->addWidget(toolButtonNumDnModPlus, 0, 5, 1, 1);

        toolButtonNumWellsModPlus = new QToolButton(Settings);
        toolButtonNumWellsModPlus->setObjectName(QString::fromUtf8("toolButtonNumWellsModPlus"));

        gridLayout->addWidget(toolButtonNumWellsModPlus, 3, 5, 1, 1);

        labelNumWellsMod = new QLabel(Settings);
        labelNumWellsMod->setObjectName(QString::fromUtf8("labelNumWellsMod"));

        gridLayout->addWidget(labelNumWellsMod, 3, 1, 1, 1);

        labelNumDnMod = new QLabel(Settings);
        labelNumDnMod->setObjectName(QString::fromUtf8("labelNumDnMod"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setBold(false);
        font2.setWeight(50);
        labelNumDnMod->setFont(font2);
        labelNumDnMod->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(labelNumDnMod, 0, 1, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 3, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 3, 6, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        verticalLayout->addLayout(verticalLayout_2);

        verticalSpacer_2 = new QSpacerItem(390, 13, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_6 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        extraSettingsButton = new QPushButton(Settings);
        extraSettingsButton->setObjectName(QString::fromUtf8("extraSettingsButton"));
        extraSettingsButton->setMinimumSize(QSize(330, 27));
        extraSettingsButton->setStyleSheet(QString::fromUtf8("#extraSettingsButton{\n"
"background-color: #18799b;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 12pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"#extraSettingsButton:pressed{\n"
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

        horizontalLayout_2->addWidget(extraSettingsButton);

        horizontalSpacer_12 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_12);


        verticalLayout->addLayout(horizontalLayout_2);

        line = new QFrame(Settings);
        line->setObjectName(QString::fromUtf8("line"));
        line->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(50, 50, 50);"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        verticalSpacer_6 = new QSpacerItem(390, 13, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_6);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_3 = new QLabel(Settings);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_4->addWidget(label_3);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        labelCmd = new QLabel(Settings);
        labelCmd->setObjectName(QString::fromUtf8("labelCmd"));
        labelCmd->setMinimumSize(QSize(60, 0));
        labelCmd->setMaximumSize(QSize(1600, 16777215));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Arial"));
        font3.setPointSize(10);
        labelCmd->setFont(font3);
        labelCmd->setStyleSheet(QString::fromUtf8("color: rgb(50, 50, 50);"));

        gridLayout_5->addWidget(labelCmd, 0, 1, 1, 1);

        horizontalSpacer_16 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_16, 0, 0, 1, 1);

        labelChannel = new QLabel(Settings);
        labelChannel->setObjectName(QString::fromUtf8("labelChannel"));
        labelChannel->setMinimumSize(QSize(60, 0));
        labelChannel->setMaximumSize(QSize(65, 16777215));
        labelChannel->setFont(font3);
        labelChannel->setStyleSheet(QString::fromUtf8("color: rgb(50, 50, 50);"));

        gridLayout_5->addWidget(labelChannel, 1, 1, 1, 1);

        comboBoxCMD = new QComboBox(Settings);
        comboBoxCMD->setObjectName(QString::fromUtf8("comboBoxCMD"));
        comboBoxCMD->setMinimumSize(QSize(0, 0));
        QFont font4;
        font4.setPointSize(11);
        comboBoxCMD->setFont(font4);
        comboBoxCMD->setAutoFillBackground(false);
        comboBoxCMD->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    border: 1px solid rgb(178,178,178);\n"
"    border-radius: 2px;\n"
"	font-style: Arial;\n"
"	font-size: 11pt;\n"
"	color: #18799b;\n"
"	background-color: #ffffff;\n"
"}\n"
"\n"
"QComboBox:editable {\n"
"    background: #ffffff;\n"
"}\n"
"\n"
"QComboBox:!editable, QComboBox::drop-down:editable {\n"
"     background: #ffffff;\n"
"}\n"
"\n"
"QComboBox:!editable:on, QComboBox::drop-down:editable:on {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #ffffff, stop: 0.4 #D8D8D8,\n"
"                                stop: 0.5 #DDDDDD, stop: 1.0 #E1E1E1);\n"
"}\n"
"/*QComboBox:on { /* shift the text when the popup opens */\n"
"/*    padding-top: 3px;\n"
"    padding-left: 6px;\n"
"}*/\n"
"\n"
"QComboBox::drop-down:button{\n"
"	background-color: #18799b;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 18px;\n"
"\n"
"    border-left-width: 2px;\n"
"    border-left-"
                        "color:rgb(178,178,178);\n"
"    border-left-style: solid; /* just a single line */\n"
"    border-top-right-radius: 1px; /* same radius as the QComboBox */\n"
"    border-bottom-right-radius: 1px;\n"
"}\n"
"\n"
"QComboBox::down-arrow:on { /* shift the arrow when popup is open */\n"
"    top: 1px;\n"
"    left: 1px;\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"    selection-background-color: #18799b;\n"
"    selection-color: #ffffff;\n"
"	color: #18799b;\n"
" 	background-color: #ffffff;\n"
"    border: 1px solid rgb(178,178,178);\n"
"	margin-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}"));
        comboBoxCMD->setDuplicatesEnabled(false);

        gridLayout_5->addWidget(comboBoxCMD, 0, 3, 1, 1);

        horizontalSpacer_17 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_17, 0, 4, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_5, 0, 2, 1, 1);

        comboBoxChannel = new QComboBox(Settings);
        comboBoxChannel->setObjectName(QString::fromUtf8("comboBoxChannel"));
        comboBoxChannel->setMinimumSize(QSize(80, 0));
        comboBoxChannel->setFont(font4);
        comboBoxChannel->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    border: 1px solid rgb(178,178,178);\n"
"    border-radius: 2px;\n"
"	font-style: Arial;\n"
"	font-size: 11pt;\n"
"	color: #18799b;\n"
"	background-color: #ffffff;\n"
"}\n"
"\n"
"QComboBox:editable {\n"
"    background: #ffffff;\n"
"}\n"
"\n"
"QComboBox:!editable, QComboBox::drop-down:editable {\n"
"     background: #ffffff;\n"
"}\n"
"\n"
"QComboBox:!editable:on, QComboBox::drop-down:editable:on {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #ffffff, stop: 0.4 #D8D8D8,\n"
"                                stop: 0.5 #DDDDDD, stop: 1.0 #E1E1E1);\n"
"}\n"
"/*QComboBox:on { /* shift the text when the popup opens */\n"
"/*    padding-top: 3px;\n"
"    padding-left: 6px;\n"
"}*/\n"
"\n"
"QComboBox::drop-down:button{\n"
"	background-color: #18799b;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 18px;\n"
"\n"
"    border-left-width: 2px;\n"
"    border-left-"
                        "color:rgb(178,178,178);\n"
"    border-left-style: solid; /* just a single line */\n"
"    border-top-right-radius: 1px; /* same radius as the QComboBox */\n"
"    border-bottom-right-radius: 1px;\n"
"}\n"
"\n"
"QComboBox::down-arrow:on { /* shift the arrow when popup is open */\n"
"    top: 1px;\n"
"    left: 1px;\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"    selection-background-color: #18799b;\n"
"    selection-color: #ffffff;\n"
"	color: #18799b;\n"
" 	background-color: #ffffff;\n"
"    border: 1px solid rgb(178,178,178);\n"
"	margin-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}"));

        gridLayout_5->addWidget(comboBoxChannel, 1, 3, 1, 1);

        buttonStopSync = new QPushButton(Settings);
        buttonStopSync->setObjectName(QString::fromUtf8("buttonStopSync"));
        buttonStopSync->setStyleSheet(QString::fromUtf8("#buttonStopSync{\n"
"background-color: #ffffff;\n"
"color: #18799b; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"#buttonStopSync:pressed{\n"
"background-color: #18799b;\n"
"color: #ffffff;\n"
"border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}"));

        gridLayout_5->addWidget(buttonStopSync, 2, 3, 1, 1);

        startSyncButton = new QPushButton(Settings);
        startSyncButton->setObjectName(QString::fromUtf8("startSyncButton"));
        startSyncButton->setStyleSheet(QString::fromUtf8("#startSyncButton{\n"
"background-color: #18799b;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"#startSyncButton:pressed{\n"
"background-color: #ffffff;\n"
"color: #18799b;\n"
"border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"\n"
""));

        gridLayout_5->addWidget(startSyncButton, 2, 1, 1, 1);


        verticalLayout_4->addLayout(gridLayout_5);


        verticalLayout->addLayout(verticalLayout_4);

        verticalSpacer_5 = new QSpacerItem(390, 13, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_2 = new QPushButton(Settings);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(140, 30));
        pushButton_2->setMaximumSize(QSize(140, 30));

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_9);

        pushButton_3 = new QPushButton(Settings);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(140, 30));
        pushButton_3->setMaximumSize(QSize(140, 30));

        horizontalLayout->addWidget(pushButton_3);

        horizontalSpacer_3 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 2);
        horizontalLayout->setStretch(2, 1);
        horizontalLayout->setStretch(4, 1);

        verticalLayout->addLayout(horizontalLayout);

        line_2 = new QFrame(Settings);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        verticalSpacer_9 = new QSpacerItem(390, 13, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_9);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_2 = new QLabel(Settings);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_3->addWidget(label_2);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(0);
        gridLayout_4->setVerticalSpacing(15);
        labelTimeRecord = new QLabel(Settings);
        labelTimeRecord->setObjectName(QString::fromUtf8("labelTimeRecord"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelTimeRecord->sizePolicy().hasHeightForWidth());
        labelTimeRecord->setSizePolicy(sizePolicy1);
        QFont font5;
        font5.setPointSize(10);
        labelTimeRecord->setFont(font5);

        gridLayout_4->addWidget(labelTimeRecord, 0, 1, 1, 1);

        labelCountRecord = new QLabel(Settings);
        labelCountRecord->setObjectName(QString::fromUtf8("labelCountRecord"));
        labelCountRecord->setLayoutDirection(Qt::LeftToRight);

        gridLayout_4->addWidget(labelCountRecord, 1, 1, 1, 1);

        labelTimeWaiting = new QLabel(Settings);
        labelTimeWaiting->setObjectName(QString::fromUtf8("labelTimeWaiting"));

        gridLayout_4->addWidget(labelTimeWaiting, 2, 1, 1, 1);

        toolButtonCountRecordMin = new QToolButton(Settings);
        toolButtonCountRecordMin->setObjectName(QString::fromUtf8("toolButtonCountRecordMin"));

        gridLayout_4->addWidget(toolButtonCountRecordMin, 1, 3, 1, 1);

        toolButtonCountRecordPlus = new QToolButton(Settings);
        toolButtonCountRecordPlus->setObjectName(QString::fromUtf8("toolButtonCountRecordPlus"));

        gridLayout_4->addWidget(toolButtonCountRecordPlus, 1, 5, 1, 1);

        horizontalSpacer_14 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_14, 1, 6, 1, 1);

        labelTime1 = new QLabel(Settings);
        labelTime1->setObjectName(QString::fromUtf8("labelTime1"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelTime1->sizePolicy().hasHeightForWidth());
        labelTime1->setSizePolicy(sizePolicy2);
        QFont font6;
        font6.setFamily(QString::fromUtf8("Arial"));
        font6.setPointSize(11);
        labelTime1->setFont(font6);
        labelTime1->setStyleSheet(QString::fromUtf8("color: rgb(50, 50, 50);"));

        gridLayout_4->addWidget(labelTime1, 0, 5, 1, 1);

        lineEditCountRecord = new QLineEdit(Settings);
        lineEditCountRecord->setObjectName(QString::fromUtf8("lineEditCountRecord"));

        gridLayout_4->addWidget(lineEditCountRecord, 1, 4, 1, 1);

        horizontalSpacer_13 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_13, 1, 0, 1, 1);

        labelTime2 = new QLabel(Settings);
        labelTime2->setObjectName(QString::fromUtf8("labelTime2"));
        labelTime2->setFont(font6);
        labelTime2->setStyleSheet(QString::fromUtf8("color: rgb(50, 50, 50);"));

        gridLayout_4->addWidget(labelTime2, 2, 5, 1, 1);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_15, 1, 2, 1, 1);


        verticalLayout_3->addLayout(gridLayout_4);


        verticalLayout->addLayout(verticalLayout_3);

        verticalSpacer_3 = new QSpacerItem(390, 13, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_3);

        line_4 = new QFrame(Settings);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_4);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        labelServiceInfo = new QLabel(Settings);
        labelServiceInfo->setObjectName(QString::fromUtf8("labelServiceInfo"));

        verticalLayout_7->addWidget(labelServiceInfo);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        labelOperator = new QLabel(Settings);
        labelOperator->setObjectName(QString::fromUtf8("labelOperator"));

        gridLayout_3->addWidget(labelOperator, 1, 1, 1, 1);

        lineEditNameArea = new QLineEdit(Settings);
        lineEditNameArea->setObjectName(QString::fromUtf8("lineEditNameArea"));

        gridLayout_3->addWidget(lineEditNameArea, 3, 2, 1, 1);

        labelNameArea = new QLabel(Settings);
        labelNameArea->setObjectName(QString::fromUtf8("labelNameArea"));

        gridLayout_3->addWidget(labelNameArea, 3, 1, 1, 1);

        lineEditDepth = new QLineEdit(Settings);
        lineEditDepth->setObjectName(QString::fromUtf8("lineEditDepth"));

        gridLayout_3->addWidget(lineEditDepth, 0, 2, 1, 1);

        labelNumHole = new QLabel(Settings);
        labelNumHole->setObjectName(QString::fromUtf8("labelNumHole"));

        gridLayout_3->addWidget(labelNumHole, 2, 1, 1, 1);

        labelDepth = new QLabel(Settings);
        labelDepth->setObjectName(QString::fromUtf8("labelDepth"));

        gridLayout_3->addWidget(labelDepth, 0, 1, 1, 1);

        lineEditOperator = new QLineEdit(Settings);
        lineEditOperator->setObjectName(QString::fromUtf8("lineEditOperator"));

        gridLayout_3->addWidget(lineEditOperator, 1, 2, 1, 1);

        lineEditNumHole = new QLineEdit(Settings);
        lineEditNumHole->setObjectName(QString::fromUtf8("lineEditNumHole"));

        gridLayout_3->addWidget(lineEditNumHole, 2, 2, 1, 1);

        horizontalSpacer_18 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_18, 2, 0, 1, 1);

        horizontalSpacer_19 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_19, 1, 3, 1, 1);

        labelDistBtwDevices = new QLabel(Settings);
        labelDistBtwDevices->setObjectName(QString::fromUtf8("labelDistBtwDevices"));

        gridLayout_3->addWidget(labelDistBtwDevices, 4, 1, 1, 1);

        lineEditDistBtwDevices = new QLineEdit(Settings);
        lineEditDistBtwDevices->setObjectName(QString::fromUtf8("lineEditDistBtwDevices"));

        gridLayout_3->addWidget(lineEditDistBtwDevices, 4, 2, 1, 1);


        verticalLayout_7->addLayout(gridLayout_3);


        verticalLayout->addLayout(verticalLayout_7);

        line_3 = new QFrame(Settings);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        verticalSpacer_4 = new QSpacerItem(390, 13, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_4);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        labelCorr = new QLabel(Settings);
        labelCorr->setObjectName(QString::fromUtf8("labelCorr"));

        verticalLayout_6->addWidget(labelCorr);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 2, 2, 1, 1);

        horizontalSpacer_61 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_61, 2, 0, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_10, 3, 5, 1, 1);

        labelZeroLines = new QLabel(Settings);
        labelZeroLines->setObjectName(QString::fromUtf8("labelZeroLines"));

        gridLayout_2->addWidget(labelZeroLines, 1, 1, 1, 1);

        comboBoxCorDraw = new QComboBox(Settings);
        comboBoxCorDraw->setObjectName(QString::fromUtf8("comboBoxCorDraw"));
        comboBoxCorDraw->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    border: 1px solid rgb(178,178,178);\n"
"    border-radius: 2px;\n"
"	font-style: Arial;\n"
"	font-size: 11pt;\n"
"	color: #18799b;\n"
"	background-color: #ffffff;\n"
"}\n"
"\n"
"QComboBox:editable {\n"
"    background: #ffffff;\n"
"}\n"
"\n"
"QComboBox:!editable, QComboBox::drop-down:editable {\n"
"     background: #ffffff;\n"
"}\n"
"\n"
"QComboBox:!editable:on, QComboBox::drop-down:editable:on {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                stop: 0 #ffffff, stop: 0.4 #D8D8D8,\n"
"                                stop: 0.5 #DDDDDD, stop: 1.0 #E1E1E1);\n"
"}\n"
"/*QComboBox:on { /* shift the text when the popup opens */\n"
"/*    padding-top: 3px;\n"
"    padding-left: 6px;\n"
"}*/\n"
"\n"
"QComboBox::drop-down:button{\n"
"	background-color: #18799b;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 18px;\n"
"\n"
"    border-left-width: 2px;\n"
"    border-left-"
                        "color:rgb(178,178,178);\n"
"    border-left-style: solid; /* just a single line */\n"
"    border-top-right-radius: 1px; /* same radius as the QComboBox */\n"
"    border-bottom-right-radius: 1px;\n"
"}\n"
"\n"
"QComboBox::down-arrow:on { /* shift the arrow when popup is open */\n"
"    top: 1px;\n"
"    left: 1px;\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"    selection-background-color: #18799b;\n"
"    selection-color: #ffffff;\n"
"	color: #18799b;\n"
" 	background-color: #ffffff;\n"
"    border: 1px solid rgb(178,178,178);\n"
"	margin-top: 0px;\n"
"    padding-bottom: 0px;\n"
"}"));

        gridLayout_2->addWidget(comboBoxCorDraw, 4, 3, 1, 1);

        checkBoxZeroLines = new QCheckBox(Settings);
        checkBoxZeroLines->setObjectName(QString::fromUtf8("checkBoxZeroLines"));
        checkBoxZeroLines->setStyleSheet(QString::fromUtf8("QCheckBox::indicator {\n"
" border: 1px solid rgb(0, 151, 167);\n"
" border-radius:2px;\n"
"background: none;}\n"
"QCheckBox::indicator:checked{\n"
"color: rgb(53, 53, 53);\n"
"background-color:rgb(0, 151, 167);}"));

        gridLayout_2->addWidget(checkBoxZeroLines, 1, 4, 1, 1);

        labelCorSave = new QLabel(Settings);
        labelCorSave->setObjectName(QString::fromUtf8("labelCorSave"));

        gridLayout_2->addWidget(labelCorSave, 3, 1, 1, 1);

        lineSwipLen = new QLineEdit(Settings);
        lineSwipLen->setObjectName(QString::fromUtf8("lineSwipLen"));

        gridLayout_2->addWidget(lineSwipLen, 3, 3, 1, 1);

        labelSwipTime = new QLabel(Settings);
        labelSwipTime->setObjectName(QString::fromUtf8("labelSwipTime"));
        labelSwipTime->setFont(font4);
        labelSwipTime->setStyleSheet(QString::fromUtf8("color: rgb(50, 50, 50);"));

        gridLayout_2->addWidget(labelSwipTime, 3, 4, 1, 1);

        checkBoxSaveMod = new QCheckBox(Settings);
        checkBoxSaveMod->setObjectName(QString::fromUtf8("checkBoxSaveMod"));
        checkBoxSaveMod->setStyleSheet(QString::fromUtf8("QCheckBox::indicator {\n"
" border: 1px solid rgb(0, 151, 167);\n"
" border-radius:2px;\n"
"background: none;}\n"
"QCheckBox::indicator:checked{\n"
"color: rgb(53, 53, 53);\n"
"background-color:rgb(0, 151, 167);}"));

        gridLayout_2->addWidget(checkBoxSaveMod, 2, 4, 1, 1);

        labelModem = new QLabel(Settings);
        labelModem->setObjectName(QString::fromUtf8("labelModem"));

        gridLayout_2->addWidget(labelModem, 0, 1, 1, 1);

        checkBoxModem = new QCheckBox(Settings);
        checkBoxModem->setObjectName(QString::fromUtf8("checkBoxModem"));
        checkBoxModem->setStyleSheet(QString::fromUtf8("QCheckBox::indicator {\n"
" border: 1px solid rgb(0, 151, 167);\n"
" border-radius:2px;\n"
"background: none;}\n"
"QCheckBox::indicator:checked{\n"
"color: rgb(53, 53, 53);\n"
"background-color:rgb(0, 151, 167);}"));

        gridLayout_2->addWidget(checkBoxModem, 0, 4, 1, 1);


        verticalLayout_6->addLayout(gridLayout_2);


        verticalLayout->addLayout(verticalLayout_6);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_8);

        verticalLayout->setStretch(0, 5);
        verticalLayout->setStretch(17, 1);

        verticalLayout_5->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_5->addItem(verticalSpacer);


        retranslateUi(Settings);

        QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QWidget *Settings)
    {
        Settings->setWindowTitle(QCoreApplication::translate("Settings", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
        label->setText(QCoreApplication::translate("Settings", "\320\234\320\276\320\264\321\203\320\273\320\270", nullptr));
        toolButtonNumDnModMin->setText(QCoreApplication::translate("Settings", "...", nullptr));
        startDwnHoleButton->setText(QCoreApplication::translate("Settings", "\320\241\321\202\320\260\321\200\321\202", nullptr));
        startUpHoleButton->setText(QCoreApplication::translate("Settings", "\320\241\321\202\320\260\321\200\321\202", nullptr));
        stopUpHoleButton->setText(QCoreApplication::translate("Settings", "\320\241\321\202\320\276\320\277", nullptr));
        toolButtonNumWellsModMin->setText(QCoreApplication::translate("Settings", "...", nullptr));
        pushButton->setText(QCoreApplication::translate("Settings", "\320\262\321\213\320\272\320\273", nullptr));
        toolButtonNumDnModPlus->setText(QCoreApplication::translate("Settings", "...", nullptr));
        toolButtonNumWellsModPlus->setText(QCoreApplication::translate("Settings", "...", nullptr));
        labelNumWellsMod->setText(QCoreApplication::translate("Settings", "\320\235\320\260\320\267\320\265\320\274\320\275\321\213\320\265 \320\274\320\276\320\264\321\203\320\273\320\270", nullptr));
        labelNumDnMod->setText(QCoreApplication::translate("Settings", "\320\241\320\272\320\262\320\260\320\266\320\270\320\275\320\275\321\213\320\265 \320\274\320\276\320\264\321\203\320\273\320\270", nullptr));
        extraSettingsButton->setText(QCoreApplication::translate("Settings", "\320\224\320\276\320\277\320\276\320\273\320\275\320\270\321\202\320\265\320\273\321\214\320\275\321\213\320\265 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\274\320\276\320\264\321\203\320\273\320\265\320\271", nullptr));
        label_3->setText(QCoreApplication::translate("Settings", "\320\234\320\276\320\264\321\203\320\273\321\214 \321\201\320\270\320\275\321\205\321\200\320\276\320\275\320\270\320\267\320\260\321\206\320\270\320\270", nullptr));
        labelCmd->setText(QCoreApplication::translate("Settings", "\320\230\321\201\321\202\320\276\321\207\320\275\320\270\320\272 \320\262\320\276\320\267\320\264\320\265\320\271\321\201\321\202\320\262\320\270\321\217", nullptr));
        labelChannel->setText(QCoreApplication::translate("Settings", "\320\232\320\260\320\275\320\260\320\273", nullptr));
        buttonStopSync->setText(QCoreApplication::translate("Settings", "\320\241\321\202\320\276\320\277", nullptr));
        startSyncButton->setText(QCoreApplication::translate("Settings", "\320\241\321\202\320\260\321\200\321\202", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Settings", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Settings", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        label_2->setText(QCoreApplication::translate("Settings", "\320\227\320\260\320\277\320\270\321\201\321\214", nullptr));
        labelTimeRecord->setText(QCoreApplication::translate("Settings", "\320\222\321\200\320\265\320\274\321\217 \320\267\320\260\320\277\320\270\321\201\320\270", nullptr));
        labelCountRecord->setText(QCoreApplication::translate("Settings", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\267\320\260\320\277\320\270\321\201\320\265\320\271", nullptr));
        labelTimeWaiting->setText(QCoreApplication::translate("Settings", "\320\236\320\266\320\270\320\264\320\260\320\275\320\270\320\265 \320\274\320\265\320\266\320\264\321\203 \320\267\320\260\320\277\320\270\321\201\321\217\320\274\320\270", nullptr));
        toolButtonCountRecordMin->setText(QCoreApplication::translate("Settings", "...", nullptr));
        toolButtonCountRecordPlus->setText(QCoreApplication::translate("Settings", "...", nullptr));
        labelTime1->setText(QCoreApplication::translate("Settings", "c\320\265\320\272", nullptr));
        labelTime2->setText(QCoreApplication::translate("Settings", "\320\274\321\201", nullptr));
        labelServiceInfo->setText(QCoreApplication::translate("Settings", "\320\241\320\273\321\203\320\266\320\265\320\261\320\275\320\260\321\217 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217", nullptr));
        labelOperator->setText(QCoreApplication::translate("Settings", "\320\244\320\230\320\236 \320\276\320\277\320\265\321\200\320\260\321\202\320\276\321\200\320\260", nullptr));
        labelNameArea->setText(QCoreApplication::translate("Settings", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\277\320\273\320\276\321\211\320\260\320\264\320\270", nullptr));
        labelNumHole->setText(QCoreApplication::translate("Settings", "\342\204\226 \321\201\320\272\320\262\320\260\320\266\320\270\320\275\321\213", nullptr));
        labelDepth->setText(QCoreApplication::translate("Settings", "\320\223\320\273\321\203\320\261\320\270\320\275\320\260", nullptr));
        labelDistBtwDevices->setText(QCoreApplication::translate("Settings", "\320\240\320\260\321\201\321\201\321\202. \320\274\320\265\320\266. \321\206\320\265\320\275\321\202\321\200. \320\277\321\200\320\276\320\273\320\265\321\202\320\276\320\262", nullptr));
        labelCorr->setText(QCoreApplication::translate("Settings", "\320\224\320\276\320\277\320\276\320\273\320\275\320\270\321\202\320\265\320\273\321\214\320\275\320\276", nullptr));
        labelZeroLines->setText(QCoreApplication::translate("Settings", "\320\236\321\202\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265 \320\273\320\270\320\275\320\270\320\271 \320\275\321\203\320\273\321\217", nullptr));
        checkBoxZeroLines->setText(QString());
        labelCorSave->setText(QCoreApplication::translate("Settings", "\320\224\320\273\320\270\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\321\214 \321\201\320\262\320\270\320\277-\321\201\320\270\320\263\320\275\320\260\320\273\320\260", nullptr));
        labelSwipTime->setText(QCoreApplication::translate("Settings", "c\320\265\320\272", nullptr));
        checkBoxSaveMod->setText(QString());
        labelModem->setText(QCoreApplication::translate("Settings", "\320\240\320\265\321\202\321\200\320\260\320\275\321\201\320\273\321\217\321\202\320\276\321\200 - \320\274\320\276\320\264\320\265\320\274", nullptr));
        checkBoxModem->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
