#-------------------------------------------------
#
# Project created by QtCreator 2014-03-16T21:13:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = PSSimulator
TEMPLATE = app

INCLUDEPATH += \
    CIM \
    Simulator

SOURCES += main.cpp\
    mainwindow.cpp \
    CIM/semdcim.cpp \
    CIM/semddata.cpp \
    Simulator/simulatordata.cpp \
    Simulator/simulator.cpp \
    ui/simulatordatawidget.cpp \
    PIU/BreakerIED.cpp \
    Helpers/UpdateSystem/DataUpdateSystem.cpp \
    ui/localwidget.cpp \
    PIU/busied.cpp \
    PIU/TrafoIED.cpp \
    Multicast/Sender.cpp \
    Multicast/Receiver.cpp \
    PIU/switchied.cpp


HEADERS  += mainwindow.h \
    CIM/semdcim.h \
    CIM/semddata.h \
    CIM/BreakerStatus.h \
    CIM/MeasurementType.h \
    Simulator/simulatordata.h \
    Simulator/simulator.h \
    ui/simulatordatawidget.h \
    ui/simulatordatawidget_p.h \
    PIU/BreakerIED.h \
    Helpers/UpdateSystem/DataUpdateSystem.h \
    ui/localwidget.h \
    PIU/TrafoIED.h \
    PIU/busied.h \
    Multicast/Sender.h \
    Multicast/Receiver.h \
    PIU/switchied.h \
    CIM/switchstatus.h


FORMS    += mainwindow.ui

#LIBS += -L/usr/lib/ -lIEC61970

#win32:CONFIG(release, debug|release): LIBS += -L/usr/lib/x86_64-linux-gnu/mesa/ -lGL
#else:win32:CONFIG(debug, debug|release): LIBS += -L/usr/lib/x86_64-linux-gnu/mesa/ -lGLd
#else:unix: LIBS += -L/usr/lib/x86_64-linux-gnu/mesa/ -lGL

#INCLUDEPATH += /usr/include/GL
#DEPENDPATH += /usr/include/GL

#win32:CONFIG(release, debug|release): LIBS += -L/usr/lib/IEC61970/ -lIEC61970
#else:win32:CONFIG(debug, debug|release): LIBS += -L/usr/lib/IEC61970/ -lIEC61970d
#else:unix: LIBS += -L/usr/lib/IEC61970/ -lIEC61970

LIBS += -L/usr/lib/IEC61970/ -lIEC61970 \
        -L/usr/lib/IEC61850/ -lIEC61850 \
        -L/usr/lib/libasn1 -lLIBASN1


INCLUDEPATH += /usr/include/IEC61970 /usr/include/IEC61850/ /usr/include/libasn1
DEPENDPATH += /usr/include/IEC61970 /usr/include/IEC61850/ /usr/include/libasn1

macx {
QMAKE_MAC_SDK = macosx10.9
}
