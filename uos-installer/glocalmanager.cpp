#include "glocalmanager.h"

#include "utils/utils.h"
#include "localsocket.h"
#include "protocol/gprotocol.h"
#include "gpartedinfo.h"
#include "gsysinfo.h"

#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

GLocalManager::GLocalManager(QObject *parent) : QObject(parent),
    m_inter(nullptr)
{

}

CommunicationInterface *GLocalManager::communication()
{
    if (m_inter) {
        return m_inter;
    }
    using namespace Tools;
    Installation mode = installation();
    switch (mode) {
    case WTI_Socket:
        break;
    case WTI_SerialPort:
        break;
    case WTI_Default:
    case WTI_Local:
    case WTI_PXE:
    case WTI_AutoInstall:
        m_inter = new LocalSocket;
    }
    m_inter->setObjectName(qApp->objectName());
    connect(m_inter, &CommunicationInterface::sigRecvData, this, &GLocalManager::recvData);
    return m_inter;
}

void GLocalManager::startInstall()
{
    if (!m_inter) {
        return;
    }
    m_flowList.append(GProtocol::getDevicesFrame());
    m_flowList.append(GProtocol::getPartedFrame(new GPartedInfo("./parted.json")));
    m_flowList.append(GProtocol::getSysInfoFrame(new GSysInfo("./sysinfo.json")));
    m_flowList.append(GProtocol::startInstallFrame());
    m_flowList.append(GProtocol::exitServerFrame());
    next();
}

void GLocalManager::recvData(const QByteArray &data)
{
    Q_UNUSED(data);
    next();
}

void GLocalManager::next()
{
    if (!m_inter || m_flowList.length() <= 0) return;
    QByteArray top = m_flowList.front();
    m_flowList.removeFirst();
    m_inter->send(top);
    if (m_flowList.length() == 0) {
        QTimer::singleShot(2000, this, []{
            qApp->exit();
        });
    }
}
