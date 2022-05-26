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
#include "parameter.h"

#include <QDebug>
#include <QDir>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    a.setObjectName("uos-installer");

    // Initialize log service.
    const char kLogFileName[] = "uos-installer.log";
    QString log_file;
#ifdef QT_DEBUG
        qCritical() << "Root privilege is required!";
        log_file = QString("/tmp/%1").arg(kLogFileName);
#else
        log_file = QString("/var/log/%1").arg(kLogFileName);
#endif

    Parameter::Instance()->setPartedFile("parted.json");
    Parameter::Instance()->setSysInfoFile("./sysinfo.json");
    Parameter::Instance()->parser();


    CommunicationInterface *socket = GLocalManager::Instance()->communication();
    socket->start();
    GLocalManager::Instance()->startInstall();
    return a.exec();
}
