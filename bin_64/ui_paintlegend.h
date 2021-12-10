/********************************************************************************
** Form generated from reading UI file 'paintlegend.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAINTLEGEND_H
#define UI_PAINTLEGEND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PaintLegend
{
public:

    void setupUi(QWidget *PaintLegend)
    {
        if (PaintLegend->objectName().isEmpty())
            PaintLegend->setObjectName(QString::fromUtf8("PaintLegend"));
        PaintLegend->resize(150, 50);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PaintLegend->sizePolicy().hasHeightForWidth());
        PaintLegend->setSizePolicy(sizePolicy);
        PaintLegend->setMinimumSize(QSize(150, 50));

        retranslateUi(PaintLegend);

        QMetaObject::connectSlotsByName(PaintLegend);
    } // setupUi

    void retranslateUi(QWidget *PaintLegend)
    {
        PaintLegend->setWindowTitle(QCoreApplication::translate("PaintLegend", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PaintLegend: public Ui_PaintLegend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAINTLEGEND_H
