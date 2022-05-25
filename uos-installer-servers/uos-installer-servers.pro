QT -= gui
QT += network
CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        communication/gcommmanager.cpp \
        scripts/gscriptsrunabstract.cpp \
        gmanager.cpp \
        main.cpp \
    gserver.cpp \
    communication/gcommserver.cpp \
    scripts/gscriptserver.cpp \
    communication/glocalsocket.cpp \
    devices/gdevices.cpp \
    devices/gparted.cpp \
    gheartbeatthread.cpp \
    communication/gtcpscoket.cpp



HEADERS += \
    communication/gcommmanager.h \
    scripts/gscriptsrunabstract.h \
    gmanager.h \
    gserver.h \
    communication/gcommserver.h \
    scripts/gscriptserver.h \
    communication/glocalsocket.h \
    devices/gdevices.h \
    devices/gparted.h \
    gheartbeatthread.h \
    communication/gtcpscoket.h



# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

LIBS += -lparted
LIBS += -L $$OUT_PWD/../libuos-installer/ -luos-installer
INCLUDEPATH  += $$PWD/../libuos-installer
QMAKE_INCDIR += $$PWD/../libuos-installer

