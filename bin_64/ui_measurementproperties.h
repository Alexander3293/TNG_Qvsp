/********************************************************************************
** Form generated from reading UI file 'measurementproperties.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEASUREMENTPROPERTIES_H
#define UI_MEASUREMENTPROPERTIES_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MeasurementProperties
{
public:
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout;
    QLabel *labelMainName;
    QGridLayout *gridLayout;
    QLabel *labelNameArea;
    QLineEdit *lineEditDepth;
    QLineEdit *lineEditOperator;
    QLineEdit *lineEditNumHole;
    QLabel *labelGainUpHole;
    QPushButton *pushButtonSave;
    QLineEdit *lineEditNameArea;
    QFrame *line_13;
    QFrame *line_11;
    QLabel *labelSource;
    QFrame *line_12;
    QFrame *line_4;
    QLabel *labelSourceType;
    QLabel *labelTimeRecord;
    QLabel *labelDepth;
    QFrame *line_7;
    QLineEdit *lineEditTimeRecord;
    QLabel *labelServiceInfo;
    QLabel *labelTimeSwip;
    QLineEdit *lineEditTimeSwip;
    QFrame *line_10;
    QLineEdit *lineEditGainUpHole;
    QLineEdit *lineEditDate;
    QFrame *line_9;
    QLineEdit *lineEditNumDnHole;
    QFrame *line_8;
    QLineEdit *lineEditTime;
    QLineEdit *lineEditSourceType;
    QLineEdit *lineEditNumUpHole;
    QLineEdit *lineEditSourceStat;
    QLineEdit *lineEditGainDnHole;
    QFrame *line_6;
    QLabel *labelNameProj;
    QFrame *line;
    QLineEdit *lineEditIdMeas;
    QLabel *labelSourceStat;
    QLabel *labelIdMeas;
    QLabel *labelNumUpHole;
    QFrame *line_5;
    QLabel *labelDate;
    QFrame *line_3;
    QLineEdit *lineEditNameProj;
    QLabel *labelGainDnHole;
    QFrame *line_2;
    QFrame *line_14;
    QLabel *labelTime;
    QLabel *labelNumDnHole;
    QLabel *labelOperator;
    QLabel *labelNumHole;
    QPushButton *pushButtonChange;
    QSpacerItem *verticalSpacer_3;
    QLineEdit *lineEditDistBtwDevices;
    QLabel *labelDistBtwDevices;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *MeasurementProperties)
    {
        if (MeasurementProperties->objectName().isEmpty())
            MeasurementProperties->setObjectName(QString::fromUtf8("MeasurementProperties"));
        MeasurementProperties->resize(422, 700);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MeasurementProperties->sizePolicy().hasHeightForWidth());
        MeasurementProperties->setSizePolicy(sizePolicy);
        MeasurementProperties->setMaximumSize(QSize(16777215, 700));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/TNG.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MeasurementProperties->setWindowIcon(icon);
        verticalLayout_2 = new QVBoxLayout(MeasurementProperties);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelMainName = new QLabel(MeasurementProperties);
        labelMainName->setObjectName(QString::fromUtf8("labelMainName"));
        labelMainName->setMinimumSize(QSize(0, 20));
        labelMainName->setMaximumSize(QSize(16777215, 70));

        verticalLayout->addWidget(labelMainName);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelNameArea = new QLabel(MeasurementProperties);
        labelNameArea->setObjectName(QString::fromUtf8("labelNameArea"));

        gridLayout->addWidget(labelNameArea, 25, 0, 1, 1);

        lineEditDepth = new QLineEdit(MeasurementProperties);
        lineEditDepth->setObjectName(QString::fromUtf8("lineEditDepth"));
        lineEditDepth->setReadOnly(true);

        gridLayout->addWidget(lineEditDepth, 22, 1, 1, 1);

        lineEditOperator = new QLineEdit(MeasurementProperties);
        lineEditOperator->setObjectName(QString::fromUtf8("lineEditOperator"));
        lineEditOperator->setReadOnly(true);

        gridLayout->addWidget(lineEditOperator, 23, 1, 1, 1);

        lineEditNumHole = new QLineEdit(MeasurementProperties);
        lineEditNumHole->setObjectName(QString::fromUtf8("lineEditNumHole"));
        lineEditNumHole->setReadOnly(true);

        gridLayout->addWidget(lineEditNumHole, 24, 1, 1, 1);

        labelGainUpHole = new QLabel(MeasurementProperties);
        labelGainUpHole->setObjectName(QString::fromUtf8("labelGainUpHole"));

        gridLayout->addWidget(labelGainUpHole, 12, 0, 1, 1);

        pushButtonSave = new QPushButton(MeasurementProperties);
        pushButtonSave->setObjectName(QString::fromUtf8("pushButtonSave"));
        pushButtonSave->setMinimumSize(QSize(0, 30));
        pushButtonSave->setMaximumSize(QSize(16777215, 30));
        pushButtonSave->setStyleSheet(QString::fromUtf8("#pushButtonSave{\n"
" background-color: #ffffff;\n"
"  color: #18799b;\n"
"  border-width: 1px; \n"
"   border-style: solid; \n"
"                                        border-color: rgb(181,181,181); \n"
"                                          font-family: Arial;\n"
"                                          font-size: 12pt; font-weight: 450; border-radius: 1;\n"
"                                          }\n"
"                                          #pushButtonSave:pressed{\n"
"                                          background-color: #18799b;\n"
"                                         color: #ffffff; border-width: 1px; \n"
"                                         border-style: solid;  \n"
"                                          border-color: rgb(181,181,181);  \n"
"                                          font-family: Arial;\n"
"                                          font-size: 12pt; font-weight: 450; border-radius: 1; \n"
"                                          }"));

        gridLayout->addWidget(pushButtonSave, 28, 0, 1, 1);

        lineEditNameArea = new QLineEdit(MeasurementProperties);
        lineEditNameArea->setObjectName(QString::fromUtf8("lineEditNameArea"));
        lineEditNameArea->setReadOnly(true);

        gridLayout->addWidget(lineEditNameArea, 25, 1, 1, 1);

        line_13 = new QFrame(MeasurementProperties);
        line_13->setObjectName(QString::fromUtf8("line_13"));
        line_13->setFrameShape(QFrame::HLine);
        line_13->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_13, 20, 0, 1, 1);

        line_11 = new QFrame(MeasurementProperties);
        line_11->setObjectName(QString::fromUtf8("line_11"));
        line_11->setFrameShape(QFrame::HLine);
        line_11->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_11, 17, 0, 1, 1);

        labelSource = new QLabel(MeasurementProperties);
        labelSource->setObjectName(QString::fromUtf8("labelSource"));
        labelSource->setMinimumSize(QSize(0, 20));
        labelSource->setMaximumSize(QSize(16777215, 30));

        gridLayout->addWidget(labelSource, 14, 0, 1, 1);

        line_12 = new QFrame(MeasurementProperties);
        line_12->setObjectName(QString::fromUtf8("line_12"));
        line_12->setFrameShape(QFrame::HLine);
        line_12->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_12, 17, 1, 1, 1);

        line_4 = new QFrame(MeasurementProperties);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_4, 13, 0, 1, 1);

        labelSourceType = new QLabel(MeasurementProperties);
        labelSourceType->setObjectName(QString::fromUtf8("labelSourceType"));

        gridLayout->addWidget(labelSourceType, 16, 0, 1, 1);

        labelTimeRecord = new QLabel(MeasurementProperties);
        labelTimeRecord->setObjectName(QString::fromUtf8("labelTimeRecord"));

        gridLayout->addWidget(labelTimeRecord, 18, 0, 1, 1);

        labelDepth = new QLabel(MeasurementProperties);
        labelDepth->setObjectName(QString::fromUtf8("labelDepth"));

        gridLayout->addWidget(labelDepth, 22, 0, 1, 1);

        line_7 = new QFrame(MeasurementProperties);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_7, 0, 1, 1, 1);

        lineEditTimeRecord = new QLineEdit(MeasurementProperties);
        lineEditTimeRecord->setObjectName(QString::fromUtf8("lineEditTimeRecord"));
        lineEditTimeRecord->setReadOnly(true);

        gridLayout->addWidget(lineEditTimeRecord, 18, 1, 1, 1);

        labelServiceInfo = new QLabel(MeasurementProperties);
        labelServiceInfo->setObjectName(QString::fromUtf8("labelServiceInfo"));

        gridLayout->addWidget(labelServiceInfo, 21, 0, 1, 1);

        labelTimeSwip = new QLabel(MeasurementProperties);
        labelTimeSwip->setObjectName(QString::fromUtf8("labelTimeSwip"));

        gridLayout->addWidget(labelTimeSwip, 19, 0, 1, 1);

        lineEditTimeSwip = new QLineEdit(MeasurementProperties);
        lineEditTimeSwip->setObjectName(QString::fromUtf8("lineEditTimeSwip"));
        lineEditTimeSwip->setReadOnly(true);

        gridLayout->addWidget(lineEditTimeSwip, 19, 1, 1, 1);

        line_10 = new QFrame(MeasurementProperties);
        line_10->setObjectName(QString::fromUtf8("line_10"));
        line_10->setFrameShape(QFrame::HLine);
        line_10->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_10, 13, 1, 1, 1);

        lineEditGainUpHole = new QLineEdit(MeasurementProperties);
        lineEditGainUpHole->setObjectName(QString::fromUtf8("lineEditGainUpHole"));
        lineEditGainUpHole->setReadOnly(true);

        gridLayout->addWidget(lineEditGainUpHole, 12, 1, 1, 1);

        lineEditDate = new QLineEdit(MeasurementProperties);
        lineEditDate->setObjectName(QString::fromUtf8("lineEditDate"));
        lineEditDate->setReadOnly(true);

        gridLayout->addWidget(lineEditDate, 4, 1, 1, 1);

        line_9 = new QFrame(MeasurementProperties);
        line_9->setObjectName(QString::fromUtf8("line_9"));
        line_9->setFrameShape(QFrame::HLine);
        line_9->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_9, 10, 1, 1, 1);

        lineEditNumDnHole = new QLineEdit(MeasurementProperties);
        lineEditNumDnHole->setObjectName(QString::fromUtf8("lineEditNumDnHole"));
        lineEditNumDnHole->setReadOnly(true);

        gridLayout->addWidget(lineEditNumDnHole, 7, 1, 1, 1);

        line_8 = new QFrame(MeasurementProperties);
        line_8->setObjectName(QString::fromUtf8("line_8"));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_8, 6, 1, 1, 1);

        lineEditTime = new QLineEdit(MeasurementProperties);
        lineEditTime->setObjectName(QString::fromUtf8("lineEditTime"));
        lineEditTime->setReadOnly(true);

        gridLayout->addWidget(lineEditTime, 5, 1, 1, 1);

        lineEditSourceType = new QLineEdit(MeasurementProperties);
        lineEditSourceType->setObjectName(QString::fromUtf8("lineEditSourceType"));
        lineEditSourceType->setReadOnly(true);

        gridLayout->addWidget(lineEditSourceType, 16, 1, 1, 1);

        lineEditNumUpHole = new QLineEdit(MeasurementProperties);
        lineEditNumUpHole->setObjectName(QString::fromUtf8("lineEditNumUpHole"));
        lineEditNumUpHole->setReadOnly(true);

        gridLayout->addWidget(lineEditNumUpHole, 9, 1, 1, 1);

        lineEditSourceStat = new QLineEdit(MeasurementProperties);
        lineEditSourceStat->setObjectName(QString::fromUtf8("lineEditSourceStat"));
        lineEditSourceStat->setReadOnly(true);

        gridLayout->addWidget(lineEditSourceStat, 15, 1, 1, 1);

        lineEditGainDnHole = new QLineEdit(MeasurementProperties);
        lineEditGainDnHole->setObjectName(QString::fromUtf8("lineEditGainDnHole"));
        lineEditGainDnHole->setReadOnly(true);

        gridLayout->addWidget(lineEditGainDnHole, 11, 1, 1, 1);

        line_6 = new QFrame(MeasurementProperties);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_6, 3, 1, 1, 1);

        labelNameProj = new QLabel(MeasurementProperties);
        labelNameProj->setObjectName(QString::fromUtf8("labelNameProj"));

        gridLayout->addWidget(labelNameProj, 1, 0, 1, 1);

        line = new QFrame(MeasurementProperties);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 0, 0, 1, 1);

        lineEditIdMeas = new QLineEdit(MeasurementProperties);
        lineEditIdMeas->setObjectName(QString::fromUtf8("lineEditIdMeas"));
        lineEditIdMeas->setReadOnly(true);

        gridLayout->addWidget(lineEditIdMeas, 2, 1, 1, 1);

        labelSourceStat = new QLabel(MeasurementProperties);
        labelSourceStat->setObjectName(QString::fromUtf8("labelSourceStat"));

        gridLayout->addWidget(labelSourceStat, 15, 0, 1, 1);

        labelIdMeas = new QLabel(MeasurementProperties);
        labelIdMeas->setObjectName(QString::fromUtf8("labelIdMeas"));

        gridLayout->addWidget(labelIdMeas, 2, 0, 1, 1);

        labelNumUpHole = new QLabel(MeasurementProperties);
        labelNumUpHole->setObjectName(QString::fromUtf8("labelNumUpHole"));

        gridLayout->addWidget(labelNumUpHole, 9, 0, 1, 1);

        line_5 = new QFrame(MeasurementProperties);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_5, 10, 0, 1, 1);

        labelDate = new QLabel(MeasurementProperties);
        labelDate->setObjectName(QString::fromUtf8("labelDate"));

        gridLayout->addWidget(labelDate, 4, 0, 1, 1);

        line_3 = new QFrame(MeasurementProperties);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_3, 6, 0, 1, 1);

        lineEditNameProj = new QLineEdit(MeasurementProperties);
        lineEditNameProj->setObjectName(QString::fromUtf8("lineEditNameProj"));
        lineEditNameProj->setReadOnly(true);

        gridLayout->addWidget(lineEditNameProj, 1, 1, 1, 1);

        labelGainDnHole = new QLabel(MeasurementProperties);
        labelGainDnHole->setObjectName(QString::fromUtf8("labelGainDnHole"));

        gridLayout->addWidget(labelGainDnHole, 11, 0, 1, 1);

        line_2 = new QFrame(MeasurementProperties);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setMinimumSize(QSize(0, 1));
        line_2->setStyleSheet(QString::fromUtf8("background-color: rgb(24, 121, 155)"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 3, 0, 1, 1);

        line_14 = new QFrame(MeasurementProperties);
        line_14->setObjectName(QString::fromUtf8("line_14"));
        line_14->setFrameShape(QFrame::HLine);
        line_14->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_14, 20, 1, 1, 1);

        labelTime = new QLabel(MeasurementProperties);
        labelTime->setObjectName(QString::fromUtf8("labelTime"));

        gridLayout->addWidget(labelTime, 5, 0, 1, 1);

        labelNumDnHole = new QLabel(MeasurementProperties);
        labelNumDnHole->setObjectName(QString::fromUtf8("labelNumDnHole"));

        gridLayout->addWidget(labelNumDnHole, 7, 0, 1, 1);

        labelOperator = new QLabel(MeasurementProperties);
        labelOperator->setObjectName(QString::fromUtf8("labelOperator"));

        gridLayout->addWidget(labelOperator, 23, 0, 1, 1);

        labelNumHole = new QLabel(MeasurementProperties);
        labelNumHole->setObjectName(QString::fromUtf8("labelNumHole"));

        gridLayout->addWidget(labelNumHole, 24, 0, 1, 1);

        pushButtonChange = new QPushButton(MeasurementProperties);
        pushButtonChange->setObjectName(QString::fromUtf8("pushButtonChange"));
        pushButtonChange->setMinimumSize(QSize(0, 30));
        pushButtonChange->setMaximumSize(QSize(16777215, 30));
        pushButtonChange->setStyleSheet(QString::fromUtf8("#pushButtonChange{\n"
"background-color: #18799b;\n"
"color: #ffffff;  border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 12pt; font-weight: 450; border-radius: 1;\n"
"}\n"
"#pushButtonChange:pressed{\n"
"background-color: #ffffff;\n"
"color: #18799b; border-width: 1px; \n"
"border-style: solid; \n"
"border-color: rgb(181,181,181); \n"
"font-family: Arial;\n"
"font-size: 12pt; font-weight: 450; border-radius: 1;\n"
"}\n"
""));

        gridLayout->addWidget(pushButtonChange, 28, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_3, 27, 0, 1, 1);

        lineEditDistBtwDevices = new QLineEdit(MeasurementProperties);
        lineEditDistBtwDevices->setObjectName(QString::fromUtf8("lineEditDistBtwDevices"));
        lineEditDistBtwDevices->setReadOnly(true);

        gridLayout->addWidget(lineEditDistBtwDevices, 26, 1, 1, 1);

        labelDistBtwDevices = new QLabel(MeasurementProperties);
        labelDistBtwDevices->setObjectName(QString::fromUtf8("labelDistBtwDevices"));

        gridLayout->addWidget(labelDistBtwDevices, 26, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(MeasurementProperties);

        QMetaObject::connectSlotsByName(MeasurementProperties);
    } // setupUi

    void retranslateUi(QWidget *MeasurementProperties)
    {
        MeasurementProperties->setWindowTitle(QCoreApplication::translate("MeasurementProperties", "\320\241\320\262\320\276\320\271\321\201\321\202\320\262\320\260", nullptr));
        labelMainName->setText(QCoreApplication::translate("MeasurementProperties", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        labelNameArea->setText(QCoreApplication::translate("MeasurementProperties", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\277\320\273\320\276\321\211\320\260\320\264\320\270", nullptr));
        labelGainUpHole->setText(QCoreApplication::translate("MeasurementProperties", "\320\243\321\201\320\270\320\273\320\265\320\275\320\270\320\265 \320\275\320\260\320\267\320\265\320\274\320\275\321\213\321\205 \320\274\320\276\320\264\321\203\320\273\320\265\320\271", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("MeasurementProperties", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        labelSource->setText(QCoreApplication::translate("MeasurementProperties", "\320\230\321\201\321\202\320\276\321\207\320\275\320\270\320\272 \320\262\320\276\320\267\320\264\320\265\320\271\321\201\321\202\320\262\320\270\321\217", nullptr));
        labelSourceType->setText(QCoreApplication::translate("MeasurementProperties", "\320\242\320\270\320\277", nullptr));
        labelTimeRecord->setText(QCoreApplication::translate("MeasurementProperties", "\320\222\321\200\320\265\320\274\321\217 \320\267\320\260\320\277\320\270\321\201\320\270", nullptr));
        labelDepth->setText(QCoreApplication::translate("MeasurementProperties", "\320\223\320\273\321\203\320\261\320\270\320\275\320\260", nullptr));
        labelServiceInfo->setText(QCoreApplication::translate("MeasurementProperties", "\320\241\320\273\321\203\320\266\320\265\320\261\320\275\320\260\321\217 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217", nullptr));
        labelTimeSwip->setText(QCoreApplication::translate("MeasurementProperties", "\320\222\321\200\320\265\320\274\321\217 \321\201\320\262\320\270\320\277-\321\201\320\270\320\263\320\275\320\260\320\273\320\260", nullptr));
        labelNameProj->setText(QCoreApplication::translate("MeasurementProperties", "\320\237\321\200\320\276\320\265\320\272\321\202", nullptr));
        labelSourceStat->setText(QCoreApplication::translate("MeasurementProperties", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265", nullptr));
        labelIdMeas->setText(QCoreApplication::translate("MeasurementProperties", "\320\235\320\276\320\274\320\265\321\200 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217", nullptr));
        labelNumUpHole->setText(QCoreApplication::translate("MeasurementProperties", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\275\320\260\320\267\320\265\320\274\320\275\321\213\321\205 \320\274\320\276\320\264\321\203\320\273\320\265\320\271", nullptr));
        labelDate->setText(QCoreApplication::translate("MeasurementProperties", "\320\224\320\260\321\202\320\260", nullptr));
        labelGainDnHole->setText(QCoreApplication::translate("MeasurementProperties", "\320\243\321\201\320\270\320\273\320\265\320\275\320\270\320\265 \321\201\320\272\320\262\320\260\320\266\320\270\320\275\320\275\321\213\321\205 \320\274\320\276\320\264\321\203\320\273\320\265\320\271", nullptr));
        labelTime->setText(QCoreApplication::translate("MeasurementProperties", "\320\222\321\200\320\265\320\274\321\217", nullptr));
        labelNumDnHole->setText(QCoreApplication::translate("MeasurementProperties", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\201\320\272\320\262\320\260\320\266\320\270\320\275\320\275\321\213\321\205  \320\274\320\276\320\264\321\203\320\273\320\265\320\271", nullptr));
        labelOperator->setText(QCoreApplication::translate("MeasurementProperties", "\320\244\320\230\320\236 \320\276\320\277\320\265\321\200\320\260\321\202\320\276\321\200\320\260", nullptr));
        labelNumHole->setText(QCoreApplication::translate("MeasurementProperties", "\342\204\226 \321\201\320\272\320\262\320\260\320\266\320\270\320\275\320\260", nullptr));
        pushButtonChange->setText(QCoreApplication::translate("MeasurementProperties", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        labelDistBtwDevices->setText(QCoreApplication::translate("MeasurementProperties", "\320\240\320\260\321\201\321\201\321\202. \320\274\320\265\320\266. \321\206\320\265\320\275\321\202\321\200. \320\277\321\200\320\276\320\273\320\265\321\202\320\276\320\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MeasurementProperties: public Ui_MeasurementProperties {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEASUREMENTPROPERTIES_H
