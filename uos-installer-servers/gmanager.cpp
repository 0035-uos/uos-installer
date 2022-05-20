#include "gmanager.h"

#include "communication/gcommserver.h"
#include "scripts/gscriptserver.h"
#include "protocol/gprotomanager.h"
#include "gheartbeatthread.h"

#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QCoreApplication>

GManager::GManager(QObject *parent) : QObject(parent)
{
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



