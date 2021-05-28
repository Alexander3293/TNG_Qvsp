QT       += core gui network printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    network/declarateTransceiveringData.cpp \
    network/syncmoduletranciever.cpp \
    network/tcpclient.cpp \
    network/transceiver_class.cpp \
    network/transceiver_ground.cpp \
    qcustomplot/graphdownhole.cpp \
    qcustomplot/graphground.cpp \
    qcustomplot/graphsync.cpp \
    qcustomplot/paintlegend.cpp \
    qcustomplot/plotdoublegraph.cpp \
    qcustomplot/qcustomplot.cpp \
    qcustomplot/test.cpp \
    settings/checkboxincombowidget.cpp \
    settings/extrasettings.cpp \
    settings/settings.cpp \
    work_with_powerSupply/powerdevices.cpp \
    work_with_powerSupply/powersupplycontroller.cpp \
    work_with_powerSupply/tdkLambdaClass.cpp \
    wsdc/create_smsp.cpp

HEADERS += \
    mainwindow.h \
    network/declarateTransceiveringData.h \
    network/syncmoduletranciever.h \
    network/tcpclient.h \
    network/transceiver_class.h \
    network/transceiver_ground.h \
    qcustomplot/graphdownhole.h \
    qcustomplot/graphground.h \
    qcustomplot/graphsync.h \
    qcustomplot/paintlegend.h \
    qcustomplot/plotdoublegraph.h \
    qcustomplot/qcustomplot.h \
    qcustomplot/test.h \
    settings/checkboxincombowidget.h \
    settings/extrasettings.h \
    settings/settings.h \
    work_with_powerSupply/powerdevices.h \
    work_with_powerSupply/powersupplycontroller.h \
    work_with_powerSupply/tdkLambdaClass.h \
    wsdc/create_smsp.h

FORMS += \
    mainwindow.ui \
    qcustomplot/graphdownhole.ui \
    qcustomplot/graphground.ui \
    qcustomplot/graphsync.ui \
    qcustomplot/paintlegend.ui \
    qcustomplot/plotdoublegraph.ui \
    qcustomplot/test.ui \
    settings/checkboxincombowidget.ui \
    settings/extrasettings.ui \
    settings/settings.ui \
    work_with_powerSupply/powerdevices.ui

LIBS    += \
    libwsock32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
