/********************************************************************************
** Form generated from reading UI file 'checkboxincombowidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKBOXINCOMBOWIDGET_H
#define UI_CHECKBOXINCOMBOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CheckBoxInComboWidget
{
public:
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox;

    void setupUi(QWidget *CheckBoxInComboWidget)
    {
        if (CheckBoxInComboWidget->objectName().isEmpty())
            CheckBoxInComboWidget->setObjectName(QString::fromUtf8("CheckBoxInComboWidget"));
        CheckBoxInComboWidget->resize(167, 22);
        verticalLayout = new QVBoxLayout(CheckBoxInComboWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        comboBox = new QComboBox(CheckBoxInComboWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setPointSize(11);
        comboBox->setFont(font);
        comboBox->setAutoFillBackground(false);
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
        comboBox->setMaxCount(20);
        comboBox->setDuplicatesEnabled(false);

        verticalLayout->addWidget(comboBox);


        retranslateUi(CheckBoxInComboWidget);

        QMetaObject::connectSlotsByName(CheckBoxInComboWidget);
    } // setupUi

    void retranslateUi(QWidget *CheckBoxInComboWidget)
    {
        CheckBoxInComboWidget->setWindowTitle(QCoreApplication::translate("CheckBoxInComboWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CheckBoxInComboWidget: public Ui_CheckBoxInComboWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKBOXINCOMBOWIDGET_H
