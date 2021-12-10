/********************************************************************************
** Form generated from reading UI file 'graphdownhole.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHDOWNHOLE_H
#define UI_GRAPHDOWNHOLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcustomplot/qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_graphDownHole
{
public:
    QGridLayout *gridLayout;
    QCustomPlot *customPlot;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *relayModeButton;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *graphDownHole)
    {
        if (graphDownHole->objectName().isEmpty())
            graphDownHole->setObjectName(QString::fromUtf8("graphDownHole"));
        graphDownHole->resize(687, 132);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphDownHole->sizePolicy().hasHeightForWidth());
        graphDownHole->setSizePolicy(sizePolicy);
        graphDownHole->setMinimumSize(QSize(0, 0));
        gridLayout = new QGridLayout(graphDownHole);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        customPlot = new QCustomPlot(graphDownHole);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(customPlot->sizePolicy().hasHeightForWidth());
        customPlot->setSizePolicy(sizePolicy1);
        customPlot->setMinimumSize(QSize(0, 0));
        customPlot->setSizeIncrement(QSize(0, 0));

        gridLayout->addWidget(customPlot, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout->setContentsMargins(0, -1, -1, -1);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer);

        relayModeButton = new QPushButton(graphDownHole);
        relayModeButton->setObjectName(QString::fromUtf8("relayModeButton"));
        relayModeButton->setMinimumSize(QSize(75, 30));
        relayModeButton->setMaximumSize(QSize(75, 30));
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

        verticalLayout->addWidget(relayModeButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_2);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);


        retranslateUi(graphDownHole);

        QMetaObject::connectSlotsByName(graphDownHole);
    } // setupUi

    void retranslateUi(QWidget *graphDownHole)
    {
        graphDownHole->setWindowTitle(QCoreApplication::translate("graphDownHole", "Form", nullptr));
        relayModeButton->setText(QCoreApplication::translate("graphDownHole", "\320\222\320\272\320\273 \320\240\320\265\320\273\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class graphDownHole: public Ui_graphDownHole {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHDOWNHOLE_H
