#include "gscriptserver.h"

#include "gscriptsrunabstract.h"
#include "protocol/gprotocol.h"
#include "utils/commands.h"
#include "utils/utils.h"
#include "gnotifyinfo.h"
#include "devices/gdevices.h"
#include "gcomponentmanager.h"
#include "glanguageinfo.h"
#include "gtimezone.h"
#include "gxkblayout.h"
#include "settingsmanager.h"

#include <QtDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFileInfo>



GScriptServer::GScriptServer(QObject *parent) : QObject(parent),
    m_script(new GScriptsRunAbstract)
{
#define REGISTERFUNCTION(cmd, func) m_registerFunction[cmd] = std::bind(&GScriptServer::func, this, std::placeholders::_1);
    m_registerFunction[cmd_get_devices] = std::bind(&GScriptServer::onGetDevices, this, std::placeholders::_1);
     m_registerFunction[cmd_set_install_devices] = std::bind(&GScriptServer::onSetDevice, this, std::placeholders::_1);
    m_registerFunction[cmd_set_parted] = std::bind(&GScriptServer::onSetParted, this, std::placeholders::_1);
    m_registerFunction[cmd_set_sys_info] = std::bind(&GScriptServer::onSetSysInfo, this, std::placeholders::_1);
    m_registerFunction[cmd_start_install] = std::bind(&GScriptServer::onStartInstall, this, std::placeholders::_1);
    m_registerFunction[cmd_exit_server] = std::bind(&GScriptServer::onExit, this, std::placeholders::_1);
    m_registerFunction[cmd_set_component] = std::bind(&GScriptServer::onSetComponent, this, std::placeholders::_1);
    m_registerFunction[cmd_get_component] = std::bind(&GScriptServer::onGetComponent, this, std::placeholders::_1);
    m_registerFunction[cmd_get_log] = std::bind(&GScriptServer::onGetLog, this, std::placeholders::_1);
    m_registerFunction[cmd_get_language] = std::bind(&GScriptServer::onGetLanguage, this, std::placeholders::_1);
    m_registerFunction[cmd_get_xkblayout] = std::bind(&GScriptServer::onGetXkbLayout, this, std::placeholders::_1);
    m_registerFunction[cmd_get_timezone] = std::bind(&GScriptServer::onGetTimezone, this, std::placeholders::_1);
    REGISTERFUNCTION(cmd_set_user_settings, onSetUserSettings)

    connect(m_script, &GScriptsRunAbstract::finished, this, &GScriptServer::finished);
}

void GScriptServer::start(const QByteArray &cmd, const QByteArray &parameter)
{
    if (m_registerFunction.contains(cmd)) {
        m_registerFunction.value(cmd)(parameter);
    }
}

void GScriptServer::finished(const QString &cmd, const QByteArray &data)
{
    Q_UNUSED(cmd)
    Q_UNUSED(data)
    GNotifyInfo info2 = GNotifyInfo::reponse(cmd_notify_install_result, true, "desc"); // undo
    sigSend(GProtocol::getNotifyFrame(info2.data()));
    ServerState::Instance()->setState(SERVER_STATE_INSTALL_FINISHED);
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
    qInfo() << __func__ << data;
    GNotifyInfo info = GNotifyInfo::reponse(cmd_get_component, true, "component"); // undo
    info.appendItem("component", GComponentManager::Instance()->object());
    info.commitData();
    sigSend(GProtocol::getNotifyFrame(info.data()));
}


void GScriptServer::onSetComponent(const QByteArray &data)
{
    qInfo() << __func__ << data;
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
            file.write("\n");
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

    GNotifyInfo info1 = GNotifyInfo::reponse(cmd_start_install, true, "desc"); // undo
    sigSend(GProtocol::getNotifyFrame(info1.data()));

    ServerState::Instance()->setState(SERVER_STATE_INSTALLING);
    QStringList args;
    args << QStringList()<< Tools::main_sh << ServerState::Instance()->getDevicePath();
    if (SettingsManager::Instance()->value("autoDetectEfi") != "true") {
        args << SettingsManager::Instance()->value("fixEfi");
    }
    m_script->startRun("/bin/bash", args);
}


void GScriptServer::onExit(const QByteArray &data)
{
    Q_UNUSED(data);
    emit sigExitServer();
}

void GScriptServer::onGetLog(const QByteArray &data)
{
    Q_UNUSED(data)
    QByteArray frame = Tools::ReadFile(Tools::installer_server_log_file).toLocal8Bit();
    sigSend(GProtocol::generateFrame(cmd_get_log, frame));
}

void GScriptServer::onGetXkbLayout(const QByteArray &data)
{
    Q_UNUSED(data)
    qInfo() << __func__;
    GNotifyInfo info = GNotifyInfo::reponse(cmd_get_xkblayout, true, "xkblayout");

    GXkbLayout xkblayout;


    Tools::XkbConfig xkb = Tools::GetXkbConfig();

    GArrayJson layoutarray;
    for (const Tools::XkbLayout& layout : xkb.layout_list) {
        GJsonItem item;
        item.appendValue("name", layout.name);
        item.appendValue("description", layout.description);
        GArrayJson array;
        for (const Tools::XkbLayoutVariant& variant : layout.variant_list) {
            GJsonItem variantitem;
            variantitem.appendValue("name", variant.name);
            variantitem.appendValue("description", variant.description);
            array.appendItem(&variantitem);
        }
        array.commitData();
        item.appendValue("variantList", array.data());
        layoutarray.appendItem(&item);
    }
    layoutarray.commitData();

    xkblayout.appendArray("layout_list", layoutarray);
    xkblayout.commitData();

    GJsonItem item;
    item.appendValue("xkblayout", xkblayout.data());

    info.appendItem("xkblayout",  &item);
    info.commitData();
    sigSend(GProtocol::getNotifyFrame(info.data()));
}

void GScriptServer::onGetLanguage(const QByteArray &data)
{
    Q_UNUSED(data)
    qInfo() << __func__;
    GNotifyInfo info = GNotifyInfo::reponse(cmd_get_language, true, "language");
    info.appendItem("language", GJson(Tools::languages_path).array());
    info.commitData();
    sigSend(GProtocol::getNotifyFrame(info.data()));
}

void GScriptServer::onGetTimezone(const QByteArray &data)
{
    Q_UNUSED(data)
    qInfo() << __func__;
    GNotifyInfo info = GNotifyInfo::reponse(cmd_get_timezone, true, "timezone");

    GTimezone zone;
    Tools::ZoneInfoList zonelist = Tools::GetZoneInfoList();
    for (const Tools::ZoneInfo& info : zonelist) {
        GJsonItem item;
        item.appendValue("country", info.country);
        item.appendValue("timezone", info.timezone);
        item.appendValue("latitude", QString::number(info.latitude));
        item.appendValue("longitude", QString::number(info.longitude));
        item.appendValue("distance", QString::number(info.distance));
        zone.appendItem(&item);
    }
    zone.commitData();

    info.appendItem("timezone", zone.array());
    info.commitData();
    sigSend(GProtocol::getNotifyFrame(info.data()));
}

void GScriptServer::onSetUserSettings(const QByteArray &data)
{
    qInfo() << __func__;
    SettingsManager::Instance()->loaddata(data);
    SettingsManager::Instance()->exportfile("./user.json");
    GNotifyInfo info = GNotifyInfo::reponse(cmd_set_user_settings, true, "user_settings");
    info.commitData();
    sigSend(GProtocol::getNotifyFrame(info.data()));
}

