#include "gdevices.h"
#include "utils/deviceinfo.h"
#include "utils/partitioninfo.h"
#include "gjson.h"

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
        if (PED_DEVICE_LOOP == pDevice->type \
                || PED_DEVICE_UNKNOWN == pDevice->type) {
            qInfo() << QString("IGNORED:by type:{%1} path:{%2}")
                       .arg(pDevice->type)
                       .arg(pDevice->path) << pDevice->type;
            continue;
        }
        PedDiskType* disk_type = ped_disk_probe(pDevice);

        DeviceInfo *info = new DeviceInfo;
        info->setPath(pDevice->path);
        info->setSectorSize(pDevice->sector_size);
        info->setPhysSectorSize(pDevice->phys_sector_size);
        info->setLength(pDevice->length);
        info->setType(int(pDevice->type));

        info->setDiskType(QString(disk_type->name)); // gpt/msdos
#if 0
        if (info->getDiskType() == "gpt" || info->getDiskType() == "msdos") {
            PedDisk* lp_disk = ped_disk_new(pDevice);
            scanDisk(lp_disk, info->m_partitions);
            ped_disk_destroy(lp_disk);
        } // 其他类型暂不处理(没用过)
#endif

        m_devices.append(info);
    }
}

void GDevices::scanDisk(void *device, QList<PartitionInfo *> &partitions)
{
    PedDisk* lp_disk = reinterpret_cast<PedDisk*>(device);
    if (!lp_disk) return;
    int max_prims = ped_disk_get_max_primary_partition_count(lp_disk);

    for (PedPartition* lp_partition = ped_disk_next_partition(lp_disk, nullptr);
         lp_partition != nullptr;
         lp_partition = ped_disk_next_partition(lp_disk, lp_partition)) {
        PartitionInfo *partition = new PartitionInfo;

        // normal/extended/freespace/logical/freespace
        partition->setType(PartitionInfo::PartitionType(lp_partition->type));
        //Partition::Ptr partition (new Partition);
        if (lp_partition->type == PED_PARTITION_NORMAL) {
            partition->setType(PartitionInfo::PARTITION_NORMAL);
        } else if (lp_partition->type == PED_PARTITION_EXTENDED) {
            partition->setType(PartitionInfo::PARTITION_EXTENDED);
        } else if (lp_partition->type ==
                   (PED_PARTITION_FREESPACE | PED_PARTITION_LOGICAL)) {
            partition->setType(PartitionInfo::Unallocated);
        } else if (lp_partition->type == PED_PARTITION_LOGICAL) {
            partition->setType(PartitionInfo::PARTITION_LOGICAL);
        } else if (lp_partition->type == PED_PARTITION_FREESPACE) {
            partition->setType(PartitionInfo::Unallocated);
        } else {
             //Ignore other types
            continue;
        }

        // Get partition flags when it is active.
        if (ped_partition_is_active(lp_partition)) {
            for (PedPartitionFlag lp_flag = ped_partition_flag_next(static_cast<PedPartitionFlag>(NULL));
                 lp_flag; lp_flag = ped_partition_flag_next(lp_flag)) {
                if (ped_partition_is_flag_available(lp_partition, lp_flag) &&
                        ped_partition_get_flag(lp_partition, lp_flag)) {
                    partition->appendFlag(PartitionInfo::PartitionFlag(lp_flag));
                }
            }
        }

        if (lp_partition->fs_type) {}

        partitions.append(partition);
    }
}


