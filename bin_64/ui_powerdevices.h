/********************************************************************************
** Form generated from reading UI file 'powerdevices.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POWERDEVICES_H
#define UI_POWERDEVICES_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PowerDevices
{
public:
    QRadioButton *radioButton_On_Off;
    QDoubleSpinBox *doubleSpinBox_Volt_Limit;
    QLineEdit *lineEdit_Command_Error_Message;
    QLabel *label_6;
    QLabel *label_13;
    QLabel *label_2;
    QPushButton *pushButton_Get_Curr_Meas;
    QPushButton *pushButton_Get_Volt_Limit;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_Volt_Meas;
    QLabel *label_11;
    QPushButton *pushButton_Get_Error;
    QLabel *label_14;
    QPushButton *pushButton_Get_On_Off;
    QLineEdit *lineEdit_Get_CC_CV;
    QPushButton *pushButton_Get_Volt_Meas;
    QPushButton *pushButton_Set_Volt_Limit;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBox_Curr_Limit;
    QLabel *label_8;
    QLabel *label_9;
    QPushButton *pushButton_Get_Curr_Limit;
    QPushButton *pushButton_Set_Curr_Limit;
    QLineEdit *lineEdit_Get_System_Error;
    QDoubleSpinBox *doubleSpinBox_Curr_Meas;
    QLineEdit *lineEdit_Get_Idntity_Query;
    QPushButton *pushButton_Get_Cv_Cc;
    QSpinBox *spinBox_Set_LRM;
    QPushButton *pushButton_Get_LRM;
    QLabel *label_5;
    QLabel *label_10;
    QLabel *label_12;
    QSpinBox *spinBox_Error;
    QPushButton *pushButton_Set_LRM;
    QLabel *label_15;
    QPushButton *pushButton_Get_Idntity_Query;
    QLabel *labelState;

    void setupUi(QWidget *PowerDevices)
    {
        if (PowerDevices->objectName().isEmpty())
            PowerDevices->setObjectName(QString::fromUtf8("PowerDevices"));
        PowerDevices->resize(573, 703);
        PowerDevices->setMinimumSize(QSize(573, 703));
        PowerDevices->setMaximumSize(QSize(650, 800));
        PowerDevices->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/TNG.ico"), QSize(), QIcon::Normal, QIcon::Off);
        PowerDevices->setWindowIcon(icon);
        PowerDevices->setStyleSheet(QString::fromUtf8("font-size: 11px;\n"
"font-family: Arial;\n"
"color: rgb(50,50,50);\n"
"background-color: #ffffff;\n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
""));
        radioButton_On_Off = new QRadioButton(PowerDevices);
        radioButton_On_Off->setObjectName(QString::fromUtf8("radioButton_On_Off"));
        radioButton_On_Off->setGeometry(QRect(28, 168, 241, 18));
        doubleSpinBox_Volt_Limit = new QDoubleSpinBox(PowerDevices);
        doubleSpinBox_Volt_Limit->setObjectName(QString::fromUtf8("doubleSpinBox_Volt_Limit"));
        doubleSpinBox_Volt_Limit->setGeometry(QRect(28, 83, 68, 21));
        doubleSpinBox_Volt_Limit->setStyleSheet(QString::fromUtf8("background-color: #ffffff;\n"
"color: #18799b; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;"));
        doubleSpinBox_Volt_Limit->setMaximum(360.000000000000000);
        lineEdit_Command_Error_Message = new QLineEdit(PowerDevices);
        lineEdit_Command_Error_Message->setObjectName(QString::fromUtf8("lineEdit_Command_Error_Message"));
        lineEdit_Command_Error_Message->setGeometry(QRect(30, 640, 382, 21));
        lineEdit_Command_Error_Message->setStyleSheet(QString::fromUtf8("background-color: #ffffff;\n"
"color: #18799b; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;"));
        label_6 = new QLabel(PowerDevices);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(28, 193, 126, 25));
        label_13 = new QLabel(PowerDevices);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(28, 547, 126, 26));
        label_2 = new QLabel(PowerDevices);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(28, 51, 184, 26));
        pushButton_Get_Curr_Meas = new QPushButton(PowerDevices);
        pushButton_Get_Curr_Meas->setObjectName(QString::fromUtf8("pushButton_Get_Curr_Meas"));
        pushButton_Get_Curr_Meas->setGeometry(QRect(140, 310, 101, 21));
        pushButton_Get_Curr_Meas->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: #18799b;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"QPushButton:pressed{\n"
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
        pushButton_Get_Volt_Limit = new QPushButton(PowerDevices);
        pushButton_Get_Volt_Limit->setObjectName(QString::fromUtf8("pushButton_Get_Volt_Limit"));
        pushButton_Get_Volt_Limit->setGeometry(QRect(280, 82, 101, 19));
        pushButton_Get_Volt_Limit->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: #18799b;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"QPushButton:pressed{\n"
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
        label_3 = new QLabel(PowerDevices);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(28, 110, 68, 25));
        doubleSpinBox_Volt_Meas = new QDoubleSpinBox(PowerDevices);
        doubleSpinBox_Volt_Meas->setObjectName(QString::fromUtf8("doubleSpinBox_Volt_Meas"));
        doubleSpinBox_Volt_Meas->setGeometry(QRect(28, 260, 68, 21));
        doubleSpinBox_Volt_Meas->setStyleSheet(QString::fromUtf8("background-color: #ffffff;\n"
"color: #18799b; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;"));
        doubleSpinBox_Volt_Meas->setMaximum(299.990000000000009);
        label_11 = new QLabel(PowerDevices);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(28, 458, 456, 25));
        pushButton_Get_Error = new QPushButton(PowerDevices);
        pushButton_Get_Error->setObjectName(QString::fromUtf8("pushButton_Get_Error"));
        pushButton_Get_Error->setGeometry(QRect(440, 580, 101, 20));
        pushButton_Get_Error->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: #18799b;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"QPushButton:pressed{\n"
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
        label_14 = new QLabel(PowerDevices);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(190, 550, 209, 26));
        pushButton_Get_On_Off = new QPushButton(PowerDevices);
        pushButton_Get_On_Off->setObjectName(QString::fromUtf8("pushButton_Get_On_Off"));
        pushButton_Get_On_Off->setGeometry(QRect(280, 166, 101, 19));
        pushButton_Get_On_Off->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: #18799b;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"QPushButton:pressed{\n"
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
        lineEdit_Get_CC_CV = new QLineEdit(PowerDevices);
        lineEdit_Get_CC_CV->setObjectName(QString::fromUtf8("lineEdit_Get_CC_CV"));
        lineEdit_Get_CC_CV->setGeometry(QRect(28, 372, 126, 21));
        lineEdit_Get_CC_CV->setStyleSheet(QString::fromUtf8("background-color: #ffffff;\n"
"color: #18799b; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;"));
        pushButton_Get_Volt_Meas = new QPushButton(PowerDevices);
        pushButton_Get_Volt_Meas->setObjectName(QString::fromUtf8("pushButton_Get_Volt_Meas"));
        pushButton_Get_Volt_Meas->setGeometry(QRect(140, 260, 101, 19));
        pushButton_Get_Volt_Meas->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: #18799b;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"QPushButton:pressed{\n"
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
        pushButton_Set_Volt_Limit = new QPushButton(PowerDevices);
        pushButton_Set_Volt_Limit->setObjectName(QString::fromUtf8("pushButton_Set_Volt_Limit"));
        pushButton_Set_Volt_Limit->setGeometry(QRect(140, 84, 101, 19));
        pushButton_Set_Volt_Limit->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: #ffffff;\n"
"color: #18799b; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"QPushButton:pressed{\n"
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
        label_7 = new QLabel(PowerDevices);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(28, 283, 68, 25));
        doubleSpinBox_Curr_Limit = new QDoubleSpinBox(PowerDevices);
        doubleSpinBox_Curr_Limit->setObjectName(QString::fromUtf8("doubleSpinBox_Curr_Limit"));
        doubleSpinBox_Curr_Limit->setGeometry(QRect(28, 141, 68, 21));
        doubleSpinBox_Curr_Limit->setStyleSheet(QString::fromUtf8("background-color: #ffffff;\n"
"color: #18799b; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;"));
        doubleSpinBox_Curr_Limit->setMaximum(7.000000000000000);
        label_8 = new QLabel(PowerDevices);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(28, 224, 184, 26));
        label_9 = new QLabel(PowerDevices);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(28, 341, 349, 25));
        pushButton_Get_Curr_Limit = new QPushButton(PowerDevices);
        pushButton_Get_Curr_Limit->setObjectName(QString::fromUtf8("pushButton_Get_Curr_Limit"));
        pushButton_Get_Curr_Limit->setGeometry(QRect(280, 140, 101, 19));
        pushButton_Get_Curr_Limit->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: #18799b;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"QPushButton:pressed{\n"
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
        pushButton_Set_Curr_Limit = new QPushButton(PowerDevices);
        pushButton_Set_Curr_Limit->setObjectName(QString::fromUtf8("pushButton_Set_Curr_Limit"));
        pushButton_Set_Curr_Limit->setGeometry(QRect(140, 140, 101, 19));
        pushButton_Set_Curr_Limit->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: #ffffff;\n"
"color: #18799b; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"QPushButton:pressed{\n"
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
        lineEdit_Get_System_Error = new QLineEdit(PowerDevices);
        lineEdit_Get_System_Error->setObjectName(QString::fromUtf8("lineEdit_Get_System_Error"));
        lineEdit_Get_System_Error->setGeometry(QRect(102, 579, 310, 21));
        lineEdit_Get_System_Error->setStyleSheet(QString::fromUtf8("background-color: #ffffff;\n"
"color: #18799b; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;"));
        doubleSpinBox_Curr_Meas = new QDoubleSpinBox(PowerDevices);
        doubleSpinBox_Curr_Meas->setObjectName(QString::fromUtf8("doubleSpinBox_Curr_Meas"));
        doubleSpinBox_Curr_Meas->setGeometry(QRect(28, 310, 68, 21));
        doubleSpinBox_Curr_Meas->setStyleSheet(QString::fromUtf8("background-color: #ffffff;\n"
"color: #18799b; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;"));
        doubleSpinBox_Curr_Meas->setMaximum(4.990000000000000);
        lineEdit_Get_Idntity_Query = new QLineEdit(PowerDevices);
        lineEdit_Get_Idntity_Query->setObjectName(QString::fromUtf8("lineEdit_Get_Idntity_Query"));
        lineEdit_Get_Idntity_Query->setGeometry(QRect(28, 489, 382, 21));
        lineEdit_Get_Idntity_Query->setStyleSheet(QString::fromUtf8("background-color: #ffffff;\n"
"color: #18799b; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;"));
        pushButton_Get_Cv_Cc = new QPushButton(PowerDevices);
        pushButton_Get_Cv_Cc->setObjectName(QString::fromUtf8("pushButton_Get_Cv_Cc"));
        pushButton_Get_Cv_Cc->setGeometry(QRect(190, 370, 101, 19));
        pushButton_Get_Cv_Cc->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: #18799b;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"QPushButton:pressed{\n"
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
        spinBox_Set_LRM = new QSpinBox(PowerDevices);
        spinBox_Set_LRM->setObjectName(QString::fromUtf8("spinBox_Set_LRM"));
        spinBox_Set_LRM->setGeometry(QRect(28, 430, 68, 21));
        spinBox_Set_LRM->setStyleSheet(QString::fromUtf8("background-color: #ffffff;\n"
"color: #18799b; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;"));
        spinBox_Set_LRM->setMaximum(3);
        pushButton_Get_LRM = new QPushButton(PowerDevices);
        pushButton_Get_LRM->setObjectName(QString::fromUtf8("pushButton_Get_LRM"));
        pushButton_Get_LRM->setGeometry(QRect(280, 430, 101, 19));
        pushButton_Get_LRM->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: #18799b;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"QPushButton:pressed{\n"
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
        label_5 = new QLabel(PowerDevices);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(28, 20, 241, 25));
        label_10 = new QLabel(PowerDevices);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(28, 399, 456, 26));
        label_12 = new QLabel(PowerDevices);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(28, 516, 241, 25));
        spinBox_Error = new QSpinBox(PowerDevices);
        spinBox_Error->setObjectName(QString::fromUtf8("spinBox_Error"));
        spinBox_Error->setGeometry(QRect(28, 579, 68, 21));
        spinBox_Error->setStyleSheet(QString::fromUtf8("background-color: #ffffff;\n"
"color: #18799b; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;"));
        spinBox_Error->setMinimum(-400);
        spinBox_Error->setMaximum(400);
        pushButton_Set_LRM = new QPushButton(PowerDevices);
        pushButton_Set_LRM->setObjectName(QString::fromUtf8("pushButton_Set_LRM"));
        pushButton_Set_LRM->setGeometry(QRect(140, 430, 101, 19));
        pushButton_Set_LRM->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: #18799b;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"QPushButton:pressed{\n"
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
        label_15 = new QLabel(PowerDevices);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(150, 600, 209, 25));
        pushButton_Get_Idntity_Query = new QPushButton(PowerDevices);
        pushButton_Get_Idntity_Query->setObjectName(QString::fromUtf8("pushButton_Get_Idntity_Query"));
        pushButton_Get_Idntity_Query->setGeometry(QRect(440, 490, 101, 20));
        pushButton_Get_Idntity_Query->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"background-color: #18799b;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 11pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"QPushButton:pressed{\n"
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
        labelState = new QLabel(PowerDevices);
        labelState->setObjectName(QString::fromUtf8("labelState"));
        labelState->setGeometry(QRect(30, 680, 381, 16));

        retranslateUi(PowerDevices);

        QMetaObject::connectSlotsByName(PowerDevices);
    } // setupUi

    void retranslateUi(QWidget *PowerDevices)
    {
        PowerDevices->setWindowTitle(QCoreApplication::translate("PowerDevices", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\277\320\270\321\202\320\260\320\275\320\270\320\265\320\274 \321\201\320\262\321\217\320\267\320\272\320\270 \320\277\321\200\320\270\320\261\320\276\321\200\320\276\320\262", nullptr));
        radioButton_On_Off->setText(QCoreApplication::translate("PowerDevices", "OUT on/off", nullptr));
        label_6->setText(QCoreApplication::translate("PowerDevices", "\320\230\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\265", nullptr));
        label_13->setText(QCoreApplication::translate("PowerDevices", "ERROR", nullptr));
        label_2->setText(QCoreApplication::translate("PowerDevices", "\320\235\320\260\320\277\321\200\321\217\320\266\320\265\320\275\320\270\320\265", nullptr));
        pushButton_Get_Curr_Meas->setText(QCoreApplication::translate("PowerDevices", "\320\247\320\270\321\202\320\260\321\202\321\214", nullptr));
        pushButton_Get_Volt_Limit->setText(QCoreApplication::translate("PowerDevices", "\320\247\320\270\321\202\320\260\321\202\321\214", nullptr));
        label_3->setText(QCoreApplication::translate("PowerDevices", "\320\242\320\276\320\272", nullptr));
        label_11->setText(QCoreApplication::translate("PowerDevices", "\320\230\320\264\320\265\320\275\321\202\320\270\321\204\320\270\320\272\320\260\321\206\320\270\321\217 \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\260 TDK-LAMBDA", nullptr));
        pushButton_Get_Error->setText(QCoreApplication::translate("PowerDevices", "\320\247\320\270\321\202\320\260\321\202\321\214", nullptr));
        label_14->setText(QCoreApplication::translate("PowerDevices", "ERROR MESSAGE", nullptr));
        pushButton_Get_On_Off->setText(QCoreApplication::translate("PowerDevices", "\320\247\320\270\321\202\320\260\321\202\321\214", nullptr));
        pushButton_Get_Volt_Meas->setText(QCoreApplication::translate("PowerDevices", "\320\247\320\270\321\202\320\260\321\202\321\214", nullptr));
        pushButton_Set_Volt_Limit->setText(QCoreApplication::translate("PowerDevices", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        label_7->setText(QCoreApplication::translate("PowerDevices", "\320\242\320\276\320\272", nullptr));
        label_8->setText(QCoreApplication::translate("PowerDevices", "\320\235\320\260\320\277\321\200\321\217\320\266\320\265\320\275\320\270\320\265", nullptr));
        label_9->setText(QCoreApplication::translate("PowerDevices", "\320\230\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\265 CV \320\270\320\273\320\270 CC", nullptr));
        pushButton_Get_Curr_Limit->setText(QCoreApplication::translate("PowerDevices", "\320\247\320\270\321\202\320\260\321\202\321\214", nullptr));
        pushButton_Set_Curr_Limit->setText(QCoreApplication::translate("PowerDevices", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        pushButton_Get_Cv_Cc->setText(QCoreApplication::translate("PowerDevices", "\320\247\320\270\321\202\320\260\321\202\321\214", nullptr));
        pushButton_Get_LRM->setText(QCoreApplication::translate("PowerDevices", "\320\247\320\270\321\202\320\260\321\202\321\214", nullptr));
        label_5->setText(QCoreApplication::translate("PowerDevices", "\320\236\320\263\321\200\320\260\320\275\320\270\321\207\320\265\320\275\320\270\320\265", nullptr));
        label_10->setText(QCoreApplication::translate("PowerDevices", "System local or Remote Modes", nullptr));
        label_12->setText(QCoreApplication::translate("PowerDevices", "\320\247\321\202\320\265\320\275\320\270\320\265 \320\276\321\210\320\270\320\261\320\276\320\272", nullptr));
        pushButton_Set_LRM->setText(QCoreApplication::translate("PowerDevices", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        label_15->setText(QCoreApplication::translate("PowerDevices", "COMMAND ERROR MESSAGE", nullptr));
        pushButton_Get_Idntity_Query->setText(QCoreApplication::translate("PowerDevices", "\320\247\320\270\321\202\320\260\321\202\321\214", nullptr));
        labelState->setText(QCoreApplication::translate("PowerDevices", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PowerDevices: public Ui_PowerDevices {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POWERDEVICES_H
