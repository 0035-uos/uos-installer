#ifndef GDEVICES_H
#define GDEVICES_H

#include "utils/singleton.h"

#include <QObject>
#include <QList>

/*
typedef enum {
        PED_DEVICE_UNKNOWN      = 0,
        PED_DEVICE_SCSI         = 1,
        PED_DEVICE_IDE          = 2,
        PED_DEVICE_DAC960       = 3,
        PED_DEVICE_CPQARRAY     = 4,
        PED_DEVICE_FILE         = 5,
        PED_DEVICE_ATARAID      = 6,
        PED_DEVICE_I2O          = 7,
        PED_DEVICE_UBD          = 8,
        PED_DEVICE_DASD         = 9,
        PED_DEVICE_VIODASD      = 10,
        PED_DEVICE_SX8          = 11,
        PED_DEVICE_DM           = 12,
        PED_DEVICE_XVD          = 13,
        PED_DEVICE_SDMMC        = 14,
        PED_DEVICE_VIRTBLK      = 15,
        PED_DEVICE_AOE          = 16,
        PED_DEVICE_MD           = 17,
        PED_DEVICE_LOOP         = 18,
        PED_DEVICE_NVME         = 19
} PedDeviceType;
*/
struct DeviceInfo
{
    QString path;
    long long       sector_size;            /**< logical sector size */
    long long       phys_sector_size;       /**< physical sector size */
    long long       length;                 /**< device length (LBA) */
    int type;
    // undo ...
};

class GDevices : public QObject, public Singleton<GDevices>
{
    Q_OBJECT
public:
    explicit GDevices(QObject *parent = nullptr);

    const QList<DeviceInfo> &Devices();

signals:

public slots:

private:
    void scanDevices();

private:
    QList<DeviceInfo> m_devices;
};

#endif // GDEVICES_H
