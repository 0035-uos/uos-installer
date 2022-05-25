#include "gdevices.h"

#include <QDebug>

#include <parted/parted.h>
#include <parted/device.h>




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


