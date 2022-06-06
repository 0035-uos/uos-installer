#include "glocalmanager.h"

#include "utils/utils.h"
#include "localsocket.h"
#include "protocol/gprotocol.h"
#include "protocol/gprotomanager.h"
#include "gpartedinfo.h"
#include "gsysinfo.h"
#include "utils/commands.h"
#include "gnotifyinfo.h"
#include "gcomponentmanager.h"
#include "parameter.h"
#include "systeminfoconfig.h"
#include "partedconfig.h"
#include "userinput.h"
#include "glanguageinfo.h"
#include "gxkblayout.h"
#include "gtimezone.h"
#include "settingsmanager.h"

#include <QtConcurrent>
#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include <QThread>

#include <iostream>

GLocalManager::GLocalManager(QObject *parent) : InstallWorker(parent)
{
    m_commandList << cmd_set_install_devices;
    m_commandList << cmd_set_component;
}

CommunicationInterface *GLocalManager::communication()
{
    if (m_inter) {
        return m_inter;
    }
    using namespace Tools;
    Installation mode = installation();
    switch (mode) {
    case WTI_Socket:
        break;
    case WTI_SerialPort:
        break;
    case WTI_Default:
    case WTI_Local:
    case WTI_PXE:
    case WTI_AutoInstall:
        m_inter = new LocalSocket;
    }
    m_inter->setObjectName(qApp->objectName());
    connect(m_inter, &CommunicationInterface::sigRecvData, this, [&](const QByteArray &data){
        GProtoManager::Instance()->appendSocketData(data);
    });
    return m_inter;
}

void GLocalManager::installResult(const QByteArray &data)
{
    Q_UNUSED(data)
    m_inter->send(GProtocol::generateFrame(cmd_get_log, "1"));
    qInfo() << tr("Install finished.");
    qInfo() << tr("pull log");
}

void GLocalManager::recvOtherData(const QByteArray &type, const QByteArray &frame)
{
    if (type == cmd_get_log) {
        qInfo() << "export log file:" << Tools::WriteFile(QString("/tmp/ex-uos-installer-server.log"), frame);
        m_inter->send(GProtocol::exitServerFrame());
        QTimer::singleShot(2000, this, []{
            qApp->exit();
        });
    }
}


void GLocalManager::notifyResponse(const GNotifyInfo &info)
{
    InstallWorker::notifyResponse(info);
    QString cmd = info.object().value("result").toObject().value("command").toString();
    if (!(m_commandList.contains(cmd.toLocal8Bit()))) {
        qInfo() << "Not processed" << cmd;
    }
}


void GLocalManager::setLanguage(const GLanguageInfo &language)
{
    SystemInfoConfig::Instance()->setLanguage(language);
}

void GLocalManager::setXkblayout(const GXkbLayout &xkblayout)
{
    SystemInfoConfig::Instance()->setXkblayout(xkblayout);
}

void GLocalManager::setTimerzone(const GTimezone &timezone)
{
    SystemInfoConfig::Instance()->setTimerzone(timezone);
}

void GLocalManager::setComponent()
{
    QStringList componentList = GComponentManager::Instance()->componentList();
    if (componentList.count() <= 0) {
        qCritical() << tr("not found valid component");
        qApp->exit(1);
    }
    int outIndex;
    QString outResult;
    UserInput::UserSelect(outIndex, outResult, componentList, tr("please select install component:"));
    m_inter->send(GProtocol::generateFrame(cmd_set_component,  outResult.toLocal8Bit()));
}

void GLocalManager::setDevices(const QList<const DeviceInfo *> &devicelist)
{
    PartedConfig::Instance()->initData();
    QStringList devlist, devdesc;

    for (const DeviceInfo* info : devicelist) {
        PartedConfig::Instance()->appendDevice(info);
        devlist << info->getPath();
        devdesc <<  QString("(%1G)").arg(1.0*info->getLength()*info->getSectorSize()/Tools::GByte);
    }

    int outIndex;
    QString outResult;
    UserInput::UserSelect(outIndex, outResult, devlist, tr("please select install device:"), true, devdesc);
    m_inter->send(GProtocol::generateFrame(cmd_set_install_devices, outResult.toLocal8Bit()));
    PartedConfig::Instance()->setDefaultDevicePath(outResult);
}

void GLocalManager::setParted()
{
    PartedConfig::Instance()->run();
    PartedConfig::Instance()->cleanData();
    m_inter->send(GProtocol::getPartedFrame(PartedConfig::Instance()->data()));
}

void GLocalManager::setSystemInfo()
{
    SystemInfoConfig::Instance()->initData();
    SystemInfoConfig::Instance()->run();
    SystemInfoConfig::Instance()->cleanData();
    m_inter->send(GProtocol::getSysInfoFrame(SystemInfoConfig::Instance()->data()));
}
