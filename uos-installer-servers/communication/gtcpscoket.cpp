#include "gtcpscoket.h"

#include "protocol/gprotomanager.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

GNetScoket::GNetScoket(QObject *parent) : CommunicationInterface(parent)
{

}

GNetScoket::~GNetScoket()
{
    if (m_server) {
        m_server->close();
        m_server->deleteLater();
    }
    m_server = nullptr;
}

void GNetScoket::recvData(const QByteArray &data)
{
    GProtoManager::Instance()->appendSocketData(data);
}

bool GNetScoket::init()
{
    if (m_server == nullptr) {
        m_server = new QTcpServer;
        connect(m_server, &QTcpServer::newConnection, this, &GNetScoket::newConnection);
    }
    return m_server->listen(QHostAddress::Any);
}

void GNetScoket::newConnection()
{

}
