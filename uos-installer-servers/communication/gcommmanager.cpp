#include "gcommmanager.h"

#include "glocalsocket.h"
#include "utils/utils.h"

#include <QCoreApplication>

CommunicationInterface* GCommManager::m_inter = nullptr;
GCommManager::GCommManager(QObject *parent) : QObject(parent)
{

}

CommunicationInterface *GCommManager::commInterface()
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
        m_inter = new GLocalSocket;
    }
    m_inter->setObjectName(qApp->objectName());
    return m_inter;
}

void GCommManager::release()
{
    if (m_inter) {
        m_inter->deleteLater();
    }
    m_inter = nullptr;
}
