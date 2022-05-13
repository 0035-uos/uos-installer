#include "gcommserver.h"

#include "gcommmanager.h"
#include "communication/communicationinterface.h"

#include <QDebug>

GCommServer::GCommServer(QObject *parent) : QObject(parent)
{

}

GCommServer::~GCommServer()
{
    GCommManager::release();
}

void GCommServer::start()
{
    GCommManager::commInterface()->start();
}

void GCommServer::sendData(const QByteArray &data)
{
    GCommManager::commInterface()->send(data);
}

