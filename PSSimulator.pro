#-------------------------------------------------
#
# Project created by QtCreator 2014-03-16T21:13:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    ui/simulatordatawidget.cpp

HEADERS  += mainwindow.h \
    CIM/semdcim.h \
    CIM/semddata.h \
    CIM/BreakerStatus.h \
    CIM/MeasurementType.h \
    Simulator/simulatordata.h \
    Simulator/simulator.h \
    ui/simulatordatawidget.h \
    ui/simulatordatawidget_p.h

FORMS    += mainwindow.ui

LIBS += -L/usr/lib/ -lIEC61970

win32:CONFIG(release, debug|release): LIBS += -L/usr/lib/x86_64-linux-gnu/mesa/ -lGL
else:win32:CONFIG(debug, debug|release): LIBS += -L/usr/lib/x86_64-linux-gnu/mesa/ -lGLd
else:unix: LIBS += -L/usr/lib/x86_64-linux-gnu/mesa/ -lGL

INCLUDEPATH += /usr/include/GL
DEPENDPATH += /usr/include/GL

win32:CONFIG(release, debug|release): LIBS += -L/usr/lib/IEC61970/ -lIEC61970
else:win32:CONFIG(debug, debug|release): LIBS += -L/usr/lib/IEC61970/ -lIEC61970d
else:unix: LIBS += -L/usr/lib/IEC61970/ -lIEC61970

INCLUDEPATH += /usr/include/IEC61970
DEPENDPATH += /usr/include/IEC61970
