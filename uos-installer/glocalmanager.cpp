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

#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include <iostream>

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
    m_flowList.append(GProtocol::generateFrame(cmd_get_component, "component"));
    m_flowList.append(GProtocol::getPartedFrame(new GPartedInfo(Parameter::Instance()->getPartedFile())));
    m_flowList.append(GProtocol::getSysInfoFrame(new GSysInfo(Parameter::Instance()->getSysInfoFile())));
    m_flowList.append(GProtocol::startInstallFrame());
    next();
}

void GLocalManager::recvData(const QByteArray &type, const QByteArray &frame)
{
    Q_UNUSED(type)
    if (type == heartbeat_packets) {
        QJsonObject object = QJsonDocument::fromJson(frame).object();
        ServerState::Instance()->jsonToPropery(object);
        heartPackets();
        return;
    } else if (type == cmd_notify_response) {
        GNotifyInfo info(GNotifyInfo::fromeByteArray(frame));
        info.commitData();
        notifyResponse(info);
    } else {
        qWarning() << "invalid data";
    }
}

void GLocalManager::heartPackets()
{
    //ServerState::Instance();
}

void GLocalManager::notifyResponse(const GNotifyInfo &info)
{
    QString cmd = info.object().value("result").toObject().value("command").toString();
    qInfo() << cmd;
    if (cmd == cmd_notify_install_result) {
        m_inter->send(GProtocol::exitServerFrame());
        QTimer::singleShot(2000, this, []{
            qApp->exit();
        });
        return;
    } else if (cmd == cmd_get_component) {
        GComponentManager::Instance()->commitData(info.object().value("component").toObject());
        GComponentManager::Instance()->exportfile("./component.json");
        QStringList componentList = GComponentManager::Instance()->componentList();
        QString comp, comp_default;
        if (componentList.count() <= 0) {
            qInfo() << tr("not found valid component");
            qApp->exit(1);
        }
        for (int i = 0; i < componentList.length(); i++) {
            if (i == 0) comp_default = componentList.at(i);
            std::cout << std::to_string(i+1) << " " << componentList.at(i).toStdString() << (i==0 ? "" :"\t[default]") << std::endl;
        }
        std::cout << tr("please select install component:").toStdString();
        std::string c;
        std::cin >> c;
        comp = QString::fromStdString(c).trimmed();

        if (comp.isEmpty()) {
            m_inter->send(GProtocol::generateFrame(cmd_set_install_devices,  comp_default.toLocal8Bit()));
        } else {
            if (componentList.contains(comp)) {
                m_inter->send(GProtocol::generateFrame(cmd_set_install_devices,  comp.toLocal8Bit()));
            } else {
                bool ok = false;
                int k = comp.toInt(&ok);
                if (ok && k > 0 && k <= componentList.length()) {
                    m_inter->send(GProtocol::generateFrame(cmd_set_install_devices, componentList.at(k-1).toLocal8Bit()));
                } else{
                    std::cout << tr("invalid device").toStdString() << c << std::endl;
                    qApp->exit(1);
                }
            }
        }
    } else if (cmd == cmd_get_devices) {
        QJsonArray array = info.object().value("devices").toArray();
        QStringList devlist;
        QString sdev, sdev_default;
        if (array.count() <= 0) {
            qInfo() << tr("not found valid devices");
            qApp->exit(1);
        }
        for (int i = 0;i < array.count();i++) {
            sdev = array.at(i).toObject().value("path").toString();
            if (i == 0) sdev_default = sdev;
            devlist << sdev;
            std::cout << std::to_string(i+1) << " " << sdev.toStdString() << (i==0 ? "" :"\t[default]") << std::endl;
        }
        std::cout << tr("please select install device:").toStdString();
        std::string dev;
        std::cin >> dev;
        sdev = QString::fromStdString(dev).trimmed();

        if (sdev.isEmpty()) {
            m_inter->send(GProtocol::generateFrame(cmd_set_install_devices,  sdev_default.toLocal8Bit()));
        } else {
            if (devlist.contains(sdev)) {
                m_inter->send(GProtocol::generateFrame(cmd_set_install_devices,  sdev.toLocal8Bit()));
            } else {
                bool ok = false;
                int k = sdev.toInt(&ok);
                if (ok && k > 0 && k <= devlist.length()) {
                    m_inter->send(GProtocol::generateFrame(cmd_set_install_devices, devlist.at(k-1).toLocal8Bit()));
                } else{
                    qInfo() << tr("invalid device") << sdev;
                    qApp->exit(1);
                }
            }
        }
    } else if (cmd == cmd_set_install_devices) {
        next();
    } else if (cmd == cmd_set_component) {
        next();
    } else if (cmd == cmd_set_parted) {
        next();
    } else if (cmd == cmd_set_sys_info) {
        next();
    } else if (cmd == cmd_start_install) {
        next();
    }
}

void GLocalManager::next()
{
    if (!m_inter || m_flowList.length() <= 0) return;
    QByteArray top = m_flowList.front();
    m_flowList.removeFirst();
    m_inter->send(top);
}
