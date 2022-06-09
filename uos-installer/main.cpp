#include <QCoreApplication>

#include "protocol/gprotocol.h"
#include "communication/communicationinterface.h"
#include "glocalmanager.h"
#include "gpartedinfo.h"
#include "gsysinfo.h"
#include "gpartedinfo.h"
#include "gparteditem.h"
#include "gsysinfo.h"
#include "log/DLog"
#include "utils/utils.h"
#include "parameter.h"

#include <QThread>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QElapsedTimer>

#include <iostream>

static void print_info(const QString& msg) {
    qInfo() << msg;
    std::cout << msg.toStdString() << std::endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    a.setObjectName("uos-installer");

    // Initialize log service.
    DLogManager::setLogFormat("%{time}{yyyy-MM-dd, HH:mm:ss.zzz} [%{type:-7}] "
                              "[%{function:-35} %{line}] %{message}\n");
    DLogManager::setlogFilePath(Tools::installer_log_file);
    DLogManager::registerConsoleAppender();
    DLogManager::registerFileAppender();

    if (argc > 1)
        Parameter::Instance()->parser();

    CommunicationInterface *socket = GLocalManager::Instance()->communication();
    bool serverReady = false;
    QElapsedTimer time;
    qreal elapsed = 0;
    qreal max_elapsed = 60*5;
    time.start();
    do {
        if (elapsed > max_elapsed) {
            print_info(QObject::tr("Service does not start normally"));
            print_info(QObject::tr("Timeout exit"));
            print_info(QObject::tr("You can start the installation by manually starting the uos-installer-cli@.service service"));
            a.exit();
        }
        elapsed = time.elapsed()/1000.0;
        print_info(QObject::tr("Waiting for service to start[%1s]").arg(elapsed));
        QThread::msleep(1000);
        serverReady = socket->start();
    } while (!serverReady);
    GLocalManager::Instance()->startInstall();
    return a.exec();
}
