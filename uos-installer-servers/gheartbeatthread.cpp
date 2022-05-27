#include "gheartbeatthread.h"
#include "protocol/gprotocol.h"
#include "protocol/serverstate.h"
#include "utils/commands.h"
#include "gjson.h"

#include <QThread>
#include <QDebug>

GHeartBeatThread::GHeartBeatThread(QObject *parent) : QObject(parent)
{
    connect(this, &GHeartBeatThread::sigStartHeartBeat, this, &GHeartBeatThread::startHeartBeat);
}

void GHeartBeatThread::startHeartBeat(ulong interval)
{
    m_exit = false;
    static GJson json;
    while (!m_exit) {
        json.commitData(ServerState::Instance()->properyToJson());
        sigSend(GProtocol::generateFrame(heartbeat_packets, json.data()));
        QThread::msleep(interval);
    }
}

bool GHeartBeatThread::exit() const
{
    return m_exit;
}

void GHeartBeatThread::setExit(bool exit)
{
    m_exit = exit;
}

