/********************************************************************************
** Form generated from reading UI file 'extrasettings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXTRASETTINGS_H
#define UI_EXTRASETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExtraSettings
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label_9;
    QLabel *label_7;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QLabel *label;
    QPushButton *saveAndCloseButton;
    QLabel *label_4;
    QLabel *label_8;
    QSpacerItem *verticalSpacer_4;
    QPushButton *readSettingsFileButton;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QComboBox *dwnHoleGainComboBox;

    void setupUi(QWidget *ExtraSettings)
    {
        if (ExtraSettings->objectName().isEmpty())
            ExtraSettings->setObjectName(QString::fromUtf8("ExtraSettings"));
        ExtraSettings->setWindowModality(Qt::WindowModal);
        ExtraSettings->resize(500, 500);
        ExtraSettings->setMinimumSize(QSize(0, 0));
        ExtraSettings->setMaximumSize(QSize(500, 500));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/SettingsLogo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        ExtraSettings->setWindowIcon(icon);
        ExtraSettings->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        verticalLayout = new QVBoxLayout(ExtraSettings);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));

        gridLayout->addLayout(horizontalLayout_3, 14, 0, 1, 2);

        label_6 = new QLabel(ExtraSettings);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMaximumSize(QSize(16777215, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(11);
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_6, 4, 0, 1, 3);

        label_5 = new QLabel(ExtraSettings);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_5, 13, 2, 1, 1);

        label_9 = new QLabel(ExtraSettings);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font);
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_9, 12, 0, 1, 3);

        label_7 = new QLabel(ExtraSettings);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMaximumSize(QSize(16777215, 20));
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_7, 2, 0, 1, 3);

        verticalSpacer_6 = new QSpacerItem(20, 24, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_6, 6, 0, 1, 3);

        label_2 = new QLabel(ExtraSettings);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 7, 0, 1, 2);

        verticalSpacer_7 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_7, 13, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 15, 0, 1, 3);

        verticalSpacer_2 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 1, 0, 1, 3);

        label = new QLabel(ExtraSettings);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(16777215, 20));
        label->setFont(font1);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 3);

        saveAndCloseButton = new QPushButton(ExtraSettings);
        saveAndCloseButton->setObjectName(QString::fromUtf8("saveAndCloseButton"));
        saveAndCloseButton->setMinimumSize(QSize(80, 49));
        saveAndCloseButton->setStyleSheet(QString::fromUtf8("#saveAndCloseButton{\n"
"background-color: #18799b;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 12pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"#saveAndCloseButton:pressed{\n"
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

        gridLayout->addWidget(saveAndCloseButton, 16, 2, 1, 1);

        label_4 = new QLabel(ExtraSettings);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 10, 2, 1, 1);

        label_8 = new QLabel(ExtraSettings);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_8, 9, 0, 1, 3);

        verticalSpacer_4 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_4, 10, 0, 1, 2);

        readSettingsFileButton = new QPushButton(ExtraSettings);
        readSettingsFileButton->setObjectName(QString::fromUtf8("readSettingsFileButton"));
        readSettingsFileButton->setMinimumSize(QSize(80, 30));
        readSettingsFileButton->setStyleSheet(QString::fromUtf8("#readSettingsFileButton{\n"
"background-color: #18799b;\n"
"color: #ffffff; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 12pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"#readSettingsFileButton:pressed{\n"
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

        gridLayout->addWidget(readSettingsFileButton, 16, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_3, 8, 0, 1, 3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

        gridLayout->addLayout(horizontalLayout_2, 11, 0, 1, 2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));

        gridLayout->addLayout(verticalLayout_3, 5, 0, 1, 3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 3);

        comboBox = new QComboBox(ExtraSettings);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(70, 23));
        comboBox->setMaximumSize(QSize(70, 23));
        comboBox->setFont(font);
        comboBox->setStyleSheet(QString::fromUtf8("QComboBox {\n"
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

        gridLayout->addWidget(comboBox, 14, 2, 1, 1);

        dwnHoleGainComboBox = new QComboBox(ExtraSettings);
        dwnHoleGainComboBox->addItem(QString());
        dwnHoleGainComboBox->addItem(QString());
        dwnHoleGainComboBox->addItem(QString());
        dwnHoleGainComboBox->addItem(QString());
        dwnHoleGainComboBox->addItem(QString());
        dwnHoleGainComboBox->addItem(QString());
        dwnHoleGainComboBox->addItem(QString());
        dwnHoleGainComboBox->setObjectName(QString::fromUtf8("dwnHoleGainComboBox"));
        dwnHoleGainComboBox->setMinimumSize(QSize(70, 23));
        dwnHoleGainComboBox->setMaximumSize(QSize(70, 23));
        dwnHoleGainComboBox->setFont(font);
        dwnHoleGainComboBox->setStyleSheet(QString::fromUtf8("QComboBox {\n"
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

        gridLayout->addWidget(dwnHoleGainComboBox, 11, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(ExtraSettings);

        QMetaObject::connectSlotsByName(ExtraSettings);
    } // setupUi

    void retranslateUi(QWidget *ExtraSettings)
    {
        ExtraSettings->setWindowTitle(QCoreApplication::translate("ExtraSettings", "\320\224\320\276\320\277. \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
        label_6->setText(QCoreApplication::translate("ExtraSettings", "\320\235\320\260\320\267\320\265\320\274\320\275\321\213\320\265 \320\274\320\276\320\264\321\203\320\273\320\270", nullptr));
        label_5->setText(QCoreApplication::translate("ExtraSettings", "\320\232\320\243", nullptr));
        label_9->setText(QCoreApplication::translate("ExtraSettings", "\320\235\320\260\320\267\320\265\320\274\320\275\321\213\320\265 \320\274\320\276\320\264\321\203\320\273\320\270", nullptr));
        label_7->setText(QCoreApplication::translate("ExtraSettings", "\320\241\320\272\320\262\320\260\320\266\320\270\320\275\320\275\321\213\320\265 \320\274\320\276\320\264\321\203\320\273\320\270", nullptr));
        label_2->setText(QCoreApplication::translate("ExtraSettings", "\320\243\321\201\320\270\320\273\320\265\320\275\320\270\320\265 \320\272\320\260\320\275\320\260\320\273\320\276\320\262", nullptr));
        label->setText(QCoreApplication::translate("ExtraSettings", "\320\230\320\275\320\262\320\265\321\200\321\201\320\270\321\217 \320\272\320\260\320\275\320\260\320\273\320\276\320\262", nullptr));
        saveAndCloseButton->setText(QCoreApplication::translate("ExtraSettings", "\320\236\320\232", nullptr));
        label_4->setText(QCoreApplication::translate("ExtraSettings", "\320\232\320\243", nullptr));
        label_8->setText(QCoreApplication::translate("ExtraSettings", "\320\241\320\272\320\262\320\260\320\266\320\270\320\275\320\275\321\213\320\265 \320\274\320\276\320\264\321\203\320\273\320\270", nullptr));
        readSettingsFileButton->setText(QCoreApplication::translate("ExtraSettings", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\277\321\200\320\265\320\264\321\213\320\264\321\203\321\211\320\270\320\265\n"
"\320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("ExtraSettings", "1", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("ExtraSettings", "-1000", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("ExtraSettings", "-100", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("ExtraSettings", "-10", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("ExtraSettings", "1", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("ExtraSettings", "2", nullptr));
        comboBox->setItemText(6, QCoreApplication::translate("ExtraSettings", "10", nullptr));
        comboBox->setItemText(7, QCoreApplication::translate("ExtraSettings", "100", nullptr));
        comboBox->setItemText(8, QCoreApplication::translate("ExtraSettings", "1000", nullptr));

        dwnHoleGainComboBox->setItemText(0, QCoreApplication::translate("ExtraSettings", "1", nullptr));
        dwnHoleGainComboBox->setItemText(1, QCoreApplication::translate("ExtraSettings", "2", nullptr));
        dwnHoleGainComboBox->setItemText(2, QCoreApplication::translate("ExtraSettings", "4", nullptr));
        dwnHoleGainComboBox->setItemText(3, QCoreApplication::translate("ExtraSettings", "8", nullptr));
        dwnHoleGainComboBox->setItemText(4, QCoreApplication::translate("ExtraSettings", "16", nullptr));
        dwnHoleGainComboBox->setItemText(5, QCoreApplication::translate("ExtraSettings", "32", nullptr));
        dwnHoleGainComboBox->setItemText(6, QCoreApplication::translate("ExtraSettings", "64", nullptr));

    } // retranslateUi

};

namespace Ui {
    class ExtraSettings: public Ui_ExtraSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTRASETTINGS_H
