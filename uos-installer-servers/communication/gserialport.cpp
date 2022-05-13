#include "gserialport.h"

#include <QSerialPort>

GSerialPort::GSerialPort(QObject *parent):
    CommunicationInterface(parent),
    m_server(nullptr)
{

}

void GSerialPort::send(const QByteArray &data)
{
    if (m_server && m_server->isOpen()) {
        m_server->write(data);
    }
}

bool GSerialPort::init()
{
    if (!m_server) {
        m_server = new QSerialPort;
        connect(m_server, &QSerialPort::readyRead, this, &GSerialPort::NewData);
    }
    if (m_server->isOpen()) {
        m_server->close();
    }
    // undo 获取串口参数....
    return true;
}

void GSerialPort::NewData()
{
    QByteArray recv_data = m_server->readAll();
    recvData(recv_data);
}

