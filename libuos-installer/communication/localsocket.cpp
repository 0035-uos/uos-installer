#include "localsocket.h"

#include <QLocalSocket>
#include <QCoreApplication>
#include <QDebug>

LocalSocket::LocalSocket(QObject *parent) : LocalInterface(parent),
    m_socket(nullptr)
{

}

bool LocalSocket::initConnection()
{
    if (!m_socket) {
        m_socket = new QLocalSocket;
    }
    if (m_socket->state() == QLocalSocket::ConnectedState) {
        return true;
    }
    m_socket->connectToServer(qApp->objectName());

    return m_socket->waitForConnected(10000);
}

void LocalSocket::disConnection()
{
    if (m_socket) {
        m_socket->close();
    }
}

void LocalSocket::writeData(const QByteArray &data)
{
    if (m_socket) {
        m_socket->flush();
        m_socket->write(data);
    }
}

void LocalSocket::recvData(QByteArray& data, int timeout)
{
    if (!m_socket)
        return;
    m_socket->waitForReadyRead(timeout);
    while (m_socket->bytesAvailable()) {
        data.append(m_socket->readAll());
    }
}
