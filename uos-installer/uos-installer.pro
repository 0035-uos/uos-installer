QT -= gui
QT += network concurrent xml
CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#DEFINES += DEEEPIN_PW_CHECK
CONFIG(DEEEPIN_PW_CHECK) {
    message("enable deepin-pw-check")
    LIBS += -ldeepin_pw_check
} else {
    message("disable deepin-pw-check")
}

SOURCES += \
        main.cpp \
    parameter.cpp \
    glocalmanager.cpp \
    localsocket.cpp \
    systeminfoconfig.cpp \
    configinterface.cpp \
    partedconfig.cpp \
    settingsmanager.cpp \
    userinput.cpp

HEADERS += \
    parameter.h \
    glocalmanager.h \
    localsocket.h \
    systeminfoconfig.h \
    configinterface.h \
    partedconfig.h \
    settingsmanager.h \
    userinput.h

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target


LIBS += -L $$OUT_PWD/../libuos-installer/ -luos-installer
INCLUDEPATH  += $$PWD/../libuos-installer
QMAKE_INCDIR += $$PWD/../libuos-installer
