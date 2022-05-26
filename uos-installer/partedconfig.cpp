#include "partedconfig.h"
#include "gpartedinfo.h"
#include "gparteditem.h"
#include "parameter.h"
#include "utils/utils.h"
#include "protocol/serverstate.h"

#include <QDebug>

#include <iostream>

static const qint64 GByte = 1024*1024*1024;

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


    for (const DeviceInfo* &info : m_devicelist) {
        qInfo() << info->getPath() << info->getSectorSize() << info->getLength() << (1.0 * info->getSectorSize() * info->getLength()/GByte);
    }
    // 默认分区方案

    // 需要添加efi分区
    if (ServerState::Instance()->getEfi()) {
        GPartedItem item{"fat32", "EFI", "/boot/efi", "usage"};
        m_data->appendItem(&item);
    }
    { // boot分区
        GPartedItem item{"ext4", "Boot", "/boot", "usage"};
        m_data->appendItem(&item);
    }
    { // 可选的
        GPartedItem item{"linux-swap", "SWAP", "swap", "usage"};
        m_data->appendItem(&item);
    }
    { // 根
        GPartedItem item{"ext4", "Roota", "/", "usage"};
        m_data->appendItem(&item);
    }
    { // 根
        GPartedItem item{"ext4", "Rootb", "", "usage"};
        m_data->appendItem(&item);
    }
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
