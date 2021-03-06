#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include "utils/propertyreflection.h"
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
class PartitionInfo;
class DeviceInfo : public PropertyReflection
{
    Q_OBJECT
    Q_PROPERTY(QString path READ getPath WRITE setPath)
    Q_PROPERTY(qint64 sectorSize READ getSectorSize WRITE setSectorSize)
    Q_PROPERTY(qint64 physSectorSize READ getPhysSectorSize WRITE setPhysSectorSize)
    Q_PROPERTY(qint64 length READ getLength WRITE setLength)
    Q_PROPERTY(int type READ getType WRITE setType)

    Q_PROPERTY(QString diskType READ getDiskType WRITE setDiskType)

    QString     path;
    qint64      sectorSize;            /**< logical sector size */
    qint64      physSectorSize;       /**< physical sector size */
    qint64      length;                 /**< device length (LBA) */
    int type;

    QString     diskType;
public:
    explicit DeviceInfo(QObject* parent = nullptr);
    QString getPath() const;
    void setPath(const QString &value);
    qint64 getSectorSize() const;
    void setSectorSize(qint64 value);
    qint64 getPhysSectorSize() const;
    void setPhysSectorSize(qint64 value);
    qint64 getLength() const;
    void setLength(qint64 value);
    int getType() const;
    void setType(int value);
    QString getDiskType() const;
    void setDiskType(const QString &value);

public:
    QList<PartitionInfo *> m_partitions;
};


#endif // DEVICEINFO_H
