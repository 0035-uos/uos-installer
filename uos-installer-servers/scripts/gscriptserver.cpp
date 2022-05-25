#include "gscriptserver.h"

#include "gscriptsrunabstract.h"
#include "protocol/gprotocol.h"
#include "utils/commands.h"
#include "utils/utils.h"
#include "gnotifyinfo.h"
#include "devices/gdevices.h"
#include "gcomponentmanager.h"

#include <QtDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFileInfo>

GScriptServer::GScriptServer(QObject *parent) : QObject(parent),
    m_script(new GScriptsRunAbstract)
{
    m_registerFunction[cmd_get_devices] = std::bind(&GScriptServer::onGetDevices, this, std::placeholders::_1);
     m_registerFunction[cmd_set_install_devices] = std::bind(&GScriptServer::onSetDevice, this, std::placeholders::_1);
    m_registerFunction[cmd_set_parted] = std::bind(&GScriptServer::onSetParted, this, std::placeholders::_1);
    m_registerFunction[cmd_set_sys_info] = std::bind(&GScriptServer::onSetSysInfo, this, std::placeholders::_1);
    m_registerFunction[cmd_start_install] = std::bind(&GScriptServer::onStartInstall, this, std::placeholders::_1);
    m_registerFunction[cmd_exit_server] = std::bind(&GScriptServer::onExit, this, std::placeholders::_1);
    m_registerFunction[cmd_set_component] = std::bind(&GScriptServer::onSetComponent, this, std::placeholders::_1);
    m_registerFunction[cmd_get_component] = std::bind(&GScriptServer::onGetComponent, this, std::placeholders::_1);
}

void GScriptServer::start(const QByteArray &cmd, const QByteArray &parameter)
{
    if (m_registerFunction.contains(cmd)) {
        m_registerFunction.value(cmd)(parameter);
    }
}

void GScriptServer::onGetDevices(const QByteArray &data)
{
    qInfo() << __func__ << data;// undo
    GNotifyInfo info = GNotifyInfo::reponse(cmd_get_devices, true, "desc"); // undo 判断设备读取情况
    info.appendItem("devices", GDevices::Instance()->DevicesJson());

    info.commitData();
    sigSend(GProtocol::getNotifyFrame(info.data()));
}

void GScriptServer::onSetDevice(const QByteArray &data)
{
    qInfo() << __func__;// undo
    ServerState::Instance()->setDevicePath(data);
    GNotifyInfo info = GNotifyInfo::reponse(cmd_set_install_devices, true, "desc");
    sigSend(GProtocol::getNotifyFrame(info.data()));
}

void GScriptServer::onSetParted(const QByteArray &data)
{
    qInfo() << __func__; // 分区信息 data->json
    // 保存路径可以先固定，后期统一配置
    QString fp = Tools::parted_parameter_path;
    if (GJson(data).exportfile(fp)) {
        qInfo() << "save parted(json):" << fp;
    } else {
        qWarning() << "save partd(json) failed:" << fp;
    }
    // undo check

    GNotifyInfo info = GNotifyInfo::reponse(cmd_set_parted, true, "desc"); // undo
    sigSend(GProtocol::getNotifyFrame(info.data()));
}

void GScriptServer::onSetSysInfo(const QByteArray &data)
{
    qInfo() << __func__;
    // 保存路径可以先固定，后期统一配置
    QString fp = Tools::sys_info_path;
    if (GJson(data).exportfile(fp)) {
        qInfo() << "save sysinfo(json):" << fp;
    } else {
        qWarning() << "save sysinfo(json) failed:" << fp;
    }
    // undo check

    GNotifyInfo info = GNotifyInfo::reponse(cmd_set_sys_info, true, "desc"); // undo
    sigSend(GProtocol::getNotifyFrame(info.data()));
}

void GScriptServer::onGetComponent(const QByteArray &data)
{
    Q_UNUSED(data)
    qInfo() << __func__;
    GNotifyInfo info = GNotifyInfo::reponse(cmd_get_component, true, "component"); // undo
    info.appendItem("component", GComponentManager::Instance()->object());
    info.commitData();
    sigSend(GProtocol::getNotifyFrame(info.data()));
}


void GScriptServer::onSetComponent(const QByteArray &data)
{
    qInfo() << __func__;
    QString fp = Tools::component_path;

    QStringList componentList = GComponentManager::Instance()->componentList();
    QStringList plist;
    if (componentList.contains(data)) {
        plist  = GComponentManager::Instance()->packagesList(data);
    }
    QFile file(fp);
    if (!(plist.isEmpty()) && file.open(QFile::WriteOnly)) {
        for (const QString& p : plist) {
            file.write(p.toLocal8Bit());
            file.write("\r\n");
        }
        file.close();
    }
    // undo check

    GNotifyInfo info = GNotifyInfo::reponse(cmd_set_component, true, "desc"); // undo
    sigSend(GProtocol::getNotifyFrame(info.data()));
}

void GScriptServer::onStartInstall(const QByteArray &data)
{
    qInfo() << __func__ << data; // 开始安装，调用启动脚本
    qInfo() << ServerState::Instance()->getDevicePath();

    ServerState::Instance()->setBootValid(true);
    ServerState::Instance()->setCdrom("cdrom");

    GNotifyInfo info1 = GNotifyInfo::reponse(cmd_start_install, true, "desc"); // undo
    sigSend(GProtocol::getNotifyFrame(info1.data()));

    m_script->startRun("/bin/bash", QStringList()<< Tools::main_sh << "/dev/sdb");

    m_script->waitFinished();
    GNotifyInfo info2 = GNotifyInfo::reponse(cmd_notify_install_result, true, "desc"); // undo
    sigSend(GProtocol::getNotifyFrame(info2.data()));
}


void GScriptServer::onExit(const QByteArray &data)
{
    Q_UNUSED(data);
    emit sigExitServer();
}

