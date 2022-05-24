#include "gdevices.h"

#include <QDebug>

#include <parted/parted.h>
#include <parted/device.h>

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



GDevices::GDevices(QObject *parent) : QObject(parent)
{
    scanDevices();
}

const QList<DeviceInfo*> &GDevices::Devices()
{
    return m_devices;
}

QJsonArray GDevices::DevicesJson() const
{
    QJsonArray array;
    for (const DeviceInfo* info : m_devices) {
        array.append(info->properyToJson());
    }
    return array;
}

void GDevices::scanDevices()
{
    PedDevice* pDevice = nullptr;
    ped_device_probe_all();;
    while ((pDevice = ped_device_get_next(pDevice))) {
        if (1 == pDevice->read_only) {
            qInfo() << QString("IGNORED:by readonly:{%1}, path:{%2}")
                       .arg(pDevice->read_only)
                       .arg(pDevice->path);
            continue;
        }
        if (PED_DEVICE_LOOP == pDevice->type) {
            qInfo() << QString("IGNORED:by type:{%1} path:{%2}")
                       .arg(pDevice->type)
                       .arg(pDevice->path);
            continue;
        }

        DeviceInfo *info = new DeviceInfo;
        info->setPath(pDevice->path);
        info->setSectorSize(pDevice->sector_size);
        info->setPhysSectorSize(pDevice->phys_sector_size);
        info->setLength(pDevice->length);
        info->setType(int(pDevice->type));
        m_devices.append(info);
    }
}


