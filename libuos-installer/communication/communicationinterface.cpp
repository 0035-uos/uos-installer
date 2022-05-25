#include "communicationinterface.h"

#include <QDebug>

CommunicationInterface::CommunicationInterface(QObject *parent):
    QObject (parent)
{

}

CommunicationInterface::~CommunicationInterface()
{
    close();
}

bool CommunicationInterface::start()
{
    return init();
}

void CommunicationInterface::send(const QByteArray &data)
{
    for (int i = 0;i < m_ioDevices.length(); i++) {
        if (m_ioDevices.at(i)->isWritable()) {
            m_ioDevices.at(i)->write(data);
        }
    }
}

bool CommunicationInterface::init()
{
    return true;
}

void CommunicationInterface::close()
{
    for (int i = 0;i < m_ioDevices.length(); i++) {
        if (m_ioDevices.at(i)->isOpen()) {
            m_ioDevices.at(i)->close();
        }
    }
}

void CommunicationInterface::recvData(const QByteArray &data)
{
    Q_UNUSED(data);
}


void CommunicationInterface::appendDevice(QIODevice *dev)
{
    if (!dev || !(dev->isOpen()) || !(dev->isWritable())) {
        return;
    }
    connect(dev, &QIODevice::readyRead, this, &CommunicationInterface::readData);
    m_ioDevices.append(dev);
    qInfo() << "new connect:" << dev->objectName();
}

void CommunicationInterface::writeData(const QByteArray &data)
{
    for (int i = 0;i < m_ioDevices.length(); i++) {
        if (m_ioDevices.at(i)->isWritable()) {
            m_ioDevices.at(i)->write(data);
        }
    }
}

void CommunicationInterface::readData()
{
    QIODevice *dev = static_cast<QIODevice*>(sender());
    if (!dev)
        return;
    QByteArray recv_data = dev->readAll();
    recvData(recv_data);
    emit sigRecvData(recv_data);
}
