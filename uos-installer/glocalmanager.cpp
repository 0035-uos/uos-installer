#include "glocalmanager.h"

#include "utils/utils.h"
#include "localsocket.h"
#include "protocol/gprotocol.h"
#include "protocol/gprotomanager.h"
#include "gpartedinfo.h"
#include "gsysinfo.h"
#include "utils/commands.h"
#include "gnotifyinfo.h"

#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

GLocalManager::GLocalManager(QObject *parent) : QObject(parent),
    m_inter(nullptr)
{
    connect(GProtoManager::Instance(), &GProtoManager::newFrame, this, &GLocalManager::recvData);
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

void GLocalManager::startInstall()
{
    if (!m_inter) {
        return;
    }
    m_flowList.append(GProtocol::getDevicesFrame());
    m_flowList.append(GProtocol::getPartedFrame(new GPartedInfo("./parted.json")));
    m_flowList.append(GProtocol::getSysInfoFrame(new GSysInfo("./sysinfo.json")));
    m_flowList.append(GProtocol::startInstallFrame());
    next();
}

void GLocalManager::recvData(const QByteArray &type, const QByteArray &frame)
{
    GNotifyInfo info(GNotifyInfo::fromeByteArray(frame));
    info.commitData();
    QString cmd = info.object().value("result").toObject().value("command").toString();
    qInfo() << cmd;
    if (cmd == cmd_notify_install_result) {
        m_inter->send(GProtocol::exitServerFrame());
        QTimer::singleShot(2000, this, []{
            qApp->exit();
        });
        return;
    }
//    if (cmd == cmd_get_devices) {
//        QFile file("./dev.json");
//        if (file.open(QFile::WriteOnly)) {
//            file.write(info.data());
//            file.close();
//        }
//    } else {
//        qInfo() << frame;
//    }
    next();
}

void GLocalManager::next()
{
    if (!m_inter || m_flowList.length() <= 0) return;
    QByteArray top = m_flowList.front();
    m_flowList.removeFirst();
    m_inter->send(top);
}
