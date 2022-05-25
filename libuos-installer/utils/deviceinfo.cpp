#include "deviceinfo.h"

DeviceInfo::DeviceInfo(QObject *parent) : PropertyReflection(parent)
{
}


QString DeviceInfo::getPath() const
{
    return path;
}

void DeviceInfo::setPath(const QString &value)
{
    path = value;
}

qint64 DeviceInfo::getSectorSize() const
{
    return sectorSize;
}

void DeviceInfo::setSectorSize(qint64 value)
{
    sectorSize = value;
}

qint64 DeviceInfo::getPhysSectorSize() const
{
    return physSectorSize;
}

void DeviceInfo::setPhysSectorSize(qint64 value)
{
    physSectorSize = value;
}

qint64 DeviceInfo::getLength() const
{
    return length;
}

void DeviceInfo::setLength(qint64 value)
{
    length = value;
}

int DeviceInfo::getType() const
{
    return type;
}

void DeviceInfo::setType(int value)
{
    type = value;
}
