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

#include <QDebug>
#include <QDir>
#include <QFileInfo>

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
    socket->start();
    GLocalManager::Instance()->startInstall();
    return a.exec();
}
