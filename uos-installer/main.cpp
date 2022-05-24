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

    Parameter::Instance()->setPartedFile("parted.json");
    Parameter::Instance()->setSysInfoFile("./sysinfo.json");
    Parameter::Instance()->parser();


    QDir dir("/uos-installer");
    if (!(dir.exists())) {
        QDir("/").mkdir("/uos-installer");
    }
    if (!(dir.exists())) {
        qWarning() << "/installer create failed";
        return 0;
    }


    CommunicationInterface *socket = GLocalManager::Instance()->communication();
    socket->start();
    GLocalManager::Instance()->startInstall();
    return a.exec();
}
