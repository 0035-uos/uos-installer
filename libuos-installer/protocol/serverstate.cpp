#include "serverstate.h"

ServerState::ServerState(QObject *parent) : PropertyReflection(parent)
{

}

int ServerState::getState() const
{
    return state;
}

void ServerState::setState(int value)
{
    state = value;
}

bool ServerState::getLoadPackagesDefault() const
{
    return loadPackagesDefault;
}

void ServerState::setLoadPackagesDefault(bool value)
{
    loadPackagesDefault = value;
}

bool ServerState::getBootValid() const
{
    return bootValid;
}

void ServerState::setBootValid(bool value)
{
    bootValid = value;
}

QString ServerState::getBoot() const
{
    return boot;
}

void ServerState::setBoot(const QString &value)
{
    boot = value;
}

QString ServerState::getCdrom() const
{
    return cdrom;
}

void ServerState::setCdrom(const QString &value)
{
    cdrom = value;
}

QString ServerState::getLiveFileSystem() const
{
    return liveFileSystem;
}

void ServerState::setLiveFileSystem(const QString &value)
{
    liveFileSystem = value;
}

QString ServerState::getDistribution() const
{
    return distribution;
}

void ServerState::setDistribution(const QString &value)
{
    distribution = value;
}

QString ServerState::getLive() const
{
    return live;
}

void ServerState::setLive(const QString &value)
{
    live = value;
}

QString ServerState::getLupinRoot() const
{
    return lupinRoot;
}

void ServerState::setLupinRoot(const QString &value)
{
    lupinRoot = value;
}
