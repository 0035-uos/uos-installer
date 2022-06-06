#include "installworker.h"
#include "utils/utils.h"
#include "protocol/gprotocol.h"
#include "protocol/gprotomanager.h"
#include "gpartedinfo.h"
#include "gsysinfo.h"
#include "utils/commands.h"
#include "gnotifyinfo.h"
#include "gcomponentmanager.h"
#include "glanguageinfo.h"
#include "gxkblayout.h"
#include "gtimezone.h"
#include "settingsmanager.h"
#include "communication/communicationinterface.h"
#include "utils/deviceinfo.h"

#include <QtConcurrent>
#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include <QThread>

#include <iostream>


InstallWorker::InstallWorker(QObject *parent): QObject (parent),
    m_inter(nullptr), m_serverReady(false)
{
    connect(GProtoManager::Instance(), &GProtoManager::newFrame, this, &InstallWorker::recvData);
    connect(this, &InstallWorker::sigStart, this, &InstallWorker::next);
    m_autoInstall = false;
    if (Tools::installation() == Tools::WTI_PXE || Tools::installation() == Tools::WTI_PXE) {
        m_autoInstall = true;
    }
}

CommunicationInterface *InstallWorker::communication()
{
    return nullptr;
}

void InstallWorker::startInstall()
{
    if (!m_inter) {
        qWarning() << "Communication protocol not created";
        return;
    }
    SettingsManager::Instance()->loadfile(Tools::user_settings);
    m_flowList.append(GProtocol::generateFrame(cmd_set_user_settings, SettingsManager::Instance()->data()));
    m_flowList.append(GProtocol::generateFrame(cmd_get_language, "language"));
    m_flowList.append(GProtocol::generateFrame(cmd_get_xkblayout, "xkblayout"));
    m_flowList.append(GProtocol::generateFrame(cmd_get_timezone, "timezone"));
    m_flowList.append(GProtocol::getDevicesFrame());
    m_flowList.append(GProtocol::generateFrame(cmd_get_component, "component"));
    m_flowList.append(GProtocol::startInstallFrame());

    m_commandList << cmd_set_user_settings;
    m_commandList << cmd_get_language;
    m_commandList << cmd_get_xkblayout;
    m_commandList << cmd_get_timezone;
    m_commandList << cmd_get_component;
    m_commandList << cmd_get_devices;
    m_commandList << cmd_start_install;
    m_commandList << cmd_notify_install_result;

    QtConcurrent::run(QThreadPool::globalInstance(), [this](){
        qInfo() << tr("waiting for the server to be ready...");
        while (!m_serverReady) {
            QThread::msleep(2000);
        }
        qInfo() << tr("server to be ready");
        emit this->sigStart();
    });
    qInfo() << "startinstall";
}

void InstallWorker::installResult(const QByteArray &data)
{
    Q_UNUSED(data);
}

void InstallWorker::recvData(const QByteArray &type, const QByteArray &frame)
{
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
        recvOtherData(type, frame);
    }
}

void InstallWorker::recvOtherData(const QByteArray &type, const QByteArray &frame)
{
    Q_UNUSED(type)
    Q_UNUSED(frame);
}

void InstallWorker::heartPackets()
{
    m_serverReady = true;
}

void InstallWorker::notifyResponse(const GNotifyInfo &info)
{
    QString cmd = info.object().value("result").toObject().value("command").toString();

    //qInfo() << cmd;
    if (cmd == cmd_notify_install_result) {
        installResult(info.data());
        return;
    } else if (cmd == cmd_get_language) {
        setLanguage(GLanguageInfo(info.object().value("language").toArray()));
        next();
    } else if (cmd == cmd_get_xkblayout) {
        GXkbLayout xkb(info.object().value("xkblayout").toObject());
        setXkblayout(xkb);
        next();
    } else if (cmd == cmd_get_timezone) {
        setTimerzone(GTimezone(info.object().value("timezone").toArray()));
        next();
    } else if (cmd == cmd_get_component) {
        GComponentManager::Instance()->commitData(info.object().value("component").toObject());
        setComponent();
    } else if (cmd == cmd_get_devices) {
        QJsonArray array = info.object().value("devices").toArray();
        QStringList devlist, devdesc;
        if (array.count() <= 0) {
            qCritical() << tr("not found valid devices");
            qApp->exit(1);
        }

        QList<const DeviceInfo *> devicelist;
        for (int i = 0;i < array.count();i++) {
            DeviceInfo *info = new DeviceInfo;
            info->jsonToPropery(array.at(i).toObject());
            devicelist.append(info);
        }
        setDevices(devicelist);
    } else if (cmd == cmd_set_install_devices) {
        next();
    } else if (cmd == cmd_set_component) {
        setParted();
    } else if (cmd == cmd_set_parted) {
        setSystemInfo();
    } else if (cmd == cmd_set_sys_info) {
        next();
    } else if (cmd == cmd_start_install) {
        qInfo() << tr("Installing, please waiting....");
    } else {
        next();
    }
}

void InstallWorker::next()
{
    if (!m_inter || m_flowList.length() <= 0) return;
    QByteArray top = m_flowList.front();
    m_flowList.removeFirst();
    m_inter->send(top);
}

void InstallWorker::setLanguage(const GLanguageInfo &language)
{
    Q_UNUSED(language)
}

void InstallWorker::setXkblayout(const GXkbLayout &xkblayout)
{
    Q_UNUSED(xkblayout)
}

void InstallWorker::setTimerzone(const GTimezone &timezone)
{
    Q_UNUSED(timezone)
}

void InstallWorker::setComponent()
{

}

void InstallWorker::setDevices(const QList<const DeviceInfo *> &devicelist)
{
    Q_UNUSED(devicelist)
}

void InstallWorker::setParted()
{

}

void InstallWorker::setSystemInfo()
{

}

