/********************************************************************************
** Form generated from reading UI file 'graphground.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHGROUND_H
#define UI_GRAPHGROUND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <qcustomplot/qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_graphGround
{
public:
    QGridLayout *gridLayout;
    QCustomPlot *customPlot;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *graphGround)
    {
        if (graphGround->objectName().isEmpty())
            graphGround->setObjectName(QString::fromUtf8("graphGround"));
        graphGround->resize(687, 132);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphGround->sizePolicy().hasHeightForWidth());
        graphGround->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(graphGround);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setVerticalSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        customPlot = new QCustomPlot(graphGround);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(customPlot->sizePolicy().hasHeightForWidth());
        customPlot->setSizePolicy(sizePolicy1);
        customPlot->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(customPlot, 0, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetMinimumSize);
        gridLayout_3->setVerticalSpacing(0);
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_3->addItem(verticalSpacer_2, 2, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(81, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_3->addItem(verticalSpacer, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_3, 0, 1, 1, 1);


        retranslateUi(graphGround);

        QMetaObject::connectSlotsByName(graphGround);
    } // setupUi

    void retranslateUi(QWidget *graphGround)
    {
        graphGround->setWindowTitle(QCoreApplication::translate("graphGround", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class graphGround: public Ui_graphGround {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHGROUND_H
