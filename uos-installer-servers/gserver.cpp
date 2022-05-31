#include "gserver.h"


#include <QLocalServer>
#include <QLocalSocket>

GServer::GServer(QObject *parent) : QObject(parent),
    m_server(nullptr)
{

}

bool GServer::start()
{
    if (m_server == nullptr) {
        m_server = new QLocalServer;
        connect(m_server, &QLocalServer::newConnection, this, &GServer::newConnection);
    }
    return m_server->listen(objectName());
}

void GServer::newConnection()
{
    QLocalSocket *socket = m_server->nextPendingConnection();
    connect(socket, &QLocalSocket::readyRead, this, &GServer::NewData);
}

void GServer::NewData()
{
    QLocalSocket *socket = static_cast<QLocalSocket*>(sender());
    if (!socket)
        return;
    QByteArray recv_data = socket->readAll();
    if (m_socketList.contains(socket)) {
        ;
    } else {
        m_socketList.append(socket);
    }
}
