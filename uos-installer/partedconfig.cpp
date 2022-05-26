#include "partedconfig.h"
#include "gpartedinfo.h"
#include "gparteditem.h"
#include "parameter.h"
#include "utils/utils.h"
#include "protocol/serverstate.h"

#include <QDebug>

#include <iostream>

static const qint64 GByte = 1024*1024*1024;
static const qint64 MByte = 1024*1024;

PartedConfig::PartedConfig(QObject *parent) : ConfigInterface(parent)
{
    m_data = new GPartedInfo(Parameter::Instance()->getPartedFile());
}

void PartedConfig::initData()
{
    m_devicelist.clear();
}

void PartedConfig::run()
{
    /// undo
    /// 1. 自动分区（默认状态）
    /// 2. 根据架构和启动方式以及硬盘大小确定需要那些分区
    /// 3. 用户交互式分区
    /// 4. 根据用户导入的配置文件来分区（oem定制）

    DeviceInfo* dev = nullptr;
    for (const DeviceInfo* &info : m_devicelist) {
        qInfo() << info->getPath() << info->getSectorSize() << info->getLength() << (1.0 * info->getSectorSize() * info->getLength()/GByte);
        if (m_defaultDevicePath == info->getPath()) {
            dev = const_cast<DeviceInfo*>(info);
            break;
        }
    }
    if (!dev) {
        qWarning() << "invalid device " << m_defaultDevicePath;
        qApp->exit(0);
        return;
    }
    // 默认分区方案

    qint64 dev_size = dev->getSectorSize() * dev->getLength()/GByte;

    // check dev_size

    qint64 efi_size = 385 * MByte;
    qint64 free_sector = dev->getLength();
    qint64 efi_sector = efi_size / dev->getSectorSize();
    // 需要添加efi分区 不小于300MB  推荐385MB
    if (ServerState::Instance()->getEfi()) {
        GPartedItem item{"fat32", "EFI", "/boot/efi", QString::number(efi_sector)};
        m_data->appendItem(&item);
    }

    qint64 swapSpace =  ServerState::Instance()->getMemTotal() * 2;
    if (ServerState::Instance()->getMemTotal() > 2 *  GByte) {
        swapSpace = ServerState::Instance()->getMemTotal()  + 2 *  GByte;
    }
    qint64 swapSector = swapSpace / dev->getSectorSize();
    if (swapSector > free_sector*.2) {
        swapSector = qint64(free_sector*.2);
    }
    {
        GPartedItem item{"linux-swap", "SWAP", "swap", QString::number(swapSector)};
        m_data->appendItem(&item);
    }
    free_sector = free_sector - efi_sector - swapSector;

    // 兼容pmon固件
    if (Tools::is_x86()) {
        qint64 boot_sector = qint64(1.5 * GByte / dev->getSectorSize());
        GPartedItem item{"ext3", "Boot", "/boot", QString::number(boot_sector)};
        m_data->appendItem(&item);
        free_sector -= boot_sector;
    }

    qint64 parted_limit = 64 * GByte / dev->getSectorSize(); // undo
    if (free_sector >= parted_limit) { // /(%40) + /data(60%)
        qint64 roota_sector = qint64(free_sector * .4);
        {
            GPartedItem item{"ext4", "Roota", "/", QString::number(roota_sector)};
            m_data->appendItem(&item);
        }
        free_sector -= roota_sector;
        {
            GPartedItem item{"ext4", "_dde_data", "/data", QString::number(free_sector)};
            m_data->appendItem(&item);
        }
    } else { // /(100%)
        GPartedItem item{"ext4", "Roota", "/", QString::number(free_sector)};
        m_data->appendItem(&item);
    }

    ///  自定义 undo

#if 0
    { // 根 deepin的备份还原的需求/ 大小和Roota相同
        GPartedItem item{"ext4", "Rootb", "", "usage"};
        m_data->appendItem(&item);
    }
#endif
    m_data->commitData();
}

void PartedConfig::cleanData()
{

}

GJson *PartedConfig::data()
{
    return m_data;
}

void PartedConfig::appendDevice(const DeviceInfo *info)
{
    m_devicelist.append(info);
}

QString PartedConfig::defaultDevicePath() const
{
    return m_defaultDevicePath;
}

void PartedConfig::setDefaultDevicePath(const QString &defaultDevicePath)
{
    m_defaultDevicePath = defaultDevicePath;
}
