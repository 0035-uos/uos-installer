#include "gscriptserver.h"

#include "gscriptsrunabstract.h"
#include "protocol/gprotocol.h"
#include "utils/commands.h"
#include "utils/utils.h"

#include <QtDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

GScriptServer::GScriptServer(QObject *parent) : QObject(parent),
    m_script(new GScriptsRunAbstract)
{
    m_registerFunction[cmd_get_devices] = std::bind(&GScriptServer::onGetDevices, this, std::placeholders::_1);
    m_registerFunction[cmd_set_parted] = std::bind(&GScriptServer::onSetParted, this, std::placeholders::_1);
    m_registerFunction[cmd_set_sys_info] = std::bind(&GScriptServer::onSetSysInfo, this, std::placeholders::_1);
    m_registerFunction[cmd_start_install] = std::bind(&GScriptServer::onStartInstall, this, std::placeholders::_1);
    m_registerFunction[cmd_exit_server] = std::bind(&GScriptServer::onExit, this, std::placeholders::_1);
}

void GScriptServer::start(const QByteArray &cmd, const QByteArray &parameter)
{
    //qInfo() << cmd << parameter;
    if (m_registerFunction.contains(cmd)) {
        m_registerFunction.value(cmd)(parameter);
    }

    QString fn = Tools::scanValidFileName("/tmp/", "uos-install-tmp");
    QFile file(fn);
    if (!file.open(QFile::WriteOnly)) {
        return;
    }
    file.write(parameter);
    file.close();
    QByteArray send;
    GProtocol::getFrameFromFile(fn, send);
    sigSend(send);
    //m_script->startRun("ls", QStringList()<<"/usr/share");
}

void GScriptServer::onGetDevices(const QByteArray &data)
{
    qInfo() << __func__ << data;// undo
}

void GScriptServer::onSetParted(const QByteArray &data)
{
    qInfo() << __func__ << data; // 分区信息 data->json
    // 保存路径可以先固定，后期统一配置
    QString fp = "/tmp/parted.json";
    QFile file(fp);
    if (file.open(QFile::WriteOnly)) {
        file.write(QJsonDocument::fromJson(data).toJson(QJsonDocument::Indented));
        file.close();
    }
}

void GScriptServer::onSetSysInfo(const QByteArray &data)
{
    qInfo() << __func__ << data;
    // 保存路径可以先固定，后期统一配置
    QString fp = "/tmp/sysinfo.json";
    QFile file(fp);
    if (file.open(QFile::WriteOnly)) {
        file.write(QJsonDocument::fromJson(data).toJson(QJsonDocument::Indented));
        file.close();
    }
}

void GScriptServer::onStartInstall(const QByteArray &data)
{
    qInfo() << __func__ << data; // 开始安装，调用启动脚本
    // m_script->startRun("ls", QStringList()<<"/usr/share");
}

void GScriptServer::onExit(const QByteArray &data)
{
    Q_UNUSED(data);
    emit sigExitServer();
}

