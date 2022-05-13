#include "glocalsocket.h"

#include "protocol/gprotomanager.h"

#include <QLocalServer>
#include <QLocalSocket>
#include <QDebug>


GLocalSocket::GLocalSocket(QObject *parent) : CommunicationInterface(parent),
    m_server(nullptr)
{

}

GLocalSocket::~GLocalSocket()
{
    if (m_server) {
        m_server->close();
        m_server->deleteLater();
    }
    m_server = nullptr;
}

void GLocalSocket::recvData(const QByteArray &data)
{
    GProtoManager::Instance()->appendSocketData(data);
}


bool GLocalSocket::init()
{
    if (m_server == nullptr) {
        m_server = new QLocalServer;
        connect(m_server, &QLocalServer::newConnection, this, &GLocalSocket::newConnection);
    }
    QLocalServer::removeServer(objectName());
    return m_server->listen(objectName());
}

void GLocalSocket::newConnection()
{
    QLocalSocket *socket = m_server->nextPendingConnection();
    appendDevice(socket);
}

