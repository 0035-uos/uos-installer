#include "gnetscoket.h"

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
    return true;
}

void GNetScoket::newConnection()
{

}
