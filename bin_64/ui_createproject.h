/********************************************************************************
** Form generated from reading UI file 'createproject.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEPROJECT_H
#define UI_CREATEPROJECT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CreateProject
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelPath_3;
    QFrame *line;
    QSpacerItem *verticalSpacer_2;
    QGridLayout *gridLayout;
    QTextEdit *textEditPath;
    QLabel *labelName;
    QLabel *labelPath;
    QSpacerItem *verticalSpacer;
    QTextEdit *textEditName;
    QPushButton *pushButtonPath;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelPicPlace;
    QLabel *labelPlace;
    QSpacerItem *horizontalSpacer_3;
    QLabel *labelPicResult;
    QLabel *labelResult;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonCancel;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;

    void setupUi(QDialog *CreateProject)
    {
        if (CreateProject->objectName().isEmpty())
            CreateProject->setObjectName(QString::fromUtf8("CreateProject"));
        CreateProject->setEnabled(true);
        CreateProject->resize(698, 480);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CreateProject->sizePolicy().hasHeightForWidth());
        CreateProject->setSizePolicy(sizePolicy);
        CreateProject->setMinimumSize(QSize(640, 480));
        CreateProject->setMaximumSize(QSize(698, 480));
        CreateProject->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/TNG.ico"), QSize(), QIcon::Normal, QIcon::Off);
        CreateProject->setWindowIcon(icon);
        CreateProject->setStyleSheet(QString::fromUtf8("background-color: #ffffff; font-family: Arial; font-size: 16pt;"));
        CreateProject->setSizeGripEnabled(false);
        verticalLayout = new QVBoxLayout(CreateProject);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(15, 35, 10, 15);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelPath_3 = new QLabel(CreateProject);
        labelPath_3->setObjectName(QString::fromUtf8("labelPath_3"));
        labelPath_3->setEnabled(true);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(58);
        labelPath_3->setFont(font);
        labelPath_3->setStyleSheet(QString::fromUtf8("color: rgb(50, 50, 50); border: NONE; font-family: Arial; font-size: 12pt; font-weight: 470;"));
        labelPath_3->setLineWidth(1);
        labelPath_3->setAlignment(Qt::AlignCenter);
        labelPath_3->setWordWrap(true);

        horizontalLayout->addWidget(labelPath_3);


        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(CreateProject);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        textEditPath = new QTextEdit(CreateProject);
        textEditPath->setObjectName(QString::fromUtf8("textEditPath"));
        sizePolicy.setHeightForWidth(textEditPath->sizePolicy().hasHeightForWidth());
        textEditPath->setSizePolicy(sizePolicy);
        textEditPath->setMinimumSize(QSize(300, 20));
        textEditPath->setMaximumSize(QSize(300, 150));
        textEditPath->setStyleSheet(QString::fromUtf8("background-color: #ffffff; color: rgb(55, 55, 55);  border-width: 1px; border-style: solid; border-color: #18799b;  font-family: Arial; font-size: 11pt; font-weight: 450;"));
        textEditPath->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        textEditPath->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEditPath->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        textEditPath->setLineWrapMode(QTextEdit::FixedPixelWidth);
        textEditPath->setLineWrapColumnOrWidth(280);
        textEditPath->setReadOnly(true);

        gridLayout->addWidget(textEditPath, 2, 1, 1, 1);

        labelName = new QLabel(CreateProject);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        labelName->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelName->sizePolicy().hasHeightForWidth());
        labelName->setSizePolicy(sizePolicy1);
        labelName->setMaximumSize(QSize(16777215, 30));
        labelName->setFont(font);
        labelName->setStyleSheet(QString::fromUtf8("color: rgb(50, 50, 50); border: NONE; font-family: Arial; font-size: 12pt; font-weight: 470;"));

        gridLayout->addWidget(labelName, 0, 0, 1, 1);

        labelPath = new QLabel(CreateProject);
        labelPath->setObjectName(QString::fromUtf8("labelPath"));
        labelPath->setEnabled(true);
        sizePolicy1.setHeightForWidth(labelPath->sizePolicy().hasHeightForWidth());
        labelPath->setSizePolicy(sizePolicy1);
        labelPath->setMaximumSize(QSize(16777215, 30));
        labelPath->setFont(font);
        labelPath->setStyleSheet(QString::fromUtf8("color: rgb(50, 50, 50); border: NONE; font-family: Arial; font-size: 12pt; font-weight: 470;"));

        gridLayout->addWidget(labelPath, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 1, 1, 1, 1);

        textEditName = new QTextEdit(CreateProject);
        textEditName->setObjectName(QString::fromUtf8("textEditName"));
        sizePolicy.setHeightForWidth(textEditName->sizePolicy().hasHeightForWidth());
        textEditName->setSizePolicy(sizePolicy);
        textEditName->setMinimumSize(QSize(300, 30));
        textEditName->setMaximumSize(QSize(300, 34));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setWeight(56);
        textEditName->setFont(font1);
        textEditName->setStyleSheet(QString::fromUtf8("background-color: #ffffff; color: rgb(55, 55, 55);  border-width: 1px; border-style: solid; border-color: #18799b;  font-family: Arial; font-size: 11pt; font-weight: 450;"));
        textEditName->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        textEditName->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEditName->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        gridLayout->addWidget(textEditName, 0, 1, 1, 1);

        pushButtonPath = new QPushButton(CreateProject);
        pushButtonPath->setObjectName(QString::fromUtf8("pushButtonPath"));
        pushButtonPath->setMinimumSize(QSize(140, 30));
        pushButtonPath->setMaximumSize(QSize(140, 30));
        pushButtonPath->setStyleSheet(QString::fromUtf8("background-color: #ffffff; color: #18799b; border-width: 1px; border-style: solid; border-color: #18799b; font-family: Arial; font-size: 12pt; font-weight: 450; border-radius: 2px;"));

        gridLayout->addWidget(pushButtonPath, 2, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        labelPicPlace = new QLabel(CreateProject);
        labelPicPlace->setObjectName(QString::fromUtf8("labelPicPlace"));
        labelPicPlace->setMinimumSize(QSize(40, 15));
        labelPicPlace->setMaximumSize(QSize(40, 15));

        horizontalLayout_4->addWidget(labelPicPlace);

        labelPlace = new QLabel(CreateProject);
        labelPlace->setObjectName(QString::fromUtf8("labelPlace"));
        labelPlace->setFont(font);
        labelPlace->setAutoFillBackground(false);
        labelPlace->setStyleSheet(QString::fromUtf8("color: rgb(50, 50, 50); border: NONE; font-family: Arial; font-size: 12pt; font-weight: 470;"));

        horizontalLayout_4->addWidget(labelPlace);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        labelPicResult = new QLabel(CreateProject);
        labelPicResult->setObjectName(QString::fromUtf8("labelPicResult"));
        labelPicResult->setMinimumSize(QSize(40, 15));
        labelPicResult->setMaximumSize(QSize(40, 15));

        horizontalLayout_4->addWidget(labelPicResult);

        labelResult = new QLabel(CreateProject);
        labelResult->setObjectName(QString::fromUtf8("labelResult"));
        labelResult->setFont(font);
        labelResult->setStyleSheet(QString::fromUtf8("color: rgb(50, 50, 50); border: NONE; font-family: Arial; font-size: 12pt; font-weight: 470;"));

        horizontalLayout_4->addWidget(labelResult);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        pushButtonCancel = new QPushButton(CreateProject);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setMinimumSize(QSize(140, 30));
        pushButtonCancel->setMaximumSize(QSize(140, 30));
        pushButtonCancel->setStyleSheet(QString::fromUtf8("background-color: #ffffff; color: #18799b; border-width: 1px; border-style: solid; border-color: #18799b; font-family: Arial; font-size: 12pt; font-weight: 450; border-radius: 2px;"));

        horizontalLayout_4->addWidget(pushButtonCancel);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(CreateProject);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(140, 30));
        pushButton_2->setMaximumSize(QSize(140, 30));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: #18799b; color: #ffffff; border-width: 1px; border-style: solid; border-color: rgb(181,181,181); font-family: Arial; font-size: 12pt; font-weight: 450; border-radius: 1;"));

        horizontalLayout_4->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 2);
        verticalLayout->setStretch(4, 3);
        verticalLayout->setStretch(5, 2);

        retranslateUi(CreateProject);

        QMetaObject::connectSlotsByName(CreateProject);
    } // setupUi

    void retranslateUi(QDialog *CreateProject)
    {
        CreateProject->setWindowTitle(QCoreApplication::translate("CreateProject", "\320\234\320\260\321\201\321\202\320\265\321\200 \321\201\320\276\320\267\320\264\320\260\320\275\320\270\321\217 \320\275\320\276\320\262\320\276\320\263\320\276 \320\277\321\200\320\276\320\265\320\272\321\202\320\260", nullptr));
        labelPath_3->setText(QCoreApplication::translate("CreateProject", "<html><head/><body><p>\320\224\320\276\320\261\321\200\320\276 \320\277\320\276\320\266\320\260\320\273\320\276\320\262\320\260\321\202\321\214 \320\262 \320\274\320\260\321\201\321\202\320\265\321\200 \321\201\320\276\320\267\320\264\320\260\320\275\320\270\321\217 \320\277\321\200\320\276\320\265\320\272\321\202\320\260.</p><p>\320\227\320\260\320\264\320\260\320\271\321\202\320\265 \320\270\320\274\321\217 \320\277\321\200\320\276\320\265\320\272\321\202\320\260 \320\270 \320\262\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \320\277\320\260\320\277\320\272\321\203 \320\264\320\273\321\217 \321\201\320\276\321\205\321\200\320\260\320\275\320\265\320\275\320\270\321\217</p></body></html>", nullptr));
        labelName->setText(QCoreApplication::translate("CreateProject", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\277\321\200\320\276\320\265\320\272\321\202\320\260:", nullptr));
        labelPath->setText(QCoreApplication::translate("CreateProject", "\320\237\321\203\321\202\321\214 \320\272 \320\277\320\260\320\277\320\272\320\265:", nullptr));
        textEditName->setHtml(QCoreApplication::translate("CreateProject", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Arial'; font-size:11pt; font-weight:448; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        pushButtonPath->setText(QCoreApplication::translate("CreateProject", "\320\236\320\261\320\267\320\276\321\200", nullptr));
        labelPicPlace->setText(QString());
        labelPlace->setText(QCoreApplication::translate("CreateProject", "\320\240\320\260\320\267\320\274\320\265\321\211\320\265\320\275\320\270\320\265", nullptr));
        labelPicResult->setText(QString());
        labelResult->setText(QCoreApplication::translate("CreateProject", "\320\230\321\202\320\276\320\263", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("CreateProject", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        pushButton_2->setText(QCoreApplication::translate("CreateProject", "\320\224\320\260\320\273\320\265\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateProject: public Ui_CreateProject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEPROJECT_H
