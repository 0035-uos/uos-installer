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

bool ServerState::getEfi() const
{
    return efi;
}

void ServerState::setEfi(bool value)
{
    efi = value;
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

QString ServerState::getPartedFile() const
{
    return partedFile;
}

void ServerState::setPartedFile(const QString &value)
{
    partedFile = value;
}

QString ServerState::getSysInfoFile() const
{
    return sysInfoFile;
}

void ServerState::setSysInfoFile(const QString &value)
{
    sysInfoFile = value;
}

QString ServerState::getDevicePath() const
{
    return devicePath;
}

void ServerState::setDevicePath(const QString &value)
{
    devicePath = value;
}

bool ServerState::getAutoInstall() const
{
    return autoInstall;
}

void ServerState::setAutoInstall(bool value)
{
    autoInstall = value;
}

qint64 ServerState::getBuffers() const
{
    return buffers;
}

void ServerState::setBuffers(const qint64 &value)
{
    buffers = value;
}

qint64 ServerState::getCached() const
{
    return cached;
}

void ServerState::setCached(const qint64 &value)
{
    cached = value;
}

qint64 ServerState::getMemAvailable() const
{
    return memAvailable;
}

void ServerState::setMemAvailable(const qint64 &value)
{
    memAvailable = value;
}

qint64 ServerState::getMemFree() const
{
    return memFree;
}

void ServerState::setMemFree(const qint64 &value)
{
    memFree = value;
}

qint64 ServerState::getMemTotal() const
{
    return memTotal;
}

void ServerState::setMemTotal(const qint64 &value)
{
    memTotal = value;
}

qint64 ServerState::getSwapFree() const
{
    return swapFree;
}

void ServerState::setSwapFree(const qint64 &value)
{
    swapFree = value;
}

qint64 ServerState::getSwapTotal() const
{
    return swapTotal;
}

void ServerState::setSwapTotal(const qint64 &value)
{
    swapTotal = value;
}


