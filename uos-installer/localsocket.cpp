#include "localsocket.h"

#include <QLocalSocket>
#include <QCoreApplication>

LocalSocket::LocalSocket(QObject *parent) : CommunicationInterface(parent),
    m_socket(nullptr)
{

}

bool LocalSocket::init()
{

    if (!m_socket) {
        m_socket = new QLocalSocket;
    }
    if (m_socket->state() == QLocalSocket::ConnectedState) {
        return true;
    }
    m_socket->connectToServer(qApp->objectName());
    if (m_socket->waitForConnected(10000)) {
        appendDevice(m_socket);
        return true;
    }
    return false;
}


