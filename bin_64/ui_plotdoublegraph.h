/********************************************************************************
** Form generated from reading UI file 'plotdoublegraph.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTDOUBLEGRAPH_H
#define UI_PLOTDOUBLEGRAPH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <qcustomplot/qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_plotDoubleGraph
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QCustomPlot *customPlot;

    void setupUi(QWidget *plotDoubleGraph)
    {
        if (plotDoubleGraph->objectName().isEmpty())
            plotDoubleGraph->setObjectName(QString::fromUtf8("plotDoubleGraph"));
        plotDoubleGraph->resize(548, 132);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(plotDoubleGraph->sizePolicy().hasHeightForWidth());
        plotDoubleGraph->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(plotDoubleGraph);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(0);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalSpacer = new QSpacerItem(81, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_3->addItem(verticalSpacer, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_3->addItem(verticalSpacer_2, 2, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout_3, 0, 1, 1, 1);

        customPlot = new QCustomPlot(plotDoubleGraph);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(customPlot->sizePolicy().hasHeightForWidth());
        customPlot->setSizePolicy(sizePolicy1);
        customPlot->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(customPlot, 0, 0, 1, 1);


        retranslateUi(plotDoubleGraph);

        QMetaObject::connectSlotsByName(plotDoubleGraph);
    } // setupUi

    void retranslateUi(QWidget *plotDoubleGraph)
    {
        plotDoubleGraph->setWindowTitle(QCoreApplication::translate("plotDoubleGraph", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class plotDoubleGraph: public Ui_plotDoubleGraph {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTDOUBLEGRAPH_H
