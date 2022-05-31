#include "libuosinstaller.h"

#include "protocol/gprotocol.h"
#include "communication/localsocket.h"


Libuosinstaller::Libuosinstaller(QObject *parent): QObject (parent),
    m_socket(nullptr)
{
}

bool Libuosinstaller::initConnect(const QStringList &parameter)
{
    Q_UNUSED(parameter)
    if (!m_socket) {
        m_socket = new LocalSocket;
    }
    return m_socket->initConnection();
}

void Libuosinstaller::closeConnect()
{
    if (m_socket) {
        m_socket->disConnection();
    }
}

bool Libuosinstaller::writeFile(const QString &filename)
{
    QByteArray buffer;
    GProtocol::getFrameFromFile(filename, buffer);

    m_socket->writeData(buffer);
    return true;
}
