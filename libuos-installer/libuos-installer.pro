#-------------------------------------------------
#
# Project created by QtCreator 2022-05-09T11:31:50
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = uos-installer
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include($$PWD/log/log.pri)

SOURCES += \
        libuosinstaller.cpp \
    communication/localsocket.cpp \
    protocol/gprotocol.cpp \
    utils/utils.cpp \
    gpartedinfo.cpp \
    gjson.cpp \
    gsysinfo.cpp \
    gnotifyinfo.cpp \
    gparteditem.cpp \
    gjsonitem.cpp \
    communication/localinterface.cpp \
    communication/communicationinterface.cpp \
    protocol/gprotomanager.cpp \
    utils/propertyreflection.cpp \
    protocol/serverstate.cpp \
    gcomponentmanager.cpp


HEADERS += \
        libuosinstaller.h \
    communication/localsocket.h \
    protocol/gprotocol.h \
    utils/commands.h \
    utils/singleton.h \
    utils/utils.h \
    gpartedinfo.h \
    gjson.h \
    gsysinfo.h \
    gnotifyinfo.h \
    gparteditem.h \
    gjsonitem.h \
    communication/localinterface.h \
    communication/communicationinterface.h \
    protocol/gprotomanager.h \
    utils/propertyreflection.h \
    protocol/serverstate.h \
    gcomponentmanager.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
