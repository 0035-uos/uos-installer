#include <QCoreApplication>


#include <QDebug>
#include <QString>

#include <parted/parted.h>




int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);

//    return a.exec();

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
