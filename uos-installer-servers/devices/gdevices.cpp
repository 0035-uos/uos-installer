#include "gdevices.h"

#include <QDebug>

#include <parted/parted.h>

GDevices::GDevices(QObject *parent) : QObject(parent)
{
    scanDevices();
}

const QList<DeviceInfo> &GDevices::Devices()
{
    return m_devices;
}

void GDevices::scanDevices()
{
    PedDevice* pDevice = nullptr;
    ped_device_probe_all();
    while ((pDevice = ped_device_get_next(pDevice))) {
       DeviceInfo info;
       info.path = pDevice->path;
       info.sector_size = pDevice->sector_size;
       info.phys_sector_size = pDevice->phys_sector_size;
       info.length = pDevice->length;
       info.type = int(pDevice->type);
       m_devices.append(info);
    }
}
