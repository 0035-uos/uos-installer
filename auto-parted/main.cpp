#include <QCoreApplication>


#include <QDebug>
#include <QString>
#include <QProcess>
#include <QStringList>

#include <parted/parted.h>


void test_1();

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);

//    return a.exec();

    test_1();
    return 0;


    PedDevice* pDevice = nullptr;
    ped_device_probe_all();
    while ((pDevice = ped_device_get_next(pDevice))) {
        if (!(QString(pDevice->path).contains("/dev/sdb"))) {
            qInfo() << "skip:" << pDevice->path;
            continue;
        }
        PedDisk *pDisk = nullptr;
        PedDiskType *pDiskType = nullptr;
        PedPartition *pPartition = nullptr;

        qInfo() << pDevice->path << pDevice->sector_size \
                << pDevice->phys_sector_size << pDevice->length << pDevice->type;

        pDiskType = ped_disk_probe(pDevice);
        if (pDiskType) {
            qInfo() << pDiskType->name << pDiskType->features;
        }
        pDisk = ped_disk_new(pDevice);
        if (pDisk) {
            int num = ped_disk_get_last_partition_num(pDisk);
            //ped_disk_delete_all(pDisk);
            qInfo() << num;
            while (num > 0) {
                pPartition = ped_disk_get_partition(pDisk, --num);
                if (pPartition) {
                    qInfo() << pPartition->fs_type << pPartition->num;
                    qInfo() << pPartition->part_list->disk->dev->path;
                }
            }
        }
        if (strcasecmp(pDevice->path, "/dev/sdb") == 0) {
            int iRet;
            // create partition
#if 0
            pDiskType = ped_disk_type_get("msdos");

            pDisk = ped_disk_new_fresh(pDevice, pDiskType);
            if (pDisk) {
                do {
                    PedFileSystemType *pfs_type;
                    pfs_type = ped_file_system_type_get("ext4");
                    pPartition = ped_partition_new(pDisk, PED_PARTITION_NORMAL, pfs_type, \
                                                   63, 2000000);
                    if (pPartition) {
                        iRet = ped_disk_add_partition(pDisk, pPartition, \
                                                      ped_constraint_exact(&pPartition->geom));
                        if (iRet == 0) {
                            break;
                        }
                    }

                    pPartition = ped_partition_new(pDisk, PED_PARTITION_EXTENDED, NULL, 2000010, 25165824);
                    if (pPartition) {
                        iRet = ped_disk_add_partition(pDisk, pPartition, \
                                                      ped_constraint_exact(&pPartition->geom));
                        if (iRet == 0) {
                            break;
                        }
                    }

                    iRet = ped_disk_commit(pDisk);
                } while(false);

                ped_disk_destroy(pDisk);
            }
#endif
        }
    }

    return 0;
}

void EnableVG(bool enable) {
    const QString cmd { "vgchange" };
    QString output { "" };
    QString error  { "" };
    const QStringList args( QStringList() << "-a" << (enable ? "y":"n"));
    QProcess process;
    process.start(cmd, args);
    process.waitForStarted();
    output = process.readAllStandardOutput();
    error = process.readAllStandardError();
    if (!output.isEmpty()) {
        qInfo() << QString("EnableVG:{%1}").arg(output);
    }
}

void test_1() {
    bool enable_os_prober = false;

    // 0. Disable VG device
    // 1. List Devices
    // 1.1. Retrieve metadata of each device->
    // 2. List partitions of each device->
    // 3. Retrieve partition metadata.

    EnableVG(false);
    // 通过 pvdisplay -s 扫描出 LVM2PV 的path
    QProcess process;
    QStringList devicePathList;
    process.start("pvdisplay -s");
    process.waitForFinished();
    QString str = process.readLine();
    while (str.size() > 0) {
        str.replace("\n","");
        auto lst = str.split("\"");
        if (lst.size() == 3) {
            devicePathList.append(lst[1]);
        }
        str = process.readLine();
    }

    // Let libparted detect all devices and construct device list.
    ped_device_probe_all();

//    DeviceList devices;
//    const LabelItems label_items = ParseLabelDir();
//    const MountItemList mount_items = ParseMountItems();

//    OsProberItems os_prober_items;
//    if (enable_os_prober) {
//        RefreshOsProberItems();
//        os_prober_items = GetOsProberItems();
//    }

    // Walk through all devices.
    for (PedDevice* lp_device = ped_device_get_next(nullptr);
         lp_device != nullptr;
         lp_device = ped_device_get_next(lp_device)) {
        PedDiskType* disk_type = ped_disk_probe(lp_device);

        qInfo() << QString("DEVICE#:path:{%1} model:{%2} type:{%3}:{%4} sec:{%5}:{%6} len:{%7}: ro:{%8}")
                   .arg(lp_device->path)
                   .arg(lp_device->model)
                   .arg(lp_device->type)
                   .arg(disk_type != nullptr ? disk_type->name : "nullptr")
                   .arg(lp_device->sector_size)
                   .arg(lp_device->phys_sector_size)
                   .arg(lp_device->length)
                   .arg(lp_device->read_only);

        if (1 == lp_device->read_only) {
            qInfo() << QString("IGNORED:by readonly:{%1}, path:{%2}")
                       .arg(lp_device->read_only)
                       .arg(lp_device->path);
            continue;
        }

//#ifndef QT_DEBUG
        if (PED_DEVICE_LOOP == lp_device->type || PED_DEVICE_UNKNOWN == lp_device->type) {
            qInfo() << QString("IGNORED:by type:{%1} path:{%2}")
                       .arg(lp_device->type)
                       .arg(lp_device->path);
            continue;
        }
//#endif


        //Device::Ptr device(new Device);
        if (disk_type == nullptr) {
            // Current device has no partition table.
            //device->table = PartitionTableType::Empty;
            continue;
        }
        const QString disk_type_name(disk_type->name);
        if (disk_type_name == /*kPartitionTableGPT*/"gpt") {
            //device->table = PartitionTableType::GPT;
        } else if (disk_type_name == /*kPartitionTableMsDos*/"msdos") {
            //device->table = PartitionTableType::MsDos;
        } else {
            //device->table = PartitionTableType::Empty;
            qWarning() << "other type of device:" << lp_device->path
                       << disk_type->name << lp_device->type;
            continue;
        }

        PedDisk* lp_disk = nullptr;
        lp_disk = ped_disk_new(lp_device);

        if (lp_disk) {
            int max_prims = ped_disk_get_max_primary_partition_count(lp_disk);

            for (PedPartition* lp_partition = ped_disk_next_partition(lp_disk, nullptr);
                 lp_partition != nullptr;
                 lp_partition = ped_disk_next_partition(lp_disk, lp_partition)) {

                //Partition::Ptr partition (new Partition);
                if (lp_partition->type == PED_PARTITION_NORMAL) {
                    //partition->type = PartitionType::Normal;
                } else if (lp_partition->type == PED_PARTITION_EXTENDED) {
                    //partition->type = PartitionType::Extended;
                } else if (lp_partition->type ==
                           (PED_PARTITION_FREESPACE | PED_PARTITION_LOGICAL)) {
                    //partition->type = PartitionType::Unallocated;
                } else if (lp_partition->type == PED_PARTITION_LOGICAL) {
                    //partition->type = PartitionType::Logical;
                } else if (lp_partition->type == PED_PARTITION_FREESPACE) {
                    //partition->type = PartitionType::Unallocated;
                } else {
                    // Ignore other types
                    continue;
                }

                // Get partition flags when it is active.
                if (ped_partition_is_active(lp_partition)) {
                    for (PedPartitionFlag lp_flag = ped_partition_flag_next(static_cast<PedPartitionFlag>(NULL));
                         lp_flag; lp_flag = ped_partition_flag_next(lp_flag)) {
                        if (ped_partition_is_flag_available(lp_partition, lp_flag) &&
                                ped_partition_get_flag(lp_partition, lp_flag)) {
                            //flags.append(static_cast<PartitionFlag>(lp_flag));
                        }
                    }
                }
}}}
#if 0
                if (lp_partition->fs_type) {
                        /*
FsType GetFsTypeByName(const QString& name) {
    const QString lower = name.toLower();

    if (lower.isEmpty() || lower == kFsUnused) return FsType::Empty;
    if (lower.startsWith("linux-swap")) return FsType::LinuxSwap;

    return FS_TYPE_MAP.key(lower, FsType::Unknown);
}

*/
                        //partition->fs = GetFsTypeByName(lp_partition->fs_type->name);
                      // If ESP/Boot flag is set on fat16/fat32 partition,
                      // it shall be an EFI partition->
//                      if ((partition->fs == FsType::Fat32 || partition->fs == FsType::Fat16) &&
//                          partition->flags.contains(PartitionFlag::ESP)) {
//                        partition->fs = FsType::EFI;
//                      }
//                    } else {
//                      partition->fs = FsType::Unknown;
//                    }
//                    partition->start_sector = lp_partition->geom.start;
//                    partition->end_sector = lp_partition->geom.end;

//                    partition->partition_number = lp_partition->num;
                    /*

QString GetPartitionPath(PedPartition* lp_partition) {
  // Result of ped_partition_get_path() need to be freed by hand.
  char* lp_path = ped_partition_get_path(lp_partition);
  QString path;
  if (lp_path != nullptr) {
    path = lp_path;
    free(lp_path);
  }
  return path;
}
*/
//                    partition->path = GetPartitionPath(lp_partition);

//                    // Avoid reading additional filesystem information if there is no path.
//                    if (!partition->path.isEmpty() &&
//                        partition->type != PartitionType::Unallocated &&
//                        partition->type != PartitionType::Extended) {

//                      // Read label based on filesystem type
//                      ReadUsage(partition->path, partition->fs, partition->freespace,
//                                partition->length);
//                      // If LinuxSwap partition is not mount, it is totally free.
//                      if (partition->fs == FsType::LinuxSwap && partition->length <= 0) {
//                        partition->length = partition->getByteLength();
//                        partition->freespace = partition->length;
//                      }

//                      // Get partition name.
//                      partition->name = ped_partition_get_name(lp_partition);
//                    }
//                    partitions.append(partition);
//                  }


//                // If partition table is known, scan partitions in this device->
//                device->partitions = ReadPartitions(lp_disk);
//                // Add additional info to partitions.
//                for (Partition::Ptr partition : device->partitions) {
//                    partition->device_path = device->path;
//                    partition->sector_size = device->sector_size;

//                    // 判断是否是LVM2PV
//                    for (QString partitionPath : devicePathList) {
//                        if (partition->path == partitionPath) {
//                            partition->fs = FsType::LVM2PV;
//                        }
//                    }

//                    if (!partition->path.isEmpty() &&
//                            partition->type != PartitionType::Unallocated) {
//                        // Read partition label and os.
//                        const QString label_str = label_items.value(partition->path, GetPartitionLabel(partition));
//                        if (!label_str.isEmpty()) {
//                            partition->label = label_str;
//                        }
//                        for (const OsProberItem& item : os_prober_items) {
//                            if (item.path == partition->path) {
//                                partition->os = item.type;
//                                break;
//                            }
//                        }

//                        // Mark busy flag of this partition when it is mounted in system.
//                        for (const MountItem& mount_item : mount_items) {
//                            if (mount_item.path == partition->path) {
//                                partition->busy = true;
//                                break;
//                            }
//                        }
//                    }
//                }
//                ped_disk_destroy(lp_disk);

//            } else {
//                qCritical() << "Failed to get disk object:" << device->path;
//            }
//        }
    }
#endif
}


/*
bool ReadUsage(const QString& partition_path,
               FsType fs_type,
               qint64& freespace,
               qint64& total) {
  bool ok = false;
  switch (fs_type) {
    case FsType::Btrfs: {
      ok = ReadBtrfsUsage(partition_path, freespace, total);
      break;
    }
    case FsType::Ext2:
    case FsType::Ext3:
    case FsType::Ext4: {
      ok = ReadExt2Usage(partition_path, freespace, total);
      break;
    }
    case FsType::EFI:
    case FsType::Fat16:
    case FsType::Fat32: {
      ok = ReadFat16Usage(partition_path, freespace, total);
      break;
    }
    case FsType::Hfs:
    case FsType::HfsPlus: {
      break;
    }
    case FsType::Jfs: {
      ok = ReadJfsUsage(partition_path, freespace, total);
      break;
    }
    case FsType::LinuxSwap: {
      ok = ReadLinuxSwapUsage(partition_path, freespace, total);
      break;
    }
    case FsType::Nilfs2: {
      ok = ReadNilfs2Usage(partition_path, freespace, total);
      break;
    }
    case FsType::NTFS: {
      ok = ReadNTFSUsage(partition_path, freespace, total);
      break;
    }
    case FsType::Reiser4: {
      ok = ReadReiser4Usage(partition_path, freespace, total);
      break;
    }
 case FsType::Reiserfs: {
      ok = ReadReiserfsUsage(partition_path, freespace, total);
      break;
    }
    case FsType::Xfs: {
      ok = ReadXfsUsage(partition_path, freespace, total);
      break;
    }
    default: {
      ok = false;
      break;
    }
  }

  if (!ok) {
    freespace = -1;
    total = -1;
    qWarning() << "Failed to read usage:" << partition_path;
  }
  return ok;
}

*/


