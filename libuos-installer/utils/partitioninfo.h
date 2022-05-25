#ifndef PARTITIONINFO_H
#define PARTITIONINFO_H

#include "propertyreflection.h"

#include <QVariant>

class PartitionInfo : public PropertyReflection
{
    Q_OBJECT
    Q_PROPERTY(PartitionType type READ getType WRITE setType)
    Q_PROPERTY(QString fsType READ getFsType WRITE setFsType)
    Q_PROPERTY(QList<QVariant> flags READ getFlags WRITE setFlags)

    Q_PROPERTY(qint64 type READ getStartSector WRITE setStartSector)
    Q_PROPERTY(qint64 type READ getEndSector WRITE setEndSector)
    Q_PROPERTY(qint64 type READ getNumSector WRITE setNumSector)

public:
    explicit PartitionInfo(QObject *parent = nullptr);

    enum PartitionType { // _PedPartitionType
        PARTITION_NORMAL            = 0x00,
        PARTITION_LOGICAL           = 0x01,
        PARTITION_EXTENDED          = 0x02,
        PARTITION_FREESPACE         = 0x04,
        PARTITION_METADATA          = 0x08,
        PARTITION_PROTECTED         = 0x10,

        Unallocated                 = PARTITION_FREESPACE | PARTITION_LOGICAL
    };
    Q_ENUM(PartitionInfo::PartitionType)
    enum PartitionFlag { // _PedPartitionFlag
        PARTITION_BOOT=1,
        PARTITION_ROOT=2,
        PARTITION_SWAP=3,
        PARTITION_HIDDEN=4,
        PARTITION_RAID=5,
        PARTITION_LVM=6,
        PARTITION_LBA=7,
        PARTITION_HPSERVICE=8,
        PARTITION_PALO=9,
        PARTITION_PREP=10,
        PARTITION_MSFT_RESERVED=11,
        PARTITION_BIOS_GRUB=12,
        PARTITION_APPLE_TV_RECOVERY=13,
        PARTITION_DIAG=14,
        PARTITION_LEGACY_BOOT=15,
        PARTITION_MSFT_DATA=16,
        PARTITION_IRST=17,
        PARTITION_ESP=18
    };
    Q_ENUM(PartitionFlag)

    PartitionType getType() const;
    void setType(const PartitionType &value);

    QList<QVariant> getFlags() const;
    void setFlags(const QList<QVariant> &value);
    void appendFlag(PartitionFlag flag);

    QString getFsType() const;
    void setFsType(const QString &value);

    qint64 getStartSector() const;
    void setStartSector(const qint64 &value);

    qint64 getEndSector() const;
    void setEndSector(const qint64 &value);

    qint64 getNumSector() const;
    void setNumSector(const qint64 &value);

private:
    PartitionType type;
    QString       fsType;
    QList<PartitionFlag> flags;

    qint64 startSector;
    qint64 endSector;
    qint64 numSector;

};

#endif // PARTITIONINFO_H
