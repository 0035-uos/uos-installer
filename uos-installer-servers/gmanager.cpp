#include "gmanager.h"

#include "communication/gcommserver.h"
#include "scripts/gscriptserver.h"
#include "protocol/gprotomanager.h"
#include "gheartbeatthread.h"
#include "gcomponentmanager.h"
#include "utils/utils.h"
#include "protocol/serverstate.h"

#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>

static const QString memInfoFile = "/proc/meminfo";

GManager::GManager(QObject *parent) : QObject(parent)
{
    initBoot();
    checkEfi();
    readMemInfo();
    GComponentManager::Instance()->loadfile(Tools::packages_default);
    ServerState::Instance()->setLoadPackagesDefault(GComponentManager::Instance()->state());
}

GManager::~GManager()
{
}

void GManager::init()
{
    initCommunication();
    initInstaller();

    connect(GHeartBeatThread::Instance(), &GHeartBeatThread::sigSend, this, &GManager::sendData);
    appendJob("heartbeat", GHeartBeatThread::Instance());
    QTimer::singleShot(200, this, []{
        GHeartBeatThread::Instance()->sigStartHeartBeat(2000);
    });
}

void GManager::onExitServer()
{
    GHeartBeatThread::Instance()->setExit(true);
    QMap<QString, JobItem>::const_iterator it = m_jobMap.constBegin();
    for (; it != m_jobMap.constEnd(); it++) {
        qInfo() << "waiting" << it.key() << "exit";
        it.value().thread->quit();
        it.value().thread->wait(10000);
        qInfo() << it.key() << "exit:" << !(it.value().thread->isRunning());
    }
    qApp->exit();
}

void GManager::initCommunication()
{
    GCommServer *comm = GCommServer::Instance();
    connect(this, &GManager::sigStartCommunication, comm, &GCommServer::start);
    connect(this, &GManager::sendData, comm, &GCommServer::sendData);
    appendJob("communication", comm);
}

void GManager::initInstaller()
{
    GScriptServer* script = GScriptServer::Instance();
    connect(GProtoManager::Instance(), &GProtoManager::newFrame, script, &GScriptServer::start);
    connect(script, &GScriptServer::sigSend, this, &GManager::sendData);
    connect(script, &GScriptServer::sigExitServer, this, &GManager::onExitServer);
    appendJob("script", script);
}

void GManager::appendJob(const QString &key, QObject *object)
{
    QThread *thread = new QThread;
    object->moveToThread(thread);
    m_jobMap[key] = {thread, object};
    thread->start();
}

bool GManager::initBoot()
{
    QFile file("/proc/cmdline");
    ServerState::Instance()->setBootValid(false);
    if (file.exists() && file.open(QFile::ReadOnly)) {
        QByteArray cmdline = file.readAll();
        file.close();
        if (cmdline.contains("boot=casper")) {
            ServerState::Instance()->setBootValid(true);
            ServerState::Instance()->setBoot("casper");
            ServerState::Instance()->setCdrom("/cdrom");
            ServerState::Instance()->setLupinRoot("/isodevice");
            ServerState::Instance()->setDistribution("ubuntu");
        } else if (cmdline.contains("boot=live")) {
            ServerState::Instance()->setBootValid(true);
            ServerState::Instance()->setBoot("live");
            if (QDir("/lib/live/mount/medium/live").exists()) {
                ServerState::Instance()->setCdrom("/lib/live/mount/medium");
            } else {
                ServerState::Instance()->setCdrom("/run/live/medium");
            }
            ServerState::Instance()->setLupinRoot("/lib/live/mount/findiso");
            ServerState::Instance()->setDistribution("debian");
        } else {
            ServerState::Instance()->setBootValid(false);
        }
        if (ServerState::Instance()->getBootValid()) {
            ServerState::Instance()->setLiveFileSystem(ServerState::Instance()->getCdrom()+"/"+ServerState::Instance()->getBoot());
            ServerState::Instance()->setLive(ServerState::Instance()->getBoot());
        }
    }
    return false;
}

bool GManager::checkEfi()
{
    ServerState::Instance()->setEfi(false);
    if (QFileInfo::exists("/sys/firmware/efi") || Tools::is_sw()) {
        ServerState::Instance()->setEfi(true);
    }
    return true;
}

bool GManager::readMemInfo()
{
    const QString content = Tools::ReadFile(memInfoFile);
    if (content.isEmpty()) {
        qWarning() << "Failed to read meminfo!";
        return false;
    }

    QHash<QString, qint64> hash;
    for (const QString& line : content.split('\n')) {
        const int index = line.indexOf(':');
        if (index > -1) {
            QString str_value = line.mid(index + 1);
            str_value.remove("kB");
            str_value = str_value.trimmed();
            // Convert kB to byte.
            const qint64 value = str_value.toLongLong() * 1024;
            hash.insert(line.left(index), value);
            qInfo() << line.left(index) << value;
        }
    }

    ServerState::Instance()->setBuffers(hash.value("Buffers"));
    ServerState::Instance()->setCached(hash.value("Cached"));
    ServerState::Instance()->setMemAvailable(hash.value("MemAvailable"));
    ServerState::Instance()->setMemFree(hash.value("MemFree"));
    ServerState::Instance()->setMemTotal(hash.value("MemTotal"));
    ServerState::Instance()->setSwapFree(hash.value("SwapFree"));
    ServerState::Instance()->setSwapTotal(hash.value("SwapTotal"));
    return true;
}







